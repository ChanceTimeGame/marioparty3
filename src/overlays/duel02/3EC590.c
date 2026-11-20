#include "common.h"

// board da1: duel01's declarations (duel01.h), renamed to duel02
#include "process.h"
#include "common_structs.h"
#include "malloc.h"
#include "game/board.h"

typedef struct unkStruct {
/* 0x00 */ s16 unk_00;
/* 0x02 */ s16 unk_02;
/* 0x04 */ s16 unk_04;
} unkStruct;
typedef struct unkStruct01 {
/* 0x00 */ f32 unk_00;
/* 0x04 */ char unk_04[4];
/* 0x08 */ f32 unk_08;
} unkStruct01;

typedef struct unkStruct02 {
/* 0x00 */ Vec unk_00;
/* 0x0C */ char unk_0C[4];
} unkStruct02;

typedef struct unkStruct03 {
/* 0x00 */ char unk_00[0x18];
/* 0x18 */ HeapNode* unk_18;
/* 0x1C */ char unk_1C[0x70];
/* 0x8C */ unkStruct02* unk_8C;
} unkStruct03;

typedef struct unkStruct04 {
/* 0x00 */ char unk_00[0x0C];
/* 0x0C */ Vec unk_0C;
} unkStruct04;

typedef struct unkStruct05 {
/* 0x00 */ char unk_00[0x24];
/* 0x24 */ s32 unk_24;
} unkStruct05;

typedef struct unkStruct06 {
/* 0x00 */ s32 unk_00;
/* 0x04 */ s32 unk_04;
/* 0x08 */ f32 unk_08;
/* 0x0C */ char unk_0C[4];
} unkStruct06;

extern s16 omovlevtno;
f32 func_800D76D0_name_81(void*);
void func_80100CEC_name_81(u8);
s32 func_800E1824_name_81(s32, s32, s32);
s32 func_800E88FC_name_81(void);
void func_800E1854_name_81(s32);
extern s32 D_80117600_duel02;
extern s32 D_80117604_duel02;
extern s32 D_80117608_duel02;
extern s32 D_8011760C_duel02;
void func_800E94D0_name_81(void);
void func_800E9564_name_81(void);
void func_800E9B10_name_81(s32, s32);
void func_800E9D9C_name_81(void);
void func_800E9F4C_name_81(s32, s8*, s8*);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s32, s8, s8);
void func_800EB708_name_81(Vec*, Vec*, Vec*); // duel b1: was (s32, s32, unkStruct01*)
unkStruct03* func_80047EA0_main(void*, s32, s32, s32);
void func_80105CC4_duel02(void); //probably takes object as arg
void func_800FC8C4_name_81(void*);
extern Vec D_80105540_name_81; // duel b1: was s32
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32); // duel b1: was (void*, s32, void*, f32)
Process* func_800EBF2C_name_81(Vec* from, Vec* to, Vec* out, s32 frames); // duel b1/b7: ovl_81 DFD60.c
void func_8010630C_duel02(void);
void func_8001C258_main(s16, s32, s32);
void func_8001C448_main(s16);
void func_8001C8E4_main(s16, u32);
Object* func_800D8010_name_81(u8, s32*); // b7: ovl_81 BFB40.c (was void*(s32, s32))
void func_800D8944_name_81(Object*);
void func_800D8F0C_name_81(Object*);
void func_80089A20_main(Vec*, s32);
void func_800D8E88_name_81(Object*); // duel b1: was (void)
s16 MBDGetCurrentPlayerIndex(void);
GW_PLAYER* MBDGetPlayerStruct(s32);
void func_800F38DC_name_81(s32, s32, s32);
// duel b1
#include "game/object.h"

typedef struct B1ThwompPrc {
/* 0x00 */ GW_PLAYER* player;
/* 0x04 */ Object* obj;
/* 0x08 */ s32 delay;
/* 0x0C */ s32 wait;
} B1ThwompPrc; // sizeof 0x10

typedef struct B1UnkBoard4 {
    /* 0x00 */ struct B1UnkBoard4* unk_00;
    /* 0x04 */ struct B1UnkBoard4* unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ f32* unk_10;
    /* 0x14 */ f32* unk_14;
    /* 0x18 */ s16* unk_18;
    /* 0x1C */ s16* unk_1C;
} B1UnkBoard4; // ovl_81's UnkBoard4

extern s16 D_80101994_name_81;
extern s32 D_80105620_name_81;
extern Object* D_80117610_duel02;
extern Object* D_80117614_duel02;
f64 fabs(f64);
void MBDCamera3Dto2D(Vec*, Vec2f*);
void MBDCameraPos2DGet(Vec2f*);
u16 MBDCameraPos2DSet(Vec2f*);
B1UnkBoard4* func_800F4528_name_81(s16, s16);
void func_800F4584_name_81(B1UnkBoard4*);
void func_800D7934_name_81(Vec*, f32);
void func_800D90D0_name_81(Object*, s16, u16);
void func_800EFB00_name_81(Object*);
void func_800EFABC_name_81(Object*);
void func_800FB0B8_name_81(Object*, s32, s32);
s32 func_800EFE20_name_81(f32);
void func_800FC888_name_81(s32);
Object* MBDGetPlayerPartnerRef(s32, s32);
void func_800D8F3C_name_81(Object*);
void func_800FAD04_name_81(s32);
void func_800FAE18_name_81(Object*, s16, s16);
void func_800FADB4_name_81(void);
void func_800ED214_name_81(s32);
// duel b1: a model's Y-rotation written straight into its HmfModel matrix (as ovl_81's func_800D9668 process does)
#define B1_MODEL_ROTY(obj, angle, mdl)                                                                        \
    sincosdf(angle, &HmfModelData[(obj)->omObj1->model[0]].mtx[8], &HmfModelData[(obj)->omObj1->model[0]].mtx[10]); \
    HmfModelData[(obj)->omObj1->model[0]].mtx[2] = -HmfModelData[(obj)->omObj1->model[0]].mtx[8];               \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[0] = mdl->mtx[10];                                                                                  \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =           \
        mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                                                       \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[5] = mdl->mtx[15] = 1.0f

extern s32 D_801165A0_duel02[]; // partner attack effect model ids, by level - 1 (read as u8)
extern char D_80117070_duel02[]; // "obj1"
extern s32 D_80105550_name_81;
extern s32 D_80105558_name_81;
extern s32 D_80105718_name_81;
extern s32 D_8010571C_name_81;
Process* func_800D9668_name_81(Object*, f32, f32, s32);
Process* func_800DCE40_name_81(s32, Vec*, Vec*, f32);
s32 func_800DD1E0_name_81(s32, char*);
void func_800DD2DC_name_81(s32, Vec*); // s16 in ovl_81
s32 func_800DD3B4_name_81(s32);
void func_800DD2BC_name_81(s32); // s16 in ovl_81
Process* func_800FAB68_name_81(Object*, s32, s32, s32, s32);
void func_800FAC1C_name_81(Vec*);
void func_8001C6A8_main(s32, f32);
void func_800EF7C8_name_81(Object*, f32, f32);
void func_800EF800_name_81(Object*);
void func_80106160_duel02(Object*, Object*, GW_PLAYER*, Vec*, Vec*, f32);
void func_800F0378_name_81(Object*, char*, s16);
void func_800EB804_name_81(Object*);
void func_800FAE98_name_81(Object*, s16, s16, s16, s16);
void func_8001C92C_main(s16, f32);
void MBDBackTPLvlSet(u8);
// duel b1: the same for an X rotation
#define B1_MODEL_ROTX(obj, angle, mdl)                                                                        \
    sincosdf(angle, &HmfModelData[(obj)->omObj1->model[0]].mtx[6], &HmfModelData[(obj)->omObj1->model[0]].mtx[5]); \
    HmfModelData[(obj)->omObj1->model[0]].mtx[9] = -HmfModelData[(obj)->omObj1->model[0]].mtx[6];               \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[10] = mdl->mtx[5];                                                                                  \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[1] = mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[7] = mdl->mtx[8] = mdl->mtx[11] =           \
        mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                                                       \
    mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                               \
    mdl->mtx[0] = mdl->mtx[15] = 1.0f
Process* func_800DCB04_name_81(s32, s32, Vec*, f32, s32);
void func_800D974C_name_81(Object*);
extern s32 D_8010554C_name_81;
typedef struct DuelB4HmfPart {
/* 0x00 */ char unk_00[0x14];
/* 0x14 */ f32 unk_14;
} DuelB4HmfPart;
extern Object *D_80100F44_name_81;
SpaceData *MBDMasuGet(s16);
Process *MBDCameraZoomMotStart(f32);
void *func_8001D33C_main(s16, char *);
void func_8002FD8C_main(s16, s16, char *, s16, s16);
void func_800D918C_name_81(Object *, s16, s16, s16, u16);
s32 func_800D9234_name_81(Object *);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB49C_name_81(s16, s32, s32, s32, s32, s32, s32);
void func_800EB58C_name_81(void);
Object *func_800EEC40_name_81(Vec *);
void func_800F74E4_name_81(s32);
void func_800FD620_name_81(void);
Object *func_800EDD50_name_81(Vec *);
void func_800EDDBC_name_81(void);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE0F4_name_81(s32);
void func_800EE468_name_81(s32);
void func_800EE74C_name_81(u32);
void func_800F3880_name_81(s32, s16, u16);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800FFCCC_name_81(void *);
void func_800E18C0_name_81(void);
s32 func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_800E24AC_name_81(s16, s16, s16, s16);
s16 func_8004ACE0_main(s16, s16);
// duel b4 (2)
extern s32 D_80101200_name_81[]; /* character name messages, 0x1C00 + chr (inner label of ovl_81's D_801011FC data) */
void func_800EA7D4_name_81(void);
void func_800EA898_name_81(s32, s32);
void func_800EA97C_name_81(void);
void Duel_PowerUpPartners(s32);
void Duel_PowerDownPartners(s32);
Process *func_800E4A74_name_81(s32);
Process *func_800EE40C_name_81(s32);
void func_8001C814_main(s16, s16, s16);
// duel b4 (3)
void Duel_SwapPartnerPositions(s32);
void func_800DD41C_name_81(Vec *);
void func_800DD554_name_81(void);
void func_800DD564_name_81(void);
void func_800DD570_name_81(void);
void func_800EB140_name_81(s32, s32);
// duel b4 (4)
typedef B1UnkBoard4 DuelB4SprGrp; /* ovl_81's UnkBoard4 (b7: one struct) */
void func_800EA8DC_name_81(void);
/* defined void in ovl_81 C5770.c, but it returns omAddPrcObj's Process* (retail reads v0) */
Process *func_800E0924_name_81(void);
void func_800F75EC_name_81(s32);
// duel b4 (5)
typedef struct DuelSpaceTbl {
    u8 idx[6];
} DuelSpaceTbl;
s32 func_800F8980_name_81(s32);

void func_801059D0_duel02(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel02(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80117600_duel02 = func_800E1824_name_81(0, 0xA0, 1);
    D_80117604_duel02 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80117608_duel02 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011760C_duel02 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel02(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80117600_duel02);
    func_800E1854_name_81(D_80117604_duel02);
    func_800E1854_name_81(D_80117608_duel02);
    func_800E1854_name_81(D_8011760C_duel02);
}

void func_80105B64_duel02(void) {
    GwSystem.current_board_index = 1;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105BA0_duel02(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x242);
    func_800E9F4C_name_81(0x1E, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(0x1D, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C68_duel02(Vec *arg0, Vec *arg1, Vec *arg2) { // duel b1: Vec* (was s32, s32, unkStruct01*)
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(temp_f20);
    arg2->z = cosdf(temp_f20);
}

// duel b1
void func_80105CC4_duel02(void) {
    Vec pos;
    Vec2f pos2D;
    unkStruct02 *work;
    f32 x;
    f32 y;
    f32 z;
    B1UnkBoard4 *spr;
    void *data;
    f32 height;
    s32 i;

    work = HuPrcCurrentGet()->user_data;
    x = work->unk_00.x;
    y = work->unk_00.y;
    z = work->unk_00.z;
    HuPrcSleep(5);
    HuVecCopyXYZ(&pos, x, y, z);
    MBDCamera3Dto2D(&pos, &pos2D);
    spr = func_800F4528_name_81(1, 0);
    data = DataRead(0x1301EC);
    *spr->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(spr->unk_0A, 0, *spr->unk_0C, 0);
    HuSprPriSet(spr->unk_0A, 0, 0x2010);
    HuSprAttrSet(spr->unk_0A, 0, 0);
    func_80054904_main(spr->unk_0A, 0, pos2D.x, pos2D.y);
    HuAudFXPlay(0x202);
    height = 20.0f;
    for (i = 0; i < 20; i++) {
        func_80054904_main(spr->unk_0A, 0, pos2D.x, pos2D.y - fabs(sindf(i * 20) * height));
        height -= 1.0f;
        if (height < 0.0f) {
            height = 0.0f;
        }
        HuPrcVSleep();
    }
    func_800F4584_name_81(spr);
    omDelPrcObj(NULL);
}

void *func_80105EB4_duel02(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105CC4_duel02, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

// duel b1
void func_80105F24_duel02(void) {
    Vec dest;
    Vec start;
    Process *process;
    B1ThwompPrc *work;
    GW_PLAYER *player;
    Object *obj;
    s32 wait;
    s32 delay;

    process = HuPrcCurrentGet();
    work = HuPrcCurrentGet()->user_data;
    player = work->player;
    obj = work->obj;
    delay = work->delay;
    wait = work->wait;
    delay -= 5;
    if (delay > 0) {
        HuPrcSleep(delay);
    }
    func_80105EB4_duel02((unkStruct04 *)obj);
    HuVecSubtract(&dest, &obj->coords, &player->player_obj->coords);
    if ((D_80105620_name_81 == 3) | (D_80105620_name_81 == 1)) {
        func_800D7934_name_81(&dest, -90.0f);
    } else {
        func_800D7934_name_81(&dest, 90.0f);
    }
    HuVecAdd(&dest, &dest, &obj->coords);
    HuVecCopy3F(&start, &obj->coords);
    func_800FB0B8_name_81(obj, 3, 0);
    D_80101994_name_81++;
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 2.0f));
    HuPrcChildWait();
    HuPrcSleep(wait);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 2.0f));
    func_8001C814_main(obj->omObj1->model[0], 0, 4);
    HuPrcChildWait();
    func_800EFB00_name_81(obj);
    func_800D90D0_name_81(obj, -1, 2);
    D_80101994_name_81--;
    omDelPrcObj(NULL);
}

// duel b1
Process *func_801060D4_duel02(GW_PLAYER *player, Object *obj, s32 delay, s32 wait) {
    Process *process;
    B1ThwompPrc *work;

    process = omAddPrcObj(func_80105F24_duel02, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(B1ThwompPrc));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->wait = wait;
    return process;
}

// duel b1
void func_80106160_duel02(Object *obj, Object *target, GW_PLAYER *player, Vec *dest, Vec *start, f32 dist) {
    Vec ofs;
    f32 angle;

    HuVecCopy3F(start, &obj->coords);
    if (target != NULL) {
        HuVecCopy3F(dest, &target->coords);
    } else {
        HuVecCopy3F(dest, &player->player_obj->coords);
    }
    func_800EB708_name_81(&obj->coords, dest, &obj->rot);
    angle = func_800D76D0_name_81(&obj->rot) + 180.0f;
    ofs.x = sindf(angle) * dist;
    ofs.y = 0.0f;
    ofs.z = cosdf(angle) * dist;
    HuVecAdd(dest, dest, &ofs);
}

void func_80106244_duel02(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

// duel b1: arg0/arg1 typed (were s32, unkStruct05*)
Process *func_80106264_duel02(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) { // duel b1: returns the camera move (was void)
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
    return process;
}

// duel b1: typed; b7: the frame count is the caller's fourth argument, passed through in $a3
Process *func_801062C4_duel02(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 frames) {
    Process *process;

    if (arg2 & 9) {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, frames);
    } else {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, frames);
    }
    return process;
}

// duel b1
void func_8010630C_duel02(void) {
    Vec2f base;
    Vec2f pos;
    unkStruct06 *work;
    s32 amp;
    s32 step;
    f32 ampf;
    f32 half;

    work = HuPrcCurrentGet()->user_data;
    amp = work->unk_00;
    step = work->unk_04;
    MBDCameraPos2DGet(&base);
    func_800FC888_name_81(0);
    while (amp >= 0) {
        pos.x = func_800EFE20_name_81(ampf = amp) + base.x - (half = amp / 2);
        pos.y = func_800EFE20_name_81(ampf) + base.y - half;
        MBDCameraPos2DSet(&pos);
        amp -= step;
        HuPrcVSleep();
        pos.x = func_800EFE20_name_81(ampf) + base.x - half;
        pos.y = func_800EFE20_name_81(ampf) + base.y - half;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
    }
    func_800FC888_name_81(4);
    omDelPrcObj(NULL);
}

Process *func_80106460_duel02(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_8010630C_duel02, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

// duel b1
void func_801064CC_duel02(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *obj;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
    case 0:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            obj = func_800D8010_name_81(0x28, 0);
            D_80117610_duel02 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            obj = func_800D8010_name_81(0x28, 0);
            D_80117614_duel02 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        break;
    case 1:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            func_800D8F3C_name_81(D_80117610_duel02);
            func_800D8E88_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            func_800D8F3C_name_81(D_80117614_duel02);
            func_800D8E88_name_81(partner);
        }
        break;
    case 2:
        switch (D_80105620_name_81) {
        case 1:
        case 3:
            if (player->stats.partners.frontID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 0);
                obj = func_800D8010_name_81(0x28, 0);
            D_80117610_duel02 = obj;
                HuVecCopy3F(&obj->coords, &partner->coords);
                HuVecCopy3F(&obj->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                obj = func_800D8010_name_81(0x28, 0);
            D_80117614_duel02 = obj;
                HuVecCopy3F(&obj->coords, &partner->coords);
                HuVecCopy3F(&obj->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        }
        break;
    case 3:
        switch (D_80105620_name_81) {
        case 1:
        case 3:
            if (player->stats.partners.frontID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 0);
                func_800D8F3C_name_81(D_80117610_duel02);
                func_800D8E88_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                func_800D8F3C_name_81(D_80117614_duel02);
                func_800D8E88_name_81(partner);
            }
            break;
        }
        break;
    }
}

