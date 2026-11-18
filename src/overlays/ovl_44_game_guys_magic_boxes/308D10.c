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

// magic boxes A: Game Guy's Magic Boxes (one player picks the left or the right of two boxes, up to three rounds,
// doubling the coins each round; a wrong box loses them all)

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
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];
extern u8 D_800D6A58_main;
extern s8 D_800CBB6E_main[];
extern u16 D_800CDA7C_main[]; /* input.h says s16: the buttons are read unsigned here */

// LOCAL
void func_801059A0_game_guys_magic_boxes(void);
s32 func_801059BC_game_guys_magic_boxes(f32 range);
void func_80105A28_game_guys_magic_boxes(void);
void func_80105AC0_game_guys_magic_boxes(void);
void func_80105AC8_game_guys_magic_boxes(void);
void func_80105B44_game_guys_magic_boxes(void);
void func_80105B60_game_guys_magic_boxes(omObjData* obj);
void func_80105CCC_game_guys_magic_boxes(void);
void func_80105FB4_game_guys_magic_boxes(omObjData* obj);
void func_80106558_game_guys_magic_boxes(omObjData* obj);
void func_801066F8_game_guys_magic_boxes(omObjData* obj);
void func_80106828_game_guys_magic_boxes(omObjData* obj);
void func_80106A2C_game_guys_magic_boxes(omObjData* obj);
void func_80106B50_game_guys_magic_boxes(omObjData* obj);
void func_80106CB8_game_guys_magic_boxes(omObjData* obj);
void func_80106DC4_game_guys_magic_boxes(omObjData* obj);
void func_80107020_game_guys_magic_boxes(void);
void func_801071B8_game_guys_magic_boxes(void);
void func_80107834_game_guys_magic_boxes(void);
void func_80107A3C_game_guys_magic_boxes(void);
void func_80107AE0_game_guys_magic_boxes(void);
void func_80107B64_game_guys_magic_boxes(void);
void func_80108294_game_guys_magic_boxes(void);
void func_80108498_game_guys_magic_boxes(void);
void func_8010861C_game_guys_magic_boxes(void);
void func_80108914_game_guys_magic_boxes(void);
void func_80108AF8_game_guys_magic_boxes(void);
void func_80108C04_game_guys_magic_boxes(void);
void func_80108D88_game_guys_magic_boxes(omObjData* obj);
void func_801090F0_game_guys_magic_boxes(omObjData* obj);
void func_8010935C_game_guys_magic_boxes(omObjData* obj);
void func_8010942C_game_guys_magic_boxes(omObjData* obj);
void func_80109600_game_guys_magic_boxes(omObjData* obj);
void func_80109658_game_guys_magic_boxes(omObjData* obj);
void func_8010982C_game_guys_magic_boxes(omObjData* obj);
void func_80109884_game_guys_magic_boxes(omObjData* obj);
void func_80109984_game_guys_magic_boxes(omObjData* obj);
void func_801099E4_game_guys_magic_boxes(omObjData* obj);
void func_80109A0C_game_guys_magic_boxes(void);
void func_80109AD8_game_guys_magic_boxes(GgmCamera* cam, f32 fov, f32 zoom, f32 rx, f32 ry, f32 rz, f32 cx, f32 cy,
                                         f32 cz);
void func_80109B10_game_guys_magic_boxes(GgmCamera* cam);
void func_80109C98_game_guys_magic_boxes(GgmSprite* sp, s32 file, s32 attr, s32 arg3);
void func_80109CFC_game_guys_magic_boxes(GgmSprite* sp, s16 prio, s16 attr, s16 x, s16 y, s16 w, s16 h, f32 rot,
                                         f32 sx, f32 sy);
void func_80109D3C_game_guys_magic_boxes(GgmSprite* sp, u8 show);
void func_80109E1C_game_guys_magic_boxes(void);
void func_8010A000_game_guys_magic_boxes(void);
void func_8010A1B0_game_guys_magic_boxes(s16 x, s16 y, s16 r);
void func_8010A388_game_guys_magic_boxes(s16 x, s16 y, s16 r);
void func_8010A4CC_game_guys_magic_boxes(void);
s16 func_8010A4EC_game_guys_magic_boxes(s16 x, s16 y, s16 mes);
void func_8010A560_game_guys_magic_boxes(s16 winId, s16 pad, s16 cpu);
s16 func_8010A6AC_game_guys_magic_boxes(s16 winId, s16 pad, s16 cpu, s16 choice, u16 cancel);
void func_8010A878_game_guys_magic_boxes(s16 winId);
// 30DC30
void func_8010A8C0_game_guys_magic_boxes(s16 x, s16 y);
s16 func_8010AC18_game_guys_magic_boxes(void);
void func_8010B8B4_game_guys_magic_boxes(void);

/* .data */
f32 D_8010C1E0_game_guys_magic_boxes = 1.0f; /* left box scale */
f32 D_8010C1E4_game_guys_magic_boxes = 1.0f; /* right box scale */
GgmCpuKey D_8010C1E8_game_guys_magic_boxes[3] = { { 0, 5 }, { 0, 25 }, { 0, 60 } }; /* by CPU level */
u8 D_8010C1EE_game_guys_magic_boxes = 0; /* the title effect's result */
u8 D_8010C1EF_game_guys_magic_boxes = 0; /* open step */
u16 D_8010C1F0_game_guys_magic_boxes = 0; /* open frames */
f32 D_8010C1F4_game_guys_magic_boxes = 0.0f; /* box rise speed */
u16 D_8010C1F8_game_guys_magic_boxes = 0; /* shuffle frame */
u8 D_8010C1FA_game_guys_magic_boxes = 0; /* round message step */
u8 D_8010C1FB_game_guys_magic_boxes = 0;
u8 D_8010C1FC_game_guys_magic_boxes = 0; /* choose step */
s16 D_8010C1FE_game_guys_magic_boxes = 0; /* choose frames */
s16 D_8010C200_game_guys_magic_boxes = 10; /* choose timer seconds */
s16 D_8010C202_game_guys_magic_boxes = 0; /* CPU choose frames */
f32 D_8010C204_game_guys_magic_boxes = 0.0f; /* cursor face scale */
u16 D_8010C208_game_guys_magic_boxes = 0; /* the choice shown */
u8 D_8010C20A_game_guys_magic_boxes = 0; /* reveal step */
f32 D_8010C20C_game_guys_magic_boxes = 1.0f; /* face scale while revealing */
u8 D_8010C210_game_guys_magic_boxes = 0; /* spot step */
u16 D_8010C212_game_guys_magic_boxes = 0; /* spot alpha */
s16 D_8010C214_game_guys_magic_boxes = 0; /* spot x */
s16 D_8010C216_game_guys_magic_boxes = 0; /* spot y */
u8 D_8010C218_game_guys_magic_boxes = 0; /* open step */
u16 D_8010C21A_game_guys_magic_boxes = 0; /* open frames */
u8 D_8010C21C_game_guys_magic_boxes = 0; /* next round step */
u16 D_8010C21E_game_guys_magic_boxes = 0x80; /* spot alpha */
u8 D_8010C220_game_guys_magic_boxes = 0; /* result frames */
s16 D_8010C222_game_guys_magic_boxes = -1; /* result step */
s16 D_8010C224_game_guys_magic_boxes = 0; /* result message */
extern char D_8010C514_game_guys_magic_boxes[];
extern char D_8010C520_game_guys_magic_boxes[];
extern char D_8010C530_game_guys_magic_boxes[];
extern char D_8010C538_game_guys_magic_boxes[];
extern char D_8010C544_game_guys_magic_boxes[];
extern char D_8010C550_game_guys_magic_boxes[];
extern char D_8010C55C_game_guys_magic_boxes[];
extern char D_8010C568_game_guys_magic_boxes[];
char* D_8010C228_game_guys_magic_boxes[8] = {
    D_8010C568_game_guys_magic_boxes, D_8010C55C_game_guys_magic_boxes, D_8010C550_game_guys_magic_boxes,
    D_8010C544_game_guys_magic_boxes, D_8010C538_game_guys_magic_boxes, D_8010C530_game_guys_magic_boxes,
    D_8010C520_game_guys_magic_boxes, D_8010C514_game_guys_magic_boxes,
}; /* character names (SJIS) */
s16 D_8010C248_game_guys_magic_boxes = 0; /* coin blink frames */
u8 D_8010C24A_game_guys_magic_boxes = 0; /* coin blink step */
f32 D_8010C24C_game_guys_magic_boxes = 0.0f; /* curtain scale */
u8 D_8010C250_game_guys_magic_boxes = 0xFF; /* Game Guy's motion shown */
u8 D_8010C251_game_guys_magic_boxes = 0xFF; /* left box's motion shown */
u8 D_8010C252_game_guys_magic_boxes = 1; /* left shadow scale */
u8 D_8010C253_game_guys_magic_boxes = 0xFF; /* right box's motion shown */
u8 D_8010C254_game_guys_magic_boxes = 1; /* right shadow scale */
extern char D_8010C574_game_guys_magic_boxes[];
extern GgmFaces D_8010C270_game_guys_magic_boxes;

