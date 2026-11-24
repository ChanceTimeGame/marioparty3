#include "ultra64.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"

/* omObjData::unk_5C of a coaster car (D_8010C3B0_cosmic_coaster[2]) */
typedef struct CcCar {
    /* 0x00 */ s16 unk00; /* side (team) */
    /* 0x02 */ s16 unk02[2]; /* the two riders (player indices) */
    /* 0x06 */ u16 unk06; /* 1 = reached the goal */
    /* 0x08 */ f32 unk08; /* distance along the track, goal at 63000 */
    /* 0x0C */ f32 unk0C; /* speed */
    /* 0x10 */ f32 unk10[2]; /* per rider: x */
    /* 0x18 */ f32 unk18[2];
    /* 0x20 */ u16 unk20[2]; /* per rider: hit stun frames */
    /* 0x24 */ u16 unk24[2]; /* per rider: visible (blinks while stunned) */
    /* 0x28 */ u16 unk28; /* winner pose state */
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ f32 unk2C[2]; /* per rider: rot y */
    /* 0x34 */ f32 unk34[2]; /* per rider: y */
    /* 0x3C */ f32 unk3C[2]; /* per rider (CPU): target x, 100000 = none */
    /* 0x44 */ omObjData *unk44[2]; /* per rider (CPU): the track object being dodged */
    /* 0x4C */ u16 unk4C[2]; /* per rider (CPU): dodging */
    /* 0x50 */ u16 unk50; /* 0: a human rides this car (checks players 0 and 1, see func_80106758) */
    /* 0x52 */ s16 unk52;
} CcCar; // Size 0x54

/* omObjData::unk_5C of the track and HUD object (D_8010C3C0_cosmic_coaster, 0x28) */
typedef struct CcTrack {
    /* 0x00 */ s16 unk00[2]; /* per side: frame sprite */
    /* 0x04 */ s16 unk04[2]; /* per side: progress bar */
    /* 0x08 */ s16 unk08[2]; /* per side: car marker */
    /* 0x0C */ s16 unk0C[4]; /* per side: two rider icons */
    /* 0x14 */ s16 unk14; /* centre sprite */
    /* 0x16 */ s16 unk16[2]; /* per side: first track model slot */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ f32 unk1C[2]; /* per side: track scroll */
    /* 0x24 */ u16 unk24[2]; /* per side: track segments passed */
} CcTrack; // Size 0x28

/* Opening camera key (D_8010BB90_cosmic_coaster[2]) */
typedef struct CcCamKey {
    /* 0x00 */ u16 unk00; /* frames to reach this key */
    /* 0x04 */ f32 unk04; /* zoom swing */
    /* 0x08 */ Vec unk08; /* camera rotation */
    /* 0x14 */ Vec unk14; /* camera centre */
} CcCamKey; // Size 0x20

/* omObjData::data of the shooting star spawner (func_801090C0_cosmic_coaster, 0x28) */
typedef struct CcStars {
    /* 0x00 */ s16 unk00[6]; /* per slot: star sprite */
    /* 0x0C */ s16 unk0C[6]; /* per slot: trail sprite */
    /* 0x18 */ u16 unk18[2]; /* per side: frames to the next star */
    /* 0x1C */ u16 unk1C[6]; /* per slot: in use */
} CcStars; // Size 0x28

/* omObjData::data of one shooting star (func_801096A8_cosmic_coaster) */
typedef struct CcShoot {
    /* 0x00 */ u16 unk00; /* side */
    /* 0x04 */ u16 *unk04; /* its CcStars slot flag */
    /* 0x08 */ s16 unk08; /* star sprite */
    /* 0x0A */ s16 unk0A; /* trail sprite */
    /* 0x0C */ f32 unk0C; /* screen x */
    /* 0x10 */ f32 unk10; /* screen y */
    /* 0x14 */ f32 unk14; /* velocity */
    /* 0x18 */ f32 unk18;
} CcShoot; // Size 0x1C

/* One track object to place (D_8010BBD0_cosmic_coaster side 0, D_8010C060_cosmic_coaster side 1) */
typedef struct CcSpawn {
    /* 0x00 */ u16 unk00; /* type 0..8, 0xFFFF ends the list */
    /* 0x04 */ f32 unk04; /* x */
    /* 0x08 */ f32 unk08; /* y */
    /* 0x0C */ f32 unk0C; /* distance / 100 */
} CcSpawn; // Size 0x10

/* omObjData::data of a spinning track object (func_8010AF04_cosmic_coaster, 0xC) */
typedef struct CcSpin {
    /* 0x00 */ f32 unk00[3]; /* rotation speed x, y, z */
} CcSpin;

/* omObjData::data of the goal gate (func_8010B1DC_cosmic_coaster, 0x10) */
typedef struct CcGate {
    /* 0x00 */ f32 unk00; /* sway phase, then flag tilt */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08; /* flag height */
    /* 0x0C */ f32 unk0C; /* flag speed */
} CcGate;

/* Track objects keep a light distance in the unused omObjData::motion word (N64 layout). */
#define CC_LIGHT_DIST(obj) (*(f32 *)&(obj)->motion)

double fabs(double); /* the GCC builtin (abs.d) */
void HmfLightStatSet(s16, u8, u8);
void *HuMemAllocTag(s32 size, s16 tag);
s16 func_8000B0D4_main(s32, s32);
void func_8000B690_main(s32);
s32 func_8000B710_main(s32 arg0);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BF00_main(u16, f32);
s16 func_8000D550_main(s16, f32, f32, f32);
s16 func_8000D658_main(s32, s16);
void func_8001766C_main(void);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
s32 func_80017BB8_main(s16, s16);
void func_8001FB34_main(s16 arg0, u8 arg1);
void func_8001FBBC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80045C2C_main(void);
void func_80047C0C_main(u16 group, u16 max_objs);
omObjData **func_80047DBC_main(s16 arg0);
void func_80047E90_main(omObjData *obj, s32 arg1);
void func_8004AE00_main(s16, s16);
void func_800E6F0C_minigame(s8 arg0);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);
void omSetStat(omObjData *obj, u16 stat);

extern D_80111B50_vine_with_me_Struct D_8010BB30_cosmic_coaster;
extern f32 D_8010BB38_cosmic_coaster[2];
extern u16 D_8010BB5C_cosmic_coaster[2]; /* 0: fade out started, 1: bonus coins given */
extern s32 D_8010BB64_cosmic_coaster[8];
extern f32 D_8010BB84_cosmic_coaster[2];
extern s32 D_8010BB8C_cosmic_coaster;
extern struct CcMotInfo { char unk00[2]; s16 unk02; char unk04[0x14]; } *D_800CCF58_main; /* = D_800CCF58_main_Struct: per motion, [1] its length */
extern CcCamKey D_8010BB90_cosmic_coaster[2];
extern s16 D_8010BB58_cosmic_coaster[2];
extern s8 D_800CBB6E_main[];
extern s32 D_800A178C_main[][6];
extern omObjData *D_8010C050_cosmic_coaster;
extern s32 D_8010C054_cosmic_coaster;
extern f32 D_8010C010_cosmic_coaster[2];
extern f32 D_8010C018_cosmic_coaster[2];
extern s32 D_8010C020_cosmic_coaster;
extern omObjData *D_8010C024_cosmic_coaster;
extern omObjData *D_8010C028_cosmic_coaster;
extern f32 D_8010C02C_cosmic_coaster;
extern f32 D_8010C030_cosmic_coaster;
extern f32 D_8010C034_cosmic_coaster;
extern f32 D_8010C038_cosmic_coaster;
extern f32 D_8010C03C_cosmic_coaster;
extern f32 D_8010C040_cosmic_coaster;
extern f32 D_8010C044_cosmic_coaster;
extern s32 D_8010C048_cosmic_coaster;
extern s32 D_8010C04C_cosmic_coaster;
extern s16 D_8010C058_cosmic_coaster;
extern u16 D_8010C05A_cosmic_coaster;
extern omObjData *D_8010C3B0_cosmic_coaster[2];
extern CcSpawn D_8010BBD0_cosmic_coaster[];
extern s32 D_8010BEE0_cosmic_coaster[11];
extern s32 D_8010BF0C_cosmic_coaster[11];
extern omObjFunc D_8010BF38_cosmic_coaster[9];
extern omObjFunc D_8010BF5C_cosmic_coaster[9];
extern s32 D_8010BF80_cosmic_coaster[9]; /* per type: object priority */
extern CcSpawn D_8010C060_cosmic_coaster[];
extern u16 D_8010C390_cosmic_coaster[2];
extern u16 D_8010C394_cosmic_coaster[2];
extern s16 D_8010C398_cosmic_coaster[11];
extern omObjData *D_8010C3B8_cosmic_coaster;
extern s16 D_8010C3BC_cosmic_coaster;
extern omObjData *D_8010C3C0_cosmic_coaster;
extern omObjData *D_8010C3C4_cosmic_coaster;

