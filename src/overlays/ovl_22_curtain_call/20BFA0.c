#include "common.h"
// m3 cu: Curtain Call (four players)
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/window.h"
#include "game/wipe.h"

/* One slot of the overlay's object table (D_8010B4B0_curtain_call, 50 x 0x84):
 * [0] the stage object, [1..4] the players, ... */
typedef struct CcEnt {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec scale;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} CcEnt; // Size 0x84

/* A camera (D_8010B280_curtain_call). */
typedef struct CcCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} CcCamera; // Size 0x2C

extern s16 D_800CDA7C_main[];
extern s32 D_800A178C_main[][6];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;
extern u8 D_800D6A58_main;
extern u8 D_800D6A90_main;

void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8004AB0C_main(s32);
void func_8004AD8C_main(s16);
void func_80045010_main(const s16 *, s32);
s32 func_80017BB8_main(s16, s16);
void func_80088800_main(HuMtx4F mf, f32 x, f32 y, f32 z);

/* .rodata: the players' animation names */
extern const char D_8010B32C_curtain_call[];
extern const char D_8010B338_curtain_call[];
extern const char D_8010B344_curtain_call[];
extern const char D_8010B350_curtain_call[];
extern const char D_8010B35C_curtain_call[];
extern const char D_8010B368_curtain_call[];
extern const char D_8010B374_curtain_call[];
extern const char D_8010B380_curtain_call[];

/* .data */
/* sound bank per character (func_80045ED0_main) */
s32 D_8010B0C0_curtain_call[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
/* host's messages (func_801062EC_curtain_call) */
s16 D_8010B0E0_curtain_call[2] = { 0x6300, 0x6301 };
s16 D_8010B0E4_curtain_call[6] = { 0x6302, 0x6303, 0x6304, 0x6305, 0x6306, 0x6307 };
/* per character: the three animation files (0 at the start, 1 win, 2 lose) */
u16 D_8010B0F0_curtain_call[8][3] = {
    { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0x1A, 0x1C, 0x1D },
};
char *D_8010B120_curtain_call[8] = {
    (char *)D_8010B380_curtain_call, (char *)D_8010B374_curtain_call,
    (char *)D_8010B368_curtain_call, (char *)D_8010B35C_curtain_call,
    (char *)D_8010B350_curtain_call, (char *)D_8010B344_curtain_call,
    (char *)D_8010B338_curtain_call, (char *)D_8010B32C_curtain_call,
};
/* CPU plan thresholds (of 100) by difficulty, then round */
u8 D_8010B140_curtain_call[3][5] = { { 13, 20, 33, 40, 74 }, { 10, 20, 30, 40, 70 }, { 7, 20, 27, 40, 66 } };
u8 D_8010B150_curtain_call[3][5] = { { 18, 25, 43, 50, 84 }, { 15, 25, 40, 50, 80 }, { 12, 25, 37, 50, 76 } };
u8 D_8010B160_curtain_call[3][5] = { { 44, 50, 73, 80, 93 }, { 40, 50, 70, 80, 90 }, { 36, 50, 67, 80, 87 } };
u8 D_8010B170_curtain_call[3][5] = { { 74, 80, 88, 90, 98 }, { 70, 80, 85, 90, 95 }, { 66, 80, 82, 90, 92 } };
/* curtain panel rise per frame, and its x/z scale */
s8 D_8010B180_curtain_call[25] = { 0, 0, 0, 0, 16, 14, 12, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -12, -14, -16, 0, 0, 0, 0 };
f32 D_8010B19C_curtain_call[25] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.7f, 0.65f, 0.6f,
    0.65f, 0.7f, 0.75f, 0.8f, 0.85f, 0.9f, 0.95f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
};
/* sound by the winning curtain */
s16 D_8010B200_curtain_call[3] = { 0x259, 0x25B, 0x257 };
/* panel x by slot, per round (3, 5 and 6 curtains) */
s16 D_8010B208_curtain_call[3] = { 150, 0, -150 };
s16 D_8010B210_curtain_call[5] = { 300, 150, 0, -150, -300 };
s16 D_8010B21C_curtain_call[6] = { 310, 185, 60, -60, -185, -310 };
/* the host's offset in front of each slot, per round */
s8 D_8010B228_curtain_call[3] = { -8, 0, 8 };
s8 D_8010B22C_curtain_call[5] = { -16, -8, 0, 8, 16 };
s8 D_8010B234_curtain_call[6] = { -18, -10, -3, 3, 10, 18 };
/* panel x while dealt, by slot */
s16 D_8010B23C_curtain_call[6] = { -525, -655, -785, -915, -1045, -1175 };
/* round 1: the three permutations of the winning slots */
u8 D_8010B248_curtain_call[6][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 } };
/* shuffle speeds per pattern, rounds 2 and 3 */
s8 D_8010B25C_curtain_call[3][3] = { { 4, 4, 8 }, { 4, 8, 4 }, { 8, 4, 4 } };
s8 D_8010B268_curtain_call[6][4] = {
    { 8, 8, -4, 4 }, { 8, -4, 8, 4 }, { 4, -4, 8, 8 }, { 4, 8, -4, 8 }, { 8, -4, 4, 8 }, { 8, 4, -4, 8 },
};
CcCamera D_8010B280_curtain_call[1] = {
    { { 0.0f, 0.0f, 320.0f, 240.0f }, { 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f }, 21.0f },
};
/* .rodata */
extern const s16 D_8010B4A0_curtain_call[];
/* .bss */
extern CcEnt D_8010B4B0_curtain_call[50];
/* entity [0]'s grp, spr and pos under their own labels */
extern s16 D_8010B4F0_curtain_call;
extern s16 D_8010B4F2_curtain_call;
extern f32 D_8010B4F4_curtain_call;
extern f32 D_8010B4F8_curtain_call;
extern f32 D_8010B4FC_curtain_call;
extern s16 D_8010CE78_curtain_call[4];
extern s8 D_8010CE80_curtain_call[4];
extern s16 D_8010CE84_curtain_call;
extern s8 D_8010CE86_curtain_call;
extern s16 D_8010CE88_curtain_call;
extern s8 D_8010CE8A_curtain_call[2];
extern void *D_8010CE90_curtain_call[4][3];
extern s8 D_8010CEC0_curtain_call;
extern s8 D_8010CEC1_curtain_call;
/* a curtain panel (D_8010CEC8_curtain_call, 6) */
typedef struct CcPanel {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 slot;
    /* 0x04 */ omObjData *obj;
} CcPanel; // Size 0x8
extern CcPanel D_8010CEC8_curtain_call[6];
extern s8 D_8010CEF8_curtain_call[4];
extern s16 D_8010CEFC_curtain_call;
extern s8 D_8010CEFE_curtain_call;
extern s8 D_8010CEFF_curtain_call;
extern s8 D_8010CF00_curtain_call;
extern s8 D_8010CF01_curtain_call;
/* the CPU's planned press and release frames, per player */
typedef struct CcCpuPlan {
    /* 0x00 */ s16 press;
    /* 0x02 */ s16 release;
} CcCpuPlan;
extern CcCpuPlan D_8010CF08_curtain_call[4];
extern s8 D_8010CF18_curtain_call[4];
extern s16 D_8010CF1C_curtain_call[2];
extern s8 D_8010CF20_curtain_call[2];
extern s8 D_8010CF22_curtain_call;
/* player 0's shared models (stage, curtain front and back) for the others to link */
extern omObjData *D_8010CF24_curtain_call;
extern s8 D_8010CF28_curtain_call[4];
extern s16 D_8010CF2C_curtain_call[3];
extern s8 D_8010CF32_curtain_call;
extern s8 D_8010CF33_curtain_call;
extern Process *D_8010CF34_curtain_call;
extern s8 D_8010CF38_curtain_call;

#define CC_PLAYER(i) (&D_8010B4B0_curtain_call[(i) + 1])

