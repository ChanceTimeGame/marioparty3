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
    /* 0x00 */ u16 unk00; /* 0 frozen, 1 walking, 2 falling */
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
    /* 0x40 */ f32 unk40; /* float angle */
    /* 0x44 */ f32 unk44; /* hook scale */
    /* 0x48 */ u16 unk48; /* footstep sound timer */
    /* 0x4A */ u16 unk4A; /* slide sound timer */
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ f32 unk50; /* splash scale */
    /* 0x54 */ u16 unk54; /* splash timer */
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

/* main 20A20.c's collision types (as minigame mgcol.h) */
typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct ColTri {
    /* 0x0 */ s16 flags; /* bits 14-15: vertex count - 2, bits 8-13: surface type */
    /* 0x2 */ s16 v[3];
} ColTri;

typedef struct HitList {
    /* 0x00 */ u16 **list;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 pos;
} HitList;

typedef struct HitProbe {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
} HitProbe;

/* Ground probe around a player (func_80109988_fridged_bridges): 8 points on a circle and the centre */
typedef struct FbGround {
    /* 0x00 */ f32 h[9]; /* ground height, -10000 = none */
    /* 0x24 */ u16 attr[9]; /* surface type (flags & 0x3F00) */
    /* 0x36 */ char unk36[2];
    /* 0x38 */ Vec pos;
} FbGround; // Size 0x44

/* view of the part func_8001D33C_main returns (hmfman.c's unk68 entry: scale at 0x40) */
typedef struct FbHmfPart {
    /* 0x00 */ char unk00[0x40];
    /* 0x40 */ Vec scale;
} FbHmfPart;

double fabs(double); /* the GCC builtin (abs.d) */
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
extern u16 D_8010CFF4_fridged_bridges[];
extern u8 D_800D6A90_main;
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];

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
void func_8010733C_fridged_bridges(omObjData *obj);
void func_80107510_fridged_bridges(omObjData *obj);
void func_80107870_fridged_bridges(void);
void func_80108648_fridged_bridges(omObjData *obj);
void *func_8001D33C_main(s16 model, char *name);
extern char D_8010D2D8_fridged_bridges[];
void func_80109F84_fridged_bridges(omObjData *obj);
void func_8010A1A4_fridged_bridges(omObjData *obj);
void func_8010B8CC_fridged_bridges(omObjData *obj);
void func_8010BFD0_fridged_bridges(s32 type, u16 player, f32 x, f32 y, f32 z);
void func_801079CC_fridged_bridges(omObjData *obj, s8 *stickX, s8 *stickY);
s16 func_80108050_fridged_bridges(omObjData *obj);
void func_801082D0_fridged_bridges(omObjData *obj);
void func_801084E0_fridged_bridges(omObjData *obj);
void func_80108720_fridged_bridges(omObjData *obj);
void func_801091F8_fridged_bridges(omObjData *obj);
void func_80109390_fridged_bridges(omObjData *obj);
u16 func_80109988_fridged_bridges(omObjData *obj, FbGround *g);
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

