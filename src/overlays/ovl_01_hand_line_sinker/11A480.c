#include "common.h"
// m4 hl: Hand, Line and Sinker (1 vs 3: the solo player fishes for the other three)
#include "overlays/minigame.h"
#include "variables.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

/* Per-player object data, both for the angler and the three fish (func_80106100_hand_line_sinker). */
typedef struct HlPlayer {
    /* 0x00 */ s8 player;
    /* 0x04 */ f32 speed;      /* fish: dash speed */
    /* 0x08 */ f32 power;      /* angler: cast power */
    /* 0x0C */ u16 timer;      /* angler: frames to the cast */
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u16 tap;        /* fish: frames since the last A press */
    /* 0x14 */ omObjData *lure; /* angler: the lure object */
    /* 0x18 */ char unk18[4];
    /* 0x1C */ struct HlLine *line; /* angler: the fishing line */
    /* 0x20 */ f32 flyAngle;   /* fish: thrown out of the water */
    /* 0x24 */ f32 flyVy;
    /* 0x28 */ char unk28[6];
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ u16 cpuTimer;   /* angler CPU: frames until it reels */
    /* 0x40 */ omObjData *target; /* angler CPU: the fish it aims at */
    /* 0x44 */ f32 aimOfs;
} HlPlayer; // Size 0x48

#define HL_LINE_POINTS 32

/* The lure object's data (func_8010689C_hand_line_sinker). */
typedef struct HlLure {
    /* 0x000 */ f32 v0;        /* cast speed */
    /* 0x004 */ f32 angle;     /* cast elevation */
    /* 0x008 */ f32 t;         /* frames in flight */
    /* 0x00C */ Vec rod;       /* rod tip */
    /* 0x018 */ Vec rot;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ struct HlLine *line;
    /* 0x02C */ u16 count;     /* points in pts */
    /* 0x030 */ Vec pts[HL_LINE_POINTS];
    /* 0x1B0 */ f32 len;
    /* 0x1B4 */ f32 slack;
    /* 0x1B8 */ omObjData *fish; /* the fish on the hook */
    /* 0x1BC */ f32 reel;
    /* 0x1C0 */ u8 splashed;
    /* 0x1C4 */ f32 bob;
    /* 0x1C8 */ s16 player;
    /* 0x1CA */ s16 sfx;
    /* 0x1CC */ s16 sfx2;
    /* 0x1CE */ s16 hookSfx;
    /* 0x1D0 */ u8 reeling;
} HlLure; // Size 0x1D4

/* A texture's size (func_800335BC_main). */
typedef struct HlTexSize {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
} HlTexSize;

typedef struct HlLine HlLine;

// main
s16 func_800329B4_main(void *);
void func_8001766C_main(void);
void func_80045C2C_main(void);
void func_80047C0C_main(u16 group, u16 max_objs);
omObjData **func_80047DBC_main(s16 group);
void func_80047E90_main(omObjData *obj, s32 arg1);
void omAddMember(u16 group, omObjData *obj);
void HmfLightStatSet(s16, s16, s16);
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
s16 func_8000B0D4_main(s32, s32);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_800335BC_main(char *arg0, void *arg1);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
f32 fabsf(f32);
f64 fabs(f64);
extern s32 D_800A178C_main[][6];
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */
extern u8 D_800D6A90_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
void func_800E6F0C_minigame(s8 arg0);
extern s16 D_800EB930_minigame;

// 120090
void func_8010B5B0_hand_line_sinker(void);
void func_8010B5EC_hand_line_sinker(void *from, void *to, s16 frames);
void func_8010BA50_hand_line_sinker(f32 t);
void func_8010BA64_hand_line_sinker(void);
HlLine *func_8010BA80_hand_line_sinker(u8 r, u8 g, u8 b);
void func_8010BB58_hand_line_sinker(HlLine *line, Vec *points, u16 count);
void func_8010BE6C_hand_line_sinker(HlLine *line);

