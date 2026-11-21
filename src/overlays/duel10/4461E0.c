#include "common.h"
#include "process.h"
#include "common_structs.h"
#include "malloc.h"
#include "game/board.h"
#include "game/object.h"
#include "mallocblock.h"
#include "game/window.h"
#include "game/sprite.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "input.h"
#include "variables.h"

// board ec1: declarations for func_801059D0_duel10..func_8010DDA4_duel10 (from duel05/426450.c, renamed)

// board dc1: declarations for func_801059D0_duel10..func_8010ADB4_duel10 (from duel01.h / 3D8AC0.c, renamed)
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
extern s32 D_80114CB0_duel10;
extern s32 D_80114CB4_duel10;
extern s32 D_80114CB8_duel10;
extern s32 D_80114CBC_duel10;
void func_800E94D0_name_81(void);
void func_800E9564_name_81(void);
void func_800E9B10_name_81(s32, s32);
void func_800E9D9C_name_81(void);
void func_800E9F4C_name_81(s32, s8*, s8*);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s32, s8, s8);
void func_800EB708_name_81(Vec*, Vec*, Vec*); // duel b1: was (s32, s32, unkStruct01*)
unkStruct03* func_80047EA0_main(void*, s32, s32, s32);
void func_80105D2C_duel10(void); //probably takes object as arg
void func_800FC8C4_name_81(Vec*);
extern Vec D_80105540_name_81; // duel b1: was s32
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32); // duel b1: was (void*, s32, void*, f32)
Process* func_800EBF2C_name_81(Vec* from, Vec* to, Vec* out, s32 frames); // duel b1/b7: ovl_81 DFD60.c
void func_80106374_duel10(void);
void func_8001C258_main(s16, s32, s32);
void func_8001C448_main(s16);
void func_8001C8E4_main(s16, u32);
Object* func_800D8010_name_81(u8, s32*); // b7: ovl_81 BFB40.c (was void*(s32, s32))
void func_800D8944_name_81(Object*);
void func_800D8F0C_name_81(Object*);
void func_80089A20_main(Vec*, s32);
void func_800D8E88_name_81(Object*); // duel b1: was (void)
s16 MBDGetCurrentPlayerIndex(void);
GW_PLAYER* MBDGetPlayerStruct(s32 playerIndex);
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
extern Object* D_80114CC0_duel10;
extern Object* D_80114CC4_duel10;
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
s32 func_800EFE20_name_81(f32 arg0);
void func_800FC888_name_81(s32 arg0);
Object* MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
void func_800D8F3C_name_81(Object *arg0);
void func_800FAD04_name_81(s32 arg0);
void func_800FAE18_name_81(Object *arg0, s16 arg1, s16 arg2);
void func_800FADB4_name_81(void);
void func_800ED214_name_81(s32 playerIndex);
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

/* board dc1: literals duel01 keeps in .rodata sit in duel05's asm .data */
extern s32 D_80105550_name_81;
extern s32 D_80105558_name_81;
extern s32 D_80105718_name_81;
extern s32 D_8010571C_name_81;
Process* func_800D9668_name_81(Object*, f32, f32, s32);
Process *func_800DCE40_name_81(s32 type, Vec *pos, Vec *vel, f32 scale);
s32 func_800DD1E0_name_81(s32 data, char *name);
void func_800DD2DC_name_81(s32 model, Vec *pos); // defined with s16 model
s32 func_800DD3B4_name_81(s32 model);
void func_800DD2BC_name_81(s32 model); // defined with s16 model
Process *func_800FAB68_name_81(Object *obj, s32 amount, s32 motion, s32 flags, s32 seNo);
void func_800FAC1C_name_81(Vec *arg0);
void func_8001C6A8_main(s32, f32);
void func_800EF7C8_name_81(Object *obj, f32 arg1, f32 arg2);
void func_800EF800_name_81(Object*);
void func_801061C8_duel10(Object *partner, Object *target, GW_PLAYER *player, Vec *arg3, Vec *arg4, f32 arg5);
void func_800F0378_name_81(Object*, char*, s16);
void func_800EB804_name_81(Object *obj);
void func_800FAE98_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_8001C92C_main(s16, f32);
void MBDBackTPLvlSet(u8 arg0);
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
void *func_8001D33C_main(s16 model, char *name);
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void func_800D918C_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
s32 func_800D9234_name_81(Object *);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB49C_name_81(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
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
extern Object *D_80114CC8_duel10;

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;



Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
Object *func_800D8B18_name_81(Object *obj);
s32 func_800EF7D4_name_81(Object *obj);
Process *func_800DCC8C_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
void func_8010AB1C_duel10(Object *obj, s32 create);
void func_8010ADB4_duel10(Object *obj);
Process *func_8010613C_duel10(GW_PLAYER *player, Object *target, s32 arg2, s32 arg3);

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

void func_80106894_duel10(s32, s32, Object *, Object *, s32, s32);
void func_801071F4_duel10(s32, s32, Object *, Object *, s32, s32);
void func_80107A24_duel10(s32, s32, Object *, Object *, s32, s32);
void func_80107F28_duel10(s32, s32, Object *, Object *, s32, s32);
void func_801098F4_duel10(s32, s32, Object *, Object *, s32, s32);
void func_80108510_duel10(s32, s32, Object *, Object *, s32, s32);
void func_801085BC_duel10(s32, s32, Object *, Object *, s32, s32);
void func_8010A27C_duel10(s32, s32, Object *, Object *, s32, s32);

extern s16 D_8010555C_name_81;
extern s32 D_80101A1C_name_81[];
void func_800ECF1C_name_81(s32, Vec*, Vec*);
void func_800F8358_name_81(s32);
Object* func_800F8050_name_81(s32);
/* defined under NON_MATCHING (asm otherwise); the .data tables name them */
s32 func_800F89D0_name_81(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, s16 arg3);
// board dc1: end
// board dc2: declarations for func_8010B020_duel10..func_80110038_duel10

/* ovl_81 (prototypes as duel01.h has them) */
void func_800EB7BC_name_81(Vec *out);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void func_800FC8DC_name_81(Object *arg0);

/* this unit, outside dc2's range */
void func_801062AC_duel10(void);
Process *func_801062CC_duel10(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3);
void *func_801067AC_duel10(s32 arg0);
void func_80106840_duel10(Object *arg0, Vec *arg1);

/* dc2's range */
void func_8010B020_duel10(void);
s16 func_8010B4EC_duel10(void);
void func_8010B52C_duel10(void);
void func_8010B594_duel10(void);
void func_8010B5A8_duel10(void);

/* data (still in the asm .data/.bss) */
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;
typedef DuelB4HmfPart Duel01Part;
typedef B1UnkBoard4 Duel01SprGrp; /* ovl_81's sprite group (UnkBoard4 there) */
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
extern omObjData *D_80114CCC_duel10;
Process *func_800DCE10_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay);
void func_800E0310_name_81(u8 *output, s32 count);
void func_800EB1D8_name_81(s32 arg0, s32 arg1);
void func_800ED118_name_81(s32 playerNo, Vec *front, Vec *back);
void func_800EE0D0_name_81(s32 arg0);
s32 func_800EED50_name_81(void);
void func_800F7BB4_name_81(s32 playerNo, s32 set);
void func_800F7D94_name_81(s32 playerNo, s32 set);
void func_800F821C_name_81(s32 playerIndex, s32 partnerNo);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800FB524_name_81(s32);
void func_800FBDD4_name_81(void);
Process *func_801064C8_duel10(s32 arg0, s32 arg1);
void func_80106534_duel10(s32 playerIndex, s32 mode);
void func_8010B19C_duel10(omObjData *obj);
void func_8010B5B8_duel10(s32, s32, Object *, Object *, s32, s32);
void func_8010CED4_duel10(s32, s32, Object *, Object *, s32, s32);
void func_8010D490_duel10(s32, s32, Object *, Object *, s32, s32);
void func_8010F114_duel10(void);
void func_8010F1A8_duel10(void);
void func_8010F7B4_duel10(void);
/* local-array initialisers: splat put them at the end of 426420's .data (0x80115DF8..0x80115E70),
   though by their order they are this unit's first .rodata; the C copies them from there */
typedef struct Dc2HitTimes {
    s32 v[3];
} Dc2HitTimes;
typedef struct Dc2SpinPrcs {
    Process *v[3];
} Dc2SpinPrcs;
typedef struct Dc2PartnerFuncs {
    DuelB2PartnerFunc f[12];
} Dc2PartnerFuncs;
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_800FC5B4_name_81(void (*arg0)(void));

// board dc3
void func_8008A120_main(f32 *mtx, f32 angle); // defined with Matrix4f (f32[4][4])
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
void func_800EAFC4_name_81(s32);
void func_800F57B0_name_81(s32 playerNo); // duel n7: was s16; the callee does not sign-extend
void func_800F5BB4_name_81(s32 playerIndex);
void func_800F5E2C_name_81(s32 playerNo); // duel n7: was u32
void func_800F5EB0_name_81(s32);
void func_800F8108_name_81(s32 playerIndex);
void func_800F82EC_name_81(s32);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
s32 func_800F37B8_name_81(s16 playerIndex);
void func_800ECD88_name_81(s16 playerNo, s16 link, s16 idx);
void func_800F8C68_name_81(s32);
extern s16 D_800CE1D0_main;
extern s16 D_800D124C_main;
extern s16 D_80101A50_name_81;
void func_80105A58_duel10(void);
void func_80105B10_duel10(void);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
UnkEA790Struct *func_800D76A0_name_81(s16 arg0, s16 *arg1);
s32 func_800D742C_name_81(UnkEA790Struct *arg0, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *arg0, s32 arg1);
s32 func_800D7518_name_81(UnkEA790Struct *arg0);
void func_800D6CA0_name_81(void *arg0);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *arg0);
void func_800ED788_name_81(s32 playerNo);
/* retail passes the back link/index addresses to the empty func_80115370_duel10, so no prototype here */
void func_800E27D4_name_81(s16 playerIndex, Vec *pos, Vec *frontPos, Vec *backPos);
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
// board ec1: end
// board ec1: the tutorial helpers func_8010DAE8_duel10..func_8010DDA4_duel10 (as w10's func_80105F64..func_8010B12C)
/* Three-sprite panel: frame, tinted backing, picture. */
typedef struct Ec1SprWork {
    /* 0x00 */ s16 group;
    /* 0x02 */ s16 spr[3];
} Ec1SprWork; // size 0x8
Process *func_800F41DC_name_81(void); /* DBE50.c */
Process *func_800F429C_name_81(void); /* DBE50.c */
// board ec1: end
// board ec2: declarations for func_8010E0EC_duel10..func_8010FE0C_duel10

/* Part of a model looked up by name (func_8001D33C_main). */
typedef DuelB4HmfPart Ec2HmfPart;

/* A player's model object, read for its current motion. */
typedef struct Ec2PlayerModel {
    /* 0x00 */ char unk_00[0x48];
    /* 0x48 */ s16 curMot;
} Ec2PlayerModel;

/* main */

/* ovl_81 */
void func_800DB4DC_name_81(s32);
void func_800DC07C_name_81(s32, s16);
s32 func_800DC0B4_name_81(s32);
Process *func_800DC324_name_81(s32);
void func_800DC3AC_name_81(s32 playerIndex);
void func_800DC410_name_81(s32 playerIndex);
void func_800E14B0_name_81(s32 player, s32 coins);
Process *func_800E39AC_name_81(s32);
void func_800E4EAC_name_81(UnkMBGuideData *guide, s16 x, s16 arg2);
void func_800EA388_name_81(s16);
void func_800EA698_name_81(s16);
void func_800EA788_name_81(s16, s32);
void func_800EB7D8_name_81(s16);
void func_800ECC34_name_81(s16, f32);
void func_800ECE38_name_81(s32);
void func_800EF754_name_81(s32 winId);
void func_800F3A04_name_81(s32, s16, s16, s16, u16);
void func_800F3AF4_name_81(s32, f32);
void func_800F924C_name_81(s32);
void func_800FC108_name_81(void);
void func_800FC4E4_name_81(void);
void func_800FCC84_name_81(s16);
void func_800FCCCC_name_81(s16);
void func_800FCF50_name_81(s32, s32);
s32 func_800FD498_name_81(void);
void func_800FFA28_name_81(Vec *);
void MBDCameraZoomSet(f32);
extern u8 D_80100E20_name_81;

/* this unit, outside ec2's range */
s16 func_8010DDA4_duel10(s32 padNo);
s32 func_80114940_duel10(void);

/* ec2's range */
void func_8010E4B4_duel10(s32 steps, s32 walkNum);
void func_8010ECA0_duel10(UnkMBGuideData *guide, s32 mess);
void func_8010EF98_duel10(void);
void func_8010F070_duel10(void);
void func_8010F258_duel10(void);
void func_8010F620_duel10(void);
void func_8010F864_duel10(void);
void func_8010FC2C_duel10(void);