/* Player object setup: character model, shadow, motions. */
void func_8010648C_fridged_bridges(omObjData *obj, s16 player) {
    FbPlayer *work;
    s8 chr;
    s32 dir;

    work = obj->data = HuMemAllocTag(sizeof(FbPlayer), 0x7918);
    work->unk02 = player;
    work->unk04 = 0;
    work->unk08 = work->unk0C = 0.0f;
    work->unk10 = work->unk14 = 0.0f;
    work->unk1E = func_80108050_fridged_bridges(obj);
    work->unk20 = 1;
    work->unk22 = 1;
    work->unk24 = 0;
    work->unk26 = 0;
    work->unk00 = 1;
    work->unk28 = 0;
    work->unk30 = 0;
    work->unk06 = 0;
    work->unk48 = 0;
    work->unk4A = 0;
    work->unk56 = 0;
    work->unk58 = 0;
    work->unk6A = 0;
    chr = GwPlayer[player].chr;
    dir = D_800A178C_main[chr][0];
    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][1], 0x20699);
    omSetTra(obj, D_8010CFA4_fridged_bridges[player].x, D_8010CFA4_fridged_bridges[player].y,
             D_8010CFA4_fridged_bridges[player].z);
    obj->model[1] = func_8000B0D4_main(9, 0xA89);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    obj->model[2] = func_8000B108_main(0x450011, 0xA9D);
    obj->model[3] = func_8000B108_main(0x450012, 0x69D);
    obj->model[4] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x2068D);
    func_80017790_main(obj->model[4], 2, chr, func_80017B6C_main(chr, 2, 0));
    func_8001C514_main(obj->model[4]);
    obj->model[5] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
    func_8001C8A8_main(obj->model[0], D_8010CF48_fridged_bridges[player]);
    func_8001C8A8_main(obj->model[1], D_8010CF48_fridged_bridges[player]);
    func_8001C8A8_main(obj->model[2], D_8010CF48_fridged_bridges[player]);
    func_8001C8A8_main(obj->model[3], D_8010CF48_fridged_bridges[player]);
    func_8001C8A8_main(obj->model[4], D_8010CF48_fridged_bridges[player]);
    if (player < 2) {
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
    } else {
        omSetRot(obj, 0.0f, 180.0f, 0.0f);
    }
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    if (chr == 5) {
        func_8000B460_main(obj, 3, 0x45000D);
        func_8000B460_main(obj, 7, 0x45000E);
        func_8000B460_main(obj, 8, 0x45000F);
    } else {
        func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x12));
    }
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0xD));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x36));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 3, 2);
    omSetSca(obj, D_8010CFD4_fridged_bridges[chr], D_8010CFD4_fridged_bridges[chr], D_8010CFD4_fridged_bridges[chr]);
    func_8010BE0C_fridged_bridges(obj);
    work->unk5C = obj->trans.x;
    work->unk60 = obj->trans.y;
    work->unk64 = obj->trans.z;
    work->unk68 = 0x100;
    obj->func = func_801068F4_fridged_bridges;
}

