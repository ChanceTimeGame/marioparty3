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
    /* 0x28 */ s16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ f32 unk2C[2]; /* per rider: rot y */
    /* 0x34 */ f32 unk34[2]; /* per rider: y */
    /* 0x3C */ f32 unk3C[2];
    /* 0x44 */ f32 unk44[2];
    /* 0x4C */ s16 unk4C[2];
    /* 0x50 */ s16 unk50; /* a human rides this car */
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
extern s16 D_8010BB58_cosmic_coaster[2];
extern s8 D_800CBB6E_main[];
extern s32 D_800A178C_main[][6];
extern omObjData *D_8010C050_cosmic_coaster;
extern s32 D_8010C054_cosmic_coaster;
extern s16 D_8010C058_cosmic_coaster;
extern s16 D_8010C05A_cosmic_coaster;
extern omObjData *D_8010C3B0_cosmic_coaster[2];
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
void func_8010812C_cosmic_coaster(omObjData *object);
void func_801083D0_cosmic_coaster(omObjData *object, s16 rider, s8 *stick);
void func_80108C9C_cosmic_coaster(omObjData *object);
u32 func_8010B644_cosmic_coaster(omObjData **hit, CcCar *car, f32 pos, f32 prev, u16 take);
void func_8010869C_cosmic_coaster(omObjData *object);
void func_801090C0_cosmic_coaster(omObjData *object);
void func_80109900_cosmic_coaster(void);
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
#ifdef NON_MATCHING
void func_80106530_cosmic_coaster(s16 side) {
    CcTrack *work;
    s32 slot;
    s32 count;
    s32 i;

    work = D_8010C3C0_cosmic_coaster->data;
    slot = work->unk16[side];
    count = work->unk24[side];
    for (i = 0; i < 4; i++) {
        count++;
        Hu3DModelPosSet(D_8010C3C0_cosmic_coaster->model[side * 4 + slot], 0.0f, 0.0f, work->unk1C[side] - i * 3000.0f);
        if (count >= 0x17) {
            func_8001C258_main(D_8010C3C0_cosmic_coaster->model[side * 4 + slot], 4, 4);
        } else {
            func_8001C258_main(D_8010C3C0_cosmic_coaster->model[side * 4 + slot], 4, 0);
        }
        slot++;
        if (slot >= 4) {
            slot -= 4;
        }
    }
    if (work->unk1C[side] >= 6300.0f) {
        work->unk1C[side] -= 3000.0f;
        if (++work->unk16[side] >= 4) {
            work->unk16[side] -= 4;
        }
        work->unk24[side]++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106530_cosmic_coaster);
#endif

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
        work->unk44[i] = 0.0f;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80107888_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010803C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801080C8_cosmic_coaster);

void func_80108124_cosmic_coaster(omObjData *object) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010812C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801083D0_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010869C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80108C9C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801090C0_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010923C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109290_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801096A8_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109900_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010991C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109A38_cosmic_coaster);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", D_8010BFE4_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109BFC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A244_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A434_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A528_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A744_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A838_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010ABE0_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010AF04_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B04C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B1DC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B234_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B5C4_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B644_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B97C_cosmic_coaster);
