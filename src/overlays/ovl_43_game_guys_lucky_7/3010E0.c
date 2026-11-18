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
void func_80107668_game_guys_lucky_7(omObjData* obj);
void func_80107AC4_game_guys_lucky_7(omObjData* obj);
void func_80107DE4_game_guys_lucky_7(omObjData* obj);
void func_80107F44_game_guys_lucky_7(omObjData* obj);
void func_80107F6C_game_guys_lucky_7(void);
void func_80107F98_game_guys_lucky_7(omObjData* obj);
void func_801087B4_game_guys_lucky_7(omObjData* obj);
void func_801092B0_game_guys_lucky_7(omObjData* obj);
void func_80109FA4_game_guys_lucky_7(omObjData* obj);
void func_8010A0DC_game_guys_lucky_7(omObjData* obj);
void func_8010A278_game_guys_lucky_7(omObjData* obj);
void func_8010A3B8_game_guys_lucky_7(omObjData* obj);
void func_8010A8A4_game_guys_lucky_7(omObjData* obj);
s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 mes);
void func_8010ADB8_game_guys_lucky_7(s16 winId);
void func_8010ADF8_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu);
s16 func_8010AF44_game_guys_lucky_7(s16 winId, s16 pad, s16 cpu, s16 arg3);

void func_801083A0_game_guys_lucky_7(void);
void func_80108498_game_guys_lucky_7(void);
void func_801085D4_game_guys_lucky_7(void);
void func_8010B528_game_guys_lucky_7(s16 model);

/* 306F70 */
void func_8010B830_game_guys_lucky_7(s16 x, s16 y);
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

/* .rodata */

/* .bss */
extern char D_8010D5D0_game_guys_lucky_7[];
extern s16 D_8010D6D0_game_guys_lucky_7; /* result message */
extern Process* D_8010D6D4_game_guys_lucky_7; /* rules window process */
extern L7Player D_8010D6DC_game_guys_lucky_7;
extern u16 D_8010D776_game_guys_lucky_7;
extern u16 D_8010D77A_game_guys_lucky_7; /* won */
extern u16 D_8010D77C_game_guys_lucky_7; /* rules window done */
extern s16 D_8010D802_game_guys_lucky_7; /* CPU level */
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80106500_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80106854_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80106A0C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80106CF4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107090_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D3B4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107270_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107668_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010783C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107AC4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107DE4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107EEC_game_guys_lucky_7);

void func_80107F44_game_guys_lucky_7(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80107DE4_game_guys_lucky_7;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107F6C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107F98_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107FD8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801080E8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010826C_game_guys_lucky_7);

void func_80108374_game_guys_lucky_7(void) {
    func_801083A0_game_guys_lucky_7();
    func_80108498_game_guys_lucky_7();
    func_801085D4_game_guys_lucky_7();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801083A0_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80108498_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801085D4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801087B4_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D404_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D434_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D488_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80108B64_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801092B0_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D508_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D518_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80109570_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80109FA4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A04C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A0DC_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A19C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A278_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A328_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A3B8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A458_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A8A4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010AA8C_game_guys_lucky_7);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D580_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D598_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D5A0_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B334_game_guys_lucky_7);

void func_8010B498_game_guys_lucky_7(omObjData *obj) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (!((D_8010D804_game_guys_lucky_7 + i) & 7)) {
            func_8010B528_game_guys_lucky_7(D_8010D798_game_guys_lucky_7[i]);
        }
    }
    D_8010D804_game_guys_lucky_7++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B528_game_guys_lucky_7);

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