/* .bss */
extern u8 D_8010C5D0_game_guys_magic_boxes[4]; /* the CPU's pick was right, by round */
extern u16 D_8010C5D4_game_guys_magic_boxes;
extern u16 D_8010C5D6_game_guys_magic_boxes; /* spot alpha */
extern Vec D_8010C5D8_game_guys_magic_boxes[2]; /* the boxes' spots in 3D */
extern GgmVec2 D_8010C5F0_game_guys_magic_boxes[2]; /* on screen */
extern GgmTrail D_8010C600_game_guys_magic_boxes[3]; /* drawn into each buffer */
extern char D_8010C630_game_guys_magic_boxes[0x100]; /* result message */
extern GgmCamera D_8010C730_game_guys_magic_boxes;
extern GgmPlayer D_8010C750_game_guys_magic_boxes;
extern omObjData* D_8010C758_game_guys_magic_boxes;
extern omObjData* D_8010C75C_game_guys_magic_boxes; /* curtain */
extern omObjData* D_8010C760_game_guys_magic_boxes; /* Game Guy */
extern omObjData* D_8010C764_game_guys_magic_boxes; /* left box */
extern omObjData* D_8010C768_game_guys_magic_boxes; /* left lid */
extern omObjData* D_8010C76C_game_guys_magic_boxes; /* right box */
extern omObjData* D_8010C770_game_guys_magic_boxes; /* right lid */
extern Process* D_8010C774_game_guys_magic_boxes;
extern Process* D_8010C778_game_guys_magic_boxes;
extern Process* D_8010C77C_game_guys_magic_boxes;
extern GgmSprite D_8010C780_game_guys_magic_boxes;
extern GgmSprite D_8010C7A0_game_guys_magic_boxes;
extern GgmSprite D_8010C7BC_game_guys_magic_boxes;
extern GgmSprite D_8010C7D8_game_guys_magic_boxes;
extern s16 D_8010C7FE_game_guys_magic_boxes; /* x of an unused sprite slot (never created) */
extern s16 D_8010C81E_game_guys_magic_boxes; /* likewise */
extern GgmSprite D_8010C838_game_guys_magic_boxes;
extern GgmRoundSprites D_8010C858_game_guys_magic_boxes[3];
extern GgmSprite D_8010C900_game_guys_magic_boxes;
extern GgmSprite D_8010C91C_game_guys_magic_boxes;
extern GgmSprite D_8010C938_game_guys_magic_boxes[3]; /* coin digits: ones, tens, hundreds */
extern GgmSprite D_8010C990_game_guys_magic_boxes; /* the player's face */
extern Vec D_8010C9B0_game_guys_magic_boxes[2]; /* the boxes' positions */
extern u8 D_8010C9C8_game_guys_magic_boxes; /* left box's motion */
extern u8 D_8010C9C9_game_guys_magic_boxes; /* right box's motion */
extern u8 D_8010C9CA_game_guys_magic_boxes; /* Game Guy's motion */
extern s16 D_8010C9CC_game_guys_magic_boxes;
extern f32 D_8010C9D0_game_guys_magic_boxes; /* curtain halves' x */
extern f32 D_8010C9D4_game_guys_magic_boxes;
extern u8 D_8010C9D8_game_guys_magic_boxes; /* curtain: 1 opens, 2 closes */
extern u8 D_8010C9D9_game_guys_magic_boxes;
extern u8 D_8010C9DA_game_guys_magic_boxes;
extern u8 D_8010C9DB_game_guys_magic_boxes[3][2]; /* by round: 1 if the box (0 left, 1 right) holds the coins */
extern u8 D_8010C9E1_game_guys_magic_boxes; /* the box chosen */
extern u8 D_8010C9E2_game_guys_magic_boxes; /* 1: won the round */
extern u8 D_8010C9E3_game_guys_magic_boxes[3]; /* the CPU's picks */
extern u8 D_8010C9E6_game_guys_magic_boxes; /* 1: every CPU pick right */
extern u8 D_8010C9E7_game_guys_magic_boxes; /* round */
extern u8 D_8010C9E8_game_guys_magic_boxes; /* director step */
extern HuSprite* D_8010C9EC_game_guys_magic_boxes;
extern s16 D_8010C9F0_game_guys_magic_boxes; /* spot sprite group */
extern u8* D_8010C9F4_game_guys_magic_boxes[3]; /* its 4-bit image buffers */
extern u8 D_8010CA00_game_guys_magic_boxes; /* buffer drawn this frame */
extern s16 D_8010CA02_game_guys_magic_boxes;
extern s16 D_8010CA04_game_guys_magic_boxes; /* the CPU's last round */
extern u8 D_8010CA06_game_guys_magic_boxes; /* 1: shadows grow */
extern s32 D_8010CA08_game_guys_magic_boxes; /* coins at the start */
extern s16 D_8010CA0C_game_guys_magic_boxes;
extern s16 D_8010CA0E_game_guys_magic_boxes; /* window process done */
extern s16 D_8010CA10_game_guys_magic_boxes;
extern s16 D_8010CA12_game_guys_magic_boxes;
extern s16 D_8010CA14_game_guys_magic_boxes; /* CPU level 0-2 */

void func_801059A0_game_guys_magic_boxes(void) {
    func_80105A28_game_guys_magic_boxes();
}

s32 func_801059BC_game_guys_magic_boxes(f32 range) {
    u8 hi = rand8();
    u8 lo = rand8();
    s32 shifted = (hi << 8);
    s32 r = ((lo | shifted) / 65536.0f) * range;

    return r;
}

void func_80105A28_game_guys_magic_boxes(void) {
    Hu3DAnimInit(0x20);
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_8004A208_main();
    func_80105AC0_game_guys_magic_boxes();
    func_80105AC8_game_guys_magic_boxes();
    func_80109E1C_game_guys_magic_boxes();
    func_80105B44_game_guys_magic_boxes();
    omAddObj(1000, 0, 0, -1, func_80105B60_game_guys_magic_boxes);
    omAddObj(10000, 0, 0, -1, func_801099E4_game_guys_magic_boxes);
}

void func_80105AC0_game_guys_magic_boxes(void) {
}

void func_80105AC8_game_guys_magic_boxes(void) {
    func_80109A0C_game_guys_magic_boxes();
    func_80109AD8_game_guys_magic_boxes(&D_8010C730_game_guys_magic_boxes, 19.03f, 1498.69f, 334.75f, 0.0f, 0.0f, 0.0f,
                                        10.82f, -505.55f);
    func_80109B10_game_guys_magic_boxes(&D_8010C730_game_guys_magic_boxes);
}

void func_80105B44_game_guys_magic_boxes(void) {
    func_8005A6B0_main();
}

void func_80105B60_game_guys_magic_boxes(omObjData* obj) {
    func_8010A8C0_game_guys_magic_boxes(0xA0, 0xBE);
    func_80105CCC_game_guys_magic_boxes();
    func_8010A000_game_guys_magic_boxes();
    D_8010C758_game_guys_magic_boxes = omAddObj(1, 10, 10, -1, func_80105FB4_game_guys_magic_boxes);
    D_8010C75C_game_guys_magic_boxes = omAddObj(2, 10, 10, -1, func_80106558_game_guys_magic_boxes);
    D_8010C760_game_guys_magic_boxes = omAddObj(3, 10, 10, -1, func_801066F8_game_guys_magic_boxes);
    D_8010C764_game_guys_magic_boxes = omAddObj(4, 10, 10, -1, func_80106828_game_guys_magic_boxes);
    D_8010C768_game_guys_magic_boxes = omAddObj(5, 10, 10, -1, func_80106A2C_game_guys_magic_boxes);
    D_8010C76C_game_guys_magic_boxes = omAddObj(6, 10, 10, -1, func_80106B50_game_guys_magic_boxes);
    D_8010C770_game_guys_magic_boxes = omAddObj(7, 10, 10, -1, func_80106CB8_game_guys_magic_boxes);
    WipeCreateIn(0xFF, 16);
    obj->func = func_80106DC4_game_guys_magic_boxes;
}

/* Hide the coins in one box per round; the CPU decides how many rounds it plays and its picks */
void func_80105CCC_game_guys_magic_boxes(void) {
    u8 i;

    D_8010C9B0_game_guys_magic_boxes[0].x = -150.0f;
    D_8010C9B0_game_guys_magic_boxes[0].y = 0.0f;
    D_8010C9B0_game_guys_magic_boxes[0].z = -1500.0f;
    D_8010C9B0_game_guys_magic_boxes[1].x = 150.0f;
    D_8010C9B0_game_guys_magic_boxes[1].y = 0.0f;
    D_8010C9B0_game_guys_magic_boxes[1].z = -1500.0f;
    D_8010CA06_game_guys_magic_boxes = 0;
    D_8010C9D0_game_guys_magic_boxes = -260.0f;
    D_8010C9D4_game_guys_magic_boxes = 260.0f;
    D_8010C9D8_game_guys_magic_boxes = 0;
    D_8010C9D9_game_guys_magic_boxes = 0;
    D_8010C1E0_game_guys_magic_boxes = 1.0f;
    D_8010C1E4_game_guys_magic_boxes = 1.0f;
    for (i = 0; i < 3; i++) {
        D_8010C9DB_game_guys_magic_boxes[i][0] = func_801059BC_game_guys_magic_boxes(2.0f);
        if (D_8010C9DB_game_guys_magic_boxes[i][0] == 0) {
            D_8010C9DB_game_guys_magic_boxes[i][1] = 1;
        } else {
            D_8010C9DB_game_guys_magic_boxes[i][1] = 0;
        }
    }
    if (D_8010C750_game_guys_magic_boxes.cpu == 0) {
        D_8010C9E1_game_guys_magic_boxes = 0;
    } else if (D_8010C750_game_guys_magic_boxes.cpu == 1) {
        D_8010CA04_game_guys_magic_boxes = func_801059BC_game_guys_magic_boxes(3.0f);
        if (D_8010C750_game_guys_magic_boxes.difficulty != 0) {
            D_8010CA04_game_guys_magic_boxes =
                func_801059BC_game_guys_magic_boxes(D_8010C750_game_guys_magic_boxes.difficulty);
            if (D_8010CA04_game_guys_magic_boxes <= 0) {
                D_8010CA04_game_guys_magic_boxes = 0;
            }
        }
        for (i = 0; i <= D_8010CA04_game_guys_magic_boxes; i++) {
            D_8010C9E3_game_guys_magic_boxes[i] = func_801059BC_game_guys_magic_boxes(2.0f);
        }
        D_8010C9E6_game_guys_magic_boxes = 1;
        for (i = 0; i <= D_8010CA04_game_guys_magic_boxes; i++) {
            if (D_8010C9DB_game_guys_magic_boxes[i][D_8010C9E3_game_guys_magic_boxes[i]] == 0) {
                D_8010C5D0_game_guys_magic_boxes[i] = 0;
                D_8010C9E6_game_guys_magic_boxes = 0;
            } else {
                D_8010C5D0_game_guys_magic_boxes[i] = 1;
            }
        }
        if (D_8010C9E6_game_guys_magic_boxes == 0) {
            D_8010CA02_game_guys_magic_boxes = 0;
        } else {
            D_8010CA02_game_guys_magic_boxes =
                D_8010C750_game_guys_magic_boxes.coins * ((D_8010CA04_game_guys_magic_boxes + 1) << 1);
        }
    }
    D_8010C9E7_game_guys_magic_boxes = 0;
    D_8010C9E8_game_guys_magic_boxes = 0;
}

