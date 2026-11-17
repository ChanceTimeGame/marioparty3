#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801059D0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105A58_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105B10_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105B64_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105BA0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105C68_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105CC4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105EB4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105F24_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801060D4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106160_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106244_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106264_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801062C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010630C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106460_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801064CC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106744_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801067D8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010682C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010718C_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117B20_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801079BC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80107EC0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801084A8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80108554_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80109408_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010988C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010A214_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AAB4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AD4C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AFB8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B134_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B484_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B4C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B52C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B540_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B550_duel03);

// board db2: declarations for func_8010BCD8_duel03..func_80110A70_duel03 (twins of duel01's)
typedef struct Duel01Part {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Duel01Part;
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;
#include "process.h"
#include "common_structs.h"
#include "malloc.h"
#include "game/board.h"
f32 func_800D76D0_name_81(void*);
s32 func_800E1824_name_81(s32, s32, s32);
void func_800E1854_name_81(s32);
void func_800EB708_name_81(Vec*, Vec*, Vec*); // duel b1: was (s32, s32, unkStruct01*)
void func_800FC8C4_name_81(void*);
extern Vec D_80105540_name_81; // duel b1: was s32
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32); // duel b1: was (void*, s32, void*, f32)
Process* func_800EBF2C_name_81(Vec* from, Vec* to, Vec* out, s32 frames); // duel b1/b7: ovl_81 DFD60.c
void func_8001C258_main(s16, s32, s32);
void func_8001C448_main(s16);
void func_8001C8E4_main(s16, u32);
Object* func_800D8010_name_81(u8, s32*); // b7: ovl_81 BFB40.c (was void*(s32, s32))
void func_800D8944_name_81(Object*);
void func_800D8F0C_name_81(Object*);
void func_800D8E88_name_81(Object*); // duel b1: was (void)
s16 MBDGetCurrentPlayerIndex(void);
GW_PLAYER* MBDGetPlayerStruct(s32);
void func_800F38DC_name_81(s32, s32, s32);
void func_8010FE9C_duel03(s32);
#include "game/object.h"
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
B1UnkBoard4* func_800F4528_name_81(s16, s16);
void func_800F4584_name_81(B1UnkBoard4*);
void func_800D90D0_name_81(Object*, s16, u16);
void func_800EFABC_name_81(Object*);
s32 func_800EFE20_name_81(f32);
void func_800FC888_name_81(s32);
Object* MBDGetPlayerPartnerRef(s32, s32);
void func_800D8F3C_name_81(Object*);
void func_800FAD04_name_81(s32);
void func_800FAE18_name_81(Object*, s16, s16);
void func_800FADB4_name_81(void);
void func_800ED214_name_81(s32);
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
extern s32 D_80117430_duel03[]; // partner attack effect model ids, by level - 1 (read as u8)
extern char D_80117B20_duel03[]; // "obj1"
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
void func_80106160_duel03(Object*, Object*, GW_PLAYER*, Vec*, Vec*, f32);
void func_800EB804_name_81(Object*);
void func_800FAE98_name_81(Object*, s16, s16, s16, s16);
void func_8001C92C_main(s16, f32);
void MBDBackTPLvlSet(u8);
extern Object *D_801180E0_duel03;
extern f32 D_8011744C_duel03;
extern char D_80117BD8_duel03[];
SpaceData *MBDMasuGet(s16);
Process *MBDCameraZoomMotStart(f32);
void *func_8001D33C_main(s16, char *);
void func_8002FD8C_main(s16, s16, char *, s16, s16);
void func_800D918C_name_81(Object *, s16, s16, s16, u16);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB49C_name_81(s16, s32, s32, s32, s32, s32, s32);
void func_800EB58C_name_81(void);
void func_8010DC08_duel03(void);
Object *func_800EDD50_name_81(Vec *);
void func_800EDDBC_name_81(void);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE468_name_81(s32);
void func_800F3880_name_81(s32, s16, u16);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_800EA7D4_name_81(void);
void func_800EA97C_name_81(void);
void Duel_PowerUpPartners(s32);
void Duel_PowerDownPartners(s32);
void func_8001C814_main(s16, s16, s16);
void func_800EB140_name_81(s32, s32);
s32 func_800F8980_name_81(s32);
#include "mallocblock.h"
typedef void (*DuelB2PartnerFunc)(s32, s32, Object *, Object *, s32, s32);
/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void *func_8001D33C_main(s16 model, char *name);
extern s32 D_80117430_duel03[];
extern char D_80117B20_duel03[];
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
Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
void func_800FAE98_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_800FC888_name_81(s32 arg0);
void MBDBackTPLvlSet(u8 arg0);
Object *func_800D8B18_name_81(Object *obj);
void func_800EF7C8_name_81(Object *obj, f32 arg1, f32 arg2);
s32 func_800EF7D4_name_81(Object *obj);
s32 func_800EFE20_name_81(f32 arg0);
void func_800D918C_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_800FAE18_name_81(Object *arg0, s16 arg1, s16 arg2);
Process *func_801060D4_duel03(GW_PLAYER *player, Object *target, s32 arg2, s32 arg3);
void func_80106160_duel03(Object *partner, Object *target, GW_PLAYER *player, Vec *arg3, Vec *arg4, f32 arg5);
void func_800D7828_name_81(Vec *vec);
void func_800D8F3C_name_81(Object *arg0);
void func_800FAC94_name_81(DuelB2PartnerFunc *arg0, DuelB2PartnerFunc *arg1);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2); // defined with two parameters in E3CD0.c
void func_800EA46C_name_81(event_table_entry *arg0);
void func_800FC5A8_name_81(process_func arg0);
void func_800FC59C_name_81(s32 arg0);
void func_800FF640_name_81(u32 arg0);
void func_8010682C_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010718C_duel03(s32, s32, Object *, Object *, s32, s32);
void func_801079BC_duel03(s32, s32, Object *, Object *, s32, s32);
void func_80107EC0_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010988C_duel03(s32, s32, Object *, Object *, s32, s32);
void func_801084A8_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010CE6C_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010D428_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD8_duel03(s32, s32, Object *, Object *, s32, s32);
void func_80108554_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010A214_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010B550_duel03(s32, s32, Object *, Object *, s32, s32);
void func_8010DCAC_duel03(void);
void func_8010DD40_duel03(void);
void func_8010E34C_duel03(void);
void func_8010EA1C_duel03(void);
void func_80113740_duel03(void);
s32 func_80117264_duel03(void);
extern event_table_entry D_8011762C_duel03[];
extern event_table_entry D_80117AD4_duel03[];
Process *func_800DCE10_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay);
void func_8010DB30_duel03(void);
void func_8010DDF0_duel03(void);
void func_8010E1B8_duel03(void);
void func_8010E3FC_duel03(void);
void func_8010E7C4_duel03(void);
extern char D_80117BD8_duel03[]; /* "bell" (rodata; func_80111DFC_duel01 uses it too) */
extern s32 D_80117450_duel03[];
extern s16 D_80117460_duel03;
extern s16 D_80117462_duel03;
extern s16 D_80117468_duel03;
extern s16 D_8011746A_duel03;
extern Process *D_80117464_duel03;
extern Process *D_8011746C_duel03;
extern Process *D_801180E4_duel03;
extern Object *D_801180E8_duel03;
extern f32 D_801180EC_duel03;
extern Object *D_801180F0_duel03;
extern f32 D_801180F4_duel03;
extern s8 D_80117478_duel03[]; /* value, chance pairs */
extern Duel01Weight *D_80117574_duel03[8]; /* per character */
extern s32 D_801175B4_duel03;
extern s32 D_801175AC_duel03;
typedef B1UnkBoard4 Duel01SprGrp; /* ovl_81's sprite group (UnkBoard4 there) */
s32 func_800F37B8_name_81(s16 playerIndex);
void func_800E0310_name_81(u8 *output, s32 count);
extern u16 D_800C9520_main[];
s32 func_8010EBD4_duel03(void);
void func_8010EDF0_duel03(void);
void func_8010EF60_duel03(void);
void func_8010DF6C_duel03(Vec *pos);
void func_8010E00C_duel03(void);
void func_8010E2D0_duel03(void);
void func_8010E2FC_duel03(void);
void func_8010E578_duel03(Vec *pos);
void func_8010E618_duel03(void);
void func_8010E8DC_duel03(void);
void func_8010E908_duel03(void);
void func_800EB140_name_81(s32 arg0, s32 arg1);
void func_800EB7BC_name_81(Vec *out);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void func_800EF800_name_81(Object *obj);
Object *func_800F8050_name_81(s32 partnerID);
void func_800FC8DC_name_81(Object *arg0);
extern s32 D_80117594_duel03[2][3]; /* per player: three space ids (splat labels 7E/82/86 are low halves) */
extern Object *D_801175B0_duel03;
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
extern const DuelPadMask D_80117CB4_duel03;
extern const DuelChoiceTbl D_80117CB8_duel03;
extern s16 D_8010555C_name_81;
void func_800FB524_name_81(s32);
void func_800EB1D8_name_81(s32 arg0, s32 arg1);
s32 func_800EED50_name_81(void);
s32 func_8010EA74_duel03(void);
s32 func_8010F7D0_duel03(s32 no);
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
extern const DuelB7VecTbl D_80117CC0_duel03; /* smoke puff offsets around a partner leaving */
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
extern u8 D_80117CE4_duel03[]; /* window strings: the starting partner choices (SJIS) */
extern u8 D_80117DCC_duel03[];
extern u8 D_80117EB4_duel03[];
extern u8 D_80117F9C_duel03[];
void func_8008A120_main(f32 *mtx, f32 angle); // defined with Matrix4f (f32[4][4])
void func_800F8108_name_81(s32 playerIndex);
void func_800F82EC_name_81(s32 playerIndex);
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
/* Window selection of one starting partner; retail reads the current player's pad even for player 2's picks. */
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

/* Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4
   coins; from the second turn the player pays the partners' upkeep, or loses them when short of coins. */
extern s16 mbItemBtnF;
void func_800E14D8_name_81(s32 player, s32 coins);
void func_800F7378_name_81(s32 playerIndex, s32 coinAmount);
void func_800FB524_name_81(s32 playerNo);
s32 func_800F8980_name_81(s32 playerIndex); // ovl_81 defines it with a void * (stored as process user_data)
void func_80110A70_duel03(void);
extern s32 D_80117450_duel03[4];
extern s8 D_80117478_duel03[13 * 2];
extern Duel01Weight *D_80117574_duel03[8];
extern event_table_entry D_8011762C_duel03[5];
extern event_table_entry D_80117AD4_duel03[13];
void func_801059D0_duel03(void);
void func_80106244_duel03(void);
Process *func_80106264_duel03(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3);
Process *func_80106460_duel03(s32 arg0, s32 arg1);
void func_801064CC_duel03(s32 playerIndex, s32 mode);
void *func_80106744_duel03(s32 arg0);
void func_801067D8_duel03(Object *arg0, Vec *arg1);
// board db2: end of declarations

void func_8010BCD8_duel03(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
    obj = func_800D8010_name_81(D_80117430_duel03[variant - 1] & 0xFF, 0);
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
    func_80106244_duel03();
    func_80106264_duel03(target, player, 0, 7.0f);
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
        func_801064CC_duel03(playerNo, 0);
        func_800EF800_name_81(partner);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, func_80106460_duel03(10, 1));
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
        func_801064CC_duel03(playerNo, 1);
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