void func_801059A0_curtain_call(void);
f32 func_801059BC_curtain_call(f32 angle, f32 add);
void func_80105A3C_curtain_call(void);
void func_80105B04_curtain_call(s32 player);
s32 func_80105B7C_curtain_call(s32 n);
void func_80105BD0_curtain_call(omObjData *obj, u16 motion, s16 arg2);
void func_80105C3C_curtain_call(omObjData *obj, u16 motion, s16 arg2, s16 arg3, s16 arg4);
s8 func_80105CB8_curtain_call(omObjData *obj, f32 target);
void func_80105D14_curtain_call(s32 conNo);
void func_801062EC_curtain_call(void);
void func_80106408_curtain_call(void);
void func_8010644C_curtain_call(void);
void func_80106494_curtain_call(void);
void func_801064A0_curtain_call(omObjData *obj);
void func_80106500_curtain_call(omObjData *obj);
void func_80106688_curtain_call(void);
void func_801066C4_curtain_call(omObjData *obj, u8 anim);
s8 func_801067A8_curtain_call(omObjData *obj, s8 mode);
void func_80106988_curtain_call(omObjData *obj, s8 motion);
void func_80106AB4_curtain_call(omObjData *obj);
void func_80106B78_curtain_call(omObjData *obj);
void func_80106C18_curtain_call(omObjData *obj);
void func_80107560_curtain_call(omObjData *obj);
void func_80107680_curtain_call(omObjData *obj);
void func_80107D20_curtain_call(omObjData *obj);
void func_801084A0_curtain_call(void);
void func_80108670_curtain_call(omObjData *obj);
void func_801089FC_curtain_call(omObjData *obj);
void func_80108E64_curtain_call(void);
void func_80108EF8_curtain_call(omObjData *obj);
void func_80108F28_curtain_call(omObjData *obj);
void func_801090FC_curtain_call(void);
void func_80109138_curtain_call(omObjData *obj);
void func_801092F0_curtain_call(omObjData *obj);
void func_801093C4_curtain_call(void);
void func_80109400_curtain_call(void);
void func_8010954C_curtain_call(void);
void func_8010982C_curtain_call(void);
void func_80109920_curtain_call(void);
void func_80109AD0_curtain_call(void);
void func_8010A734_curtain_call(void);
void func_8010A7D8_curtain_call(omObjData *obj);
void func_8010A7FC_curtain_call(omObjData *obj);
void func_8010A8E8_curtain_call(omObjData *obj);
void func_8010A948_curtain_call(omObjData *obj);
void func_8010AD68_curtain_call(omObjData *obj);
void func_8010AE00_curtain_call(void);
void func_8010AE08_curtain_call(void);
void func_8010AF78_curtain_call(void);

void func_801059A0_curtain_call(void) {
    func_8010AF78_curtain_call();
}

f32 func_801059BC_curtain_call(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_curtain_call(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010B4B0_curtain_call; i < 50; i++, ent++) {
        ent->obj = NULL;
        ent->unk04 = 0;
        ent->unk06 = 0;
        ent->unk08 = 0;
        ent->unk0A = 0;
        ent->unk0C = 0;
        ent->unk0E = 0;
        ent->unk10 = 0;
        ent->unk12 = 0;
        ent->unk14 = 0;
        ent->unk16 = 0;
        ent->unk18 = 0;
        ent->unk1C = 0;
        ent->unk20 = 0;
        ent->unk24 = 0;
        ent->unk28 = 0;
        ent->unk2C = 0;
        ent->unk30 = 0;
        ent->unk34 = 0;
        ent->unk38 = 0;
        ent->unk3C = 0;
        ent->grp = -1;
        ent->spr = -1;
        ent->pos.x = ent->pos.y = ent->pos.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->scale.x = ent->scale.y = ent->scale.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105B04_curtain_call(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

s32 func_80105B7C_curtain_call(s32 n) {
    return rand8() % n;
}

void func_80105BD0_curtain_call(omObjData *obj, u16 motion, s16 arg2) {
    if (motion < 10) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], arg2, arg2);
    }
}

void func_80105C3C_curtain_call(omObjData *obj, u16 motion, s16 arg2, s16 arg3, s16 arg4) {
    if (motion < 10) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, arg2, arg3, arg4);
    }
}

#ifdef NON_MATCHING
s8 func_80105CB8_curtain_call(omObjData *obj, f32 target) {
    s32 ret = 0;

    if (obj->rot.y != target) {
        obj->rot.y = func_801059BC_curtain_call(obj->rot.y, 10.0f);
        ret = 1;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105CB8_curtain_call);
#endif

#ifdef NON_MATCHING
void func_80105D14_curtain_call(s32 conNo) {
    s16 i;

    if ((u16)conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x400) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_curtain_call(CRotM[i].x, 1.0f);
        }
    }
    /* retail reads player 0's pad here, not conNo's */
    if (D_800CDA7C_main[GwPlayer[0].pad] & 0x800) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_curtain_call(CRotM[i].x, -1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x200) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_curtain_call(CRotM[i].y, 1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x100) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_curtain_call(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[(s16)conNo] & 0x8000) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x4000) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 2) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 1) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 8) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 4) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if (D_800D5558_main[(s16)conNo] & 0x2000) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105D14_curtain_call);
#endif

void func_801062EC_curtain_call(void) {
    s16 win;

    win = func_80060880_main(0xAF, 0x5C, 10);
    func_80060C14_main(win, 1);
    func_8005B6BC_main(win, D_8010B0E4_curtain_call[D_8010CE8A_curtain_call[1]], 0);
    func_8005B43C_main(win, D_8010B0E0_curtain_call[D_8010CE8A_curtain_call[0]], -1, -1);
    while (1) {
        if (func_8005E0C0_main(win) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    while (1) {
        if (D_8010CEC1_curtain_call == 4) {
            break;
        }
        HuPrcVSleep();
    }
    func_80060EA8_main(win, 1);
    func_800610E0_main(win);
    func_8005F524_main();
    while (1) {
        HuPrcVSleep();
    }
}

void func_80106408_curtain_call(void) {
    D_800D6A58_main = 1;
    func_8005A6B0_main();
    D_8010CF34_curtain_call = omAddPrcObj(func_801062EC_curtain_call, 0x3F00, 0x800, 0);
}

void func_8010644C_curtain_call(void) {
    if (D_8010CF34_curtain_call != NULL) {
        func_8005F524_main();
        while (omDelPrcObj(D_8010CF34_curtain_call) != 0) {
        }
        D_8010CF34_curtain_call = NULL;
    }
}

void func_80106494_curtain_call(void) {
    D_800D6A58_main = 0;
}

void func_801064A0_curtain_call(omObjData *obj) {
    switch (D_8010CEC1_curtain_call) {
    case 3:
        func_8001C258_main(obj->model[2], 4, 4);
        break;
    case 5:
        func_8001C258_main(obj->model[2], 4, 0);
        break;
    }
}

void func_80106500_curtain_call(omObjData *obj) {
    s16 grp;

    /* retail names entity [0]'s fields by their own labels */
    D_8010B4F4_curtain_call = 160.0f;
    D_8010B4F8_curtain_call = 120.0f;
    D_8010B4FC_curtain_call = 45.0f;
    grp = func_8000B838_main(0x430000);
    D_8010B4F0_curtain_call = grp;
    D_8010B4F2_curtain_call = InitEspriteSlot(grp, 0, 0);
    func_8000BC48_main(D_8010B4F2_curtain_call, 0x5000);
    func_8000BBD4_main(D_8010B4F2_curtain_call, D_8010B4F4_curtain_call, D_8010B4F8_curtain_call);
    obj->model[0] = func_8000B108_main(0x430001, 0x299);
    obj->model[1] = func_8000B108_main(0x430002, 0x299);
    obj->model[2] = func_8000B108_main(0x430003, 0x299);
    func_8001C92C_main(obj->model[0], 0.0f);
    func_8001C6A8_main(obj->model[0], 60.0f);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    func_8001C8A8_main(obj->model[2], 1);
    obj->func = func_801064A0_curtain_call;
}

void func_80106688_curtain_call(void) {
    D_8010B4B0_curtain_call[0].obj = omAddObj(500, 4, 2, -1, func_80106500_curtain_call);
}

void func_801066C4_curtain_call(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    func_80033354_main(D_8010CE78_curtain_call[player]);
    D_8010CE78_curtain_call[player] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010CE90_curtain_call[player][anim], 0,
                            D_8010B120_curtain_call[chr]);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B32C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B338_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B344_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B350_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B35C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B368_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B374_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B380_curtain_call);

s8 func_801067A8_curtain_call(omObjData *obj, s8 mode) {
    CcEnt *ent = CC_PLAYER(obj->work[0]);

    switch (mode) {
    case 0:
        if (ent->scale.y == 0.05f) {
            func_8001C258_main(obj->model[2], 4, 0);
            func_8001C258_main(obj->model[3], 4, 0);
        }
        if (ent->scale.y < 1.0f) {
            ent->scale.y += 0.19f;
            break;
        }
        ent->scale.y = 1.0f;
        Hu3DModelScaleSet(obj->model[2], ent->scale.x, 1.0f, ent->scale.z);
        Hu3DModelScaleSet(obj->model[3], ent->scale.x, ent->scale.y, ent->scale.z);
        return 1;
    case 1:
        if (ent->scale.y > 0.05f) {
            ent->scale.y -= 0.19;
            break;
        }
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[3], 4, 4);
        ent->scale.y = 0.05f;
        Hu3DModelScaleSet(obj->model[2], ent->scale.x, 0.05f, ent->scale.z);
        Hu3DModelScaleSet(obj->model[3], ent->scale.x, ent->scale.y, ent->scale.z);
        return 1;
    }
    Hu3DModelScaleSet(obj->model[2], ent->scale.x, ent->scale.y, ent->scale.z);
    Hu3DModelScaleSet(obj->model[3], ent->scale.x, ent->scale.y, ent->scale.z);
    return 0;
}

