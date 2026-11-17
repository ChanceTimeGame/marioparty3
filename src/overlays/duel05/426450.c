#include "common.h"
#include "process.h"
#include "common_structs.h"
#include "malloc.h"
#include "game/board.h"
#include "game/object.h"

// board dc1: declarations for func_801059D0_duel05..func_8010AD58_duel05 (from duel01.h / 3D8AC0.c, renamed)
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
extern s32 D_801163A0_duel05;
extern s32 D_801163A4_duel05;
extern s32 D_801163A8_duel05;
extern s32 D_801163AC_duel05;
void func_800E94D0_name_81(void);
void func_800E9564_name_81(void);
void func_800E9B10_name_81(s32, s32);
void func_800E9D9C_name_81(void);
void func_800E9F4C_name_81(s32, s8*, s8*);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s32, s8, s8);
void func_800EB708_name_81(Vec*, Vec*, Vec*); // duel b1: was (s32, s32, unkStruct01*)
unkStruct03* func_80047EA0_main(void*, s32, s32, s32);
void func_80105CD0_duel05(void); //probably takes object as arg
void func_800FC8C4_name_81(void*);
extern Vec D_80105540_name_81; // duel b1: was s32
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32); // duel b1: was (void*, s32, void*, f32)
Process* func_800EBF2C_name_81(Vec* from, Vec* to, Vec* out, s32 frames); // duel b1/b7: ovl_81 DFD60.c
void func_80106318_duel05(void);
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
extern Object* D_801163B0_duel05;
extern Object* D_801163B4_duel05;
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

extern s32 D_801156B0_duel05[]; // partner attack effect model ids, by level - 1 (read as u8)
extern char D_80115DC0_duel05[]; // "obj1"
/* board dc1: literals duel01 keeps in .rodata sit in duel05's asm .data */
extern char D_80115DC8_duel05[]; // "item_hook"
extern const f64 D_80115DD8_duel05; // 1.0
extern const f64 D_80115DE0_duel05; // 1.0
extern const f64 D_80115DE8_duel05; // 1.0
extern const f64 D_80115DF0_duel05; // 1.0
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
void func_8010616C_duel05(Object*, Object*, GW_PLAYER*, Vec*, Vec*, f32);
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

// ---- from 3D8AC0.c


// duel b2: local types and prototypes for func_8010A210..func_8010DB2C
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
extern Object *D_801163B8_duel05;
extern s32 D_801156B8_duel05[];

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;

void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void *func_8001D33C_main(s16 model, char *name);

extern s32 D_801156B0_duel05[];
extern s32 D_80105550_name_81;
extern s32 D_80105558_name_81;
extern s32 D_80105718_name_81;
extern s32 D_8010571C_name_81;
extern char D_80115DC0_duel05[];

void func_800D90D0_name_81(Object *, s16, u16);
Process *func_800DCE40_name_81(s32 type, Vec *pos, Vec *vel, f32 scale);
s32 func_800DD1E0_name_81(s32 data, char *name);
void func_800DD2BC_name_81(s32 model); // defined with s16 model
void func_800DD2DC_name_81(s32 model, Vec *pos); // defined with s16 model
s32 func_800DD3B4_name_81(s32 model);
void func_800EB804_name_81(Object *obj);
void func_800ED214_name_81(s32 playerIndex);
void func_800EFABC_name_81(Object *);
Process *func_800FAB68_name_81(Object *obj, s32 amount, s32 motion, s32 flags, s32 seNo);
void func_800FAC1C_name_81(Vec *arg0);
void func_800FAD04_name_81(s32 arg0);
void func_800FADB4_name_81(void);
Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
void func_800FAE98_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_800FC888_name_81(s32 arg0);
void MBDBackTPLvlSet(u8 arg0);
Object *func_800D8B18_name_81(Object *obj);
void func_800EF7C8_name_81(Object *obj, f32 arg1, f32 arg2);
s32 func_800EF7D4_name_81(Object *obj);
s32 func_800EFE20_name_81(f32 arg0);
Process *func_800DCC8C_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
void func_800D918C_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_8010AAC0_duel05(Object *obj, s32 create);
void func_8010AD58_duel05(Object *obj);
void func_800FAE18_name_81(Object *arg0, s16 arg1, s16 arg2);
Process *func_801060E0_duel05(GW_PLAYER *player, Object *target, s32 arg2, s32 arg3);
void func_8010616C_duel05(Object *partner, Object *target, GW_PLAYER *player, Vec *arg3, Vec *arg4, f32 arg5);

u16 func_80014618_main(s16 index, u16 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_80014850_main(s16 index);
void func_80016638_main(s32 index);
void func_800166D0_main(void);
void func_800D7828_name_81(Vec *vec);
void func_800D8F3C_name_81(Object *arg0);
void func_800FAC94_name_81(DuelB2PartnerFunc *arg0, DuelB2PartnerFunc *arg1);
void func_800EA7D4_name_81(void);
void func_800EA97C_name_81(void);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2); // defined with two parameters in E3CD0.c
void func_800EA46C_name_81(event_table_entry *arg0);
void func_800FC5A8_name_81(process_func arg0);
void func_800FC59C_name_81(s32 arg0);
void func_800FF640_name_81(u32 arg0);

void func_80106838_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107198_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801079C8_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107ECC_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80109898_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801084B4_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80108560_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010A220_duel05(s32, s32, Object *, Object *, s32, s32);

// board dc1: end