void func_80105D80_cosmic_coaster(omObjData *object);
void func_80105DAC_cosmic_coaster(omObjData *object);
void func_80105FEC_cosmic_coaster(omObjData *object);
void func_801063CC_cosmic_coaster(omObjData *object);
void func_80106530_cosmic_coaster(s16 side);
void func_80106720_cosmic_coaster(omObjData *object);
void func_8010673C_cosmic_coaster(omObjData *object);
void func_80106758_cosmic_coaster(omObjData *object, s16 side);
void func_80106D10_cosmic_coaster(omObjData *object);
void func_80107888_cosmic_coaster(omObjData *object);
void func_80108124_cosmic_coaster(omObjData *object);
void func_8010803C_cosmic_coaster(omObjData *object);
void func_801080C8_cosmic_coaster(omObjData *object);
void func_8010812C_cosmic_coaster(omObjData *object);
void func_801083D0_cosmic_coaster(omObjData *object, s16 rider, s8 *stick);
void func_80108C9C_cosmic_coaster(omObjData *object);
s32 func_8010B97C_cosmic_coaster(omObjData *object, s32 rider, omObjData *obj);
u32 func_8010B644_cosmic_coaster(omObjData **hit, CcCar *car, f32 pos, f32 prev, u16 take);
void func_8010869C_cosmic_coaster(omObjData *object);
void func_801090C0_cosmic_coaster(omObjData *object);
void func_80109290_cosmic_coaster(omObjData *object);
s16 func_8010923C_cosmic_coaster(CcStars *work);
void func_801096A8_cosmic_coaster(omObjData *object);
void func_80109900_cosmic_coaster(void);
void func_80109A38_cosmic_coaster(omObjData *object);
void func_80109BFC_cosmic_coaster(omObjData *object, s16 side, CcSpawn *spawn);
void func_8010ABE0_cosmic_coaster(void);
void func_8010A434_cosmic_coaster(omObjData *object);
void func_8010A744_cosmic_coaster(omObjData *object);
void func_8010B5C4_cosmic_coaster(omObjData *object);
void func_8010991C_cosmic_coaster(omObjData *object);


// m3 co: Cosmic Coaster (2 vs 2, two coaster cars on split screens)

void func_801059A0_cosmic_coaster(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(0x78, 0);
    func_8004A208_main();
    func_80045C2C_main();
    func_8001EF24_main(0x3AC, 0x3E8, 0, 0xC, 0x37);
    D_8010C058_cosmic_coaster = func_8000D658_main(0x2A9, 4);
    func_8000B690_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1400.0f;
        CRotM[i].x = -8.0f;
        CRotM[i].y = 180.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 200.0f;
        CenterM[i].z = 0.0f;
        Hu3DCamSetPerspective(i, 60.0f, 80.0f, 20000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 144.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ScissorSet(1, 176.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    HmfLightMaxSet(3);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, 3.0f, 89.0f, 80.0f);
    HmfLightStatSet(1, 1, 1);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(3, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105D80_cosmic_coaster);
    D_8010C3C0_cosmic_coaster = omAddObj(0x14, 8, 0, -1, func_80105FEC_cosmic_coaster);
    D_8010C3C4_cosmic_coaster = omAddObj(0x14, 0x37, 0, -1, func_8010991C_cosmic_coaster);
    D_8010C3B0_cosmic_coaster[0] = omAddObj(0xA, 9, 0xE, -1, func_80106720_cosmic_coaster);
    D_8010C3B0_cosmic_coaster[1] = omAddObj(0xA, 9, 0xE, -1, func_8010673C_cosmic_coaster);
    omSetStat(D_8010C3C4_cosmic_coaster, 0x100);
    omAddObj(0x28, 0, 0, -1, func_801090C0_cosmic_coaster);
    func_800E5EA0_minigame(&D_8010BB30_cosmic_coaster);
    func_800EA0FC_minigame(0, 0.0f, 130.0f);
    func_800EA0FC_minigame(1, 0.0f, 130.0f);
    func_8001766C_main();
}

void func_80105D80_cosmic_coaster(omObjData *object) {
    D_8010C054_cosmic_coaster = 0;
    D_8010C050_cosmic_coaster = 0;
    D_8010C3BC_cosmic_coaster = -1;
    object->func = func_80105DAC_cosmic_coaster;
}

/* Main state: start the race, pick the winning car, pay the bonus, fade out. */
#ifdef NON_MATCHING
void func_80105DAC_cosmic_coaster(omObjData *object) {
    CcCar *car;
    CcCar *car1;
    f32 d0;
    f32 d1;
    s32 done;
    s32 i;
    u16 winner;

    if (D_8010BB5C_cosmic_coaster[0] == 0) {
        switch (func_800E6F40_minigame()) {
        case 0:
            if (D_8010C050_cosmic_coaster == NULL) {
                D_8010C05A_cosmic_coaster = 0;
                D_8010C050_cosmic_coaster = omAddObj(4, 0, 0, -1, func_8010869C_cosmic_coaster);
            }
            break;
        case 1:
            break;
        case 2:
            done = 0;
            for (i = 0; i < 2; i++) {
                car = D_8010C3B0_cosmic_coaster[i]->data;
                if (car->unk06 == 1) {
                    done |= car->unk06 << i;
                }
            }
            if (done - 1U < 2) {
                D_8010C3BC_cosmic_coaster = done - 1;
                func_800E6F0C_minigame(3);
            } else if (done == 3) {
                car = D_8010C3B0_cosmic_coaster[0]->data;
                car1 = D_8010C3B0_cosmic_coaster[1]->data;
                d0 = car->unk08;
                d1 = car1->unk08;
                if (d1 < d0) {
                    D_8010C3BC_cosmic_coaster = 0;
                } else {
                    winner = 1;
                    if (!(d0 < d1)) {
                        winner = rand8() & 1;
                    }
                    D_8010C3BC_cosmic_coaster = winner;
                }
                func_800E6F0C_minigame(3);
            }
            break;
        case 3:
            car = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->data;
            D_8010BB30_cosmic_coaster.unk18 = car->unk02[0];
            D_8010BB30_cosmic_coaster.unk19[0] = car->unk02[1];
            if (D_8010BB5C_cosmic_coaster[1] == 0) {
                GwPlayer[car->unk02[0]].bonusCoin = 10;
                GwPlayer[car->unk02[1]].bonusCoin = 10;
                D_8010BB5C_cosmic_coaster[1] = 1;
            }
            break;
        case 4:
            break;
        case 5:
            WipeCreateOut(0, 0x14);
            D_8010BB5C_cosmic_coaster[0] = 1;
            break;
        }
    } else if (WipeStatGet() == 0) {
        func_80109900_cosmic_coaster();
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80105DAC_cosmic_coaster);
#endif

/* Track and HUD setup: sprites, rider icons, four track segment models per side. */
void func_80105FEC_cosmic_coaster(omObjData *object) {
    s16 icons[4];
    s16 frame;
    s16 bar;
    s16 marker;
    s16 centre;
    s32 side;
    s32 j;
    s16 x;
    s32 layer;
    CcTrack *work;

    omSetStat(object, 0x100);
    work = object->data = HuMemAllocTag(0x28, 0x7918);
    frame = func_8000B838_main(0x31000E);
    bar = func_8000B838_main(0x31000F);
    marker = func_8000B838_main(0x310011);
    centre = func_8000B838_main(0x310010);
    for (side = 0; side < 4; side++) {
        icons[side] = func_8000B838_main(D_8010BB64_cosmic_coaster[GwPlayer[((CcCar *)D_8010C3B0_cosmic_coaster[side / 2]->data)->unk02[side % 2]].chr]);
    }
    work->unk14 = InitEspriteSlot(centre, 0, 0);
    func_8000BBD4_main(work->unk14, 0xA0, 0x28);
    func_8000BCC8_main(work->unk14, 0x80C8);
    for (side = 0; side < 2; side++) {
        layer = 2;
        if (side == 0) {
            layer = 1;
        }
        work->unk00[side] = InitEspriteSlot(frame, 0, 0);
        func_8000BBD4_main(work->unk00[side], side * 0xA0 + 0x50, 0x78);
        func_8000BC48_main(work->unk00[side], 0x4000);
        func_8000BCC8_main(work->unk00[side], 0x8190);
        work->unk04[side] = InitEspriteSlot(bar, 0, 0);
        func_8000BBD4_main(work->unk04[side], side * 0xF + 0x99, 0x78);
        func_8000BCC8_main(work->unk04[side], 0x812C);
        work->unk08[side] = InitEspriteSlot(marker, 0, 0);
        func_8000BBD4_main(work->unk08[side], side * 0x12 + 0x97, 0xCC);
        func_8000BCC8_main(work->unk08[side], 0x8064);
        for (j = 0; j < 2; j++) {
            work->unk0C[side * 2 + j] = InitEspriteSlot(icons[side * 2 + j], 0, 0);
            func_8000BCC8_main(work->unk0C[side * 2 + j], 0x8032);
        }
        /* Retail places side 0's icons for both sides; func_801063CC moves them each frame. */
        x = side * 0x12 + 0x97;
        func_8000BBD4_main(work->unk0C[0], x, 0xC4);
        func_8000BBD4_main(work->unk0C[1], x, 0xC4);
        for (j = 0; j < 4; j++) {
            if (side == 0 && j == 0) {
                object->model[0] = func_8000B108_main(0x310000, 0x20699);
            } else {
                object->model[side * 4 + j] = Hu3DModelLink(object->model[0]);
            }
            func_8001C8A8_main(object->model[side * 4 + j], layer);
        }
        work->unk1C[side] = 3300.0f;
        work->unk16[side] = 0;
        work->unk24[side] = 0;
    }
    func_80106530_cosmic_coaster(0);
    func_80106530_cosmic_coaster(1);
    object->func = func_801063CC_cosmic_coaster;
}

/* Track and HUD per frame: scroll the track by the car speed, move the progress markers. */
void func_801063CC_cosmic_coaster(omObjData *object) {
    CcTrack *work;
    CcCar *car;
    s32 side;
    s16 x;
    s32 y;

    work = D_8010C3C0_cosmic_coaster->data;
    for (side = 0; side < 2; side++) {
        car = D_8010C3B0_cosmic_coaster[side]->data;
        work->unk1C[side] += D_8010BB38_cosmic_coaster[side] / 1.08f;
        func_80106530_cosmic_coaster(side);
        x = side * 0x12 + 0x97;
        y = 204.0f - car->unk08 / 63000.0f * 164.0f;
        func_8000BBD4_main(work->unk08[side], x, y);
        func_8000BBD4_main(work->unk0C[side * 2], x, y - 8);
        func_8000BBD4_main(work->unk0C[side * 2 + 1], x, y + 8);
    }
}

/* Place one side's four track segments, recycling the nearest one when it passes. */
// decomp-permuter
void func_80106530_cosmic_coaster(s16 side)
{
  CcTrack *work;
  s32 slot;
  s32 count;
  unsigned int new_var;
  s32 i;
  new_var = side;
  work = D_8010C3C0_cosmic_coaster->data;
  slot = work->unk16[new_var];
  count = work->unk24[side];
  for (i = 0; i < 4; i++)
  {
    count++;
    Hu3DModelPosSet(D_8010C3C0_cosmic_coaster->model[(side * 4) + slot], 0.0f, 0.0f, work->unk1C[side] - (i * 3000.0f));
    if (count >= 0x17)
    {
      func_8001C258_main(D_8010C3C0_cosmic_coaster->model[(side * 4) + slot], 4, 4);
    }
    else
    {
      func_8001C258_main(D_8010C3C0_cosmic_coaster->model[(side * 4) + slot], 4, 0);
    }
    slot++;
    if (slot >= 4)
    {
      slot -= 4;
    }
  }

  if (work->unk1C[side] >= 6300.0f)
  {
    work->unk1C[side] -= 3000.0f;
    if ((++work->unk16[side]) >= 4)
    {
      work->unk16[side] -= 4;
    }
    work->unk24[side]++;
  }
}

void func_80106720_cosmic_coaster(omObjData *object) {
    func_80106758_cosmic_coaster(object, 0);
}

void func_8010673C_cosmic_coaster(omObjData *object) {
    func_80106758_cosmic_coaster(object, 1);
}

/* Car setup: the car, its two riders (model, shadow, motions), start positions. */
void func_80106758_cosmic_coaster(omObjData *object, s16 side) {
    CcCar *work;
    s32 layer;
    s32 n;
    s32 i;
    s8 chr;
    s32 dir;

    layer = 2;
    if (side == 0) {
        layer = 1;
    }
    work = object->data = HuMemAllocTag(0x54, 0x7918);
    work->unk00 = side;
    work->unk08 = work->unk0C = 0.0f;
    work->unk06 = 0;
    work->unk52 = -1;
    for (n = 0, i = 0; i < 4; i++) {
        if (GwPlayer[i].group == side) {
            work->unk02[n] = i;
            n++;
        }
    }
    object->model[0] = func_8000B108_main(0x310001, 0x206D9);
    func_8001C8A8_main(object->model[0], layer);
    object->model[1] = func_8000B108_main(0x310002, 0x206D9);
    object->model[2] = func_8000B108_main(0x310003, 0x206D9);
    func_8001C8A8_main(object->model[1], layer);
    func_8001C8A8_main(object->model[2], layer);
    func_8001FB34_main(object->model[0], 1);
    func_8001FBBC_main(object->model[0], 0, 0, 0);
    func_8001FBFC_main(object->model[0], 0.0f, -127.0f, 0.0f);
    work->unk50 = 0;
    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            work->unk50 = 1;
        }
        chr = GwPlayer[work->unk02[i]].chr;
        dir = D_800A178C_main[chr][0];
        object->model[3 + i] = func_8000B108_main(dir | D_800A178C_main[chr][1], 0x206D9);
        object->model[7 + i] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x206CD);
        func_80017790_main(object->model[7 + i], 2, chr, func_80017B6C_main(chr, 2, 1));
        func_8001C514_main(object->model[7 + i]);
        func_8001C8A8_main(object->model[3 + i], layer);
        func_8001C8A8_main(object->model[7 + i], layer);
        work->unk2C[i] = 180.0f;
        Hu3DModelRotSet(object->model[3 + i], 0.0f, 180.0f, 0.0f);
        work->unk34[i] = 125.0f;
        object->model[5 + i] = func_8000B0D4_main(9, 0x68D);
        func_8001C8A8_main(object->model[5 + i], layer);
        func_8000B460_main(object, i, func_80017BB8_main(chr, 0));
        func_8000B460_main(object, i + 2, func_80017BB8_main(chr, 0x53));
        func_8000B460_main(object, i + 4, func_80017BB8_main(chr, 0x54));
        func_8000B460_main(object, i + 6, func_80017BB8_main(chr, 4));
        func_8000B460_main(object, i + 8, func_80017BB8_main(chr, 1));
        func_8000B460_main(object, i + 10, func_80017BB8_main(chr, 0x2F));
        func_8000B460_main(object, i + 12, func_80017BB8_main(chr, 0x36));
        func_8001C5B4_main(object->model[3 + i], object->motion[2 + i]);
        func_8001C814_main(object->model[3 + i], 2, 2);
        work->unk10[i] = 0.0f;
        work->unk18[i] = 0.0f;
        work->unk20[i] = 0;
        work->unk24[i] = 1;
        work->unk3C[i] = 100000.0f;
        work->unk44[i] = NULL;
        work->unk4C[i] = 0;
        func_8001FB34_main(object->model[1 + i], 1);
        func_8001FBBC_main(object->model[1 + i], 0, 0, 0);
        func_8001FBFC_main(object->model[1 + i], 0.0f, -127.0f, 0.0f);
        func_8001FB34_main(object->model[3 + i], 1);
        func_8001FBBC_main(object->model[3 + i], 0, 0, 0);
        func_8001FBFC_main(object->model[3 + i], 0.0f, -127.0f, 0.0f);
        object->work[0] = 0;
    }
    Hu3DModelPosSet(object->model[1], work->unk10[0], 125.0f, D_8010BB84_cosmic_coaster[0]);
    Hu3DModelPosSet(object->model[2], work->unk10[1], 125.0f, D_8010BB84_cosmic_coaster[1]);
    Hu3DModelPosSet(object->model[3], work->unk10[0], work->unk34[0], D_8010BB84_cosmic_coaster[0]);
    Hu3DModelPosSet(object->model[4], work->unk10[1], work->unk34[1], D_8010BB84_cosmic_coaster[1]);
    object->func = func_80106D10_cosmic_coaster;
}

