#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

// pz A: Mario's Puzzle Party (4 players, each drops two-block pieces into a 4-column well)

/* One board cell (board[player][column][row]); columns 1..4 are the well, 0 and 5 are walls */
typedef struct PzCell {
    /* 0x00 */ s32 unk0; /* batch sprite handle */
    /* 0x04 */ s32 unk4; /* x */
    /* 0x08 */ s32 unk8; /* y */
    /* 0x0C */ s32 unkC; /* colour (6 = garbage, -1 none) */
    /* 0x10 */ s32 unk10; /* 0 empty, 1 lower half, 2 upper half, 3 single */
} PzCell; /* size 0x14 */

/* A falling piece (the current one per player in D_80116238, the next one in D_80116308) */
typedef struct PzPiece {
    /* 0x00 */ s32 unk0; /* esprite slot */
    /* 0x04 */ s32 unk4; /* player */
    /* 0x08 */ s32 unk8; /* lower block handle */
    /* 0x0C */ s32 unkC; /* upper block handle */
    /* 0x10 */ s32 unk10; /* x on the column grid */
    /* 0x14 */ s32 unk14; /* column */
    /* 0x18 */ s32 unk18; /* row */
    /* 0x1C */ s32 unk1C; /* lower colour (7 = special piece) */
    /* 0x20 */ s32 unk20; /* upper colour */
    /* 0x24 */ s32 unk24; /* sideways move: -1, 0, 1 */
    /* 0x28 */ s32 unk28; /* dropped */
    /* 0x2C */ f32 unk2C; /* x */
    /* 0x30 */ f32 unk30; /* y */
} PzPiece; /* size 0x34 */

/* CPU player state (D_80114DE0) */
typedef struct PzAi {
    /* 0x00 */ s32 unk0[4]; /* first free row per column */
    /* 0x10 */ s32 unk10[2][4]; /* colour matches per column, for each half */
    /* 0x30 */ s32 unk30; /* mode */
    /* 0x34 */ s32 unk34; /* target column */
    /* 0x38 */ s32 unk38; /* swap halves */
    /* 0x3C */ s32 unk3C; /* delay */
    /* 0x40 */ u16 unk40; /* held buttons */
    /* 0x42 */ u16 unk42; /* pressed buttons */
} PzAi; /* size 0x44 */

/* Board origin per player (data) */
typedef struct PzOrigin {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} PzOrigin; /* size 8 */

/* Squash job (func_80109160's user data) */
typedef struct PzSquash {
    /* 0x00 */ s32 unk0; /* player */
    /* 0x04 */ s32 unk4; /* column */
    /* 0x08 */ s32 unk8; /* special piece sprite group */
    /* 0x0C */ s32 unkC; /* x */
    /* 0x10 */ PzPiece* unk10;
    /* 0x14 */ s32 unk14[2];
} PzSquash; /* size 0x1C */

/* Debris of a cleared block (D_80114EF0) */
typedef struct PzDebris {
    /* 0x00 */ s32 unk0; /* batch handle */
    /* 0x04 */ s32 unk4; /* in use */
    /* 0x08 */ f32 unk8; /* x */
    /* 0x0C */ f32 unkC; /* y */
    /* 0x10 */ f32 unk10; /* x speed */
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; /* y speed */
} PzDebris; /* size 0x1C */

/* Background sparkle (func_8010D490's user data, from the table at D_80110168) */
typedef struct PzSparkle {
    /* 0x00 */ s32 unk0; /* sprite group */
    /* 0x04 */ s32 unk4; /* spread: 0 x, 1 y, else both */
    /* 0x08 */ s32 unk8; /* drift: 1 x, 0 y, else both */
    /* 0x0C */ f32 unkC; /* x */
    /* 0x10 */ f32 unk10; /* y */
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; /* x speed */
    /* 0x1C */ f32 unk1C; /* y speed */
    /* 0x20 */ f32 unk20; /* scale */
} PzSparkle; /* size 0x24 */

/* Chain counter colour and size per chain length (D_801100B0[n], n >= 1; entry 0 is D_801100A0[2..3]) */
typedef struct PzChain {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
    /* 0x0C */ f32 scale;
} PzChain; /* size 0x10 */

/* func_8010AD20's local block; func_801098A0 is given its address */
typedef struct PzLocal {
    /* 0x00 */ s32 player;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 height[4];
    /* 0x18 */ s32 flag[4];
} PzLocal; /* size 0x28 */

/* A matched block (D_801163F0, D_801163E8 entries) */
typedef struct PzMatch {
    /* 0x00 */ s32 col;
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 state;
} PzMatch; /* size 0xC */

/* A block falling into place (func_80108C80's user data) */
typedef struct PzFall {
    /* 0x00 */ s32 unk0; /* player */
    /* 0x04 */ s32 unk4; /* handle */
    /* 0x08 */ s32 unk8; /* x */
    /* 0x0C */ s32 unkC; /* y */
    /* 0x10 */ s32 unk10; /* colour */
    /* 0x14 */ s32 unk14; /* state */
    /* 0x18 */ s32 unk18;
} PzFall; /* size 0x1C */

// main
void Hu3DAnimInit(s32);
void func_80021BE0_main(s32* arg0, s32 n);
void func_800142A0_main(s32);
void func_8004A208_main(void);
void func_8005A6B0_main(void);
void func_8000B5F0_main(u8 arg0);
s32 func_8000B638_main(void);
void func_8000BB54_main(u16 arg0);
void func_8000BBD4_main(u16 spriteId, s16 x, s16 y);
void func_8000BCC8_main(u16, s32);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
s16 func_8000B838_main(s32 arg0);
s16 InitEspriteSlot(s16 arg0, s16 arg1, u16 arg2);
void func_80019C00_main(void* data);
void* HuMemAlloc(s32 size);
void* HuMemAllocTag(s32 size, s16 tag);
s16 func_8004AC98_main(s16, s16);
void HuSprAttrReset(s16 group, s16 member, s32 attr);
extern s16 D_800EB930_minigame;
extern s32 D_800EBEB0_minigame[];
void func_8004AB0C_main(s32);
void func_8001F38C_main(s32, s32, s32);
void func_8005F524_main(void);
u16 func_80049F98_main(void);
extern u8 D_800D6A90_main;
void func_8000BB94_main(u16 arg0);
void func_800552DC_main(s16, s16, f32);
void func_8011006C_marios_puzzle_party(s32 player, s32 y);
void func_8010CFF8_marios_puzzle_party(omObjData* obj);
void omVibrate(s16 player, s16 duration, s16 off, s16 on);
f32 SprPos3DSet(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z);
void SprPosPerspectiveSet(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z);

extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];
extern u8 D_800CE20A_main;
extern struct {
    s32 unk0;
    s16 unk4;
} D_800CB890_main; /* other units see an f32 here */
void* DataRead(s32 dirAndFile);
void DataClose(void* data);
s16 func_80055810_main(void*);
void func_8000BC48_main(u16, s32);
void func_8000B880_main(s16 sprite, f32 r, f32 g, f32 b);
void func_8010F570_marios_puzzle_party(s16 n);
void func_8010F678_marios_puzzle_party(s32 file, s16 n);

// 1FD760
s16 func_8010FEDC_marios_puzzle_party(s16 id, f32 x, f32 y);
void func_8010FF78_marios_puzzle_party(s16 handle, f32 x, f32 y);
void func_8010FFBC_marios_puzzle_party(s16 handle, f32 sx, f32 sy);
void func_80110000_marios_puzzle_party(s16 handle);

// this unit
void func_80105C98_marios_puzzle_party(void);
void func_80105D50_marios_puzzle_party(s32 player, s32 color, s32 state, s32 col, s32 row);
u16 func_80105E88_marios_puzzle_party(s32 player);
u16 func_80105FCC_marios_puzzle_party(s32 player, s32 mask);
void func_8010604C_marios_puzzle_party(void);
s32 func_80106A44_marios_puzzle_party(s32 player, s32 color, s32 state, s32 x, s32 y);
s32 func_80106ACC_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir);
s32 func_80106BB0_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir);
s32 func_80106C98_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy);
s32 func_80106E40_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy);
s32 func_80107000_marios_puzzle_party(s32 player, s32 col);
s32 func_80107070_marios_puzzle_party(s32 player, s32 col);
s32 func_80107108_marios_puzzle_party(s32 player, s32 col);
s32 func_8010718C_marios_puzzle_party(s32 col, s32 row);
void func_80107224_marios_puzzle_party(s32 player, s32 col, s32 row);
void func_80107400_marios_puzzle_party(s32 player, s32 col, s32 row, s32 color, s32 state);
void func_80107880_marios_puzzle_party(s32 player, s32 col, s32 row, s32 color, s32 state);
void func_80107BB0_marios_puzzle_party(s32 player);
void func_80107CBC_marios_puzzle_party(void);
void func_80108568_marios_puzzle_party(s32 player, s32 counter);
void func_801088F4_marios_puzzle_party(s32 player, PzPiece* piece);
s32 func_80108A50_marios_puzzle_party(s32 player, s32 kind, s32 color, s32 col, s32 row);
void func_80108BB0_marios_puzzle_party(void);
void func_80108C80_marios_puzzle_party(void);
void func_8010913C_marios_puzzle_party(void);
void func_80109160_marios_puzzle_party(void);
s32 func_8010961C_marios_puzzle_party(s32 player, s32 x, s32 handle, PzPiece* piece, s32 first);
void func_801098A0_marios_puzzle_party(void);
void func_80109C04_marios_puzzle_party(s32 player, s32 color, s32 state, s32 col, s32 row, s32 arg5);
void func_80109D24_marios_puzzle_party(void);
void func_8010A0D8_marios_puzzle_party(void);
s32 func_8010A4B4_marios_puzzle_party(s32 player, s32 x, s32 y);
void func_8010A588_marios_puzzle_party(void);
void func_8010A958_marios_puzzle_party(void);
void func_8010AD20_marios_puzzle_party(void);
void func_8010CF4C_marios_puzzle_party(void);
void func_8010D290_marios_puzzle_party(s32 player, s32 col, s32 row);
void func_8010D46C_marios_puzzle_party(void);
void func_8010D490_marios_puzzle_party(void);
void func_8010D8E8_marios_puzzle_party(void);
void func_8010D9AC_marios_puzzle_party(void);
void func_8010DB98_marios_puzzle_party(void);
void func_8010E12C_marios_puzzle_party(void);
void func_8010EAA0_marios_puzzle_party(void);
void func_8010ECD8_marios_puzzle_party(void);
void func_8010EEB0_marios_puzzle_party(void);
void func_8010EF30_marios_puzzle_party(void);

// data
/* Background sparkle spots */
typedef struct PzSparkleInit {
    /* 0x00 */ s32 spread;
    /* 0x04 */ s32 drift;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 vx;
    /* 0x14 */ s32 vy;
} PzSparkleInit; /* size 0x18 */

extern PzOrigin D_80110080_marios_puzzle_party[4];
extern D_80111B50_vine_with_me_Struct D_80110140_marios_puzzle_party;
extern PzSparkleInit D_80110168_marios_puzzle_party[8];
extern PzOrigin D_801100A0_marios_puzzle_party[4];
extern PzChain D_801100B0_marios_puzzle_party[9]; /* overlaps D_801100A0[2..3] */

// bss
extern PzCell D_801102E0_marios_puzzle_party[4][6][40]; /* D_80110600, D_80110920, D_80110C40 are views */
extern PzAi D_80114DE0_marios_puzzle_party[4]; /* D_80114E20 is a view (player 0's unk40.. tail) */
extern PzDebris D_80114EF0_marios_puzzle_party[160];
extern s32 D_80116070_marios_puzzle_party[7];
/* sprite data handles (func_80055810_main results, read back through their low halves) */
extern s32 D_8011608C_marios_puzzle_party;
extern s32 D_80116090_marios_puzzle_party;
extern s32 D_80116094_marios_puzzle_party;
extern s32 D_80116098_marios_puzzle_party;
extern s32 D_8011609C_marios_puzzle_party;
extern s32 D_801160A0_marios_puzzle_party;
extern s32 D_801160A4_marios_puzzle_party;
extern s32 D_801160A8_marios_puzzle_party;
extern s32 D_801160AC_marios_puzzle_party;
extern s32 D_801160B0_marios_puzzle_party;
extern s32 D_801160B4_marios_puzzle_party;
extern s32 D_801160B8_marios_puzzle_party;
extern s32 D_801160C0_marios_puzzle_party[4];
extern s32 D_801160D0_marios_puzzle_party;
extern s32 D_801160D4_marios_puzzle_party;
extern s32 D_801160D8_marios_puzzle_party;
extern s32 D_801160DC_marios_puzzle_party;
extern s32 D_801160E0_marios_puzzle_party;
extern s32 D_801160E4_marios_puzzle_party; /* D_801160E7 is its low byte */
extern s32 D_801160E8_marios_puzzle_party;
extern s32 D_80116198_marios_puzzle_party[4];
extern s32 D_801161B8_marios_puzzle_party[4];
extern s32 D_801161C8_marios_puzzle_party[4];
extern s32 D_801167B0_marios_puzzle_party[30][2]; /* D_801167B4 is a view */
extern s32 D_801168A0_marios_puzzle_party[4];
extern s32 D_801160F0_marios_puzzle_party[4];
extern s32 D_80116108_marios_puzzle_party[4];
extern s32 D_80116118_marios_puzzle_party[4];
extern s32 D_80116128_marios_puzzle_party[4];
extern s32 D_80116138_marios_puzzle_party[4];
extern s32 D_80116148_marios_puzzle_party[4];
extern s32 D_80116158_marios_puzzle_party;
extern s32 D_8011615C_marios_puzzle_party;
extern s32 D_80116168_marios_puzzle_party[4];
extern s32 D_80116178_marios_puzzle_party[4];
extern s32 D_80116188_marios_puzzle_party[4];
extern s32 D_801161A8_marios_puzzle_party[4];
extern s32 D_801161D8_marios_puzzle_party[4];
extern s32 D_801161E8_marios_puzzle_party[4];
extern s32 D_801161F8_marios_puzzle_party[4];
extern s32 D_80116208_marios_puzzle_party[4];
extern s32 D_80116218_marios_puzzle_party[4];
extern s32 D_80116228_marios_puzzle_party[4];
extern PzPiece D_80116238_marios_puzzle_party[4];
extern PzPiece D_80116308_marios_puzzle_party[4];
extern s32 D_80116100_marios_puzzle_party;
extern Process* D_801163D8_marios_puzzle_party[4];
extern s32 D_801163E8_marios_puzzle_party;
extern PzMatch D_801163F0_marios_puzzle_party[80];

