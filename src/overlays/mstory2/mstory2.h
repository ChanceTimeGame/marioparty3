#ifndef MSTORY2_H
#define MSTORY2_H

#include "common.h"

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). Same as mstory1's. */
typedef struct ObPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} ObPathSeg; /* size = 0x8 */

typedef struct ObPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ ObPathSeg *segs;
} ObPath; /* size = 0x10 */

typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; /* size = 0xC */

/* a chapter 2 actor: its object and the hook its process runs every frame (scene steps hand the
   next step to other actors; the idle hooks do nothing). As mstory1's MsActor, 0x14 bytes here. */
typedef struct StoryActor2 {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *obj);
    /* 0x08 */ s32 flags; /* scene progress other actors wait on */
    /* 0x0C */ s32 sfxOn; /* 1: walking, sfxId replays when the walk motion restarts */
    /* 0x10 */ s32 sfxId; /* footstep sound */
} StoryActor2; /* size = 0x14 */

typedef struct StoryMotions {
    s32 v[8][3]; /* per character: three motion files of directory 0x1D */
} StoryMotions;

typedef struct StoryTargets {
    Vec v[6];
} StoryTargets;

typedef struct StoryRot4 {
    Vec v[4];
} StoryRot4;

typedef struct StoryPads {
    s16 v[4];
} StoryPads;

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_800E989C_minigame(void);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
#include "mallocblock.h"

extern Vec D_8011B920_mstory2; /* camera position */
extern Vec D_8011B92C_mstory2; /* camera target */
extern Vec D_8011B938_mstory2; /* camera up */
extern s16 D_8011B944_mstory2; /* 1: the scene was seen before, A skips it */
extern s16 D_8011B946_mstory2; /* main object state */
extern s16 D_8011B948_mstory2; /* 1: leave to the minigame */
extern s32 D_8011B94C_mstory2;
extern void (*const D_8011BDE0_mstory2[5])(void);
extern const s32 D_8011BDF4_mstory2[5];
extern const StoryPads D_8011BE1C_mstory2;
extern const StoryPads D_8011BE24_mstory2;
extern const s32 D_8011BE2C_mstory2[7]; /* board icon sprites */
extern const s16 D_8011BE48_mstory2[7][2]; /* board icon positions */
extern s16 D_8011C640_mstory2; /* story step (GwPlayer[0].coin, at most 4) */
extern s16 D_8011C642_mstory2; /* the controller that drives the story messages */
extern s16 D_8011C644_mstory2; /* message window */
extern u16 D_8011C646_mstory2; /* background sprite */
extern s16 D_8011C648_mstory2; /* background model */
extern s16 D_8011C650_mstory2[8]; /* chapter map: [0] the map, [1..7] the board icons */
extern s16 D_8011C660_mstory2[8]; /* the stars around this chapter's icon */
extern s16 D_8011C670_mstory2; /* frame sprite */
extern s32 D_8011C674_mstory2; /* the chapter the map shows */
void func_80106D50_mstory2(void);
extern const StoryRot4 D_8011BEB0_mstory2;
extern StoryActor2 D_8011C680_mstory2[6];
extern s16 D_8011C75A_mstory2; /* shadow model */
extern s16 D_8011C75C_mstory2; /* the story character (GwStory.unk1) */
extern s16 D_8011C75E_mstory2; /* the partner character */
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80105FBC_mstory2(void);
void func_801060A4_mstory2(void);
void func_801060D4_mstory2(void);
void func_801060F8_mstory2(s32 mess);
void func_8010614C_mstory2(s32 mess);
void func_801072AC_mstory2(s16 model);
void func_801076DC_mstory2(omObjData *a, omObjData *b);
void func_801088A4_mstory2(void);
void func_8010889C_mstory2(omObjData *obj);
void func_80108A3C_mstory2(void);
void func_80108AB0_mstory2(omObjData *unused);
void func_80108C40_mstory2(omObjData *obj);
void func_80109D04_mstory2(void);
void func_8010AC1C_mstory2(void);
void func_8010B7B8_mstory2(void);
void func_8010C038_mstory2(void);
void func_8010C1E4_mstory2(void);
void func_8010C398_mstory2(void);
void func_8010A5FC_mstory2(omObjData *obj);
void func_80106D58_mstory2(s16 model, s16 anim, s16 frame);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
extern s16 D_8011C74A_mstory2[3]; /* actor 0's texture animations */
extern s16 D_8011C750_mstory2;
extern const StoryTargets D_8011BEE0_mstory2;
extern Vec D_8011B950_mstory2[]; /* paths: Vec lists ended by { 9999, 9999, 9999 } */
extern Vec D_8011B980_mstory2[];
extern Vec D_8011B9C8_mstory2;
extern Vec D_8011B9D4_mstory2;
extern Vec D_8011B9E0_mstory2[5];
extern Vec D_8011BA1C_mstory2;
extern Vec D_8011BA28_mstory2;
extern Vec D_8011BA34_mstory2;
extern s16 D_8011C740_mstory2[3]; /* actor 2's texture animations */
extern s16 D_8011C746_mstory2;
extern s16 D_8011C748_mstory2; /* 1 while actor 3 turns round */
void func_800138EC_main(s16 model, u16 mask, u16 flags);
ObPath *func_80107B90_mstory2(Vec *points, s16 flags);
void func_80107E94_mstory2(ObPath *path, f32 t, Vec *out);
void func_8010873C_mstory2(ObPath *path);
void func_80107824_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106E2C_mstory2(omObjData *obj, Vec *to, s32 frames);
void func_80105EA4_mstory2(void);
void func_8010622C_mstory2(void);
void func_8010A298_mstory2(omObjData *obj);
void func_8010A3B4_mstory2(omObjData *obj);
void func_8010A784_mstory2(omObjData *obj);
void func_8010A9F0_mstory2(omObjData *obj);
void func_8010B110_mstory2(omObjData *obj);
void func_8010B200_mstory2(omObjData *obj);
void func_8010B46C_mstory2(omObjData *obj);
void func_8010B688_mstory2(omObjData *obj);
void func_8010B738_mstory2(omObjData *obj);
void func_8010BACC_mstory2(omObjData *obj);
void func_8010BD04_mstory2(omObjData *obj);
void func_8010BDC4_mstory2(omObjData *obj);
void func_8010C018_mstory2(omObjData *obj);
void func_8010C328_mstory2(omObjData *obj);
void func_8010C348_mstory2(omObjData *obj);
extern const StoryMotions D_8011BF28_mstory2;
extern char *D_8011BA40_mstory2[8]; /* per character: its model's texture name */
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_8010A290_mstory2(void);
extern s16 D_8011C756_mstory2;
extern s16 D_8011C758_mstory2;
extern s16 D_8011CA80_mstory2[4]; /* play order: player per slot */