void func_80106988_curtain_call(omObjData *obj, s8 motion) {
    s32 player = obj->work[0];
    s8 chr = GwPlayer[player].chr;
    CcEnt *ent = CC_PLAYER(player);
    s8 blend = 0;

    if (ent->unk06 != motion) {
        switch (motion) {
        case 4:
        case 5:
        case 6:
        case 8:
            blend = 0;
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 7:
            blend = 2;
            break;
        }
        func_8001C92C_main(obj->model[0], 1.0f);
        func_80105C3C_curtain_call(obj, motion, 0, 10, blend);
        ent->unk06 = motion;
        if (motion == 4) {
            func_80045ED0_main((D_8010B0C0_curtain_call[chr] << 16) | 0x2F);
        }
    }
}

void func_80106AB4_curtain_call(omObjData *obj) {
    CcEnt *ent;

    if (D_8010CF32_curtain_call < 5) {
        func_80106988_curtain_call(obj, 3);
        return;
    }
    ent = CC_PLAYER(obj->work[0]);
    if (ent->unk04 != 0) {
        func_80106988_curtain_call(obj, 5);
        if (ent->unk16 == 0) {
            ent->unk16++;
            func_801066C4_curtain_call(obj, 2);
        }
    } else {
        func_80106988_curtain_call(obj, 4);
        if (ent->unk16 == 0) {
            ent->unk16++;
            func_801066C4_curtain_call(obj, 1);
        }
    }
}

void func_80106B78_curtain_call(omObjData *obj) {
    if (!(D_8010CE88_curtain_call & 0xF)) {
        switch (func_80105B7C_curtain_call(3)) {
        case 0:
            D_800CBB6E_main[obj->work[3]] = 0;
            break;
        case 1:
            D_800CBB6E_main[obj->work[3]] = 10;
            break;
        case 2:
            D_800CBB6E_main[obj->work[3]] = -10;
            break;
        }
    }
}

/* CPU player: pick when to press (unk0E: a plan 1..6 drawn from the difficulty table) and steer. */
void func_80106C18_curtain_call(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CcEnt *ent = CC_PLAYER(player);
    s8 r;
    s8 lv;

    if (obj->work[1] != 0) {
        func_80105B04_curtain_call(player);
        switch (D_8010CEC1_curtain_call) {
        case 0:
            r = func_80105B7C_curtain_call(100);
            lv = D_8010CEFE_curtain_call;
            switch (D_8010CEF8_curtain_call[player]) {
            case 0:
                if (r < D_8010B140_curtain_call[lv][0]) {
                    ent->unk0E = 1;
                } else if (r < D_8010B140_curtain_call[lv][1]) {
                    ent->unk0E = 2;
                } else if (r < D_8010B140_curtain_call[lv][2]) {
                    ent->unk0E = 3;
                } else if (r < D_8010B140_curtain_call[lv][3]) {
                    ent->unk0E = 4;
                } else if (r < D_8010B140_curtain_call[lv][4]) {
                    ent->unk0E = 5;
                } else if (r < 100) {
                    ent->unk0E = 6;
                }
                break;
            case 1:
                if (r < D_8010B150_curtain_call[lv][0]) {
                    ent->unk0E = 1;
                } else if (r < D_8010B150_curtain_call[lv][1]) {
                    ent->unk0E = 2;
                } else if (r < D_8010B150_curtain_call[lv][2]) {
                    ent->unk0E = 3;
                } else if (r < D_8010B150_curtain_call[lv][3]) {
                    ent->unk0E = 4;
                } else if (r < D_8010B150_curtain_call[lv][4]) {
                    ent->unk0E = 5;
                } else if (r < 100) {
                    ent->unk0E = 6;
                }
                break;
            case 2:
                if (r < D_8010B160_curtain_call[lv][0]) {
                    ent->unk0E = 1;
                } else if (r < D_8010B160_curtain_call[lv][1]) {
                    ent->unk0E = 2;
                } else if (r < D_8010B160_curtain_call[lv][2]) {
                    ent->unk0E = 3;
                } else if (r < D_8010B160_curtain_call[lv][3]) {
                    ent->unk0E = 4;
                } else if (r < D_8010B160_curtain_call[lv][4]) {
                    ent->unk0E = 5;
                } else if (r < 100) {
                    ent->unk0E = 6;
                }
                break;
            case 3:
                if (r < D_8010B170_curtain_call[lv][0]) {
                    ent->unk0E = 1;
                } else if (r < D_8010B170_curtain_call[lv][1]) {
                    ent->unk0E = 2;
                } else if (r < D_8010B170_curtain_call[lv][2]) {
                    ent->unk0E = 3;
                } else if (r < D_8010B170_curtain_call[lv][3]) {
                    ent->unk0E = 4;
                } else if (r < D_8010B170_curtain_call[lv][4]) {
                    ent->unk0E = 5;
                } else if (r < 100) {
                    ent->unk0E = 6;
                }
                break;
            }
            switch (ent->unk0E) {
            case 1:
            case 2:
                D_8010CF08_curtain_call[player].press = 230 - func_80105B7C_curtain_call(70);
                D_8010CF08_curtain_call[player].release = func_80105B7C_curtain_call(20) + 20;
                break;
            case 3:
            case 4:
                D_8010CF08_curtain_call[player].press = func_80105B7C_curtain_call(20) + 20;
                break;
            case 5:
            case 6:
                D_8010CF08_curtain_call[player].press = 120 - func_80105B7C_curtain_call(60);
                break;
            }
            ent->unk10 = func_80105B7C_curtain_call(2);
            ent->unk0C = func_80105B7C_curtain_call(3);
            break;
        case 3:
            switch (ent->unk0E) {
            case 1:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player].press) {
                    ent->unk0A = 2;
                    func_8004AC98_main(0x417, obj->work[0]);
                } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player].release) {
                    if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                        ent->unk0A = 4;
                        func_8004AC98_main(0x418, obj->work[0]);
                    }
                } else if (D_8010CE88_curtain_call < D_8010CF08_curtain_call[player].release) {
                    if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                        if (ent->unk10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    }
                }
                break;
            case 2:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player].press) {
                    ent->unk0A = 2;
                    func_8004AC98_main(0x417, obj->work[0]);
                } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player].release) {
                    ent->unk0A = 4;
                    func_8004AC98_main(0x418, obj->work[0]);
                } else if (D_8010CE88_curtain_call < D_8010CF08_curtain_call[player].release) {
                    if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                        if (ent->unk10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    }
                }
                break;
            case 3:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                    if (ent->unk10 != 0) {
                        D_800CBB6E_main[pad] = 10;
                    } else {
                        D_800CBB6E_main[pad] = -10;
                    }
                }
                break;
            case 4:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    if (ent->unk10 != 0) {
                        D_800CBB6E_main[pad] = 10;
                    } else {
                        D_800CBB6E_main[pad] = -10;
                    }
                }
                break;
            case 5:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                    if (ent->unk10 != 0) {
                        D_800CBB6E_main[pad] = 10;
                    } else {
                        D_800CBB6E_main[pad] = -10;
                    }
                } else if (ent->unk0C == 0) {
                    ent->unk0A = 2;
                    func_8004AC98_main(0x417, obj->work[0]);
                    ent->unk0C = 1;
                }
                break;
            case 6:
                if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player].press) {
                    func_80106B78_curtain_call(obj);
                } else if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    if (ent->unk10 != 0) {
                        D_800CBB6E_main[pad] = 10;
                    } else {
                        D_800CBB6E_main[pad] = -10;
                    }
                } else if (ent->unk0C == 0) {
                    ent->unk0A = 2;
                    func_8004AC98_main(0x417, obj->work[0]);
                    ent->unk0C = 1;
                }
                break;
            }
            break;
        }
    }
}

