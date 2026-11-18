#include "ultra64.h"
#include "include_asm.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "game/esprite.h"
#include "game/sprite.h"
#include "game/data.h"
#include "mallocblock.h"

/* An esprite slot with its place on screen (func_80109C98/80109CFC/80109D3C) */
typedef struct GgmSprite {
    /* 0x00 */ u16 id;
    /* 0x02 */ u16 prio;
    /* 0x04 */ s16 attr;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 w;
    /* 0x0C */ s16 h;
    /* 0x10 */ f32 rot;
    /* 0x14 */ f32 sx;
    /* 0x18 */ f32 sy;
} GgmSprite; /* size 0x1C */

/* A box's two coin sprites, per round */
typedef struct GgmRoundSprites {
    /* 0x00 */ GgmSprite off;
    /* 0x1C */ GgmSprite on;
} GgmRoundSprites; /* size 0x38 */

/* The camera (func_80109AD8/80109B10) */
typedef struct GgmCamera {
    /* 0x00 */ f32 fov;
    /* 0x04 */ f32 zoom;
    /* 0x08 */ Vec rot;
    /* 0x14 */ Vec center;
} GgmCamera; /* size 0x20 */

/* The player who plays (func_80109E1C) */
typedef struct GgmPlayer {
    /* 0x00 */ u8 player;
    /* 0x01 */ u8 pad;
    /* 0x02 */ u8 chr;
    /* 0x03 */ u8 cpu;
    /* 0x04 */ u8 difficulty;
    /* 0x06 */ s16 coins;
} GgmPlayer; /* size 0x8 */

/* The CPU's key presses in the window, by CPU level */
typedef struct GgmCpuKey {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 delay;
} GgmCpuKey;


/* The face sprite files by character (a table in the object after 30DC30's .data) */
typedef struct GgmFaces {
    s32 file[8];
} GgmFaces;

typedef struct GgmVec2 {
    f32 x;
    f32 y;
} GgmVec2; /* Vec2f (common_structs.h is not includable here) */

/* The light trail drawn under each box, by buffer */
typedef struct GgmTrail {
    /* 0x00 */ GgmVec2 pos[2];
} GgmTrail; /* size 0x10 */

int sprintf(char* s, const char* fmt, ...);
s32 HmfAnimCreate(HmfData*, void*, s32, char*);
void func_80032FC0_main(s32, s32, s32);
void func_80032FF8_main(s32, u8);
s16 func_8004A5C4_main(s32);
void func_8004A7C4_main(s32);
void func_8004A650_main(s32);
void func_8004A670_main(s32);
void func_8004AB0C_main(s32);
void func_800610E0_main(s16);
void osViBlack(u8);
void Hu3DCam3DToScreen(s16 camIndex, Vec* worldPos, GgmVec2* outPos);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 attr);
void func_8000BF00_main(u16 spriteId, f32 rot);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void GMesMaxTimeGet(s16 mesId, s16 time);
void func_800557A0_main(void);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8000B5F0_main(u8 arg0);
void func_8003302C_main(s32, u8);
void func_8001C92C_main(s16 model, f32 arg1);
typedef struct L7MotionInfo {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ s16 unk02; /* last frame */
    /* 0x04 */ char unk04[0x14];
} L7MotionInfo; /* include/overlays/ovl_39.h D_800CCF58_main_Struct */
extern L7MotionInfo* D_800CCF58_main;
omObjData* func_80045ED0_main(u32 arg0);
void func_8001C6A8_main(s32 model, f32 arg1);
s32 func_80017BB8_main(s16, s16);
extern s32 D_800A178C_main[][6];
s16 HmfAnimRead(HmfData* hmf, s32 dataNum, char* name);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
s16 func_8000B638_main(void);
void func_8004A208_main(void);
void func_8005A6B0_main(void);
s32 func_80060880_main(s32 arg0, s32 arg1, s32 arg2);
void func_8005B63C_main(s16, s32, s32);
void func_80061100_main(s16, s32);
void func_80060EA8_main(s32 winId, s32 sound);
void func_80060C14_main(s32 winId, s32 sound);
void func_8005D294_main(s16);
void func_8005B43C_main(s16, s32, s32, s32);
void func_8005F904_main(void);
s16 func_8005E0C0_main(s16);
void func_8005F698_main(s16, s16, s16, s16, u8);
void func_8005F744_main(s16, s16, s16, s16);
void func_8005FE54_main(s16, s16);
s32 func_8005E1D8_main(s16, s16, s32);
void func_8005F524_main(void);
void func_8005BDFC_main(s16, s32);
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];
extern u8 D_800D6A58_main;
extern s8 D_800CBB6E_main[];
extern u16 D_800CDA7C_main[];

// lucky 7 A: Game Guy's Lucky 7

/* The player who plays (func_80105C24) */
typedef struct L7Player {
    /* 0x00 */ u16 player;
    /* 0x02 */ u16 pad;
    /* 0x04 */ u16 chr;
    /* 0x06 */ u16 cpu;
    /* 0x08 */ u16 difficulty;
    /* 0x0A */ u16 coins;
    /* 0x0C */ u16 coinsStart;
} L7Player; /* size 0xE */

/* A sprite's file, priority and place (the setup tables) */
typedef struct L7SprInit4 {
    /* 0x00 */ s32 file;
    /* 0x04 */ s32 prio;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
} L7SprInit4; /* size 0x10 */

typedef struct L7SprInit3 {
    /* 0x00 */ s32 file;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
} L7SprInit3; /* size 0xC */

/* The player's model files and motions (func_801087B4) */
typedef struct L7ModelInit {
    /* 0x00 */ s32 files[4];
    /* 0x10 */ s32 motions[10];
} L7ModelInit; /* size 0x38 */

/* A step counter pair */
typedef struct L7Step {
    /* 0x00 */ s16 step;
    /* 0x02 */ u16 frame;
} L7Step;

/* A model's vertex-scatter effect: a copy of src/13F90.c's HmfFxPart/HmfFxWork (main's real layout) */
typedef struct L7FxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir;
    /* 0x24 */ Vec vel;
} L7FxPart; /* size 0x30 */

typedef struct L7FxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* frame */
    /* 0x04 */ u16 unk04; /* flags: 1 loop, 4 finished, 8 recolour */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ L7FxPart* parts;
} L7FxWork; /* size 0x5C */

// LOCAL
void func_801059A0_game_guys_lucky_7(void);
s32 func_801059BC_game_guys_lucky_7(f32 range);
void func_80105A28_game_guys_lucky_7(void);
void func_80105AC0_game_guys_lucky_7(void);
void func_80105AC8_game_guys_lucky_7(void);
void func_80105C08_game_guys_lucky_7(void);
void func_80105C24_game_guys_lucky_7(void);
void func_80105E34_game_guys_lucky_7(omObjData* obj);
void func_80105F70_game_guys_lucky_7(omObjData* obj);
void func_80106248_game_guys_lucky_7(omObjData* obj);
void func_80106370_game_guys_lucky_7(void);
void func_80106500_game_guys_lucky_7(omObjData* obj);
void func_80106854_game_guys_lucky_7(omObjData* obj);
void func_80106A0C_game_guys_lucky_7(omObjData* obj);
void func_80106CF4_game_guys_lucky_7(omObjData* obj);
void func_80107090_game_guys_lucky_7(void);
void func_80107270_game_guys_lucky_7(void);
void func_80107668_game_guys_lucky_7(omObjData* obj);
void func_8010783C_game_guys_lucky_7(omObjData* obj);
void func_80107AC4_game_guys_lucky_7(omObjData* obj);
void func_80107DE4_game_guys_lucky_7(omObjData* obj);
void func_80107EEC_game_guys_lucky_7(omObjData* obj);
void func_80107F44_game_guys_lucky_7(omObjData* obj);
void func_80107F6C_game_guys_lucky_7(void);
void func_80107F98_game_guys_lucky_7(omObjData* obj);
void func_801087B4_game_guys_lucky_7(omObjData* obj);
void func_80108B64_game_guys_lucky_7(omObjData* obj);
void func_801092B0_game_guys_lucky_7(omObjData* obj);
void func_80109570_game_guys_lucky_7(omObjData* obj);
void func_80109FA4_game_guys_lucky_7(omObjData* obj);
void func_8010A04C_game_guys_lucky_7(omObjData* obj);
void func_8010A0DC_game_guys_lucky_7(omObjData* obj);
void func_8010A19C_game_guys_lucky_7(omObjData* obj);
void func_8010A278_game_guys_lucky_7(omObjData* obj);
void func_8010A328_game_guys_lucky_7(omObjData* obj);
void func_8010A3B8_game_guys_lucky_7(omObjData* obj);
void func_8010A458_game_guys_lucky_7(omObjData* obj);
void func_8010A8A4_game_guys_lucky_7(omObjData* obj);
void func_8010AA8C_game_guys_lucky_7(omObjData* obj);
s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 mes);
void func_8010ADB8_game_guys_lucky_7(s16 winId);
void func_8010ADF8_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu);
s16 func_8010AF44_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu, s16 arg3);
s16 func_8010B13C_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu, s16 arg3);

void func_80107FD8_game_guys_lucky_7(void);
void func_801080E8_game_guys_lucky_7(void);
void func_8010826C_game_guys_lucky_7(void);
void func_80108374_game_guys_lucky_7(omObjData* obj);
void func_801083A0_game_guys_lucky_7(void);
void func_80108498_game_guys_lucky_7(void);
void func_801085D4_game_guys_lucky_7(void);
void func_8010B334_game_guys_lucky_7(void);
void func_8010B528_game_guys_lucky_7(s16 model);
void func_8010B6E0_game_guys_lucky_7(s16 model);
void func_8010B498_game_guys_lucky_7(omObjData* obj);

/* 306F70 */
void func_8010B830_game_guys_lucky_7(s16 x, s16 y);
void func_8010C824_game_guys_lucky_7(void);
void func_8010BAFC_game_guys_lucky_7(void);
s16 func_8010BB88_game_guys_lucky_7(void);
s16 func_8010C670_game_guys_lucky_7(s32 x);