#ifdef NON_MATCHING
/* ObjectSetup: camera, the per-player games, board placement, sparkles, setup, pause watcher. */
void func_801059A0_marios_puzzle_party(void) {
    Process* proc;
    PzSparkle* sp;
    s32 i;
    u8 cam;

    Hu3DAnimInit(0x32);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(0xAA, 0xC8);
    i = 0;
    func_8004A208_main();
    func_800E1804_minigame();
    func_8005A6B0_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 16.0f, 500.0f, 5000.0f);
    CZoom = 800.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    omAddPrcObj(func_8010EF30_marios_puzzle_party, 0x4001, 0x800, 0);
    for (; i < 4; i++) {
        proc = omAddPrcObj(func_8010AD20_marios_puzzle_party, 0x4001, 0x3000, 0);
        D_801163D8_marios_puzzle_party[i] = proc;
        proc->user_data = (void*)i;
    }
    D_80116100_marios_puzzle_party = i;
    omAddPrcObj(func_8010DB98_marios_puzzle_party, 0x4001, 0x800, 0);
    for (i = 0; i < 8; i++) {
        proc = omAddPrcObj(func_8010D490_marios_puzzle_party, 0x4001, 0x800, 0);
        sp = HuMemAlloc(sizeof(PzSparkle));
        proc->user_data = sp;
        sp->unkC = D_80110168_marios_puzzle_party[i].x;
        sp->unk10 = D_80110168_marios_puzzle_party[i].y;
        sp->unk18 = D_80110168_marios_puzzle_party[i].vx;
        sp->unk1C = D_80110168_marios_puzzle_party[i].vy;
        sp->unk4 = D_80110168_marios_puzzle_party[i].spread;
        sp->unk8 = D_80110168_marios_puzzle_party[i].drift;
    }
    func_8010604C_marios_puzzle_party();
    omAddPrcObj(func_80105C98_marios_puzzle_party, 0x4001, 0x800, 0);
    omPrcSetStatBit(omAddPrcObj(func_8010D9AC_marios_puzzle_party, 0x4001, 0x800, 0), 0xA0);
    func_800E5EA0_minigame(&D_80110140_marios_puzzle_party);
    D_800EB930_minigame = 0x38;
    WipeCreateIn(0xFF, 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801059A0_marios_puzzle_party);
#endif

/* Quit to the minigame menu when asked from the pause menu. */
void func_80105C98_marios_puzzle_party(void) {
    s32 quit = FALSE;

    while (TRUE) {
        if (D_800D530C_main == 1) {
            quit = TRUE;
        }
        if (quit) {
            D_801160E8_marios_puzzle_party = 1;
            WipeCreateOut(0, 0x14);
            HuAudSeqFadeOut(0x1E);
            func_8004AB0C_main(0x1E);
            while (WipeStatGet() != 0) {
                HuPrcVSleep();
            }
            func_8001F38C_main(0, 0, 0);
            func_8005F524_main();
            omOvlKill();
            omOvlReturnEx(1);
        }
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
void func_80105D50_marios_puzzle_party(s32 player, s32 color, s32 state, s32 col, s32 row) {
    PzCell* cells = D_801102E0_marios_puzzle_party[player][col];
    PzCell* cell = &cells[row];

    cell->unkC = color;
    cell->unk4 = col * 14 + D_80110080_marios_puzzle_party[player].x;
    cell->unk8 = D_80110080_marios_puzzle_party[player].y - row * 7;
    cell->unk10 = state;
    cell->unk0 = func_80106A44_marios_puzzle_party(player, cell->unkC, cell->unk10, cell->unk4, cell->unk8);
    if (state == 1) {
        cells[row + 1].unkC = color;
        cells[row + 1].unk4 = cell->unk4;
        cells[row + 1].unk8 = cell->unk8 - 7;
        cells[row + 1].unk10 = 2;
        cells[row + 1].unk0 = cell->unk0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105D50_marios_puzzle_party);
#endif

u16 func_80105E88_marios_puzzle_party(s32 player) {
    u16 btn;

    if (!(GwPlayer[player].stat & 1)) {
        btn = D_800CDA7C_main[GwPlayer[player].pad];
        btn &= 0xF0FF;
        if (D_800CBB6E_main[GwPlayer[player].pad] > 30.0f) {
            btn |= 0x100;
        }
        if (D_800CBB6E_main[GwPlayer[player].pad] < -30.0f) {
            btn |= 0x200;
        }
        if (D_800D20A1_main[GwPlayer[player].pad] < -30.0f) {
            btn |= 0x400;
        }
    } else {
        btn = D_80114DE0_marios_puzzle_party[player].unk40;
    }
    return btn;
}

#ifdef NON_MATCHING
u16 func_80105FCC_marios_puzzle_party(s32 player, s32 mask) {
    u16 ret;
    PzAi* ai;

    if (!(GwPlayer[player].stat & 1)) {
        ret = D_800D5558_main[GwPlayer[player].pad] & mask;
    } else {
        ai = &D_80114DE0_marios_puzzle_party[player];
        ret = mask & ai->unk42;
        ai->unk42 = ai->unk42 & ~mask;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105FCC_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Mode, sprite data, block batches, empty boards with walls, the piece colour sequence and the
   shuffled board positions; the Mode 2 boards start with four rows of blocks. */
void func_8010604C_marios_puzzle_party(void) {
    void* data;
    PzCell* cell;
    s32 i;
    s32 j;
    s32 k;
    s32 a;
    s32 b;
    s32* pair;
    u16 slot;

    if (D_800CE20A_main != 1) {
        if (D_800CE20A_main != 2) {
            k = 100;
            D_80116158_marios_puzzle_party = 0;
        } else {
            D_80116158_marios_puzzle_party = 2;
            k = 9999;
        }
    } else {
        D_80116158_marios_puzzle_party = 1;
        k = D_800CB890_main.unk4;
    }
    D_8011615C_marios_puzzle_party = k;
    slot = InitEspriteSlot(func_8000B838_main(0x400000), 0, 1);
    func_8000BC48_main(slot, 0x4000);
    func_8000BBD4_main(slot, 0xA0, 0x78);
    func_8000BCC8_main(slot, 0xFFFF);
    data = DataRead(0x210028);
    D_8011608C_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400001);
    D_80116090_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400002);
    D_80116094_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400003);
    D_80116098_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400004);
    D_8011609C_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 5) | 0x400000);
        D_801160C0_marios_puzzle_party[i] = func_80055810_main(data);
        DataClose(data);
    }
    data = DataRead(0x400014);
    D_801160AC_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400015);
    D_801160B0_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400016);
    D_801160B4_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x400017);
    D_801160B8_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x40001A);
    D_801160D0_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    k = 0x400018;
    if (D_80116158_marios_puzzle_party == 0) {
        k = 0x400019;
    }
    data = DataRead(k);
    D_801160D4_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x40001B);
    D_801160D8_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x40001C);
    D_801160DC_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x40001D);
    D_801160E0_marios_puzzle_party = func_80055810_main(data);
    DataClose(data);
    func_8010F570_marios_puzzle_party(0x1D);
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 7; i++) {
            func_8010F678_marios_puzzle_party((i + 0xD) | 0x400000, 0x32);
        }
    }
    func_8010F678_marios_puzzle_party(0x40001E, 0xA0);
    for (i = 0; i < 7; i++) {
        data = DataRead((i + 0xD) | 0x400000);
        D_80116070_marios_puzzle_party[i] = func_80055810_main(data);
        DataClose(data);
    }
    if (D_80116158_marios_puzzle_party == 2) {
        data = DataRead(0x31);
        D_801160A0_marios_puzzle_party = func_80055810_main(data);
        DataClose(data);
        func_8000B880_main(D_801160A0_marios_puzzle_party, 0.0f, 1.0f, 0.0f);
        data = DataRead(0x40001F);
        D_801160A4_marios_puzzle_party = func_80055810_main(data);
        DataClose(data);
        func_8000B880_main(D_801160A4_marios_puzzle_party, 0.0f, 1.0f, 0.0f);
        omAddPrcObj(func_8010E12C_marios_puzzle_party, 0x4001, 0, 0);
        data = DataRead(0x31);
        D_801160A8_marios_puzzle_party = func_80055810_main(data);
        DataClose(data);
        omAddPrcObj(func_8010EAA0_marios_puzzle_party, 0x4001, 0, 0);
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)30;
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)70;
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)100;
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)220;
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)270;
        omAddPrcObj(func_8010ECD8_marios_puzzle_party, 0x4001, 0, 0)->user_data = (void*)300;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 40; k++) {
                cell = &D_801102E0_marios_puzzle_party[i][j][k];
                cell->unkC = -1;
                if (j == 0 || j == 5 || k == 0) {
                    cell->unk10 = -1;
                } else {
                    cell->unk10 = 0;
                }
            }
        }
    }
    D_801160E8_marios_puzzle_party = 0;
    for (i = 0; i < 4; i++) {
        D_80116118_marios_puzzle_party[i] = 0;
        D_80116168_marios_puzzle_party[i] = 0;
        D_80116178_marios_puzzle_party[i] = 0;
        D_80116188_marios_puzzle_party[i] = 0;
        D_801161A8_marios_puzzle_party[i] = 0;
        D_80116198_marios_puzzle_party[i] = 0;
        D_801168A0_marios_puzzle_party[i] = 0;
        D_801161C8_marios_puzzle_party[i] = 0;
    }
    for (i = 0; i < 30; i++) {
        pair = D_801167B0_marios_puzzle_party[i];
        pair[0] = (u8)(rand8() % 6);
        do {
            pair[1] = (u8)(rand8() % 6);
        } while (pair[0] == pair[1]);
    }
    for (i = 0; i < 8; i++) {
        a = rand8() & 3;
        do {
            b = rand8() & 3;
        } while (a == b);
        j = D_80110080_marios_puzzle_party[a].x;
        D_80110080_marios_puzzle_party[a].x = D_80110080_marios_puzzle_party[b].x;
        D_80110080_marios_puzzle_party[b].x = j;
    }
    if (D_80116158_marios_puzzle_party == 2) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                (&D_80110080_marios_puzzle_party[i].x)[j] = (&D_801100A0_marios_puzzle_party[i].x)[j];
            }
        }
        for (i = 1; i < D_80116100_marios_puzzle_party; i++) {
            for (j = 1; j < 0x14; j += 2) {
                func_80105D50_marios_puzzle_party(i, 1, 3, 1, j);
                func_80105D50_marios_puzzle_party(i, 0, 3, 2, j);
                func_80105D50_marios_puzzle_party(i, 1, 3, 3, j);
                func_80105D50_marios_puzzle_party(i, 0, 3, 4, j);
                func_80105D50_marios_puzzle_party(i, 0, 3, 1, j + 1);
                func_80105D50_marios_puzzle_party(i, 1, 3, 2, j + 1);
                func_80105D50_marios_puzzle_party(i, 0, 3, 3, j + 1);
                func_80105D50_marios_puzzle_party(i, 1, 3, 4, j + 1);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010604C_marios_puzzle_party);
#endif

s32 func_80106A44_marios_puzzle_party(s32 player, s32 color, s32 state, s32 x, s32 y) {
    s32 handle = func_8010FEDC_marios_puzzle_party(player * 7 + color, x, y);

    if (state != 1) {
        func_8010FFBC_marios_puzzle_party(handle, 1.0f, 0.5f);
    }
    return handle;
}

s32 func_80106ACC_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir) {
    s32 ret = TRUE;
    s32 dx = -14;
    s32 col;
    s32 row;
    PzCell* cells;
    PzCell* cell;

    if (dir > 0) {
        dx = 14;
    }
    col = (dx + piece->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f;
    row = (D_80110080_marios_puzzle_party[player].y - piece->unk30) / 7.0f;
    cells = D_801102E0_marios_puzzle_party[player][col];
    cell = &cells[row];
    if (cell->unk10 == 0) {
        ret = FALSE;
    }
    return ret;
}

s32 func_80106BB0_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir) {
    s32 ret = TRUE;
    s32 dx = -28;
    s32 col;
    s32 row;
    PzCell* cells;
    PzCell* cell;

    if (dir > 0) {
        dx = 14;
    }
    col = (dx + piece->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f;
    row = (D_80110080_marios_puzzle_party[player].y - (piece->unk30 + 14.0f)) / 7.0f;
    cells = D_801102E0_marios_puzzle_party[player][col];
    cell = &cells[row];
    if (cell->unk10 == 0) {
        ret = FALSE;
    }
    return ret;
}

#ifdef NON_MATCHING
/* Move a piece down by dy; undo and return TRUE if it hits something. */
s32 func_80106C98_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy) {
    PzCell* cell;
    s32 col;
    s32 row;
    s32 c2;
    s32 hit;
    s32 state;
    f32 x;

    piece->unk30 += dy;
    x = piece->unk2C;
    col = (x - D_80110080_marios_puzzle_party[player].x) / 14.0f;
    row = (D_80110080_marios_puzzle_party[player].y - piece->unk30) / 7.0f;
    cell = &D_801102E0_marios_puzzle_party[player][col][row];
    hit = TRUE;
    if (piece->unk24 != 0) {
        c2 = col - 1;
        if (!(col * 14 - x > 0.0f)) {
            c2 = col + 1;
        }
        if (cell->unk10 != 0) {
            goto end;
        }
        state = D_801102E0_marios_puzzle_party[player][c2][row].unk10;
    } else {
        state = cell->unk10;
    }
    if (state == 0) {
        piece->unk14 = col;
        piece->unk18 = row;
        hit = FALSE;
    }
end:
    if (hit) {
        piece->unk30 -= dy;
    }
    return hit;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106C98_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* The same for the special piece, which spans two columns. */
s32 func_80106E40_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy) {
    PzCell* a;
    PzCell* b;
    s32 col;
    s32 row;
    s32 c2;
    s32 hit = TRUE;

    piece->unk30 += dy;
    row = (D_80110080_marios_puzzle_party[player].y - piece->unk30 - 14.0f) / 7.0f;
    col = (piece->unk2C - (D_80110080_marios_puzzle_party[player].x + 0x16)) / 14.0f + 1.0f;
    a = &D_801102E0_marios_puzzle_party[player][col][row];
    b = &D_801102E0_marios_puzzle_party[player][col + 1][row];
    if (piece->unk24 != 0) {
        c2 = col + 2;
        if (piece->unk24 < 0) {
            c2 = col - 1;
        }
        if (a->unk10 == 0 && b->unk10 == 0) {
            hit = D_801102E0_marios_puzzle_party[player][c2][row].unk10 != 0;
        }
    } else if (a->unk10 == 0) {
        hit = b->unk10 != 0;
    }
    if (hit) {
        piece->unk30 -= dy;
    }
    return hit;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106E40_marios_puzzle_party);