/* data (still in the asm .data/.bss) */
extern u8 D_800CC0BA_main;
extern s8 D_801149D3_duel10; /* message speed saved at board start */
extern s16 D_80114A40_duel10; /* motion requested of the guide, -1 = none */
extern char D_80114BBC_duel10[]; /* "bell" */
extern UnkMBGuideData *D_80114CD0_duel10;
extern Object *D_80114CD4_duel10;
extern Process *D_80114CD8_duel10;
extern Object *D_80114CDC_duel10;
extern f32 D_80114CE0_duel10;
extern Object *D_80114CE4_duel10;
extern f32 D_80114CE8_duel10;
// board ec2: end
// board ec3: declarations for func_80111D0C_duel10..func_80114940_duel10 and the board's .data
void func_8010F3D4_duel10(Vec *pos);
void func_8010F474_duel10(void);
void func_8010F738_duel10(void);
void func_8010F764_duel10(void);
void func_8010F9E0_duel10(Vec *pos);
void func_8010FA80_duel10(void);
void func_8010FD44_duel10(void);
void func_8010FD70_duel10(void);
void func_80111E6C_duel10(void);
void func_80111FDC_duel10(void);
void func_800FC8E8_name_81(void);
void func_8010DA60_duel10(void);
void func_8010E0EC_duel10(void);
void func_8010FE0C_duel10(void);
void func_8011450C_duel10(void);
extern const DuelB7VecTbl D_80114C80_duel10; /* smoke puff offsets around a partner leaving */
extern B1UnkBoard4 *D_80114CEC_duel10;
extern const DuelPadMask D_80114C74_duel10;
extern const DuelChoiceTbl D_80114C78_duel10;
void func_801059D0_duel10(void);
s32 func_80111DC4_duel10(void);
s32 func_801127A8_duel10(s32 no);
/* part of a model looked up by name (func_8001D33C_main) */
typedef DuelB4HmfPart Ec3HmfPart;
// board ec4: declarations for func_8010FE0C_duel10
void func_800EBAD4_name_81(s32);
u16 MBDCameraPos3DSet(Vec *);
void func_800D9F90_name_81(s32);
void func_800DB624_name_81(s32, s8);
void func_800DF210_name_81(void);
void func_800E02B4_name_81(s32);
void func_800E0300_name_81(void);
Process *func_800E415C_name_81(void);
UnkMBGuideData *func_800E4B64_name_81(s32 *fileIds, s32);
void func_800E4E64_name_81(UnkMBGuideData *);
void func_800E5964_name_81(void);
void func_800EA1FC_name_81(s16 spaceIdx, u16 newSpaceType);
void func_800EAD08_name_81(s32);
Process *func_800EDEC4_name_81(Object *, f32, f32);
void func_800F0480_name_81(Object *, s16, s16, s32);
void func_800F05B4_name_81(Object *, s32);
void func_800FB59C_name_81(s32 playerIndex, s32 partnerNo, s32 targetNo, s32 starLoss, s32 damage, s32 selfStars, s32 selfDamage);
extern void (*D_8010198C_name_81)(void);
extern s16 D_80105712_name_81; /* message window id */
void func_80112E74_duel10(s32 no, s32 cpuTake);
void func_80113644_duel10(s32 no, s32 slot, s32 partnerID);
void func_801136B4_duel10(s32 no, s32 slot);
void func_80113840_duel10(s32 no, s32 slot, s32 partnerID);
void func_80113970_duel10(s32 no);
void func_80113AF4_duel10(void);
void func_801148D8_duel10(void);
void func_8010E268_duel10(void);
void func_8010E37C_duel10(s16 arg0);
void func_8010E408_duel10(s16 arg0);
void func_8010E8F4_duel10(void);
void func_8010EDF8_duel10(UnkMBGuideData *guide, s16 x);
// board ec4: end
// board ec3: the board's .data (0x4551E0-0x455380; 4461B0.c holds the first 0x20 bytes)
void func_8010BD40_duel10(s32, s32, Object *, Object *, s32, s32);
void func_80114140_duel10(void);

/* GwSystem byte 0x14 saved across the board; the asm reads back its low byte: D_801149D3_duel10 = this + 3 */
s32 D_801149D0_duel10 = 1;
s32 D_801149D4_duel10[2] = { 0xA007E, 0xA007F }; /* file ids */
s32 D_801149DC_duel10[4] = { 0xA0080, 0xA0081, 0xA0082, 0xA0083 };
s32 D_801149EC_duel10[2] = { 0xA0084, 0xA0085 };
/* the asm reads the low byte of [i - 1]: D_801149F3_duel10 = this - 1 */
s32 D_801149F4_duel10[2] = { 0x37, 0x39 };
s32 D_801149FC_duel10[5] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F }; /* count, then file ids */
s32 D_80114A10_duel10[8] = { 0x130014, 0x130002, 0x130003, 0x130004, 0x130005, 0x130006, 0x130007, 0x130008 };
s32 D_80114A30_duel10 = 1;
s32 D_80114A34_duel10[2] = { 1, 0xA0078 }; /* count, then file ids */
s32 D_80114A3C_duel10 = 0;
s16 D_80114A40_duel10 = -1;
f32 D_80114A44_duel10 = 3.0f;
s32 D_80114A48_duel10[4] = { 3, 0xA011D, 0xA011E, 0xA0121 }; /* count, then file ids */
s16 D_80114A58_duel10 = 0x11; /* first object: from space id */
s16 D_80114A5A_duel10 = 0xF; /* to */
Process *D_80114A5C_duel10 = NULL;
s16 D_80114A60_duel10 = 0x12; /* second object: from space id */
s16 D_80114A62_duel10 = 0x10; /* to */
Process *D_80114A64_duel10 = NULL;
s32 D_80114A68_duel10 = 0;
/* per player: three space ids; the asm reads the low halves: D_80114A6E/72/76_duel10 = (s16 *)&[0][0..2] + 1 */
s32 D_80114A6C_duel10[2][3] = { { 0xD, 0xF, 0x11 }, { 0xE, 0x10, 0x12 } };
s32 D_80114A84_duel10 = -1;
Object *D_80114A88_duel10 = NULL;
s32 D_80114A8C_duel10 = 0;
event_list_entry D_80114A90_duel10[2] = {
    { 1, 1, func_80114140_duel10 },
    { 0, 0, NULL },
};
event_table_entry D_80114AA0_duel10[2] = {
    { 0x13, D_80114A90_duel10 },
    { -1, NULL },
};
event_table_entry D_80114AB0_duel10[2] = {
    { -1, NULL },
    { 0, NULL },
};
char D_80114AC0_duel10[] = "obj1";
char D_80114AC8_duel10[] = "item_hook";
const f64 D_80114AD8_duel10 __attribute__((section(".data"))) = 1.0;
const f64 D_80114AE0_duel10 __attribute__((section(".data"))) = 1.0;
const f64 D_80114AE8_duel10 __attribute__((section(".data"))) = 1.0;
const f64 D_80114AF0_duel10 __attribute__((section(".data"))) = 1.0;
/* local-array initialisers the partner functions copy (as duel05's D_80115DF8..D_80115E40) */
Dc2HitTimes D_80114AF8_duel10 = { { -1, -1, -1 } };
Dc2SpinPrcs D_80114B04_duel10 = { { NULL, NULL, NULL } };
Dc2PartnerFuncs D_80114B10_duel10 = { { /* partner attacks by partner id */
    func_80106894_duel10, func_801071F4_duel10, func_80107A24_duel10, func_80107F28_duel10,
    func_801098F4_duel10, func_80108510_duel10, func_8010CED4_duel10, func_8010D490_duel10,
    func_8010BD40_duel10, func_801085BC_duel10, func_8010A27C_duel10, func_8010B5B8_duel10,
} };
Dc2PartnerFuncs D_80114B40_duel10 = { { /* second table: only [4] set */
    NULL, NULL, NULL, NULL, func_801098F4_duel10, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
} };