/* .data (still asm) */
extern s16 D_8010D150_game_guys_lucky_7[10][3]; /* windows: x, y, ? */
extern u16 D_8010D18E_game_guys_lucky_7; /* main step */
extern u16 D_8010D190_game_guys_lucky_7; /* main step frames */
extern GgmCpuKey D_8010D188_game_guys_lucky_7[3]; /* CPU key delay by CPU level */
extern char* D_8010D194_game_guys_lucky_7[8]; /* character names */
extern s16 D_8010D1B4_game_guys_lucky_7; /* title step */
extern u16 D_8010D1B6_game_guys_lucky_7; /* title frame */
extern u16 D_8010D1B8_game_guys_lucky_7; /* intro step */
extern u16 D_8010D1BA_game_guys_lucky_7; /* title done */
extern f32 D_8010D1BC_game_guys_lucky_7; /* intro bounce speed */
extern u16 D_8010D1C0_game_guys_lucky_7; /* intro wait */
extern u16 D_8010D1C2_game_guys_lucky_7; /* play step */
extern u16 D_8010D1C4_game_guys_lucky_7; /* play wait */
extern u16 D_8010D1C6_game_guys_lucky_7; /* spin step */
extern u16 D_8010D1C8_game_guys_lucky_7; /* spin wait */
extern u16 D_8010D1CA_game_guys_lucky_7; /* countdown frames */
extern u16 D_8010D1CC_game_guys_lucky_7; /* countdown seconds */
extern u16 D_8010D1CE_game_guys_lucky_7; /* reel stop step */
extern u16 D_8010D1D0_game_guys_lucky_7; /* reel stop wait */
extern u16 D_8010D1D2_game_guys_lucky_7; /* result step */
extern u16 D_8010D1D4_game_guys_lucky_7; /* jump step */
extern f32 D_8010D1D8_game_guys_lucky_7; /* jump speed */
extern u16 D_8010D1DC_game_guys_lucky_7; /* player jump step */
extern f32 D_8010D1E0_game_guys_lucky_7; /* player jump speed */
extern s16 D_8010D1E4_game_guys_lucky_7;
extern u16 D_8010D1E6_game_guys_lucky_7; /* title blink frames */
extern u16 D_8010D1E8_game_guys_lucky_7; /* title blink step */
extern u16 D_8010D1EA_game_guys_lucky_7; /* player motion shown */
extern u16 D_8010D1EC_game_guys_lucky_7; /* player hop step */
extern u16 D_8010D1EE_game_guys_lucky_7; /* player hop wait */
extern f32 D_8010D1F0_game_guys_lucky_7; /* player hop speed */
extern u16 D_8010D1F4_game_guys_lucky_7; /* player hops made */
extern f32 D_8010D1FC_game_guys_lucky_7[][3]; /* player step heights: .y of a Vec[8] at 0x8010D1F8 (label view; see report) */
extern u16 D_8010D258_game_guys_lucky_7; /* Game Guy motion shown */
extern u16 D_8010D2C8_game_guys_lucky_7; /* sign step */
extern f32 D_8010D2CC_game_guys_lucky_7; /* sign rot x */
extern f32 D_8010D2D0_game_guys_lucky_7; /* sign rot y */
extern f32 D_8010D2D4_game_guys_lucky_7; /* sign scale x */
extern f32 D_8010D2D8_game_guys_lucky_7; /* sign scale y, z */
extern f32 D_8010D2DC_game_guys_lucky_7; /* sign frames */
extern u16 D_8010D2E0_game_guys_lucky_7; /* number step */
extern f32 D_8010D2E4_game_guys_lucky_7; /* number y */
extern f32 D_8010D2E8_game_guys_lucky_7; /* number scale */
extern u16 D_8010D2EC_game_guys_lucky_7; /* number wait */
extern u16 D_8010D25A_game_guys_lucky_7; /* Game Guy hop step */
extern u16 D_8010D25C_game_guys_lucky_7; /* Game Guy hop wait */
extern f32 D_8010D260_game_guys_lucky_7; /* Game Guy hop speed */
extern u16 D_8010D264_game_guys_lucky_7; /* Game Guy hops made */
extern f32 D_8010D26C_game_guys_lucky_7[][3]; /* Game Guy step heights: .y of a Vec[8] at 0x8010D268 (label view) */

/* .rodata */

/* .bss */
extern char D_8010D5D0_game_guys_lucky_7[];
extern s16 D_8010D6D0_game_guys_lucky_7; /* result message */
extern Process* D_8010D6D4_game_guys_lucky_7; /* rules window process */
extern Process* D_8010D6D8_game_guys_lucky_7; /* play process */
extern L7Player D_8010D6DC_game_guys_lucky_7;
extern s16 D_8010D6EA_game_guys_lucky_7[3]; /* title sprites (labels D_8010D6EA, D_8010D6EC: one array) */
extern s16 D_8010D6F0_game_guys_lucky_7[7]; /* reel lamp sprites (labels D_8010D6F0, D_8010D6FC: one array) */
extern f32 D_8010D700_game_guys_lucky_7[7]; /* reel lamp scales */
extern s16 D_8010D71C_game_guys_lucky_7[5]; /* coin counter sprites (labels D_8010D71C..D_8010D724: one array) */
extern u8 D_8010D6E1_game_guys_lucky_7; /* low byte of D_8010D6DC.chr (a view; see report) */
extern u16 D_8010D726_game_guys_lucky_7;
extern u16 D_8010D728_game_guys_lucky_7;
extern f32 D_8010D72C_game_guys_lucky_7;
extern f32 D_8010D730_game_guys_lucky_7;
extern f32 D_8010D734_game_guys_lucky_7;
extern f32 D_8010D738_game_guys_lucky_7;
extern u16 D_8010D73C_game_guys_lucky_7; /* Game Guy pose */
extern u16 D_8010D73E_game_guys_lucky_7;
extern s16 D_8010D740_game_guys_lucky_7; /* Game Guy motion frame / 2 */
extern u16 D_8010D742_game_guys_lucky_7;
extern u16 D_8010D744_game_guys_lucky_7;
extern u16 D_8010D746_game_guys_lucky_7; /* player motion */
extern f32 D_8010D748_game_guys_lucky_7;
extern u16 D_8010D758_game_guys_lucky_7; /* Game Guy sign state */
extern f32 D_8010D75C_game_guys_lucky_7; /* sign x */
extern f32 D_8010D760_game_guys_lucky_7; /* sign y */
extern f32 D_8010D764_game_guys_lucky_7; /* sign z */
extern u16 D_8010D768_game_guys_lucky_7;
extern u16 D_8010D76A_game_guys_lucky_7; /* reels to stop */
extern u16 D_8010D76C_game_guys_lucky_7;
extern u16 D_8010D76E_game_guys_lucky_7;
extern u16 D_8010D770_game_guys_lucky_7;
extern f32 D_8010D74C_game_guys_lucky_7;
extern f32 D_8010D750_game_guys_lucky_7;
extern f32 D_8010D754_game_guys_lucky_7;
extern u16 D_8010D772_game_guys_lucky_7; /* rules shown */
extern u16 D_8010D774_game_guys_lucky_7;
extern u16 D_8010D776_game_guys_lucky_7;
extern u16 D_8010D778_game_guys_lucky_7;
extern u16 D_8010D77A_game_guys_lucky_7; /* won */
extern u16 D_8010D77C_game_guys_lucky_7; /* rules window done */
extern s16 D_8010D800_game_guys_lucky_7;
extern s16 D_8010D802_game_guys_lucky_7; /* CPU level */
extern s32 D_8010D2F0_game_guys_lucky_7[4]; /* result effect model files */
extern s16 D_8010D798_game_guys_lucky_7[4]; /* result effect models */
extern s16 D_8010D804_game_guys_lucky_7; /* result effect frame */


void func_801059A0_game_guys_lucky_7(void) {
    func_80105A28_game_guys_lucky_7();
}

s32 func_801059BC_game_guys_lucky_7(f32 range) {
    u8 hi = rand8();
    u8 lo = rand8();
    s32 shifted = (hi << 8);
    s32 r = ((lo | shifted) / 65536.0f) * range;

    return r;
}

void func_80105A28_game_guys_lucky_7(void) {
    Hu3DAnimInit(0x20);
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_8004A208_main();
    func_80105AC0_game_guys_lucky_7();
    func_80105AC8_game_guys_lucky_7();
    func_80105C08_game_guys_lucky_7();
    func_80105C24_game_guys_lucky_7();
    omAddObj(1000, 0, 0, -1, func_80105E34_game_guys_lucky_7);
    omAddObj(2000, 0, 0, -1, func_80107F44_game_guys_lucky_7);
}

void func_80105AC0_game_guys_lucky_7(void) {
}

void func_80105AC8_game_guys_lucky_7(void) {
    s16 cam;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 6.57f, 2000.0f, 8500.0f);
    CZoom = 8075.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 350.0f;
    Center.z = 0.0f;
}

void func_80105C08_game_guys_lucky_7(void) {
    func_8005A6B0_main();
}

void func_80105C24_game_guys_lucky_7(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
    case 0:
        D_8010D6DC_game_guys_lucky_7.player = 0;
        break;
    case 1:
        D_8010D6DC_game_guys_lucky_7.player = 1;
        break;
    case 2:
        D_8010D6DC_game_guys_lucky_7.player = 2;
        break;
    case 3:
        D_8010D6DC_game_guys_lucky_7.player = 3;
        break;
    default:
        D_8010D6DC_game_guys_lucky_7.player = 0;
        break;
    }
    D_8010D6DC_game_guys_lucky_7.pad = GwPlayer[D_8010D6DC_game_guys_lucky_7.player].pad;
    D_8010D6DC_game_guys_lucky_7.chr = GwPlayer[D_8010D6DC_game_guys_lucky_7.player].chr;
    if (GwPlayer[D_8010D6DC_game_guys_lucky_7.player].stat & 1) {
        D_8010D6DC_game_guys_lucky_7.cpu = 1;
        D_8010D6DC_game_guys_lucky_7.difficulty = GwPlayer[D_8010D6DC_game_guys_lucky_7.player].cpu_difficulty;
        D_8010D802_game_guys_lucky_7 = (s8)GwCommon.unkA0;
        if (D_8010D802_game_guys_lucky_7 <= 0) {
            D_8010D802_game_guys_lucky_7 = 0;
        } else if (D_8010D802_game_guys_lucky_7 >= 2) {
            D_8010D802_game_guys_lucky_7 = 2;
        }
    } else {
        D_8010D6DC_game_guys_lucky_7.cpu = 0;
        D_8010D6DC_game_guys_lucky_7.difficulty = 0;
    }
    D_8010D6DC_game_guys_lucky_7.coins = D_8010D6DC_game_guys_lucky_7.coinsStart =
        GwPlayer[D_8010D6DC_game_guys_lucky_7.player].gameCoin;
    if (D_8010D6DC_game_guys_lucky_7.coins >= 999) {
        D_8010D6DC_game_guys_lucky_7.coins = 999;
        D_8010D6DC_game_guys_lucky_7.coinsStart = 999;
    } else if (D_8010D6DC_game_guys_lucky_7.coins == 0) {
        D_8010D6DC_game_guys_lucky_7.coins = 0;
        D_8010D6DC_game_guys_lucky_7.coinsStart = 0;
    }
}

void func_80105E34_game_guys_lucky_7(omObjData* obj) {
    func_80107F6C_game_guys_lucky_7();
    func_8010B830_game_guys_lucky_7(0xA0, 0xC2);
    omAddObj(10, 10, 10, -1, func_80107F98_game_guys_lucky_7);
    omAddObj(20, 10, 20, -1, func_801087B4_game_guys_lucky_7);
    omAddObj(30, 10, 20, -1, func_801092B0_game_guys_lucky_7);
    omAddObj(40, 10, 10, -1, func_8010A3B8_game_guys_lucky_7);
    omAddObj(41, 10, 10, -1, func_80109FA4_game_guys_lucky_7);
    omAddObj(42, 10, 10, -1, func_8010A0DC_game_guys_lucky_7);
    omAddObj(42, 10, 10, -1, func_8010A278_game_guys_lucky_7);
    omAddObj(50, 10, 10, -1, func_8010A8A4_game_guys_lucky_7);
    obj->func = func_80105F70_game_guys_lucky_7;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D310_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D31C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D32C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D334_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D340_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D34C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D358_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D364_game_guys_lucky_7);

