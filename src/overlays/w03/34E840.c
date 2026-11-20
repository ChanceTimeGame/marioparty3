#include "SpinyDesert.h"
#include "common.h"
#include "game/object.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/10C230.h"
#include "WaluigisIsland.h" /* BranchLink */
#include "game/board.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "../ovl_80_shared_board/106640.h"
#include "input.h"
#include "game/window.h"
#include "game/hmfman.h"

typedef struct {
    u8 unk[4];
} Unk4Bytes;
typedef Unk4Bytes g1Unk4Bytes;
typedef Unk4Bytes g2Unk4Bytes;
typedef Unk4Bytes p3Unk4Bytes;
typedef BranchLink g1BranchLink;
typedef BranchLink p3BranchLink;
typedef s16 SpaceTriple[3];
typedef SpaceTriple p3SpaceTriple;
typedef BranchLink BranchPair[2];
typedef BranchPair p3BranchPair;

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 unk1C;
} ModelFadeWork;

typedef struct WarpBlockSwapWork {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 spriteGroup;
} WarpBlockSwapWork;

typedef struct {
    /* 0x00 */ u16 multiplier;
    /* 0x02 */ u16 threshold;
} p3GameGuyReward;

typedef struct {
    /* 0x00 */ Object *obj1;
    /* 0x04 */ Object *obj2;
    /* 0x08 */ s32 state;
    /* 0x0C */ s32 flag;
} p3ModelAnimWork;

typedef struct {
    s32 player;
    s32 slot;
} W03PipeArg;


void func_80105DB0_w03(void);
void func_801061A0_w03(UnkMBGuideData*);
extern s16 D_8011C150_w03[];
extern Object* D_8011EAC8_w03[];
extern Process* D_8011EB08_w03;
extern Object* D_8011EB0C_w03;
extern s16 D_8011CB20_w03[3][3]; /* D_8011C288_w06 */
extern s16 D_8011CC40_w03[3][3]; /* D_8011C288_w06 */
extern s16 D_8011CCD0_w03[3][3]; /* D_8011C3F0_w06 */
extern s16 D_8011CD18_w03[3][3]; /* D_8011C3F0_w06 */
extern s16 D_8011CD60_w03[3][3]; /* D_8011C3F0_w06 */
extern s16 D_8011CDA8_w03[3][3]; /* D_8011C3F0_w06 */
extern const u8 D_8011E910_w03[]; /* D_8011EA70_w02 */
void func_80106D84_w03(void);
void func_80106E54_w03(void);
s32 func_80106EB4_w03(u8 *arg0);
s32 func_80107148_w03(void);
s32 func_80107628_w03(u8 *arg0, s32 arg1, s32 arg2);
void func_80108AB8_w03(void);
s32 func_801098C8_w03(s32 arg0);
s32 func_80109F44_w03(s32 arg0, s32 arg1);
void func_8010A930_w03(void);
void func_80113080_w03(void);
void func_8011655C_w03(p3SpaceTriple *masu, p3BranchPair *links, DecisionTreeNonLeafNode **trees);
s32 func_8011BD24_w03(void);
s32 func_8011C088_w03(void);
extern s32 D_8011C160_w03; /* D_8011C6E8_w02 */
extern s16 D_8011C1A0_w03[][2]; /* D_8011C724_w02 */
extern s16 D_8011C1A8_w03[][2]; /* D_8011C72C_w02 */
extern s16 D_8011C1B0_w03[][2]; /* D_8011C734_w02 */
extern s16 D_8011C1B8_w03[][2]; /* D_8011C73C_w02 */
extern s16 D_8011C1C0_w03[][2]; /* D_8011C744_w02 */
extern s16 D_8011C1E8_w03[]; /* D_8011C76C_w02 */
extern s16 D_8011C1EC_w03[]; /* D_8011C770_w02 */
extern Vec D_8011C1F0_w03[]; /* D_8011C774_w02 */
extern Vec D_8011C22C_w03[]; /* D_8011C7B0_w02 */
extern s16 D_8011C268_w03[]; /* D_8011C7EC_w02 */
extern s16 D_8011C26C_w03[]; /* D_8011C7F0_w02 */
extern u32 *D_8011C2A8_w03[]; /* D_8011C82C_w02 */
extern s32 D_8011C2C0_w03[]; /* D_8011C844_w02 */
extern s32 D_8011C2E4_w03[]; /* D_8011C868_w02 */
extern s32 D_8011C308_w03[]; /* D_8011C88C_w02 */
extern s32 D_8011C32C_w03[]; /* D_8011C8B0_w02 */
extern s16 D_8011C350_w03[]; /* D_8011C8D4_w02 */
extern s16 D_8011C354_w03[]; /* D_8011C8D8_w02 */
extern DecisionTreeNonLeafNode *D_8011C528_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C5F4_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C6D8_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C804_w03[]; /* D_8011C994_w02 */
extern s16 D_8011CB68_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CB7C_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CBB0_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CBC4_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CBF8_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CC0C_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CC88_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CC9C_w03[][2]; /* D_8011D084_w02 */
extern DecisionTreeNonLeafNode D_8011CF50_w03[]; /* D_8011D414_w02 */
extern u32 D_8011CF68_w03[]; /* D_8011D42C_w02 */
extern s8 D_8011CF98_w03[2][5][7]; /* D_8011D45C_w02 */
extern const char D_8011E98C_w03[]; /* D_8011EA74_w02 */
extern Process *D_8011EAE8_w03[]; /* D_8011EBF8_w02 */
extern Unk3 *D_8011EB10_w03; /* D_8011EC20_w02 */
extern Unk3 *D_8011EB14_w03; /* D_8011EC24_w02 */
extern Unk3 *D_8011EB18_w03; /* D_8011EC28_w02 */
extern Unk3 *D_8011EB1C_w03; /* D_8011EC2C_w02 */
extern Unk3 *D_8011EB20_w03; /* D_8011EC30_w02 */
extern s32 D_8011EB24_w03; /* D_8011EC34_w02 */
extern s32 D_8011EB28_w03; /* D_8011EC38_w02 */
extern Object *D_8011EB54_w03; /* D_8011EC3C_w02 */
extern Object *D_8011EB58_w03[]; /* D_8011EC40_w02 */
extern Object *D_8011EB5C_w03; /* D_8011EC44_w02 */
extern Object *D_8011EB60_w03[]; /* D_8011EC48_w02 */
extern Object *D_8011EB88_w03; /* D_8011EC70_w02 */
extern Object *D_8011EB8C_w03[]; /* D_8011EC74_w02 */
extern s32 D_8011EB94_w03; /* D_8011EC90_w02 */
extern s32 D_8011EB98_w03; /* D_8011EC94_w02 */
extern u8 *D_8011EB9C_w03; /* D_8011EC98_w02 */
extern DecisionTreeNonLeafNode *D_8011C4C8_w03[]; /* D_8011BBA0_w06 */
extern DecisionTreeNonLeafNode *D_8011C774_w03[]; /* D_8011BBA0_w06 */
extern DecisionTreeNonLeafNode *D_8011C864_w03[]; /* D_8011BD98_w06 */
extern DecisionTreeNonLeafNode *D_8011C8D0_w03[]; /* D_8011BD98_w06 */
extern DecisionTreeNonLeafNode *D_8011C924_w03[]; /* D_8011BD98_w06 */
extern BranchLink D_8011CB34_w03[3][2]; /* D_8011C29C_w06 */
extern BranchLink D_8011CC54_w03[3][2]; /* D_8011C29C_w06 */
extern BranchLink D_8011CCE4_w03[3][2]; /* D_8011C404_w06 */
extern BranchLink D_8011CD2C_w03[3][2]; /* D_8011C404_w06 */
extern BranchLink D_8011CD74_w03[3][2]; /* D_8011C404_w06 */
extern BranchLink D_8011CDBC_w03[3][2]; /* D_8011C404_w06 */
extern s16 D_8011C110_w03[]; /* star-space order */
extern s16 D_8011C120_w03[]; /* order constraints */
void func_801059F8_w03(void);
extern s16 D_8011C130_w03[]; /* star board flags */
extern s16 D_8011C140_w03[]; /* star spaces */
void func_8010DF54_w03(void);
void func_8010F3D4_w03(void);
void func_8010F79C_w03(void);
void func_8010F808_w03(void);
void func_80117D38_w03(void);
void func_80110A14_w03(void);
void func_80110CA0_w03(void);
void func_8010FCFC_w03(void);
void func_8011026C_w03(void);
void func_801105B8_w03(void);
void func_80117034_w03(void);
void func_801178B4_w03(void);
void func_801110F0_w03(void);
void func_801113B0_w03(void);
void func_80111750_w03(void);
void func_8011214C_w03(void);
void func_80112CA4_w03(void);
void func_801139BC_w03(void);
void func_80114C58_w03(void);
void func_80115C58_w03(void);
void func_80116E84_w03(void);
void func_8011777C_w03(void);
void func_80105B44_w03(void);
void func_80105C50_w03(void);
void func_80107F30_w03(void);
void func_80116B78_w03(void);
void func_8011908C_w03(void);
s32 func_8011B71C_w03(void);
extern s16 D_8011C164_w03[]; /* blocked-space extension table */
extern s16 D_8011C16C_w03[]; /* blocked spaces */
void func_80108118_w03(void);
void func_801083DC_w03(void);
void func_801085B0_w03(void);
void func_80108820_w03(void);
void func_801088A0_w03(void);
extern s16 D_8011C180_w03[][2]; /* star guide offsets (asm also labels +2 as D_8011C182_w03) */
extern s16 D_8011C1C8_w03[]; /* star guide spaces */
extern Object *D_8011EAC0_w03;
void func_80107D54_w03(s16 arg0);
extern s16 D_8011C1D8_w03[]; /* star guide board flags */
void func_80107ECC_w03(void);
extern s16 D_8011C358_w03[]; /* board flag per star space */
extern s16 D_8011C368_w03[8];
extern s16 D_8011C378_w03[8];
extern s16 D_8011C388_w03[8];
extern s16 D_8011C398_w03[8];
extern s16 D_8011C3A8_w03[8];
extern s16 D_8011C3B8_w03[8];
extern s16 D_8011C3C8_w03[8];
extern DecisionTreeNonLeafNode *D_8011CABC_w03[];
extern s16 D_8011CAD8_w03[3][3];
extern BranchLink D_8011CAEC_w03[3][2];
extern s16 D_8011CDF0_w03[];
extern s16 D_8011CDF8_w03[];
extern s16 D_8011CE00_w03[];
extern s16 D_8011CE08_w03[];
void func_800D7770_shared_board(s32 arg0); /* not in EB2F0.h */
void func_8001ED54_main(s16 arg0);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8010F2BC_w03(omObjData *arg0);
void func_80106C2C_w03(Object *arg);
void func_80106CA0_w03(void);
void func_80106D28_w03(void);
s32 func_801078F4_w03(u8 *arg0);
s32 func_80107914_w03(u8 *arg0);
void func_801087E4_w03(s32 arg);
void func_8010B55C_w03(void);
void func_801128B0_w03(void);
omObjData *func_8010F160_w03(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5);
Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010FF2C_w03(void);
extern u8 D_8011CF80_w03[2][3][4];
extern u8 D_8011CFE0_w03[2][3][4];
extern s8 D_8011CFF8_w03[2][5][10];
extern u8 D_8011D05C_w03[2][10];
extern s32 D_8011D070_w03[5][2];
extern s32 D_8011D098_w03[2];
extern s32 D_8011D0A0_w03[2];
extern s32 D_8011D0A8_w03[2];
extern s32 D_8011D0B0_w03[2];
extern s32 D_8011D0B8_w03[2];
extern u32 D_8011D0C0_w03[];
extern u32 D_8011D0C8_w03[];
extern s32 D_8011D0D0_w03;
extern Vec2f D_8011D0E4_w03[];
extern Vec2f D_8011D104_w03[];
extern u8 D_8011D124_w03[6][3];
extern u8 D_8011D138_w03[14][3];
extern u8 D_8011D164_w03[];
extern s32 D_8011D16C_w03[];
extern s32 D_8011D178_w03[];
extern Vec2f D_8011D24C_w03[];
extern Vec2f D_8011D26C_w03[];
extern s32 D_8011D338_w03[];
extern Object *D_8011EBA0_w03;
extern s32 D_8011EBA4_w03;
extern DecisionTreeNonLeafNode D_8011D2CC_w03[];
extern DecisionTreeNonLeafNode D_8011D34C_w03[];
extern Vec2f D_8011D358_w03[];
extern s32 D_8011D388_w03;
extern u8 D_8011D38C_w03[];
extern u8 D_8011D390_w03[];
extern p3GameGuyReward D_8011D394_w03[];
extern RGB D_8011D3B0_w03[];
extern s32 D_8011EBA8_w03;
extern s32 D_8011EBAC_w03;
extern Object *D_8011EBB0_w03;
extern Object *D_8011EBB4_w03;
extern s32 D_8011EBB8_w03;
extern s32 D_8011EBBC_w03;
extern Object *D_8011EBC0_w03;
extern s32 D_8011EBC8_w03[4];
extern Object *D_8011EBD8_w03;
extern Object *D_8011EBE0_w03[4];
extern omObjData *D_8011EBF0_w03[4];
void func_80108174_w03(void);
void func_8010A1C8_w03(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
void func_8010A284_w03(void);
void func_8010B734_w03(void);
void func_8011077C_w03(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode);
void func_80110EE0_w03(void);
void func_80112694_w03(void);
void func_80112D60_w03(void);
void func_80112EF0_w03(void);
s32 func_8011343C_w03(u8 *arg0, s32 arg1);
void func_80114728_w03(void);
void func_80116830_w03(omObjData *obj);
void func_80116ADC_w03(s32 arg);
void func_801167CC_w03(void);
void func_801169DC_w03(s32 arg0, s32 arg1);
void func_80116754_w03(s32 arg0);
void func_80116FE4_w03(void);
extern s32 D_8011EC04_w03;
void func_801175AC_w03(void);
extern s32 D_8011EC00_w03;
extern Vec2f D_8011D28C_w03[]; /* splat labels D_8011D28C (x) / D_8011D290 (rest): one Vec2f[4] */
void func_801100FC_w03(void);
extern Vec2f D_8011D2AC_w03[]; /* D_8011D2AC / D_8011D2B0 likewise */
extern s32 D_8011EB40_w03[];
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
extern Object *D_8011EB30_w03;
extern Process *D_8011EB2C_w03;
extern DecisionTreeNonLeafNode D_8011C9FC_w03[];
extern DecisionTreeNonLeafNode D_8011CA44_w03[];
extern DecisionTreeNonLeafNode D_8011CA68_w03[];
extern s16 D_8011D3E0_w03[];
extern s16 D_8011D3E8_w03[];
extern s16 D_8011D3F0_w03[];
extern Object *D_8011EB34_w03;
Process *func_800ED75C_shared_board(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
extern Object *D_8011EB38_w03;
extern SpaceData *D_8011EB3C_w03;
extern s32 D_8011EB50_w03;
extern Vec2f D_8011D438_w03[]; /* splat labels D_8011D438 (x) / D_8011D43C (y) */
void func_8011A338_w03(void);
void func_8011A550_w03(void);
extern s16 D_8011D3F8_w03[];
extern s16 D_8011D404_w03[];
extern s16 D_8011D41C_w03[];
void func_80032FC0_main(s16, u8, u8);
void func_80119290_w03(void);
extern DecisionTreeNonLeafNode D_8011C948_w03[];
extern DecisionTreeNonLeafNode D_8011C99C_w03[];
extern s16 D_8011D458_w03[];
extern s16 D_8011D460_w03[];
extern DecisionTreeNonLeafNode D_8011E0DC_w03[];
extern DecisionTreeNonLeafNode D_8011E64C_w03[];
extern DecisionTreeNonLeafNode D_8011E3A0_w03[];
extern DecisionTreeNonLeafNode D_8011DF68_w03[];
extern DecisionTreeNonLeafNode D_8011DB9C_w03[];
extern DecisionTreeNonLeafNode D_8011DDD0_w03[];
s32 func_8011B470_w03(void);
extern DecisionTreeNonLeafNode D_8011E568_w03[];
s32 func_8011B51C_w03(void);
extern DecisionTreeNonLeafNode D_8011DB30_w03[];
extern DecisionTreeNonLeafNode D_8011E6B8_w03[];
extern DecisionTreeNonLeafNode D_8011E184_w03[];
extern DecisionTreeNonLeafNode *D_8011E8EC_w03[2];
extern u8 *D_8011E82C_w03[8];
extern DecisionTreeNonLeafNode *D_8011E8F4_w03[2];
extern s32 D_8011E7A8_w03;
s32 func_8010B4F4_w03(void);
s32 func_8010B46C_w03(s32 item);
extern s8 *D_8011E8CC_w03[8];
extern DecisionTreeNonLeafNode *D_8011E8FC_w03[];


s16 func_801059D0_w03(void) {
    return D_8011C150_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

#ifdef NON_MATCHING
// board p1: li s0,7 scheduled into the MBRand delay slot (retail: before the lui)
void func_801059F8_w03(void) {
    s32 var;
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011C120_w03[idx2]) {
                continue;
            }
            if (idx2 < D_8011C120_w03[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011C110_w03[idx1];
                D_8011C110_w03[idx1] = D_8011C110_w03[idx2];
                D_8011C110_w03[idx2] = temp;
                temp = D_8011C120_w03[idx1];
                D_8011C120_w03[idx1] = D_8011C120_w03[idx2];
                D_8011C120_w03[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011C110_w03[i];
    }

    var = 7;
    GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f) + 1];
    if (GwSystem.boardData.halfWordBytes[0] != var) {
        GWBoardFlagClear(0x12);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801059F8_w03);
#endif

void func_80105B44_w03(void) {
    s32 temp_s0;
    s32 temp_v1;
    GW_SYSTEM *system = &GwSystem;

    if (++system->current_star_spawn >= 8) {
        temp_s0 = system->star_spawn_indices[7];
        system->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w03();
        if (temp_s0 == system->star_spawn_indices[0]) {
            temp_s0 = system->star_spawn_indices[0];
            system->star_spawn_indices[0] = system->star_spawn_indices[7];
            system->star_spawn_indices[7] = temp_s0;
        }
    }
    if (system->current_star_spawn >= 7) {
        GwSystem.boardData.halfWordBytes[0] = system->star_spawn_indices[MBRand(6.0f)];
    } else {
        GwSystem.boardData.halfWordBytes[0] = system->star_spawn_indices[MBRand(7 - system->current_star_spawn) + system->current_star_spawn + 1];
    }
    GWBoardFlagClear(0x12);
}

void func_80105C50_w03(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011C130_w03[i]);
    }
    MBMasuTypeSet(D_8011C140_w03[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011C130_w03[loc->star_spawn_indices[loc->current_star_spawn]]);
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        MBMasuTypeSet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]], 0xE);
    }
}

s16 func_80105D20_w03(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011C140_w03[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011C130_w03[i];
                return 1;
            }
            if (i == GwSystem.boardData.halfWordBytes[0]) {
                return 2;
            }
            break;
        }
    }
    return 0;
}

void func_80105DB0_w03(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011EB0C_w03 = MBModelCreate(0x3A, NULL);
    model = D_8011EB0C_w03;
    func_800461B4_main(model->omObj1->model[0]);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    HuVecCopy3F(&model->coords, &space->coords);
    model->velocity.x = 50.0f;
    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 30.0f);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
    func_8001C8A8_main(obj, 1);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 30.0f);
    HuPrcSleep(30);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    while (1) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (scale > 0.6f) {
            scale -= 0.04f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        if (model->velocity.x > 10.0f) {
            model->velocity.x -= 1.2f;
        }
        func_8000D018_main(obj, scale * 30.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        if ((model->velocity.x <= 10.0f) & (scale <= 0.6f)) {
            if (angle == 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, 0.0f);
    func_8000D044_main(obj);
    D_8011EB08_w03 = NULL;
    omDelPrcObj(NULL);
}

void func_801061A0_w03(UnkMBGuideData *arg) {
    omObjData *s0 = *(omObjData **)arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

// Star tour.
void func_8010622C_w03(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *first;
    SpaceData *second;
    SpaceData *temp;
    s32 mesNum;
    GW_SYSTEM* system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, 0xA007E);
    func_800FFF44_shared_board();
    MBModelDispOff(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOff(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_801061A0_w03(guide);

    first = MBMasuGet(D_8011C150_w03[system->star_spawn_indices[system->current_star_spawn]]);
    second = MBMasuGet(D_8011C150_w03[GwSystem.boardData.halfWordBytes[0]]);

    if (MBRandCheck100(50) != 0) {
        temp = first;
        first = second;
        second = temp;
    }
    
    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        mesNum = 0x5E09;
    } else {
        mesNum = 0x5E0A;
    }

    
    func_8005B43C_main(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    temp = first;
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    MBMotionSet(guide->obj, -1, 2);
    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    D_800CC69C_main[guide->amount].unk20 = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);

    while (D_8011EB08_w03 != NULL) {
        HuPrcVSleep();
    }
    temp = second;
    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    D_800CC69C_main[guide->amount].unk20 = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011EB0C_w03->omObj1->model[0]);
    MBModelKill(D_8011EB0C_w03);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}


void func_801066CC_w03(void) {
    Object *playerModel = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *model;
    Vec camPos;
    f32 scale;
    f32 angle;
    s32 obj;
    s32 i;

    HuAudFXPlay(0x11B);
    model = MBModelCreate(0x1A, NULL);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8E) {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 15.0f;
    } else {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z + 30.0f);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 35.0f;
    }

    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 15.0f);
    func_8001C8A8_main(obj, 1);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 15.0f);
    HuPrcSleep(20);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    HuVecCopyXYZ(&camPos, player->player_obj->coords.x, player->player_obj->coords.y - 10.0f, player->player_obj->coords.z);
    MBPlayerPosMoveCreate(&model->coords, &camPos, &model->coords, 40);

    for (i = 0; i < 40; i++) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        scale -= 0.05f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8000D018_main(obj, scale * 15.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(model);
    func_8000D044_main(obj);
    MBVecForwardSet(&player->player_obj->rot);
    MBPlayerVibrate(-1, 5);
    if (D_8011C160_w03 != 0) {
        func_8004A670_main(0xE);
    } else {
        HuAudSeqPlay(0x6F);
    }

    GwPlayer[GwSystem.current_player_index].star += 1;
    if (GwPlayer[GwSystem.current_player_index].star >= 100) {
        GwPlayer[GwSystem.current_player_index].star = 99;
    }

    MBPlayerMotionSet(-1, 6, 0);
    func_8004ACE0_main(0x262, GwSystem.current_player_index);
    if (D_8011C160_w03 != 0) {
        HuPrcSleep(16);
        func_80003A70_main(D_800CDBC8_main);
        func_8004A918_main(0x6F);
        func_8004A880_main(0);
        HuPrcSleep(110);
        func_80003B70_main(D_800CDBC8_main, 0);
        func_8004A72C_main(0xF);
    } else {
        HuPrcSleep(60);
    }
    omDelPrcObj(NULL);
}