void func_80107560_curtain_call(omObjData *obj) {
    s32 player = obj->work[0];
    CcEnt *ent = CC_PLAYER(player);
    CcEnt *other = CC_PLAYER(D_8010CF20_curtain_call[0]);

    if (ent->unk14 != 1000 && D_8010CF22_curtain_call >= 2 && D_8010CEFE_curtain_call < 2) {
        if (D_8010CF20_curtain_call[0] == player || D_8010CF20_curtain_call[1] == D_8010CEFE_curtain_call) {
            func_80106988_curtain_call(obj, 7);
            ent->unk14 = 1000;
        } else if (HmfModelData[other->obj->model[0]].unk40 == 0.0f && ent->unk06 != 7) {
            func_80105BD0_curtain_call(obj, 7, 2);
            ent->unk06 = 7;
            ent->unk14 = 1000;
        }
    }
}

/* A player's update while the curtain game runs. */
void func_80107680_curtain_call(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CcEnt *ent = CC_PLAYER(player);

    if (D_8010CF32_curtain_call != 2) {
        if (D_8010CF32_curtain_call >= 3) {
            obj->func = func_80106AB4_curtain_call;
        }
    } else {
        if (ent->unk04 != 0) {
            func_80107560_curtain_call(obj);
            return;
        }
        func_80106C18_curtain_call(obj);
        switch (D_8010CEC1_curtain_call) {
        case 0:
            func_80106988_curtain_call(obj, 0);
            break;
        case 3:
            if (ent->unk0A == 1) {
                if (ent->unk08 <= 0 && D_800CBB6E_main[pad] < -5) {
                    if ((s32)ent->pos.x == -180) {
                        ent->pos.x = 0.0f;
                    }
                    ent->unk08 = 1;
                    D_8010CF18_curtain_call[player] = (D_8010CF18_curtain_call[player] + 1) % 3;
                }
                if (ent->unk08 >= 0 && D_800CBB6E_main[pad] >= 6) {
                    if ((s32)ent->pos.x == 0) {
                        ent->pos.x = -180.0f;
                    }
                    ent->unk08 = -1;
                    D_8010CF18_curtain_call[player] =
                        (D_8010CF18_curtain_call[player] != 0) ? D_8010CF18_curtain_call[player] - 1 : 2;
                }
            }
        case 2:
            if (func_80105CB8_curtain_call(obj, 0.0f)) {
                func_80106988_curtain_call(obj, 2);
            } else if (ent->unk06 != 3) {
                func_80106988_curtain_call(obj, 1);
            }
            break;
        case 4:
        case 5:
            if (func_80105CB8_curtain_call(obj, 180.0f)) {
                func_80106988_curtain_call(obj, 2);
            } else {
                func_80106988_curtain_call(obj, 3);
            }
            D_8010CF22_curtain_call = 0;
            ent->unk12 = 0;
            break;
        case 6:
            if (ent->unk12 < 30) {
                func_80105CB8_curtain_call(obj, 0.0f);
                func_80106988_curtain_call(obj, 2);
            } else if (ent->unk12 == 30) {
                if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    func_80106988_curtain_call(obj, 6);
                    D_8010CF22_curtain_call++;
                } else {
                    func_80106988_curtain_call(obj, 8);
                    if (ent->unk16 == 0) {
                        ent->unk16++;
                        func_8004ACE0_main(0x286, obj->work[0]);
                    }
                }
            } else if (ent->unk12 >= 71) {
                if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    if (D_8010CF22_curtain_call != 1 && D_8010CEFE_curtain_call != 2
                        && func_80105CB8_curtain_call(obj, 180.0f)) {
                        func_80106988_curtain_call(obj, 2);
                    } else {
                        func_80106988_curtain_call(obj, 3);
                    }
                } else {
                    ent->unk04 = 1;
                    if (D_8010CF20_curtain_call[0] < 0) {
                        D_8010CF20_curtain_call[0] = player;
                        D_8010CF20_curtain_call[1] = D_8010CEFE_curtain_call;
                    } else {
                        func_80106988_curtain_call(obj, 3);
                    }
                }
            }
            ent->unk12++;
            break;
        }
        if (ent->unk08 > 0) {
            ent->pos.x -= 4.0f;
            if ((s32)ent->pos.x % 60 == 0) {
                ent->unk08 = 0;
            }
        }
        if (ent->unk08 < 0) {
            ent->pos.x += 4.0f;
            if ((s32)ent->pos.x % 60 == 0) {
                ent->unk08 = 0;
            }
        }
        Hu3DModelPosSet(obj->model[3], obj->trans.x + ent->pos.x, ent->pos.y, obj->trans.z);
        switch (D_8010CEC1_curtain_call) {
        case 0:
            ent->pos.x = 0.0f;
            D_8010CF18_curtain_call[player] = 0;
            ent->unk0A = 0;
            ent->unk14 = 0;
            break;
        case 3:
            switch (ent->unk0A) {
            case 0:
                if (func_801067A8_curtain_call(obj, 0)) {
                    ent->unk0A = 1;
                }
                break;
            case 1:
                if ((s32)ent->pos.x % 60 == 0 && (D_800D5558_main[pad] & 0x8000)) {
                    func_8004AC98_main(0x417, obj->work[0]);
                    ent->unk0A = 2;
                }
                break;
            case 2:
                if (func_801067A8_curtain_call(obj, 1)) {
                    ent->unk0A = 3;
                    func_80106988_curtain_call(obj, 3);
                }
                break;
            case 3:
                if (D_800D5558_main[pad] & 0x4000) {
                    func_8004AC98_main(0x418, obj->work[0]);
                    ent->unk0A = 4;
                }
                break;
            case 4:
                if (func_801067A8_curtain_call(obj, 0)) {
                    ent->unk0A = 1;
                    func_80106988_curtain_call(obj, 1);
                }
                break;
            }
            break;
        case 4:
            if (func_801067A8_curtain_call(obj, 0)) {
                ent->unk0A = 1;
            }
            break;
        case 6:
            if (func_801067A8_curtain_call(obj, 1)) {
                ent->unk0A = 0;
            }
            break;
        }
    }
}