void func_80105F70_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D18E_game_guys_lucky_7) {
    case 0:
        WipeCreateIn(0xFF, 16);
        D_8010D18E_game_guys_lucky_7++;
        break;
    case 1:
        obj->func = func_80106248_game_guys_lucky_7;
        D_8010D18E_game_guys_lucky_7++;
        break;
    case 2:
        if (D_8010D190_game_guys_lucky_7++ == 0) {
            GMesCreate(9);
            D_8010D190_game_guys_lucky_7 = 1;
        } else if (GMesStatGet() == 0) {
            D_8010D190_game_guys_lucky_7 = 0;
            D_8010D18E_game_guys_lucky_7++;
        }
        break;
    case 3:
        obj->func = func_80106854_game_guys_lucky_7;
        D_8010D18E_game_guys_lucky_7++;
        break;
    case 4:
        if (D_8010D190_game_guys_lucky_7++ == 0) {
            GMesCreate(0x14);
            HuAudSeqFadeOut(120);
        } else if (D_8010D190_game_guys_lucky_7 == 15) {
            if (D_8010D776_game_guys_lucky_7 >= 8) {
                obj->func = func_80107AC4_game_guys_lucky_7;
            }
        } else if (GMesStatGet() == 0) {
            D_8010D190_game_guys_lucky_7 = 0;
            D_8010D18E_game_guys_lucky_7++;
        }
        break;
    case 5:
        obj->func = func_80107668_game_guys_lucky_7;
        D_8010D18E_game_guys_lucky_7++;
        break;
    case 6:
        if (D_8010D190_game_guys_lucky_7++ == 0) {
            switch (D_8010D77A_game_guys_lucky_7) {
            case 1:
                HuAudSeqPlay(0x73);
                D_8010D6D0_game_guys_lucky_7 = GMesCreate(0x16, D_8010D6DC_game_guys_lucky_7.chr);
                GMesMaxTimeGet(D_8010D6D0_game_guys_lucky_7, 120);
                break;
            case 0:
                HuAudSeqPlay(0x71);
                sprintf(D_8010D5D0_game_guys_lucky_7, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49", /* "%s KONOSU!" */ D_8010D194_game_guys_lucky_7[D_8010D6DC_game_guys_lucky_7.chr]);
                D_8010D6D0_game_guys_lucky_7 = GMesCreate(0x19, D_8010D5D0_game_guys_lucky_7, 160, 120, 1.0, 1.0, 1);
                GMesMaxTimeGet(D_8010D6D0_game_guys_lucky_7, 120);
                break;
            }
        } else if (D_8010D190_game_guys_lucky_7 >= 135) {
            D_8010D18E_game_guys_lucky_7++;
        }
        break;
    case 7:
        obj->func = func_80107DE4_game_guys_lucky_7;
        break;
    case 999:
        break;
    case 1000:
        func_8010C670_game_guys_lucky_7(0x44);
        break;
    }
}

void func_80106248_game_guys_lucky_7(omObjData* obj) {
    s16 ret;

    switch (D_8010D1B4_game_guys_lucky_7) {
    case 0:
        D_8010D1B4_game_guys_lucky_7 = ret = func_8010BB88_game_guys_lucky_7();
        if ((s16)D_8010D1B6_game_guys_lucky_7++ >= 115) {
            D_8010D1B4_game_guys_lucky_7 = ret + 1;
        }
        break;
    case 1:
        D_8010D77C_game_guys_lucky_7 = 0;
        D_8010D6D4_game_guys_lucky_7 = omAddPrcObj(func_80106370_game_guys_lucky_7, 0x3F00, 0x800, 0);
        D_8010D1B4_game_guys_lucky_7++;
        break;
    case 2:
        if (D_8010D77C_game_guys_lucky_7 != 0) {
            HuPrcKill(D_8010D6D4_game_guys_lucky_7);
            D_8010D77C_game_guys_lucky_7 = 0;
            D_8010D1B4_game_guys_lucky_7++;
        }
        break;
    case 3:
        obj->func = func_80106500_game_guys_lucky_7;
        D_8010D1B4_game_guys_lucky_7++;
        break;
    case 4:
        obj->func = func_80105F70_game_guys_lucky_7;
        break;
    case 1000: /* an empty case (keeps the switch a branch tree) */
        break;
    }
}

void func_80106370_game_guys_lucky_7(void) {
    s16 winId;
    s16 ret;
    s16 done = 0;

    winId = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[0][0], D_8010D150_game_guys_lucky_7[0][1],
                                            D_8010D150_game_guys_lucky_7[0][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2B00, -1, -1);
    func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
    func_8005B43C_main(winId, 0x2B01, -1, -1);
    do {
        ret = func_8010AF44_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu, 1);
        if (ret == 0) {
            func_8005B43C_main(winId, 0x2B02, -1, -1);
            func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
            done = 1;
        } else if (ret == 1) {
            done = 1;
        }
        HuPrcVSleep();
    } while (done == 0);
    func_8005B43C_main(winId, 0x2B03, -1, -1);
    func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
    func_8010ADB8_game_guys_lucky_7(winId);
    D_8010D77C_game_guys_lucky_7 = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80106500_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D1BA_game_guys_lucky_7 == 0) {
        D_8010D1BA_game_guys_lucky_7 = func_8010BB88_game_guys_lucky_7();
    }
    switch (D_8010D1B8_game_guys_lucky_7) {
    case 0:
        D_8010D1BC_game_guys_lucky_7 = -1.7f;
        D_8010D73C_game_guys_lucky_7 = 7;
        D_8010D746_game_guys_lucky_7 = 1;
        D_8010D74C_game_guys_lucky_7 = 1000.0f;
        D_8010D754_game_guys_lucky_7 = 270.0f;
        D_8010D1B8_game_guys_lucky_7++;
        break;
    case 1:
        if (D_8010D74C_game_guys_lucky_7 > 350.0f) {
            D_8010D74C_game_guys_lucky_7 -= 10.0f;
        } else {
            D_8010D754_game_guys_lucky_7 = (D_8010D754_game_guys_lucky_7 < 360.0f)
                ? D_8010D754_game_guys_lucky_7 + 10.0f : (D_8010D746_game_guys_lucky_7 = 0, 360.0f);
        }
        if (D_8010D740_game_guys_lucky_7 >= 25 && D_8010D73E_game_guys_lucky_7 != 0.0f) {
            D_8010D1BC_game_guys_lucky_7 += 0.11f;
            if (D_8010D1BC_game_guys_lucky_7 > 1.7f) {
                D_8010D1BC_game_guys_lucky_7 = 1.7f;
            }
            D_8010D730_game_guys_lucky_7 += D_8010D1BC_game_guys_lucky_7 * D_8010D1BC_game_guys_lucky_7
                * ((D_8010D1BC_game_guys_lucky_7 >= 0.0f) ? -17.5f : 26.0f);
        } else if (D_8010D73E_game_guys_lucky_7 == 0.0f) {
            if (D_8010D1C0_game_guys_lucky_7++ >= 30) {
                D_8010D73E_game_guys_lucky_7 = 1;
            }
        }
        if (D_8010D740_game_guys_lucky_7 == 30) {
            D_8010D73E_game_guys_lucky_7 = 0;
            D_8010D1BC_game_guys_lucky_7 = 0.0f;
            D_8010D72C_game_guys_lucky_7 = 450.0f;
            D_8010D730_game_guys_lucky_7 = 800.0f;
            D_8010D734_game_guys_lucky_7 = -100.0f;
            D_8010D738_game_guys_lucky_7 = 360.0f;
        }
        if (D_8010D730_game_guys_lucky_7 <= 0.0f) {
            D_8010D754_game_guys_lucky_7 = 360.0f;
            D_8010D73C_game_guys_lucky_7 = 0;
            D_8010D730_game_guys_lucky_7 = 0.0f;
            D_8010D726_game_guys_lucky_7 = 2;
            D_8010D1B8_game_guys_lucky_7++;
        }
        break;
    case 2:
        obj->func = func_80106248_game_guys_lucky_7;
        break;
    }
}

void func_80106854_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D1C2_game_guys_lucky_7) {
    case 0:
        obj->func = func_80106A0C_game_guys_lucky_7;
        D_8010D1C2_game_guys_lucky_7++;
        break;
    case 1:
        D_8010D77C_game_guys_lucky_7 = 0;
        D_8010D6D8_game_guys_lucky_7 = omAddPrcObj(func_80107090_game_guys_lucky_7, 0x3F00, 0x800, 0);
        D_8010D1C2_game_guys_lucky_7++;
        break;
    case 2:
        if (D_8010D77C_game_guys_lucky_7 != 0) {
            HuPrcKill(D_8010D6D8_game_guys_lucky_7);
            if (D_8010D77C_game_guys_lucky_7 == 2) {
                D_8010D772_game_guys_lucky_7 = 0;
                obj->func = func_80106A0C_game_guys_lucky_7;
            }
            D_8010D1C2_game_guys_lucky_7++;
            D_8010D77C_game_guys_lucky_7 = 0;
        }
        break;
    case 3:
        D_8010D77C_game_guys_lucky_7 = 0;
        D_8010D772_game_guys_lucky_7 = 1;
        D_8010D6D8_game_guys_lucky_7 = omAddPrcObj(func_80107270_game_guys_lucky_7, 0x3F00, 0x800, 0);
        D_8010D1C2_game_guys_lucky_7++;
        break;
    case 4:
        if (D_8010D77C_game_guys_lucky_7 != 0 && D_8010D1C4_game_guys_lucky_7++ >= 15) {
            HuPrcKill(D_8010D6D8_game_guys_lucky_7);
            if (D_8010D77C_game_guys_lucky_7 == 1) {
                if (D_8010D774_game_guys_lucky_7 >= 8) {
                    D_8010D800_game_guys_lucky_7 = 5;
                    D_8010D73C_game_guys_lucky_7 = 5;
                }
                obj->func = func_80106A0C_game_guys_lucky_7;
            } else if (D_8010D77C_game_guys_lucky_7 == 2) {
                obj->func = func_80105F70_game_guys_lucky_7;
            }
        }
        break;
    }
}