void func_801059D0_duel10(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel10(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80114CB0_duel10 = func_800E1824_name_81(0, 0xA0, 1);
    D_80114CB4_duel10 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80114CB8_duel10 = func_800E1824_name_81(1, 0xBC, 1);
    D_80114CBC_duel10 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel10(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80114CB0_duel10);
    func_800E1854_name_81(D_80114CB4_duel10);
    func_800E1854_name_81(D_80114CB8_duel10);
    func_800E1854_name_81(D_80114CBC_duel10);
}

void func_80105B64_duel10(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(10, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105BA0_duel10(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x247);
    func_800E9F4C_name_81(0xD, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(2, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    GwPlayer[0].stat = 1;
    GwPlayer[1].stat = 1;
    GwPlayer[2].stat = 1;
    GwPlayer[3].stat = 1;
    GwPlayer[0].chr = 0;
    GwPlayer[1].chr = 1;
    GwPlayer[0].pad = 0;
    GwPlayer[1].pad = 1;
    GwPlayer[2].pad = 2;
    GwPlayer[3].pad = 3;
    GwPlayer[0].coin = 10;
    GwPlayer[1].coin = 10;
    GwSystem.current_turn = 1;
    GwSystem.current_player_index = 0;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    func_800F8418_name_81(0, 0, 0);
    func_800F8418_name_81(1, 1, 1);
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105CD0_duel10(Vec *arg0, Vec *arg1, Vec *arg2) { // duel b1: Vec* (was s32, s32, unkStruct01*)
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(temp_f20);
    arg2->z = cosdf(temp_f20);
}

void func_80105D2C_duel10(void) {
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

void *func_80105F1C_duel10(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105D2C_duel10, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

void func_80105F8C_duel10(void) {
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
    func_80105F1C_duel10((unkStruct04 *)obj);
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

Process *func_8010613C_duel10(GW_PLAYER *player, Object *obj, s32 delay, s32 wait) {
    Process *process;
    B1ThwompPrc *work;

    process = omAddPrcObj(func_80105F8C_duel10, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(B1ThwompPrc));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->wait = wait;
    return process;
}

void func_801061C8_duel10(Object *obj, Object *target, GW_PLAYER *player, Vec *dest, Vec *start, f32 dist) {
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

void func_801062AC_duel10(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

Process *func_801062CC_duel10(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) { // duel b1: returns the camera move (was void)
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
    return process;
}

Process *func_8010632C_duel10(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 frames) {
    Process *process;

    if (arg2 & 9) {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, frames);
    } else {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, frames);
    }
    return process;
}

void func_80106374_duel10(void) {
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

Process *func_801064C8_duel10(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_80106374_duel10, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

void func_80106534_duel10(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *obj;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
    case 0:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            obj = func_800D8010_name_81(0x28, 0);
            D_80114CC0_duel10 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            obj = func_800D8010_name_81(0x28, 0);
            D_80114CC4_duel10 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        break;
    case 1:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            func_800D8F3C_name_81(D_80114CC0_duel10);
            func_800D8E88_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            func_800D8F3C_name_81(D_80114CC4_duel10);
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
            D_80114CC0_duel10 = obj;
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
            D_80114CC4_duel10 = obj;
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
                func_800D8F3C_name_81(D_80114CC0_duel10);
                func_800D8E88_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                func_800D8F3C_name_81(D_80114CC4_duel10);
                func_800D8E88_name_81(partner);
            }
            break;
        }
        break;
    }
}

void *func_801067AC_duel10(s32 arg0) {
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

void func_80106840_duel10(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0); // duel b1: was ()
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

void func_80106894_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
        standIn = func_801067AC_duel10(0x45);
    }
    effect = func_800D8010_name_81(D_801149F4_duel10[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_801062AC_duel10();
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
    func_801061C8_duel10(partner, target, player, &dest, &start, 6.0f);
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
    func_801062CC_duel10(target, player, flags, 3.0f);
    if (flags & 8) {
        func_8010613C_duel10(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        if (level == 1) {
            func_80106840_duel10(standIn, &partner->coords);
        }
        if (flags & 1) {
            HuVecAdd(&mid, &target->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105CD0_duel10(&target->coords, &standIn->coords, &standIn->rot);
                func_80106840_duel10(standIn, &target->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80114AC0_duel10);
                func_800DD2DC_name_81(model, &mid);
            }
        } else {
            HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105CD0_duel10(&player->player_obj->coords, &standIn->coords, &standIn->rot);
                func_80106840_duel10(standIn, &player->player_obj->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80114AC0_duel10);
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

void func_801071F4_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_801067AC_duel10(standInIds[level - 1]);
    effect = func_800D8010_name_81(D_801149F4_duel10[level - 1] & 0xFF, 0);
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
    func_801061C8_duel10(partner, target, player, &dest, &start, 7.0f);
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, flags, 3.0f);
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
        func_8010613C_duel10(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        func_80106840_duel10(standIn, &partner->coords);
        HuAudFXPlay(0x25B);
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += partner->velocity.x;
        func_80106840_duel10(standIn, midp);
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

// decomp-permuter
void func_80107A24_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level)
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
  standIn = func_801067AC_duel10(standInIds[level - 1]);
  effect = func_800D8010_name_81(D_801149F4_duel10[level - 1] & 0xFF, 0);
  func_8001C8E4_main(effect->omObj1->model[0], 0);
  func_8001C448_main(effect->omObj1->model[0]);
  func_800D8944_name_81(effect);
  func_800D8F0C_name_81(effect);
  hook = func_800D8010_name_81(0x3F, 0);
  func_800D8F0C_name_81(hook);
  func_800F0378_name_81(partner, D_80114AC8_duel10, hook->omObj1->model[0]);
  func_800D90D0_name_81(partner, 0, 2);
  func_801061C8_duel10(partner, target, player, &dest, &start, 6.0f);
  func_801062AC_duel10();
  func_801062CC_duel10(target, player, flags, 3.0f);
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
    func_8010613C_duel10(player, target, 0, 20);
  }
  else
  {
    HuPrcSleep(9);
 do { HuAudFXPlay(0x1D7); if (level == 2) { HuAudFXPlay(0x1F2); } midp = &mid; if (flags & 1) { HuVecAdd(midp, &target->coords, &partner->coords); } else { HuVecAdd(midp, &player->player_obj->coords, &partner->coords); } HuVecMulScalar(midp, 0.5f, midp); func_800EB804_name_81(standIn); func_80106840_duel10(standIn, midp); } while (0);
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

void func_80107F28_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_801067AC_duel10(standInIds[level - 1]);
    HuVecCopyXYZ(&standIn->scale, 2.0f, 2.0f, 2.0f);
    if (level == 2) {
        HuPrcVSleep();
        blast = func_801067AC_duel10(0x5B);
        HuPrcVSleep();
    }
    effect = func_800D8010_name_81(D_801149F4_duel10[level - 1] & 0xFF, 0);
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
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, flags, 2.0f);
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
        func_80106840_duel10(blast, &partner->coords);
        func_8001C92C_main(blast->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        func_80106840_duel10(standIn, &mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (level == 1) {
        func_80106840_duel10(standIn, &mid);
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

void func_80108510_duel10(s32 playerIndex, s32 arg1, Object *partner, Object *target, s32 arg4, s32 count) {
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
void func_801085BC_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    standIn = func_801067AC_duel10(0x55);
    func_801061C8_duel10(partner, target, player, &dest, &start, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, flags, 3.0f);
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
                func_8010613C_duel10(player, target, 0, 55);
            } else {
                func_8010613C_duel10(player, target, 0, 120);
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
            func_80106534_duel10(targetIndex, 2);
            if (level == 1) {
                func_800EB804_name_81(standIn);
                func_80106840_duel10(standIn, &target->coords);
                func_800DCE40_name_81(0x47, &target->coords, NULL, 1.0f);
            } else {
                dust = func_800D8010_name_81(0x5A, 0);
                func_800D974C_name_81(dust);
                HuVecCopy3F(&dust->coords, &partner->coords);
                model = func_800DD1E0_name_81(0xB0023, D_80114AC0_duel10);
                func_800DD2DC_name_81(model, &partner->coords);
            }
        }
        if (level == 1) {
            func_801064C8_duel10(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, func_801064C8_duel10(5, 2));
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
                    func_80106840_duel10(standIn, &partner->coords);
                    func_800DCE40_name_81(0x47, &partner->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    dust = func_800D8010_name_81(0x5A, 0);
                    func_800D974C_name_81(dust);
                    HuVecCopy3F(&dust->coords, &partner->coords);
                }
                HuPrcChildLink(process, func_801064C8_duel10(5, 2));
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
        func_80106534_duel10(targetIndex, 3);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801085BC_duel10);
#endif

void func_80109470_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
    func_801061C8_duel10(partner, target, player, &dest, &start, 0.0f);
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, flags, 3.0f);
    dest.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    frames = HuVecGetLength3F(&diff) / 3.0f;
    partner->flags |= 1;
    if (flags & 8) {
        func_8010613C_duel10(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
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

void func_801098F4_duel10(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
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
        func_80109470_duel10(playerIndex, targetIndex, partner, target, flags, 1);
        return;
    }
    level &= ~0x10;
    func_800D90D0_name_81(partner, 0, 2);
    func_801061C8_duel10(partner, target, player, &near, &start, 6.0f);
    func_801061C8_duel10(partner, target, player, &dest, &start, 8.0f);
    func_801062AC_duel10();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    HuPrcChildLink(process, func_801062CC_duel10(target, player, flags, 3.0f));
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
            func_8010613C_duel10(player, target, 0, 20);
        } else {
            func_8010613C_duel10(player, target, 0, 40);
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

void func_8010A27C_duel10(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra2 = func_801067AC_duel10(0x51);
        HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    extra1 = func_801067AC_duel10(0x4C);
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
    func_801062AC_duel10();
    func_8010632C_duel10(target, player, flags, 0x1E);
    if (flags & 8) {
        HuVecCopy3F(&sp78, &target->coords);
        sp78.y += 5.0f;
        func_8010613C_duel10(player, target, 0x19, 0x28);
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
        func_80106840_duel10(extra1, &sp78);
        if (variant == 2) {
            func_80106840_duel10(extra2, &sp78);
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
        func_80106840_duel10(extra1, &sp78);
        if (variant == 2) {
            func_80106840_duel10(extra2, &sp78);
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

void func_8010AB1C_duel10(Object *obj, s32 create) {
    Object *puff;
    f32 rot;
    f32 scale;

    if (create != 0) {
        D_80114CC8_duel10 = func_800D8010_name_81(8, D_801149FC_duel10);
        func_800D8944_name_81(D_80114CC8_duel10);
        func_800D8F0C_name_81(D_80114CC8_duel10);
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
    for (scale = 1.0f; scale < 10.0f; scale += D_80114AD8_duel10) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    if (create != 0) {
        HuVecCopy3F(&D_80114CC8_duel10->coords, &obj->coords);
        HuVecCopy3F(&D_80114CC8_duel10->rot, &obj->rot);
        func_800D8E88_name_81(D_80114CC8_duel10);
        func_800D8F0C_name_81(obj);
    }
    for (; scale >= 1.0f; scale -= D_80114AE0_duel10) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

void func_8010ADB4_duel10(Object *obj) {
    Object *puff;
    f32 rot;
    f32 scale;

    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &D_80114CC8_duel10->coords);
    puff->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += D_80114AE8_duel10) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &D_80114CC8_duel10->coords);
    HuVecCopy3F(&obj->rot, &D_80114CC8_duel10->rot);
    func_800D8F3C_name_81(D_80114CC8_duel10);
    func_800D8E88_name_81(obj);
    obj->flags &= ~1;
    for (; scale >= 1.0f; scale -= D_80114AF0_duel10) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

void func_8010B020_duel10(void) {
    DuelB2Puffs *puffs;
    void *data;
    s32 i;

    func_800142A0_main(0x1A);
    D_80114CCC_duel10 = omAddObj(0x1F4, 0, 0, -1, func_8010B19C_duel10);
    puffs = D_80114CCC_duel10->data = HuMemAllocTag(sizeof(DuelB2Puffs), 0x7918);
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
    D_80114CCC_duel10->work[0] = 0;
    puffs->delay = 0;
}

void func_8010B19C_duel10(omObjData *obj) {
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
                puffs->vel[i].x = D_80114CC8_duel10->rot.x;
                puffs->vel[i].y = -0.8f;
                puffs->vel[i].z = D_80114CC8_duel10->rot.z;
                func_800D7828_name_81(&puffs->vel[i]);
                puffs->vel[i].x = 2.0f * puffs->vel[i].x;
                puffs->vel[i].y = 2.0f * puffs->vel[i].y;
                puffs->vel[i].z = 2.0f * puffs->vel[i].z;
                puffs->pos[i].x = D_80114CC8_duel10->rot.x * 10.0f + D_80114CC8_duel10->coords.x;
                puffs->pos[i].z = D_80114CC8_duel10->rot.z * 10.0f + D_80114CC8_duel10->coords.z;
                puffs->pos[i].y = D_80114CC8_duel10->coords.y + 6.0f;
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

s16 func_8010B4EC_duel10(void) {
    DuelB2Puffs *puffs = D_80114CCC_duel10->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B52C_duel10(void) {
    DuelB2Puffs *puffs = D_80114CCC_duel10->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        func_80016638_main(puffs->spr[i]);
    }
    omDelObj(D_80114CCC_duel10);
    func_800166D0_main();
}

void func_8010B594_duel10(void) {
    D_80114CCC_duel10->work[0] = 1;
}

void func_8010B5A8_duel10(void) {
    D_80114CCC_duel10->work[0] = 0;
}

void func_8010B5B8_duel10(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
    f32 scale;
    Vec *mid;
    s32 effect;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    func_800FAD04_name_81(0xB);
    if (flags != 0) {
        obj = func_800D8010_name_81(D_801149F4_duel10[variant - 1], 0);
        func_8001C8E4_main(obj->omObj1->model[0], 0);
        func_8001C448_main(obj->omObj1->model[0]);
        func_800D8944_name_81(obj);
        func_800D8F0C_name_81(obj);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AB1C_duel10(partner, 1);
        HuAudFXPlay(0x29C);
        func_800D90D0_name_81(D_80114CC8_duel10, 0, 2);
        HuVecCopy3F(&sp28, &D_80114CC8_duel10->coords);
        HuVecCopy3F(&sp48, &D_80114CC8_duel10->rot);
        if (target != NULL) {
            HuVecCopy3F(&sp18, &target->coords);
        } else {
            HuVecCopy3F(&sp18, &player->player_obj->coords);
        }
        func_800EB708_name_81(&D_80114CC8_duel10->coords, &sp18, &D_80114CC8_duel10->rot);
        angle = func_800D76D0_name_81(&D_80114CC8_duel10->rot) + 180.0f;
        if (variant == 1) {
            offset.x = sindf(angle) * (scale = 6.0f) * (speed = 2.5f);
        } else {
            offset.x = sindf(angle) * (scale = 6.0f) * (speed = 3.0f);
        }
        offset.y = 0.0f;
        offset.z = cosdf(angle) * scale * speed;
        HuVecAdd(&sp18, &sp18, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&D_80114CC8_duel10->coords, &sp18, &D_80114CC8_duel10->coords, 0.5f));
        func_801062AC_duel10();
        func_801062CC_duel10(target, player, flags, 0.8f);
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &D_80114CC8_duel10->coords);
        func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 0.5f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 1) {
            func_800D90D0_name_81(D_80114CC8_duel10, 3, 0);
            if (flags & 8) {
                func_8010613C_duel10(player, target, 0, 0x32);
            } else {
                HuPrcSleep(8);
                mid = &sp58;
                if (flags & 1) {
                    HuVecAdd(mid, &target->coords, &D_80114CC8_duel10->coords);
                } else {
                    HuVecAdd(mid, &player->player_obj->coords, &D_80114CC8_duel10->coords);
                }
                HuVecMulScalar(mid, 0.5f, mid);
                sp58.y += 5.0f;
                effect = func_800DD1E0_name_81(0xB0025, D_80114AC0_duel10);
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
            func_800EFABC_name_81(D_80114CC8_duel10);
            func_800D90D0_name_81(D_80114CC8_duel10, -1, 2);
            HuPrcSleep(0x14);
        } else {
            func_800D90D0_name_81(D_80114CC8_duel10, 1, 0);
            HuPrcSleep(0x1E);
            func_8010B020_duel10();
            func_8010B594_duel10();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                func_8010613C_duel10(player, target, 0, 0x32);
            }
            func_800EFABC_name_81(D_80114CC8_duel10);
            func_800D90D0_name_81(D_80114CC8_duel10, 2, 2);
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
            func_8010B5A8_duel10();
            while (func_8010B4EC_duel10() != 0) {
                HuPrcVSleep();
            }
            func_800D918C_name_81(D_80114CC8_duel10, -1, 0, 5, 2);
            HuPrcSleep(0xA);
            func_8010B52C_duel10();
        }
        func_8010ADB4_duel10(partner);
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
        func_8010AB1C_duel10(partner, 0);
        HuAudFXPlay(0x2A0);
        func_80105F1C_duel10((unkStruct04 *)partner);
        HuPrcSleep(0xA);
        func_800FAE18_name_81(partner, 1, 0);
        func_800EFABC_name_81(partner);
        func_800D90D0_name_81(partner, -1, 2);
    }
    func_800FADB4_name_81();
}

void func_8010BD40_duel10(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    Process *process = HuPrcCurrentGet();
    Object *front = NULL;
    Object *back = NULL;
    s32 frontNo = -1;
    s32 backNo = -1;
    Dc2HitTimes hitTime = D_80114AF8_duel10;
    Dc2SpinPrcs spinPrc = D_80114B04_duel10;
    Vec pos;
    Object *obj;
    HmfModel *mdl;
    s32 i;
    f32 scale;
    f32 amp;

    func_800FAD04_name_81(8);
    obj = func_800D8010_name_81(D_801149F4_duel10[variant - 1] & 0xFF, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    HuVecCopy3F(&start, &partner->coords);
    HuVecCopy3F(&dest, &player->player_obj->coords);
    func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
    HuVecSubtract(&diff, &partner->coords, &player->player_obj->coords);
    hitTime.v[0] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
    if (hitTime.v[0] < 0) {
        hitTime.v[0] = 0;
    }
    if (player->stats.partners.frontID != -1) {
        front = MBDGetPlayerPartnerRef(playerNo, 0);
        frontNo = GwPlayer[playerNo].stats.partners.frontID;
        HuVecSubtract(&diff, &partner->coords, &front->coords);
        hitTime.v[1] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime.v[1] < 0) {
            hitTime.v[1] = 0;
        }
    }
    if (player->stats.partners.backID != -1) {
        back = MBDGetPlayerPartnerRef(playerNo, 1);
        backNo = GwPlayer[playerNo].stats.partners.backID;
        HuVecSubtract(&diff, &partner->coords, &back->coords);
        hitTime.v[2] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime.v[2] < 0) {
            hitTime.v[2] = 0;
        }
    }
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, 0, 7.0f);
    if (variant == 1) {
        func_800FAE18_name_81(partner, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 7.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &dest, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 7.0f));
        for (i = 0; ; i++) {
            if (i == hitTime.v[0]) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1E5);
                spinPrc.v[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
                func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
                hitTime.v[0] = -1;
                HuVecCopy3F(&pos, &player->player_obj->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime.v[1]) {
                HuAudFXPlay((D_80105718_name_81 & 2) ? 0x1CE : 0x1E5);
                spinPrc.v[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
                func_800EF7C8_name_81(front, 7.0f, -0.4f);
                hitTime.v[1] = -1;
                HuVecCopy3F(&pos, &front->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime.v[2]) {
                HuAudFXPlay((D_80105718_name_81 & 4) ? 0x1CE : 0x1E5);
                spinPrc.v[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
                func_800EF7C8_name_81(back, 7.0f, -0.4f);
                hitTime.v[2] = -1;
                HuVecCopy3F(&pos, &back->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (HuPrcChildGet(process) == 0) {
                break;
            }
            HuPrcVSleep();
        }
        if (hitTime.v[0] != -1) {
            spinPrc.v[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
            func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &player->player_obj->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime.v[1] != -1) {
            spinPrc.v[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
            func_800EF7C8_name_81(front, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &front->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime.v[2] != -1) {
            spinPrc.v[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
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
            if (spinPrc.v[0] != NULL && func_800EF7D4_name_81(player->player_obj) == 0) {
                B1_MODEL_ROTY(player->player_obj, 0.0f, mdl);
                omDelPrcObj(spinPrc.v[0]);
                spinPrc.v[0] = NULL;
            }
            if (spinPrc.v[1] != NULL && func_800EF7D4_name_81(front) == 0) {
                B1_MODEL_ROTY(front, 0.0f, mdl);
                omDelPrcObj(spinPrc.v[1]);
                spinPrc.v[1] = NULL;
            }
            if (spinPrc.v[2] != NULL && func_800EF7D4_name_81(back) == 0) {
                B1_MODEL_ROTY(back, 0.0f, mdl);
                omDelPrcObj(spinPrc.v[2]);
                spinPrc.v[2] = NULL;
            }
            if (spinPrc.v[0] == NULL && spinPrc.v[1] == NULL && spinPrc.v[2] == NULL) {
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
        func_80106534_duel10(playerNo, 0);
        func_800EF800_name_81(partner);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, func_801064C8_duel10(10, 1));
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
        func_80106534_duel10(playerNo, 1);
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
void func_8010CED4_duel10(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra1 = func_801067AC_duel10(0x4C);
        HuPrcVSleep();
        extra2 = func_801067AC_duel10(0x53);
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
    func_801062AC_duel10();
    func_800D8E88_name_81(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, func_801062CC_duel10(target, player, flags, 4.0f));
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
        func_8010613C_duel10(player, target, 0, 0x14);
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
            func_80106840_duel10(extra1, &sp28);
            HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
            func_80106840_duel10(extra2, &sp28);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010CED4_duel10);
#endif

#ifdef NON_MATCHING
// duel b2: masked 0, raw 28: partner and obj swap s3/s4.
void func_8010D490_duel10(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra = func_801067AC_duel10(0x45);
    }
    obj = func_800D8010_name_81(D_801149F4_duel10[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_801061C8_duel10(partner, target, player, &sp18, &sp28, 7.5f);
    func_801062AC_duel10();
    func_801062CC_duel10(target, player, flags, 3.0f);
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
        func_8010613C_duel10(player, target, 0, 0x1E);
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
            func_80106840_duel10(extra, &sp38);
        } else {
            effect = func_800DD1E0_name_81(0xB0024, D_80114AC0_duel10);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010D490_duel10);
#endif

void func_8010D9C8_duel10(void) {
    Dc2PartnerFuncs funcs1 = D_80114B10_duel10;
    Dc2PartnerFuncs funcs2 = D_80114B40_duel10;

    func_800FAC94_name_81(funcs1.f, funcs2.f);
}

void func_8010DA60_duel10(void) {
    omInitObjMan(0xA0, 0x50);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_800FC260_name_81(0x1E, 0x247, 0);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    func_8010F114_duel10();
    func_8010F1A8_duel10();
    func_8010F7B4_duel10();
    func_8010D9C8_duel10();
}


void func_8010DAE8_duel10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F41DC_name_81());
    HuPrcChildWait();
}

void func_8010DB24_duel10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F429C_name_81());
    HuPrcChildWait();
}

Ec1SprWork *func_8010DB60_duel10(s16 arg0, s16 x, s16 y) {
    Ec1SprWork *work;
    void *data;

    work = HuMemMemoryAllocPerm(sizeof(Ec1SprWork));
    work->group = HuSprGrpCreate(3, 0);
    data = DataRead(0x130000);
    work->spr[0] = func_80055810_main(data);
    func_80055024_main(work->group, 0, work->spr[0], 0);
    HuSprPriSet(work->group, 0, 11);
    HuSprAttrSet(work->group, 0, 0x1000);
    func_80054904_main(work->group, 0, x + 5, y);
    DataClose(data);
    data = DataRead(0x130001);
    work->spr[1] = func_80055810_main(data);
    func_80055024_main(work->group, 1, work->spr[1], 0);
    HuSprPriSet(work->group, 1, 12);
    HuSprAttrSet(work->group, 1, 0x1000);
    func_80054904_main(work->group, 1, x + 5, y);
    func_80055420_main(work->group, 1, 0x1F, 0xB0, 0x3F);
    DataClose(data);
    data = DataRead(D_80114A10_duel10[arg0]);
    work->spr[2] = func_80055810_main(data);
    func_80055024_main(work->group, 2, work->spr[2], 0);
    HuSprPriSet(work->group, 2, 10);
    HuSprAttrSet(work->group, 2, 0x1000);
    func_80054904_main(work->group, 2, x, y);
    DataClose(data);
    return work;
}

void func_8010DD5C_duel10(Ec1SprWork *work) {
    HuSprKill(work->spr[0]);
    HuSprKill(work->spr[1]);
    HuSprKill(work->spr[2]);
    HuSprGrpKill(work->group);
    HuMemMemoryFreePerm(work);
}

// Tutorial pause menu: dims the screen, asks whether to quit; true when the player chose to quit.
s16 func_8010DDA4_duel10(s32 padNo) {
    s16 size[2];
    B1UnkBoard4 *dim;
    B1UnkBoard4 *frame;
    void *data;
    s16 winId;
    s16 choice;

    func_8004A9DC_main(0x60);
    dim = func_800F4528_name_81(1, 0);
    data = DataRead(0x13025D);
    dim->unk_0C[0] = func_80055810_main(data);
    func_80055024_main(dim->unk_0A, 0, dim->unk_0C[0], 0);
    HuSprPriSet(dim->unk_0A, 0, 9);
    HuSprAttrSet(dim->unk_0A, 0, 0x1000);
    func_80054904_main(dim->unk_0A, 0, 160, 120);
    HuSprScaleSet(dim->unk_0A, 0, 40.0f, 30.0f);
    func_80055484_main(dim->unk_0A, 0, 0, 0, 0, 0xC0);
    DataClose(data);
    frame = func_800F4528_name_81(1, 0);
    data = DataRead(0x130009);
    frame->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(frame->unk_0A, 0, frame->unk_0C[0], 0);
    HuSprPriSet(frame->unk_0A, 0, 8);
    HuSprAttrSet(frame->unk_0A, 0, 0x1000);
    func_80054904_main(frame->unk_0A, 0, 160, 120);
    func_80055420_main(frame->unk_0A, 0, 0x89, 0xCA, 0xB2);
    func_80060394_main(1, size, 0x253A);
    winId = func_8005A968_main(160 - size[0] / 2, 120 - size[1] / 2, size[0], size[1], 0, 2);
    func_8005BE30_main(winId, 5);
    func_8005BEE0_main(winId, 0);
    func_80060144_main(winId);
    func_8005C060_main(winId, 7, 0, 0, 0xE0);
    func_8005C060_main(winId, 0, 0x89, 0xCA, 0xB2);
    func_8005C060_main(winId, 4, 0, 0x80, 0);
    func_8005FBF8_main(winId, 0x89, 0xCA, 0xB2);
    func_8005B43C_main(winId, 0x253A, -1, -1);
    func_8005BDFC_main(winId, 0);
    while (func_8005E0C0_main(winId) != 0) {
        HuPrcVSleep();
    }
    func_8005FE54_main(winId, 1 << padNo);
    choice = func_8005E1D8_main(winId, 0, 0);
    func_8005F364_main(winId);
    func_8004A9DC_main(0x7F);
    func_800F4584_name_81(dim);
    func_800F4584_name_81(frame);
    return choice == 1;
}


// board ec2: pause watcher: Start opens the pause menu; quitting leaves Duel Mode.
void func_8010E0EC_duel10(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;

    while (1) {
        HuPrcVSleep();
        if (WipeStatGet() != 0) {
            continue;
        }
        if (D_800CC0BA_main == 3) {
            continue;
        }
        curPlayerNo = MBDGetCurrentPlayerIndex();
        for (i = 0; i < 4; i++) {
            if (!(D_800C9520_main[i] & START_BUTTON)) {
                continue;
            }
            if (D_80114A30_duel10 == 0) {
                continue;
            }
            func_800DC3AC_name_81(curPlayerNo);
            MBDCameraPos2DGet(&sp10);
            MBDCameraPos2DSet(&sp10);
            D_800CB99C_main = 1;
            func_80049FB8_main();
            HmfPauseF = 1;
            if (func_8010DDA4_duel10(i) != 0) {
                GwSystem.message_speed = D_801149D3_duel10;
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(0, 0x10);
                HuPrcSleep(0x11);
                func_800FC4E4_name_81();
                func_800FC108_name_81();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            HmfPauseF = 0;
            func_8004A0E0_main();
            D_800CB99C_main = 0;
            func_800DC410_name_81(curPlayerNo);
            break;
        }
    }
}

void func_8010E258_duel10(void) {
}

void func_8010E260_duel10(void) {
}

#ifdef NON_MATCHING
// board ec2: the turn passes to the other player; both stand idle facing the camera.
// board ec2: masked 13: retail never keeps &GwSystem.current_player_index in a register (it reads it as if a scalar global); this C shares the address
void func_8010E268_duel10(void) {
    GW_PLAYER *player;
    s32 i;
    s8 cur;

    cur = GwSystem.current_player_index + 1;
    GwSystem.current_player_index = cur;
    if (cur >= 2) {
        GwSystem.current_player_index = 0;
    }
    for (i = 0; i < 2; i++) {
        player = MBDGetPlayerStruct(i);
        func_800EB7D8_name_81(i);
        func_800D90D0_name_81(player->player_obj, -1, 2);
        func_800FCF50_name_81(i, 1);
    }
    HuPrcVSleep();
    MBDCameraZoomSet(1.4f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E268_duel10);
#endif

void func_8010E31C_duel10(Vec *arg0) {
    func_800FFA28_name_81(arg0);
}

void func_8010E338_duel10(void) {
    Process *proc = HuPrcCurrentGet();

    HuPrcChildLink(proc, func_800E39AC_name_81(GwSystem.current_player_index));
    HuPrcChildWait();
}

// decomp-permuter
void func_8010E37C_duel10(s16 arg0)
{
  Process *diceProc;
  Process *proc;
  func_800DC07C_name_81((&GwSystem)->current_player_index, arg0);
  proc = HuPrcCurrentGet();
 do { } while (0);
  HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
  diceProc = func_800DC324_name_81(GwSystem.current_player_index);
  HuPrcChildWait();
  HuPrcChildLink(proc, diceProc);
  HuPrcChildWait();
}

// decomp-permuter
void func_8010E408_duel10(s16 arg0)
{
  Process *diceProc;
  Process *proc;
  func_800DC07C_name_81(GwSystem.current_player_index, arg0);
  D_80100E20_name_81 = 1;
  proc = HuPrcCurrentGet();
  HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
 do { } while (0);
  diceProc = func_800DC324_name_81(GwSystem.current_player_index);
  HuPrcChildWait();
  HuPrcChildLink(proc, diceProc);
}

void func_8010E494_duel10(void) {
    D_80100E20_name_81 = 0;
    HuPrcChildWait();
}

#ifdef NON_MATCHING
// board ec2: walk the current player: `steps` spaces at most (-1: no limit), `walkNum` counted spaces
// (0: the dice roll); func_80114940_duel10 may stop the walk for an event.
// board ec2: masked 30: the saved clink/cidx are sign-extended in retail, and the in-loop motion calls are not cross-jumped; logic checked against the asm block by block
void func_8010E4B4_duel10(s32 steps, s32 walkNum) {
    Vec sp18;
    Process *proc;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    SpaceData *space;
    s32 ret;
    s32 speed;
    s16 masuId;
    s16 num;
    s8 clink;
    s8 cidx;

    player = MBDGetPlayerStruct(-1);
    speed = 1;
    proc = HuPrcCurrentGet();
    if (walkNum != 0) {
        num = walkNum;
    } else {
        num = func_800DC0B4_name_81(system->current_player_index);
    }
    func_800ECE38_name_81(system->current_player_index);
    if (!(player->rev & 2)) {
        func_800F3A04_name_81(-1, 0, 0, 5, 2);
    } else {
        func_800F3A04_name_81(-1, 0, 0, 5, 6);
    }
    while (num != 0 && steps != 0) {
        if (func_80114940_duel10() != 0) {
            ret = func_80114940_duel10();
            if (ret != -1) {
                func_800F38DC_name_81(-1, -1, 2);
                func_800DB3E0_name_81(player->turn);
                func_800F924C_name_81(ret);
                func_800DADA0_name_81(player->turn);
                HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
                HuPrcChildWait();
                if (!(player->rev & 2)) {
                func_800F3A04_name_81(-1, 0, 0, 5, 2);
            } else {
                func_800F3A04_name_81(-1, 0, 0, 5, 6);
            }
            }
        }
        clink = player->clink;
        cidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;
        func_800FCF50_name_81((s8)(system->current_player_index ^ 1), (speed * 7) + 8);
        player->clink = clink;
        player->cidx = cidx;
        space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));
        if (((Ec2PlayerModel *)player->player_obj)->curMot != 0) {
            if (!(player->rev & 2)) {
                func_800F3A04_name_81(-1, 0, 0, 5, 2);
            } else {
                func_800F3A04_name_81(-1, 0, 0, 5, 6);
            }
        }
        switch (speed) {
            case 0:
                func_800F3AF4_name_81(-1, 1.5f);
                func_800ECC34_name_81(system->current_player_index, 5.0f);
                break;
            case 1:
                func_800F3AF4_name_81(-1, 1.0f);
                func_800ECC34_name_81(system->current_player_index, 4.0f);
                break;
            case 2:
                func_800F3AF4_name_81(-1, 0.75f);
                func_800ECC34_name_81(system->current_player_index, 3.0f);
                break;
        }
        func_800F3AF4_name_81(-1, 1.0f);
        player->blink = player->clink;
        player->bidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;
        if (!(player->rev & 1)) {
            player->nidx = player->nidx + 1;
        } else {
            player->nidx = player->nidx - 1;
        }
        masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBDMasuGet(masuId);
        func_800EA698_name_81(masuId);
        switch (space->space_type) {
            case 2:
            case 3:
            case 5:
            case 6:
            case 8:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                func_800DB4DC_name_81(system->current_player_index);
                num--;
                steps--;
                func_800EA388_name_81(masuId);
                break;
        }
        if (walkNum == 0) {
            if (num != 0) {
                func_800FCC84_name_81(space->space_type);
            } else {
                func_800FCCCC_name_81(space->space_type);
            }
        }
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&sp18);
    func_800EBC60_name_81(&player->player_obj->rot, &sp18, &player->player_obj->rot, 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E4B4_duel10);
#endif

void func_8010E8D4_duel10(void) {
    func_8010E4B4_duel10(-1, 0);
}

#ifdef NON_MATCHING
// board ec2: the space the current player landed on: an event space, or a character space (11..18)
// that pays the owner, or with a coin partner prize takes coins from the rival.
// board ec2: masked 35: masuId kept unextended and the direct GwSystem.current_player_index reads not shared with `system` in retail; logic checked against the asm block by block
void func_8010E8F4_duel10(void) {
    Vec sp10;
    Vec sp20;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    Process *proc;
    SpaceData *space;
    Object *partner;
    s32 masuId;
    s32 amount;

    player = MBDGetPlayerStruct(-1);
    proc = HuPrcCurrentGet();
    masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
    space = MBDMasuGet(masuId);
    switch (space->space_type) {
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            amount = func_800FD498_name_81();
            if (space->space_type - 11 == GwPlayer[GwSystem.current_player_index].chr) {
                func_800E14D8_name_81(GwSystem.current_player_index, amount);
                func_800F7378_name_81(GwSystem.current_player_index, amount);
                HuPrcSleep(30);
            } else if (player->stats.prize.gamblePrize == 2 || player->stats.prize.duelNo == 2) {
                partner = MBDGetPlayerPartnerRef(system->current_player_index,
                                                 (player->stats.prize.duelNo != 2) ? 0 : 1);
                HuPrcChildLink(proc, MBDCameraZoomMotStart(2.0f));
                HuPrcChildWait();
                HuVecCopy3F(&sp20, &player->player_obj->coords);
                func_800FC888_name_81(4);
                func_800FC8C4_name_81(&sp20);
                HuPrcChildLink(proc, func_800EC1E4_name_81(&sp20, &partner->coords, &sp20, 2.0f));
                HuPrcChildWait();
                func_800EB7BC_name_81(&sp10);
                func_800EBC60_name_81(&partner->rot, &sp10, &partner->rot, 8);
                HuPrcSleep(8);
                func_800FAD04_name_81(2);
                func_800FAE18_name_81(partner, 1, 0);
                func_800EFABC_name_81(partner);
                func_800D90D0_name_81(partner, -1, 2);
                func_800FADB4_name_81();
                func_800EAFC4_name_81(0x1F1C);
            } else {
                if (GwPlayer[system->current_player_index].coin == 0) {
                    amount = 0;
                    func_800EAFC4_name_81(0x1F1B);
                } else if (GwPlayer[system->current_player_index].coin < amount) {
                    amount = GwPlayer[system->current_player_index].coin;
                }
                if (amount != 0) {
                    func_800E14D8_name_81(system->current_player_index, -amount);
                    func_800F7378_name_81(system->current_player_index, -amount);
                    HuPrcSleep(30);
                    func_800E14B0_name_81((s8)(system->current_player_index ^ 1), amount);
                    func_800F7378_name_81((s8)(system->current_player_index ^ 1), amount);
                    HuPrcSleep(30);
                }
            }
            break;
        case 6:
            HuPrcSleep(8);
            func_800EA788_name_81(masuId, system->current_player_index);
            func_800EA7D4_name_81();
            func_800EA97C_name_81();
            HuAudFXPlay(0x201);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E8F4_duel10);
#endif

// board ec2: turn the current player around (sets the reverse flags).
void func_8010EC1C_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 7;
}

// board ec2: turn the current player back (clears the reverse flags).
void func_8010EC60_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 0;
}

// board ec2: the guide speaks message `mess` in its window and waits for it to close.
void func_8010ECA0_duel10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EF754_name_81(guide->amount);
    D_80114A3C_duel10 = 1;
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_8010ED14_duel10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
}

void func_8010ED50_duel10(UnkMBGuideData *guide) {
    func_800EF754_name_81(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_8010ED98_duel10(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    func_800EF800_name_81(guide->obj);
    func_800D90D0_name_81(guide->obj, -1, 2);
}

#ifdef NON_MATCHING
// board ec2: slide the guide from its x position to x over 14 frames, then idle.
// board ec2: masked 0; raw residue is the register allocation (guide s1, x - start in a1 in retail)
void func_8010EDF8_duel10(UnkMBGuideData *guide, s16 x) {
    s32 i;
    s32 step;
    s16 start = guide->spriteGroup;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (x - start) / 14;
    for (i = 0; i < 14; i++) {
        func_800E4EAC_name_81(guide, guide->spriteGroup + step, 0);
        HuPrcVSleep();
    }
    func_800E4EAC_name_81(guide, x, 0);
    func_800D90D0_name_81(guide->obj, -1, 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010EDF8_duel10);
#endif

// board ec2: guide motion process: plays each motion D_80114A40_duel10 requests, then idles.
void func_8010EEE4_duel10(void) {
    Object **obj = HuPrcCurrentGet()->user_data;

    while (1) {
        do {
            HuPrcVSleep();
        } while (D_80114A40_duel10 == -1);
        func_800D918C_name_81(*obj, D_80114A40_duel10, 0, 10, 0);
        D_80114A40_duel10 = -1;
        while (!(u16)func_800D9234_name_81(*obj) && D_80114A40_duel10 == -1) {
            HuPrcVSleep();
        }
        func_800D90D0_name_81(*obj, -1, 2);
    }
}

// board ec2: from duel05 (func_8010DB3C_duel05..func_8010E308_duel05); two sets for the two swinging signs
void func_8010EF98_duel10(void) {
    Ec2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0], HmfModelData[D_80114CD4_duel10->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], "neji");
        angle += D_80114A44_duel10;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->unk_14 = angle;
        HuPrcVSleep();
    }
}

void func_8010F070_duel10(void) {
    s16 model = D_80114CD4_duel10->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114BBC_duel10, 0x4C, 0x46);
    ((Ec2HmfPart *)func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], D_80114BBC_duel10))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010F114_duel10(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_80114A48_duel10);
    func_800D8944_name_81(obj);
    D_80114CD4_duel10 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x14)->coords);
    func_8010F070_duel10();
    D_80114CD8_duel10 = omAddPrcObj(func_8010EF98_duel10, 0xA, 0, 0);
    omPrcSetStatBit(D_80114CD8_duel10, 0xA0);
}

void func_8010F1A8_duel10(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_80114CDC_duel10 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80114A58_duel10);
    to = MBDMasuGet(D_80114A5A_duel10);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010F258_duel10(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_80114CE0_duel10;
        sincosdf(rot, &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010F3D4_duel10(Vec *pos) {
    Process *process;
    s32 *angle;

    D_80114CE0_duel10 = 10.0f;
    process = omAddPrcObj(func_8010F258_duel10, 0xA, 0, 0x40);
    D_80114A5C_duel10 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80114CDC_duel10->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010F474_duel10(void) {
    HmfModel *mdl;

    if (D_80114A5C_duel10 != NULL) {
        while (D_80114CE0_duel10 >= 0.0f) {
            D_80114CE0_duel10 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80114A5C_duel10);
        sincosdf(0.0f, &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BBC_duel10);

void func_8010F620_duel10(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80114CDC_duel10->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80114CDC_duel10->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80114CDC_duel10);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80114CDC_duel10->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80114CDC_duel10->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010F738_duel10(void) {
    omAddPrcObj(func_8010F620_duel10, 0xA, 0, 0);
}

void func_8010F764_duel10(void) {
    func_8001C814_main(D_80114CDC_duel10->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80114CDC_duel10->omObj1->model[0], 1.0f);
}

void func_8010F7B4_duel10(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_80114CE4_duel10 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80114A60_duel10);
    to = MBDMasuGet(D_80114A62_duel10);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010F864_duel10(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_80114CE8_duel10;
        sincosdf(rot, &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010F9E0_duel10(Vec *pos) {
    Process *process;
    s32 *angle;

    D_80114CE8_duel10 = 10.0f;
    process = omAddPrcObj(func_8010F864_duel10, 0xA, 0, 0x40);
    D_80114A64_duel10 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80114CE4_duel10->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010FA80_duel10(void) {
    HmfModel *mdl;

    if (D_80114A64_duel10 != NULL) {
        while (D_80114CE8_duel10 >= 0.0f) {
            D_80114CE8_duel10 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80114A64_duel10);
        sincosdf(0.0f, &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010FC2C_duel10(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80114CE4_duel10->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80114CE4_duel10->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80114CE4_duel10);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80114CE4_duel10->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80114CE4_duel10->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010FD44_duel10(void) {
    omAddPrcObj(func_8010FC2C_duel10, 0xA, 0, 0);
}

void func_8010FD70_duel10(void) {
    func_8001C814_main(D_80114CE4_duel10->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80114CE4_duel10->omObj1->model[0], 1.0f);
}

// board ec2: on the second call the guide gives message 0x2524.
void func_8010FDC0_duel10(void) {
    if (D_80114A68_duel10 == 1) {
        func_8010ECA0_duel10(D_80114CD0_duel10, 0x2524);
    }
    D_80114A68_duel10++;
}


// board ec4: the tutorial script: the guide explains a duel turn by turn (44 messages 0x250D..0x2539; 0x2524 is func_8010FDC0_duel10's).
// board ec4: NON_MATCHING: masked 0 with D_801149DC_duel10[-2] below (kept as D_801149D4_duel10[0] for a
// layout-independent read); raw residue is the callee-saved register allocation (system s7, player0 fp, curPrc s6 in retail)
#ifdef NON_MATCHING
void func_8010FE0C_duel10(void) {
    GW_SYSTEM *system = &GwSystem;
    s8 chain1, link1, chain2, link2, chain3, link3;
    s8 chain4, link4, chain5, link5;
    s8 chain6, link6;
    s8 chain7, link7;
    s8 chain9, link9;
    GW_PLAYER *player0;
    Process *curPrc;
    Object *obj;
    Process *prc;
    Ec1SprWork *work;
    SpaceData *space;
    Ec3HmfPart *part;
    GW_PLAYER *player;
    s16 model;
    f32 ofs;
    s32 i;

    player0 = MBDGetPlayerStruct(0);
    curPrc = HuPrcCurrentGet();
    D_801149D0_duel10 = GwSystem.message_speed;
    GwSystem.message_speed = 1;
    func_800EBAD4_name_81(1);
    func_800FC888_name_81(1);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    MBDCameraZoomSet(1.4f);
    MBDCameraPos3DSet(&MBDGetPlayerStruct(-1)->player_obj->coords);
    HuPrcSleep(1);
    WipeCreateIn(2, 0x10);
    func_800E5964_name_81();
    D_80114CD0_duel10 = func_800E4B64_name_81(D_80114A34_duel10, 0);
    HuVecCopyXYZ(&D_80114CD0_duel10->obj->scale, 1.1f, 1.1f, 1.1f);
    D_80114CD0_duel10->obj->coords.x -= 1.0f;
    D_80114CD0_duel10->obj->coords.y -= 2.0f;
    func_800F0480_name_81(D_80114CD0_duel10->obj, 2, 0xF, D_801149D4_duel10[0]);
    func_800E4EAC_name_81(D_80114CD0_duel10, 0x5A, 0);
    omAddPrcObj(func_8010EEE4_duel10, 0x4800, 0, 0)->user_data = D_80114CD0_duel10;
    func_8005B63C_main(D_80114CD0_duel10->amount, 0x40, 0x40);
    func_8010E258_duel10();
    func_8010E260_duel10();
    func_800EA1FC_name_81(5, 0xC);
    func_800EA1FC_name_81(6, 0xB);
    func_800EA97C_name_81();
    func_800F38DC_name_81(-1, -1, 2);
    func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(1);
    HuPrcSleep(3);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(3);

    /* the first turn: roll and walk */
    func_8010ED98_duel10(D_80114CD0_duel10);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x250D);
    system->current_player_index = 0;
    func_8010E338_duel10();
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    work = func_8010DB60_duel10(0, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x250E);
    func_8010DD5C_duel10(work);
    func_8010E8F4_duel10();
    HuPrcSleep(10);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x250F);
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    work = func_8010DB60_duel10(2, 100, 100);
    func_8010ED14_duel10(D_80114CD0_duel10, 0x2510);
    func_800F05B4_name_81(D_80114CD0_duel10->obj, D_801149DC_duel10[0]);
    func_8010ED50_duel10(D_80114CD0_duel10);
    func_8010DD5C_duel10(work);
    func_8010E8F4_duel10();
    /* retail reads this through D_801149DC_duel10's address (lw -0x8): D_801149DC_duel10[-2] gives masked 0 */
    func_800F05B4_name_81(D_80114CD0_duel10->obj, D_801149D4_duel10[0]);
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    work = func_8010DB60_duel10(1, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2511);
    func_8010DD5C_duel10(work);
    func_8010E8F4_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2512);
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    work = func_8010DB60_duel10(5, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2513);
    func_8010DD5C_duel10(work);

    /* a minigame */
    func_800F74E4_name_81(-1);
    func_8010EDF8_duel10(D_80114CD0_duel10, -30);
    D_80114A30_duel10 = 0;
    HuPrcSleep(1);
    GwSystem.minigame_index = -1;
    func_800E02B4_name_81(0);
    HuPrcSleep(15);
    func_800E0300_name_81();
    while (GwSystem.minigame_index == -1) {
        HuPrcVSleep();
    }
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2514);
    func_800DF210_name_81();
    D_80114A30_duel10 = 1;
    func_8010EDF8_duel10(D_80114CD0_duel10, 0x5A);
    func_800F75EC_name_81(-1);

    /* an object flies in */
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    obj = func_800D8010_name_81(0x3D, NULL);
    func_800D8944_name_81(obj);
    HuVecCopy3F(&obj->coords, &player0->player_obj->coords);
    obj->velocity.x = 100.0f;
    do {
        obj->velocity.x -= 3.0f;
        HuPrcVSleep();
    } while (obj->velocity.x >= 30.0f);
    prc = func_800EDEC4_name_81(obj, 5.0f, 2.0f);
    work = func_8010DB60_duel10(7, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2515);
    func_8010DD5C_duel10(work);
    omDelPrcObj(prc);
    while (obj->velocity.x <= 100.0f) {
        obj->velocity.x += 5.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(obj);

    /* the partners power up */
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    func_800EDD50_name_81(&player0->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(0);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    obj = func_800D8010_name_81(0x38, NULL);
    func_800D8944_name_81(obj);
    HuVecCopy3F(&obj->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
    func_8001C814_main(obj->omObj1->model[0], 2, 0);
    HuAudFXPlay(0x1FA);
    func_800EFABC_name_81(obj);
    func_800D8F3C_name_81(obj);
    Duel_PowerUpPartners(system->current_player_index);
    HuPrcChildLink(curPrc, func_800E4A74_name_81(0));
    HuPrcChildWait();
    work = func_8010DB60_duel10(6, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2516);
    func_8010DD5C_duel10(work);
    Duel_PowerDownPartners(system->current_player_index);

    /* dice blocks and items */
    func_8010E37C_duel10(2);
    func_8010E8D4_duel10();
    func_800DB624_name_81(system->current_player_index, 1);
    func_8010EC1C_duel10();
    func_8010E408_duel10(1);
    work = func_8010DB60_duel10(4, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2517);
    func_8010DD5C_duel10(work);
    func_8010E494_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2518);
    func_8010E8D4_duel10();
    player0->rev = 0;
    func_8011450C_duel10();
    work = func_8010DB60_duel10(3, 100, 100);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2519);
    func_8010DD5C_duel10(work);
    func_801148D8_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251A);
    HuPrcSleep(10);
    func_8010ED98_duel10(D_80114CD0_duel10);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251B);
    func_800F74E4_name_81(-1);
    func_8001FDE8_main(MBDGetPlayerStruct(0)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(0);
    func_800F8C68_name_81(1);

    /* the bell space */
    D_80114A30_duel10 = 0;
    {
        Vec pos;

        space = MBDMasuGet(0x14);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&pos);
        HuVecCopy3F(&pos, &player0->player_obj->coords);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &space->coords, &pos, 4.0f));
        i = 0;
        HuPrcChildWait();
    }
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251C);
    func_80114140_duel10();
    HuPrcSleep(10);
    do {
        model = D_80114CD4_duel10->omObj1->model[0];
        func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114BBC_duel10, 0x4C, 0x46);
        part = func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], D_80114BBC_duel10);
        part->unk_14 = (GwSystem.bank_coins - 5) * 60;
        HuAudFXPlay(0x1C7);
        for (ofs = 0.0f; ofs >= -60.0f; ofs -= 4.0f) {
            part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
            HuPrcVSleep();
        }
        if (GwSystem.bank_coins != 0) {
            GwSystem.bank_coins--;
        }
        i++;
        func_8010F070_duel10();
        HuPrcSleep(10);
    } while (i < 3);
    func_80114140_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251D);

    /* partner spaces */
    func_8010DAE8_duel10();
    func_800FC888_name_81(1);
    func_800D90D0_name_81(D_80114CD4_duel10, -1, 2);
    func_8001FDE8_main(D_80114CD4_duel10->omObj1->model[0]);
    func_800E9F4C_name_81(0xD, &chain1, &link1);
    func_800ECD0C_name_81(0, chain1, link1);
    func_800FCF50_name_81(0, 1);
    func_800F85A4_name_81(0, 0);
    func_800F8358_name_81(0);
    func_800F57B0_name_81(0);
    system->current_player_index = 0;
    func_8010E31C_duel10(NULL);
    func_8010DB24_duel10();
    func_800EDD50_name_81(&player0->player_obj->coords);
    func_800EE0D0_name_81(0);
    func_800EDF48_name_81();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251E);
    func_800F3880_name_81(-1, 6, 0);
    func_800E14D8_name_81(0, 10);
    func_800F7378_name_81(0, 10);
    HuPrcSleep(30);
    func_800F3880_name_81(-1, -1, 2);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x251F);
    func_80112E74_duel10(0, 0);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2520);
    func_80113970_duel10(0);
    GwSystem.playerIndexVisitingBowser = 2;
    func_80112E74_duel10(0, 1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2521);

    /* partner attacks */
    func_8010DAE8_duel10();
    func_800EDF78_name_81();
    func_800EDDBC_name_81();
    func_800E9F4C_name_81(7, &chain2, &link2);
    func_800ECD0C_name_81(0, chain2, link2);
    func_800E9F4C_name_81(8, &chain2, &link2);
    func_800ECD0C_name_81(1, chain2, link2);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    func_800F85A4_name_81(0, 0);
    func_800F85A4_name_81(0, 1);
    func_800F85A4_name_81(1, 0);
    func_800F85A4_name_81(1, 1);
    func_800F8358_name_81(0);
    func_800F8358_name_81(1);
    func_800F57B0_name_81(0);
    func_800F5E2C_name_81(0);
    func_800F57B0_name_81(1);
    func_800F5E2C_name_81(1);
    func_800F8418_name_81(0, 1, 0);
    func_800F8418_name_81(1, 2, 1);
    func_800F821C_name_81(0, 0);
    func_800F821C_name_81(1, 1);
    func_800F89D0_name_81(0, 0, -1, 2);
    func_800F89D0_name_81(1, 1, -1, 2);
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
    func_800F5BB4_name_81(0);
    func_800F5EB0_name_81(1);
    func_800EA1FC_name_81(9, 5);
    func_800EA97C_name_81();
    system->current_player_index = 0;
    func_8010E31C_duel10(NULL);
    func_8010DB24_duel10();
    func_800F75EC_name_81(-1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2522);
    D_80114A30_duel10 = 0;
    HuPrcChildLink(curPrc, func_800E415C_name_81());
    HuPrcChildWait();
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2523);
    D_80114A68_duel10 = 0;
    D_8010198C_name_81 = func_8010FDC0_duel10;
    D_80105718_name_81 = 10;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 1, 1, 0, 0);
    D_80114A30_duel10 = 1;
    D_8010198C_name_81 = NULL;
    func_800F8418_name_81(1, 2, 1);
    func_800F821C_name_81(1, 1);
    func_800F89D0_name_81(1, 1, -1, 2);
    func_800ED214_name_81(1);
    func_800F5EB0_name_81(1);
    D_80114A30_duel10 = 0;
    HuPrcChildLink(curPrc, func_800E415C_name_81());
    HuPrcChildWait();
    D_80114A30_duel10 = 1;
    D_80105718_name_81 = 12;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 0, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2525);

    /* the other player's turn */
    func_8010DAE8_duel10();
    func_8010E268_duel10();
    func_8010E31C_duel10(NULL);
    func_8010DB24_duel10();
    MBDGetPlayerStruct(1);
    func_8010E338_duel10();
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    func_800DB624_name_81(system->current_player_index, 1);
    func_8010EC1C_duel10();
    func_8010E37C_duel10(4);
    func_8010E4B4_duel10(1, 0);
    func_800DB3E0_name_81(1);
    D_80114A30_duel10 = 0;
    HuPrcChildLink(curPrc, func_800E415C_name_81());
    HuPrcChildWait();
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2526);
    D_80105718_name_81 = 10;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(1, 1, 0, 0, 1, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2527);
    D_80114A30_duel10 = 0;
    HuPrcChildLink(curPrc, func_800E415C_name_81());
    HuPrcChildWait();
    D_80114A30_duel10 = 1;
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(1, 1, -1, 1, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_800DADA0_name_81(1);
    HuPrcChildLink(curPrc, MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
    func_8010E8D4_duel10();
    func_8010EC60_duel10();
    HuPrcSleep(10);
    func_8010E338_duel10();
    func_8010E37C_duel10(2);
    func_8010E4B4_duel10(1, 0);
    func_800DB3E0_name_81(1);
    HuPrcChildLink(curPrc, MBDCameraZoomMotStart(1.0f));
    HuPrcChildWait();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2528);
    func_800EAD08_name_81(0x1E00);
    func_800EF754_name_81(D_80105712_name_81);
    func_800EAF94_name_81();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2529);

    /* stars */
    func_8010DAE8_duel10();
    GwPlayer[0].star = 5;
    GwPlayer[1].star = 5;
    func_800E9F4C_name_81(5, &chain3, &link3);
    func_800ECD0C_name_81(0, chain3, link3);
    func_800E9F4C_name_81(6, &chain3, &link3);
    func_800ECD0C_name_81(1, chain3, link3);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    func_800F85A4_name_81(0, 0);
    func_800F85A4_name_81(0, 1);
    func_800F85A4_name_81(1, 0);
    func_800F85A4_name_81(1, 1);
    func_800F8358_name_81(0);
    func_800F8358_name_81(1);
    func_800F57B0_name_81(0);
    func_800F5E2C_name_81(0);
    func_800F57B0_name_81(1);
    func_800F5E2C_name_81(1);
    func_800EA1FC_name_81(6, 0xC);
    func_800EA1FC_name_81(5, 0xB);
    func_800EA1FC_name_81(0, 6);
    func_800EA97C_name_81();
    system->current_player_index = 1;
    func_8010E31C_duel10(NULL);
    func_8010DB24_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252A);
    func_80113840_duel10(1, 1, 0);
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(1, 1, -1, 1, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252B);
    {
        Vec camPos2;

        player = MBDGetPlayerStruct(1);
        HuVecCopy3F(&camPos2, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos2);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos2, &MBDGetPlayerStruct(0)->player_obj->coords, &camPos2, 3.0f));
        HuPrcChildWait();
    }
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_80113840_duel10(0, 0, 1);
    D_80105718_name_81 = 12;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 0, 2, 0, 0);
    D_80114A30_duel10 = 1;
    func_800FC888_name_81(3);
    system->current_player_index = 1;
    func_8010E4B4_duel10(1, 1);
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252C);
    func_80113970_duel10(0);
    func_80113840_duel10(0, 0, 2);
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    obj = MBDGetPlayerPartnerRef(system->current_player_index, 0);
    HuPrcChildLink(curPrc, MBDCameraZoomMotStart(2.0f));
    HuPrcChildWait();
    player = MBDGetPlayerStruct(0);
    {
        Vec camPos3;
        Vec rot3;

        HuVecCopy3F(&camPos3, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos3);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos3, &obj->coords, &camPos3, 2.0f));
        HuPrcChildWait();
        func_800EB7BC_name_81(&rot3);
        func_800EBC60_name_81(&obj->rot, &rot3, &obj->rot, 8);
        HuPrcSleep(8);
        func_800FAD04_name_81(2);
        HuAudFXPlay(0x298);
        func_800FAE18_name_81(obj, 1, 0);
        func_800EFABC_name_81(obj);
        func_800D90D0_name_81(obj, -1, 2);
        func_800FADB4_name_81();
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos3, &player->player_obj->coords, &camPos3, 2.0f));
        HuPrcChildWait();
    }
    func_800FC888_name_81(1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252D);
    func_80113970_duel10(0);
    func_800E9F4C_name_81(8, &chain4, &link4);
    func_800ECD0C_name_81(1, chain4, link4);
    func_800FCF50_name_81(1, 1);
    func_80113644_duel10(1, 1, 1);
    func_800FC888_name_81(3);
    system->current_player_index = 1;
    func_8010EC1C_duel10();
    func_8010E4B4_duel10(1, 1);
    func_8010EC60_duel10();
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_80113840_duel10(0, 0, 3);
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 1, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_800FC888_name_81(3);
    system->current_player_index = 1;
    func_8010E4B4_duel10(1, 1);
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252E);
    func_800E9F4C_name_81(5, &chain5, &link5);
    func_800ECD0C_name_81(1, chain5, link5);
    func_800FCF50_name_81(1, 1);
    func_801136B4_duel10(1, 1);
    HuPrcVSleep();
    func_80113840_duel10(0, 1, 4);
    HuPrcVSleep();
    func_80113644_duel10(1, 0, 2);
    {
        Vec camPos4;

        player = MBDGetPlayerStruct(0);
        HuVecCopy3F(&camPos4, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos4);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos4, &MBDGetPlayerStruct(1)->player_obj->coords, &camPos4, 3.0f));
        HuPrcChildWait();
    }
    system->current_player_index = 1;
    func_800FC888_name_81(1);
    D_8010554C_name_81 = 10;
    D_80105718_name_81 = 16;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(1, 0, 1, 0, 1, 0, 1);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x252F);
    {
        Vec camPos5;

        player = MBDGetPlayerStruct(1);
        HuVecCopy3F(&camPos5, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos5);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos5, &MBDGetPlayerStruct(0)->player_obj->coords, &camPos5, 3.0f));
        HuPrcChildWait();
    }
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_800E9F4C_name_81(8, &chain6, &link6);
    func_800ECD0C_name_81(1, chain6, link6);
    func_800FCF50_name_81(1, 1);
    func_80113644_duel10(1, 0, 2);
    func_80113644_duel10(1, 1, 5);
    func_800FC888_name_81(3);
    system->current_player_index = 1;
    func_8010EC1C_duel10();
    func_8010E4B4_duel10(1, 1);
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    {
        Vec camPos6;

        player = MBDGetPlayerStruct(0);
        HuVecCopy3F(&camPos6, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos6);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos6, &MBDGetPlayerStruct(1)->player_obj->coords, &camPos6, 3.0f));
        HuPrcChildWait();
    }
    system->current_player_index = 1;
    func_800FC888_name_81(1);
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(1, 1, -1, 0, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2530);
    {
        Vec camPos7;

        player = MBDGetPlayerStruct(1);
        HuVecCopy3F(&camPos7, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos7);
        HuPrcChildLink(curPrc, func_800EC1E4_name_81(&camPos7, &MBDGetPlayerStruct(0)->player_obj->coords, &camPos7, 3.0f));
        HuPrcChildWait();
    }
    system->current_player_index = 0;
    func_800FC888_name_81(1);
    func_80113840_duel10(0, 0, 8);
    D_80105718_name_81 = 10;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 0, 200, 0, 0);
    D_80114A30_duel10 = 1;
    func_800F8C68_name_81(1);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2531);
    func_80113970_duel10(0);
    func_80113840_duel10(0, 0, 9);
    D_80105718_name_81 = 12;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 1, 0, 3, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2532);
    func_80113970_duel10(0);
    func_80113840_duel10(0, 0, 10);
    HuPrcVSleep();
    func_80113644_duel10(1, 0, 2);
    D_80105718_name_81 = 10;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, 0, 0, 1, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2533);
    func_80113970_duel10(0);
    GwPlayer[0].star = 5;
    GwPlayer[1].star = 5;
    func_80113840_duel10(0, 0, 11);
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, -1, 3, 0, 0, 0);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2534);
    D_80105718_name_81 = 0;
    D_80114A30_duel10 = 0;
    func_800FB59C_name_81(0, 0, -1, 0, 0, -1, -1);
    D_80114A30_duel10 = 1;
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2535);
    func_80113970_duel10(0);
    func_80113840_duel10(0, 1, 6);
    func_80113AF4_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2536);

    /* a partner bites the other player */
    func_800E9F4C_name_81(9, &chain7, &link7);
    func_800ECD0C_name_81(1, chain7, link7);
    func_800FCF50_name_81(1, 1);
    func_80113840_duel10(0, 0, 7);
    func_8010E37C_duel10(1);
    func_8010E8D4_duel10();
    player = MBDGetPlayerStruct(0);
    {
        Vec rot8;
        Vec rot8b;

        func_800EB7BC_name_81(&rot8);
        func_800EBC60_name_81(&player->player_obj->rot, &rot8, &player->player_obj->rot, 8);
        func_800F38DC_name_81(-1, -1, 2);
        func_800FAD04_name_81(7);
        obj = MBDGetPlayerPartnerRef(system->current_player_index, 0);
        func_800EB708_name_81(&obj->coords, &player->player_obj->coords, &rot8);
        HuVecCopy3F(&rot8b, &obj->rot);
        func_800EBC60_name_81(&obj->rot, &rot8, &obj->rot, 2);
        func_800FAE18_name_81(obj, 2, 0);
        HuPrcSleep(5);
        HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
        func_800DC07C_name_81(system->current_player_index, 1);
        func_800DB624_name_81(system->current_player_index, 2);
        prc = func_800DC324_name_81(system->current_player_index);
        GWBoardFlagSet(0x11);
        func_800EFABC_name_81(obj);
        func_800FAE18_name_81(obj, 3, 2);
        HuPrcSleep(20);
        func_800D918C_name_81(obj, -1, 0, 5, 2);
        func_800EBC60_name_81(&obj->rot, &rot8b, &obj->rot, 6);
    }
    HuPrcSleep(6);
    func_800FADB4_name_81();
    func_800FC888_name_81(1);
    GWBoardFlagClear(0x11);
    func_800D9F90_name_81(system->current_player_index);
    HuPrcChildLink(curPrc, prc);
    HuPrcChildWait();
    func_8010E8D4_duel10();
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2537);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2538);
    func_800E14D8_name_81(system->current_player_index, -30);
    func_800F7378_name_81(system->current_player_index, -30);
    HuPrcSleep(30);
    func_80113970_duel10(0);

    /* the end: both players walk to space 8 */
    func_800FC888_name_81(3);
    func_800E9F4C_name_81(9, &chain9, &link9);
    func_800ECD0C_name_81(1, chain9, link9);
    func_800FCF50_name_81(1, 1);
    space = MBDMasuGet(8);
    {
        Vec dest[2];

        HuVecCopy3F(&dest[0], &space->coords);
        dest[0].x += 10.0f;
        HuVecCopy3F(&dest[1], &space->coords);
        dest[1].x -= 10.0f;
        player = MBDGetPlayerStruct(0);
        func_800EB708_name_81(&player->player_obj->coords, &dest[0], &player->player_obj->rot);
        func_800D90D0_name_81(player->player_obj, 0, 2);
        HuPrcChildLink(curPrc, func_800EBF2C_name_81(&player->player_obj->coords, &dest[0], &player->player_obj->coords, 30));
        player = MBDGetPlayerStruct(1);
        func_800EB708_name_81(&player->player_obj->coords, &dest[0], &player->player_obj->rot);
        func_800D90D0_name_81(player->player_obj, 0, 2);
        HuPrcChildLink(curPrc, func_800EBF2C_name_81(&player->player_obj->coords, &dest[1], &player->player_obj->coords, 30));
        HuPrcChildWait();
        func_800EB7BC_name_81(&dest[0]);
        func_800EB7BC_name_81(&dest[1]);
        player = MBDGetPlayerStruct(0);
        func_800D90D0_name_81(player->player_obj, -1, 2);
        func_800EBC60_name_81(&player->player_obj->rot, &dest[0], &player->player_obj->rot, 8);
        player = MBDGetPlayerStruct(1);
        func_800D90D0_name_81(player->player_obj, -1, 2);
        func_800EBC60_name_81(&player->player_obj->rot, &dest[1], &player->player_obj->rot, 8);
    }
    HuPrcSleep(8);
    func_8010ECA0_duel10(D_80114CD0_duel10, 0x2539);
    func_800F05B4_name_81(D_80114CD0_duel10->obj, D_801149EC_duel10[0]);
    HuPrcSleep(30);
    GwSystem.message_speed = D_801149D3_duel10;
    HuAudSeqFadeOut(60);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(16);
    func_800E4E64_name_81(D_80114CD0_duel10);
    func_800FC4E4_name_81();
    func_800FC108_name_81();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FE0C_duel10);