/* Car per frame while racing: steer the riders, speed up or brake, hit or collect, sounds. */
#ifdef NON_MATCHING
void func_80106D10_cosmic_coaster(omObjData *object) {
    s8 stick;
    omObjData *hit[2];
    s16 pad;
    CcCar *work;
    s32 layer;
    s32 i;
    u32 res;
    u32 res1;
    s16 mdl;
    f32 maxSpeed;

    work = object->data;
    layer = 2;
    if (work->unk00 == 0) {
        layer = 1;
    }
    maxSpeed = 130.0f;
    func_8010812C_cosmic_coaster(object);
    for (i = 0; i < 2; i++) {
        pad = GwPlayer[work->unk02[i]].pad;
        if (GwPlayer[work->unk02[i]].stat & 1) {
            func_801083D0_cosmic_coaster(object, i, &stick);
        } else {
            stick = D_800CBB6E_main[pad];
        }
        if (func_800E6E8C_minigame() != 2) {
            stick = 0;
        }
        work->unk10[i] += stick * 0.4f;
        if (work->unk10[i] < -160.0f) {
            work->unk10[i] = -160.0f;
        }
        if (work->unk10[i] > 160.0f) {
            work->unk10[i] = 160.0f;
        }
        Hu3DModelPosSet(object->model[1 + i], work->unk10[i], 125.0f, D_8010BB84_cosmic_coaster[i]);
        Hu3DModelPosSet(object->model[3 + i], work->unk10[i], 125.0f, D_8010BB84_cosmic_coaster[i]);
    }
    if (D_8010C3BC_cosmic_coaster == -1) {
        if (func_800E6E8C_minigame() == 2) {
            D_8010BB38_cosmic_coaster[work->unk00] += 4.0f;
            if (D_8010BB38_cosmic_coaster[work->unk00] > maxSpeed) {
                D_8010BB38_cosmic_coaster[work->unk00] = maxSpeed;
            }
        }
    } else if (work->unk00 == D_8010C3BC_cosmic_coaster) {
        if (work->unk08 < 63200.0f) {
            D_8010BB38_cosmic_coaster[work->unk00] += 4.0f;
            if (D_8010BB38_cosmic_coaster[work->unk00] > maxSpeed) {
                D_8010BB38_cosmic_coaster[work->unk00] = maxSpeed;
            }
        } else {
            D_8010BB38_cosmic_coaster[work->unk00] -= 12.0f;
            if (D_8010BB38_cosmic_coaster[work->unk00] < 0.0f) {
                D_8010BB38_cosmic_coaster[work->unk00] = 0.0f;
            }
            if (D_8010BB38_cosmic_coaster[work->unk00] == 0.0f && work->unk18[0] >= 0.0f && work->unk18[1] >= 0.0f) {
                HuAudFXStop(work->unk52);
                D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->func = func_80107888_cosmic_coaster;
                work->unk28 = 0;
            }
        }
        func_8001FBBC_main(object->model[0], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[0], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[1], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[1], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[2], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[2], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[3], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[3], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[4], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[4], 69.0f, 69.0f, 69.0f);
    } else {
        D_8010BB38_cosmic_coaster[work->unk00] -= 9.6f;
        if (D_8010BB38_cosmic_coaster[work->unk00] < 0.0f) {
            D_8010BB38_cosmic_coaster[work->unk00] = 0.0f;
        }
        if (D_8010BB38_cosmic_coaster[work->unk00] == 0.0f && work->unk18[0] >= 0.0f && work->unk18[1] >= 0.0f) {
            HuAudFXStop(work->unk52);
            D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster ^ 1]->func = func_80108124_cosmic_coaster;
        }
    }
    work->unk0C = work->unk08;
    work->unk08 += D_8010BB38_cosmic_coaster[work->unk00] / 1.08f;
    if (work->unk08 >= 63000.0f) {
        work->unk06 = 1;
    }
    for (i = 0; i < 2; i++) {
        if (work->unk18[i] < 0.0f) {
            work->unk24[i] ^= 1;
            if (work->unk20[i] == 0) {
                work->unk18[i] += 10.0f;
            } else {
                work->unk20[i]--;
            }
        } else {
            work->unk24[i] = 1;
            func_8001C624_main(object->model[3 + i], HmfModelData[object->motion[2 + i]].unk02, 0, 6, 0);
        }
        if (work->unk24[i] != 0) {
            func_8001C258_main(object->model[1 + i], 4, 0);
            func_8001C258_main(object->model[3 + i], 4, 0);
        } else {
            func_8001C258_main(object->model[1 + i], 4, 4);
            func_8001C258_main(object->model[3 + i], 4, 4);
        }
    }
    res = func_8010B644_cosmic_coaster(hit, work, work->unk08, work->unk0C, 1);
    if ((res & 0xFFFF) != 0xFFFF) {
        if ((res & 0xFFFF) == 4) {
            func_8004AE00_main(HuAudFXPlay(9), D_8010BB58_cosmic_coaster[work->unk00]);
            GwPlayer[work->unk02[0]].gameCoin++;
            GwPlayer[work->unk02[1]].gameCoin++;
            mdl = func_8000D550_main(D_8010C058_cosmic_coaster, 0.0f, 0.0f, 0.0f);
            if (mdl >= 0) {
                func_8001C8A8_main(mdl, layer);
                Hu3DModelPosSet(mdl, work->unk10[0], 270.0f, -100.0f);
                Hu3DModelScaleSet(mdl, 2.0f, 2.0f, 2.0f);
            }
        } else {
            func_8004AE00_main(func_8004AC98_main(0x373, work->unk02[0]), D_8010BB58_cosmic_coaster[work->unk00]);
            D_8010BB38_cosmic_coaster[work->unk00] *= 0.3f;
            work->unk18[0] = -50.0f;
            work->unk20[0] = 10;
            func_8001C5B4_main(object->model[3], object->motion[4]);
            omVibrate(work->unk02[0], 20, 0, 20);
        }
    }
    res1 = res >> 16;
    if (res1 != 0xFFFF) {
        if (res1 == 4) {
            func_8004AE00_main(HuAudFXPlay(9), D_8010BB58_cosmic_coaster[work->unk00]);
            GwPlayer[work->unk02[0]].gameCoin++;
            GwPlayer[work->unk02[1]].gameCoin++;
            mdl = func_8000D550_main(D_8010C058_cosmic_coaster, 0.0f, 0.0f, 0.0f);
            if (mdl >= 0) {
                func_8001C8A8_main(mdl, layer);
                Hu3DModelPosSet(mdl, work->unk10[1], 270.0f, 100.0f);
                Hu3DModelScaleSet(mdl, 2.0f, 2.0f, 2.0f);
            }
        } else {
            func_8004AE00_main(func_8004AC98_main(0x373, work->unk02[1]), D_8010BB58_cosmic_coaster[work->unk00]);
            D_8010BB38_cosmic_coaster[work->unk00] *= 0.3f;
            work->unk18[1] = -50.0f;
            work->unk20[1] = 10;
            func_8001C5B4_main(object->model[4], object->motion[5]);
            omVibrate(work->unk02[1], 20, 0, 20);
        }
    }
    Hu3DModelRotSet(object->model[1], work->unk18[0], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[3], work->unk18[0], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], work->unk18[1], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[4], work->unk18[1], 180.0f, 0.0f);
    if (D_8010BB38_cosmic_coaster[work->unk00] > 0.0f && work->unk52 == -1) {
        work->unk52 = HuAudFXPlay(0x372);
        func_8004AE00_main(work->unk52, D_8010BB58_cosmic_coaster[work->unk00]);
    }
    func_80108C9C_cosmic_coaster(object);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106D10_cosmic_coaster);
