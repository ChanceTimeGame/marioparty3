#include "common.h"
// m3 bk: Baby Bowser Bonkers
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

/* A camera key (D_8010BCB0, 2 x 0x24); the same layout as Log Jam's BkCamera. */
typedef struct BkCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} BkCamera; // Size 0x24

typedef struct BkBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} BkBytes;

typedef union BkPack {
    void *p;
    BkBytes b;
} BkPack;

#define BK_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

/* One hit in a pattern: on frame `frame`, hammer `id` drops. */
typedef struct BkStep {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 id;
} BkStep; // Size 4

/* A Baby Bowser attack pattern (D_8010B888 points at one). */
typedef struct BkPattern {
    /* 0x00 */ s16 length; /* frames */
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4; /* 0: ends on its length alone */
    /* 0x06 */ s16 count;
    /* 0x08 */ BkStep* steps;
} BkPattern; // Size 0xC

/* A player's work (0x50; func_8010B3AC from obj->work). */
typedef struct BkPlayer {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02; /* score */
    /* 0x04 */ s16 unk04; /* result motion: 0 win, 1 lose */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ s32 unk0C; /* win voice file */
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C; /* velocity */
    /* 0x28 */ s16 unk28; /* GwPlayer index */
    /* 0x2A */ s16 unk2A; /* controller port */
    /* 0x2C */ s16 unk2C; /* character */
    /* 0x2E */ s16 unk2E; /* CPU */
    /* 0x30 */ s16 unk30; /* CPU difficulty */
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ s16 unk4C; /* hit effect, 0..2 */
    /* 0x4E */ char unk4E[2];
} BkPlayer; // Size 0x50

/* The ground object's work (0xB4), as Locked Out's LoGround. */
typedef struct BkGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} BkGround; // Size 0xB4

/* One of the 14 blocks (D_8010BC60, 14 x 0x30). */
typedef struct BkBlock {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 model;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A; /* frames in the current state */
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; /* height offset */
    /* 0x1C */ f32 unk1C; /* base height */
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ void (*unk28)(struct BkBlock*); /* state last frame */
    /* 0x2C */ void (*unk2C)(struct BkBlock*); /* state */
} BkBlock; // Size 0x30

/* A score counter (D_8010BCAC, 2 x 0x12). */
typedef struct BkCounter {
    /* 0x00 */ s16 file; /* character face sprite */
    /* 0x02 */ s16 grp;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 off[2]; /* digit x offsets */
    /* 0x0C */ s16 value; /* shown */
    /* 0x0E */ s16 target;
    /* 0x10 */ s16 timer;
} BkCounter; // Size 0x12

extern u16 D_800D5558_main[];
extern u8 D_800D6A90_main;
extern s32 fontcolor;

extern s32 D_8010B890_baby_bowser_bonkers;
extern f32 D_8010B8EC_baby_bowser_bonkers;
extern f32 D_8010B8F0_baby_bowser_bonkers;
extern f32 D_8010B8F4_baby_bowser_bonkers;
extern s32 D_8010B938_baby_bowser_bonkers; /* debug camera mode */
extern s32 D_8010B93C_baby_bowser_bonkers; /* debug text x */
extern s32 D_8010B940_baby_bowser_bonkers; /* debug text y */
extern BkCamera D_8010BCB0_baby_bowser_bonkers[2];
extern s32 D_8010BCF8_baby_bowser_bonkers;
extern s32 D_8010BCFC_baby_bowser_bonkers;
extern s32 D_8010BD00_baby_bowser_bonkers;

void func_801062E8_baby_bowser_bonkers(omObjData* obj);
void func_8010A6D8_baby_bowser_bonkers(omObjData *obj);
void func_8010AB14_baby_bowser_bonkers(s32 idx);
void func_8010AD00_baby_bowser_bonkers(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010AEF0_baby_bowser_bonkers(s32 idx);
f32 func_8010B044_baby_bowser_bonkers(f32 a, f32 b);
f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 cur, f32 step);
f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 a, f32 b);
f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 a, f32 b);
void func_8010B380_baby_bowser_bonkers(omObjData *obj, u32 value);
void *func_8010B3AC_baby_bowser_bonkers(omObjData *obj);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
f32 fabsf(f32);
f64 fmod(f64, f64);
u8 func_8000B638_main(void);
void func_80105BB0_baby_bowser_bonkers(omObjData* obj);
extern omObjData* D_8010BC38_baby_bowser_bonkers;
extern s32 D_8010BC40_baby_bowser_bonkers;
extern s32 D_8010BC44_baby_bowser_bonkers;
extern s32 D_8010BC48_baby_bowser_bonkers;
extern s32 D_8010BC4C_baby_bowser_bonkers;
extern s32 D_8010BC50_baby_bowser_bonkers;
extern s32 D_8010BC54_baby_bowser_bonkers;
extern s16 D_8010BC5C_baby_bowser_bonkers;
extern D_80111B50_vine_with_me_Struct D_8010BD08_baby_bowser_bonkers;
void func_80105C0C_baby_bowser_bonkers(omObjData* obj);
void func_801063B4_baby_bowser_bonkers(void);
void func_80107CD8_baby_bowser_bonkers(void);
void func_80108160_baby_bowser_bonkers(void);
void func_80109890_baby_bowser_bonkers(void);
void func_80109EB8_baby_bowser_bonkers(void);
extern s32 D_8010BC3C_baby_bowser_bonkers;
void func_80107678_baby_bowser_bonkers(omObjData* obj, s16 a, s16 b);
void func_801076D8_baby_bowser_bonkers(omObjData* a, omObjData* b, Vec* va, Vec* vb, s16 again);
s32 func_80109080_baby_bowser_bonkers(s32 id, s16 rise, s16 stay);
s32 func_801096D0_baby_bowser_bonkers(void);
void func_8010630C_baby_bowser_bonkers(omObjData* obj);
void func_800E6F0C_minigame(s32);
extern BkPattern* D_8010B888_baby_bowser_bonkers;
extern s16 D_8010B88C_baby_bowser_bonkers; /* player whose turn it is */
extern BkPattern* D_8010BC68_baby_bowser_bonkers[4][4];
void func_8010660C_baby_bowser_bonkers(omObjData* obj);
extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB774_minigame;
extern s32 D_8010B894_baby_bowser_bonkers[4];
extern Vec D_8010B8A4_baby_bowser_bonkers[2];
extern BkPlayer* D_8010BC58_baby_bowser_bonkers;
void func_80106AA4_baby_bowser_bonkers(omObjData* obj);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
s32 func_80017BB8_main(s16, s16);
extern s32 D_800A178C_main[][6];
extern s32 D_8010B8BC_baby_bowser_bonkers[8]; /* voice directories by character */
extern s32 D_8010B8DC_baby_bowser_bonkers[2]; /* win voices */
extern s32 D_8010B8E4_baby_bowser_bonkers[2];
void func_80106CEC_baby_bowser_bonkers(omObjData* obj);
u8 func_800E6E8C_minigame(void);
void func_800DDD94_minigame(omObjData* obj);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
omObjData* func_80045F1C_main(u32, s16, s16);
extern s32 D_8010B848_baby_bowser_bonkers[8]; /* win motions by character */
extern s32 D_8010B868_baby_bowser_bonkers[8]; /* lose motions by character */
void func_80109E98_baby_bowser_bonkers(s32 idx, s16 score);
void func_80107D38_baby_bowser_bonkers(omObjData* obj);
void func_80107E54_baby_bowser_bonkers(omObjData* obj);
void func_800E1490_minigame(s32);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
extern omObjData* D_800EC1C0_minigame[];
f64 fabs(f64);
void func_801081C0_baby_bowser_bonkers(omObjData* obj);
void func_8010831C_baby_bowser_bonkers(omObjData* obj);
s16 func_80108454_baby_bowser_bonkers(BkBlock* b);
void func_801089CC_baby_bowser_bonkers(BkBlock* b);
void func_80108E90_baby_bowser_bonkers(BkBlock* b);
void func_80109704_baby_bowser_bonkers(void);
extern Vec D_8010B400_baby_bowser_bonkers[14]; /* block positions */
extern BkBlock* D_8010BC60_baby_bowser_bonkers;
int abs(int);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_801075F4_baby_bowser_bonkers(omObjData* obj, f32 x, f32 z);
extern f32 D_800EB760_minigame;
void func_80108B84_baby_bowser_bonkers(BkBlock* b);
void func_80108D6C_baby_bowser_bonkers(BkBlock* b);
void func_80108F9C_baby_bowser_bonkers(BkBlock* b);
void func_80108A0C_baby_bowser_bonkers(BkBlock* b);
BkBlock* func_8010919C_baby_bowser_bonkers(s32 id);
s32 func_801080D0_baby_bowser_bonkers(f32 x, f32 z);
s32 func_80109388_baby_bowser_bonkers(BkBlock* b, s32 margin);
extern BkPattern** D_8010B8F8_baby_bowser_bonkers[4]; /* patterns by level */
extern s32 D_8010B908_baby_bowser_bonkers[4]; /* pattern counts by level */
u16 func_8010984C_baby_bowser_bonkers(s32 dirAndFile);
void func_80109990_baby_bowser_bonkers(omObjData* obj);
void func_80109BFC_baby_bowser_bonkers(s32 idx, s32 chr);
extern s32 D_8010B918_baby_bowser_bonkers[8]; /* face sprites by character */
extern s16* D_8010BCA8_baby_bowser_bonkers; /* sprite files: [0] digits, [1] counter backing */
extern BkCounter* D_8010BCAC_baby_bowser_bonkers;
void func_801091D4_baby_bowser_bonkers(f32 x, f32 z, BkBlock** list);
s32 func_801093D4_baby_bowser_bonkers(s32 id);
s32 func_8010943C_baby_bowser_bonkers(BkBlock** list, s32 max, s32 player);
s32 func_8010958C_baby_bowser_bonkers(BkBlock** list, s32 max, s32 player);
s32 func_80107648_baby_bowser_bonkers(omObjData* obj);
extern BkBlock* D_8010BC00_baby_bowser_bonkers[14]; /* blocks by distance (func_801091D4) */
// end m3 bk

