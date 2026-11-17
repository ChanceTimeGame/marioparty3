#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801059D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105A58_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105B10_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105B64_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105BA0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105C74_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105CD0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105EC0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105F30_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801060E0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010616C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106250_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106270_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801062D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106318_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010646C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801064D8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106750_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801067E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106838_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80107198_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801079C8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80107ECC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801084B4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80108560_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80109414_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80109898_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010A220_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AAC0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AD58_duel05);

// board dc2: declarations for func_8010AFC4_duel05..func_80110038_duel05
#ifndef OVL_81_H_INCLUDED
#define OVL_81_H_INCLUDED
#include "../ovl_81_name/ovl_81.h"
#endif
#include "game/object.h"

/* ovl_81 (prototypes as duel01.h has them) */
SpaceData *MBDMasuGet(s16);
f32 func_800D76D0_name_81(void *);
Object *func_800D8B18_name_81(Object *obj);
void func_800D90D0_name_81(Object *, s16, u16);
Process *func_800DCE40_name_81(s32, Vec *, Vec *, f32);
s32 func_800DD1E0_name_81(s32, char *);
void func_800DD2BC_name_81(s32);
void func_800DD2DC_name_81(s32, Vec *);
s32 func_800DD3B4_name_81(s32);
void func_800EB140_name_81(s32, s32);
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EB7BC_name_81(Vec *out);
void func_800EB804_name_81(Object *);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 frames);
Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
void func_800EF7C8_name_81(Object *, f32, f32);
void func_800EF800_name_81(Object *);
void func_800F3880_name_81(s32, s16, u16);
Process *func_800FAB68_name_81(Object *, s32, s32, s32, s32);
void func_800FAC1C_name_81(Vec *);
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s16, s16);
void func_800FAE98_name_81(Object *, s16, s16, s16, s16);
void func_800FC8DC_name_81(Object *arg0);

/* this unit, outside dc2's range */
void *func_80105EC0_duel05(Object *arg0);
Process *func_801060E0_duel05(GW_PLAYER *player, Object *obj, s32 delay, s32 wait);
void func_8010616C_duel05(Object *obj, Object *target, GW_PLAYER *player, Vec *dest, Vec *start, f32 dist);
void func_80106250_duel05(void);
Process *func_80106270_duel05(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3);
void *func_80106750_duel05(s32 arg0);
void func_801067E4_duel05(Object *arg0, Vec *arg1);
void func_8010AAC0_duel05(Object *obj, s32 create);
void func_8010AD58_duel05(Object *obj);

/* dc2's range */
void func_8010AFC4_duel05(void);
s16 func_8010B490_duel05(void);
void func_8010B4D0_duel05(void);
void func_8010B538_duel05(void);
void func_8010B54C_duel05(void);
void func_8010DF78_duel05(Vec *pos);
void func_8010E018_duel05(void);
void func_8010E2DC_duel05(void);
void func_8010E308_duel05(void);
void func_8010E584_duel05(Vec *pos);
void func_8010E624_duel05(void);
void func_8010E8E8_duel05(void);
void func_8010E914_duel05(void);
void func_8010F0FC_duel05(void);