void *func_80106744_duel02(s32 arg0) {
    Object *obj;

    obj = func_800D8010_name_81(arg0 & 0xFF, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0x1800);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    return obj;
}

void func_801067D8_duel02(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0); // duel b1: was ()
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

// duel b1: a partner charges at the target (level 1: with a stand-in model, level 2: spinning with a second effect model)
void func_8010682C_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    Process *spinPrc[2];
    Vec mid;
    Process *process;
    GW_PLAYER *player;
    HmfModel *mdl;
    Object *effect;
    Object *standIn;
    Object *effect2;
    f32 angle;
    f32 speed;
    s32 model;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    spinPrc[0] = NULL;
    spinPrc[1] = NULL;
    standIn = NULL;
    effect2 = NULL;
    model = -1;
    func_800FAD04_name_81(0);
    if (level == 1) {
        standIn = func_80106744_duel02(0x45);
    }
    effect = func_800D8010_name_81(D_801165A0_duel02[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_80106244_duel02();
    HuAudFXPlay(0x25A);
    func_800FAE18_name_81(partner, 0, 0);
    func_800EFABC_name_81(partner);
    func_800FAE18_name_81(partner, 1, 2);
    if (level == 2) {
        HuAudFXPlay(0x1D6);
        angle = 0.0f;
        for (speed = 0.0f; speed <= 30.0f; speed += 2.0f) {
            HuPrcVSleep();
            angle += speed;
            B1_MODEL_ROTY(partner, angle, mdl);
        }
        spinPrc[0] = func_800D9668_name_81(partner, angle, 30.0f, -1);
        HuVecCopy3F(&effect2->coords, &partner->coords);
        func_800D8E88_name_81(effect2);
        spinPrc[1] = func_800D9668_name_81(effect2, 0.0f, 30.0f, -1);
        HuPrcSleep(20);
    }
    func_80106160_duel02(partner, target, player, &dest, &start, 6.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
    if (level == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect2->coords, &dest, &effect2->coords, 3.0f));
    }
    func_80106264_duel02(target, player, flags, 3.0f);
    if (flags & 8) {
        func_801060D4_duel02(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        if (level == 1) {
            func_801067D8_duel02(standIn, &partner->coords);
        }
        if (flags & 1) {
            HuVecAdd(&mid, &target->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C68_duel02(&target->coords, &standIn->coords, &standIn->rot);
                func_801067D8_duel02(standIn, &target->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80117070_duel02);
                func_800DD2DC_name_81(model, &mid);
            }
        } else {
            HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C68_duel02(&player->player_obj->coords, &standIn->coords, &standIn->rot);
                func_801067D8_duel02(standIn, &player->player_obj->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80117070_duel02);
                func_800DD2DC_name_81(model, &mid);
            }
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &start, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
    if (level == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect2->coords, &start, &effect2->coords, 3.0f));
    }
    HuPrcChildWait();
    func_800D8F0C_name_81(effect);
    if (spinPrc[0] != NULL) {
        omDelPrcObj(spinPrc[0]);
    }
    if (level == 2) {
        if (spinPrc[1] != NULL) {
            omDelPrcObj(spinPrc[1]);
        }
        func_800D8F0C_name_81(effect2);
    }
    B1_MODEL_ROTY(partner, 0.0f, mdl);
    func_800FAE18_name_81(partner, 0, 0);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_8001C6A8_main(partner->omObj1->model[0], 1000.0f);
    func_800EFB00_name_81(partner);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(effect);
    if (level == 1) {
        func_800D8F3C_name_81(standIn);
    } else {
        func_800D8F3C_name_81(effect2);
        if (model != -1) {
            while (func_800DD3B4_name_81(model) == 0) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(model);
        }
    }
    func_800FADB4_name_81();
}

// duel b1: a partner jumps on the target (level 2: spinning, with a second effect model)
void func_8010718C_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    s32 standInIds[2];
    Vec mid;
    Vec *midp;
    Process *process;
    Object *standIn;
    GW_PLAYER *player;
    HmfModel *mdl;
    Object *effect;
    Object *effect2;
    Process *spinPrc;
    s32 i;
    f32 speed;
    f32 jumpSpeed;
    f32 jumpGravity;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    effect2 = NULL;
    standInIds[0] = 0x48;
    standInIds[1] = 0x49;
    spinPrc = NULL;
    standIn = func_80106744_duel02(standInIds[level - 1]);
    effect = func_800D8010_name_81(D_801165A0_duel02[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_800FAD04_name_81(1);
    func_800D90D0_name_81(partner, 0, 2);
    func_80106160_duel02(partner, target, player, &dest, &start, 7.0f);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
    HuPrcChildWait();
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        HuVecCopy3F(&effect2->coords, &partner->coords);
        func_800D8E88_name_81(effect2);
        spinPrc = func_800D9668_name_81(effect2, 0.0f, 30.0f, -1);
        jumpSpeed = 3.0f;
        jumpGravity = -0.375f;
        func_800EF7C8_name_81(effect2, jumpSpeed, jumpGravity);
        func_800D8E88_name_81(effect);
        func_800EF7C8_name_81(effect, jumpSpeed, jumpGravity);
    }
    func_800FAE18_name_81(partner, 0, 2);
    speed = level + 1.0f;
    func_800EF7C8_name_81(partner, speed, -speed / 8.0f);
    if (level == 2) {
        for (i = 0; i < 8; i++) {
            B1_MODEL_ROTY(partner, i * 45.0f, mdl);
            HuPrcVSleep();
        }
        B1_MODEL_ROTY(partner, 0.0f, mdl);
    } else {
        HuPrcSleep(8);
    }
    partner->velocity.z = 0.0f;
    func_800FAE18_name_81(partner, 1, 0);
    if (level == 2) {
        if (spinPrc != NULL) {
            omDelPrcObj(spinPrc);
        }
        func_800D8F0C_name_81(effect2);
        func_800D8F0C_name_81(effect);
    }
    if (flags & 8) {
        func_801060D4_duel02(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        func_801067D8_duel02(standIn, &partner->coords);
        HuAudFXPlay(0x25B);
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += partner->velocity.x;
        func_801067D8_duel02(standIn, midp);
        if (level == 2) {
            func_800DCE40_name_81(0x4B, &mid, NULL, 2.0f);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    func_800EFABC_name_81(partner);
    partner->velocity.z = -(level + 1.0f) / 8.0f;
    func_800EF800_name_81(partner);
    func_800EB708_name_81(&partner->coords, &start, &partner->rot);
    func_800D90D0_name_81(partner, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &start, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
    HuPrcChildWait();
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(standIn);
    func_800D8F3C_name_81(effect);
    if (level == 2) {
        func_800D8F3C_name_81(effect2);
    }
    func_800FADB4_name_81();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117070_duel02);

// duel b1: a partner swings a hooked item at the target
// decomp-permuter
void func_801079BC_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level)
{
  Vec dest;
  Vec start;
  s32 standInIds[2];
  s32 effectIds[2];
  Vec mid;
  Vec *midp;
  Process *process;
  GW_PLAYER *player;
  Object *effect;
  Object *standIn;
  Object *hook;
  player = MBDGetPlayerStruct(targetIndex);
  process = HuPrcCurrentGet();
  standInIds[0] = 0x54;
  standInIds[1] = 0x55;
  effectIds[0] = 0x4E;
  effectIds[1] = 0x4A;
  func_800FAD04_name_81(2);
  standIn = func_80106744_duel02(standInIds[level - 1]);
  effect = func_800D8010_name_81(D_801165A0_duel02[level - 1] & 0xFF, 0);
  func_8001C8E4_main(effect->omObj1->model[0], 0);
  func_8001C448_main(effect->omObj1->model[0]);
  func_800D8944_name_81(effect);
  func_800D8F0C_name_81(effect);
  hook = func_800D8010_name_81(0x3F, 0);
  func_800D8F0C_name_81(hook);
  func_800F0378_name_81(partner, "item_hook", hook->omObj1->model[0]);
  func_800D90D0_name_81(partner, 0, 2);
  func_80106160_duel02(partner, target, player, &dest, &start, 6.0f);
  func_80106244_duel02();
  func_80106264_duel02(target, player, flags, 3.0f);
  HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
  func_800D8E88_name_81(effect);
  func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
  HuVecCopy3F(&effect->coords, &partner->coords);
  func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
  HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
  HuPrcChildWait();
  func_800D8F0C_name_81(effect);
  func_800D8E88_name_81(hook);
  if (level == 2)
  {
    func_800FAE18_name_81(partner, 0, 0);
    HuAudFXPlay(0x1D8);
    HuPrcSleep(6);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_800EFB00_name_81(partner);
    func_800FAE18_name_81(partner, 0, 0);
    HuAudFXPlay(0x1D8);
    HuPrcSleep(6);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_800EFB00_name_81(partner);
  }
  func_800FAE18_name_81(partner, 0, 0);
  HuAudFXPlay(0x1D8);
  if (flags & 8)
  {
    func_801060D4_duel02(player, target, 0, 20);
  }
  else
  {
 do { HuPrcSleep(9); HuAudFXPlay(0x1D7); if (level == 2) { HuAudFXPlay(0x1F2); } midp = &mid; if (flags & 1) { HuVecAdd(midp, &target->coords, &partner->coords); } else { HuVecAdd(midp, &player->player_obj->coords, &partner->coords); } HuVecMulScalar(midp, 0.5f, midp); func_800EB804_name_81(standIn); func_801067D8_duel02(standIn, midp); } while (0);
    func_800DCE40_name_81(effectIds[level - 1], &mid, 0, 2.0f);
    func_800FAC1C_name_81(&D_80105540_name_81);
    if (flags & 1)
    {
      func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
    }
    if (flags & 2)
    {
      func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
    }
  }
  func_800EFABC_name_81(partner);
  func_800D8F0C_name_81(hook);
  func_800EB708_name_81(&partner->coords, &start, &partner->rot);
  func_800D90D0_name_81(partner, 0, 2);
  HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
  func_800D8E88_name_81(effect);
  func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
  HuVecCopy3F(&effect->coords, &partner->coords);
  func_800EB708_name_81(&effect->coords, &start, &effect->rot);
  HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
  HuPrcChildWait();
  func_800D90D0_name_81(partner, -1, 2);
  func_800ED214_name_81(playerIndex);
  func_800D8F3C_name_81(hook);
  func_800D8F3C_name_81(standIn);
  func_800D8F3C_name_81(effect);
  func_800FADB4_name_81();
}

// duel b1: a partner throws itself at the target (or straight at the player) and explodes
void func_80107EC0_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec ofs;
    s32 standInIds[2];
    Vec mid;
    Object *blast;
    GW_PLAYER *player;
    Object *standIn;
    Object *effect;
    Object *orig;
    Process *process;
    f32 angle;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    blast = NULL;
    standInIds[0] = 0x4F;
    standInIds[1] = 0x52;
    standIn = func_80106744_duel02(standInIds[level - 1]);
    HuVecCopyXYZ(&standIn->scale, 2.0f, 2.0f, 2.0f);
    if (level == 2) {
        HuPrcVSleep();
        blast = func_80106744_duel02(0x5B);
        HuPrcVSleep();
    }
    effect = func_800D8010_name_81(D_801165A0_duel02[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    func_800FAD04_name_81(3);
    if (level == 2) {
        func_800D8F0C_name_81(partner);
        orig = partner;
        partner = func_800D8010_name_81(0x27, 0);
        HuVecCopy3F(&partner->coords, &orig->coords);
        HuVecCopy3F(&partner->rot, &orig->rot);
    }
    func_800FAE98_name_81(partner, 0, 0, 5, 2);
    HuAudFXPlay(0x1DC);
    HuPrcSleep(20);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 2.0f);
    if (target != NULL) {
        HuVecCopy3F(&dest, &target->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        angle = func_800D76D0_name_81(&partner->rot) + 180.0f;
        ofs.x = sindf(angle) * 9.0f;
        ofs.y = 0.0f;
        ofs.z = cosdf(angle) * 9.0f;
        HuVecAdd(&dest, &dest, &ofs);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 2.0f));
        func_800D8E88_name_81(effect);
        func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
        HuVecCopy3F(&effect->coords, &partner->coords);
        func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 2.0f));
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        HuAudFXPlay(0x256);
        HuVecCopy3F(&dest, &player->player_obj->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        func_800EF7C8_name_81(partner, 7.5f, -0.825f);
        HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 15));
        HuPrcChildWait();
    } else {
        HuVecCopy3F(&dest, &player->player_obj->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        angle = func_800D76D0_name_81(&partner->rot) + 180.0f;
        ofs.x = sindf(angle) * 6.0f / 2.0f;
        ofs.y = 0.0f;
        ofs.z = cosdf(angle) * 6.0f / 2.0f;
        HuVecAdd(&dest, &dest, &ofs);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 2.0f));
        func_800D8E88_name_81(effect);
        func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
        HuVecCopy3F(&effect->coords, &partner->coords);
        func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 2.0f));
        HuAudFXPlay(0x256);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    }
    func_800D8F0C_name_81(partner);
    partner->coords.y += partner->velocity.x;
    HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
    HuVecMulScalar(&mid, 0.5f, &mid);
    if (level == 2) {
        func_801067D8_duel02(blast, &partner->coords);
        func_8001C92C_main(blast->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        func_801067D8_duel02(standIn, &mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (level == 1) {
        func_801067D8_duel02(standIn, &mid);
        HuAudFXPlay(0x1DD);
    } else {
        HuAudFXPlay(0x1DE);
    }
    MBDBackTPLvlSet(0xFF);
    HuPrcVSleep();
    MBDBackTPLvlSet(0x40);
    func_800FAC1C_name_81(&D_80105540_name_81);
    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
    HuPrcSleep(30);
    if (level == 2) {
        func_800D8F3C_name_81(partner);
        func_800D8F3C_name_81(blast);
    }
    func_800D8F3C_name_81(effect);
    func_800D8F3C_name_81(standIn);
    func_800FADB4_name_81();
}

// duel b1
void func_801084A8_duel02(s32 playerIndex, s32 arg1, Object *partner, Object *target, s32 arg4, s32 count) {
    func_800FAD04_name_81(5);
    if (count == 2) {
        HuAudFXPlay(0x25D);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
    }
    HuAudFXPlay(0x25D);
    func_800FAE18_name_81(partner, 0, 0);
    func_800EFABC_name_81(partner);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800FADB4_name_81();
}

// duel b1: a partner rears up and slams down on the target (level 2: three slams, then a wobble)
#ifdef NON_MATCHING // duel b1: masked 0; float registers of the final squash loop ($f20/$f22/$f24) rotated
void func_80108554_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player;
    Process *process;
    Object *standIn;
    Object *dust;
    HmfModel *mdl;
    s32 model;
    s32 i;
    f32 amp;
    f32 height;
    f32 scale;
    f32 angle;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    model = -1;
    if (target == NULL) {
        HuPrcSleep(20);
        return;
    }
    standIn = func_80106744_duel02(0x55);
    func_80106160_duel02(partner, target, player, &dest, &start, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 3.0f);
    B1_MODEL_ROTX(partner, 20.0f, mdl);
    HuVecSubtract(&diff, &dest, &partner->coords);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
    for (i = 20; i > 0; i--) {
        B1_MODEL_ROTX(partner, i, mdl);
        HuPrcVSleep();
    }
    B1_MODEL_ROTX(partner, 0.0f, mdl);
    HuPrcSleep(5);
    for (height = 20.0f; height >= 0.0f; height -= 10.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    HuPrcSleep(10);
    if (target != NULL) {
        HuPrcSleep(10);
        for (height = 0.0f; height <= 24.0f; height += 2.0f) {
            partner->velocity.x = height;
            HuPrcVSleep();
        }
        HuVecCopy3F(&dest, &target->coords);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
        HuPrcChildWait();
        HuPrcSleep(10);
        if (flags & 8) {
            if (level == 1) {
                func_801060D4_duel02(player, target, 0, 55);
            } else {
                func_801060D4_duel02(player, target, 0, 120);
            }
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                partner->velocity.x = height;
                HuPrcVSleep();
            }
            if (level == 1) {
                HuAudFXPlay(0x1E7);
                HuAudFXPlay(0x1E8);
            } else {
                HuAudFXPlay(0x1E9);
            }
            func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
        } else {
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                scale = height / 24.0f;
                partner->velocity.x = height;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                if (scale < 0.1f) {
                    scale = 0.1f;
                }
                HuVecCopyXYZ(&target->scale, 1.0f, scale, 1.0f);
                HuPrcVSleep();
            }
            HuAudFXPlay((level == 1) ? 0x1F3 : 0x1E9);
            HuVecCopyXYZ(&target->scale, 1.0f, 0.1f, 1.0f);
            func_801064CC_duel02(targetIndex, 2);
            if (level == 1) {
                func_800EB804_name_81(standIn);
                func_801067D8_duel02(standIn, &target->coords);
                func_800DCE40_name_81(0x47, &target->coords, NULL, 1.0f);
            } else {
                dust = func_800D8010_name_81(0x5A, 0);
                func_800D974C_name_81(dust);
                HuVecCopy3F(&dust->coords, &partner->coords);
                model = func_800DD1E0_name_81(0xB0023, D_80117070_duel02);
                func_800DD2DC_name_81(model, &partner->coords);
            }
        }
        if (level == 1) {
            func_80106460_duel02(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, func_80106460_duel02(5, 2));
            HuPrcChildWait();
            for (i = 0; i < 3; i++) {
                for (height = 0.0f; height < 9.0f; height += 3.0f) {
                    partner->velocity.x = height;
                    HuPrcVSleep();
                }
                for (; height >= 0.0f; height -= 4.5f) {
                    partner->velocity.x = height;
                    HuPrcVSleep();
                }
                if (i == 2) {
                    HuAudFXPlay(0x1F3);
                    func_800EB804_name_81(standIn);
                    func_801067D8_duel02(standIn, &partner->coords);
                    func_800DCE40_name_81(0x47, &partner->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    dust = func_800D8010_name_81(0x5A, 0);
                    func_800D974C_name_81(dust);
                    HuVecCopy3F(&dust->coords, &partner->coords);
                }
                HuPrcChildLink(process, func_80106460_duel02(5, 2));
                HuPrcChildWait();
            }
            angle = func_800D76D0_name_81(&partner->rot);
            for (i = 0; i < 30; i++) {
                partner->rot.x = sindf(angle + sindf(i * 60) * (30 - i));
                partner->rot.z = cosdf(angle + sindf(i * 60) * (30 - i));
                HuPrcVSleep();
            }
            partner->rot.x = sindf(angle);
            partner->rot.z = cosdf(angle);
            HuPrcSleep(10);
        }
    }
    for (height = 0.0f; height <= 24.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    B1_MODEL_ROTX(partner, 20.0f, mdl);
    HuVecSubtract(&diff, &start, &partner->coords);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &start, &partner->coords, 20));
    for (i = 20; i > 0; i--) {
        B1_MODEL_ROTX(partner, i, mdl);
        HuPrcVSleep();
    }
    B1_MODEL_ROTX(partner, 0.0f, mdl);
    HuPrcSleep(5);
    for (height = 24.0f; height >= 0.0f; height -= 6.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
    func_800ED214_name_81(playerIndex);
    if (target != NULL && !(flags & 8)) {
        func_801064CC_duel02(targetIndex, 3);
        amp = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&target->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            amp -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&target->scale, 1.0f, 1.0f, 1.0f);
        func_800FAC1C_name_81(&D_80105540_name_81);
        func_800FAB68_name_81(target, -1, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
    }
    func_800D8F3C_name_81(standIn);
    if (model != -1) {
        while (func_800DD3B4_name_81(model) == 0) {
            HuPrcVSleep();
        }
        func_800DD2BC_name_81(model);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80108554_duel02);
#endif

// duel b1: a partner drifts into the target and fades out (and back in)
void func_80109408_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    Vec pos;
    GW_PLAYER *player;
    Process *process;
    s32 frames;
    s32 i;
    f32 scale;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    HuAudFXPlay(0x1F4);
    func_800D90D0_name_81(partner, 0, 2);
    func_80106160_duel02(partner, target, player, &dest, &start, 0.0f);
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 3.0f);
    dest.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    frames = HuVecGetLength3F(&diff) / 3.0f;
    partner->flags |= 1;
    if (flags & 8) {
        func_801060D4_duel02(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        for (i = 0; i < frames; i++) {
            func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 128) / frames);
            scale = 2.0f * i / frames + 1.0f;
            HuVecCopyXYZ(&partner->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
    } else {
        for (i = 0; i < frames; i++) {
            func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 128) / 10);
            scale = 2.0f * i / frames + 1.0f;
            HuVecCopyXYZ(&partner->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopy3F(&pos, &partner->coords);
        pos.y += 10.0f;
        func_800DCE40_name_81(0x44, &pos, NULL, 1.0f);
        HuPrcSleep(10);
        func_800DCE40_name_81(0x44, &pos, NULL, 1.0f);
        HuPrcSleep(12);
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_8010554C_name_81 & 8, D_8010571C_name_81);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_8010554C_name_81 & 1, -1);
        }
    }
    if (!(D_80105718_name_81 & 0x10)) {
        func_800ED214_name_81(playerIndex);
        HuVecCopyXYZ(&partner->scale, 1.0f, 1.0f, 1.0f);
        for (i = 0; i < 256; i += 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    }
}