const s16 D_8010B950_baby_bowser_bonkers[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };
const s16 D_8010B95C_baby_bowser_bonkers[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000 };

void func_801059A0_baby_bowser_bonkers(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x10);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010BC48_baby_bowser_bonkers = 900;
    D_8010BC44_baby_bowser_bonkers = 0;
    D_8010BC40_baby_bowser_bonkers = 0;
    D_8010BC4C_baby_bowser_bonkers = -1;
    D_8010BC50_baby_bowser_bonkers = 0;
    D_8010BC54_baby_bowser_bonkers = -1;
    D_8010BC5C_baby_bowser_bonkers = -1;
    D_8010BC38_baby_bowser_bonkers = omAddObj(0x20, 0, 0, -1, func_80105BB0_baby_bowser_bonkers);
    memset(&D_8010BD08_baby_bowser_bonkers, 0, 0x28);
    D_8010BD08_baby_bowser_bonkers.unk01 = 4;
    func_800E5EA0_minigame(&D_8010BD08_baby_bowser_bonkers);
    func_80045010_main(D_8010B950_baby_bowser_bonkers, 1);
    func_80045010_main(D_8010B95C_baby_bowser_bonkers, 1);
}

void func_80105BB0_baby_bowser_bonkers(omObjData* obj) {
    obj->func = func_80105C0C_baby_bowser_bonkers;
    func_80107CD8_baby_bowser_bonkers();
    func_80108160_baby_bowser_bonkers();
    func_801063B4_baby_bowser_bonkers();
    func_80109890_baby_bowser_bonkers();
    func_80109EB8_baby_bowser_bonkers();
    if (_CheckFlag(0xA) != 0) {
        D_8010BC3C_baby_bowser_bonkers = 1;
    }
}

/* NON_MATCHING: retail reloads D_8010BC48 for each level threshold and D_800EC598_minigame for the winner
   (no CSE across those blocks); this C keeps them in registers, so one more saved register. */
#ifdef NON_MATCHING
void func_80105C0C_baby_bowser_bonkers(omObjData* obj) {
    BkPlayer* p0;
    BkPlayer* p1;
    BkPlayer* cur;
    omObjData* winner;
    s32 i;
    s32 done;
    s32 level;
    s32 over;

    done = 0;
    switch (D_8010BC4C_baby_bowser_bonkers) {
    case -1:
        if (D_8010BC44_baby_bowser_bonkers > 0) {
            D_8010BC54_baby_bowser_bonkers = HuAudFXPlay(0x4AE);
            WipeCreateIn(0xFF, 0x10);
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 0:
        if (WipeStatGet() == 0) {
            GMesCreate(6);
            HuAudFXPlay(0xE);
            HuAudSeqPlay(0x36);
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 1:
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010BC48_baby_bowser_bonkers + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            if (D_8010B888_baby_bowser_bonkers == NULL) {
                D_8010BC44_baby_bowser_bonkers = 3;
                D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[0][0];
            }
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 2:
        func_8003F578_main((D_8010BC48_baby_bowser_bonkers-- + 28) / 30);
        if (D_8010BC48_baby_bowser_bonkers <= 0) {
            D_8010BC48_baby_bowser_bonkers = 0;
        }
        if (D_8010BC48_baby_bowser_bonkers >= 60) {
            for (i = 0; i < D_8010B888_baby_bowser_bonkers->count; i++) {
                if (D_8010BC44_baby_bowser_bonkers == D_8010B888_baby_bowser_bonkers->steps[i].frame) {
                    func_80109080_baby_bowser_bonkers(D_8010B888_baby_bowser_bonkers->steps[i].id, 12,
                                                      D_8010B888_baby_bowser_bonkers->unk2);
                }
            }
        }
        if (D_8010B888_baby_bowser_bonkers->unk4 == 0 || func_801096D0_baby_bowser_bonkers() != 0) {
            done = 1;
        }
        over = D_8010BC44_baby_bowser_bonkers >= D_8010B888_baby_bowser_bonkers->length;
        if (over & done) {
            level = 0;
            if (D_8010BC48_baby_bowser_bonkers < 600) {
                level = 1;
                if (D_8010BC48_baby_bowser_bonkers < 450) {
                    level = (D_8010BC48_baby_bowser_bonkers < 300) ? 3 : 2;
                }
            }
            if (++D_8010BC50_baby_bowser_bonkers >= 4) {
                D_8010BC50_baby_bowser_bonkers = 0;
            }
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[level][D_8010BC50_baby_bowser_bonkers];
        }
        if (D_8010BC48_baby_bowser_bonkers <= 0) {
            func_8003F5C0_main();
            GMesCreate(0x11);
            func_800E6F0C_minigame(3);
            func_80107678_baby_bowser_bonkers(D_800EC598_minigame[0], 0, 13);
            func_80107678_baby_bowser_bonkers(D_800EC598_minigame[1], 0, 13);
            HuAudSeqFadeOut(0x78);
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 3:
        if (D_8010BC44_baby_bowser_bonkers == 15) {
            if (D_8010BC54_baby_bowser_bonkers != -1) {
                func_8004AEF0_main((s16)D_8010BC54_baby_bowser_bonkers, 15);
            }
            D_8010BC54_baby_bowser_bonkers = -1;
        }
        if (GMesStatGet() == 0) {
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 4:
        if (D_8010BC44_baby_bowser_bonkers >= 15) {
            p0 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[0]);
            p1 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[1]);
            if (p0->unk02 > p1->unk02) {
                GMesCreate(0x16, p0->unk2C);
                GwPlayer[p0->unk28].bonusCoin += 10;
                D_8010BC5C_baby_bowser_bonkers = p0->unk2C;
                D_8010BC50_baby_bowser_bonkers = 0x8C;
                p0->unk04 = 0;
                p1->unk04 = 1;
                HuAudSeqPlay(0x67);
                winner = D_800EC598_minigame[0];
                func_8010AD00_baby_bowser_bonkers(winner->trans.x, winner->trans.y + 50.0, winner->trans.z, 65535.0f,
                                                  65535.0f, 65535.0f, 600.0f, 30);
            } else if (p0->unk02 < p1->unk02) {
                GMesCreate(0x16, p1->unk2C);
                GwPlayer[p1->unk28].bonusCoin += 10;
                D_8010BC5C_baby_bowser_bonkers = p1->unk2C;
                D_8010BC50_baby_bowser_bonkers = 0x8C;
                p0->unk04 = 1;
                p1->unk04 = 0;
                HuAudSeqPlay(0x67);
                winner = D_800EC598_minigame[1];
                func_8010AD00_baby_bowser_bonkers(winner->trans.x, winner->trans.y + 50.0, winner->trans.z, 65535.0f,
                                                  65535.0f, 65535.0f, 600.0f, 30);
            } else {
                GMesCreate(0x20);
                D_8010BC50_baby_bowser_bonkers = 0x90;
                HuAudSeqPlay(0x6C);
                p1->unk04 = 1;
                p0->unk04 = 1;
            }
            func_800E6F0C_minigame(4);
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    case 6:
        if (D_8010BC44_baby_bowser_bonkers >= 15) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010BC44_baby_bowser_bonkers = 0;
            D_8010BC4C_baby_bowser_bonkers++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_801062E8_baby_bowser_bonkers;
        }
        break;
    }
    cur = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers]);
    func_801076D8_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers],
                                      D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers ^ 1], &cur->unk1C,
                                      &((BkPlayer*)func_8010B3AC_baby_bowser_bonkers(
                                            D_800EC598_minigame[(s16)(D_8010B88C_baby_bowser_bonkers ^ 1)]))->unk1C,
                                      0);
    D_8010B88C_baby_bowser_bonkers ^= 1;
    func_8010630C_baby_bowser_bonkers(obj);
    D_8010BC40_baby_bowser_bonkers++;
    D_8010BC44_baby_bowser_bonkers++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80105C0C_baby_bowser_bonkers);