void func_80106A0C_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D1C6_game_guys_lucky_7) {
    case 0:
        D_8010D758_game_guys_lucky_7 = 1;
        if (D_8010D772_game_guys_lucky_7 == 1) {
            GMesCreate(0x1A, 10, 156, 56);
        }
        D_8010D1C6_game_guys_lucky_7++;
        break;
    case 1:
        if (D_8010D1C8_game_guys_lucky_7++ >= 10) {
            D_8010D1C8_game_guys_lucky_7 = 0;
            D_8010D1C6_game_guys_lucky_7++;
        }
        break;
    case 2:
        if (D_8010D772_game_guys_lucky_7 == 0) {
            if (D_8010D1C8_game_guys_lucky_7++ >= 30) {
                D_8010D73C_game_guys_lucky_7 = 2;
                D_8010D1C8_game_guys_lucky_7 = 0;
                D_8010D1C6_game_guys_lucky_7++;
            }
        } else if (D_8010D772_game_guys_lucky_7 == 1) {
            if (D_8010D1CA_game_guys_lucky_7++ >= 30) {
                D_8010D1CC_game_guys_lucky_7--;
                D_8010D1CA_game_guys_lucky_7 = 0;
            }
            func_8003F578_main(D_8010D1CC_game_guys_lucky_7);
            switch (D_8010D6DC_game_guys_lucky_7.cpu) {
            case 0:
                if ((D_800D5558_main[D_8010D6DC_game_guys_lucky_7.pad] & 0x8000) || D_8010D1CC_game_guys_lucky_7 == 0) {
                    D_8010D746_game_guys_lucky_7 = 3;
                    D_8010D1C8_game_guys_lucky_7 = 0;
                    D_8010D1C6_game_guys_lucky_7++;
                }
                break;
            case 1:
                if (D_8010D1C8_game_guys_lucky_7++ >= 60) {
                    D_8010D746_game_guys_lucky_7 = 3;
                    D_8010D1C8_game_guys_lucky_7 = 0;
                    D_8010D1C6_game_guys_lucky_7++;
                }
                break;
            }
        }
        break;
    case 3:
        if (D_8010D1C8_game_guys_lucky_7++ >= 31) {
            D_8010D1C8_game_guys_lucky_7 = 0;
            D_8010D1C6_game_guys_lucky_7++;
        } else if (D_8010D1C8_game_guys_lucky_7 == 5) {
            D_8010D76C_game_guys_lucky_7 = 1;
            D_8010D770_game_guys_lucky_7 = 1;
            D_8010D768_game_guys_lucky_7 = 1;
            D_8010D758_game_guys_lucky_7 = 2;
            D_8010D76A_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(6.0f);
            if (D_8010D772_game_guys_lucky_7 == 1) {
                func_8003F5C0_main();
            }
        }
        break;
    case 4:
        D_8010D1CA_game_guys_lucky_7 = 0;
        D_8010D1CC_game_guys_lucky_7 = 10;
        D_8010D1C6_game_guys_lucky_7 = 0;
        D_8010D1C8_game_guys_lucky_7 = 0;
        obj->func = func_80106CF4_game_guys_lucky_7;
        break;
    case 999:
        if (D_800D5558_main[0] & 2) {
            D_8010D1C6_game_guys_lucky_7 = 0;
        }
        break;
    }
}

void func_80106CF4_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D772_game_guys_lucky_7 == 0) {
        if (D_8010D1CE_game_guys_lucky_7 != D_8010D76A_game_guys_lucky_7 + 1 && D_8010D728_game_guys_lucky_7 == 0
            && D_8010D774_game_guys_lucky_7 < 8) {
            D_8010D728_game_guys_lucky_7 = 1;
            D_8010D1CE_game_guys_lucky_7++;
        } else if ((D_8010D1CE_game_guys_lucky_7 == D_8010D76A_game_guys_lucky_7 + 1 || D_8010D774_game_guys_lucky_7 == 8)
                   && D_8010D728_game_guys_lucky_7 == 0) {
            if (D_8010D774_game_guys_lucky_7 >= 8) {
                D_8010D1CE_game_guys_lucky_7 = 0;
                D_8010D772_game_guys_lucky_7 = 1;
                D_8010D1D0_game_guys_lucky_7 = 0;
                obj->func = func_8010783C_game_guys_lucky_7;
            } else if (D_8010D1D0_game_guys_lucky_7++ >= 6) {
                if (D_8010D738_game_guys_lucky_7 <= 360.0f) {
                    D_8010D73C_game_guys_lucky_7 = 0;
                    D_8010D738_game_guys_lucky_7 += 10.0f;
                } else {
                    D_8010D1CE_game_guys_lucky_7 = 0;
                    D_8010D738_game_guys_lucky_7 = 360.0f;
                    D_8010D772_game_guys_lucky_7 = 1;
                    D_8010D1D0_game_guys_lucky_7 = 0;
                    if (D_8010D778_game_guys_lucky_7 == 0) {
                        obj->func = func_80106A0C_game_guys_lucky_7;
                    } else if (D_8010D778_game_guys_lucky_7 == 1) {
                        obj->func = func_80106854_game_guys_lucky_7;
                    }
                }
            }
        }
    } else if (D_8010D772_game_guys_lucky_7 == 1) {
        if (D_8010D1CE_game_guys_lucky_7 != D_8010D76A_game_guys_lucky_7 + 1 && D_8010D744_game_guys_lucky_7 == 0
            && D_8010D776_game_guys_lucky_7 < 8) {
            D_8010D744_game_guys_lucky_7 = 1;
            D_8010D1CE_game_guys_lucky_7++;
        } else if ((D_8010D1CE_game_guys_lucky_7 == D_8010D76A_game_guys_lucky_7 + 1 || D_8010D776_game_guys_lucky_7 == 8)
                   && D_8010D744_game_guys_lucky_7 == 0) {
            if (D_8010D776_game_guys_lucky_7 >= 8) {
                CharFXPlay(0x286, D_8010D6E1_game_guys_lucky_7);
                D_8010D746_game_guys_lucky_7 = 7;
                obj->func = func_80105F70_game_guys_lucky_7;
            } else if (D_8010D1D0_game_guys_lucky_7++ >= 6) {
                if (D_8010D754_game_guys_lucky_7 <= 360.0f) {
                    D_8010D746_game_guys_lucky_7 = 1;
                    D_8010D754_game_guys_lucky_7 += 10.0f;
                } else {
                    if (D_8010D776_game_guys_lucky_7 == 7) {
                        omVibrate(D_8010D6DC_game_guys_lucky_7.player, 30, 0, 30);
                    }
                    D_8010D746_game_guys_lucky_7 = 0;
                    D_8010D1D0_game_guys_lucky_7 = 0;
                    D_8010D1CE_game_guys_lucky_7 = 0;
                    D_8010D754_game_guys_lucky_7 = 360.0f;
                    D_8010D772_game_guys_lucky_7 = 0;
                    if (D_8010D778_game_guys_lucky_7 == 0) {
                        D_8010D778_game_guys_lucky_7 = 1;
                        obj->func = func_80106854_game_guys_lucky_7;
                    } else if (D_8010D778_game_guys_lucky_7 == 1) {
                        obj->func = func_80105F70_game_guys_lucky_7;
                    }
                }
            }
        }
    }
}

#ifdef NON_MATCHING
/* retail keeps the three identical 100% cases as separate calls (ours are merged into one) and reloads D_8010D774 for the switch; logic checked against the asm */
void func_80107090_game_guys_lucky_7(void) {
    s16 winId;
    s32 won = 0;

    if (D_8010D776_game_guys_lucky_7 < D_8010D774_game_guys_lucky_7) {
        switch (D_8010D774_game_guys_lucky_7) {
        case 1:
            if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                won = 1;
            }
            break;
        case 2:
            if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                won = 1;
            }
            break;
        case 3:
            if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                won = 1;
            }
            break;
        case 4:
            if (func_801059BC_game_guys_lucky_7(100.0f) < 30) {
                won = 1;
            }
            break;
        case 5:
            if (func_801059BC_game_guys_lucky_7(100.0f) < 10) {
                won = 1;
            }
            break;
        }
    } else {
        won = 1;
    }
    winId = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][0],
                                            D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][1],
                                            D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, (won != 1) ? 0x2B05 : 0x2B04, -1, -1);
    func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
    func_8010ADB8_game_guys_lucky_7(winId);
    if (won == 0) {
        D_8010D77C_game_guys_lucky_7 = 1;
    } else if (won == 1) {
        D_8010D77C_game_guys_lucky_7 = 2;
    }
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107090_game_guys_lucky_7);
#endif

#ifdef NON_MATCHING
/* regalloc: retail keeps 'done' in s0 and copies it to s4 before the window loop (one move more); ops, branches, calls and fields equal */
void func_80107270_game_guys_lucky_7(void) {
    s16 stop = 1;
    s16 adj[4] = { 30, 20, 10, 0 }; /* CPU chance to stop, by CPU level */
    s16 winId;
    s32 done = 0;

    if (D_8010D6DC_game_guys_lucky_7.cpu == 1) {
        if (D_8010D776_game_guys_lucky_7 < D_8010D774_game_guys_lucky_7 && D_8010D774_game_guys_lucky_7 < 8) {
            stop = 0;
        } else {
            switch (D_8010D776_game_guys_lucky_7) {
            case 1:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty] + 100) {
                    stop = 0;
                }
                break;
            case 2:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty] + 100) {
                    stop = 0;
                }
                break;
            case 3:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty] + 100) {
                    stop = 0;
                }
                break;
            case 4:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty] + 30) {
                    stop = 0;
                }
                break;
            case 5:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty] + 10) {
                    stop = 0;
                }
                break;
            case 6:
                if (func_801059BC_game_guys_lucky_7(100.0f) < adj[D_8010D6DC_game_guys_lucky_7.difficulty]) {
                    stop = 0;
                }
                break;
            }
        }
    }
    winId = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][0],
                                            D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][1],
                                            D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    if (D_8010D774_game_guys_lucky_7 <= D_8010D776_game_guys_lucky_7 || D_8010D774_game_guys_lucky_7 >= 8) {
        if (D_8010D776_game_guys_lucky_7 == 1) {
            func_8005B43C_main(winId, 0x2B09, -1, -1);
            func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
            func_8005B43C_main(winId, 0x2B0A, -1, -1);
        } else {
            func_8005B43C_main(winId, 0x2B07, -1, -1);
            func_8005B6BC_main(winId, D_8010D776_game_guys_lucky_7 + 0x2B09, 0);
            func_8010ADF8_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu);
            func_8005B43C_main(winId, 0x2B08, -1, -1);
        }
        done = 1;
        stop = stop != 1;
    } else {
        func_8005B43C_main(winId, 0x2B06, -1, -1);
    }
    while (D_8010D77C_game_guys_lucky_7 == 0) {
        switch (done == 0 ? func_8010AF44_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu, stop)
                          : func_8010B13C_game_guys_lucky_7(winId, D_8010D6DC_game_guys_lucky_7.pad, D_8010D6DC_game_guys_lucky_7.cpu, stop)) {
        case 0:
            D_8010D77C_game_guys_lucky_7 = 1;
            func_8010ADB8_game_guys_lucky_7(winId);
            break;
        case 1:
            D_8010D77C_game_guys_lucky_7 = 2;
            func_8010ADB8_game_guys_lucky_7(winId);
            break;
        }
        HuPrcVSleep();
    }
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D3B4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107270_game_guys_lucky_7);
#endif

