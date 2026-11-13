#include "common.h"
#include "105D50.h"
#include "ECA50.h"
#include "FA250.h"
#include "F9DE0.h"

/* This unit's .data (0x801011A0-0x80101630) also holds the data of the units after it in the
 * ROM (FA250, FFB10, 1006F0, 101840): retail linked them from 16-byte-aligned files, so each of
 * their starts is padded to 16 (SB_DATA_FILE_END). Their C keeps `extern` declarations. */
#ifdef NON_MATCHING
#define SB_DATA_FILE_END()
#else
#define SB_DATA_FILE_END() __asm__(".section .data\n    .align 4\n");
#endif

void func_80017358_main(s16 arg0, char* arg1, s16 arg2, char* arg3);

extern s16 D_80102DA0_shared_board;
extern Object* D_80105710_shared_board;

extern const char D_8010226C_shared_board[];
extern const char D_80102280_shared_board[];
extern const char D_80102290_shared_board[];
extern const char D_801022A0_shared_board[];
extern const char D_801022B8_shared_board[];
extern const char D_801022CC_shared_board[];

/* F9DE0: Koopa Kid suit model (MBKSuit*) */
u32 D_801011A0_shared_board[] = { 7, 0x000A004D, 0x000A004D, 0x000A004E, 0x000A0051, 0x000A0052, 0x000A0050, 0x000A0058 };
/* suit attach node per character (GW_PLAYER.chr) */
const char* D_801011C0_shared_board[] = {
    D_801022CC_shared_board, D_801022B8_shared_board, D_801022A0_shared_board, D_80102290_shared_board,
    D_80102280_shared_board, D_8010226C_shared_board, D_801022B8_shared_board, D_801022A0_shared_board,
};
u32 D_801011E0_shared_board[] = { 6, 0x000A0037, 0x000A0033, 0x000A0031, 0x000A0034, 0x000A0036, 0x000A003C };
Object* D_801011FC_shared_board = NULL;
omObjData* D_80101200_shared_board = NULL;
/* pairs: { motion id, file in directory 0x0A } */
u16 D_80101204_shared_board[24] = {
    0x0001, 0x004D, 0x0002, 0x004D, 0x0004, 0x004E, 0x0036, 0x0051, 0x0015, 0x0052, 0x0032, 0x0050,
    0x0035, 0x0058, 0x000A, 0x0053, 0x0070, 0x0055, 0x0010, 0x0054, 0x001A, 0x0056, 0x000F, 0x0057,
};
SB_DATA_FILE_END()

/* FA250: board model and spaces */
s32* D_80101240_shared_board = NULL;
u32* D_80101244_shared_board = NULL;
struct UnkModelStruct* D_80101248_shared_board = NULL;
u8 D_8010124C_shared_board = 0xFF;
f32 D_80101250_shared_board = 1.0f;
f32 D_80101254_shared_board = 0.0f;
f32 D_80101258_shared_board = 0.0f;
Vec D_8010125C_shared_board = { 0.0f, 0.0f, 0.0f };
s32 D_80101268_shared_board = 0;
u8 D_8010126C_shared_board = 0xFF;
Gfx D_80101270_shared_board[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};
Process* D_801012B8_shared_board = NULL;
s32 D_801012BC_shared_board = 1;
void* D_801012C0_shared_board = NULL;
u8 (*D_801012C4_shared_board)[SPACES_MAX] = NULL;
/* space bitmap files per space type, board set 0 and 1 (MBMasuBmpCreate) */
s32 D_801012C8_shared_board[] = {
    0, 0x00130215, 0x00130216, 0, 0x00130219, 0x0013021F, 0x00130218, 0x0013021D,
    0, 0x00130217, 0, 0, 0x0013021E, 0x00130222, 0x0013021B, 0x0013021A,
};
u8 D_80101308_shared_board[] = { 0, 2, 2, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1 };
s32 D_80101318_shared_board[] = {
    0, 0x00130248, 0x00130249, 0, 0x0013024B, 0x0013024C, 0x00130250, 0x0013024D,
    0, 0x0013024F, 0, 0, 0x00130251, 0x0013024E, 0x00130252, 0x0013024A,
};
/* two 200x200 quads (32x32 and 8x8 texels): FA250.c's space-marker draw loads them by their physical
   addresses D_101358 ([0]) and D_101398 ([4]), absolute symbols in the matching build */