// duel b1: a partner vanishes and reappears beside the target to strike (level 2: two blinks around the camera
// focus first); flag 0x10 in the level picks the fade-through attack instead
void func_8010988C_duel02(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec near;
    Vec dir;
    Vec mid;
    GW_PLAYER *player;
    Process *process;
    s32 seNo;
    s32 i;
    f32 baseAngle;
    s32 angle;
    Vec *midp;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    seNo = -1;
    if (level & 0x10) {
        func_80109408_duel02(playerIndex, targetIndex, partner, target, flags, 1);
        return;
    }
    level &= ~0x10;
    func_800D90D0_name_81(partner, 0, 2);
    func_80106160_duel02(partner, target, player, &near, &start, 6.0f);
    func_80106160_duel02(partner, target, player, &dest, &start, 8.0f);
    func_80106244_duel02();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    HuPrcChildLink(process, func_80106264_duel02(target, player, flags, 3.0f));
    HuPrcChildWait();
    if (level == 2) {
        seNo = HuAudFXPlay(0x1DF);
        func_800EB708_name_81(&D_80105540_name_81, &partner->coords, &dir);
        baseAngle = func_800D76D0_name_81(&dir);
        angle = baseAngle + 90.0f;
        HuVecCopyXYZ(&partner->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y,
                     D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_8001F9E4_main(partner->omObj2->model[0], 0);
        HuPrcVSleep();
        angle = baseAngle + -90.0f;
        HuVecCopyXYZ(&partner->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y,
                     D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_8001F9E4_main(partner->omObj2->model[0], 0);
        HuPrcVSleep();
    }
    HuVecCopy3F(&partner->coords, &dest);
    func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
    for (i = 0; i < 255; i += 10) {
        func_8001F9E4_main(partner->omObj1->model[0], i);
        func_8001F9E4_main(partner->omObj2->model[0], i);
        HuPrcVSleep();
        if (i == 160) {
            if (seNo != -1) {
                HuAudFXStop((s16)seNo);
            }
            HuAudFXPlay(0x257);
        }
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    func_8001F9E4_main(partner->omObj2->model[0], 0xFF);
    HuPrcSleep((level == 1) ? 10 : 3);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
    if (flags & 8) {
        if (level == 1) {
            func_801060D4_duel02(player, target, 0, 20);
        } else {
            func_801060D4_duel02(player, target, 0, 40);
        }
        HuPrcChildWait();
        if (level == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
            HuPrcChildWait();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
            HuPrcChildWait();
        }
    } else {
        HuPrcChildWait();
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += 3.0f;
        func_800DCE40_name_81(0x59, &mid, NULL, 1.0f);
        HuAudFXPlay(0x1E0);
        if (level == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
            HuPrcChildWait();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
            HuPrcChildWait();
            func_800DCE40_name_81(0x59, &mid, NULL, 1.0f);
            HuAudFXPlay(0x1E0);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
    HuPrcChildWait();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    func_800ED214_name_81(playerIndex);
    for (i = 0; i < 256; i += 10) {
        func_8001F9E4_main(partner->omObj1->model[0], i);
        func_8001F9E4_main(partner->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    func_8001F9E4_main(partner->omObj2->model[0], 0xFF);
}

// duel b2: local types and prototypes for func_8010A210..func_8010DB2C
#include "mallocblock.h"
typedef void (*DuelB2PartnerFunc)(s32, s32, Object *, Object *, s32, s32);

/* Sixteen sprite-billboard puffs (func_8010AFB4 creates, func_8010B130 moves). */
typedef struct DuelB2Puffs {
    /* 0x000 */ Vec pos[16];
    /* 0x0C0 */ Vec vel[16];
    /* 0x180 */ s16 active[16];
    /* 0x1A0 */ s16 spr[16];
    /* 0x1C0 */ s16 model[16];
    /* 0x1E0 */ s16 delay;
    /* 0x1E4 */ f32 life[16];
    /* 0x224 */ f32 scale[16];
} DuelB2Puffs; // sizeof 0x264

typedef struct DuelB2SprModel {
    /* 0x00 */ u16 model;
    /* 0x02 */ char unk_02[0x22];
} DuelB2SprModel; // sizeof 0x24

extern DuelB2SprModel *D_800CBB60_main;
extern Object *D_80117618_duel02;
extern omObjData *D_8011761C_duel02;
extern s32 D_801165A8_duel02[];

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;



Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
Object *func_800D8B18_name_81(Object *obj);
s32 func_800EF7D4_name_81(Object *obj);
Process *func_800DCC8C_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
void func_8010AAB4_duel02(Object *obj, s32 create);
void func_8010AD4C_duel02(Object *obj);
void func_8010AFB8_duel02(void);

u16 func_80014618_main(s16 index, u16 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_80014850_main(s16 index);
void func_80016638_main(s32 index);
void func_800166D0_main(void);
void func_800D7828_name_81(Vec *vec);
void func_800FAC94_name_81(DuelB2PartnerFunc *arg0, DuelB2PartnerFunc *arg1);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2); // defined with two parameters in E3CD0.c
void func_800EA46C_name_81(event_table_entry *arg0);
void func_800FC5A8_name_81(process_func arg0);
void func_800FC59C_name_81(s32 arg0);
void func_800FF640_name_81(u32 arg0);

void func_801079BC_duel02(s32, s32, Object *, Object *, s32, s32);
void func_80108554_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010A214_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010B134_duel02(omObjData *obj);

// board da1: duel01's func_8010A210 (duel b2), matched by assigning vel = &sp98 in each arm
void func_8010A214_duel02(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    Object *parts[16];
    Vec sp78;
    Vec sp88;
    Vec sp98;
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    Object *extra2;
    Object *extra1;
    s32 i;
    s32 count;
    Vec *vel;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    extra2 = NULL;
    func_800FAD04_name_81(0xA);
    if (variant == 2) {
        extra2 = func_80106744_duel02(0x51);
        HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    extra1 = func_80106744_duel02(0x4C);
    HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
    HuPrcVSleep();
    if (target != NULL) {
        HuVecCopy3F(&sp18, &target->coords);
    } else {
        HuVecCopy3F(&sp18, &player->player_obj->coords);
    }
    func_800EB708_name_81(&partner->coords, &sp18, &partner->rot);
    obj = func_800D8010_name_81(0x57, 0);
    func_800D8F0C_name_81(obj);
    HuVecCopy3F(&obj->coords, &partner->coords);
    obj->coords.y += 5.0f;
    sp18.y += 5.0f;
    if (variant == 2) {
        HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
        for (i = 0; i < 16; i++) {
            parts[i] = func_800D8B18_name_81(obj);
            HuVecCopy3F(&parts[i]->coords, &obj->coords);
            func_800D8F0C_name_81(parts[i]);
            HuVecCopyXYZ(&parts[i]->scale, 0.5f, 0.5f, 0.5f);
        }
    }
    func_800FAE18_name_81(partner, 0, 0);
    HuPrcSleep(0x14);
    func_800D8E88_name_81(obj);
    func_800EF7C8_name_81(obj, 3.0f, -0.18f);
    HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &sp18, &obj->coords, 0x1E));
    if (variant == 2) {
        for (i = 0; i < 16; i++) {
            HuVecCopy3F(&sp28, &sp18);
            sp28.x += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.y += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.z += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            func_800EF7C8_name_81(parts[i], 3.0f, -0.18f);
            HuPrcChildLink(process, func_800EBF2C_name_81(&parts[i]->coords, &sp28, &parts[i]->coords, 0x1E));
        }
    }
    HuAudFXPlay(0x1E1);
    func_80106244_duel02();
    func_801062C4_duel02(target, player, flags, 0x1E);
    if (flags & 8) {
        HuVecCopy3F(&sp78, &target->coords);
        sp78.y += 5.0f;
        func_801060D4_duel02(player, target, 0x19, 0x28);
        if (variant == 1) {
            HuPrcSleep(0x20);
        } else {
            HuPrcSleep(0x14);
            func_800D8F0C_name_81(obj);
            HuVecCopy3F(&sp88, &obj->coords);
            sp88.y += obj->velocity.x;
            HuVecSubtract(&sp98, &target->coords, &sp88);
            HuVecMulScalar(&sp98, 0.05f, &sp98);
            func_800DCC8C_name_81(0x4E, &sp88, &sp98, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(parts[i]);
                parts[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                parts[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
            HuPrcChildWait();
        }
        func_801067D8_duel02(extra1, &sp78);
        if (variant == 2) {
            func_801067D8_duel02(extra2, &sp78);
        }
    } else {
        if (variant != 1) {
            HuPrcSleep(0x14);
            func_800D8F0C_name_81(obj);
            HuVecCopy3F(&sp78, &obj->coords);
            sp78.y += obj->velocity.x;
            if (flags & 1) {
                HuVecSubtract(vel = &sp98, &target->coords, &sp78);
            } else {
                HuVecSubtract(vel = &sp98, &player->player_obj->coords, &sp78);
            }
            HuVecMulScalar(vel, 0.05f, vel);
            func_800DCC8C_name_81(0x4E, &sp78, &sp98, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(parts[i]);
                parts[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                parts[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
        }
        HuPrcChildWait();
        if (flags & 1) {
            HuVecCopy3F(&sp78, &target->coords);
        } else {
            HuVecCopy3F(&sp78, &player->player_obj->coords);
        }
        sp78.y += 5.0f;
        func_801067D8_duel02(extra1, &sp78);
        if (variant == 2) {
            func_801067D8_duel02(extra2, &sp78);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    if (variant == 2) {
        while (TRUE) {
            count = 0;
            for (i = 0; i < 16; i++) {
                if (func_800EF7D4_name_81(parts[i]) == 0) {
                    count++;
                    func_800D8F0C_name_81(parts[i]);
                }
            }
            if (i == count) {
                break;
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 16; i++) {
            func_800D8F3C_name_81(parts[i]);
        }
    }
    func_800D8F3C_name_81(obj);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    HuPrcSleep(0x1E);
    func_800D8F3C_name_81(extra1);
    if (variant == 2) {
        func_800D8F3C_name_81(extra2);
    }
    func_800FADB4_name_81();
}

/* A smoke puff (model 0x21) grows over obj; with create, model 8 (D_80119488) is made, then hidden at obj's place. */
void func_8010AAB4_duel02(Object *obj, s32 create) {
    Object *puff;
    f32 rot;
    f32 scale;

    if (create != 0) {
        D_80117618_duel02 = func_800D8010_name_81(8, D_801165A8_duel02);
        func_800D8944_name_81(D_80117618_duel02);
        func_800D8F0C_name_81(D_80117618_duel02);
    } else {
        HuPrcSleep(3);
    }
    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &obj->coords);
    puff->coords.y += 5.0f;
    HuAudFXPlay(0x1E3);
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    if (create != 0) {
        HuVecCopy3F(&D_80117618_duel02->coords, &obj->coords);
        HuVecCopy3F(&D_80117618_duel02->rot, &obj->rot);
        func_800D8E88_name_81(D_80117618_duel02);
        func_800D8F0C_name_81(obj);
    }
    for (; scale >= 1.0f; scale -= 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

/* Smoke puff over D_80119488: obj takes its place and hides, and that model is freed. */
void func_8010AD4C_duel02(Object *obj) {
    Object *puff;
    f32 rot;
    f32 scale;

    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &D_80117618_duel02->coords);
    puff->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &D_80117618_duel02->coords);
    HuVecCopy3F(&obj->rot, &D_80117618_duel02->rot);
    func_800D8F3C_name_81(D_80117618_duel02);
    func_800D8E88_name_81(obj);
    obj->flags &= ~1;
    for (; scale >= 1.0f; scale -= 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

void func_8010AFB8_duel02(void) {
    DuelB2Puffs *puffs;
    void *data;
    s32 i;

    func_800142A0_main(0x1A);
    D_8011761C_duel02 = omAddObj(0x1F4, 0, 0, -1, func_8010B134_duel02);
    puffs = D_8011761C_duel02->data = HuMemAllocTag(sizeof(DuelB2Puffs), 0x7918);
    data = DataRead(0xB0047);
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            puffs->spr[0] = HmfSprModelCreate(data, 0x1A0D, 8);
        } else {
            puffs->spr[i] = func_80014618_main(puffs->spr[0], 8);
        }
        func_800146DC_main(puffs->spr[i], 6, 0x180);
        puffs->model[i] = D_800CBB60_main[puffs->spr[i]].model;
        func_800147FC_main(puffs->spr[i], 0xFF, 0x40, 8);
        func_80014794_main(puffs->spr[i], 0xC8);
        func_8001C2FC_main(puffs->model[i], 0x70000000, 0x70000000);
    }
    DataClose(data);
    for (i = 0; i < 16; i++) {
        puffs->active[i] = 0;
    }
    D_8011761C_duel02->work[0] = 0;
    puffs->delay = 0;
}

void func_8010B134_duel02(omObjData *obj) {
    DuelB2Puffs *puffs = obj->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            puffs->pos[i].x += puffs->vel[i].x;
            puffs->pos[i].y += puffs->vel[i].y;
            puffs->pos[i].z += puffs->vel[i].z;
            if (puffs->pos[i].y < 0.0f) {
                puffs->pos[i].y = 0.0f;
            }
            Hu3DModelPosSet(puffs->model[i], puffs->pos[i].x, puffs->pos[i].y, puffs->pos[i].z);
            puffs->life[i] -= 2.0f;
            if (puffs->life[i] <= 0.0f) {
                puffs->active[i] = 0;
                func_8001C258_main(puffs->model[i], 4, 4);
                func_800146DC_main(puffs->spr[i], 0, 0x80);
            }
            puffs->scale[i] += 0.02f;
            if (puffs->scale[i] >= 3.0f) {
                puffs->scale[i] = 3.0f;
            }
            Hu3DModelScaleSet(puffs->model[i], puffs->scale[i], puffs->scale[i], puffs->scale[i]);
        }
    }
    if (obj->work[0] == 1) {
        if (puffs->delay == 0) {
            for (i = 0; i < 16; i++) {
                if (puffs->active[i] == 0) {
                    break;
                }
            }
            if (i != 16) {
                puffs->active[i] = 1;
                puffs->delay = 1;
                puffs->vel[i].x = D_80117618_duel02->rot.x;
                puffs->vel[i].y = -0.8f;
                puffs->vel[i].z = D_80117618_duel02->rot.z;
                func_800D7828_name_81(&puffs->vel[i]);
                puffs->vel[i].x = 2.0f * puffs->vel[i].x;
                puffs->vel[i].y = 2.0f * puffs->vel[i].y;
                puffs->vel[i].z = 2.0f * puffs->vel[i].z;
                puffs->pos[i].x = D_80117618_duel02->rot.x * 10.0f + D_80117618_duel02->coords.x;
                puffs->pos[i].z = D_80117618_duel02->rot.z * 10.0f + D_80117618_duel02->coords.z;
                puffs->pos[i].y = D_80117618_duel02->coords.y + 6.0f;
                puffs->life[i] = 15.0f;
                puffs->scale[i] = 0.1f;
                func_8001C258_main(puffs->model[i], 4, 0);
                func_80014850_main(puffs->spr[i]);
                Hu3DModelPosSet(puffs->model[i], puffs->pos[i].x, puffs->pos[i].y, puffs->pos[i].z);
                Hu3DModelScaleSet(puffs->model[i], puffs->scale[i], puffs->scale[i], puffs->scale[i]);
                func_8001C8A8_main(puffs->model[i], 1);
            }
        } else {
            puffs->delay--;
        }
    }
}



// board da2: declarations for func_8010B484_duel02..func_80110C7C_duel02 (from duel01)
void func_801100A8_duel02(s32);
extern Object *D_80117620_duel02;
extern f32 D_801165BC_duel02;
extern char D_80117128_duel02[];
void func_8010DC08_duel02(void);
s16 func_8010B484_duel02(void);
void func_8010B4C4_duel02(void);
void func_8010B52C_duel02(void);
void func_8010B540_duel02(void);
void func_8010CE6C_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010D428_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD8_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010B550_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010DCAC_duel02(void);
void func_8010DD40_duel02(void);
void func_8010E34C_duel02(void);
void func_8010EA10_duel02(void);
void func_8011394C_duel02(void);
s32 func_801163A4_duel02(void);
extern event_table_entry D_801167B8_duel02[];
extern event_table_entry D_80117008_duel02[];
Process *func_800DCE10_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay);
void func_8010DB30_duel02(void);
typedef struct Duel01Part {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Duel01Part;
extern s32 D_801165C0_duel02[];
extern s16 D_801165D0_duel02;
extern s16 D_801165D8_duel02;
extern s16 D_801165D2_duel02;
extern s16 D_801165DA_duel02;
extern Process *D_801165D4_duel02;
extern Process *D_801165DC_duel02;
extern Process *D_80117624_duel02;
extern Object *D_80117628_duel02;
extern Object *D_80117630_duel02;
extern f32 D_8011762C_duel02;
extern f32 D_80117634_duel02;
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;
extern s8 D_80116604_duel02[]; /* value, chance pairs */
extern Duel01Weight *D_80116700_duel02[8]; /* per character */
extern s32 D_80116740_duel02;
extern s32 D_80116738_duel02;
typedef B1UnkBoard4 Duel01SprGrp; /* ovl_81's sprite group (UnkBoard4 there) */
s32 func_800F37B8_name_81(s16 playerIndex);
void func_800E0310_name_81(u8 *output, s32 count);
extern u16 D_800C9520_main[];
s32 func_8010EDE0_duel02(void);
void func_8010EFFC_duel02(void);
void func_8010F16C_duel02(void);
void func_8010DF6C_duel02(Vec *pos);
void func_8010E00C_duel02(void);
void func_8010E2D0_duel02(void);
void func_8010E2FC_duel02(void);
void func_8010E578_duel02(Vec *pos);
void func_8010E618_duel02(void);
void func_8010E8DC_duel02(void);
void func_8010E908_duel02(void);
void func_800EB7BC_name_81(Vec *out);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Object *func_800F8050_name_81(s32 partnerID);
void func_800FC8DC_name_81(Object *arg0);
extern s32 D_80116720_duel02[2][3]; /* per player: three space ids (splat labels 7E/82/86 are low halves) */
extern Object *D_8011673C_duel02;
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
extern const DuelPadMask D_801171F4_duel02;
extern const DuelChoiceTbl D_801171F8_duel02;
extern s16 D_8010555C_name_81;
void func_800FB524_name_81(s32);
void func_800EB1D8_name_81(s32 arg0, s32 arg1);
s32 func_800EED50_name_81(void);
s32 func_8010EBC8_duel02(void);
s32 func_8010F9DC_duel02(s32 no);
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
extern const DuelB7VecTbl D_80117200_duel02; /* smoke puff offsets around a partner leaving */
extern s32 D_80101A1C_name_81[];             /* partner name messages, by partner id */
void func_800EAFC4_name_81(s32 mess);
void func_800EE0D0_name_81(s32 arg0);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
void func_800F8358_name_81(s32 playerIndex);
void func_800F57B0_name_81(s32 playerNo);
void func_800F5E2C_name_81(s32 playerNo);
void func_800ECF1C_name_81(s32 playerNo, Vec *front, Vec *back);
void func_800ED118_name_81(s32 playerNo, Vec *front, Vec *back);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800F821C_name_81(s32 playerIndex, s32 partnerNo);
s32 func_800F89D0_name_81(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, s16 arg3);
void func_800F5BB4_name_81(s32 playerIndex);
void func_800F5EB0_name_81(s32 playerIndex);
void func_800F7BB4_name_81(s32 playerNo, s32 set);
void func_800F7D94_name_81(s32 playerNo, s32 set);
void func_800FBDD4_name_81(void);
extern u8 D_80117224_duel02[]; /* window strings: the starting partner choices (SJIS) */
extern u8 D_8011730C_duel02[];
extern u8 D_801173F4_duel02[];
extern u8 D_801174DC_duel02[];
void func_8008A120_main(f32 *mtx, f32 angle); // defined with Matrix4f (f32[4][4])
void func_800F8108_name_81(s32 playerIndex);
void func_800F82EC_name_81(s32 playerIndex);
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
#define DUEL_B7_PICK(win, mess, cur, padMask, choice, buf, result, last)                                         \
    win = func_80061188_main(-1, 0x50, 0x50, 0xA0, 0x69, 0);                                                     \
    func_8005B63C_main(win, 0x40, 0x40);                                                                         \
    func_80061388_main(win);                                                                                     \
    func_8005FBA4_main(buf, mess);                                                                               \
    func_8005B43C_main(win, (s32)buf, -1, -1);                                                                   \
    while (func_8005E0C0_main(win) != 0) {                                                                       \
        HuPrcVSleep();                                                                                           \
    }                                                                                                            \
    if (func_800F37B8_name_81(cur) == 0) {                                                                       \
        func_8005FE54_main(win, padMask.mask[GwPlayer[cur].pad]);                                                \
        choice.choice[GwPlayer[cur].pad] = -1;                                                                   \
        func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);              \
    } else {                                                                                                     \
        if (GwPlayer[cur].chr == 5) {                                                                            \
            choice.choice[GwPlayer[cur].pad] = 0x400;                                                            \
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81()); \
        }                                                                                                        \
        choice.choice[GwPlayer[cur].pad] = -0x8000;                                                              \
        func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81()); \
        func_8005B63C_main(win, 2, 2);                                                                           \
    }                                                                                                            \
    result = (s16)func_8005E1D8_main(win, 0, last);                                                                 \
    func_80061A5C_main(win, 0);                                                                                  \
    func_8005F364_main(win)
extern s16 mbItemBtnF;
void func_80110C7C_duel02(void);
// board da2: functions the other duel02 forks own
// board da2: from w10
extern Object *D_80117638_duel02[2];
void func_8010E958_duel02(s16 arg0);
extern s16 D_801165E0_duel02[2]; /* space ids */
extern Vec D_801165E4_duel02[2]; /* rotations */
extern s32 D_801165FC_duel02[];
// board da2: end of declarations

s16 func_8010B484_duel02(void) {
    DuelB2Puffs *puffs = D_8011761C_duel02->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4C4_duel02(void) {
    DuelB2Puffs *puffs = D_8011761C_duel02->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        func_80016638_main(puffs->spr[i]);
    }
    omDelObj(D_8011761C_duel02);
    func_800166D0_main();
}

void func_8010B52C_duel02(void) {
    D_8011761C_duel02->work[0] = 1;
}

void func_8010B540_duel02(void) {
    D_8011761C_duel02->work[0] = 0;
}

#ifdef NON_MATCHING
// duel b2: masked 78 of 649: func_800EB708 is called through a correctly typed local pointer (duel01.h has it wrong) and GCC keeps it in $s8 (jalr), which shifts the allocation; logic checked block by block.
void func_8010B550_duel02(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    Vec offset;
    Vec sp48;
    Vec sp58;
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    f32 angle;
    f32 speed;
    s32 effect;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    func_800FAD04_name_81(0xB);
    if (flags != 0) {
        obj = func_800D8010_name_81(D_801165A0_duel02[variant - 1], 0);
        func_8001C8E4_main(obj->omObj1->model[0], 0);
        func_8001C448_main(obj->omObj1->model[0]);
        func_800D8944_name_81(obj);
        func_800D8F0C_name_81(obj);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AAB4_duel02(partner, 1);
        HuAudFXPlay(0x29C);
        func_800D90D0_name_81(D_80117618_duel02, 0, 2);
        HuVecCopy3F(&sp28, &D_80117618_duel02->coords);
        HuVecCopy3F(&sp48, &D_80117618_duel02->rot);
        HuVecCopy3F(&sp18, (target != NULL) ? &target->coords : &player->player_obj->coords);
        func_800EB708_name_81(&D_80117618_duel02->coords, &sp18, &D_80117618_duel02->rot);
        angle = func_800D76D0_name_81(&D_80117618_duel02->rot) + 180.0f;
        if (variant == 1) {
            speed = 2.5f;
        } else {
            speed = 3.0f;
        }
        offset.x = sindf(angle) * 6.0f * speed;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 6.0f * speed;
        HuVecAdd(&sp18, &sp18, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&D_80117618_duel02->coords, &sp18, &D_80117618_duel02->coords, 0.5f));
        func_80106244_duel02();
        func_80106264_duel02(target, player, flags, 0.8f);
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &D_80117618_duel02->coords);
        func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 0.5f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 1) {
            func_800D90D0_name_81(D_80117618_duel02, 3, 0);
            if (flags & 8) {
                func_801060D4_duel02(player, target, 0, 0x32);
            } else {
                HuPrcSleep(8);
                HuVecAdd(&sp58, (flags & 1) ? &target->coords : &player->player_obj->coords, &D_80117618_duel02->coords);
                HuVecMulScalar(&sp58, 0.5f, &sp58);
                sp58.y += 5.0f;
                effect = func_800DD1E0_name_81(0xB0025, D_80117070_duel02);
                func_800DD2DC_name_81(effect, &sp58);
                func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                    HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                    if (!(flags & 1)) {
                        HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
                    }
                }
            }
            func_800EFABC_name_81(D_80117618_duel02);
            func_800D90D0_name_81(D_80117618_duel02, -1, 2);
            HuPrcSleep(0x14);
        } else {
            func_800D90D0_name_81(D_80117618_duel02, 1, 0);
            HuPrcSleep(0x1E);
            func_8010AFB8_duel02();
            func_8010B52C_duel02();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                func_801060D4_duel02(player, target, 0, 0x32);
            }
            func_800EFABC_name_81(D_80117618_duel02);
            func_800D90D0_name_81(D_80117618_duel02, 2, 2);
            if (!(flags & 8)) {
                func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                }
            }
            HuPrcSleep(0x1E);
            func_8010B540_duel02();
            while (func_8010B484_duel02() != 0) {
                HuPrcVSleep();
            }
            func_800D918C_name_81(D_80117618_duel02, -1, 0, 5, 2);
            HuPrcSleep(0xA);
            func_8010B4C4_duel02();
        }
        func_8010AD4C_duel02(partner);
        func_800EB708_name_81(&partner->coords, &sp28, &partner->rot);
        func_800D90D0_name_81(partner, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &sp28, &partner->coords, 3.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &sp28, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp28, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        if (variant == 1) {
            if (effect != -1) {
                while (func_800DD3B4_name_81(effect) == 0) {
                    HuPrcVSleep();
                }
                func_800DD2BC_name_81(effect);
            }
        }
    } else {
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AAB4_duel02(partner, 0);
        HuAudFXPlay(0x2A0);
        func_80105EB4_duel02((unkStruct04 *)partner);
        HuPrcSleep(0xA);
        func_800FAE18_name_81(partner, 1, 0);
        func_800EFABC_name_81(partner);
        func_800D90D0_name_81(partner, -1, 2);
    }
    func_800FADB4_name_81();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B550_duel02);
#endif

void func_8010BCD8_duel02(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    Process *process = HuPrcCurrentGet();
    Object *front = NULL;
    Object *back = NULL;
    s32 frontNo = -1;
    s32 backNo = -1;
    s32 hitTime[3] = { -1, -1, -1 };
    Process *spinPrc[3] = { NULL, NULL, NULL };
    Vec pos;
    Object *obj;
    HmfModel *mdl;
    s32 i;
    f32 scale;
    f32 amp;

    func_800FAD04_name_81(8);
    obj = func_800D8010_name_81(D_801165A0_duel02[variant - 1] & 0xFF, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    HuVecCopy3F(&start, &partner->coords);
    HuVecCopy3F(&dest, &player->player_obj->coords);
    func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
    HuVecSubtract(&diff, &partner->coords, &player->player_obj->coords);
    hitTime[0] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
    if (hitTime[0] < 0) {
        hitTime[0] = 0;
    }
    if (player->stats.partners.frontID != -1) {
        front = MBDGetPlayerPartnerRef(playerNo, 0);
        frontNo = GwPlayer[playerNo].stats.partners.frontID;
        HuVecSubtract(&diff, &partner->coords, &front->coords);
        hitTime[1] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime[1] < 0) {
            hitTime[1] = 0;
        }
    }
    if (player->stats.partners.backID != -1) {
        back = MBDGetPlayerPartnerRef(playerNo, 1);
        backNo = GwPlayer[playerNo].stats.partners.backID;
        HuVecSubtract(&diff, &partner->coords, &back->coords);
        hitTime[2] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime[2] < 0) {
            hitTime[2] = 0;
        }
    }
    func_80106244_duel02();
    func_80106264_duel02(target, player, 0, 7.0f);
    if (variant == 1) {
        func_800FAE18_name_81(partner, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 7.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &dest, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 7.0f));
        for (i = 0; ; i++) {
            if (i == hitTime[0]) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1E5);
                spinPrc[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
                func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
                hitTime[0] = -1;
                HuVecCopy3F(&pos, &player->player_obj->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime[1]) {
                HuAudFXPlay((D_80105718_name_81 & 2) ? 0x1CE : 0x1E5);
                spinPrc[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
                func_800EF7C8_name_81(front, 7.0f, -0.4f);
                hitTime[1] = -1;
                HuVecCopy3F(&pos, &front->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime[2]) {
                HuAudFXPlay((D_80105718_name_81 & 4) ? 0x1CE : 0x1E5);
                spinPrc[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
                func_800EF7C8_name_81(back, 7.0f, -0.4f);
                hitTime[2] = -1;
                HuVecCopy3F(&pos, &back->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (HuPrcChildGet(process) == 0) {
                break;
            }
            HuPrcVSleep();
        }
        if (hitTime[0] != -1) {
            spinPrc[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
            func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &player->player_obj->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime[1] != -1) {
            spinPrc[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
            func_800EF7C8_name_81(front, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &front->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime[2] != -1) {
            spinPrc[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
            func_800EF7C8_name_81(back, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &back->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &start, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        while (TRUE) {
            if (spinPrc[0] != NULL && func_800EF7D4_name_81(player->player_obj) == 0) {
                B1_MODEL_ROTY(player->player_obj, 0.0f, mdl);
                omDelPrcObj(spinPrc[0]);
                spinPrc[0] = NULL;
            }
            if (spinPrc[1] != NULL && func_800EF7D4_name_81(front) == 0) {
                B1_MODEL_ROTY(front, 0.0f, mdl);
                omDelPrcObj(spinPrc[1]);
                spinPrc[1] = NULL;
            }
            if (spinPrc[2] != NULL && func_800EF7D4_name_81(back) == 0) {
                B1_MODEL_ROTY(back, 0.0f, mdl);
                omDelPrcObj(spinPrc[2]);
                spinPrc[2] = NULL;
            }
            if (spinPrc[0] == NULL && spinPrc[1] == NULL && spinPrc[2] == NULL) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        dest.y = 20.0f;
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 7.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &dest, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 7.0f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        partner->velocity.x = partner->coords.y;
        partner->coords.y = 0.0f;
        HuPrcSleep(10);
        HuAudFXPlay(0x1E6);
        for (i = 0; i < 20; i++) {
            f32 grow = i / 10.0f + 1.0f;
            HuVecCopyXYZ(&partner->scale, grow, grow, grow);
            HuPrcVSleep();
        }
        HuPrcSleep(10);
        if (front != NULL) {
            func_800DCE10_name_81(0x4C, &front->coords, NULL, 2.0f, 4);
        }
        if (back != NULL) {
            func_800DCE10_name_81(0x4C, &back->coords, NULL, 2.0f, 4);
        }
        func_800DCE10_name_81(0x51, &player->player_obj->coords, NULL, 3.0f, 4);
        func_800EF7C8_name_81(partner, -1.0f, -2.0f);
        player->stat |= 4;
        for (i = 0; i < 6; i++) {
            scale = (10 - i) * 0.9f / 10.0f + 0.1f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, scale, 1.0f);
            if (front != NULL) {
                HuVecCopyXYZ(&front->scale, 1.0f, scale, 1.0f);
            }
            if (back != NULL) {
                HuVecCopyXYZ(&back->scale, 1.0f, scale, 1.0f);
            }
            HuPrcVSleep();
        }
        func_801064CC_duel02(playerNo, 0);
        func_800EF800_name_81(partner);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, func_80106460_duel02(10, 1));
        HuPrcChildWait();
        HuPrcSleep(10);
        for (i = 20; i >= 0; i -= 2) {
            f32 grow = i / 10.0f + 1.0f;
            HuVecCopyXYZ(&partner->scale, grow, grow, grow);
            HuPrcVSleep();
        }
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &start, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        func_801064CC_duel02(playerNo, 1);
        amp = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            if (front != NULL) {
                HuVecCopyXYZ(&front->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            }
            if (back != NULL) {
                HuVecCopyXYZ(&back->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            }
            amp -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
        if (front != NULL) {
            HuVecCopyXYZ(&front->scale, 1.0f, 1.0f, 1.0f);
        }
        if (back != NULL) {
            HuVecCopyXYZ(&back->scale, 1.0f, 1.0f, 1.0f);
        }
        player->stat &= ~4;
    }
    func_800FAC1C_name_81(&D_80105540_name_81);
    if (flags & 0x20) {
        func_800FAB68_name_81(player->player_obj, 4, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 4, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 4, 1, D_80105718_name_81 & 4, backNo);
        }
    } else if (flags & 0x10) {
        func_800FAB68_name_81(player->player_obj, 2, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 2, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 2, 1, D_80105718_name_81 & 4, backNo);
        }
    } else {
        func_800FAB68_name_81(player->player_obj, 1, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 1, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 1, 1, D_80105718_name_81 & 4, backNo);
        }
    }
    func_800FADB4_name_81();
}

#ifdef NON_MATCHING
// duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block.
void func_8010CE6C_duel02(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    s32 effects[2];
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    Object *obj2;
    Object *extra1;
    Object *extra2;
    s32 i;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effects[0] = 0x4D;
    effects[1] = 0x53;
    obj2 = NULL;
    extra1 = NULL;
    extra2 = NULL;
    func_800FAD04_name_81(6);
    if (variant == 2) {
        extra1 = func_80106744_duel02(0x4C);
        HuPrcVSleep();
        extra2 = func_80106744_duel02(0x53);
        HuPrcVSleep();
    }
    HuVecCopy3F(&sp18, (target != NULL) ? &target->coords : &player->player_obj->coords);
    func_800EB708_name_81(&partner->coords, &sp18, &partner->rot);
    obj = func_800D8010_name_81(0x58, 0);
    func_800D8F0C_name_81(obj);
    HuPrcVSleep();
    if (variant == 2) {
        obj2 = func_800D8010_name_81(0x53, 0);
        func_800D8F0C_name_81(obj2);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A3);
    func_800FAE98_name_81(partner, variant - 1, 0, 5, 2);
    HuPrcSleep(variant == 1 ? 7 : 0xF);
    func_800D8E88_name_81(obj);
    HuVecCopy3F(&obj->coords, &partner->coords);
    obj->velocity.x = 5.0f;
    func_800D8F0C_name_81(obj);
    func_80106244_duel02();
    func_800D8E88_name_81(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, func_80106264_duel02(target, player, flags, 4.0f));
    HuVecCopy3F(&sp28, &partner->rot);
    func_800D7828_name_81(&sp28);
    HuVecMulScalar(&sp28, 6.0f, &sp28);
    HuVecAdd(&sp28, &sp28, &obj->coords);
    sp28.y += 5.0f;
    func_800DCE40_name_81(0x4E, &sp28, NULL, 0.5f);
    if (variant != 2) {
        HuAudFXPlay(0x1D9);
    } else {
        func_800D8E88_name_81(obj2);
        func_8001C258_main(obj2->omObj1->model[0], 0x180, 0);
        func_8001C8E4_main(obj2->omObj1->model[0], 0x800);
        HuVecCopy3F(&obj2->coords, &obj->coords);
        obj2->velocity.x = 5.0f;
        HuPrcChildLink(process, func_800EC36C_name_81(&obj2->coords, &sp18, &obj2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
    }
    if (flags & 8) {
        func_801060D4_duel02(player, target, 0, 0x14);
        HuPrcChildWait();
        func_800FC888_name_81(3);
        func_800D8F0C_name_81(obj);
        if (variant == 2) {
            func_800D8F0C_name_81(obj2);
        }
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 2) {
            func_800D8F0C_name_81(obj2);
        }
        HuVecCopy3F(&sp28, (flags & 1) ? &target->coords : &player->player_obj->coords);
        sp28.y += obj->velocity.x;
        if (variant == 1) {
            func_800DCE40_name_81(effects[0], &sp28, NULL, 2.0f);
        } else {
            func_801067D8_duel02(extra1, &sp28);
            HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
            func_801067D8_duel02(extra2, &sp28);
            HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            if (variant == 2) {
                HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1EF : 0x1EE);
            } else {
                HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
            }
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (variant == 2) {
                if (!(flags & 1)) {
                    HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1EF : 0x1EE);
                }
            } else if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
        if (variant == 2) {
            for (i = 0; i < 3; i++) {
                MBDBackTPLvlSet(0xFF);
                HuPrcVSleep();
                MBDBackTPLvlSet(0x40);
                HuPrcVSleep();
            }
        }
    }
    func_800D8F3C_name_81(obj);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    if (variant == 2) {
        HuPrcSleep(0x1E);
        func_800D8F3C_name_81(extra1);
        func_800D8F3C_name_81(extra2);
        func_800D8F3C_name_81(obj2);
    }
    func_800FADB4_name_81();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010CE6C_duel02);
#endif

#ifdef NON_MATCHING
// duel b2: masked 0, raw 28: partner and obj swap s3/s4.
void func_8010D428_duel02(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Object *obj;
    Vec sp18;
    Vec sp28;
    Vec sp38;
    GW_PLAYER *player;
    Process *process;
    Object *extra;
    s32 effect;
    Vec *partnerPos;
    Vec *mid;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    extra = NULL;
    if (variant == 1) {
        extra = func_80106744_duel02(0x45);
    }
    obj = func_800D8010_name_81(D_801165A0_duel02[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_80106160_duel02(partner, target, player, &sp18, &sp28, 7.5f);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(partnerPos, &sp18, partnerPos, 3.0f));
    func_800D8E88_name_81(partner);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, partnerPos);
    func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 3.0f));
    HuPrcChildWait();
    func_800D8F0C_name_81(obj);
    if (variant == 1) {
        func_800FAE18_name_81(partner, 0, 2);
    } else {
        func_800FAE18_name_81(partner, 1, 0);
    }
    if (flags & 8) {
        if (variant == 2) {
            HuPrcSleep(10);
        }
        func_801060D4_duel02(player, target, 0, 0x1E);
        if (variant == 1) {
            HuPrcSleep(0x1E);
        } else {
            func_800EFABC_name_81(partner);
        }
    } else {
        HuPrcSleep(variant == 1 ? 10 : 0x11);
        mid = &sp38;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &partner->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        sp38.y += 5.0f;
        if (variant == 1) {
            func_800DCE40_name_81(0x4B, &sp38, NULL, 2.0f);
            func_800EB804_name_81(extra);
            func_801067D8_duel02(extra, &sp38);
        } else {
            effect = func_800DD1E0_name_81(0xB0024, D_80117070_duel02);
            func_800DD2DC_name_81(effect, &sp38);
            HuAudFXPlay(0x1DB);
            HuAudFXPlay(0x1F1);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
        if (variant == 2) {
            func_800EFABC_name_81(partner);
        } else {
            HuPrcSleep(10);
        }
    }
    func_800EB708_name_81(&partner->coords, &sp28, &partner->rot);
    func_800D90D0_name_81(partner, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &sp28, &partner->coords, 3.0f));
    func_800D8E88_name_81(partner);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, &partner->coords);
    func_800EB708_name_81(&obj->coords, &sp28, &obj->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp28, &obj->coords, 3.0f));
    HuPrcChildWait();
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    func_800D8F3C_name_81(obj);
    if (variant == 2) {
        if (effect != -1) {
            while (func_800DD3B4_name_81(effect) == 0) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(effect);
        }
    } else {
        func_800D8F3C_name_81(extra);
    }
    func_800FADB4_name_81();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D428_duel02);
#endif

void func_8010D960_duel02(void) {
    DuelB2PartnerFunc funcs1[12] = {
        func_8010682C_duel02, func_8010718C_duel02, func_801079BC_duel02, func_80107EC0_duel02,
        func_8010988C_duel02, func_801084A8_duel02, func_8010CE6C_duel02, func_8010D428_duel02,
        func_8010BCD8_duel02, func_80108554_duel02, func_8010A214_duel02, func_8010B550_duel02,
    };
    DuelB2PartnerFunc funcs2[12] = {
        NULL, NULL, NULL, NULL, func_8010988C_duel02, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(funcs1, funcs2);
}

void func_8010D9F8_duel02(void) {
    omInitObjMan(0xA0, 0x50);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_800FC260_name_81(0x19, 0x242, 0);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    func_8010DCAC_duel02();
    func_8010DD40_duel02();
    func_8010E34C_duel02();
    func_8010EA10_duel02();
    func_8010D960_duel02();
}

void func_8010DA88_duel02(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F8_duel02();
    func_800EA46C_name_81(D_801167B8_duel02);
    func_800EA46C_name_81(D_80117008_duel02);
    func_800FC5A8_name_81(func_8011394C_duel02);
    func_800FC59C_name_81((s32)func_801163A4_duel02);
    func_800FF640_name_81(0);
}

void func_8010DB04_duel02(void) {
    Hu3DCamInit(1);
    func_8010D9F8_duel02();
    func_800FF640_name_81(1);
}

void func_8010DB30_duel02(void) {
    DuelB2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], HmfModelData[D_80117620_duel02->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_80117620_duel02->omObj1->model[0], "neji");
        angle += D_801165BC_duel02;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->rotY = angle;
        HuPrcVSleep();
    }
}

void func_8010DC08_duel02(void) {
    s16 model = D_80117620_duel02->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80117128_duel02, 0x4C, 0x46);
    ((Duel01Part *)func_8001D33C_main(D_80117620_duel02->omObj1->model[0], D_80117128_duel02))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010DCAC_duel02(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_801165C0_duel02);
    func_800D8944_name_81(obj);
    D_80117620_duel02 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x20)->coords);
    func_8010DC08_duel02();
    D_80117624_duel02 = omAddPrcObj(func_8010DB30_duel02, 0xA, 0, 0);
    omPrcSetStatBit(D_80117624_duel02, 0xA0);
}

void func_8010DD40_duel02(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_80117628_duel02 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_801165D0_duel02);
    to = MBDMasuGet(D_801165D2_duel02);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010DDF0_duel02(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_8011762C_duel02;
        sincosdf(rot, &HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF6C_duel02(Vec *pos) {
    Process *process;
    s32 *angle;

    D_8011762C_duel02 = 10.0f;
    process = omAddPrcObj(func_8010DDF0_duel02, 0xA, 0, 0x40);
    D_801165D4_duel02 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80117628_duel02->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E00C_duel02(void) {
    HmfModel *mdl;

    if (D_801165D4_duel02 != NULL) {
        while (D_8011762C_duel02 >= 0.0f) {
            D_8011762C_duel02 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801165D4_duel02);
        sincosdf(0.0f, &HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80117628_duel02->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80117628_duel02->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117128_duel02);

void func_8010E1B8_duel02(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80117628_duel02->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80117628_duel02->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80117628_duel02);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80117628_duel02->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80117628_duel02->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2D0_duel02(void) {
    omAddPrcObj(func_8010E1B8_duel02, 0xA, 0, 0);
}

void func_8010E2FC_duel02(void) {
    func_8001C814_main(D_80117628_duel02->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80117628_duel02->omObj1->model[0], 1.0f);
}

void func_8010E34C_duel02(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_80117630_duel02 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_801165D8_duel02);
    to = MBDMasuGet(D_801165DA_duel02);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010E3FC_duel02(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_80117634_duel02;
        sincosdf(rot, &HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E578_duel02(Vec *pos) {
    Process *process;
    s32 *angle;

    D_80117634_duel02 = 10.0f;
    process = omAddPrcObj(func_8010E3FC_duel02, 0xA, 0, 0x40);
    D_801165DC_duel02 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80117630_duel02->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E618_duel02(void) {
    HmfModel *mdl;

    if (D_801165DC_duel02 != NULL) {
        while (D_80117634_duel02 >= 0.0f) {
            D_80117634_duel02 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801165DC_duel02);
        sincosdf(0.0f, &HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80117630_duel02->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80117630_duel02->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010E7C4_duel02(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80117630_duel02->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80117630_duel02->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80117630_duel02);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80117630_duel02->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80117630_duel02->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8DC_duel02(void) {
    omAddPrcObj(func_8010E7C4_duel02, 0xA, 0, 0);
}

void func_8010E908_duel02(void) {
    func_8001C814_main(D_80117630_duel02->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80117630_duel02->omObj1->model[0], 1.0f);
}

void func_8010E958_duel02(s16 idx) {
    Object *obj;

    if (D_80117638_duel02[idx] == NULL) {
        obj = func_800D8010_name_81(0x2E, D_801165FC_duel02);
        func_800D8944_name_81(obj);
        D_80117638_duel02[idx] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBDMasuGet(D_801165E0_duel02[idx])->coords);
        HuVecCopy3F(&obj->rot, &D_801165E4_duel02[idx]);
    }
}

void func_8010EA10_duel02(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_80117638_duel02[i] = NULL;
        func_8010E958_duel02(i);
    }
}

void func_8010EA68_duel02(void) {
    s32 *idx = HuPrcCurrentGet()->user_data;

    func_800D90D0_name_81(D_80117638_duel02[*idx], 0, 4);
    /* retail reads HmfModelData[1] for any nonzero model index (not HmfModelData[model]) */
    while (TRUE) {
        if (HmfModelData[D_80117638_duel02[*idx]->omObj1->model[0] != 0].unk40 == 0.0f) {
            break;
        }
        HuPrcVSleep();
    }
    func_800D90D0_name_81(D_80117638_duel02[*idx], -1, 2);
    omDelPrcObj(NULL);
}

void func_8010EB40_duel02(s32 idx) {
    Process *prc = omAddPrcObj(func_8010EA68_duel02, 0x1000, 0, 0x40);
    s32 *data = HuMemMemoryAlloc(prc->heap, 0x10);

    prc->user_data = data;
    *data = idx;
}

void func_8010EB98_duel02(s32 idx) {
    func_800D90D0_name_81(D_80117638_duel02[idx], 0, 0);
}

#ifdef NON_MATCHING
s32 func_8010EBC8_duel02(void) {
    GW_PLAYER *rival;
    s32 chance;
    s32 dist;

    rival = MBDGetPlayerStruct((s8)(GwSystem.current_player_index ^ 1));
    chance = (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
    if (mbWalkNum < 4) {
        if (GwSystem.current_player_index == 0) {
            if (rival->clink == 0) {
                dist = rival->cidx - 8;
                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            }
        } else if (rival->clink == 1) {
            dist = rival->cidx - 8;
            if (dist == mbWalkNum) {
                chance = 0;
            }
            if (dist < mbWalkNum) {
                chance += 20;
            }
        }
    }
    return chance;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EBC8_duel02);
#endif

s32 func_8010ECB8_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

s32 func_8010ED60_duel02(s32 no) {
    s16 tbl[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return tbl[no];
}

s32 func_8010EDE0_duel02(void) {
    GW_PLAYER *player;
    s32 result;
    s32 roll;
    s32 i;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    result = -1;
    roll = func_800EFE20_name_81(10.0f);
    switch (player->cpu_difficulty) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            /* Both prize bytes (gamblePrize, duelNo) unset, read as one big-endian word. */
            if ((*(u32 *)&player->stats.prize.gamblePrize & 0xFFFF0000) != 0xFFFF0000) {
                if (roll < 6) {
                    if (player->stats.prize.gamblePrize != -1) {
                        result = player->stats.prize.gamblePrize;
                    }
                    if (player->stats.prize.duelNo != -1) {
                        result = player->stats.prize.duelNo;
                    }
                    break;
                }
                if (roll < 8) {
                    for (i = 0; D_80116604_duel02[i * 2] != -1; i++) {
                        if (D_80116604_duel02[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    result = D_80116604_duel02[i * 2];
                    break;
                }
            }
            for (i = 0; D_80116700_duel02[player->chr][i].value != -1; i++) {
                if (D_80116700_duel02[player->chr][i].chance > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            result = D_80116700_duel02[player->chr][i].value;
            break;
    }
    if (result == -1) {
        result = func_800EFE20_name_81(12.0f);
    }
    if (result < 0 || result >= 12) {
        result = 0;
    }
    return result;
}

#ifdef NON_MATCHING
void func_8010EFFC_duel02(void) {
    s32 *data;
    f32 angle1;
    f32 angle2;
    s32 win;
    s16 r;
    s16 g;
    s16 b;

    r = 0x43;
    data = HuPrcCurrentGet()->user_data;
    angle2 = 0.0f;
    angle1 = 90.0f;
    win = *data;
    func_8005FBF8_main(*data, 0x43, 0x80, 1);
    while (TRUE) {
        if (D_80116740_duel02 != 0) {
            g = sindf(angle1) * 128.0f;
            if (g < 0) {
                g = -g;
            }
            angle1 += 6.0f;
            if (angle1 > 360.0f) {
                angle1 -= 360.0f;
            }
            b = sindf(angle2) * 64.0f;
            if (b < 0) {
                b = -b;
            }
            angle2 += 3.0f;
            if (angle2 > 360.0f) {
                angle2 -= 360.0f;
            }
            func_8005FBF8_main(win, (u8)r, (u8)g, (u8)b);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EFFC_duel02);
#endif

void func_8010F16C_duel02(void) {
    s16 pos[3][2] = { { 160, -80 }, { 160, -160 }, { 160, -80 } };
    s32 files[6] = { 0x13011C, 0x13011F, 0x13011E, 0x13011D, 0x130120, 0x13011E }; /* [player * 3 + i] */
    u8 order[32];
    s32 player;
    s32 msg;
    s16 win;
    Process *proc;
    s32 kind;
    s32 cpuChoice;
    s32 cpuCount;
    s32 wait;
    s32 n;
    s32 i;
    s32 *data;
    void *file;
    Duel01SprGrp *grp;
    u8 last;

    player = *(s32 *)HuPrcCurrentGet()->user_data;
    proc = NULL;
    cpuChoice = -1;
    mbItemBtnF = 0;
    if (player == 0) {
        kind = (u8)GwSystem.playerIndexVisitingBowser;
    } else {
        kind = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    win = func_8005A968_main(60, -160, 200, 160, 0, 0);
    func_8005FBF8_main(win, 0x43, 5, 1);
    func_8005BEE0_main(win, 0xC0);
    if (kind == 2) {
        proc = omAddPrcObj(func_8010EFFC_duel02, 0xA, 0, 0x40);
        data = HuMemMemoryAlloc(proc->heap, 0x10);
        proc->user_data = data;
        *data = win;
    }
    grp = func_800F4528_name_81(3, 0);
    for (i = 0; i < 3; i++) {
        file = DataRead(files[player * 3 + i]);
        grp->unk_0C[i] = func_80055810_main(file);
        func_80055024_main(grp->unk_0A, i, grp->unk_0C[i], 0);
        HuSprPriSet(grp->unk_0A, i, i + 1);
        HuSprAttrSet(grp->unk_0A, i, 0);
        func_80054904_main(grp->unk_0A, i, pos[i][0], pos[i][1]);
        DataClose(file);
        if (i == 2) {
            func_80055140_main(grp->unk_0A, 2, func_800EFE20_name_81(12.0f), 0);
        }
    }
    for (wait = 90; wait < 180; wait += 15) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -200.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -200.0f + 55.0f);
        HuPrcVSleep();
    }
    for (wait = 0; wait < 180; wait += 20) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -50.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -50.0f + 55.0f);
        HuPrcVSleep();
    }
    for (wait = 0; wait < 180; wait += 20) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -30.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -30.0f + 55.0f);
        HuPrcVSleep();
    }
    if (func_800F37B8_name_81(CUR_PLAYER) != 0) {
        cpuCount = func_800EFE20_name_81(10.0f) + 10;
        cpuChoice = func_8010EDE0_duel02();
        if (kind == 2 && cpuChoice != -1) {
            cpuCount = 5;
        }
    } else {
        cpuCount = -1;
    }
    msg = func_800E1824_name_81(0x13, 0xB9, 0);
    D_80116740_duel02 = 1;
    last = 0xFF;
    n = 11;
    do {
        func_800E0310_name_81(order, n);
        if (last == order[0]) {
            last = order[n];
            order[n] = order[0];
            order[0] = last;
            last = 0xFF;
        }
        for (i = 0; i <= n; i++) {
            HuAudFXPlay(0x1C8);
            last = order[i];
            func_80055140_main(grp->unk_0A, 2, order[i], 0);
            func_800550F4_main(grp->unk_0A, 2, 1);
            wait = (kind == 2) ? 15 : 1;
            while (TRUE) {
                if (cpuCount > 0) {
                    if (kind != 2 || cpuChoice == -1 || cpuChoice == order[i]) {
                        if (--cpuCount == 0) {
                            break;
                        }
                    }
                } else if (D_800C9520_main[GwPlayer[player].pad] & 0x8000) {
                    break;
                }
                HuPrcVSleep();
                if (--wait == 0) {
                    break;
                }
            }
            if (wait != 0) {
                break;
            }
        }
    } while (i == n + 1);
    {
        s32 sfx[12] = { 0x25A, 0x25B, 0x298, 0x256, 0x257, 0x25D, 0x2A3, 0x2A4, 0x2A2, 0x1E7, 0x2A5, 0x2A0 };

        HuAudFXPlay(sfx[order[i]]);
    }
    D_80116740_duel02 = 0;
    if (player == 0) {
        if (kind == 2) {
            GwSystem.playerIndexVisitingBowser &= 0xFF00;
        } else {
            GwSystem.playerIndexVisitingBowser++;
        }
    } else if (kind == 2) {
        GwSystem.playerIndexVisitingBowser &= 0xFF;
    } else {
        GwSystem.playerIndexVisitingBowser += 0x100;
    }
    HuPrcSleep(30);
    D_80116738_duel02 = order[i];
    func_800E1854_name_81(msg);
    if (proc != NULL) {
        omDelPrcObj(proc);
    }
    func_800F4584_name_81(grp);
    func_8005F364_main(win);
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
s32 func_8010F9DC_duel02(s32 no) {
    Vec dir;
    Vec cam;
    Vec target;
    Object *fx[4];
    Vec unused; /* retail's frame has 0x18 bytes here and 8 after offs */
    s32 pad[2];
    SpaceData *start;
    SpaceData *goal;
    GW_PLAYER *player;
    Vec *pos;
    Object *partner;
    Object *bell;
    Process *proc;
    s32 *data;
    s32 i;
    s32 kind;

    start = MBDMasuGet(D_80116720_duel02[no][1]);
    goal = MBDMasuGet(D_80116720_duel02[no][2]);
    player = MBDGetPlayerStruct(no);
    if (no == 0) {
        kind = (u8)GwSystem.playerIndexVisitingBowser;
    } else {
        kind = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    if (kind == 2) {
        func_800EB140_name_81(0x16, 0x1F07);
    }
    HuVecCopy3F(&cam, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&target, &start->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 3.0f));
    func_800F3880_name_81(-1, 0, 2);
    func_800EB708_name_81(&player->player_obj->coords, &start->coords,
                          &player->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EC1E4_name_81(&player->player_obj->coords, &start->coords, &player->player_obj->coords, 3.0f));
    HuPrcChildWait();
    func_800EB708_name_81(&player->player_obj->coords, &goal->coords,
                          &player->player_obj->rot);
    func_800F3880_name_81(-1, 7, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x1C9);
    if (no == 0) {
        func_8010DF6C_duel02(&player->player_obj->coords);
    } else {
        func_8010E578_duel02(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_80116738_duel02 = -1;
    proc = omAddPrcObj(func_8010F16C_duel02, 0xA, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = data;
    *data = no;
    pos = &MBDMasuGet(D_80116720_duel02[no][0])->coords;
    func_800EB708_name_81(&player->player_obj->coords, pos, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&player->player_obj->coords, pos, &player->player_obj->coords, 2.0f));
    HuPrcChildWait();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&dir);
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    if (D_80116738_duel02 == -1) {
        do {
            HuPrcVSleep();
        } while (D_80116738_duel02 == -1);
    }
    HuVecCopy3F(&target, &goal->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 2.0f));
    HuPrcChildWait();
    if (no == 0) {
        func_8010E00C_duel02();
    } else {
        func_8010E618_duel02();
    }
    bell = func_800D8010_name_81(0x35, 0);
    func_800D8F0C_name_81(bell);
    partner = func_800F8050_name_81(D_80116738_duel02);
    HuVecCopy3F(&partner->coords, &goal->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (no == 0) {
        func_8010E2D0_duel02();
    } else {
        func_8010E8DC_duel02();
    }
    HuPrcSleep(20);
    {
        Vec offs[4] = { { 4.0f, 4.0f, -4.0f }, { -4.0f, -2.0f, -4.0f }, { 4.0f, 0.0f, 4.0f }, { -4.0f, 2.0f, 4.0f } };
        s32 pad2[2];

        for (i = 0; i < 4; i++) {
            fx[i] = func_800D8B18_name_81(bell);
            func_8001C8E4_main(fx[i]->omObj1->model[0], 0x800);
            func_8001C258_main(fx[i]->omObj1->model[0], 0x180, 0);
            func_8001C814_main(fx[i]->omObj1->model[0], 2, 0);
            HuVecCopy3F(&fx[i]->coords, &goal->coords);
            fx[i]->velocity.x = 26.0f;
            fx[i]->coords.x += offs[i].x;
            fx[i]->coords.y += offs[i].y;
            fx[i]->coords.z += offs[i].z;
            if (i == 3) {
                func_800D8E88_name_81(partner);
            }
            HuPrcSleep(4);
        }
    }
    HuPrcSleep(25);
    for (i = 0; i < 4; i++) {
        func_800D8F3C_name_81(fx[i]);
    }
    func_800D8F3C_name_81(bell);
    func_800FC888_name_81(5);
    func_800FC8DC_name_81(partner);
    pos = &MBDMasuGet(D_80116720_duel02[no][1])->coords;
    func_800EB708_name_81(&partner->coords, pos, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, pos, &partner->coords, 20));
    HuPrcChildWait();
    func_800EF800_name_81(partner);
    if (no == 0) {
        func_8010E2FC_duel02();
    } else {
        func_8010E908_duel02();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&cam, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &player->player_obj->coords, &cam, 2.0f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
    D_8011673C_duel02 = partner;
    return D_80116738_duel02;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010F9DC_duel02);
#endif

void func_801100A8_duel02(s32 no) {
    Vec pos;
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    DuelB7VecTbl ofs;
    Vec frontPos;
    Vec backPos;
    Vec frontRot;
    Vec backRot;
    GW_PLAYER *player;
    Object *partner;
    s32 i;
    s16 partnerID;
    s16 result;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    padMask = D_801171F4_duel02;
    choice = D_801171F8_duel02;
    func_800DB3E0_name_81(no);
    func_800F38DC_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&pos);
    func_800EBC60_name_81(&player->player_obj->rot, &pos, &player->player_obj->rot, 8);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuPrcChildWait();
    if ((player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2)
        || (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2)) {
        func_800EAFC4_name_81(0x1F00);
        Duel_PowerDownPartners(no);
    }
    func_800EDD50_name_81(&MBDMasuGet(D_80116720_duel02[no][0])->coords);
    func_800EE0D0_name_81(0);
    func_800EDF48_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F01);
    func_800F3880_name_81(-1, 6, 0);
    func_800E14D8_name_81(no, 10);
    func_800F7378_name_81(no, 10);
    HuPrcSleep(30);
    func_800F3880_name_81(-1, -1, 2);
    if ((*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        func_800EB140_name_81(0x16, 0x1F04);
        partnerID = func_8010F9DC_duel02(no);
    loop1:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_8010EBC8_duel02() >= func_800EFE20_name_81(100.0f)
                || func_8010ED60_duel02(partnerID) >= func_800EFE20_name_81(100.0f)) {
                choice.choice[GwPlayer[no].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[no].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[no].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel02();
            goto loop1;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(no);
            mbItemBtnF = 1;
            goto loop1;
        }
    } else {
        func_800EB140_name_81(0x16, 0x1F02);
    loop2:
        func_800EB1D8_name_81(0x16, 0x1F03);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (player->stats.partners.backID == -1 || func_8010ECB8_duel02() >= func_800EFE20_name_81(100.0f)) {
                choice.choice[GwPlayer[no].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[no].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[no].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel02();
            goto loop2;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(no);
            mbItemBtnF = 1;
            goto loop2;
        }
        partner = MBDGetPlayerPartnerRef(no, result);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            ofs = D_80117200_duel02;
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[i], 3.0f));
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            func_800D8F0C_name_81(partner);
            HuPrcChildWait();
            func_800F85A4_name_81(no, result);
            func_800F8358_name_81(no);
            func_800F57B0_name_81(no);
            func_800F5E2C_name_81(no);
        }
        partnerID = func_8010F9DC_duel02(no);
    }
    func_800ECF1C_name_81(no, &frontPos, &backPos);
    func_800ED118_name_81(no, &frontRot, &backRot);
    func_800D918C_name_81(D_8011673C_duel02, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        func_800EF7C8_name_81(D_8011673C_duel02, 2.0f, -0.2f);
    }
    if (result == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_8011673C_duel02->coords, &frontPos, &D_8011673C_duel02->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_8011673C_duel02->coords, &frontPos, &D_8011673C_duel02->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_8011673C_duel02->rot, &frontRot, &D_8011673C_duel02->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_8011673C_duel02->coords, &backPos, &D_8011673C_duel02->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_8011673C_duel02->coords, &backPos, &D_8011673C_duel02->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_8011673C_duel02->rot, &backRot, &D_8011673C_duel02->rot, 7));
    }
    HuPrcChildWait();
    func_800D8F3C_name_81(D_8011673C_duel02);
    func_800F8418_name_81(no, partnerID, result);
    func_800F821C_name_81(no, result);
    func_800F89D0_name_81(no, 0, -1, 2);
    func_800F89D0_name_81(no, 1, -1, 2);
    func_800ED214_name_81(no);
    func_800F5BB4_name_81(no);
    func_800F5EB0_name_81(no);
    if (player->stats.partners.frontID == player->stats.partners.backID) {
        switch (player->stats.partners.frontID) {
        case 5:
        case 9:
            func_800EB49C_name_81(0x16, 0x1F09, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontCost--;
            player->stats.partners.backCost--;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(no, 1);
            func_800F7D94_name_81(no, 1);
            break;
        default:
            func_800EB49C_name_81(0x16, 0x1F08, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontPower++;
            player->stats.partners.backPower++;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(no, 0);
            func_800F7D94_name_81(no, 0);
            break;
        }
        /* board flag: player 1 or 2 has a matching pair */
        if (no == 0) {
            GWBoardFlagSet(0x12);
        } else {
            GWBoardFlagSet(0x13);
        }
    }
    func_800FBDD4_name_81();
    func_800EB140_name_81(0x16, 0x1F06);
    func_800EDF78_name_81();
    func_800EE468_name_81(0);
    func_800EDDBC_name_81();
    func_800DADA0_name_81(no);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
}

void func_80110BBC_duel02(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_801100A8_duel02(0);
    }
}

void func_80110C18_duel02(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_801100A8_duel02(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171C4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171F4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171F8_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117200_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117220_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117224_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_8011730C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801173F4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801174DC_duel02);

#ifdef NON_MATCHING // duel b7: masked 0 but for register allocation: one extra callee-saved register ($s8), so every $s register is one higher
/* Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4
   coins; from the second turn the player pays the partners' upkeep, or loses them when short of coins. */
void func_80110C7C_duel02(void) {
    u8 buf[0x200];
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    Vec dir;
    Vec rot;
    Vec camPos;
    char str[8];
    Vec puffPos;
    Vec pos;
    DuelB7VecTbl ofs;
    s32 cur;
    GW_PLAYER *player;
    Object *partner;
    Object *coin;
    s16 win;
    s32 front;
    s32 back;
    s32 count;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    f32 scale;
    s32 cost;
    s32 coins;

    cur = GwSystem.current_player_index;
    player = MBDGetPlayerStruct(cur);
    padMask = D_801171F4_duel02;
    choice = D_801171F8_duel02;
    if (cur == 0 && GwSystem.current_turn == 1 && (*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        DUEL_B7_PICK(win, D_80117224_duel02, cur, padMask, choice, buf, front, 1);
        DUEL_B7_PICK(win, D_8011730C_duel02, cur, padMask, choice, buf, back, 1);
        func_800F8418_name_81(cur, front, 0);
        func_800F8418_name_81(cur, back, 1);
        func_800F8108_name_81(cur);
        func_800ED214_name_81(cur);
        func_800F5BB4_name_81(cur);
        func_800F5EB0_name_81(cur);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(cur);
        }
        DUEL_B7_PICK(win, D_801173F4_duel02, cur, padMask, choice, buf, front, 0);
        DUEL_B7_PICK(win, D_801174DC_duel02, cur, padMask, choice, buf, back, 0);
        func_800F8418_name_81(1, front, 0);
        func_800F8418_name_81(1, back, 1);
        func_800F8108_name_81(1);
        func_800ED214_name_81(1);
        func_800F5BB4_name_81(1);
        func_800F5EB0_name_81(1);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(1);
        }
    }
    if ((player->stats.partners.frontID == 6 || player->stats.partners.backID == 6) && func_800EFE20_name_81(100.0f) < 34) {
        count = func_800EFE20_name_81(3.0f) + 2;
        func_800FAD04_name_81(6);
        if (player->stats.partners.backID == 6) {
            partner = MBDGetPlayerPartnerRef(cur, 1);
        } else {
            partner = MBDGetPlayerPartnerRef(cur, 0);
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
        HuPrcChildWait();
        HuVecCopy3F(&camPos, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&camPos, &partner->coords, &camPos, 2.0f));
        HuPrcChildWait();
        func_800EB708_name_81(&partner->coords, &player->player_obj->coords, &dir);
        HuVecCopy3F(&rot, &partner->rot);
        func_800EBC60_name_81(&partner->rot, &dir, &partner->rot, 8);
        HuPrcSleep(8);
        for (i = 0; i < 31; i += 5) {
            func_8008A120_main(HmfModelData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x += 1.0f;
            HuPrcVSleep();
        }
        func_800FAE98_name_81(partner, 2, 0, 5, 2);
        coin = NULL;
        for (i = 0; i < count; i++) {
            if (coin != NULL) {
                for (j = 6; j < 12; j++) {
                    scale = j / 6.0f + 0.5f;
                    if (scale > 1.0f) {
                        scale = 1.0f;
                    }
                    HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                    func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, j * 40);
                    HuPrcVSleep();
                }
            } else {
                HuPrcSleep(3);
                HuVecCopy3F(&puffPos, &partner->coords);
                puffPos.y += 12.0f;
                func_800DCE40_name_81(0x4E, &puffPos, NULL, 1.0f);
                HuPrcSleep(1);
            }
            if (coin != NULL) {
                func_800F7378_name_81(cur, 1);
                func_800D8F3C_name_81(coin);
                HuVecCopy3F(&puffPos, &partner->coords);
                puffPos.y += 12.0f;
                func_800DCE40_name_81(0x4E, &puffPos, NULL, 1.0f);
            }
            coin = func_800D8010_name_81(0x1C, NULL);
            coin->velocity.x = 13.0f;
            HuVecCopy3F(&coin->coords, &partner->coords);
            HuVecCopyXYZ(&coin->scale, 0.0f, 0.0f, 0.0f);
            func_800EF7C8_name_81(coin, 2.0f, -0.2f);
            func_800EBF2C_name_81(&coin->coords, &player->player_obj->coords, &coin->coords, 10);
            HuAudFXPlay(0x200);
            for (k = 0; k < 6; k++) {
                scale = k / 6.0f;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, k * 40);
                HuPrcVSleep();
            }
        }
        for (l = 6; l < 12; l++) {
            scale = l / 6.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&coin->scale, scale, scale, scale);
            func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, l * 40);
            HuPrcVSleep();
        }
        func_800F7378_name_81(cur, 1);
        func_800D8F3C_name_81(coin);
        func_800D90D0_name_81(partner, -1, 2);
        for (i = 30; i >= 0; i -= 10) {
            func_8008A120_main(HmfModelData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        partner->velocity.x = 0.0f;
        func_800EBC60_name_81(&partner->rot, &rot, &partner->rot, 4);
        HuPrcSleep(4);
        func_800FADB4_name_81();
        sprintf(str, "%d", count);
        func_800EADBC_name_81(0x4F0C, (u32)str, 0, 0, 0, 0);
        func_800EAF70_name_81(cur);
        func_800EAF94_name_81();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&camPos, &player->player_obj->coords, &camPos, 2.0f));
        HuPrcChildWait();
        func_800FC888_name_81(1);
    }
    if (GwSystem.current_turn != 1) {
        cost = func_800F8980_name_81(cur);
        coins = GwPlayer[cur].coin;
        if (coins < cost) {
            func_800E14D8_name_81(cur, -coins);
            func_800F7378_name_81(cur, -coins);
            HuPrcSleep(30);
            for (i = 0; i < 2; i++) {
                partner = MBDGetPlayerPartnerRef(cur, i);
                if (partner != NULL) {
                    HuVecCopy3F(&pos, &partner->coords);
                    pos.y += 2.0f;
                    ofs = D_80117200_duel02;
                    for (j = 0; j < 3; j++) {
                        HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[j], 3.0f));
                    }
                    func_800D8F0C_name_81(partner);
                }
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            HuPrcChildWait();
            func_800F85A4_name_81(cur, 0);
            func_800F85A4_name_81(cur, 1);
            func_800F82EC_name_81(cur);
            func_800F57B0_name_81(cur);
            func_800F5E2C_name_81(cur);
            func_800EAFC4_name_81(0x1E01);
            return;
        }
        if (cost != 0) {
            func_800E14D8_name_81(cur, -cost);
            func_800F7378_name_81(cur, -cost);
            HuPrcSleep(30);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80110C7C_duel02);
#endif

// board da3: declarations for func_80111E3C_duel02..func_80116564_duel02

typedef Duel01Part Da3HmfPart;

typedef B1UnkBoard4 Da3SprGrp; /* ovl_81's UnkBoard4 */

// board da3: spin the partner's model about Y by ang * 10 degrees (the model matrix is rebuilt as a pure Y rotation)
#define DA3_PARTNER_SPIN(obj, vel, ang)                                                                        \
    {                                                                                                          \
        HmfModel *mdl;                                                                                         \
        (obj)->velocity.x = (vel);                                                                             \
        sincosdf((ang) * 10.0f, &HmfModelData[(obj)->omObj1->model[0]].mtx[8],                                 \
                 &HmfModelData[(obj)->omObj1->model[0]].mtx[10]);                                              \
        HmfModelData[(obj)->omObj1->model[0]].mtx[2] = -HmfModelData[(obj)->omObj1->model[0]].mtx[8];         \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[0] = mdl->mtx[10];                                                                            \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =     \
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                                                 \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[5] = mdl->mtx[15] = 1.0f;                                                                     \
    }

extern void (*D_80116788_duel02[])(void); /* space events by GwSystem.minigame_index */
/* defined void in ovl_81 C5770.c, but it returns omAddPrcObj's Process* (retail reads v0) */
extern u8 D_801167EC_duel02[];
extern u8 D_801167F8_duel02[];
extern u8 D_801167E0_duel02[];
extern u8 D_80116800_duel02[];
extern u8 D_801167DC_duel02[]; /* D_801167E0_duel02 - 4 (undefined_syms.txt) */
extern u8 D_801167FC_duel02[]; /* D_80116800_duel02 - 4 */
extern u8 D_801167E7_duel02[]; /* D_801167EC_duel02 - 5 */
extern u8 D_801167F3_duel02[]; /* D_801167F8_duel02 - 5 */
UnkEA790Struct *func_800D76A0_name_81(s16 arg0, s16 *arg1);
s32 func_800D742C_name_81(UnkEA790Struct *arg0, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *arg0, s32 arg1);
s32 func_800D7518_name_81(UnkEA790Struct *arg0);
void func_800D6CA0_name_81(void *arg0);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *arg0);
void func_800ECD88_name_81(s16 playerNo, s16 link, s16 idx);
void func_800ED788_name_81(s32 playerNo);
extern DecisionTreeNonLeafNode D_801169A0_duel02[];
extern DecisionTreeNonLeafNode D_80116B68_duel02[];
extern DecisionTreeNonLeafNode D_80116D30_duel02[];
extern DecisionTreeNonLeafNode D_80116EF8_duel02[];
extern s16 D_80116F28_duel02[];
extern s16 D_80116F40_duel02[];
extern s16 D_80116F58_duel02[];
extern s16 D_80116F70_duel02[];
void func_800E27D4_name_81(s16 playerIndex, Vec *pos, Vec *frontPos, Vec *backPos);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
/* retail passes the back link/index addresses to the empty func_8011639C_duel02, so no prototype here */
void func_8011639C_duel02();
void func_80116414_duel02(void);
// board da3 (end of declarations)

// board da3: bell space: ring the bell; at zero coins the bell pays out and the board ends the turn
// (the duel01 twin's if-chain matches here with one sprintf per branch)
void func_80111E3C_duel02(void) {
    Vec pos;
    char buf[8];
    GW_PLAYER *player;
    SpaceData *space;
    Da3HmfPart *part;
    f32 ofs;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    space = MBDMasuGet(0x20);
    func_800DB3E0_name_81(system->current_player_index);
    func_800F38DC_name_81(-1, -1, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuVecCopy3F(&pos, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &space->coords, &pos, 4.0f));
    func_800D90D0_name_81(D_80117620_duel02, 2, 0);
    func_8002FD8C_main(D_80117620_duel02->omObj1->model[0],
                       HmfModelData[D_80117620_duel02->omObj1->model[0]].unk02, D_80117128_duel02, 0x4C, 0x46);
    func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], D_80117620_duel02->omObj1->motion[2],
                       D_80117128_duel02, 0x4C, 0x46);
    i = 0;
    ((Da3HmfPart *)func_8001D33C_main(D_80117620_duel02->omObj1->model[0], D_80117128_duel02))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
    while (!(func_800D9234_name_81(D_80117620_duel02) & 1)) {
        if (++i == 8) {
            HuAudFXPlay(0x1C5);
        }
        HuPrcVSleep();
    }
    func_8002FD8C_main(D_80117620_duel02->omObj1->model[0],
                       HmfModelData[D_80117620_duel02->omObj1->model[0]].unk02, D_80117128_duel02, 0x4C, 0x46);
    part = func_8001D33C_main(D_80117620_duel02->omObj1->model[0], D_80117128_duel02);
    part->unk_14 = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (ofs = 0.0f; ofs >= -60.0f; ofs -= 4.0f) {
        part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
        HuPrcVSleep();
    }
    HuPrcChildWait();
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    func_8010DC08_duel02();
    D_801165BC_duel02 = 12.0f;
    if (GwSystem.bank_coins != 0) {
        HuAudFXPlay(0x207);
        func_800D918C_name_81(D_80117620_duel02, 0, 0, 5, 2);
        func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], D_80117620_duel02->omObj1->motion[0],
                           D_80117128_duel02, 0x4C, 0x46);
        func_8001C92C_main(D_80117620_duel02->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(0x18);
        func_800D90D0_name_81(D_80117620_duel02, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        func_800D918C_name_81(D_80117620_duel02, 1, 0, 5, 2);
        func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], D_80117620_duel02->omObj1->motion[1],
                           D_80117128_duel02, 0x4C, 0x46);
        func_8001C92C_main(D_80117620_duel02->omObj1->model[0], 1.0f);
        func_8010DC08_duel02();
        func_800F74E4_name_81(-1);
        func_800EEC40_name_81(&pos);
        if (system->current_turn < 11) {
            sprintf(buf, "20");
        } else if (system->current_turn >= 20) {
            sprintf(buf, "40");
        } else {
            sprintf(buf, "30");
        }
        HuAudFXPlay(0x2A7);
        func_800EB49C_name_81(0x15, 0x1F30, (s32)buf, 0, 0, 0, 0);
        func_800EB58C_name_81();
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80116414_duel02();
        D_80100F44_name_81 = D_80117620_duel02;
        func_800FD620_name_81();
        HuPrcSleep(-1);
    }
    D_801165BC_duel02 = 3.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &player->player_obj->coords, &pos, 4.0f));
    func_800DADA0_name_81(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
}

void func_80112428_duel02(void) {
    GW_PLAYER *player;
    void *win;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FF);
    win = func_800FFC2C_name_81(-1, 3, 5);
    func_800EE74C_name_81(3);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    GwPlayer[GwSystem.current_player_index].star = 5;
}

void func_80112518_duel02(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_80112554_duel02(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 coins = GwPlayer[system->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(system->current_player_index, -coins);
    func_800F7378_name_81(system->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_801125D0_duel02(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 10);
    func_800F7378_name_81(system->current_player_index, 10);
    HuPrcSleep(30);
}

void func_8011260C_duel02(void) {
    s8 link;
    s8 idx;
    s8 backLink = -1;
    s8 backIdx = -1;

    func_800E9F4C_name_81(MBDGetCurrentPlayerIndex() == 0 ? 0x1E : 0x1D, &link, &idx);
    func_8011639C_duel02(&backLink, &backIdx);
    func_800E24AC_name_81(link, idx, backLink, backIdx);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_801100A8_duel02(MBDGetCurrentPlayerIndex());
}

void func_8011268C_duel02(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;
    s32 cur;
    s32 other;

    cur = MBDGetCurrentPlayerIndex();
    other = (cur + 1) & 1;
    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1F9);
    win[0] = func_800FFC2C_name_81(0, 3, 5);
    win[1] = func_800FFC2C_name_81(1, 3, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA898_name_81(other, cur);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB49C_name_81(0x16, 0x1F2B, D_80101200_name_81[GwPlayer[GwSystem.current_player_index ^ 1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
}

void func_80112A08_duel02(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(0);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    HuAudFXPlay(0x1FA);
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerUpPartners(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(0));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

void func_80112BF4_duel02(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FB);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(4);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerDownPartners(system->current_player_index);
    HuAudFXPlay(0x1FC);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(1));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

void func_80112DE0_duel02(void) {
    GW_PLAYER *player;
    Object *obj;
    void *win;
    f32 angle;
    s32 cur;

    player = MBDGetPlayerStruct(-1);
    cur = MBDGetCurrentPlayerIndex();
    func_800DD41C_name_81(&player->player_obj->coords);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuAudFXPlay(0x1FD);
    func_800DD554_name_81();
    win = func_800FFC2C_name_81(-1, 1, 5);
    for (angle = 0.0f; angle < 120.0f; angle += 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            DA3_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            DA3_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    Duel_SwapPartnerPositions(cur);
    func_800DD564_name_81();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            DA3_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            DA3_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win);
    /* angle is 0 here: the loop steps from 120 by 5 */
    if (player->stats.prize.gamblePrize != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 0);
        DA3_PARTNER_SPIN(obj, 0.0f, angle);
    }
    if (player->stats.prize.duelNo != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 1);
        DA3_PARTNER_SPIN(obj, 0.0f, angle);
    }
    func_800DD570_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2C);
    func_800EDF78_name_81();
    func_800EE468_name_81(1);
    func_800EDDBC_name_81();
}

void func_80113618_duel02(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1FB);
    func_800EE74C_name_81(4);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x22, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1FE);
    win[0] = func_800FFC2C_name_81(0, 2, 5);
    win[1] = func_800FFC2C_name_81(1, 2, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA8DC_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2D);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    CharFXPlay(0x286, GwPlayer[GwSystem.current_player_index].chr);
    func_800F3880_name_81(-1, 5, 0);
    func_800EFABC_name_81(player->player_obj);
}

void func_80113910_duel02(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 20);
    func_800F7378_name_81(system->current_player_index, 20);
    HuPrcSleep(30);
}

void func_8011394C_duel02(void) {
    Da3SprGrp *grp;
    void *data;
    s32 i;
    s32 y;

    mbItemBtnF = 0;
    func_800F74E4_name_81(-1);
    HuAudFXPlay(0x204);
    grp = func_800F4528_name_81(2, 2);
    data = DataRead(0x130103);
    grp->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->unk_0A, 0, grp->unk_0C[0], 0);
    HuSprPriSet(grp->unk_0A, 0, 1);
    HuSprAttrSet(grp->unk_0A, 0, 0x1000);
    func_80054904_main(grp->unk_0A, 0, 160, -32);
    func_800555E8_main(grp->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    grp->unk_0C[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->unk_0A, 1, grp->unk_0C[1], 0);
    HuSprPriSet(grp->unk_0A, 1, 2);
    HuSprAttrSet(grp->unk_0A, 1, 0x1000);
    func_80054904_main(grp->unk_0A, 1, 0, 0);
    func_800555E8_main(grp->unk_0A, 0, 16, 12, 304, 228);
    func_80055420_main(grp->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    func_80054904_main(grp->unk_0A, 0, 160, 120);
    for (y = 0, i = 0; i < 9; i++) {
        y += i * 2;
        func_80054904_main(grp->unk_0A, 0, 160, 120 - y);
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800E0924_name_81());
    HuPrcChildWait();
    func_800F4584_name_81(grp);
    func_800F75EC_name_81(-1);
    D_80116788_duel02[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
// board da4: logic checked block by block against the asm; 579 vs 592 instructions: GCC store-flags and cross-jumps
// some bool tails (case 1 turn test and roll, case 2 tail, case 3 power test) that the original keeps as branches
// board da4: COM decision for the current player against the opponent on links 0-3 (the other branch pair of
// func_80114630_duel02's tree); D_801167DC/D_801167FC_duel02 are the asm's labels 4 bytes before D_801167E0/D_80116800
s32 func_80113CEC_duel02(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    switch (opp->clink) {
        case 0:
            if (walk < 5) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (opp->cidx == D_801167DC_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (opp->cidx < D_801167DC_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                return me->stats.partners.backID != 4;
            }
            return TRUE;
        case 1:
            if (opp->cidx == D_801167EC_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (opp->cidx < D_801167EC_duel02[walk]) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 9) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star > opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return FALSE;
                    }
                }
                break;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (opp->cidx < 6) {
                return TRUE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
            }
            if (n >= 3 && walk < 6) {
                if (func_800EFE20_name_81(100.0f) < 50) {
                    return FALSE;
                }
            }
            break;
        case 2:
            if (walk < 5 && opp->cidx == D_801167F8_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (walk >= 5 || opp->cidx < D_801167F8_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower != 0) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 4) {
                    return FALSE;
                }
                return TRUE;
            }
            if (opp->stats.partners.frontPower != 0) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
            }
            return n < 3;
        case 3:
            if (walk < 5) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (walk < 10 && opp->cidx == D_801167FC_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (walk >= 10 || opp->cidx < D_801167FC_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                        return FALSE;
                    }
                } else if (!(me->stats.partners.frontPower < opp->stats.partners.backHp + opp->star)) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                return me->stats.partners.backID != 4;
            }
            return TRUE;
    }
    return TRUE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80113CEC_duel02);
#endif

#ifdef NON_MATCHING
// board da3: logic checked block by block against the asm; masked 41 (382 vs 381 instructions): the bool tails
// (frontPower/backID tests) become store-flag sequences and the compares against 4 take other registers
// board da3: COM decision for the current player against the opponent, from the opponent's position (clink, cidx)
// relative to the roll (mbWalkNum); compares partner power with HP. me/opp partner fields are PartnerStats.
s32 func_80114630_duel02(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    switch (opp->clink) {
        case 0:
            return FALSE;
        case 1:
            if (opp->cidx == D_801167EC_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (opp->cidx < D_801167EC_duel02[walk]) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 9) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star > opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return FALSE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return FALSE;
                }
                return TRUE;
            }
            if (walk == 4) {
                return func_800EFE20_name_81(100.0f) < 50;
            }
            return walk >= 6;
        case 2:
            if (walk < 5 && opp->cidx == D_801167F8_duel02[walk]) {
                if (opp->stats.partners.backID != 4) {
                    return FALSE;
                }
                return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
            }
            if (walk >= 5 || opp->cidx < D_801167F8_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (walk != 2) {
                return FALSE;
            }
            if (me->stats.partners.frontPoweredUp == walk) {
                return FALSE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / (func_800F8980_name_81(cur) * 2);
            }
            if (n < 3) {
                return FALSE;
            }
            return me->stats.partners.frontPower != 0;
    }
    return FALSE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80114630_duel02);
#endif

#ifdef NON_MATCHING
// board da4: func_80113CEC_duel02's decision with the links' roles exchanged (0<->1, 2<->3) and roll limits of 6;
// logic checked block by block against the asm (m2c draft); 580 vs 593 instructions, the same store-flag and
// cross-jump residue as func_80113CEC_duel02 (the case order sets the block layout). D_801167E7/D_801167F3_duel02
// are the asm's labels 5 bytes before D_801167EC/D_801167F8
s32 func_80114B94_duel02(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    switch (opp->clink) {
        case 1:
            if (walk < 6) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (opp->cidx == D_801167E7_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (opp->cidx < D_801167E7_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                return me->stats.partners.backID != 4;
            }
            return TRUE;
        case 0:
            if (opp->cidx == D_801167E0_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (opp->cidx < D_801167E0_duel02[walk]) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 9) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star > opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return FALSE;
                    }
                }
                break;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (opp->cidx < 6) {
                return TRUE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
            }
            if (n >= 3 && walk < 6) {
                if (func_800EFE20_name_81(100.0f) < 50) {
                    return FALSE;
                }
            }
            break;
        case 3:
            if (walk < 6 && opp->cidx == D_80116800_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (walk >= 6 || opp->cidx < D_80116800_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower != 0) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 4) {
                    return FALSE;
                }
                return TRUE;
            }
            if (opp->stats.partners.frontPower != 0) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
            }
            return n < 3;
        case 2:
            if (walk < 6) {
                return TRUE;
            }
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (walk < 10 && opp->cidx == D_801167F3_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower >= me->star + me->stats.partners.frontHp;
                }
                return FALSE;
            }
            if (walk >= 10 || opp->cidx < D_801167F3_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                        return FALSE;
                    }
                } else if (!(me->stats.partners.frontPower < opp->stats.partners.backHp + opp->star)) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                return me->stats.partners.backID != 4;
            }
            return TRUE;
    }
    return TRUE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80114B94_duel02);