void func_801059BC_mstory2(void);
void func_801059E4_mstory2(omObjData *obj);
void func_80105A64_mstory2(void);
void func_80105B44_mstory2(void);
void func_80105B60_mstory2(void);
void func_80105C1C_mstory2(void);
void func_80105DB4_mstory2(omObjData *obj);
void func_80105EC4_mstory2(omObjData *obj);
void func_80105F4C_mstory2(omObjData *obj);
void func_80105F94_mstory2(omObjData *obj);
void func_801063B0_mstory2(void);
void func_801064AC_mstory2(void);
void func_80106E48_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_801070D8_mstory2(omObjData *obj, Vec *to, s32 frames);
s32 func_801072F8_mstory2(s16 model);
void func_8010876C_mstory2(void);
void func_8010D0EC_mstory2(void);
void func_80111D7C_mstory2(void);
void func_80116A3C_mstory2(void);
void func_8011AAE0_mstory2(void);


void func_8010A61C_mstory2(omObjData *obj);
void func_8010B108_mstory2(void);
void func_8010BAC4_mstory2(void);
void func_8010BCE4_mstory2(omObjData *obj);
void func_8010BF7C_mstory2(omObjData *obj);
void func_8010C1DC_mstory2(void);
void func_8010C508_mstory2(void);
void func_8010D21C_mstory2(omObjData *obj);
ObPath *func_8010C510_mstory2(Vec *points, s16 flags);
void func_8010C814_mstory2(ObPath *path, f32 t, Vec *out);
void func_8010D0BC_mstory2(ObPath *path);
void func_8010D224_mstory2(void);
void func_8010D3BC_mstory2(void);
void func_8010D430_mstory2(omObjData *obj);
void func_8010D5C0_mstory2(omObjData *obj);
void func_8010E9E0_mstory2(void);
void func_8010EF6C_mstory2(void);
void func_8010F8F8_mstory2(void);
void func_801103E4_mstory2(void);
void func_80110C64_mstory2(void);
void func_80110E10_mstory2(void);
void func_80111024_mstory2(void);