void func_80105FB4_game_guys_magic_boxes(omObjData* obj) {
    u8 chr = GwPlayer[D_8010C750_game_guys_magic_boxes.player].chr;
    GgmFaces faces = D_8010C270_game_guys_magic_boxes;
    u8 i;

    func_80109C98_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 0x650000, 0, 0x4000);
    func_80109CFC_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 1000, 0x100, 0, 0, 320, 240, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 0x650001, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0x650002, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0);
    func_80109C98_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0x650003, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0);
    func_80109C98_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 0x650004, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 800, 0x100, 242, 16, 54, 54, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 1);
    for (i = 0; i < 3; i++) {
        func_80109C98_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].off, 0x21002A, 0, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].off, 99, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].off, 0);
        func_80109C98_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].on, 0x21002B, 0, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].on, 100, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].on, 1);
    }
    func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[0].off, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 0x21001A, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 100, 0x100, 24, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 0x21001B, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 100, 0x100, 36, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 1);
    for (i = 0; i < 3; i++) {
        func_80109C98_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 0x31, 1, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 100, 0x100, i * 12 + 48, 16, 12, 12,
                                            0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 1);
    }
    func_80109C98_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, faces.file[chr] | 0x210000, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 100, 0x100, 55, 70, 46, 46, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 0);
    obj->func = func_80108D88_game_guys_magic_boxes;
}

/* The curtain: two halves and their linked copies */
void func_80106558_game_guys_magic_boxes(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x650006, 0x2B9);
    omSetTra(obj, 330.0f, -400.0f, -1000.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    Hu3DModelPosSet(obj->model[1], 460.0f, -400.0f, -1000.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->model[2] = func_8000B108_main(0x650007, 0x2B9);
    obj->model[3] = Hu3DModelLink(obj->model[2]);
    Hu3DModelPosSet(obj->model[2], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[3], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    obj->func = func_801090F0_game_guys_magic_boxes;
}

/* Game Guy */
void func_801066F8_game_guys_magic_boxes(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xA0063, 0x2B9);
    func_8001C92C_main(obj->model[0], 1.0f);
    omSetTra(obj, 0.0f, 0.0f, -150.0f);
    omSetRot(obj, -10.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xA0063);
    func_8000B460_main(obj, 1, 0xA0068);
    func_8000B460_main(obj, 2, 0xA006C);
    D_8010C9CA_game_guys_magic_boxes = 0;
    obj->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, -150.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->func = func_8010935C_game_guys_magic_boxes;
}

/* The left box and its shadow */
void func_80106828_game_guys_magic_boxes(omObjData* obj) {
    void* data;
    s16 anim;

    obj->model[0] = func_8000B108_main(0xA0000, 0x2A9);
    func_8001C92C_main(obj->model[0], 1.0f);
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xA0001);
    func_8000B460_main(obj, 1, 0xA000A);
    func_8000B460_main(obj, 2, 0xA000B);
    func_8000B460_main(obj, 3, 0xA001F);
    func_8000B460_main(obj, 4, 0xA0020);
    data = DataRead(0xA002B);
    anim = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c160n_0_DEF");
    DataClose(data);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80032FC0_main(anim, 1, 0);
    func_80032FF8_main(anim, 0);
    D_8010C9C8_game_guys_magic_boxes = 1;
    obj->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[1], -150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(obj->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->func = func_8010942C_game_guys_magic_boxes;
}

/* The left lid and its coins */
void func_80106A2C_game_guys_magic_boxes(omObjData* obj) {
    D_8010CA10_game_guys_magic_boxes = obj->model[0] = func_8000B108_main(0x650009, 0x2B9);
    func_8001C92C_main(obj->model[0], 1.0f);
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x65000A);
    D_8010CA12_game_guys_magic_boxes = obj->model[1] = func_8000B108_main(0x650008, 0x2B9);
    Hu3DModelPosSet(obj->model[1], D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
                    D_8010C9B0_game_guys_magic_boxes[0].z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->func = func_80109600_game_guys_magic_boxes;
}

/* The right box and its shadow */
void func_80106B50_game_guys_magic_boxes(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xA00EE, 0x2B9);
    func_8001C92C_main(obj->model[0], 1.0f);
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xA00EE);
    func_8000B460_main(obj, 1, 0xA00F4);
    func_8000B460_main(obj, 2, 0xA00F5);
    func_8000B460_main(obj, 3, 0xA00FD);
    func_8000B460_main(obj, 4, 0xA00FE);
    D_8010C9C9_game_guys_magic_boxes = 1;
    obj->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[1], 150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(obj->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->func = func_80109658_game_guys_magic_boxes;
}

/* The right lid and its coins: links of the left's */
void func_80106CB8_game_guys_magic_boxes(omObjData* obj) {
    obj->model[0] = Hu3DModelLink(D_8010CA10_game_guys_magic_boxes);
    func_8001C92C_main(obj->model[0], 1.0f);
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x65000A);
    obj->model[1] = Hu3DModelLink(D_8010CA12_game_guys_magic_boxes);
    Hu3DModelPosSet(obj->model[1], D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
                    D_8010C9B0_game_guys_magic_boxes[1].z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    obj->func = func_8010982C_game_guys_magic_boxes;
}

/* The director */
void func_80106DC4_game_guys_magic_boxes(omObjData* obj) {
    switch (D_8010C9E8_game_guys_magic_boxes) {
    case 0:
        D_8010C1EE_game_guys_magic_boxes = func_8010AC18_game_guys_magic_boxes();
        if (D_8010C1EE_game_guys_magic_boxes == 1) {
            D_8010C9E8_game_guys_magic_boxes = 1;
        }
        break;
    case 1:
        D_8010C774_game_guys_magic_boxes = omAddPrcObj(func_80107020_game_guys_magic_boxes, 0x3F00, 0x800, 0);
        D_8010C9E8_game_guys_magic_boxes = 2;
        break;
    case 2:
        if (D_8010CA0E_game_guys_magic_boxes == 1) {
            D_8010C9E8_game_guys_magic_boxes = 3;
            D_8010CA0E_game_guys_magic_boxes = 0;
            omDelPrcObj(D_8010C774_game_guys_magic_boxes);
        }
        break;
    case 3:
        func_801071B8_game_guys_magic_boxes();
        break;
    case 4:
        func_80107834_game_guys_magic_boxes();
        break;
    case 5:
        D_8010C778_game_guys_magic_boxes = omAddPrcObj(func_80107A3C_game_guys_magic_boxes, 0x3F00, 0x800, 0);
        D_8010C9E8_game_guys_magic_boxes = 6;
        break;
    case 6:
        if (D_8010CA0E_game_guys_magic_boxes == 1) {
            D_8010C9E8_game_guys_magic_boxes = 7;
            D_8010CA0E_game_guys_magic_boxes = 0;
            omDelPrcObj(D_8010C778_game_guys_magic_boxes);
        }
        break;
    case 7:
        func_80107AE0_game_guys_magic_boxes();
        break;
    case 8:
        func_80107B64_game_guys_magic_boxes();
        break;
    case 9:
        func_80108294_game_guys_magic_boxes();
        break;
    case 10:
        func_80108498_game_guys_magic_boxes();
        break;
    case 11:
        func_8010861C_game_guys_magic_boxes();
        break;
    case 12:
        D_8010C77C_game_guys_magic_boxes = omAddPrcObj(func_80108914_game_guys_magic_boxes, 0x3F00, 0x800, 0);
        D_8010C9E8_game_guys_magic_boxes = 13;
        break;
    case 13:
        if (D_8010CA0E_game_guys_magic_boxes == 1) {
            D_8010C9E8_game_guys_magic_boxes = 14;
            D_8010CA0E_game_guys_magic_boxes = 0;
            omDelPrcObj(D_8010C77C_game_guys_magic_boxes);
        } else if (D_8010CA0E_game_guys_magic_boxes == 2) {
            HuAudSeqFadeOut(14);
            D_8010C9E8_game_guys_magic_boxes = 15;
            D_8010CA0E_game_guys_magic_boxes = 0;
            omDelPrcObj(D_8010C77C_game_guys_magic_boxes);
        }
        break;
    case 14:
        func_80108AF8_game_guys_magic_boxes();
        break;
    case 15:
        func_80108C04_game_guys_magic_boxes();
        break;
    case 16:
        obj->func = func_80109884_game_guys_magic_boxes;
        break;
    }
}

