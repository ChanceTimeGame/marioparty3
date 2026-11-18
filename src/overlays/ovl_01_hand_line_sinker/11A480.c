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
    /* 0x0E */ char unk0E[2];
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
    /* 0x024 */ s16 unk24;
    /* 0x028 */ struct HlLine *line;
    /* 0x02C */ u16 count;     /* points in pts */
    /* 0x030 */ Vec pts[HL_LINE_POINTS];
    /* 0x1B0 */ f32 len;
    /* 0x1B4 */ f32 slack;
    /* 0x1B8 */ omObjData *fish; /* the fish on the hook */
    /* 0x1BC */ f32 reel;
    /* 0x1C0 */ u16 splashed;
    /* 0x1C4 */ f32 bob;
    /* 0x1C8 */ s16 player;
    /* 0x1CA */ s16 sfx;
    /* 0x1CC */ s16 sfx2;
    /* 0x1CE */ s16 hookSfx;
    /* 0x1D0 */ u16 reeling;
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
/* regalloc only: retail keeps the angle in $f20 (reused for z) and the distance in $f22; the C swaps them */
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
            if (HuSqrtf((other->trans.x - x) * (other->trans.x - x) + (other->trans.z - z) * (other->trans.z - z)) <
                405.0f) {
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

#ifdef NON_MATCHING
/* regalloc only: retail puts fabsf's result and the case-3 rod angle in other float registers */
void func_8010689C_hand_line_sinker(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    u16 btn;
    s8 sx;
    s8 sy;
    Vec pos;
    u32 flags = obj->unk10;
    HlPlayer *pl = obj->data;
    u16 pad;
    HlLure *ld;
    omObjData *lure;
    HmfModel *mdl;
    f32 angle;
    f32 rotY;
    f32 dir;
    f32 dist;

    pad = GwPlayer[pl->player].pad;
    if (GwPlayer[pl->player].stat & 1) {
        func_80107420_hand_line_sinker(obj, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        btn = D_800D5558_main[pad];
    }
    if (func_800E6E8C_minigame() != 2) {
        stickY = 0;
        stickX = 0;
        btn = 0;
    }
    sy = stickY;
    sx = stickX;
    angle = atan2df(sy, sx);
    switch (obj->work[0]) {
        case 0:
            if ((sx != 0) | (sy != 0)) {
                obj->rot.y = angle + 270.0f;
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 135.0f) {
                    obj->rot.y = 135.0f;
                }
                if (obj->rot.y > 225.0f) {
                    obj->rot.y = 225.0f;
                }
                Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                Hu3DModelRotSet(obj->model[3], 0.0f, obj->rot.y, 0.0f);
                pl->power = func_801092B8_hand_line_sinker(sx, sy);
                if (func_800E6E8C_minigame() != 2) {
                    obj->work[0] = 0;
                } else {
                    obj->work[0] = 1;
                }
            }
            break;
        case 1:
            if ((sx != 0) | (sy != 0)) {
                obj->rot.y = angle + 270.0f;
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 135.0f) {
                    obj->rot.y = 135.0f;
                }
                if (obj->rot.y > 225.0f) {
                    obj->rot.y = 225.0f;
                }
                Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                Hu3DModelRotSet(obj->model[3], 0.0f, obj->rot.y, 0.0f);
                pl->power = func_801092B8_hand_line_sinker(sx, sy);
            }
            if (func_800E6E8C_minigame() != 2) {
                obj->work[0] = 0;
            } else if (btn & A_BUTTON) {
                if (func_800E6E8C_minigame() != 2) {
                    obj->work[0] = 0;
                } else {
                    obj->work[0] = 2;
                    func_8001C258_main(obj->model[1], 0x4000, 0);
                    func_8001C258_main(obj->model[1], 4, 4);
                    func_8001C258_main(obj->model[2], 4, 0);
                    func_8001C5B4_main(obj->model[0], obj->motion[3]);
                    func_8001C5B4_main(obj->model[2], obj->motion[14]);
                    pl->timer = 5;
                }
            }
            break;
        case 2:
            if (--pl->timer == 0) {
                if (func_800E6E8C_minigame() != 2) {
                    obj->work[0] = 0;
                    func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                    func_8001C258_main(obj->model[1], 4, 0);
                    func_8001C258_main(obj->model[2], 4, 4);
                    func_8001C5B4_main(obj->model[0], obj->motion[8]);
                    func_8001C814_main(obj->model[0], 3, 3);
                } else {
                    obj->work[0] = 4;
                    func_8001C5B4_main(obj->model[0], obj->motion[8]);
                    func_8001C814_main(obj->model[0], 3, 3);
                    func_8001C92C_main(obj->model[0], 1.0f);
                    func_8001C92C_main(obj->model[2], 1.0f);
                    func_8001C258_main(obj->model[3], 0x4000, 0);
                    if (pl->lure != NULL) {
                        omDelObj(pl->lure);
                    }
                    pl->lure = omAddObj(0x14, 1, 0, -1, func_80107B24_hand_line_sinker);
                    pl->lure->model[0] = obj->model[3];
                    pl->lure->data = HuMemAllocTag(sizeof(HlLure), 0x7918);
                    lure = pl->lure;
                    ld = lure->data;
                    lure->work[0] = 0;
                    pl->lure->work[1] = 0;
                    ld->hookSfx = 0;
                    ld->fish = NULL;
                    ld->reel = 0.0f;
                    ld->splashed = 0;
                    ld->player = pl->player;
                    ld->v0 = -((pl->power / 70.0f) * 85.0f) - 15.0f;
                    dir = obj->rot.y;
                    if (dir > 180.0f) {
                        dir -= 360.0f;
                    }
                    ld->v0 = ld->v0 * fabs(sindf(fabsf(dir) - 90.0f));
                    ld->angle = 45.0f;
                    ld->t = 0.0f;
                    ld->rod.y = 240.0f;
                    ld->rod.x = sindf(obj->rot.y - 6.0f) * 140.0f + obj->trans.x;
                    ld->rod.z = cosdf(obj->rot.y - 6.0f) * 140.0f + obj->trans.z;
                    ld->rot.x = 75.0f;
                    ld->rot.y = obj->rot.y;
                    ld->rot.z = 0.0f;
                    ld->unk24 = 0;
                    ld->count = 0;
                    ld->line = pl->line;
                    ld->sfx = HuAudFXPlay(0x302);
                    ld->sfx2 = -1;
                    omSetTra(pl->lure, ld->rod.x, ld->rod.y, ld->rod.z);
                    omSetRot(pl->lure, ld->rot.x, ld->rot.y, ld->rot.z);
                    Hu3DModelPosSet(pl->lure->model[0], ld->rod.x, ld->rod.y, ld->rod.z);
                    Hu3DModelRotSet(pl->lure->model[0], ld->rot.x, ld->rot.y, ld->rot.z);
                }
            }
            break;
        case 4:
            if (flags & 1) {
                obj->unk10 &= ~1;
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[5]].unk02, 0, 6, 2);
                obj->work[0] = 3;
            }
            break;
        case 3:
            ld = pl->lure->data;
            if (flags & 2) {
                obj->unk10 &= ~2;
                if (pl->lure->work[1] == 1) {
                    func_80047E90_main(ld->fish, 2);
                    obj->work[0] = 5;
                    func_8001C258_main(obj->model[1], 0x4000, 0);
                    func_8001C258_main(obj->model[1], 4, 4);
                    func_8001C258_main(obj->model[2], 4, 0);
                    func_8001C5B4_main(obj->model[0], obj->motion[2]);
                    func_8001C5B4_main(obj->model[2], obj->motion[17]);
                    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
                } else {
                    obj->work[0] = 0;
                    func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                    func_8001C258_main(obj->model[1], 4, 0);
                    func_8001C258_main(obj->model[2], 4, 4);
                    func_8001C5B4_main(obj->model[0], obj->motion[8]);
                    func_8001C814_main(obj->model[0], 3, 3);
                    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
                    pl->target = NULL;
                }
                omDelObj(pl->lure);
                pl->lure = NULL;
            } else if (ld->reeling == 0 && ((sx != 0) | (sy != 0))) {
                rotY = angle + 270.0f;
                if (rotY >= 360.0f) {
                    rotY -= 360.0f;
                }
                if (rotY < 135.0f) {
                    rotY = 135.0f;
                }
                if (rotY > 225.0f) {
                    rotY = 225.0f;
                }
                if (rotY != obj->rot.y) {
                    obj->rot.y = rotY;
                    pos.y = 240.0f;
                    pos.x = sindf(obj->rot.y - 6.0f) * 140.0f + obj->trans.x;
                    pos.z = cosdf(obj->rot.y - 6.0f) * 140.0f + obj->trans.z;
                    lure = pl->lure;
                    dist = HuSqrtf((pos.x - lure->trans.x) * (pos.x - lure->trans.x) +
                                   (pos.y - lure->trans.y) * (pos.y - lure->trans.y) +
                                   (pos.z - lure->trans.z) * (pos.z - lure->trans.z));
                    ld->rod = pos;
                    Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                    if (dist < ld->len) {
                        ld->slack += ld->len - dist;
                    }
                    ld->len = dist;
                }
            }
            break;
        case 5:
            mdl = &HmfModelData[obj->model[0]];
            if (D_800CCF58_main[mdl->unk02].unk02 <= mdl->unk40) {
                obj->work[0] = 0;
                func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                func_8001C258_main(obj->model[1], 4, 0);
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C5B4_main(obj->model[0], obj->motion[8]);
                func_8001C814_main(obj->model[0], 3, 3);
                pl->target = NULL;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010689C_hand_line_sinker);