#endif

s32 func_80107000_marios_puzzle_party(s32 player, s32 col) {
    s32 row = 1;
    PzCell* cells = D_801102E0_marios_puzzle_party[player][col];
    PzCell* cell;

    for (; row < 40; row++) {
        cell = &cells[row];
        if (cell->unk10 == 0) {
            break;
        }
    }
    return row;
}

s32 func_80107070_marios_puzzle_party(s32 player, s32 col) {
    s32 row = 1;
    s32 n = 0;
    PzCell* cells = D_801102E0_marios_puzzle_party[player][col];
    PzCell* cell;

    for (; row < 40; row++) {
        cell = &cells[row];
        if (cell->unk10 == 0) {
            break;
        }
        if (cell->unk10 == 1) {
            row++;
            n++;
        }
        if (cell->unk10 == 3) {
            n++;
        }
    }
    return n;
}

s32 func_80107108_marios_puzzle_party(s32 player, s32 col) {
    s32 row = 1;
    s32 n = 0;
    PzCell* cells = D_801102E0_marios_puzzle_party[player][col];
    s32 state;

    PzCell* cell;

    for (; row < 40;) {
        cell = &cells[row];
        state = cell->unk10;
        if (state == 0) {
            break;
        }
        row++;
        if (state == 1) {
            n++;
            row++;
        }
    }
    return n;
}

s32 func_8010718C_marios_puzzle_party(s32 col, s32 row) {
    PzMatch* m;
    s32 i;

    for (i = 0; i < D_801163E8_marios_puzzle_party; i++) {
        m = &D_801163F0_marios_puzzle_party[i];
        if (col == m->col && row == m->row) {
            return TRUE;
        }
        if (m->state == 1 && col == m->col && row == m->row + 1) {
            return TRUE;
        }
    }
    return FALSE;
}