/* The opening message */
void func_80107020_game_guys_magic_boxes(void) {
    s16 winId;
    s16 r;
    s16 done = 0;

    D_8010CA0E_game_guys_magic_boxes = 0;
    winId = func_8010A4EC_game_guys_magic_boxes(0x82, 0xA0, 0xC);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2C00, -1, -1);
    func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad, D_8010C750_game_guys_magic_boxes.cpu);
    func_8005B43C_main(winId, 0x2C01, -1, -1);
    do {
        r = func_8010A6AC_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad,
                                                D_8010C750_game_guys_magic_boxes.cpu, 1, 0);
        switch (r) {
        case 0:
            func_8005B43C_main(winId, 0x2C02, -1, -1);
            func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad,
                                                D_8010C750_game_guys_magic_boxes.cpu);
        case 1:
            done = 1;
            break;
        }
        HuPrcVSleep();
    } while (done == 0);
    func_8005B43C_main(winId, 0x2C03, -1, -1);
    func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad, D_8010C750_game_guys_magic_boxes.cpu);
    func_8010A878_game_guys_magic_boxes(winId);
    D_8010CA0E_game_guys_magic_boxes = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* The boxes rise, open their lids and close again; the light spots follow them */
void func_801071B8_game_guys_magic_boxes(void) {
    D_8010C9B0_game_guys_magic_boxes[0].y -= D_8010C1F4_game_guys_magic_boxes;
    D_8010C9B0_game_guys_magic_boxes[1].y -= D_8010C1F4_game_guys_magic_boxes;
    D_8010C5D8_game_guys_magic_boxes[0].x = D_8010C9B0_game_guys_magic_boxes[0].x;
    D_8010C5D8_game_guys_magic_boxes[0].y = D_8010C9B0_game_guys_magic_boxes[0].y + 100.0f;
    D_8010C5D8_game_guys_magic_boxes[0].z = D_8010C9B0_game_guys_magic_boxes[0].z;
    D_8010C5D8_game_guys_magic_boxes[1].x = D_8010C9B0_game_guys_magic_boxes[1].x;
    D_8010C5D8_game_guys_magic_boxes[1].y = D_8010C9B0_game_guys_magic_boxes[1].y + 100.0f;
    D_8010C5D8_game_guys_magic_boxes[1].z = D_8010C9B0_game_guys_magic_boxes[1].z;
    Hu3DCam3DToScreen(0, &D_8010C5D8_game_guys_magic_boxes[0], &D_8010C5F0_game_guys_magic_boxes[0]);
    Hu3DCam3DToScreen(0, &D_8010C5D8_game_guys_magic_boxes[1], &D_8010C5F0_game_guys_magic_boxes[1]);
    switch (D_8010C1EF_game_guys_magic_boxes) {
    case 0:
        D_8010C5D4_game_guys_magic_boxes = 0;
        D_8010C5D6_game_guys_magic_boxes = 0;
        D_8010C9D9_game_guys_magic_boxes = 1;
        D_8010C1EF_game_guys_magic_boxes++;
        break;
    case 1:
        if (D_8010C5D6_game_guys_magic_boxes >= 0x80) {
            D_8010C1F4_game_guys_magic_boxes = 8.0f;
            D_8010CA06_game_guys_magic_boxes = 0;
        } else {
            D_8010C5D6_game_guys_magic_boxes += 8;
        }
        func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C5D6_game_guys_magic_boxes);
        if (D_8010C9B0_game_guys_magic_boxes[0].y == -128.0f) {
            HuAudFXPlay(0x535);
        }
        if (D_8010C9B0_game_guys_magic_boxes[0].y <= -450.0f) {
            HuAudFXPlay(0x531);
            HuAudFXPlay(0x530);
            D_8010C1EF_game_guys_magic_boxes++;
        }
        break;
    case 2:
        D_8010C1F4_game_guys_magic_boxes -= 0.4f;
        if (D_8010C1F4_game_guys_magic_boxes < 0.0f) {
            omVibrate(D_8010C750_game_guys_magic_boxes.player, 2, 3, 10);
            D_8010C1F4_game_guys_magic_boxes = 0.0f;
            D_8010C1EF_game_guys_magic_boxes++;
        }
        break;
    case 3:
        if (D_8010C5D6_game_guys_magic_boxes == 0) {
            D_8010C1EF_game_guys_magic_boxes = 4;
        } else {
            D_8010C5D6_game_guys_magic_boxes -= 8;
        }
        func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C5D6_game_guys_magic_boxes);
        break;
    case 4:
        if (D_8010C9E2_game_guys_magic_boxes != 0) {
            HuAudFXPlay(0x531);
            HuAudFXPlay(0x530);
        }
        HuAudFXPlay(0x52E);
        func_8001C92C_main(D_8010C768_game_guys_magic_boxes->model[0], -1.2f);
        func_8001C92C_main(D_8010C770_game_guys_magic_boxes->model[0], -1.2f);
        D_8010C1EF_game_guys_magic_boxes = 5;
        D_8010C9D9_game_guys_magic_boxes = 0;
        break;
    case 5:
        if (D_8010C1F0_game_guys_magic_boxes >= 13) {
            D_8010C9C8_game_guys_magic_boxes = 0;
            if (D_8010C9E7_game_guys_magic_boxes == 0) {
                D_8010C9C9_game_guys_magic_boxes = 0;
            }
        } else {
            D_8010C1F0_game_guys_magic_boxes++;
        }
        if (HmfModelData[D_8010C768_game_guys_magic_boxes->model[0]].unk40 < 0.0f) {
            func_8001C92C_main(D_8010C768_game_guys_magic_boxes->model[0], 0.0f);
            D_8010C1EF_game_guys_magic_boxes = 6;
        }
        if (HmfModelData[D_8010C770_game_guys_magic_boxes->model[0]].unk40 < 0.0f) {
            func_8001C92C_main(D_8010C770_game_guys_magic_boxes->model[0], 0.0f);
            D_8010C1EF_game_guys_magic_boxes = 6;
        }
        break;
    case 6:
        func_8001C8A8_main(D_8010C76C_game_guys_magic_boxes->model[0], 0);
        func_8001C8A8_main(D_8010C764_game_guys_magic_boxes->model[0], 0);
        D_8010C1F0_game_guys_magic_boxes = 0;
        D_8010C1EF_game_guys_magic_boxes = 4;
        D_8010C1F4_game_guys_magic_boxes = 0.0f;
        func_8001C92C_main(D_8010C768_game_guys_magic_boxes->model[0], 0.0f);
        func_8001C92C_main(D_8010C770_game_guys_magic_boxes->model[0], 0.0f);
        D_8010C9CA_game_guys_magic_boxes = 1;
        D_8010C9E8_game_guys_magic_boxes = 4;
        break;
    }
    if (D_8010C1EF_game_guys_magic_boxes < 4) {
        func_8010A388_game_guys_magic_boxes(D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[0].x,
                                            D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[0].y, 50);
        func_8010A388_game_guys_magic_boxes(D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[1].x,
                                            D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[1].y, 50);
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[0].x = D_8010C5F0_game_guys_magic_boxes[0].x;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[1].x = D_8010C5F0_game_guys_magic_boxes[1].x;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[0].y = D_8010C5F0_game_guys_magic_boxes[0].y;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes].pos[1].y = D_8010C5F0_game_guys_magic_boxes[1].y;
        func_8010A1B0_game_guys_magic_boxes(D_8010C5F0_game_guys_magic_boxes[0].x, D_8010C5F0_game_guys_magic_boxes[0].y, 50);
        func_8010A1B0_game_guys_magic_boxes(D_8010C5F0_game_guys_magic_boxes[1].x, D_8010C5F0_game_guys_magic_boxes[1].y, 50);
        D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 =
            D_8010C9F4_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes];
        D_8010CA00_game_guys_magic_boxes = (u8)(D_8010CA00_game_guys_magic_boxes + 1) % 3;
    }
}

/* Game Guy shuffles the boxes (a timeline by frame) */
void func_80107834_game_guys_magic_boxes(void) {
    switch (D_8010C1F8_game_guys_magic_boxes) {
    case 10:
        HuAudFXPlay(0x532);
        break;
    case 18:
        D_8010C9D8_game_guys_magic_boxes = 1;
        break;
    case 30:
        if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][0] == 1) {
            D_8010C9B0_game_guys_magic_boxes[0].x = -150.0f;
            D_8010C9B0_game_guys_magic_boxes[1].x = 150.0f;
        } else {
            D_8010C9B0_game_guys_magic_boxes[0].x = 150.0f;
            D_8010C9B0_game_guys_magic_boxes[1].x = -150.0f;
        }
        break;
    case 27:
        HuAudFXPlay(0x52D);
        break;
    case 43:
        D_8010C9CA_game_guys_magic_boxes = 2;
        break;
    case 45:
        func_8001C92C_main(D_8010C760_game_guys_magic_boxes->model[0], 0.0f);
        break;
    case 48:
        func_8001C92C_main(D_8010C760_game_guys_magic_boxes->model[0], 1.0f);
        break;
    case 60: /* nothing happens on these frames: they only make the switch a jump table */
    case 70:
        break;
    case 91:
        D_8010C9CA_game_guys_magic_boxes = 1;
        break;
    case 94:
        HuAudFXPlay(0x52D);
        func_8001C6A8_main(D_8010C760_game_guys_magic_boxes->model[0], 90.0f);
        func_8001C92C_main(D_8010C760_game_guys_magic_boxes->model[0], -1.0f);
        break;
    case 122:
        HuAudFXPlay(0x533);
        D_8010C9D8_game_guys_magic_boxes = 2;
        break;
    case 138:
        D_8010C9CA_game_guys_magic_boxes = 0;
        break;
    case 140:
        func_8001C92C_main(D_8010C760_game_guys_magic_boxes->model[0], 1.0f);
        D_8010C7FE_game_guys_magic_boxes = -58;
        D_8010C81E_game_guys_magic_boxes = 250;
        D_8010C1F8_game_guys_magic_boxes = 0;
        D_8010C9E8_game_guys_magic_boxes = 5;
        break;
    }
    D_8010C1F8_game_guys_magic_boxes++;
}

