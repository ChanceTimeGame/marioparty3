#include "ultra64.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"

/* omObjData::data of a player (func_8010648C_fridged_bridges, 0x6C) */
typedef struct FbPlayer {
    /* 0x00 */ s16 unk00; /* 0 frozen, 1 walking, 2 falling */
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
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ omObjData *unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ f32 unk34; /* fall velocity x */
    /* 0x38 */ f32 unk38; /* fall velocity y */
    /* 0x3C */ f32 unk3C; /* fall velocity z */
    /* 0x40 */ char unk40[8];
    /* 0x48 */ u16 unk48; /* footstep sound timer */
    /* 0x4A */ u16 unk4A; /* slide sound timer */
    /* 0x4C */ char unk4C[0xA];
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ char unk5A[2];
    /* 0x5C */ f32 unk5C; /* last safe x */
    /* 0x60 */ f32 unk60; /* last safe y */
    /* 0x64 */ f32 unk64; /* last safe z */
    /* 0x68 */ u16 unk68; /* last safe tile */
    /* 0x6A */ s16 unk6A;
} FbPlayer; // Size 0x6C

/* Water texture scroll (D_8010D368_fridged_bridges, per player) */
typedef struct FbWaterSize {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
} FbWaterSize;

typedef struct FbUV {
    /* 0x00 */ f32 u;
    /* 0x04 */ f32 v;
} FbUV;

void HmfLightStatSet(s16, u8, u8);
void Hu3DAnimInit(s32);
void *HuMemAllocTag(s32 size, s16 tag);
s16 func_8000B0D4_main(s32, s32);
void func_8000B690_main(s32);
void func_8000B710_main(s32);
s32 func_80017AD8_main(s32);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
s32 func_80017BB8_main(s16, s16);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80020E94_main(void *, struct HmfModel *);
void func_80021BE0_main(s32 *arg0, s32 n);
void func_800335BC_main(char *name, void *size);
void func_80045C2C_main(void);
void func_80047C0C_main(u16 group, u16 max_objs);
omObjData **func_80047DBC_main(s16 arg0);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
void omSetStat(omObjData *obj, u16 stat);

extern f32 D_800CCF98_main[];
extern f32 D_800D4198_main[];
extern s32 D_800EBEB0_minigame[];
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;

extern D_80111B50_vine_with_me_Struct D_8010CF20_fridged_bridges;
extern s16 D_8010CF48_fridged_bridges[4]; /* per player: camera bit */
extern u16 D_8010CF50_fridged_bridges; /* 1 = fade out started */
extern s32 D_8010CF54_fridged_bridges[4];
extern s32 D_8010CF64_fridged_bridges[4];
extern char *D_8010CF94_fridged_bridges[4];
extern Vec D_8010CFA4_fridged_bridges[4]; /* per player: start position */
extern f32 D_8010CFD4_fridged_bridges[]; /* per character: scale */
extern omObjData *D_8010D35C_fridged_bridges;
extern omObjData *D_8010D360_fridged_bridges;
extern s16 D_8010D364_fridged_bridges;
extern s16 D_8010D366_fridged_bridges;
extern FbWaterSize D_8010D368_fridged_bridges[4];
extern FbUV D_8010D378_fridged_bridges[4];
extern s16 D_8010DA60_fridged_bridges; /* winner, -1 = none yet */
extern omObjData **D_8010DA64_fridged_bridges;
extern s16 D_8010DA68_fridged_bridges;
extern omObjData *D_8010DA6C_fridged_bridges;
extern omObjData *D_8010DA70_fridged_bridges;
extern u8 D_8010DA90_fridged_bridges[4][0xC18];