// board db2: func_8010CE68_duel01's twin (same instructions), same residue.
#ifdef NON_MATCHING
// duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block.
void func_8010CE6C_duel03(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra1 = func_80106744_duel03(0x4C);
        HuPrcVSleep();
        extra2 = func_80106744_duel03(0x53);
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
    func_80106244_duel03();
    func_800D8E88_name_81(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, func_80106264_duel03(target, player, flags, 4.0f));
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
        func_801060D4_duel03(player, target, 0, 0x14);
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
            func_801067D8_duel03(extra1, &sp28);
            HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
            func_801067D8_duel03(extra2, &sp28);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010CE6C_duel03);
#endif

// board db2: func_8010D424_duel01's twin (same instructions), same residue.
#ifdef NON_MATCHING
// duel b2: masked 0, raw 28: partner and obj swap s3/s4.
void func_8010D428_duel03(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra = func_80106744_duel03(0x45);
    }
    obj = func_800D8010_name_81(D_80117430_duel03[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_80106160_duel03(partner, target, player, &sp18, &sp28, 7.5f);
    func_80106244_duel03();
    func_80106264_duel03(target, player, flags, 3.0f);
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
        func_801060D4_duel03(player, target, 0, 0x1E);
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
            func_801067D8_duel03(extra, &sp38);
        } else {
            effect = func_800DD1E0_name_81(0xB0024, D_80117B20_duel03);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010D428_duel03);
#endif

void func_8010D960_duel03(void) {
    DuelB2PartnerFunc funcs1[12] = {
        func_8010682C_duel03, func_8010718C_duel03, func_801079BC_duel03, func_80107EC0_duel03,
        func_8010988C_duel03, func_801084A8_duel03, func_8010CE6C_duel03, func_8010D428_duel03,
        func_8010BCD8_duel03, func_80108554_duel03, func_8010A214_duel03, func_8010B550_duel03,
    };
    DuelB2PartnerFunc funcs2[12] = {
        NULL, NULL, NULL, NULL, func_8010988C_duel03, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(funcs1, funcs2);
}

void func_8010D9F8_duel03(void) {
    omInitObjMan(0xA0, 0x50);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_800FC260_name_81(0x1A, 0x243, 0);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    func_8010DCAC_duel03();
    func_8010DD40_duel03();
    func_8010E34C_duel03();
    func_8010EA1C_duel03();
    func_8010D960_duel03();
}

void func_8010DA88_duel03(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F8_duel03();
    func_800EA46C_name_81(D_8011762C_duel03);
    func_800EA46C_name_81(D_80117AD4_duel03);
    func_800FC5A8_name_81(func_80113740_duel03);
    func_800FC59C_name_81((s32)func_80117264_duel03);
    func_800FF640_name_81(0);
}

void func_8010DB04_duel03(void) {
    Hu3DCamInit(1);
    func_8010D9F8_duel03();
    func_800FF640_name_81(1);
}





void func_8010DB30_duel03(void) {
    DuelB2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_801180E0_duel03->omObj1->model[0], HmfModelData[D_801180E0_duel03->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_801180E0_duel03->omObj1->model[0], "neji");
        angle += D_8011744C_duel03;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->rotY = angle;
        HuPrcVSleep();
    }
}

void func_8010DC08_duel03(void) {
    s16 model = D_801180E0_duel03->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80117BD8_duel03, 0x4C, 0x46);
    ((Duel01Part *)func_8001D33C_main(D_801180E0_duel03->omObj1->model[0], D_80117BD8_duel03))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010DCAC_duel03(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_80117450_duel03);
    func_800D8944_name_81(obj);
    D_801180E0_duel03 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x1A)->coords);
    func_8010DC08_duel03();
    D_801180E4_duel03 = omAddPrcObj(func_8010DB30_duel03, 0xA, 0, 0);
    omPrcSetStatBit(D_801180E4_duel03, 0xA0);
}

