#include "common.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "WaluigisIsland.h" /* BranchLink */
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/board.h"
#include "../ovl_80_shared_board/106640.h"
#include "input.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "../ovl_80_shared_board/F2910.h"
#include "../ovl_80_shared_board/1063F0.h"

typedef struct {
    u8 b[4];
} W04Bytes4_q1;
typedef s16 Q1SpaceTriple[3];
typedef BranchLink Q1BranchPair[2];
typedef struct G3ModelFadeWork {
    /* 0x00 */ Vec vel;
    /* 0x0C */ f32 alpha;
    /* 0x10 */ f32 scaleRate;
    /* 0x14 */ f32 fadeRate;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 killOnFade;
} G3ModelFadeWork; // size 0x20
typedef struct G3ItemMoveWork {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 spriteGroup;
} G3ItemMoveWork; // size 0xC (allocated as 0x10)
/* Spark directions copied into a local array before each loop (an initialised local in the
   original; the table is D_8011DDE0_w04 in this unit's .data). */
typedef struct G3SparkDirs {
    Vec dir[8];
} G3SparkDirs;
typedef G3ModelFadeWork Q3ModelFadeWork;
typedef G3ItemMoveWork Q3ItemMoveWork;
typedef G3SparkDirs Q3SparkDirs;
typedef struct Q3ItemExchangeWork {
    Object* unk_00;
    Object* unk_04;
    s32 unk_08;
    s32 unk_0C;
    char unk_10[0x10];
} Q3ItemExchangeWork; // board g4
typedef W04Bytes4_q1 Q3Bytes4;
typedef Q1SpaceTriple Q3SpaceTriple;
typedef Q1BranchPair Q3BranchPair;

void func_801183D4_w04(void);
void func_801191B8_w04(void);
void func_8011A4E0_w04(s32 index);
extern Process *D_8011E038_w04;
extern s32 D_8011B790_w04[7];
extern s32 D_8011B7AC_w04[7];
extern Object *D_8011DFF8_w04[];
extern s32 D_8011B7C8_w04;
extern Unk3 *D_8011E040_w04;
extern Unk3 *D_8011E044_w04;
extern Unk3 *D_8011E048_w04;
extern Unk3 *D_8011E04C_w04;
extern Unk3 *D_8011E050_w04;
extern u8 D_8011DDD0_w04[4];
s32 func_8011B350_w04(void);
s32 func_8011B6B4_w04(void);
extern s32 D_8011E054_w04;
extern s32 D_8011E058_w04;
void func_8010DA1C_w04(void);
void func_8010EE9C_w04(void);
void func_8010F264_w04(void);
void func_8010F2D0_w04(void);
void func_80117800_w04(void);
void func_801104DC_w04(void);
void func_80110768_w04(void);
void func_8010F7C4_w04(void);
void func_8010FD34_w04(void);
void func_80110080_w04(void);
void func_80116AFC_w04(void);
void func_8011737C_w04(void);
void func_80110BB8_w04(void);
void func_80110E78_w04(void);
void func_80111218_w04(void);
void func_80111C14_w04(void);
void func_8011276C_w04(void);
void func_80113484_w04(void);
void func_80114720_w04(void);
void func_80115720_w04(void);
void func_8011694C_w04(void);
void func_80117244_w04(void);
s32 func_8011AD48_w04(void);
void func_80116640_w04(void);
void func_80107D70_w04(void);
void func_80107F3C_w04(void);
void func_80108200_w04(void);
void func_801083D4_w04(void);
void func_80108644_w04(void);
void func_801086C4_w04(void);
void func_8010886C_w04(void);
void func_80107828_w04(void);
extern Object *D_8011DFF0_w04;
extern Process *D_8011E018_w04[8];
extern s16 D_8011B7E4_w04[8][2];
extern s16 D_8011B82C_w04[8];
extern s16 D_8011B83C_w04[8];
extern Object *D_8011E05C_w04;
extern Object *D_8011E060_w04[1];
extern Object *D_8011E064_w04;
extern Object *D_8011E068_w04[];
extern s16 D_8011B804_w04[2][2];
extern s16 D_8011B84C_w04[2];
extern s16 D_8011B850_w04[2];
extern Vec D_8011B854_w04[5];
extern Vec D_8011B890_w04[5];
extern Object *D_8011E090_w04;
extern Object *D_8011E094_w04[];
extern s16 D_8011B8CC_w04[2];
extern s16 D_8011B8D0_w04[6];
extern u32 *D_8011B90C_w04[6];
extern s16 D_8011B824_w04[2][2];
extern s16 D_8011B81C_w04[2][2];
extern s32 D_8011B924_w04[9];
extern s32 D_8011B948_w04[9];
extern s32 D_8011B96C_w04[9];
extern s32 D_8011B990_w04[9];
extern s16 D_8011B9B4_w04[2];
extern s16 D_8011B80C_w04[2][2];
extern s16 D_8011B814_w04[2][2];
extern s16 D_8011B9B8_w04[2];
extern s16 D_8011B9BC_w04[4];
extern s16 D_8011B9C4_w04[4];
extern Object *D_8011E09C_w04[3];
extern s16 D_8011B7CC_w04[1];
extern s16 D_8011B7D0_w04[10];
extern event_table_entry D_8011C77C_w04[15];
extern event_table_entry D_8011C7F4_w04[2];
extern event_table_entry D_8011C988_w04[2];
extern event_table_entry D_8011C9C0_w04[43];
void func_8011A858_w04(void);
extern Object *D_8011E03C_w04;
void func_80116024_w04(Q3SpaceTriple *masu, Q3BranchPair *links, DecisionTreeNonLeafNode **trees);
extern s16 D_8011BFB8_w04[3][3];
extern BranchLink D_8011BFCC_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BA08_w04[3];
extern s16 D_8011C000_w04[3][3];
extern BranchLink D_8011C014_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BA68_w04[3];
extern s16 D_8011C048_w04[3][3];
extern BranchLink D_8011C05C_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BAEC_w04[3];
extern s16 D_8011C090_w04[3][3];
extern BranchLink D_8011C0A4_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BB40_w04[3];
extern s16 D_8011C0D8_w04[3][3];
extern BranchLink D_8011C0EC_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BBAC_w04[3];
extern s16 D_8011C120_w04[3][3];
extern BranchLink D_8011C134_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BC24_w04[3];
extern s16 D_8011C168_w04[3][3];
extern BranchLink D_8011C17C_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BC84_w04[3];
extern s16 D_8011C1B0_w04[3][3];
extern BranchLink D_8011C1C4_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BCF0_w04[3];
extern s16 D_8011C1F8_w04[3][3];
extern BranchLink D_8011C20C_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BD38_w04[3];
extern s16 D_8011C240_w04[3][3];
extern BranchLink D_8011C254_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BD68_w04[3];
extern s16 D_8011C288_w04[3][3];
extern BranchLink D_8011C29C_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BDE0_w04[3];
extern s16 D_8011C2D0_w04[3][3];
extern BranchLink D_8011C2E4_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BE28_w04[3];
extern s16 D_8011C318_w04[3][3];
extern BranchLink D_8011C32C_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BE88_w04[3];
extern s16 D_8011C360_w04[3][3];
extern BranchLink D_8011C374_w04[3][2];
extern DecisionTreeNonLeafNode *D_8011BF0C_w04[3];
extern s16 D_8011B740_w04[8];
extern s16 D_8011B750_w04[8];
extern s16 D_8011B760_w04[8];
extern s16 D_8011B770_w04[8];
extern s16 D_8011B780_w04[8];
extern s8 D_8011C550_w04[2][5][7];
extern s32 D_8011E0A8_w04;
extern s32 D_8011E0AC_w04;
extern u8 *D_8011E0B0_w04;
extern DecisionTreeNonLeafNode D_8011C508_w04[2];
extern u32 D_8011C520_w04[2];
extern char D_8011DDD4_w04[4];
void func_80112B48_w04(void);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8001ED54_main(s16 arg0);
extern u8 D_8011C538_w04[2][3][4];
extern u8 D_8011C598_w04[2][3][4];
extern s8 D_8011C5B0_w04[2][5][10];
extern u8 D_8011C614_w04[2][10];
extern s32 D_8011C628_w04[5][2];
extern s32 D_8011C650_w04[2];
extern s32 D_8011C658_w04[2];
extern s32 D_8011C660_w04[2];
extern s32 D_8011C668_w04[2];
extern s32 D_8011C670_w04[2];
extern u32 D_8011C678_w04[2];
extern u32 D_8011C680_w04[2];
extern s32 D_8011C688_w04;
extern Vec2f D_8011C69C_w04[4];
extern Vec2f D_8011C6BC_w04[4];
extern u8 D_8011C6DC_w04[6][3];
extern u8 D_8011C6F0_w04[14][3];
extern u8 D_8011C71C_w04[8];
extern s32 D_8011C724_w04[3];
extern s32 D_8011C730_w04[7];
extern Vec2f D_8011C804_w04[4];
extern Vec2f D_8011C824_w04[4];
extern const f64 D_8011DDD8_w04;
extern const G3SparkDirs D_8011DDE0_w04;
extern const f64 D_8011DE40_w04;
extern Object *D_8011E0B4_w04;
void func_80106A3C_w04(Object *arg);
void func_80106AB0_w04(void);
void func_80106B38_w04(void);
s32 func_80106CC4_w04(u8 *enabled);
s32 func_80106F58_w04(void);
s32 func_80107704_w04(u8 *enabled);
s32 func_80107724_w04(u8 *enabled);
void func_80108608_w04(s32 arg);
void func_80109CCC_w04(void);
void func_8010B024_w04(void);
void func_8010B1FC_w04(void);
void func_8010C4B4_w04(Object *obj);
void func_8010C554_w04(Object *obj);
s32 func_8010C5F4_w04(s32 playerIndex);
void func_8010CA3C_w04(void);
s32 func_8010CA60_w04(s32 playerIndex);
void func_8010D88C_w04(void);
void func_8010D9E0_w04(s32 arg);
void func_8010EBF0_w04(void);
void func_8010EC0C_w04(void);
omObjData *func_8010EC28_w04(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star);
void func_8010ED84_w04(omObjData *arg0);
void func_8010F490_w04(void);
Process *func_8010F6F4_w04(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010F9F4_w04(void);
void func_8010FBC4_w04(void);
void func_80110244_w04(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode);
void func_80112378_w04(void);
extern DecisionTreeNonLeafNode D_8011C884_w04[9];
extern s32 D_8011C8F0_w04[5];
extern DecisionTreeNonLeafNode D_8011C904_w04[1];
extern Vec2f D_8011C910_w04[6];
extern s32 D_8011C940_w04;
extern u8 D_8011C944_w04[4];
extern u8 D_8011C948_w04[4];
extern u16 D_8011C94C_w04[7][2];
extern RGB D_8011C968_w04[2];
extern s32 D_8011E0B8_w04;
extern s32 D_8011E0BC_w04;
extern s32 D_8011E0C0_w04;
extern Object* D_8011E0C4_w04;
extern Object* D_8011E0C8_w04;
extern s32 D_8011E0CC_w04;
extern s32 D_8011E0D0_w04;
extern Object* D_8011E0D4_w04;
extern s32 D_8011E0D8_w04[4];
extern void* D_8011E0E8_w04;
void func_80106B94_w04(void);
void func_80106C64_w04(void);
void func_80107F98_w04(void);
s32 func_80109CD4_w04(DecisionTreeNonLeafNode *tree, s32 count);
void func_80109F58_w04(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
void func_8010A014_w04(void);
void func_801109A8_w04(void);
void func_8011297C_w04(Object* arg0);
s32 func_80112F04_w04(u8 *arg0, s32 arg1);
extern Vec2f D_8011C844_w04[4];
extern Vec2f D_8011C864_w04[4];
extern Object *D_8011E0F0_w04[4];
extern omObjData *D_8011E100_w04[4];
extern s32 D_8011E110_w04;
extern s32 D_8011E114_w04;
void func_8011621C_w04(s32 arg0);
void func_80116294_w04(void);
void func_801162F8_w04(omObjData *obj);
void func_801164A4_w04(s32 arg0, s32 arg1);
void func_801165A4_w04(s32 arg);
void func_80116AAC_w04(void);
void func_80117074_w04(void);
extern RectF D_8011CB18_w04;
extern DecisionTreeNonLeafNode D_8011CF48_w04[9];
extern DecisionTreeNonLeafNode D_8011CFB4_w04[1];
extern DecisionTreeNonLeafNode D_8011D1D0_w04[9];
extern DecisionTreeNonLeafNode D_8011D314_w04[9];
extern DecisionTreeNonLeafNode D_8011D494_w04[13];
extern DecisionTreeNonLeafNode D_8011D530_w04[5];
extern DecisionTreeNonLeafNode *D_8011D65C_w04[8];
extern DecisionTreeNonLeafNode D_8011D838_w04[9];
extern DecisionTreeNonLeafNode *D_8011DAC0_w04[8];
extern DecisionTreeNonLeafNode *D_8011DAE0_w04[8];
extern DecisionTreeNonLeafNode D_8011DB00_w04[1];
extern s32 D_8011DC68_w04;
extern u8 *D_8011DCEC_w04[8];
extern s8 *D_8011DD8C_w04[8];
extern DecisionTreeNonLeafNode *D_8011DDAC_w04[2];
extern DecisionTreeNonLeafNode *D_8011DDB4_w04[2];
extern DecisionTreeNonLeafNode *D_8011DDBC_w04[5];
s32 func_8010AF34_w04(s32 arg0);
s32 func_8010AFBC_w04(void);
s32 func_8011AA64_w04(void);
s32 func_8011AB34_w04(void);
void func_80106120_w04(void);
extern s16 D_8011C998_w04[2];
extern s16 D_8011C99C_w04[2];
extern Object *D_8011E118_w04[2];
void func_800DC104_shared_board(s32 arg0, s8 arg1);
void func_8010873C_w04(void);
void func_800EC5B4_shared_board(s16 arg0, s32 arg1);
extern DecisionTreeNonLeafNode D_8011BF6C_w04[4];
extern DecisionTreeNonLeafNode D_8011BF9C_w04[1];
void func_80119FCC_w04(s32 index, s32 arg1);
void func_801088C8_w04(void);
void func_801088FC_w04(void);
void func_80108934_w04(void);
void func_801089B0_w04(void);
void func_80108A58_w04(void);
void func_80108AD4_w04(void);
void func_80108B4C_w04(void);
void func_80108C00_w04(void);
void func_80108CA8_w04(void);
void func_80108D00_w04(void);
void func_80108D58_w04(void);
void func_80108DB0_w04(void);
void func_80108E08_w04(void);
void func_80108E60_w04(void);
void func_80108EB8_w04(void);
void func_80108F10_w04(void);
void func_80108F70_w04(void);
void func_80108FD0_w04(void);
void func_80109030_w04(void);
void func_80109090_w04(void);
void func_801090F0_w04(void);
void func_80109150_w04(void);
void func_801091B0_w04(void);
void func_80109210_w04(void);
void func_80109270_w04(void);
void func_801092D0_w04(void);
void func_80109330_w04(void);
void func_80109390_w04(void);
void func_801093F0_w04(void);
void func_80109450_w04(void);
void func_801094B0_w04(void);
void func_80109510_w04(void);
void func_80109570_w04(void);
void func_801095D0_w04(void);
void func_80109630_w04(void);
void func_801098A0_w04(void);
void func_8010A054_w04(void);
void func_8010A400_w04(void);
void func_80116740_w04(void);
void func_8011A5DC_w04(void);
void func_8011A91C_w04(void);


s16 func_801059D0_w04(void) {
    return D_8011B780_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w04(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011B750_w04[idx2]) {
                continue;
            }
            if (idx2 < D_8011B750_w04[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011B740_w04[idx1];
                D_8011B740_w04[idx1] = D_8011B740_w04[idx2];
                D_8011B740_w04[idx2] = temp;
                temp = D_8011B750_w04[idx1];
                D_8011B750_w04[idx1] = D_8011B750_w04[idx2];
                D_8011B750_w04[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011B740_w04[i];
    }
}

void func_80105B00_w04(void) {
    GW_SYSTEM *loc;
    s32 last;
    s32 first;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        last = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w04();
        first = loc->star_spawn_indices[0];
        if ((last ^ first) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = first;
        }
    }
}

void func_80105B8C_w04(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011B760_w04[i]);
    }
    MBMasuTypeSet(D_8011B770_w04[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011B760_w04[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s32 func_80105C30_w04(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011B770_w04[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011B760_w04[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void func_80105CA4_w04(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011E03C_w04 = MBModelCreate(0x3A, NULL);
    model = D_8011E03C_w04;
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
    D_8011E038_w04 = NULL;
    omDelPrcObj(NULL);
}

void func_80106094_w04(omObjData **arg) {
    omObjData *s0 = *arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

void func_80106120_w04(void) {
    struct UnkMBGuideData *data;
    GW_SYSTEM *loc = &GwSystem;
    SpaceData *space;
    s32 idx;

    D_800A12D4_main = 0;
    data = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(data->obj, 2, 0xF, D_8011B790_w04[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(D_8011DFF8_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w04((omObjData **)data);
    func_8005B43C_main(
        data->amount,
        (loc->current_star_spawn == 0 && GWBoardFlagCheck(4) == 0)
            ? (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E00)
            : (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E01),
        -1, -1);
    func_80060C14_main(data->amount, 1);
    HuAudFXPlay(0x2A7);
    func_800EE2C0_shared_board(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    func_80060EA8_main(data->amount, 1);
    func_8001FDE8_main(data->obj->omObj1->model[0]);
    if (loc->current_board_index != 2 || (rand8() & 1)) {
        space = MBMasuGet(D_8011B780_w04[loc->star_spawn_indices[loc->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    idx = MBRand(7.0f);
    MBGuideFaceSet(data->obj, D_8011B790_w04[idx]);
    MBMotionSet(data->obj, -1, 2);
    if (loc->current_board_index != 2) {
        Process *prc = omAddPrcObj(func_80105CA4_w04, 0x4800, 0, 0);
        D_8011E038_w04 = prc;
        prc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_8011E038_w04 = NULL;
    }
    func_8005B43C_main(data->amount, D_8011B7AC_w04[idx], -1, -1);
    func_80060C14_main(data->amount, 1);
    func_800EE2C0_shared_board(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    func_80060EA8_main(data->amount, 1);
    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011E03C_w04->omObj1->model[0]);
    MBModelKill(D_8011E03C_w04);
    MBModelDispOn(D_8011DFF8_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBGuideKill(data);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void func_801064DC_w04(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8D) {
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
    if (D_8011B7C8_w04 != 0) {
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
    if (D_8011B7C8_w04 != 0) {
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

void func_80106A3C_w04(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w04, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106AB0_w04(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106B38_w04(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106B94_w04(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011E040_w04 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011E044_w04 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011E050_w04 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011E048_w04 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011E04C_w04 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106C64_w04(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011E040_w04);
    MBHelpWinKill(D_8011E044_w04);
    MBHelpWinKill(D_8011E050_w04);
    MBHelpWinKill(D_8011E048_w04);
    MBHelpWinKill(D_8011E04C_w04);
}

s32 func_80106CC4_w04(u8 *enabled) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = *(W04Bytes4_q1 *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = func_8011B350_w04();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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
        if (enabled[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (TRUE) {
        i = func_8005E1D8_main(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
        if (enabled[i] != 0) {
            return i;
        }
    }
}

s32 func_80106F58_w04(void) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = *(W04Bytes4_q1 *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = func_8011B6B4_w04();
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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

void func_80107170_w04(void) {
    s32 cur = GwSystem.current_player_index;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != MB_MAX_PLAYERS && GwPlayer[cur].coin >= 50 && MBRand(100.0f) < GwPlayer[cur].coin + 10) {
        D_8011E054_w04 = 1;
        if (GwPlayer[cur].star < 99) {
            return;
        }
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != MB_MAX_PLAYERS) {
        D_8011E054_w04 = 0;
    } else {
        D_8011E054_w04 = 2;
    }
}

void func_801072A0_w04(void) {
    s32 order[MB_MAX_PLAYERS];
    s32 cur = GwSystem.current_player_index;
    s32 i;
    s32 rank;
    s32 player;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        order[i] = -1;
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        rank = MBPlayerStealRankGet(i);
        while (TRUE) {
            if (order[rank] == -1) {
                break;
            }
            rank++;
        }
        order[rank] = i;
    }
    func_80107170_w04();
    if (D_8011E054_w04 == 1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = order[i];
            if (player != cur && GwPlayer[player].star != 0) {
                D_8011E058_w04 = player;
                break;
            }
        }
    } else if (D_8011E054_w04 == 0) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = order[i];
            if (player != cur && GwPlayer[player].coin >= 5) {
                D_8011E058_w04 = player;
                break;
            }
        }
    }
    if (i == MB_MAX_PLAYERS) {
        D_8011E054_w04 = 2;
    }
}

s32 func_80107438_w04(u8 *enabled, s32 targetSet, s32 canCancel) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = *(W04Bytes4_q1 *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (targetSet == 0) {
                    func_801072A0_w04();
                    comCount = D_8011E054_w04 + 1;
                } else {
                    comCount = D_8011E058_w04 + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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
        if (enabled[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (TRUE) {
        i = func_8005E1D8_main(mbDlgWinId, i, canCancel);
        if (canCancel == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (enabled[i] != 0) {
            return i;
        }
    }
}

s32 func_80107704_w04(u8 *enabled) {
    return func_80107438_w04(enabled, 0, 1);
}

s32 func_80107724_w04(u8 *enabled) {
    return func_80107438_w04(enabled, 1, 0);
}

void func_80107744_w04(void) {
    GwSystem.current_board_index = 3;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80107780_w04(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w04();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 1;
    GwSystem.boardData.halfWordBytes[1] = 1;
    GwSystem.boardData.halfWordBytes[2] = 1;
    GwSystem.boardData.halfWordBytes[3] = 0;
    GwSystem.boardData.halfWordBytes[4] = 0;
    omOvlReturnEx(1);
}

void func_80107828_w04(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(0xC, 0x23D, 0xE, 0);
    MBMasuBlockTblExtSet(D_8011B7CC_w04);
    MBMasuBlockTblSet(D_8011B7D0_w04);
    space = MBMasuGet(0x71);
    MBVecDirGet(&space->coords, &MBMasuGet(0x75)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x8C);
    MBVecDirGet(&space->coords, &MBMasuGet(0x76)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &func_8010DA1C_w04);
    MBItemHookSet(1, &func_8010EE9C_w04);
    MBItemHookSet(9, &func_8010F264_w04);
    MBItemHookSet(2, &func_8010F2D0_w04);
    MBItemHookSet(3, &func_80117800_w04);
    MBItemHookSet(4, &func_801104DC_w04);
    MBItemHookSet(5, &func_80110768_w04);
    MBItemHookSet(6, &func_8010F7C4_w04);
    MBItemHookSet(7, &func_8010FD34_w04);
    MBItemHookSet(8, &func_80110080_w04);
    MBItemHookSet(0xA, &func_80116AFC_w04);
    MBItemHookSet(0xB, &func_8011737C_w04);
    MBItemHookSet(0xE, &func_80110BB8_w04);
    MBItemHookSet(0xF, &func_80110E78_w04);
    MBItemHookSet(0x10, &func_80111218_w04);
    MBItemHookSet(0x11, &func_80111C14_w04);
    MBItemHookSet(0x12, &func_8011276C_w04);
    MBItemHookSet(0x13, &func_80113484_w04);
    MBItemHookSet(0x14, &func_80114720_w04);
    MBItemHookSet(0x15, &func_80115720_w04);
    MBItemHookSet(0xC, &func_8011694C_w04);
    MBItemHookSet(0xD, &func_80117244_w04);
    MBComItemDecideHookSet(func_8011AD48_w04);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011B780_w04[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B00_w04();
    }

    func_80105B8C_w04();
    func_80107D70_w04();
    func_80107F3C_w04();
    func_80108200_w04();
    func_801083D4_w04();
    func_80108644_w04();
    func_801086C4_w04();
    func_8010886C_w04();
    func_80116640_w04();
    func_800EBDAC_shared_board();
}

void func_80107B34_w04(void) {
    HuAudSeqPlay(0x1B);
    D_800CE198_main = 0x1B;
    func_800F8D6C_shared_board(0x1B);
    Hu3DCamInit(2);
    func_80107828_w04();
    MBMasuEventTblAdd(D_8011C77C_w04);
    MBMasuEventTblAdd(D_8011C9C0_w04);
    MBHatenaFuncSet(&func_8011A858_w04);
    MBMasuEventTblAdd(D_8011C7F4_w04);
    MBMasuEventTblAdd(D_8011C988_w04);
    MBStart(0);
}

void func_80107BB8_w04(void) {
    Hu3DCamInit(1);
    func_80107828_w04();
    MBStart(1);
}

void func_80107BE4_w04(s16 arg0) {
    Object *obj;

    if (D_8011DFF8_w04[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011DFF0_w04 == NULL) {
        D_8011DFF0_w04 = obj;
    }
    D_8011DFF8_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011E018_w04[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B82C_w04[arg0])->coords);
    func_800D771C_shared_board(0xB, obj, D_8011B7E4_w04[arg0][0], D_8011B7E4_w04[arg0][1]);
}

void func_80107D0C_w04(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_8011E018_w04[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_8011E018_w04[i] = NULL;
        }
    }
}

void func_80107D70_w04(void) {
    s32 i;

    D_8011DFF0_w04 = 0;
    for (i = 0; i < 8; i++) {
        D_8011DFF8_w04[i] = 0;
        D_8011E018_w04[i] = NULL;
        MBKinokoEffKillHookSet(func_80107D0C_w04);
        if (!GWBoardFlagCheck(D_8011B83C_w04[i])) {
            func_80107BE4_w04(i);
        }
    }
}

void func_80107E1C_w04(s16 arg0) {
    Object *obj;

    if (D_8011E060_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E05C_w04 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011E05C_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E05C_w04);
    }
    MBModelDispOff(obj);
    D_8011E060_w04[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B84C_w04[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011B804_w04[arg0][0], D_8011B804_w04[arg0][1]);
}

void func_80107F3C_w04(void) {
    s32 i;

    D_8011E05C_w04 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011E060_w04[i] = NULL;
        func_80107E1C_w04(i);
    }
}

void func_80107F98_w04(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011E068_w04[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011E068_w04[i * 5 + j]);
        }
    }
}

void func_80108094_w04(s16 arg0) {
    Object *obj;

    if (D_8011E068_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E064_w04 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011E064_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E064_w04);
    }
    D_8011E068_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B850_w04[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011B854_w04[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011B890_w04[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011B890_w04[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_80108200_w04(void) {
    s32 i;

    D_8011E064_w04 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011E068_w04[i] = NULL;
        func_80108094_w04(i);
    }
    func_80107F98_w04();
}

void func_80108268_w04(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011E094_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E090_w04 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011B8D0_w04[board], D_8011B90C_w04[board]);
        MBModelTempAllocFree(obj);
        D_8011E090_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E090_w04);
    }
    D_8011E094_w04[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B8CC_w04[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011B824_w04[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011B824_w04[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011B81C_w04[arg0][0], D_8011B81C_w04[arg0][1]);
}

void func_801083D4_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        D_8011E094_w04[i] = NULL;
        func_80108268_w04(i);
    }
}

void func_80108434_w04(void) {
    HuPrcSleep(D_8011B96C_w04[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011B948_w04[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_80108490_w04(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011E094_w04[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011E094_w04[arg0]->omObj1->model[0], 5, 0);
    if (D_8011B924_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B924_w04[GwSystem.current_board_index]);
    }

    if (D_8011B948_w04[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108434_w04, 0x1000, 0, 0);
    }
}

void func_80108558_w04(void) {
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
    func_8001C814_main(D_8011E094_w04[index]->omObj1->model[0], 1, 4);

    if (D_8011B990_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B990_w04[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_80108608_w04(s32 arg) {
    Process *temp = omAddPrcObj(func_80108558_w04, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_80108644_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011B9B4_w04[i])->coords,
                                         D_8011B80C_w04[i][0], D_8011B80C_w04[i][1]);
    }
}

void func_801086C4_w04(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011B9B8_w04[i])->coords,
                                         D_8011B814_w04[i][0], D_8011B814_w04[i][1]);
    }
}

void func_8010873C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (GwSystem.boardData.halfWordBytes[D_8011B9C4_w04[i]] == 0) {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = -1.0f;
        } else {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = 1.0f;
        }
    }
}

void func_801087CC_w04(s32 arg0) {
    Object *obj;

    if (D_8011E09C_w04[arg0] != NULL) {
        return;
    }
    obj = MBModelFileCreate(0x130177, 0, 3.0f, 0, 0);
    MBModelTempAllocFree(obj);
    D_8011E09C_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B9BC_w04[arg0])->coords);
}

void func_8010886C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8011E09C_w04[i] = NULL;
        func_801087CC_w04(i);
    }
    func_8010873C_w04();
}

void func_801088C8_w04(void) {
    MBMoveNextMasuSet(CUR_PLAYER, 1, 0x15);
    MBMoveBackMasuSet(CUR_PLAYER, 1, 0x15);
}

void func_801088FC_w04(void) {
    func_80116024_w04(D_8011BFB8_w04, D_8011BFCC_w04, D_8011BA08_w04);
    omDelPrcObj(NULL);
}

void func_80108934_w04(void) {
    if (MBPlayerGet(CUR_PLAYER)->rev & 0x80) {
        func_80116024_w04(D_8011C000_w04, D_8011C014_w04, D_8011BA68_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[0] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 4, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 9, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801089B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5C && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(CUR_PLAYER, 6, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C048_w04, D_8011C05C_w04, D_8011BAEC_w04);
    }
}

void func_80108A58_w04(void) {
    if (MBPlayerGet(CUR_PLAYER)->rev & 0x80) {
        func_80116024_w04(D_8011C090_w04, D_8011C0A4_w04, D_8011BB40_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[1] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 7, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 8, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_80108AD4_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(CUR_PLAYER, 9, 5);
        player->rev |= 1;
    } else {
        func_80116024_w04(D_8011C0D8_w04, D_8011C0EC_w04, D_8011BBAC_w04);
    }
    omDelPrcObj(NULL);
}

void func_80108B4C_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 3);
        player->rev |= 1;
    } else if (player->rev & 0x80) {
        func_80116024_w04(D_8011C120_w04, D_8011C134_w04, D_8011BC24_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[2] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 0xC, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_80108C00_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x39 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(CUR_PLAYER, 1, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C168_w04, D_8011C17C_w04, D_8011BC84_w04);
    }
}

void func_80108CA8_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C1B0_w04, D_8011C1C4_w04, D_8011BCF0_w04);
    }
}

void func_80108D00_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C1F8_w04, D_8011C20C_w04, D_8011BD38_w04);
    }
}

void func_80108D58_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C240_w04, D_8011C254_w04, D_8011BD68_w04);
    }
}

void func_80108DB0_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C288_w04, D_8011C29C_w04, D_8011BDE0_w04);
    }
}

void func_80108E08_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C2D0_w04, D_8011C2E4_w04, D_8011BE28_w04);
    }
}

void func_80108E60_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C318_w04, D_8011C32C_w04, D_8011BE88_w04);
    }
}

void func_80108EB8_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C360_w04, D_8011C374_w04, D_8011BF0C_w04);
    }
}