void func_80107668_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D1D2_game_guys_lucky_7) {
    case 0:
        if (D_8010D776_game_guys_lucky_7 < 8) {
            if (D_8010D776_game_guys_lucky_7 >= D_8010D774_game_guys_lucky_7) {
                D_8010D77A_game_guys_lucky_7 = 1;
            }
            if (D_8010D774_game_guys_lucky_7 >= 8) {
                D_8010D77A_game_guys_lucky_7 = 1;
            }
        } else {
            D_8010D77A_game_guys_lucky_7 = 0;
        }
        D_8010D1D2_game_guys_lucky_7++;
        break;
    case 1:
        if (D_8010D77A_game_guys_lucky_7 == 1) {
            if (D_8010D776_game_guys_lucky_7 == 7) {
                HuAudFXPlay(0x522);
            } else {
                HuAudFXPlay(0x535);
            }
        } else {
            HuAudFXPlay(0x518);
        }
        D_8010D1D2_game_guys_lucky_7++;
        break;
    case 2:
        if (D_8010D776_game_guys_lucky_7 == 7) {
            func_8010BAFC_game_guys_lucky_7();
            D_8010D1D2_game_guys_lucky_7++;
        } else {
            D_8010D1D2_game_guys_lucky_7 += 2;
        }
    case 3:
        D_8010D1D2_game_guys_lucky_7 += func_8010C670_game_guys_lucky_7(0x44);
        break;
    case 4:
        if (D_8010D77A_game_guys_lucky_7 == 1) {
            if (D_8010D776_game_guys_lucky_7 == 7) {
                func_8010B334_game_guys_lucky_7();
            }
            D_8010D746_game_guys_lucky_7 = 5;
            D_8010D73C_game_guys_lucky_7 = 4;
        } else if (D_8010D77A_game_guys_lucky_7 == 0) {
            D_8010D73C_game_guys_lucky_7 = 3;
            if (D_8010D776_game_guys_lucky_7 < 8) {
                D_8010D746_game_guys_lucky_7 = 6;
            }
        }
        D_8010D1D2_game_guys_lucky_7++;
        break;
    case 5:
        obj->func = func_80105F70_game_guys_lucky_7;
        break;
    }
}

void func_8010783C_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D1D4_game_guys_lucky_7) {
    case 0:
        D_8010D1D8_game_guys_lucky_7 = 0.0f;
        HuAudFXPlay(0x51D);
        D_8010D1D4_game_guys_lucky_7 = 2;
        break;
    case 1:
        break;
    case 2:
        D_8010D1D8_game_guys_lucky_7 += 0.11f;
        if (D_8010D1D8_game_guys_lucky_7 >= 1.7f) {
            D_8010D1D8_game_guys_lucky_7 = 1.7f;
        }
        D_8010D730_game_guys_lucky_7 += D_8010D1D8_game_guys_lucky_7 * D_8010D1D8_game_guys_lucky_7 * -17.75f;
        if (D_8010D730_game_guys_lucky_7 <= 0.0f) {
            HuAudFXPlay(0x520);
            D_8010D726_game_guys_lucky_7 = 1;
            D_8010D1D4_game_guys_lucky_7++;
            D_8010D1D8_game_guys_lucky_7 = -1.47f;
        }
        break;
    case 3:
        D_8010D1D8_game_guys_lucky_7 += 0.22f;
        if (D_8010D1D8_game_guys_lucky_7 >= 1.7f) {
            D_8010D1D8_game_guys_lucky_7 = 1.7f;
        }
        D_8010D730_game_guys_lucky_7 += D_8010D1D8_game_guys_lucky_7 * D_8010D1D8_game_guys_lucky_7
            * ((D_8010D1D8_game_guys_lucky_7 >= 0.0f) ? -17.5f : 17.5f);
        D_8010D738_game_guys_lucky_7 = (D_8010D738_game_guys_lucky_7 < 360.0f) ? D_8010D738_game_guys_lucky_7 + 10.0f : 360.0f;
        if (D_8010D730_game_guys_lucky_7 <= 0.0f && D_8010D1D8_game_guys_lucky_7 >= 0.0f) {
            D_8010D800_game_guys_lucky_7 = 4;
            D_8010D730_game_guys_lucky_7 = 0.0f;
            D_8010D1D4_game_guys_lucky_7++;
        }
        break;
    case 4:
        if (D_8010D73C_game_guys_lucky_7 == 0) {
            obj->func = func_80106854_game_guys_lucky_7;
        }
        break;
    }
}

void func_80107AC4_game_guys_lucky_7(omObjData* obj) {
    switch (D_8010D1DC_game_guys_lucky_7) {
    case 0:
        D_8010D746_game_guys_lucky_7 = 7;
        HuAudFXPlay(0x51D);
        D_8010D1E0_game_guys_lucky_7 = 0.0f;
        D_8010D1DC_game_guys_lucky_7++;
        break;
    case 1:
        D_8010D748_game_guys_lucky_7 = 1.0f;
        D_8010D746_game_guys_lucky_7 = 8;
        D_8010D1DC_game_guys_lucky_7++;
        break;
    case 2:
        D_8010D1E0_game_guys_lucky_7 += 0.11f;
        if (D_8010D1E0_game_guys_lucky_7 >= 1.7f) {
            D_8010D1E0_game_guys_lucky_7 = 1.7f;
        }
        D_8010D750_game_guys_lucky_7 += D_8010D1E0_game_guys_lucky_7 * D_8010D1E0_game_guys_lucky_7 * -17.5f;
        if (D_8010D750_game_guys_lucky_7 < 0.0f) {
            HuAudFXPlay(0x520);
            D_8010D750_game_guys_lucky_7 = 0.0f;
            D_8010D742_game_guys_lucky_7 = 1;
            D_8010D1DC_game_guys_lucky_7++;
            D_8010D1E0_game_guys_lucky_7 = -1.47f;
            omVibrate(D_8010D6DC_game_guys_lucky_7.player, 2, 2, 20);
        }
        break;
    case 3:
        D_8010D1E0_game_guys_lucky_7 += 0.15f;
        if (D_8010D1E0_game_guys_lucky_7 >= 1.7f) {
            D_8010D1E0_game_guys_lucky_7 = 1.7f;
        }
        D_8010D750_game_guys_lucky_7 += D_8010D1E0_game_guys_lucky_7 * D_8010D1E0_game_guys_lucky_7
            * ((D_8010D1E0_game_guys_lucky_7 >= 0.0f) ? -17.5f : 17.5f);
        D_8010D754_game_guys_lucky_7 = (D_8010D754_game_guys_lucky_7 < 360.0f) ? D_8010D754_game_guys_lucky_7 + 10.0f : 360.0f;
        if (D_8010D750_game_guys_lucky_7 <= 0.0f && D_8010D1E0_game_guys_lucky_7 >= 0.0f) {
            HuAudFXPlay(0x51E);
            CharFXPlay(0x31, D_8010D6E1_game_guys_lucky_7);
            D_8010D76E_game_guys_lucky_7 = 1;
            D_8010D750_game_guys_lucky_7 = 0.0f;
            D_8010D748_game_guys_lucky_7 = 0.0f;
            D_8010D746_game_guys_lucky_7 = 9;
            obj->func = func_80105F70_game_guys_lucky_7;
            D_8010D1E4_game_guys_lucky_7 = 0;
            D_8010D1DC_game_guys_lucky_7 = 0;
        }
        break;
    }
}

void func_80107DE4_game_guys_lucky_7(omObjData* obj) {
    GwPlayer[D_8010D6DC_game_guys_lucky_7.player].gameCoin = D_8010D6DC_game_guys_lucky_7.coinsStart;
    if (D_8010D77A_game_guys_lucky_7 == 0) {
        GwPlayer[D_8010D6DC_game_guys_lucky_7.player].bonusCoin = 0;
    } else if (D_8010D77A_game_guys_lucky_7 == 1) {
        if (D_8010D776_game_guys_lucky_7 == 7) {
            GwPlayer[D_8010D6DC_game_guys_lucky_7.player].bonusCoin = 10;
        } else {
            GwPlayer[D_8010D6DC_game_guys_lucky_7.player].bonusCoin = 2;
        }
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80107EEC_game_guys_lucky_7;
}

void func_80107EEC_game_guys_lucky_7(omObjData* obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8010C824_game_guys_lucky_7();
        GMesClose();
        func_8005F524_main();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_80107F44_game_guys_lucky_7(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80107DE4_game_guys_lucky_7;
    }
}

void func_80107F6C_game_guys_lucky_7(void) {
    D_8010D772_game_guys_lucky_7 = 0;
    D_8010D774_game_guys_lucky_7 = 0;
    D_8010D776_game_guys_lucky_7 = 0;
    D_8010D778_game_guys_lucky_7 = 0;
    D_8010D77A_game_guys_lucky_7 = 0;
}

void func_80107F98_game_guys_lucky_7(omObjData* obj) {
    func_80107FD8_game_guys_lucky_7();
    func_801080E8_game_guys_lucky_7();
    func_8010826C_game_guys_lucky_7();
    obj->func = func_80108374_game_guys_lucky_7;
}

void func_80107FD8_game_guys_lucky_7(void) {
    L7SprInit4 init[3] = {
        { 0x640000, 1000, 160, 120 },
        { 0x640001, 900, 160, 57 },
        { 0x640002, 900, 160, 57 },
    };
    u16 i;

    for (i = 0; i < 3; i++) {
        D_8010D6EA_game_guys_lucky_7[i] = InitEspriteSlot(func_8000B838_main(init[i].file), 0, 0);
        func_8000BC48_main(D_8010D6EA_game_guys_lucky_7[i], 0x4000);
        func_8000BCC8_main(D_8010D6EA_game_guys_lucky_7[i], (u16)init[i].prio);
        func_8000BBD4_main(D_8010D6EA_game_guys_lucky_7[i], init[i].x, init[i].y);
    }
    func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[1]);
    func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[2]);
}

void func_801080E8_game_guys_lucky_7(void) {
    L7SprInit3 init[7] = {
        { 0x640003, 225, 202 },
        { 0x640004, 199, 202 },
        { 0x640005, 173, 202 },
        { 0x640006, 147, 202 },
        { 0x640007, 121, 202 },
        { 0x640008, 95, 202 },
        { 0x640009, 68, 200 },
    };
    u16 i;

    for (i = 0; i < 7; i++) {
        D_8010D6F0_game_guys_lucky_7[i] = InitEspriteSlot(func_8000B838_main(init[i].file), 0, 0);
        if (i != 0) {
            func_8000BC48_main(D_8010D6F0_game_guys_lucky_7[i], 0x4000);
        }
        func_8000BCC8_main(D_8010D6F0_game_guys_lucky_7[i], 700);
        func_8000BBD4_main(D_8010D6F0_game_guys_lucky_7[i], init[i].x, init[i].y);
        func_8000BE5C_main(D_8010D6F0_game_guys_lucky_7[i], 0.5f, 0.5f);
    }
    for (i = 0; i < 7; i++) {
        D_8010D700_game_guys_lucky_7[i] = 0.5f;
    }
}

void func_8010826C_game_guys_lucky_7(void) {
    L7SprInit3 init[5] = {
        { 0x21001A, 30, 22 },
        { 0x21001B, 42, 22 },
        { 0x31, 54, 22 },
        { 0x31, 66, 22 },
        { 0x31, 78, 22 },
    };
    u16 i;

    for (i = 0; i < 5; i++) {
        D_8010D71C_game_guys_lucky_7[i] = InitEspriteSlot(func_8000B838_main(init[i].file), 0, 0);
        func_8000BCC8_main(D_8010D71C_game_guys_lucky_7[i], 700);
        func_8000BBD4_main(D_8010D71C_game_guys_lucky_7[i], init[i].x, init[i].y);
    }
}