/* A player's object: model, motions, the shared curtain models (made by player 0), seat. */
void func_80107D20_curtain_call(omObjData *obj) {
    s8 player = obj->work[0];
    CcEnt *ent = CC_PLAYER(player);
    u16 chr = GwPlayer[player].chr;
    s32 dir = D_800A178C_main[chr][0];
    s8 i;

    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][3], 0x2A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x63));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x3A));
    for (i = 0; i < 3; i++) {
        D_8010CE90_curtain_call[player][i] = DataRead(dir | D_8010B0F0_curtain_call[chr][i]);
    }
    D_8010CE78_curtain_call[player] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010CE90_curtain_call[player][0], 0,
                                                    D_8010B120_curtain_call[chr]);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    if (obj->work[0] == 0) {
        obj->model[1] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[1], 0x80000000, 0);
        func_8001C448_main(obj->model[1]);
        func_8001C514_main(obj->model[1]);
        func_80088800_main(*(HuMtx4F *)HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        obj->model[2] = func_8000B108_main(0x430004, 0x288);
        func_8001C448_main(obj->model[2]);
        func_8001C514_main(obj->model[2]);
        obj->model[3] = func_8000B108_main(0x430005, 0x288);
        func_8001C2FC_main(obj->model[3], 0x80000000, 0x80000000);
        func_8001C448_main(obj->model[3]);
        func_8001C514_main(obj->model[3]);
        D_8010CF2C_curtain_call[0] = obj->model[1];
        D_8010CF2C_curtain_call[1] = obj->model[2];
        D_8010CF2C_curtain_call[2] = obj->model[3];
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
        obj->model[2] = Hu3DModelLink(D_8010CF2C_curtain_call[1]);
        obj->model[3] = Hu3DModelLink(D_8010CF2C_curtain_call[2]);
    }
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C6A8_main(obj->model[2], func_80105B7C_curtain_call(50));
    switch (obj->work[1]) {
    case 0:
        obj->trans.x = -225.0f;
        obj->trans.z = 0.0f;
        obj->trans.y = 3.0f;
        break;
    case 1:
        obj->trans.x = -75.0f;
        obj->trans.z = 10.0f;
        obj->trans.y = 5.0f;
        break;
    case 2:
        obj->trans.x = 75.0f;
        obj->trans.z = 0.0f;
        obj->trans.y = 3.0f;
        break;
    case 3:
        obj->trans.x = 225.0f;
        obj->trans.z = 10.0f;
        obj->trans.y = 5.0f;
        break;
    }
    ent->pos.y = obj->trans.y + 160.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, ent->pos.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, ent->pos.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    ent->scale.x = 1.0f;
    ent->scale.y = 0.05f;
    ent->scale.z = 1.0f;
    Hu3DModelScaleSet(obj->model[2], ent->scale.x, ent->scale.y, ent->scale.z);
    Hu3DModelScaleSet(obj->model[3], ent->scale.x, ent->scale.y, ent->scale.z);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_80105BD0_curtain_call(obj, 3, 2);
    ent->unk06 = 3;
    D_8010CF18_curtain_call[player] = 0;
    D_8010CF20_curtain_call[0] = -1;
    D_8010CF20_curtain_call[1] = -1;
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    func_8001C8A8_main(obj->model[2], 1);
    func_8001C8A8_main(obj->model[3], 1);
    obj->work[1] = GwPlayer[player].stat & 1;
    D_8010CEF8_curtain_call[player] = GwPlayer[player].cpu_difficulty;
    obj->work[3] = GwPlayer[player].pad;
    obj->func = func_80107680_curtain_call;
}

#ifdef NON_MATCHING
/* The four players, each on a random seat. */
void func_801084A0_curtain_call(void) {
    s8 seats[4];
    s8 free[4];
    s8 unused[4];
    omObjData *obj;
    CcEnt *ent;
    s32 player = 0;
    s8 i;
    s8 j;
    s8 n;

    for (i = 0; i < 4; i++) {
        seats[i] = i;
        free[i] = 1;
    }
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            player = 0;
            break;
        case 1:
            player = 1;
            break;
        case 2:
            player = 2;
            break;
        case 3:
            player = 3;
            break;
        }
        ent = CC_PLAYER(i);
        obj = omAddObj(700, 5, 10, -1, func_80107D20_curtain_call);
        obj->work[0] = player;
        ent->obj = obj;
        j = func_80105B7C_curtain_call(4 - i);
        obj->work[1] = seats[j];
        free[seats[j]] = 0;
        for (j = 0, n = 0; j < 4; j++) {
            if (free[j]) {
                seats[n] = j;
                n++;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801084A0_curtain_call);
#endif

/* One of the six curtain panels (entities [5..10]). */
void func_80108670_curtain_call(omObjData *obj) {
    s8 idx = obj->work[0];
    CcEnt *ent = &D_8010B4B0_curtain_call[5 + idx];

    if (D_8010CF32_curtain_call >= 2) {
        switch (D_8010CEC1_curtain_call) {
        case 0:
            ent->unk04 = 0;
            ent->unk16 = 0;
            if (idx >= 4) {
                obj->trans.y = 190.0f;
            } else {
                obj->trans.y = 125.0f;
            }
            ent->scale.z = 1.0f;
            ent->scale.x = 1.0f;
            break;
        case 1:
            if (func_80049F98_main() + D_800D6A90_main != 0) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
            } else {
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
        case 2:
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            break;
        case 6:
            if (D_8010CEC0_curtain_call == D_8010CEC8_curtain_call[idx].slot
                && (D_8010CF32_curtain_call < 3 || (D_8010CF32_curtain_call == 3 && ent->unk04 != 0))) {
                obj->trans.y += D_8010B180_curtain_call[ent->unk04];
                ent->scale.x = ent->scale.z = D_8010B19C_curtain_call[ent->unk04];
                ent->unk04 = (ent->unk04 + 1) % 25;
                if (ent->unk16 == 0) {
                    ent->unk16++;
                    HuAudFXPlay(D_8010B200_curtain_call[D_8010CEFF_curtain_call]);
                }
            }
        case 4:
        case 5:
            if (func_80049F98_main() + D_800D6A90_main != 0) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
            } else {
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
        }
        if (D_8010CF32_curtain_call >= 4) {
            if (ent->unk06 > 0) {
                ent->unk06--;
            } else {
                obj->trans.y += D_8010B180_curtain_call[ent->unk04];
                ent->scale.x = ent->scale.z = D_8010B19C_curtain_call[ent->unk04];
                ent->unk04 = (ent->unk04 + 1) % 25;
            }
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
        Hu3DModelScaleSet(obj->model[1], ent->scale.x, ent->scale.y, ent->scale.z);
    }
}

/* A curtain panel object: panels 0, 2 and 4 load the model, 1, 3 and 5 link the one before. */
void func_801089FC_curtain_call(omObjData *obj) {
    s8 idx = obj->work[0];
    CcEnt *ent = &D_8010B4B0_curtain_call[5 + idx];

    switch (idx) {
    case 0:
        obj->model[0] = func_8000B108_main(0xA008E, 0x2B9);
        func_8000B460_main(obj, 0, 0xA0097);
        func_8000B460_main(obj, 1, 0xA0098);
        func_8000B460_main(obj, 2, 0xA0099);
        obj->work[1] = 0;
        D_8010CF2C_curtain_call[0] = obj->model[0];
        D_8010CF24_curtain_call = obj;
        break;
    case 1:
        obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
        obj->work[1] = 0;
        obj->motion[0] = D_8010CF24_curtain_call->motion[0];
        obj->motion[1] = D_8010CF24_curtain_call->motion[1];
        obj->motion[2] = D_8010CF24_curtain_call->motion[2];
        break;
    case 2:
        obj->model[0] = func_8000B108_main(0xA00A5, 0x2B9);
        func_8000B460_main(obj, 0, 0xA00A8);
        func_8000B460_main(obj, 1, 0xA00A9);
        func_8000B460_main(obj, 2, 0xA00AA);
        obj->work[1] = 1;
        D_8010CF2C_curtain_call[0] = obj->model[0];
        D_8010CF24_curtain_call = obj;
        break;
    case 3:
        obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
        obj->work[1] = 1;
        obj->motion[0] = D_8010CF24_curtain_call->motion[0];
        obj->motion[1] = D_8010CF24_curtain_call->motion[1];
        obj->motion[2] = D_8010CF24_curtain_call->motion[2];
        break;
    case 4:
        obj->model[0] = func_8000B108_main(0xA00C5, 0x2B9);
        func_8000B460_main(obj, 0, 0xA00CB);
        func_8000B460_main(obj, 1, 0xA00CC);
        func_8000B460_main(obj, 2, 0xA00CD);
        obj->work[1] = 2;
        D_8010CF2C_curtain_call[0] = obj->model[0];
        D_8010CF24_curtain_call = obj;
        break;
    case 5:
        obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
        obj->work[1] = 2;
        obj->motion[0] = D_8010CF24_curtain_call->motion[0];
        obj->motion[1] = D_8010CF24_curtain_call->motion[1];
        obj->motion[2] = D_8010CF24_curtain_call->motion[2];
        break;
    }
    func_80105BD0_curtain_call(obj, 0, 2);
    if (obj->work[0] == 0) {
        obj->model[1] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[1], 0x80000000, 0);
        func_8001C448_main(obj->model[1]);
        func_8001C514_main(obj->model[1]);
        func_80088800_main(*(HuMtx4F *)HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        D_8010CF2C_curtain_call[1] = obj->model[1];
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CF2C_curtain_call[1]);
    }
    obj->trans.x = -1500.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
    if (idx == 0 || idx == 1) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (idx == 2 || idx == 3) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (idx == 4 || idx == 5) {
        obj->scale.x = obj->scale.y = obj->scale.z = 0.52f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    ent->scale.z = 1.0f;
    ent->scale.x = 1.0f;
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_80108670_curtain_call;
}

void func_80108E64_curtain_call(void) {
    omObjData *obj;
    s16 i;

    for (i = 0; i < 6; i++) {
        obj = omAddObj(800, 3, 4, -1, func_801089FC_curtain_call);
        D_8010CEC8_curtain_call[i].obj = obj;
        obj->work[0] = i;
        /* retail stores every panel in entity [5] */
        D_8010B4B0_curtain_call[5].obj = obj;
        omSetStatBit(obj, 0xA0);
    }
}

void func_80108EF8_curtain_call(omObjData *obj) {
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 127.0f, obj->trans.z);
}

void func_80108F28_curtain_call(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0xA0000, 0x2B9);
    func_8000B460_main(obj, 0, 0xA000C);
    func_80105BD0_curtain_call(obj, 0, 2);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(*(HuMtx4F *)HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    obj->trans.x = -450.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -350.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_80108EF8_curtain_call;
}

void func_801090FC_curtain_call(void) {
    D_8010B4B0_curtain_call[11].obj = omAddObj(600, 3, 2, -1, func_80108F28_curtain_call);
}

void func_80109138_curtain_call(omObjData *obj) {
    CcEnt *light = &D_8010B4B0_curtain_call[13];

    switch (D_8010CEC1_curtain_call) {
    case 0:
        func_8001C258_main(obj->model[0], 4, 4);
        break;
    case 5:
        switch (D_8010CEFE_curtain_call) {
        case 0:
            obj->trans.x = (f32)D_8010B208_curtain_call[D_8010CEC0_curtain_call] + D_8010B228_curtain_call[D_8010CEC0_curtain_call];
            break;
        case 1:
            obj->trans.x = (f32)D_8010B210_curtain_call[D_8010CEC0_curtain_call] + D_8010B22C_curtain_call[D_8010CEC0_curtain_call];
            break;
        case 2:
            obj->trans.x = (f32)D_8010B21C_curtain_call[D_8010CEC0_curtain_call] + D_8010B234_curtain_call[D_8010CEC0_curtain_call];
            break;
        }
        func_8001C258_main(obj->model[0], 4, 0);
        break;
    }
    if (D_8010CF32_curtain_call >= 3) {
        if (light->unk04 <= 0) {
            light->unk04 = 0;
            func_8001C258_main(obj->model[0], 4, 4);
            return;
        }
        light->unk04 -= 5;
        func_8001F9E4_main(obj->model[0], light->unk04);
    }
}

void func_801092F0_curtain_call(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x430006, 0x2A8);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xD2);
    obj->trans.x = 0.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010B4B0_curtain_call[13].unk04 = 0xFF;
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80109138_curtain_call;
}