// LOCAL
void func_80105CF0_hand_line_sinker(omObjData *obj);
void func_80105D28_hand_line_sinker(omObjData *obj);
void func_80105EE8_hand_line_sinker(omObjData *obj);
void func_80105FA4_hand_line_sinker(omObjData *obj);
void func_80106040_hand_line_sinker(omObjData *obj);
void func_80106070_hand_line_sinker(omObjData *obj);
void func_801060A0_hand_line_sinker(omObjData *obj);
void func_801060D0_hand_line_sinker(omObjData *obj);
void func_80106100_hand_line_sinker(omObjData *obj, u16 player);
void func_8010689C_hand_line_sinker(omObjData *obj);
void func_80107420_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn);
omObjData *func_80107A3C_hand_line_sinker(void);
void func_80107B24_hand_line_sinker(omObjData *obj);
omObjData *func_801080F0_hand_line_sinker(omObjData *obj);
void func_801081D0_hand_line_sinker(omObjData *obj);
void func_80108880_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn);
f32 func_801092B8_hand_line_sinker(s8 stickX, s8 stickY);
void func_801093A4_hand_line_sinker(omObjData *obj);
void func_80109584_hand_line_sinker(omObjData *obj);
void func_80109B9C_hand_line_sinker(omObjData *obj);
void func_8010A5F0_hand_line_sinker(void);
void func_8010A6D0_hand_line_sinker(omObjData *obj, s32 type, Vec *pos, Vec *rot);
void func_8010AD7C_hand_line_sinker(omObjData *obj, f32 len, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1);
void func_8010B0FC_hand_line_sinker(omObjData *obj, f32 y);
void func_8010B1E4_hand_line_sinker(omObjData *obj);

/* .data */
extern D_80111B50_vine_with_me_Struct D_8010BF00_hand_line_sinker;
extern u16 D_8010BF60_hand_line_sinker; /* wipe out started */
extern s32 D_8010BF64_hand_line_sinker[]; /* fish model per character */
extern char *D_8010BF88_hand_line_sinker[];
extern u16 D_8010BF9C_hand_line_sinker; /* fish placed */

/* .rodata */
/* the minigame title in Shift-JIS ("ＡＢＣ") */
const s16 D_8010BFB0_hand_line_sinker[] = { 0x8260, 0x8261, 0x8262, 0 };

/* .bss */
extern u16 D_8010C0EA_hand_line_sinker; /* the angler's player number */
extern s16 D_8010C0EC_hand_line_sinker;
extern s16 D_8010C0EE_hand_line_sinker;
extern s16 D_8010C0F0_hand_line_sinker;
extern omObjData *D_8010C0F4_hand_line_sinker;
extern omObjData *D_8010C0F8_hand_line_sinker;
extern omObjData *D_8010C0FC_hand_line_sinker; /* the angler */
extern omObjData **D_8010C100_hand_line_sinker; /* the fish */
extern HlTexSize D_8010C104_hand_line_sinker;
extern f32 D_8010C108_hand_line_sinker;
extern u16 D_8010C10C_hand_line_sinker; /* fish caught */
extern s16 D_8010C12C_hand_line_sinker;

void func_801059A0_hand_line_sinker(void) {
    omObjData *fish[4];
    s32 i;
    void *data;

    omInitObjMan(0x1A, 0);
    func_8004A208_main();
    data = DataRead(0x220015);
    D_8010C12C_hand_line_sinker = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_800142A0_main(9);
    func_8001F38C_main(0, 0x28, 0x78);
    D_800CD280_main = 1;
    i = 0;
    func_8010B5B0_hand_line_sinker();
    func_8010A5F0_hand_line_sinker();
    func_80045C2C_main();
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x40, 0x40, 0x60);
    HmfLightDirSet(0, 92.0f, 79.0f, 22.0f);
    HmfLightStatSet(0, 1, 1);
    HmfLightColorSet(2, 0x64, 0xFF, 0xFF);
    HmfLightDirSet(2, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010C0EA_hand_line_sinker = i;
            break;
        }
    }
    omAddObj(0, 0, 0, -1, func_80105CF0_hand_line_sinker);
    omAddObj(6, 6, 0, -1, func_80105EE8_hand_line_sinker);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    fish[0] = omAddObj(0x14, 6, 0x12, -1, func_80106040_hand_line_sinker);
    fish[1] = omAddObj(0x14, 6, 0x12, -1, func_80106070_hand_line_sinker);
    fish[2] = omAddObj(0x14, 6, 0x12, -1, func_801060A0_hand_line_sinker);
    fish[3] = omAddObj(0x14, 6, 0x12, -1, func_801060D0_hand_line_sinker);
    func_80047C0C_main(0, 4);
    for (i = 0; i < 4; i++) {
        if (i == D_8010C0EA_hand_line_sinker) {
            D_8010C0FC_hand_line_sinker = fish[i];
        } else {
            omAddMember(0, fish[i]);
        }
    }
    D_8010C100_hand_line_sinker = func_80047DBC_main(0);
    func_80045010_main(D_8010BFB0_hand_line_sinker, 1);
    func_800E5EA0_minigame(&D_8010BF00_hand_line_sinker);
    D_800EB930_minigame = 0x2D;
    func_8001766C_main();
}