/* Player: walk on the ice, fall through holes. */
void func_801068F4_fridged_bridges(omObjData *obj) {
    FbGround g;
    s8 stick[2];
    FbPlayer *work;
    u16 pad;
    f32 mag;
    f32 angle;
    u16 n;

    work = obj->data;
    pad = GwPlayer[work->unk02].pad;
    if (func_800E6E8C_minigame() == 2) {
        if (!(GwPlayer[work->unk02].stat & 1)) {
            stick[0] = D_800CBB6E_main[pad];
            stick[1] = D_800D20A1_main[pad];
        } else {
            func_801079CC_fridged_bridges(obj, &stick[0], &stick[1]);
        }
    } else {
        stick[1] = 0;
        stick[0] = 0;
    }
    if (work->unk58 != 0) {
        if (--work->unk58 == 0) {
            work->unk56 = 0;
        }
    }
    if (work->unk00 == 0) {
        stick[1] = 0;
        stick[0] = 0;
    }
    mag = HuSqrtf(stick[0] * stick[0] + stick[1] * stick[1]) * 0.08f;
    angle = atan2df(stick[0], -stick[1]);
    if (stick[0] != 0 || stick[1] != 0) {
        work->unk10 = sindf(angle) * mag;
        work->unk14 = cosdf(angle) * mag;
        omSetRot(obj, 0.0f, angle, 0.0f);
        if (mag > 2.5f) {
            if (work->unk04 != 2) {
                if (GwPlayer[work->unk02].chr == 5 && work->unk28 == 1) {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[8]].unk02, 0, 6, 2);
                } else {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 6, 2);
                }
                work->unk04 = 2;
                work->unk48 = 0;
            }
            if (work->unk48 == 0) {
                func_8004ACE0_main(0x28, work->unk02);
                work->unk48 = 0xC;
            } else {
                work->unk48--;
            }
        } else {
            if (work->unk04 != 1) {
                if (GwPlayer[work->unk02].chr == 5 && work->unk28 == 1) {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[3]].unk02, 0, 6, 2);
                } else {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, 0, 6, 2);
                }
                work->unk04 = 1;
                work->unk48 = 0;
            }
            if (work->unk48 == 0) {
                func_8004ACE0_main(0x1F, work->unk02);
                work->unk48 = 0x16;
            } else {
                work->unk48--;
            }
        }
        work->unk4A = 0;
    } else {
        work->unk10 = work->unk14 = 0.0f;
        if (work->unk04 != 0) {
            if (GwPlayer[work->unk02].chr == 5 && work->unk28 == 1) {
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[7]].unk02, 0, 6, 2);
            } else {
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 6, 2);
            }
            work->unk04 = 0;
        }
        if (work->unk08 != 0.0f || work->unk0C != 0.0f) {
            if (work->unk4A == 0) {
                func_8004ACE0_main(0xD3, work->unk02);
                work->unk4A = 0xB;
            } else {
                work->unk4A--;
            }
        }
    }
    if (fabs(work->unk08) < 0.1f) {
        work->unk08 = 0.0f;
    }
    if (fabs(work->unk0C) < 0.1f) {
        work->unk0C = 0.0f;
    }
    if (work->unk28 != 0) {
        work->unk10 *= 0.85f;
        work->unk14 *= 0.85f;
    }
    work->unk08 += work->unk10;
    work->unk0C += work->unk14;
    mag = HuSqrtf(work->unk08 * work->unk08 + work->unk0C * work->unk0C);
    if (mag != 0.0f) {
        work->unk08 /= mag;
        work->unk0C /= mag;
        if (mag > 16.0f) {
            mag = 16.0f;
        }
    }
    work->unk08 = mag * work->unk08;
    work->unk0C = mag * work->unk0C;
    if (work->unk00 == 0 || D_8010DA60_fridged_bridges != -1) {
        work->unk08 = work->unk0C = 0.0f;
    }
    if (func_8010A0F4_fridged_bridges(obj, obj->trans.x + work->unk08, obj->trans.y, obj->trans.z + work->unk0C) == 1) {
        if (work->unk28 == 0) {
            func_801082D0_fridged_bridges(obj);
            func_8004AC98_main(0x42D, work->unk02);
            work->unk1E = func_80108050_fridged_bridges(obj);
            work->unk20 = 1;
            work->unk22 = 1;
        }
        work->unk08 = work->unk0C = 0.0f;
    }
    func_8010B7CC_fridged_bridges(obj);
    omSetTra(obj, obj->trans.x + work->unk08, obj->trans.y, obj->trans.z + work->unk0C);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    work->unk08 *= 0.8f;
    work->unk0C *= 0.8f;
    g.pos.x = obj->trans.x;
    g.pos.y = obj->trans.y;
    g.pos.z = obj->trans.z;
    n = func_80109988_fridged_bridges(obj, &g);
    if (g.h[8] != -10000.0f) {
        n = 0;
    }
    if (n >= 6) {
        work->unk00 = 2;
        work->unk34 = sindf(angle) * 10.0f;
        work->unk3C = cosdf(angle) * 10.0f;
        work->unk38 = -1.2f;
        work->unk04 = 0;
        work->unk48 = 0;
        obj->func = func_80107164_fridged_bridges;
        work->unk2C->work[0] = 0;
        func_8001C814_main(obj->model[0], 1, 1);
    }
    if (work->unk1C == D_8010CFF4_fridged_bridges[work->unk24] && work->unk28 == 1) {
        func_801084E0_fridged_bridges(obj);
        if (work->unk24 != 2) {
            work->unk22 = -1;
            work->unk20--;
        }
    } else if (work->unk1C == 0x600) {
        D_8010DA68_fridged_bridges = 1;
        work->unk06 = 1;
    }
    if (work->unk00 != 2) {
        work->unk68 = work->unk1C;
        work->unk5C = obj->trans.x;
        work->unk60 = obj->trans.y;
        work->unk64 = obj->trans.z;
    }
}