#endif

void func_801062E8_baby_bowser_bonkers(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_8010630C_baby_bowser_bonkers(omObjData* obj) {
    if (D_8010B890_baby_bowser_bonkers != 0) {
        if (D_8010B890_baby_bowser_bonkers == 1) {
            obj->func = func_801062E8_baby_bowser_bonkers;
        }
        D_8010B890_baby_bowser_bonkers--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010B890_baby_bowser_bonkers = 0x10;
        WipeCreateOut(0, (s16)D_8010B890_baby_bowser_bonkers);
        HuAudSeqFadeOut((s16)D_8010B890_baby_bowser_bonkers);
        func_8004AB0C_main((s16)D_8010B890_baby_bowser_bonkers);
    }
}

void func_801063B4_baby_bowser_bonkers(void) {
    s32 picked[2] = { -1, -1 };
    BkPlayer* p;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 min;

    p = D_8010BC58_baby_bowser_bonkers = HuMemAllocTag(sizeof(BkPlayer) * 2, 31000);
    memset(p, 0, sizeof(BkPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, min = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (picked[k] == D_8010B894_baby_bowser_bonkers[j]) {
                    found = 1;
                }
            }
            if (!found) {
                if (GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group < min) {
                    min = GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group;
                    D_8010BC58_baby_bowser_bonkers[i].unk28 = D_8010B894_baby_bowser_bonkers[j];
                }
            }
        }
        picked[i] = D_8010BC58_baby_bowser_bonkers[i].unk28;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    D_800EB744_minigame = 1.4f;
    D_800EB748_minigame = 0.14f;
    D_800EB774_minigame = 1.46f;
    for (i = 0; i < 2; i++, p++) {
        p->unk00 = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(0x10, 14, 60, -1, func_8010660C_baby_bowser_bonkers);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010B8A4_baby_bowser_bonkers[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010B8A4_baby_bowser_bonkers[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = 39.100002f;
        func_8010B380_baby_bowser_bonkers(D_800EC598_minigame[D_800EC280_minigame], (u32)p);
        D_800EC280_minigame++;
    }
}

/* NON_MATCHING: only the voice-table index shift is scheduled one instruction earlier than retail. */
#ifdef NON_MATCHING
void func_8010660C_baby_bowser_bonkers(omObjData* obj) {
    func_800E1BA8_minigame_ObjData* w;
    BkPlayer* p;
    s32* voice;
    u32 file0;
    s32 file1;
    u32 file2;
    s16 gw;
    s16 chr;
    s16 i;

    p = func_8010B3AC_baby_bowser_bonkers(obj);
    gw = p->unk28;
    chr = GwPlayer[gw].chr;
    p->unk2C = chr;
    p->unk2A = GwPlayer[gw].pad;
    p->unk2E = GwPlayer[gw].stat & 1;
    p->unk30 = GwPlayer[gw].cpu_difficulty;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][1];
    file2 = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, file0, file1, gw, 0x289, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    obj->model[3] = func_8000B108_main(3, 0x68D);
    obj->model[4] = func_8000B108_main(4, 0x68D);
    for (i = 0; i < 3; i++) {
        obj->model[7 + i] = func_8000B108_main(8, 0x68D);
    }
    obj->model[13] = func_8000B108_main(file0 | file2, 0x28D);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x11, func_80017BB8_main(chr, 0xE), 0, 0);
    func_800E5A00_minigame(obj, 0x12, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0x14, func_80017BB8_main(chr, 0x1D), 0, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5978_minigame(obj, 0x21, func_80017BB8_main(chr, 0x23), 2, 0);
    func_800E5A00_minigame(obj, 0x22, func_80017BB8_main(chr, 0x24), 2, 0);
    voice = &D_8010B8DC_baby_bowser_bonkers[rand8() & 1];
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, (s16)*voice), 1, 0x78);
    p->unk0C = D_8010B8BC_baby_bowser_bonkers[chr] | *voice;
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, (s16)D_8010B8E4_baby_bowser_bonkers[rand8() & 1]), 1,
                           0x78);
    func_800E5690_minigame(obj, 0);
    func_800E149C_minigame(obj, 0, 2);
    p->unk10.x = p->unk1C.x = 0.0f;
    p->unk02 = 0;
    p->unk04 = -1;
    p->unk32 = -1;
    p->unk34 = 0;
    p->unk36 = 0;
    p->unk38 = 1000.0 - p->unk30 * 225.0;
    p->unk08 = 0.0f;
    p->unk3C = p->unk30 * 6 + ((rand8() & 3) + 4);
    p->unk3E = 0;
    p->unk40 = 0;
    p->unk42 = 0;
    p->unk44 = p->unk48 = 0.0f;
    obj->func = func_80106AA4_baby_bowser_bonkers;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010660C_baby_bowser_bonkers);
#endif

void func_80106AA4_baby_bowser_bonkers(omObjData* obj) {
    BkPlayer* p;
    func_800E1BA8_minigame_ObjData* w;
    f32 rot;

    p = func_8010B3AC_baby_bowser_bonkers(obj);
    w = obj->data;
    p->unk10.x = obj->trans.x;
    p->unk10.y = obj->trans.y;
    p->unk10.z = obj->trans.z;
    w->unk50 |= 0x8000;
    switch (func_800E6E8C_minigame()) {
    case 2:
        if (w->unk38 != 1000.0f) {
            obj->trans.y -= 1.5000000596046448;
        }
        if (p->unk2E != 0) {
            func_80106CEC_baby_bowser_bonkers(obj);
        }
        break;
    case 3:
        w->unk3C = func_8010B148_baby_bowser_bonkers(0.0f, w->unk3C, 15.0f);
        break;
    case 4:
        switch (p->unk04) {
        case 0:
            if (func_800E5690_minigame(obj, 0xD) != 0) {
                func_80017790_main(obj->model[0], 2, p->unk2C, D_8010B848_baby_bowser_bonkers[p->unk2C]);
                func_80045F1C_main(p->unk0C, -1, p->unk00);
                p->unk04 = -1;
            }
            break;
        case 1:
            if (func_800E5690_minigame(obj, 0xE) != 0) {
                func_80017790_main(obj->model[0], 2, p->unk2C, D_8010B868_baby_bowser_bonkers[p->unk2C]);
                p->unk04 = -1;
            }
            break;
        }
        break;
    }
    rot = w->unk3C;
    func_800DDD94_minigame(obj);
    p->unk1C.x = obj->trans.x - p->unk10.x;
    p->unk1C.y = obj->trans.y - p->unk10.y;
    p->unk1C.z = obj->trans.z - p->unk10.z;
    w->unk3C = func_8010B148_baby_bowser_bonkers(w->unk3C, rot, 30.0f);
    func_80088910_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, w->unk3C, 0.0f);
}