/* data (still in the asm .data/.bss) */
extern s32 D_801156B0_duel05[]; /* partner attack effect model ids, by level - 1 (read as u8) */
extern char D_80115DC0_duel05[]; /* "obj1" */
extern Object *D_801163B8_duel05;
extern s32 D_80115818_duel05[2][3]; /* per player: three space ids (an undefined_syms alias; splat labels the s16 halves) */
extern s32 D_80115830_duel05;
extern Object *D_80115834_duel05;
extern s32 D_80115838_duel05;
#include "malloc.h"
#include "mallocblock.h"
typedef struct DuelB2SprModel {
    /* 0x00 */ u16 model;
    /* 0x02 */ char unk_02[0x22];
} DuelB2SprModel; // sizeof 0x24
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;
typedef struct Duel01Part {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Duel01Part;
typedef UnkBoard4 Duel01SprGrp; /* ovl_81's sprite group (UnkBoard4 there) */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;
typedef void (*DuelB2PartnerFunc)(s32, s32, Object *, Object *, s32, s32);
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
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
extern DuelB2SprModel *D_800CBB60_main;
extern f32 D_801156CC_duel05;
extern s32 D_801156D0_duel05[];
extern s16 D_801156E0_duel05;
extern s16 D_801156E2_duel05;
extern Process *D_801156E4_duel05;
extern s16 D_801156E8_duel05;
extern s16 D_801156EA_duel05;
extern Process *D_801156EC_duel05;
extern s8 D_801156FC_duel05[]; /* value, chance pairs */
extern Duel01Weight *D_801157F8_duel05[8]; /* per character */
extern event_table_entry D_801158B0_duel05[];
extern event_table_entry D_80115D00_duel05[];
extern char D_80115E78_duel05[];
extern const DuelPadMask D_80115F54_duel05;
extern const DuelChoiceTbl D_80115F58_duel05;
extern const DuelB7VecTbl D_80115F60_duel05; /* smoke puff offsets around a partner leaving */
extern omObjData *D_801163BC_duel05;
extern Object *D_801163C0_duel05;
extern Process *D_801163C4_duel05;
extern Object *D_801163C8_duel05;
extern f32 D_801163CC_duel05;
extern Object *D_801163D0_duel05;
extern f32 D_801163D4_duel05;
void Duel_PowerDownPartners(s32);
u16 func_80014618_main(s16 index, u16 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_80014850_main(s16 index);
void func_80016638_main(s32 index);
void func_800166D0_main(void);
void *func_8001D33C_main(s16, char *);
void func_8002FD8C_main(s16, s16, char *, s16, s16);
Process* func_800D9668_name_81(Object*, f32, f32, s32);
Process *func_800DCE10_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay);
void func_800E0310_name_81(u8 *output, s32 count);
void func_800E14D8_name_81(s32, s32);
void func_800EA46C_name_81(event_table_entry *arg0);
void func_800EA7D4_name_81(void);
void func_800EA97C_name_81(void);
void func_800EB1D8_name_81(s32 arg0, s32 arg1);
void func_800ED118_name_81(s32 playerNo, Vec *front, Vec *back);
Object *func_800EDD50_name_81(Vec *);
void func_800EDDBC_name_81(void);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE0D0_name_81(s32 arg0);
void func_800EE468_name_81(s32);
s32 func_800EED50_name_81(void);
s32 func_800EF7D4_name_81(Object *obj);
void func_800F38DC_name_81(s32, s32, s32);
void func_800F7378_name_81(s32, s32);
void func_800F7BB4_name_81(s32 playerNo, s32 set);
void func_800F7D94_name_81(s32 playerNo, s32 set);
void func_800F821C_name_81(s32 playerIndex, s32 partnerNo);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800FAC94_name_81(DuelB2PartnerFunc *arg0, DuelB2PartnerFunc *arg1);
void func_800FB524_name_81(s32);
void func_800FBDD4_name_81(void);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2); // defined with two parameters in E3CD0.c
void func_800FC59C_name_81(s32 arg0);
void func_800FC5A8_name_81(process_func arg0);
void func_800FF640_name_81(u32 arg0);
void func_801059D0_duel05(void);
Process *func_8010646C_duel05(s32 arg0, s32 arg1);
void func_801064D8_duel05(s32 playerIndex, s32 mode);
void func_80106838_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107198_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801079C8_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107ECC_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801084B4_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80108560_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80109898_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010A220_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010B140_duel05(omObjData *obj);
void func_8010B55C_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010CE78_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010D434_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010DCB8_duel05(void);
void func_8010DD4C_duel05(void);
void func_8010E358_duel05(void);
void func_8010EAFC_duel05(void);
s32 func_8010EB58_duel05(void);
void func_8010EF8C_duel05(void);
s32 func_8010F96C_duel05(s32 no);
void func_801138DC_duel05(void);
s32 func_80115378_duel05(void);
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
extern Dc2HitTimes D_80115DF8_duel05; /* { -1, -1, -1 } */
extern Dc2SpinPrcs D_80115E04_duel05; /* { NULL, NULL, NULL } */
extern Dc2PartnerFuncs D_80115E10_duel05; /* partner attacks by partner id */
extern Dc2PartnerFuncs D_80115E40_duel05; /* second table: only [4] set */
#ifndef B1_MODEL_ROTY
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

#endif

void func_8010AFC4_duel05(void) {
    DuelB2Puffs *puffs;
    void *data;
    s32 i;

    func_800142A0_main(0x1A);
    D_801163BC_duel05 = omAddObj(0x1F4, 0, 0, -1, func_8010B140_duel05);
    puffs = D_801163BC_duel05->data = HuMemAllocTag(sizeof(DuelB2Puffs), 0x7918);
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
    D_801163BC_duel05->work[0] = 0;
    puffs->delay = 0;
}