void func_80107164_fridged_bridges(omObjData *obj) {
    FbPlayer *work = obj->data;
    f32 scale;

    obj->trans.x += work->unk08;
    obj->trans.y += work->unk38;
    obj->trans.z += work->unk0C;
    func_8010B7CC_fridged_bridges(obj);
    func_80109F84_fridged_bridges(obj);
    work->unk08 *= 0.91f;
    work->unk0C *= 0.91f;
    work->unk38 *= 1.3f;
    if (obj->trans.y <= -150.0f) {
        obj->trans.y = -150.0f;
        omVibrate(work->unk02, 2, 2, 0x14);
        func_8004ACE0_main(0x70, work->unk02);
        func_8010BFD0_fridged_bridges(0, work->unk02, obj->trans.x, -150.0f, obj->trans.z);
        func_8001C258_main(obj->model[1], 4, 4);
        work->unk54 = 0x1D;
        work->unk50 = 0.1f;
        work->unk00 = 3;
        Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelScaleSet(obj->model[3], work->unk50, work->unk50, work->unk50);
        func_8004AC98_main(0x42F, work->unk02);
        obj->func = func_8010733C_fridged_bridges;
        work->unk56 = 0;
        work->unk58 = 0;
        if (D_8010DA68_fridged_bridges == 0) {
            func_8010A1A4_fridged_bridges(obj);
            func_8010B8CC_fridged_bridges(obj);
        }
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, -100.0f, obj->trans.z);
}

void func_8010733C_fridged_bridges(omObjData *obj) {
    FbPlayer *work = obj->data;
    f32 scale;

    if (--work->unk54 != 0) {
        if (work->unk54 & 1) {
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C258_main(obj->model[3], 4, 4);
            if (work->unk28 == 1) {
                func_8001C258_main(D_8010DA70_fridged_bridges->model[work->unk02 * 5], 4, 0);
            }
        } else {
            func_8001C258_main(obj->model[3], 4, 0);
            func_8001C258_main(obj->model[0], 4, 4);
            if (work->unk28 == 1) {
                func_8001C258_main(D_8010DA70_fridged_bridges->model[work->unk02 * 5], 4, 4);
            }
        }
        scale = work->unk50 += 0.03f;
        Hu3DModelScaleSet(obj->model[3], scale, scale, scale);
        return;
    }
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(D_8010DA70_fridged_bridges->model[work->unk02 * 5], 4, 4);
    func_8001C258_main(obj->model[3], 4, 0);
    work->unk40 = 0.0f;
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    obj->func = func_80107510_fridged_bridges;
}

void func_80107510_fridged_bridges(omObjData *obj) {
    FbPlayer *work = obj->data;

    obj->trans.y += sindf(work->unk40);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    work->unk40 += 5.0f;
    if (work->unk40 >= 360.0f) {
        work->unk40 -= 360.0f;
    }
}

void func_801075A4_fridged_bridges(void) {
}

#ifdef NON_MATCHING
void func_801075AC_fridged_bridges(omObjData *obj) {
    f32 rot;
    f32 step;
    f32 diff;

    diff = -obj->rot.y;
    if (diff < 0.0f) {
        diff += 360.0f;
    }
    if (diff < 180.0f) {
        if (diff > 5.0f) {
            rot = obj->rot.y + 5.0f;
        } else {
            rot = diff + obj->rot.y;
        }
    } else {
        step = (360.0f - diff) > 5.0f ? 5.0f : (360.0f - diff);
        rot = obj->rot.y - step;
    }
    obj->rot.y = rot;
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    if (obj->rot.y < 0.0f) {
        obj->rot.y += 360.0f;
    }
    if (obj->rot.y < 0.0001f) {
        obj->work[0] = 1;
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 6, 2);
        obj->func = NULL;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801075AC_fridged_bridges);
#endif

void func_8010775C_fridged_bridges(omObjData *obj) {
    FbPlayer *work = obj->data;
    FbHmfPart *part;

    if (work->unk28 == 1) {
        part = func_8001D33C_main(obj->model[0], D_8010D2D8_fridged_bridges);
        part->scale.x = work->unk44 -= 0.1f;
        part->scale.y = work->unk44;
        part->scale.z = work->unk44;
        if (work->unk44 <= 0.0f) {
            func_8001C258_main(D_8010DA70_fridged_bridges->model[work->unk02 * 5], 0x4004, 4);
            func_80108648_fridged_bridges(obj);
        } else {
            return;
        }
    }
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[6]].unk02, 0, 6, 0);
    obj->func = NULL;
}

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