Vtx D_80101358_shared_board[] = {
    { { { 100, 0, -100 }, 0, { 992, 992 }, { 0, 0, 0x7F, 0xFF } } },
    { { { -100, 0, -100 }, 0, { 0, 992 }, { 0, 0, 0x7F, 0xFF } } },
    { { { -100, 0, 100 }, 0, { 0, 0 }, { 0, 0, 0x7F, 0xFF } } },
    { { { 100, 0, 100 }, 0, { 992, 0 }, { 0, 0, 0x7F, 0xFF } } },
    { { { 100, 0, -100 }, 0, { 224, 224 }, { 0, 0, 0x7F, 0xFF } } },
    { { { -100, 0, -100 }, 0, { 0, 224 }, { 0, 0, 0x7F, 0xFF } } },
    { { { -100, 0, 100 }, 0, { 0, 0 }, { 0, 0, 0x7F, 0xFF } } },
    { { { 100, 0, 100 }, 0, { 224, 0 }, { 0, 0, 0x7F, 0xFF } } },
};
Gfx D_801013D8_shared_board[] = {
    gsSPSegment(0x00, 0x00000000),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};
u8 D_80101468_shared_board[] = {
    0x01, 0x02, 0x04, 0x01, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};
SB_DATA_FILE_END()

/* FFB10 */
s16 D_80101480_shared_board = 0;
s16 D_80101482_shared_board = 0;
SB_DATA_FILE_END()

/* 1006F0 */
s32 D_80101490_shared_board[] = { 5, 25, 60, 0 };

/* 101840 */
s32 mbCharNameMesTbl[] = { 0x1C00, 0x1C01, 0x1C02, 0x1C03, 0x1C04, 0x1C05, 0x1C06, 0x1C07 };
u8 D_801014C0_shared_board[] = { 34, 62, 84, 100 };
SB_DATA_FILE_END()
s32 D_801014D0_shared_board[] = { 0x0013007D, 0x0013007E, 0x0013007F, 0x00130080, 0x00130081, 0x00130082 };
s16 D_801014E8_shared_board = 0;
s16 D_801014EA_shared_board = 0;
s32 D_801014EC_shared_board = 0;
s32 D_801014F0_shared_board = 0;
/* RGB colours */
u8 D_801014F4_shared_board[][3] = {
    { 0xFE, 0xFF, 0xA4 }, { 0xB0, 0xFF, 0xA4 }, { 0xFF, 0xA4, 0xAC }, { 0xA4, 0xE7, 0xFF }, { 0xCC, 0xFF, 0x83 },
};
s32 D_80101504_shared_board[] = { 0x00130084, 0x00130085, 0x00130086, 0x00130087 };
s32 D_80101514_shared_board[] = { 0x3001, 0x300A, 0x3004 };
s32 D_80101520_shared_board[] = { 0x5101, 0x5105, 0x5127, 0x512C, 0x5121, 0x5108, 0x510C, 0x5110 };
s32 D_80101540_shared_board[] = {
    0x0013008C, 0x0013008D, 0x0013008F, 0x00130092, 0x00130095, 0x00130099, 0x0013009B, 0x0013009A,
};
s32 D_80101560_shared_board[] = { 0x0013008D, 0x0013008E };
s32 D_80101568_shared_board[] = { 0x0013008F, 0x00130090 };
s32 D_80101570_shared_board[] = { 0x00130091, 0x00130092, 0x00130093 };
s32 D_8010157C_shared_board[] = { 0x00130094, 0x00130095, 0x00130096 };
s32 D_80101588_shared_board[] = { 0x00130097, 0x00130098, 0x00130099 };
s32 D_80101594_shared_board = 0x001300B1;
s32 D_80101598_shared_board = 0x001300B2;
s32 D_8010159C_shared_board = 0x0013009D;
s32 D_801015A0_shared_board[] = { 0x511F, 0x5120 };
s32 D_801015A8_shared_board[] = {
    0x00130107, 0x00130108, 0x00130109, 0x0013010A, 0x0013010B, 0x0013010C, 0x0013010D, 0x0013010E,
};
s32 D_801015C8_shared_board[] = {
    0x0013009E, 0x0013009F, 0x001300A0, 0x001300A1, 0x001300A2, 0x001300A6, 0x001300A5, 0x001300A4, 0x001300A3,
};
/* model slot per pad / per CPU difficulty, two each */
s8 D_801015EC_shared_board[] = { 0, -1, 1, -1, 2, -1, 3, -1 };
s8 D_801015F4_shared_board[] = { 4, 8, 4, 7, 4, 6, 4, 5 };
s16 D_801015FC_shared_board[] = { 100, 236, 100, 236 };
s16 D_80101604_shared_board[] = { 50, 50, 122, 122 };
s16 D_8010160C_shared_board[][4] = {
    { 0, 2, 0, 1 }, { 0, 2, -1, 0 }, { -2, 0, 0, 1 }, { -2, 0, -1, 0 },
};

