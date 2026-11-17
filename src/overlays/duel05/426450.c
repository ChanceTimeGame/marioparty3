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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AFC4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B140_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B490_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B4D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B538_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B54C_duel05);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010BCE4_duel05);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EC48_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010ECF0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010ED70_duel05);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F0FC_duel05);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110038_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110B4C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110BA8_duel05);

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