/* CPU player: picks a rising block away from the opponent, walks to it and jumps on it. */
/* NON_MATCHING: masked 77, register allocation and scheduling (one more stack slot); the control flow and every store follow the asm. */
#ifdef NON_MATCHING
void func_80106CEC_baby_bowser_bonkers(omObjData* obj) {
    BkPlayer* p;
    func_800E1BA8_minigame_ObjData* w;
    BkBlock* blk;
    HmfModel* m;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    s32 need;
    s32 lead;
    s32 n;
    s32 i;
    f32 ex;
    f32 ez;

    p = func_8010B3AC_baby_bowser_bonkers(obj);
    w = obj->data;
    D_800D5558_main[p->unk2A] = 0;
    D_800CDA7C_main[p->unk2A] = 0;
    D_800CBB6E_main[p->unk2A] = 0;
    D_800D20A1_main[p->unk2A] = 0;
    if (D_8010BC48_baby_bowser_bonkers >= 450) {
        need = p->unk3C / 2;
    } else {
        need = p->unk3C;
    }
    lead = p->unk02 >= need;
    if (w->unk38 != 1000.0f) {
        p->unk42 = p->unk02;
    }
    if (p->unk42 < p->unk02 && (lead || p->unk30 == 0)) {
        /* Retail aims at (unk44, unk44): the z target reads the x field. */
        dx = p->unk44 - obj->trans.x;
        dz = p->unk44 - obj->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist != 0.0f) {
            dx /= dist;
            dz /= dist;
        } else {
            dx = dz = 0.0f;
        }
        s = dist / 100.0;
        if (s >= 1.0f) {
            s = 1.0f;
        }
        D_800CBB6E_main[p->unk2A] = dx * 64.0f * s;
        D_800D20A1_main[p->unk2A] = -(dz * 64.0f * s);
        D_800CDA7C_main[p->unk2A] |= 0x8000;
        D_800D5558_main[p->unk2A] = 0;
        return;
    }
    if (lead) {
        if (p->unk3E != 0) {
            D_800CBB6E_main[p->unk2A] = 0;
            D_800D20A1_main[p->unk2A] = 0;
            if (!(p->unk3E & 7) && p->unk32 != -1) {
                D_800D5558_main[p->unk2A] |= 0x8000;
                D_800CDA7C_main[p->unk2A] |= 0x8000;
            }
            if (--p->unk3E <= 0) {
                p->unk40 = (u8)(rand8() % 15) + 15.0f + p->unk30 * 5;
                p->unk3E = 0;
            }
            return;
        }
        if (--p->unk40 <= 0) {
            p->unk3E = (u8)(rand8() % 15) + 15.0f - p->unk30 * 5;
            p->unk40 = 0;
        }
    }
    if (p->unk32 != -1) {
        blk = func_8010919C_baby_bowser_bonkers(p->unk32);
        if (blk == NULL) {
            p->unk32 = -1;
            return;
        }
        m = &HmfModelData[blk->model];
        dx = m->pos.x - obj->trans.x;
        dz = m->pos.z - obj->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 150.0 && dist > 50.0 && p->unk34 >= 12 - p->unk30 * 2 &&
            func_80107648_baby_bowser_bonkers(obj) == 0 && blk->unk04 != 0) {
            D_800D5558_main[p->unk2A] |= 0x8000;
        }
        if (w->unk38 != 1000.0f) {
            D_800CDA7C_main[p->unk2A] |= 0x8000;
        } else if ((func_801093D4_baby_bowser_bonkers(blk->id) < 15.0f && p->unk34 >= p->unk36 &&
                    p->unk38 <= dist) ||
                   (lead && !(rand8() & 0xF))) {
            func_801091D4_baby_bowser_bonkers(obj->trans.x, obj->trans.z, D_8010BC00_baby_bowser_bonkers);
            for (i = 0; i < 14; i++) {
                if (func_801093D4_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers[i]->id) >= 225) {
                    m = &HmfModelData[D_8010BC00_baby_bowser_bonkers[i]->model];
                    ex = m->pos.x - obj->trans.x;
                    ez = m->pos.z - obj->trans.z;
                    if (sqrtf(ex * ex + ez * ez) <= p->unk38) {
                        /* Retail stores the index into the sorted list, not the block id. */
                        p->unk32 = i;
                        return;
                    }
                }
            }
        }
        if (blk->unk06 != 4 && blk->unk06 != 5 && (blk->unk04 != 0 || func_80107648_baby_bowser_bonkers(obj) != 0)) {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            s = dist / 100.0;
            if (s >= 1.0f) {
                s = 1.0f;
            }
            D_800CBB6E_main[p->unk2A] = dx * 64.0f * s;
            D_800D20A1_main[p->unk2A] = -(dz * 64.0f * s);
        } else if (p->unk34 >= p->unk36) {
            p->unk32 = -1;
        } else {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            s = dist / 100.0;
            if (s >= 1.0f) {
                s = 1.0f;
            }
            D_800CBB6E_main[p->unk2A] = dx * 64.0f * s;
            D_800D20A1_main[p->unk2A] = -(dz * 64.0f * s);
        }
    } else {
        func_801091D4_baby_bowser_bonkers(obj->trans.x, obj->trans.z, D_8010BC00_baby_bowser_bonkers);
        n = 7 - (s32)(p->unk30 * 1.5f);
        if (n <= 0) {
            n = 1;
        }
        p->unk32 = func_8010943C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, n, (s16)(p->unk00 ^ 1));
        if (p->unk32 == -1) {
            p->unk32 = func_8010958C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, n, (s16)(p->unk00 ^ 1));
        }
        p->unk36 = 39.0f - p->unk30 * 7.5f;
        p->unk34 = 0;
    }
    p->unk34++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106CEC_baby_bowser_bonkers);
#endif

void func_801075F4_baby_bowser_bonkers(omObjData* obj, f32 x, f32 z) {
    BkPlayer* p = func_8010B3AC_baby_bowser_bonkers(obj);

    p->unk02++;
    p->unk44 = x;
    p->unk48 = z;
    func_80109E98_baby_bowser_bonkers(p->unk00, p->unk02);
}

s32 func_80107648_baby_bowser_bonkers(omObjData* obj) {
    s32 ret = 1;

    if (!(obj->trans.y >= 44.10000093281269)) {
        ret = 0;
    }
    return ret;
}

/* Swaps the display data of two of an object's models. */
void func_80107678_baby_bowser_bonkers(omObjData* obj, s16 a, s16 b) {
    HmfModel* ma = &HmfModelData[obj->model[a]];
    HmfModel* mb = &HmfModelData[obj->model[b]];
    HmfData* tmp = ma->hmf;

    ma->hmf = mb->hmf;
    mb->hmf = tmp;
}

/* Pushes two players apart (the moving or higher one moves) and keeps both in the arena; once more with
   the roles swapped when the push hit the wall. */