void func_801093C4_curtain_call(void) {
    D_8010B4B0_curtain_call[13].obj = omAddObj(900, 1, 1, -1, func_801092F0_curtain_call);
}

/* Curtain panel motions: a 50-frame cycle, every panel at once. */
void func_80109400_curtain_call(void) {
    s8 i;
    s8 t = D_8010CF38_curtain_call;

    for (i = 0; i < 6; i++) {
        switch (t) {
        case 0:
            func_80105C3C_curtain_call(D_8010CEC8_curtain_call[i].obj, 1, 0, 5, 2);
            break;
        case 25:
            func_80105C3C_curtain_call(D_8010CEC8_curtain_call[i].obj, 2, 0, 5, 2);
            break;
        case 50:
            func_80105C3C_curtain_call(D_8010CEC8_curtain_call[i].obj, 0, 0, 5, 2);
            break;
        }
    }
    if (t == 50) {
        D_8010CE84_curtain_call++;
        D_8010CF38_curtain_call = 0;
    } else {
        D_8010CF38_curtain_call++;
    }
}

/* Shuffle step: slide the panels by the pattern for this round. */
void func_8010954C_curtain_call(void) {
    s8 dx = 0;
    s8 i;
    s16 t;

    if (D_8010CE84_curtain_call == D_8010CF1C_curtain_call[0] || D_8010CE84_curtain_call == D_8010CF1C_curtain_call[1]) {
        func_80109400_curtain_call();
        return;
    }
    t = ++D_8010CE84_curtain_call;
    switch (D_8010CEFE_curtain_call) {
    case 0:
        dx = 6;
        break;
    case 1:
        if (t < 60) {
            dx = 6;
        } else if (t < 105) {
            dx = D_8010B25C_curtain_call[D_8010CE86_curtain_call][0];
        } else if (t < 150) {
            dx = 6;
        } else if (t < 195) {
            dx = D_8010B25C_curtain_call[D_8010CE86_curtain_call][1];
        } else if (t < 240) {
            dx = 6;
        } else if (t < 285) {
            dx = D_8010B25C_curtain_call[D_8010CE86_curtain_call][2];
        } else {
            dx = 6;
        }
        break;
    case 2:
        if (t < 60) {
            dx = 6;
        } else if (t < 105) {
            dx = D_8010B268_curtain_call[D_8010CE86_curtain_call][0];
        } else if (t < 150) {
            dx = 6;
        } else if (t < 195) {
            dx = D_8010B268_curtain_call[D_8010CE86_curtain_call][1];
        } else if (t < 240) {
            dx = D_8010B268_curtain_call[D_8010CE86_curtain_call][2];
        } else if (t < 285) {
            dx = 6;
        } else if (t < 330) {
            dx = D_8010B268_curtain_call[D_8010CE86_curtain_call][3];
        } else {
            dx = 6;
        }
        break;
    }
    for (i = 0; i < 6; i++) {
        if (D_8010CEC8_curtain_call[i].unk00 != 0) {
            D_8010CEC8_curtain_call[i].obj->trans.x += dx;
        }
    }
}

/* Who is still in: the characters and player numbers left, and how many are out. */
void func_8010982C_curtain_call(void) {
    s8 i;
    s8 n;
    CcEnt *ent;

    D_8010CF01_curtain_call = 0;
    for (i = 0; i < 4; i++) {
        D_8010CE80_curtain_call[i] = 0;
    }
    for (i = 0, n = 0; i < 4; i++) {
        ent = CC_PLAYER(i);
        if (ent->unk04 == 0) {
            D_8010CE80_curtain_call[n] = GwPlayer[ent->obj->work[0]].chr;
            D_8010CF28_curtain_call[n] = ent->obj->work[0];
            n++;
        } else {
            D_8010CF01_curtain_call++;
        }
    }
}