void func_8010B140_duel05(omObjData *obj) {
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
                puffs->vel[i].x = D_801163B8_duel05->rot.x;
                puffs->vel[i].y = -0.8f;
                puffs->vel[i].z = D_801163B8_duel05->rot.z;
                func_800D7828_name_81(&puffs->vel[i]);
                puffs->vel[i].x = 2.0f * puffs->vel[i].x;
                puffs->vel[i].y = 2.0f * puffs->vel[i].y;
                puffs->vel[i].z = 2.0f * puffs->vel[i].z;
                puffs->pos[i].x = D_801163B8_duel05->rot.x * 10.0f + D_801163B8_duel05->coords.x;
                puffs->pos[i].z = D_801163B8_duel05->rot.z * 10.0f + D_801163B8_duel05->coords.z;
                puffs->pos[i].y = D_801163B8_duel05->coords.y + 6.0f;
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

s16 func_8010B490_duel05(void) {
    DuelB2Puffs *puffs = D_801163BC_duel05->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4D0_duel05(void) {
    DuelB2Puffs *puffs = D_801163BC_duel05->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        func_80016638_main(puffs->spr[i]);
    }
    omDelObj(D_801163BC_duel05);
    func_800166D0_main();
}

void func_8010B538_duel05(void) {
    D_801163BC_duel05->work[0] = 1;
}

void func_8010B54C_duel05(void) {
    D_801163BC_duel05->work[0] = 0;
}

#ifdef NON_MATCHING
// duel b2: masked 78 of 649: func_800EB708 is called through a correctly typed local pointer (duel01.h has it wrong) and GCC keeps it in $s8 (jalr), which shifts the allocation; logic checked block by block.
void func_8010B55C_duel05(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        obj = func_800D8010_name_81(D_801156B0_duel05[variant - 1], 0);
        func_8001C8E4_main(obj->omObj1->model[0], 0);
        func_8001C448_main(obj->omObj1->model[0]);
        func_800D8944_name_81(obj);
        func_800D8F0C_name_81(obj);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AAC0_duel05(partner, 1);
        HuAudFXPlay(0x29C);
        func_800D90D0_name_81(D_801163B8_duel05, 0, 2);
        HuVecCopy3F(&sp28, &D_801163B8_duel05->coords);
        HuVecCopy3F(&sp48, &D_801163B8_duel05->rot);
        HuVecCopy3F(&sp18, (target != NULL) ? &target->coords : &player->player_obj->coords);
        func_800EB708_name_81(&D_801163B8_duel05->coords, &sp18, &D_801163B8_duel05->rot);
        angle = func_800D76D0_name_81(&D_801163B8_duel05->rot) + 180.0f;
        if (variant == 1) {
            speed = 2.5f;
        } else {
            speed = 3.0f;
        }
        offset.x = sindf(angle) * 6.0f * speed;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 6.0f * speed;
        HuVecAdd(&sp18, &sp18, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&D_801163B8_duel05->coords, &sp18, &D_801163B8_duel05->coords, 0.5f));
        func_80106250_duel05();
        func_80106270_duel05(target, player, flags, 0.8f);
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &D_801163B8_duel05->coords);
        func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 0.5f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 1) {
            func_800D90D0_name_81(D_801163B8_duel05, 3, 0);
            if (flags & 8) {
                func_801060E0_duel05(player, target, 0, 0x32);
            } else {
                HuPrcSleep(8);
                HuVecAdd(&sp58, (flags & 1) ? &target->coords : &player->player_obj->coords, &D_801163B8_duel05->coords);
                HuVecMulScalar(&sp58, 0.5f, &sp58);
                sp58.y += 5.0f;
                effect = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
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
            func_800EFABC_name_81(D_801163B8_duel05);
            func_800D90D0_name_81(D_801163B8_duel05, -1, 2);
            HuPrcSleep(0x14);
        } else {
            func_800D90D0_name_81(D_801163B8_duel05, 1, 0);
            HuPrcSleep(0x1E);
            func_8010AFC4_duel05();
            func_8010B538_duel05();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                func_801060E0_duel05(player, target, 0, 0x32);
            }
            func_800EFABC_name_81(D_801163B8_duel05);
            func_800D90D0_name_81(D_801163B8_duel05, 2, 2);
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
            func_8010B54C_duel05();
            while (func_8010B490_duel05() != 0) {
                HuPrcVSleep();
            }
            func_800D918C_name_81(D_801163B8_duel05, -1, 0, 5, 2);
            HuPrcSleep(0xA);
            func_8010B4D0_duel05();
        }
        func_8010AD58_duel05(partner);
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
        func_8010AAC0_duel05(partner, 0);
        HuAudFXPlay(0x2A0);
        func_80105EC0_duel05(partner);
        HuPrcSleep(0xA);
        func_800FAE18_name_81(partner, 1, 0);
        func_800EFABC_name_81(partner);
        func_800D90D0_name_81(partner, -1, 2);
    }
    func_800FADB4_name_81();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B55C_duel05);