#endif

/* Winning car after the goal: riders turn, jump off, land, spin and cheer. */
void func_80107888_cosmic_coaster(omObjData *object) {
    f32 z[2];
    CcCar *work;
    s32 i;
    s16 tmp;

    z[0] = -100.0f;
    z[1] = 100.0f;
    work = object->data;
    switch (work->unk28) {
    case 0:
        work->unk28 = 1;
        D_8010C020_cosmic_coaster = 30;
        break;
    case 1:
        if (D_8010C020_cosmic_coaster != 0) {
            if (--D_8010C020_cosmic_coaster == 0) {
                func_8001C5B4_main(object->model[3], object->motion[8]);
                func_8001C5B4_main(object->model[4], object->motion[9]);
                func_8001C814_main(object->model[3], 3, 2);
                func_8001C814_main(object->model[4], 3, 2);
            }
            break;
        }
        for (i = 0; i < 2; i++) {
            if (work->unk2C[i] < 270.0f) {
                work->unk2C[i] += 8.0f;
                if (work->unk2C[i] > 270.0f) {
                    work->unk2C[i] = 270.0f;
                }
            } else {
                D_8010C024_cosmic_coaster = omAddObj(0x28, 0, 0, -1, func_8010803C_cosmic_coaster);
                work->unk28 = 2;
                func_8001C258_main(object->model[3 + i], 4, 4);
                func_8001C258_main(object->model[7 + i], 4, 0);
                tmp = object->model[3 + i];
                object->model[3 + i] = object->model[7 + i];
                object->model[7 + i] = tmp;
                Hu3DModelPosSet(object->model[3 + i], work->unk10[i], work->unk34[i], z[i]);
                Hu3DModelRotSet(object->model[3 + i], 0.0f, work->unk2C[i], 0.0f);
                func_8001C5B4_main(object->model[3], object->motion[0]);
                func_8001C5B4_main(object->model[4], object->motion[1]);
            }
            Hu3DModelRotSet(object->model[3 + i], 0.0f, work->unk2C[i], 0.0f);
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            work->unk10[i] -= 20.0f;
            if (work->unk10[i] < -160.0f) {
                work->unk10[i] = -160.0f;
            }
            Hu3DModelPosSet(object->model[1 + i], work->unk10[i], work->unk34[i], z[i]);
            Hu3DModelPosSet(object->model[3 + i], work->unk10[i], work->unk34[i], z[i]);
        }
        if (work->unk10[0] == -160.0f && work->unk10[1] == -160.0f) {
            work->unk28 = 3;
            func_8001C5B4_main(object->model[3], object->motion[6]);
            func_8001C5B4_main(object->model[4], object->motion[7]);
            func_8001C814_main(object->model[3], 2, 0);
            func_8001C814_main(object->model[4], 2, 0);
            for (i = 0; i < 2; i++) {
                D_8010C018_cosmic_coaster[i] = 70.0f;
            }
            D_8010C010_cosmic_coaster[0] = -17.0f;
            D_8010C010_cosmic_coaster[1] = -12.0f;
        }
        break;
    case 3:
        for (i = 0; i < 2; i++) {
            work->unk10[i] += D_8010C010_cosmic_coaster[i];
            work->unk34[i] += D_8010C018_cosmic_coaster[i];
            D_8010C018_cosmic_coaster[i] -= 10.0f;
            if (work->unk34[i] < 125.0f) {
                work->unk34[i] = 125.0f;
                work->unk28 = 4;
                omDelObj(D_8010C024_cosmic_coaster);
                D_8010C024_cosmic_coaster = omAddObj(0x28, 0, 0, -1, func_801080C8_cosmic_coaster);
                func_8001C5B4_main(object->model[3], object->motion[8]);
                func_8001C5B4_main(object->model[4], object->motion[9]);
            }
            Hu3DModelPosSet(object->model[3 + i], work->unk10[i], work->unk34[i], z[i]);
            func_8001C258_main(object->model[5 + i], 4, 0);
            Hu3DModelPosSet(object->model[5 + i], work->unk10[i], 125.0f, z[i]);
        }
        break;
    case 4:
        for (i = 0; i < 2; i++) {
            work->unk2C[i] += 8.0f;
            if (work->unk2C[i] >= 360.0f) {
                work->unk2C[0] = 0.0f;
                work->unk28 = 5;
            }
            Hu3DModelRotSet(object->model[3 + i], 0.0f, work->unk2C[i], 0.0f);
        }
        break;
    case 5:
        if (D_8010C024_cosmic_coaster->work[0] == 1) {
            work->unk28 = 6;
            omDelObj(D_8010C024_cosmic_coaster);
        }
        break;
    case 6:
        D_8010C028_cosmic_coaster = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster ^ 1];
        for (i = 0; i < 2; i++) {
            func_8001C624_main(object->model[3 + i], HmfModelData[object->motion[10 + i]].unk02, 0, 6, 0);
            func_8001C624_main(D_8010C028_cosmic_coaster->model[3 + i], HmfModelData[D_8010C028_cosmic_coaster->motion[12 + i]].unk02, 0, 6, 0);
            func_80045ED0_main(D_800A178C_main[GwPlayer[work->unk02[0]].chr][0] | 0x2F);
            func_80045ED0_main(D_800A178C_main[GwPlayer[work->unk02[1]].chr][0] | 0x2F);
        }
        D_8010C028_cosmic_coaster->work[0] = 1;
        D_8010C028_cosmic_coaster->work[1] = 45;
        func_800E6F0C_minigame(4);
        work->unk28 = 7;
        break;
    }
}