/* Pick the winning curtain for the round. */
void func_80109920_curtain_call(void) {
    s8 order[6];
    s8 i;
    s8 r;

    for (i = 0; i < 6; i++) {
        order[D_8010CEC8_curtain_call[i].slot] = D_8010CEC8_curtain_call[i].obj->work[1];
    }
    switch (D_8010CEFE_curtain_call) {
    case 0:
        r = func_80105B7C_curtain_call(3);
        D_8010CEFF_curtain_call = order[r];
        D_8010CEC0_curtain_call = r;
        D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
        if (D_8010CE8A_curtain_call[0] != 0) {
            D_8010CE8A_curtain_call[1] = r;
        } else {
            D_8010CE8A_curtain_call[1] = 2 - r;
        }
        break;
    case 1:
        r = func_80105B7C_curtain_call(5);
        D_8010CEFF_curtain_call = order[r];
        D_8010CEC0_curtain_call = r;
        D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
        if (D_8010CE8A_curtain_call[0] != 0) {
            D_8010CE8A_curtain_call[1] = r;
        } else {
            D_8010CE8A_curtain_call[1] = 4 - r;
        }
        break;
    case 2:
        r = func_80105B7C_curtain_call(6);
        D_8010CEFF_curtain_call = order[r];
        D_8010CEC0_curtain_call = r;
        D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
        if (D_8010CE8A_curtain_call[0] != 0) {
            D_8010CE8A_curtain_call[1] = r;
        } else {
            D_8010CE8A_curtain_call[1] = 5 - r;
        }
        break;
    }
}

#ifdef NON_MATCHING
/* One curtain round: deal the panels, shuffle, the host walks on, countdown, reveal, next round. */
void func_80109AD0_curtain_call(void) {
    omObjData *stage = D_8010B4B0_curtain_call[0].obj;
    omObjData *host = D_8010B4B0_curtain_call[11].obj;
    s8 seats[6];
    s8 free[6];
    s8 i;
    s8 j;
    s8 n;
    s8 r;

    switch (D_8010CEC1_curtain_call) {
    case 0:
        if (D_8010CEFE_curtain_call == 0) {
            D_8010CEC8_curtain_call[0].unk00 = D_8010CEC8_curtain_call[2].unk00 = D_8010CEC8_curtain_call[4].unk00 = 1;
            D_8010CEC8_curtain_call[1].unk00 = D_8010CEC8_curtain_call[3].unk00 = D_8010CEC8_curtain_call[5].unk00 = 0;
            r = func_80105B7C_curtain_call(6);
            D_8010CEC8_curtain_call[0].slot = D_8010B248_curtain_call[r][0];
            D_8010CEC8_curtain_call[2].slot = D_8010B248_curtain_call[r][1];
            D_8010CEC8_curtain_call[4].slot = D_8010B248_curtain_call[r][2];
            D_8010CEC8_curtain_call[1].slot = 3;
            D_8010CEC8_curtain_call[3].slot = 4;
            D_8010CEC8_curtain_call[5].slot = 5;
        } else if (D_8010CEFE_curtain_call >= 0) {
            if (D_8010CEFE_curtain_call >= 3) {
                goto dealt;
            }
            for (i = 0; i < 6; i++) {
                seats[i] = i;
                free[i] = 1;
            }
            for (i = 0; i < 6; i++) {
                j = func_80105B7C_curtain_call(6 - i);
                D_8010CEC8_curtain_call[i].slot = seats[j];
                free[seats[j]] = 0;
                for (j = 0, n = 0; j < 6; j++) {
                    if (free[j]) {
                        seats[n] = j;
                        n++;
                    }
                }
            }
            for (i = 0; i < 6; i++) {
                D_8010CEC8_curtain_call[i].unk00 = 1;
                if (D_8010CEFE_curtain_call == 1 && D_8010CEC8_curtain_call[i].slot == 5) {
                    D_8010CEC8_curtain_call[i].unk00 = 0;
                }
            }
        }
    dealt:
        switch (D_8010CEFE_curtain_call) {
        case 0:
            D_8010CF1C_curtain_call[0] = 108;
            D_8010CF1C_curtain_call[1] = 1000;
            break;
        case 1:
            D_8010CF1C_curtain_call[0] = func_80105B7C_curtain_call(75) + 60;
            D_8010CF1C_curtain_call[1] = func_80105B7C_curtain_call(105) + 135;
            D_8010CE86_curtain_call = func_80105B7C_curtain_call(3);
            break;
        case 2:
            D_8010CF1C_curtain_call[0] = func_80105B7C_curtain_call(105) + 60;
            D_8010CF1C_curtain_call[1] = func_80105B7C_curtain_call(135) + 165;
            D_8010CE86_curtain_call = func_80105B7C_curtain_call(6);
            break;
        }
        for (i = 0; i < 6; i++) {
            if (D_8010CEC8_curtain_call[i].unk00 != 0) {
                D_8010CEC8_curtain_call[i].obj->trans.x = D_8010B23C_curtain_call[D_8010CEC8_curtain_call[i].slot];
            } else {
                D_8010CEC8_curtain_call[i].obj->trans.x = -1500.0f;
            }
        }
        D_8010CF38_curtain_call = 0;
        D_8010CE84_curtain_call = 0;
        func_8001C92C_main(stage->model[0], -1.0f);
        for (i = 0; i < 6; i++) {
            switch (D_8010CEFE_curtain_call) {
            case 0:
                if (D_8010CEC8_curtain_call[i].slot == 2) {
                    D_8010CF33_curtain_call = i;
                }
                break;
            case 1:
                if (D_8010CEC8_curtain_call[i].slot == 4) {
                    D_8010CF33_curtain_call = i;
                }
                break;
            case 2:
                if (D_8010CEC8_curtain_call[i].slot == 5) {
                    D_8010CF33_curtain_call = i;
                }
                break;
            }
        }
        func_80109920_curtain_call();
        D_8010CEC1_curtain_call = 1;
        break;
    case 1:
        if ((s32)HmfModelData[stage->model[0]].unk40 <= 0) {
            func_8001C6A8_main(stage->model[0], 0.0f);
            func_8001C92C_main(stage->model[0], 0.0f);
            func_8001C258_main(stage->model[0], 4, 4);
        }
        func_8010954C_curtain_call();
        if (D_8010CEC8_curtain_call[D_8010CF33_curtain_call].obj->trans.x >= 500.0f) {
            D_8010CEC1_curtain_call = 2;
            func_8001C258_main(stage->model[0], 4, 0);
            func_8001C258_main(host->model[0], 4, 0);
            func_8001C258_main(host->model[1], 4, 0);
        }
        break;
    case 2:
        func_8001C92C_main(stage->model[0], 1.0f);
        if (host->trans.x < 0.0f) {
            host->trans.x += 7.0f;
        } else {
            host->trans.x = 0.0f;
            HuAudFXPlay(0x298);
            GMesCreate(0x1A, 10, 160, 28);
            D_8010CE88_curtain_call = 301;
            func_80106408_curtain_call();
            HuAudFXPlay(0x414);
            D_8010CEC1_curtain_call = 3;
        }
        break;
    case 3:
        if (D_8010CE88_curtain_call > 0) {
            D_8010CE88_curtain_call--;
            func_8003F578_main((D_8010CE88_curtain_call + 29) / 30);
        } else {
            func_8003F5C0_main();
            func_8004AD8C_main(0x414);
            D_8010CEC1_curtain_call = 4;
        }
        break;
    case 4:
        if (host->trans.x > -450.0f) {
            host->trans.x -= 7.0f;
            if (host->trans.x < -300.0f && D_8010CF00_curtain_call == 0) {
                func_8004A670_main(30);
                D_8010CF00_curtain_call = 1;
            }
        } else {
            host->trans.x = -450.0f;
            func_8001C258_main(host->model[0], 4, 4);
            func_8001C258_main(host->model[1], 4, 4);
            D_8010CF00_curtain_call = 0;
            for (i = 0; i < 6; i++) {
                if (D_8010CEC8_curtain_call[i].unk00 != 0) {
                    switch (D_8010CEFE_curtain_call) {
                    case 0:
                        D_8010CEC8_curtain_call[i].obj->trans.x = D_8010B208_curtain_call[D_8010CEC8_curtain_call[i].slot];
                        break;
                    case 1:
                        D_8010CEC8_curtain_call[i].obj->trans.x = D_8010B210_curtain_call[D_8010CEC8_curtain_call[i].slot];
                        break;
                    case 2:
                        D_8010CEC8_curtain_call[i].obj->trans.x = D_8010B21C_curtain_call[D_8010CEC8_curtain_call[i].slot];
                        break;
                    }
                } else {
                    D_8010CEC8_curtain_call[i].obj->trans.x = -1500.0f;
                }
            }
            D_8010CEC1_curtain_call = 5;
            HuAudFXPlay(0x419);
            func_8010644C_curtain_call();
        }
        break;
    case 5:
        func_80106494_curtain_call();
        func_8001C92C_main(stage->model[0], -1.0f);
        if ((s32)HmfModelData[stage->model[0]].unk40 <= 0) {
            func_8001C6A8_main(stage->model[0], 0.0f);
            func_8001C92C_main(stage->model[0], 0.0f);
            func_8001C258_main(stage->model[0], 4, 4);
            HuAudFXPlay(0x522);
            D_8010CE88_curtain_call = 100;
            D_8010CEC1_curtain_call = 6;
        }
        break;
    case 6:
        if (D_8010CE88_curtain_call > 0) {
            D_8010CE88_curtain_call--;
            break;
        }
        switch (D_8010CEFE_curtain_call) {
        case 0:
        case 1:
            func_8010982C_curtain_call();
            if (D_8010CF01_curtain_call >= 3) {
                D_8010CEFE_curtain_call = 3;
                r = func_80105B7C_curtain_call(2);
                for (i = 0; i < 6; i++) {
                    for (j = 0; j < 6; j++) {
                        if (D_8010CEC8_curtain_call[i].slot == j) {
                            if (r != 0) {
                                (&D_8010B4B0_curtain_call[5])[i].unk06 = D_8010CEC8_curtain_call[i].slot * 5;
                            } else {
                                (&D_8010B4B0_curtain_call[5])[i].unk06 = (5 - j) * 5;
                            }
                            break;
                        }
                    }
                }
                return;
            }
            break;
        case 2:
            func_8010982C_curtain_call();
            D_8010CEFE_curtain_call++;
            r = func_80105B7C_curtain_call(2);
            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    if (D_8010CEC8_curtain_call[i].slot == j) {
                        if (r != 0) {
                            (&D_8010B4B0_curtain_call[5])[i].unk06 = D_8010CEC8_curtain_call[i].slot * 5;
                        } else {
                            (&D_8010B4B0_curtain_call[5])[i].unk06 = (5 - j) * 5;
                        }
                        break;
                    }
                }
            }
            return;
        }
        if (D_8010CF00_curtain_call == 0) {
            D_8010CF00_curtain_call = 1;
            func_8004AB0C_main(30);
            func_8004A72C_main(30);
        }
        func_8001C92C_main(stage->model[0], 1.0f);
        func_8001C258_main(stage->model[0], 4, 0);
        if ((s32)HmfModelData[stage->model[0]].unk40 >= 60) {
            func_8001C6A8_main(stage->model[0], 60.0f);
            func_8001C92C_main(stage->model[0], 0.0f);
            D_8010CF00_curtain_call = 0;
            D_8010CEFE_curtain_call++;
            D_8010CEC1_curtain_call = 0;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109AD0_curtain_call);