#endif

void func_8010BCE4_duel05(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    Process *process = HuPrcCurrentGet();
    Object *front = NULL;
    Object *back = NULL;
    s32 frontNo = -1;
    s32 backNo = -1;
    Dc2HitTimes hitTime = D_80115DF8_duel05;
    Dc2SpinPrcs spinPrc = D_80115E04_duel05;
    Vec pos;
    Object *obj;
    HmfModel *mdl;
    s32 i;
    f32 scale;
    f32 amp;

    func_800FAD04_name_81(8);
    obj = func_800D8010_name_81(D_801156B0_duel05[variant - 1] & 0xFF, 0);
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
    func_80106250_duel05();
    func_80106270_duel05(target, player, 0, 7.0f);
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
        func_801064D8_duel05(playerNo, 0);
        func_800EF800_name_81(partner);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, func_8010646C_duel05(10, 1));
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
        func_801064D8_duel05(playerNo, 1);
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
void func_8010CE78_duel05(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra1 = func_80106750_duel05(0x4C);
        HuPrcVSleep();
        extra2 = func_80106750_duel05(0x53);
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
    func_80106250_duel05();
    func_800D8E88_name_81(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, func_80106270_duel05(target, player, flags, 4.0f));
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
        func_801060E0_duel05(player, target, 0, 0x14);
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
            func_801067E4_duel05(extra1, &sp28);
            HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
            func_801067E4_duel05(extra2, &sp28);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010CE78_duel05);
#endif

#ifdef NON_MATCHING
// duel b2: masked 0, raw 28: partner and obj swap s3/s4.
void func_8010D434_duel05(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
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
        extra = func_80106750_duel05(0x45);
    }
    obj = func_800D8010_name_81(D_801156B0_duel05[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010616C_duel05(partner, target, player, &sp18, &sp28, 7.5f);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
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
        func_801060E0_duel05(player, target, 0, 0x1E);
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
            func_801067E4_duel05(extra, &sp38);
        } else {
            effect = func_800DD1E0_name_81(0xB0024, D_80115DC0_duel05);
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010D434_duel05);
#endif

void func_8010D96C_duel05(void) {
    Dc2PartnerFuncs funcs1 = D_80115E10_duel05;
    Dc2PartnerFuncs funcs2 = D_80115E40_duel05;

    func_800FAC94_name_81(funcs1.f, funcs2.f);
}

void func_8010DA04_duel05(void) {
    omInitObjMan(0xA0, 0x50);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_800FC260_name_81(0x1C, 0x245, 0);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    func_8010DCB8_duel05();
    func_8010DD4C_duel05();
    func_8010E358_duel05();
    func_8010EAFC_duel05();
    func_8010D96C_duel05();
}

void func_8010DA94_duel05(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010DA04_duel05();
    func_800EA46C_name_81(D_801158B0_duel05);
    func_800EA46C_name_81(D_80115D00_duel05);
    func_800FC5A8_name_81(func_801138DC_duel05);
    func_800FC59C_name_81((s32)func_80115378_duel05);
    func_800FF640_name_81(0);
}

void func_8010DB10_duel05(void) {
    Hu3DCamInit(1);
    func_8010DA04_duel05();
    func_800FF640_name_81(1);
}

void func_8010DB3C_duel05(void) {
    DuelB2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], HmfModelData[D_801163C0_duel05->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], "neji");
        angle += D_801156CC_duel05;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->rotY = angle;
        HuPrcVSleep();
    }
}