/* Camera follow: pan the winner's camera left with the riders. */
void func_8010803C_cosmic_coaster(omObjData *object) {
    CcCar *car;

    car = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->data;
    if (CenterM[D_8010C3BC_cosmic_coaster].x > car->unk10[0]) {
        CenterM[D_8010C3BC_cosmic_coaster].x -= 20.0f;
        if (CenterM[D_8010C3BC_cosmic_coaster].x < car->unk10[0]) {
            CenterM[D_8010C3BC_cosmic_coaster].x = car->unk10[0];
        }
    }
}

/* Camera zoom in on the winners, then report done. */
void func_801080C8_cosmic_coaster(omObjData *object) {
    if (D_8010BB8C_cosmic_coaster != 0) {
        CZoomM[D_8010C3BC_cosmic_coaster] -= 30.0f;
        D_8010BB8C_cosmic_coaster--;
    } else {
        object->work[0] = 1;
    }
}

void func_80108124_cosmic_coaster(omObjData *object) {
}

/* CPU riders: look ahead for track objects and pick a free lane to steer to. */
void func_8010812C_cosmic_coaster(omObjData *object) {
    u8 lane[3];
    u8 cand[3];
    f32 laneX[3] = { -160.0f, 0.0f, 160.0f };
    f32 z[2];
    omObjData *hit[2];
    CcCar *work;
    s32 i;
    s32 j;
    u8 n;
    u32 bits;
    omObjData *obj;
    f32 ahead;

    z[0] = -100.0f;
    z[1] = 100.0f;
    work = object->data;
    ahead = D_8010BB38_cosmic_coaster[work->unk00] / 1.08f * 15.0f;
    hit[1] = NULL;
    hit[0] = NULL;
    func_8010B644_cosmic_coaster(hit, work, ahead + work->unk08, work->unk08, 0);
    for (i = 0; i < 2; i++) {
        if (work->unk4C[i] == 0) {
            obj = hit[i];
            if (obj != NULL) {
                work->unk44[i] = obj;
                bits = func_8010B97C_cosmic_coaster(object, i, obj);
                work->unk4C[i] = 1;
                lane[0] = (bits & 0x30) >> 4;
                lane[1] = (bits & 0xC) >> 2;
                lane[2] = bits & 3;
                for (n = 0, j = 0; j < 3; j++) {
                    if (lane[j] < 2) {
                        cand[n++] = j;
                    }
                }
                if (work->unk3C[i] == 100000.0f) {
                    if (n == 1) {
                        work->unk3C[i] = laneX[cand[0]];
                    } else {
                        work->unk3C[i] = laneX[cand[rand8() % n]];
                    }
                }
            }
        } else {
            D_8010C3B8_cosmic_coaster = work->unk44[i];
            if (work->unk08 - z[i] - 30.0f > work->unk44[i]->trans.z) {
                work->unk44[i] = NULL;
                work->unk3C[i] = 100000.0f;
                work->unk4C[i] = 0;
            }
        }
    }
}

/* CPU rider steering: stick value toward the chosen lane, speed by difficulty. */
// decomp-permuter
void func_801083D0_cosmic_coaster(omObjData *object, s16 rider, s8 *stick)
{
  CcCar *work;
  s8 speed;
  f32 tol;
  f32 d;
  work = object->data;
  *stick = 0;
  if (work->unk3C[rider] != 100000.0f)
  {
    if (work->unk50 == 1)
    {
      speed = 70;
      tol = 4.0f;
    }
    else
    {
 do { switch (GwPlayer[work->unk02[rider]].cpu_difficulty) { case 0: speed = (rand8() % 13) + 58; tol = 2.0f; break; case 1: speed = (rand8() % 10) + 62; tol = 2.0f; break; case 2: speed = (rand8() & 7) + 66; tol = 3.0f; break; case 3: speed = 70; tol = 4.0f; break; } } while (0);
    }
    if (speed >= 71)
    {
      speed = 70;
    }
    if (work->unk10[rider] > work->unk3C[rider])
    {
      d = work->unk10[rider] - work->unk3C[rider];
      if (d > 10.0f)
      {
        *stick = -speed;
        return;
      }
      if (!(d < tol))
      {
        *stick = (-speed) / 2;
        return;
      }
    }
    else
      if (work->unk10[rider] < work->unk3C[rider])
    {
      d = work->unk10[rider] - work->unk3C[rider];
      if (d < (-10.0f))
      {
        *stick = speed;
        return;
      }
      if (!(d < (-tol)))
      {
        *stick = speed / 2;
        return;
      }
    }
    work->unk3C[rider] = 100000.0f;
  }
}

/* Opening: fade in, then move both cameras through the two keys, start the music. */
#ifdef NON_MATCHING
void func_8010869C_cosmic_coaster(omObjData *object) {
    s32 i;
    f32 f;

    switch (D_8010C05A_cosmic_coaster) {
    case 0:
        WipeCreateIn(0xFF, 0x10);
        D_8010C05A_cosmic_coaster = 1;
        break;
    case 1:
        if (WipeStatGet() == 0) {
            D_8010C05A_cosmic_coaster = 2;
            D_8010C04C_cosmic_coaster = 0;
            D_8010C02C_cosmic_coaster = CZoomM[0];
            D_8010C030_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.x - -8.0f) / 30.0f;
            D_8010C034_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.y - 180.0f) / 30.0f;
            D_8010C038_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.z - 0.0f) / 30.0f;
            D_8010C03C_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.x - 0.0f) / 30.0f;
            D_8010C040_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.y - 200.0f) / 30.0f;
            D_8010C044_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.z - 0.0f) / 30.0f;
            D_8010C048_cosmic_coaster = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk00;
        }
        break;
    case 2:
        if (--D_8010C048_cosmic_coaster != 0) {
            for (i = 0; i < 2; i++) {
                CRotM[i].x += D_8010C030_cosmic_coaster;
                CRotM[i].y += D_8010C034_cosmic_coaster;
                CRotM[i].z += D_8010C038_cosmic_coaster;
                CenterM[i].x += D_8010C03C_cosmic_coaster;
                CenterM[i].y += D_8010C040_cosmic_coaster;
                CenterM[i].z += D_8010C044_cosmic_coaster;
                if (CRotM[i].y > 90.0f) {
                    f = sindf(CRotM[i].y);
                } else {
                    f = cosdf(CRotM[i].y);
                }
                CZoomM[i] = D_8010C02C_cosmic_coaster + fabs(f) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk04;
            }
            break;
        }
        for (i = 0; i < 2; i++) {
            CRotM[i].x = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.x;
            CRotM[i].y = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.y;
            CRotM[i].z = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.z;
            CenterM[i].x = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.x;
            CenterM[i].y = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.y;
            CenterM[i].z = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.z;
            if (CRotM[i].y >= 90.0f) {
                f = sindf(CRotM[i].y);
            } else {
                f = cosdf(CRotM[i].y);
            }
            CZoomM[i] = D_8010C02C_cosmic_coaster + fabs(f) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk04;
        }
        if (++D_8010C04C_cosmic_coaster == 2) {
            D_8010C05A_cosmic_coaster = 3;
            HuAudSeqPlay(0x37);
            break;
        }
        D_8010C030_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.x - CRotM[0].x) / 30.0f;
        D_8010C034_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.y - CRotM[0].y) / 30.0f;
        D_8010C038_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk08.z - CRotM[0].z) / 30.0f;
        D_8010C03C_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.x - CenterM[0].x) / 30.0f;
        D_8010C040_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.y - CenterM[0].y) / 30.0f;
        D_8010C044_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk14.z - CenterM[0].z) / 30.0f;
        D_8010C02C_cosmic_coaster = CZoomM[0];
        D_8010C048_cosmic_coaster = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].unk00;
        break;
    case 3:
        omDelObj(object);
        D_8010C050_cosmic_coaster = NULL;
        func_800E6F0C_minigame(1);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010869C_cosmic_coaster);
#endif