extern char *D_8011BA60_mstory2[4]; /* .data: actor 1's animation names by model */
extern const Vec D_8011BE74_mstory2;
extern const Vec D_8011BE80_mstory2;
extern const Vec D_8011BE8C_mstory2;
extern const Vec D_8011BE98_mstory2;
extern const Vec D_8011BFF4_mstory2;
extern const Vec D_8011C000_mstory2;
extern const Vec D_8011C00C_mstory2;
extern const Vec D_8011C024_mstory2;
extern const Vec D_8011C030_mstory2;
extern const Vec D_8011C03C_mstory2;
extern const StoryRot4 D_8011C090_mstory2; /* actors 3 and 2's turns in func_8010D430_mstory2 */

extern Vec D_8011C704_mstory2; /* actor 1's start position */
extern Vec D_8011C710_mstory2; /* actor 2's */
extern Vec D_8011C71C_mstory2; /* actor 3's */
extern Vec D_8011C728_mstory2; /* actor 4's */
extern s16 D_8011C752_mstory2[3]; /* actor 1's slots */

void *HuMemAllocTag(s32 size, s16 tag);
void HuMemFree(void *data);
extern char *D_8011BB60_mstory2[8]; /* .data: scene B actor 0's animation names by character */
extern const StoryMotions D_8011C108_mstory2;
extern s16 D_8011C82A_mstory2[3]; /* scene B actor 0's texture animation slots */
extern s16 D_8011C830_mstory2; /* its texture animation */
void func_8010EF74_mstory2(omObjData *obj);
void func_8010F090_mstory2(omObjData *obj);
void func_8010F460_mstory2(omObjData *obj);
void func_8010F6CC_mstory2(omObjData *obj);
void func_8010FDEC_mstory2(omObjData *obj);
void func_8010FEDC_mstory2(omObjData *obj);
void func_80110148_mstory2(omObjData *obj);
void func_80110364_mstory2(omObjData *obj);
void func_801106F8_mstory2(omObjData *obj);
void func_80110930_mstory2(omObjData *obj);
void func_801109F0_mstory2(omObjData *obj);
void func_80110C44_mstory2(omObjData *obj);
void func_80110F54_mstory2(omObjData *obj);
void func_80110F74_mstory2(omObjData *obj);
void func_80110FC4_mstory2(omObjData *obj);
extern Vec D_8011BA70_mstory2[]; /* .data: actor 4's flight in */
extern Vec D_8011BAA0_mstory2[]; /* .data: its flight out (point 0 is where it hovered) */
extern Vec D_8011BAE8_mstory2; /* .data: rotations */
extern Vec D_8011BAF4_mstory2;
extern Vec D_8011BB00_mstory2;
extern Vec D_8011BB0C_mstory2[4];
extern Vec D_8011BB3C_mstory2;
extern Vec D_8011BB48_mstory2;
extern Vec D_8011BB54_mstory2;
extern const StoryTargets D_8011C0C0_mstory2; /* func_8010D5C0_mstory2's targets */
extern s16 D_8011C820_mstory2[3]; /* scene B actor 2's texture animation slots */
extern s16 D_8011C826_mstory2; /* its texture animation */
extern s16 D_8011C828_mstory2;
extern StoryActor2 D_8011C760_mstory2[6]; /* scene B's actors */
extern s16 D_8011C83A_mstory2; /* scene B's shadow model */
extern s16 D_8011C83C_mstory2; /* actor 0's character (the player's) */
extern s16 D_8011C83E_mstory2; /* actor 1's character */