#endif

void func_8010A734_curtain_call(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 1520.0f;
        CRotM[i].x = 347.14f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 225.0f;
        CenterM[i].z = -25.0f;
    }
}

void func_8010A7D8_curtain_call(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010A7FC_curtain_call(omObjData *obj) {
    s8 i;
    s8 j;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                DataClose(D_8010CE90_curtain_call[i][j]);
            }
            func_80033354_main(D_8010CE78_curtain_call[i]);
        }
        obj->func = func_8010A7D8_curtain_call;
    }
}

void func_8010A8E8_curtain_call(omObjData *obj) {
    if (D_800D530C_main == 1) {
        func_8010644C_curtain_call();
        WipeCreateOut(0, 20);
        obj->func = func_8010A7FC_curtain_call;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

/* The minigame's main state: intro message, rounds, the end message and the result. */
void func_8010A948_curtain_call(omObjData *obj) {
    switch (D_8010CF32_curtain_call) {
    case 0:
        GMesCreate(3);
        D_8010CF32_curtain_call = 1;
        D_8010CEFC_curtain_call = 0;
        break;
    case 1:
        if (GMesStatGet() == 0) {
            D_8010CF32_curtain_call = 2;
            D_8010CEC1_curtain_call = 0;
        }
        if (++D_8010CEFC_curtain_call == 62) {
            HuAudSeqPlay(0x31);
        }
        break;
    case 2:
        func_80109AD0_curtain_call();
        if (D_8010CEFE_curtain_call == 3) {
            GMesCreate(0xE);
            HuAudSeqFadeOut(120);
            D_8010CF32_curtain_call = 3;
        }
        break;
    case 3:
        if (GMesStatGet() == 0) {
            D_8010CF32_curtain_call = 4;
            D_8010CE88_curtain_call = 0;
        }
        break;
    case 4:
        if (D_8010CF01_curtain_call == 4) {
            if (++D_8010CE88_curtain_call >= 16) {
                D_8010CF32_curtain_call = 5;
            }
        } else {
            if (++D_8010CE88_curtain_call >= 16) {
                D_8010CF32_curtain_call = 6;
            }
        }
        break;
    case 6:
        switch (D_8010CF01_curtain_call) {
        case 0:
            GMesCreate(0x23, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1], D_8010CE80_curtain_call[2],
                       D_8010CE80_curtain_call[3]);
            GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[2]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[3]].bonusCoin = 10;
            HuAudSeqPlay(0x66);
            break;
        case 1:
            GMesCreate(0x22, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1], D_8010CE80_curtain_call[2]);
            GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[2]].bonusCoin = 10;
            HuAudSeqPlay(0x66);
            break;
        case 2:
            GMesCreate(0x1E, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1]);
            GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
            GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
            HuAudSeqPlay(0x66);
            break;
        case 3:
            GMesCreate(0x16, D_8010CE80_curtain_call[0]);
            GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
            HuAudSeqPlay(0x65);
            break;
        }
        D_8010CE88_curtain_call = 15;
        D_8010CF32_curtain_call = 7;
        break;
    case 5:
        GMesCreate(0x20);
        HuAudSeqPlay(0x6C);
        D_8010CE88_curtain_call = 15;
        D_8010CF32_curtain_call = 7;
        break;
    case 7:
        if (GMesStatGet() == 0) {
            if (--D_8010CE88_curtain_call <= 0) {
                WipeCreateOut(0, 20);
                obj->func = func_8010A7FC_curtain_call;
            }
        }
        break;
    }
}

void func_8010AD68_curtain_call(omObjData *obj) {
    D_8010CF32_curtain_call = 0;
    D_8010CEC1_curtain_call = 20;
    D_8010CE88_curtain_call = 0;
    D_8010CEFE_curtain_call = 0;
    D_8010CF34_curtain_call = NULL;
    D_8010CF00_curtain_call = 0;
    func_8010A734_curtain_call();
    func_80106688_curtain_call();
    func_801093C4_curtain_call();
    func_801090FC_curtain_call();
    func_801084A0_curtain_call();
    func_80108E64_curtain_call();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010A948_curtain_call;
}

void func_8010AE00_curtain_call(void) {
}

void func_8010AE08_curtain_call(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010B280_curtain_call[i].scissor[0], D_8010B280_curtain_call[i].scissor[1],
                   D_8010B280_curtain_call[i].scissor[2], D_8010B280_curtain_call[i].scissor[3]);
        ViewportSet(i, D_8010B280_curtain_call[i].viewport[0], D_8010B280_curtain_call[i].viewport[1],
                    D_8010B280_curtain_call[i].viewport[2], D_8010B280_curtain_call[i].viewport[3],
                    D_8010B280_curtain_call[i].viewport[4], D_8010B280_curtain_call[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010B280_curtain_call[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010AF78_curtain_call(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 3);
    func_8004A208_main();
    func_8010AE08_curtain_call();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010B4A0_curtain_call, 0);
    func_80045010_main(D_8010B4A0_curtain_call, 1);
    omAddObj(1500, 0, 0, -1, func_8010AD68_curtain_call);
    omAddObj(1500, 0, 0, -1, func_8010A8E8_curtain_call);
    func_80105A3C_curtain_call();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B4A0_curtain_call);