/* Light the car and riders by the nearest glowing track object (type 4). */
void func_80108C9C_cosmic_coaster(omObjData *object) {
    CcCar *work;
    omObjData **objs;
    omObjData *o;
    omObjData *best;
    f32 bestD;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 nx;
    f32 ny;
    f32 nz;
    u8 r;
    u8 g;
    u8 b;
    s32 i;

    work = object->data;
    best = NULL;
    objs = func_80047DBC_main(work->unk00);
    bestD = 500000.0f;
    for (i = 0; i < 0x37; i++) {
        o = objs[i];
        if (o == NULL) {
            continue;
        }
        if (o->work[1] != 4) {
            continue;
        }
        d = HuSqrtf((o->trans.x - object->trans.x) * (o->trans.x - object->trans.x) + (o->trans.y - object->trans.y) * (o->trans.y - object->trans.y) + (work->unk08 - o->trans.z - object->trans.z) * (work->unk08 - o->trans.z - object->trans.z));
        if (d < bestD) {
            bestD = d;
            best = o;
        }
    }
    if (best != NULL && bestD <= 1600.0f) {
        nx = (best->trans.x - object->trans.x) / bestD * 127.0f;
        ny = (best->trans.y - object->trans.y) / bestD * 127.0f;
        nz = (work->unk08 - best->trans.z - object->trans.z) / bestD * 127.0f;
        r = (1600.0f - bestD) * 0.159375f;
        g = (1600.0f - bestD) * 0.159375f;
        b = (1600.0f - bestD) * 0.159375f;
        func_8001FBBC_main(object->model[0], r, g, b);
        func_8001FBFC_main(object->model[0], nx, ny, nz);
        for (i = 0; i < 2; i++) {
            func_8001FBBC_main(object->model[1 + i], r, g, b);
            func_8001FBFC_main(object->model[1 + i], nx, ny, nz);
            func_8001FBBC_main(object->model[3 + i], r, g, b);
            func_8001FBFC_main(object->model[3 + i], nx, ny, nz);
        }
    } else {
        func_8001FBBC_main(object->model[0], 0, 0, 0);
        for (i = 0; i < 2; i++) {
            func_8001FBBC_main(object->model[1 + i], 0, 0, 0);
            func_8001FBBC_main(object->model[3 + i], 0, 0, 0);
        }
    }
}