void func_801059D0_duel05(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel05(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_801163A0_duel05 = func_800E1824_name_81(0, 0xA0, 1);
    D_801163A4_duel05 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_801163A8_duel05 = func_800E1824_name_81(1, 0xBC, 1);
    D_801163AC_duel05 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel05(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_801163A0_duel05);
    func_800E1854_name_81(D_801163A4_duel05);
    func_800E1854_name_81(D_801163A8_duel05);
    func_800E1854_name_81(D_801163AC_duel05);
}

void func_80105B64_duel05(void) {
    GwSystem.current_board_index = 4;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105BA0_duel05(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x245);
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
    GwSystem.boardData.halfWordBytes[0] = 0;
    GwSystem.boardData.halfWordBytes[1] = 1;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C74_duel05(Vec *arg0, Vec *arg1, Vec *arg2) { // duel b1: Vec* (was s32, s32, unkStruct01*)
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(temp_f20);
    arg2->z = cosdf(temp_f20);
}

void func_80105CD0_duel05(void) {
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

void *func_80105EC0_duel05(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105CD0_duel05, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

void func_80105F30_duel05(void) {
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
    func_80105EC0_duel05((unkStruct04 *)obj);
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

Process *func_801060E0_duel05(GW_PLAYER *player, Object *obj, s32 delay, s32 wait) {
    Process *process;
    B1ThwompPrc *work;

    process = omAddPrcObj(func_80105F30_duel05, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(B1ThwompPrc));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->wait = wait;
    return process;
}

void func_8010616C_duel05(Object *obj, Object *target, GW_PLAYER *player, Vec *dest, Vec *start, f32 dist) {
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

void func_80106250_duel05(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

Process *func_80106270_duel05(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) { // duel b1: returns the camera move (was void)
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
    return process;
}

Process *func_801062D0_duel05(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 frames) {
    Process *process;

    if (arg2 & 9) {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, frames);
    } else {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, frames);
    }
    return process;
}

void func_80106318_duel05(void) {
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

Process *func_8010646C_duel05(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_80106318_duel05, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

void func_801064D8_duel05(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *obj;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
    case 0:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            obj = func_800D8010_name_81(0x28, 0);
            D_801163B0_duel05 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            obj = func_800D8010_name_81(0x28, 0);
            D_801163B4_duel05 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        break;
    case 1:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            func_800D8F3C_name_81(D_801163B0_duel05);
            func_800D8E88_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            func_800D8F3C_name_81(D_801163B4_duel05);
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
            D_801163B0_duel05 = obj;
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
            D_801163B4_duel05 = obj;
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
                func_800D8F3C_name_81(D_801163B0_duel05);
                func_800D8E88_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                func_800D8F3C_name_81(D_801163B4_duel05);
                func_800D8E88_name_81(partner);
            }
            break;
        }
        break;
    }
}

void *func_80106750_duel05(s32 arg0) {
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

void func_801067E4_duel05(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0); // duel b1: was ()
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

void func_80106838_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
        standIn = func_80106750_duel05(0x45);
    }
    effect = func_800D8010_name_81(D_801156B0_duel05[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_80106250_duel05();
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
    func_8010616C_duel05(partner, target, player, &dest, &start, 6.0f);
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
    func_80106270_duel05(target, player, flags, 3.0f);
    if (flags & 8) {
        func_801060E0_duel05(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        if (level == 1) {
            func_801067E4_duel05(standIn, &partner->coords);
        }
        if (flags & 1) {
            HuVecAdd(&mid, &target->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C74_duel05(&target->coords, &standIn->coords, &standIn->rot);
                func_801067E4_duel05(standIn, &target->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
                func_800DD2DC_name_81(model, &mid);
            }
        } else {
            HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C74_duel05(&player->player_obj->coords, &standIn->coords, &standIn->rot);
                func_801067E4_duel05(standIn, &player->player_obj->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
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

void func_80107198_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_80106750_duel05(standInIds[level - 1]);
    effect = func_800D8010_name_81(D_801156B0_duel05[level - 1] & 0xFF, 0);
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
    func_8010616C_duel05(partner, target, player, &dest, &start, 7.0f);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
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
        func_801060E0_duel05(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        func_801067E4_duel05(standIn, &partner->coords);
        HuAudFXPlay(0x25B);
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += partner->velocity.x;
        func_801067E4_duel05(standIn, midp);
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

#ifdef NON_MATCHING // duel b1: masked 0; $s7/$s8 swapped between the stand-in and effect models
void func_801079C8_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_80106750_duel05(standInIds[level - 1]);
    effect = func_800D8010_name_81(D_801156B0_duel05[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    hook = func_800D8010_name_81(0x3F, 0);
    func_800D8F0C_name_81(hook);
    func_800F0378_name_81(partner, D_80115DC8_duel05, hook->omObj1->model[0]);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010616C_duel05(partner, target, player, &dest, &start, 6.0f);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
    HuPrcChildWait();
    func_800D8F0C_name_81(effect);
    func_800D8E88_name_81(hook);
    if (level == 2) {
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
    if (flags & 8) {
        func_801060E0_duel05(player, target, 0, 20);
    } else {
        HuPrcSleep(9);
        HuAudFXPlay(0x1D7);
        if (level == 2) {
            HuAudFXPlay(0x1F2);
        }
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        func_800EB804_name_81(standIn);
        func_801067E4_duel05(standIn, midp);
        func_800DCE40_name_81(effectIds[level - 1], &mid, NULL, 2.0f);
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
        }
        if (flags & 2) {
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801079C8_duel05);
#endif

void func_80107ECC_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_80106750_duel05(standInIds[level - 1]);
    HuVecCopyXYZ(&standIn->scale, 2.0f, 2.0f, 2.0f);
    if (level == 2) {
        HuPrcVSleep();
        blast = func_80106750_duel05(0x5B);
        HuPrcVSleep();
    }
    effect = func_800D8010_name_81(D_801156B0_duel05[level - 1] & 0xFF, 0);
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
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 2.0f);
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
        func_801067E4_duel05(blast, &partner->coords);
        func_8001C92C_main(blast->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        func_801067E4_duel05(standIn, &mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (level == 1) {
        func_801067E4_duel05(standIn, &mid);
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

void func_801084B4_duel05(s32 playerIndex, s32 arg1, Object *partner, Object *target, s32 arg4, s32 count) {
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

#ifdef NON_MATCHING // duel b1: masked 0; float registers of the final squash loop ($f20/$f22/$f24) rotated
void func_80108560_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_80106750_duel05(0x55);
    func_8010616C_duel05(partner, target, player, &dest, &start, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
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
                func_801060E0_duel05(player, target, 0, 55);
            } else {
                func_801060E0_duel05(player, target, 0, 120);
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
            func_801064D8_duel05(targetIndex, 2);
            if (level == 1) {
                func_800EB804_name_81(standIn);
                func_801067E4_duel05(standIn, &target->coords);
                func_800DCE40_name_81(0x47, &target->coords, NULL, 1.0f);
            } else {
                dust = func_800D8010_name_81(0x5A, 0);
                func_800D974C_name_81(dust);
                HuVecCopy3F(&dust->coords, &partner->coords);
                model = func_800DD1E0_name_81(0xB0023, D_80115DC0_duel05);
                func_800DD2DC_name_81(model, &partner->coords);
            }
        }
        if (level == 1) {
            func_8010646C_duel05(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, func_8010646C_duel05(5, 2));
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
                    func_801067E4_duel05(standIn, &partner->coords);
                    func_800DCE40_name_81(0x47, &partner->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    dust = func_800D8010_name_81(0x5A, 0);
                    func_800D974C_name_81(dust);
                    HuVecCopy3F(&dust->coords, &partner->coords);
                }
                HuPrcChildLink(process, func_8010646C_duel05(5, 2));
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
        func_801064D8_duel05(targetIndex, 3);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80108560_duel05);
#endif

void func_80109414_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    func_8010616C_duel05(partner, target, player, &dest, &start, 0.0f);
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
    dest.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    frames = HuVecGetLength3F(&diff) / 3.0f;
    partner->flags |= 1;
    if (flags & 8) {
        func_801060E0_duel05(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
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

void func_80109898_duel05(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
        func_80109414_duel05(playerIndex, targetIndex, partner, target, flags, 1);
        return;
    }
    level &= ~0x10;
    func_800D90D0_name_81(partner, 0, 2);
    func_8010616C_duel05(partner, target, player, &near, &start, 6.0f);
    func_8010616C_duel05(partner, target, player, &dest, &start, 8.0f);
    func_80106250_duel05();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    HuPrcChildLink(process, func_80106270_duel05(target, player, flags, 3.0f));
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
            func_801060E0_duel05(player, target, 0, 20);
        } else {
            func_801060E0_duel05(player, target, 0, 40);
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

// board dc1: matches with &sp98 taken in each arm (duel01's twin is NON_MATCHING, masked 24)
void func_8010A220_duel05(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra2 = func_80106750_duel05(0x51);
        HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    extra1 = func_80106750_duel05(0x4C);
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
    func_80106250_duel05();
    func_801062D0_duel05(target, player, flags, 0x1E);
    if (flags & 8) {
        HuVecCopy3F(&sp78, &target->coords);
        sp78.y += 5.0f;
        func_801060E0_duel05(player, target, 0x19, 0x28);
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
        func_801067E4_duel05(extra1, &sp78);
        if (variant == 2) {
            func_801067E4_duel05(extra2, &sp78);
        }
    } else {
        if (variant != 1) {
            HuPrcSleep(0x14);
            func_800D8F0C_name_81(obj);
            HuVecCopy3F(&sp78, &obj->coords);
            sp78.y += obj->velocity.x;
            if (flags & 1) {
                vel = &sp98;
                HuVecSubtract(vel, &target->coords, &sp78);
            } else {
                vel = &sp98;
                HuVecSubtract(vel, &player->player_obj->coords, &sp78);
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
        func_801067E4_duel05(extra1, &sp78);
        if (variant == 2) {
            func_801067E4_duel05(extra2, &sp78);
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

void func_8010AAC0_duel05(Object *obj, s32 create) {
    Object *puff;
    f32 rot;
    f32 scale;

    if (create != 0) {
        D_801163B8_duel05 = func_800D8010_name_81(8, D_801156B8_duel05);
        func_800D8944_name_81(D_801163B8_duel05);
        func_800D8F0C_name_81(D_801163B8_duel05);
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
    for (scale = 1.0f; scale < 10.0f; scale += D_80115DD8_duel05) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    if (create != 0) {
        HuVecCopy3F(&D_801163B8_duel05->coords, &obj->coords);
        HuVecCopy3F(&D_801163B8_duel05->rot, &obj->rot);
        func_800D8E88_name_81(D_801163B8_duel05);
        func_800D8F0C_name_81(obj);
    }
    for (; scale >= 1.0f; scale -= D_80115DE0_duel05) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

void func_8010AD58_duel05(Object *obj) {
    Object *puff;
    f32 rot;
    f32 scale;

    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &D_801163B8_duel05->coords);
    puff->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += D_80115DE8_duel05) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &D_801163B8_duel05->coords);
    HuVecCopy3F(&obj->rot, &D_801163B8_duel05->rot);
    func_800D8F3C_name_81(D_801163B8_duel05);
    func_800D8E88_name_81(obj);
    obj->flags &= ~1;
    for (; scale >= 1.0f; scale -= D_80115DF0_duel05) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AFC4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B140_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B490_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B4D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B538_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B54C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B55C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010BCE4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010CE78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010D434_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010D96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DA04_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DA94_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DB10_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DB3C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DC14_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DCB8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DD4C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DDFC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DF78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E018_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115E78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E1C4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E2DC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E308_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E358_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E408_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E584_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E624_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E7D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E8E8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E914_duel05);

void func_8010E964_duel05(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EA00_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EAFC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EB58_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EC48_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010ECF0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010ED70_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EF8C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F0FC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110038_duel05);

// board dc3
#include "game/object.h"
#include "game/board.h"
#include "game/window.h"
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
typedef struct DuelB4HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} DuelB4HmfPart;
extern const DuelPadMask D_80115F54_duel05;
extern const DuelChoiceTbl D_80115F58_duel05;
extern const DuelB7VecTbl D_80115F60_duel05; /* smoke puff offsets around a partner leaving */
extern u8 D_80115F84_duel05[]; /* window strings: the starting partner choices (SJIS) */
extern u8 D_8011606C_duel05[];
extern u8 D_80116154_duel05[];
extern u8 D_8011623C_duel05[];
extern char D_80115E78_duel05[]; /* hmf part name (rodata) */
extern f32 D_801156CC_duel05;
extern Object *D_801163C0_duel05;
extern Object *D_80100F44_name_81;
void func_8010DC14_duel05(void);
void func_80115550_duel05(void);
Process* MBDCameraZoomMotStart(f32);
Object* MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
GW_PLAYER* MBDGetPlayerStruct(s32 playerIndex);
SpaceData *MBDMasuGet(s16);
void *func_8001D33C_main(s16, char *);
void func_8002FD8C_main(s16, s16, char *, s16, s16);
void func_8008A120_main(f32 *mtx, f32 angle); // defined with Matrix4f (f32[4][4])
Object* func_800D8010_name_81(u8, s32*);
void func_800D8F0C_name_81(Object*);
void func_800D8F3C_name_81(Object*);
void func_800D90D0_name_81(Object*, s16, u16);
void func_800D918C_name_81(Object*, s16, s16, s16, u16);
s32 func_800D9234_name_81(Object *);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
Process* func_800DCE40_name_81(s32, Vec*, Vec*, f32);
void func_800E14D8_name_81(s32, s32);
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
void func_800EAFC4_name_81(s32);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB49C_name_81(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_800EB58C_name_81(void);
void func_800EB708_name_81(Vec*, Vec*, Vec*); // duel b1: was (s32, s32, unkStruct01*)
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Process* func_800EBF2C_name_81(Vec* from, Vec* to, Vec* out, s32 frames); // duel b1/b7: ovl_81 DFD60.c
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32);
void func_800ED214_name_81(s32 playerIndex);
Object *func_800EEC40_name_81(Vec *);
void func_800EF7C8_name_81(Object*, f32, f32);
s32 func_800EFE20_name_81(f32);
void func_800F38DC_name_81(s32, s32, s32);
void func_800F57B0_name_81(s32 playerNo); // duel n7: was s16; the callee does not sign-extend
void func_800F5BB4_name_81(s32 playerIndex);
void func_800F5E2C_name_81(s32 playerNo); // duel n7: was u32
void func_800F5EB0_name_81(s32);
void func_800F7378_name_81(s32, s32);
void func_800F74E4_name_81(s32);
void func_800F8108_name_81(s32 playerIndex);
void func_800F82EC_name_81(s32);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
s32 func_800F8980_name_81(s32);
void func_800FAD04_name_81(s32 arg0);
void func_800FADB4_name_81(void);
void func_800FAE98_name_81(Object*, s16, s16, s16, s16);
void func_800FC888_name_81(s32);
void func_800FC8C4_name_81(Vec*);
void func_800FD620_name_81(void);
void Duel_PowerUpPartners(s32);
s32 func_800F37B8_name_81(s16 playerIndex);
s32 func_800EED50_name_81(void);
typedef struct DuelB4SprGrp { /* ovl_81's UnkBoard4 */
    /* 0x00 */ struct DuelB4SprGrp *unk_00;
    /* 0x04 */ struct DuelB4SprGrp *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 *unk_0C;
    /* 0x10 */ f32 *unk_10;
    /* 0x14 */ f32 *unk_14;
    /* 0x18 */ s16 *unk_18;
    /* 0x1C */ s16 *unk_1C;
} DuelB4SprGrp;
DuelB4SprGrp *func_800F4528_name_81(s16 arg0, s16 arg1);
void func_800F4584_name_81(DuelB4SprGrp *);
extern s32 D_80101200_name_81[]; /* character name messages, 0x1C00 + chr (inner label of ovl_81's D_801011FC data) */
extern void (*D_80115880_duel05[])(void); /* space events by GwSystem.minigame_index */
void func_80110038_duel05(s32 no);
void func_800ECD88_name_81(s16 playerNo, s16 link, s16 idx);
void func_800F8C68_name_81(s32);
void func_8010E96C_duel05(void);
extern s16 D_800CE1D0_main;
extern s16 D_800D124C_main;
extern s16 D_80101A50_name_81;
extern u8 D_801158D8_duel05[]; /* opponent space index by roll (read unsigned): -1 never matches */
extern u8 D_801158E0_duel05[];
extern u8 D_801158E8_duel05[];
extern u8 D_801158F0_duel05[];
extern u8 D_801158F8_duel05[];
extern u8 D_80115900_duel05[];
extern u8 D_80115908_duel05[];
void func_80105A58_duel05(void);
void func_80105B10_duel05(void);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
UnkEA790Struct *func_800D76A0_name_81(s16 arg0, s16 *arg1);
s32 func_800D742C_name_81(UnkEA790Struct *arg0, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *arg0, s32 arg1);
s32 func_800D7518_name_81(UnkEA790Struct *arg0);
void func_800D6CA0_name_81(void *arg0);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *arg0);
void func_800ED788_name_81(s32 playerNo);
extern DecisionTreeNonLeafNode D_80115A18_duel05[]; /* CPU decision trees: take the branch at the junction */
extern DecisionTreeNonLeafNode D_80115B50_duel05[];
extern s16 D_80115B80_duel05[]; /* junction choice tables */
extern s16 D_80115B98_duel05[];
/* retail passes the back link/index addresses to the empty func_80115370_duel05, so no prototype here */
void func_80115370_duel05();
void Duel_PowerDownPartners(s32);
void Duel_SwapPartnerPositions(s32);
s16 MBDGetCurrentPlayerIndex(void);
void func_800D8944_name_81(Object*);
void func_800DD41C_name_81(Vec *);
void func_800DD554_name_81(void);
void func_800DD564_name_81(void);
void func_800DD570_name_81(void);
Process *func_800E0924_name_81(void);
void func_800E18C0_name_81(void);
s32 func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E24AC_name_81(s16, s16, s16, s16);
void func_800E27D4_name_81(s16 playerIndex, Vec *pos, Vec *frontPos, Vec *backPos);
Process *func_800E4A74_name_81(s32);
void func_800E9F4C_name_81(s32, s8*, s8*);
void func_800EA7D4_name_81(void);
void func_800EA898_name_81(s32, s32);
void func_800EA8DC_name_81(void);
void func_800EA97C_name_81(void);
void func_800EB140_name_81(s32, s32);
void func_800ECD0C_name_81(s32, s8, s8);
Object *func_800EDD50_name_81(Vec *);
void func_800EDDBC_name_81(void);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE0F4_name_81(s32);
Process *func_800EE40C_name_81(s32);
void func_800EE468_name_81(s32);
void func_800EE74C_name_81(u32);
void func_800EFABC_name_81(Object*);
void func_800F3880_name_81(s32, s16, u16);
void func_800F75EC_name_81(s32);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800FFCCC_name_81(void *);
s16 func_8004ACE0_main(s16, s16);
// duel b4: spin the partner's model about Y by ang * 10 degrees (the model matrix is rebuilt as a pure Y rotation)
#define B4_PARTNER_SPIN(obj, vel, ang)                                                                         \
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

void func_80110B4C_duel05(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110038_duel05(0);
    }
}

void func_80110BA8_duel05(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110038_duel05(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EA0_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EB8_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115ED0_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EDC_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EF4_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F24_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F54_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F58_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F60_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F80_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F84_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011606C_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80116154_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011623C_duel05);

#ifdef NON_MATCHING // duel b7: masked 0 but for register allocation: one extra callee-saved register ($s8), so every $s register is one higher
/* Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4
   coins; from the second turn the player pays the partners' upkeep, or loses them when short of coins. */
void func_80110C0C_duel05(void) {
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
    padMask = D_80115F54_duel05;
    choice = D_80115F58_duel05;
    if (cur == 0 && GwSystem.current_turn == 1 && (*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        DUEL_B7_PICK(win, D_80115F84_duel05, cur, padMask, choice, buf, front, 1);
        DUEL_B7_PICK(win, D_8011606C_duel05, cur, padMask, choice, buf, back, 1);
        func_800F8418_name_81(cur, front, 0);
        func_800F8418_name_81(cur, back, 1);
        func_800F8108_name_81(cur);
        func_800ED214_name_81(cur);
        func_800F5BB4_name_81(cur);
        func_800F5EB0_name_81(cur);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(cur);
        }
        DUEL_B7_PICK(win, D_80116154_duel05, cur, padMask, choice, buf, front, 0);
        DUEL_B7_PICK(win, D_8011623C_duel05, cur, padMask, choice, buf, back, 0);
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
                    ofs = D_80115F60_duel05;
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110C0C_duel05);
#endif

#ifdef NON_MATCHING
// duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions)
// duel b4: bell space: ring the bell; at zero coins the bell pays out and the board ends the turn
void func_80111DCC_duel05(void) {
    Vec pos;
    char buf[8];
    GW_PLAYER *player;
    SpaceData *space;
    DuelB4HmfPart *part;
    f32 ofs;
    s32 i;
    char *str;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    space = MBDMasuGet(0x1D);
    func_800DB3E0_name_81(system->current_player_index);
    func_800F38DC_name_81(-1, -1, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuVecCopy3F(&pos, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &space->coords, &pos, 4.0f));
    func_800D90D0_name_81(D_801163C0_duel05, 2, 0);
    func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0],
                       HmfModelData[D_801163C0_duel05->omObj1->model[0]].unk02, D_80115E78_duel05, 0x4C, 0x46);
    func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], D_801163C0_duel05->omObj1->motion[2],
                       D_80115E78_duel05, 0x4C, 0x46);
    i = 0;
    ((DuelB4HmfPart *)func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], D_80115E78_duel05))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
    while (!(func_800D9234_name_81(D_801163C0_duel05) & 1)) {
        if (++i == 8) {
            HuAudFXPlay(0x1C5);
        }
        HuPrcVSleep();
    }
    func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0],
                       HmfModelData[D_801163C0_duel05->omObj1->model[0]].unk02, D_80115E78_duel05, 0x4C, 0x46);
    part = func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], D_80115E78_duel05);
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
    func_8010DC14_duel05();
    D_801156CC_duel05 = 12.0f;
    if (GwSystem.bank_coins != 0) {
        HuAudFXPlay(0x207);
        func_800D918C_name_81(D_801163C0_duel05, 0, 0, 5, 2);
        func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], D_801163C0_duel05->omObj1->motion[0],
                           D_80115E78_duel05, 0x4C, 0x46);
        func_8001C92C_main(D_801163C0_duel05->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(0x18);
        func_800D90D0_name_81(D_801163C0_duel05, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        func_800D918C_name_81(D_801163C0_duel05, 1, 0, 5, 2);
        func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], D_801163C0_duel05->omObj1->motion[1],
                           D_80115E78_duel05, 0x4C, 0x46);
        func_8001C92C_main(D_801163C0_duel05->omObj1->model[0], 1.0f);
        func_8010DC14_duel05();
        func_800F74E4_name_81(-1);
        func_800EEC40_name_81(&pos);
        if (system->current_turn < 11) {
            str = "20";
        } else if (system->current_turn >= 20) {
            str = "40";
        } else {
            str = "30";
        }
        sprintf(buf, str);
        HuAudFXPlay(0x2A7);
        func_800EB49C_name_81(0x15, 0x1F30, (s32)buf, 0, 0, 0, 0);
        func_800EB58C_name_81();
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80115550_duel05();
        D_80100F44_name_81 = D_801163C0_duel05;
        func_800FD620_name_81();
        HuPrcSleep(-1);
    }
    D_801156CC_duel05 = 3.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &player->player_obj->coords, &pos, 4.0f));
    func_800DADA0_name_81(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80111DCC_duel05);
#endif

void func_801123B8_duel05(void) {
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

void func_801124A8_duel05(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_801124E4_duel05(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 coins = GwPlayer[system->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(system->current_player_index, -coins);
    func_800F7378_name_81(system->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_80112560_duel05(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 10);
    func_800F7378_name_81(system->current_player_index, 10);
    HuPrcSleep(30);
}

void func_8011259C_duel05(void) {
    s8 link;
    s8 idx;
    s8 backLink = -1;
    s8 backIdx = -1;

    func_800E9F4C_name_81(MBDGetCurrentPlayerIndex() == 0 ? 0x1E : 0x1D, &link, &idx);
    func_80115370_duel05(&backLink, &backIdx);
    func_800E24AC_name_81(link, idx, backLink, backIdx);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_80110038_duel05(MBDGetCurrentPlayerIndex());
}

void func_8011261C_duel05(void) {
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

void func_80112998_duel05(void) {
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

void func_80112B84_duel05(void) {
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

void func_80112D70_duel05(void) {
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
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    Duel_SwapPartnerPositions(cur);
    func_800DD564_name_81();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win);
    /* angle is 0 here: the loop steps from 120 by 5 */
    if (player->stats.prize.gamblePrize != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 0);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    if (player->stats.prize.duelNo != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 1);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    func_800DD570_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2C);
    func_800EDF78_name_81();
    func_800EE468_name_81(1);
    func_800EDDBC_name_81();
}

void func_801135A8_duel05(void) {
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

void func_801138A0_duel05(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 20);
    func_800F7378_name_81(system->current_player_index, 20);
    HuPrcSleep(30);
}

void func_801138DC_duel05(void) {
    DuelB4SprGrp *grp;
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
    D_80115880_duel05[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
// board dc3: logic checked against the asm case by case; masked ~240: retail cross-jumps the repeated
// partner tests between cases and keeps branches where this C gets setcc (543 vs 585 instructions)
/* COM decision at a junction (the decision tree's leaf): from where the opponent stands (clink, cidx)
   relative to the roll (mbWalkNum), weigh the front partner's power against the opponent's HP (star)
   and the opponent's partners against the player's own. */
s32 func_80113C7C_duel05(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
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
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (walk < 5) {
                if (opp->stats.partners.frontPower == 0) {
                    return FALSE;
                }
                if (walk == 2) {
                    return func_800EFE20_name_81(100.0f) < 50;
                }
                return TRUE;
            }
            if (opp->cidx == 1) {
                return TRUE;
            }
            if (walk < 8 && opp->cidx == D_801158D8_duel05[walk - 3]) {
                if (opp->stats.partners.backID == 4) {
                    return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
                }
                return FALSE;
            }
            if (walk < 8 && opp->cidx < D_801158D8_duel05[walk - 3]) {
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
                        return opp->stats.partners.frontPower >= me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            return TRUE;
        case 1:
            if (walk < 5 && opp->cidx == D_801158E0_duel05[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
                }
                return FALSE;
            }
            if (walk >= 6 || opp->cidx < D_801158E0_duel05[walk]) {
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
                        return opp->stats.partners.frontPower >= me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 2:
            if (walk < 5 && opp->cidx == D_801158E8_duel05[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (walk >= 6 || opp->cidx < D_801158E8_duel05[walk]) {
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
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return FALSE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return FALSE;
                    }
                    return TRUE;
                }
                return TRUE;
            }
            if (walk != 2) {
                return TRUE;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 3:
        case 4:
            if (walk != 2) {
                return func_800EFE20_name_81(100.0f) < 70;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 5:
            if (walk >= 5 && opp->stats.partners.frontPower != 0) {
                return FALSE;
            }
            return TRUE;
        case 6:
            if (walk < 5) {
                return TRUE;
            }
            if (walk < 10 && opp->cidx == D_80115908_duel05[walk - 4]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (walk >= 10 || opp->cidx < D_80115908_duel05[walk - 4]) {
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
                        return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return FALSE;
                    }
                    return TRUE;
                }
                return TRUE;
            }
            if (walk == 2) {
                return func_800EFE20_name_81(100.0f) < 50;
            }
            return TRUE;
    }
    return TRUE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80113C7C_duel05);
#endif

#ifdef NON_MATCHING
// board dc3: logic checked against the asm case by case; masked ~240: retail cross-jumps the repeated
// partner tests between cases and keeps branches where this C gets setcc (543 vs 585 instructions)
/* The same COM decision as func_80113C7C_duel05 for the other junction (the opponent's links renumbered) (the decision tree's leaf): from where the opponent stands (clink, cidx)
   relative to the roll (mbWalkNum), weigh the front partner's power against the opponent's HP (star)
   and the opponent's partners against the player's own. */
s32 func_80114428_duel05(void) {
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    switch (opp->clink) {
        case 3:
            if (me->stats.partners.frontPower == 0) {
                return TRUE;
            }
            if (walk < 5) {
                if (opp->stats.partners.frontPower == 0) {
                    return FALSE;
                }
                if (walk == 2) {
                    return func_800EFE20_name_81(100.0f) < 50;
                }
                return TRUE;
            }
            if (opp->cidx == 1) {
                return TRUE;
            }
            if (walk < 8 && opp->cidx == D_801158F0_duel05[walk - 3]) {
                if (opp->stats.partners.backID == 4) {
                    return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
                }
                return FALSE;
            }
            if (walk < 8 && opp->cidx < D_801158F0_duel05[walk - 3]) {
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
                        return opp->stats.partners.frontPower >= me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            return TRUE;
        case 4:
            if (walk < 5 && opp->cidx == D_801158F8_duel05[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp);
                }
                return FALSE;
            }
            if (walk >= 6 || opp->cidx < D_801158F8_duel05[walk]) {
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
                        return opp->stats.partners.frontPower >= me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                }
                if (me->stats.partners.frontPower == 0 && me->stats.partners.backID != 4) {
                    return TRUE;
                }
                return FALSE;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 5:
            if (walk < 5 && opp->cidx == D_80115900_duel05[walk]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (walk >= 6 || opp->cidx < D_80115900_duel05[walk]) {
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
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return FALSE;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return FALSE;
                    }
                    return TRUE;
                }
                return TRUE;
            }
            if (walk != 2) {
                return TRUE;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 0:
        case 1:
            if (walk != 2) {
                return func_800EFE20_name_81(100.0f) < 70;
            }
            return func_800EFE20_name_81(100.0f) < 50;
        case 2:
            if (walk >= 5 && opp->stats.partners.frontPower != 0) {
                return FALSE;
            }
            return TRUE;
        case 6:
            if (walk < 5) {
                return TRUE;
            }
            if (walk < 10 && opp->cidx == D_80115908_duel05[walk - 4]) {
                if (opp->stats.partners.backID == 4) {
                    return me->stats.partners.frontPower < me->star + me->stats.partners.frontHp;
                }
                return TRUE;
            }
            if (walk >= 10 || opp->cidx < D_80115908_duel05[walk - 4]) {
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
                        return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return FALSE;
                    }
                    return TRUE;
                }
                return TRUE;
            }
            if (walk == 2) {
                return func_800EFE20_name_81(100.0f) < 50;
            }
            return TRUE;
    }
    return TRUE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114428_duel05);
#endif

void func_80114BD4_duel05(void) {
    GW_PLAYER *player;
    UnkEA790Struct *tree;
    s32 result;
    s32 i;
    s32 count;

    player = MBDGetPlayerStruct(-1);
    if (MBDMasuLinkMasuIdGet(player->blink, player->bidx) != 0x12) {
        func_800F38DC_name_81(-1, -1, 2);
        func_800ECD88_name_81(-1, 2, 0);
        HuPrcVSleep();
        func_80105A58_duel05();
        tree = func_800D76A0_name_81(GwSystem.current_player_index, D_80115B80_duel05);
        func_800D742C_name_81(tree, GwSystem.current_player_index, 0);
        if (func_800F37B8_name_81(-1) != 0) {
            count = func_800D97B0_name_81(D_80115A18_duel05);
            for (i = 0; i < count; i++) {
                func_800D7250_name_81(tree, -2);
            }
            func_800D7250_name_81(tree, -4);
        }
        result = func_800D7518_name_81(tree);
        func_800D6CA0_name_81(tree);
        func_80105B10_duel05();
        if (result != 0) {
            func_800ECD88_name_81(-1, 1, 0);
            func_800ED788_name_81(GwSystem.current_player_index);
        }
    }
}

void func_80114D24_duel05(void) {
    GW_PLAYER *player;
    UnkEA790Struct *tree;
    s32 result;
    s32 i;
    s32 count;

    player = MBDGetPlayerStruct(-1);
    if (MBDMasuLinkMasuIdGet(player->blink, player->bidx) != 0x1C) {
        func_800F38DC_name_81(-1, -1, 2);
        func_800ECD88_name_81(-1, 5, 0);
        HuPrcVSleep();
        func_80105A58_duel05();
        tree = func_800D76A0_name_81(GwSystem.current_player_index, D_80115B98_duel05);
        func_800D742C_name_81(tree, GwSystem.current_player_index, 0);
        if (func_800F37B8_name_81(-1) != 0) {
            count = func_800D97B0_name_81(D_80115B50_duel05);
            for (i = 0; i < count; i++) {
                func_800D7250_name_81(tree, -2);
            }
            func_800D7250_name_81(tree, -4);
        }
        result = func_800D7518_name_81(tree);
        func_800D6CA0_name_81(tree);
        func_80105B10_duel05();
        if (result != 0) {
            func_800ECD88_name_81(-1, 4, 0);
            func_800ED788_name_81(GwSystem.current_player_index);
        }
    }
}

void func_80114E74_duel05(void) {
    func_800ECD88_name_81(-1, 0, 3);
}

void func_80114E98_duel05(void) {
    func_800ECD88_name_81(-1, 3, 3);
}

void func_80114EBC_duel05(void) {
    if (!(MBDGetPlayerStruct(-1)->rev & 1)) {
        func_800ECD88_name_81(-1, 6, 0);
    }
    GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] = 0;
}

void func_80114F10_duel05(void) {
    if (!(MBDGetPlayerStruct(-1)->rev & 1)) {
        func_800ECD88_name_81(-1, 6, 0);
    }
    GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] = 1;
}

void func_80114F68_duel05(void) {
    if (GwSystem.current_turn & 1) {
        func_800ECD88_name_81(-1, 0, 0);
    } else {
        func_800ECD88_name_81(-1, 3, 0);
    }
    func_8001FDE8_main(MBDGetPlayerStruct(-1)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(MBDGetCurrentPlayerIndex());
}

void func_80114FD8_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (player->rev & 1) {
        func_800E9F4C_name_81(GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] == 0 ? 0x15 : 3,
                              &player->nlink, &player->nidx);
        if (mbWalkNum != 0) {
            func_800EAFC4_name_81(0x2200);
        }
    }
}

void func_8011505C_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (player->rev & 1) {
        func_800E9F4C_name_81(0x28, &player->nlink, &player->nidx);
    }
}

void func_80115098_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (player->rev & 1) {
        func_800E9F4C_name_81(0x1F, &player->nlink, &player->nidx);
    }
}

void func_801150D4_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(0x1C, &player->nnlink, &player->nnidx);
    }
}

void func_80115120_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    func_800E9F4C_name_81(0xB, &player->nnlink, &player->nnidx);
}

void func_8011514C_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x1F, &player->nnlink, &player->nnidx);
    }
}

void func_80115198_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(4, &player->nnlink, &player->nnidx);
    }
}

void func_801151E4_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(0x12, &player->nnlink, &player->nnidx);
    }
}

void func_80115230_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    func_800E9F4C_name_81(0xA, &player->nnlink, &player->nnidx);
}

void func_8011525C_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x28, &player->nnlink, &player->nnidx);
    }
}