void func_80108374_game_guys_lucky_7(omObjData* obj) {
    func_801083A0_game_guys_lucky_7();
    func_80108498_game_guys_lucky_7();
    func_801085D4_game_guys_lucky_7();
}

void func_801083A0_game_guys_lucky_7(void) {
    if (D_8010D1E6_game_guys_lucky_7 >= 10) {
        switch (D_8010D1E8_game_guys_lucky_7) {
        case 0:
            func_8000BB54_main(D_8010D6EA_game_guys_lucky_7[1]);
            func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[2]);
            D_8010D1E8_game_guys_lucky_7++;
            break;
        case 1:
            func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[1]);
            func_8000BB54_main(D_8010D6EA_game_guys_lucky_7[2]);
            D_8010D1E8_game_guys_lucky_7++;
            break;
        case 2:
            func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[1]);
            func_8000BB94_main(D_8010D6EA_game_guys_lucky_7[2]);
            D_8010D1E8_game_guys_lucky_7 = 0;
            break;
        }
        D_8010D1E6_game_guys_lucky_7 = 0;
    } else {
        D_8010D1E6_game_guys_lucky_7++;
    }
}

void func_80108498_game_guys_lucky_7(void) {
    u16 i;

    for (i = 0; i < 7; i++) {
        if (i == D_8010D776_game_guys_lucky_7 - 1) {
            if (D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] < 1.0f) {
                D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] += 0.125f;
            } else {
                D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] = 1.0f;
            }
        } else if (D_8010D700_game_guys_lucky_7[i] > 0.5f) {
            D_8010D700_game_guys_lucky_7[i] -= 0.1f;
        } else {
            D_8010D700_game_guys_lucky_7[i] = 0.5f;
        }
    }
    for (i = 0; i < 7; i++) {
        func_8000BE5C_main(D_8010D6F0_game_guys_lucky_7[i], D_8010D700_game_guys_lucky_7[i], D_8010D700_game_guys_lucky_7[i]);
    }
}

void func_801085D4_game_guys_lucky_7(void) {
    s16 digit;
    s32 x = 0;

    if (D_8010D6DC_game_guys_lucky_7.coins >= 999) {
        D_8010D6DC_game_guys_lucky_7.coins = 999;
    } else if (D_8010D6DC_game_guys_lucky_7.coins == 0) {
        D_8010D6DC_game_guys_lucky_7.coins = 0;
    }
    digit = D_8010D6DC_game_guys_lucky_7.coins / 100;
    if (!(digit & 0xFFFF)) {
        func_8000BB94_main(D_8010D71C_game_guys_lucky_7[2]);
    } else {
        func_8000BD50_main(D_8010D71C_game_guys_lucky_7[2], digit);
        func_8000BBD4_main(D_8010D71C_game_guys_lucky_7[2], 54, 22);
        x += 12;
        func_8000BB54_main(D_8010D71C_game_guys_lucky_7[2]);
    }
    digit = (u16)(D_8010D6DC_game_guys_lucky_7.coins % 100) / 10;
    if (!(digit & 0xFFFF) && (u16)(D_8010D6DC_game_guys_lucky_7.coins / 100) == 0) {
        func_8000BB94_main(D_8010D71C_game_guys_lucky_7[3]);
    } else {
        func_8000BD50_main(D_8010D71C_game_guys_lucky_7[3], digit);
        func_8000BBD4_main(D_8010D71C_game_guys_lucky_7[3], x + 54, 22);
        x += 12;
        func_8000BB54_main(D_8010D71C_game_guys_lucky_7[3]);
    }
    func_8000BD50_main(D_8010D71C_game_guys_lucky_7[4], D_8010D6DC_game_guys_lucky_7.coins % 10);
    func_8000BBD4_main(D_8010D71C_game_guys_lucky_7[4], x + 54, 22);
    func_8000BB54_main(D_8010D71C_game_guys_lucky_7[4]);
}

void func_801087B4_game_guys_lucky_7(omObjData* obj) {
    s32 files[4];
    u16 i;
    s32 attr = 0x2A9;
    s32 chr = D_8010D6DC_game_guys_lucky_7.chr;

    files[0] = D_800A178C_main[chr][0] | D_800A178C_main[chr][1];
    files[1] = 9;
    files[2] = 0x82;
    files[3] = 0x83;
    {
    s32 motions[10] = {
        func_80017BB8_main(chr, 0),
        func_80017BB8_main(chr, 1),
        func_80017BB8_main(chr, 4),
        func_80017BB8_main(chr, 0x2B),
        func_80017BB8_main(chr, 0x1F),
        func_80017BB8_main(chr, 0x2F),
        func_80017BB8_main(chr, 0x36),
        func_80017BB8_main(chr, 0x29),
        func_80017BB8_main(chr, 0xF),
        func_80017BB8_main(chr, 0x15),
    };


    obj->model[0] = func_8000B108_main(files[0], attr);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        func_8000B460_main(obj, i, motions[i]);
    }
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 4, 2);
    for (i = 1; i < 4; i++) {
        obj->model[i] = func_8000B108_main(files[i], attr);
    }
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    D_8010D742_game_guys_lucky_7 = 0;
    D_8010D744_game_guys_lucky_7 = 0;
    D_8010D746_game_guys_lucky_7 = 0;
    D_8010D74C_game_guys_lucky_7 = 1340.0f;
    D_8010D750_game_guys_lucky_7 = 0.0f;
    D_8010D754_game_guys_lucky_7 = 270.0f;
    obj->func = func_80108B64_game_guys_lucky_7;
    }
}

void func_80108B64_game_guys_lucky_7(omObjData* obj) {
    f32 scale;
    u16 i;
    u16 n;

    if (D_8010D1EA_game_guys_lucky_7 != D_8010D746_game_guys_lucky_7) {
        switch (D_8010D746_game_guys_lucky_7) {
        case 4:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D746_game_guys_lucky_7]].unk02, 0, 10, 0);
            break;
        case 0:
        case 1:
        case 9:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D746_game_guys_lucky_7]].unk02, 0, 4, 2);
            break;
        case 2:
        case 3:
            func_8001C5B4_main(obj->model[0], obj->motion[D_8010D746_game_guys_lucky_7]);
            break;
        case 5:
            func_8001C5B4_main(obj->model[0], obj->motion[5]);
            func_80045ED0_main(D_800A178C_main[D_8010D6DC_game_guys_lucky_7.chr][0] | 0x2F);
            break;
        case 6:
            func_8001C5B4_main(obj->model[0], obj->motion[6]);
            func_80045ED0_main(D_800A178C_main[D_8010D6DC_game_guys_lucky_7.chr][0] | 0x36);
            break;
        case 7:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D746_game_guys_lucky_7]].unk02, 0, 10, 2);
            break;
        case 8:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D746_game_guys_lucky_7]].unk02, 0, 30, 1);
            break;
        }
        D_8010D1EA_game_guys_lucky_7 = D_8010D746_game_guys_lucky_7;
    }
    if (D_8010D744_game_guys_lucky_7 == 1) {
        switch (D_8010D1EC_game_guys_lucky_7) {
        case 0:
            D_8010D1F0_game_guys_lucky_7 = -1.47f;
            if (D_8010D754_game_guys_lucky_7 != 270.0f) {
                D_8010D746_game_guys_lucky_7 = 1;
                D_8010D1EC_game_guys_lucky_7++;
            } else {
                D_8010D1EC_game_guys_lucky_7 += 2;
            }
            break;
        case 1:
            D_8010D754_game_guys_lucky_7 -= 10.0f;
            if (D_8010D754_game_guys_lucky_7 <= 270.0f) {
                D_8010D754_game_guys_lucky_7 = 270.0f;
                D_8010D1EC_game_guys_lucky_7++;
            }
            break;
        case 2:
            if (D_8010D1EE_game_guys_lucky_7++ == 0) {
                D_8010D746_game_guys_lucky_7 = 2;
                CharFXPlay(0x3A, D_8010D6E1_game_guys_lucky_7);
            } else if (D_8010D1EE_game_guys_lucky_7 >= 5) {
                D_8010D1EE_game_guys_lucky_7 = 0;
                D_8010D1EC_game_guys_lucky_7++;
            }
            break;
        case 3:
            if (D_8010D1F0_game_guys_lucky_7 >= 1.7f) {
                D_8010D1F0_game_guys_lucky_7 = 1.7f;
            }
            if (D_8010D1F4_game_guys_lucky_7 == 7 && D_8010D1F0_game_guys_lucky_7 >= 0.5f) {
                D_8010D746_game_guys_lucky_7 = 7;
            }
            D_8010D74C_game_guys_lucky_7 -= 7.14f;
            D_8010D750_game_guys_lucky_7 += D_8010D1F0_game_guys_lucky_7 * D_8010D1F0_game_guys_lucky_7
                * ((D_8010D1F0_game_guys_lucky_7 >= 0.0f) ? -35.0f : 35.0f);
            if (D_8010D750_game_guys_lucky_7 < D_8010D1FC_game_guys_lucky_7[D_8010D1F4_game_guys_lucky_7][0]
                && D_8010D1F0_game_guys_lucky_7 >= 0.0f) {
                D_8010D750_game_guys_lucky_7 = D_8010D1FC_game_guys_lucky_7[D_8010D1F4_game_guys_lucky_7][0];
                n = D_8010D776_game_guys_lucky_7++;
                if (D_8010D1F4_game_guys_lucky_7 != 7) {
                    D_8010D746_game_guys_lucky_7 = 4;
                    HuAudFXPlay(n + 0x524);
                }
                D_8010D1EC_game_guys_lucky_7 += 2;
            }
            D_8010D1F0_game_guys_lucky_7 += 0.22f;
            break;
        case 4:
            if (D_8010D1EE_game_guys_lucky_7++ != 0) {
                D_8010D1EE_game_guys_lucky_7 = 0;
                D_8010D1EC_game_guys_lucky_7++;
            }
            break;
        case 5:
            D_8010D1F0_game_guys_lucky_7 = 0.0f;
            D_8010D1EC_game_guys_lucky_7 = 0;
            D_8010D1EE_game_guys_lucky_7 = 0;
            D_8010D1F4_game_guys_lucky_7++;
            D_8010D744_game_guys_lucky_7 = 0;
            break;
        }
    }
    omSetTra(obj, D_8010D74C_game_guys_lucky_7, D_8010D750_game_guys_lucky_7, 0.0f);
    omSetRot(obj, 0.0f, D_8010D754_game_guys_lucky_7, 0.0f);
    if (D_8010D742_game_guys_lucky_7 == 1) {
        for (i = 2; i < 4; i++) {
            func_8001C6A8_main(obj->model[i], 0.0f);
        }
        D_8010D742_game_guys_lucky_7 = 0;
    }
    scale = (1340.0f - D_8010D750_game_guys_lucky_7) * (1.0f / 1340.0f);
    if (D_8010D74C_game_guys_lucky_7 >= 300.0f || D_8010D74C_game_guys_lucky_7 <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(obj->model[i], D_8010D74C_game_guys_lucky_7, 0.0f, 10.0f);
        }
        Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(obj->model[1], D_8010D74C_game_guys_lucky_7, 5000.0f, 0.0f);
    }
}