#endif


void func_80111D0C_duel10(void) {
    HuAudSeqPlay(0xB);
    Hu3DCamInit(2);
    func_8010DA60_duel10();
    func_8004A208_main();
    func_800EA46C_name_81(D_80114AA0_duel10);
    func_800EA46C_name_81(D_80114AB0_duel10);
    func_800FC5A8_name_81(func_8011450C_duel10);
    func_800FC59C_name_81((s32)func_80114940_duel10);
    omAddPrcObj(func_8010FE0C_duel10, 0xEFFF, 0x2000, 0);
    omAddPrcObj(func_800FC8E8_name_81, 0x1005, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_8010E0EC_duel10, 0x1005, 0, 0), 0x80);
}


s32 func_80111DC4_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

// board ec3: duel01/duel05 twin; float constants: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (masked 24)
#ifdef NON_MATCHING
void func_80111E6C_duel10(void) {
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
        if (D_80114A8C_duel10 != 0) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111E6C_duel10);
#endif

void func_80111FDC_duel10(void) {
    s16 pos[3][2] = { { 160, -80 }, { 160, -160 }, { 160, -80 } };
    s32 files[6] = { 0x13011C, 0x13011F, 0x13011E, 0x13011D, 0x130120, 0x13011E }; /* [player * 3 + i] */
    u8 order[32];
    s32 player;
    s32 msg;
    s16 win;
    Process *proc;
    s32 kind;
    s32 cpuCount;
    s32 wait;
    s32 n;
    s32 i;
    s32 *data;
    void *file;
    Duel01SprGrp *grp;

    player = *(s32 *)HuPrcCurrentGet()->user_data;
    n = 11;
    proc = NULL;
    D_80114A30_duel10 = 0;
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
        proc = omAddPrcObj(func_80111E6C_duel10, 0xA, 0, 0x40);
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
        cpuCount = func_800EFE20_name_81(10.0f) + 100;
    } else {
        cpuCount = -1;
    }
    msg = func_800E1824_name_81(0x13, 0xB9, 0);
    D_80114A8C_duel10 = 1;
    do {
        func_800E0310_name_81(order, n);
        for (i = 0; i <= n; i++) {
            HuAudFXPlay(0x1C8);
            func_80055140_main(grp->unk_0A, 2, order[i], 0);
            func_800550F4_main(grp->unk_0A, 2, 1);
            wait = (kind == 2) ? 15 : 1;
            while (TRUE) {
                if (cpuCount > 0) {
                    if (--cpuCount == 0) {
                        break;
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
    D_80114A8C_duel10 = 0;
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
    D_80114A84_duel10 = order[i];
    func_800E1854_name_81(msg);
    if (proc != NULL) {
        omDelPrcObj(proc);
    }
    func_800F4584_name_81(grp);
    func_8005F364_main(win);
    D_80114A30_duel10 = 1;
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C44_duel10);

// board ec3: duel01/duel05 twin; register allocation (the -1, walk target and partner/bell registers) and one branch-likely (masked 15)
#ifdef NON_MATCHING
s32 func_801127A8_duel10(s32 no) {
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

    start = MBDMasuGet(D_80114A6C_duel10[no][1]);
    goal = MBDMasuGet(D_80114A6C_duel10[no][2]);
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
        func_8010F3D4_duel10(&player->player_obj->coords);
    } else {
        func_8010F9E0_duel10(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_80114A84_duel10 = -1;
    proc = omAddPrcObj(func_80111FDC_duel10, 0xA, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = data;
    *data = no;
    pos = &MBDMasuGet(D_80114A6C_duel10[no][0])->coords;
    func_800EB708_name_81(&player->player_obj->coords, pos, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&player->player_obj->coords, pos, &player->player_obj->coords, 2.0f));
    HuPrcChildWait();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&dir);
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    if (D_80114A84_duel10 == -1) {
        do {
            HuPrcVSleep();
        } while (D_80114A84_duel10 == -1);
    }
    HuVecCopy3F(&target, &goal->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 2.0f));
    HuPrcChildWait();
    if (no == 0) {
        func_8010F474_duel10();
    } else {
        func_8010FA80_duel10();
    }
    bell = func_800D8010_name_81(0x35, 0);
    func_800D8F0C_name_81(bell);
    partner = func_800F8050_name_81(D_80114A84_duel10);
    HuVecCopy3F(&partner->coords, &goal->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (no == 0) {
        func_8010F738_duel10();
    } else {
        func_8010FD44_duel10();
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
    pos = &MBDMasuGet(D_80114A6C_duel10[no][1])->coords;
    func_800EB708_name_81(&partner->coords, pos, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, pos, &partner->coords, 20));
    HuPrcChildWait();
    func_800EF800_name_81(partner);
    if (no == 0) {
        func_8010F764_duel10();
    } else {
        func_8010FD70_duel10();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&cam, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &player->player_obj->coords, &cam, 2.0f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
    D_80114A88_duel10 = partner;
    return D_80114A84_duel10;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801127A8_duel10);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C74_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C78_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C80_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114CA0_duel10);

void func_80112E74_duel10(s32 no, s32 cpuTake) {
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
    padMask = D_80114C74_duel10;
    choice = D_80114C78_duel10;
    if ((*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        HuAudFXPlay(0x159);
        func_800EB140_name_81(0x16, 0x1F04);
        partnerID = func_801127A8_duel10(no);
    loop1:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (cpuTake != 0) {
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
            func_801059D0_duel10();
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
            if (player->stats.partners.backID == -1 || func_80111DC4_duel10() >= func_800EFE20_name_81(100.0f)) {
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
            func_801059D0_duel10();
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
            ofs = D_80114C80_duel10;
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
        partnerID = func_801127A8_duel10(no);
    }
    func_800ECF1C_name_81(no, &frontPos, &backPos);
    func_800ED118_name_81(no, &frontRot, &backRot);
    func_800D918C_name_81(D_80114A88_duel10, 0, 0, 5, 2);
    if (result == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_80114A88_duel10->coords, &frontPos, &D_80114A88_duel10->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80114A88_duel10->coords, &frontPos, &D_80114A88_duel10->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80114A88_duel10->rot, &frontRot, &D_80114A88_duel10->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_80114A88_duel10->coords, &backPos, &D_80114A88_duel10->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80114A88_duel10->coords, &backPos, &D_80114A88_duel10->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80114A88_duel10->rot, &backRot, &D_80114A88_duel10->rot, 7));
    }
    HuPrcChildWait();
    func_800D8F3C_name_81(D_80114A88_duel10);
    func_800F8418_name_81(no, partnerID, result);
    func_800F821C_name_81(no, result);
    func_800F89D0_name_81(no, 0, -1, 2);
    func_800F89D0_name_81(no, 1, -1, 2);
    func_800ED214_name_81(no);
    func_800F5BB4_name_81(no);
    func_800F5EB0_name_81(no);
}

void func_80113644_duel10(s32 no, s32 slot, s32 partnerID) {
    func_800F8418_name_81(no, partnerID, slot);
    func_800F821C_name_81(no, slot);
    func_800F89D0_name_81(no, slot, -1, 2);
    func_800ED214_name_81(no);
    func_800F5BB4_name_81(no);
    func_800F5EB0_name_81(no);
}

void func_801136B4_duel10(s32 no, s32 slot) {
    func_800F85A4_name_81(no, slot);
    func_800F82EC_name_81(no);
    func_800F57B0_name_81(no);
    func_800F5E2C_name_81(no);
}

void func_801136F0_duel10(s32 no, s32 slot) {
    Vec front;
    Vec back;
    Vec pos;
    DuelB7VecTbl ofs;
    GW_PLAYER *player;
    s32 i;

    player = MBDGetPlayerStruct(no);
    func_800ECF1C_name_81(no, &front, &back);
    HuVecAdd(&front, &player->player_obj->coords, &front);
    HuVecAdd(&back, &player->player_obj->coords, &back);
    HuVecCopy3F(&pos, (slot == 0) ? &front : &back);
    pos.y += 2.0f;
    ofs = D_80114C80_duel10;
    for (i = 0; i < 3; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[i], 3.0f));
    }
    HuAudFXPlay(0x1CB);
}

void func_80113840_duel10(s32 no, s32 slot, s32 partnerID) {
    Vec pos;
    DuelB7VecTbl ofs;
    Object *partner;
    s32 i;

    func_80113644_duel10(no, slot, partnerID);
    partner = MBDGetPlayerPartnerRef(no, slot);
    func_800D8F0C_name_81(partner);
    HuVecCopy3F(&pos, &partner->coords);
    pos.y += 2.0f;
    ofs = D_80114C80_duel10;
    for (i = 0; i < 3; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[i], 3.0f));
    }
    HuAudFXPlay(0x1CB);
    HuPrcSleep(20);
    func_800D8E88_name_81(partner);
    HuPrcChildWait();
}

void func_80113970_duel10(s32 no) {
    Vec pos;
    DuelB7VecTbl ofs;
    Object *partner;
    s32 i;
    s32 slot;

    for (slot = 0; slot < 2; slot++) {
        partner = MBDGetPlayerPartnerRef(no, slot);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            ofs = D_80114C80_duel10;
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[i], 3.0f));
            }
            func_800D8F0C_name_81(partner);
        }
    }
    HuAudFXPlay(0x1CB);
    HuPrcChildWait();
    func_800F85A4_name_81(no, 0);
    func_800F85A4_name_81(no, 1);
    func_800F82EC_name_81(no);
    func_800F57B0_name_81(no);
    func_800F5E2C_name_81(no);
}