#endif

/* The angler CPU: picks a fish, aims at it with some error, and reels after a delay. */
void func_80107420_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn) {
    HlPlayer *pl;
    omObjData *fish;
    f32 ofs;
    f32 angle;
    f32 dist;
    f32 x;
    f32 z;
    u16 delay;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    pl = obj->data;
    ofs = 0.0f;
    switch (GwPlayer[pl->player].cpu_difficulty) {
        case 0:
            if ((u8)(rand8() % 10) < 8) {
                ofs = (u8)(rand8() % 31) - 15;
            }
            delay = (u8)(rand8() % 45) + 20;
            break;
        case 1:
            if ((u8)(rand8() % 10) < 5) {
                ofs = (u8)(rand8() % 21) - 10;
            }
            delay = (u8)(rand8() % 30) + 15;
            break;
        case 2:
            if ((u8)(rand8() % 10) < 3) {
                ofs = (u8)(rand8() % 11) - 5;
            }
            delay = (u8)(rand8() % 15) + 10;
            break;
        case 3:
            if ((u8)(rand8() % 10) < 1) {
                ofs = (u8)(rand8() % 11) - 5;
            }
            delay = (u8)(rand8() % 10) + 10;
            break;
    }
    switch (obj->work[0]) {
        case 0:
            fish = pl->target;
            if (fish != NULL) {
                angle = atan2df(fish->trans.x - obj->trans.x, fish->trans.z - obj->trans.z) + pl->aimOfs;
                dist = HuSqrtf((fish->trans.x - obj->trans.x) * (fish->trans.x - obj->trans.x) +
                               (fish->trans.z - obj->trans.z) * (fish->trans.z - obj->trans.z)) / 15.0f;
                x = -sindf(angle) * dist;
                z = cosdf(angle) * dist;
                *stickX = x;
                *stickY = z;
                pl->cpuTimer = delay;
            } else {
                pl->target = func_80107A3C_hand_line_sinker();
                pl->aimOfs = ofs;
            }
            break;
        case 1:
            fish = pl->target;
            if (fish == NULL) {
                pl->target = func_80107A3C_hand_line_sinker();
                pl->aimOfs = ofs;
            } else {
                angle = atan2df(fish->trans.x - obj->trans.x, fish->trans.z - obj->trans.z) + pl->aimOfs;
                dist = HuSqrtf((fish->trans.x - obj->trans.x) * (fish->trans.x - obj->trans.x) +
                               (fish->trans.z - obj->trans.z) * (fish->trans.z - obj->trans.z)) / 15.0f;
                x = -sindf(angle) * dist;
                z = cosdf(angle) * dist;
                if (--pl->cpuTimer == 0) {
                    *btn |= A_BUTTON;
                } else {
                    *stickX = x;
                    *stickY = z;
                }
            }
            break;
        case 3:
            fish = pl->target;
            angle = atan2df(fish->trans.x - obj->trans.x, fish->trans.z - obj->trans.z);
            dist = HuSqrtf((fish->trans.x - obj->trans.x) * (fish->trans.x - obj->trans.x) +
                           (fish->trans.z - obj->trans.z) * (fish->trans.z - obj->trans.z)) / 15.0f;
            x = -sindf(angle) * dist;
            z = cosdf(angle) * dist;
            *stickX = x;
            *stickY = z;
            break;
        case 2:
        case 4:
        case 5:
            break;
    }
}