void func_8010DD40_duel03(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_801180E8_duel03 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80117460_duel03);
    to = MBDMasuGet(D_80117462_duel03);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010DDF0_duel03(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801180EC_duel03;
        sincosdf(rot, &HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF6C_duel03(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801180EC_duel03 = 10.0f;
    process = omAddPrcObj(func_8010DDF0_duel03, 0xA, 0, 0x40);
    D_80117464_duel03 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801180E8_duel03->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E00C_duel03(void) {
    HmfModel *mdl;

    if (D_80117464_duel03 != NULL) {
        while (D_801180EC_duel03 >= 0.0f) {
            D_801180EC_duel03 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80117464_duel03);
        sincosdf(0.0f, &HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801180E8_duel03->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801180E8_duel03->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117BD8_duel03);

void func_8010E1B8_duel03(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801180E8_duel03->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801180E8_duel03->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801180E8_duel03);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801180E8_duel03->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801180E8_duel03->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2D0_duel03(void) {
    omAddPrcObj(func_8010E1B8_duel03, 0xA, 0, 0);
}

void func_8010E2FC_duel03(void) {
    func_8001C814_main(D_801180E8_duel03->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801180E8_duel03->omObj1->model[0], 1.0f);
}

void func_8010E34C_duel03(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_801180F0_duel03 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80117468_duel03);
    to = MBDMasuGet(D_8011746A_duel03);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010E3FC_duel03(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801180F4_duel03;
        sincosdf(rot, &HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E578_duel03(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801180F4_duel03 = 10.0f;
    process = omAddPrcObj(func_8010E3FC_duel03, 0xA, 0, 0x40);
    D_8011746C_duel03 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801180F0_duel03->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E618_duel03(void) {
    HmfModel *mdl;

    if (D_8011746C_duel03 != NULL) {
        while (D_801180F4_duel03 >= 0.0f) {
            D_801180F4_duel03 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_8011746C_duel03);
        sincosdf(0.0f, &HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801180F0_duel03->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801180F0_duel03->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010E7C4_duel03(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801180F0_duel03->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801180F0_duel03->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801180F0_duel03);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801180F0_duel03->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801180F0_duel03->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8DC_duel03(void) {
    omAddPrcObj(func_8010E7C4_duel03, 0xA, 0, 0);
}

void func_8010E908_duel03(void) {
    func_8001C814_main(D_801180F0_duel03->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801180F0_duel03->omObj1->model[0], 1.0f);
}

// board db2: duel03's own space objects (duel01 has two at other spaces; no twin)
extern Object *D_801180F8_duel03[4]; /* one object per space below */
extern s16 D_80117470_duel03[4]; /* their space ids */

void func_8010E958_duel03(s16 no) {
    s32 models[4] = { 0x40, 0x41, 0x42, 0x43 };
    Object *obj;

    if (D_801180F8_duel03[no] == NULL) {
        obj = func_800D8010_name_81(models[no], NULL);
        func_800D8944_name_81(obj);
        D_801180F8_duel03[no] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBDMasuGet(D_80117470_duel03[no])->coords);
    }
}

void func_8010EA1C_duel03(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_801180F8_duel03[i] = NULL;
        func_8010E958_duel03(i);
    }
}

/* Chance in percent: 10 per star below 5 (the current player's). */
s32 func_8010EA74_duel03(void) {
    return (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
}

s32 func_8010EAAC_duel03(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

s32 func_8010EB54_duel03(s32 no) {
    s16 tbl[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return tbl[no];
}

s32 func_8010EBD4_duel03(void) {
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
                    for (i = 0; D_80117478_duel03[i * 2] != -1; i++) {
                        if (D_80117478_duel03[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    result = D_80117478_duel03[i * 2];
                    break;
                }
            }
            for (i = 0; D_80117574_duel03[player->chr][i].value != -1; i++) {
                if (D_80117574_duel03[player->chr][i].chance > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            result = D_80117574_duel03[player->chr][i].value;
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

// board db2: func_8010EFBC_duel01's twin (same instructions), same residue: retail keeps 64.0f and 3.0f out of
// registers (loop hoisting), frame 8 bytes larger (masked 24)
#ifdef NON_MATCHING
void func_8010EDF0_duel03(void) {
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
        if (D_801175B4_duel03 != 0) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EDF0_duel03);
#endif

void func_8010EF60_duel03(void) {
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
        proc = omAddPrcObj(func_8010EDF0_duel03, 0xA, 0, 0x40);
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
        cpuChoice = func_8010EBD4_duel03();
        if (kind == 2 && cpuChoice != -1) {
            cpuCount = 5;
        }
    } else {
        cpuCount = -1;
    }
    msg = func_800E1824_name_81(0x13, 0xB9, 0);
    D_801175B4_duel03 = 1;
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
    D_801175B4_duel03 = 0;
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
    D_801175AC_duel03 = order[i];
    func_800E1854_name_81(msg);
    if (proc != NULL) {
        omDelPrcObj(proc);
    }
    func_800F4584_name_81(grp);
    func_8005F364_main(win);
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

// board db2: func_8010F99C_duel01's twin (same instructions), same residue: register allocation (the -1, walk
// target and partner/bell registers) and one branch-likely (masked 14)
#ifdef NON_MATCHING
s32 func_8010F7D0_duel03(s32 no) {
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

    start = MBDMasuGet(D_80117594_duel03[no][1]);
    goal = MBDMasuGet(D_80117594_duel03[no][2]);
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
        func_8010DF6C_duel03(&player->player_obj->coords);
    } else {
        func_8010E578_duel03(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_801175AC_duel03 = -1;
    proc = omAddPrcObj(func_8010EF60_duel03, 0xA, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = data;
    *data = no;
    pos = &MBDMasuGet(D_80117594_duel03[no][0])->coords;
    func_800EB708_name_81(&player->player_obj->coords, pos, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&player->player_obj->coords, pos, &player->player_obj->coords, 2.0f));
    HuPrcChildWait();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&dir);
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    if (D_801175AC_duel03 == -1) {
        do {
            HuPrcVSleep();
        } while (D_801175AC_duel03 == -1);
    }
    HuVecCopy3F(&target, &goal->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 2.0f));
    HuPrcChildWait();
    if (no == 0) {
        func_8010E00C_duel03();
    } else {
        func_8010E618_duel03();
    }
    bell = func_800D8010_name_81(0x35, 0);
    func_800D8F0C_name_81(bell);
    partner = func_800F8050_name_81(D_801175AC_duel03);
    HuVecCopy3F(&partner->coords, &goal->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (no == 0) {
        func_8010E2D0_duel03();
    } else {
        func_8010E8DC_duel03();
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
    pos = &MBDMasuGet(D_80117594_duel03[no][1])->coords;
    func_800EB708_name_81(&partner->coords, pos, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, pos, &partner->coords, 20));
    HuPrcChildWait();
    func_800EF800_name_81(partner);
    if (no == 0) {
        func_8010E2FC_duel03();
    } else {
        func_8010E908_duel03();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&cam, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &player->player_obj->coords, &cam, 2.0f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
    D_801175B0_duel03 = partner;
    return D_801175AC_duel03;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C84_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010F7D0_duel03);
#endif

void func_8010FE9C_duel03(s32 no) {
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
    padMask = D_80117CB4_duel03;
    choice = D_80117CB8_duel03;
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
    func_800EDD50_name_81(&MBDMasuGet(D_80117594_duel03[no][0])->coords);
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
        partnerID = func_8010F7D0_duel03(no);
    loop1:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_8010EA74_duel03() >= func_800EFE20_name_81(100.0f)
                || func_8010EB54_duel03(partnerID) >= func_800EFE20_name_81(100.0f)) {
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
            func_801059D0_duel03();
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
            if (player->stats.partners.backID == -1 || func_8010EAAC_duel03() >= func_800EFE20_name_81(100.0f)) {
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
            func_801059D0_duel03();
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
            ofs = D_80117CC0_duel03;
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
        partnerID = func_8010F7D0_duel03(no);
    }
    func_800ECF1C_name_81(no, &frontPos, &backPos);
    func_800ED118_name_81(no, &frontRot, &backRot);
    func_800D918C_name_81(D_801175B0_duel03, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        func_800EF7C8_name_81(D_801175B0_duel03, 2.0f, -0.2f);
    }
    if (result == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_801175B0_duel03->coords, &frontPos, &D_801175B0_duel03->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_801175B0_duel03->coords, &frontPos, &D_801175B0_duel03->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_801175B0_duel03->rot, &frontRot, &D_801175B0_duel03->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_801175B0_duel03->coords, &backPos, &D_801175B0_duel03->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_801175B0_duel03->coords, &backPos, &D_801175B0_duel03->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_801175B0_duel03->rot, &backRot, &D_801175B0_duel03->rot, 7));
    }
    HuPrcChildWait();
    func_800D8F3C_name_81(D_801175B0_duel03);
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

void func_801109B0_duel03(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_8010FE9C_duel03(0);
    }
}

void func_80110A0C_duel03(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_8010FE9C_duel03(1);
    }
}








INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CB4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CB8_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CC0_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CE0_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CE4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117DCC_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117EB4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117F9C_duel03);

// board db2: func_80110C3C_duel01's twin (same instructions), same residue.
#ifdef NON_MATCHING // duel b7: masked 0 but for register allocation: one extra callee-saved register ($s8), so every $s register is one higher
/* Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4
   coins; from the second turn the player pays the partners' upkeep, or loses them when short of coins. */
void func_80110A70_duel03(void) {
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
    padMask = D_80117CB4_duel03;
    choice = D_80117CB8_duel03;
    if (cur == 0 && GwSystem.current_turn == 1 && (*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        DUEL_B7_PICK(win, D_80117CE4_duel03, cur, padMask, choice, buf, front, 1);
        DUEL_B7_PICK(win, D_80117DCC_duel03, cur, padMask, choice, buf, back, 1);
        func_800F8418_name_81(cur, front, 0);
        func_800F8418_name_81(cur, back, 1);
        func_800F8108_name_81(cur);
        func_800ED214_name_81(cur);
        func_800F5BB4_name_81(cur);
        func_800F5EB0_name_81(cur);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(cur);
        }
        DUEL_B7_PICK(win, D_80117EB4_duel03, cur, padMask, choice, buf, front, 0);
        DUEL_B7_PICK(win, D_80117F9C_duel03, cur, padMask, choice, buf, back, 0);
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
                    ofs = D_80117CC0_duel03;
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80110A70_duel03);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80111C30_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011221C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011230C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112348_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801123C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112400_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112480_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801127FC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801129E8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112BD4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011340C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113704_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113740_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113AE0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80114030_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011454C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011485C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80114D80_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801152E0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011580C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80115B18_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116000_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116C54_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116D84_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116EB4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116FE4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80117124_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801171C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80117210_duel03);

void func_8011725C_duel03(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80117264_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801172D4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801173F0_duel03);