/* NON_MATCHING: masked 41, all from one extra instruction: retail tests (stayX & stayZ) and pushed with two branches and moves sqrt.s through f0; this C folds them. Logic checked against the asm, including retail's z overshoot read from trans.x. */
#ifdef NON_MATCHING
void func_801076D8_baby_bowser_bonkers(omObjData* a, omObjData* b, Vec* va, Vec* vb, s16 again) {
    omObjData* mover;
    omObjData* other;
    func_800E1BA8_minigame_ObjData* wm;
    func_800E1BA8_minigame_ObjData* wo;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 r;
    f32 k;
    f32 lim;
    f32 ox;
    f32 oz;
    u16 pushed;
    s32 stayX;
    s32 stayZ;

    pushed = 0;
    if (again == 0) {
        if ((va->x != 0.0f || va->z != 0.0f) && vb->x == 0.0f && vb->z == 0.0f) {
            mover = a;
            other = b;
        } else if ((vb->x != 0.0f || vb->z != 0.0f) && va->x == 0.0f && va->z == 0.0f) {
            mover = b;
            other = a;
        } else if (a->trans.y > b->trans.y) {
            mover = a;
            other = b;
        } else if (b->trans.y > a->trans.y) {
            mover = b;
            other = a;
        } else {
            mover = a;
            other = b;
        }
    } else {
        mover = a;
        other = b;
    }
    wm = mover->data;
    wo = other->data;
    dx = mover->trans.x - other->trans.x;
    dz = mover->trans.z - other->trans.z;
    dist = sqrtf(dx * dx + dz * dz);
    r = (wm->unk48 + wo->unk48) * 0.75f;
    if (dist < r) {
        if (mover->trans.y >= other->trans.y && mover->trans.y <= other->trans.y + wo->unk34) {
            if (dist != 0.0f) {
                k = r / dist;
            } else {
                if (r == 0.0f) {
                    dx = dz = 0.0f;
                } else {
                    if (other->trans.x >= 0.0f) {
                        dx = r / 1.4142f;
                    } else {
                        dx = -r / 1.4142f;
                    }
                    if (other->trans.z >= 0.0f) {
                        dz = r / 1.4142f;
                    } else {
                        dz = -r / 1.4142f;
                    }
                }
                k = 1.0f;
            }
            mover->trans.x = dx * k + other->trans.x;
            mover->trans.z = dz * k + other->trans.z;
            pushed = 1;
        }
    }
    oz = 0.0f;
    lim = 469.9999809265137 - wm->unk48;
    ox = 0.0f;
    if (mover->trans.x > lim) {
        ox = lim - mover->trans.x;
        mover->trans.x = lim;
    } else if (mover->trans.x < -lim) {
        ox = -lim - mover->trans.x;
        mover->trans.x = -lim;
    }
    /* Retail measures the z overshoot from trans.x. */
    if (mover->trans.z > lim) {
        oz = lim - mover->trans.x;
        mover->trans.z = lim;
    } else if (mover->trans.z < -lim) {
        oz = -lim - mover->trans.x;
        mover->trans.z = -lim;
    }
    lim = 469.9999809265137 - wo->unk48;
    if (other->trans.x > lim) {
        other->trans.x = lim;
    } else if (other->trans.x < -lim) {
        other->trans.x = -lim;
    }
    if (other->trans.z > lim) {
        other->trans.z = lim;
    } else if (other->trans.z < -lim) {
        other->trans.z = -lim;
    }
    stayX = ox == 0.0f;
    stayZ = oz == 0.0f;
    if (!(stayX & stayZ) && pushed) {
        dx = mover->trans.x - other->trans.x;
        dz = mover->trans.z - other->trans.z;
        if (sqrtf(dx * dx + dz * dz) < r && mover->trans.y >= other->trans.y &&
            mover->trans.y <= wo->unk34 * 0.5f + other->trans.y) {
            other->trans.x = ox + other->trans.x;
            other->trans.z = oz + other->trans.z;
            if (other->trans.x > lim) {
                other->trans.x = lim;
            } else if (other->trans.x < -lim) {
                other->trans.x = -lim;
            }
            if (other->trans.z > lim) {
                other->trans.z = lim;
            } else if (other->trans.z < -lim) {
                other->trans.z = -lim;
            }
        }
        if (again == 0) {
            func_801076D8_baby_bowser_bonkers(other, mover, NULL, NULL, 1);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801076D8_baby_bowser_bonkers);
#endif

void func_80107CD8_baby_bowser_bonkers(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 0x10, 0, -1, func_80107D38_baby_bowser_bonkers);
    func_800E1490_minigame(0);
}

void func_80107D38_baby_bowser_bonkers(omObjData* obj) {
    BkGround* g;

    obj->data = g = HuMemAllocTag(sizeof(BkGround), 31000);
    memset(g, 0, sizeof(BkGround));
    g->unk03 = 1;
    g->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 39.100002f, -939.99994f, -939.99994f, 939.99994f, 939.99994f);
    obj->model[0] = func_8000B0A0_main(0x560000, 0x10099);
    func_8001C954_main(obj->model[0]);
    omSetStatBit(obj, 0xA0);
    obj->model[1] = func_8000B0A0_main(0x560001, 0x99);
    obj->model[2] = func_8000B0A0_main(0x560002, 0x99);
    obj->func = func_80107E54_baby_bowser_bonkers;
}

void func_80107E54_baby_bowser_bonkers(omObjData* obj) {
    func_8001E65C_main(obj->model[0], sindf(D_8010B8EC_baby_bowser_bonkers) * 15.0f, -D_8010B8F0_baby_bowser_bonkers,
                       64, 64);
    func_8001F6BC_main(obj->model[0], (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f), 0, 0,
                       (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f));
    func_8001F6F8_main(obj->model[0], 64, 32, 32, 0);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010B8EC_baby_bowser_bonkers += 0.5f;
        if (D_8010B8EC_baby_bowser_bonkers >= 360.0f) {
            D_8010B8EC_baby_bowser_bonkers -= 360.0f;
        }
        D_8010B8F0_baby_bowser_bonkers += 0.2f;
        if (D_8010B8F0_baby_bowser_bonkers >= 64.0f) {
            D_8010B8F0_baby_bowser_bonkers -= 64.0f;
        }
        D_8010B8F4_baby_bowser_bonkers += 2.4f;
        if (D_8010B8F4_baby_bowser_bonkers >= 360.0f) {
            D_8010B8F4_baby_bowser_bonkers -= 360.0f;
        }
    }
}

/* The quadrant of (x, z) outside the central 200-unit square: 1..4, or 0 inside it. */
s32 func_801080D0_baby_bowser_bonkers(f32 x, f32 z) {
    if (fabs(x) < 200.0 && fabs(z) < 200.0) {
        return 0;
    }
    if (x > 0.0f) {
        if (z > 0.0f) {
            return 1;
        }
        return 2;
    }
    if (z > 0.0f) {
        return 3;
    }
    return 4;
}

void func_80108160_baby_bowser_bonkers(void) {
    D_8010BC60_baby_bowser_bonkers = HuMemAllocTag(sizeof(BkBlock) * 14, 31000);
    memset(D_8010BC60_baby_bowser_bonkers, 0, sizeof(BkBlock) * 14);
    omAddObj(2, 8, 0, -1, func_801081C0_baby_bowser_bonkers);
    func_80109704_baby_bowser_bonkers();
}

void func_801081C0_baby_bowser_bonkers(omObjData* obj) {
    BkBlock* b;
    s32 i;

    obj->func = func_8010831C_baby_bowser_bonkers;
    b = D_8010BC60_baby_bowser_bonkers;
    for (i = 0; i < 14; i++, b++) {
        if (i == 0) {
            b->model = func_8000B0A0_main(0x560003, 0x299);
        } else {
            b->model = Hu3DModelLink(D_8010BC60_baby_bowser_bonkers->model);
        }
        b->id = i;
        b->unk04 = -1;
        b->unk08 = 0;
        b->unk0E = 0;
        b->unk0C = 0;
        b->unk0A = 0;
        b->unk06 = 0;
        b->unk10 = 0;
        b->unk12 = 0;
        b->unk14 = 0;
        b->unk18 = 0;
        b->unk1C = D_8010B400_baby_bowser_bonkers[i].y - 110.00000238418579;
        b->unk20 = 65.0f;
        b->unk24 = 70.0f;
        b->unk28 = func_801089CC_baby_bowser_bonkers;
        b->unk2C = func_801089CC_baby_bowser_bonkers;
        Hu3DModelPosSet(b->model, D_8010B400_baby_bowser_bonkers[i].x, D_8010B400_baby_bowser_bonkers[i].y,
                        D_8010B400_baby_bowser_bonkers[i].z - 20.000000298023224);
    }
}

void func_8010831C_baby_bowser_bonkers(omObjData* obj) {
    BkBlock* b;
    HmfModel* m;
    s32 i;

    b = D_8010BC60_baby_bowser_bonkers;
    for (i = 0; i < 14; i++, b++) {
        m = &HmfModelData[b->model];
        if (b->unk2C != NULL) {
            b->unk2C(b);
        }
        m->pos.y = b->unk1C + b->unk18;
        if (b->unk04 != 0) {
            b->unk08 = func_80108454_baby_bowser_bonkers(b);
            if (b->unk08 != -1) {
                HuAudFXPlay(0x4AD);
                b->unk2C = func_80108E90_baby_bowser_bonkers;
            }
        }
        if (m->unk44 < 0.0f && m->unk40 + m->unk44 <= 0.0f) {
            m->unk44 = 0.0f;
        }
        if (b->unk28 == b->unk2C) {
            b->unk0A++;
        } else {
            b->unk28 = b->unk2C;
            b->unk0A = 0;
        }
    }
}