#endif

#ifdef NON_MATCHING
// board da3: logic checked against the asm; masked 41 (388 vs 387 instructions), the same residue as func_80114630_duel02
// board da3: func_80114630_duel02's decision for the other branch of the board (opponent on link 0 or 3)
s32 func_801154DC_duel02(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    switch (opp->clink) {
        case 1:
            return FALSE;
        case 2:
            return FALSE;
        case 0:
            if (opp->cidx == D_801167E0_duel02[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (opp->cidx < D_801167E0_duel02[walk]) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 9) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star > opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return FALSE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return FALSE;
                }
                return TRUE;
            }
            if (walk == 4) {
                return func_800EFE20_name_81(100.0f) < 50;
            }
            return walk >= 6;
        case 3:
            if (walk < 6 && opp->cidx == D_80116800_duel02[walk]) {
                if (opp->stats.partners.backID != 4) {
                    return FALSE;
                }
                return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
            }
            if (walk >= 6 || opp->cidx < D_80116800_duel02[walk]) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return TRUE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return me->stats.partners.frontHp + me->star <= opp->stats.partners.frontPower;
                    }
                    if (opp->stats.partners.frontPower > me->stats.partners.backHp + me->star) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (walk != 2) {
                return FALSE;
            }
            if (me->stats.partners.frontPoweredUp == walk) {
                return FALSE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 0;
            } else {
                n = GwPlayer[cur].coin / (func_800F8980_name_81(cur) * 2);
            }
            if (n < 3) {
                return FALSE;
            }
            return me->stats.partners.frontPower != 0;
    }
    return FALSE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801154DC_duel02);