void func_80106C2C_w03(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801066CC_w03, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106CA0_w03(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106D28_w03(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106D84_w03(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011EB10_w03 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011EB14_w03 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011EB20_w03 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011EB18_w03 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011EB1C_w03 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106E54_w03(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EB10_w03);
    MBHelpWinKill(D_8011EB14_w03);
    MBHelpWinKill(D_8011EB20_w03);
    MBHelpWinKill(D_8011EB18_w03);
    MBHelpWinKill(D_8011EB1C_w03);
}

s32 func_80106EB4_w03(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011BD24_w03();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < 9; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
    } while (arg0[i] == 0);
    return i;
}

s32 func_80107148_w03(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011C088_w03();
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_80107360_w03(void) {
    s32 i;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != 4) {
        if (GwPlayer[cur].coin >= 50) {
            if (MBRand(100.0f) < GwPlayer[cur].coin + 10) {
                D_8011EB24_w03 = 1;
                if (GwPlayer[cur].star < 99) {
                    return;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != 4) {
        D_8011EB24_w03 = 0;
    } else {
        D_8011EB24_w03 = 2;
    }
}

void func_80107490_w03(void) {
    s32 order[4];
    s32 i;
    s32 j;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        order[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        j = MBPlayerStealRankGet(i);
        while (1) {
            if (order[j] == -1) {
                break;
            }
            j++;
        }
        order[j] = i;
    }
    func_80107360_w03();
    if (D_8011EB24_w03 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    } else if (D_8011EB24_w03 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_8011EB24_w03 = 2;
    }
}

s32 func_80107628_w03(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_80107490_w03();
                    var_s2 = D_8011EB24_w03 + 1;
                } else {
                    var_s2 = D_8011EB28_w03 + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (1) {
        i = func_8005E1D8_main(mbDlgWinId, i, arg2);
        if (arg2 == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (arg0[i] != 0) {
            return i;
        }
    }
}

s32 func_801078F4_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 0, 1);
}

s32 func_80107914_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 1, 0);
}

// entrypoint 0
void func_80107934_w03(void) {
    GwSystem.current_board_index = 2;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

// entrypoint 1
void func_80107970_w03(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w03();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[2] = 0;
    omOvlReturnEx(1);
}

void func_80107A04_w03(void) {
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(9, 0x23C, 0xB, 0);
    MBMasuBlockTblExtSet(D_8011C164_w03);
    MBMasuBlockTblSet(D_8011C16C_w03);
    MBItemHookSet(0, &func_8010DF54_w03);
    MBItemHookSet(1, &func_8010F3D4_w03);
    MBItemHookSet(9, &func_8010F79C_w03);
    MBItemHookSet(2, &func_8010F808_w03);
    MBItemHookSet(3, &func_80117D38_w03);
    MBItemHookSet(4, &func_80110A14_w03);
    MBItemHookSet(5, &func_80110CA0_w03);
    MBItemHookSet(6, &func_8010FCFC_w03);
    MBItemHookSet(7, &func_8011026C_w03);
    MBItemHookSet(8, &func_801105B8_w03);
    MBItemHookSet(0xA, &func_80117034_w03);
    MBItemHookSet(0xB, &func_801178B4_w03);
    MBItemHookSet(0xE, &func_801110F0_w03);
    MBItemHookSet(0xF, &func_801113B0_w03);
    MBItemHookSet(0x10, &func_80111750_w03);
    MBItemHookSet(0x11, &func_8011214C_w03);
    MBItemHookSet(0x12, &func_80112CA4_w03);
    MBItemHookSet(0x13, &func_801139BC_w03);
    MBItemHookSet(0x14, &func_80114C58_w03);
    MBItemHookSet(0x15, &func_80115C58_w03);
    MBItemHookSet(0xC, &func_80116E84_w03);
    MBItemHookSet(0xD, &func_8011777C_w03);
    MBComItemDecideHookSet(func_8011B71C_w03);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011C150_w03[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B44_w03();
    }

    func_80105C50_w03();
    func_80107F30_w03();
    func_80108118_w03();
    func_801083DC_w03();
    func_801085B0_w03();
    func_80108820_w03();
    func_801088A0_w03();
    func_80116B78_w03();
    func_800EBDAC_shared_board();
    omAddPrcObj(func_8011908C_w03, 0x4800, 0, 0);
}

// entrypoint 2
void func_80107CA4_w03() {
    HuAudSeqPlay(0x1A);
    D_800CE198_main = 0x1A;
    func_800F8D6C_shared_board(0x1A);
    Hu3DCamInit(2);
    func_80107A04_w03();
    MBMasuEventTblAdd(D_8011D1C4_w03);
    MBMasuEventTblAdd(D_8011D478_w03);
    MBHatenaFuncSet(func_8011A704_w03);
    MBMasuEventTblAdd(D_8011D23C_w03);
    MBMasuEventTblAdd(D_8011D3D0_w03);
    MBStart(0);
}

// entrypoint 3
void func_80107D28_w03(void) {
    Hu3DCamInit(1);
    func_80107A04_w03();
    MBStart(1);
}

void func_80107D54_w03(s16 arg0) {
    Object *obj;

    if (D_8011EAC8_w03[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001FA68_main(obj->omObj2->model[0]);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011EAC0_w03 == NULL) {
        D_8011EAC0_w03 = obj;
    }
    D_8011EAC8_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011EAE8_w03[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1C8_w03[arg0])->coords);
    GwSystem.boardData.halfWordBytes[1] = func_800D771C_shared_board(0xB, obj, D_8011C180_w03[arg0][0], D_8011C180_w03[arg0][1]);
}

void func_80107ECC_w03(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_8011EAE8_w03[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_8011EAE8_w03[i] = NULL;
        }
    }
}

void func_80107F30_w03(void) {
    s32 i;

    D_8011EAC0_w03 = NULL;
    for (i = 0; i < 8; i++) {
        D_8011EAC8_w03[i] = NULL;
        D_8011EAE8_w03[i] = NULL;
        MBKinokoEffKillHookSet(func_80107ECC_w03);
        if (!GWBoardFlagCheck(D_8011C1D8_w03[i])) {
            func_80107D54_w03(i);
        }
    }
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        func_80107D54_w03(GwSystem.boardData.halfWordBytes[0]);
    }
}

void func_80107FF8_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB58_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB54_w03 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011EB54_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB54_w03);
    }
    MBModelDispOff(obj);
    D_8011EB58_w03[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1E8_w03[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011C1A0_w03[arg0][0], D_8011C1A0_w03[arg0][1]);
}

void func_80108118_w03(void) {
    s32 i;

    D_8011EB54_w03 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011EB58_w03[i] = NULL;
        func_80107FF8_w03(i);
    }
}

void func_80108174_w03(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011EB60_w03[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011EB60_w03[i * 5 + j]);
        }
    }
}

void func_80108270_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB60_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB5C_w03 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011EB5C_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB5C_w03);
    }
    D_8011EB60_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1EC_w03[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011C1F0_w03[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011C22C_w03[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011C22C_w03[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_801083DC_w03(void) {
    s32 i;

    D_8011EB5C_w03 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011EB60_w03[i] = NULL;
        func_80108270_w03(i);
    }
    func_80108174_w03();
}

void func_80108444_w03(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011EB8C_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB88_w03 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011C26C_w03[board], D_8011C2A8_w03[board]);
        MBModelTempAllocFree(obj);
        D_8011EB88_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB88_w03);
    }
    D_8011EB8C_w03[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C268_w03[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011C1C0_w03[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011C1C0_w03[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011C1B8_w03[arg0][0], D_8011C1B8_w03[arg0][1]);
}

void func_801085B0_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        D_8011EB8C_w03[i] = NULL;
        func_80108444_w03(i);
    }
}

void func_80108610_w03(void) {
    HuPrcSleep(D_8011C308_w03[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011C2E4_w03[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_8010866C_w03(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011EB8C_w03[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011EB8C_w03[arg0]->omObj1->model[0], 5, 0);
    if (D_8011C2C0_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C2C0_w03[GwSystem.current_board_index]);
    }

    if (D_8011C2E4_w03[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108610_w03, 0x1000, 0, 0);
    }
}

void func_80108734_w03(void) {
    s32 index;
    s32 sleep;

    index = (s32)HuPrcCurrentGet()->user_data;

    switch (GwSystem.walk_speed) {
        case 0:
            sleep = 5;
            break;
        case 1:
            sleep = 10;
            break;
        default:
            sleep = 15;
            break;
    }

    HuPrcSleep(sleep);
    func_8001C814_main(D_8011EB8C_w03[index]->omObj1->model[0], 1, 4);

    if (D_8011C32C_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C32C_w03[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_801087E4_w03(s32 arg) {
    Process *temp = omAddPrcObj(func_80108734_w03, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_80108820_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011C350_w03[i])->coords,
                                         D_8011C1A8_w03[i][0], D_8011C1A8_w03[i][1]);
    }
}

void func_801088A0_w03(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011C354_w03[i])->coords,
                                         D_8011C1B0_w03[i][0], D_8011C1B0_w03[i][1]);
    }
}

s32 func_80108918_w03(s16 *list) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    for (; i < 8; i++) {
        if (*list == GwSystem.boardData.halfWordBytes[0]) {
            found = 1;
            break;
        }
        if (!GWBoardFlagCheck(D_8011C358_w03[*list])) {
            break;
        }
        list++;
    }
    return found;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E910_w03);

s32 func_801089AC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *list;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x79:
            list = D_8011C368_w03;
            break;
        case 0x84:
            list = D_8011C378_w03;
            break;
        case 0x89:
            list = D_8011C388_w03;
            break;
        case 0x8A:
            list = D_8011C398_w03;
            break;
        case 0x8B:
            list = D_8011C3A8_w03;
            break;
        case 0x6F:
            list = D_8011C3B8_w03;
            break;
        default:
            list = D_8011C3C8_w03;
            break;
    }
    if (func_80108918_w03(list) != 0) {
        GwSystem.boardData.halfWordBytes[2] |= 1 << GwSystem.current_player_index;
    } else {
        GwSystem.boardData.halfWordBytes[2] &= ~(1 << GwSystem.current_player_index);
    }
    return 0;
}

void func_80108AB8_w03(void) {
    MBMoveNextMasuSet(-1, 1, 7);
}

void func_80108ADC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6D) {
        if (player->rev & 0x80) {
            if (mbWalkNum != 0) {
                func_8011655C_w03((SpaceTriple *)D_8011CAD8_w03, (BranchPair *)D_8011CAEC_w03, D_8011CABC_w03);
                return;
            }
            MBMoveBackMasuSet(-1, 1, 8);
        } else {
            MBMoveBackMasuSet(-1, 1, 6);
        }
    }
}

void func_80108B98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x41 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 2, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03((SpaceTriple *)D_8011CB20_w03, (BranchPair *)D_8011CB34_w03, D_8011C4C8_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108C48_w03(void) {
    func_8011655C_w03(D_8011CB68_w03, D_8011CB7C_w03, D_8011C528_w03);
    omDelPrcObj(NULL);
}

void func_80108C80_w03(void) {
    func_8011655C_w03(D_8011CBB0_w03, D_8011CBC4_w03, D_8011C5F4_w03);
    omDelPrcObj(NULL);
}

void func_80108CB8_w03(void) {
    func_8011655C_w03(D_8011CBF8_w03, D_8011CC0C_w03, D_8011C6D8_w03);
    omDelPrcObj(NULL);
}

void func_80108CF0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x32 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 9, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03((SpaceTriple *)D_8011CC40_w03, (BranchPair *)D_8011CC54_w03, D_8011C774_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108DA0_w03(void) {
    func_8011655C_w03(D_8011CC88_w03, D_8011CC9C_w03, D_8011C804_w03);
    omDelPrcObj(NULL);
}

void func_80108DD8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CCD0_w03, (BranchPair *)D_8011CCE4_w03, D_8011C864_w03);
    }
}

void func_80108E30_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CD18_w03, (BranchPair *)D_8011CD2C_w03, D_8011C864_w03);
    }
}

void func_80108E88_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CD60_w03, (BranchPair *)D_8011CD74_w03, D_8011C8D0_w03);
    }
}

void func_80108EE0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CDA8_w03, (BranchPair *)D_8011CDBC_w03, D_8011C924_w03);
    }
}

void func_80108F38_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    UnkEA790Struct *win;
    s32 sel;
    s32 choice;
    s32 sel2;
    s32 i;

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        func_80106D84_w03();

        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF0_w03);
                choice = MBRand(3.0f);
                break;
            case 0x46:
                choice = 2;
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF8_w03);
                break;
            case 0x45:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE00_w03);
                choice = MBRand(3.0f);
                break;
            default:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE08_w03);
                choice = MBRand(3.0f);
                break;
        }

        func_800D742C_shared_board(win, GwSystem.current_player_index, 0);

        if (MBPlayerComCheck(-1) != 0) {
            sel = choice;
            for (i = 0; i < sel; i++) {
                func_800D7250_shared_board(win, -2);
            }
            func_800D7250_shared_board(win, -4);
        }

        sel2 = func_800D7518_shared_board(win);
        func_800D6CA0_shared_board(win);
        func_80106E54_w03();

        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x46:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x45:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            default:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                }
                break;
        }
    }
}

void func_80109268_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x3B) {
        MBMoveNextMasuSet(-1, 11, 11);
    }
}

void func_801092C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x43) {
        MBMoveNextMasuSet(-1, 1, 13);
    }
}

void func_80109328_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x8) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109388_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x9) {
        MBMoveNextMasuSet(-1, 2, 2);
    }
}

void func_801093E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xD) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109448_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xF) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_801094A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x54) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_80109508_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5B) {
        MBMoveNextMasuSet(-1, 5, 10);
    }
}

void func_80109568_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 25);
    }
}

void func_801095C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2F) {
        MBMoveNextMasuSet(-1, 5, 20);
    }
}

void func_80109628_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x8B) {
        MBMoveNextMasuSet(-1, 5, 25);
    }
}

void func_80109688_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5E) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_801096E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x51) {
        MBMoveNextMasuSet(-1, 5, 18);
    }
}

void func_80109748_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x42) {
        MBMoveNextMasuSet(-1, 1, 13);
    }
}

void func_801097A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x44) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109808_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x33) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_80109868_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2) {
        MBMoveNextMasuSet(-1, 11, 11);
    }
}

s32 func_801098C8_w03(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1;
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 0x5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_80109AD8_w03(void) {
    GW_PLAYER *player;
    Process *proc;
    UnkVibrateProcess *vib;
    s32 masu;
    s32 ret;
    s32 blocked = 1;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(-1);
    masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    if ((((masu == 0x74) | (masu == 0x8C)) == 0 || !(player->rev & 1)) &&
        (((masu == 0x75) | (masu == 0x8D)) == 0 || (player->rev & 1))) {
        MBPlayerMotionSet(-1, -1, 2);

        if (MBItemFind(system->current_player_index, 1) != -1) {
            func_800DBEC0_shared_board(system->current_player_index);
            switch (masu) {
                case 0x74:
                case 0x75:
                    func_800ED20C_shared_board(-1, 8, 0x7D);
                    break;
                default:
                    func_800ED20C_shared_board(-1, 8, 0x7E);
            }

            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.6f));
            HuPrcChildWait();
            MBPlayerVibrate(-1, 1);

            while (1) {
                MBDlgWinCreate(0x38, 0x4103);
                ret = func_801098C8_w03(0);
                MBDlgWinClose();
                MBDlgWinKill();
                switch (ret) {
                    case 0:
                        MBDlgWinExec(0x38, 0x4104);
                        GwPlayer[system->current_player_index].itemNo[MBItemFind(system->current_player_index, 1)] = -1;
                        MBItemRemoveEmpty(GwSystem.current_player_index);
                        MBStatusItemIconSprReinit(-1);
                        switch (masu) {
                            case 0x74:
                                func_8010866C_w03(0, 0);
                                break;
                            case 0x75:
                                func_8010866C_w03(0, 1);
                                break;
                            case 0x8C:
                                func_8010866C_w03(1, 0);
                                break;
                            default:
                                func_8010866C_w03(1, 1);
                                break;
                        }
                        blocked = 0;
                        vib = MBPlayerVibrateObjCreate(-1, 2, 5);
                        HuPrcSleep(0x14);
                        MBPlayerVibrateObjKill(vib);
                        break;
                    case 1:
                        MBDlgWinExec(0x38, 0x4105);
                        break;
                    case 2:
                        func_80106CA0_w03();
                        continue;
                }
                break;
            }
            func_800DB884_shared_board(system->current_player_index);
            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.3f));
            HuPrcChildWait();
        } else {
            MBDlgWinExec(-1, 0x4106);
        }

        if (blocked != 0) {
            switch (masu) {
                case 0x74:
                    MBMoveNextMasuSet(-1, 0xA, 1);
                    player->rev |= 1;
                    break;
                case 0x75:
                    MBMoveNextMasuSet(-1, 0xA, 5);
                    player->rev &= ~1;
                    break;
                case 0x8C:
                    MBMoveNextMasuSet(-1, 0xB, 2);
                    player->rev |= 1;
                    break;
                default:
                    MBMoveNextMasuSet(-1, 0xB, 6);
                    player->rev &= ~1;
                    break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_80109E90_w03(void) {
}

void func_80109E98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 2 && MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x63) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109F3C_w03(void) {
}

s32 func_80109F44_w03(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g2Unk4Bytes *)sp20 = *(g2Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch (arg0) {
                    case 0:
                        var_s2 = func_800EF0D8_shared_board(0) + 1;
                        break;
                    case 1:
                        var_s2 = func_800EF0D8_shared_board(1) + 1;
                        break;
                    case 2:
                        var_s2 = arg1 + 1;
                        break;
                    default:
                        var_s2 = MBComTreeExec((void *)arg0) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_8010A1C8_w03(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s16 sp10[2];
    s16 winId;

    func_80060394_main(1, sp10, arg1);
    winId = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = winId;
    func_8005B43C_main(winId, arg1, -1, -1);
    func_80061388_main(winId);
    func_800EBF98_shared_board(winId, arg3);
    func_80061A5C_main(winId, 0);
    func_8005F364_main(winId);
}

void func_8010A284_w03(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_8010A2C4_w03(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;
    Object *model;
    SpaceData *space;
    s32 alpha;
    f32 scale;
    f32 scaleMax;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105D20_w03(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w03());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
        HuPrcSleep(0x14);
        HuAudFXPlay(0x159);

        if (GwPlayer[loc->current_player_index].itemTurn != 0) {
            MBDlgWinInsertCreate(0x16, 0x4805, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
        }

        if (GwPlayer[loc->current_player_index].star >= 99) {
            MBDlgWinExec(0x16, 0x4804);
        } else {
            if (GwPlayer[loc->current_player_index].coin >= 20) {
            purchaseMenu:
                MBDlgWinInsertCreate(0x16, 0x4800, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
                choice = func_80109F44_w03(2, 0);
                MBDlgWinClose();
                MBDlgWinKill();

                switch (choice) {
                    case 0:
                        MBCoinChangeCreate(loc->current_player_index, -20);
                        MBCoinTakeCreate(loc->current_player_index, -20);
                        HuPrcSleep(30);
                        MBDlgWinExec(0x16, 0x4802);
                        if (D_800A12D0_main != 0) {
                            func_8004A950_main();
                            func_800039A4_main(D_800C9930_main, 60);
                            D_800C9930_main = -1;
                        } else {
                            HuAudSeqFadeOut(0x5A);
                        }
                        func_80106C2C_w03(D_8011EAC0_w03);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        goto end;
                    case 1:
                        if (D_800A12D0_main != 0) {
                            func_800039A4_main(D_800C9930_main, 60);
                            func_80003310_main(D_800CE198_main);
                            func_8004A670_main(0);
                            func_8004A72C_main(0x5A);
                            D_800C9930_main = -1;
                        }
                        MBDlgWinExec(0x16, 0x4803);
                        func_800DB884_shared_board(loc->current_player_index);
                        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                        HuPrcChildWait();
                        goto end;
                    case 2:
                        func_80106CA0_w03();
                        goto purchaseMenu;
                    default:
                        goto end;
                }
            } else {
                MBDlgWinExec(0x16, 0x4801);
            }
        }

        if (D_800A12D0_main != 0) {
            func_800039A4_main(D_800C9930_main, 60);
            func_80003310_main(D_800CE198_main);
            func_8004A670_main(0);
            func_8004A72C_main(0x5A);
            D_800C9930_main = -1;
        }

        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    }
end:
    if (spaceIdx == 2) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, D_8011C150_w03[GwSystem.boardData.halfWordBytes[0]]);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
        HuPrcSleep(0x14);
        HuAudFXPlay(0x19C);
        model = D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]];
        for (alpha = 0xFF; alpha > 0; alpha -= 10) {
            func_8001F9E4_main(model->omObj1->model[0], alpha);
            func_8001F9E4_main(model->omObj2->model[0], alpha);
            HuPrcVSleep();
        }
        MBModelDispOff(model);
        GWBoardFlagSet(0x12);
        func_800D7770_shared_board(GwSystem.boardData.halfWordBytes[1]);
        space = MBMasuGet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]]);
        scaleMax = space->rot.x;
        for (scale = scaleMax; scale > 0.0f; scale -= scaleMax / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, 0.0f, 0.0f, 0.0f);
        MBMasuTypeSet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]], 1);
        func_800EBDAC_shared_board();
        for (; scale < scaleMax; scale += scaleMax / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, scaleMax, scaleMax, scaleMax);
        GwSystem.boardData.halfWordBytes[0] = -1;
        MBDlgResultWinExec(0x800);
        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    }
    func_80109E98_w03();
}