void func_801152A8_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(4, &player->nnlink, &player->nnidx);
    }
}

void func_801152F4_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] == 0 ? 0x15 : 3,
                              &player->nnlink, &player->nnidx);
    }
}

void func_80115370_duel05(void) {
}

s32 func_80115378_duel05(void) {
    GW_PLAYER *player;
    GW_PLAYER *otherPlayer;
    s32 cur = GwSystem.current_player_index;
    s32 other = (cur + 1) & 1;

    player = MBDGetPlayerStruct(cur);
    otherPlayer = MBDGetPlayerStruct(other);
    if (player->nlink == otherPlayer->clink) {
        if (player->nidx == otherPlayer->cidx) {
            return player->rev & 1;
        }
        return -1;
    }
    return -1;
}

void func_801153E8_duel05(void) {
    GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] = 1;
}

void func_8011541C_duel05(void) {
    GwSystem.boardData.halfWordBytes[MBDGetCurrentPlayerIndex()] = 0;
}

void func_8011544C_duel05(void) {
    func_8010E96C_duel05();
}

/* Before moving: with walk left, take the turn's branch; with partner 7 and no other event pending, a 50%
   chance to take it anyway (D_80101A50_name_81 records the roll). */
void func_80115468_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);

    if (mbWalkNum != 0) {
        if (GwSystem.current_turn & 1) {
            func_800E9F4C_name_81(0x25, &player->nnlink, &player->nnidx);
        } else {
            func_800E9F4C_name_81(0x24, &player->nnlink, &player->nnidx);
        }
        return;
    }
    if ((player->stats.partners.frontID == 7 || player->stats.partners.backID == 7) && D_800D124C_main == 0 &&
        D_800CE1D0_main == 0) {
        if (func_800EFE20_name_81(100.0f) < 50) {
            D_80101A50_name_81 = 1;
            if (GwSystem.current_turn & 1) {
                func_800E9F4C_name_81(0x25, &player->nnlink, &player->nnidx);
            } else {
                func_800E9F4C_name_81(0x24, &player->nnlink, &player->nnidx);
            }
            return;
        }
        D_80101A50_name_81 = -1;
    }
}