#ifdef NON_MATCHING
void func_80107224_marios_puzzle_party(s32 player, s32 col, s32 row) {
    PzCell* cell = &D_801102E0_marios_puzzle_party[player][col][row];

    if (cell->unkC != 6) {
        D_80116188_marios_puzzle_party[player]++;
    }
    func_8010D290_marios_puzzle_party(player, col, row);
    if (cell->unk10 == 2) {
        row--;
        cell = &D_801102E0_marios_puzzle_party[player][col][row];
    }
    func_80110000_marios_puzzle_party(cell->unk0);
    cell->unk0 = -1;
    if (cell->unk10 == 1) {
        D_801102E0_marios_puzzle_party[player][col][row + 1].unkC = -1;
        D_801102E0_marios_puzzle_party[player][col][row + 1].unk10 = 0;
    }
    D_801102E0_marios_puzzle_party[player][col][row].unkC = -1;
    D_801102E0_marios_puzzle_party[player][col][row].unk10 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107224_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Flood fill: record (col, row) in the match list, then recurse into same-coloured neighbours. */
void func_80107400_marios_puzzle_party(s32 player, s32 col, s32 row, s32 color, s32 state) {
    PzCell* cell;
    s32 c;
    s32 r;

    if (state == 2) {
        row--;
        state = 1;
    }
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].col = col;
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].row = row;
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].state = state;
    if (++D_801163E8_marios_puzzle_party >= 80) {
        osSyncPrintf("BlockDelete Over\n");
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    if (color != 6) {
        c = col - 1;
        if (func_8010718C_marios_puzzle_party(c, row) == 0) {
            cell = &D_801102E0_marios_puzzle_party[player][col - 1][row];
            if (cell->unkC == color) {
                func_80107400_marios_puzzle_party(player, c, row, color, cell->unk10);
            }
        }
        c = col + 1;
        if (func_8010718C_marios_puzzle_party(c, row) == 0) {
            cell = &D_801102E0_marios_puzzle_party[player][col + 1][row];
            if (cell->unkC == color) {
                func_80107400_marios_puzzle_party(player, c, row, color, cell->unk10);
            }
        }
        r = row - 1;
        if (func_8010718C_marios_puzzle_party(col, r) == 0) {
            cell = &D_801102E0_marios_puzzle_party[player][col][row - 1];
            if (cell->unkC == color) {
                func_80107400_marios_puzzle_party(player, col, r, color, cell->unk10);
            }
        }
        r = row + 1;
        if (state == 1) {
            c = col - 1;
            r = row + 1;
            if (func_8010718C_marios_puzzle_party(c, r) == 0) {
                cell = &D_801102E0_marios_puzzle_party[player][col - 1][row + 1];
                if (cell->unkC == color) {
                    func_80107400_marios_puzzle_party(player, c, r, color, cell->unk10);
                }
            }
            c = col + 1;
            r = row + 1;
            if (func_8010718C_marios_puzzle_party(c, r) == 0) {
                cell = &D_801102E0_marios_puzzle_party[player][col + 1][row + 1];
                if (cell->unkC == color) {
                    func_80107400_marios_puzzle_party(player, c, r, color, cell->unk10);
                }
            }
            r = row + 2;
            if (func_8010718C_marios_puzzle_party(col, r) == 0) {
                cell = &D_801102E0_marios_puzzle_party[player][col][row + 2];
                if (cell->unkC == color) {
                    func_80107400_marios_puzzle_party(player, col, r, color, cell->unk10);
                }
            }
        } else if (func_8010718C_marios_puzzle_party(col, r) == 0) {
            cell = &D_801102E0_marios_puzzle_party[player][col][row + 1];
            if (cell->unkC == color) {
                func_80107400_marios_puzzle_party(player, col, r, color, cell->unk10);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107400_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Clear the garbage blocks (colour 6) next to a cleared block. */
void func_80107880_marios_puzzle_party(s32 player, s32 col, s32 row, s32 color, s32 state) {
    if (state == 2) {
        row--;
        state = 1;
    }
    if (D_801102E0_marios_puzzle_party[player][col - 1][row].unkC == color) {
        func_80107224_marios_puzzle_party(player, col - 1, row);
    }
    if (D_801102E0_marios_puzzle_party[player][col + 1][row].unkC == color) {
        func_80107224_marios_puzzle_party(player, col + 1, row);
    }
    if (D_801102E0_marios_puzzle_party[player][col][row - 1].unkC == color) {
        func_80107224_marios_puzzle_party(player, col, row - 1);
    }
    if (state == 1) {
        if (D_801102E0_marios_puzzle_party[player][col - 1][row + 1].unkC == color) {
            func_80107224_marios_puzzle_party(player, col - 1, row + 1);
        }
        if (D_801102E0_marios_puzzle_party[player][col + 1][row + 1].unkC == color) {
            func_80107224_marios_puzzle_party(player, col + 1, row + 1);
        }
        if (D_801102E0_marios_puzzle_party[player][col][row + 2].unkC == color) {
            func_80107224_marios_puzzle_party(player, col, row + 2);
        }
    } else if (D_801102E0_marios_puzzle_party[player][col][row + 1].unkC == color) {
        func_80107224_marios_puzzle_party(player, col, row + 1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107880_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
void func_80107BB0_marios_puzzle_party(s32 player) {
    s32 i;

    for (i = 0; i < D_801163E8_marios_puzzle_party; i++) {
        func_80107224_marios_puzzle_party(player, D_801163F0_marios_puzzle_party[i].col, D_801163F0_marios_puzzle_party[i].row);
        D_80116148_marios_puzzle_party[player] += 1 + D_80116108_marios_puzzle_party[player];
        D_80116138_marios_puzzle_party[player] += 1 + D_80116108_marios_puzzle_party[player];
        func_80107880_marios_puzzle_party(player, D_801163F0_marios_puzzle_party[i].col, D_801163F0_marios_puzzle_party[i].row, 6,
                                          D_801163F0_marios_puzzle_party[i].state);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107BB0_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Chain counter: "N chain" digits above the board while the chain lasts, then grow and fade out;
   each new chain step adds the cleared count to the player's score. */
void func_80107CBC_marios_puzzle_party(void) {
    s32 chain;
    s32 grp;
    s32 r;
    s32 g;
    s32 b;
    s32 i;
    s32 digits;
    s32 div;
    s32 shown;
    s32 x;
    s32 bright;
    s32 player;
    s32 d;
    s32 alpha;
    PzChain* tbl;
    f32 scale;

    chain = -1;
    r = 0;
    g = 0;
    b = 0;
    scale = 0.0f;
    tbl = NULL;
    player = (s32)HuPrcCurrentGet()->user_data;
    grp = HuSprGrpCreate(6, 5);
    func_80055024_main(grp, 1, D_801160DC_marios_puzzle_party, 0);
    func_800550F4_main(grp, 1, 0);
    func_80054904_main(grp, 1, 0, 0);
    HuSprAttrReset(grp, 1, 0xFFFF);
    HuSprAttrSet(grp, 1, 0x1008);
    HuSprPriSet(grp, 1, 0x100);
    func_80055420_main(grp, 1, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grp, 1, 0xFF);
    func_800554C4_main(grp, 1, 0);
    for (i = 2; i < 5; i++) {
        func_80055024_main(grp, i, D_801160D8_marios_puzzle_party, 0);
        func_800550F4_main(grp, i, 0);
        func_80054904_main(grp, i, 0, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x1008);
        HuSprPriSet(grp, i, 0x100);
        func_80055420_main(grp, i, 0xFF, 0xFF, 0xFF);
        func_80055458_main(grp, i, 0xFF);
        func_800554C4_main(grp, i, 0);
    }
    func_80055024_main(grp, 5, D_801160E0_marios_puzzle_party, 0);
    func_800550F4_main(grp, 5, 0);
    func_80054904_main(grp, 5, 0, 0);
    HuSprAttrReset(grp, 5, 0xFFFF);
    HuSprAttrSet(grp, 5, 0x1008);
    HuSprPriSet(grp, 5, 0x100);
    func_80055420_main(grp, 5, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grp, 5, 0xFF);
    func_800554C4_main(grp, 5, 0);
    func_80055024_main(grp, 0, D_801160DC_marios_puzzle_party, 0);
    HuSprAttrSet(grp, 0, 0x8000);
    func_800554C4_main(grp, 0, -1);
    func_80054904_main(grp, 0, D_80110080_marios_puzzle_party[player].x + 0x2A, D_80110080_marios_puzzle_party[player].y - 0x46);
    HuSprScaleSet(grp, 0, 0.0f, 0.0f);
    bright = 1;
    while (D_80116138_marios_puzzle_party[player] != 0 && D_80116178_marios_puzzle_party[player] != 1) {
        d = D_80116108_marios_puzzle_party[player];
        if (d >= 9) {
            d = 8;
        }
        tbl = &D_801100B0_marios_puzzle_party[d];
        r = tbl->r;
        g = tbl->g;
        b = tbl->b;
        scale = tbl->scale;
        div = 10;
        if (d == 1 && GwPlayer[0].coin == 11) {
            r = GwPlayer[1].coin;
            g = GwPlayer[2].coin;
            b = GwPlayer[3].coin;
            div = 10;
        }
        digits = 1;
        do {
            digits += div < D_80116148_marios_puzzle_party[player];
            div *= 10;
        } while (div < 1001);
        x = -((digits * 18) + 54) / 2 + 9;
        func_80054904_main(grp, 1, x, 0);
        HuSprScaleSet(grp, 1, scale, scale);
        if (bright != 0) {
            func_80055458_main(grp, 1, 0xFF);
            func_80055420_main(grp, 1, r, g, b);
        } else {
            func_80055458_main(grp, 1, 0x80);
        }
        for (i = 2; i < 5; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
        for (i = 4, div = 100, shown = 0; i >= 2; i--, div /= 10) {
            d = (D_80116148_marios_puzzle_party[player] / div) % 10;
            if (d > 0 || div == 1 || shown != 0) {
                shown = 1;
                HuSprAttrReset(grp, i, 0x8000);
                func_80055024_main(grp, i, D_801160D8_marios_puzzle_party, d);
                x += 18;
                func_80054904_main(grp, i, x, 0);
                HuSprScaleSet(grp, i, scale, scale);
                if (bright != 0) {
                    func_80055458_main(grp, i, 0xFF);
                    func_80055420_main(grp, i, r, g, b);
                } else {
                    func_80055458_main(grp, i, 0x80);
                }
            }
        }
        func_80054904_main(grp, 5, x + 0x1B, 0);
        HuSprScaleSet(grp, 5, scale, scale);
        if (bright != 0) {
            func_80055458_main(grp, 5, 0xFF);
            func_80055420_main(grp, 5, r, g, b);
        } else {
            func_80055458_main(grp, 5, 0x80);
        }
        bright = (bright + 1) & 1;
        if (chain != D_80116108_marios_puzzle_party[player]) {
            chain = D_80116108_marios_puzzle_party[player];
            D_80116128_marios_puzzle_party[player] += D_80116148_marios_puzzle_party[player];
        }
        HuPrcVSleep();
    }
    alpha = 0xFF;
    do {
        scale += 0.15f;
        func_80055458_main(grp, 1, alpha);
        HuSprScaleSet(grp, 1, tbl->scale, scale);
        func_80055420_main(grp, 1, r, g, b);
        for (i = 2; i < 5; i++) {
            func_80055458_main(grp, i, alpha);
            HuSprScaleSet(grp, i, tbl->scale, scale);
            func_80055420_main(grp, i, r, g, b);
        }
        func_80055458_main(grp, 5, alpha);
        HuSprScaleSet(grp, 5, tbl->scale, scale);
        func_80055420_main(grp, 5, r, g, b);
        alpha -= 10;
        HuPrcVSleep();
    } while (alpha > 0);
    HuSprGrpKill(grp);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107CBC_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Clear every group of matching blocks, let the blocks above fall, and repeat while chains form. */
void func_80108568_marios_puzzle_party(s32 player, s32 counter) {
    PzCell* cell;
    Process* proc;
    PzFall* fall;
    s32 first;
    s32 saved;
    s32 col;
    s32 row;
    s32 cleared;
    s32 n;

    first = TRUE;
    while (TRUE) {
        saved = D_80116148_marios_puzzle_party[player];
        D_80116148_marios_puzzle_party[player] = 0;
        cleared = FALSE;
        for (col = 1; col < 5; col++) {
            for (row = 1; row < 40; row++) {
                cell = &D_801102E0_marios_puzzle_party[player][col][row];
                if (cell->unk10 == 1 || cell->unk10 == 3) {
                    D_801163E8_marios_puzzle_party = 0;
                    func_80107400_marios_puzzle_party(player, col, row, cell->unkC, cell->unk10);
                    if (D_801163E8_marios_puzzle_party >= 2) {
                        func_80107BB0_marios_puzzle_party(player);
                        cleared = TRUE;
                        if (first && counter) {
                            first = FALSE;
                            omAddPrcObj(func_80107CBC_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void*)player;
                        }
                    }
                }
            }
        }
        if (!cleared) {
            break;
        }
        D_80116108_marios_puzzle_party[player]++;
        func_8004AC98_main(0x3F8, player);
        n = D_80116108_marios_puzzle_party[player] - 1;
        if ((u32)n >= 5) {
            n = 4;
        }
        func_8004AC98_main(n + 0x400, player);
        omVibrate(player, 2, 3, 10);
        for (col = 1; col < 5; col++) {
            for (row = 1; row < 40; row++) {
                if (D_801102E0_marios_puzzle_party[player][col][row].unk10 == 0) {
                    break;
                }
            }
            for (; row < 40; row++) {
                cell = &D_801102E0_marios_puzzle_party[player][col][row];
                if (cell->unk10 == 1 || cell->unk10 == 3) {
                    proc = omAddPrcObj(func_80108C80_marios_puzzle_party, 0x4001, 0x800, 0);
                    HuPrcChildLink(HuPrcCurrentGet(), proc);
                    fall = HuMemAlloc(sizeof(PzFall));
                    proc->user_data = fall;
                    fall->unk0 = player;
                    fall->unk4 = cell->unk0;
                    fall->unk8 = col * 14 + D_80110080_marios_puzzle_party[player].x;
                    fall->unkC = D_80110080_marios_puzzle_party[player].y - row * 7;
                    fall->unk10 = cell->unkC;
                    fall->unk14 = cell->unk10;
                    fall->unk18 = 0;
                }
            }
        }
        HuPrcChildWait();
    }
    D_80116148_marios_puzzle_party[player] = saved;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108568_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
void func_801088F4_marios_puzzle_party(s32 player, PzPiece* piece) {
    PzCell* cell;
    s32 i;

    for (i = 0; i < 2; i++) {
        cell = &D_801102E0_marios_puzzle_party[player][piece->unk14][i + piece->unk18];
        cell->unk0 = piece->unk8;
        cell->unk4 = piece->unk2C;
        cell->unk8 = piece->unk30;
        cell->unkC = piece->unk1C;
        cell->unk10 = i + 1;
    }
    for (i = 0; i < 2; i++) {
        cell = &D_801102E0_marios_puzzle_party[player][piece->unk14][i + 2 + piece->unk18];
        cell->unk0 = piece->unkC;
        cell->unk4 = piece->unk2C;
        cell->unk8 = piece->unk30 - 14.0f;
        cell->unkC = piece->unk20;
        cell->unk10 = i + 1;
    }
    func_80108568_marios_puzzle_party(player, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801088F4_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
s32 func_80108A50_marios_puzzle_party(s32 player, s32 kind, s32 color, s32 col, s32 row) {
    s32 n = 0;

    if (color != 6) {
        n = (D_801102E0_marios_puzzle_party[player][col - 1][row].unkC == color) +
            (D_801102E0_marios_puzzle_party[player][col + 1][row].unkC == color) +
            (D_801102E0_marios_puzzle_party[player][col][row - 1].unkC == color);
        if (kind == 1) {
            n += (D_801102E0_marios_puzzle_party[player][col - 1][row + 1].unkC == color) +
                 (D_801102E0_marios_puzzle_party[player][col + 1][row + 1].unkC == color);
            n += D_801102E0_marios_puzzle_party[player][col][row + 2].unkC == color;
        } else {
            n += D_801102E0_marios_puzzle_party[player][col][row + 1].unkC == color;
        }
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108A50_marios_puzzle_party);
#endif

/* Destructor of func_80108C80: when that player's game is being torn down, remove the block. */
void func_80108BB0_marios_puzzle_party(void) {
    PzFall* fall = HuPrcCurrentGet()->user_data;

    if (D_801160E4_marios_puzzle_party == fall->unk0 && D_80116178_marios_puzzle_party[D_801160E4_marios_puzzle_party] != 0) {
        func_8010D290_marios_puzzle_party(D_801160E4_marios_puzzle_party,
                                          (fall->unk8 - D_80110080_marios_puzzle_party[D_801160E4_marios_puzzle_party].x) / 14,
                                          (D_80110080_marios_puzzle_party[D_801160E4_marios_puzzle_party].y - fall->unkC) / 7);
        func_80110000_marios_puzzle_party(fall->unk4);
    }
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

#ifdef NON_MATCHING
/* A block (or a two-block piece) falls down its column until it rests on something. */
void func_80108C80_marios_puzzle_party(void) {
    PzFall* fall;
    PzCell* cells;
    PzCell* cell;
    s32 state;
    s32 color;
    s32 col;
    s32 row;
    s32 y0;
    s32 done;
    f32 speed;

    fall = HuPrcCurrentGet()->user_data;
    omPrcSetDestructor((s32)HuPrcCurrentGet(), func_80108BB0_marios_puzzle_party);
    col = (fall->unk8 - D_80110080_marios_puzzle_party[fall->unk0].x) / 14;
    row = (D_80110080_marios_puzzle_party[fall->unk0].y - fall->unkC) / 7;
    cell = &D_801102E0_marios_puzzle_party[fall->unk0][col][row];
    state = cell->unk10;
    color = cell->unkC;
    cell->unkC = -1;
    cell->unk10 = 0;
    if (state == 1) {
        D_801102E0_marios_puzzle_party[fall->unk0][col][row + 1].unkC = -1;
        D_801102E0_marios_puzzle_party[fall->unk0][col][row + 1].unk10 = 0;
    }
    done = FALSE;
    do {
        col = (fall->unk8 - D_80110080_marios_puzzle_party[fall->unk0].x) / 14;
        if (D_801102E0_marios_puzzle_party[fall->unk0][col][(D_80110080_marios_puzzle_party[fall->unk0].y - fall->unkC) / 7 - 1].unk10 != 0) {
            done = TRUE;
        } else {
            speed = 1.0f;
            while (TRUE) {
                fall->unkC += speed;
                speed += 0.5f;
                if (speed > 6.0f) {
                    speed = 6.0f;
                }
                y0 = D_80110080_marios_puzzle_party[fall->unk0].y;
                row = (y0 - fall->unkC) / 7;
                cells = D_801102E0_marios_puzzle_party[fall->unk0][col];
                if (cells[row].unk10 != 0) {
                    break;
                }
                func_8010FF78_marios_puzzle_party(fall->unk4, fall->unk8, fall->unkC);
                HuPrcVSleep();
            }
            cell = &cells[row + 1];
            cell->unk8 = fall->unkC = y0 - (row + 1) * 7;
            func_8010FF78_marios_puzzle_party(fall->unk4, fall->unk8, fall->unkC);
            cell->unk0 = fall->unk4;
            cell->unkC = color;
            cell->unk10 = state;
            if (state == 1) {
                cell = &cells[row + 2];
                cell->unk0 = fall->unk4;
                cell->unkC = color;
                cell->unk10 = 2;
            }
        }
        HuPrcVSleep();
    } while (!done);
    col = (fall->unk8 - D_80110080_marios_puzzle_party[fall->unk0].x) / 14;
    row = (D_80110080_marios_puzzle_party[fall->unk0].y - fall->unkC) / 7;
    if ((row >= 20 && state == 1) || (row >= 21 && state == 3)) {
        func_80107224_marios_puzzle_party(fall->unk0, col, row);
    } else if (fall->unk18 != 0) {
        func_8004AC98_main(0x3F9, fall->unk0);
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108C80_marios_puzzle_party);
#endif

void func_8010913C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

#ifdef NON_MATCHING
/* The special piece lands on a column: squash the first two-block piece under it, push the blocks
   above down, then turn it into a single block and close the gap. */
void func_80109160_marios_puzzle_party(void) {
    PzSquash* sq;
    PzCell* base;
    PzCell* cell;
    PzCell* cells;
    s32 row;
    s32 r;
    s32 a;
    s32 b;
    s32 keep;
    s32 more;
    f32 scale;

    row = 1;
    sq = HuPrcCurrentGet()->user_data;
    omPrcSetDestructor((s32)HuPrcCurrentGet(), func_8010913C_marios_puzzle_party);
    while ((u32)(base = &D_801102E0_marios_puzzle_party[sq->unk0][sq->unk4][row])->unk10 >= 2) {
        row++;
    }
    keep = TRUE;
    if (base->unk10 != 0) {
        scale = 1.0f;
        do {
            scale -= 0.2f;
            if (scale <= 0.5f) {
                scale = 0.5f;
                keep = FALSE;
            }
            r = row + 2;
            func_8010FFBC_marios_puzzle_party(base->unk0, 1.0f, scale);
            more = TRUE;
            do {
                cell = &D_801102E0_marios_puzzle_party[sq->unk0][sq->unk4][r];
                switch (cell->unk10) {
                    case 1:
                        cell->unk8 = base->unk8 - 2.0f * (scale * 7.0f) - ((r - 2 - row) * 7);
                        func_8010FF78_marios_puzzle_party(cell->unk0, sq->unk4 * 14 + D_80110080_marios_puzzle_party[sq->unk0].x, cell->unk8);
                        r += 2;
                        break;
                    case 3:
                        cell->unk8 = base->unk8 - 2.0f * (scale * 7.0f) - ((r - 2 - row) * 7);
                        r++;
                        func_8010FF78_marios_puzzle_party(cell->unk0, sq->unk4 * 14 + D_80110080_marios_puzzle_party[sq->unk0].x, cell->unk8);
                        break;
                    case 0:
                        more = FALSE;
                        r++;
                        break;
                    default:
                        r++;
                        break;
                }
            } while (more);
            sq->unk10->unk30 = base->unk8 - 2.0f * (scale * 7.0f) - ((r - 2 - row) * 7) - 7.0f;
            func_80054904_main(sq->unk8, 0, sq->unkC, D_801161A8_marios_puzzle_party[sq->unk0] + sq->unk10->unk30);
            HuPrcVSleep();
        } while (keep);
        a = row + 1;
        D_801102E0_marios_puzzle_party[sq->unk0][sq->unk4][row].unk10 = 3;
        b = a + 1;
        do {
            cells = D_801102E0_marios_puzzle_party[sq->unk0][sq->unk4];
            cells[a].unk0 = cells[b].unk0;
            cells[a].unk4 = cells[b].unk4;
            cells[a].unk8 = cells[b].unk8;
            cells[a].unkC = cells[b].unkC;
            cells[a].unk10 = cells[b].unk10;
            a++;
            if (cells[b].unk10 == 0) {
                break;
            }
            b++;
        } while (TRUE);
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109160_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* The special piece has landed between two columns: squash them until neither has a two-block
   piece left to squash, then clear matches; returns whether anything was cleared. */
s32 func_8010961C_marios_puzzle_party(s32 player, s32 x, s32 handle, PzPiece* piece, s32 first) {
    s32 n[2];
    s32 top[2];
    s32 col;
    s32 side;
    s32 saved;
    Process* proc;
    PzSquash* sq;

    col = (x - 0x16 - D_80110080_marios_puzzle_party[player].x) / 14 + 1;
    omAddPrcObj(func_8010D8E8_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void*)player;
    func_8004AC98_main(0x3FA, player);
    omVibrate(player, 20, 0, 20);
    while (TRUE) {
        n[0] = func_80107070_marios_puzzle_party(player, col);
        n[1] = func_80107070_marios_puzzle_party(player, col + 1);
        side = n[1] >= n[0];
        if (func_80107108_marios_puzzle_party(player, col + side) == 0) {
            n[0] = func_80107000_marios_puzzle_party(player, col);
            n[1] = func_80107000_marios_puzzle_party(player, col + 1);
            if (side == 0 ? !(n[0] < n[1]) : !(n[1] < n[0])) {
                break;
            }
        }
        top[0] = func_80107000_marios_puzzle_party(player, col) - 1;
        top[1] = func_80107000_marios_puzzle_party(player, col + 1) - 1;
        if (top[0] >= top[1]) {
            proc = omAddPrcObj(func_80109160_marios_puzzle_party, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), proc);
            sq = HuMemAlloc(sizeof(PzSquash));
            proc->user_data = sq;
            sq->unk0 = player;
            sq->unk8 = handle;
            sq->unk4 = col;
            sq->unkC = x;
            sq->unk10 = piece;
        }
        if (top[1] >= top[0]) {
            func_8004AC98_main(0x3FB, player);
            proc = omAddPrcObj(func_80109160_marios_puzzle_party, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), proc);
            sq = HuMemAlloc(sizeof(PzSquash));
            proc->user_data = sq;
            sq->unk0 = player;
            sq->unk8 = handle;
            sq->unk4 = col + 1;
            sq->unkC = x;
            sq->unk10 = piece;
        }
        HuPrcChildWait();
    }
    saved = D_80116138_marios_puzzle_party[player];
    func_80108568_marios_puzzle_party(player, first);
    return saved < D_80116138_marios_puzzle_party[player];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010961C_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Score display (five digits, clamped to 0..99999). */
void func_801098A0_marios_puzzle_party(void) {
    PzLocal* loc;
    s32 player;
    s32 grp;
    s32 i;
    s32 div;
    s32 d;
    s32 shown;

    loc = HuPrcCurrentGet()->user_data;
    player = loc->player;
    grp = loc->grp;
    D_80116128_marios_puzzle_party[player] = 0;
    for (i = 1; i < 6; i++) {
        func_80055024_main(grp, i, D_801160D0_marios_puzzle_party, 0);
        if (D_80116158_marios_puzzle_party == 0) {
            func_80054904_main(grp, i, 16 - i * 8, 12);
        } else {
            func_80054904_main(grp, i, 24 - i * 8, 12);
        }
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x4000);
        HuSprPriSet(grp, i, 0x1FE);
        func_800554C4_main(grp, i, 0);
    }
    func_80055024_main(grp, 8, D_801160D4_marios_puzzle_party, 0);
    func_80054904_main(grp, 8, 0, 12);
    HuSprAttrReset(grp, 8, 0xFFFF);
    HuSprAttrSet(grp, 8, 0x4000);
    HuSprPriSet(grp, 8, 0x1FF);
    func_800554C4_main(grp, 8, 0);
    while (TRUE) {
        if (D_80116128_marios_puzzle_party[player] < 0) {
            D_80116128_marios_puzzle_party[player] = 0;
        }
        if (D_80116128_marios_puzzle_party[player] > 99999) {
            D_80116128_marios_puzzle_party[player] = 99999;
        }
        func_80055024_main(grp, 1, D_801160D0_marios_puzzle_party, D_80116128_marios_puzzle_party[player] % 10);
        for (i = 5; i >= 2; i--) {
            HuSprAttrSet(grp, i, 0x8000);
        }
        for (i = 5, div = 10000, shown = 0; i >= 2; i--, div /= 10) {
            d = (D_80116128_marios_puzzle_party[player] / div) % 10;
            if (d > 0 || div == 1 || shown != 0) {
                shown = 1;
                HuSprAttrReset(grp, i, 0x8000);
                func_80055024_main(grp, i, D_801160D0_marios_puzzle_party, d);
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801098A0_marios_puzzle_party);
#endif

void func_80109C04_marios_puzzle_party(s32 player, s32 color, s32 state, s32 col, s32 row, s32 arg5) {
    Process* proc;
    PzCell* cell;
    PzFall* fall;

    func_80105D50_marios_puzzle_party(player, color, state, col, row);
    cell = &D_801102E0_marios_puzzle_party[player][col][row];
    if (cell->unk10 == 1 || cell->unk10 == 3) {
        proc = omAddPrcObj(func_80108C80_marios_puzzle_party, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        fall = HuMemAlloc(sizeof(PzFall));
        proc->user_data = fall;
        fall->unk0 = player;
        fall->unk4 = cell->unk0;
        fall->unk8 = cell->unk4;
        fall->unkC = cell->unk8;
        fall->unk10 = cell->unkC;
        fall->unk14 = cell->unk10;
        fall->unk18 = arg5;
    }
}

/* Make the next piece (the special piece after ten cleared blocks) and drop it into the preview. */
void func_80109D24_marios_puzzle_party(void) {
    PzPiece* piece;
    s32 player;
    s32* idx;
    s32 moving;
    f32 lim;

    piece = HuPrcCurrentGet()->user_data;
    player = piece->unk4;
    if (D_80116188_marios_puzzle_party[player] < 10) {
        idx = &D_801168A0_marios_puzzle_party[player];
        piece->unk1C = D_801167B0_marios_puzzle_party[*idx][0];
        piece->unk20 = D_801167B0_marios_puzzle_party[*idx][1];
        if (++*idx >= 30) {
            *idx = 0;
        }
        piece->unk2C = D_80110080_marios_puzzle_party[player].x + 0x23;
        piece->unk30 = D_80110080_marios_puzzle_party[player].y - 0xE7;
        piece->unk8 = func_80106A44_marios_puzzle_party(player, piece->unk1C, 1, piece->unk2C, piece->unk30);
        piece->unkC = func_80106A44_marios_puzzle_party(player, piece->unk20, 1, piece->unk2C, piece->unk30 - 14.0f);
    } else {
        piece->unk2C = D_80110080_marios_puzzle_party[player].x + 0x2A;
        piece->unk30 = D_80110080_marios_puzzle_party[player].y - 0xE7;
        piece->unk1C = 7;
        piece->unk8 = HuSprGrpCreate(1, 5);
        func_80055024_main(piece->unk8, 0, D_801160AC_marios_puzzle_party, 0);
        func_80054904_main(piece->unk8, 0, piece->unk2C, D_801161A8_marios_puzzle_party[player] + piece->unk30);
        HuSprAttrReset(piece->unk8, 0, 0xFFFF);
        HuSprAttrSet(piece->unk8, 0, 8);
    }
    moving = TRUE;
    do {
        piece->unk30 += 5.0f;
        if (piece->unk1C != 7) {
            lim = D_80110080_marios_puzzle_party[player].y - 0xB6;
            if (lim < piece->unk30) {
                piece->unk30 = lim;
                moving = FALSE;
            }
            func_8010FF78_marios_puzzle_party(piece->unk8, piece->unk2C, piece->unk30);
            func_8010FF78_marios_puzzle_party(piece->unkC, piece->unk2C, piece->unk30 - 14.0f);
        } else {
            lim = D_80110080_marios_puzzle_party[player].y - 0xC4;
            if (lim < piece->unk30) {
                piece->unk30 = lim;
                moving = FALSE;
            }
            func_80054904_main(piece->unk8, 0, piece->unk2C, D_801161A8_marios_puzzle_party[player] + piece->unk30);
        }
        HuPrcVSleep();
    } while (moving);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
/* Result rank flying in from the distance over a player's board (player 4: the centre). */
void func_8010A0D8_marios_puzzle_party(void) {
    f32 xs[5] = { -95.0f, -30.0f, 30.0f, 95.0f, 0.0f };
    s32 player;
    s32 i;
    s16 g0;
    s16 g1;
    s16 g2;
    f32* x;
    f32 z;
    f32 a;
    f32 y;

    player = (s32)HuPrcCurrentGet()->user_data;
    i = 0;
    func_8004AC98_main(0x3FE, (player != 4) ? player : 0);
    g0 = HuSprGrpCreate(1, 5);
    func_80055024_main(g0, 0, D_801160B0_marios_puzzle_party, 0);
    HuSprAttrReset(g0, 0, 0xFFFF);
    HuSprPriSet(g0, 0, 0x200);
    HuSprAttrSet(g0, 0, 0x4000);
    g1 = HuSprGrpCreate(1, 5);
    func_80055024_main(g1, 0, D_801160D0_marios_puzzle_party, 0);
    HuSprAttrReset(g1, 0, 0xFFFF);
    HuSprPriSet(g1, 0, 0x1FE);
    HuSprAttrSet(g1, 0, 0x4000);
    g2 = HuSprGrpCreate(1, 5);
    func_80055024_main(g2, 0, D_801160D4_marios_puzzle_party, 0);
    HuSprAttrReset(g2, 0, 0xFFFF);
    HuSprPriSet(g2, 0, 0x1FF);
    HuSprAttrSet(g2, 0, 0x4000);
    z = -5000.0f;
    a = 0.0f;
    x = &xs[player];
    do {
        y = sindf(a) * 150.0f;
        a += 6.0f;
        z += 111.111115f;
        SprPos3DSet(g0, 0, 0, *x, y, z);
        SprPosPerspectiveSet(g0, 0, 0, *x, y, z);
        if (D_80116158_marios_puzzle_party == 0) {
            SprPos3DSet(g1, 0, 0, *x + 8.0f, y - 12.0f, z);
            SprPosPerspectiveSet(g1, 0, 0, *x + 8.0f, y - 12.0f, z);
        } else {
            SprPos3DSet(g1, 0, 0, *x + 16.0f, y - 12.0f, z);
            SprPosPerspectiveSet(g1, 0, 0, *x + 16.0f, y - 12.0f, z);
        }
        i++;
        SprPos3DSet(g2, 0, 0, *x, y - 12.0f, z);
        SprPosPerspectiveSet(g2, 0, 0, *x, y - 12.0f, z);
        HuPrcVSleep();
    } while (i < 45);
    HuSprGrpKill(g0);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A0D8_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
s32 func_8010A4B4_marios_puzzle_party(s32 player, s32 x, s32 y) {
    s32 row = (D_80110080_marios_puzzle_party[player].y - y) / 7;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_801102E0_marios_puzzle_party[player][(x - D_80110080_marios_puzzle_party[player].x) / 14][row + i].unk10 != 0) {
            break;
        }
    }
    return !(i < 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A4B4_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Game over for a player: shake the frame, swap in the game-over panel, then bob it. */
void func_8010A588_marios_puzzle_party(void) {
    PzPiece* next;
    s32 player;
    s32 x;
    s32 y;
    s16 grp;
    f32 a;

    player = (s32)HuPrcCurrentGet()->user_data;
    next = &D_80116308_marios_puzzle_party[player];
    if (next->unk1C != 7) {
        func_8010D290_marios_puzzle_party(player, (next->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f,
                                          (D_80110080_marios_puzzle_party[player].y - next->unk30) / 7.0f);
        func_80110000_marios_puzzle_party(next->unk8);
        func_80110000_marios_puzzle_party(next->unkC);
    } else {
        HuSprAttrSet(next->unk8, 0, 0x8000);
    }
    a = 0.0f;
    do {
        a += 10.0f;
        if (a > 360.0f) {
            a = 360.0f;
        }
        func_800552DC_main(D_801161D8_marios_puzzle_party[player], 0, sindf(a) * 45.0f);
        HuPrcVSleep();
    } while (a != 360.0f);
    HuSprGrpKill(D_801161E8_marios_puzzle_party[player]);
    D_801161E8_marios_puzzle_party[player] = grp = HuSprGrpCreate(1, 5);
    func_80055024_main(grp, 0, D_80116094_marios_puzzle_party, 0);
    func_80054904_main(grp, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0xA1));
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x4008);
    HuSprPriSet(grp, 0, 0x300);
    omAddPrcObj(func_8010CF4C_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void*)player;
    HuPrcSleep(10);
    x = D_80110080_marios_puzzle_party[player].x + 0x2A;
    y = D_80110080_marios_puzzle_party[player].y - 0xB5;
    if (y < 0x82) {
        y += 3;
        do {
            func_80054904_main(D_801161D8_marios_puzzle_party[player], 0, x, y);
            HuPrcVSleep();
            y += 3;
        } while (y < 0x82);
    }
    func_80054904_main(D_801161D8_marios_puzzle_party[player], 0, x, 0x82);
    a = 0.0f + 8.0f;
    while (TRUE) {
        if (a > 360.0f) {
            a -= 360.0f;
        }
        func_80054904_main(D_801161D8_marios_puzzle_party[player], 0, x, 130.0f + sindf(a) * 3.0f);
        HuPrcVSleep();
        a += 8.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A588_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Destructor of a player's game process (game over, or the minigame ending). */
void func_8010A958_marios_puzzle_party(void) {
    PzPiece* cur;
    PzPiece* next;
    s32 player;
    s32 col;
    s32 row;
    Process* proc;

    player = (s32)HuPrcCurrentGet()->user_data;
    cur = &D_80116238_marios_puzzle_party[player];
    next = &D_80116308_marios_puzzle_party[player];
    if (D_801160E4_marios_puzzle_party == player || D_801160E8_marios_puzzle_party == 0) {
        if (D_801160E4_marios_puzzle_party != player) {
            if (D_80116158_marios_puzzle_party != 2 || player == 0) {
                omVibrate(player, 10, 0, 10);
            }
            D_80116168_marios_puzzle_party[player] = 1;
            proc = omAddPrcObj(func_8010A588_marios_puzzle_party, 0x4001, 0x1000, 0);
            proc->user_data = HuPrcCurrentGet()->user_data;
        }
        if (D_801160E8_marios_puzzle_party == 0) {
            func_80055140_main(D_801161D8_marios_puzzle_party[player], 0, 0, 2);
            func_800550F4_main(D_801161D8_marios_puzzle_party[player], 0, 1);
            HuSprAttrReset(D_801161D8_marios_puzzle_party[player], 0, 0x8000);
            HuSprAttrSet(D_801161D8_marios_puzzle_party[player], 9, 0x8000);
            if (D_801160E8_marios_puzzle_party == 0) {
                if (next->unk1C != 7) {
                    func_8010D290_marios_puzzle_party(player, (next->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f,
                                                      (D_80110080_marios_puzzle_party[player].y - next->unk30) / 7.0f);
                    func_80110000_marios_puzzle_party(next->unk8);
                    func_80110000_marios_puzzle_party(next->unkC);
                } else {
                    HuSprAttrSet(next->unk8, 0, 0x8000);
                }
            }
        }
    }
    D_80116178_marios_puzzle_party[player] = 1;
    if (D_801160E4_marios_puzzle_party == player) {
        HuAudFXPlay(0x3FF);
        for (row = 1; row < 40; row++) {
            for (col = 1; col < 5; col++) {
                if (D_801102E0_marios_puzzle_party[player][col][row].unk10 == 3 || D_801102E0_marios_puzzle_party[player][col][row].unk10 == 1) {
                    func_80107224_marios_puzzle_party(player, col, row);
                }
            }
        }
        if (D_801160E8_marios_puzzle_party == 0) {
            if (cur->unk1C != 7) {
                func_8010D290_marios_puzzle_party(player, (cur->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f,
                                                  (D_80110080_marios_puzzle_party[player].y - cur->unk30) / 7.0f);
                func_80110000_marios_puzzle_party(cur->unk8);
                func_80110000_marios_puzzle_party(cur->unkC);
                return;
            }
            if (D_80116228_marios_puzzle_party[player] != -1) {
                HuSprAttrSet(D_80116228_marios_puzzle_party[player], 0, 0x8000);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A958_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* One player's game: show the next piece, drop garbage rows sent by the others, move the next piece
   into the well, then let the player (or the CPU) steer and drop it until it lands; game over when
   there is no room. */
void func_8010AD20_marios_puzzle_party(void) {
    PzLocal loc;
    s32 cnt;
    s32 player;
    s32 handleB;
    s32 speed;
    s32 level;
    PzPiece* next;
    s32 handleA;
    s32 x;
    s32 y;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 garbage;
    s32 best;
    s32 h;
    s32 hit;
    s32 landed;
    s32 spec;
    Process* proc;
    PzPiece* cur;
    PzAi* ai;
    f32 dx1;
    f32 dy1;
    f32 dx2;
    f32 dy2;
    f32 fy;
    s32 r;

    cnt = 0;
    level = 1;
    ai = NULL;
    player = (s32)HuPrcCurrentGet()->user_data;
    omPrcSetDestructor((s32)HuPrcCurrentGet(), func_8010A958_marios_puzzle_party);
    loc.grp = HuSprGrpCreate(10, 5);
    D_801161D8_marios_puzzle_party[player] = loc.grp;
    func_80055024_main(loc.grp, 0, D_801160B4_marios_puzzle_party, 0);
    func_800550F4_main(loc.grp, 0, 0);
    func_80054904_main(loc.grp, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0xB6));
    HuSprAttrReset(loc.grp, 0, 0xFFFF);
    HuSprAttrSet(loc.grp, 0, 0x4000);
    HuSprPriSet(loc.grp, 0, 0x200);
    func_80055024_main(loc.grp, 9, D_801160B8_marios_puzzle_party, 0);
    func_800550F4_main(loc.grp, 9, 0);
    func_80054904_main(loc.grp, 9, 0, 0);
    HuSprAttrReset(loc.grp, 9, 0xFFFF);
    HuSprAttrSet(loc.grp, 9, 0xC000);
    HuSprPriSet(loc.grp, 9, 0x200);
    func_800554C4_main(loc.grp, 9, 0);
    proc = omAddPrcObj(func_801098A0_marios_puzzle_party, 0x4001, 0x800, 0);
    loc.player = player;
    proc->user_data = &loc;
    i = HuSprGrpCreate(1, 5);
    D_801161E8_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_80116090_marios_puzzle_party, 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0xA1));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x4008);
    HuSprPriSet(i, 0, 0x300);
    i = HuSprGrpCreate(1, 5);
    D_801161F8_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_80116098_marios_puzzle_party, 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0x4E));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x4008);
    HuSprPriSet(i, 0, 0x600);
    i = HuSprGrpCreate(1, 5);
    D_80116208_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_8011609C_marios_puzzle_party, 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0x4E));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x5008);
    HuSprPriSet(i, 0, 0x600);
    func_80055458_main(i, 0, 0x80);
    i = HuSprGrpCreate(1, 5);
    D_80116218_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_801160C0_marios_puzzle_party[player], 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0x69));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x5008);
    HuSprPriSet(i, 0, 0x500);
    func_80055458_main(i, 0, 0x9A);
    cur = &D_80116238_marios_puzzle_party[player];
    cur->unk0 = InitEspriteSlot(func_8000B838_main(GwPlayer[player].chr + 0x6A), 0, 1);
    cur->unk2C = cur->unk10 = D_80110080_marios_puzzle_party[player].x + 0x1C;
    cur->unk30 = D_80110080_marios_puzzle_party[player].y - 0x46;
    cur->unk14 = 2;
    cur->unk18 = 10;
    cur->unk24 = 0;
    func_8000BBD4_main(cur->unk0, cur->unk2C + 7.0f, D_801161A8_marios_puzzle_party[player] + cur->unk30);
    func_8000BCC8_main(cur->unk0, 0x200);
    func_8000BB54_main(cur->unk0);
    func_80055140_main(loc.grp, 0, 0, 2);
    func_800550F4_main(loc.grp, 0, 1);
    HuPrcVSleep();
    func_800550F4_main(loc.grp, 0, 0);
    while (func_800E6E8C_minigame() != 2) {
        HuPrcVSleep();
    }
    proc = omAddPrcObj(func_80109D24_marios_puzzle_party, 0x4001, 0x800, 0);
    HuPrcChildLink(HuPrcCurrentGet(), proc);
    next = &D_80116308_marios_puzzle_party[player];
    proc->user_data = next;
    next->unk4 = player;
    HuPrcVSleep();
    if (next->unk1C != 7) {
        func_80055140_main(loc.grp, 0, 0, 0);
        func_800550F4_main(loc.grp, 0, 1);
        HuSprAttrReset(loc.grp, 0, 0x8000);
        HuSprAttrSet(loc.grp, 9, 0x8000);
        HuPrcVSleep();
        i = 0;
    } else {
        func_80055140_main(loc.grp, 9, 0, 0);
        func_800550F4_main(loc.grp, 9, 1);
        HuSprAttrReset(loc.grp, 9, 0x8000);
        HuSprAttrSet(loc.grp, 0, 0x8000);
        HuPrcVSleep();
        i = 9;
    }
    func_800550F4_main(loc.grp, i, 0);
    HuPrcChildWait();

    while (TRUE) {
        if (D_80116108_marios_puzzle_party[player] >= 2) {
            for (i = 0; i < 4; i++) {
                if (i != player) {
                    D_80116118_marios_puzzle_party[i] += D_80116108_marios_puzzle_party[player];
                }
            }
        }
        D_80116108_marios_puzzle_party[player] = 0;
        D_80116138_marios_puzzle_party[player] = 0;
        if (D_80116158_marios_puzzle_party == 2 && D_80116128_marios_puzzle_party[player] >= level * 100) {
            HuAudFXPlay(0x3FC);
            level++;
            D_80116118_marios_puzzle_party[player] = level + 3;
            if (D_80116118_marios_puzzle_party[player] >= 10) {
                D_80116118_marios_puzzle_party[player] = 9;
            }
        }
        garbage = D_80116118_marios_puzzle_party[player];
        D_80116118_marios_puzzle_party[player] = 0;
        if (garbage >= 2) {
            for (i = 0; i < 4; i++) {
                loc.height[i] = 0x15 - func_80107000_marios_puzzle_party(player, i + 1);
            }
            for (n = 0, i = 0; i < 4; i++) {
                if (loc.height[i] >= 2) {
                    loc.flag[i] = 1;
                    n++;
                } else {
                    loc.flag[i] = 0;
                }
            }
            garbage--;
            if (n == 0) {
                break;
            }
            for (cnt = garbage, j = 0; cnt != 0; cnt--) {
                r = (rand8() * (1.0f / 256.0f)) * n;
                for (k = 0, i = 0; i < 4; i++) {
                    if (loc.flag[i] != 0) {
                        if (r == k) {
                            func_80109C04_marios_puzzle_party(player, 6, 1, i + 1, j + 0x1D, j == 0);
                            loc.height[i] -= 2;
                            loc.flag[i] = 0;
                        }
                        k++;
                    }
                }
                if (--n <= 0) {
                    j += 2;
                    if (j >= 6) {
                        break;
                    }
                    for (n = 0, i = 0; i < 4; i++) {
                        if (loc.height[i] >= 2) {
                            loc.flag[i] = 1;
                            n++;
                        } else {
                            loc.flag[i] = 0;
                        }
                    }
                    if (n == 0) {
                        break;
                    }
                }
            }
        }
        HuPrcChildWait();
        speed = 2;
        HuPrcChildWait();
        k = 0;
        if (next->unk1C != 7) {
            x = D_80110080_marios_puzzle_party[player].x + 0x1C;
            y = D_80110080_marios_puzzle_party[player].y - 0x77;
            if (func_8010A4B4_marios_puzzle_party(player, x, y) == 0) {
                x = D_80110080_marios_puzzle_party[player].x + 0x2A;
                if (func_8010A4B4_marios_puzzle_party(player, x, y) == 0) {
                    x = D_80110080_marios_puzzle_party[player].x + 0xE;
                    if (func_8010A4B4_marios_puzzle_party(player, x, y) == 0) {
                        x = D_80110080_marios_puzzle_party[player].x + 0x38;
                        if (func_8010A4B4_marios_puzzle_party(player, x, y) == 0) {
                            break;
                        }
                    }
                }
            }
        } else {
            D_80116188_marios_puzzle_party[player] = 0;
            for (k = 0; k < 4; k++) {
                if (D_801102E0_marios_puzzle_party[player][2][k + 17].unk10 == 0) {
                    break;
                }
            }
            for (cnt = 0; cnt < 4; cnt++) {
                if (D_801102E0_marios_puzzle_party[player][3][cnt + 17].unk10 == 0) {
                    break;
                }
            }
            i = k + 0x13;
            if (cnt >= k) {
                i = cnt + 0x13;
            }
            x = D_80110080_marios_puzzle_party[player].x + 0x2A;
            y = D_80110080_marios_puzzle_party[player].y - i * 7;
        }
        dx1 = (x - next->unk2C) / 10.0f;
        dy1 = (y - next->unk30) / 10.0f;
        dx2 = (x - cur->unk2C) / 10.0f;
        dy2 = (y - cur->unk30) / 10.0f;
        if (next->unk1C != 7) {
            i = 0;
        } else {
            i = 9;
        }
        func_800550F4_main(loc.grp, i, 1);
        fy = y;
        do {
            next->unk2C += dx1;
            next->unk30 += dy1;
            cur->unk2C += dx2;
            cur->unk30 += dy2;
            if (fy <= next->unk30) {
                cur->unk10 = x;
                cur->unk2C = x;
                next->unk2C = cur->unk2C;
                cur->unk30 = fy;
                next->unk30 = fy;
            }
            if (next->unk1C != 7) {
                func_8010FF78_marios_puzzle_party(next->unk8, next->unk2C, next->unk30);
                func_8010FF78_marios_puzzle_party(next->unkC, next->unk2C, next->unk30 - 14.0f);
            } else {
                func_80054904_main(next->unk8, 0, next->unk2C, D_801161A8_marios_puzzle_party[player] + next->unk30);
            }
            func_8000BBD4_main(cur->unk0, cur->unk2C + 7.0f, D_801161A8_marios_puzzle_party[player] + cur->unk30);
            cur->unk14 = (cur->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f;
            HuPrcVSleep();
        } while (next->unk30 != y);
        if (D_80116158_marios_puzzle_party == 2) {
            func_8004AC98_main(0x3FD, player);
        }
        func_8000BD94_main(cur->unk0, 1, 0);
        func_8000BDDC_main(cur->unk0, 1);
        handleA = cur->unk8 = next->unk8;
        handleB = cur->unkC = next->unkC;
        cur->unk1C = next->unk1C;
        cur->unk20 = next->unk20;
        cur->unk24 = 0;
        D_80116228_marios_puzzle_party[player] = handleA;
        proc = omAddPrcObj(func_80109D24_marios_puzzle_party, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        next = &D_80116308_marios_puzzle_party[player];
        proc->user_data = next;
        next->unk4 = player;
        HuPrcVSleep();
        if (next->unk1C != 7) {
            func_80055140_main(loc.grp, 0, 0, 0);
            func_800550F4_main(loc.grp, 0, 1);
            HuPrcVSleep();
            func_800550F4_main(loc.grp, 0, 0);
            HuSprAttrReset(loc.grp, 0, 0x8000);
            i = 9;
        } else {
            func_80055140_main(loc.grp, 9, 0, 0);
            func_800550F4_main(loc.grp, 9, 1);
            HuPrcVSleep();
            func_800550F4_main(loc.grp, 9, 0);
            HuSprAttrReset(loc.grp, 9, 0x8000);
            i = 0;
        }
        HuSprAttrSet(loc.grp, i, 0x8000);

        if (GwPlayer[player].stat & 1) {
            ai = &D_80114DE0_marios_puzzle_party[player];
            ai->unk40 = 0;
            ai->unk42 = 0;
            if (cur->unk1C != 7) {
                for (i = 1; i < 5; i++) {
                    for (j = 1; D_801102E0_marios_puzzle_party[player][i][j].unk10 != 0; j++) {
                    }
                    ai->unk0[i - 1] = j;
                    ai->unk10[0][i - 1] = func_80108A50_marios_puzzle_party(player, 1, cur->unk1C, i, j);
                    ai->unk10[1][i - 1] = func_80108A50_marios_puzzle_party(player, 1, cur->unk20, i, ai->unk0[i - 1]);
                }
                for (n = 0, i = 0; i < 4; i++) {
                    n += func_80107070_marios_puzzle_party(player, i + 1);
                }
                if (D_8011615C_marios_puzzle_party - 10 < D_80116128_marios_puzzle_party[player]) {
                    best = 5;
                } else {
                    best = 0x19;
                    if (D_8011615C_marios_puzzle_party - 20 < D_80116128_marios_puzzle_party[player]) {
                        best = 10;
                    }
                }
                if (best < n) {
                    ai->unk30 = 0;
                } else {
                    ai->unk30 = 1;
                }
                switch (ai->unk30) {
                    case 1:
                        best = 0x3E7;
                        cnt = 0;
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (ai->unk10[i][j] < best) {
                                    best = ai->unk10[i][j];
                                    h = func_80107000_marios_puzzle_party(player, j + 1);
                                    ai->unk38 = i;
                                    ai->unk34 = j + 1;
                                    if (cnt < h && h < 0x12) {
                                        cnt = h;
                                    }
                                } else if (ai->unk10[i][j] == best) {
                                    h = func_80107000_marios_puzzle_party(player, j + 1);
                                    if (cnt < h && h < 0x12) {
                                        cnt = h;
                                        ai->unk38 = i;
                                        ai->unk34 = j + 1;
                                    }
                                }
                            }
                        }
                        break;
                    case 0:
                        best = 0x3E7;
                        cnt = 0;
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (ai->unk10[i][j] > 0) {
                                    cnt = func_80107000_marios_puzzle_party(player, j + 1);
                                    if (cnt < best) {
                                        best = cnt;
                                        ai->unk38 = i;
                                        ai->unk34 = j + 1;
                                    }
                                }
                            }
                        }
                        if (best == 0x3E7) {
                            best = 0;
                            cnt = 0;
                            for (i = 1; i < 5; i++) {
                                h = func_80107000_marios_puzzle_party(player, i);
                                if (best < h) {
                                    best = h;
                                    cnt = i;
                                }
                            }
                            ai->unk38 = 0;
                            ai->unk34 = cnt;
                        }
                        break;
                    case 2:
                        best = 0;
                        for (i = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (best < ai->unk10[i][j]) {
                                    best = ai->unk10[i][j];
                                    ai->unk38 = i;
                                    ai->unk34 = j + 1;
                                }
                            }
                        }
                        if (best == 0) {
                            for (i = 1; i < 5; i++) {
                                h = func_80107000_marios_puzzle_party(player, i);
                                if (best < h) {
                                    best = h;
                                    cnt = i;
                                }
                            }
                            ai->unk38 = 0;
                            ai->unk34 = cnt;
                        }
                        break;
                }
            } else {
                for (i = 0; i < 3; i++) {
                    ai->unk10[0][i] = func_80107108_marios_puzzle_party(player, i + 1);
                    ai->unk10[0][i] += func_80107108_marios_puzzle_party(player, i + 2);
                }
                j = -1;
                for (best = 0, i = 0; i < 3; i++) {
                    if (best < ai->unk10[0][i]) {
                        best = ai->unk10[0][i];
                        j = i;
                    }
                }
                if (j == -1) {
                    ai->unk34 = (u8)(rand8() % 3) + 2;
                } else {
                    ai->unk34 = j + 2;
                }
            }
            switch (GwPlayer[player].cpu_difficulty) {
                case 0:
                    i = rand8() & 1;
                    j = (u8)(rand8() % 30) + 30;
                    break;
                case 1:
                    i = (u8)(rand8() % 3);
                    j = (u8)(rand8() % 20) + 20;
                    break;
                case 2:
                    i = rand8() & 3;
                    j = (u8)(rand8() % 10) + 10;
                    break;
                default:
                    i = (u8)(rand8() % 10);
                    j = (u8)(rand8() % 10) + 1;
                    break;
            }
            ai->unk3C = j;
            if (i == 0) {
                ai->unk34 = ai->unk34 - 1 + (u8)(rand8() % 3);
            }
        }

        cur->unk28 = 0;
        landed = 0;
        if (cur->unk1C != 7) {
            while (TRUE) {
                cur->unk14 = (cur->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f;
                cur->unk18 = (D_80110080_marios_puzzle_party[player].y - cur->unk30) / 7.0f;
                if (GwPlayer[player].stat & 1) {
                    ai->unk40 = 0;
                    ai->unk42 = 0;
                    if (ai->unk34 < cur->unk14) {
                        ai->unk40 |= 0x200;
                    }
                    if (cur->unk14 < ai->unk34) {
                        ai->unk40 |= 0x100;
                    }
                    if (ai->unk38 != 0) {
                        ai->unk38 = 0;
                        ai->unk42 |= 0x8000;
                    }
                    h = func_80107000_marios_puzzle_party(player, ai->unk34);
                    if (ai->unk3C-- <= 0) {
                        if ((cur->unk14 == ai->unk34 && ai->unk42 == 0) || cur->unk18 < h) {
                            ai->unk42 |= 0x2000;
                        }
                        switch (GwPlayer[player].cpu_difficulty) {
                            case 2:
                                if (ai->unk3C < -60) {
                                    ai->unk42 |= 0x2000;
                                }
                                break;
                            case 3:
                                if (ai->unk3C < -30) {
                                    ai->unk42 |= 0x2000;
                                }
                                break;
                        }
                    }
                }
                n = speed;
                hit = 0;
                while (n >= 8) {
                    hit |= func_80106C98_marios_puzzle_party(player, cur, 7);
                    n -= 7;
                }
                if (hit | func_80106C98_marios_puzzle_party(player, cur, n)) {
                    cur->unk30 = D_80110080_marios_puzzle_party[player].y -
                                 (s32)((D_80110080_marios_puzzle_party[player].y - cur->unk30) / 7.0f) * 7;
                    if (cur->unk24 == 0) {
                        func_8010FF78_marios_puzzle_party(handleA, cur->unk2C, cur->unk30);
                        func_8010FF78_marios_puzzle_party(handleB, cur->unk2C, cur->unk30 - 14.0f);
                        if (++landed >= 6 || speed != 2) {
                            break;
                        }
                    }
                }
                if (cur->unk24 == 0 && speed != 7 && cur->unk28 == 0) {
                    if ((func_80105E88_marios_puzzle_party(player) & 0x200) &&
                        func_80106ACC_marios_puzzle_party(player, cur, -1) == 0) {
                        cur->unk24 = -1;
                    }
                    if ((func_80105E88_marios_puzzle_party(player) & 0x100) &&
                        func_80106ACC_marios_puzzle_party(player, cur, 1) == 0) {
                        cur->unk24 = 1;
                    }
                }
                if (cur->unk24 > 0) {
                    cur->unk2C += 5.0f;
                    if (cur->unk10 + 14 < cur->unk2C) {
                        cur->unk10 += 14;
                        cur->unk2C = cur->unk10;
                        cur->unk24 = 0;
                    }
                }
                if (cur->unk24 < 0) {
                    cur->unk2C -= 5.0f;
                    if (cur->unk2C < cur->unk10 - 14) {
                        cur->unk10 -= 14;
                        cur->unk2C = cur->unk10;
                        cur->unk24 = 0;
                    }
                }
                if (cur->unk28 == 0) {
                    speed = (func_80105E88_marios_puzzle_party(player) & 0x400) ? 7 : 2;
                }
                if (func_80105FCC_marios_puzzle_party(player, 0x2000)) {
                    landed = 5;
                    cur->unk28 = 1;
                    speed = 14;
                }
                if (func_80105FCC_marios_puzzle_party(player, 0x8000) && cur->unk28 == 0) {
                    i = cur->unk1C;
                    cur->unk1C = cur->unk20;
                    cur->unk20 = i;
                    i = handleA;
                    handleA = handleB;
                    cur->unk8 = handleA;
                    handleB = i;
                    cur->unkC = handleB;
                }
                func_8000BBD4_main(cur->unk0, cur->unk2C + 7.0f, D_801161A8_marios_puzzle_party[player] + cur->unk30);
                func_8010FF78_marios_puzzle_party(handleA, cur->unk2C, cur->unk30);
                func_8010FF78_marios_puzzle_party(handleB, cur->unk2C, cur->unk30 - 14.0f);
                HuPrcVSleep();
            }
            func_801088F4_marios_puzzle_party(player, cur);
        } else {
            spec = 0;
            D_80116228_marios_puzzle_party[player] = handleA;
            D_801160F0_marios_puzzle_party[player] = 1;
            while (TRUE) {
                if (GwPlayer[player].stat & 1) {
                    ai->unk40 = 0;
                    ai->unk42 = 0;
                    cur->unk14 = (cur->unk2C - D_80110080_marios_puzzle_party[player].x) / 14.0f;
                    if (ai->unk34 < cur->unk14) {
                        ai->unk40 |= 0x200;
                    }
                    if (cur->unk14 < ai->unk34) {
                        ai->unk40 |= 0x100;
                    }
                    func_80107000_marios_puzzle_party(player, ai->unk34);
                    if (ai->unk3C-- <= 0) {
                        if (cur->unk14 == ai->unk34) {
                            ai->unk42 |= 0x2000;
                        }
                        switch (GwPlayer[player].cpu_difficulty) {
                            case 2:
                                if (ai->unk3C < -60) {
                                    ai->unk42 |= 0x2000;
                                }
                                break;
                            case 3:
                                if (ai->unk3C < -30) {
                                    ai->unk42 |= 0x2000;
                                }
                                break;
                        }
                    }
                }
                if (cur->unk24 == 0 && speed != 7 && spec == 0 && cur->unk28 == 0) {
                    if ((func_80105E88_marios_puzzle_party(player) & 0x200) &&
                        func_80106BB0_marios_puzzle_party(player, cur, -1) == 0) {
                        cur->unk24 = -1;
                    }
                    if ((func_80105E88_marios_puzzle_party(player) & 0x100) &&
                        func_80106BB0_marios_puzzle_party(player, cur, 1) == 0) {
                        cur->unk24 = 1;
                    }
                }
                if (cur->unk24 > 0) {
                    cur->unk2C += 5.0f;
                    if (cur->unk10 + 14 < cur->unk2C) {
                        cur->unk10 += 14;
                        cur->unk2C = cur->unk10;
                        cur->unk24 = 0;
                    }
                }
                if (cur->unk24 < 0) {
                    cur->unk2C -= 5.0f;
                    if (cur->unk2C < cur->unk10 - 14) {
                        cur->unk10 -= 14;
                        cur->unk2C = cur->unk10;
                        cur->unk24 = 0;
                    }
                }
                n = speed;
                hit = 0;
                while (n >= 8) {
                    hit |= func_80106E40_marios_puzzle_party(player, cur, 7);
                    n -= 7;
                }
                if (hit | func_80106E40_marios_puzzle_party(player, cur, n)) {
                    cur->unk30 = D_80110080_marios_puzzle_party[player].y -
                                 (s32)((D_80110080_marios_puzzle_party[player].y - cur->unk30) / 7.0f) * 7;
                    if (cur->unk24 == 0) {
                        if (++landed >= 6 || speed != 2) {
                            spec = 1;
                            if (func_8010961C_marios_puzzle_party(player, cur->unk2C, handleA, cur,
                                                                  D_801160F0_marios_puzzle_party[player]) == 0) {
                                break;
                            }
                            D_801160F0_marios_puzzle_party[player] = 0;
                            speed = 7;
                        }
                    }
                }
                if (cur->unk28 == 0) {
                    speed = (func_80105E88_marios_puzzle_party(player) & 0x400) ? 7 : 2;
                }
                if ((func_80105E88_marios_puzzle_party(player) & 0x2000) || spec != 0) {
                    landed = 5;
                    cur->unk28 = 1;
                    speed = 14;
                }
                func_8000BBD4_main(cur->unk0, cur->unk2C + 7.0f, cur->unk30 + 7.0f + D_801161A8_marios_puzzle_party[player]);
                func_80054904_main(handleA, 0, cur->unk2C, D_801161A8_marios_puzzle_party[player] + cur->unk30);
                HuPrcVSleep();
            }
            D_80116228_marios_puzzle_party[player] = -1;
            HuSprGrpKill(handleA);
        }
        HuPrcVSleep();
    }
    D_80116168_marios_puzzle_party[player] = 1;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010AD20_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Game over: drop the board out of view, accelerating. */
void func_8010CF4C_marios_puzzle_party(void) {
    s32 player = (s32)HuPrcCurrentGet()->user_data;
    s32* y;
    f32 speed;

    D_801161C8_marios_puzzle_party[player] = 0;
    speed = 0.0f;
    y = &D_801161C8_marios_puzzle_party[player];
    do {
        speed += 0.5f;
        *y += speed;
        HuPrcVSleep();
    } while (*y < 300);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010CF4C_marios_puzzle_party);
#endif

/* Debris of a cleared block: fly up and out, then fall off screen. */
void func_8010CFF8_marios_puzzle_party(omObjData* obj) {
    PzDebris* d = &D_80114EF0_marios_puzzle_party[obj->work[0]];

    switch (obj->work[1]) {
        case 0:
            switch (obj->work[2]) {
                case 0:
                    d->unk18 = -3.0f;
                    d->unk10 = -1.0f - (u8)(rand8() % 10) * 0.1f;
                    break;
                case 1:
                    d->unk18 = -5.0f;
                    d->unk10 = -1.0f - (u8)(rand8() % 10) * 0.1f;
                    break;
                case 2:
                    d->unk18 = -3.0f;
                    d->unk10 = (u8)(rand8() % 10) * 0.1f + 1.0f;
                    break;
                default:
                    d->unk18 = -5.0f;
                    d->unk10 = (u8)(rand8() % 10) * 0.1f + 1.0f;
                    break;
            }
            obj->work[1] = 1;
        case 1:
            d->unk18 += 1.0f;
            d->unkC += d->unk18;
            d->unk8 += d->unk10;
            func_8010FF78_marios_puzzle_party(d->unk0, d->unk8, d->unkC);
            if (d->unkC > 250.0f) {
                obj->work[1] = 2;
            }
            break;
        case 2:
            func_80110000_marios_puzzle_party(d->unk0);
            d->unk4 = 0;
            obj->work[1] = 100;
            omDelObj(obj);
            break;
    }
}

#ifdef NON_MATCHING
/* Break the block at (col, row) into four debris pieces. */
void func_8010D290_marios_puzzle_party(s32 player, s32 col, s32 row) {
    s32 slot[4];
    s32 x;
    s32 y;
    s32 i;
    s32 n;
    s32 dx;
    s32 dy;
    u32 k;
    PzDebris* d;
    omObjData* obj;

    n = 0;
    for (i = 0; i < 160; i++) {
        if (D_80114EF0_marios_puzzle_party[i].unk4 == 0) {
            slot[n++] = i;
            if (n >= 4) {
                break;
            }
        }
    }
    if (i < 160) {
        x = col * 14 + D_80110080_marios_puzzle_party[player].x;
        y = D_80110080_marios_puzzle_party[player].y - row * 7;
        for (k = 0, dx = 0; dx < 8; dx += 7) {
            for (dy = 0; dy >= -7; dy -= 7, k++) {
                d = &D_80114EF0_marios_puzzle_party[slot[k]];
                d->unk4 = 1;
                d->unk8 = x + dx;
                d->unkC = y + dy;
                d->unk14 = 1.0f;
                d->unk0 = func_8010FEDC_marios_puzzle_party(0x1C, d->unk8, d->unkC);
                obj = omAddObj(100, 0, 0, -1, func_8010CFF8_marios_puzzle_party);
                obj->work[0] = slot[k];
                obj->work[1] = 0;
                obj->work[2] = k;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D290_marios_puzzle_party);
#endif

void func_8010D46C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

#ifdef NON_MATCHING
/* Background sparkle: wait a random time, appear near its spot, drift and shrink. */
void func_8010D490_marios_puzzle_party(void) {
    PzSparkle* sp;
    f32 x0;
    f32 y0;
    f32 vx;
    f32 vy;
    f32 s;

    sp = HuPrcCurrentGet()->user_data;
    omPrcSetDestructor((s32)HuPrcCurrentGet(), func_8010D46C_marios_puzzle_party);
    sp->unk0 = HuSprGrpCreate(1, 5);
    func_80055024_main(sp->unk0, 0, D_8011608C_marios_puzzle_party, 0);
    HuSprAttrReset(sp->unk0, 0, 0xFFFF);
    HuSprAttrSet(sp->unk0, 0, 0xC008);
    HuSprPriSet(sp->unk0, 0, 0x1000);
    x0 = sp->unkC;
    y0 = sp->unk10;
    while (TRUE) {
        HuPrcSleep((u8)(rand8() % 90));
        HuSprAttrReset(sp->unk0, 0, 0x8000);
        sp->unkC = x0;
        sp->unk10 = y0;
        vx = sp->unk18;
        vy = sp->unk1C;
        switch (sp->unk4) {
            case 0:
                sp->unkC = x0 + (u8)(rand8() % 40) - 20.0f;
                break;
            case 1:
                sp->unk10 = y0 + (u8)(rand8() % 40) - 20.0f;
                break;
            default:
                sp->unkC = x0 + (u8)(rand8() % 20) - 10.0f;
                sp->unk10 = y0 + (u8)(rand8() % 20) - 10.0f;
                break;
        }
        switch (rand8() & 1) {
            case 1:
                s = 2.0f;
                if (vx != 0.0f) {
                    if (vx > 0.0f) {
                        vx -= 1.0f;
                    } else {
                        vx += 1.0f;
                    }
                }
                if (vy != 0.0f) {
                    if (vy > 0.0f) {
                        vy -= 1.0f;
                    } else {
                        vy += 1.0f;
                    }
                }
                break;
            default:
                s = 1.2f;
                break;
        }
        for (sp->unk20 = s; sp->unk20 > 0.0f; sp->unk20 -= 0.03f) {
            switch (sp->unk8) {
                case 1:
                    sp->unkC += vx;
                    break;
                case 0:
                    sp->unk10 += vy;
                    break;
                default:
                    sp->unkC += vx;
                    sp->unk10 += vy;
                    break;
            }
            func_80054904_main(sp->unk0, 0, sp->unkC, sp->unk10);
            HuSprScaleSet(sp->unk0, 0, sp->unk20, sp->unk20);
            HuPrcVSleep();
        }
        HuSprAttrSet(sp->unk0, 0, 0x8000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D490_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Special piece landing: shake the player's board. */
void func_8010D8E8_marios_puzzle_party(void) {
    s32 player = (s32)HuPrcCurrentGet()->user_data;
    s32* y = &D_801161B8_marios_puzzle_party[player];
    f32 a;

    a = 0.0f;
    while (TRUE) {
        a += 90.0f;
        if (a > 1080.0f) {
            break;
        }
        *y = 2.0f * sindf(a);
        HuPrcVSleep();
    }
    D_801161B8_marios_puzzle_party[player] = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D8E8_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Hide the pieces and cursors while paused (or once a player is out). */
void func_8010D9AC_marios_puzzle_party(void) {
    PzPiece* cur;
    PzPiece* next;
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            cur = &D_80116238_marios_puzzle_party[i];
            if (cur->unk1C == 7 && D_80116228_marios_puzzle_party[i] != -1) {
                if ((u16)(func_80049F98_main() + D_800D6A90_main) != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                    HuSprAttrSet(D_80116228_marios_puzzle_party[i], 0, 0x8000);
                } else {
                    HuSprAttrReset(D_80116228_marios_puzzle_party[i], 0, 0x8000);
                }
            }
            next = &D_80116308_marios_puzzle_party[i];
            if (next->unk1C == 7) {
                if ((u16)(func_80049F98_main() + D_800D6A90_main) != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                    HuSprAttrSet(next->unk8, 0, 0x8000);
                } else {
                    HuSprAttrReset(next->unk8, 0, 0x8000);
                }
            }
            if ((u16)(func_80049F98_main() + D_800D6A90_main) != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                func_8000BB94_main(cur->unk0);
            } else {
                func_8000BB54_main(cur->unk0);
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D9AC_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Per frame: bob each board until its player is out, add the shake and drop offsets, and move the
   frame, panels and cursor with it. */
void func_8010DB98_marios_puzzle_party(void) {
    struct {
        s32 done[4];
        f32 ang[4];
        f32 off[4];
    } st;
    PzPiece* piece;
    s32 i;

    for (i = 0; i < 4; i++) {
        st.off[i] = 0;
        st.ang[i] = 0;
        st.done[i] = 0;
    }
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (st.done[i] == 0 && func_800E6E8C_minigame()) {
                st.ang[i] += 8.0f;
                st.off[i] = sindf(i * 45.0f + st.ang[i]) * 3.0f;
                if (st.ang[i] > 360.0f) {
                    st.ang[i] -= 360.0f;
                }
                if ((st.ang[i] > 360.0f || st.ang[i] > 180.0f) && D_80116168_marios_puzzle_party[i] != 0) {
                    st.done[i] = 1;
                    st.off[i] = 0;
                }
            }
            D_801161A8_marios_puzzle_party[i] = (s32)st.off[i] + D_801161B8_marios_puzzle_party[i] + D_801161C8_marios_puzzle_party[i];
            func_8011006C_marios_puzzle_party(i, D_801161A8_marios_puzzle_party[i]);
            if (st.done[i] == 0) {
                func_80054904_main(D_801161D8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i].x + 0x2A,
                                   D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i].y - 0xB5);
            }
            func_80054904_main(D_801161E8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i].x + 0x2A,
                               D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i].y - 0xA0);
            func_80054904_main(D_801161F8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i].x + 0x2A,
                               D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i].y - 0x4C);
            func_80054904_main(D_80116208_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i].x + 0x2A,
                               D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i].y - 0x4C);
            func_80054904_main(D_80116218_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i].x + 0x2A,
                               D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i].y - 0x68);
            piece = &D_80116238_marios_puzzle_party[i];
            if (piece->unk1C != 7) {
                func_8000BBD4_main(piece->unk0, piece->unk2C + 7.0f, D_801161A8_marios_puzzle_party[i] + piece->unk30);
            } else {
                if (D_80116228_marios_puzzle_party[i] != -1) {
                    func_80054904_main(piece->unk8, 0, piece->unk2C, D_801161A8_marios_puzzle_party[i] + piece->unk30);
                    if ((u16)(func_80049F98_main() + D_800D6A90_main) != 0) {
                        HuSprAttrSet(piece->unk8, 0, 0x8000);
                    } else {
                        HuSprAttrReset(piece->unk8, 0, 0x8000);
                    }
                }
                func_8000BBD4_main(piece->unk0, piece->unk2C + 7.0f, piece->unk30 + 7.0f + D_801161A8_marios_puzzle_party[i]);
            }
            piece = &D_80116308_marios_puzzle_party[i];
            if (piece->unk1C == 7) {
                func_80054904_main(piece->unk8, 0, piece->unk2C, D_801161A8_marios_puzzle_party[i] + piece->unk30);
                if ((u16)(func_80049F98_main() + D_800D6A90_main) != 0) {
                    HuSprAttrSet(piece->unk8, 0, 0x8000);
                } else {
                    HuSprAttrReset(piece->unk8, 0, 0x8000);
                }
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010DB98_marios_puzzle_party);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E12C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E868_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EAA0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010ECD8_marios_puzzle_party);

void func_8010EEB0_marios_puzzle_party(void) {
    s32 i;

    for (i = 0; i < D_80116100_marios_puzzle_party; i++) {
        if (D_80116168_marios_puzzle_party[i] == 0) {
            omDelPrcObj(D_801163D8_marios_puzzle_party[i]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", D_801102B4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EF30_marios_puzzle_party);