void func_80105CF0_hand_line_sinker(omObjData *obj) {
    D_8010C0EC_hand_line_sinker = 0;
    D_8010C0F8_hand_line_sinker = NULL;
    D_8010C0F4_hand_line_sinker = NULL;
    D_8010C0F0_hand_line_sinker = 0;
    D_8010C10C_hand_line_sinker = 0;
    obj->func = func_80105D28_hand_line_sinker;
}

void func_80105D28_hand_line_sinker(omObjData *obj) {
    HlPlayer *pl;
    omObjData *o;

    if (D_8010BF60_hand_line_sinker == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010C0F4_hand_line_sinker == NULL) {
                    D_8010C0EE_hand_line_sinker = 0;
                    D_8010C0F4_hand_line_sinker = omAddObj(4, 0, 0, -1, func_801093A4_hand_line_sinker);
                    HuAudSeqPlay(0);
                }
                break;
            case 1:
                break;
            case 2:
                if (D_8010C10C_hand_line_sinker == 3) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (D_8010C0F8_hand_line_sinker == NULL) {
                    if (D_8010C10C_hand_line_sinker == 3) {
                        o = omAddObj(4, 0, 0, -1, func_80109584_hand_line_sinker);
                        D_8010C0F8_hand_line_sinker = o;
                        o->work[1] = 0;
                    } else {
                        o = omAddObj(4, 0, 0, -1, func_80109B9C_hand_line_sinker);
                        D_8010C0F8_hand_line_sinker = o;
                        o->work[1] = 0;
                    }
                    D_8010C0F8_hand_line_sinker->work[0] = 0;
                } else if (D_8010C0F8_hand_line_sinker->work[0] == 1) {
                    omDelObj(D_8010C0F8_hand_line_sinker);
                    func_800E6F0C_minigame(4);
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(0, 0x14);
                D_8010BF60_hand_line_sinker = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        pl = D_8010C0FC_hand_line_sinker->data;
        func_8010BE6C_hand_line_sinker(pl->line);
        pl->line = NULL;
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
        func_8010BA64_hand_line_sinker();
    }
}

void func_80105EE8_hand_line_sinker(omObjData *obj) {
    obj->data = HuMemAllocTag(0x24, 0x7918);
    obj->model[0] = func_8000B108_main(0x220000, 0x699);
    obj->model[1] = func_8000B108_main(0x220001, 0x1A99);
    obj->model[2] = func_8000B108_main(0x220003, 0x699);
    func_8001C814_main(obj->model[2], 2, 2);
    func_800335BC_main("m201_3mizu_DEF", &D_8010C104_hand_line_sinker);
    func_8001C954_main(obj->model[1]);
    D_8010C108_hand_line_sinker = 0.0f;
    obj->func = func_80105FA4_hand_line_sinker;
}

void func_80105FA4_hand_line_sinker(omObjData *obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010C108_hand_line_sinker += 0.1f;
    }
    func_8001E888_main(obj->model[1], D_8010C108_hand_line_sinker, 0, D_8010C104_hand_line_sinker.w,
                       D_8010C104_hand_line_sinker.h, "m201_00-grid6", 0);
}

void func_80106040_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 0);
}

void func_80106070_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 1);
}

void func_801060A0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 2);
}

void func_801060D0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 3);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010BFF0_hand_line_sinker);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010C008_hand_line_sinker);