/* Picks a random fish that is still swimming (not caught, hooked or out of the water). */
omObjData *func_80107A3C_hand_line_sinker(void) {
    omObjData *free[3];
    s32 n = 0;
    s32 i = 0;
    omObjData *fish;
    u32 state;

    do {
        fish = D_8010C100_hand_line_sinker[i];
        state = fish->work[0];
        if (((state == 2) | (state == 4)) == 0 && state != 3) {
            free[n] = fish;
            n++;
        }
        i++;
    } while (i < 3);
    if (n == 0) {
        return NULL;
    }
    if (n == 1) {
        return free[0];
    }
    return free[rand8() % n];
}

/* The lure: flies out in an arc, sinks, hooks a fish, and is reeled in. */
void func_80107B24_hand_line_sinker(omObjData *obj) {
    Vec pos;
    Vec rot;
    HlLure *ld = obj->data;
    omObjData *fish;
    HlPlayer *fpl;
    f32 h;
    f32 dx;
    f32 dz;
    f32 t;
    f32 y;
    f32 dy;
    f32 len;
    f32 r;
    f32 a;

    switch (obj->work[0]) {
        case 0:
            y = sindf(ld->angle) * ld->v0;
            h = -ld->v0 * cosdf(ld->angle);
            dx = sindf(obj->rot.y) * h;
            dz = cosdf(obj->rot.y) * h;
            t = ld->t;
            y *= t;
            y += t * t * 4.9f;
            y = ld->rod.y - y;
            ld->t = t + 1.0f;
            if (obj->trans.y <= -50.0f && ld->splashed == 0) {
                ld->splashed = 1;
                pos.x = obj->trans.x;
                pos.y = -50.0f;
                pos.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &pos, &rot);
                ld->sfx2 = func_8004AC98_main(0x300, ld->player);
                HuAudFXStop(ld->sfx);
                omVibrate(ld->player, 2, 3, 10);
            }
            if (y <= -210.0f) {
                y = -210.0f;
                ld->reeling = 0;
                obj->work[0] = 1;
                func_80047E90_main(D_8010C0FC_hand_line_sinker, 1);
                ld->bob = 0.0f;
                ld->sfx = HuAudFXPlay(0x303);
            }
            omSetTra(obj, dx + obj->trans.x, y, dz + obj->trans.z);
            ld->len = HuSqrtf((ld->rod.x - obj->trans.x) * (ld->rod.x - obj->trans.x) +
                              (ld->rod.y - obj->trans.y) * (ld->rod.y - obj->trans.y) +
                              (ld->rod.z - obj->trans.z) * (ld->rod.z - obj->trans.z));
            if (y <= -240.0f) {
                ld->slack = 5.0f + ld->len;
            } else {
                ld->slack = ld->len + 3.0f;
            }
            func_8010AD7C_hand_line_sinker(obj, ld->len, ld->rod.x, ld->rod.y, ld->rod.z, obj->trans.x, obj->trans.y,
                                           obj->trans.z);
            func_8010B0FC_hand_line_sinker(obj, 111.0f);
            break;
        case 1:
            ld->slack -= 21.0f - ld->reel * 21.0f;
            if (ld->reeling == 0) {
                fish = func_801080F0_hand_line_sinker(obj);
                if (fish != NULL && obj->work[1] == 0) {
                    obj->work[1] = 1;
                    func_80047E90_main(fish, 1);
                    ld->fish = fish;
                    obj->trans.y = -140.0f;
                    fpl = fish->data;
                    ld->sfx2 = func_8004AC98_main(0x301, ld->player);
                    omVibrate(fpl->player, 2, 2, 20);
                    omVibrate(ld->player, 2, 2, 20);
                }
            }
            if (ld->slack < ld->len) {
                len = ld->len - (ld->len - ld->slack);
                ld->len = len;
                if (len > fabs(240.0f - obj->trans.y)) {
                    dy = fabsf(ld->rod.y - obj->trans.y);
                    r = HuSqrtf(fabsf(len * len - dy * dy));
                    a = atan2df(obj->trans.x - ld->rod.x, -(obj->trans.z - ld->rod.z));
                    omSetTra(obj, sindf(a) * r + ld->rod.x, obj->trans.y, ld->rod.z - cosdf(a) * r);
                    obj->rot.y = 180.0f - a;
                    ld->slack = ld->len;
                    if (ld->bob < 5.0f) {
                        ld->bob += 0.5f;
                    }
                } else {
                    ld->reeling = 1;
                    if (ld->hookSfx == 0 && ld->fish != NULL) {
                        ld->hookSfx = 1;
                        func_8004AC98_main(0x304, ld->player);
                    }
                    ld->bob = 0.0f;
                    obj->rot.y = D_8010C0FC_hand_line_sinker->rot.y;
                    if (ld->len < 0.0f) {
                        func_80047E90_main(D_8010C0FC_hand_line_sinker, 2);
                        omSetTra(obj, ld->rod.x, ld->rod.y, ld->rod.z);
                        HuAudFXStop(ld->sfx);
                    } else {
                        omSetTra(obj, ld->rod.x, 240.0f - ld->len, ld->rod.z);
                        omSetRot(obj, 160.0f, obj->rot.y, 0.0f);
                    }
                }
            }
            func_8010AD7C_hand_line_sinker(obj, ld->slack + ld->bob, ld->rod.x, ld->rod.y, ld->rod.z, obj->trans.x,
                                           obj->trans.y, obj->trans.z);
            func_8010B0FC_hand_line_sinker(obj, 104.0f);
            break;
    }
    func_8010BB58_hand_line_sinker(ld->line, ld->pts, ld->count);
}