#endif

// board da3: branch-space path choice: on the junction the player (or the COM, through the decision tree) picks
// a path; taking it moves the player on and sets the following space
void func_80115A54_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);
    UnkEA790Struct *path;
    s32 i;
    s32 n;
    s32 ret;

    if (space == 7) {
        return;
    }
    if (space == 0x28) {
        func_800ECD88_name_81(-1, 1, 0);
        return;
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800ECD88_name_81(-1, 1, 0);
    HuPrcVSleep();
    func_80105A58_duel02();
    path = func_800D76A0_name_81(GwSystem.current_player_index, D_80116F28_duel02);
    func_800D742C_name_81(path, GwSystem.current_player_index, 0);
    if (func_800F37B8_name_81(-1) != 0) {
        n = func_800D97B0_name_81(D_801169A0_duel02);
        for (i = 0; i < n; i++) {
            func_800D7250_name_81(path, -2);
        }
        func_800D7250_name_81(path, -4);
    }
    ret = func_800D7518_name_81(path);
    func_800D6CA0_name_81(path);
    func_80105B10_duel02();
    if (ret != 0) {
        func_800E9F4C_name_81(0x28, &player->nlink, &player->nidx);
        func_800ED788_name_81(GwSystem.current_player_index);
        func_800E9F4C_name_81(0x13, &player->nnlink, &player->nnidx);
    }
}