void func_8010F2D8_mstory2(omObjData *obj);
extern s16 D_8011C832_mstory2[3]; /* actor 1's animations */
extern s16 D_8011C838_mstory2; /* actor 1's animation motion */
extern const Vec D_8011C1D4_mstory2;
extern const Vec D_8011C1E0_mstory2;
void func_80110BA8_mstory2(omObjData *obj);
extern Vec D_8011C7E4_mstory2; /* actor 1's position */
extern const Vec D_8011C054_mstory2;
extern char *D_8011BB80_mstory2[4];
void func_8010FDE4_mstory2(void);
extern const Vec D_8011C1EC_mstory2;
void func_8010F2F8_mstory2(omObjData *obj);
extern Vec D_8011C7F0_mstory2; /* actor 2's position */
extern const Vec D_8011C060_mstory2;
void func_801106F0_mstory2(void);
extern const Vec D_8011C204_mstory2;
extern const Vec D_8011C210_mstory2;
extern const Vec D_8011C21C_mstory2;
void func_80110910_mstory2(omObjData *obj);
extern Vec D_8011C7FC_mstory2; /* actor 3's position */
extern Vec D_8011C808_mstory2; /* actor 4's position */
extern const Vec D_8011C06C_mstory2;
extern const Vec D_8011C078_mstory2;
extern const Vec D_8011C228_mstory2;
void func_80110E08_mstory2(void);
void func_80111194_mstory2(void);

void func_801114A4_mstory2(ObPath *path, f32 t, Vec *out);

extern StoryActor2 D_8011C840_mstory2[]; /* the second scene's actors */
extern s16 D_8011C91A_mstory2; /* the second scene's shadow model */
extern s16 D_8011C91C_mstory2; /* the second scene's characters */
extern s16 D_8011C91E_mstory2;
extern const StoryRot4 D_8011C27C_mstory2;
void func_80111EB4_mstory2(void);
void func_8011204C_mstory2(void);
void func_801120C0_mstory2(omObjData *obj);
void func_80112250_mstory2(omObjData *obj);
void func_80113670_mstory2(void);
void func_80114588_mstory2(void);
void func_8011509C_mstory2(void);
void func_8011591C_mstory2(void);
void func_80115AC8_mstory2(void);
void func_80115CDC_mstory2(void);

extern const StoryTargets D_8011C2AC_mstory2;
extern Vec D_8011BB90_mstory2[]; /* actor 4's flight in (path points) */
extern Vec D_8011BBC0_mstory2[]; /* its flight out; [0] is where the flight in ended */
extern Vec D_8011BC08_mstory2;
extern Vec D_8011BC14_mstory2;
extern Vec D_8011BC20_mstory2;
extern Vec D_8011BC2C_mstory2[4];
extern Vec D_8011BC5C_mstory2;
extern Vec D_8011BC68_mstory2;
extern Vec D_8011BC74_mstory2;
extern s16 D_8011C900_mstory2[3]; /* actor 2's animations */
extern s16 D_8011C906_mstory2; /* actor 2's animation motion */
extern s16 D_8011C908_mstory2;
void func_80111EAC_mstory2(omObjData *obj);
void func_80113C04_mstory2(omObjData *obj);
void func_80113D20_mstory2(omObjData *obj);
void func_801140F0_mstory2(omObjData *obj);
void func_8011435C_mstory2(omObjData *obj);
void func_80114AA4_mstory2(omObjData *obj);
void func_80114B94_mstory2(omObjData *obj);
void func_80114E00_mstory2(omObjData *obj);
void func_8011501C_mstory2(omObjData *obj);
void func_801153B0_mstory2(omObjData *obj);
void func_801155E8_mstory2(omObjData *obj);
void func_801156A8_mstory2(omObjData *obj);
void func_801158FC_mstory2(omObjData *obj);
void func_80115C0C_mstory2(omObjData *obj);
void func_80115C2C_mstory2(omObjData *obj);
void func_80115C7C_mstory2(omObjData *obj);


ObPath *func_80115E60_mstory2(Vec *points, s16 flags);
void func_80116164_mstory2(ObPath *path, f32 t, Vec *out);
void func_80116A0C_mstory2(ObPath *path);

s32 HmfAnimCreate(HmfData *, void *, s32, char *);
s16 func_80032694_main(HmfData *, u16, s32, char *);
void func_80032FF8_main(s32, u8);