void func_80105F00_fridged_bridges(omObjData *obj);
void func_80105F34_fridged_bridges(omObjData *obj);
void func_801061C4_fridged_bridges(omObjData *obj);
void func_801062F8_fridged_bridges(omObjData *obj);
void func_8010641C_fridged_bridges(omObjData *obj);
void func_80106438_fridged_bridges(omObjData *obj);
void func_80106454_fridged_bridges(omObjData *obj);
void func_80106470_fridged_bridges(omObjData *obj);
void func_8010648C_fridged_bridges(omObjData *obj, s16 player);
void func_801068F4_fridged_bridges(omObjData *obj);
void func_80107164_fridged_bridges(omObjData *obj);
void func_80107870_fridged_bridges(void);
void func_801079CC_fridged_bridges(omObjData *obj, s8 *stickX, s8 *stickY);
s16 func_80108050_fridged_bridges(omObjData *obj);
void func_801082D0_fridged_bridges(omObjData *obj);
void func_801084E0_fridged_bridges(omObjData *obj);
void func_80108720_fridged_bridges(omObjData *obj);
void func_801091F8_fridged_bridges(omObjData *obj);
void func_80109390_fridged_bridges(omObjData *obj);
u16 func_8010A0F4_fridged_bridges(omObjData *obj, f32 x, f32 y, f32 z);
u16 func_8010ADC0_fridged_bridges(void);
void func_8010B164_fridged_bridges(void);
void func_8010B7CC_fridged_bridges(omObjData *obj);
void func_8010BDF0_fridged_bridges(void);
void func_8010BE0C_fridged_bridges(omObjData *obj);
void func_8010BEE8_fridged_bridges(void);
void func_8010C1D8_fridged_bridges(omObjData *obj);

void func_801059A0_fridged_bridges(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(0x3C, 0);
    i = 0;
    func_8004A208_main();
    Hu3DAnimInit(0x10);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_80045C2C_main();
    func_8000B690_main(4);
    func_8000B710_main(4);
    for (; i < 4; i++) {
        CZoomM[i] = 1340.0f;
        CRotM[i].x = -60.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = -320.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = -420.0f;
        D_800CCF98_main[i] = 5000.0f;
        D_800D4198_main[i] = 1000.0f;
        func_80012888_main(i, func_80020E94_main, D_8010DA90_fridged_bridges[i]);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, func_8010C1D8_fridged_bridges);
    obj->work[0] = 4;
    omSetStatBit(obj, 0xA0);
    ScissorSet(0, 1.0f, 1.0f, 159.0f, 119.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 161.0f, 1.0f, 319.0f, 119.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 1.0f, 121.0f, 159.0f, 239.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 161.0f, 121.0f, 319.0f, 239.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 3000.0f);
    Hu3DCamSetPerspective(1, 45.0f, 80.0f, 3000.0f);
    Hu3DCamSetPerspective(2, 45.0f, 80.0f, 3000.0f);
    Hu3DCamSetPerspective(3, 45.0f, 80.0f, 3000.0f);
    func_8001F38C_main(0, 0, 0);
    HmfLightMaxSet(3);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, 3.0f, 89.0f, 80.0f);
    HmfLightStatSet(1, 1, 1);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(3, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105F00_fridged_bridges);
    D_8010DA6C_fridged_bridges = omAddObj(0xA, 8, 0, -1, func_801061C4_fridged_bridges);
    omSetStatBit(D_8010DA6C_fridged_bridges, 0xA0);
    func_800E5EA0_minigame(&D_8010CF20_fridged_bridges);
    D_800EB930_minigame = 0x2E;
    D_800EB932_minigame = 0x1E;
    func_80047C0C_main(0, 4);
    D_8010DA64_fridged_bridges = func_80047DBC_main(0);
    omAddObj(0x14, 6, 9, 0, func_8010641C_fridged_bridges);
    omAddObj(0x14, 6, 9, 0, func_80106438_fridged_bridges);
    omAddObj(0x14, 6, 9, 0, func_80106454_fridged_bridges);
    omAddObj(0x14, 6, 9, 0, func_80106470_fridged_bridges);
    D_8010DA70_fridged_bridges = omAddObj(0x1E, 0x14, 0, -1, func_80108720_fridged_bridges);
    omSetStat(D_8010DA70_fridged_bridges, 0x100);
    func_80107870_fridged_bridges();
    func_8010BEE8_fridged_bridges();
}

void func_80105F00_fridged_bridges(omObjData *obj) {
    D_8010D360_fridged_bridges = NULL;
    D_8010D35C_fridged_bridges = NULL;
    D_8010DA68_fridged_bridges = 0;
    D_8010DA60_fridged_bridges = -1;
    obj->func = func_80105F34_fridged_bridges;
}