/* "Which box?" */
void func_80107A3C_game_guys_magic_boxes(void) {
    s16 winId;

    D_8010CA0E_game_guys_magic_boxes = 0;
    winId = func_8010A4EC_game_guys_magic_boxes(0x82, 0xA0, 0xC);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2C04, -1, -1);
    func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad, D_8010C750_game_guys_magic_boxes.cpu);
    func_8010A878_game_guys_magic_boxes(winId);
    D_8010CA0E_game_guys_magic_boxes = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* The round message */
void func_80107AE0_game_guys_magic_boxes(void) {
    if (D_8010C1FA_game_guys_magic_boxes == 0) {
        GMesClose();
        D_8010CA0C_game_guys_magic_boxes = GMesCreate(9);
        D_8010C1FA_game_guys_magic_boxes = 1;
    } else if (D_8010C1FA_game_guys_magic_boxes == 1) {
        if (GMesStatGet() == 0) {
            D_8010C9E8_game_guys_magic_boxes = 8;
            D_8010C1FA_game_guys_magic_boxes = 0;
            D_8010C1FB_game_guys_magic_boxes = 0;
        }
    }
}

#ifdef NON_MATCHING
/* register allocation only: retail ORs the A press with the timer test into a fresh register (or v0,s0,v0), this keeps it in s0 */
/* Choose a box: the player with the stick and A, the CPU after a wait; ten seconds */
void func_80107B64_game_guys_magic_boxes(void) {
    u8 dir = 0;
    s32 ok = 0;

    switch (D_8010C1FC_game_guys_magic_boxes) {
    case 0:
        GMesCreate(0x1A, 10, 156, 56);
        D_8010C9E1_game_guys_magic_boxes = 0;
        D_8010C208_game_guys_magic_boxes = 0;
        D_8010C1FC_game_guys_magic_boxes = 10;
        break;
    case 10:
        D_8010C990_game_guys_magic_boxes.x = 55;
        D_8010C990_game_guys_magic_boxes.sy = D_8010C204_game_guys_magic_boxes;
        D_8010C990_game_guys_magic_boxes.sx = D_8010C204_game_guys_magic_boxes;
        if (D_8010C204_game_guys_magic_boxes < 1.0f) {
            D_8010C204_game_guys_magic_boxes += 0.25f;
        } else {
            D_8010C1FC_game_guys_magic_boxes = 1;
        }
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
        if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 0) {
            if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
                D_8010C1E0_game_guys_magic_boxes -= 0.05f;
            }
            if (D_8010C1E4_game_guys_magic_boxes < 1.1f) {
                D_8010C1E4_game_guys_magic_boxes += 0.05f;
            }
        } else {
            if (D_8010C1E0_game_guys_magic_boxes < 1.1f) {
                D_8010C1E0_game_guys_magic_boxes += 0.05f;
            }
            if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
                D_8010C1E4_game_guys_magic_boxes -= 0.05f;
            }
        }
        omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
                 D_8010C1E0_game_guys_magic_boxes);
        Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                          D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
        omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
                 D_8010C1E4_game_guys_magic_boxes);
        Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                          D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
        break;
    case 1:
        if (D_8010C750_game_guys_magic_boxes.cpu == 0) {
            if (D_800CBB6E_main[D_8010C750_game_guys_magic_boxes.pad] > 64) {
                dir = 1;
            }
            if (D_800CBB6E_main[D_8010C750_game_guys_magic_boxes.pad] < -64) {
                dir = 2;
            }
            if (D_800CDA7C_main[D_8010C750_game_guys_magic_boxes.pad] & 0x8000) {
                ok = 1;
            }
            if (dir == 1) {
                D_8010C9E1_game_guys_magic_boxes = 1;
            } else if (dir == 2) {
                D_8010C9E1_game_guys_magic_boxes = 0;
            }
        } else if (D_8010C750_game_guys_magic_boxes.cpu == 1) {
            if (D_8010C202_game_guys_magic_boxes >= 35) {
                if (D_8010C9E3_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes] != D_8010C9E1_game_guys_magic_boxes) {
                    D_8010C9E1_game_guys_magic_boxes = 1;
                    D_8010C202_game_guys_magic_boxes = 0;
                } else {
                    D_8010C202_game_guys_magic_boxes = 0;
                    ok = 1;
                }
            } else {
                D_8010C202_game_guys_magic_boxes++;
            }
        }
        if (D_8010C208_game_guys_magic_boxes != D_8010C9E1_game_guys_magic_boxes) {
            if (D_8010C9E1_game_guys_magic_boxes == 1) {
                HuAudFXPlay(1);
                D_8010C990_game_guys_magic_boxes.x = 140;
            } else if (D_8010C9E1_game_guys_magic_boxes == 0) {
                HuAudFXPlay(1);
                D_8010C990_game_guys_magic_boxes.x = 55;
            }
            D_8010C208_game_guys_magic_boxes = D_8010C9E1_game_guys_magic_boxes;
        }
        if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 0) {
            if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
                D_8010C1E0_game_guys_magic_boxes -= 0.05f;
            }
            if (D_8010C1E4_game_guys_magic_boxes < 1.1f) {
                D_8010C1E4_game_guys_magic_boxes += 0.05f;
            }
        } else {
            if (D_8010C1E0_game_guys_magic_boxes < 1.1f) {
                D_8010C1E0_game_guys_magic_boxes += 0.05f;
            }
            if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
                D_8010C1E4_game_guys_magic_boxes -= 0.05f;
            }
        }
        omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
                 D_8010C1E0_game_guys_magic_boxes);
        Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                          D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
        omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
                 D_8010C1E4_game_guys_magic_boxes);
        Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                          D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
        if (D_8010C1FE_game_guys_magic_boxes >= 30) {
            D_8010C200_game_guys_magic_boxes--;
            D_8010C1FE_game_guys_magic_boxes = 0;
            func_8003F578_main(D_8010C200_game_guys_magic_boxes);
        } else {
            D_8010C1FE_game_guys_magic_boxes++;
        }
        ok |= D_8010C200_game_guys_magic_boxes < 1;
        if (ok) {
            D_8010C204_game_guys_magic_boxes = 0.0f;
            D_8010C1FC_game_guys_magic_boxes = 2;
        }
        break;
    case 2:
        if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 1) {
            D_8010C9E2_game_guys_magic_boxes = 1;
        } else {
            D_8010C9E2_game_guys_magic_boxes = 0;
        }
        HuAudFXPlay(3);
        D_800D6A58_main = 1;
        func_8003F5C0_main();
        D_8010C9E8_game_guys_magic_boxes = 9;
        D_8010C1FC_game_guys_magic_boxes = 0;
        D_8010C1FE_game_guys_magic_boxes = 0;
        D_8010C200_game_guys_magic_boxes = 10;
        D_8010C204_game_guys_magic_boxes = 0.0f;
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107B64_game_guys_magic_boxes);
#endif

/* The face shrinks away and the lids settle; "Let's open it!" */
void func_80108294_game_guys_magic_boxes(void) {
    if (D_8010C20C_game_guys_magic_boxes > 0.0f) {
        D_8010C20C_game_guys_magic_boxes -= 0.25f;
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
    } else {
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 0);
    }
    D_8010C990_game_guys_magic_boxes.sx = D_8010C990_game_guys_magic_boxes.sy = D_8010C20C_game_guys_magic_boxes;
    if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
        D_8010C1E0_game_guys_magic_boxes -= 0.05f;
    }
    if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
        D_8010C1E4_game_guys_magic_boxes -= 0.05f;
    }
    omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
             D_8010C1E0_game_guys_magic_boxes);
    Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                      D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
    omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
             D_8010C1E4_game_guys_magic_boxes);
    Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                      D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
    if (D_8010C20A_game_guys_magic_boxes == 0) {
        func_8004A670_main(120);
        GMesCreate(0x14);
        D_8010C20A_game_guys_magic_boxes = 1;
    } else if (D_8010C20A_game_guys_magic_boxes == 1) {
        if (GMesStatGet() == 0) {
            D_8010C9E8_game_guys_magic_boxes = 10;
            D_8010C20C_game_guys_magic_boxes = 1.0f;
            D_8010C20A_game_guys_magic_boxes = 0;
            D_8010C990_game_guys_magic_boxes.x = 55;
        }
    }
}