void func_80113BFC_mstory2(void);
void func_80113F68_mstory2(omObjData *obj);
void func_80113F88_mstory2(omObjData *obj);
void func_80114A9C_mstory2(void);
void func_80115860_mstory2(omObjData *obj);

extern char *D_8011BC80_mstory2[];
extern char *D_8011BCA0_mstory2[];
extern const Vec D_8011C240_mstory2;
extern const StoryMotions D_8011C2F4_mstory2;
extern const Vec D_8011C3C0_mstory2;
extern const Vec D_8011C3CC_mstory2;
extern const Vec D_8011C3D8_mstory2;
extern const Vec D_8011C24C_mstory2;
extern const Vec D_8011C258_mstory2;
extern const Vec D_8011C264_mstory2;
extern const Vec D_8011C3F0_mstory2;
extern const Vec D_8011C3FC_mstory2;
extern const Vec D_8011C408_mstory2;
extern const Vec D_8011C414_mstory2;
extern Vec D_8011C8D0_mstory2;
extern Vec D_8011C8DC_mstory2;
extern Vec D_8011C8E8_mstory2;
void func_801153A8_mstory2(void);
void func_801155C8_mstory2(omObjData *obj);
void func_80115AC0_mstory2(void);
void func_80115E4C_mstory2(void);
extern const StoryRot4 D_8011C468_mstory2;
extern StoryActor2 D_8011C920_mstory2[6]; /* the second scene's actors */
extern s16 D_8011C9FA_mstory2;
extern s16 D_8011C9FC_mstory2; /* the player's character */
extern s16 D_8011C9FE_mstory2; /* the partner's character */
void func_80116B74_mstory2(void);
void func_80116D0C_mstory2(void);
void func_80116D80_mstory2(omObjData *obj);
void func_80116F0C_mstory2(omObjData *obj);
void func_8011831C_mstory2(void);
void func_80119234_mstory2(void);
void func_80119D20_mstory2(void);
void func_8011A5A0_mstory2(void);
void func_8011A74C_mstory2(void);
void func_8011A960_mstory2(void);
extern Vec D_8011BCB0_mstory2[];
extern Vec D_8011BCE0_mstory2[]; /* the second flight path; [0] is set to where the first one ends */
extern Vec D_8011BD28_mstory2;
extern Vec D_8011BD34_mstory2;
extern Vec D_8011BD40_mstory2;
extern Vec D_8011BD4C_mstory2[4];
extern Vec D_8011BD7C_mstory2;
extern Vec D_8011BD88_mstory2;
extern Vec D_8011BD94_mstory2;
extern const StoryTargets D_8011C498_mstory2;
extern s16 D_8011C9E0_mstory2[3];
extern s16 D_8011C9E6_mstory2;
extern s16 D_8011C9E8_mstory2;
void func_8000CFA4_main(s16, f32, f32, f32);
void func_801188B0_mstory2(omObjData *obj);
void func_801189CC_mstory2(omObjData *obj);
void func_80118D9C_mstory2(omObjData *obj);
void func_80119008_mstory2(omObjData *obj);
void func_80119728_mstory2(omObjData *obj);
void func_80119818_mstory2(omObjData *obj);
void func_80119A84_mstory2(omObjData *obj);
void func_80119CA0_mstory2(omObjData *obj);
void func_8011A034_mstory2(omObjData *obj);
void func_8011A26C_mstory2(omObjData *obj);
void func_8011A32C_mstory2(omObjData *obj);
void func_8011A580_mstory2(omObjData *obj);
void func_8011A890_mstory2(omObjData *obj);
void func_8011A8B0_mstory2(omObjData *obj);
void func_8011A900_mstory2(omObjData *obj);
extern Vec D_8011C8C4_mstory2;
extern s16 D_8011C90A_mstory2[3];
extern s16 D_8011C910_mstory2;
extern s16 D_8011C912_mstory2[3];
extern s16 D_8011C918_mstory2;


void func_801188A8_mstory2(void);
void func_80118C14_mstory2(omObjData *obj);