void func_80113AF4_duel10(void) {
    Vec dir;
    Vec rot;
    Vec camPos;
    Vec puffPos;
    s32 cur;
    GW_PLAYER *player;
    Object *partner;
    Object *coin;
    s32 count;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    f32 scale;

    cur = GwSystem.current_player_index;
    player = MBDGetPlayerStruct(cur);
    if (player->stats.partners.frontID == 6 || player->stats.partners.backID == 6) {
        count = 4;
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
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&camPos, &player->player_obj->coords, &camPos, 2.0f));
        HuPrcChildWait();
        func_800FC888_name_81(1);
    }
}

void func_80114140_duel10(void) {
    Ec3HmfPart *part;
    f32 ofs;

    func_800D90D0_name_81(D_80114CD4_duel10, 2, 0);
    func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0],
                       HmfModelData[D_80114CD4_duel10->omObj1->model[0]].unk02, D_80114BBC_duel10, 0x4C, 0x46);
    func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0], D_80114CD4_duel10->omObj1->motion[2],
                       D_80114BBC_duel10, 0x4C, 0x46);
    ((Ec3HmfPart *)func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], D_80114BBC_duel10))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
    HuPrcSleep(10);
    HuAudFXPlay(0x1C5);
    func_800EFABC_name_81(D_80114CD4_duel10);
    HuAudFXPlay(0x1C7);
    func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0],
                       HmfModelData[D_80114CD4_duel10->omObj1->model[0]].unk02, D_80114BBC_duel10, 0x4C, 0x46);
    part = func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], D_80114BBC_duel10);
    part->unk_14 = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (ofs = 0.0f; ofs >= -60.0f; ofs -= 4.0f) {
        part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
        HuPrcVSleep();
    }
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    func_8010F070_duel10();
    D_80114A44_duel10 = 12.0f;
    if (GwSystem.bank_coins != 0) {
        func_800D918C_name_81(D_80114CD4_duel10, 0, 0, 5, 2);
        func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0], D_80114CD4_duel10->omObj1->motion[0],
                           D_80114BBC_duel10, 0x4C, 0x46);
        func_8001C92C_main(D_80114CD4_duel10->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(0x18);
        func_800D90D0_name_81(D_80114CD4_duel10, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        func_800D918C_name_81(D_80114CD4_duel10, 1, 0, 5, 2);
        func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0], D_80114CD4_duel10->omObj1->motion[1],
                           D_80114BBC_duel10, 0x4C, 0x46);
        func_8001C92C_main(D_80114CD4_duel10->omObj1->model[0], 1.0f);
        func_8010F070_duel10();
    }
    D_80114A44_duel10 = 3.0f;
}