void func_80115BDC_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);
    UnkEA790Struct *path;
    s32 i;
    s32 n;
    s32 ret;

    if (space == 0x19) {
        return;
    }
    if (space == 0x26) {
        func_800ECD88_name_81(-1, 0, 0);
        return;
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800ECD88_name_81(-1, 0, 0);
    HuPrcVSleep();
    func_80105A58_duel02();
    path = func_800D76A0_name_81(GwSystem.current_player_index, D_80116F40_duel02);
    func_800D742C_name_81(path, GwSystem.current_player_index, 0);
    if (func_800F37B8_name_81(-1) != 0) {
        n = func_800D97B0_name_81(D_80116B68_duel02);
        for (i = 0; i < n; i++) {
            func_800D7250_name_81(path, -2);
        }
        func_800D7250_name_81(path, -4);
    }
    ret = func_800D7518_name_81(path);
    func_800D6CA0_name_81(path);
    func_80105B10_duel02();
    if (ret != 0) {
        func_800E9F4C_name_81(0x26, &player->nlink, &player->nidx);
        func_800ED788_name_81(GwSystem.current_player_index);
        func_800E9F4C_name_81(0xE, &player->nnlink, &player->nnidx);
    }
}

void func_80115D64_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    UnkEA790Struct *path;
    s32 i;
    s32 n;
    s32 ret;

    if (MBDMasuLinkMasuIdGet(player->blink, player->bidx) == 0x1F) {
        func_800ECD88_name_81(-1, 3, 0);
        return;
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800ECD88_name_81(-1, 3, 0);
    HuPrcVSleep();
    func_80105A58_duel02();
    path = func_800D76A0_name_81(GwSystem.current_player_index, D_80116F58_duel02);
    func_800D742C_name_81(path, GwSystem.current_player_index, 0);
    if (func_800F37B8_name_81(-1) != 0) {
        n = func_800D97B0_name_81(D_80116D30_duel02);
        for (i = 0; i < n; i++) {
            func_800D7250_name_81(path, -2);
        }
        func_800D7250_name_81(path, -4);
    }
    ret = func_800D7518_name_81(path);
    func_800D6CA0_name_81(path);
    func_80105B10_duel02();
    if (ret != 0) {
        func_800E9F4C_name_81(0x1F, &player->nlink, &player->nidx);
        func_800ED788_name_81(GwSystem.current_player_index);
        func_800E9F4C_name_81(0x19, &player->nnlink, &player->nnidx);
    }
}