void func_8010DC14_duel05(void) {
    s16 model = D_801163C0_duel05->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80115E78_duel05, 0x4C, 0x46);
    ((Duel01Part *)func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], D_80115E78_duel05))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010DCB8_duel05(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_801156D0_duel05);
    func_800D8944_name_81(obj);
    D_801163C0_duel05 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x23)->coords);
    func_8010DC14_duel05();
    D_801163C4_duel05 = omAddPrcObj(func_8010DB3C_duel05, 0xA, 0, 0);
    omPrcSetStatBit(D_801163C4_duel05, 0xA0);
}

void func_8010DD4C_duel05(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_801163C8_duel05 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_801156E0_duel05);
    to = MBDMasuGet(D_801156E2_duel05);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010DDFC_duel05(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801163CC_duel05;
        sincosdf(rot, &HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF78_duel05(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801163CC_duel05 = 10.0f;
    process = omAddPrcObj(func_8010DDFC_duel05, 0xA, 0, 0x40);
    D_801156E4_duel05 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801163C8_duel05->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E018_duel05(void) {
    HmfModel *mdl;

    if (D_801156E4_duel05 != NULL) {
        while (D_801163CC_duel05 >= 0.0f) {
            D_801163CC_duel05 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801156E4_duel05);
        sincosdf(0.0f, &HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801163C8_duel05->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801163C8_duel05->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115E78_duel05);

void func_8010E1C4_duel05(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801163C8_duel05->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801163C8_duel05->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801163C8_duel05);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801163C8_duel05->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801163C8_duel05->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2DC_duel05(void) {
    omAddPrcObj(func_8010E1C4_duel05, 0xA, 0, 0);
}

void func_8010E308_duel05(void) {
    func_8001C814_main(D_801163C8_duel05->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801163C8_duel05->omObj1->model[0], 1.0f);
}

void func_8010E358_duel05(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_801163D0_duel05 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_801156E8_duel05);
    to = MBDMasuGet(D_801156EA_duel05);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010E408_duel05(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801163D4_duel05;
        sincosdf(rot, &HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E584_duel05(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801163D4_duel05 = 10.0f;
    process = omAddPrcObj(func_8010E408_duel05, 0xA, 0, 0x40);
    D_801156EC_duel05 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801163D0_duel05->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E624_duel05(void) {
    HmfModel *mdl;

    if (D_801156EC_duel05 != NULL) {
        while (D_801163D4_duel05 >= 0.0f) {
            D_801163D4_duel05 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801156EC_duel05);
        sincosdf(0.0f, &HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801163D0_duel05->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801163D0_duel05->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010E7D0_duel05(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801163D0_duel05->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801163D0_duel05->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801163D0_duel05);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801163D0_duel05->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801163D0_duel05->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8E8_duel05(void) {
    omAddPrcObj(func_8010E7D0_duel05, 0xA, 0, 0);
}

void func_8010E914_duel05(void) {
    func_8001C814_main(D_801163D0_duel05->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801163D0_duel05->omObj1->model[0], 1.0f);
}

void func_8010E964_duel05(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EA00_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EAFC_duel05);

#ifdef NON_MATCHING
s32 func_8010EB58_duel05(void) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EB58_duel05);
#endif

s32 func_8010EC48_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

s32 func_8010ECF0_duel05(s32 no) {
    s16 tbl[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return tbl[no];
}

s32 func_8010ED70_duel05(void) {
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
                    for (i = 0; D_801156FC_duel05[i * 2] != -1; i++) {
                        if (D_801156FC_duel05[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    result = D_801156FC_duel05[i * 2];
                    break;
                }
            }
            for (i = 0; D_801157F8_duel05[player->chr][i].value != -1; i++) {
                if (D_801157F8_duel05[player->chr][i].chance > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            result = D_801157F8_duel05[player->chr][i].value;
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
void func_8010EF8C_duel05(void) {
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
        if (D_80115838_duel05 != 0) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EF8C_duel05);
#endif

void func_8010F0FC_duel05(void) {
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
        proc = omAddPrcObj(func_8010EF8C_duel05, 0xA, 0, 0x40);
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
        cpuChoice = func_8010ED70_duel05();
        if (kind == 2 && cpuChoice != -1) {
            cpuCount = 5;
        }
    } else {
        cpuCount = -1;
    }
    msg = func_800E1824_name_81(0x13, 0xB9, 0);
    D_80115838_duel05 = 1;
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
    D_80115838_duel05 = 0;
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
    D_80115830_duel05 = order[i];
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
s32 func_8010F96C_duel05(s32 no) {
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

    start = MBDMasuGet(D_80115818_duel05[no][1]);
    goal = MBDMasuGet(D_80115818_duel05[no][2]);
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
        func_8010DF78_duel05(&player->player_obj->coords);
    } else {
        func_8010E584_duel05(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_80115830_duel05 = -1;
    proc = omAddPrcObj(func_8010F0FC_duel05, 0xA, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = data;
    *data = no;
    pos = &MBDMasuGet(D_80115818_duel05[no][0])->coords;
    func_800EB708_name_81(&player->player_obj->coords, pos, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&player->player_obj->coords, pos, &player->player_obj->coords, 2.0f));
    HuPrcChildWait();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&dir);
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    if (D_80115830_duel05 == -1) {
        do {
            HuPrcVSleep();
        } while (D_80115830_duel05 == -1);
    }
    HuVecCopy3F(&target, &goal->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 2.0f));
    HuPrcChildWait();
    if (no == 0) {
        func_8010E018_duel05();
    } else {
        func_8010E624_duel05();
    }
    bell = func_800D8010_name_81(0x35, 0);
    func_800D8F0C_name_81(bell);
    partner = func_800F8050_name_81(D_80115830_duel05);
    HuVecCopy3F(&partner->coords, &goal->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (no == 0) {
        func_8010E2DC_duel05();
    } else {
        func_8010E8E8_duel05();
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
    pos = &MBDMasuGet(D_80115818_duel05[no][1])->coords;
    func_800EB708_name_81(&partner->coords, pos, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, pos, &partner->coords, 20));
    HuPrcChildWait();
    func_800EF800_name_81(partner);
    if (no == 0) {
        func_8010E308_duel05();
    } else {
        func_8010E914_duel05();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&cam, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &player->player_obj->coords, &cam, 2.0f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
    D_80115834_duel05 = partner;
    return D_80115830_duel05;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F96C_duel05);
#endif

void func_80110038_duel05(s32 no) {
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
    padMask = D_80115F54_duel05;
    choice = D_80115F58_duel05;
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
    func_800EDD50_name_81(&MBDMasuGet(D_80115818_duel05[no][0])->coords);
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
        partnerID = func_8010F96C_duel05(no);
    loop1:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_8010EB58_duel05() >= func_800EFE20_name_81(100.0f)
                || func_8010ECF0_duel05(partnerID) >= func_800EFE20_name_81(100.0f)) {
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
            func_801059D0_duel05();
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
            if (player->stats.partners.backID == -1 || func_8010EC48_duel05() >= func_800EFE20_name_81(100.0f)) {
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
            func_801059D0_duel05();
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
            ofs = D_80115F60_duel05;
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
        partnerID = func_8010F96C_duel05(no);
    }
    func_800ECF1C_name_81(no, &frontPos, &backPos);
    func_800ED118_name_81(no, &frontRot, &backRot);
    func_800D918C_name_81(D_80115834_duel05, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        func_800EF7C8_name_81(D_80115834_duel05, 2.0f, -0.2f);
    }
    if (result == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_80115834_duel05->coords, &frontPos, &D_80115834_duel05->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80115834_duel05->coords, &frontPos, &D_80115834_duel05->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80115834_duel05->rot, &frontRot, &D_80115834_duel05->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_80115834_duel05->coords, &backPos, &D_80115834_duel05->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80115834_duel05->coords, &backPos, &D_80115834_duel05->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80115834_duel05->rot, &backRot, &D_80115834_duel05->rot, 7));
    }
    HuPrcChildWait();
    func_800D8F3C_name_81(D_80115834_duel05);
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110B4C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110BA8_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F24_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F54_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F58_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F60_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F80_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F84_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011606C_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80116154_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011623C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110C0C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80111DCC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801123B8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801124A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801124E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112560_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011259C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011261C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112998_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112B84_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112D70_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801135A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801138A0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801138DC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80113C7C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114428_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114BD4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114D24_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114E74_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114E98_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114EBC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114F10_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114F68_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114FD8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011505C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115098_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801150D4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115120_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011514C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115198_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801151E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115230_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011525C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801152A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801152F4_duel05);

void func_80115370_duel05(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115378_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801153E8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011541C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011544C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115468_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115550_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011566C_duel05);