/* A spot lights the chosen box */
void func_80108498_game_guys_magic_boxes(void) {
    s32 i;
    u8* p;

    switch (D_8010C210_game_guys_magic_boxes) {
    case 0:
        func_8004A5C4_main(0x49);
        GMesClose();
        D_8010C9D9_game_guys_magic_boxes = 1;
        D_8010C212_game_guys_magic_boxes = 0;
        if (D_8010C9E1_game_guys_magic_boxes == 1) {
            D_8010C214_game_guys_magic_boxes = 203;
        } else {
            D_8010C214_game_guys_magic_boxes = 117;
        }
        D_8010C216_game_guys_magic_boxes = 120;
        p = D_8010C9F4_game_guys_magic_boxes[0];
        for (i = 0; i < 0x9600; i++) {
            *p = 0;
            p++;
        }
        D_8010CA00_game_guys_magic_boxes = 0;
        func_8010A1B0_game_guys_magic_boxes(D_8010C214_game_guys_magic_boxes, D_8010C216_game_guys_magic_boxes, 50);
        D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 = D_8010C9F4_game_guys_magic_boxes[0];
        D_8010C210_game_guys_magic_boxes = 1;
        break;
    case 1:
        if (D_8010C212_game_guys_magic_boxes >= 0x80) {
            D_8010C210_game_guys_magic_boxes = 2;
        } else {
            D_8010C212_game_guys_magic_boxes += 8;
        }
        func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C212_game_guys_magic_boxes);
        break;
    case 2:
        D_8010C210_game_guys_magic_boxes = 0;
        D_8010C214_game_guys_magic_boxes = 0;
        D_8010C216_game_guys_magic_boxes = 0;
        D_8010C9E8_game_guys_magic_boxes = 11;
        break;
    }
}

/* Open both boxes */
void func_8010861C_game_guys_magic_boxes(void) {
    switch (D_8010C218_game_guys_magic_boxes) {
    case 0:
        if (D_8010C21A_game_guys_magic_boxes >= 30) {
            func_8004A7C4_main(1);
            D_8010C21A_game_guys_magic_boxes = 0;
            D_8010C218_game_guys_magic_boxes = 1;
        } else {
            D_8010C21A_game_guys_magic_boxes++;
        }
        break;
    case 1:
        HuAudFXPlay(0x52F);
        func_8001C8A8_main(D_8010C76C_game_guys_magic_boxes->model[0], 1);
        func_8001C8A8_main(D_8010C764_game_guys_magic_boxes->model[0], 1);
        func_8001C92C_main(D_8010C768_game_guys_magic_boxes->model[0], 1.0f);
        func_8001C92C_main(D_8010C770_game_guys_magic_boxes->model[0], 1.0f);
        D_8010C9C8_game_guys_magic_boxes = 2;
        D_8010C9C9_game_guys_magic_boxes = 2;
        D_8010C218_game_guys_magic_boxes = 2;
        if (D_8010C9E2_game_guys_magic_boxes == 1) {
            if (D_8010C9E7_game_guys_magic_boxes == 2) {
                omVibrate(D_8010C750_game_guys_magic_boxes.player, 30, 0, 30);
            } else {
                omVibrate(D_8010C750_game_guys_magic_boxes.player, 10, 0, 10);
            }
        } else {
            omVibrate(D_8010C750_game_guys_magic_boxes.player, 2, 2, 20);
        }
        break;
    case 2:
        if (D_8010C21A_game_guys_magic_boxes >= 45) {
            if (D_8010C9E2_game_guys_magic_boxes == 0) {
                HuAudFXPlay(0x534);
            } else {
                HuAudFXPlay(0x535);
            }
            D_8010C21A_game_guys_magic_boxes = 0;
            D_8010C218_game_guys_magic_boxes = 3;
        } else {
            D_8010C21A_game_guys_magic_boxes++;
        }
        if (D_8010C21A_game_guys_magic_boxes == 23) {
            if (D_8010C9E2_game_guys_magic_boxes == 1) {
                D_8010C9C8_game_guys_magic_boxes = 4;
                D_8010C9C9_game_guys_magic_boxes = 4;
            } else {
                D_8010C9C8_game_guys_magic_boxes = 3;
                D_8010C9C9_game_guys_magic_boxes = 3;
            }
        }
        if (D_8010C21A_game_guys_magic_boxes == 25) {
            if (D_8010C9E2_game_guys_magic_boxes == 1) {
                HuAudFXPlay(0x531);
            } else {
                HuAudFXPlay(0x530);
            }
        }
        break;
    case 3:
        if (D_8010C9E2_game_guys_magic_boxes == 1 && D_8010C9E7_game_guys_magic_boxes != 2) {
            func_8004A5C4_main(0x70);
            D_8010C9E8_game_guys_magic_boxes = 12;
            D_8010C218_game_guys_magic_boxes = 0;
            D_8010C21A_game_guys_magic_boxes = 0;
        } else if (D_8010C9E2_game_guys_magic_boxes == 0 || D_8010C9E7_game_guys_magic_boxes == 2) {
            D_8010C9E8_game_guys_magic_boxes = 15;
        }
        break;
    }
}

/* "Go on to the next round?" */
void func_80108914_game_guys_magic_boxes(void) {
    s16 winId;
    s16 done = 0;
    s16 r = 0;

    HuPrcSleep(50);
    func_8004A650_main(10);
    D_8010CA0E_game_guys_magic_boxes = 0;
    winId = func_8010A4EC_game_guys_magic_boxes(0x82, 0xA0, 0xC);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2C05, -1, -1);
    func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad, D_8010C750_game_guys_magic_boxes.cpu);
    func_8005B43C_main(winId, 0x2C06, -1, -1);
    if (D_8010CA04_game_guys_magic_boxes != D_8010C9E7_game_guys_magic_boxes) {
        D_8010C9DA_game_guys_magic_boxes = 0;
    } else {
        D_8010C9DA_game_guys_magic_boxes = 1;
    }
    while (done == 0) {
        r = func_8010A6AC_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad,
                                                D_8010C750_game_guys_magic_boxes.cpu, D_8010C9DA_game_guys_magic_boxes, 1);
        switch (r) {
        case 0:
            func_8005B43C_main(winId, 0x2C07, -1, -1);
            func_8010A560_game_guys_magic_boxes(winId, D_8010C750_game_guys_magic_boxes.pad,
                                                D_8010C750_game_guys_magic_boxes.cpu);
        case 1:
            done = 1;
            break;
        }
        HuPrcVSleep();
    }
    func_8010A878_game_guys_magic_boxes(winId);
    if (r == 0) {
        D_8010CA0E_game_guys_magic_boxes = 1;
    } else if (r == 1) {
        D_8010CA0E_game_guys_magic_boxes = 2;
    }
    while (1) {
        HuPrcVSleep();
    }
}

/* Next round: double the coins, fade the spot out */
void func_80108AF8_game_guys_magic_boxes(void) {
    switch (D_8010C21C_game_guys_magic_boxes) {
    case 0:
        D_8010C9E7_game_guys_magic_boxes++;
        D_8010C750_game_guys_magic_boxes.coins *= 2;
        D_8010C9E1_game_guys_magic_boxes = 0;
        D_8010C21C_game_guys_magic_boxes++;
        break;
    case 1:
        if (D_8010C21E_game_guys_magic_boxes == 0) {
            D_8010C21C_game_guys_magic_boxes = 2;
        } else {
            D_8010C21E_game_guys_magic_boxes -= 8;
        }
        func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C21E_game_guys_magic_boxes);
        break;
    case 2:
        D_8010C9D9_game_guys_magic_boxes = 0;
        D_8010C9E8_game_guys_magic_boxes = 3;
        D_8010C21C_game_guys_magic_boxes = 0;
        D_8010C21E_game_guys_magic_boxes = 0x80;
        break;
    }
}


INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C514_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C520_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C530_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C538_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C544_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C550_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C55C_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C568_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C574_game_guys_magic_boxes);