void func_80115EE4_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    UnkEA790Struct *path;
    s32 i;
    s32 n;
    s32 ret;

    if (MBDMasuLinkMasuIdGet(player->blink, player->bidx) == 0x29) {
        func_800ECD88_name_81(-1, 2, 0);
        return;
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800ECD88_name_81(-1, 2, 0);
    HuPrcVSleep();
    func_80105A58_duel02();
    path = func_800D76A0_name_81(GwSystem.current_player_index, D_80116F70_duel02);
    func_800D742C_name_81(path, GwSystem.current_player_index, 0);
    if (func_800F37B8_name_81(-1) != 0) {
        n = func_800D97B0_name_81(D_80116EF8_duel02);
        for (i = 0; i < n; i++) {
            func_800D7250_name_81(path, -2);
        }
        func_800D7250_name_81(path, -4);
    }
    ret = func_800D7518_name_81(path);
    func_800D6CA0_name_81(path);
    func_80105B10_duel02();
    if (ret != 0) {
        func_800E9F4C_name_81(0x29, &player->nlink, &player->nidx);
        func_800ED788_name_81(GwSystem.current_player_index);
        func_800E9F4C_name_81(7, &player->nnlink, &player->nnidx);
    }
}

void func_80116064_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
        func_800E9F4C_name_81(0x1F, &player->nlink, &player->nidx);
        if (mbWalkNum != 0) {
            func_8010EB98_duel02(1);
        }
    }
}