/* A player landing on top of the block: bounce, score, and the player index; -1 none. */
/* NON_MATCHING: retail sign-extends the stick bytes from lbu and masks the dead zone with -(c)&x, keeps 1.2f unhoisted; this C uses lb + branches and hoists 1.2f. Logic checked against the asm. */
#ifdef NON_MATCHING
s16 func_80108454_baby_bowser_bonkers(BkBlock* b) {
    s16 order[12];
    HmfModel* m;
    omObjData* obj;
    func_800E1BA8_minigame_ObjData* w;
    BkPlayer* p;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 r;
    s16 i;
    s16 sx;
    s16 sy;
    s32 port;
    u8 stx;
    u8 sty;

    if (D_8010BC40_baby_bowser_bonkers & 1) {
        for (i = 0; i < D_800EC280_minigame; i++) {
            order[i] = i;
        }
    } else {
        for (i = 0; i < D_800EC280_minigame; i++) {
            order[i] = D_800EC280_minigame - i - 1;
        }
    }
    m = &HmfModelData[b->model];
    for (i = 0; i < D_800EC280_minigame; i++) {
        obj = D_800EC598_minigame[order[i]];
        w = obj->data;
        p = func_8010B3AC_baby_bowser_bonkers(obj);
        dx = obj->trans.x - m->pos.x;
        dz = obj->trans.z - m->pos.z;
        dist = sqrtf(dx * dx + dz * dz);
        r = w->unk48 + b->unk20;
        if (!(obj->trans.y + w->unk34 < m->pos.y) && !(b->unk24 * m->scale.y + m->pos.y < obj->trans.y) &&
            dist < r) {
            if (w->unk38 == 1000.0f) {
                obj->trans.y = b->unk24 * 1.2f + m->pos.y;
                func_800E5798_minigame(obj, 6);
                w->unk38 = -D_800EB744_minigame;
                w->unk50 &= ~0x80;
                w->unk40 = 0.0f;
            } else {
                obj->trans.y = b->unk24 * 1.2f + m->pos.y;
                port = GwPlayer[order[i]].pad;
                stx = D_800CBB6E_main[port];
                sx = abs((s8)stx) >= 9 ? (s8)stx : 0;
                sty = D_800D20A1_main[port];
                sy = abs((s8)sty) >= 9 ? (s8)sty : 0;
                if ((sx != 0) | (sy != 0)) {
                    if (sx > 60) {
                        sx = 60;
                    } else if (sx < -60) {
                        sx = -60;
                    }
                    if (sy > 60) {
                        sy = 60;
                    } else if (sy < -60) {
                        sy = -60;
                    }
                    w->unk3C = atan2df(sx, -sy) + w->unk60;
                    w->unk40 = D_800EB760_minigame * 0.5f * (sqrtf(sx * sx + sy * sy) / 60.0f);
                }
                func_800E5798_minigame(obj, 6);
                w->unk50 &= ~0x80;
                if (D_800CDA7C_main[port] & 0x8000) {
                    w->unk38 = -D_800EB744_minigame;
                } else {
                    w->unk38 = -D_800EB744_minigame * 0.75f;
                }
            }
            func_800E4C88_minigame(obj, p->unk4C + 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
            omVibrate(p->unk28, 10, 0, 10);
            if (++p->unk4C >= 3) {
                p->unk4C = 0;
            }
            func_801075F4_baby_bowser_bonkers(obj, m->pos.x, m->pos.z);
            return order[i];
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108454_baby_bowser_bonkers);
#endif

/* Block state: idle. */
void func_801089CC_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];

    b->unk06 = 0;
    b->unk04 = 0;
    b->unk08 = -1;
    b->unk18 = 0.0f;
    m->unk18 |= 4;
}

/* Block state: rising. */
void func_80108A0C_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];
    f32 t;
    f32 s;

    b->unk06 = 1;
    if (b->unk0C != 0) {
        t = (f32)b->unk0A / (f32)b->unk0C;
    } else {
        t = 1.0f;
    }
    b->unk18 = t * 110.0f;
    s = t * 0.8f + 0.2f;
    m->scale.x = s;
    m->scale.y = s;
    m->scale.z = s;
    if (t > 0.3f) {
        b->unk04 = 0;
    } else {
        b->unk04 = 1;
    }
    if (b->unk10 != 0 && b->unk0A >= 7 && m->unk44 == 0.0f) {
        if (--b->unk10 <= 0) {
            m->unk44 = 1.0f;
            m->unk40 = 0.0f;
        } else {
            b->unk0A--;
        }
    }
    if (t >= 1.0f) {
        b->unk0A = 0;
        b->unk2C = func_80108B84_baby_bowser_bonkers;
    }
}

/* Block state: up, wobbling. */
void func_80108B84_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];

    b->unk06 = 2;
    b->unk04 = 1;
    switch (b->unk12) {
    case 1:
        if (b->unk14 < 20.0f) {
            b->unk14 += 2.5f;
        }
        m->rot.y = sindf((f32)b->unk0A / (f32)b->unk0E * 720.0f) * b->unk14;
        break;
    case 2:
    case 3:
        if (b->unk14 < 20.0f) {
            b->unk14 += 2.5f;
        }
        m->rot.y = -(sindf((f32)b->unk0A / (f32)b->unk0E * 720.0f) * b->unk14);
        break;
    }
    if (b->unk0A >= b->unk0E - 7 && m->unk44 >= 0.0f) {
        m->unk44 = -1.5f;
        m->unk40 = 30.0f;
    }
    if (b->unk0A >= b->unk0E) {
        b->unk0A = 0;
        b->unk2C = func_80108D6C_baby_bowser_bonkers;
    }
}

/* Block state: sinking. */
void func_80108D6C_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];
    f32 t;
    f32 s;

    b->unk06 = 3;
    if (b->unk0C != 0) {
        t = (f32)b->unk0A / (f32)b->unk0C;
    } else {
        t = 1.0f;
    }
    b->unk18 = (1.0f - t) * 110.0f;
    s = (1.0f - t) * 0.8f + 0.2f;
    m->scale.x = s;
    m->scale.y = s;
    m->scale.z = s;
    if (t < 0.3f) {
        b->unk04 = 0;
    } else {
        b->unk04 = 1;
    }
    if (t >= 1.0f) {
        m->unk18 |= 4;
        b->unk0A = 0;
        b->unk2C = func_801089CC_baby_bowser_bonkers;
    }
}

/* Block state: stomped flat. */
void func_80108E90_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];
    f32 t;

    b->unk06 = 4;
    b->unk04 = 0;
    b->unk18 = 110.0f;
    t = 1.0f - (f32)b->unk0A / 5.0f;
    if (t <= 0.0f) {
        t = 0.0f;
    }
    m->scale.x = 1.0f;
    m->scale.z = 1.0f;
    m->scale.y = 0.4f - t * 0.35f;
    m->unk44 = 0.0f;
    if ((f32)b->unk0A >= 15.0f) {
        b->unk0A = 0;
        b->unk2C = func_80108F9C_baby_bowser_bonkers;
    }
}

/* Block state: stomped, shrinking away. */
void func_80108F9C_baby_bowser_bonkers(BkBlock* b) {
    HmfModel* m = &HmfModelData[b->model];
    f32 s;

    b->unk06 = 5;
    b->unk04 = 0;
    b->unk18 -= 9.166667f;
    s = m->scale.z - 0.2f;
    m->scale.z = s;
    m->scale.x = s;
    if (s <= 0.1f) {
        m->scale.x = m->scale.z = 0.0f;
    }
    if (b->unk18 <= 0.0f) {
        m->unk18 |= 4;
        m->scale.y = 1.0f;
        b->unk0A = 0;
        b->unk2C = func_801089CC_baby_bowser_bonkers;
    }
}

