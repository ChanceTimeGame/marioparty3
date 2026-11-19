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

extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];

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
s16 func_80106A44_marios_puzzle_party(s32 color, s32 kind, s32 state, s32 x, s32 y);
s32 func_80106ACC_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir);
s32 func_80106BB0_marios_puzzle_party(s32 player, PzPiece* piece, s32 dir);
s32 func_80106C98_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy);
s32 func_80106E40_marios_puzzle_party(s32 player, PzPiece* piece, s32 dy);
s32 func_80107000_marios_puzzle_party(s32 player, s32 col);
s32 func_80107070_marios_puzzle_party(s32 player, s32 col);
s32 func_80107108_marios_puzzle_party(s32 player, s32 col);
s32 func_8010718C_marios_puzzle_party(s32 col, s32 row);
void func_80107224_marios_puzzle_party(s32 player, s32 col, s32 row);
void func_80107400_marios_puzzle_party(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80107880_marios_puzzle_party(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80107BB0_marios_puzzle_party(s32 player);
void func_80107CBC_marios_puzzle_party(void);
void func_80108568_marios_puzzle_party(s32 arg0, s32 arg1);
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
extern PzOrigin D_80110080_marios_puzzle_party[4];

// bss
extern PzCell D_801102E0_marios_puzzle_party[4][6][40]; /* D_80110600, D_80110920, D_80110C40 are views */
extern PzAi D_80114DE0_marios_puzzle_party[4]; /* D_80114E20 is a view (player 0's unk40.. tail) */
extern s16 D_80116092_marios_puzzle_party;
extern s16 D_8011609A_marios_puzzle_party;
extern s16 D_8011609E_marios_puzzle_party;
extern s16 D_801160B6_marios_puzzle_party;
extern s16 D_801160BA_marios_puzzle_party;
extern s32 D_801160C0_marios_puzzle_party[4];
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801059A0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105C98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105D50_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105E88_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105FCC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010604C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106A44_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106ACC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106C98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106E40_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107000_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107070_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107108_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010718C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107224_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107400_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107880_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107CBC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108568_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801088F4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108A50_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108C80_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010913C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109160_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010961C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801098A0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109C04_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109D24_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A0D8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A4B4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A588_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A958_marios_puzzle_party);

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
    func_80055024_main(loc.grp, 0, D_801160B6_marios_puzzle_party, 0);
    func_800550F4_main(loc.grp, 0, 0);
    func_80054904_main(loc.grp, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0xB6));
    HuSprAttrReset(loc.grp, 0, 0xFFFF);
    HuSprAttrSet(loc.grp, 0, 0x4000);
    HuSprPriSet(loc.grp, 0, 0x200);
    func_80055024_main(loc.grp, 9, D_801160BA_marios_puzzle_party, 0);
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
    func_80055024_main(i, 0, D_80116092_marios_puzzle_party, 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0xA1));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x4008);
    HuSprPriSet(i, 0, 0x300);
    i = HuSprGrpCreate(1, 5);
    D_801161F8_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_8011609A_marios_puzzle_party, 0);
    func_80054904_main(i, 0, D_80110080_marios_puzzle_party[player].x + 0x2A,
                       D_80110080_marios_puzzle_party[player].y + (D_801161A8_marios_puzzle_party[player] - 0x4E));
    HuSprAttrReset(i, 0, 0xFFFF);
    HuSprAttrSet(i, 0, 0x4008);
    HuSprPriSet(i, 0, 0x600);
    i = HuSprGrpCreate(1, 5);
    D_80116208_marios_puzzle_party[player] = i;
    func_80055024_main(i, 0, D_8011609E_marios_puzzle_party, 0);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010CF4C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010CFF8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D290_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D46C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D490_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D8E8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D9AC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010DB98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E12C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E868_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EAA0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010ECD8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EEB0_marios_puzzle_party);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", D_801102B4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EF30_marios_puzzle_party);