/* Shooting star spawner setup: six star and trail sprites, a random delay per side. */
void func_801090C0_cosmic_coaster(omObjData *object) {
    CcStars *work;
    s16 star;
    s16 trail;
    s32 i;

    work = object->data = HuMemAllocTag(0x28, 0x7918);
    star = func_8000B838_main(0x310012);
    trail = func_8000B838_main(0x310013);
    for (i = 0; i < 6; i++) {
        work->unk00[i] = InitEspriteSlot(star, 0, 0);
        func_8000BCC8_main(work->unk00[i], 0x815E);
        func_8000BC48_main(work->unk00[i], 0x4000);
        func_8000BE5C_main(work->unk00[i], 0.5f, 0.5f);
        func_8000BB94_main(work->unk00[i]);
        work->unk0C[i] = InitEspriteSlot(trail, 0, 0);
        func_8000BCC8_main(work->unk0C[i], 0x815E);
        func_8000BC48_main(work->unk0C[i], 0x4000);
        func_8000BE5C_main(work->unk0C[i], 0.5f, 0.5f);
        func_8000BB94_main(work->unk0C[i]);
        work->unk1C[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        work->unk18[i] = rand8() + 0x78;
    }
    object->func = func_80109290_cosmic_coaster;
}

/* Claim a free star slot; -1 when all six are flying. */
s16 func_8010923C_cosmic_coaster(CcStars *work) {
    s16 i;

    for (i = 0; i < 6; i++) {
        if (work->unk1C[i] == 0) {
            work->unk1C[i] = 1;
            return i;
        }
    }
    return -1;
}

/* Shooting star spawner per frame: launch a star on each side when its delay runs out. */
#ifdef NON_MATCHING
void func_80109290_cosmic_coaster(omObjData *object) {
    CcStars *work;
    omObjData *obj;
    CcShoot *star;
    s32 side;
    s16 slot;
    f32 angle;
    f32 x;
    f32 y;

    work = object->data;
    for (side = 0; side < 2; side++) {
        if (--work->unk18[side] == 0) {
            work->unk18[side] = rand8() % 121 + 0x78;
            slot = func_8010923C_cosmic_coaster(work);
            if (slot != -1) {
                obj = omAddObj(0x28, 0, 0, -1, func_801096A8_cosmic_coaster);
                star = obj->data = HuMemAllocTag(sizeof(CcShoot), 0x7918);
                star->unk00 = side;
                angle = (rand8() * rand8()) % 1801 / 10.0f;
                if (angle >= 60.0f && angle <= 120.0f) {
                    if (angle > 90.0f) {
                        angle = 120.0f;
                    } else {
                        angle = 60.0f;
                    }
                }
                x = cosdf(angle) * 160.0f;
                y = -(sindf(angle) * 160.0f + 80.0f);
                if (side == 0) {
                    if (x < -20.0f) {
                        x = -20.0f;
                    }
                    if (x > 164.0f) {
                        x = 164.0f;
                    }
                } else {
                    x += 160.0f;
                    if (x < 156.0f) {
                        x = 156.0f;
                    }
                    if (x > 340.0f) {
                        x = 180.0f;
                    }
                }
                if (y < -20.0f) {
                    y = -20.0f;
                }
                if (y > 80.0f) {
                    y = 80.0f;
                }
                star->unk0C = x;
                star->unk10 = y;
                angle -= 180.0f;
                star->unk14 = cosdf(angle) * 4.5f;
                star->unk18 = -sindf(angle) * 4.5f;
                star->unk04 = &work->unk1C[slot];
                star->unk08 = work->unk00[slot];
                star->unk0A = work->unk0C[slot];
                func_8000BBD4_main(star->unk08, star->unk0C, star->unk10);
                func_8000BB54_main(star->unk08);
                func_8000BBD4_main(star->unk0A, star->unk0C, star->unk10);
                func_8000BB54_main(star->unk0A);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109290_cosmic_coaster);
#endif

/* One shooting star: fly, point the trail along the motion, vanish off its half of the screen. */
// C path identical (n64chkf), but retail pads 2 nops after it: a TU boundary at 0x80109900 (split wall), so the ROM cannot match in this unit
#ifdef NON_MATCHING
void func_801096A8_cosmic_coaster(omObjData *object) {
    CcShoot *star;

    star = object->data;
    star->unk0C += star->unk14;
    star->unk10 += star->unk18;
    star->unk18 *= 1.0f;
    func_8000BBD4_main(star->unk08, star->unk0C, star->unk10);
    func_8000BBD4_main(star->unk0A, star->unk0C, star->unk10);
    func_8000BF00_main(star->unk0A, atan2df(-star->unk18, star->unk14) - 180.0f);
    switch (star->unk00) {
    case 0:
        if (star->unk10 >= 260.0f) {
            goto end;
        }
        if (star->unk14 < 0.0f && star->unk0C < -20.0f) {
            goto end;
        }
        if (!(star->unk18 >= 0.0f)) {
            break;
        }
        if (!(star->unk0C > 164.0f)) {
            break;
        }
        goto end;
    case 1:
        if (star->unk10 >= 260.0f) {
            goto end;
        }
        if (star->unk14 < 0.0f && star->unk0C < 156.0f) {
            goto end;
        }
        if (!(star->unk18 >= 0.0f)) {
            break;
        }
        if (!(star->unk0C > 324.0f)) {
            break;
        }
    end:
        func_8000BB94_main(star->unk08);
        func_8000BB94_main(star->unk0A);
        *star->unk04 = 0;
        omDelObj(object);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801096A8_cosmic_coaster);
#endif

/* Leave the minigame. */
void func_80109900_cosmic_coaster(void) {
    omOvlReturnEx(1);
}

/* Track object manager setup: free model slots, spawn lists, the eleven object models. */
void func_8010991C_cosmic_coaster(omObjData *object) {
    s32 i;

    func_80047C0C_main(0, 0x37);
    func_80047C0C_main(1, 0x37);
    for (i = 0; i < 0x37; i++) {
        object->model[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        D_8010C390_cosmic_coaster[i] = 0;
        D_8010C394_cosmic_coaster[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        D_8010C398_cosmic_coaster[i] = func_8000B108_main(D_8010BEE0_cosmic_coaster[i], D_8010BF0C_cosmic_coaster[i] | 4);
    }
    func_8010ABE0_cosmic_coaster();
    object->func = func_80109A38_cosmic_coaster;
}

/* Track object manager per frame: spawn every listed object within 9000 of each car. */
void func_80109A38_cosmic_coaster(omObjData *object) {
    CcSpawn *spawn;
    f32 reach;
    s32 side;

    for (side = 0; side < 2; side++) {
        reach = ((CcCar *)D_8010C3B0_cosmic_coaster[side]->data)->unk08 + 9000.0f;
        spawn = &D_8010BBD0_cosmic_coaster[D_8010C390_cosmic_coaster[side]];
        while (spawn->unk00 != 0xFFFF) {
            if (spawn->unk0C * 100.0f <= reach) {
                func_80109BFC_cosmic_coaster(object, side, spawn);
                D_8010C390_cosmic_coaster[side]++;
            }
            spawn++;
        }
        spawn = &D_8010C060_cosmic_coaster[D_8010C394_cosmic_coaster[side]];
        while (spawn->unk00 != 0xFFFF) {
            if (spawn->unk0C * 100.0f <= reach) {
                func_80109BFC_cosmic_coaster(object, side, spawn);
                D_8010C394_cosmic_coaster[side]++;
            }
            spawn++;
        }
    }
}

/* Spawn one track object: link its model into a free slot, add its object, run its init. */
#ifdef NON_MATCHING
void func_80109BFC_cosmic_coaster(omObjData *object, s16 side, CcSpawn *spawn) {
    omObjData *obj;
    CcCar *car;
    s32 slot;
    s32 slot1;
    s32 slot2;
    s32 src;
    s32 layer;
    omObjFunc init;

    for (slot = 0; slot < 0x37; slot++) {
        if (object->model[slot] == -1) {
            break;
        }
    }
    if (slot == 0x37) {
        osSyncPrintf("obj over\n");
        return;
    }
    car = D_8010C3B0_cosmic_coaster[side]->data;
    if (spawn->unk00 != 1) {
        src = D_8010C398_cosmic_coaster[spawn->unk00];
    } else if (spawn->unk04 < 0.0f) {
        src = D_8010C398_cosmic_coaster[9];
    } else {
        src = D_8010C398_cosmic_coaster[1];
    }
    layer = 2;
    object->model[slot] = Hu3DModelLink(src);
    if (side == 0) {
        layer = 1;
    }
    if (spawn->unk00 != 6) {
        obj = omAddObj((s16)D_8010BF80_cosmic_coaster[spawn->unk00], 1, 0, side, D_8010BF38_cosmic_coaster[spawn->unk00]);
        omSetStat(obj, 0x100);
        obj->model[0] = object->model[slot];
        obj->work[0] = slot;
        obj->work[1] = spawn->unk00;
        obj->work[2] = side;
    } else {
        obj = omAddObj((s16)D_8010BF80_cosmic_coaster[spawn->unk00], 3, 0, side, D_8010BF38_cosmic_coaster[spawn->unk00]);
        omSetStat(obj, 0x100);
        obj->model[0] = object->model[slot];
        obj->work[1] = spawn->unk00;
        obj->work[2] = side;
        obj->work[3] = -1;
        for (slot1 = 0; slot1 < 0x37; slot1++) {
            if (object->model[slot1] == -1) {
                break;
            }
        }
        if (slot1 != 0x37) {
            object->model[slot1] = Hu3DModelLink(D_8010C398_cosmic_coaster[7]);
            obj->work[3] &= 0xFFFF;
            obj->model[1] = object->model[slot1];
            obj->work[3] |= slot1 << 16;
        } else {
            osSyncPrintf("obj over\n");
        }
        for (slot2 = 0; slot2 < 0x37; slot2++) {
            if (object->model[slot2] == -1) {
                break;
            }
        }
        if (slot2 != 0x37) {
            object->model[slot2] = Hu3DModelLink(D_8010C398_cosmic_coaster[8]);
            obj->work[3] &= 0xFFFF0000;
            obj->model[2] = object->model[slot2];
            obj->work[3] |= slot2 & 0xFFFF;
        } else {
            osSyncPrintf("obj over\n");
        }
        func_8001C258_main(object->model[slot1], 4, 0);
        Hu3DModelPosSet(object->model[slot1], spawn->unk04, spawn->unk08 + 400.0f, car->unk08 - spawn->unk0C * 100.0 - 1185.0);
        Hu3DModelPosSet(object->model[slot2], spawn->unk04, spawn->unk08 + 400.0f, car->unk08 - spawn->unk0C * 100.0 - 1185.0);
        func_8001C8A8_main(object->model[slot1], layer);
        func_8001C8A8_main(object->model[slot2], layer);
        func_8001FB34_main(object->model[slot1], 1);
        func_8001FBBC_main(object->model[slot1], 0, 0, 0);
        func_8001FBFC_main(object->model[slot1], 0.0f, -127.0f, 0.0f);
        func_8001FB34_main(object->model[slot2], 1);
        func_8001FBBC_main(object->model[slot2], 0, 0, 0);
        func_8001FBFC_main(object->model[slot2], 0.0f, -127.0f, 0.0f);
    }
    func_8001FB34_main(object->model[slot], 1);
    func_8001FBBC_main(object->model[slot], 0, 0, 0);
    func_8001FBFC_main(object->model[slot], 0.0f, -127.0f, 0.0f);
    func_8001C258_main(object->model[slot], 4, 0);
    func_8001C814_main(object->model[slot], 2, 2);
    func_8001C8A8_main(object->model[slot], layer);
    omSetTra(obj, spawn->unk04, spawn->unk08, spawn->unk0C * 100.0f);
    /* Retail uses the manager's own position here; the object's update moves it. */
    Hu3DModelPosSet(obj->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    Hu3DModelRotSet(obj->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
    init = D_8010BF5C_cosmic_coaster[spawn->unk00];
    if (init != NULL) {
        init(obj);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109BFC_cosmic_coaster);
#endif

/* Track object type 0 (hazard): follow the track; on a hit swap to its broken model. */
void func_8010A244_cosmic_coaster(omObjData *object) {
    CcCar *car;
    s16 slot;
    s16 mdl;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    if (object->unk10 == 1) {
        func_8010B5C4_cosmic_coaster(object);
        func_8001ACDC_main(object->model[0]);
        slot = object->work[0];
        mdl = Hu3DModelLink(D_8010C398_cosmic_coaster[2]);
        object->model[0] = D_8010C3C4_cosmic_coaster->model[slot] = mdl;
        if (object->work[2] == 0) {
            func_8001C8A8_main(object->model[0], 1);
        } else {
            func_8001C8A8_main(object->model[0], 2);
        }
        object->work[1] = 2;
        object->func = func_8010A434_cosmic_coaster;
        func_8001FB34_main(object->model[0], 1);
        func_8001FBBC_main(object->model[0], 0, 0, 0);
        func_8001FBFC_main(object->model[0], 0.0f, -127.0f, 0.0f);
        func_8001C258_main(object->model[0], 4, 0);
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    } else if (car->unk08 - object->trans.z >= 3300.0f) {
        func_8001ACDC_main(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Broken hazard: follow the track until its motion ends, then free the slot. */
void func_8010A434_cosmic_coaster(omObjData *object) {
    HmfModel *hmf;
    CcCar *car;
    s16 mdl;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    mdl = object->model[0];
    if (D_800CCF58_main[HmfModelData[mdl].unk02].unk02 <= HmfModelData[mdl].unk40) {
        func_8001ACDC_main(mdl);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Track object type 1 (side hazard): as type 0, broken model by side of the track. */
void func_8010A528_cosmic_coaster(omObjData *object) {
    CcCar *car;
    s16 slot;
    s32 src;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    if (object->unk10 == 1) {
        func_8010B5C4_cosmic_coaster(object);
        func_8001ACDC_main(object->model[0]);
        slot = object->work[0];
        if (object->trans.x > 0.0f) {
            src = D_8010C398_cosmic_coaster[3];
        } else {
            src = D_8010C398_cosmic_coaster[10];
        }
        object->model[0] = D_8010C3C4_cosmic_coaster->model[slot] = Hu3DModelLink(src);
        if (object->work[2] == 0) {
            func_8001C8A8_main(object->model[0], 1);
        } else {
            func_8001C8A8_main(object->model[0], 2);
        }
        object->work[1] = 2;
        object->func = func_8010A744_cosmic_coaster;
        func_8001FB34_main(object->model[0], 1);
        func_8001FBBC_main(object->model[0], 0, 0, 0);
        func_8001FBFC_main(object->model[0], 0.0f, -127.0f, 0.0f);
        func_8001C258_main(object->model[0], 4, 0);
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    } else if (car->unk08 - object->trans.z >= 3300.0f) {
        func_8001ACDC_main(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Broken side hazard (same as func_8010A434). */
void func_8010A744_cosmic_coaster(omObjData *object) {
    HmfModel *hmf;
    CcCar *car;
    s16 mdl;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    mdl = object->model[0];
    if (D_800CCF58_main[HmfModelData[mdl].unk02].unk02 <= HmfModelData[mdl].unk40) {
        func_8001ACDC_main(mdl);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Track object type 4 (glowing star): light the nearby objects of its side, vanish when hit or passed. */
void func_8010A838_cosmic_coaster(omObjData *object) {
    CcCar *car;
    omObjData **objs;
    omObjData *o;
    f32 d;
    f32 nx;
    f32 ny;
    f32 nz;
    u8 r;
    u8 g;
    u8 b;
    s32 i;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    omSetSca(object, 2.5f, 2.5f, 2.5f);
    Hu3DModelScaleSet(object->model[0], 2.5f, 2.5f, 2.5f);
    func_8001FBFC_main(object->model[0], 69.0f, 69.0f, 69.0f);
    func_8001FBBC_main(object->model[0], 0xFF, 0xFF, 0xFF);
    objs = func_80047DBC_main((s16)object->work[2]);
    for (i = 0; i < 0x37; i++) {
        if (objs[i] != NULL && (o = objs[i])->work[1] != 4) {
            d = HuSqrtf((o->trans.x - object->trans.x) * (o->trans.x - object->trans.x) + (o->trans.y - object->trans.y) * (o->trans.y - object->trans.y) + (o->trans.z - object->trans.z) * (o->trans.z - object->trans.z));
            if (!(d > 1600.0f) && !(CC_LIGHT_DIST(o) < d)) {
                CC_LIGHT_DIST(o) = d;
                nx = (object->trans.x - o->trans.x) / d * 127.0f;
                ny = (object->trans.y - o->trans.y) / d * 127.0f;
                nz = (object->trans.z - o->trans.z) / d * 127.0f;
                r = (1600.0f - d) * 0.159375f;
                g = (1600.0f - d) * 0.159375f;
                b = (1600.0f - d) * 0.159375f;
                HmfLightColorSet(o->model[0], r, g, b);
                HmfLightDirSet(o->model[0], nx, ny, nz);
            }
        }
    }
    if (car->unk08 - object->trans.z >= 5900.0f || object->unk10 == 1) {
        func_8010B5C4_cosmic_coaster(object);
        func_8001ACDC_main(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Side 1's spawn list: fifty glowing stars at random spots along the track. */
void func_8010ABE0_cosmic_coaster(void) {
    CcSpawn *spawn;
    s32 i;
    f32 dist;
    f32 angle;
    f32 r;
    f32 x;
    f32 y;

    spawn = D_8010C060_cosmic_coaster;
    dist = (u8)(rand8() % 15) + 17;
    for (i = 0; i != 50; i++) {
        spawn->unk00 = 5;
        spawn->unk0C = dist;
        angle = (rand8() * rand8()) % 3600 / 10.0f;
        r = (rand8() * rand8()) % 4500 / 10.0f + 500.0f;
        x = cosdf(angle) * r;
        y = sindf(angle) * r;
        spawn->unk04 = x;
        if (((y > 0.0f) & (y < 800.0f) && (x > -300.0f) & (x < 300.0f)) || (spawn->unk0C > 625.0f && spawn->unk0C < 685.0f)) {
            y = 650.0f;
        }
        spawn->unk08 = y + 150.0f;
        dist += (u8)(rand8() % 7) + 11.0f;
        spawn++;
    }
    spawn->unk00 = 0xFFFF;
}

/* Init of track object type 5: random spin speeds. */
void func_8010AF04_cosmic_coaster(omObjData *object) {
    CcSpin *work;

    work = object->data = HuMemAllocTag(0xC, 0x7918);
    work->unk00[0] = ((u8)(rand8() % 35) + 5) / 10.0f;
    work->unk00[1] = ((u8)(rand8() % 35) + 5) / 10.0f;
    work->unk00[2] = ((u8)(rand8() % 35) + 5) / 10.0f;
}

/* Track object type 5 (spinning star): follow the track and spin. */
void func_8010B04C_cosmic_coaster(omObjData *object) {
    CcCar *car;
    CcSpin *work;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    work = object->data;
    object->rot.x += work->unk00[0];
    object->rot.y += work->unk00[1];
    object->rot.z += work->unk00[2];
    if (object->rot.x >= 360.0f) {
        object->rot.x -= 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.z >= 360.0f) {
        object->rot.z -= 360.0f;
    }
    /* Retail passes trans.z as the z rotation. */
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->trans.z);
    if (car->unk08 - object->trans.z >= 3300.0f) {
        func_8001ACDC_main(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

/* Init of track object type 6 (goal gate). */
void func_8010B1DC_cosmic_coaster(omObjData *object) {
    CcGate *work;

    work = object->data = HuMemAllocTag(0x10, 0x7918);
    work->unk00 = 0.0f;
    work->unk04 = -5.0f;
    work->unk08 = 400.0f;
    work->unk0C = -5.0f;
}

/* Track object type 6 (goal gate): the winner's flag sways, the loser's flag drops. */
void func_8010B234_cosmic_coaster(omObjData *object) {
    CcCar *car;
    CcGate *work;
    omObjData *loser;

    car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->unk08 - object->trans.z);
    CC_LIGHT_DIST(object) = 0.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 400.0f, car->unk08 - object->trans.z - 1185.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y + 400.0f, car->unk08 - object->trans.z - 1185.0f);
    work = object->data;
    if (D_8010C3BC_cosmic_coaster != -1 && D_8010C3BC_cosmic_coaster == object->work[2]) {
        func_8001C258_main(object->model[1], 4, 4);
        func_8001C258_main(object->model[2], 4, 0);
        work->unk00 += 8.0f;
        if (work->unk00 >= 360.0f) {
            work->unk00 -= 360.0f;
        }
        Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, sindf(work->unk00) * 45.0f);
        func_8001FBBC_main(object->model[0], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[0], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[1], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[1], 69.0f, 69.0f, 69.0f);
        func_8001FBBC_main(object->model[2], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[2], 69.0f, 69.0f, 69.0f);
    }
    loser = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster ^ 1];
    if (D_8010C3BC_cosmic_coaster != -1 && loser->work[0] != 0 && (D_8010C3BC_cosmic_coaster ^ 1) == object->work[2]) {
        if (loser->work[1] != 0) {
            loser->work[1]--;
        } else {
            work->unk08 += work->unk0C;
            work->unk0C *= 1.45f;
            work->unk00 += 8.0f;
            if (work->unk08 <= 270.0f) {
                work->unk08 = 270.0f;
            }
            if (work->unk00 > 40.0f) {
                work->unk00 = 40.0f;
            }
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + work->unk08, car->unk08 - object->trans.z - 1185.0f);
            Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, work->unk00);
        }
    }
}

/* A track object is gone: no CPU rider may keep dodging it (retail clears every target). */
void func_8010B5C4_cosmic_coaster(omObjData *object) {
    CcCar *car;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        car = D_8010C3B0_cosmic_coaster[i]->data;
        for (j = 0; j < 2; j++) {
            if (car->unk44[j] == object) {
                car->unk44[j] = NULL;
            }
            car->unk3C[j] = 100000.0f;
            car->unk4C[j] = 0;
        }
    }
}

/* Riders' boxes against this side's track objects (types 0, 1, 4): result per rider in a half. */
#ifdef NON_MATCHING
u32 func_8010B644_cosmic_coaster(omObjData **hit, CcCar *car, f32 pos, f32 prev, u16 take) {
    u16 res[2];
    Vec bmin;
    Vec bmax;
    Vec rmin[2];
    Vec rmax[2];
    u16 mode;
    omObjData **objs;
    omObjData *o;
    s32 i;
    s32 j;

    mode = take;
    objs = func_80047DBC_main(car->unk00);
    rmin[0].x = car->unk10[0] - 30.0f;
    rmin[0].y = 225.0f;
    rmin[0].z = pos + 130.0f;
    rmax[0].x = car->unk10[0] + 30.0f;
    rmax[0].y = 125.0f;
    rmax[0].z = prev - -100.0f + 30.0f;
    rmin[1].x = car->unk10[1] - 30.0f;
    rmin[1].y = 225.0f;
    rmin[1].z = pos + -130.0f;
    rmax[1].x = car->unk10[1] + 30.0f;
    rmax[1].y = 125.0f;
    rmax[1].z = prev - 100.0f - 30.0f;
    res[1] = 0xFFFF;
    res[0] = 0xFFFF;
    for (i = 0; i < 0x37; i++) {
        o = objs[i];
        if (o != NULL && (o->work[1] < 2 || o->work[1] == 4)) {
            if (o->work[1] == 1) {
                bmin.x = o->trans.x - 150.0f;
                bmin.y = o->trans.y - 100.0f;
                bmin.z = o->trans.z;
                bmax.x = o->trans.x + 150.0f;
            } else if (o->work[1] == 0 || o->work[1] == 4) {
                bmin.x = o->trans.x - 70.0f;
                bmin.y = o->trans.y - 100.0f;
                bmin.z = o->trans.z;
                bmax.x = o->trans.x + 70.0f;
            }
            bmax.y = o->trans.y + 100.0f;
            bmax.z = o->trans.z;
            for (j = 0; j < 2; j++) {
                if (res[j] == 0xFFFF) {
                    if (bmin.z <= rmin[j].z && rmax[j].z <= bmin.z && rmin[j].x < bmax.x && bmin.x < rmax[j].x) {
                        hit[j] = o;
                        res[j] = (u16)o->work[1];
                        if (mode == 1) {
                            func_80047E90_main(o, 1);
                        }
                    }
                }
            }
        }
    }
    return (res[1] << 16) | res[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B644_cosmic_coaster);
#endif

/* Lanes blocked at obj's distance: per lane (left, middle, right) 2 bits, 0x30/0xC/0x3. */
// decomp-permuter
s32 func_8010B97C_cosmic_coaster(omObjData *object, s32 rider, omObjData *obj)
{
  omObjData *new_var;
  omObjData **objs;
  omObjData *o;
  s32 bits;
  s32 i;
  bits = 0;
  if (obj == 0)
  {
    return 0;
  }
  objs = func_80047DBC_main(((CcCar *) object->data)->unk00);
  for (i = 0; i < 0x37; i++)
  {
    o = objs[i];
    if (((o != 0) && (((new_var = o)->work[1] < 2) || (new_var->work[1] == 4))) && (new_var->trans.z == obj->trans.z))
    {
      switch (new_var->work[1])
      {
        case 0:
          if (new_var->trans.x < 0.0f)
        {
          bits |= 0x20;
        }
          if (new_var->trans.x == 0.0f)
        {
          bits |= 8;
        }
          if (new_var->trans.x > 0.0f)
        {
          bits |= 2;
        }
          break;

        case 1:
          if (new_var->trans.x < 0.0f)
        {
          bits |= 0x28;
        }
          if (new_var->trans.x > 0.0f)
        {
          bits |= 0xA;
        }
          break;

        case 4:
          if (new_var->trans.x < 0.0f)
        {
          bits |= 0x10;
        }
          if (new_var->trans.x == 0.0f)
        {
          bits |= 4;
        }
          if (new_var->trans.x > 0.0f)
        {
          bits |= 1;
        }
          break;

      }

    }
  }

  return bits;
}