void func_8010A930_w03(void) {
    Object *model;
    Object *effectModel;
    SpaceData *spaceA;
    SpaceData *spaceB;
    GW_SYSTEM *sys;
    Vec *vec;
    s16 mgId;
    s32 choice;
    s32 flag;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    char sp20[0x10];
    char sp30[0x10];
    Vec sp40;

    flag = 0;
    mgId = MBMasuCurGet();
    sys = &GwSystem;
    spaceA = NULL;
    spaceB = NULL;
    if (func_800DCD9C_shared_board(sys->current_player_index) <= 0) {
        MBPlayerVibrate(-1, 3);
    }
    MBPlayerMotionSet(-1, -1, 2);

    switch (mgId) {
        case 0x1C:
            func_800ED20C_shared_board(-1, 8, 0x7B);
            spaceA = MBMasuGet(0x7B);
            spaceB = MBMasuGet(0x1C);
            break;
        case 0x5F:
            func_800ED20C_shared_board(-1, 8, 0x78);
            spaceA = MBMasuGet(0x78);
            spaceB = MBMasuGet(0x5F);
            break;
    }

    HuPrcSleep(8);
    if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
        func_800DBEC0_shared_board(sys->current_player_index);
    }
    HuAudFXPlay(0x114);

    model = MBModelCreate(0x32, NULL);
    MBModelTempAllocFree(model);
    vec = &sp40;
    HuVecSubtract(vec, &spaceB->coords, &spaceA->coords);
    MBVecNormalize(vec);
    HuVecCopy3F(&model->rot, vec);
    model->scale.y = 0.0f;
    HuVecCopy3F(&model->coords, &spaceA->coords);
    MBMotionSet(model, -1, 1);
    func_800D9A40_shared_board(model);

    effectModel = MBModelCreate(0x35, D_8011CF68_w03);
    MBModelTempAllocFree(effectModel);
    HuVecCopy3F(&effectModel->rot, vec);
    HuVecCopy3F(&effectModel->coords, &spaceA->coords);
    effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 0.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    if (50.0f < angle) {
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        do {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
            angle -= scaleStep;
        } while (50.0f < angle);
    }

    model->scale.z = model->scale.x = model->scale.y = 1.0f;
    func_800D9A40_shared_board(effectModel);

    if (MBItemFind(-1, 0xF) != -1) {
    dialogLoop:
        MBDlgWinInsertCreate(-1, 0x3A1D, 0, 0, 0, 0, 0);
        choice = func_80109F44_w03((s32)D_8011CF50_w03, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106CA0_w03();
                goto dialogLoop;
        }
    }

    MBMotionSet(model, -1, 0);
    func_8001C92C_main(model->omObj1->model[0], 1.2f);
    while (MBMotionCheck(model) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x259);
    MBMotionSet(effectModel, 0, 0);
    while (MBMotionCheck(effectModel) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(effectModel, -1, 2);

    if (flag != 0) {
        sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
        if (GwSystem.bank_coins != 0) {
            MBDlgWinInsertCreate(2, 0x3A1E, (s32)sp20, 0, 0, 0, 0);
        } else {
            MBDlgWinInsertCreate(2, 0x3A1F, 0, 0, 0, 0, 0);
        }
        func_800EC9DC_shared_board();
        MBDlgWinClose();
        MBDlgWinKill();

        if (GwSystem.bank_coins != 0) {
            mbItemBtnF = 0;
            func_80113080_w03();
            mbItemBtnF = 1;
        } else {
            MBDlgWinInsertCreate(2, 0x3A21, 0, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            GwPlayer[sys->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
            MBItemRemoveEmpty(sys->current_player_index);
            MBStatusItemIconSprReinit(sys->current_player_index);
        }

        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            func_800DB884_shared_board(sys->current_player_index);
        }
    } else {
        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            if ((GwPlayer[sys->current_player_index].coin != 0) && (GwPlayer[sys->current_player_index].coin < 5)) {
                sprintf(sp20, D_8011E98C_w03, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011E98C_w03, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80108174_w03();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80108174_w03();
                MBCoinChangeCreate(sys->current_player_index, -5);
                MBCoinTakeCreate(sys->current_player_index, -5);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            }
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            func_800DB884_shared_board(sys->current_player_index);
            HuPrcSleep(10);
        } else {
            if (GwSystem.bank_coins != 0) {
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80108174_w03();
                MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
                MBPlayerMotionSet(-1, 5, 0);
                func_8004ACE0_main(0x274, sys->current_player_index);
                HuPrcSleep(30);
                MBPlayerMotionSet(-1, -1, 2);
                func_800EC6A8_shared_board();
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBDlgWinKill();
            } else {
                MBDlgWinExec(2, 0x1204);
            }
        }
    }

    HuAudFXPlay(0x115);
    MBMotionSet(model, -1, 4);
    func_8001C92C_main(model->omObj1->model[0], 1.2f);
    func_8001C6A8_main(
        model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
    while (func_800D9E80_shared_board(model) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 50.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    angle = 90.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 0.0f;
    for (; scaleLimit < angle; angle -= scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    model->scale.y = 0;
    model->scale.x = 0;
    model->scale.z = 0;
    MBModelKill(model);
    MBModelKill(effectModel);
    func_80109E90_w03();
}

s32 func_8010B46C_w03(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EB9C_w03[i] != 0) {
            if (D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010B4F4_w03(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010B55C_w03(void) {
    s32 grp = (s32)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scaleX;

    MBPlayerGet(GwSystem.current_player_index);
    MBPlayerVibrate(-1, 2);
    HuAudFXPlay(0x15A);

    for (angle = 0.0f; angle < 180.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 1.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.5f);
        HuPrcVSleep();
    }

    while (angle < 360.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
        angle += 20.0f;
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010B734_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    SpaceData *spaceA;
    SpaceData *spaceB;
    Object *model;
    Object *playerObj;
    Unk3 *helpWin;
    void *data;
    Process *prc;
    u8 enabled[9];
    u8 itemFlags[6][4];
    Vec sp48;
    s32 dlgWin;
    s16 shopIdx;
    s32 flag2;
    s32 id;
    s32 slot;
    s32 row;
    s32 row2;
    s32 sel;
    s32 choice;
    s32 count;
    s32 item;
    s8 *itemPtr;
    s8(*shopTable)[5][7];
    s8(*shopItems)[7];
    s32 timer;
    s32 randVal;
    s32 i;
    s32 j;
    s32 grp;
    s32 grp2;
    s16 spriteId;
    s32 spriteId2;
    s16 sprY;
    s16 masuId;
    s16 camMasu;
    GW_PLAYER *player;
    Object *effectModel;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    f32 scale;
    player = MBPlayerGet(-1);
    spaceA = NULL;
    spaceB = NULL;
    model = NULL;
    effectModel = NULL;
    MBPlayerMotionSet(-1, -1, 2);

    masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    switch (masuId) {
        case 0x6E:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x6E);
            D_8011D0D0_w03 = 0;
            break;
        case 0x71:
            camMasu = 0x77;
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x71);
            D_8011D0D0_w03 = 1;
            break;
        default:
            camMasu = -1;
            break;
    }

    if (camMasu != -1) {
        func_800ED20C_shared_board(-1, 8, camMasu);
        HuPrcSleep(8);
    }
    func_800DBEC0_shared_board(system->current_player_index);

    switch (GwSystem.forceShopHost) {
        case 0:
            shopIdx = !MBRandCheck100(0x42);
            break;
        case 1:
            shopIdx = 0;
            break;
        default:
            shopIdx = 1;
            break;
    }

    dlgWin = 3;
    if (shopIdx != 0) {
        dlgWin = 5;
    }

    if (camMasu != -1) {
        flag2 = (shopIdx << 1) >> 1;
        id = (-shopIdx & 0x31) | 0x30;
        HuAudFXPlay(0x114);
        model = MBModelCreate(id, NULL);
        MBModelTempAllocFree(model);
        HuVecSubtract(&sp48, &spaceB->coords, &spaceA->coords);
        MBVecNormalize(&sp48);
        HuVecCopy3F(&model->rot, &sp48);
        model->scale.y = 0.0f;
        MBMotionSet(model, -1, 1);
        func_800D9A40_shared_board(model);
        HuVecCopy3F(&model->coords, &spaceA->coords);

        if (flag2 != 0) {
            effectModel = MBModelCreate(0x39, D_8011D0C8_w03);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011D0C0_w03);
        }
        MBModelTempAllocFree(effectModel);
        HuVecCopy3F(&effectModel->rot, &sp48);
        HuVecCopy3F(&effectModel->coords, &spaceA->coords);
        effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 0.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        for (; 50.0f < angle; angle -= scaleStep) {
            scaleK = 0.2f;
            scaleBase = 0.8f;
            scaleStep = 11.25f;
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = model->scale.x = model->scale.z = 1.0f;
        func_800D9A40_shared_board(effectModel);
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, 0, 0);

        if (shopIdx != 0) {
            HuAudFXPlay(0x2A0);
        } else {
            if (GwPlayer[system->current_player_index].coin < 5 || MBItemFindEmpty(system->current_player_index) == -1) {
                HuAudFXPlay(0x29A);
            } else if (system->current_turn != system->total_turns) {
                HuAudFXPlay(0x298);
            } else {
                HuAudFXPlay(0x29A);
            }
        }

        while (MBMotionCheck(effectModel) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, -1, 2);
    }

    if (system->current_turn == system->total_turns) {
        MBDlgWinExec(dlgWin, D_8011D0B0_w03[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011D0A8_w03[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011D0A0_w03[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011D098_w03[shopIdx]);
    choice = func_80107148_w03();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011CF80_w03[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011CF98_w03[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011CF98_w03[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011CF98_w03[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011CF98_w03[shopIdx][row][j]] >
                    GwPlayer[system->current_player_index].coin) {
                    enabled[j] = 0;
                    itemFlags[i][0] = 1;
                }
                itemFlags[i][1] = 0;
                count++;
            }
            for (; j < 9; j++) {
                enabled[j] = 1;
            }

            MBDlgWinInsertCreate(dlgWin, D_8011D070_w03[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011EB94_w03 = slot;
            D_8011EB98_w03 = row;
            D_8011EB9C_w03 = enabled;
            sel = func_80106EB4_w03(enabled);
            MBDlgWinClose();
            MBDlgWinKill();

            if (sel == count) {
                mbItemBtnF = 0;
                MBItemSelNoClear();
                MBItemDescExec(system->current_player_index);
                mbItemBtnF = 1;
                goto restart;
            }
            if (sel == count + 1 || sel == -1) {
                goto itemSelect;
            }

            playerObj = player->player_obj;
            i = shopIdx;
            shopTable = D_8011CF98_w03;
            shopItems = shopTable[i];
            itemPtr = (s8 *)(row * 7);
            itemPtr += (s32)shopItems;
            itemPtr += sel;
            MBCoinChangeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            MBCoinTakeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            HuPrcSleep(30);

            if (*itemPtr == 0x13) {
                item = i + 0x13;
            } else {
                GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] =
                    D_8011CF98_w03[shopIdx][row][sel];
                item = D_8011CF98_w03[shopIdx][row][sel];
            }

            grp = HuSprGrpCreate(1, 5);
            i = 0;
            data = DataRead(D_8010197C_shared_board[item]);
            spriteId = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(grp, 0, spriteId, 0);
            HuSprPriSet(grp, 0, 0xA);
            func_800550F4_main(grp, 0, 0);
            HuSprAttrSet(grp, 0, 0x180C);
            func_80054904_main(grp, 0, 0xA0, 0x5A);
            func_80055458_main(grp, 0, 0);
            MBVecForwardSet(&sp48);
            func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);
            HuAudFXPlay(0x19);
            for (; i < 10; i++) {
                func_80055458_main(grp, 0, i * 25);
                HuPrcVSleep();
            }
            func_80055458_main(grp, 0, 0x100);

            if (D_8011CF98_w03[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011CFE0_w03[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011CFF8_w03[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011D05C_w03[shopIdx][i];

                    if (camMasu != -1) {
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 1);
                    } else {
                        playerObj->flags |= 0x10;
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 0);
                    }
                    timer = 30;

                    if ((*(u16 *)((u8 *)D_800C9520_main + (GwPlayer[system->current_player_index].pad << 1)) & 0x8000) == 0) {
                        row = (s32)D_800C9520_main;
                        while (1) {
                            if (MBPlayerComCheck(-1) != 0) {
                                timer--;
                                if (timer == -1) {
                                    break;
                                }
                            }
                            HuPrcVSleep();
                            if (((u16 *)row)[GwPlayer[system->current_player_index].pad] & 0x8000) {
                                break;
                            }
                        }
                    }
                    MBHelpWinKill(helpWin);

                    MBPlayerMotionSet(system->current_player_index, 2, 0);
                    func_800EE688_shared_board(playerObj, 2.0f, -0.3f);
                    HuPrcSleep(5);
                    prc = omAddPrcObj(func_8010B55C_w03, 0x4002, 0, 0);
                    prc->user_data = (void *)grp;
                    func_800EE6C0_shared_board(playerObj);
                    MBPlayerMotionSet(-1, -1, 2);

                    grp2 = HuSprGrpCreate(1, 5);
                    i = 0;
                    data = DataRead(D_8010197C_shared_board[item]);
                    spriteId2 = func_80055810_main(data);
                    DataClose(data);
                    func_80055024_main(grp2, 0, spriteId2, 0);
                    HuSprPriSet(grp2, 0, 0xB);
                    func_800550F4_main(grp2, 0, 0);
                    HuSprAttrSet(grp2, 0, 0x1000);
                    func_80054904_main(grp2, 0, 0xA0, 0x5A);
                    func_80055458_main(grp2, 0, 0);
                    MBVecForwardSet(&sp48);
                    func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);

                    sprY = 0x5A;
                    scale = 0.0f;
                    do {
                        func_80054904_main(grp2, 0, 0xA0, sprY);
                        func_80055458_main(grp2, 0, i * 25);
                        HuSprScaleSet(grp2, 0, scale, scale);
                        i++;
                        HuPrcVSleep();
                        sprY -= 3;
                        scale += 0.1f;
                    } while (i < 10);
                    HuSprScaleSet(grp2, 0, 1.0f, 1.0f);
                    func_80055458_main(grp2, 0, 0x100);
                    HuPrcSleep(10);
                    GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] = item;
                    HuSprGrpKill(grp2);
                    HuSprKill(spriteId2);
                }
                if (camMasu == -1) {
                    playerObj->flags &= ~0x10;
                }
            }

            HuPrcSleep(5);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, system->current_player_index);
            HuPrcSleep(20);
            HuPrcVSleep();
            func_800F2388_shared_board(-1, -1, 0, 5, 2);
            HuPrcSleep(10);
            HuSprGrpKill(grp);
            HuSprKill(spriteId);
            break;
        case 1:
            MBDlgWinExec(dlgWin, D_8011D0B8_w03[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106D28_w03();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106CA0_w03();
            }
            goto itemSelect;
    }

end:
    if (camMasu != -1) {
        HuAudFXPlay(0x115);
        MBMotionSet(model, -1, 4);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        func_8001C6A8_main(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 50.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        angle = 90.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 0.0f;
        for (; scaleLimit < angle; angle -= scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = 0;
        model->scale.x = 0;
        model->scale.z = 0;
        MBModelKill(model);
        MBModelKill(effectModel);
    }
    func_800DB884_shared_board(system->current_player_index);
    HuPrcSleep(10);
}

void func_8010C9EC_w03(Object *obj) {
    s32 i;

    MBModelDispOn(obj);
    for (i = 0; i < 0x100; i += 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
}

void func_8010CA8C_w03(Object *obj) {
    s32 i;

    for (i = 0xFF; i >= 0; i -= 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    MBModelDispOff(obj);
}

s32 func_8010CB2C_w03(s32 playerIndex) {
    s32 hasRareItem = 0;
    s16 grp;
    void *data;
    s16 spriteId;
    s32 i;
    s32 duration;
    Process *process;

    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    func_800550F4_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, D_8011D0E4_w03[playerIndex].x,
                        D_8011D0E4_w03[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011D104_w03[playerIndex].x) +
                                D_8011D0E4_w03[playerIndex].x,
                            (i * D_8011D104_w03[playerIndex].y) +
                                D_8011D0E4_w03[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_801128B0_w03, 0x4002, 0, 0);
        process->user_data = (void *)playerIndex;
    }

    if (!hasRareItem) {
        GwPlayer[playerIndex].star--;
    }
    MBPlayerVibrate(playerIndex, 5);
    HuAudFXPlay(0x257);

    duration = hasRareItem ? 0x78 : 0x1E;
    for (i = 0; i < duration; i++) {
        func_80054904_main(grp, 0,
                            (D_8011D104_w03[playerIndex].x * 16.0f) +
                                D_8011D0E4_w03[playerIndex].x,
                            (D_8011D104_w03[playerIndex].y * 16.0f) +
                                D_8011D0E4_w03[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011D104_w03[playerIndex].x) +
                                D_8011D0E4_w03[playerIndex].x,
                            (i * D_8011D104_w03[playerIndex].y) +
                                D_8011D0E4_w03[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010CF74_w03(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010CF98_w03(s32 playerIndex) {
    s32 hasRareItem;
    s16 grp;
    void *data;
    s16 spriteId;
    s16 playerGrp;
    s16 playerSpriteId;
    s32 i;
    s32 state;
    s32 playerSpriteVisible;
    s16 delay;
    s32 angle;
    s32 attempts;
    void *dialog;
    Process *process;

    hasRareItem = 0;
    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    func_800550F4_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, D_8011D0E4_w03[playerIndex].x,
                        D_8011D0E4_w03[playerIndex].y);
    func_80055458_main(grp, 0, 0);

    {
        playerGrp = HuSprGrpCreate(1, 5);
        playerSpriteVisible = 0;
        data = DataRead(D_80101040_shared_board[GwPlayer[playerIndex].chr]);
        playerSpriteId = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(playerGrp, 0, playerSpriteId, 0);
        HuSprPriSet(playerGrp, 0, 0xA);
        func_800550F4_main(playerGrp, 0, 1);
        if (playerIndex & 1) {
            HuSprAttrSet(playerGrp, 0, 0x1001);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x1000);
        }
        if (MBItemFind(playerIndex, 0xC) != -1) {
            HuSprAttrSet(playerGrp, 0, 0x8000);
        }
        func_80054904_main(playerGrp, 0,
                            D_8011D0E4_w03[playerIndex].x -
                                (D_8011D104_w03[playerIndex].x * 16.0f) - 8.0f,
                            D_8011D0E4_w03[playerIndex].y +
                                (D_8011D104_w03[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
        func_80055458_main(grp, 0, 0xFF);
        func_80055458_main(playerGrp, 0, 0xFF);

        MBWinInsertOpen(MBItemFind(playerIndex, 0xC) == -1 ? 0x620E : 0x620F,
                        (char *)mbCharNameMesTbl[GwPlayer[playerIndex].chr], 0, 0, 0, 0);
        MBPlayerVibrate(playerIndex, 2);
        func_800EC3C0_shared_board(playerIndex);
        if (MBItemFind(playerIndex, 0xC) != -1) {
            omAddPrcObj(func_8010CF74_w03, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_801128B0_w03, 0x4002, 0, 0);
            process->user_data = (void *)playerIndex;
        }
        HuAudFXPlay(0x133);
        dialog = MBPlayerVibrateObjCreate(playerIndex, 3, 5);
        delay = MBRand(10.0f) + 1;
        i = 0;
        angle = 0;

        for (; i < 0x78; i++, delay--) {
            if (delay == 0) {
                HuAudFXPlay(0x257);
                delay = MBRand(15.0f) + 0x1E;
            }
            state -= !(state < 2);
            if (state == 0) {
                func_80054904_main(
                    grp, 0,
                    (D_8011D104_w03[playerIndex].x * 16.0f) +
                        D_8011D0E4_w03[playerIndex].x,
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011D104_w03[playerIndex].x * 16.0f) +
                        D_8011D0E4_w03[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D0E4_w03[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
                angle++;
            }

            if (GwPlayer[playerIndex].stat & 1) {
                if (state == 0) {
                    goto tryInput;
                } else {
                    if (GwPlayer[playerIndex].cpu_difficulty == 0) {
                        if ((6 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 1) {
                        if ((7 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 2) {
                        if ((8 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if ((9 - MBRand(2.0f)) >= state) {
                        goto tryInput;
                    }
                }
            } else if (D_800C9520_main[GwPlayer[playerIndex].pad] & 0x8000) {
            tryInput:
                if (!hasRareItem) {
                    attempts++;
                    state = 10;
                    if (!playerSpriteVisible) {
                        func_80055140_main(playerGrp, 0, 1, 0);
                        func_800550F4_main(playerGrp, 0, 1);
                        playerSpriteVisible = 1;
                        func_80054904_main(
                            playerGrp, 0, D_8011D0E4_w03[playerIndex].x - 8.0f,
                            (D_8011D104_w03[playerIndex].y * 16.0f) +
                                D_8011D0E4_w03[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D0E4_w03[playerIndex].x -
                        (D_8011D104_w03[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CF74_w03, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x - 8.0f,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            if (hasRareItem) {
                i -= 2;
            }
            HuPrcVSleep();
        }
        func_80055140_main(playerGrp, 0, 0, 0);
        func_800550F4_main(playerGrp, 0, 1);
        for (i = 0x10; i >= 0; i -= 2) {
            func_80055458_main(grp, 0, i << 4);
            HuPrcVSleep();
        }
    }

    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    HuSprGrpKill(playerGrp);
    HuSprKill(playerSpriteId);

    playerSpriteVisible = -2;
    if (!hasRareItem) {
        for (i = 0; i < ARRAY_COUNTU(D_8011D124_w03); i++) {
            if ((GwSystem.current_turn >= D_8011D124_w03[i][0]) &&
                (GwSystem.current_turn <= D_8011D124_w03[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011D124_w03[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011D138_w03); i++) {
            if ((attempts >= D_8011D138_w03[i][0]) &&
                (attempts <= D_8011D138_w03[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011D138_w03[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

const char D_8011E98C_w03[] = "%d";

void func_8010DDC4_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBA0_w03);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_8010DF18_w03(Object *arg) {
    Process *temp = omAddPrcObj(func_8010DDC4_w03, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_8010DF54_w03(void) {
    char inserts[4][16];
    u8 choices[8];
    Vec direction;
    s32 rankedPlayers[3];
    Object *model = NULL;
    SpaceData *space;
    Vec *spaceCoords;
    GW_PLAYER *player;
    GW_SYSTEM *sys;
    Process *process;
    void *coinEffect;
    s32 resultAmount;
    s32 selectedByCpu;
    s16 target;
    s32 menuResult;
    s32 playerChoice;
    s32 rank;
    s32 count;
    s32 i;
    s32 j;
    s32 amountDifference;
    s16 spaceId;
    f32 angle;
    f32 scale;
    f32 rate;
    f32 booVelocity;
    Object *boo;
    s32 modelIsLinked;
    s32 estimatedAmount;
    s16 camMasu;
    s16 menu;
    s32 cameraSet;

    resultAmount = 0;
    estimatedAmount = resultAmount;
    MBMasuCurGet();
    sys = &GwSystem;
    player = MBPlayerGet(-1);
    cameraSet = func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    menu = 0;
    spaceId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    if (spaceId != 0x8E) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011EB54_w03);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x6C;
        space = MBMasuGet(0x6C);
        boo = D_8011EB58_w03[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011D178_w03[sys->current_board_index] != 0) {
            func_8001ED54_main(model->omObj1->model[0]);
        }
        func_8001C448_main(model->omObj1->model[0]);
        MBModelTempAllocFree(model);
        spaceCoords = &space->coords;
        HuVecSubtract(&direction, &MBMasuGet(spaceId)->coords, spaceCoords);
        MBVecNormalize(&direction);
        HuVecCopy3F(&model->rot, &direction);
        model->scale.y = 0.0f;
        HuVecCopy3F(&model->coords, spaceCoords);
        MBMotionSet(model, -1, 1);
        MBModelDispOn(model);
        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011D178_w03[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C9EC_w03(boo);
    space = MBMasuGet(spaceId);
    spaceId = camMasu;
    if (spaceId != -1) {
        func_800D9F5C_shared_board(boo, &space->coords, 5);
        func_800ED20C_shared_board(-1, 5, spaceId);
        HuPrcSleep(5);
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
    }

    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(7, 0x6201);
        goto finishMenu;
    }

restartMenu:
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index &&
            (GwPlayer[i].coin != 0 || GwPlayer[i].star != 0)) {
            break;
        }
    }
    if (i >= 4) {
        MBDlgWinExec(7, 0x6202);
        goto finishMenu;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].coin != 0) {
            break;
        }
    }
    if (i == 4) {
        inserts[0][0] = 1;
        choices[0] = 0;
    } else {
        inserts[0][0] = 8;
        choices[0] = 1;
    }
    inserts[0][1] = 0;
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i == 4) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].coin < 50) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].star < 99) {
        goto starChoiceAvailable;
    }

starChoiceUnavailable: {
    inserts[1][0] = 1;
    choices[1] = 0;
    goto starChoiceDone;
}

starChoiceAvailable: {
    inserts[1][0] = 8;
    choices[1] = 1;
}

starChoiceDone:
    inserts[1][1] = 0;
    choices[3] = 1;
    choices[2] = 1;
    MBDlgWinInsertCreate(7, 0x6200, (s32)inserts[0], (s32)inserts[1], 0, 0, 0);
    menuResult = func_801078F4_w03(choices);
    menu = menuResult;
    MBDlgWinClose();
    MBDlgWinKill();
    switch ((s16)menuResult) {
        case 0:
        case 1:
            goto selectPlayer;
        case 2:
            goto menuResultTwo;
        case 3:
            goto menuResultThree;
        default:
            goto finishMenu;
    }

selectPlayer:
    i = 0;
    j = 0;
    while (i < 4) {
        if (i == sys->current_player_index) {
            choices[j] = 0;
            inserts[j][0] = 1;
        } else if (menu == 0) {
            if (GwPlayer[i].coin == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        } else {
            if (GwPlayer[i].star == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        }
        func_800E2260_shared_board(i, &inserts[j][1]);
        i++;
        j++;
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(7, 0x5C02, (s32)inserts[0], (s32)inserts[1], (s32)inserts[2], (s32)inserts[3], 0);
    playerChoice = func_80107914_w03(choices);
    target = playerChoice;
    MBDlgWinClose();
    selectedByCpu = 0;
    MBDlgWinKill();
    switch ((s16)playerChoice) {
        case -1:
            goto restartMenu;
        case 4:
            goto selectCpuPlayer;
        case 5:
            if (modelIsLinked == -1) {
                func_80106D28_w03();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106CA0_w03();
            }
            goto selectPlayer;
        default:
            goto playerSelected;
    }

selectCpuPlayer: {
    i = 0;
    count = 0;
    while (i < 4) {
        for (j = 0; j < 4; j++) {
            if (i == BoardPlayerRankCalc(j) && sys->current_player_index != j) {
                rankedPlayers[count++] = j;
            }
        }
        i++;
    }
    rank = MBRand(100.0f);
    for (i = 0; i < 3; i++) {
        if (rank < D_8011D16C_w03[i]) {
            break;
        }
    }
    if (menu != 0) {
        while (GwPlayer[rankedPlayers[i]].star == 0 || rankedPlayers[i] == sys->current_player_index) {
            i--;
        }
    } else {
        while (i >= 0 &&
               (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
            i--;
        }
        i = 2;
        while (i >= 0 &&
               (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
            i--;
        }
    }
    target = rankedPlayers[i];
    selectedByCpu = 1;
}

playerSelected:
    if (menu == 0) {
        MBCoinChangeCreate(sys->current_player_index, -5);
        MBCoinTakeCreate(sys->current_player_index, -5);
    } else {
        MBCoinChangeCreate(sys->current_player_index, -50);
        MBCoinTakeCreate(sys->current_player_index, -50);
    }
    HuPrcSleep(30);
    if (menu == 1) {
        if (selectedByCpu != 0) {
            MBDlgWinExec(7, 0x6206);
        }
    } else {
        for (i = 0; (u32)i < 6; i++) {
            if (GwSystem.current_turn >= D_8011D124_w03[i][0] &&
                GwSystem.current_turn <= D_8011D124_w03[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011D124_w03[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010CA8C_w03(boo);
    if (menu == 0) {
        resultAmount = func_8010CF98_w03(target);
        func_8010C9EC_w03(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011E98C_w03, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011E98C_w03, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011D164_w03[i]) {
                        break;
                    }
                }
                MBDlgWinInsertCreate(7, i + 0x6210, (s32)inserts[0], 0, 0, 0, 0);
            }
            MBDlgWinClose();
            MBDlgWinKill();
        }
        if (resultAmount != -2) {
            mbItemBtnF = 0;
            rate = (f32)resultAmount / 90.0f;
            angle = 0.0f;
            D_8011EBA0_w03 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011EBA0_w03);
            MBModelDispOff(D_8011EBA0_w03);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010DF18_w03(boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011EBA0_w03);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010CB2C_w03(target);
        func_8010C9EC_w03(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011C160_w03 = 1;
            func_80106C2C_w03(boo);
            D_8011C160_w03 = 0;
            goto outcomeDone;
        } else {
            resultAmount = -2;
        }
    }

outcomeDone:
    if (modelIsLinked == -1) {
        HuPrcSleep(20);
        MBPlayerMotionSet(-1, -1, 2);
    }
    if (resultAmount == -2) {
        HuPrcSleep(30);
        MBDlgWinExec(7, 0x6215);
    }
    goto finishMenu;

menuResultTwo:
    func_8010CA8C_w03(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106D28_w03();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106CA0_w03();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010CA8C_w03(boo);
    }
    MBVecForwardSet(&boo->rot);
    if (modelIsLinked == -1) {
        MBModelKill(boo);
    }
    if (camMasu != -1) {
        HuAudFXPlay(0x126);
        MBMotionSet(model, -1, 4);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        func_8001C6A8_main(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 0.0f;
        model->scale.x = 0.0f;
        model->scale.z = 0.0f;
        MBModelKill(model);
    }
    if (cameraSet != 0) {
        func_800DB884_shared_board(sys->current_player_index);
    }
    if (modelIsLinked != -1) {
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    }
    func_80109F3C_w03();
}

void func_8010F128_w03(void) {
    func_801087E4_w03(0);
}

void func_8010F144_w03(void) {
    func_801087E4_w03(1);
}

omObjData *func_8010F160_w03(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010F2BC_w03);
    data = obj->data = HuMemAllocTag(0x20, 0x7918);
    data->unk0C = 255.0f;
    data->unk10 = arg1;
    data->unk14 = arg2;
    HuVecCopy3F(&data->unk00, arg4);
    if (arg5 != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = arg0->x;
    model->coords.y = arg0->y;
    model->coords.z = arg0->z;
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->unk1C = arg3;
    return obj;
}

void func_8010F2BC_w03(omObjData *arg0) {
    ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->unk00);
    scale = model->scale.z + data->unk10;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->unk0C - data->unk14;
    data->unk0C = alpha;
    if (alpha < 0.0f) {
        data->unk0C = 0.0f;
        if (data->unk1C != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, 8);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->unk0C);
}

void func_8010F3D4_w03(void) {
    Vec pos;
    s8 link;
    s8 index;
    GW_PLAYER *player;
    Object *lamp;
    UnkVibrateProcess *vib;
    s32 angle;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    func_8010FF2C_w03();
    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
    for (lamp->coords.y = 100.0f; lamp->coords.y > 30.0f;) {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x127);
    func_8004A7C4_main(0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 4, 5);

    angle = 0xB4;
    i = 0;
    while (angle < 0x438) {
        Vec particleDir[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011C140_w03[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
    player->clink = link;
    player->cidx = index;
    player->nlink = link;
    player->nidx = index + 1;
    player->blink = link;
    player->bidx = index - 1;
    player->rev &= ~FLAG_REV;
    func_800FC9E0_shared_board();
    HuAudFXPlay(0x128);
    func_8004A0E0_main();

    while (1) {
        Vec particleDir2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010F79C_w03(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011C140_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010F808_w03(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010FF2C_w03();
    func_800DCA64_shared_board(currentPlayerIndex);
    MBPlayerVibrate(CUR_PLAYER, 3);
    GWBoardFlagSet(0x11);
    func_800DC128_shared_board(currentPlayerIndex);
    playerIndex = func_800EF0D8_shared_board(1);
    func_8004A0E0_main();
    func_800FC8A4_shared_board();
    HuPrcSleep(5);
    HuPrcSleep(25);
    MBPlayerMotionSet(currentPlayerIndex, 2, 0);
    func_800EE688_shared_board(GwPlayer[currentPlayerIndex].player_obj, 2.0f, -0.3f);
    HuPrcSleep(5);
    func_800DCBCC_shared_board(currentPlayerIndex);
    func_800F2388_shared_board(currentPlayerIndex, CUR_PLAYER, 0, 10, 2);
    HuPrcSleep(20);
    MBItemWarpBlockSwapInit();
    MBItemWarpBlockSwapPlayerSet(playerIndex);
    MBItemWarpBlockSwapCreate();
    GWBoardFlagClear(0x11);
    fxId = func_800DC128_shared_board(currentPlayerIndex);
    HuAudFXStop(fxId);
    func_800DC06C_shared_board(currentPlayerIndex);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    func_800DCD2C_shared_board(currentPlayerIndex, CUR_PLAYER);
    spaceIndex = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    MBMasuCurSet(spaceIndex);
    MBMasuEventCall(spaceIndex, 1);
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(CUR_PLAYER);
    }
    func_800DAA40_shared_board(currentPlayerIndex);
}

void func_8010F9C8_w03(void) {
    Process *process = HuPrcCurrentGet();
    WarpBlockSwapWork *work = process->user_data;
    f32 deltaX;
    f32 deltaY;
    f32 spriteX;
    f32 spriteY;
    s32 i;

    deltaX = (f32)(work->endX - work->startX) / (f32)work->duration;
    deltaY = (f32)(work->endY - work->startY) / (f32)work->duration;
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &spriteX, &spriteY);

    for (i = 1; i <= work->duration; i++) {
        if (work->spriteGroup != -1) {
            func_80054904_main(work->spriteGroup, 0,
                                work->startX + (deltaX * i), work->startY + (deltaY * i));
        }

        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                           spriteX + (deltaX * i), spriteY + (deltaY * i));
        HuPrcVSleep();
    }

    if (work->spriteGroup != -1) {
        func_80054904_main(work->spriteGroup, 0, work->endX, work->endY);
    }

    MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                       work->endX + spriteX - work->startX,
                       work->endY + spriteY - work->startY);
    omDelPrcObj(NULL);
}

Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                                  s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(func_8010F9C8_w03, 0x4002, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = work;
    work->startX = startX;
    work->startY = startY;
    work->endX = endX;
    work->endY = endY;
    if (duration == -1) {
        duration = 25;
    }
    work->duration = duration;
    work->spriteGroup = spriteGroup;
    return process;
}

void func_8010FCFC_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, func_8010FC2C_w03(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011D24C_w03[system->current_player_index].x,
                                D_8011D24C_w03[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        MBStatusItemOfsApply(system->current_player_index,
                             MBItemSelNoGet(), 0, 2.0f);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    MBPlayerMotionSet(-1, 5, 0);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(50);
    MBPlayerMotionSet(-1, -1, 2);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010FF2C_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010FC2C_w03(
        mbItemCursorGrpId, position[0], position[1],
        D_8011D26C_w03[system->current_player_index].x,
        D_8011D26C_w03[system->current_player_index].y, -1);
    HuPrcSleep(20);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuPrcSleep(2);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_801100FC_w03(void) {
    f32 position[2];
    s32 targetX;
    s32 targetY;
    Process *process;
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    func_800F6848_shared_board(GwSystem.current_player_index,
                                      MBItemSelNoGet(), &position[0], &position[1]);
    MBStatusItemPosGet(-1, MBItemSelNoGet(), &targetX, &targetY);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8011026C_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;
    s32 j;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    if ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 0xB) ||
        (GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 8)) {
        HuAudFXPlay(0x141);
    }

    for (i = 0; i <= 1080; i += 30) {
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
    }

    for (j = 1; j < 10; j++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (j * 25));
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
        i += 30;
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_801105B8_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8011077C_w03(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
    f32 position[2];
    f32 stepX;
    f32 stepY;
    f32 scale;
    s32 i;

    if (mode == 2) {
        HuAudFXPlay(0x145);
    }

    func_800F6848_shared_board(arg0, arg1, &position[0], &position[1]);
    stepX = (target[0] - position[0]) / duration;
    stepY = (target[1] - position[1]) / duration;

    for (i = 2; duration != 0; duration--, i++) {
        position[0] += stepX;
        position[1] += stepY;
        MBStatusItemPosSet(arg0, arg1, position[0], position[1]);

        if ((mode == 1) && (i < 11)) {
            MBStatusItemTPLvlSet(arg0, arg1, i * 25);
            scale = i * 0.07f;
            MBStatusItemScaleSet(arg0, arg1, scale + 0.3f,
                                 (f32)((f64)scale + 0.3));
        }
        HuPrcVSleep();
    }

    MBStatusItemPosSet(arg0, arg1, target[0], target[1]);

    if (mode == 0) {
        for (i = 1; i < 10; i++) {
            MBStatusItemTPLvlSet(arg0, arg1, 255 - (i * 25));
            MBStatusItemScaleSet(arg0, arg1, 1.0f - (i * 0.1f), 1.0f - (i * 0.1f));
            HuPrcVSleep();
        }
        MBStatusItemTPLvlSet(arg0, arg1, 0);
    }
}

void func_80110A14_w03(void) {
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitCreate();
    MBModelDispOff(D_801011FC_shared_board);
    D_801011FC_shared_board->omObj1->scale.x = 0.0f;
    D_801011FC_shared_board->omObj1->scale.y = 0.0f;
    D_801011FC_shared_board->omObj1->scale.z = 0.0f;
    MBPlayerVibrate(-1, 3);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(model->omObj1->model[0], 0x1800);
    func_8001C448_main(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOff(player->player_obj);
    MBModelDispOn(D_801011FC_shared_board);

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    HuPrcSleep(20);
    func_8004ACE0_main(0x274, GwSystem.current_player_index);
    MBKSuitMotionSet(5, 2);
    HuPrcSleep(40);
    MBKSuitMotionSet(-1, 2);
    MBDlgResultWinExec(0x3A14);
}

void func_80110CA0_w03(void) {
    Vec direction;
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitMotionSet(-1, 2);
    MBVecForwardSet(&direction);
    func_800ED128_shared_board(&player->player_obj->rot, &direction, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(model->omObj1->model[0], 0x1800);
    func_8001C448_main(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOn(player->player_obj);
    MBKSuitKill();

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
}

void func_80110EE0_w03(void) {
    s32 index;
    s32 group;
    s32 alpha;
    void *dialog;
    f32 x;
    f32 y;
    f32 angle;

    index = (s32)HuPrcCurrentGet()->user_data;
    dialog = MBPlayerVibrateObjCreate(-1, 1, 5);
    group = HuSprGrpCreate(1, 0);
    func_80055024_main(group, 0, (s16)D_8011EBA4_w03, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    func_80054904_main(group, 0, x, y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011D338_w03[index];
    for (; alpha >= 0; alpha -= 0x14) {
        x += cosdf(angle) * 5.0f;
        y -= sindf(angle) * 5.0f;
        func_80054904_main(group, 0, x, y);
        func_80055458_main(group, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(group, 0, 0);
    MBPlayerVibrateObjKill(dialog);
    HuSprGrpKill(group);
    omDelPrcObj(0);
}


void func_801110F0_w03(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011EBA4_w03 = func_80055810_main(data);
    DataClose(data);
    func_801105B8_w03();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_80109F44_w03((s32)D_8011D2CC_w03, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
                omPrcSetStatBit(process, 0x80);
                func_80106D28_w03();
                one = 1;
                D_800CB99C_main = one;
                func_80049FB8_main();
                omDelPrcObj(process);
                func_800FC8A4_shared_board();
                continue;
            }
            GwSystem.forceShopHost = choice + 1;
            break;
        }

        process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
        omPrcSetStatBit(process, 0x80);
        func_80106D28_w03();
        one = 1;
        D_800CB99C_main = one;
        func_80049FB8_main();
        omDelPrcObj(process);
        func_800FC8A4_shared_board();
        continue;
    }

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);
    }

    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011EBA4_w03);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (choice != 0) {
        HuAudFXPlay(0x2A0);
    } else if (GwPlayer[loc->current_player_index].coin < 5 ||
               loc->current_turn == loc->total_turns) {
        HuAudFXPlay(0x29A);
    } else {
        HuAudFXPlay(0x298);
    }
    func_8010B734_w03();
    GwSystem.forceShopHost = 0;
}

void func_801113B0_w03(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011EBA4_w03 = func_80055810_main(data);
    DataClose(data);
    func_801105B8_w03();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);
    }

    HuAudFXPlay(0x29F);
retry:
    MBDlgWinInsertCreate(4, 0x3A0A,
                         mbCharNameMesTbl[GwPlayer[0].chr],
                         mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr],
                         mbCharNameMesTbl[GwPlayer[3].chr], 0);
    if (GwPlayer[loc->current_player_index].coin != 0) {
        choice = func_80109F44_w03(1, 0);
    } else {
        choice = func_80109F44_w03(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
            omPrcSetStatBit(process, 0x80);
            func_80106D28_w03();
            one = 1;
            D_800CB99C_main = one;
            func_80049FB8_main();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B,
                                 mbCharNameMesTbl[GwPlayer[choice].chr],
                                 0, 0, 0, 0);
            break;
    }
    MBDlgWinClose();
    MBDlgWinKill();

    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011EBA4_w03);

    if (func_800DEB2C_shared_board(loc->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FCA4C_shared_board();
    func_800FF794_shared_board(0x50, 0, 3, 1);
    func_800FC8A4_shared_board();
    func_800FF7F0_shared_board(2);
    func_8004A0E0_main();
    HuPrcSleep(-1);
}

void func_80111750_w03(void) {
    s32 i;
    s32 j;
    s32 wipeStarted;
    GW_SYSTEM *system = &GwSystem;
    Object *lamp;
    Object *starModel;
    Object *targetStar;
    Process *process;
    Process *dialogProcess;
    Vec direction;
    Vec pos;
    Vec destination;
    s32 angle;
    s32 alpha;
    f32 speed;
    f32 rotation;
    void *dialog;

    {
        GW_PLAYER *player;

        player = MBPlayerGet(-1);
        lamp = MBModelCreate(0x3C, NULL);
        MBMotionSet(lamp, -1, 1);
        Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
        lamp->velocity.x = 30.0f;
        lamp->flags |= 1;
        HuVecCopyXYZ(&lamp->scale, 0.0f, 0.0f, 0.0f);
        MBModelDispOff(lamp);
        func_8010FF2C_w03();

        {
            s32 itemSlot = MBItemFind(-1, 9);

            GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
        }
        MBItemRemoveEmpty(system->current_player_index);

        starModel = MBModelCreate(0x3D, NULL);
        func_8001FA68_main(starModel->omObj1->model[0]);
        func_8001F9E4_main(starModel->omObj1->model[0], 0xFF);
        Hu3DModelScaleSet(starModel->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&starModel->coords, &player->player_obj->coords);
        starModel->coords.y = 100.0f;
        while (starModel->coords.y > 30.0f) {
            starModel->coords.y -= 1.0f;
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x127);
    func_800039A4_main(D_800CDBC8_main, 0xB4);
    dialog = MBPlayerVibrateObjCreate(-1, 3, 5);

    for (angle = 180, i = 0; angle < 1080; angle += 20, i++) {
        Vec velocities[8] = {
            { 1.0f, 1.0f, 1.0f },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1,
                                     &velocities[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        Vec velocities2[8] = {
            { 1.0f, 1.0f, 1.0f },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1,
                                     &velocities2[(i / 2) & 7], 1);
        }

        if (alpha > 0) {
            func_8001F9E4_main(starModel->omObj1->model[0], alpha & 0xFF);
            alpha -= 12;
        } else {
            MBModelDispOff(starModel);
            func_800D9A40_shared_board(lamp);
            speed += 0.1f;
            lamp->scale.z = speed;
            lamp->scale.y = speed;
            lamp->scale.x = speed;
            if (speed > 1.0f) {
                HuAudSeqPlay(0x3D);
                break;
            }
        }
        i++;
        HuPrcVSleep();
    }

    lamp->scale.x = lamp->scale.y = lamp->scale.z = 1.0f;
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBPlayerVibrateObjKill(dialog);
    HuPrcSleep(30);
    MBDlgWinExec(0x3C, 0x3A2F);
    omDelPrcObj(dialogProcess);

    i = 1;
    lamp->coords.y -= lamp->velocity.x;
    HuVecSubtract(&direction, &gCameraList->pos, &lamp->coords);
    MBVecNormalize(&direction);
    lamp->coords.y += lamp->velocity.x;

    while (lamp->velocity.x < 1800.0f) {
        lamp->coords.x += direction.x * 40.2f;
        lamp->velocity.x += direction.y * 40.0f;
        lamp->coords.z += direction.z * 40.2f;
        if ((lamp->velocity.x > 300.0f) && (i != 0)) {
            i = 0;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x32);
            HuAudFXPlay(0x128);
        }
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    {
        SpaceData *space;
        SpaceData *nextSpace;

        space = MBMasuGet(D_8011C140_w03[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011C150_w03[system->star_spawn_indices[system->current_star_spawn]]);
        HuVecCopy3F(&destination, &space->coords);
        MBCameraPos3DSet(&destination);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&destination);
        lamp->flags &= ~1;
        HuVecCopy3F(&lamp->coords, &space->coords);
        HuVecSubtract(&direction, &nextSpace->coords, &space->coords);
        MBVecNormalize(&direction);
        lamp->coords.x -= direction.x * 20.0f;
        lamp->coords.z -= direction.z * 20.0f;
    }

    HuAudFXPlay(0x129);
    WipeCreateIn(0xB, 0x32);
    lamp->velocity.x = 100.0f;
    while (lamp->velocity.x > 30.0f) {
        HuPrcVSleep();
        lamp->velocity.x -= 3.0f;
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_800ED128_shared_board(&lamp->rot,
                                                     &direction,
                                                     &lamp->rot, 0x10));
    i = 0;
    HuPrcChildWait();
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBDlgWinExec(0x3C, 0x3A30);
    HuAudFXPlay(0x12C);
    MBMotionSet(lamp, -1, 0);
    HuPrcSleep(20);

    wipeStarted = 1;
    for (j = 0; j < 8; j++) {
        if (D_8011EAE8_w03[j] != NULL) {
            omDelPrcObj(D_8011EAE8_w03[j]);
            D_8011EAE8_w03[j] = NULL;
        }
    }

    targetStar = D_8011EAC8_w03[system->star_spawn_indices[system->current_star_spawn]];
    HuAudSeqFadeOut(0x5A);
    rotation = 0.0f;
    while (targetStar->velocity.x < 400.0f) {
        targetStar->velocity.x += 3.0f;
        targetStar->coords.x += direction.x * 3.0f;
        targetStar->coords.z += direction.z * 3.0f;
        targetStar->rot.x = -sindf(rotation);
        targetStar->rot.z = cosdf(rotation);
        rotation += 45.0f;
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
        if ((targetStar->velocity.x > 50.0f) && (wipeStarted != 0)) {
            if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
                GWBoardFlagSet(0x17);
            } else {
                GWBoardFlagClear(0x17);
            }
            wipeStarted = 0;
            WipeColorSet(0, 0, 0);
            omDelPrcObj(dialogProcess);
            func_800EDA58_shared_board();
            func_800FC8A4_shared_board();
            func_800FF7F0_shared_board(2);
            func_800FCA14_shared_board();
            func_8004A0E0_main();
        }
        HuPrcVSleep();
    }
    HuPrcSleep(-1);
}

void func_8011214C_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 player;
    Process *process;
    s32 group;
    void *sprite;
    s32 spriteCount;
    s32 i;
    f32 position[2];
    s32 result;

    player = GwSystem.current_player_index;
    group = HuSprGrpCreate(1, 0);
    sprite = DataRead(D_8010197C_shared_board[1]);
    spriteCount = func_80055810_main(sprite);
    DataClose(sprite);
    func_80055024_main(group, 0, spriteCount, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x9000);
    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - i * 25);
        HuPrcVSleep();
    }
    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    GwPlayer[player].itemNo[MBItemSelNoGet()] = -1;
    MBStatusItemTPLvlSet(player, MBItemSelNoGet(), 0);
    func_800F6848_shared_board(player, MBItemSelNoGet(), &position[0], &position[1]);
    func_80054904_main(group, 0, position[0], position[1]);
    HuSprAttrReset(group, 0, 0x8000);
    MBItemRemoveEmpty(player);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
retry:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    result = func_80109F44_w03((s32)&D_8011D34C_w03, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (result) {
        case 0:
            MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
            break;
        case 1:
            MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
            HuSprAttrSet(group, 0, 0x8000);
            GwPlayer[player].itemNo[MBItemFindEmpty(player)] = 1;
            MBItemRemoveEmpty(player);
            GwSystem.cur_player_used_item &= ~1;
            break;
        default:
            HuSprAttrSet(group, 0, 0x8000);
            func_80106D28_w03();
            D_800CB99C_main = 1;
            func_80049FB8_main();
            HuSprAttrReset(group, 0, 0x8000);
            goto retry;
    }
    MBDlgWinClose();
    MBDlgWinKill();
    if (result == 0) {
        HuPrcSleep(10);
        for (i = 1; i < 0x40; i++) {
            func_80055458_main(group, 0, (u16)(255.0f - (f32)i * 3.984f));
            HuPrcVSleep();
        }
        func_80055458_main(group, 0, 0);
    }
    HuSprGrpKill(group);
    HuSprKill(spriteCount);
}

void func_80112694_w03(void) {
    s32 playerIndex;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    f32 scale;
    s32 alpha;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    group = HuSprGrpCreate(1, 0);
    setupGroup = group;
    func_80055024_main(setupGroup, 0, D_8011EBAC_w03, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    MBStatusItemPosGet(D_8011EBA8_w03, 0, &xPos, &yPos);

    xPos = (s32)((D_8011D104_w03[D_8011EBA8_w03].x * 16.0f) +
                 D_8011D0E4_w03[D_8011EBA8_w03].x);
    yPos = (s32)((D_8011D104_w03[D_8011EBA8_w03].y * 16.0f) +
                 D_8011D0E4_w03[D_8011EBA8_w03].y);
    func_80054904_main(
        setupGroup, 0, (f32)xPos + D_8011D358_w03[playerIndex].x,
        (f32)yPos + D_8011D358_w03[playerIndex].y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0xFF);
    func_80055458_main(group, 0, 0xFF);

    scale = 0.0f;
    alpha = 0xFF;
    while (alpha >= 0) {
        HuSprScaleSet(group, 0, scale, scale);
        func_80055458_main(group, 0, alpha);
        HuPrcVSleep();
        alpha -= 10;
        scale += 0.1f;
    }

    func_80055458_main(group, 0, 0);
    HuSprGrpKill(group);
    omDelPrcObj(NULL);
}

void func_801128B0_w03(void) {
    s32 playerIndex;
    void *data;
    s32 itemSpriteId;
    s32 auraSpriteId;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    s32 i;
    s32 j;
    Process *childProcess;
    s32 fxId;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    data = DataRead(0x21002C);
    itemSpriteId = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1301BA);
    auraSpriteId = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1301B9);
    D_8011EBAC_w03 = func_80055810_main(data);
    DataClose(data);

    group = HuSprGrpCreate(2, 2);
    setupGroup = group;
    func_800550F4_main(setupGroup, 0, 1);
    func_80055024_main(setupGroup, 0, itemSpriteId, 0xC);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    func_800554C4_main(setupGroup, 0, -1);
    func_80055024_main(setupGroup, 1, auraSpriteId, 0);
    HuSprPriSet(setupGroup, 1, 9);
    HuSprAttrSet(setupGroup, 1, 0x9000);
    func_80055420_main(setupGroup, 1, 0xFF, 0xFF, 0xFF);
    func_80055458_main(setupGroup, 1, 0xFF);
    HuSprScaleSet(setupGroup, 1, 2.0f, 2.0f);
    func_800554C4_main(setupGroup, 1, 0);

    yPos = 0xC8;
    if (playerIndex & 1) {
        HuSprAttrSet(setupGroup, 0, 1);
        HuSprAttrSet(setupGroup, 1, 1);
        func_80054904_main(setupGroup, 1, 0x14, -5);
    } else {
        yPos = 0x78;
        func_80054904_main(group, 1, -0x14, -5);
    }

    xPos = (playerIndex < 2) ? -0x20 : 0x110;
    HuPrcSleep(0x14);
    GwPlayer[playerIndex].itemNo[MBItemFind(playerIndex, 0xC)] = -1;
    MBItemRemoveEmpty(playerIndex);
    MBStatusItemIconSprReinit(playerIndex);

    do {
        if (playerIndex < 2) {
            xPos += 5;
            if (xPos >= 0x33) {
                break;
            }
        } else {
            xPos -= 5;
            if (xPos < 0xD2) {
                break;
            }
        }
        func_80054904_main(group, 0, yPos, xPos);
        HuPrcVSleep();
    } while (1);

    HuPrcSleep(0xA);
    HuSprAttrReset(group, 1, 0x8000);
    fxId = HuAudFXPlay(0x14C);
    D_8011EBA8_w03 = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(func_80112694_w03, 0x4002, 0, 0);
            childProcess->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), childProcess);
    HuPrcChildWait();
    HuAudFXStop(fxId);
    func_80055458_main(group, 1, 0);

    for (i = 0xFF; i >= 0; i -= 0x1E) {
        func_80055458_main(group, 0, i);
        HuPrcVSleep();
    }

    func_80055458_main(group, 0, 0);
    HuSprGrpKill(group);
    HuSprKill(D_8011EBAC_w03);
    HuSprKill(auraSpriteId);
    HuSprKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void func_80112CA4_w03(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_80112D60_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBB0_w03);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_80112EB4_w03(Object *arg) {
    Process *temp = omAddPrcObj(func_80112D60_w03, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_80112EF0_w03(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        D_8011EBB4_w03->rot.x = -sindf(angle);
        D_8011EBB4_w03->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            D_8011EBB4_w03->scale.z = scale;
            D_8011EBB4_w03->scale.y = scale;
            D_8011EBB4_w03->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    D_8011EBB4_w03->scale.x = D_8011EBB4_w03->scale.y = D_8011EBB4_w03->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(D_8011EBB4_w03);
    omDelPrcObj(0);
}

void func_80113080_w03(void) {
    s32 flag = 0;
    GW_SYSTEM *system = &GwSystem;
    void *data;
    UnkVibrateProcess *process;
    s32 positionX;
    s32 positionY;
    s32 bankCoins;
    s32 coinCount;
    s32 spriteId;
    f32 coinStep;
    f32 coinProgress;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    data = DataRead(D_80101040_shared_board[GwPlayer[system->current_player_index].chr]);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(mbItemCursorGrpId, 0, spriteId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 10);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    MBStatusItemPosGet(-1, 0, &positionX, &positionY);
    func_80054904_main(mbItemCursorGrpId, 0, positionX, positionY);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(-1, 0xF));
    func_8010FF2C_w03();

    D_8011EBB4_w03 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_8011EBB4_w03->coords, &MBPlayerGet(-1)->player_obj->coords);
    D_8011EBB4_w03->velocity.x = 100.0f;
    while (30.0f < D_8011EBB4_w03->velocity.x) {
        D_8011EBB4_w03->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_80112EF0_w03, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    D_8011EBB0_w03 = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(D_8011EBB0_w03);
    MBModelDispOff(D_8011EBB0_w03);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                func_80112EB4_w03(D_8011EBB4_w03);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                func_80108174_w03();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(D_8011EBB0_w03);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 func_8011343C_w03(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(p3Unk4Bytes *)buttons = *(p3Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = D_8011EBB8_w03 + 1;
                } else {
                    delay = D_8011EBBC_w03 + 1;
                }
                inputs[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, buttons[GwPlayer[i].pad]);
                inputs[GwPlayer[i].pad] = -1;
            }
        } else {
            inputs[GwPlayer[i].pad] = 0;
        }
    }

    if (delay != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; delay != 0; j++) {
            if (--delay == 0) {
                inputs[GwPlayer[GwSystem.current_player_index].pad] = 0x8000;
            }
            if (j == 0) {
                func_8005F698_main(inputs[0], inputs[1], inputs[2], inputs[3],
                                    func_800EDC40_shared_board());
            } else {
                func_8005F698_main(inputs[0], inputs[1], inputs[2], inputs[3], 5);
            }
        }
    } else {
        func_8005F744_main(inputs[0], inputs[1], inputs[2], inputs[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void func_801136D4_w03(void) {
    Process *prc = HuPrcCurrentGet();
    s32 playerIdx = (s32)prc->user_data;
    s32 j;
    s32 val;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    MBPlayerVibrate(((s16 *)&prc->user_data)[1], 4);

    for (val = 0x80; val > 0; val -= 0xA) {
        for (j = 0; j < 3; j++) {
            if (GwPlayer[playerIdx].itemNo[j] != -1) {
                MBStatusItemTPLvlSet(playerIdx, j, val);
            }
        }
        HuPrcVSleep();
    }

    for (j = 0; j < 3; j++) {
        if (GwPlayer[playerIdx].itemNo[j] != -1) {
            MBStatusItemTPLvlSet(playerIdx, j, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801137E0_w03(void) {
    Process *process = HuPrcCurrentGet();
    s32 playerIndex = (s32)process->user_data;
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    s32 alpha;
    s32 itemIndex;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;

    for (i = 0, itemIndex = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerIndex, itemIndex, &xPos, &yPos);
            MBStatusItemPosSet(system->current_player_index, i, xPos, yPos);
            itemIndex += (i != MBItemSelNoGet());
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
                if (i != MBItemSelNoGet()) {
                    MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
                }
            }
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            if (i != MBItemSelNoGet()) {
                MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_801139BC_w03(void) {
    char playerNames[4][16];
    u8 choices[16];
    Vec2f position;
    Vec2f target;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    u16 spriteId;
    Object *box;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer;
    s32 noAnimation = 0;
    s32 itemCount;
    s32 itemSlot;
    s32 sleepTime;
    s32 i;
    s32 j;
    s32 item;
    f32 angle;
    f32 angleStep;
    f32 spinStep;
    f32 scale;
    f32 scaleY;
    f32 itemAngle;
    f32 scaleZ;
    f32 finalScale;

    func_8010FF2C_w03();
    box = MBModelCreate(0x20, NULL);
    func_8001C2FC_main(box->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(box->omObj1->model[0]);
    func_8001C954_main(box->omObj1->model[0]);
    func_8001C514_main(box->omObj1->model[0]);
    Hu3DModelScaleSet(box->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&box->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(box->omObj1->model[0], 2, 1);
    box->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (box->velocity.x > 30.0f) {
        box->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    for (itemSlot = 0; itemSlot < 4; itemSlot++) {
        if (GwSystem.current_player_index == itemSlot) {
            playerNames[itemSlot][0] = 1;
            choices[itemSlot] = 0;
        } else {
            playerNames[itemSlot][0] = 8;
            choices[itemSlot] = 1;
        }
        func_800E2260_shared_board(itemSlot, &playerNames[itemSlot][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_8011343C_w03(choices, 1);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    itemSlot = MBItemSelNoGet();
    if (GwPlayer[GwSystem.current_player_index].itemNo[itemSlot] == 0x10 &&
        MBItemFindEmpty(GwSystem.current_player_index) == 1 && MBItemFindEmpty(targetPlayer) == 0) {
        noAnimation = 1;
    }

    if (!noAnimation) {
        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 1, 0);
        HuPrcSleep(20);
        position.x = 160.0f;
        position.y = 84.0f;
        for (itemSlot = 0; itemSlot < 3; itemSlot++) {
            for (j = 0; j < 3; j++) {
                spriteId = 0x4790;
                if (j == itemSlot) {
                    spriteId = 0x4786;
                }
                MBStatusItemPriSet(system->current_player_index, j, spriteId);
            }
            if (GwPlayer[system->current_player_index].itemNo[itemSlot] != -1) {
                if (itemSlot != MBItemSelNoGet()) {
                    func_8011077C_w03(system->current_player_index, itemSlot, 10, &position.x, 0);
                    HuPrcSleep(2);
                }
            }
        }
        func_8001C814_main(box->omObj1->model[0], 4, 4);
        while (HmfModelData[box->omObj1->model[0]].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x150);
        HuPrcSleep(20);
        process = omAddPrcObj(func_801136D4_w03, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        HuAudFXPlay(0x151);

        angle = 0.0f;
        spinStep = 5.0f;
        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            spinStep += 2.0f;
            if (spinStep > 45.0f) {
                spinStep = 45.0f;
                if (i++ >= 31) {
                    break;
                }
            }
            HuPrcVSleep();
        }

        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
                if (++i >= 2) {
                    break;
                }
            }
            spinStep -= 2.0f;
            if (spinStep < 5.0f) {
                spinStep = 5.0f;
            }
            HuPrcVSleep();
        }
        box->rot.x = 0.0f;
        box->rot.z = 1.0f;
        HuAudFXPlay(0x152);
        for (itemSlot = 0; itemSlot < 1441; itemSlot += 40) {
            scale = itemSlot;
            angleStep = sindf(scale) / 1.5f + 1.0f;
            scaleY = sindf(scale) / 1.5f + 1.0f;
            scaleZ = sindf(scale) / 1.5f + 1.0f;
            HuVecCopyXYZ(&box->scale, angleStep, scaleY, scaleZ);
            HuPrcVSleep();
        }

        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 4, 0);
        HuPrcSleep(20);
        process = omAddPrcObj(func_801137E0_w03, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011077C_w03(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011077C_w03(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011077C_w03(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_8011077C_w03(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011077C_w03(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_8011077C_w03(targetPlayer, 2, 7, &target.x, 2);
                break;
        }
        HuPrcSleep(2);
    }

    itemSlot = MBItemSelNoGet();
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    for (itemSlot = 0; itemSlot < 3; itemSlot++) {
        item = GwPlayer[targetPlayer].itemNo[itemSlot];
        GwPlayer[targetPlayer].itemNo[itemSlot] = GwPlayer[system->current_player_index].itemNo[itemSlot];
        GwPlayer[system->current_player_index].itemNo[itemSlot] = item;
    }
    if (!noAnimation) {
        MBStatusItemSprKill(-1);
        MBStatusItemSprKill(targetPlayer);
        sleepTime = 10;
    } else {
        sleepTime = 20;
    }
    HuPrcSleep(sleepTime);
    HuAudFXPlay(0x15B);
    finalScale = 0.1f;
    for (i = 0; i < 20; i++) {
        finalScale += 0.044999998f;
        func_8001D558_main(box->omObj1->model[0], finalScale, finalScale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(box);

    if (noAnimation) {
        func_8004ACE0_main(0x286, system->current_player_index);
        MBPlayerMotionSet(-1, 3, 0);
        HuPrcSleep(70);
    } else {
        func_8004ACE0_main(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, 5, 0);
        HuPrcSleep(50);
    }
    func_800F2388_shared_board(-1, -1, 0, 10, 2);
    MBDlgWinInsertCreate(-1, noAnimation ? 0x3A2E : 0x3A2D,
                         mbCharNameMesTbl[GwPlayer[system->current_player_index].chr],
                         mbCharNameMesTbl[GwPlayer[targetPlayer].chr], 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
}

void func_80114668_w03(void) {
    p3ModelAnimWork *data = HuPrcCurrentGet()->user_data;
    Object *obj1 = data->obj1;
    Object *obj2 = data->obj2;

    MBMotionSet(obj1, -1, data->state);
    HuVecCopy3F(&obj1->coords, &obj2->coords);
    obj1->coords.y += obj2->velocity.x - 10.0f;
    func_800D9A40_shared_board(obj1);
    while (MBMotionCheck(obj1) == 0 && data->flag == 0) {
        HuPrcVSleep();
    }
    MBModelKill(obj1);
    omDelPrcObj(0);
}

void func_80114728_w03(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = D_8011EBC0_w03;
    Object *model;
    Process *process;
    p3ModelAnimWork *work;
    s32 effect;
    f32 angle;
    f32 angleStep;
    f32 fallSpeed;
    f32 scale;
    s32 i;

    model = MBModelCreate(0x45, NULL);
    MBModelDispOff(model);
    effect = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 10.0f);
    func_8001C8A8_main(effect, 1);
    HuAudFXPlay(0x24C);

    angle = 0.0f;
    angleStep = 2.0f;
    while (angleStep < 80.0f) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        angleStep += 1.0f;
        if (angleStep > 80.0f) {
            angleStep = 80.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14A);
    while (gameGuyModel->velocity.x < 110.0f) {
        gameGuyModel->velocity.x += 7.0f;
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    *processFlag = 0;
    while (*processFlag == 0) {
        if (D_8011D388_w03 != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(D_8011D388_w03)->player_obj->coords);
            func_8000CFA4_main(effect, gameGuyModel->coords.x,
                               gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14B);
    fallSpeed = 3.0f;
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= fallSpeed;
        if (fallSpeed > 1.0f) {
            fallSpeed -= 0.2f;
        }
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (angleStep > 15.0f) {
            angleStep -= 3.0f;
        } else {
            angleStep -= 0.5f;
        }
        if (angleStep < 1.0f) {
            break;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    func_8000D044_main(effect);
    process = omAddPrcObj(func_80114668_w03, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x20);
    process->user_data = work;
    work->obj1 = model;
    work->obj2 = gameGuyModel;
    work->state = 0;
    work->flag = 0;
    HuPrcSleep(3);
    *processFlag = 0;
    HuAudFXPlay(0x24D);

    i = 0;
    scale = 0.1f;
    for (; i < 20; i++) {
        scale += 0.044999998f;
        func_8001D558_main(gameGuyModel->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(gameGuyModel);
    omDelPrcObj(NULL);
}

void func_80114C58_w03(void) {
    Object *coinModel;
    Object *gameGuyModel;
    Object *playerObj;
    Process *process;
    GW_SYSTEM *system;
    s32 choice;
    s32 itemSlot;
    s32 rewardIndex;
    s32 randomValue;
    s32 rewardAmount;
    s32 i;
    struct {
        s32 processFlag;
        s32 pad;
        char rewardText[0x10];
    } locals;

    system = &GwSystem;
    func_8010FF2C_w03();
    itemSlot = MBItemFind(-1, 0x11);
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    coinModel = MBModelCreate(0x3E, 0);
    Hu3DModelScaleSet(coinModel->omObj1->model[0], 0, 0, 0);
    MBModelTempAllocFree(coinModel);
    coinModel->velocity.x = 30.0f;
    MBModelDispOff(coinModel);

    gameGuyModel = MBModelCreate(0x43, 0);
    D_8011EBC0_w03 = gameGuyModel;
    func_8001C2FC_main(gameGuyModel->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(gameGuyModel->omObj1->model[0]);
    func_8001C954_main(gameGuyModel->omObj1->model[0]);
    func_8001C514_main(gameGuyModel->omObj1->model[0]);
    HuVecCopy3F(&gameGuyModel->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(gameGuyModel->omObj1->model[0], 2, 1);
    gameGuyModel->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

selectPlayer:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (choice >= 0) {
        if (choice < 4) {
            goto validChoice;
        }
        if (choice == 4) {
            choice = func_800EF0D8_shared_board(0);
            goto validChoice;
        }
    }
    func_80106D28_w03();
    D_800CB99C_main = 1;
    func_80049FB8_main();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(func_80114728_w03, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        D_8011D388_w03 = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        D_8011D388_w03 = choice;
    }

    locals.processFlag = 1;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    playerObj = MBPlayerGet(choice)->player_obj;
    process = func_800EDB98_shared_board(coinModel, 5.0f, 2.0f);
    HuVecCopy3F(&coinModel->coords, &playerObj->coords);
    func_800D9A40_shared_board(coinModel);
    coinModel->scale.x = coinModel->scale.y = coinModel->scale.z = 0.0f;
    while (coinModel->scale.x < 1.0f) {
        coinModel->scale.x = coinModel->scale.y = coinModel->scale.z += 0.2f;
        HuPrcVSleep();
    }

    MBPlayerVibrate(choice, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[choice].coin != 0) {
        func_8010A1C8_w03(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        func_8010A1C8_w03(10, 0x2F02, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x >= 10.0f) {
            coinModel->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        while (coinModel->velocity.x < 100.0f) {
            coinModel->velocity.x += 4.0f;
            playerObj->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        func_8010A1C8_w03(10, 0x2F01, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x <= 100.0f) {
            coinModel->velocity.x += 4.0f;
            HuPrcVSleep();
        }
        MBModelKill(coinModel);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBPlayerComCheck((s16)choice) != 0 && system->show_com_minigames != 0) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(coinModel);
        func_800EE688_shared_board(playerObj, 0, 0);
        playerObj->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        randomValue = MBRand(100.0f) + 1;
        for (rewardIndex = 0; rewardIndex < 7; rewardIndex++) {
            if (randomValue <= D_8011D394_w03[rewardIndex].threshold) {
                break;
            }
        }
        if (D_8011D394_w03[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * D_8011D394_w03[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, D_8011E98C_w03, rewardAmount);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)locals.rewardText, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(choice, rewardAmount);
            MBCoinTakeCreate(choice, rewardAmount);
            HuPrcSleep(20);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(10);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    MBPlayerGet(choice)->group = 0;
    randomValue = MBRand(100.0f);
    for (rewardIndex = 0; (u32)rewardIndex < 3; rewardIndex++) {
        if (randomValue < D_8011D390_w03[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = D_8011D38C_w03[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FC998_shared_board();
    func_8004A0E0_main();
    func_800FF7F0_shared_board(2);
    HuPrcSleep(-1);
}

void func_80115564_w03(s32 arg0, s32 arg1, f32 *arg2) {
    f32 curX;
    f32 curY;
    f32 stepX;
    f32 stepY;

    MBStatusSprPosGet((s16)arg0, 0, &curX, &curY);
    stepX = (arg2[0] - curX) / arg1;
    stepY = (arg2[1] - curY) / arg1;
    while (arg1 != 0) {
        curX += stepX;
        curY += stepY;
        func_80054904_main(arg0, 0, curX, curY);
        HuPrcVSleep();
        arg1--;
    }
    func_80054904_main(arg0, 0, arg2[0], arg2[1]);
}

void func_8011569C_w03(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0x7A, 0x39);
            break;
        default:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprAttrReset(D_8011EBC8_w03[idx], 0, 0x8000U);
    for (i = 0; i < 255; i += 255 / divisor) {
        func_80055458_main(D_8011EBC8_w03[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    func_80055458_main(D_8011EBC8_w03[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void func_8011580C_w03(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011D3B0_w03[i].r;
        sp18.g = D_8011D3B0_w03[i].g;
        sp18.b = D_8011D3B0_w03[i].b;

        sp28.r = (D_8011D3B0_w03[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011D3B0_w03[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011D3B0_w03[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            func_80055420_main(D_8011EBC8_w03[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        func_80055420_main(D_8011EBC8_w03[3], 0, D_8011D3B0_w03[i + 1].r, D_8011D3B0_w03[i + 1].g, D_8011D3B0_w03[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void func_801159D4_w03(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = D_8011EBD8_w03;
    func_800D9A40_shared_board(model);

    angle = 0.0f;
    for (scale = 1.0f; scale < 18.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 1) {
        wait_angle_step = 20.0f;
        while (*state != 1) {
            func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += wait_angle_step;
            HuPrcVSleep();
        }
    }

    for (; scale < 40.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 2) {
        scale = 20.0f;
        while (*state != 2) {
            func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += scale;
            HuPrcVSleep();
        }
    }

    MBModelKill(model);
    omDelPrcObj(0);
}

void func_80115C58_w03(void) {
    s32 sp18[4];
    f32 sp28[2];
    s32 sp30;
    s32 sp34;
    f32 sp38;
    f32 sp3C;
    s32 sp40;
    Process *temp_v0_4;
    f32 temp_f20;
    f32 var_f20;
    s32 temp_s0_3;
    s32 temp_s4;
    s32 temp_s7;
    void *temp_s1_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    void *temp_v0;
    Object *temp_v0_3;
    s32 i;
    s32 j;
    GW_SYSTEM *system = &GwSystem;
    s32 temp;

    temp_s4 = HuSprGrpCreate(1, 0);
    temp_v0 = DataRead(D_8010197C_shared_board[18]);
    temp_s7 = func_80055810_main(temp_v0);
    DataClose(temp_v0);
    func_80055024_main(temp_s4, 0, temp_s7, 0);
    HuSprPriSet(temp_s4, 0, 0x4776U);
    HuSprAttrSet(temp_s4, 0, 0x1000U);
    for (i = 0; i < 4; i++) {
        D_8011EBC8_w03[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8011EBC8_w03[i], 0, sp18[i], 0);
        HuSprPriSet(D_8011EBC8_w03[i], 0, 0x4780U);
        HuSprAttrSet(D_8011EBC8_w03[i], 0, 0x980CU);
        func_80055458_main(D_8011EBC8_w03[i], 0, 0U);
        func_80055420_main(D_8011EBC8_w03[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_8011EBD8_w03 = temp_v0_3;
    func_8001C258_main(temp_v0_3->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(temp_v0_3->omObj1->model[0], 0x1800);
    func_8001C448_main(temp_v0_3->omObj1->model[0]);
    Hu3DModelScaleSet(temp_v0_3->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&temp_v0_3->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    MBModelTempAllocFree(temp_v0_3);
    MBModelDispOff(temp_v0_3);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000U);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBStatusItemPosGet(system->current_player_index, MBItemSelNoGet(), &sp30, &sp34);
    func_80054904_main(temp_s4, 0, sp30, sp34);
    sp28[0] = 160.0f;
    sp28[1] = 76.0f;
    HuAudFXPlay(0x145);
    func_80115564_w03(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_80115564_w03(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_80115564_w03(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_80115564_w03(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    HuAudFXPlay(0x14E);
    MBStatusSprPosGet(temp_s4, 0, &sp38, &sp3C);
    for (var_f20 = 0.0f, var_s1 = 0; var_f20 < 90.0f; var_f20 += 3.6f) {
        func_80054904_main(temp_s4, 0, ((cosdf((2.0f * var_f20) + 270.0f) * 80.0f) + sp38), (((1.0f - cosdf(var_f20)) * 90.0f) + sp3C));
        if (!(var_f20 > 54.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = 1;
        }
        temp = var_v1 != 0;
        if (temp && var_s1 == 0) {
            var_s1 = 1;
            temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
            temp_v0_4->user_data = (void *)2;
            HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
        }
        HuPrcVSleep();
    }

    temp_s0_3 = (s16)(s32)((cosdf(450.0f) * 80.0f) + sp38);
    func_80054904_main(temp_s4, 0, temp_s0_3, (((1.0f - cosdf(90.0f)) * 90.0f) + sp3C));

    for (j = 255; j > 0; j -= 0x19, HuPrcVSleep()) {
        func_80055458_main(temp_s4, 0, j);
    }

    HuSprGrpKill(temp_s4);
    HuSprKill(temp_s7);
    HuPrcChildWait();

    for (i = 0; i < 3; i++) {
        HuSprAttrSet(D_8011EBC8_w03[i], 0, 0x8000);
    }

    HuSprAttrReset(D_8011EBC8_w03[3], 0, 0x8000U);
    func_80055458_main(D_8011EBC8_w03[3], 0, 0xFFU);
    func_80054904_main(D_8011EBC8_w03[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8011580C_w03, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_801159D4_w03, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWait();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_8011EBC8_w03[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
        if (i >= (2880 / 2 + 1)) {
            sp40 = 1;
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 0x32);
    MBPlayerVibrateObjKill(temp_s1_2);

    for (var_f20 = 0.0f; WipeStatGet() != 0; var_f20 += 0.1f) {
        HuSprScaleSet(D_8011EBC8_w03[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_8011EBC8_w03[i]);
        HuSprKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void func_8011655C_w03(p3SpaceTriple *masu, p3BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    p3BranchLink *link;
    s32 back;
    s32 sel;
    s32 count;
    s32 row;
    s32 col;
    s32 i;
    s16 *temp;
    DecisionTreeNonLeafNode **tree;

    link = links[0];
    tree = trees;
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    func_80106D84_w03();
    player = MBPlayerGet(GwSystem.current_player_index);
    back = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 2; col++) {
            if (masu[row][col] == back) {
                break;
            }
        }
        if (col == 2) {
            break;
        }
    }

    temp = masu[row];
    link += row * 2;
    win = func_800D76A0_shared_board(GwSystem.current_player_index, temp);
    func_800D742C_shared_board(win, GwSystem.current_player_index, 0);

    if (MBPlayerComCheck(-1)) {
        count = MBComTreeExec(tree[row]);
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }

    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80106E54_w03();

    if (sel) {
        link++;
    }

    MBMoveNextMasuSet(-1, link->link, link->idx);
    switch (link->rev) {
        case 0:
            player->rev &= ~1;
            break;
        case 1:
            player->rev |= 1;
            break;
    }
}

void func_80116754_w03(s32 arg0) {
    if (D_8011EBF0_w03[arg0] != NULL) {
        omDelObj(D_8011EBF0_w03[arg0]);
        D_8011EBF0_w03[arg0] = NULL;
    }
    if (D_8011EBE0_w03[arg0] != NULL) {
        MBModelKill(D_8011EBE0_w03[arg0]);
        D_8011EBE0_w03[arg0] = NULL;
    }
}

void func_801167CC_w03(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011EBF0_w03[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011EBF0_w03[i] = NULL;
        }
    }
}

void func_80116830_w03(omObjData *obj) {
    s32 playerIdx = obj->work[0];

    if (GwSystem.current_player_index == 4) {
        if (obj->work[2] == 0) {
            if (obj->work[1] != 0) {
                obj->work[1] -= 1;
                if (obj->work[1] != 0) {
                    return;
                }
                obj->work[2] = 1;
            } else {
                obj->work[1] = 40;
                return;
            }
        }
    }

    {
        GW_PLAYER *player = MBPlayerGet(playerIdx);
        Object *effectObj = D_8011EBE0_w03[playerIdx];

        HuVecCopy3F(&effectObj->coords, &player->player_obj->coords);
        effectObj->velocity.x = player->player_obj->velocity.x + 20.0f;
        HuVecCopy3F(&effectObj->rot, &player->player_obj->rot);
        effectObj->coords.x += sindf(obj->rot.x) * obj->trans.x;
        effectObj->coords.z += cosdf(obj->rot.x) * obj->trans.x;
        obj->rot.x += 5.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        if (obj->trans.x <= 5.0f) {
            obj->trans.x += 0.25f;
        }
        if (player->player_obj->flags & 8) {
            func_800D9A40_shared_board(effectObj);
        } else {
            MBModelDispOff(effectObj);
        }
    }
}


void func_801169DC_w03(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (D_8011EBE0_w03[arg0] == NULL) {
        switch (arg1) {
            case 0:
                modelId = 0x3F;
                break;
            case 1:
                modelId = 0x40;
                break;
            case 2:
                modelId = 0x41;
                break;
            default:
                modelId = 0x42;
                break;
        }

        obj = MBModelCreate(modelId, NULL);
        MBModelTempAllocFree(obj);
        D_8011EBE0_w03[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011EBE0_w03[arg0]);
    }
}


void func_80116ADC_w03(s32 arg) {
    D_8011EBF0_w03[arg] = omAddObj(0x3FFF, 0, 0, -1, func_80116830_w03);
    D_8011EBF0_w03[arg]->work[0] = arg;
    D_8011EBF0_w03[arg]->work[1] = 0;
    D_8011EBF0_w03[arg]->work[2] = 0;
    D_8011EBF0_w03[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011EBF0_w03[arg]->trans.x = 0;
}


void func_80116B78_w03(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_8011EBF0_w03[i] = NULL;
        D_8011EBE0_w03[i] = NULL;
        idx = -!(MBPlayerGet(i)->rev & 0x2);
        if (MBPlayerGet(i)->rev & 0x4) {
            idx = 1;
        }
        if (MBPlayerGet(i)->rev & 0x20) {
            idx = 2;
        }
        if (MBPlayerGet(i)->rev & 0x40) {
            idx = 3;
        }
        if (idx != -1) {
            func_801169DC_w03(i, idx);
            func_80116ADC_w03(i);
        }
    }
    func_800F8D54_shared_board(func_801167CC_w03);
}


void func_80116C78_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    f32 scale;

    if ((((*slowDiceFlags >> loc->current_player_index) & 1))) {
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        if ((player->rev & 0x20) || ((player->rev & 8) && !(player->rev & 2))) {
            MBDlgWinExec(-1, 0x4219);
        } else {
            MBDlgWinExec(-1, 0x3A07);
        }

        if (player->rev & 2) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}


void func_80116E84_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}


void func_80116FE4_w03(void) {
    void *data;
    s32 i;

    i = 0x3C;
    data = HuPrcCurrentGet()->user_data;

    while (i != 0) {
        HuPrcVSleep();
        i--;
    }

    MBPlayerVibrateObjKill(data);
    omDelPrcObj(NULL);
}


void func_80117034_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    UnkVibrateProcess *vib;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(2, D_8011EC04_w03);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    GwSystem.slow_dice_flags |= 1 << targetPlayer;
    player = MBPlayerGet(targetPlayer);

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_80116754_w03(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_801169DC_w03(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_80116ADC_w03(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_80116FE4_w03, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (player->rev & 0x80) {
        MBDlgWinExec(-1, 0x3A09);
    }
    MBDlgWinExec(-1, 0x3A06);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        GWBoardFlagSet(0x10);
        MBDlgWinExec(-1, 0x3A07);
        for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
            HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_80116754_w03(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}


void func_801175AC_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x80) {
        if ((player->rev & 0x40) || ((player->rev & 0x10) && !(player->rev & 4))) {
            MBDlgWinExec(-1, 0x421C);
        } else {
            MBDlgWinExec(-1, 0x3A03);
        }
        if (player->rev & 4) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}


void func_8011777C_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}


void func_801178B4_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;
    UnkVibrateProcess *vib;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(2, D_8011EC00_w03);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    player = MBPlayerGet(targetPlayer);
    player->rev |= 0x80;

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_80116754_w03(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_801169DC_w03(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_80116ADC_w03(targetPlayer);
    omAddPrcObj(func_80116FE4_w03, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (((previousPlayer == targetPlayer) && (func_800DEB2C_shared_board(previousPlayer) == 3)) ||
        ((GwSystem.slow_dice_flags >> targetPlayer) & 1)) {
        MBDlgWinExec(-1, 0x3A05);
    }
    MBDlgWinExec(-1, 0x3A02);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        func_801175AC_w03();
    }
}


void func_80117D38_w03(void) {
    char playerNames[4][16];
    u8 choices[16];
    Object *chest;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer = 0;
    s32 itemSlot;
    s32 i;
    f32 angle;
    u32 *motion;

    func_8010FF2C_w03();
    chest = MBModelCreate(0x21, NULL);
    Hu3DModelScaleSet(chest->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&chest->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(chest->omObj1->model[0], 2, 1);
    chest->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (chest->velocity.x > 30.0f) {
        chest->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    if (targetPlayer != 0) {
        for (i = 0; i < 1081; i += 30) {
            angle = sindf((f32)i) / 2.0f + 1.0f;
            HuVecCopyXYZ(&chest->scale, angle, sindf((f32)i) / 2.0f + 1.0f,
                         sindf((f32)i) / 2.0f + 1.0f);
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x149);
    func_8001C814_main(chest->omObj1->model[0], 1, 0);
    HuPrcSleep(20);

    for (i = 0; i < 4; i++) {
        if (GwSystem.current_player_index == i) {
            playerNames[i][0] = 1;
            choices[i] = 0;
        } else {
            playerNames[i][0] = 8;
            choices[i] = 1;
        }
        func_800E2260_shared_board(i, &playerNames[i][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_8011343C_w03(choices, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    if (GwPlayer[targetPlayer].itemNo[0] == -1) {
        MBPlayerMotionSet(-1, 3, 0);
        func_8004ACE0_main(0x286, system->current_player_index);
        HuPrcSleep(60);
        func_800E2260_shared_board(targetPlayer, playerNames[0]);
        MBWinInsertOpen(0x3A0F, playerNames[0], 0, 0, 0, 0);
        func_800EC3C0_shared_board(system->current_player_index);
        func_800EC3E4_shared_board();
        func_800F2388_shared_board(-1, -1, 0, 10, 2);
        MBModelKill(chest);
        GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
        MBItemRemoveEmpty(system->current_player_index);
        return;
    }

    itemSlot = MBItemFindEmpty(targetPlayer);
    if (itemSlot == -1) {
        itemSlot = 3;
    }
    itemSlot = MBRand((f32)itemSlot);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] =
        GwPlayer[targetPlayer].itemNo[itemSlot];
    GwPlayer[targetPlayer].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(targetPlayer);
    MBPlayerVibrate((s16)targetPlayer, 3);
    if (MBItemSelNoGet() == itemSlot) {
        MBStatusItemTPLvlSet(targetPlayer, MBItemSelNoGet(), 0);
    }
    MBStatusItemSprKill(-1);
    MBStatusItemPosSet(system->current_player_index, MBItemSelNoGet(),
                       D_8011D2AC_w03[system->current_player_index].x,
                       D_8011D2AC_w03[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(-1,
                                            D_8011D2AC_w03[system->current_player_index].x,
                                            D_8011D2AC_w03[system->current_player_index].y,
                                            D_8011D28C_w03[system->current_player_index].x,
                                            D_8011D28C_w03[system->current_player_index].y, 5));
    HuPrcChildWait();
    func_8004ACE0_main(0x274, system->current_player_index);
    MBPlayerMotionLoad(system->current_player_index, 5, 0x31);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(50);
    func_800F2388_shared_board(system->current_player_index, -1, 0, 10, 2);
    HuPrcSleep(11);
    motion = D_80101734_shared_board[0];
    for (i = 6; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    MBModelKill(chest);
    MBDlgWinInsertCreate(-1, 0x3A0D, GwPlayer[targetPlayer].chr + 0x1C00,
                         GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    func_801100FC_w03();
}


void func_801183E0_w03(void) {
    s32 spr[3][4];
    s32 titleSpr;
    s32 frameSpr;
    s32 grp;
    Process *proc;
    Unk3 *win;
    void *data;
    s32 playerGrp;
    s32 alpha;
    s32 mask;
    s32 clamped;
    s32 fading;
    s32 wrapped;
    s32 count;
    s32 i;
    s32 j;
    f32 angle;
    f32 speed;

    i = 0;
    proc = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleSpr = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    spr[0][0] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    spr[0][1] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    spr[0][2] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    spr[0][3] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    frameSpr = func_80055810_main(data);
    DataClose(data);
    for (; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        spr[1][i] = func_80055810_main(data);
        DataClose(data);
    }
    grp = HuSprGrpCreate(1, 5);
    func_80055024_main(grp, 0, titleSpr, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPriSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, 0xA0, 0x5A);
    angle = 0.0f;
    speed = 30.0f;
    count = 0;
    wrapped = 0;
    while (1) {
        if ((angle >= 90.0f) & (wrapped == 0)) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if ((angle >= 180.0f) & (angle <= 360.0f)) {
            HuSprAttrSet(grp, 0, 2);
        } else {
            HuSprAttrReset(grp, 0, 2);
        }
        HuSprScaleSet(grp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprAttrReset(grp, 0, 2);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    win = func_800E210C_shared_board(0x14, 0xA0, 1);
    for (i = 0; i < 4; i++) {
        playerGrp = spr[2][i] = HuSprGrpCreate(6, 5);
        func_80055024_main(playerGrp, 0, frameSpr, 0);
        func_800550F4_main(playerGrp, 0, 0);
        HuSprAttrReset(playerGrp, 0, 0xFFFF);
        if (D_8011EB40_w03[i] != 0) {
            HuSprAttrSet(playerGrp, 0, 8);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x8000);
        }
        HuSprPriSet(playerGrp, 0, 0x1000);
        func_800554C4_main(playerGrp, 0, -1);
        func_80055024_main(playerGrp, 1, spr[1][i], 0);
        func_800550F4_main(playerGrp, 1, 0);
        HuSprAttrReset(playerGrp, 1, 0xFFFF);
        if (D_8011EB40_w03[i] != 0) {
            HuSprAttrSet(playerGrp, 1, 8);
        } else {
            HuSprAttrSet(playerGrp, 1, 0x8000);
        }
        HuSprPriSet(playerGrp, 1, 0x1000);
        func_80054904_main(playerGrp, 1, 0, -9);
        func_800554C4_main(playerGrp, 1, 0);
        for (j = 0; j < 4; j++) {
            func_80055024_main(playerGrp, j + 2, spr[0][j], 0);
            func_800550F4_main(playerGrp, j + 2, 1);
            HuSprAttrReset(playerGrp, j + 2, 0xFFFF);
            if (D_8011EB40_w03[i] == j + 1) {
                HuSprAttrSet(playerGrp, j + 2, 8);
            } else {
                HuSprAttrSet(playerGrp, j + 2, 0x8000);
            }
            HuSprPriSet(playerGrp, j + 2, 0x1000);
            func_80054904_main(playerGrp, j + 2, 0, 9);
            func_800554C4_main(playerGrp, j + 2, 0);
        }
        func_80054904_main(playerGrp, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);
    angle = 90.0f;
    count = 0;
    fading = 0;
    wrapped = 0;
    alpha = 255;
    while (1) {
        if ((angle >= 360.0f) & (wrapped == 0)) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if ((fading == 0) & (count != 0)) {
            if ((angle >= 90.0f) & (angle < 180.0f)) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            mask = -(alpha > 0);
            clamped = mask & alpha;
            alpha = clamped;
        }
        func_80055458_main(grp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprScaleSet(grp, 0, 1.0f, 0.0f);
    HuSprGrpKill(grp);
    HuSprKill(titleSpr);
    proc->user_data = (void *)1;
    while (1) {
        for (i = 0; i < 4; i++) {
            switch (D_8011EB40_w03[i]) {
            case 0:
                for (j = 0; j < 6; j++) {
                    HuSprAttrSet(spr[2][i], j, 0x8000);
                }
                break;
            case 1:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 2, 0x8000);
                break;
            case 2:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 3, 0x8000);
                break;
            case 3:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 4, 0x8000);
                break;
            case 4:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 5, 0x8000);
                break;
            default:
                goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(win);
    HuSprKill(frameSpr);
    for (i = 0; i < 4; i++) {
        HuSprKill(spr[0][i]);
        HuSprKill(spr[1][i]);
        HuSprGrpKill(spr[2][i]);
    }
    omDelPrcObj(NULL);
}


void func_80118E3C_w03(omObjData *obj) {
    func_8001E888_main(D_8011EB30_w03->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "R3-cyl4", 0);
    obj->trans.x += 1.0f;
    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void func_80118F64_w03(omObjData *obj) {
    func_8001E888_main(D_8011EB30_w03->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "R3-cyl5_2", 0);
    obj->trans.x += 1.0f;
    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void func_8011908C_w03(void) {
    Object *obj;

    obj = D_8011EB34_w03 = MBModelCreate(0x4A, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x85)->coords);
    obj = D_8011EB38_w03 = MBModelCreate(0x4B, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x87)->coords);
    while (1) {
        HuPrcVSleep();
    }
}

void func_80119120_w03(void) {
    f32 angle;
    f32 scale;
    s32 count;
    Object *obj;
    omObjData *work;

    if (HuPrcCurrentGet()->user_data == NULL) {
        obj = D_8011EB34_w03;
    } else {
        obj = D_8011EB38_w03;
    }
    angle = 0.0f;
    scale = 1.0f;
    do {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        scale = 1.0f + 0.3f * sindf(angle);
        HuPrcVSleep();
        angle += 22.5f;
    } while (angle < 90.0f);
    count = 0;
    work = obj->omObj1;
    work->rot.z = 0.0f;
    angle = work->rot.z;
    scale = 5.0f;
    do {
        obj->omObj1->rot.z = sindf(angle) * scale;
        if (angle > 360.0f) {
            count++;
            angle -= 360.0f;
            scale -= 1.0f;
        }
        HuPrcVSleep();
        angle += 45.0f;
    } while (count < 4);
    obj->omObj1->rot.z = 0.0f;
    omDelPrcObj(NULL);
}

// NON_MATCHING: masked-equal at 1302 instructions except the frame (retail reserves 8 more bytes of
// spill space, 0x80 vs 0x78) and the register allocation that follows from it.
#ifdef NON_MATCHING
void func_80119290_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    Vec dir;
    Vec target;
    s32 comNoJump1;
    s32 comNoJump2;
    GW_PLAYER *player;
    Object *obj;
    SpaceData *masu;
    UnkEA790Struct *junction;
    UnkVibrateProcess *vib;
    Process *proc;
    u32 *motion;
    s32 state;
    s32 side;
    s32 count;
    s32 result;
    s32 i;

    player = MBPlayerGet(-1);
    obj = player->player_obj;
    mbItemBtnF = 0;
    MBStatusHideAll();
    func_800DBEC0_shared_board(system->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    comNoJump1 = MBComTreeExec(D_8011C9FC_w03);
    comNoJump2 = MBComTreeExec(D_8011CA44_w03);
    func_800E6FCC_shared_board();
    func_800ED20C_shared_board(system->current_player_index, 10, 0x85);
    MBPlayerMotionSet(-1, 0, 2);
    masu = MBMasuGet(0x85);
    HuVecCopy3F(&target, &obj->coords);
    HuVecSubtract(&dir, &masu->coords, &obj->coords);
    MBVecNormalize(&dir);
    target.x -= dir.x * 20.0f;
    target.z -= dir.z * 20.0f;
    proc = func_800ED75C_shared_board(&obj->coords, &target, &obj->coords, 2.0f);
    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWait();
    MBPlayerMotionSet(-1, -1, 2);
    for (i = 0; i < 4; i++) {
        D_8011EB40_w03[i] = 0;
    }
    D_8011EB2C_w03 = omAddPrcObj(func_801183E0_w03, 0x4800, 0, 0);
    while (D_8011EB2C_w03->user_data == NULL) {
        HuPrcVSleep();
    }
    D_8011EB40_w03[system->current_player_index] = 1;
    MBPlayerMotionSet(-1, 1, 2);
    MBVecDirGet(&obj->coords, &MBMasuGet(0x73)->coords, &obj->rot);
    state = 0;
    side = 0;
    while (1) {
        obj->coords.x += 2.0f * obj->rot.x;
        obj->coords.z += 2.0f * obj->rot.z;
        if (HuVecDistance(&obj->coords, &D_8011EB34_w03->coords) < 44.0f && state != 2) {
            D_8011EB40_w03[system->current_player_index] = 2;
        }
        if (HuVecDistance(&obj->coords, &D_8011EB34_w03->coords) < 40.0f) {
            if (HuVecDistance(&obj->coords, &D_8011EB34_w03->coords) < 20.0f) {
                break;
            }
            if ((D_800C9520_main[GwPlayer[system->current_player_index].pad] & 0x8000) && state != 2) {
                state = 1;
                break;
            }
            if (MBPlayerComCheck(system->current_player_index) && comNoJump1 == 0) {
                state = 1;
                break;
            }
        } else if (D_800C9520_main[GwPlayer[system->current_player_index].pad] & 0x8000) {
            state = 2;
            D_8011EB40_w03[system->current_player_index] = 4;
        }
        HuPrcVSleep();
    }
    if (state == 1) {
        func_8004ACE0_main(0x3A, system->current_player_index);
        func_8004ACE0_main(0x274, system->current_player_index);
        D_8011EB40_w03[system->current_player_index] = 3;
        MBPlayerMotionSet(-1, 2, 0);
        func_800EE688_shared_board(obj, 7.0f, -0.5f);
        for (i = 0; func_800EE694_shared_board(obj); i++) {
            obj->coords.x += 2.0f * obj->rot.x;
            obj->coords.z += 2.0f * obj->rot.z;
            if (i >= 21) {
                D_8011EB40_w03[system->current_player_index] = 1;
            }
            HuPrcVSleep();
        }
        func_8004ACE0_main(0x31, system->current_player_index);
        MBPlayerMotionSet(-1, 1, 2);
        state = 0;
        side = 1;
        while (1) {
            obj->coords.x += 2.0f * obj->rot.x;
            obj->coords.z += 2.0f * obj->rot.z;
            if (HuVecDistance(&obj->coords, &D_8011EB38_w03->coords) < 44.0f) {
                D_8011EB40_w03[system->current_player_index] = 2;
            }
            if (HuVecDistance(&obj->coords, &D_8011EB38_w03->coords) < 40.0f) {
                if (HuVecDistance(&obj->coords, &D_8011EB38_w03->coords) < 20.0f) {
                    break;
                }
                if (D_800C9520_main[GwPlayer[system->current_player_index].pad] & 0x8000) {
                    state = 1;
                    break;
                }
                if (MBPlayerComCheck(system->current_player_index) && comNoJump2 == 0) {
                    state = 1;
                    break;
                }
            }
            HuPrcVSleep();
        }
        if (state != 0) {
            func_8004ACE0_main(0x3A, system->current_player_index);
            func_8004ACE0_main(0x274, system->current_player_index);
            D_8011EB40_w03[system->current_player_index] = 3;
            MBPlayerMotionSet(-1, 2, 0);
            func_800EE688_shared_board(obj, 7.0f, -0.5f);
            while (func_800EE694_shared_board(obj)) {
                obj->coords.x += 2.0f * obj->rot.x;
                obj->coords.z += 2.0f * obj->rot.z;
                HuPrcVSleep();
            }
            func_8004ACE0_main(0x31, system->current_player_index);
            MBPlayerMotionSet(-1, 1, 2);
            HuVecCopy3F(&target, &MBMasuGet(0x73)->coords);
            HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&obj->coords, &target, &obj->coords, 2.0f));
            HuPrcChildWait();
            MBPlayerMotionSet(-1, -1, 2);
            HuPrcSleep(10);
            D_8011EB40_w03[0] = -1;
            MBStatusShowAll();
            func_800DB884_shared_board(system->current_player_index);
            HuPrcSleep(10);
            mbItemBtnF = 1;
            player->clink = 6;
            player->cidx = 4;
            player->nlink = 6;
            player->nidx = 5;
            player->blink = 6;
            player->bidx = 3;
            if (player->rev & 0x80) {
                func_80106D84_w03();
                junction = func_800D76A0_shared_board(system->current_player_index, D_8011D3F0_w03);
                func_800D742C_shared_board(junction, system->current_player_index, 0);
                if (MBPlayerComCheck(-1)) {
                    count = MBComTreeExec(D_8011CA68_w03);
                    for (i = 0; i < count; i++) {
                        func_800D7250_shared_board(junction, -2);
                    }
                    func_800D7250_shared_board(junction, -4);
                }
                result = func_800D7518_shared_board(junction);
                func_800D6CA0_shared_board(junction);
                func_80106E54_w03();
                if (result == 0) {
                    MBMoveNextMasuSet(-1, 6, 3);
                    player->rev |= 1;
                } else {
                    MBMoveNextMasuSet(-1, 6, 5);
                    player->rev &= ~1;
                }
            }
            func_800E6FBC_shared_board();
            omDelPrcObj(NULL);
            return;
        }
    }
    vib = MBPlayerVibrateObjCreate(-1, 2, 5);
    HuAudFXPlay(0x19A);
    func_8004ACE0_main(0x286, system->current_player_index);
    D_8011EB40_w03[system->current_player_index] = 4;
    MBPlayerMotionLoad(system->current_player_index, 5, 0x1A);
    MBPlayerMotionSet(-1, 5, 2);
    masu = MBMasuGet(side == 0 ? 0x71 : 0x19);
    omAddPrcObj(func_80119120_w03, 0x4800, 0, 0)->user_data = (void *)side;
    MBVecDirGet(&obj->coords, &masu->coords, &dir);
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            WipeCreateOut(11, 16);
        }
        func_800EE688_shared_board(obj, 7.0f, -0.5f);
        while (func_800EE694_shared_board(obj)) {
            obj->coords.x += 2.0f * dir.x;
            obj->coords.z += 2.0f * dir.z;
            HuPrcVSleep();
        }
        HuAudFXPlay(0x19B);
    }
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    masu = MBMasuGet(side == 0 ? 0x6F : 0x19);
    HuVecCopy3F(&dir, &masu->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&dir);
    func_800E6FBC_shared_board();
    HuPrcSleep(5);
    HuVecCopyXYZ(&D_8011EB34_w03->scale, 1.0f, 1.0f, 1.0f);
    HuVecCopyXYZ(&D_8011EB38_w03->scale, 1.0f, 1.0f, 1.0f);
    WipeCreateIn(11, 16);
    if (side == 0) {
        HuVecCopyXYZ(&obj->coords, 113.0f, 0.0f, -30.0f);
    } else {
        HuVecCopyXYZ(&obj->coords, -153.0f, 0.0f, -5.0f);
    }
    if (side == 0) {
        player->clink = 11;
        player->cidx = 11;
        player->nlink = 11;
        player->nidx = 11;
        player->blink = 11;
        player->bidx = 10;
    } else {
        player->clink = 5;
        player->cidx = 10;
        player->nlink = 5;
        player->nidx = 11;
        player->blink = 5;
        player->bidx = 9;
    }
    for (i = 0; i < 4; i++) {
        if (i != system->current_player_index) {
            MBPlayerPosFixSet(i, 20);
        }
    }
    MBVecDirGet(&obj->coords, &masu->coords, &target);
    for (i = 0; i < 2; i++) {
        func_800EE688_shared_board(obj, 7.0f, -0.5f);
        while (func_800EE694_shared_board(obj)) {
            obj->coords.x += 2.0f * target.x;
            obj->coords.z += 2.0f * target.z;
            HuPrcVSleep();
        }
        HuAudFXPlay(0x19B);
    }
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    MBCameraFocusModeSet(1);
    MBPlayerVibrateObjKill(vib);
    D_8011EB40_w03[0] = -1;
    MBPlayerMotionLoad(system->current_player_index, 6, 0xF);
    MBPlayerMotionSet(-1, 6, 0);
    MBPlayerMotionWait(-1);
    MBPlayerMotionSet(-1, -1, 2);
    motion = D_80101734_shared_board[0];
    for (i = 6; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    motion = D_80101734_shared_board[0];
    for (i = 7; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 6, ((u16 *)motion)[1]);
    MBStatusShowAll();
    MBDlgResultWinExec(0x700);
    func_800DB884_shared_board(system->current_player_index);
    HuPrcSleep(10);
    mbItemBtnF = 1;
    if (side == 0) {
        if (player->rev & 0x80) {
            func_80106D84_w03();
            junction = func_800D76A0_shared_board(system->current_player_index, D_8011D3E0_w03);
            func_800D742C_shared_board(junction, system->current_player_index, 0);
            if (MBPlayerComCheck(-1)) {
                switch (system->star_spawn_indices[system->current_star_spawn]) {
                case 6:
                    count = 2;
                    if (GwPlayer[system->current_player_index].coin < 20) {
                        count = 1;
                    }
                    if (GwPlayer[system->current_player_index].coin >= 20 && mbWalkNum >= 2) {
                        count = 2;
                    }
                    break;
                case 7:
                    count = 2;
                    if (GwPlayer[system->current_player_index].coin < 20) {
                        count = 1;
                    }
                    if (GwPlayer[system->current_player_index].coin >= 20 && mbWalkNum >= 5) {
                        count = 0;
                    }
                    break;
                default:
                    count = 2;
                    if (GwPlayer[system->current_player_index].coin >= 5 && mbWalkNum >= 4) {
                        count = 1;
                    }
                    break;
                }
                for (i = 0; i < count; i++) {
                    func_800D7250_shared_board(junction, -2);
                }
                func_800D7250_shared_board(junction, -4);
            }
            result = func_800D7518_shared_board(junction);
            func_800D6CA0_shared_board(junction);
            func_80106E54_w03();
            switch (result) {
            case 0:
                MBMoveNextMasuSet(-1, 1, 0);
                player->rev &= ~1;
                break;
            case 1:
                MBMoveNextMasuSet(-1, 11, 10);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 12, 0);
                player->rev &= ~1;
                break;
            }
        } else {
            HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_80108DA0_w03, 0x4800, 0, 0));
            HuPrcChildWait();
        }
    } else if (player->rev & 0x80) {
        func_80106D84_w03();
        junction = func_800D76A0_shared_board(system->current_player_index, D_8011D3E8_w03);
        func_800D742C_shared_board(junction, system->current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            switch (system->star_spawn_indices[system->current_star_spawn]) {
            case 2:
                count = 0;
                break;
            case 1:
                count = 2;
                break;
            default:
                count = 1;
                if (GwPlayer[system->current_player_index].coin < 20) {
                    count = mbWalkNum == 3;
                }
                break;
            }
            i = 0;
            if (count != 0) {
                do {
                    func_800D7250_shared_board(junction, -2);
                    i++;
                } while (i < count);
            }
            func_800D7250_shared_board(junction, -4);
        }
        result = func_800D7518_shared_board(junction);
        func_800D6CA0_shared_board(junction);
        func_80106E54_w03();
        switch (result) {
        case 0:
            MBMoveNextMasuSet(-1, 5, 9);
            player->rev |= 1;
            break;
        case 1:
            MBMoveNextMasuSet(-1, 5, 11);
            player->rev &= ~1;
            break;
        default:
            MBMoveNextMasuSet(-1, 6, 9);
            player->rev |= 1;
            break;
        }
    }
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80119290_w03);
#endif

void func_8011A2BC_w03(void) {
    GW_PLAYER *player = MBPlayerGet((s32)HuPrcCurrentGet()->user_data);
    s32 i;

    for (i = 0; i < 60; i++) {
        player->player_obj->velocity.x -= 0.41666666f;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

// decomp-permuter
void func_8011A338_w03(void)
{
  GW_PLAYER *player;
  W03PipeArg *arg;
  SpaceData *dest;
  s32 playerNo;
  Object *obj;
  GW_SYSTEM *sys;
  arg = HuPrcCurrentGet()->user_data;
  sys = &GwSystem;
  playerNo = arg->player;
  player = MBPlayerGet(playerNo);
  dest = MBMasuGet((D_8011EB3C_w03 == MBMasuGet(0x7F)) ? (0x24) : (0x4E));
  func_8004AC98_main(0x199, sys->current_player_index);
  player->player_obj->velocity.x = 0.0f;
  HuVecCopy3F(&player->player_obj->coords, &D_8011EB3C_w03->coords);
  obj = MBModelCreate(0x36, 0);
  HuVecCopy3F(&obj->coords, &D_8011EB3C_w03->coords);
  MBMotionSet(obj, -1, 0);
  func_800EE688_shared_board(player->player_obj, 15.0f, -0.1f);
  HuPrcSleep(10);
  player->player_obj->velocity.x = 100.0f;
  HuVecCopy3F(&player->player_obj->coords, &dest->coords);
  player->player_obj->coords.x += D_8011D438_w03[D_8011EB50_w03 + arg->slot].x;
  player->player_obj->coords.z += D_8011D438_w03[D_8011EB50_w03 + arg->slot].y;
  func_800EE688_shared_board(player->player_obj, 0.0f, -1.0f);
  func_800EE6C0_shared_board(player->player_obj);
  MBPlayerVibrate(playerNo, 1);
  MBModelKill(obj);
  if (D_8011EB3C_w03 == MBMasuGet(0x7F))
  {
    player->clink = 5;
    player->cidx = 0x14;
    player->nlink = 5;
    player->nidx = 0x15;
    player->blink = 5;
    player->bidx = 0x13;
  }
  else
    if (dest)
  {
    player->clink = 2;
    player->cidx = 2;
    player->nlink = 2;
    player->nidx = 3;
    player->blink = 2;
    player->bidx = 1;
  }
  else
  {
    player->clink = 2;
    player->cidx = 2;
    player->nlink = 2;
    player->nidx = 3;
    player->blink = 2;
    player->bidx = 1;
  }
  omDelPrcObj(0);
}

// decomp-permuter
void func_8011A550_w03(void)
{
  Vec dir;
  GW_PLAYER *player;
  s32 playerNo;
  s32 second;
  SpaceData *space;
  GW_SYSTEM *sys;
  f32 speed;
  second = 0;
  playerNo = (s32) HuPrcCurrentGet()->user_data;
  sys = &GwSystem;
 if (0) { }
  if (playerNo >= 4)
  {
    second = 1;
    playerNo -= 4;
  }
  player = MBPlayerGet(playerNo);
  space = MBMasuGet((second == 0) ? (0x80) : (0x7F));
  MBPlayerMotionSet(-1, 2, 0);
  func_800EE688_shared_board(player->player_obj, 15.0f, -2.5f);
  func_800EE6C0_shared_board(player->player_obj);
  HuVecSubtract(&dir, &player->player_obj->coords, &space->coords);
  MBVecNormalize(&dir);
  HuVecCopy3F(&player->player_obj->rot, &dir);
  func_8004ACE0_main(0x286, playerNo);
  if (playerNo == sys->current_player_index)
  {
    MBPlayerMotionSet(-1, 1, 2);
    MBPlayerSpeedSet(sys->current_player_index, 1.5f);
  }
  else
    if (player || space)
  {
    MBMotionSet(player->player_obj, 1, 2);
    func_8001C92C_main(player->player_obj->omObj1->model[0], 1.5f);
  }
  else
  {
    MBMotionSet(player->player_obj, 1, 2);
    func_8001C92C_main(player->player_obj->omObj1->model[0], 1.5f);
  }
  speed = 1.0f;
  do
  {
    player->player_obj->coords.x += speed * dir.x;
    player->player_obj->coords.z += speed * dir.z;
    HuPrcVSleep();
    speed -= 0.1f;
  }
  while (speed > 0.0f);
  omDelPrcObj(0);
}

#ifdef NON_MATCHING
void func_8011A704_w03(void) {
    Vec pos;
    UnkVibrateProcess *vibrate[4];
    s32 anim;
    GW_PLAYER *player;
    s16 *here;
    s16 *list;
    SpaceData *space;
    Object *heli;
    omObjData *scroll;
    void *data;
    Process *process;
    W03PipeArg *arg;
    f32 scale;
    s32 i;
    s32 n;
    s16 dest;
    SpaceData *destSpace;

    mbItemBtnF = 0;
    D_800A12D8_main = 1;
    MBStatusHideAll();
    here = D_8011D3F8_w03;
    player = MBPlayerGet(-1);
    while (*here != -1 && MBMasuLinkMasuIdGet(player->clink, player->cidx) != *here) {
        here++;
    }
    if (*here != -1) {
        D_8011EB30_w03 = MBModelCreate(0x47, NULL);
        space = MBMasuGet(0x80);
        list = D_8011D404_w03;
    } else {
        D_8011EB30_w03 = MBModelCreate(0x48, NULL);
        space = MBMasuGet(0x7F);
        list = D_8011D41C_w03;
    }
    func_8001C954_main(D_8011EB30_w03->omObj1->model[0]);
    HuVecCopy3F(&D_8011EB30_w03->coords, &space->coords);
    HuVecCopyXYZ(&D_8011EB30_w03->scale, 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);
    HuPrcSleep(10);
    for (; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                vibrate[i] = MBPlayerVibrateObjCreate(i, 1, 5);
            }
        }
    }
    HuAudFXPlay(0x198);
    if (*here != -1) {
        scroll = omAddObj(0x1000, 0, 0, -1, func_80118E3C_w03);
    } else {
        scroll = omAddObj(0x1000, 0, 0, -1, func_80118F64_w03);
    }
    scroll->trans.x = 0.0f;
    for (scale = scroll->trans.x; scale < 1.0f; scale += 0.1f) {
        HuVecCopyXYZ(&D_8011EB30_w03->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    /* Retail bug: list was not reset after the loop above, so this loop never runs. */
    for (; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                if (*here != -1) {
                    func_800ED20C_shared_board(i, 10, 0x80);
                } else {
                    func_800ED20C_shared_board(i, 10, 0x7F);
                }
            }
        }
    }
    list = *here != -1 ? D_8011D404_w03 : D_8011D41C_w03;
    HuPrcSleep(10);
    heli = MBModelCreate(0x49, NULL);
    HuVecCopy3F(&heli->coords, &space->coords);
    data = DataRead(0x130205);
    anim = (s16)HmfAnimCreate(HmfModelData[heli->omObj1->model[0]].hmf, data, 0, "f_heleye_I8");
    func_80032FC0_main(anim, 0, 0);
    DataClose(data);
    func_8001C258_main(heli->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(heli->omObj1->model[0], 0x1800);
    func_8001C448_main(heli->omObj1->model[0]);
    HuPrcSleep(12);
    for (; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                process = omAddPrcObj(func_8011A550_w03, 0x4800, 0, 0);
                if (*here != -1) {
                    process->user_data = (void *)i;
                } else {
                    process->user_data = (void *)(i + 4);
                }
                HuPrcChildLink(HuPrcCurrentGet(), process);
            }
        }
    }
    HuPrcChildWait();
    for (list = *here != -1 ? D_8011D404_w03 : D_8011D41C_w03; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords,
                                                                        &player->player_obj->coords, 60));
                omAddPrcObj(func_8011A2BC_w03, 0x4800, 0, 0)->user_data = (void *)i;
            }
        }
    }
    HuPrcChildWait();
    for (list = *here != -1 ? D_8011D404_w03 : D_8011D41C_w03; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                MBPlayerVibrateObjKill(vibrate[i]);
            }
        }
    }
    WipeCreateOut(11, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    if (*here != -1) {
        D_8011EB3C_w03 = space = MBMasuGet(0x7F);
        list = D_8011D404_w03;
    } else {
        D_8011EB3C_w03 = space = MBMasuGet(0x80);
        list = D_8011D41C_w03;
    }
    HuVecCopy3F(&pos, &space->coords);
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);
    omDelObj(scroll);
    func_80033354_main(anim);
    MBModelKill(heli);
    MBModelKill(D_8011EB30_w03);
    if (*here != -1) {
        dest = 0x24;
        destSpace = MBMasuGet(0x24);
    } else {
        dest = 0x4E;
        destSpace = MBMasuGet(0x4E);
    }
    D_8011EB50_w03 = 0;
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == dest) {
            HuVecCopy3F(&player->player_obj->coords, &destSpace->coords);
            player->player_obj->coords.x += D_8011D438_w03[D_8011EB50_w03].x;
            player->player_obj->coords.z += D_8011D438_w03[D_8011EB50_w03].y;
            D_8011EB50_w03++;
        }
    }
    MBCameraZoomSet(1.1f);
    HuPrcSleep(5);
    WipeCreateIn(4, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    for (n = 0; *list != -1; list++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *list) {
                HuVecCopyXYZ(&player->player_obj->rot, 0.0f, 0.0f, 1.0f);
                if (i == GwSystem.current_player_index) {
                    MBPlayerMotionSet(-1, -1, 2);
                } else {
                    MBMotionSet(player->player_obj, -1, 2);
                }
                process = omAddPrcObj(func_8011A338_w03, 0x4800, 0, 0x40);
                arg = HuMemMemoryAlloc(process->heap, 0x20);
                process->user_data = arg;
                arg->player = i;
                arg->slot = n;
                HuPrcChildLink(HuPrcCurrentGet(), process);
                n++;
                HuPrcSleep(10);
            }
        }
    }
    HuPrcChildWait();
    MBStatusShowAll();
    if (MBKettouPlayerBitGet(0)) {
        func_800E6FCC_shared_board();
        player = MBPlayerGet(-1);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&pos);
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&pos, &player->player_obj->coords, &pos, 2.0f));
        HuPrcChildWait();
        func_800E6FBC_shared_board();
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&pos);
    }
    D_800A12D8_main = 0;
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A704_w03);
#endif

void func_8011B1FC_w03(void) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    DecisionTreeNonLeafNode *tree;
    s32 count;
    s32 sel;
    s32 i;
    Process *process;
    GW_SYSTEM *sys = &GwSystem;

    player = MBPlayerGet(-1);
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    func_80106D84_w03();
    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
        win = func_800D76A0_shared_board(sys->current_player_index, D_8011D458_w03);
    } else {
        win = func_800D76A0_shared_board(sys->current_player_index, D_8011D460_w03);
    }
    func_800D742C_shared_board(win, sys->current_player_index, 0);
    if (MBPlayerComCheck(-1)) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
            tree = D_8011C948_w03;
        } else {
            tree = D_8011C99C_w03;
        }
        count = MBComTreeExec(tree);
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }
    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80106E54_w03();
    if (sel == 0) {
        process = omAddPrcObj(func_80119290_w03, 0x4800, 0, 0);
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcChildWait();
    } else {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
            MBMoveNextMasuSet(-1, 9, 0xE);
        } else {
            MBMoveNextMasuSet(-1, 9, 0xC);
        }
    }
    omDelPrcObj(NULL);
}

// entrypoint 4
void func_8011B41C_w03() {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011D598_w03);
    func_80107A04_w03();
    MBStart(2);
    omAddPrcObj(func_8010622C_w03, 0x1005, 0x1000, 0);
}

s32 func_8011B470_w03(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            func_800DA778_shared_board(i);
            if ((MBComTreeExec(D_8011E0DC_w03) == 0) &&
                (BoardPlayerRankCalc(i) < bestRank)) {
                bestRank = BoardPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}


s32 func_8011B51C_w03(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(D_8011E3A0_w03) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                func_800DA778_shared_board(i);
                if ((MBComTreeExec(D_8011E64C_w03) == 0) &&
                    (BoardPlayerRankCalc(i) < bestRank)) {
                    bestRank = BoardPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}


s32 func_8011B5E0_w03(void) {
    s32 turnsLeft;
    s32 slot;
    GW_SYSTEM *sys = &GwSystem;

    turnsLeft = sys->total_turns - sys->current_turn + 1;
    slot = MBItemFindEmpty(-1);
    if (slot == -1) {
        slot = 3;
    }
    return (slot < turnsLeft) ? 0 : 1;
}


s32 func_8011B634_w03(s32 base, s32 perLevel) {
    s32 ret;
    s32 i;
    s32 j;

    ret = 1;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != GwSystem.current_player_index) {
            for (j = 0; j < ARRAY_COUNT(GwPlayer->itemNo); j++) {
                if ((GwPlayer[i].itemNo[j] == ITEM_PLUNDER_CHEST) ||
                    (GwPlayer[i].itemNo[j] == ITEM_BARTER_BOX)) {
                    break;
                }
            }
            if (j < 3) {
                break;
            }
        }
    }
    if ((i < MB_MAX_PLAYERS) && MBRandCheck100(base + (perLevel * GwPlayer[i].cpu_difficulty)) != 0) {
        ret = 0;
    }
    return ret;
}


s32 func_8011B71C_w03(void) {
    s32 curPlayer = MBPlayerTurnGet();
    GW_SYSTEM *loc = &GwSystem;
    s32 results[3];
    s32 item;
    s32 i;
    s32 j;
    s32 count;
    s32 best;
    s32 slot;

    if (GwSystem.cur_player_used_item & 1) {
        return -1;
    }
    for (slot = 0; slot < 3; slot++) {
        results[slot] = -1;
        item = GwPlayer[curPlayer].itemNo[slot];
        switch (item) {
            case ITEM_NONE:
                continue;
            case ITEM_SKELETON_KEY:
            case ITEM_BOO_REPELLENT:
            case ITEM_KOOPA_KARD:
                for (i = 0, count = 0; i < 3; i++) {
                    if (GwPlayer[curPlayer].itemNo[i] == item) {
                        count++;
                    }
                }
                if (count < 2) {
                    continue;
                }
                break;
            case ITEM_WACKY_WATCH:
                if (loc->total_turns == loc->current_turn) {
                    if (MBPlayerStealRankGet(loc->current_player_index) != 0) {
                        break;
                    }
                }
                if (loc->total_turns - loc->current_turn < 6) {
                    continue;
                }
                if (MBPlayerStealRankGet(loc->current_player_index) == 0) {
                    break;
                }
                continue;
            case ITEM_MUSHROOM:
            case ITEM_LUCKY_CHARM:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBRandCheck100(80) == 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_PHONE:
                if (GwPlayer[curPlayer].coin == 0) {
                    break;
                }
                for (i = 0; i < 4; i++) {
                    if (i != curPlayer && GwPlayer[i].coin == 0) {
                        break;
                    }
                }
                if (i >= 4) {
                    break;
                }
                if (MBRandCheck100(70) != 0 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB30_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB9C_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011DDD0_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011E184_w03) == 0) {
                    s32 target = func_8011B470_w03();

                    D_8011EC04_w03 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011E568_w03) == 0) {
                    s32 target = func_8011B51C_w03();

                    D_8011EC00_w03 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011EBBC_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011EBBC_w03 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011EBBC_w03 == -1) {
                    continue;
                }
                if (best >= 4) {
                    break;
                }
                if (MBRandCheck100(5) == 0) {
                    continue;
                }
                break;
            case ITEM_BARTER_BOX:
                for (i = 0, best = 0; i < 3; i++) {
                    if (i != slot) {
                        s8 it = GwPlayer[loc->current_player_index].itemNo[i];

                        if (it != -1) {
                            best += D_80100FA8_shared_board[it];
                        }
                    }
                }
                for (i = 0, D_8011EBB8_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011EBB8_w03 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011EBB8_w03 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011B634_w03(0x32, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_CELLULAR_SHOPPER:
                if (loc->total_turns == loc->current_turn) {
                    continue;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_MAGIC_LAMP:
                if (func_8011B634_w03(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011DF68_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011E6B8_w03) != 0) {
                    continue;
                }
                break;
        }
        results[slot] = GwPlayer[curPlayer].itemNo[slot];
    }
    slot = 0;
    i = 0;
    for (j = 0; j < 3; j++) {
        item = results[j];
        if (item == -1) {
            continue;
        }
        if (loc->total_turns == loc->current_turn) {
            if (item == ITEM_WACKY_WATCH) {
                return j;
            }
        }
        if (slot < D_80100FF4_shared_board[results[j]]) {
            i = j;
            slot = D_80100FF4_shared_board[results[j]];
        }
    }
    if (slot == 0) {
        return -1;
    }
    return i;
}


s32 func_8011BD24_w03(void) {
    s32 sp14;
    GW_PLAYER* temp_s3;
    s32 var_s1_2;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s2_2;
    s32 temp_s0;
    u8 temp_s0_2;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    temp_s3 = MBPlayerGet(CUR_PLAYER);
    sp14 = 1;

    for (i = 0; i < 16; i++) {
        temp_s0 = D_8011E82C_w03[temp_s3->chr][i];
        var_s2 = func_8010B46C_w03(temp_s0);
        if (var_s2 != -1 && D_80100F94_shared_board[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(D_8011E8CC_w03[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((func_8010B46C_w03(0xE) != var_s2) &&
        ((func_8010B46C_w03(0xB) != var_s2) ||
        ((D_80100F94_shared_board[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((func_8010B46C_w03(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(D_8011E8EC_w03[D_8011D0D0_w03]) == 0) && GwPlayer[system->current_player_index].coin >= D_80100F94_shared_board[1]) {
        temp_v0 = func_8010B46C_w03(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(D_8011E8F4_w03[D_8011D0D0_w03]);
        if (i == 0) {
            do {
                temp_s0_2 = D_8011E82C_w03[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = func_8010B46C_w03(temp_s0_2);
                    if ((var_s2_2 != -1) && !(D_80100F94_shared_board[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(D_8011E8CC_w03[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = func_8010B46C_w03(0);
        if (var_s2_2 == -1) {
            D_8011E7A8_w03 = 1;
            return func_8010B4F4_w03() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}


s32 func_8011C088_w03(void) {
    if (D_8011E7A8_w03 != 0) {
        D_8011E7A8_w03 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011E8FC_w03[D_8011D0D0_w03]) + 1;
}

/* .data (0x8011C110, 0x2800 bytes): the overlay's initialised data, in address order. */
s16 D_8011C110_w03[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
s16 D_8011C120_w03[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
s16 D_8011C130_w03[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C140_w03[8] = { 4, 90, 20, 30, 40, 79, 2, 62 };
s16 D_8011C150_w03[8] = { 100, 101, 102, 103, 104, 105, 106, 107 };
s32 D_8011C160_w03 = 0;
s16 D_8011C164_w03[4] = { 54, 57, -1, 0 };
s16 D_8011C16C_w03[10] = { 4, 90, 20, 30, 40, 79, 2, 62, -1, 0 };
s16 D_8011C180_w03[8][2] = { { 7, -8 }, { 7, -1 }, { 8, -5 }, { 5, -9 }, { -1, -8 }, { 7, 0 }, { 0, -7 }, { -3, -6 } };
s16 D_8011C1A0_w03[2][2] = { { 2, 0 }, { 2, 0 } };
s16 D_8011C1A8_w03[2][2] = { { 0, -2 }, { 4, -1 } };
s16 D_8011C1B0_w03[2][2] = { { 2, -2 }, { 2, -3 } };
s16 D_8011C1B8_w03[2][2] = { { -1, -2 }, { 0, -3 } };
s16 D_8011C1C0_w03[2][2] = { { 116, 117 }, { 140, 141 } };
s16 D_8011C1C8_w03[8] = { 100, 101, 102, 103, 104, 105, 106, 107 };
s16 D_8011C1D8_w03[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C1E8_w03[2] = { 108, 0 };
s16 D_8011C1EC_w03[2] = { 124, 122 };
Vec D_8011C1F0_w03[5] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f },
};
Vec D_8011C22C_w03[5] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f },
};
s16 D_8011C268_w03[2] = { 125, 126 };
s16 D_8011C26C_w03[6] = { 38, 39, 40, 41, 42, 43 };
u32 D_8011C278_w03[2] = { 1, 0x00130163 };
u32 D_8011C280_w03[2] = { 1, 0x00130168 };
u32 D_8011C288_w03[2] = { 1, 0x0013016F };
u32 D_8011C290_w03[2] = { 1, 0x00130176 };
u32 D_8011C298_w03[2] = { 1, 0x00130180 };
u32 D_8011C2A0_w03[2] = { 1, 0x00130184 };
u32 *D_8011C2A8_w03[6] = { D_8011C278_w03, D_8011C280_w03, D_8011C288_w03, D_8011C290_w03, D_8011C298_w03, D_8011C2A0_w03 };
s32 D_8011C2C0_w03[9] = { 0x00000148, 0x00000148, 0x00000148, 0x00000148, 0x00000148, 0x00000148, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
s32 D_8011C2E4_w03[9] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
s32 D_8011C308_w03[9] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
s32 D_8011C32C_w03[9] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
s16 D_8011C350_w03[2] = { 123, 120 };
s16 D_8011C354_w03[2] = { 118, 119 };
s16 D_8011C358_w03[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C368_w03[8] = { 0, 1, 2, 3, 4, 6, 5, 7 };
s16 D_8011C378_w03[8] = { 0, 1, 2, 3, 4, 6, 5, 7 };
s16 D_8011C388_w03[8] = { 1, 2, 3, 4, 6, 5, 7, 0 };
s16 D_8011C398_w03[8] = { 4, 6, 1, 5, 7, 3, 0, 2 };
s16 D_8011C3A8_w03[8] = { 6, 1, 5, 7, 3, 4, 0, 2 };
s16 D_8011C3B8_w03[8] = { 6, 7, 1, 5, 3, 0, 4, 2 };
s16 D_8011C3C8_w03[8] = { 1, 6, 5, 7, 3, 4, 0, 2 };
DecisionTreeNonLeafNode D_8011C3D8_w03[2] = {
    { 3, { .data = 0x00000028 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011C3F0_w03[2] = {
    { 3, { .data = 0x00000280 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011C408_w03[2] = {
    { 2, { .data = 0x000000EA }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011C420_w03[5] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011C408_w03 } },
    { 2, { .data = 0x0000000F }, { .node_data = D_8011C3D8_w03 } },
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011C3F0_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C45C_w03[2] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1B541E32 } },
    { 0, { .data = 0x00000000 }, { .node_data = D_8011C3F0_w03 } },
};
DecisionTreeNonLeafNode D_8011C474_w03[4] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011C45C_w03 } },
    { 2, { .data = 0x0000000F }, { .data = 0x1B541E32 } },
    { 2, { .data = 0x000000F0 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C4A4_w03[3] = {
    { 2, { .data = 0x0000000F }, { .data = 0x1B541E32 } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011C3D8_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011C4C8_w03[3] = { D_8011C420_w03, D_8011C474_w03, D_8011C4A4_w03 };
DecisionTreeNonLeafNode D_8011C4D4_w03[3] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 2, { .data = 0x0000000E }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C4F8_w03[2] = {
    { 2, { .data = 0x0000000E }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C510_w03[2] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011C528_w03[3] = { D_8011C4D4_w03, D_8011C4F8_w03, D_8011C510_w03 };
DecisionTreeNonLeafNode D_8011C534_w03[3] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000020 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } },
};
DecisionTreeNonLeafNode D_8011C558_w03[7] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000002 }, { .data = 0x1C96A33C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0C96A33C } },
    { 3, { .data = 0x00004000 }, { .data = 0x1B542332 } },
    { 3, { .data = 0x00000008 }, { .data = 0x1A119E32 } },
    { 12, { .data = 0x0000000A }, { .node_data = D_8011C534_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } },
};
DecisionTreeNonLeafNode D_8011C5AC_w03[3] = {
    { 2, { .data = 0x00000005 }, { .data = 0x0C96A33C } },
    { 2, { .data = 0x0000000A }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C5D0_w03[3] = {
    { 2, { .data = 0x00000003 }, { .data = 0x0C96A33C } },
    { 2, { .data = 0x0000000C }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011C5F4_w03[3] = { D_8011C558_w03, D_8011C5AC_w03, D_8011C5D0_w03 };
DecisionTreeNonLeafNode D_8011C600_w03[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C618_w03[5] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000015 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x000000E0 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x0000000A }, { .node_data = D_8011C600_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C654_w03[1] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011C618_w03 } },
};
DecisionTreeNonLeafNode D_8011C660_w03[3] = {
    { 3, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000022 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011C684_w03[3] = {
    { 3, { .data = 0x00000033 }, { .data = 0x0A119E32 } },
    { 3, { .data = 0x000000C8 }, { .data = 0x1A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011C6A8_w03[4] = {
    { 2, { .data = 0x0000000F }, { .node_data = D_8011C660_w03 } },
    { 2, { .data = 0x000000E0 }, { .node_data = D_8011C684_w03 } },
    { 12, { .data = 0x00000014 }, { .node_data = D_8011C684_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97ED50 } },
};
DecisionTreeNonLeafNode *D_8011C6D8_w03[3] = { D_8011C618_w03, D_8011C654_w03, D_8011C6A8_w03 };
DecisionTreeNonLeafNode D_8011C6E4_w03[7] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x0B541E32 } },
    { 3, { .data = 0x00000100 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000212 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A332 } },
};
DecisionTreeNonLeafNode D_8011C738_w03[3] = {
    { 2, { .data = 0x00000015 }, { .data = 0x0C96A33C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C75C_w03[2] = {
    { 2, { .data = 0x00000015 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode *D_8011C774_w03[3] = { D_8011C6E4_w03, D_8011C738_w03, D_8011C75C_w03 };
DecisionTreeNonLeafNode D_8011C780_w03[2] = {
    { 1, { .data = 0x00000014 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011C798_w03[2] = {
    { 2, { .data = 0x00000040 }, { .node_data = D_8011C780_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011C7B0_w03[3] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000085 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011C7D4_w03[2] = {
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011C7EC_w03[2] = {
    { 2, { .data = 0x00000080 }, { .node_data = D_8011C7D4_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011C804_w03[3] = { D_8011C798_w03, D_8011C7B0_w03, D_8011C7EC_w03 };
DecisionTreeNonLeafNode D_8011C810_w03[2] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011C828_w03[3] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1A119E32 } },
};
DecisionTreeNonLeafNode D_8011C84C_w03[2] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } },
};
DecisionTreeNonLeafNode *D_8011C864_w03[3] = { D_8011C810_w03, D_8011C828_w03, D_8011C84C_w03 };
DecisionTreeNonLeafNode D_8011C870_w03[2] = {
    { 9, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B541E32 } },
};
DecisionTreeNonLeafNode D_8011C888_w03[2] = {
    { 2, { .data = 0x00000020 }, { .node_data = D_8011C870_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B541E32 } },
};
DecisionTreeNonLeafNode D_8011C8A0_w03[2] = {
    { 2, { .data = 0x00000020 }, { .node_data = D_8011C870_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C8B8_w03[2] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011C8D0_w03[3] = { D_8011C888_w03, D_8011C8A0_w03, D_8011C8B8_w03 };
DecisionTreeNonLeafNode D_8011C8DC_w03[2] = {
    { 9, { .data = 0x00000004 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011C8F4_w03[2] = {
    { 2, { .data = 0x00000028 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011C90C_w03[2] = {
    { 2, { .data = 0x00000028 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode *D_8011C924_w03[3] = { D_8011C8DC_w03, D_8011C8F4_w03, D_8011C90C_w03 };
DecisionTreeNonLeafNode D_8011C930_w03[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C948_w03[4] = {
    { 6, { .func = func_801089AC_w03 }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011C930_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C978_w03[3] = {
    { 12, { .data = 0x00000005 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C99C_w03[2] = {
    { 2, { .data = 0x00000030 }, { .node_data = D_8011C978_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C9B4_w03[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C9CC_w03[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C9E4_w03[2] = {
    { 5, { .data = 0x0000000C }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011C9FC_w03[6] = {
    { 2, { .data = 0x000000C5 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011C9B4_w03 } },
    { 3, { .data = 0x00000004 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011C9CC_w03 } },
    { 3, { .data = 0x00000001 }, { .node_data = D_8011C9E4_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011CA44_w03[3] = {
    { 2, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .node_data = D_8011C9E4_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011CA68_w03[2] = {
    { 2, { .data = 0x00000005 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011CA80_w03[3] = {
    { 2, { .data = 0x00000005 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000100 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011CAA4_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011CAB0_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011CABC_w03[3] = { D_8011CA80_w03, D_8011CAA4_w03, D_8011CAB0_w03 };
event_list_entry D_8011CAC8_w03[2] = {
    { 8, 1, func_80108AB8_w03 },
    { 0, 0, NULL },
};
s16 D_8011CAD8_w03[3][3] = { { 64, 12, -1 }, { 45, 65, -1 }, { 45, 56, -1 } };
BranchLink D_8011CAEC_w03[3][2] = {
    { { 1, 6, 1 }, { 1, 8, 0 } },
    { { 1, 12, 1 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 2, 0, 0 } },
};
event_list_entry D_8011CB10_w03[2] = {
    { 1, 1, func_80108ADC_w03 },
    { 0, 0, NULL },
};
s16 D_8011CB20_w03[3][3] = { { 56, 65, -1 }, { 45, 65, -1 }, { 45, 56, -1 } };
BranchLink D_8011CB34_w03[3][2] = {
    { { 2, 0, 0 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 2, 0, 0 } },
};
event_list_entry D_8011CB58_w03[2] = {
    { 1, 2, func_80108B98_w03 },
    { 0, 0, NULL },
};
s16 D_8011CB68_w03[3][3] = { { 7, 11, -1 }, { 6, 11, -1 }, { 6, 7, -1 } };
BranchLink D_8011CB7C_w03[3][2] = {
    { { 3, 0, 0 }, { 4, 0, 0 } },
    { { 2, 8, 1 }, { 4, 0, 0 } },
    { { 2, 8, 1 }, { 3, 0, 0 } },
};
event_list_entry D_8011CBA0_w03[2] = {
    { 1, 2, func_80108C48_w03 },
    { 0, 0, NULL },
};
s16 D_8011CBB0_w03[3][3] = { { 14, 83, -1 }, { 13, 83, -1 }, { 13, 14, -1 } };
BranchLink D_8011CBC4_w03[3][2] = {
    { { 5, 0, 0 }, { 6, 0, 0 } },
    { { 4, 1, 1 }, { 6, 0, 0 } },
    { { 4, 1, 1 }, { 5, 0, 0 } },
};
event_list_entry D_8011CBE8_w03[2] = {
    { 1, 2, func_80108C80_w03 },
    { 0, 0, NULL },
};
s16 D_8011CBF8_w03[3][3] = { { 41, 49, -1 }, { 40, 49, -1 }, { 40, 41, -1 } };
BranchLink D_8011CC0C_w03[3][2] = {
    { { 7, 0, 0 }, { 8, 0, 0 } },
    { { 5, 24, 1 }, { 8, 0, 0 } },
    { { 5, 24, 1 }, { 7, 0, 0 } },
};
event_list_entry D_8011CC30_w03[2] = {
    { 1, 2, func_80108CB8_w03 },
    { 0, 0, NULL },
};
s16 D_8011CC40_w03[3][3] = { { 93, 50, -1 }, { 49, 50, -1 }, { 49, 93, -1 } };
BranchLink D_8011CC54_w03[3][2] = {
    { { 9, 0, 0 }, { 11, 0, 0 } },
    { { 8, 0, 1 }, { 11, 0, 0 } },
    { { 8, 0, 1 }, { 9, 0, 0 } },
};
event_list_entry D_8011CC78_w03[2] = {
    { 1, 2, func_80108CF0_w03 },
    { 0, 0, NULL },
};
s16 D_8011CC88_w03[3][3] = { { 57, 99, -1 }, { 58, 99, -1 }, { 58, 57, -1 } };
BranchLink D_8011CC9C_w03[3][2] = {
    { { 11, 10, 1 }, { 12, 0, 0 } },
    { { 1, 0, 0 }, { 12, 0, 0 } },
    { { 1, 0, 0 }, { 11, 10, 1 } },
};
event_list_entry D_8011CCC0_w03[2] = {
    { 1, 2, func_80108DA0_w03 },
    { 0, 0, NULL },
};
s16 D_8011CCD0_w03[3][3] = { { 89, 10, -1 }, { 67, 10, -1 }, { 67, 89, -1 } };
BranchLink D_8011CCE4_w03[3][2] = {
    { { 2, 3, 0 }, { 3, 3, 1 } },
    { { 2, 1, 1 }, { 3, 3, 1 } },
    { { 2, 1, 1 }, { 2, 3, 0 } },
};
event_list_entry D_8011CD08_w03[2] = {
    { 1, 1, func_80108DD8_w03 },
    { 0, 0, NULL },
};
s16 D_8011CD18_w03[3][3] = { { 26, 92, -1 }, { 24, 92, -1 }, { 24, 26, -1 } };
BranchLink D_8011CD2C_w03[3][2] = {
    { { 5, 11, 0 }, { 6, 9, 1 } },
    { { 5, 9, 1 }, { 6, 9, 1 } },
    { { 5, 9, 1 }, { 5, 11, 0 } },
};
event_list_entry D_8011CD50_w03[2] = {
    { 1, 1, func_80108E30_w03 },
    { 0, 0, NULL },
};
s16 D_8011CD60_w03[3][3] = { { 35, 82, -1 }, { 32, 82, -1 }, { 32, 35, -1 } };
BranchLink D_8011CD74_w03[3][2] = {
    { { 5, 19, 0 }, { 9, 20, 1 } },
    { { 5, 17, 1 }, { 9, 20, 1 } },
    { { 5, 17, 1 }, { 5, 19, 0 } },
};
event_list_entry D_8011CD98_w03[2] = {
    { 1, 1, func_80108E88_w03 },
    { 0, 0, NULL },
};
s16 D_8011CDA8_w03[3][3] = { { 37, 48, -1 }, { 35, 48, -1 }, { 35, 37, -1 } };
BranchLink D_8011CDBC_w03[3][2] = {
    { { 5, 21, 0 }, { 7, 6, 1 } },
    { { 5, 19, 1 }, { 7, 6, 1 } },
    { { 5, 19, 1 }, { 5, 21, 0 } },
};
event_list_entry D_8011CDE0_w03[2] = {
    { 1, 1, func_80108EE0_w03 },
    { 0, 0, NULL },
};
s16 D_8011CDF0_w03[4] = { 70, 69, 2, -1 };
s16 D_8011CDF8_w03[4] = { 98, 69, 2, -1 };
s16 D_8011CE00_w03[4] = { 98, 70, 2, -1 };
s16 D_8011CE08_w03[4] = { 98, 70, 69, -1 };
event_list_entry D_8011CE10_w03[2] = {
    { 1, 1, func_80108F38_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE20_w03[2] = {
    { 1, 1, func_80109268_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE30_w03[2] = {
    { 1, 1, func_801092C8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE40_w03[2] = {
    { 1, 1, func_80109328_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE50_w03[2] = {
    { 1, 1, func_80109388_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE60_w03[2] = {
    { 1, 1, func_801093E8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE70_w03[2] = {
    { 1, 1, func_80109448_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE80_w03[2] = {
    { 1, 1, func_801094A8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CE90_w03[2] = {
    { 1, 1, func_80109508_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CEA0_w03[2] = {
    { 1, 1, func_80109568_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CEB0_w03[2] = {
    { 1, 1, func_801095C8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CEC0_w03[2] = {
    { 1, 1, func_80109628_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CED0_w03[2] = {
    { 1, 1, func_80109688_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CEE0_w03[2] = {
    { 1, 1, func_801096E8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CEF0_w03[2] = {
    { 1, 1, func_80109748_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CF00_w03[2] = {
    { 1, 1, func_801097A8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CF10_w03[2] = {
    { 1, 1, func_80109808_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CF20_w03[2] = {
    { 1, 1, func_80109868_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CF30_w03[2] = {
    { 1, 2, func_80109AD8_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011CF40_w03[2] = {
    { 1, 1, func_8010A2C4_w03 },
    { 0, 0, NULL },
};
DecisionTreeNonLeafNode D_8011CF50_w03[2] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } },
};
u32 D_8011CF68_w03[2] = { 1, 0x000A009D };
event_list_entry D_8011CF70_w03[2] = {
    { 1, 1, func_8010A930_w03 },
    { 0, 0, NULL },
};
u8 D_8011CF80_w03[2][3][4] = { { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }, { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } } };
s8 D_8011CF98_w03[2][5][7] = { { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } }, { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } } };
u8 D_8011CFE0_w03[2][3][4] = { { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }, { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } } };
s8 D_8011CFF8_w03[2][5][10] = { { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } }, { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } } };
u8 D_8011D05C_w03[2][10] = { { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 }, { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 } };
s32 D_8011D070_w03[5][2] = { { 0x00003B05, 0x00003D05 }, { 0x00003B06, 0x00003D06 }, { 0x00003B07, 0x00003D07 }, { 0x00003B08, 0x00003D08 }, { 0x00003B09, 0x00003D09 } };
s32 D_8011D098_w03[2] = { 0x00003B00, 0x00003D00 };
s32 D_8011D0A0_w03[2] = { 0x00003B01, 0x00003D01 };
s32 D_8011D0A8_w03[2] = { 0x00003B02, 0x00003D02 };
s32 D_8011D0B0_w03[2] = { 0x00003B03, 0x00003D03 };
s32 D_8011D0B8_w03[2] = { 0x00003B04, 0x00003D04 };
u32 D_8011D0C0_w03[2] = { 1, 0x000A0017 };
u32 D_8011D0C8_w03[2] = { 1, 0x000A00F0 };
s32 D_8011D0D0_w03 = 0;
event_list_entry D_8011D0D4_w03[2] = {
    { 1, 1, func_8010B734_w03 },
    { 0, 0, NULL },
};
Vec2f D_8011D0E4_w03[4] = { { 76.0f, 52.0f }, { 244.0f, 52.0f }, { 76.0f, 192.0f }, { 244.0f, 192.0f } };
Vec2f D_8011D104_w03[4] = { { -1.0f, -1.0f }, { 1.0f, -1.0f }, { -1.0f, 1.0f }, { 1.0f, 1.0f } };
u8 D_8011D124_w03[6][3] = { { 1, 5, 15 }, { 6, 15, 25 }, { 16, 25, 27 }, { 26, 35, 30 }, { 36, 45, 32 }, { 46, 50, 35 } };
u8 D_8011D138_w03[14][3] = { { 0, 0, 0 }, { 1, 10, 1 }, { 11, 11, 4 }, { 12, 14, 2 }, { 15, 15, 4 }, { 16, 23, 3 }, { 24, 33, 4 }, { 34, 37, 5 }, { 38, 39, 2 }, { 40, 49, 6 }, { 50, 54, 5 }, { 55, 63, 7 }, { 64, 64, 8 }, { 65, 255, 9 } };
u8 D_8011D164_w03[8] = { 0x09, 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00 };
s32 D_8011D16C_w03[3] = { 0x00000032, 0x00000050, 0x00000064 };
s32 D_8011D178_w03[7] = { 1, 0, 1, 0, 0, 1, 0 };
event_list_entry D_8011D194_w03[2] = {
    { 1, 1, func_8010DF54_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011D1A4_w03[2] = {
    { 1, 1, func_8010F128_w03 },
    { 0, 0, NULL },
};
event_list_entry D_8011D1B4_w03[2] = {
    { 1, 1, func_8010F144_w03 },
    { 0, 0, NULL },
};
event_table_entry D_8011D1C4_w03[15] = {
    { 4, D_8011CF40_w03 },
    { 90, D_8011CF40_w03 },
    { 20, D_8011CF40_w03 },
    { 30, D_8011CF40_w03 },
    { 40, D_8011CF40_w03 },
    { 79, D_8011CF40_w03 },
    { 2, D_8011CF40_w03 },
    { 62, D_8011CF40_w03 },
    { 28, D_8011CF70_w03 },
    { 95, D_8011CF70_w03 },
    { 110, D_8011D0D4_w03 },
    { 113, D_8011D0D4_w03 },
    { 125, D_8011D1A4_w03 },
    { 126, D_8011D1B4_w03 },
    { -1, NULL },
};
event_table_entry D_8011D23C_w03[2] = {
    { 142, D_8011D194_w03 },
    { -1, NULL },
};
Vec2f D_8011D24C_w03[4] = { { 164.0f, 76.0f }, { 140.0f, 76.0f }, { 164.0f, 76.0f }, { 140.0f, 76.0f } };
Vec2f D_8011D26C_w03[4] = { { 132.0f, 62.0f }, { 220.0f, 62.0f }, { 132.0f, 180.0f }, { 220.0f, 180.0f } };
Vec2f D_8011D28C_w03[4] = { { 164.0f, 66.0f }, { 164.0f, 66.0f }, { 164.0f, 66.0f }, { 164.0f, 66.0f } };
Vec2f D_8011D2AC_w03[4] = { { 164.0f, 76.0f }, { 164.0f, 76.0f }, { 164.0f, 76.0f }, { 164.0f, 76.0f } };
DecisionTreeNonLeafNode D_8011D2CC_w03[9] = {
    { 13, { .data = 0x00000000 }, { .data = 0x0A142850 } },
    { 13, { .data = 0x00000001 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000002 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000003 }, { .data = 0x08D1A346 } },
    { 13, { .data = 0x00000004 }, { .data = 0x078F1E3C } },
    { 13, { .data = 0x00000005 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000006 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000007 }, { .data = 0x078F1E3C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
s32 D_8011D338_w03[5] = { 20, 60, 30, 50, 70 };
DecisionTreeNonLeafNode D_8011D34C_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
Vec2f D_8011D358_w03[6] = { { -10.0f, 0.0f }, { 10.0f, -5.0f }, { 10.0f, 5.0f }, { -5.0f, -5.0f }, { 10.0f, 0.0f }, { -5.0f, 5.0f } };
s32 D_8011D388_w03 = -1;
u8 D_8011D38C_w03[4] = { 0x43, 0x44, 0x45, 0x00 };
u8 D_8011D390_w03[4] = { 0x14, 0x3C, 0x64, 0x00 };
p3GameGuyReward D_8011D394_w03[7] = { { 0, 50 }, { 2, 80 }, { 4, 90 }, { 8, 94 }, { 16, 97 }, { 32, 99 }, { 64, 100 } };
RGB D_8011D3B0_w03[2] = { { 0xF0, 0xDE, 0x35 }, { 0xF7, 0x1A, 0x42 } };
event_list_entry D_8011D3B8_w03[3] = {
    { 7, 1, func_80116C78_w03 },
    { 7, 1, func_801175AC_w03 },
    { 0, 0, NULL },
};
event_table_entry D_8011D3D0_w03[2] = {
    { -5, D_8011D3B8_w03 },
    { -1, NULL },
};
s16 D_8011D3E0_w03[4] = { 58, 57, 99, -1 };
s16 D_8011D3E8_w03[4] = { 24, 26, 92, -1 };
s16 D_8011D3F0_w03[4] = { 86, 87, -1, 0 };
s16 D_8011D3F8_w03[6] = { 89, 3, 9, 10, -1, 0 };
s16 D_8011D404_w03[12] = { 78, 89, 1, 3, 4, 5, 6, 7, 8, 9, 10, -1 };
s16 D_8011D41C_w03[14] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, -1, 0 };
Vec2f D_8011D438_w03[4] = { { 0.0f, 0.0f }, { -10.0f, 0.0f }, { 0.0f, -10.0f }, { 10.0f, 0.0f } };
s16 D_8011D458_w03[4] = { 115, 75, -1, 0 };
s16 D_8011D460_w03[4] = { 115, 74, -1, 0 };
event_list_entry D_8011D468_w03[2] = {
    { 1, 2, func_8011B1FC_w03 },
    { 0, 0, NULL },
};
event_table_entry D_8011D478_w03[36] = {
    { 109, D_8011CAC8_w03 },
    { 0, D_8011CB10_w03 },
    { 121, D_8011CB58_w03 },
    { 132, D_8011CBA0_w03 },
    { 137, D_8011CBE8_w03 },
    { 138, D_8011CC30_w03 },
    { 139, D_8011CC78_w03 },
    { 111, D_8011CCC0_w03 },
    { 78, D_8011CD08_w03 },
    { 25, D_8011CD50_w03 },
    { 33, D_8011CD98_w03 },
    { 36, D_8011CDE0_w03 },
    { 112, D_8011CE10_w03 },
    { 58, D_8011CE20_w03 },
    { 56, D_8011CE30_w03 },
    { 7, D_8011CE40_w03 },
    { 10, D_8011CE50_w03 },
    { 11, D_8011CE60_w03 },
    { 14, D_8011CE70_w03 },
    { 83, D_8011CE80_w03 },
    { 92, D_8011CE90_w03 },
    { 41, D_8011CEA0_w03 },
    { 48, D_8011CEB0_w03 },
    { 49, D_8011CEC0_w03 },
    { 93, D_8011CED0_w03 },
    { 82, D_8011CEE0_w03 },
    { 65, D_8011CEF0_w03 },
    { 69, D_8011CF00_w03 },
    { 50, D_8011CF10_w03 },
    { 99, D_8011CF20_w03 },
    { 116, D_8011CF30_w03 },
    { 140, D_8011CF30_w03 },
    { 117, D_8011CF30_w03 },
    { 141, D_8011CF30_w03 },
    { 114, D_8011D468_w03 },
    { -1, NULL },
};
RectF D_8011D598_w03 = { 0.0f, 0.0f, 320.0f, 240.0f };
DecisionTreeNonLeafNode D_8011D5A8_w03[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00020000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001000C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D5D8_w03[15] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00060000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020008 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010A0C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00090208 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B000A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D68C_w03[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020008 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010A0C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D6E0_w03[8] = {
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001050C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x0000001E }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051718 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D740_w03[18] = {
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050009 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060009 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020608 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B080A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D6E0_w03 } },
    { 12, { .data = 0x0000001E }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051718 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001050C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D818_w03[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050412 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070005 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00090414 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D86C_w03[3] = {
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001040C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D890_w03[11] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009020A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B000A }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D86C_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D914_w03[8] = {
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050E18 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00091114 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001020C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D974_w03[14] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D914_w03 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0101 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051218 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001020C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA1C_w03[8] = {
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070406 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051118 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00091414 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010205 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA7C_w03[15] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011DA1C_w03 } },
    { 10, { .data = 0x000B0606 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000B0809 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0101 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010205 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB30_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D5A8_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D5D8_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011D68C_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011D740_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D818_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D890_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011D974_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011DA7C_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB9C_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } },
};
DecisionTreeNonLeafNode D_8011DBA8_w03[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020105 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DBD8_w03[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00060106 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090A0C }, { .data = 0x0000028A } },
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DC20_w03[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050105 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DC50_w03[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050A0E }, { .data = 0x0000028A } },
    { 11, { .data = 0x00050D0E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028A1E } },
    { 11, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DC98_w03[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00051317 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00070606 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DCE0_w03[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090B10 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DD10_w03[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000C0000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B060A }, { .data = 0x0000028A } },
    { 10, { .data = 0x0009080C }, { .data = 0x0000028A } },
    { 11, { .data = 0x000C0000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B060A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0009080C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DD70_w03[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010003 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0A0A }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0000028A } },
    { 11, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0A0A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011DDD0_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DBA8_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DBD8_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DC20_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011DC50_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011DC98_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011DCE0_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011DD10_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011DD70_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DE3C_w03[2] = {
    { 10, { .data = 0x00020105 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DE54_w03[3] = {
    { 10, { .data = 0x00060106 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090A0C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DE78_w03[2] = {
    { 10, { .data = 0x00050105 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DE90_w03[2] = {
    { 1, { .data = 0x00000019 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DEA8_w03[3] = {
    { 10, { .data = 0x00050A0E }, { .data = 0x0000028A } },
    { 11, { .data = 0x00090C0C }, { .node_data = D_8011DE90_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DECC_w03[3] = {
    { 10, { .data = 0x00051317 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00070606 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DEF0_w03[2] = {
    { 10, { .data = 0x00090B10 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DF08_w03[4] = {
    { 10, { .data = 0x000C0000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B060A }, { .data = 0x0000028A } },
    { 10, { .data = 0x0009080C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DF38_w03[4] = {
    { 10, { .data = 0x00010003 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0A0A }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011DF68_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DE3C_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DE54_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DE78_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011DEA8_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011DECC_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011DEF0_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011DF08_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011DF38_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DFD4_w03[2] = {
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DFEC_w03[3] = {
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E010_w03[2] = {
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E028_w03[2] = {
    { 11, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E040_w03[3] = {
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E064_w03[2] = {
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E07C_w03[4] = {
    { 11, { .data = 0x000C0000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B060A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0009080C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E0AC_w03[4] = {
    { 11, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0A0A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E0DC_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DFD4_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DFEC_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E010_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E028_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E040_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E064_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E07C_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E0AC_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E148_w03[5] = {
    { 10, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E184_w03[3] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011E0DC_w03 } },
    { 0, { .data = 0x00000000 }, { .node_data = D_8011E148_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E1A8_w03[7] = {
    { 10, { .data = 0x00040001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060000 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020708 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E1FC_w03[6] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060809 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090E10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E244_w03[4] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0005070B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090E0F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E274_w03[5] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00051014 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090E10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2B0_w03[6] = {
    { 10, { .data = 0x00080000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0A119E32 } },
    { 10, { .data = 0x00090003 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00070004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2F8_w03[4] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00091214 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00051313 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E328_w03[7] = {
    { 10, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090E11 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0009070C }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E37C_w03[3] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0001050A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E3A0_w03[13] = {
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E328_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E37C_w03 } },
    { 12, { .data = 0x00000005 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B080A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E1A8_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E1FC_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E244_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E274_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E2B0_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E2F8_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E43C_w03[2] = {
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E454_w03[3] = {
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E478_w03[2] = {
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E490_w03[2] = {
    { 11, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E4A8_w03[3] = {
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E4CC_w03[2] = {
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8011E4E4_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E4F0_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E4FC_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E43C_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E454_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E478_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E490_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E4A8_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E4CC_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E4E4_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E4F0_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E568_w03[3] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011E3A0_w03 } },
    { 0, { .data = 0x00000000 }, { .node_data = D_8011E4FC_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E58C_w03[2] = {
    { 15, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E5A4_w03[3] = {
    { 15, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E5C8_w03[2] = {
    { 15, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E5E0_w03[2] = {
    { 15, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E5F8_w03[3] = {
    { 15, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E61C_w03[2] = {
    { 15, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E634_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E640_w03[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E64C_w03[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E58C_w03 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E5A4_w03 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E5C8_w03 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E5E0_w03 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E5F8_w03 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E61C_w03 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E634_w03 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E640_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6B8_w03[2] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011E4FC_w03 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6D0_w03[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x000000EA }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6F4_w03[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x0000007A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E718_w03[2] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E730_w03[2] = {
    { 1, { .data = 0x00000037 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E748_w03[3] = {
    { 2, { .data = 0x000000FA }, { .data = 0x0B54233C } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } },
};
DecisionTreeNonLeafNode D_8011E76C_w03[2] = {
    { 1, { .data = 0x0000001E }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } },
};
DecisionTreeNonLeafNode D_8011E784_w03[3] = {
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E76C_w03 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } },
};
s32 D_8011E7A8_w03 = 0;
u8 D_8011E7AC_w03[16] = { 0x0E, 0x0A, 0x00, 0x03, 0x02, 0x04, 0x13, 0x0B, 0x05, 0x06, 0x0C, 0x0D, 0x09, 0x07, 0x08, 0x01 };
u8 D_8011E7BC_w03[16] = { 0x0E, 0x01, 0x0B, 0x0A, 0x13, 0x0C, 0x00, 0x06, 0x09, 0x03, 0x0D, 0x04, 0x08, 0x07, 0x02, 0x05 };
u8 D_8011E7CC_w03[16] = { 0x0E, 0x0B, 0x06, 0x09, 0x0C, 0x07, 0x03, 0x0D, 0x02, 0x04, 0x0A, 0x13, 0x00, 0x08, 0x05, 0x01 };
u8 D_8011E7DC_w03[16] = { 0x0E, 0x05, 0x09, 0x0A, 0x0B, 0x07, 0x13, 0x0C, 0x00, 0x06, 0x03, 0x0D, 0x04, 0x08, 0x02, 0x01 };
u8 D_8011E7EC_w03[16] = { 0x0E, 0x08, 0x0D, 0x0B, 0x0A, 0x13, 0x06, 0x07, 0x0C, 0x00, 0x09, 0x03, 0x04, 0x02, 0x05, 0x01 };
u8 D_8011E7FC_w03[16] = { 0x0E, 0x03, 0x0B, 0x0A, 0x13, 0x0C, 0x00, 0x06, 0x09, 0x0D, 0x04, 0x08, 0x07, 0x02, 0x05, 0x01 };
u8 D_8011E80C_w03[16] = { 0x0E, 0x02, 0x09, 0x03, 0x06, 0x07, 0x08, 0x05, 0x04, 0x13, 0x0B, 0x0D, 0x0A, 0x0C, 0x00, 0x01 };
u8 D_8011E81C_w03[16] = { 0x0E, 0x04, 0x13, 0x09, 0x0B, 0x0A, 0x03, 0x0C, 0x07, 0x00, 0x01, 0x06, 0x0D, 0x08, 0x02, 0x05 };
u8 *D_8011E82C_w03[8] = { D_8011E7AC_w03, D_8011E7BC_w03, D_8011E7CC_w03, D_8011E7DC_w03, D_8011E7EC_w03, D_8011E7FC_w03, D_8011E80C_w03, D_8011E81C_w03 };
s8 D_8011E84C_w03[16] = { 0x5A, 0x46, 0x3C, 0x1E, 0x14, 0x14, 0x14, 0x14, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
s8 D_8011E85C_w03[16] = { 0x50, 0x32, 0x14, 0x14, 0x14, 0x0A, 0x14, 0x0A, 0x0A, 0x0A, 0x14, 0x0A, 0x0A, 0x0A, 0x0A, 0x00 };
s8 D_8011E86C_w03[16] = { 0x50, 0x1E, 0x32, 0x1E, 0x1E, 0x14, 0x14, 0x14, 0x14, 0x14, 0x1E, 0x14, 0x1E, 0x0A, 0x0A, 0x0A };
s8 D_8011E87C_w03[16] = { 0x5A, 0x32, 0x14, 0x1E, 0x14, 0x0A, 0x14, 0x0A, 0x1E, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
s8 D_8011E88C_w03[16] = { 0x5A, 0x32, 0x1E, 0x1E, 0x1E, 0x14, 0x14, 0x14, 0x0A, 0x1E, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
s8 D_8011E89C_w03[16] = { 0x5A, 0x32, 0x1E, 0x3C, 0x14, 0x14, 0x1E, 0x14, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
s8 D_8011E8AC_w03[16] = { 0x46, 0x28, 0x28, 0x28, 0x1E, 0x14, 0x1E, 0x1E, 0x14, 0x28, 0x28, 0x1E, 0x28, 0x0A, 0x28, 0x0A };
s8 D_8011E8BC_w03[16] = { 0x50, 0x32, 0x3C, 0x14, 0x14, 0x1E, 0x14, 0x1E, 0x0A, 0x1E, 0x14, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A };
s8 *D_8011E8CC_w03[8] = { D_8011E84C_w03, D_8011E85C_w03, D_8011E86C_w03, D_8011E87C_w03, D_8011E88C_w03, D_8011E89C_w03, D_8011E8AC_w03, D_8011E8BC_w03 };
DecisionTreeNonLeafNode *D_8011E8EC_w03[2] = { D_8011E6D0_w03, D_8011E6F4_w03 };
DecisionTreeNonLeafNode *D_8011E8F4_w03[2] = { D_8011E718_w03, D_8011E730_w03 };
DecisionTreeNonLeafNode *D_8011E8FC_w03[5] = { D_8011E748_w03, D_8011E784_w03, NULL, NULL, NULL };