#ifdef NON_MATCHING
/* register allocation only: the message id is sign-extended in v0 before the GMesMaxTimeGet call, here in a0 */
/* The result: "You won N coins!" or the loss message, with its jingle */
void func_80108C04_game_guys_magic_boxes(void) {
    s16 mes;

    if (D_8010C222_game_guys_magic_boxes == -1) {
        if (D_8010C220_game_guys_magic_boxes++ >= 15) {
            D_8010C220_game_guys_magic_boxes = 0;
            D_8010C222_game_guys_magic_boxes = 0;
        }
        if (D_8010C9E2_game_guys_magic_boxes == 0) {
            D_8010C222_game_guys_magic_boxes = 0;
            D_8010C220_game_guys_magic_boxes = 0;
        }
    } else if (D_8010C222_game_guys_magic_boxes == 0) {
        if (D_8010C9E2_game_guys_magic_boxes == 1) {
            HuAudSeqPlay(0x73);
            mes = GMesCreate(0x16, D_8010C750_game_guys_magic_boxes.chr);
        } else {
            HuAudSeqPlay(0x71);
            sprintf(D_8010C630_game_guys_magic_boxes, D_8010C574_game_guys_magic_boxes,
                    D_8010C228_game_guys_magic_boxes[D_8010C750_game_guys_magic_boxes.chr]);
            mes = GMesCreate(0x19, D_8010C630_game_guys_magic_boxes, 160, 120, 1.0, 1.0, 1);
        }
        GMesMaxTimeGet(D_8010C224_game_guys_magic_boxes = mes, 120);
        D_8010C222_game_guys_magic_boxes = 1;
    } else if (D_8010C222_game_guys_magic_boxes == 1) {
        if (D_8010C220_game_guys_magic_boxes++ == 135) {
            D_8010C9E8_game_guys_magic_boxes = 16;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108C04_game_guys_magic_boxes);
#endif

/* The screen sprites: the blinking lights, the coins and the rounds */
void func_80108D88_game_guys_magic_boxes(omObjData* obj) {
    s32 x = 0;
    u8 i;
    s16 hundreds;
    s16 tens;

    if (D_8010C248_game_guys_magic_boxes >= 5) {
        D_8010C24A_game_guys_magic_boxes++;
        if (D_8010C24A_game_guys_magic_boxes >= 3) {
            D_8010C24A_game_guys_magic_boxes = 0;
        }
        switch (D_8010C24A_game_guys_magic_boxes) {
        case 0:
            func_80109D3C_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0);
            func_80109D3C_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0);
            break;
        case 1:
            func_80109D3C_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 1);
            func_80109D3C_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0);
            break;
        case 2:
            func_80109D3C_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0);
            func_80109D3C_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 1);
            break;
        }
        D_8010C248_game_guys_magic_boxes = 0;
    }
    if (D_8010C9D9_game_guys_magic_boxes != 1 || D_8010C24A_game_guys_magic_boxes != 0) {
        D_8010C248_game_guys_magic_boxes++;
    }
    if (D_8010C750_game_guys_magic_boxes.coins >= 999) {
        D_8010C750_game_guys_magic_boxes.coins = 999;
    } else if (D_8010C750_game_guys_magic_boxes.coins <= 0) {
        D_8010C750_game_guys_magic_boxes.coins = 0;
    }
    hundreds = D_8010C750_game_guys_magic_boxes.coins / 100;
    if (hundreds == 0) {
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[2], 0);
    } else {
        func_8000BD50_main(D_8010C938_game_guys_magic_boxes[2].id, hundreds);
        D_8010C938_game_guys_magic_boxes[2].x = x + 48;
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[2], 1);
        x += 12;
    }
    tens = (D_8010C750_game_guys_magic_boxes.coins % 100) / 10;
    if (tens == 0 && (s16)(D_8010C750_game_guys_magic_boxes.coins / 100) == 0) {
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[1], 0);
    } else {
        func_8000BD50_main(D_8010C938_game_guys_magic_boxes[1].id, tens);
        D_8010C938_game_guys_magic_boxes[1].x = x + 48;
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[1], 1);
        x += 12;
    }
    func_8000BD50_main(D_8010C938_game_guys_magic_boxes[0].id, D_8010C750_game_guys_magic_boxes.coins % 10);
    D_8010C938_game_guys_magic_boxes[0].x = x + 48;
    func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[0], 1);
    for (i = 0; i <= D_8010C9E7_game_guys_magic_boxes; i++) {
        func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i].off, 1);
    }
}

/* The curtain opens (1) or closes (2) */
void func_801090F0_game_guys_magic_boxes(omObjData* obj) {
    if (D_8010C9D8_game_guys_magic_boxes == 1) {
        if (D_8010C9D0_game_guys_magic_boxes < -200.0f) {
            D_8010C9D4_game_guys_magic_boxes -= 12.0f;
            D_8010C9D0_game_guys_magic_boxes += 12.0f;
            D_8010C24C_game_guys_magic_boxes += 0.2f;
        } else {
            D_8010C9D8_game_guys_magic_boxes = 0;
            D_8010C9D0_game_guys_magic_boxes = -200.0f;
            D_8010C9D4_game_guys_magic_boxes = 200.0f;
            D_8010C24C_game_guys_magic_boxes = 1.0f;
        }
    } else if (D_8010C9D8_game_guys_magic_boxes == 2) {
        if (D_8010C24C_game_guys_magic_boxes > 0.0f) {
            D_8010C9D4_game_guys_magic_boxes += 9.0f;
            D_8010C9D0_game_guys_magic_boxes -= 9.0f;
            D_8010C24C_game_guys_magic_boxes -= 0.03f;
        } else {
            D_8010C9D8_game_guys_magic_boxes = 0;
            D_8010C9D0_game_guys_magic_boxes = -260.0f;
            D_8010C9D4_game_guys_magic_boxes = 260.0f;
            D_8010C24C_game_guys_magic_boxes = 0.0f;
        }
    }
    omSetTra(obj, D_8010C9D0_game_guys_magic_boxes, -440.0f, -1000.0f);
    omSetSca(obj, D_8010C24C_game_guys_magic_boxes, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[1], D_8010C9D4_game_guys_magic_boxes, -440.0f, -1000.0f);
    Hu3DModelScaleSet(obj->model[1], D_8010C24C_game_guys_magic_boxes, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[2], D_8010C9D0_game_guys_magic_boxes, -440.0f, -999.0f);
    Hu3DModelScaleSet(obj->model[2], D_8010C24C_game_guys_magic_boxes, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[3], D_8010C9D4_game_guys_magic_boxes, -440.0f, -999.0f);
    Hu3DModelScaleSet(obj->model[3], D_8010C24C_game_guys_magic_boxes, 1.0f, 1.0f);
}

/* Game Guy's motion */
void func_8010935C_game_guys_magic_boxes(omObjData* obj) {
    if (D_8010C250_game_guys_magic_boxes != D_8010C9CA_game_guys_magic_boxes) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010C9CA_game_guys_magic_boxes]].unk02, 0, 4, 2);
        D_8010C250_game_guys_magic_boxes = D_8010C9CA_game_guys_magic_boxes;
    }
    D_8010C9CC_game_guys_magic_boxes = HmfModelData[obj->model[0]].unk40 / 2.0f;
}

/* The left box: its motion (3 plays once, the others loop), place and shadow */
void func_8010942C_game_guys_magic_boxes(omObjData* obj) {
    if (D_8010C251_game_guys_magic_boxes != D_8010C9C8_game_guys_magic_boxes) {
        if (D_8010C9C8_game_guys_magic_boxes != 3) {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010C9C8_game_guys_magic_boxes]].unk02, 0, 10,
                               2);
        } else {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010C9C8_game_guys_magic_boxes]].unk02, 0, 10,
                               0);
        }
        D_8010C251_game_guys_magic_boxes = D_8010C9C8_game_guys_magic_boxes;
    }
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    if (D_8010CA06_game_guys_magic_boxes == 1 && D_8010C252_game_guys_magic_boxes < 2.0) {
        D_8010C252_game_guys_magic_boxes += 0.01f; /* a u8: 1 + 0.01 truncates back to 1 */
    }
    Hu3DModelScaleSet(obj->model[1], D_8010C252_game_guys_magic_boxes, 1.0f, D_8010C252_game_guys_magic_boxes);
}

void func_80109600_game_guys_magic_boxes(omObjData* obj) {
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    Hu3DModelPosSet(obj->model[1], D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
                    D_8010C9B0_game_guys_magic_boxes[0].z);
}

/* The right box (4 plays once) */
void func_80109658_game_guys_magic_boxes(omObjData* obj) {
    if (D_8010C253_game_guys_magic_boxes != D_8010C9C9_game_guys_magic_boxes) {
        if (D_8010C9C9_game_guys_magic_boxes != 4) {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010C9C9_game_guys_magic_boxes]].unk02, 0, 10,
                               2);
        } else {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010C9C9_game_guys_magic_boxes]].unk02, 0, 10,
                               0);
        }
        D_8010C253_game_guys_magic_boxes = D_8010C9C9_game_guys_magic_boxes;
    }
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    if (D_8010CA06_game_guys_magic_boxes == 1 && D_8010C254_game_guys_magic_boxes < 2.0) {
        D_8010C254_game_guys_magic_boxes += 0.01f; /* a u8: 1 + 0.01 truncates back to 1 */
    }
    Hu3DModelScaleSet(obj->model[1], D_8010C254_game_guys_magic_boxes, 1.0f, D_8010C254_game_guys_magic_boxes);
}