void func_80108F10_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x28) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0xB);
    }
}

void func_80108F70_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5B) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x19);
    }
}

void func_80108FD0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x41) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x19);
    }
}

void func_80109030_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x57) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x12);
    }
}

void func_80109090_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x51) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x7);
    }
}

void func_801090F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x70) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x4, 0x4);
    }
}

void func_80109150_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xC) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x4, 0x4);
    }
}

void func_801091B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x9) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x6, 0x2);
    }
}

void func_80109210_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x9) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0xE);
    }
}

void func_80109270_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xE) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x6, 0x2);
    }
}

void func_801092D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x10) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xC, 0x7);
    }
}

void func_80109330_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4D) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x7);
    }
}

void func_80109390_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x9, 0x6);
    }
}

void func_801093F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x58) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x4);
    }
}

void func_80109450_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3D) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x9, 0x6);
    }
}

void func_801094B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x19) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 0x4);
    }
}

void func_80109510_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x37) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x5);
    }
}

void func_80109570_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x1C) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 0x4);
    }
}

void func_801095D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3A) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0xB);
    }
}

void func_80109630_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x66) {
        MBMoveBackMasuSet(CUR_PLAYER, 0x1, 0x14);
    }
}

s32 func_80109690_w04(s32 arg0) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = *(W04Bytes4_q1 *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = 1;
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_801098A0_w04(void) {
    GW_SYSTEM *loc;
    GW_PLAYER *player;
    s32 flag;
    s32 choice;
    void *prc;
    s16 sp18;
    s16 masuId;

    loc = &GwSystem;
    player = MBPlayerGet(GwSystem.current_player_index);
    flag = 1;

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6F) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6A) {
            if (MBItemFind(GwSystem.current_player_index, 1) != -1) {
                func_800DBEC0_shared_board(GwSystem.current_player_index);
                MBPlayerMotionSet(-1, -1, 2);
                sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (sp18) {
                    case 0x70:
                    case 0x88:
                        func_800ED20C_shared_board(-1, 8, 0x6F);
                        break;
                    default:
                        func_800ED20C_shared_board(-1, 8, 0x6A);
                        break;
                }
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
                HuPrcChildWait();
                MBPlayerVibrate(-1, 1);

                while (1) {
                    MBDlgWinCreate(0x38, 0x4103);
                    choice = func_80109690_w04(0);
                    MBDlgWinClose();
                    MBDlgWinKill();

                    switch (choice) {
                        case 0:
                            MBDlgWinExec(0x38, 0x4104);
                            GwPlayer[loc->current_player_index].itemNo[MBItemFind(loc->current_player_index, 1)] = -1;
                            MBItemRemoveEmpty(GwSystem.current_player_index);
                            MBStatusItemIconSprReinit(-1);
                            sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                            switch (sp18) {
                                case 0x70:
                                    func_80108490_w04(0, 0);
                                    break;
                                case 0x88:
                                    func_80108490_w04(0, 1);
                                    break;
                                case 0x69:
                                    func_80108490_w04(1, 0);
                                    break;
                                default:
                                    func_80108490_w04(1, 1);
                                    break;
                            }
                            flag = 0;
                            prc = MBPlayerVibrateObjCreate(-1, 2, 5);
                            HuPrcSleep(0x14);
                            MBPlayerVibrateObjKill(prc);
                            break;
                        case 1:
                            MBDlgWinExec(0x38, 0x4105);
                            break;
                        case 2:
                            func_80106AB0_w04();
                            continue;
                        default:
                            break;
                    }
                    break;
                }

                func_800DB884_shared_board(loc->current_player_index);
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                HuPrcChildWait();
            } else {
                MBDlgWinExec(-1, 0x4106);
            }
        }
    }

    if (flag != 0) {
        masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        switch (masuId) {
            case 0x70:
                MBMoveNextMasuSet(-1, 5, 0);
                player->rev |= 1;
                break;
            case 0x88:
                MBMoveNextMasuSet(-1, 3, 2);
                player->rev &= ~1;
                break;
            case 0x69:
                MBMoveNextMasuSet(-1, 0xE, 1);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xC, 2);
                player->rev &= ~1;
                break;
        }
    }

    omDelPrcObj(NULL);
}

void func_80109CBC_w04(void) {
}

void func_80109CC4_w04(void) {
}

void func_80109CCC_w04(void) {
}