#ifdef NON_MATCHING
/* retail keeps the angle in $f20 and reuses it for z; the C swaps $f20/$f22 and gets two mul.s nops */
void func_80106100_hand_line_sinker(omObjData *obj, u16 player) {
    s8 chr = GwPlayer[player].chr;
    s32 mdl0 = D_800A178C_main[chr][0];
    s32 mdl2 = D_800A178C_main[chr][2];
    HlPlayer *pl;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    f32 dx;
    f32 dz;
    u32 i;
    omObjData *other;

    pl = obj->data = HuMemAllocTag(sizeof(HlPlayer), 0x7918);
    pl->player = player;
    pl->timer = 0;
    pl->unk2E = 0;
    pl->unk10 = 0;
    pl->tap = 0;
    pl->speed = 0.0f;
    if (player == D_8010C0EA_hand_line_sinker) {
        obj->model[0] = func_8000B108_main(mdl0 | mdl2, 0x20689);
        func_80017790_main(obj->model[0], 2, chr, func_80017B6C_main(chr, 2, 0));
        func_8001C514_main(obj->model[0]);
        obj->model[5] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
        obj->work[0] = 0;
        pl->power = 0.0f;
        pl->line = func_8010BA80_hand_line_sinker(0xFF, 0xFF, 0xFF);
        pl->lure = NULL;
        pl->target = NULL;
        obj->model[1] = func_8000B108_main(0x220006, 0x20499);
        obj->model[2] = func_8000B108_main(0x220007, 0x20499);
        obj->model[3] = func_8000B108_main(0x22000B, 0x21899);
        obj->model[4] = func_8000B0D4_main(9, 0x689);
        func_8001EF6C_main(obj->model[1], obj->model[0], "item_hook");
        func_8000B460_main(obj, 0x11, 0x220007);
        func_8000B460_main(obj, 0xE, 0x220008);
        func_8000B460_main(obj, 0xF, 0x220009);
        func_8000B460_main(obj, 0x10, 0x22000A);
        func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x16));
        func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x17));
        func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x40));
        func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x26));
        func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x2A));
        func_8000B460_main(obj, 0xA, func_80017BB8_main(chr, 1));
        func_8000B460_main(obj, 0xB, func_80017BB8_main(chr, 0));
        func_8000B460_main(obj, 0xC, func_80017BB8_main(chr, 0x2F));
        func_8000B460_main(obj, 0xD, func_80017BB8_main(chr, 0x36));
        func_8001C5B4_main(obj->model[0], obj->motion[4]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001EF6C_main(obj->model[3], obj->model[1], D_8010BF88_hand_line_sinker[0]);
        func_8001C258_main(obj->model[3], 0x4000, 0x4000);
        func_8001C258_main(obj->model[1], 0x4000, 0x4000);
        omSetTra(obj, 0.0f, 100.0f, 900.0f);
        omSetRot(obj, 0.0f, 180.0f, 0.0f);
        Hu3DModelPosSet(obj->model[4], 0.0f, 100.0f, 900.0f);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->func = func_8010689C_hand_line_sinker;
        return;
    }
    obj->model[0] = func_8000B108_main(D_8010BF64_hand_line_sinker[chr] | 0x220000, 0x1A99);
    func_8000B460_main(obj, 0, D_8010BF64_hand_line_sinker[chr] | 0x220000);
    func_8000B460_main(obj, 1, 0x220014);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    do {
        angle = (rand8() * rand8()) % 360;
        dist = (rand8() * rand8()) % 595;
        x = sindf(angle) * dist;
        z = cosdf(angle) * dist;
        for (i = 0; i < D_8010BF9C_hand_line_sinker; i++) {
            other = D_8010C100_hand_line_sinker[i];
            dx = other->trans.x - x;
            dx = dx * dx;
            dz = other->trans.z - z;
            dz = dz * dz;
            if (HuSqrtf(dx + dz) < 405.0f) {
                break;
            }
        }
    } while (i != D_8010BF9C_hand_line_sinker);
    omSetTra(obj, x, -240.0f, z);
    D_8010BF9C_hand_line_sinker++;
    obj->rot.y = (rand8() * rand8()) % 360;
    pl->unk34 = pl->unk30 = (rand8() * rand8()) % 360;
    pl->unk38 = 0;
    obj->work[0] = 0;
    obj->func = func_801081D0_hand_line_sinker;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80106100_hand_line_sinker);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010689C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80107420_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80107A3C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80107B24_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801080F0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801081D0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108880_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108C5C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108F44_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801092B8_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801093A4_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80109584_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80109B9C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A554_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A5F0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A6D0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A904_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A9F8_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010AAEC_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010ABD4_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010AD7C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010B0FC_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010B1E4_hand_line_sinker);