extern char *D_8011BDA0_mstory2[8];
extern const StoryMotions D_8011C4E0_mstory2;
extern Vec D_8011C9A4_mstory2; /* the actors' start positions: actor 1 */
extern s16 D_8011C9EA_mstory2[3];
extern s16 D_8011C9F0_mstory2;
extern s16 D_8011C9F8_mstory2;
void func_8011A4E4_mstory2(omObjData *obj);
extern const Vec D_8011C5AC_mstory2;
extern const Vec D_8011C5B8_mstory2;
void func_80119720_mstory2(void);
extern char *D_8011BDC0_mstory2[4];
extern const Vec D_8011C42C_mstory2;
extern s16 D_8011C9F2_mstory2[3];
extern const Vec D_8011C5C4_mstory2;
void func_8011A02C_mstory2(void);
void func_8011A24C_mstory2(omObjData *obj);
extern const Vec D_8011C438_mstory2;
extern const Vec D_8011C5DC_mstory2;
extern Vec D_8011C9B0_mstory2; /* the actors' start positions: actor 2 */
extern u8 D_8011C9FF_mstory2;
void func_8011A744_mstory2(void);
extern const Vec D_8011C444_mstory2;
extern const Vec D_8011C5E8_mstory2;
extern const Vec D_8011C5F4_mstory2;
extern Vec D_8011C9BC_mstory2; /* the actors' start positions: actor 3 */
void func_8011AAD0_mstory2(void);
extern const Vec D_8011C450_mstory2;
extern const Vec D_8011C600_mstory2;
extern Vec D_8011C9C8_mstory2; /* the actors' start positions: actor 4 */
s16 func_801061BC_mstory2(void);
void func_8011AB84_mstory2(void);
void func_8011AC08_mstory2(void);
void func_8011AC10_mstory2(omObjData *obj);
void func_8011AD8C_mstory2(omObjData *obj);
void func_8011B080_mstory2(omObjData *obj);
void func_8011B198_mstory2(void);
void func_8011B64C_mstory2(void);
extern StoryActor2 D_8011CA10_mstory2[3];
extern s16 D_8011CA4C_mstory2; /* the shadow model */
void func_80105EB4_mstory2(void);
void func_8011B464_mstory2(omObjData *obj);
extern s16 D_8011CA74_mstory2[3]; /* actor 0's texture animation slots */
extern s16 D_8011CA7A_mstory2;
extern const Vec D_8011C60C_mstory2;
extern Vec D_8011CA50_mstory2; /* the actors' start positions: actor 0 */
extern f32 D_8011BDD0_mstory2;
void func_8011B45C_mstory2(void);
void func_8011B818_mstory2(void);
void func_8011B820_mstory2(omObjData *obj);
extern const Vec D_8011C618_mstory2[2];
extern Vec D_8011CA5C_mstory2; /* the actors' start positions: actor 1 */
extern f32 D_8011CA04_mstory2;
extern f32 D_8011BDD4_mstory2;
extern f32 D_8011BDD8_mstory2;

extern char D_8011BF88_mstory2[];
extern char D_8011BF94_mstory2[];
extern char D_8011BFA0_mstory2[];
extern char D_8011BFAC_mstory2[];
extern char D_8011BFB8_mstory2[];
extern char D_8011BFC4_mstory2[];
extern char D_8011BFD0_mstory2[];
extern char D_8011BFDC_mstory2[];
extern char D_8011C168_mstory2[];
extern char D_8011C174_mstory2[];
extern char D_8011C180_mstory2[];
extern char D_8011C18C_mstory2[];
extern char D_8011C198_mstory2[];
extern char D_8011C1A4_mstory2[];
extern char D_8011C1B0_mstory2[];
extern char D_8011C1BC_mstory2[];
extern char D_8011C354_mstory2[];
extern char D_8011C360_mstory2[];
extern char D_8011C36C_mstory2[];
extern char D_8011C378_mstory2[];
extern char D_8011C384_mstory2[];
extern char D_8011C390_mstory2[];
extern char D_8011C39C_mstory2[];
extern char D_8011C3A8_mstory2[];
extern char D_8011C540_mstory2[];
extern char D_8011C54C_mstory2[];
extern char D_8011C558_mstory2[];
extern char D_8011C564_mstory2[];
extern char D_8011C570_mstory2[];
extern char D_8011C57C_mstory2[];
extern char D_8011C588_mstory2[];
extern char D_8011C594_mstory2[];

#endif