void func_80115550_duel05(void) {
    s8 linkIdx[2]; // link, index
    Vec pos[3]; // center, front, back
    GW_PLAYER *player;
    SpaceData *space;
    s8 playerNo;

    playerNo = GwSystem.current_player_index ^ 1;
    player = MBDGetPlayerStruct(playerNo);
    func_800E9F4C_name_81(0x26, &linkIdx[0], &linkIdx[1]);
    func_800ECD0C_name_81(playerNo, linkIdx[0], linkIdx[1]);
    player->rev = 0;
    player->nnlink = -1;
    player->nnidx = -1;
    space = MBDMasuGet(0x26);
    HuVecAdd(&pos[0], &space->coords, &MBDMasuGet(0x23)->coords);
    HuVecMulScalar(&pos[0], 0.5f, &pos[0]);
    HuVecCopy3F(&pos[1], &pos[0]);
    pos[1].z += 12.0f;
    HuVecCopy3F(&pos[2], &pos[0]);
    pos[2].z -= 12.0f;
    func_800E27D4_name_81(playerNo, &pos[0], &pos[1], &pos[2]);
}

void func_8011566C_duel05(void) {
}

// board dc3: the board's .data (0x436130-0x436E20; 426420.c holds the first 0x30 bytes)
void func_80106838_duel05();
void func_80107198_duel05();
void func_801079C8_duel05();
void func_80107ECC_duel05();
void func_801084B4_duel05();
void func_80108560_duel05();
void func_80109898_duel05();
void func_8010A220_duel05();
void func_8010B55C_duel05();
void func_8010BCE4_duel05();
void func_8010CE78_duel05();
void func_8010D434_duel05();
void func_80110B4C_duel05();
void func_80110BA8_duel05();
void func_80110C0C_duel05();
void func_80111DCC_duel05();
void func_801123B8_duel05();
void func_801124A8_duel05();
void func_801124E4_duel05();
void func_80112560_duel05();
void func_8011259C_duel05();
void func_8011261C_duel05();
void func_80112998_duel05();
void func_80112B84_duel05();
void func_80112D70_duel05();
void func_801135A8_duel05();
void func_801138A0_duel05();
s32 func_80113C7C_duel05(void);
s32 func_80114428_duel05(void);
void func_80114BD4_duel05();
void func_80114D24_duel05();
void func_80114E74_duel05();
void func_80114E98_duel05();
void func_80114EBC_duel05();
void func_80114F10_duel05();
void func_80114F68_duel05();
void func_80114FD8_duel05();
void func_8011505C_duel05();
void func_80115098_duel05();
void func_801150D4_duel05();
void func_80115120_duel05();
void func_8011514C_duel05();
void func_80115198_duel05();
void func_801151E4_duel05();
void func_80115230_duel05();
void func_8011525C_duel05();
void func_801152A8_duel05();
void func_801152F4_duel05();
void func_801153E8_duel05();
void func_8011541C_duel05();
void func_8011544C_duel05();
void func_80115468_duel05();
void func_8011566C_duel05();