/* Raises block `id` over `rise` frames, up for `stay` frames; the id, or -1 if it is busy. */
s32 func_80109080_baby_bowser_bonkers(s32 id, s16 rise, s16 stay) {
    BkBlock* b;
    HmfModel* m;

    if (id >= 14) {
        return -1;
    }
    if (id < 0) {
        return -1;
    }
    b = &D_8010BC60_baby_bowser_bonkers[id];
    m = &HmfModelData[b->model];
    if (b->unk06 != 0) {
        return -1;
    }
    b->unk0C = rise;
    b->unk0E = stay;
    b->unk0A = 0;
    b->unk10 = 15;
    b->unk14 = 0.0f;
    if (!(rand8() & 3)) {
        b->unk12 = (u8)(rand8() % 3) + 1;
    } else {
        b->unk12 = 0;
    }
    b->unk2C = func_80108A0C_baby_bowser_bonkers;
    m->unk18 &= ~4;
    m->rot.x = m->rot.y = m->rot.z = 0.0f;
    m->unk40 = m->unk44 = 0.0f;
    return id;
}

BkBlock* func_8010919C_baby_bowser_bonkers(s32 id) {
    if (id < 14) {
        if (id >= 0) {
            return &D_8010BC60_baby_bowser_bonkers[id];
        }
    }
    return NULL;
}

/* Fills list[14] with the blocks, nearest to (x, z) first. */
void func_801091D4_baby_bowser_bonkers(f32 x, f32 z, BkBlock** list) {
    HmfModel* ma;
    HmfModel* mb;
    BkBlock* tmp;
    f32 dx;
    f32 dz;
    f32 da;
    s32 i;
    s32 j;

    for (i = 0; i < 14; i++) {
        list[i] = &D_8010BC60_baby_bowser_bonkers[i];
    }
    for (i = 0; i < 13; i++) {
        for (j = i + 1; j < 14; j++) {
            ma = &HmfModelData[list[i]->model];
            mb = &HmfModelData[list[j]->model];
            dx = ma->pos.x - x;
            dz = ma->pos.z - z;
            da = sqrtf(dx * dx + dz * dz);
            dx = mb->pos.x - x;
            dz = mb->pos.z - z;
            if (sqrtf(dx * dx + dz * dz) < da) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}

/* 1 if the block is rising, or up with more than `margin` frames left. */
s32 func_80109388_baby_bowser_bonkers(BkBlock* b, s32 margin) {
    if (b->unk08 != 0) {
        if (b->unk06 == 1 || (b->unk06 == 2 && b->unk0A > b->unk0E - margin)) {
            return 1;
        }
        return 0;
    }
    return 0;
}

/* Frames block `id` has left in its rise/up states. */
s32 func_801093D4_baby_bowser_bonkers(s32 id) {
    BkBlock* b = &D_8010BC60_baby_bowser_bonkers[id];

    if (b->unk08 != 0) {
        switch (b->unk06) {
        case 1:
            return b->unk0E;
        case 2:
            return b->unk0E - b->unk0A;
        default:
            return 0;
        }
    }
    return 0;
}

/* A random one of the first `max` live blocks in `list` outside player `player`'s quadrant; -1 none. */
s32 func_8010943C_baby_bowser_bonkers(BkBlock** list, s32 max, s32 player) {
    s32 ids[16];
    HmfModel* m;
    s32 quad;
    s32 i;
    s32 n;

    quad = func_801080D0_baby_bowser_bonkers(D_800EC598_minigame[player]->trans.x,
                                             D_800EC598_minigame[player]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        m = &HmfModelData[list[i]->model];
        if (func_80109388_baby_bowser_bonkers(list[i], 9) != 0 &&
            func_801080D0_baby_bowser_bonkers(m->pos.x, m->pos.z) != quad) {
            ids[n++] = list[i]->id;
            if (n >= max) {
                break;
            }
        }
    }
    if (n != 0) {
        return ids[rand8() % n];
    }
    return -1;
}

/* As func_8010943C, for blocks flagged unk04. */
s32 func_8010958C_baby_bowser_bonkers(BkBlock** list, s32 max, s32 player) {
    s32 ids[16];
    HmfModel* m;
    s32 quad;
    s32 i;
    s32 n;

    quad = func_801080D0_baby_bowser_bonkers(D_800EC598_minigame[player]->trans.x,
                                             D_800EC598_minigame[player]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        m = &HmfModelData[list[i]->model];
        if (list[i]->unk04 != 0 && func_801080D0_baby_bowser_bonkers(m->pos.x, m->pos.z) != quad) {
            ids[n++] = list[i]->id;
            if (n >= max) {
                break;
            }
        }
    }
    if (n != 0) {
        return ids[rand8() % n];
    }
    return -1;
}

/* 1 when every block is idle. */
s32 func_801096D0_baby_bowser_bonkers(void) {
    BkBlock* b;
    s32 i;

    for (i = 0, b = D_8010BC60_baby_bowser_bonkers; i < 14; i++, b++) {
        if (b->unk06 != 0) {
            return 0;
        }
    }
    return 1;
}

/* Deals the four patterns of each difficulty level into D_8010BC68 and shuffles them. */
void func_80109704_baby_bowser_bonkers(void) {
    BkPattern* tmp;
    s32 a;
    s32 b;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_8010BC68_baby_bowser_bonkers[i][j] = D_8010B8F8_baby_bowser_bonkers[i][j % D_8010B908_baby_bowser_bonkers[i]];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 255; j++) {
            a = rand8() & 3;
            b = rand8() & 3;
            if (a != b) {
                tmp = D_8010BC68_baby_bowser_bonkers[i][a];
                D_8010BC68_baby_bowser_bonkers[i][a] = D_8010BC68_baby_bowser_bonkers[i][b];
                D_8010BC68_baby_bowser_bonkers[i][b] = tmp;
            }
        }
    }
}

u16 func_8010984C_baby_bowser_bonkers(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

void func_80109890_baby_bowser_bonkers(void) {
    BkCounter* c;
    s32 i;

    D_8010BCA8_baby_bowser_bonkers = HuMemAllocTag(0x20, 31000);
    D_8010BCAC_baby_bowser_bonkers = HuMemAllocTag(sizeof(BkCounter) * 2, 31000);
    D_8010BCA8_baby_bowser_bonkers[0] = func_8010984C_baby_bowser_bonkers(0x31);
    D_8010BCA8_baby_bowser_bonkers[1] = func_8010984C_baby_bowser_bonkers(0x560004);
    for (i = 0, c = D_8010BCAC_baby_bowser_bonkers; i < 2; i++, c++) {
        memset(c, 0, sizeof(BkCounter));
        func_80109BFC_baby_bowser_bonkers(i, GwPlayer[D_8010BC58_baby_bowser_bonkers[i].unk28].chr);
    }
    omAddObj(0x1E, 0, 0, -1, func_80109990_baby_bowser_bonkers);
}

/* The two score counters. */
void func_80109990_baby_bowser_bonkers(omObjData* obj) {
    BkCounter* c;
    u16 digit[2];
    f32 scale;
    s16 i;

    for (i = 0, c = D_8010BCAC_baby_bowser_bonkers; i < 2; i++, c++) {
        digit[0] = c->value / 10;
        digit[1] = c->value - digit[0] * 10;
        if (digit[0] >= 10) {
            digit[0] = 9;
        }
        if (digit[1] >= 10) {
            digit[1] = 9;
        }
        func_80054FF8_main(c->grp, 0, (s16)digit[0]);
        func_80054FF8_main(c->grp, 1, (s16)digit[1]);
        if (c->value < c->target && c->timer == 0) {
            c->timer = 12;
            if (++c->value == 10) {
                HuSprAttrReset(c->grp, 0, 0x8000);
            }
        }
        scale = sindf(c->timer / 12.0f * 180.0f) * 0.5f + 1.0f;
        func_80054904_main(c->grp, 0, c->x + c->off[0] * scale, c->y);
        func_80054904_main(c->grp, 1, c->x + c->off[1] * scale, c->y);
        HuSprScaleSet(c->grp, 0, scale, scale);
        HuSprScaleSet(c->grp, 1, scale, scale);
        if (c->timer != 0) {
            c->timer--;
        }
    }
}

/* Builds player `idx`'s score counter: two digits, the character face and a backing. */
/* NON_MATCHING: retail sign-extends HuSprGrpCreate's result before storing it (a call declared int-returning there); include/ declares it s16, so this C saves the two shift instructions. Otherwise identical. */
#ifdef NON_MATCHING
void func_80109BFC_baby_bowser_bonkers(s32 idx, s32 chr) {
    BkCounter* c;
    s16 grp;
    s16 x;
    s16 y;
    s32 i;

    c = &D_8010BCAC_baby_bowser_bonkers[idx];
    c->file = func_8010984C_baby_bowser_bonkers(D_8010B918_baby_bowser_bonkers[chr]);
    grp = HuSprGrpCreate(4, 0);
    c->grp = grp;
    x = 266;
    if (idx == 0) {
        x = 56;
    }
    c->x = x + 8;
    c->y = y = 30;
    c->off[0] = -6;
    c->off[1] = 6;
    c->timer = 0;
    c->target = 0;
    c->value = 0;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            HuSprAttrSet(grp, i, 0x8000);
        case 1:
            func_80055024_main(grp, i, D_8010BCA8_baby_bowser_bonkers[0], 0);
            func_80054904_main(grp, i, c->x + c->off[i], y);
            break;
        case 2:
            func_80055024_main(grp, i, c->file, 0);
            func_80054904_main(grp, i, x - 18, y);
            break;
        case 3:
            func_80055024_main(grp, i, D_8010BCA8_baby_bowser_bonkers[1], 0);
            func_80054904_main(grp, i, x, y);
            HuSprScaleSet(grp, i, 1.0f, 1.0f);
            func_80055484_main(grp, i, 0, 0, 0xFF, 0xA0);
            break;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        HuSprPriSet(grp, i, i - 16);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109BFC_baby_bowser_bonkers);
#endif

/* NON_MATCHING: masked 0; v0/v1 swapped. */
// decomp-permuter
void func_80109E98_baby_bowser_bonkers(s32 idx, s16 score)
{
  s32 offset = idx * (sizeof(BkCounter));
  u8 *new_var;
  new_var = ((u8 *) D_8010BCAC_baby_bowser_bonkers) + offset;
  ((BkCounter *) new_var)->target = score;
}

void func_80109EB8_baby_bowser_bonkers(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = -708.8f;
    Center.z = -781.8f;
    CRot.x = 318.38f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2938.0f;
    func_8010AB14_baby_bowser_bonkers(0);
    func_8010AB14_baby_bowser_bonkers(1);
    D_8010BCF8_baby_bowser_bonkers = D_8010BCFC_baby_bowser_bonkers = D_8010BD00_baby_bowser_bonkers = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010A6D8_baby_bowser_bonkers);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}