s32 func_80109CD4_w04(DecisionTreeNonLeafNode *tree, s32 count) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = *(W04Bytes4_q1 *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch ((s32)tree) {
                    case 0:
                        comCount = func_800EF0D8_shared_board(0) + 1;
                        break;
                    case 1:
                        comCount = func_800EF0D8_shared_board(1) + 1;
                        break;
                    case 2:
                        comCount = count + 1;
                        break;
                    default:
                        comCount = MBComTreeExec(tree) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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

void func_80109F58_w04(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void func_8010A014_w04(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_8010A054_w04(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105C30_w04(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w04());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
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
                choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)2, 0);
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
                        func_80106A3C_w04(D_8011DFF0_w04);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        func_80109CC4_w04();
                        return;
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
                        func_80109CC4_w04();
                        return;
                    case 2:
                        func_80106AB0_w04();
                        goto purchaseMenu;
                    default:
                        func_80109CC4_w04();
                        return;
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

    func_80109CC4_w04();
}

void func_8010A400_w04(void) {
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
        case 0x3D:
            func_800ED20C_shared_board(-1, 8, 0x77);
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x3D);
            break;
        case 6:
            func_800ED20C_shared_board(-1, 8, 0x6D);
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(6);
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

    effectModel = MBModelCreate(0x35, D_8011C520_w04);
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
        choice = func_80109CD4_w04(D_8011C508_w04, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106AB0_w04();
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
        sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
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
            func_80112B48_w04();
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
                sprintf(sp20, D_8011DDD4_w04, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011DDD4_w04, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80107F98_w04();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80107F98_w04();
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
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80107F98_w04();
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
    func_80109CBC_w04();
}

s32 func_8010AF34_w04(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011E0B0_w04[i] != 0) {
            if (D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010AFBC_w04(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010B024_w04(void) {
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

    for (; angle < 360.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010B1FC_w04(void) {
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
        case 0x71:
            camMasu = 0x75;
            spaceA = MBMasuGet(0x75);
            spaceB = MBMasuGet(0x71);
            D_8011C688_w04 = 0;
            break;
        case 0x8C:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x8C);
            D_8011C688_w04 = 1;
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
            effectModel = MBModelCreate(0x39, D_8011C680_w04);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011C678_w04);
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
        MBDlgWinExec(dlgWin, D_8011C668_w04[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011C660_w04[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011C658_w04[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011C650_w04[shopIdx]);
    choice = func_80106F58_w04();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011C538_w04[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011C550_w04[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011C550_w04[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, D_8011C628_w04[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011E0A8_w04 = slot;
            D_8011E0AC_w04 = row;
            D_8011E0B0_w04 = enabled;
            sel = func_80106CC4_w04(enabled);
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
            shopTable = D_8011C550_w04;
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
                    D_8011C550_w04[shopIdx][row][sel];
                item = D_8011C550_w04[shopIdx][row][sel];
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

            if (D_8011C550_w04[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011C598_w04[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011C5B0_w04[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011C614_w04[shopIdx][i];

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
                    prc = omAddPrcObj(func_8010B024_w04, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, D_8011C670_w04[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106B38_w04();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w04();
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

void func_8010C4B4_w04(Object *obj) {
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

void func_8010C554_w04(Object *obj) {
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

s32 func_8010C5F4_w04(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011C69C_w04[playerIndex].x,
                        D_8011C69C_w04[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011C6BC_w04[playerIndex].x) +
                                D_8011C69C_w04[playerIndex].x,
                            (i * D_8011C6BC_w04[playerIndex].y) +
                                D_8011C69C_w04[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
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
                            (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                                D_8011C69C_w04[playerIndex].x,
                            (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                                D_8011C69C_w04[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011C6BC_w04[playerIndex].x) +
                                D_8011C69C_w04[playerIndex].x,
                            (i * D_8011C6BC_w04[playerIndex].y) +
                                D_8011C69C_w04[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010CA3C_w04(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010CA60_w04(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011C69C_w04[playerIndex].x,
                        D_8011C69C_w04[playerIndex].y);
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
                            D_8011C69C_w04[playerIndex].x -
                                (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                            D_8011C69C_w04[playerIndex].y +
                                (D_8011C6BC_w04[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
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
            omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
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
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
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
                            playerGrp, 0, D_8011C69C_w04[playerIndex].x - 8.0f,
                            (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                                D_8011C69C_w04[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x -
                        (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x - 8.0f,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(D_8011C6DC_w04); i++) {
            if ((GwSystem.current_turn >= D_8011C6DC_w04[i][0]) &&
                (GwSystem.current_turn <= D_8011C6DC_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011C6DC_w04[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011C6F0_w04); i++) {
            if ((attempts >= D_8011C6F0_w04[i][0]) &&
                (attempts <= D_8011C6F0_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011C6F0_w04[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void func_8010D88C_w04(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011E0B4_w04);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += D_8011DDD8_w04; // 1.5 (a const double in .data)
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_8010D9E0_w04(s32 arg) {
    Process *temp = omAddPrcObj(func_8010D88C_w04, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_8010DA1C_w04(void) {
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
    if (spaceId != 0x8D) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011E05C_w04);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x7D;
        space = MBMasuGet(0x7D);
        boo = D_8011E060_w04[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011C730_w04[sys->current_board_index] != 0) {
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
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011C730_w04[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C4B4_w04(boo);
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
    menuResult = func_80107704_w04(choices);
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
    playerChoice = func_80107724_w04(choices);
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
                func_80106B38_w04();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w04();
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
        if (rank < D_8011C724_w04[i]) {
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
            if (GwSystem.current_turn >= D_8011C6DC_w04[i][0] &&
                GwSystem.current_turn <= D_8011C6DC_w04[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011C6DC_w04[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010C554_w04(boo);
    if (menu == 0) {
        resultAmount = func_8010CA60_w04(target);
        func_8010C4B4_w04(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011C71C_w04[i]) {
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
            D_8011E0B4_w04 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011E0B4_w04);
            MBModelDispOff(D_8011E0B4_w04);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010D9E0_w04((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011E0B4_w04);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010C5F4_w04(target);
        func_8010C4B4_w04(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011B7C8_w04 = 1;
            func_80106A3C_w04(boo);
            D_8011B7C8_w04 = 0;
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
    func_8010C554_w04(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106B38_w04();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106AB0_w04();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010C554_w04(boo);
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
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
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
    func_80109CCC_w04();
}

void func_8010EBF0_w04(void) {
    func_80108608_w04(0);
}

void func_8010EC0C_w04(void) {
    func_80108608_w04(1);
}

omObjData *func_8010EC28_w04(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star) {
    omObjData *obj;
    G3ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010ED84_w04);
    data = obj->data = HuMemAllocTag(sizeof(G3ModelFadeWork), 0x7918);
    data->alpha = 255.0f;
    data->scaleRate = scaleRate;
    data->fadeRate = fadeRate;
    HuVecCopy3F(&data->vel, vel);
    if (star != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = pos->x;
    model->coords.y = pos->y;
    model->coords.z = pos->z;
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->killOnFade = killOnFade;
    return obj;
}

void func_8010ED84_w04(omObjData *arg0) {
    G3ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->vel);
    scale = model->scale.z + data->scaleRate;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->alpha - data->fadeRate;
    data->alpha = alpha;
    if (alpha < 0.0f) {
        data->alpha = 0.0f;
        if (data->killOnFade != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, 8);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->alpha);
}

void func_8010EE9C_w04(void) {
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
    func_8010F9F4_w04();
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
        G3SparkDirs particleDir = D_8011DDE0_w04;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir.dir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011B770_w04[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
        G3SparkDirs particleDir2 = D_8011DDE0_w04;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir2.dir[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010F264_w04(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011B770_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010F2D0_w04(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9F4_w04();
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

void func_8010F490_w04(void) {
    Process *process = HuPrcCurrentGet();
    G3ItemMoveWork *work = process->user_data;
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

Process *func_8010F6F4_w04(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration) {
    Process *process;
    G3ItemMoveWork *work;

    process = omAddPrcObj(func_8010F490_w04, 0x4002, 0, 0x40);
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

void func_8010F7C4_w04(void) {
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
    HuPrcChildLink(process, func_8010F6F4_w04(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011C804_w04[system->current_player_index].x,
                                D_8011C804_w04[system->current_player_index].y, -1));
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

void func_8010F9F4_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010F6F4_w04(
        mbItemCursorGrpId, position[0], position[1],
        D_8011C824_w04[system->current_player_index].x,
        D_8011C824_w04[system->current_player_index].y, -1);
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

void func_8010FBC4_w04(void) {
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
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010FD34_w04(void) {
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
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            D_8011C804_w04[system->current_player_index].x,
                                            D_8011C804_w04[system->current_player_index].y, -1));
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

void func_80110080_w04(void) {
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
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            D_8011C804_w04[system->current_player_index].x,
                                            D_8011C804_w04[system->current_player_index].y, -1));
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

void func_80110244_w04(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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
                                 (f32)((f64)scale + D_8011DE40_w04));
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

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE40_w04);

void func_801104DC_w04(void) {
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

void func_80110768_w04(void) {
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

void func_801109A8_w04(void) {
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
    func_80055024_main(group, 0, D_8011E0B8_w04, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    func_80054904_main(group, 0, x, y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011C8F0_w04[index];
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

void func_80110BB8_w04(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011E0B8_w04 = func_80055810_main(data);
    DataClose(data);
    func_80110080_w04();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_80109CD4_w04(D_8011C884_w04, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
                omPrcSetStatBit(process, 0x80);
                func_80106B38_w04();
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

        process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
        omPrcSetStatBit(process, 0x80);
        func_80106B38_w04();
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
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
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
    HuSprKill(D_8011E0B8_w04);
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
    func_8010B1FC_w04();
    GwSystem.forceShopHost = 0;
}

void func_80110E78_w04(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011E0B8_w04 = func_80055810_main(data);
    DataClose(data);
    func_80110080_w04();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
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
        choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)1, 0);
    } else {
        choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
            omPrcSetStatBit(process, 0x80);
            func_80106B38_w04();
            one = 1;
            D_800CB99C_main = one;
            func_80049FB8_main();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B, mbCharNameMesTbl[GwPlayer[choice].chr], 0, 0, 0, 0);
            break;
    }
    MBDlgWinClose();
    MBDlgWinKill();

    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011E0B8_w04);

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

void func_80111218_w04(void) {
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
        func_8010F9F4_w04();

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
        Q3SparkDirs velocities = D_8011DDE0_w04;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &velocities.dir[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        Q3SparkDirs velocities2 = D_8011DDE0_w04;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &velocities2.dir[(i / 2) & 7], 1);
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

        space = MBMasuGet(D_8011B770_w04[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011B780_w04[system->star_spawn_indices[system->current_star_spawn]]);
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
        if (D_8011E018_w04[j] != NULL) {
            omDelPrcObj(D_8011E018_w04[j]);
            D_8011E018_w04[j] = NULL;
        }
    }

    targetStar = D_8011DFF8_w04[system->star_spawn_indices[system->current_star_spawn]];
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

void func_80111C14_w04(void) {
    f32 sp20[2];
    Process *proc;
    void *file;
    s32 grpId;
    s32 sprId;
    s32 ret;
    s32 i;
    GW_SYSTEM* system = &GwSystem;
    s32 curPlayer = GwSystem.current_player_index;

    grpId = HuSprGrpCreate(1, 0);
    file = DataRead(D_8010197C_shared_board[1]);
    sprId = func_80055810_main(file);
    DataClose(file);
    func_80055024_main(grpId, 0, sprId, 0);
    HuSprPriSet(grpId, 0, 0x4780);
    HuSprAttrSet(grpId, 0, 0x9000);

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp20[0], &sp20[1]);

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc,
        func_8010F6F4_w04(mbItemCursorGrpId, sp20[0], sp20[1],
                             D_8011C804_w04[system->current_player_index].x,
                             D_8011C804_w04[system->current_player_index].y,
                             -1));
    HuPrcChildWait();
    HuPrcSleep(0xA);

    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 0xA; i++, HuPrcVSleep()) {
        func_80055458_main(mbItemCursorGrpId, 0, (255 - (i * 25)));
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);

    GwPlayer[curPlayer].itemNo[MBItemSelNoGet()] = ITEM_NONE;
    MBStatusItemTPLvlSet(curPlayer, MBItemSelNoGet(), 0);
    func_800F6848_shared_board(curPlayer, MBItemSelNoGet(), &sp20[0], &sp20[1]);
    func_80054904_main(grpId, 0, sp20[0], sp20[1]);
    HuSprAttrReset(grpId, 0, 0x8000);
    MBItemRemoveEmpty(curPlayer);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

choiceLoop:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    ret = func_80109CD4_w04(D_8011C904_w04, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch (ret) {
    case 0:
        MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
        break;
    case 1:
        MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
        HuSprAttrSet(grpId, 0, 0x8000);
        GwPlayer[curPlayer].itemNo[MBItemFindEmpty(curPlayer)] = ITEM_SKELETON_KEY;
        MBItemRemoveEmpty(curPlayer);
        GwSystem.cur_player_used_item &= ~1;
        break;
    default:
        HuSprAttrSet(grpId, 0, 0x8000);
        func_80106B38_w04();
        D_800CB99C_main = 1;
        func_80049FB8_main();
        HuSprAttrReset(grpId, 0, 0x8000);
        goto choiceLoop;
    }

    MBDlgWinClose();
    MBDlgWinKill();

    if (ret == 0) {
        HuPrcSleep(0xA);
        for (i = 1; i < 0x40; i++, HuPrcVSleep()) {
            func_80055458_main(grpId, 0, 255.0f - (i * 3.984f));
        }
        func_80055458_main(grpId, 0, 0);
    }

    HuSprGrpKill(grpId);
    HuSprKill(sprId);
}

void func_8011215C_w04(void) {
    s32 x;
    s32 y;
    s32 grpId;
    s32 idx;
    f32 scale;
    s32 alpha;

    idx = (s32)HuPrcCurrentGet()->user_data;

    grpId = HuSprGrpCreate(1, 0);
    func_80055024_main(grpId, 0, D_8011E0C0_w04, 0);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, 0x1000);

    MBStatusItemPosGet(D_8011E0BC_w04, 0, &x, &y);
    x = (D_8011C6BC_w04[D_8011E0BC_w04].x * 16.0f) +
         D_8011C69C_w04[D_8011E0BC_w04].x;
    y = (D_8011C6BC_w04[D_8011E0BC_w04].y * 16.0f) +
         D_8011C69C_w04[D_8011E0BC_w04].y;

    func_80054904_main(grpId, 0,
                        x + D_8011C910_w04[idx].x,
                        y + D_8011C910_w04[idx].y);
    func_80055420_main(grpId, 0, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grpId, 0, 0xFF);

    for (scale = 0.0f, alpha = 0xFF; alpha >= 0; alpha -= 0xA, scale += 0.1f) {
        HuSprScaleSet(grpId, 0, scale, scale);
        func_80055458_main(grpId, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(grpId, 0, 0);
    HuSprGrpKill(grpId);
    omDelPrcObj(NULL);
}

void func_80112378_w04(void) {
    Process *proc;
    void *file;
    s32 grpId;
    s32 charmSpr;
    s32 booSpr;
    s32 sfx;
    s32 x;
    s32 startX;
    s32 playerNo;
    s32 y;
    s32 i;
    s32 j;
    s32 alpha;

    playerNo = (s32)HuPrcCurrentGet()->user_data;

    file = DataRead(0x21002C);
    booSpr = func_80055810_main(file);
    DataClose(file);
    file = DataRead(0x1301BA);
    charmSpr = func_80055810_main(file);
    DataClose(file);
    file = DataRead(0x1301B9);
    D_8011E0C0_w04 = func_80055810_main(file);
    DataClose(file);

    grpId = HuSprGrpCreate(2, 2);
    func_800550F4_main(grpId, 0, 1);
    func_80055024_main(grpId, 0, booSpr, 0xC);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, 0x1000);
    func_800554C4_main(grpId, 0, -1);
    func_80055024_main(grpId, 1, charmSpr, 0);
    HuSprPriSet(grpId, 1, 9);
    HuSprAttrSet(grpId, 1, 0x9000);
    func_80055420_main(grpId, 1, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grpId, 1, 0xFF);
    HuSprScaleSet(grpId, 1, 2.0f, 2.0f);
    func_800554C4_main(grpId, 1, 0);

    if (playerNo & 1) {
        x = 0xC8;
        HuSprAttrSet(grpId, 0, 1);
        HuSprAttrSet(grpId, 1, 1);
        func_80054904_main(grpId, 1, 0x14, -5);
    } else {
        x = 0x78;
        func_80054904_main(grpId, 1, -0x14, -5);
    }
    

    if (playerNo < 2) {
        y = -0x20;
    } else {
        y = 0x110;
    }

    HuPrcSleep(0x14);
    GwPlayer[playerNo].itemNo[MBItemFind(playerNo, ITEM_BOO_REPELLENT)] = ITEM_NONE;
    MBItemRemoveEmpty(playerNo);
    MBStatusItemIconSprReinit(playerNo);

    //TODO: this sure is some cod...
    while (1) {
        if (playerNo < 2) {
            y += 5;
            if (y > 50) {
                break;
            }
        } else {
            y -= 5;
            if (y < 210) {
                break;
            }
        }
        loop:
        func_80054904_main(grpId, 0, x, y);
        HuPrcVSleep();
    
        if (playerNo < 2) {
            y += 5;
            if (y < 51) {
                goto loop;
            }
            break;
        }
    }

    HuPrcSleep(0xA);
    HuSprAttrReset(grpId, 1, 0x8000);
    sfx = HuAudFXPlay(0x14C);
    D_8011E0BC_w04 = playerNo;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            proc = omAddPrcObj(func_8011215C_w04, 0x4002, 0, 0);
            proc->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWait();
    HuAudFXStop(sfx);
    func_80055458_main(grpId, 1, 0);

    for (alpha = 0xFF; alpha >= 0; alpha -= 30) {
        func_80055458_main(grpId, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(grpId, 0, 0);
    HuSprGrpKill(grpId);
    HuSprKill(D_8011E0C0_w04);
    HuSprKill(charmSpr);
    HuSprKill(booSpr);
    omDelPrcObj(NULL);
}

void func_8011276C_w04(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_80112828_w04(void) {
    Object* modelObj;
    f32 angle;
    Object* obj;

    obj = HuPrcCurrentGet()->user_data;
    modelObj = MBModelLinkCreate(D_8011E0C4_w04);
    HuVecCopy3F(&modelObj->coords, &obj->coords);
    HuVecCopyXYZ(&modelObj->scale, 2.0f, 2.0f, 2.0f);
    modelObj->velocity.x = obj->velocity.x + 10.0f;
    MBModelDispOn(modelObj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        modelObj->velocity.x += 1.5;
        if ((obj->velocity.x + 35.0f) <= modelObj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[modelObj->omObj1->model[0]].mtx, angle);
    }

    MBModelKill(modelObj);
    omDelPrcObj(NULL);
}

void func_8011297C_w04(Object* arg0) {
    omAddPrcObj(func_80112828_w04, 0x1000, 0, 0)->user_data = arg0;
}

void func_801129B8_w04(void) {
    s32 *done = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *system = &GwSystem;

    while (1) {
        D_8011E0C8_w04->rot.x = -sindf(angle);
        D_8011E0C8_w04->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }

        if (*done != 0) {
            D_8011E0C8_w04->scale.x =
            D_8011E0C8_w04->scale.y =
            D_8011E0C8_w04->scale.z = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    D_8011E0C8_w04->scale.x =
    D_8011E0C8_w04->scale.y =
    D_8011E0C8_w04->scale.z = 0.0f;
    GwPlayer[system->current_player_index].itemNo[MBItemFind(CUR_PLAYER, ITEM_KOOPA_KARD)] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBModelKill(D_8011E0C8_w04);
    omDelPrcObj(NULL);
}

void func_80112B48_w04(void) {
    s32 pos[2];
    UnkVibrateProcess *vib;
    Object *coin;
    void *file;
    s32 sprId;
    s32 amount;
    s32 n;
    f32 step;
    f32 frac;
    s32 done = 0;
    GW_SYSTEM *system = &GwSystem;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    file = DataRead(D_80101040_shared_board[GwPlayer[system->current_player_index].chr]);
    sprId = func_80055810_main(file);
    DataClose(file);
    func_80055024_main(mbItemCursorGrpId, 0, sprId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 0xA);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    MBStatusItemPosGet(-1, 0, &pos[0], &pos[1]);
    func_80054904_main(mbItemCursorGrpId, 0, pos[0], pos[1]);

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(CUR_PLAYER, 0xF));
    func_8010F9F4_w04();

    D_8011E0C8_w04 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_8011E0C8_w04->coords,
                &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    D_8011E0C8_w04->velocity.x = 100.0f;
    while (D_8011E0C8_w04->velocity.x > 30.0f) {
        D_8011E0C8_w04->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_801129B8_w04, 0x4002, 0, 0)->user_data = &done;
    vib = MBPlayerVibrateObjCreate(-1, 4, 5);

    amount = GwSystem.bank_coins;
    step = (f32)amount / 30.0f;
    frac = 0.0f;
    coin = MBModelCreate(0x19, NULL);
    D_8011E0C4_w04 = coin;
    MBModelTempAllocFree(coin);
    MBModelDispOff(D_8011E0C4_w04);

    while (amount != 0) {
        frac += step;
        n = 0;
        while (frac >= 1.0f) {
            frac -= 1.0f;
            n++;
        }
        if (n != 0) {
            func_8011297C_w04(D_8011E0C8_w04);
            if ((amount - n) < 0) {
                n = amount;
            }
            amount -= n;
            MBPlayerCoinAdd(system->current_player_index, n);
            HuAudFXPlay(0x106);
            GwSystem.bank_coins -= n;
            func_80107F98_w04();
            HuPrcSleep(5);
        }
    }

    MBPlayerVibrateObjKill(vib);
    done = 1;
    HuPrcSleep(0x14);
    MBModelKill(D_8011E0C4_w04);
    MBVecForwardSet(&MBPlayerGet(CUR_PLAYER)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 func_80112F04_w04(u8 *arg0, s32 arg1) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    Q3Bytes4 sp20 = *(Q3Bytes4 *)D_8011DDD0_w04;
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 != 0) {
                    count = D_8011E0CC_w04 + 1;
                } else {
                    count = D_8011E0D0_w04 + 1;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (count != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void func_8011319C_w04(void) {
    Process *proc;
    s32 playerNo;
    s32 alpha;
    s32 i;

    proc = HuPrcCurrentGet();
    playerNo = (s32)proc->user_data;
    MBPlayerVibrate(playerNo, 4);

    for (alpha = 0x80; alpha > 0; alpha -= 0xA, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
                MBStatusItemTPLvlSet(playerNo, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
            MBStatusItemTPLvlSet(playerNo, i, 0);
        }
    }

    omDelPrcObj(NULL);
}

void func_801132A8_w04(void) {
    s32 pos[2];
    s32 alpha;
    s32 i;
    s32 slot;
    s32 playerNo = (s32)HuPrcCurrentGet()->user_data;
    GW_SYSTEM* system = &GwSystem;

    for (i = 0, slot = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerNo, slot, &pos[0], &pos[1]);
            MBStatusItemPosSet(system->current_player_index, i, pos[0], pos[1]);
            slot += i != MBItemSelNoGet();
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
                (i != MBItemSelNoGet())) {
                MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
            (i != MBItemSelNoGet())) {
            MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
        }
    }

    omDelPrcObj(NULL);
}

void func_80113484_w04(void) {
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

    func_8010F9F4_w04();
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
    targetPlayer = func_80112F04_w04(choices, 1);
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
                    func_80110244_w04(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(func_8011319C_w04, 0x4800, 0, 0);
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
        process = omAddPrcObj(func_801132A8_w04, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_80110244_w04(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_80110244_w04(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_80110244_w04(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_80110244_w04(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_80110244_w04(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_80110244_w04(targetPlayer, 2, 7, &target.x, 2);
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

void func_80114130_w04(void) {
    Object* temp_s1;
    Object* temp_s0;
    Q3ItemExchangeWork* temp_s2;

    temp_s2 = HuPrcCurrentGet()->user_data;
    temp_s1 = temp_s2->unk_00;
    temp_s0 = temp_s2->unk_04;
    MBMotionSet(temp_s1, -1, temp_s2->unk_08);
    HuVecCopy3F(&temp_s1->coords, &temp_s0->coords);
    temp_s1->coords.y += temp_s0->velocity.x - 10.0f;
    func_800D9A40_shared_board(temp_s1);
    while (!(MBMotionCheck(temp_s1)) && (temp_s2->unk_0C == 0)) {
        HuPrcVSleep();
    }
    MBModelKill(temp_s1);
    omDelPrcObj(NULL);
}

void func_801141F0_w04(void) {
    Object *coin;
    Object *obj;
    Process *proc;
    Q3ItemExchangeWork *work;
    s32 *flag;
    s32 light;
    f32 angle;
    f32 speed;
    f32 decel;
    f32 scale;
    s32 i;

    flag = HuPrcCurrentGet()->user_data;
    coin = D_8011E0D4_w04;
    obj = MBModelCreate(0x45, NULL);
    MBModelDispOff(obj);

    light = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(light, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(light, 10.0f);
    func_8001C8A8_main(light, 1);
    HuAudFXPlay(0x24C);

    for (angle = 0.0f, speed = 2.0f; speed < 80.0f; HuPrcVSleep()) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        speed += 1.0f;
        if (speed > 80.0f) {
            speed = 80.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);        
    }

    HuAudFXPlay(0x14A);
    
    while (coin->velocity.x < 110.0f) {
        coin->velocity.x += 7.0f;
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    for (*flag = 0; *flag == 0; HuPrcVSleep()) {
        if (D_8011C940_w04 != -1) {
            HuVecCopy3F(&coin->coords,
                        &MBPlayerGet(D_8011C940_w04)->player_obj->coords);
            func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                               coin->coords.z);
        }        
    }

    HuAudFXPlay(0x14B);
    
    decel = 3.0f;
    while (coin->velocity.x > 30.0f) {
        coin->velocity.x -= decel;
        if (decel > 1.0f) {
            decel -= 0.2f;
        }
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (speed > 15.0f) {
            speed -= 3.0f;
        } else {
            speed -= 0.5f;
        }
        if (speed < 1.0f) {
            break;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    func_8000D044_main(light);
    proc = omAddPrcObj(func_80114130_w04, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, sizeof(Q3ItemExchangeWork));
    proc->user_data = work;
    work->unk_00 = obj;
    work->unk_04 = coin;
    work->unk_08 = 0;
    work->unk_0C = 0;
    HuPrcSleep(3);

    *flag = 0;
    HuAudFXPlay(0x24D);
    
    for (i = 0, scale = 0.1f; i < 0x14; i++) {
        scale += 0.044999998f;
        func_8001D558_main(coin->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }

    MBModelKill(coin);
    omDelPrcObj(NULL);
}

void func_80114720_w04(void) {
    s32 sp20;
    GW_SYSTEM* system = &GwSystem;
    Object* temp_s3;
    Object* temp_v0;
    Object* temp_v0_2;
    Process* temp_s4;
    s32 temp_a0;
    s32 var_s1;
    s32 sel;
    s32 i;
    u32 var_v1_3;

    func_8010F9F4_w04();
    GwPlayer[system->current_player_index].itemNo[MBItemFind(-1, 0x11)] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    temp_v0 = MBModelCreate(0x3EU, NULL);
    Hu3DModelScaleSet(temp_v0->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    MBModelTempAllocFree(temp_v0);
    temp_v0->velocity.x = 30.0f;
    MBModelDispOff(temp_v0);
    temp_v0_2 = MBModelCreate(0x43U, NULL);
    D_8011E0D4_w04 = temp_v0_2;
    func_8001C2FC_main(temp_v0_2->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(temp_v0_2->omObj1->model[0]);
    func_8001C954_main(temp_v0_2->omObj1->model[0]);
    func_8001C514_main(temp_v0_2->omObj1->model[0]);
    HuVecCopy3F(&temp_v0_2->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    func_8001C814_main(temp_v0_2->omObj1->model[0], 2, 1);
    temp_v0_2->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (temp_v0_2->velocity.x > 30.0f) {
        temp_v0_2->velocity.x -= 1.0f;
        HuPrcVSleep();
    } 
loop:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00, GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    sel = func_80109CD4_w04(NULL, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch(sel) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            sel = func_800EF0D8_shared_board(0);
            break;
        default:
            func_80106B38_w04();
            D_800CB99C_main = 1;
            func_80049FB8_main();
            goto loop;
    }

    sp20 = 1;
    omAddPrcObj(func_801141F0_w04, 0x4002U, 0, 0)->user_data = &sp20;
    while(sp20) {
        HuPrcVSleep();
    }
    
    if (sel != system->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        D_8011C940_w04 = sel;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(sel)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(sel)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(0xA);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(0x1E);
        D_8011C940_w04 = sel;
    }
    sp20 = 1;
    while (sp20) {
        HuPrcVSleep();
    }
    
    temp_s3 = MBPlayerGet(sel)->player_obj;
    temp_s4 = func_800EDB98_shared_board(temp_v0, 5.0f, 2.0f);
    HuVecCopy3F(&temp_v0->coords, &temp_s3->coords);
    func_800D9A40_shared_board(temp_v0);
    temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z = 0.0f;
    while (temp_v0->scale.x < 1.0f) {
        temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z += 0.2f;
        HuPrcVSleep();
    }
    MBPlayerVibrate(sel, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[sel].coin != 0) {
        func_80109F58_w04(0xA, 0x2F00, -1, sel);
        GwPlayer[sel].gameCoin = GwPlayer[sel].coin;
        MBCoinChangeCreate(sel, -GwPlayer[sel].coin);
        MBCoinTakeCreate(sel, -GwPlayer[sel].coin);
        HuPrcSleep(0x1E);
        func_80109F58_w04(0xA, 0x2F02, -1, sel);
        omDelPrcObj(temp_s4);
        while(10.0f <= temp_v0->velocity.x) {
            temp_v0->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(0x1E);
        while (temp_v0->velocity.x < 100.0f) {
            temp_v0->velocity.x += 4.0f;
            temp_s3->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        func_80109F58_w04(0xA, 0x2F01, -1, sel);
        omDelPrcObj(temp_s4);
            while (temp_v0->velocity.x <= 100.0f) {
                temp_v0->velocity.x += 4.0f;
                HuPrcVSleep();
            } 
        MBModelKill(temp_v0);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }
    
    if ((MBPlayerComCheck(sel) != 0) && (system->show_com_minigames != 0)) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(temp_v0);
        func_800EE688_shared_board(temp_s3, 0.0f, 0.0f);
        temp_s3->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        temp_a0 = MBRand(100.0f) + 1;
        for (i = 0; i < 7; i++) {
            if (D_8011C94C_w04[i][1] >= temp_a0) {
                break;
            }
        }
        if (D_8011C94C_w04[i][0] != 0) {
            char sp28[16]; // required to be here or the codegen changes(?!)
            
            var_s1 = GwPlayer[sel].gameCoin * D_8011C94C_w04[i][0];
            if (var_s1 >= 1000) {
                var_s1 = 999;
            }
            sprintf(sp28, D_8011DDD4_w04, var_s1);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)sp28, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(sel, var_s1);
            MBCoinTakeCreate(sel, var_s1);
            HuPrcSleep(0x14);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(0xA);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
    } else {
        if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
            GWBoardFlagSet(0x17);
        } else {
            GWBoardFlagClear(0x17);
        }
        for (i = 0; i < 4; i++) {
            GwPlayer[i].group = 1;
        }
        MBPlayerGet(sel)->group = 0;
        temp_a0 = MBRand(100.0f);
        for(var_v1_3 = 0; var_v1_3 < 3; var_v1_3++) {
            if (temp_a0 < D_8011C948_w04[var_v1_3]) {
                break;
            }
        }
    
        if (var_v1_3 == 3) {
            var_v1_3 = 2;
        }
        system->minigame_index = D_8011C944_w04[var_v1_3];
        GwSystem.playerIndexVisitingBowser = sel;
        func_800FC998_shared_board();
        func_8004A0E0_main();
        func_800FF7F0_shared_board(2);
        HuPrcSleep(-1);
    }
}

void func_8011502C_w04(s32 sprGrp, s32 frames, f32 *dest) {
    f32 x;
    f32 y;
    f32 stepX;
    f32 stepY;
    s32 i;

    MBStatusSprPosGet(sprGrp, 0, &x, &y);
    stepX = (dest[0] - x) / frames;
    stepY = (dest[1] - y) / frames;

    for (; frames != 0; frames--) {
        x += stepX;
        y += stepY;
        func_80054904_main(sprGrp, 0, x, y);
        HuPrcVSleep();
    }

    func_80054904_main(sprGrp, 0, dest[0], dest[1]);
}

void func_80115164_w04(omObjData *obj) {
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s3;
    s32 var_v0;
    s32 i;

    temp_s1 = (s32)HuPrcCurrentGet()->user_data;
    var_s3 = 10;

    switch (temp_s1) {
        case 0:
            func_80054904_main(D_8011E0D8_w04[temp_s1], 0, 0xB1, 0x2C);
            break;
        case 1:
            func_80054904_main(D_8011E0D8_w04[temp_s1], 0, 0x7A, 0x39);
            break;
        default:
            func_80054904_main(D_8011E0D8_w04[temp_s1], 0, 0xA0, 0x98);
            var_s3 = 30;
            break;
    }

    HuSprAttrReset(D_8011E0D8_w04[temp_s1], 0, 0x8000);
    for (i = 0; i < 255; i += 255 / var_s3) {
        func_80055458_main(D_8011E0D8_w04[temp_s1], 0, i);
        HuPrcVSleep();
    }

    func_80055458_main(D_8011E0D8_w04[temp_s1], 0, 0xFF);
    omDelPrcObj(0);
}

void func_801152D4_w04(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i, j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011C968_w04[i].r;
        sp18.g = D_8011C968_w04[i].g;
        sp18.b = D_8011C968_w04[i].b;

        sp28.r = (D_8011C968_w04[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011C968_w04[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011C968_w04[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            func_80055420_main(D_8011E0D8_w04[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        func_80055420_main(D_8011E0D8_w04[3], 0, D_8011C968_w04[i + 1].r, D_8011C968_w04[i + 1].g, D_8011C968_w04[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void func_8011549C_w04(void) {
    Object *obj;
    s32 *state;
    f32 spin;
    f32 scale;

    state = HuPrcCurrentGet()->user_data;
    HuAudFXPlay(0x143);
    obj = D_8011E0E8_w04;
    func_800D9A40_shared_board(obj);

    for (spin = 0.0f, scale = 1.0f; scale < 18.0f; scale += 0.8) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 1) {
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    for (; scale < 40.0f; scale += 0.8) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 2) {
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_80115720_w04(void) {
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
    s32 *temp_s0;
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
        D_8011E0D8_w04[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8011E0D8_w04[i], 0, sp18[i], 0);
        HuSprPriSet(D_8011E0D8_w04[i], 0, 0x4780U);
        HuSprAttrSet(D_8011E0D8_w04[i], 0, 0x980CU);
        func_80055458_main(D_8011E0D8_w04[i], 0, 0U);
        func_80055420_main(D_8011E0D8_w04[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_8011E0E8_w04 = temp_v0_3;
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
    func_8011502C_w04(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_8011502C_w04(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_8011502C_w04(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_8011502C_w04(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002, 0, 0);
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
        HuSprAttrSet(D_8011E0D8_w04[i], 0, 0x8000);
    }

    HuSprAttrReset(D_8011E0D8_w04[3], 0, 0x8000U);
    func_80055458_main(D_8011E0D8_w04[3], 0, 0xFFU);
    func_80054904_main(D_8011E0D8_w04[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_801152D4_w04, 0x4002, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_8011549C_w04, 0x4002, 0, 0)->user_data = &sp40;
    HuPrcChildWait();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_8011E0D8_w04[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(D_8011E0D8_w04[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_8011E0D8_w04[i]);
        HuSprKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = WATCH_USED;
}

void func_80116024_w04(Q3SpaceTriple *masu, Q3BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    BranchLink *link;
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
    func_80106B94_w04();
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
    func_80106C64_w04();

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


void func_8011621C_w04(s32 arg0) {
    if (D_8011E100_w04[arg0] != NULL) {
        omDelObj(D_8011E100_w04[arg0]);
        D_8011E100_w04[arg0] = NULL;
    }
    if (D_8011E0F0_w04[arg0] != NULL) {
        MBModelKill(D_8011E0F0_w04[arg0]);
        D_8011E0F0_w04[arg0] = NULL;
    }
}

void func_80116294_w04(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011E100_w04[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011E100_w04[i] = NULL;
        }
    }
}

void func_801162F8_w04(omObjData *obj) {
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
        Object *effectObj = D_8011E0F0_w04[playerIdx];

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

void func_801164A4_w04(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (D_8011E0F0_w04[arg0] == NULL) {
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
        D_8011E0F0_w04[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011E0F0_w04[arg0]);
    }
}

void func_801165A4_w04(s32 arg) {
    D_8011E100_w04[arg] = omAddObj(0x3FFF, 0, 0, -1, func_801162F8_w04);
    D_8011E100_w04[arg]->work[0] = arg;
    D_8011E100_w04[arg]->work[1] = 0;
    D_8011E100_w04[arg]->work[2] = 0;
    D_8011E100_w04[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011E100_w04[arg]->trans.x = 0;
}

void func_80116640_w04(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_8011E100_w04[i] = NULL;
        D_8011E0F0_w04[i] = NULL;
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
            func_801164A4_w04(i, idx);
            func_801165A4_w04(i);
        }
    }
    func_800F8D54_shared_board(func_80116294_w04);
}

void func_80116740_w04(void) {
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
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void func_8011694C_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_8011621C_w04(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_80116AAC_w04(void) {
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

void func_80116AFC_w04(void) {
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
    choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)2, D_8011E114_w04);
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

    func_8011621C_w04(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_801164A4_w04(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_801165A4_w04(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_80116AAC_w04, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_8011621C_w04(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void func_80117074_w04(void) {
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
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void func_80117244_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_8011621C_w04(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_8011737C_w04(void) {
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
    choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)2, D_8011E110_w04);
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

    func_8011621C_w04(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_801164A4_w04(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_801165A4_w04(targetPlayer);
    omAddPrcObj(func_80116AAC_w04, 0x4002, 0, 0)->user_data = vib;
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
        func_80117074_w04();
    }
}

void func_80117800_w04(void) {
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

    func_8010F9F4_w04();
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
    targetPlayer = func_80112F04_w04(choices, 0);
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
                       D_8011C864_w04[system->current_player_index].x,
                       D_8011C864_w04[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(-1,
                                            D_8011C864_w04[system->current_player_index].x,
                                            D_8011C864_w04[system->current_player_index].y,
                                            D_8011C844_w04[system->current_player_index].x,
                                            D_8011C844_w04[system->current_player_index].y, 5));
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
    func_8010FBC4_w04();
}

void func_80117EA8_w04(void) {
    void *data;
    s32 sprite;
    s32 group;
    s32 turns;
    s32 counted;
    s32 fading;
    s32 alpha;
    f32 angle;
    f32 a;
    f32 step;

    data = DataRead(0x1300F7);
    sprite = func_80055810_main(data);
    DataClose(data);
    group = HuSprGrpCreate(1, 5);
    func_80055024_main(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x1008);
    HuSprPriSet(group, 0, 0x1000);
    func_80054904_main(group, 0, 0xA0, 0x5A);
    angle = 0.0f;
    step = 30.0f;
    turns = 0;
    counted = 0;
    while (TRUE) {
        if ((angle >= 90.0f) & (counted == 0)) {
            counted = 1;
            turns++;
        }
        if (angle >= 360.0f) {
            counted = 0;
            angle -= 360.0f;
        }
        if ((angle >= 180.0f) & (angle <= 360.0f)) {
            HuSprAttrSet(group, 0, 2);
        } else {
            HuSprAttrReset(group, 0, 2);
        }
        a = angle;
        if (angle >= 180.0f) {
            a = angle - 180.0f;
        }
        HuSprScaleSet(group, 0, 1.0f, sindf(a));
        if (turns >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprAttrReset(group, 0, 2);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    HuPrcSleep(20);
    angle = 90.0f;
    turns = 0;
    fading = 0;
    counted = 0;
    alpha = 0xFF;
    while (TRUE) {
        if ((angle >= 360.0f) & (counted == 0)) {
            counted = 1;
            turns++;
        }
        if (angle >= 360.0f) {
            counted = 0;
            angle -= 360.0f;
        }
        if ((fading == 0) & (turns != 0)) {
            if ((angle >= 90.0f) & (angle < 180.0f)) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        func_80055458_main(group, 0, alpha);
        if (turns >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprScaleSet(group, 0, 1.0f, 0.0f);
    HuSprGrpKill(group);
    HuSprKill(sprite);
    omDelPrcObj(NULL);
}

Process *func_80118240_w04(void) {
    return omAddPrcObj(func_80117EA8_w04, 0x1000, 0, 0);
}

void func_8011826C_w04(omObjData *obj) {
    s32 i;

    if (obj->work[0] == 0) {
        for (i = 0; i < 2; i++) {
            HuVecCopy3F(&D_8011E118_w04[i]->coords, &MBMasuGet(D_8011C998_w04[i])->coords);
            D_8011E118_w04[i]->coords.x = (MBRand(30.0f) / 10.0f - 1.5f) + D_8011E118_w04[i]->coords.x;
        }
    } else {
        for (i = 0; i < 2; i++) {
            HuVecCopy3F(&D_8011E118_w04[i]->coords, &MBMasuGet(D_8011C99C_w04[i])->coords);
            D_8011E118_w04[i]->coords.x = (MBRand(30.0f) / 10.0f - 1.5f) + D_8011E118_w04[i]->coords.x;
        }
    }
}

#ifdef NON_MATCHING
// board q4: masked 30; retail keeps -1 in s8 for the second choice loop, this C hoists 2.0f into $f24 instead
void func_801183D4_w04(void) {
    Vec target;
    Vec camPos;
    s32 markerFiles[2];
    Object *boxes[2];
    Object *effects[2];
    s32 boxFiles[2];
    u8 order[2];
    GW_PLAYER *player;
    SpaceData *space;
    SpaceData *curSpace;
    s32 playerNo;
    s32 choice;
    s32 i;
    s32 frames;
    omObjData *jitter;
    Unk3 *help1;
    Unk3 *help2;
    s16 win;
    UnkVibrateProcess *vib;
    f32 speed;
    f32 scale;

    player = MBPlayerGet(-1);
    space = MBMasuGet(0x89);
    curSpace = MBMasuGet(MBMasuCurGet());
    playerNo = GwSystem.current_player_index;
    markerFiles[0] = 0x130179;
    markerFiles[1] = 0x13017A;
    effects[0] = NULL;
    effects[1] = NULL;
    boxFiles[0] = 0x13017B;
    boxFiles[1] = 0x13017C;
    choice = -1;
    MBDlgWinInsertCreate(0x3E, 0x900, mbCharNameMesTbl[GwPlayer[playerNo].chr], 0, 0, 0, 0);
    func_800EC9DC_shared_board();
    func_800EC9DC_shared_board();
    MBDlgWinClose();
    MBDlgWinKill();
    MBVecDirGet(&player->player_obj->coords, &space->coords, &target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords, &player->player_obj->coords, 15));
    player->player_obj->velocity.y = 6.0f;
    player->player_obj->velocity.z = -0.75f;
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, -1, 2);
    space = MBMasuGet(0x7C);
    MBVecDirGet(&player->player_obj->coords, &space->coords, &target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    HuVecCopy3F(&camPos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&camPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &space->coords, &camPos, 10));
    HuPrcChildWait();
    MBStatusHideAll();
    for (i = 0; i < 2; i++) {
        D_8011E118_w04[i] = MBModelFileCreate(markerFiles[0], -1, 1.0f, 0.0f, NULL);
        func_8001C258_main(D_8011E118_w04[i]->omObj1->model[0], 0x180, 0);
        func_8001C8E4_main(D_8011E118_w04[i]->omObj1->model[0], 0x1800);
        func_8001C448_main(D_8011E118_w04[i]->omObj1->model[0]);
        MBModelTempAllocFree(D_8011E118_w04[i]);
        HuVecCopy3F(&D_8011E118_w04[i]->coords, &MBMasuGet(D_8011C998_w04[i])->coords);
    }
    jitter = omAddObj(0x1000, 0, 0, -1, func_8011826C_w04);
    jitter->work[0] = 0;
    MBArrayShuffle(order, 1);
    for (i = 0; i < 2; i++) {
        boxes[i] = MBModelFileCreate(boxFiles[order[i]], -1, 1.0f, 0.0f, NULL);
        MBModelTempAllocFree(boxes[i]);
        HuVecCopy3F(&boxes[i]->coords, &MBMasuGet(D_8011C998_w04[i])->coords);
    }
    HuAudFXPlay(0x1A5);
    vib = MBPlayerVibrateObjCreate(-1, 1, 5);
    HuPrcChildLink(HuPrcCurrentGet(), func_80118240_w04());
    HuPrcSleep(30);
    win = func_8005A968_main(0x5A, 0xB4, 0x8C, 0x2A, 0, 0);
    func_8005BEE0_main(win, 0x100);
    func_8005FBF8_main(win, 0x8C, 0x3C, 0xC8);
    help1 = func_800E210C_shared_board(0x18, 0xB6, 1);
    help2 = func_800E210C_shared_board(0x19, 0xC8, 1);
    HuPrcChildWait();
    frames = MBRand(20.0f) + 20;
    for (i = 0; i < frames; i++) {
        if (choice == -1) {
            if (!MBPlayerComCheck(-1)) {
                if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x200) {
                    choice = 0;
                } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x100) {
                    choice = 1;
                }
            }
            if (choice != -1) {
                HuVecCopy3F(&target, &MBMasuGet(D_8011C998_w04[choice])->coords);
                target.y = 0.0f;
                MBVecDirGet(&player->player_obj->coords, &target, &player->player_obj->rot);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target, &player->player_obj->coords, 10));
                MBPlayerMotionSet(playerNo, 1, 2);
            }
        }
        HuPrcVSleep();
    }
    speed = 0.5f;
    scale = 1.0f;
    while (boxes[0]->coords.y >= 20.0f) {
        for (i = 0; i < 2; i++) {
            boxes[i]->coords.y -= speed;
            HuVecCopyXYZ(&boxes[i]->scale, scale, scale, scale);
        }
        scale -= 0.01f;
        speed += 0.2f;
        if (speed >= 2.0f) {
            speed = 2.0f;
        }
        if (choice == -1) {
            if (MBPlayerComCheck(-1) != 0) {
                if (MBRand(10.0f) == 0) {
                    choice = MBRand(2.0f) != 0;
                }
            } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x200) {
                choice = 0;
            } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x100) {
                choice = 1;
            }
            if (choice != -1) {
                HuVecCopy3F(&target, &MBMasuGet(D_8011C998_w04[choice])->coords);
                target.y = 0.0f;
                MBVecDirGet(&player->player_obj->coords, &target, &player->player_obj->rot);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target, &player->player_obj->coords, 10));
                MBPlayerMotionSet(playerNo, 1, 2);
            }
        }
        HuPrcVSleep();
    }
    MBHelpWinKill(help1);
    MBHelpWinKill(help2);
    func_8005F364_main(win);
    while (boxes[0]->scale.x > 0.0f) {
        for (i = 0; i < 2; i++) {
            if (choice != i) {
                MBModelDispOff(boxes[i]);
                if (effects[i] == NULL) {
                    effects[i] = MBModelFileCreate(0xB003C, -1, 2.0f, 0.0f, NULL);
                    MBModelTempAllocFree(effects[i]);
                    HuVecCopy3F(&effects[i]->coords, &boxes[i]->coords);
                    func_8001C814_main(effects[i]->omObj1->model[0], 2, 0);
                    if ((choice == -1) & (i == 0)) {
                        HuAudFXPlay(0x1A8);
                    }
                }
            }
            boxes[i]->coords.y -= 0.75f;
            HuVecCopyXYZ(&boxes[i]->scale, scale, scale, scale);
        }
        scale -= 0.075f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }
    MBPlayerVibrateObjKill(vib);
    for (i = 0; i < 2; i++) {
        if (choice == i) {
            effects[choice] = MBModelFileCreate(0xB003B, -1, 2.0f, 0.0f, NULL);
            func_8001C258_main(effects[choice]->omObj1->model[0], 0x180, 0);
            func_8001C8E4_main(effects[choice]->omObj1->model[0], 0x1800);
            func_8001C448_main(effects[choice]->omObj1->model[0]);
            HuVecCopy3F(&effects[choice]->coords, &boxes[choice]->coords);
            func_8001C814_main(effects[choice]->omObj1->model[0], 2, 0);
            HuAudFXPlay(0x1A6);
            MBPlayerVibrate(-1, 3);
        }
    }
    if (effects[0] != NULL) {
        MBModelMotionWait(effects[0]);
    }
    if (effects[1] != NULL) {
        MBModelMotionWait(effects[1]);
    }
    omDelObj(jitter);
    for (i = 0; i < 2; i++) {
        MBModelKill(D_8011E118_w04[i]);
        MBModelKill(boxes[i]);
        if (effects[i] != NULL) {
            MBModelKill(effects[i]);
        }
    }
    MBVecForwardSet(&player->player_obj->rot);
    if (choice == -1) {
        MBDlgWinExec(0x3E, 0x903);
        boxes[0] = MBModelFileCreate(boxFiles[1], -1, 1.0f, 0.0f, NULL);
        func_8001FA68_main(boxes[0]->omObj1->model[0]);
        HuVecCopy3F(&boxes[0]->coords, &player->player_obj->coords);
        boxes[0]->velocity.x = 60.0f;
        boxes[0]->coords.x += 3.0f;
        HuAudFXPlay(0x19);
        for (i = 0; i < 0x100; i += 12) {
            func_8001F9E4_main(boxes[0]->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(boxes[0]->omObj1->model[0], 0xFF);
        func_8004ACE0_main(0x274, playerNo);
        MBPlayerMotionSet(playerNo, 5, 0);
        choice = 0;
        MBModelMotionWait(player->player_obj);
        MBDlgResultWinExec(0x904);
        MBModelKill(boxes[0]);
        order[0] = 1;
    } else {
        func_8004ACE0_main(0x274, playerNo);
        MBPlayerMotionSet(playerNo, 5, 0);
        MBModelMotionWait(player->player_obj);
        MBDlgResultWinExec(order[choice] == 1 ? 0x902 : 0x901);
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &player->player_obj->coords, &camPos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(1);
    MBVecDirGet(&player->player_obj->coords, &curSpace->coords, &player->player_obj->rot);
    MBPlayerMotionSet(playerNo, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &curSpace->coords, &player->player_obj->coords, 20));
    player->player_obj->velocity.y = 6.0f;
    player->player_obj->velocity.z = -0.6f;
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, -1, 2);
    MBVecForwardSet(&target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    MBStatusShowAll();
    if (choice != -1) {
        if (order[choice] == 1) {
            GwSystem.boardData.halfWordBytes[3] = 1;
            GwSystem.cur_player_used_item = 1;
            return;
        }
        MBCoinChangeCreate(playerNo, 5);
        MBCoinTakeCreate(playerNo, 5);
        HuPrcSleep(30);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801183D4_w04);
#endif

#ifdef NON_MATCHING
// board q4: masked 53; the same 2.0f/-1 hoisting residue as func_801183D4_w04, and GCC turns the 0x906/0x907 message
// choice into a store-flag sequence where retail branches
void func_801191B8_w04(void) {
    Vec target;
    Vec camPos;
    s32 markerFiles[2];
    Object *boxes[2];
    Object *effects[2];
    s32 boxFiles[2];
    u8 order[2];
    GW_PLAYER *player;
    SpaceData *space;
    SpaceData *curSpace;
    s32 playerNo;
    s32 choice;
    s32 i;
    s32 frames;
    omObjData *jitter;
    Unk3 *help1;
    Unk3 *help2;
    s16 win;
    UnkVibrateProcess *vib;
    f32 speed;
    f32 scale;
    s32 msg;

    player = MBPlayerGet(-1);
    space = MBMasuGet(0x8A);
    curSpace = MBMasuGet(MBMasuCurGet());
    playerNo = GwSystem.current_player_index;
    markerFiles[0] = 0x130179;
    markerFiles[1] = 0x13017A;
    effects[0] = NULL;
    effects[1] = NULL;
    boxFiles[0] = 0x13017D;
    boxFiles[1] = 0x13017E;
    choice = -1;
    MBDlgWinInsertCreate(0x3F, 0x905, mbCharNameMesTbl[GwPlayer[playerNo].chr], 0, 0, 0, 0);
    func_800EC9DC_shared_board();
    func_800EC9DC_shared_board();
    MBDlgWinClose();
    MBDlgWinKill();
    MBVecDirGet(&player->player_obj->coords, &space->coords, &target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords, &player->player_obj->coords, 15));
    player->player_obj->velocity.y = 6.0f;
    player->player_obj->velocity.z = -0.75f;
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, -1, 2);
    space = MBMasuGet(0x7E);
    MBVecDirGet(&player->player_obj->coords, &space->coords, &target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    HuVecCopy3F(&camPos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&camPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &space->coords, &camPos, 10));
    HuPrcChildWait();
    MBStatusHideAll();
    for (i = 0; i < 2; i++) {
        D_8011E118_w04[i] = MBModelFileCreate(markerFiles[1], -1, 1.0f, 0.0f, NULL);
        func_8001C258_main(D_8011E118_w04[i]->omObj1->model[0], 0x180, 0);
        func_8001C8E4_main(D_8011E118_w04[i]->omObj1->model[0], 0x1800);
        func_8001C448_main(D_8011E118_w04[i]->omObj1->model[0]);
        MBModelTempAllocFree(D_8011E118_w04[i]);
        HuVecCopy3F(&D_8011E118_w04[i]->coords, &MBMasuGet(D_8011C99C_w04[i])->coords);
    }
    jitter = omAddObj(0x1000, 0, 0, -1, func_8011826C_w04);
    jitter->work[0] = 1;
    MBArrayShuffle(order, 1);
    for (i = 0; i < 2; i++) {
        boxes[i] = MBModelFileCreate(boxFiles[order[i]], -1, 1.0f, 0.0f, NULL);
        MBModelTempAllocFree(boxes[i]);
        HuVecCopy3F(&boxes[i]->coords, &MBMasuGet(D_8011C99C_w04[i])->coords);
    }
    HuAudFXPlay(0x1A5);
    vib = MBPlayerVibrateObjCreate(-1, 1, 5);
    HuPrcChildLink(HuPrcCurrentGet(), func_80118240_w04());
    HuPrcSleep(30);
    win = func_8005A968_main(0x5A, 0xB4, 0x8C, 0x2A, 0, 0);
    func_8005BEE0_main(win, 0x100);
    func_8005FBF8_main(win, 0x8C, 0x3C, 0xC8);
    help1 = func_800E210C_shared_board(0x18, 0xB6, 1);
    help2 = func_800E210C_shared_board(0x19, 0xC8, 1);
    HuPrcChildWait();
    frames = MBRand(20.0f) + 20;
    for (i = 0; i < frames; i++) {
        if (choice == -1) {
            if (!MBPlayerComCheck(-1)) {
                if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x200) {
                    choice = 0;
                } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x100) {
                    choice = 1;
                }
            }
            if (choice != -1) {
                HuVecCopy3F(&target, &MBMasuGet(D_8011C99C_w04[choice])->coords);
                target.y = 0.0f;
                MBVecDirGet(&player->player_obj->coords, &target, &player->player_obj->rot);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target, &player->player_obj->coords, 10));
                MBPlayerMotionSet(playerNo, 1, 2);
            }
        }
        HuPrcVSleep();
    }
    speed = 0.5f;
    scale = 1.0f;
    while (boxes[0]->coords.y >= 20.0f) {
        for (i = 0; i < 2; i++) {
            boxes[i]->coords.y -= speed;
            HuVecCopyXYZ(&boxes[i]->scale, scale, scale, scale);
        }
        scale -= 0.01f;
        speed += 0.2f;
        if (speed >= 2.0f) {
            speed = 2.0f;
        }
        if (choice == -1) {
            if (MBPlayerComCheck(-1) != 0) {
                if (MBRand(10.0f) == 0) {
                    choice = MBRand(2.0f) != 0;
                }
            } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x200) {
                choice = 0;
            } else if (D_800D5546_main[GwPlayer[playerNo].pad] & 0x100) {
                choice = 1;
            }
            if (choice != -1) {
                HuVecCopy3F(&target, &MBMasuGet(D_8011C99C_w04[choice])->coords);
                target.y = 0.0f;
                MBVecDirGet(&player->player_obj->coords, &target, &player->player_obj->rot);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target, &player->player_obj->coords, 10));
                MBPlayerMotionSet(playerNo, 1, 2);
            }
        }
        HuPrcVSleep();
    }
    MBHelpWinKill(help1);
    MBHelpWinKill(help2);
    func_8005F364_main(win);
    while (boxes[0]->scale.x > 0.0f) {
        for (i = 0; i < 2; i++) {
            if (choice != i) {
                MBModelDispOff(boxes[i]);
                if (effects[i] == NULL) {
                    effects[i] = MBModelFileCreate(0xB003C, -1, 2.0f, 0.0f, NULL);
                    MBModelTempAllocFree(effects[i]);
                    HuVecCopy3F(&effects[i]->coords, &boxes[i]->coords);
                    func_8001C814_main(effects[i]->omObj1->model[0], 2, 0);
                    if ((choice == -1) & (i == 0)) {
                        HuAudFXPlay(0x1A8);
                    }
                }
            }
            boxes[i]->coords.y -= 0.75f;
            HuVecCopyXYZ(&boxes[i]->scale, scale, scale, scale);
        }
        scale -= 0.075f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }
    MBPlayerVibrateObjKill(vib);
    for (i = 0; i < 2; i++) {
        if (choice == i) {
            effects[choice] = MBModelFileCreate(0xB003B, -1, 2.0f, 0.0f, NULL);
            func_8001C258_main(effects[choice]->omObj1->model[0], 0x180, 0);
            func_8001C8E4_main(effects[choice]->omObj1->model[0], 0x1800);
            func_8001C448_main(effects[choice]->omObj1->model[0]);
            HuVecCopy3F(&effects[choice]->coords, &boxes[choice]->coords);
            func_8001C814_main(effects[choice]->omObj1->model[0], 2, 0);
            HuAudFXPlay(0x1A7);
            MBPlayerVibrate(-1, 3);
        }
    }
    if (effects[0] != NULL) {
        MBModelMotionWait(effects[0]);
    }
    if (effects[1] != NULL) {
        MBModelMotionWait(effects[1]);
    }
    omDelObj(jitter);
    for (i = 0; i < 2; i++) {
        MBModelKill(D_8011E118_w04[i]);
        MBModelKill(boxes[i]);
        if (effects[i] != NULL) {
            MBModelKill(effects[i]);
        }
    }
    MBVecForwardSet(&player->player_obj->rot);
    if (choice == -1) {
        MBDlgWinExec(0x3F, 0x908);
        boxes[0] = MBModelFileCreate(boxFiles[1], -1, 1.0f, 0.0f, NULL);
        func_8001FA68_main(boxes[0]->omObj1->model[0]);
        HuVecCopy3F(&boxes[0]->coords, &player->player_obj->coords);
        boxes[0]->velocity.x = 60.0f;
        boxes[0]->coords.x += 3.0f;
        HuAudFXPlay(0x19);
        for (i = 0; i < 0x100; i += 12) {
            func_8001F9E4_main(boxes[0]->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(boxes[0]->omObj1->model[0], 0xFF);
        func_8004ACE0_main(0x286, playerNo);
        MBPlayerMotionSet(playerNo, 3, 0);
        choice = 0;
        MBModelMotionWait(player->player_obj);
        MBDlgResultWinExec(0x909);
        MBModelKill(boxes[0]);
        order[0] = 1;
    } else {
        func_8004ACE0_main(0x286, playerNo);
        MBPlayerMotionSet(playerNo, 3, 0);
        MBModelMotionWait(player->player_obj);
        msg = 0x906;
        if (order[choice] == 1) {
            msg = 0x907;
        }
        MBDlgResultWinExec(msg);
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &player->player_obj->coords, &camPos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(1);
    MBVecDirGet(&player->player_obj->coords, &curSpace->coords, &player->player_obj->rot);
    MBPlayerMotionSet(playerNo, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &curSpace->coords, &player->player_obj->coords, 20));
    player->player_obj->velocity.y = 6.0f;
    player->player_obj->velocity.z = -0.6f;
    HuPrcChildWait();
    MBPlayerMotionSet(playerNo, -1, 2);
    MBVecForwardSet(&target);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&player->player_obj->rot, &target, &player->player_obj->rot, 5));
    HuPrcChildWait();
    MBStatusShowAll();
    if (choice != -1) {
        if (order[choice] == 1) {
            GwSystem.boardData.halfWordBytes[3] = 1;
            GwSystem.cur_player_used_item = 1;
            GwSystem.boardData.halfWordBytes[4] = 1;
            player->rev |= 0x80;
            func_800DC104_shared_board(MBPlayerTurnGet(), 1);
            return;
        }
        MBCoinChangeCreate(playerNo, -5);
        MBCoinTakeCreate(playerNo, -5);
        HuPrcSleep(30);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801191B8_w04);
#endif

void func_80119FCC_w04(s32 index, s32 arg1) {
    s16 spaces[3] = { 0x81, 0x83, 0x82 };
    Object *base;
    Object *gust;
    Object *target;
    SpaceData *space;
    HmfModel *mdl;
    f32 start;
    f32 angle;
    s32 i;
    s32 played;

    played = 0;
    base = MBModelFileCreate(0x130178, -1, 1.0f, 0.0f, NULL);
    func_8001C8E4_main(base->omObj1->model[0], 0);
    func_8001C258_main(base->omObj1->model[0], 0x80000, 0x80000);
    func_8001C448_main(base->omObj1->model[0]);
    MBModelTempAllocFree(base);
    if (index == -1) {
        space = MBMasuGet(spaces[0]);
        target = D_8011E09C_w04[0];
    } else {
        space = MBMasuGet(spaces[index]);
        target = D_8011E09C_w04[index];
    }
    HuVecCopy3F(&base->coords, &space->coords);
    gust = MBModelFileCreate(0xA0156, -1, 0.9f, 0.0f, NULL);
    HuVecCopyXYZ(&gust->scale, 1.8f, 1.8f, 1.8f);
    MBModelTempAllocFree(gust);
    HuVecCopy3F(&gust->coords, &space->coords);
    gust->velocity.x = -30.0f;
    HuAudFXPlay(0x1A2);
    angle = 0.0f;
    do {
        gust->velocity.x = sindf(angle) * 35.0f - 30.0f;
        HuPrcVSleep();
        angle += 15.0f;
    } while (angle <= 135.0f);
    HuPrcSleep(10);
    angle = start = MBVecAngleGet(&target->rot);
    for (i = 0; i < 361; i += 20) {
        sincosdf(i, &HmfModelData[gust->omObj1->model[0]].mtx[8], &HmfModelData[gust->omObj1->model[0]].mtx[10]);
        HmfModelData[gust->omObj1->model[0]].mtx[2] = -HmfModelData[gust->omObj1->model[0]].mtx[8];
        mdl = &HmfModelData[gust->omObj1->model[0]];
        mdl->mtx[0] = mdl->mtx[10];
        mdl = &HmfModelData[gust->omObj1->model[0]];
        mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[gust->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[15] = 1.0f;
        if (i >= 181) {
            angle -= 20.0f;
            if (played == 0) {
                HuAudFXPlay(0x1A4);
                played = 1;
            }
        }
        target->rot.x = sindf(angle);
        target->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    while (start - 180.0f <= angle) {
        target->rot.x = sindf(angle);
        target->rot.z = cosdf(angle);
        HuPrcVSleep();
        angle -= 20.0f;
    }
    HuAudFXPlay(0x1A3);
    angle = 135.0f;
    do {
        gust->velocity.x = sindf(angle) * 25.0f - 20.0f;
        HuPrcVSleep();
        angle -= 20.0f;
    } while (angle >= 0.0f);
    MBModelKill(gust);
    MBModelKill(base);
    HuPrcSleep(5);
    if (index == -1) {
        for (i = 0; i < 3; i++) {
            GwSystem.boardData.halfWordBytes[D_8011B9C4_w04[i]] ^= 1;
        }
        func_8010873C_w04();
        if (arg1 == 0) {
            MBDlgResultWinExec(0xB03);
        } else {
            func_800EC5B4_shared_board(-1, 0xB05);
        }
    } else {
        GwSystem.boardData.halfWordBytes[D_8011B9C4_w04[index]] ^= 1;
        func_8010873C_w04();
        MBDlgResultWinExec(0xA00);
    }
}

void func_8011A4E0_w04(s32 index) {
    Vec camPos;
    SpaceData *space;
    GW_PLAYER *player;

    space = MBMasuGet(D_8011B9BC_w04[index]);
    player = MBPlayerGet(-1);
    HuVecCopy3F(&camPos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&camPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &space->coords, &camPos, 15));
    HuPrcChildWait();
    func_80119FCC_w04(index, 0);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &player->player_obj->coords, &camPos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(1);
}

#ifdef NON_MATCHING
// board q4: masked 1; retail reuses the a0 = 0x3D set in the case-1 branch delay slot before calling func_80106AB0_w04 (void)
void func_8011A5DC_w04(void) {
    SpaceData *space;
    GW_SYSTEM *sys;
    DecisionTreeNonLeafNode *tree;
    s32 masu;
    s32 choice;

    space = MBMasuGet(D_8011B9BC_w04[0]);
    masu = MBMasuCurGet();
    sys = &GwSystem;
    if (masu == 0x73) {
        tree = D_8011BF6C_w04;
        masu = 0x7F;
    } else {
        tree = D_8011BF9C_w04;
        masu = 0x80;
    }
    func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    func_800ED20C_shared_board(-1, 8, masu);
    HuPrcSleep(8);
    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(0x3D, 0xB01);
    } else {
    loop:
        MBDlgWinInsertCreate(0x3D, 0xB00, 0, 0, 0, 0, 0);
        choice = func_80109CD4_w04(tree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                MBCoinChangeCreate(sys->current_player_index, -5);
                MBCoinTakeCreate(sys->current_player_index, -5);
                HuPrcSleep(30);
                MBDlgWinExec(0x3D, 0xB02);
                WipeCreateOut(0xB, 0x10);
                while (WipeStatGet()) {
                    HuPrcVSleep();
                }
                MBCameraFocusModeSet(0);
                func_800E9AF0_shared_board(&space->coords, 0);
                HuPrcSleep(5);
                WipeCreateIn(0xB, 0x10);
                while (WipeStatGet()) {
                    HuPrcVSleep();
                }
                func_80119FCC_w04(-1, 0);
                WipeCreateOut(0xB, 0x10);
                while (WipeStatGet()) {
                    HuPrcVSleep();
                }
                MBCameraFocusModeSet(1);
                HuPrcSleep(5);
                WipeCreateIn(0xB, 0x10);
                while (WipeStatGet()) {
                    HuPrcVSleep();
                }
                break;
            case 1:
                MBDlgWinExec(0x3D, 0xB04);
                break;
            default:
                func_80106AB0_w04();
                goto loop;
        }
    }
    func_800DB884_shared_board(sys->current_player_index);
    HuPrcSleep(10);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A5DC_w04);
#endif

// main func for reroll event in woody woods
void func_8011A858_w04(void) {
    GW_PLAYER *curPlayer;
    s16 curPlayerSpace;

    curPlayer = MBPlayerGet(CUR_PLAYER);
    curPlayerSpace = MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx);
    HuPrcSleep(8);
    switch (curPlayerSpace) {
        // space IDs for reroll event
        case 0x3F:
        case 0x49:
        case 0x4A:
            func_801183D4_w04();
            break;
        case 0x1F:
        case 0x21:
        case 0x22:
            func_801191B8_w04();
            break;
        case 0x4F:
            func_8011A4E0_w04(0);
            break;
        case 0xC:
            func_8011A4E0_w04(1);
            break;
        case 0x3B:
            func_8011A4E0_w04(2);
            break;
    }
    omDelPrcObj(NULL);
}

void func_8011A91C_w04(void) {
    Vec camPos;
    SpaceData *space;

    space = MBMasuGet(D_8011B9BC_w04[0]);
    if (GwSystem.current_turn >= 2) {
        HuVecCopy3F(&camPos, &space->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&camPos);
        HuPrcSleep(2);
        MBPlayerPosFixSet(0, 1);
        MBPlayerPosFixSet(1, 1);
        MBPlayerPosFixSet(2, 1);
        MBPlayerPosFixSet(3, 1);
        HuPrcChildLink(HuPrcCurrentGet(), func_800F29EC_shared_board());
        HuPrcChildWait();
        func_80119FCC_w04(-1, 1);
        HuPrcChildLink(HuPrcCurrentGet(), func_800F292C_shared_board());
        HuPrcChildWait();
        MBCameraFocusModeSet(1);
        HuPrcSleep(5);
    }
}

void func_8011AA10_w04(void) {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011CB18_w04);
    func_80107828_w04();
    MBStart(2);
    omAddPrcObj(func_80106120_w04, 0x1005, 0x1000, 0);
}

s32 func_8011AA64_w04(void) {
    s32 i;
    DecisionTreeNonLeafNode *tree;
    GW_SYSTEM *loc = &GwSystem;

    tree = D_8011D65C_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(D_8011D530_w04) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}

s32 func_8011AB34_w04(void) {
    s32 i;
    DecisionTreeNonLeafNode *tree1;
    DecisionTreeNonLeafNode *tree2;
    GW_SYSTEM *loc = &GwSystem;

    tree1 = D_8011DAC0_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    tree2 = D_8011DAE0_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(tree1) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree2) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}

s32 func_8011AC0C_w04(void) {
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

s32 func_8011AC60_w04(s32 base, s32 perLevel) {
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

s32 func_8011AD48_w04(void) {
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
                if (func_8011AC0C_w04() != 0) {
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
                if (MBRandCheck100(70) != 0 && func_8011AC0C_w04() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011AC0C_w04() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011CF48_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011AC0C_w04() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011CFB4_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011D1D0_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011D494_w04) == 0) {
                    s32 target = func_8011AA64_w04();

                    D_8011E114_w04 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011D838_w04) == 0) {
                    s32 target = func_8011AB34_w04();

                    D_8011E110_w04 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011E0D0_w04 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011E0D0_w04 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011E0D0_w04 == -1) {
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
                for (i = 0, D_8011E0CC_w04 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011E0CC_w04 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011E0CC_w04 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011AC60_w04(0x32, 0xA) == 0) {
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
                if (func_8011AC60_w04(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011D314_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011AC0C_w04() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011DB00_w04) != 0) {
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

s32 func_8011B350_w04(void) {
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
        temp_s0 = D_8011DCEC_w04[temp_s3->chr][i];
        var_s2 = func_8010AF34_w04(temp_s0);
        if (var_s2 != -1 && D_80100F94_shared_board[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(D_8011DD8C_w04[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((func_8010AF34_w04(0xE) != var_s2) &&
        ((func_8010AF34_w04(0xB) != var_s2) ||
        ((D_80100F94_shared_board[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((func_8010AF34_w04(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(D_8011DDAC_w04[D_8011C688_w04]) == 0) && GwPlayer[system->current_player_index].coin >= D_80100F94_shared_board[1]) {
        temp_v0 = func_8010AF34_w04(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(D_8011DDB4_w04[D_8011C688_w04]);
        if (i == 0) {
            do {
                temp_s0_2 = D_8011DCEC_w04[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = func_8010AF34_w04(temp_s0_2);
                    if ((var_s2_2 != -1) && !(D_80100F94_shared_board[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(D_8011DD8C_w04[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = func_8010AF34_w04(0);
        if (var_s2_2 == -1) {
            D_8011DC68_w04 = 1;
            return func_8010AFBC_w04() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}

s32 func_8011B6B4_w04(void) {
    if (D_8011DC68_w04 != 0) {
        D_8011DC68_w04 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011DDBC_w04[D_8011C688_w04]) + 1;
}

// board q4
/* .data (0x8011B740, 0x2700 bytes): the overlay's initialised data, in address order. */
s16 D_8011B740_w04[8] = { 0, 1, 2, 4, 6, 3, 5, 7 };
s16 D_8011B750_w04[8] = { 0, 0, 0, 0, 0, 1, 1, 1 };
s16 D_8011B760_w04[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011B770_w04[8] = { 75, 70, 22, 37, 53, 48, 9, 3 };
s16 D_8011B780_w04[8] = { 99, 100, 98, 97, 96, 95, 101, 94 };
s32 D_8011B790_w04[7] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };
s32 D_8011B7AC_w04[7] = { 24066, 24067, 24068, 24069, 24070, 24071, 24072 };
s32 D_8011B7C8_w04 = 0;
s16 D_8011B7CC_w04[1] = { -1 };
s16 D_8011B7D0_w04[10] = {
    75, 70, 22, 37, 53, 48, 9, 3,
    -1, 0,
};
s16 D_8011B7E4_w04[8][2] = {
    { 4, -4 },
    { 0, 0 },
    { 2, -4 },
    { 0, -4 },
    { 0, 0 },
    { 6, -6 },
    { 1, -2 },
    { 2, 0 },
};
s16 D_8011B804_w04[2][2] = {
    { 2, -4 },
    { 0, 0 },
};
s16 D_8011B80C_w04[2][2] = {
    { 0, 0 },
    { 2, 0 },
};
s16 D_8011B814_w04[2][2] = {
    { 0, -2 },
    { 0, -2 },
};
s16 D_8011B81C_w04[2][2] = {
    { 0, 0 },
    { 0, 0 },
};
s16 D_8011B824_w04[2][2] = {
    { 112, 136 },
    { 105, 107 },
};
s16 D_8011B82C_w04[8] = { 99, 100, 98, 97, 96, 95, 101, 94 };
s16 D_8011B83C_w04[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011B84C_w04[2] = { 125, 0 };
s16 D_8011B850_w04[2] = { 120, 110 };
Vec D_8011B854_w04[5] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f },
};
Vec D_8011B890_w04[5] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 2e+01f, 0.0f, -3e+01f },
    { 45.0f, 0.0f, 45.0f },
};
s16 D_8011B8CC_w04[2] = { 111, 106 };
s16 D_8011B8D0_w04[6] = { 38, 39, 40, 41, 42, 43 };
u32 D_8011B8DC_w04[2] = { 1, 0x130163 };
u32 D_8011B8E4_w04[2] = { 1, 0x130168 };
u32 D_8011B8EC_w04[2] = { 1, 0x13016F };
u32 D_8011B8F4_w04[2] = { 1, 0x130176 };
u32 D_8011B8FC_w04[2] = { 1, 0x130180 };
u32 D_8011B904_w04[2] = { 1, 0x130184 };
u32 *D_8011B90C_w04[6] = {
    D_8011B8DC_w04, D_8011B8E4_w04, D_8011B8EC_w04, D_8011B8F4_w04,
    D_8011B8FC_w04, D_8011B904_w04,
};
s32 D_8011B924_w04[9] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1,
};
s32 D_8011B948_w04[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011B96C_w04[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011B990_w04[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s16 D_8011B9B4_w04[2] = { 119, 109 };
s16 D_8011B9B8_w04[2] = { 117, 118 };
s16 D_8011B9BC_w04[4] = { 122, 121, 123, 0 };
s16 D_8011B9C4_w04[4] = { 0, 1, 2, 0 };
DecisionTreeNonLeafNode D_8011B9CC_w04[2] = {
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011B9E4_w04[2] = {
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011B9FC_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BA08_w04[3] = { D_8011B9CC_w04, D_8011B9E4_w04, D_8011B9FC_w04 };
DecisionTreeNonLeafNode D_8011BA14_w04[3] = {
    { 2, { .data = 0x0000000F }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000030 }, { .data = 0x164C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011BA38_w04[2] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BA50_w04[2] = {
    { 2, { .data = 0x000000C0 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BA68_w04[3] = { D_8011BA14_w04, D_8011BA38_w04, D_8011BA50_w04 };
DecisionTreeNonLeafNode D_8011BA74_w04[2] = {
    { 4, { .data = 0x00100000 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BA8C_w04[2] = {
    { 4, { .data = 0x00100000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BAA4_w04[4] = {
    { 2, { .data = 0x00000030 }, { .node_data = D_8011BA74_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011BA8C_w04 } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BAD4_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BAE0_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BAEC_w04[3] = { D_8011BAA4_w04, D_8011BAD4_w04, D_8011BAE0_w04 };
DecisionTreeNonLeafNode D_8011BAF8_w04[2] = {
    { 2, { .data = 0x000000CF }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011BB10_w04[2] = {
    { 2, { .data = 0x00000030 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BB28_w04[2] = {
    { 2, { .data = 0x00000030 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BB40_w04[3] = { D_8011BAF8_w04, D_8011BB10_w04, D_8011BB28_w04 };
DecisionTreeNonLeafNode D_8011BB4C_w04[3] = {
    { 2, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000C0 }, { .data = 0x08D19E3C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011BB70_w04[2] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BB88_w04[3] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BBAC_w04[3] = { D_8011BB4C_w04, D_8011BB70_w04, D_8011BB88_w04 };
DecisionTreeNonLeafNode D_8011BBB8_w04[3] = {
    { 2, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x18D19E3C } },
};
DecisionTreeNonLeafNode D_8011BBDC_w04[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x18D19E3C } },
};
DecisionTreeNonLeafNode D_8011BC00_w04[3] = {
    { 2, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BC24_w04[3] = { D_8011BBB8_w04, D_8011BBDC_w04, D_8011BC00_w04 };
DecisionTreeNonLeafNode D_8011BC30_w04[2] = {
    { 2, { .data = 0x0000001C }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BC48_w04[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode D_8011BC6C_w04[2] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x18D1A346 } },
};
DecisionTreeNonLeafNode *D_8011BC84_w04[3] = { D_8011BC30_w04, D_8011BC48_w04, D_8011BC6C_w04 };
DecisionTreeNonLeafNode D_8011BC90_w04[3] = {
    { 2, { .data = 0x00000070 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BCB4_w04[3] = {
    { 2, { .data = 0x00000070 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BCD8_w04[2] = {
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BCF0_w04[3] = { D_8011BC90_w04, D_8011BCB4_w04, D_8011BCD8_w04 };
DecisionTreeNonLeafNode D_8011BCFC_w04[2] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BD14_w04[2] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BD2C_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BD38_w04[3] = { D_8011BCFC_w04, D_8011BD14_w04, D_8011BD2C_w04 };
DecisionTreeNonLeafNode D_8011BD44_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BD50_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BD5C_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x18D1A346 } },
};
DecisionTreeNonLeafNode *D_8011BD68_w04[3] = { D_8011BD44_w04, D_8011BD50_w04, D_8011BD5C_w04 };
DecisionTreeNonLeafNode D_8011BD74_w04[3] = {
    { 2, { .data = 0x00000030 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000040 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BD98_w04[3] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000040 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BDBC_w04[3] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000030 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011BDE0_w04[3] = { D_8011BD74_w04, D_8011BD98_w04, D_8011BDBC_w04 };
DecisionTreeNonLeafNode D_8011BDEC_w04[2] = {
    { 2, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BE04_w04[2] = {
    { 2, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0A142346 } },
};
DecisionTreeNonLeafNode D_8011BE1C_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A142346 } },
};
DecisionTreeNonLeafNode *D_8011BE28_w04[3] = { D_8011BDEC_w04, D_8011BE04_w04, D_8011BE1C_w04 };
DecisionTreeNonLeafNode D_8011BE34_w04[2] = {
    { 2, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BE4C_w04[3] = {
    { 2, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000020 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BE70_w04[2] = {
    { 2, { .data = 0x00000020 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x18D1A346 } },
};
DecisionTreeNonLeafNode *D_8011BE88_w04[3] = { D_8011BE34_w04, D_8011BE4C_w04, D_8011BE70_w04 };
DecisionTreeNonLeafNode D_8011BE94_w04[4] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_8011BEC4_w04[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011BEE8_w04[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011BF0C_w04[3] = { D_8011BE94_w04, D_8011BEC4_w04, D_8011BEE8_w04 };
DecisionTreeNonLeafNode D_8011BF18_w04[2] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011BF30_w04[3] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011BF18_w04 } },
    { 4, { .data = 0x00000000 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011BF54_w04[2] = {
    { 4, { .data = 0x00000000 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011BF6C_w04[4] = {
    { 9, { .data = 0x00000006 }, { .node_data = D_8011BF30_w04 } },
    { 2, { .data = 0x00000001 }, { .node_data = D_8011BF54_w04 } },
    { 4, { .data = 0x00000000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011BF9C_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x03C78F1E } },
};
event_list_entry D_8011BFA8_w04[2] = {
    { 8, 1, func_801088C8_w04 },
    { 0, 0, NULL },
};
s16 D_8011BFB8_w04[3][3] = {
    { 43, 54, -1 },
    { 32, 54, -1 },
    { 32, 43, -1 },
};
BranchLink D_8011BFCC_w04[3][2] = {
    { { 2, 0, 0 }, { 3, 0, 0 } },
    { { 1, 24, 1 }, { 3, 0, 0 } },
    { { 1, 24, 1 }, { 2, 0, 0 } },
};
event_list_entry D_8011BFF0_w04[2] = {
    { 1, 2, func_801088FC_w04 },
    { 0, 0, NULL },
};
s16 D_8011C000_w04[3][3] = {
    { 80, 78, -1 },
    { 79, 78, -1 },
    { 79, 80, -1 },
};
BranchLink D_8011C014_w04[3][2] = {
    { { 4, 0, 0 }, { 9, 0, 0 } },
    { { 2, 6, 1 }, { 9, 0, 0 } },
    { { 2, 6, 1 }, { 4, 0, 0 } },
};
event_list_entry D_8011C038_w04[2] = {
    { 1, 2, func_80108934_w04 },
    { 0, 0, NULL },
};
s16 D_8011C048_w04[3][3] = {
    { 15, 92, -1 },
    { 83, 92, -1 },
    { 83, 15, -1 },
};
BranchLink D_8011C05C_w04[3][2] = {
    { { 6, 0, 0 }, { 5, 0, 0 } },
    { { 4, 3, 1 }, { 5, 0, 0 } },
    { { 4, 3, 1 }, { 6, 0, 0 } },
};
event_list_entry D_8011C080_w04[2] = {
    { 1, 1, func_801089B0_w04 },
    { 0, 0, NULL },
};
s16 D_8011C090_w04[3][3] = {
    { 11, 13, -1 },
    { 12, 13, -1 },
    { 12, 11, -1 },
};
BranchLink D_8011C0A4_w04[3][2] = {
    { { 7, 0, 0 }, { 8, 0, 0 } },
    { { 6, 1, 1 }, { 8, 0, 0 } },
    { { 6, 1, 1 }, { 7, 0, 0 } },
};
event_list_entry D_8011C0C8_w04[2] = {
    { 1, 2, func_80108A58_w04 },
    { 0, 0, NULL },
};
s16 D_8011C0D8_w04[3][3] = {
    { 64, 62, -1 },
    { 63, 62, -1 },
    { 63, 64, -1 },
};
BranchLink D_8011C0EC_w04[3][2] = {
    { { 10, 0, 0 }, { 11, 0, 0 } },
    { { 9, 5, 1 }, { 11, 0, 0 } },
    { { 9, 5, 1 }, { 10, 0, 0 } },
};
event_list_entry D_8011C110_w04[2] = {
    { 1, 2, func_80108AD4_w04 },
    { 0, 0, NULL },
};
s16 D_8011C120_w04[3][3] = {
    { 26, 27, -1 },
    { 59, 27, -1 },
    { 59, 26, -1 },
};
BranchLink D_8011C134_w04[3][2] = {
    { { 12, 0, 0 }, { 13, 0, 0 } },
    { { 11, 3, 1 }, { 13, 0, 0 } },
    { { 11, 3, 1 }, { 12, 0, 0 } },
};
event_list_entry D_8011C158_w04[2] = {
    { 1, 2, func_80108B4C_w04 },
    { 0, 0, NULL },
};
s16 D_8011C168_w04[3][3] = {
    { 39, 57, -1 },
    { 38, 57, -1 },
    { 38, 39, -1 },
};
BranchLink D_8011C17C_w04[3][2] = {
    { { 1, 0, 0 }, { 14, 0, 0 } },
    { { 13, 10, 1 }, { 14, 0, 0 } },
    { { 13, 10, 1 }, { 1, 0, 0 } },
};
event_list_entry D_8011C1A0_w04[2] = {
    { 1, 1, func_80108C00_w04 },
    { 0, 0, NULL },
};
s16 D_8011C1B0_w04[3][3] = {
    { 87, 136, -1 },
    { 65, 136, -1 },
    { 65, 87, -1 },
};
BranchLink D_8011C1C4_w04[3][2] = {
    { { 3, 3, 0 }, { 5, 3, 1 } },
    { { 3, 1, 1 }, { 5, 3, 1 } },
    { { 3, 1, 1 }, { 3, 3, 0 } },
};
event_list_entry D_8011C1E8_w04[2] = {
    { 1, 1, func_80108CA8_w04 },
    { 0, 0, NULL },
};
s16 D_8011C1F8_w04[3][3] = {
    { 3, 5, -1 },
    { 1, 5, -1 },
    { 1, 3, -1 },
};
BranchLink D_8011C20C_w04[3][2] = {
    { { 1, 19, 0 }, { 1, 17, 1 } },
    { { 3, 4, 1 }, { 1, 17, 1 } },
    { { 3, 4, 1 }, { 1, 19, 0 } },
};
event_list_entry D_8011C230_w04[2] = {
    { 1, 1, func_80108D00_w04 },
    { 0, 0, NULL },
};
s16 D_8011C240_w04[3][3] = {
    { 84, 86, -1 },
    { 90, 86, -1 },
    { 90, 84, -1 },
};
BranchLink D_8011C254_w04[3][2] = {
    { { 2, 5, 0 }, { 10, 11, 1 } },
    { { 2, 3, 1 }, { 10, 11, 1 } },
    { { 2, 3, 1 }, { 2, 5, 0 } },
};
event_list_entry D_8011C278_w04[2] = {
    { 1, 1, func_80108D58_w04 },
    { 0, 0, NULL },
};
s16 D_8011C288_w04[3][3] = {
    { 104, 17, -1 },
    { 19, 17, -1 },
    { 19, 104, -1 },
};
BranchLink D_8011C29C_w04[3][2] = {
    { { 12, 8, 0 }, { 8, 3, 1 } },
    { { 12, 6, 1 }, { 8, 3, 1 } },
    { { 12, 6, 1 }, { 12, 8, 0 } },
};
event_list_entry D_8011C2C0_w04[2] = {
    { 1, 1, func_80108DB0_w04 },
    { 0, 0, NULL },
};
s16 D_8011C2D0_w04[3][3] = {
    { 45, 56, -1 },
    { 42, 56, -1 },
    { 42, 45, -1 },
};
BranchLink D_8011C2E4_w04[3][2] = {
    { { 1, 6, 0 }, { 12, 12, 1 } },
    { { 1, 4, 1 }, { 12, 12, 1 } },
    { { 1, 4, 1 }, { 1, 6, 0 } },
};
event_list_entry D_8011C308_w04[2] = {
    { 1, 1, func_80108E08_w04 },
    { 0, 0, NULL },
};
s16 D_8011C318_w04[3][3] = {
    { 7, 8, -1 },
    { 50, 8, -1 },
    { 50, 7, -1 },
};
BranchLink D_8011C32C_w04[3][2] = {
    { { 1, 15, 0 }, { 7, 2, 1 } },
    { { 1, 13, 1 }, { 7, 2, 1 } },
    { { 1, 13, 1 }, { 1, 15, 0 } },
};
event_list_entry D_8011C350_w04[2] = {
    { 1, 1, func_80108E60_w04 },
    { 0, 0, NULL },
};
s16 D_8011C360_w04[3][3] = {
    { 23, 107, -1 },
    { 25, 107, -1 },
    { 25, 23, -1 },
};
BranchLink D_8011C374_w04[3][2] = {
    { { 12, 3, 0 }, { 14, 4, 1 } },
    { { 12, 1, 1 }, { 14, 4, 1 } },
    { { 12, 1, 1 }, { 12, 3, 0 } },
};
event_list_entry D_8011C398_w04[2] = {
    { 1, 1, func_80108EB8_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3A8_w04[2] = {
    { 1, 1, func_80108F10_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3B8_w04[2] = {
    { 1, 1, func_80108F70_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3C8_w04[2] = {
    { 1, 1, func_80108FD0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3D8_w04[2] = {
    { 1, 1, func_80109030_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3E8_w04[2] = {
    { 1, 1, func_80109090_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C3F8_w04[2] = {
    { 1, 1, func_801090F0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C408_w04[2] = {
    { 1, 1, func_80109150_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C418_w04[2] = {
    { 1, 1, func_801091B0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C428_w04[2] = {
    { 1, 1, func_80109210_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C438_w04[2] = {
    { 1, 1, func_80109270_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C448_w04[2] = {
    { 1, 1, func_801092D0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C458_w04[2] = {
    { 1, 1, func_80109330_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C468_w04[2] = {
    { 1, 1, func_80109390_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C478_w04[2] = {
    { 1, 1, func_801093F0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C488_w04[2] = {
    { 1, 1, func_80109450_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C498_w04[2] = {
    { 1, 1, func_801094B0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4A8_w04[2] = {
    { 1, 1, func_80109510_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4B8_w04[2] = {
    { 1, 1, func_80109570_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4C8_w04[2] = {
    { 1, 1, func_801095D0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4D8_w04[2] = {
    { 1, 1, func_80109630_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4E8_w04[2] = {
    { 1, 2, func_801098A0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C4F8_w04[2] = {
    { 1, 1, func_8010A054_w04 },
    { 0, 0, NULL },
};
DecisionTreeNonLeafNode D_8011C508_w04[2] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } },
};
u32 D_8011C520_w04[2] = { 1, 0xA009D };
event_list_entry D_8011C528_w04[2] = {
    { 1, 1, func_8010A400_w04 },
    { 0, 0, NULL },
};
u8 D_8011C538_w04[2][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
};
s8 D_8011C550_w04[2][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } },
};
u8 D_8011C598_w04[2][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
};
s8 D_8011C5B0_w04[2][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } },
};
u8 D_8011C614_w04[2][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 },
};
s32 D_8011C628_w04[5][2] = {
    { 15109, 15621 },
    { 15110, 15622 },
    { 15111, 15623 },
    { 15112, 15624 },
    { 15113, 15625 },
};
s32 D_8011C650_w04[2] = { 15104, 15616 };
s32 D_8011C658_w04[2] = { 15105, 15617 };
s32 D_8011C660_w04[2] = { 15106, 15618 };
s32 D_8011C668_w04[2] = { 15107, 15619 };
s32 D_8011C670_w04[2] = { 15108, 15620 };
u32 D_8011C678_w04[2] = { 1, 0xA0017 };
u32 D_8011C680_w04[2] = { 1, 0xA00F0 };
s32 D_8011C688_w04 = 0;
event_list_entry D_8011C68C_w04[2] = {
    { 1, 1, func_8010B1FC_w04 },
    { 0, 0, NULL },
};
Vec2f D_8011C69C_w04[4] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f },
};
Vec2f D_8011C6BC_w04[4] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f },
};
u8 D_8011C6DC_w04[6][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 },
};
u8 D_8011C6F0_w04[14][3] = {
    { 0, 0, 0 },
    { 1, 10, 1 },
    { 11, 11, 4 },
    { 12, 14, 2 },
    { 15, 15, 4 },
    { 16, 23, 3 },
    { 24, 33, 4 },
    { 34, 37, 5 },
    { 38, 39, 2 },
    { 40, 49, 6 },
    { 50, 54, 5 },
    { 55, 63, 7 },
    { 64, 64, 8 },
    { 65, 255, 9 },
};
u8 D_8011C71C_w04[8] = { 9, 7, 4, 1, 0, 0, 0, 0 };
s32 D_8011C724_w04[3] = { 50, 80, 100 };
s32 D_8011C730_w04[7] = { 1, 0, 1, 0, 0, 1, 0 };
event_list_entry D_8011C74C_w04[2] = {
    { 1, 1, func_8010DA1C_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C75C_w04[2] = {
    { 1, 1, func_8010EBF0_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C76C_w04[2] = {
    { 1, 1, func_8010EC0C_w04 },
    { 0, 0, NULL },
};
event_table_entry D_8011C77C_w04[15] = {
    { 75, D_8011C4F8_w04 },
    { 70, D_8011C4F8_w04 },
    { 22, D_8011C4F8_w04 },
    { 37, D_8011C4F8_w04 },
    { 53, D_8011C4F8_w04 },
    { 48, D_8011C4F8_w04 },
    { 9, D_8011C4F8_w04 },
    { 3, D_8011C4F8_w04 },
    { 61, D_8011C528_w04 },
    { 6, D_8011C528_w04 },
    { 113, D_8011C68C_w04 },
    { 140, D_8011C68C_w04 },
    { 111, D_8011C75C_w04 },
    { 106, D_8011C76C_w04 },
    { -1, NULL },
};
event_table_entry D_8011C7F4_w04[2] = {
    { 141, D_8011C74C_w04 },
    { -1, NULL },
};
Vec2f D_8011C804_w04[4] = {
    { 164.0f, 76.0f },
    { 1.4e+02f, 76.0f },
    { 164.0f, 76.0f },
    { 1.4e+02f, 76.0f },
};
Vec2f D_8011C824_w04[4] = {
    { 132.0f, 62.0f },
    { 2.2e+02f, 62.0f },
    { 132.0f, 1.8e+02f },
    { 2.2e+02f, 1.8e+02f },
};
Vec2f D_8011C844_w04[4] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
};
Vec2f D_8011C864_w04[4] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
};
DecisionTreeNonLeafNode D_8011C884_w04[9] = {
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
s32 D_8011C8F0_w04[5] = { 20, 60, 30, 50, 70 };
DecisionTreeNonLeafNode D_8011C904_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
Vec2f D_8011C910_w04[6] = {
    { -1e+01f, 0.0f },
    { 1e+01f, -5.0f },
    { 1e+01f, 5.0f },
    { -5.0f, -5.0f },
    { 1e+01f, 0.0f },
    { -5.0f, 5.0f },
};
s32 D_8011C940_w04 = -1;
u8 D_8011C944_w04[4] = { 67, 68, 69, 0 };
u8 D_8011C948_w04[4] = { 20, 60, 100, 0 };
u16 D_8011C94C_w04[7][2] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 },
};
RGB D_8011C968_w04[2] = {
    { 240, 222, 53 },
    { 247, 26, 66 },
};
event_list_entry D_8011C970_w04[3] = {
    { 7, 1, func_80116740_w04 },
    { 7, 1, func_80117074_w04 },
    { 0, 0, NULL },
};
event_table_entry D_8011C988_w04[2] = {
    { -5, D_8011C970_w04 },
    { -1, NULL },
};
s16 D_8011C998_w04[2] = { 133, 132 };
s16 D_8011C99C_w04[2] = { 134, 135 };
event_list_entry D_8011C9A0_w04[2] = {
    { 1, 1, func_8011A5DC_w04 },
    { 0, 0, NULL },
};
event_list_entry D_8011C9B0_w04[2] = {
    { 7, 1, func_8011A91C_w04 },
    { 0, 0, NULL },
};
event_table_entry D_8011C9C0_w04[43] = {
    { 102, D_8011BFA8_w04 },
    { 103, D_8011BFF0_w04 },
    { 116, D_8011C038_w04 },
    { 114, D_8011C080_w04 },
    { 139, D_8011C0C8_w04 },
    { 108, D_8011C110_w04 },
    { 143, D_8011C158_w04 },
    { 142, D_8011C1A0_w04 },
    { 76, D_8011C1E8_w04 },
    { 2, D_8011C230_w04 },
    { 85, D_8011C278_w04 },
    { 18, D_8011C2C0_w04 },
    { 44, D_8011C308_w04 },
    { 51, D_8011C350_w04 },
    { 24, D_8011C398_w04 },
    { 39, D_8011C3A8_w04 },
    { 43, D_8011C3B8_w04 },
    { 54, D_8011C3C8_w04 },
    { 1, D_8011C3D8_w04 },
    { 80, D_8011C3E8_w04 },
    { 92, D_8011C3F8_w04 },
    { 15, D_8011C408_w04 },
    { 11, D_8011C418_w04 },
    { 8, D_8011C428_w04 },
    { 13, D_8011C438_w04 },
    { 17, D_8011C448_w04 },
    { 78, D_8011C458_w04 },
    { 64, D_8011C468_w04 },
    { 86, D_8011C478_w04 },
    { 62, D_8011C488_w04 },
    { 26, D_8011C498_w04 },
    { 56, D_8011C4A8_w04 },
    { 27, D_8011C4B8_w04 },
    { 57, D_8011C4C8_w04 },
    { 0, D_8011C4D8_w04 },
    { 112, D_8011C4E8_w04 },
    { 105, D_8011C4E8_w04 },
    { 136, D_8011C4E8_w04 },
    { 107, D_8011C4E8_w04 },
    { -2, D_8011C9B0_w04 },
    { 115, D_8011C9A0_w04 },
    { 104, D_8011C9A0_w04 },
    { -1, NULL },
};
RectF D_8011CB18_w04 = { 0.0f, 0.0f, 3.2e+02f, 2.4e+02f };
DecisionTreeNonLeafNode D_8011CB28_w04[4] = {
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000A0007 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090306 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CB58_w04[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011CB28_w04 } },
    { 10, { .data = 0x00020003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A000B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090306 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00011019 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CBB8_w04[3] = {
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000A0507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CBDC_w04[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00090006 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011CBB8_w04 } },
    { 10, { .data = 0x00020007 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A080B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CC30_w04[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 4, { .data = 0x00200001 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0103 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CC84_w04[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000D0004 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00200000 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0103 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CCE4_w04[5] = {
    { 4, { .data = 0x00100000 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CD20_w04[5] = {
    { 10, { .data = 0x000B0103 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CD5C_w04[12] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000C0003 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00200001 }, { .node_data = D_8011CCE4_w04 } },
    { 4, { .data = 0x00100000 }, { .node_data = D_8011CD20_w04 } },
    { 10, { .data = 0x000B0103 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CDEC_w04[9] = {
    { 12, { .data = 0x00000005 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000E0001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D000B }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000C000C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010304 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CE58_w04[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 4, { .data = 0x00100001 }, { .data = 0x01428A1E } },
    { 4, { .data = 0x00000001 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00020007 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00011219 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A090B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CEAC_w04[13] = {
    { 12, { .data = 0x0000000A }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D090A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000E0001 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0001030D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000C070C }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00100001 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011CF48_w04[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011CB58_w04 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011CBDC_w04 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011CC30_w04 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011CC84_w04 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011CD5C_w04 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011CDEC_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011CE58_w04 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011CEAC_w04 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011CFB4_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A141932 } },
};
DecisionTreeNonLeafNode D_8011CFC0_w04[7] = {
    { 10, { .data = 0x00090001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00020007 }, { .data = 0x0001038A } },
    { 10, { .data = 0x000A090B }, { .data = 0x0001038A } },
    { 11, { .data = 0x00090001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00020007 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000A090B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D014_w04[5] = {
    { 10, { .data = 0x000A0004 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00090305 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000A0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090305 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D050_w04[5] = {
    { 10, { .data = 0x000C0003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x000B0004 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000C0003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D08C_w04[3] = {
    { 10, { .data = 0x000D0008 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000D0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D0B0_w04[5] = {
    { 10, { .data = 0x000C0109 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000C0109 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D0EC_w04[5] = {
    { 10, { .data = 0x0001020A }, { .data = 0x0001038A } },
    { 10, { .data = 0x000C0A0C }, { .data = 0x0001038A } },
    { 11, { .data = 0x0001020A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D128_w04[9] = {
    { 10, { .data = 0x00070000 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00060002 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00040004 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00050000 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00070000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D194_w04[5] = {
    { 10, { .data = 0x00010A12 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030004 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00010A12 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011D1D0_w04[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011CFC0_w04 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D014_w04 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011D050_w04 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011D08C_w04 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D0B0_w04 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D0EC_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011D128_w04 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011D194_w04 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D23C_w04[2] = {
    { 10, { .data = 0x00090001 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D254_w04[2] = {
    { 10, { .data = 0x000A0004 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D26C_w04[2] = {
    { 10, { .data = 0x000C0003 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D284_w04[2] = {
    { 10, { .data = 0x000D0308 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D29C_w04[3] = {
    { 10, { .data = 0x000C0409 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D2C0_w04[2] = {
    { 10, { .data = 0x0001050A }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D2D8_w04[2] = {
    { 10, { .data = 0x00070000 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D2F0_w04[3] = {
    { 10, { .data = 0x00010D12 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030004 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011D314_w04[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D23C_w04 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D254_w04 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011D26C_w04 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011D284_w04 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D29C_w04 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D2C0_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011D2D8_w04 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011D2F0_w04 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D380_w04[3] = {
    { 4, { .data = 0x00000000 }, { .data = 0x1B54233C } },
    { 11, { .data = 0x00020305 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D3A4_w04[2] = {
    { 11, { .data = 0x000A0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D3BC_w04[4] = {
    { 11, { .data = 0x000C0001 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00200001 }, { .data = 0x1B54233C } },
    { 11, { .data = 0x000B0102 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D3EC_w04[2] = {
    { 11, { .data = 0x000D0106 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D404_w04[3] = {
    { 11, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0306 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D428_w04[2] = {
    { 11, { .data = 0x00010306 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D440_w04[4] = {
    { 4, { .data = 0x00100001 }, { .data = 0x1B54233C } },
    { 11, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040103 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D470_w04[3] = {
    { 11, { .data = 0x00011010 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D494_w04[13] = {
    { 10, { .data = 0x00010D0F }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070202 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090405 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D380_w04 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D3A4_w04 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011D3BC_w04 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011D3EC_w04 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D404_w04 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D428_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011D440_w04 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011D470_w04 } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D530_w04[5] = {
    { 15, { .data = 0x00010D0F }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00070202 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B0000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00090405 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D56C_w04[2] = {
    { 15, { .data = 0x00020305 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D584_w04[2] = {
    { 15, { .data = 0x000A0002 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D59C_w04[3] = {
    { 15, { .data = 0x000C0001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B0102 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D5C0_w04[2] = {
    { 15, { .data = 0x000D0106 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D5D8_w04[3] = {
    { 15, { .data = 0x00080003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000C0306 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D5FC_w04[2] = {
    { 15, { .data = 0x00010306 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D614_w04[3] = {
    { 15, { .data = 0x00050000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040103 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D638_w04[3] = {
    { 15, { .data = 0x00011010 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00030003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode *D_8011D65C_w04[8] = {
    D_8011D56C_w04, D_8011D584_w04, D_8011D59C_w04, D_8011D5C0_w04,
    D_8011D5D8_w04, D_8011D5FC_w04, D_8011D614_w04, D_8011D638_w04,
};
DecisionTreeNonLeafNode D_8011D67C_w04[6] = {
    { 10, { .data = 0x00090305 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D6C4_w04[4] = {
    { 10, { .data = 0x000A060B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000A0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D6F4_w04[4] = {
    { 10, { .data = 0x000C050B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D724_w04[5] = {
    { 10, { .data = 0x000D0A0A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000E0001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010009 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000D0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D760_w04[6] = {
    { 10, { .data = 0x000C0B0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0001060A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0409 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D7A8_w04[2] = {
    { 10, { .data = 0x00010C12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D7C0_w04[6] = {
    { 10, { .data = 0x00070202 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010F14 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D808_w04[4] = {
    { 10, { .data = 0x00011417 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010309 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00010C12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D838_w04[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D67C_w04 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D6C4_w04 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011D6F4_w04 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011D724_w04 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D760_w04 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D7A8_w04 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011D7C0_w04 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011D808_w04 } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011D8A4_w04[5] = {
    { 15, { .data = 0x00090305 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000A0002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B0002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D8E0_w04[3] = {
    { 15, { .data = 0x000A060B }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D904_w04[3] = {
    { 15, { .data = 0x000C050B }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D928_w04[4] = {
    { 15, { .data = 0x000D0A0A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000E0001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010009 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D958_w04[4] = {
    { 15, { .data = 0x000C0B0C }, { .data = 0x0C993264 } },
    { 15, { .data = 0x0001060A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D988_w04[2] = {
    { 15, { .data = 0x00010C12 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D9A0_w04[4] = {
    { 15, { .data = 0x00070202 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010F14 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D9D0_w04[3] = {
    { 15, { .data = 0x00011417 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00010309 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011D9F4_w04[2] = {
    { 15, { .data = 0x00090001 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA0C_w04[2] = {
    { 15, { .data = 0x000A0004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA24_w04[2] = {
    { 15, { .data = 0x000C0003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA3C_w04[2] = {
    { 15, { .data = 0x000D0008 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA54_w04[3] = {
    { 15, { .data = 0x000C0409 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00080003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA78_w04[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DA84_w04[3] = {
    { 15, { .data = 0x00070000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DAA8_w04[2] = {
    { 15, { .data = 0x00010C12 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode *D_8011DAC0_w04[8] = {
    D_8011D8A4_w04, D_8011D8E0_w04, D_8011D904_w04, D_8011D928_w04,
    D_8011D958_w04, D_8011D988_w04, D_8011D9A0_w04, D_8011D9D0_w04,
};
DecisionTreeNonLeafNode *D_8011DAE0_w04[8] = {
    D_8011D9F4_w04, D_8011DA0C_w04, D_8011DA24_w04, D_8011DA3C_w04,
    D_8011DA54_w04, D_8011DA78_w04, D_8011DA84_w04, D_8011DAA8_w04,
};
DecisionTreeNonLeafNode D_8011DB00_w04[1] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011D1D0_w04 } },
};
DecisionTreeNonLeafNode D_8011DB0C_w04[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000080 }, { .data = 0x01450F28 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB30_w04[2] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB48_w04[2] = {
    { 2, { .data = 0x000000BC }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB60_w04[2] = {
    { 2, { .data = 0x0000005F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DB78_w04[2] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011DB90_w04[5] = {
    { 9, { .data = 0x00000007 }, { .node_data = D_8011DB78_w04 } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } },
};
DecisionTreeNonLeafNode D_8011DBCC_w04[3] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DB90_w04 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011DBF0_w04[2] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011DC08_w04[5] = {
    { 9, { .data = 0x00000004 }, { .node_data = D_8011DBF0_w04 } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } },
};
DecisionTreeNonLeafNode D_8011DC44_w04[3] = {
    { 2, { .data = 0x00000020 }, { .node_data = D_8011DC08_w04 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
s32 D_8011DC68_w04 = 0;
u8 D_8011DC6C_w04[16] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1,
};
u8 D_8011DC7C_w04[16] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5,
};
u8 D_8011DC8C_w04[16] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1,
};
u8 D_8011DC9C_w04[16] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1,
};
u8 D_8011DCAC_w04[16] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1,
};
u8 D_8011DCBC_w04[16] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1,
};
u8 D_8011DCCC_w04[16] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1,
};
u8 D_8011DCDC_w04[16] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5,
};
u8 *D_8011DCEC_w04[8] = {
    D_8011DC6C_w04, D_8011DC7C_w04, D_8011DC8C_w04, D_8011DC9C_w04,
    D_8011DCAC_w04, D_8011DCBC_w04, D_8011DCCC_w04, D_8011DCDC_w04,
};
s8 D_8011DD0C_w04[16] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011DD1C_w04[16] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0,
};
s8 D_8011DD2C_w04[16] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10,
};
s8 D_8011DD3C_w04[16] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011DD4C_w04[16] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10,
};
s8 D_8011DD5C_w04[16] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011DD6C_w04[16] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10,
};
s8 D_8011DD7C_w04[16] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10,
};
s8 *D_8011DD8C_w04[8] = {
    D_8011DD0C_w04, D_8011DD1C_w04, D_8011DD2C_w04, D_8011DD3C_w04,
    D_8011DD4C_w04, D_8011DD5C_w04, D_8011DD6C_w04, D_8011DD7C_w04,
};
DecisionTreeNonLeafNode *D_8011DDAC_w04[2] = { D_8011DB0C_w04, D_8011DB30_w04 };
DecisionTreeNonLeafNode *D_8011DDB4_w04[2] = { D_8011DB48_w04, D_8011DB60_w04 };
DecisionTreeNonLeafNode *D_8011DDBC_w04[5] = {
    D_8011DBCC_w04, D_8011DC44_w04, NULL, NULL,
    NULL,
};
u8 D_8011DDD0_w04[4] = { 1, 2, 4, 8 };
char D_8011DDD4_w04[4] = "%d";
const f64 D_8011DDD8_w04 __attribute__((section(".data"))) = 1.5;
const G3SparkDirs D_8011DDE0_w04 __attribute__((section(".data"))) = { {
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 2.0f, 1.0f }, { 0.0f, 2.0f, 1.0f }, { -1.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 1.0f }, { -1.0f, 2.0f, 1.0f }, { 1.0f, -1.0f, 1.0f },
} };