void func_8011450C_duel10(void) {
    void *data;
    s32 i;
    s32 y;

    D_80114A30_duel10 = 0;
    mbItemBtnF = 0;
    func_800F74E4_name_81(-1);
    HuAudFXPlay(0x204);
    D_80114CEC_duel10 = func_800F4528_name_81(2, 2);
    data = DataRead(0x130103);
    D_80114CEC_duel10->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80114CEC_duel10->unk_0A, 0, D_80114CEC_duel10->unk_0C[0], 0);
    HuSprPriSet(D_80114CEC_duel10->unk_0A, 0, 11);
    HuSprAttrSet(D_80114CEC_duel10->unk_0A, 0, 0x1000);
    func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, -32);
    func_800555E8_main(D_80114CEC_duel10->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    D_80114CEC_duel10->unk_0C[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80114CEC_duel10->unk_0A, 1, D_80114CEC_duel10->unk_0C[1], 0);
    HuSprPriSet(D_80114CEC_duel10->unk_0A, 1, 12);
    HuSprAttrSet(D_80114CEC_duel10->unk_0A, 1, 0x1000);
    func_80054904_main(D_80114CEC_duel10->unk_0A, 1, 0, 0);
    func_800555E8_main(D_80114CEC_duel10->unk_0A, 0, 16, 12, 304, 228);
    func_80055420_main(D_80114CEC_duel10->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, 120);
    for (y = 0, i = 0; i < 9; i++) {
        y += i * 2;
        func_80054904_main(D_80114CEC_duel10->unk_0A, 0, 160, 120 - y);
        HuPrcVSleep();
    }
}

void func_801148D8_duel10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800E0924_name_81());
    HuPrcChildWait();
    func_800F4584_name_81(D_80114CEC_duel10);
    func_800F75EC_name_81(-1);
    D_80114A30_duel10 = 1;
    mbItemBtnF = 1;
}

// board ec3: register allocation only (the second player struct in a0, retail a1; masked 0)
#ifdef NON_MATCHING
s32 func_80114940_duel10(void) {
    GW_PLAYER *player;
    GW_PLAYER *otherPlayer;
    s32 cur = GwSystem.current_player_index;
    s32 other = (cur + 1) & 1;

    player = MBDGetPlayerStruct(cur);
    otherPlayer = MBDGetPlayerStruct(other);
    if (player->nlink != otherPlayer->clink) {
        return -1;
    }
    return -(player->nidx != otherPlayer->cidx);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80114940_duel10);
#endif