void func_8010982C_game_guys_magic_boxes(omObjData* obj) {
    omSetTra(obj, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    Hu3DModelPosSet(obj->model[1], D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
                    D_8010C9B0_game_guys_magic_boxes[1].z);
}

/* The end: hand the coins back, fade out */
void func_80109884_game_guys_magic_boxes(omObjData* obj) {
    s16 bonus[3] = { 2, 4, 8 };

    GwPlayer[D_8010C750_game_guys_magic_boxes.player].gameCoin = D_8010CA08_game_guys_magic_boxes;
    if (D_8010C9E2_game_guys_magic_boxes == 1) {
        GwPlayer[D_8010C750_game_guys_magic_boxes.player].bonusCoin = bonus[D_8010C9E7_game_guys_magic_boxes];
    } else {
        GwPlayer[D_8010C750_game_guys_magic_boxes.player].bonusCoin = 0;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80109984_game_guys_magic_boxes;
}

void func_80109984_game_guys_magic_boxes(omObjData* obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8010B8B4_game_guys_magic_boxes();
        func_8010A4CC_game_guys_magic_boxes();
        GMesClose();
        func_8005F524_main();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_801099E4_game_guys_magic_boxes(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80109884_game_guys_magic_boxes;
    }
}

void func_80109A0C_game_guys_magic_boxes(void) {
    u8 cam;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
}

void func_80109AD8_game_guys_magic_boxes(GgmCamera* cam, f32 fov, f32 zoom, f32 rx, f32 ry, f32 rz, f32 cx, f32 cy,
                                         f32 cz) {
    cam->fov = fov;
    cam->zoom = zoom;
    cam->rot.x = rx;
    cam->rot.y = ry;
    cam->rot.z = rz;
    cam->center.x = cx;
    cam->center.y = cy;
    cam->center.z = cz;
}

void func_80109B10_game_guys_magic_boxes(GgmCamera* cam) {
    if (cam->rot.x >= 360.0f) {
        cam->rot.x -= 360.0f;
    } else if (cam->rot.x < 0.0f) {
        cam->rot.x += 360.0f;
    }
    if (cam->rot.y >= 360.0f) {
        cam->rot.y -= 360.0f;
    } else if (cam->rot.y < 0.0f) {
        cam->rot.y += 360.0f;
    }
    if (cam->rot.z >= 360.0f) {
        cam->rot.z -= 360.0f;
    } else if (cam->rot.z < 0.0f) {
        cam->rot.z += 360.0f;
    }
    Hu3DCamSetPerspective(0, cam->fov, 80.0f, 8000.0f);
    CZoom = cam->zoom;
    CRot.x = cam->rot.x;
    CRot.y = cam->rot.y;
    CRot.z = cam->rot.z;
    Center.x = cam->center.x;
    Center.y = cam->center.y;
    Center.z = cam->center.z;
}

void func_80109C98_game_guys_magic_boxes(GgmSprite* sp, s32 file, s32 attr, s32 arg3) {
    sp->id = InitEspriteSlot(func_8000B838_main(file), 0, attr);
    func_8000BC48_main(sp->id, arg3);
}

void func_80109CFC_game_guys_magic_boxes(GgmSprite* sp, s16 prio, s16 attr, s16 x, s16 y, s16 w, s16 h, f32 rot,
                                         f32 sx, f32 sy) {
    sp->prio = prio;
    sp->attr = attr;
    sp->x = x;
    sp->y = y;
    sp->w = w;
    sp->h = h;
    sp->rot = rot;
    sp->sx = sx;
    sp->sy = sy;
}

void func_80109D3C_game_guys_magic_boxes(GgmSprite* sp, u8 show) {
    func_8000BCC8_main(sp->id, sp->prio);
    func_8000BBFC_main(sp->id, sp->attr);
    func_8000BBD4_main(sp->id, sp->x + sp->w / 2, sp->y + sp->h / 2);
    func_8000BF00_main(sp->id, sp->rot);
    func_8000BE5C_main(sp->id, sp->sx, sp->sy);
    if (show == 1) {
        func_8000BB54_main(sp->id);
    } else {
        func_8000BB94_main(sp->id);
    }
}

/* The player in group 0 plays */
void func_80109E1C_game_guys_magic_boxes(void) {
    u8 i;
    u8 n;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
    case 0:
        n = 0;
        break;
    case 1:
        n = 1;
        break;
    case 2:
        n = 2;
        break;
    case 3:
        n = 3;
        break;
    default:
        n = 0;
        break;
    }
    D_8010C750_game_guys_magic_boxes.player = n;
    D_8010C750_game_guys_magic_boxes.pad = GwPlayer[n].pad;
    D_8010C750_game_guys_magic_boxes.chr = GwPlayer[n].chr;
    if (GwPlayer[n].stat & 1) {
        D_8010C750_game_guys_magic_boxes.cpu = 1;
        D_8010C750_game_guys_magic_boxes.difficulty = GwPlayer[n].cpu_difficulty;
        D_8010CA14_game_guys_magic_boxes = GwCommon.unkA0;
        if (D_8010CA14_game_guys_magic_boxes <= 0) {
            D_8010CA14_game_guys_magic_boxes = 0;
        } else if (D_8010CA14_game_guys_magic_boxes >= 2) {
            D_8010CA14_game_guys_magic_boxes = 2;
        }
    } else {
        D_8010C750_game_guys_magic_boxes.cpu = 0;
        D_8010C750_game_guys_magic_boxes.difficulty = 0;
    }
    D_8010CA08_game_guys_magic_boxes = D_8010C750_game_guys_magic_boxes.coins = GwPlayer[n].gameCoin;
    if (D_8010C750_game_guys_magic_boxes.coins >= 999) {
        D_8010C750_game_guys_magic_boxes.coins = 999;
    } else if (D_8010C750_game_guys_magic_boxes.coins <= 0) {
        D_8010C750_game_guys_magic_boxes.coins = 0;
    }
    if (D_8010CA08_game_guys_magic_boxes >= 999) {
        D_8010CA08_game_guys_magic_boxes = 999;
    } else if (D_8010CA08_game_guys_magic_boxes <= 0) {
        D_8010CA08_game_guys_magic_boxes = 0;
    }
}

/* The light spots' sprite: a 320x240 4-bit image cycled through three buffers */
void func_8010A000_game_guys_magic_boxes(void) {
    s16 data = func_8000B838_main(0x650005);
    HuSprite* spr;
    u16* pal;
    s32 i;
    s32 j;
    u8* p;

    D_8010C9F0_game_guys_magic_boxes = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010C9F0_game_guys_magic_boxes, 0, data, 0);
    HuSprAttrReset(D_8010C9F0_game_guys_magic_boxes, 0, 0xFFFF);
    HuSprAttrSet(D_8010C9F0_game_guys_magic_boxes, 0, 0x1000);
    func_80054904_main(D_8010C9F0_game_guys_magic_boxes, 0, 160, 120);
    func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, 0);
    HuSprPriSet(D_8010C9F0_game_guys_magic_boxes, 0, 10);
    D_8010C9EC_game_guys_magic_boxes = spr = HuSprGet(D_8010C9F0_game_guys_magic_boxes, 0);
    D_8010C9F4_game_guys_magic_boxes[0] = spr->unk_84->unk00->unk00;
    pal = spr->unk_84->unk0C;
    D_8010C9F4_game_guys_magic_boxes[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010C9F4_game_guys_magic_boxes[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 1;
    pal[1] = 0x3F;
    pal[2] = 0x7C1;
    pal[3] = 0x7FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;
    for (i = 0; i < 3; i++) {
        p = D_8010C9F4_game_guys_magic_boxes[i];
        for (j = 0; j < 0x9600; j++) {
            *p = 0;
            p++;
        }
    }
    D_8010CA00_game_guys_magic_boxes = 0;
}

/* Draw a spot of radius r at (x, y) into this frame's buffer (colour 7) */
void func_8010A1B0_game_guys_magic_boxes(s16 x, s16 y, s16 r) {
    s32 rr = r * r;
    s16 xx;
    s16 yy;
    s32 dy;
    u8* p;

    for (yy = y - r; yy < y + r; yy++) {
        p = D_8010C9F4_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes] + (x - r) / 2 + yy * 160;
        dy = (yy - y) * (yy - y);
        for (xx = x - r; xx < x + r; xx++) {
            if (xx >= 0 && xx < 320 && yy >= 0 && yy < 240 && (xx - x) * (xx - x) + (s16)dy < rr) {
                if (xx & 1) {
                    *p |= 7;
                } else {
                    *p |= 0x70;
                }
            }
            p += xx & 1;
        }
    }
}

/* Clear the square around a spot in this frame's buffer */
void func_8010A388_game_guys_magic_boxes(s16 x, s16 y, s16 r) {
    s16 xx;
    s16 yy;
    u8* p;

    for (yy = y - r; yy < y + r; yy++) {
        p = D_8010C9F4_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes] + (x - r) / 2 + yy * 160;
        for (xx = x - r; xx < x + r + 1; xx += 2) {
            if (xx >= 0 && xx < 320 && yy >= 0 && yy < 240) {
                *p = 0;
            }
            p++;
        }
    }
}

/* Give the sprite its own image back */
void func_8010A4CC_game_guys_magic_boxes(void) {
    D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 = D_8010C9F4_game_guys_magic_boxes[0];
}

s16 func_8010A4EC_game_guys_magic_boxes(s16 x, s16 y, s16 mes) {
    s16 winId = func_80060880_main(x, y, mes);

    func_8005B63C_main(winId, 2, 2);
    func_80061100_main(winId, 1);
    func_8005BDFC_main(winId, 0);
    func_8005D294_main(winId);
    return winId;
}

/* Wait for the window's message to end: a human presses A, the CPU's key is pressed for it */
void func_8010A560_game_guys_magic_boxes(s16 winId, s16 pad, s16 cpu) {
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
                                   (&D_8010C1E8_game_guys_magic_boxes[D_8010CA14_game_guys_magic_boxes])->delay);
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

/* A yes/no choice in the window: a human answers with the pad, the CPU moves down `count` times */
s16 func_8010A6AC_game_guys_magic_boxes(s16 winId, s16 pad, s16 cpu, s16 count, u16 cancel) {
    s16 keys[4] = { 0, 0, 0, 0 };
    s16 ports[4] = { 1, 2, 4, 8 };
    s16 i;

    switch (cpu) {
    case 0:
        keys[pad] = -1;
        func_8005B63C_main(winId, 2, 0);
        func_8005FE54_main(winId, ports[pad]);
        func_8005F744_main(keys[0], keys[1], keys[2], keys[3]);
        break;
    case 1:
        for (i = 0; i < count; i++) {
            func_8005F698_main(0x400, 0x400, 0x400, 0x400,
                               (&D_8010C1E8_game_guys_magic_boxes[D_8010CA14_game_guys_magic_boxes])->delay);
        }
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000,
                           D_8010C1E8_game_guys_magic_boxes[D_8010CA14_game_guys_magic_boxes].delay);
        break;
    }
    if (cancel == 0) {
        return func_8005E1D8_main(winId, 0, 1);
    } else {
        return func_8005E1D8_main(winId, 1, 1);
    }
}

void func_8010A878_game_guys_magic_boxes(s16 winId) {
    func_8005D294_main(winId);
    func_80060EA8_main(winId, 1);
    func_800610E0_main(winId);
}