/* the asm reads the low byte of [i - 1]: D_801156AF_duel05 = this - 1 */
s32 D_801156B0_duel05[2] = { 0x37, 0x39 };
s32 D_801156B8_duel05[5] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F }; /* count, then file ids */
f32 D_801156CC_duel05 = 3.0f;
s32 D_801156D0_duel05[4] = { 3, 0xA011D, 0xA011E, 0xA0121 }; /* count, then file ids */
s16 D_801156E0_duel05 = 0x22; /* first object: from space id */
s16 D_801156E2_duel05 = 0x21; /* to */
Process *D_801156E4_duel05 = NULL;
s16 D_801156E8_duel05 = 0x20; /* second object: from space id */
s16 D_801156EA_duel05 = 0x29; /* to */
Process *D_801156EC_duel05 = NULL;
s32 D_801156F0_duel05 = 0;
s32 D_801156F4_duel05[2] = { 0x31, 0x30 };
typedef struct Duel05Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel05Weight;
s8 D_801156FC_duel05[13 * 2] = { /* value, chance pairs (D_801156FD_duel05 = [1]) */
    7, 30, 6, 30, 4, 30, 1, 30, 11, 30, 8, 20, 3, 20,
    10, 20, 0, 20, 2, 20, 9, 20, 5, 20, -1, -1,
};
Duel05Weight D_80115718_duel05[14] = {
    { 0, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_80115734_duel05[14] = {
    { 1, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_80115750_duel05[14] = {
    { 2, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_8011576C_duel05[14] = {
    { 4, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_80115788_duel05[14] = {
    { 3, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_801157A4_duel05[14] = {
    { 5, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_801157C0_duel05[14] = {
    { 7, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight D_801157DC_duel05[14] = {
    { 6, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel05Weight *D_801157F8_duel05[8] = {
    D_80115718_duel05, D_80115734_duel05, D_80115750_duel05, D_8011576C_duel05,
    D_80115788_duel05, D_801157A4_duel05, D_801157C0_duel05, D_801157DC_duel05,
};
/* the asm reads the low halves: D_8011581A/1E/22_duel05 = (s16 *)&[0..2] + 1 */
s32 D_80115818_duel05[2][3] = { { 0x1E, 0x21, 0x22 }, { 0x1D, 0x29, 0x20 } };
s32 D_80115830_duel05 = -1;
Object *D_80115834_duel05 = NULL;
s32 D_80115838_duel05 = 0;
event_list_entry D_8011583C_duel05[2] = {
    { 1, 1, func_80110B4C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_8011584C_duel05[2] = {
    { 1, 1, func_80110BA8_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_8011585C_duel05[2] = {
    { 7, 1, func_80110C0C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_8011586C_duel05[3] = {
    { 1, 1, func_80111DCC_duel05 },
    { 8, 1, func_8011566C_duel05 },
    { 0, 0, NULL },
};
/* indexed from 1 by GwSystem.minigame_index: the asm addresses it as D_80115880_duel05 (= this - 4) */
void (*D_80115884_duel05[11])() = {
    func_801123B8_duel05, func_801124A8_duel05, func_801124E4_duel05, func_80112560_duel05,
    func_8011259C_duel05, func_8011261C_duel05, func_80112998_duel05, func_80112B84_duel05,
    func_80112D70_duel05, func_801135A8_duel05, func_801138A0_duel05,
};
event_table_entry D_801158B0_duel05[5] = {
    { 30, D_8011583C_duel05 },
    { 29, D_8011584C_duel05 },
    { -5, D_8011585C_duel05 },
    { 38, D_8011586C_duel05 },
    { -1, NULL },
};
/* the opponent's space index by roll for the COM junction decisions (read unsigned, so 0xFF never matches);
   the asm addresses them with the index offset folded in: D_801158D5/ED_duel05 = this - 3, D_80115904_duel05 = D_80115908_duel05 - 4 */
u8 D_801158D8_duel05[5] = { 0xFF, 1, 2, 3, 4 };
u8 D_801158E0_duel05[5] = { 0xFF, 0, 1, 2, 3 };
u8 D_801158E8_duel05[5] = { 0xFF, 0, 1, 2, 3 };
u8 D_801158F0_duel05[5] = { 0xFF, 1, 2, 3, 4 };
u8 D_801158F8_duel05[5] = { 0xFF, 0, 1, 2, 3 };
u8 D_80115900_duel05[5] = { 0xFF, 0, 1, 2, 3 };
u8 D_80115908_duel05[6] = { 0xFF, 0, 1, 3, 4, 5 };
DecisionTreeNonLeafNode D_80115910_duel05[2] = {
    { 0x5, { .func = func_80113C7C_duel05 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_80115928_duel05[5] = {
    { 0x2, { .data = 0x0000000F }, { .data = 0x0B56AD5A } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x178F1E3C } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80115964_duel05[6] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80115928_duel05 } },
    { 0x2, { .data = 0x0000000F }, { .data = 0x0B56AD5A } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_801159AC_duel05[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x178F1E3C } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_801159DC_duel05[5] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_801159AC_duel05 } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x08D1A346 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80115A18_duel05[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80115910_duel05 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80115964_duel05 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_801159DC_duel05 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80115A48_duel05[2] = {
    { 0x5, { .func = func_80114428_duel05 }, { .data = 0x0C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_80115A60_duel05[5] = {
    { 0x2, { .data = 0x0000000F }, { .data = 0x0B56AD5A } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x178F1E3C } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80115A9C_duel05[6] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80115A60_duel05 } },
    { 0x2, { .data = 0x0000000F }, { .data = 0x0B56AD5A } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_80115AE4_duel05[4] = {
    { 0x19, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x178F1E3C } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80115B14_duel05[5] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80115AE4_duel05 } },
    { 0x19, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00060006 }, { .data = 0x08D1A346 } },
    { 0xB, { .data = 0x00010003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80115B50_duel05[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80115A48_duel05 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80115A9C_duel05 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80115B14_duel05 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
s16 D_80115B80_duel05[3] = { 0x12, 0x0E, -1 };
event_list_entry D_80115B88_duel05[2] = {
    { 1, 1, func_80114BD4_duel05 },
    { 0, 0, NULL },
};
s16 D_80115B98_duel05[3] = { 0x1C, 0x18, -1 };
event_list_entry D_80115BA0_duel05[2] = {
    { 1, 1, func_80114D24_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115BB0_duel05[2] = {
    { 1, 1, func_80114E74_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115BC0_duel05[2] = {
    { 1, 1, func_80114E98_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115BD0_duel05[2] = {
    { 1, 1, func_80114EBC_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115BE0_duel05[2] = {
    { 1, 1, func_80114F10_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115BF0_duel05[2] = {
    { 1, 1, func_80114F68_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C00_duel05[2] = {
    { 1, 1, func_80114FD8_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C10_duel05[2] = {
    { 1, 1, func_8011505C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C20_duel05[2] = {
    { 1, 1, func_80115098_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C30_duel05[2] = {
    { 1, 1, func_801150D4_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C40_duel05[2] = {
    { 1, 1, func_80115120_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C50_duel05[2] = {
    { 1, 1, func_8011514C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C60_duel05[2] = {
    { 1, 1, func_80115198_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C70_duel05[2] = {
    { 1, 1, func_801151E4_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C80_duel05[2] = {
    { 1, 1, func_80115230_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115C90_duel05[2] = {
    { 1, 1, func_8011525C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CA0_duel05[2] = {
    { 1, 1, func_801152A8_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CB0_duel05[2] = {
    { 1, 1, func_801152F4_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CC0_duel05[2] = {
    { 1, 1, func_801153E8_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CD0_duel05[2] = {
    { 1, 1, func_8011541C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CE0_duel05[2] = {
    { 7, 1, func_8011544C_duel05 },
    { 0, 0, NULL },
};
event_list_entry D_80115CF0_duel05[2] = {
    { 1, 1, func_80115468_duel05 },
    { 0, 0, NULL },
};
event_table_entry D_80115D00_duel05[24] = {
    { 40, D_80115B88_duel05 },
    { 31, D_80115BA0_duel05 },
    { 17, D_80115BB0_duel05 },
    { 27, D_80115BC0_duel05 },
    { 21, D_80115BD0_duel05 },
    { 3, D_80115BE0_duel05 },
    { 39, D_80115BF0_duel05 },
    { 4, D_80115C00_duel05 },
    { 18, D_80115C10_duel05 },
    { 28, D_80115C20_duel05 },
    { 23, D_80115C30_duel05 },
    { 26, D_80115C40_duel05 },
    { 1, D_80115C50_duel05 },
    { 2, D_80115C60_duel05 },
    { 13, D_80115C70_duel05 },
    { 16, D_80115C80_duel05 },
    { 19, D_80115C90_duel05 },
    { 20, D_80115CA0_duel05 },
    { 5, D_80115CB0_duel05 },
    { 0, D_80115CC0_duel05 },
    { 9, D_80115CD0_duel05 },
    { -2, D_80115CE0_duel05 },
    { 8, D_80115CF0_duel05 },
    { -1, NULL },
};
char D_80115DC0_duel05[] = "obj1";
char D_80115DC8_duel05[] = "item_hook";
f64 D_80115DD8_duel05 = 1.0;
f64 D_80115DE0_duel05 = 1.0;
f64 D_80115DE8_duel05 = 1.0;
f64 D_80115DF0_duel05 = 1.0;
s32 D_80115DF8_duel05[3] = { -1, -1, -1 };
s32 D_80115E04_duel05[3] = { 0, 0, 0 };
void (*D_80115E10_duel05[12])() = {
    func_80106838_duel05, func_80107198_duel05, func_801079C8_duel05, func_80107ECC_duel05,
    func_80109898_duel05, func_801084B4_duel05, func_8010CE78_duel05, func_8010D434_duel05,
    func_8010BCE4_duel05, func_80108560_duel05, func_8010A220_duel05, func_8010B55C_duel05,
};
void (*D_80115E40_duel05[12])() = {
    NULL, NULL, NULL, NULL, func_80109898_duel05, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