void func_801092B0_game_guys_lucky_7(omObjData* obj) {
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA0063, 9, 0x82, 0x83 };
    s32 motions[10] = { 0xA0065, 0xA006A, 0xA0069, 0xA0067, 0xA006B, 0xA0073, 0xA0074, 0xA006E, 0xA006D, 0xA0070 };
    u16 i;

    obj->model[0] = func_8000B108_main(files[0], attr);
    omSetTra(obj, 0.0f, 190.0f, 5100.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        func_8000B460_main(obj, i, motions[i]);
    }
    for (i = 1; i < 4; i++) {
        obj->model[i] = func_8000B108_main(files[i], attr);
    }
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    D_8010D726_game_guys_lucky_7 = 0;
    D_8010D728_game_guys_lucky_7 = 0;
    D_8010D72C_game_guys_lucky_7 = 0.0f;
    D_8010D730_game_guys_lucky_7 = 190.0f;
    D_8010D734_game_guys_lucky_7 = 5100.0f;
    D_8010D738_game_guys_lucky_7 = 0.0f;
    D_8010D73C_game_guys_lucky_7 = 0;
    D_8010D73E_game_guys_lucky_7 = 1;
    obj->func = func_80109570_game_guys_lucky_7;
}

void func_80109570_game_guys_lucky_7(omObjData* obj) {
    f32 scale;
    u16 i;

    if (D_8010D258_game_guys_lucky_7 != D_8010D73C_game_guys_lucky_7) {
        switch (D_8010D73C_game_guys_lucky_7) {
        case 9:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D73C_game_guys_lucky_7]].unk02, 0, 10, 0);
            break;
        case 0:
        case 3:
        case 5:
        case 8:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D73C_game_guys_lucky_7]].unk02, 0, 4, 2);
            break;
        case 1:
        case 2:
        case 4:
        case 7:
            func_8001C5B4_main(obj->model[0], obj->motion[D_8010D73C_game_guys_lucky_7]);
            break;
        case 6:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010D73C_game_guys_lucky_7]].unk02, 0, 15, 0);
            break;
        }
        D_8010D258_game_guys_lucky_7 = D_8010D73C_game_guys_lucky_7;
    }
    if (D_8010D800_game_guys_lucky_7 == 3 && D_8010D73C_game_guys_lucky_7 == 6
        && HmfModelData[obj->model[0]].unk40 >= 30.0f) {
        func_8001C6A8_main(obj->model[0], 15.0f);
        D_8010D73E_game_guys_lucky_7 = 0;
        func_8001C92C_main(obj->model[0], 0.0f);
        D_8010D800_game_guys_lucky_7 = 0;
    }
    if (D_8010D800_game_guys_lucky_7 == 4) {
        D_8010D73E_game_guys_lucky_7 = 1;
        func_8001C92C_main(obj->model[0], 1.0f);
        if (HmfModelData[obj->model[0]].unk40 == D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02) {
            D_8010D73C_game_guys_lucky_7 = 0;
            D_8010D800_game_guys_lucky_7 = 0;
        }
    }
    if (D_8010D728_game_guys_lucky_7 == 1) {
        switch (D_8010D25A_game_guys_lucky_7) {
        case 0:
            D_8010D260_game_guys_lucky_7 = -1.47f;
            if (D_8010D738_game_guys_lucky_7 != 270.0f) {
                D_8010D73C_game_guys_lucky_7 = 0;
                D_8010D25A_game_guys_lucky_7++;
            } else {
                D_8010D25A_game_guys_lucky_7 += 2;
            }
            break;
        case 1:
            D_8010D738_game_guys_lucky_7 -= 10.0f;
            if (D_8010D738_game_guys_lucky_7 <= 270.0f) {
                D_8010D738_game_guys_lucky_7 = 270.0f;
                D_8010D73C_game_guys_lucky_7 = 0;
                D_8010D25A_game_guys_lucky_7++;
            }
            break;
        case 2:
            if (D_8010D25C_game_guys_lucky_7 >= 4) {
                D_8010D25C_game_guys_lucky_7 = 0;
                D_8010D25A_game_guys_lucky_7++;
                HuAudFXPlay(0x519);
                D_8010D73C_game_guys_lucky_7 = 3;
            } else {
                D_8010D25C_game_guys_lucky_7++;
            }
            break;
        case 3:
            if (D_8010D260_game_guys_lucky_7 >= 1.7f) {
                D_8010D260_game_guys_lucky_7 = 1.7f;
            }
            if (D_8010D264_game_guys_lucky_7 == 7 && D_8010D260_game_guys_lucky_7 >= 0.8f) {
                D_8010D774_game_guys_lucky_7++;
                D_8010D25A_game_guys_lucky_7 += 2;
                D_8010D800_game_guys_lucky_7 = 3;
                D_8010D73C_game_guys_lucky_7 = 6;
            } else {
                if (D_8010D264_game_guys_lucky_7 == 0) {
                    D_8010D72C_game_guys_lucky_7 -= 11.5f;
                } else if (D_8010D264_game_guys_lucky_7 == 7) {
                    D_8010D72C_game_guys_lucky_7 -= 17.0f;
                    D_8010D738_game_guys_lucky_7 += 5.0f;
                } else {
                    D_8010D72C_game_guys_lucky_7 -= 7.14f;
                }
                D_8010D730_game_guys_lucky_7 += D_8010D260_game_guys_lucky_7 * D_8010D260_game_guys_lucky_7
                    * ((D_8010D260_game_guys_lucky_7 >= 0.0f) ? -35.0f : 35.0f);
                if (D_8010D730_game_guys_lucky_7 < D_8010D26C_game_guys_lucky_7[D_8010D264_game_guys_lucky_7][0]
                    && D_8010D260_game_guys_lucky_7 >= 0.0f) {
                    D_8010D730_game_guys_lucky_7 = D_8010D26C_game_guys_lucky_7[D_8010D264_game_guys_lucky_7][0];
                    HuAudFXPlay(0x51A);
                    if (D_8010D774_game_guys_lucky_7 != 7) {
                        D_8010D73C_game_guys_lucky_7 = 9;
                    }
                    D_8010D774_game_guys_lucky_7++;
                    D_8010D25A_game_guys_lucky_7 += 2;
                }
                D_8010D260_game_guys_lucky_7 += 0.22f;
            }
            break;
        case 4:
            if (D_8010D25C_game_guys_lucky_7 >= 3) {
                D_8010D25C_game_guys_lucky_7 = 0;
                D_8010D25A_game_guys_lucky_7++;
                D_8010D73C_game_guys_lucky_7 = 0;
            } else {
                D_8010D25C_game_guys_lucky_7++;
            }
            break;
        case 5:
            D_8010D260_game_guys_lucky_7 = 0.0f;
            D_8010D25A_game_guys_lucky_7 = 0;
            D_8010D25C_game_guys_lucky_7 = 0;
            D_8010D264_game_guys_lucky_7++;
            D_8010D728_game_guys_lucky_7 = 0;
            break;
        }
    }
    omSetTra(obj, D_8010D72C_game_guys_lucky_7, D_8010D730_game_guys_lucky_7, D_8010D734_game_guys_lucky_7);
    omSetRot(obj, 0.0f, D_8010D738_game_guys_lucky_7, 0.0f);
    func_8001C92C_main(obj->model[0], D_8010D73E_game_guys_lucky_7);
    if (D_8010D726_game_guys_lucky_7 == 1) {
        for (i = 2; i < 4; i++) {
            func_8001C6A8_main(obj->model[i], 0.0f);
        }
        D_8010D726_game_guys_lucky_7 = 0;
    }
    if (D_8010D726_game_guys_lucky_7 == 2) {
        func_8001C6A8_main(obj->model[2], 0.0f);
        D_8010D726_game_guys_lucky_7 = 0;
        Hu3DModelPosSet(obj->model[2], D_8010D72C_game_guys_lucky_7, D_8010D730_game_guys_lucky_7, -100.0f);
    }
    scale = (1340.0f - D_8010D730_game_guys_lucky_7) * (1.0f / 1340.0f);
    if (D_8010D72C_game_guys_lucky_7 >= 350.0f || D_8010D72C_game_guys_lucky_7 <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(obj->model[i], D_8010D72C_game_guys_lucky_7, 0.0f, -100.0f);
        }
        Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(obj->model[1], D_8010D72C_game_guys_lucky_7, 5000.0f, -100.0f);
    }
    D_8010D740_game_guys_lucky_7 = (s16)HmfModelData[obj->model[0]].unk40 / 2;
    if (D_8010D800_game_guys_lucky_7 == 5) {
        if (obj->trans.z < 900.0f) {
            D_8010D734_game_guys_lucky_7 = obj->trans.z += 100.0f;
        } else if (obj->trans.x < 0.0f) {
            D_8010D738_game_guys_lucky_7 = obj->rot.y = 90.0f;
            D_8010D72C_game_guys_lucky_7 = obj->trans.x += 15.0f;
        } else if (obj->rot.y > 0.0f) {
            D_8010D738_game_guys_lucky_7 = obj->rot.y -= 10.0f;
            if (obj->rot.y <= 0.0f) {
                D_8010D738_game_guys_lucky_7 = obj->rot.y = 0.0f;
                D_8010D800_game_guys_lucky_7 = 0;
                D_8010D73C_game_guys_lucky_7 = 0;
            }
        }
    }
}

void func_80109FA4_game_guys_lucky_7(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x83, 0x2A9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x83);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    D_8010D76C_game_guys_lucky_7 = 0;
    obj->func = func_8010A04C_game_guys_lucky_7;
}

void func_8010A04C_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D76C_game_guys_lucky_7 == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        D_8010D76C_game_guys_lucky_7 = 0;
    }
    omSetTra(obj, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f, D_8010D764_game_guys_lucky_7 + 120.0f);
}

void func_8010A0DC_game_guys_lucky_7(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xB002F, 0x2A9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xB002F);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C8A8_main(obj->model[0], 0);
    D_8010D76E_game_guys_lucky_7 = 0;
    obj->func = func_8010A19C_game_guys_lucky_7;
}

void func_8010A19C_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D76E_game_guys_lucky_7 == 1) {
        func_8001C8A8_main(obj->model[0], 1);
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        D_8010D76E_game_guys_lucky_7 = 0;
        if (D_8010D776_game_guys_lucky_7 >= 8) {
            omSetTra(obj, D_8010D74C_game_guys_lucky_7, 125.0f, 0.0f);
        } else if (D_8010D774_game_guys_lucky_7 >= 8) {
            omSetTra(obj, D_8010D72C_game_guys_lucky_7, 125.0f, -100.0f);
        }
    }
}

void func_8010A278_game_guys_lucky_7(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xB0006, 0x2A9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(obj, 0, 0xB0006);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    D_8010D770_game_guys_lucky_7 = 0;
    obj->func = func_8010A328_game_guys_lucky_7;
}