static void MBKSuitMain(omObjData* arg0) {
    GW_PLAYER* player;

    player = MBPlayerGet(arg0->work[0]);
    HuVecCopy3F(&D_801011FC_shared_board->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_801011FC_shared_board->rot, &player->player_obj->rot);
    HuVecCopy3F(&D_801011FC_shared_board->scale, &player->player_obj->scale);
    D_801011FC_shared_board->velocity.x = player->player_obj->velocity.x;
    D_801011FC_shared_board->flags &= ~1;
    D_801011FC_shared_board->flags = D_801011FC_shared_board->flags | (player->player_obj->flags & 1);
}


const char D_801021F0_shared_board[] = " 1 VS 1 GAME";
const char D_80102200_shared_board[] = " BATTLE GAME";
const char D_80102210_shared_board[] = " ITEM   GAME";
const char D_80102220_shared_board[] = " 2 VS 2 GAME";
const char D_80102230_shared_board[] = " 1 VS 3 GAME";
const char D_80102240_shared_board[] = "4=PLAYER GAME";
/* used by F5E80 (MBItem*) */
const SomeStruct D_80102250_shared_board = { { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 } };
const SomeStruct2 D_8010225C_shared_board = { { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 } };
const char D_8010226C_shared_board[] = "c005_000-bmerge1";
const char D_80102280_shared_board[] = "Luigi1-atama_1";
const char D_80102290_shared_board[] = "c003_000-head_1";
const char D_801022A0_shared_board[] = "C002_000b-bmerge10_1";
const char D_801022B8_shared_board[] = "c001_000-atama_2";
const char D_801022CC_shared_board[] = "atama_2";

Object* MBKSuitCreate(void) {
    GW_PLAYER* player;
    Object* model;
    omObjData* obj;
    u32 playerNo;

    playerNo = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MBKSuitKill();
    if (playerNo < 4) {
        D_801011FC_shared_board = MBModelCreate(0x23, D_801011A0_shared_board);
        obj = omAddObj(0x3FFF, 0, 0, -1, MBKSuitMain);
        D_80101200_shared_board = obj;
        obj->work[0] = playerNo & 0xFF;
        func_80017358_main(player->player_obj->omObj1->model[0], (char*)D_801011C0_shared_board[GwPlayer[playerNo].chr],
                           D_801011FC_shared_board->omObj1->model[0], "atama_3");
        HuVecCopy3F(&D_801011FC_shared_board->coords, &player->player_obj->coords);
    } else {
        model = MBModelCreate(8, D_801011E0_shared_board);
        D_801011FC_shared_board = model;
        GwPlayer[4].player_obj = model;
        MBModelDispOff(model);
    }
    return D_801011FC_shared_board;
}

void MBKSuitKill(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelKill(D_801011FC_shared_board);
        D_801011FC_shared_board = NULL;
    }
    if (D_80101200_shared_board != NULL) {
        omDelObj(D_80101200_shared_board);
        D_80101200_shared_board = NULL;
    }
}

void MBKSuitInit(void) {
    D_801011FC_shared_board = NULL;
    D_80101200_shared_board = NULL;
}

void MBKSuitClose(void) {
    MBKSuitKill();
}

void MBKSuitMotionSet(s16 arg0, s32 arg1) {
    MBMotionSet(D_801011FC_shared_board, arg0, arg1);
}

void MBKSuitMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    MBMotionShiftSet(D_801011FC_shared_board, arg0, arg1, arg2, arg3);
}

void func_800E648C_shared_board(void) {
    HuVecCopy3F(&D_801011FC_shared_board->coords, &D_80105710_shared_board->coords);
    func_800EB24C_shared_board(D_80102DA0_shared_board, &GwPlayer[4].clink, &GwPlayer[4].clink + 1);
    func_800EB24C_shared_board(D_80102DA0_shared_board, &GwPlayer[4].nlink, &GwPlayer[4].nlink + 1);
    GwPlayer[4].nidx = GwPlayer[4].nidx + 1;
}

void func_800E6500_shared_board(s16 arg0) {
    D_80102DA0_shared_board = arg0;
}

void MBKSuitDispOn(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelDispOff(D_801011FC_shared_board);
    }
}

void MBKSuitDispOff(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelDispOn(D_801011FC_shared_board);
    }
}

void MBKSuitMotionLoad(s32 arg0, s32 arg1) {
    omObjData *objData;
    s16 motion;
    s32 dataNum;
    u32 i;
    Object* obj = D_801011FC_shared_board;

    objData = obj->omObj1;

    for (i = 0; i < ARRAY_COUNT(D_80101204_shared_board); i += 2) {
        if (D_80101204_shared_board[i] == arg1) {
            break;
        }
    }

    dataNum = D_80101204_shared_board[i+1] | 0x000A0000;
    motion = objData->motion[arg0];

    if ((motion != -1) && (obj->unk46 != arg0)) {
        MBMotionKill(motion);
    }

    objData->motion[arg0] = func_800D8E88_shared_board(dataNum);
}