/* Game flow: wait for the start, pick a winner, end. */
void func_80105F34_fridged_bridges(omObjData *obj) {
    u16 goal[4];
    u16 n;
    s32 i;

    if (D_8010CF50_fridged_bridges == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010D35C_fridged_bridges == NULL) {
                    D_8010D364_fridged_bridges = 0;
                    D_8010D35C_fridged_bridges = omAddObj(4, 0, 0, -1, func_801091F8_fridged_bridges);
                }
                break;
            case 2:
                if (D_8010DA68_fridged_bridges == 1) {
                    n = 0;
                    if (D_8010DA60_fridged_bridges == -1) {
                        for (i = 0; i < 4; i++) {
                            if (((FbPlayer *)D_8010DA64_fridged_bridges[i]->data)->unk06 == 1) {
                                goal[n++] = i;
                            }
                        }
                        if (n == 1) {
                            D_8010DA60_fridged_bridges = goal[0];
                        } else {
                            D_8010DA60_fridged_bridges = goal[rand8() % n];
                        }
                        D_8010CF20_fridged_bridges.unk18 = D_8010DA60_fridged_bridges;
                    } else if (func_8010ADC0_fridged_bridges() == 1) {
                        func_800E6F0C_minigame(3);
                    }
                } else if (func_800E6E9C_minigame() == 0x1518) {
                    D_8010DA68_fridged_bridges = 1;
                    D_8010CF20_fridged_bridges.unk06 = 4;
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (D_8010D360_fridged_bridges == NULL) {
                    D_8010D360_fridged_bridges = omAddObj(4, 0, 0, -1, func_80109390_fridged_bridges);
                    if (D_8010DA60_fridged_bridges != -1) {
                        D_8010D366_fridged_bridges = 0;
                    } else {
                        D_8010D366_fridged_bridges = 6;
                    }
                }
                break;
            case 1:
            case 4:
                break;
            case 5:
                WipeCreateOut(0, 0x14);
                HuAudSeqFadeOut(0x1E);
                func_8004AB0C_main(0x1E);
                D_8010CF50_fridged_bridges = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010BDF0_fridged_bridges();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D268_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D27C_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D290_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D2A4_fridged_bridges);

/* Water: two scrolling planes per player view. */
void func_801061C4_fridged_bridges(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        obj->model[i] = func_8000B108_main(D_8010CF54_fridged_bridges[i], 0x699);
        obj->model[i + 4] = func_8000B108_main(D_8010CF64_fridged_bridges[i], 0x689);
        func_8001C8A8_main(obj->model[i], D_8010CF48_fridged_bridges[i]);
        func_8001C8A8_main(obj->model[i + 4], D_8010CF48_fridged_bridges[i]);
        D_8010D378_fridged_bridges[i].u = 0.0f;
        D_8010D378_fridged_bridges[i].v = 0.0f;
        func_800335BC_main("sea_01_DEF", &D_8010D368_fridged_bridges[i]);
        func_8001C954_main(obj->model[i + 4]);
    }
    func_8010B164_fridged_bridges();
    obj->func = func_801062F8_fridged_bridges;
}

void func_801062F8_fridged_bridges(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_80049F98_main() + D_800D6A90_main == 0) {
            D_8010D378_fridged_bridges[i].u += 0.1f;
            D_8010D378_fridged_bridges[i].v += 0.1f;
        }
        func_8001E888_main(obj->model[i + 4], D_8010D378_fridged_bridges[i].u, D_8010D378_fridged_bridges[i].v,
                           D_8010D368_fridged_bridges[i].w, D_8010D368_fridged_bridges[i].h,
                           D_8010CF94_fridged_bridges[i], 0);
    }
}

void func_8010641C_fridged_bridges(omObjData *obj) {
    func_8010648C_fridged_bridges(obj, 0);
}

void func_80106438_fridged_bridges(omObjData *obj) {
    func_8010648C_fridged_bridges(obj, 1);
}

void func_80106454_fridged_bridges(omObjData *obj) {
    func_8010648C_fridged_bridges(obj, 2);
}

void func_80106470_fridged_bridges(omObjData *obj) {
    func_8010648C_fridged_bridges(obj, 3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010648C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801068F4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107164_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010733C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107510_fridged_bridges);

void func_801075A4_fridged_bridges(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801075AC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010775C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107870_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D2D8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801079CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108050_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801082D0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801084E0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108648_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108720_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108B08_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108BEC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108C60_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108EBC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108FBC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109154_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801091F8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109390_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109988_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D4C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D6C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109F84_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A0F4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A1A4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A360_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010ADC0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE0C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE98_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B164_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B3EC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B7CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B8CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010BB18_fridged_bridges);