/* The swimming fish close enough to the lure to bite, if any. */
omObjData *func_801080F0_hand_line_sinker(omObjData *obj) {
    omObjData *fish;
    s32 i;
    f32 dist;

    if (func_800E6E8C_minigame() != 2) {
        return NULL;
    }
    for (i = 0; i < 3; i++) {
        fish = D_8010C100_hand_line_sinker[i];
        if (fish->work[0] < 2) {
            dist = HuSqrtf((obj->trans.x - fish->trans.x) * (obj->trans.x - fish->trans.x) +
                           (obj->trans.z - fish->trans.z) * (obj->trans.z - fish->trans.z));
            if (dist < HuSqrtf(8725.0f)) {
                return fish;
            }
        }
    }
    return NULL;
}

/* A fish: swims, dashes on A, and once hooked mashes A to slow the reel. */
void func_801081D0_hand_line_sinker(omObjData *obj) {
    Vec pos;
    Vec rot;
    s8 stickX;
    s8 stickY;
    u16 btn;
    HlPlayer *pl = obj->data;
    u16 pad;
    omObjData *lure;
    HlLure *ld;
    u32 flags;
    f32 angle;
    f32 diff;

    pad = GwPlayer[pl->player].pad;
    if (GwPlayer[pl->player].stat & 1) {
        func_80108880_hand_line_sinker(obj, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        btn = D_800D5558_main[pad];
    }
    if (func_800E6E8C_minigame() != 2) {
        stickY = 0;
        stickX = 0;
        btn = 0;
    }
    flags = obj->unk10;
    if (flags & 1) {
        obj->unk10 = flags & ~1;
        obj->work[0] = 3;
        pl->unk38 = 0;
        pl->unk3A = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 2);
    }
    switch (obj->work[0]) {
        case 0:
            if ((stickX != 0) | (stickY != 0)) {
                angle = atan2df(stickX, -stickY);
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                if (obj->rot.y != angle) {
                    diff = angle - obj->rot.y;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (diff > 4.0f) {
                            obj->rot.y = obj->rot.y + 4.0f;
                        } else {
                            obj->rot.y = diff + obj->rot.y;
                        }
                    } else if (360.0f - diff > 4.0f) {
                        obj->rot.y = obj->rot.y - 4.0f;
                    } else {
                        obj->rot.y = obj->rot.y - (360.0f - diff);
                    }
                    if (obj->rot.y < 0.0f) {
                        obj->rot.y += 360.0f;
                    }
                    if (obj->rot.y >= 360.0f) {
                        obj->rot.y -= 360.0f;
                    }
                }
            }
            func_8010B1E4_hand_line_sinker(obj);
            if (btn & A_BUTTON) {
                obj->work[0] = 1;
                pl->speed = 20.0f;
                angle = obj->rot.y + 180.0f;
                pos.x = sindf(angle) * 80.0f;
                pos.y = 0.0f;
                pos.z = cosdf(angle) * 80.0f;
                rot.x = rot.z = 0.0f;
                rot.y = obj->rot.y + 180.0f;
                func_8010A6D0_hand_line_sinker(obj, 1, &pos, &rot);
                func_8004ACE0_main(0x306, pl->player);
            }
            pl->tap = 1000;
            break;
        case 1:
            func_8010B1E4_hand_line_sinker(obj);
            pl->speed *= 0.85f;
            if (pl->speed < 2.0f) {
                obj->work[0] = 0;
                pl->speed = 0.0f;
            }
            break;
        case 2:
            break;
        case 3:
            if (flags & 2) {
                obj->unk10 &= ~2;
                obj->work[0] = 4;
                D_8010C10C_hand_line_sinker++;
                pl->flyAngle = atan2df(obj->trans.x - D_8010C0FC_hand_line_sinker->trans.x,
                                       obj->trans.z - D_8010C0FC_hand_line_sinker->trans.z) + 180.0f;
                pl->flyVy = 50.0f;
                HuAudFXPlay(GwPlayer[pl->player].chr + 0x287);
                omVibrate(pl->player, 10, 0, 10);
                break;
            }
            lure = ((HlPlayer *)D_8010C0FC_hand_line_sinker->data)->lure;
            ld = lure->data;
            if (ld != NULL) {
                if (btn & A_BUTTON) {
                    if (pl->tap < 2) {
                        ld->reel = 0.5f;
                        pl->tap = 0;
                    } else if (pl->tap < 3) {
                        ld->reel = 0.3f;
                        pl->tap = 0;
                    } else if (pl->tap < 4) {
                        ld->reel = 0.1f;
                        pl->tap = 0;
                    } else {
                        pl->tap = 0;
                    }
                } else {
                    pl->tap++;
                }
            }
            if (lure != NULL) {
                if (ld->reeling == 0) {
                    omSetTra(obj, sindf(lure->rot.y) * 40.0f + lure->trans.x, lure->trans.y - 60.0f,
                             cosdf(lure->rot.y) * 40.0f + lure->trans.z);
                } else {
                    omSetTra(obj, sindf(lure->rot.y) * 40.0f + lure->trans.x, lure->trans.y - 100.0f,
                             cosdf(lure->rot.y) * 40.0f + lure->trans.z);
                }
            }
            break;
        case 4:
            obj->trans.x += sindf(pl->flyAngle) * 35.0f;
            obj->trans.z += cosdf(pl->flyAngle) * 35.0f;
            obj->trans.y += pl->flyVy;
            pl->flyVy -= 5.0f;
            if (pl->flyVy < -600.0f) {
                obj->work[0] = 2;
            }
            break;
    }
}

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