void func_8010A328_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D770_game_guys_lucky_7 == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        D_8010D770_game_guys_lucky_7 = 0;
    }
    omSetTra(obj, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f, D_8010D764_game_guys_lucky_7 + 120.0f);
}

void func_8010A3B8_game_guys_lucky_7(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x64000B, 0x2A9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    D_8010D758_game_guys_lucky_7 = 0;
    D_8010D75C_game_guys_lucky_7 = 0.0f;
    D_8010D760_game_guys_lucky_7 = 0.0f;
    D_8010D764_game_guys_lucky_7 = 0.0f;
    obj->func = func_8010A458_game_guys_lucky_7;
}

void func_8010A458_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D758_game_guys_lucky_7 == 1) {
        switch (D_8010D2C8_game_guys_lucky_7) {
        case 0:
            D_8010D2CC_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(4.0f) * 90;
            D_8010D2D0_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(4.0f) * 90;
            D_8010D2D4_game_guys_lucky_7 = 0.0f;
            D_8010D2D8_game_guys_lucky_7 = 0.0f;
            if (D_8010D772_game_guys_lucky_7 == 0) {
                D_8010D75C_game_guys_lucky_7 = D_8010D72C_game_guys_lucky_7;
                D_8010D760_game_guys_lucky_7 = D_8010D730_game_guys_lucky_7 + 250.0f;
                D_8010D764_game_guys_lucky_7 = -100.0f;
            } else if (D_8010D772_game_guys_lucky_7 == 1) {
                D_8010D75C_game_guys_lucky_7 = D_8010D74C_game_guys_lucky_7;
                D_8010D760_game_guys_lucky_7 = D_8010D750_game_guys_lucky_7 + 250.0f;
                D_8010D764_game_guys_lucky_7 = 0.0f;
            }
            D_8010D2C8_game_guys_lucky_7++;
            break;
        case 1:
            D_8010D2D4_game_guys_lucky_7 = (D_8010D2D4_game_guys_lucky_7 < 0.99f) ? D_8010D2D4_game_guys_lucky_7 + 0.4f : 1.0f;
            D_8010D2D8_game_guys_lucky_7 = (D_8010D2D8_game_guys_lucky_7 < 0.99f) ? D_8010D2D8_game_guys_lucky_7 + 0.8f : 1.0f;
            if (D_8010D2DC_game_guys_lucky_7++ >= 10.0f) {
                D_8010D2DC_game_guys_lucky_7 = 0.0f;
                D_8010D2CC_game_guys_lucky_7 = 0.0f;
                D_8010D2D0_game_guys_lucky_7 = 0.0f;
                HuAudFXPlay(0x51B);
                D_8010D2C8_game_guys_lucky_7++;
            }
            break;
        case 2:
            D_8010D2CC_game_guys_lucky_7 += 36.0f;
            if (D_8010D2CC_game_guys_lucky_7 >= 360.0f) {
                D_8010D2CC_game_guys_lucky_7 -= 360.0f;
            } else if (D_8010D2CC_game_guys_lucky_7 < 0.0f) {
                D_8010D2CC_game_guys_lucky_7 += 360.0f;
            }
            break;
        }
    } else if (D_8010D758_game_guys_lucky_7 == 2) {
    HuAudFXPlay(0x51C);
    D_8010D758_game_guys_lucky_7 = 0;
    } else if (D_8010D758_game_guys_lucky_7 == 0) {
    if (D_8010D2D4_game_guys_lucky_7 > 0.0f) {
        D_8010D2D4_game_guys_lucky_7 -= 0.2f;
    } else {
        D_8010D2D4_game_guys_lucky_7 = 0.0f;
    }
    if (D_8010D2D8_game_guys_lucky_7 > 0.0f) {
        D_8010D2D8_game_guys_lucky_7 -= 0.2f;
    } else {
        D_8010D2D8_game_guys_lucky_7 = 0.0f;
    }
    D_8010D2C8_game_guys_lucky_7 = 0;
    }
    omSetTra(obj, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
    omSetRot(obj, D_8010D2CC_game_guys_lucky_7, D_8010D2D0_game_guys_lucky_7, 0.0f);
    omSetSca(obj, D_8010D2D4_game_guys_lucky_7, D_8010D2D8_game_guys_lucky_7, D_8010D2D8_game_guys_lucky_7);
}

void func_8010A8A4_game_guys_lucky_7(omObjData* obj) {
    u16 i = 0;
    s32 attr = 0x2A9;
    s32 files[6] = { 0x64000C, 0x64000D, 0x64000E, 0x64000F, 0x640010, 0x640011 };

    for (; i < 6; i++) {
        obj->model[i] = func_8000B108_main(files[i], attr);
    }
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 6; i++) {
        Hu3DModelPosSet(obj->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i], 1.0f, 1.0f, 1.0f);
    }
    for (i = 0; i < 6; i++) {
        func_8001C8A8_main(obj->model[i], 0);
    }
    D_8010D768_game_guys_lucky_7 = 0;
    D_8010D76A_game_guys_lucky_7 = 0;
    obj->func = func_8010AA8C_game_guys_lucky_7;
}

void func_8010AA8C_game_guys_lucky_7(omObjData* obj) {
    if (D_8010D768_game_guys_lucky_7 == 1) {
        switch (D_8010D2E0_game_guys_lucky_7) {
        case 0:
            D_8010D2E4_game_guys_lucky_7 = D_8010D760_game_guys_lucky_7;
            D_8010D2E8_game_guys_lucky_7 = 0.0f;
            D_8010D2EC_game_guys_lucky_7 = 0;
            func_8001C8A8_main(obj->model[D_8010D76A_game_guys_lucky_7], 1);
            D_8010D2E0_game_guys_lucky_7++;
            break;
        case 1:
            if (D_8010D2E8_game_guys_lucky_7 < 1.0f) {
                D_8010D2E8_game_guys_lucky_7 += 0.1f;
            } else {
                D_8010D2E8_game_guys_lucky_7 = 1.0f;
                D_8010D2E0_game_guys_lucky_7++;
            }
            D_8010D2E4_game_guys_lucky_7 += 0.0f;
            break;
        case 2:
            if (D_8010D2EC_game_guys_lucky_7 >= 15) {
                D_8010D2EC_game_guys_lucky_7 = 0;
                D_8010D2E0_game_guys_lucky_7++;
            } else {
                D_8010D2EC_game_guys_lucky_7++;
            }
            break;
        case 3:
            D_8010D2E0_game_guys_lucky_7 = 0;
            D_8010D768_game_guys_lucky_7 = 0;
            break;
        }
    } else if (D_8010D768_game_guys_lucky_7 == 0) {
        if (D_8010D2E8_game_guys_lucky_7 > 0.0f) {
            D_8010D2E8_game_guys_lucky_7 -= 0.1f;
        } else {
            D_8010D2E8_game_guys_lucky_7 = 0.0f;
            func_8001C8A8_main(obj->model[D_8010D76A_game_guys_lucky_7], 0);
        }
    }
    if (D_8010D76A_game_guys_lucky_7 == 0) {
        omSetTra(obj, D_8010D75C_game_guys_lucky_7, D_8010D2E4_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
        omSetSca(obj, D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7);
    } else {
        Hu3DModelPosSet(obj->model[D_8010D76A_game_guys_lucky_7], D_8010D75C_game_guys_lucky_7, D_8010D2E4_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
        Hu3DModelScaleSet(obj->model[D_8010D76A_game_guys_lucky_7], D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7);
    }
}

s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 mes) {
    s16 winId = func_80060880_main(x, y, mes);

    func_8005B63C_main(winId, 2, 2);
    func_80061100_main(winId, 1);
    func_8005BDFC_main(winId, 0);
    func_8005D294_main(winId);
    return winId;
}

void func_8010ADB8_game_guys_lucky_7(s16 winId) {
    func_8005D294_main(winId);
    func_80060EA8_main(winId, 1);
    func_800610E0_main(winId);
}

void func_8010ADF8_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu) {
    s16 i;

    func_8005F904_main();
    while (func_8005E0C0_main(winId) != 0) {
        switch (cpu) {
        case 0:
            if (D_800D5558_main[pad] & 0x8000) {
                func_8005F744_main(-0x8000, -0x8000, -0x8000, -0x8000);
            }
            break;
        case 1:
            for (i = 0; i < 10; i++) {
                func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000,
                                   (&D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7])->delay);
            }
            while (func_8005E0C0_main(winId) != 0) {
                HuPrcVSleep();
            }
            break;
        }
        HuPrcVSleep();
    }
    func_8005F904_main();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010AF44_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B13C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D598_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D5A0_game_guys_lucky_7);

void func_8010B334_game_guys_lucky_7(void) {
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(D_8010D2F0_game_guys_lucky_7[i], 0x2A9);
        D_8010D798_game_guys_lucky_7[i] = model;
        func_8003302C_main(HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, NULL, func_8010B6E0_game_guys_lucky_7);
    }
    omAddObj(0xA, 0xA, 0xA, -1, func_8010B498_game_guys_lucky_7);
}

void func_8010B498_game_guys_lucky_7(omObjData *obj) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (!((D_8010D804_game_guys_lucky_7 + i) & 7)) {
            func_8010B528_game_guys_lucky_7(D_8010D798_game_guys_lucky_7[i]);
        }
    }
    D_8010D804_game_guys_lucky_7++;
}

#ifdef NON_MATCHING
/* masked 0: retail swaps $f0/$f2 around the pos.x add */
void func_8010B528_game_guys_lucky_7(s16 model) {
    L7FxPart *part;
    s16 count;
    s16 i;

    count = ((s16 *)HmfModelData[model].hmf->unk16)[2];
    part = ((L7FxWork *)HmfModelData[model].unkBC)->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y <= 0.0f) {
            part->pos.x = (s32)(u8)(rand8() % 200) + -450.0f;
            part->pos.y = 1000.0f;
            part->pos.z = ((rand8() * 125) >> 5) - 500;
            part->dir.x = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->dir.y = 0.0f;
            part->dir.z = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->scale = 5.0f;
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B528_game_guys_lucky_7);
#endif

void func_8010B6E0_game_guys_lucky_7(s16 model) {
    HmfData *hmf;
    L7FxWork *work;
    L7FxPart *part;
    u16 count;
    s16 i;

    hmf = HmfModelData[model].hmf;
    work = (L7FxWork *)HmfModelData[model].unkBC;
    count = ((s16 *)hmf->unk16)[2]; /* HmfData +0x1A: face group count */
    if (work->unk02 == 0) {
        work->unk04 &= ~4;
        part = work->parts;
        for (i = 0; i < (s16)count; i++, part++) {
            part->scale = part->vel.x = part->vel.y = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->speed = 1.0f;
        }
        work->unk02++;
    }
    part = work->parts;
    for (i = 0; i < (s16)count; i++, part++) {
        if (part->pos.y > 0.0f) {
            part->pos.x += part->dir.x;
            part->pos.y += part->dir.y - 10.0f;
            part->pos.z += part->dir.z;
        } else {
            part->scale = 0.0f;
        }
    }
}