void func_80109FE8_baby_bowser_bonkers(void) {
    BkCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010B938_baby_bowser_bonkers) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & 0x200) {
                    c.center.x = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 0x100) {
                    c.center.x = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x800) {
                    c.center.z = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x400) {
                    c.center.z = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 8) {
                    c.center.y = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 4) {
                    c.center.y = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 1) {
                    c.zoom = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 2) {
                    c.zoom = -(2.0 * speed);
                }
                c.center.x += Center.x;
                c.center.y += Center.y;
                c.center.z += Center.z;
                c.rot.x += CRot.x;
                c.rot.y += CRot.y;
                c.rot.z += CRot.z;
                c.zoom += CZoom;
                func_8010AD00_baby_bowser_bonkers(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010B93C_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010B93C_baby_bowser_bonkers--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010B940_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010B940_baby_bowser_bonkers--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 104, D_800D5218_main);
            break;
        case 3:
            D_8010B938_baby_bowser_bonkers = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010B938_baby_bowser_bonkers == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010B938_baby_bowser_bonkers++ >= 4) {
            D_8010B938_baby_bowser_bonkers = 0;
        }
    }
}

void func_8010A6D8_baby_bowser_bonkers(omObjData *obj) {
    f32 t;

    if (D_8010BCFC_baby_bowser_bonkers <= 0) {
        func_8010AEF0_baby_bowser_bonkers(0);
        D_8010BD00_baby_bowser_bonkers = 0;
        return;
    }
    if (D_8010BCF8_baby_bowser_bonkers == 0) {
        Center.x = D_8010BCB0_baby_bowser_bonkers[0].center.x;
        Center.y = D_8010BCB0_baby_bowser_bonkers[0].center.y;
        Center.z = D_8010BCB0_baby_bowser_bonkers[0].center.z;
        CRot.x = D_8010BCB0_baby_bowser_bonkers[0].rot.x;
        CRot.y = D_8010BCB0_baby_bowser_bonkers[0].rot.y;
        CRot.z = D_8010BCB0_baby_bowser_bonkers[0].rot.z;
        CZoom = D_8010BCB0_baby_bowser_bonkers[0].zoom;
        BK_WRAP(CRot.x);
        BK_WRAP(CRot.y);
        BK_WRAP(CRot.z);
        D_8010BCFC_baby_bowser_bonkers = 0;
    } else {
        t = (f32)D_8010BCF8_baby_bowser_bonkers / (f32)D_8010BCFC_baby_bowser_bonkers;
        Center.x = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.x, D_8010BCB0_baby_bowser_bonkers[1].center.x);
        Center.y = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.y, D_8010BCB0_baby_bowser_bonkers[1].center.y);
        Center.z = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.z, D_8010BCB0_baby_bowser_bonkers[1].center.z);
        CRot.x = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.x, D_8010BCB0_baby_bowser_bonkers[1].rot.x);
        CRot.y = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.y, D_8010BCB0_baby_bowser_bonkers[1].rot.y);
        CRot.z = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.z, D_8010BCB0_baby_bowser_bonkers[1].rot.z);
        CZoom = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].zoom, D_8010BCB0_baby_bowser_bonkers[1].zoom);
        BK_WRAP(CRot.x);
        BK_WRAP(CRot.y);
        BK_WRAP(CRot.z);
        if (D_8010BCF8_baby_bowser_bonkers > 0) {
            D_8010BCF8_baby_bowser_bonkers--;
        } else {
            D_8010BCF8_baby_bowser_bonkers++;
        }
    }
    D_8010BD00_baby_bowser_bonkers = 1;
    func_8010AEF0_baby_bowser_bonkers(0);
}

void func_8010AB14_baby_bowser_bonkers(s32 idx) {
    BK_WRAP(CRot.x);
    BK_WRAP(CRot.y);
    BK_WRAP(CRot.z);
    D_8010BCB0_baby_bowser_bonkers[idx].center.x = Center.x;
    D_8010BCB0_baby_bowser_bonkers[idx].center.y = Center.y;
    D_8010BCB0_baby_bowser_bonkers[idx].center.z = Center.z;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.x = CRot.x;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.y = CRot.y;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.z = CRot.z;
    D_8010BCB0_baby_bowser_bonkers[idx].zoom = CZoom;
    D_8010BCB0_baby_bowser_bonkers[idx].unk1C = D_8010BCB0_baby_bowser_bonkers[idx].unk20 = 0.0f;
}

void func_8010AD00_baby_bowser_bonkers(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010BCF8_baby_bowser_bonkers = frames - 1;
        D_8010BCFC_baby_bowser_bonkers = frames;
        if (cx != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = cx;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = cy;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = cz;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = rx;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = ry;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = rz;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = zoom;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = CZoom;
        }
        func_8010AB14_baby_bowser_bonkers(1);
    }
}

void func_8010AEF0_baby_bowser_bonkers(s32 idx) {
    HuCamera *cam = &gCameraList[idx];
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}

f32 func_8010B044_baby_bowser_bonkers(f32 a, f32 b) {
    f32 d;

    if (a >= 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    if (b >= 360.0f) {
        b -= 360.0f;
    } else if (b < 0.0f) {
        b += 360.0f;
    }
    d = a - b;
    if (d <= -180.0f) {
        d += 360.0f;
    } else if (d >= 180.0f) {
        d -= 360.0f;
    }
    return d;
}

f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    BK_WRAP(target);
    BK_WRAP(cur);
    d = fmod(target - cur + 360.0, 360.0);
    if (d < 180.0) {
        if (d <= step) {
            v = d;
        } else {
            v = step;
        }
    } else {
        e = 360.0 - d;
        if (e <= step) {
            v = -e;
        } else {
            v = -step;
        }
    }
    v += cur;
    BK_WRAP(v);
    return v;
}

f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 a, f32 b) {
    return func_8010B148_baby_bowser_bonkers(b, a, fabsf(func_8010B044_baby_bowser_bonkers(b, a) * t));
}

void func_8010B380_baby_bowser_bonkers(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010B3AC_baby_bowser_bonkers(omObjData *obj) {
    BkPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}