void func_8011611C_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
        func_800E9F4C_name_81(0x29, &player->nlink, &player->nidx);
        if (mbWalkNum != 0) {
            func_8010EB98_duel02(0);
        }
    }
}

void func_801161D4_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(0x19, &player->nnlink, &player->nnidx);
    }
    if (player->rev & 1) {
        func_8010EB40_duel02(1);
    }
}

void func_80116240_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x1F, &player->nnlink, &player->nnidx);
    }
}

void func_8011628C_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(7, &player->nnlink, &player->nnidx);
    }
    if (player->rev & 1) {
        func_8010EB40_duel02(0);
    }
}

void func_801162F8_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x29, &player->nnlink, &player->nnidx);
    }
}

void func_80116344_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    func_800E9F4C_name_81(0x13, &player->nnlink, &player->nnidx);
}

void func_80116370_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    func_800E9F4C_name_81(0xE, &player->nnlink, &player->nnidx);
}

void func_8011639C_duel02(void) {
}

// board da3: the current player's reverse flag when the opponent stands on the current player's next space, else -1
s32 func_801163A4_duel02(void) {
    s32 idx = GwSystem.current_player_index;
    s32 other = (idx + 1) & 1;
    GW_PLAYER *cur = MBDGetPlayerStruct(idx);
    GW_PLAYER *opp = MBDGetPlayerStruct(other);

    if (cur->nlink == opp->clink && cur->nidx == opp->cidx) {
        return cur->rev & 1;
    }
    return -1;
}

// board da3: place the opponent between spaces 0x2A and 0x20 (front partner 12 to the right, back partner 12 along 60 degrees)
void func_80116414_duel02(void) {
    s8 linkIdx[2]; // link, index
    Vec pos[3]; // center, front, back
    GW_PLAYER *player;
    SpaceData *space;
    s8 playerNo;

    playerNo = GwSystem.current_player_index ^ 1;
    player = MBDGetPlayerStruct(playerNo);
    func_800E9F4C_name_81(0x2A, &linkIdx[0], &linkIdx[1]);
    func_800ECD0C_name_81(playerNo, linkIdx[0], linkIdx[1]);
    player->rev = 0;
    player->nnlink = -1;
    player->nnidx = -1;
    space = MBDMasuGet(0x2A);
    HuVecAdd(&pos[0], &space->coords, &MBDMasuGet(0x20)->coords);
    HuVecMulScalar(&pos[0], 0.5f, &pos[0]);
    HuVecCopy3F(&pos[1], &pos[0]);
    pos[1].x += 12.0f;
    HuVecCopy3F(&pos[2], &pos[0]);
    pos[2].x -= sindf(60.0f) * 12.0f;
    pos[2].z -= cosdf(60.0f) * 12.0f;
    func_800E27D4_name_81(playerNo, &pos[0], &pos[1], &pos[2]);
}

void func_80116564_duel02(void) {
}

/* .data */
// board da3: the unit's .data (0x3FD160, 0xAD0 bytes)
s32 func_80113CEC_duel02(void);
s32 func_80114630_duel02(void);
s32 func_80114B94_duel02(void);
s32 func_801154DC_duel02(void);
typedef Duel01Weight Da3Weight; /* a weighted choice: taken when a roll of 100 falls under chance; value -1 ends a list */

s32 D_801165A0_duel02[2] = { 0x37, 0x39 };
s32 D_801165A8_duel02[5] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F }; /* count, then file ids */
f32 D_801165BC_duel02 = 3.0f;
s32 D_801165C0_duel02[4] = { 3, 0xA011D, 0xA011E, 0xA0121 }; /* count, then file ids */
s16 D_801165D0_duel02 = 0x22; /* bell object: from space id */
s16 D_801165D2_duel02 = 0x21; /* to */
Process *D_801165D4_duel02 = NULL;
s16 D_801165D8_duel02 = 0x24; /* second object: from space id */
s16 D_801165DA_duel02 = 0x23; /* to */
Process *D_801165DC_duel02 = NULL;
s16 D_801165E0_duel02[2] = { 0x25, 0x27 };
Vec D_801165E4_duel02[2] = { { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } };
s32 D_801165FC_duel02[2] = { 1, 0x13014B }; /* count, then file ids */
s8 D_80116604_duel02[13 * 2] = { /* value, chance pairs (D_80116605_duel02 = [1]) */
    7, 30, 6, 30, 4, 30, 1, 30, 11, 30, 8, 20, 3, 20,
    10, 20, 0, 20, 2, 20, 9, 20, 5, 20, -1, -1,
};
Da3Weight D_80116620_duel02[14] = {
    { 0, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_8011663C_duel02[14] = {
    { 1, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_80116658_duel02[14] = {
    { 2, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_80116674_duel02[14] = {
    { 4, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_80116690_duel02[14] = {
    { 3, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_801166AC_duel02[14] = {
    { 5, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_801166C8_duel02[14] = {
    { 7, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Da3Weight D_801166E4_duel02[14] = {
    { 6, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};

Da3Weight *D_80116700_duel02[8] = {
    D_80116620_duel02, D_8011663C_duel02, D_80116658_duel02, D_80116674_duel02,
    D_80116690_duel02, D_801166AC_duel02, D_801166C8_duel02, D_801166E4_duel02,
};
/* the asm reads the low halves: D_80116722/26/2A_duel02 = (s16 *)&[0..2] + 1 */
s32 D_80116720_duel02[2][3] = { { 0x1E, 0x21, 0x22 }, { 0x1D, 0x23, 0x24 } };
s32 D_80116738_duel02 = -1;
Object *D_8011673C_duel02 = NULL;
s32 D_80116740_duel02 = 0;
event_list_entry D_80116744_duel02[2] = {
    { 1, 1, func_80110BBC_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116754_duel02[2] = {
    { 1, 1, func_80110C18_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116764_duel02[2] = {
    { 7, 1, func_80110C7C_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116774_duel02[3] = {
    { 1, 1, func_80111E3C_duel02 },
    { 8, 1, func_80116564_duel02 },
    { 0, 0, NULL },
};
/* indexed from 1: the asm addresses it as D_80116788_duel02 (= this - 4) */
void (*D_8011678C_duel02[11])(void) = {
    func_80112428_duel02, func_80112518_duel02, func_80112554_duel02, func_801125D0_duel02,
    func_8011260C_duel02, func_8011268C_duel02, func_80112A08_duel02, func_80112BF4_duel02,
    func_80112DE0_duel02, func_80113618_duel02, func_80113910_duel02,
};
event_table_entry D_801167B8_duel02[5] = {
    { 30, D_80116744_duel02 },
    { 29, D_80116754_duel02 },
    { -5, D_80116764_duel02 },
    { 42, D_80116774_duel02 },
    { -1, NULL },
};
/* roll -> space index tables (the asm also reads them as D_801167DC/E7/F3/FC_duel02 = [-4], [-5], [-5], [-4]) */
u8 D_801167E0_duel02[12] = { 0xFF, 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 0 };
u8 D_801167EC_duel02[12] = { 0xFF, 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 0 };
u8 D_801167F8_duel02[8] = { 0xFF, 0, 1, 2, 4, 0, 0, 0 };
u8 D_80116800_duel02[8] = { 0xFF, 0, 1, 2, 3, 4, 0, 0 };
DecisionTreeNonLeafNode D_80116808_duel02[2] = {
    { 0x5, { .func = func_80113CEC_duel02 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_80116820_duel02[3] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116808_duel02 } },
    { 0x5, { .func = func_80114630_duel02 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_80116844_duel02[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80116868_duel02[2] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80116880_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116844_duel02 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116868_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_801168B0_duel02[7] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116880_duel02 } },
    { 0x2, { .data = 0x00000008 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0001060B }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0000000B }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80116904_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x7, { .data = 0x00000007 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x164C9932 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_80116934_duel02[2] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_8011694C_duel02[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80116970_duel02[4] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116904_duel02 } },
    { 0x7, { .data = 0x00000004 }, { .node_data = D_8011694C_duel02 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_80116934_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_801169A0_duel02[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80116820_duel02 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_801168B0_duel02 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80116970_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_801169D0_duel02[2] = {
    { 0x5, { .func = func_80114B94_duel02 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_801169E8_duel02[3] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_801169D0_duel02 } },
    { 0x5, { .func = func_801154DC_duel02 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_80116A0C_duel02[3] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80116A30_duel02[2] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80116A48_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116A0C_duel02 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116A30_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80116A78_duel02[7] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80116A48_duel02 } },
    { 0x2, { .data = 0x00000008 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0000060B }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0001000B }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80116ACC_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x7, { .data = 0x00000007 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x164C9932 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_80116AFC_duel02[2] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80116B14_duel02[3] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x1A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80116B38_duel02[4] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80116ACC_duel02 } },
    { 0x7, { .data = 0x00000004 }, { .node_data = D_80116B14_duel02 } },
    { 0xB, { .data = 0x00030005 }, { .node_data = D_80116AFC_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80116B68_duel02[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_801169E8_duel02 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80116A78_duel02 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80116B38_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80116B98_duel02[2] = {
    { 0x5, { .func = func_80114B94_duel02 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80116BB0_duel02[3] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80116B98_duel02 } },
    { 0x5, { .func = func_801154DC_duel02 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80116BD4_duel02[3] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116BF8_duel02[2] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116C10_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116BD4_duel02 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116BF8_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116C40_duel02[7] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80116C10_duel02 } },
    { 0x2, { .data = 0x00000008 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x0000060B }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x0001000B }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x18D1A346 } },
};
DecisionTreeNonLeafNode D_80116C94_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x7, { .data = 0x00000007 }, { .data = 0x1A142850 } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x064C9932 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1A142850 } },
};
DecisionTreeNonLeafNode D_80116CC4_duel02[2] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116CDC_duel02[3] = {
    { 0xB, { .data = 0x00030005 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116D00_duel02[4] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80116C94_duel02 } },
    { 0x7, { .data = 0x00000004 }, { .node_data = D_80116CDC_duel02 } },
    { 0xB, { .data = 0x00030005 }, { .node_data = D_80116CC4_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116D30_duel02[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80116BB0_duel02 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80116C40_duel02 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80116D00_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode D_80116D60_duel02[2] = {
    { 0x5, { .func = func_80113CEC_duel02 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80116D78_duel02[3] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116D60_duel02 } },
    { 0x5, { .func = func_80114630_duel02 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80116D9C_duel02[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116DC0_duel02[2] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116DD8_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116D9C_duel02 } },
    { 0x7, { .data = 0x00000009 }, { .node_data = D_80116DC0_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1B56AD5A } },
};
DecisionTreeNonLeafNode D_80116E08_duel02[7] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116DD8_duel02 } },
    { 0x2, { .data = 0x00000008 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x0001060B }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x0000000B }, { .data = 0x0B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x18D1A346 } },
};
DecisionTreeNonLeafNode D_80116E5C_duel02[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x7, { .data = 0x00000007 }, { .data = 0x1A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x064C9932 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1A142850 } },
};
DecisionTreeNonLeafNode D_80116E8C_duel02[2] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116EA4_duel02[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00030005 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116EC8_duel02[4] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80116E5C_duel02 } },
    { 0x7, { .data = 0x00000004 }, { .node_data = D_80116EA4_duel02 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_80116E8C_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x178F1E3C } },
};
DecisionTreeNonLeafNode D_80116EF8_duel02[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80116D78_duel02 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80116E08_duel02 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80116EC8_duel02 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
s16 D_80116F28_duel02[3] = { 0x7, 0x28, -1 };
event_list_entry D_80116F30_duel02[2] = {
    { 1, 1, func_80115A54_duel02 },
    { 0, 0, NULL },
};
s16 D_80116F40_duel02[3] = { 0x19, 0x26, -1 };
event_list_entry D_80116F48_duel02[2] = {
    { 1, 1, func_80115BDC_duel02 },
    { 0, 0, NULL },
};
s16 D_80116F58_duel02[3] = { 0xE, 0x1F, -1 };
event_list_entry D_80116F60_duel02[2] = {
    { 1, 1, func_80115D64_duel02 },
    { 0, 0, NULL },
};
s16 D_80116F70_duel02[3] = { 0x13, 0x29, -1 };
event_list_entry D_80116F78_duel02[2] = {
    { 1, 1, func_80115EE4_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116F88_duel02[2] = {
    { 1, 1, func_80116064_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116F98_duel02[2] = {
    { 1, 1, func_8011611C_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FA8_duel02[2] = {
    { 1, 1, func_801161D4_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FB8_duel02[2] = {
    { 1, 1, func_80116240_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FC8_duel02[2] = {
    { 1, 1, func_8011628C_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FD8_duel02[2] = {
    { 1, 1, func_801162F8_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FE8_duel02[2] = {
    { 1, 1, func_80116344_duel02 },
    { 0, 0, NULL },
};
event_list_entry D_80116FF8_duel02[2] = {
    { 1, 1, func_80116370_duel02 },
    { 0, 0, NULL },
};
event_table_entry D_80117008_duel02[13] = {
    { 41, D_80116F30_duel02 },
    { 31, D_80116F48_duel02 },
    { 38, D_80116F60_duel02 },
    { 40, D_80116F78_duel02 },
    { 25, D_80116F88_duel02 },
    { 7, D_80116F98_duel02 },
    { 24, D_80116FA8_duel02 },
    { 26, D_80116FB8_duel02 },
    { 6, D_80116FC8_duel02 },
    { 8, D_80116FD8_duel02 },
    { 18, D_80116FE8_duel02 },
    { 23, D_80116FF8_duel02 },
    { -1, NULL },
};
