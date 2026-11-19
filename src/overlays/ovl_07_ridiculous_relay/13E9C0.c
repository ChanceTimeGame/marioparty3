#include "common.h"
#include "overlays/minigame.h"
#include "game/pause.h"

/* A relay runner's player (D_80111940[], filled by func_80105D40_ridiculous_relay). */
typedef struct {
    /* 0x00 */ s8 unk0; /* player index */
    /* 0x01 */ u8 unk1; /* group (leg) */
    /* 0x02 */ s8 unk2; /* pad */
    /* 0x03 */ u8 unk3; /* character */
    /* 0x04 */ s8 unk4; /* CPU difficulty, -1 human */
    /* 0x05 */ char unk5[3];
    /* 0x08 */ s32 unk8; /* message */
} RrPlayer; // Size 0xC

void func_8004AE00_main(s16, s16);
extern s16 D_801119E0_ridiculous_relay[31];
extern u16 D_80111A40_ridiculous_relay[8];
extern s16 D_80111A58_ridiculous_relay[31];
void func_80106D28_ridiculous_relay(omObjData *obj);
extern s32 D_80111A30_ridiculous_relay[3];
void func_80105F48_ridiculous_relay(omObjData *obj);
void func_80108DE8_ridiculous_relay(Gfx **gfx, s32 arg1, s32 arg2);
void func_8000B5F0_main(u8 arg0);
void func_8000B710_main(s32);
void func_800142A0_main(s32);
void func_80105D40_ridiculous_relay(omObjData *obj);
void func_801066A0_ridiculous_relay(omObjData *obj);
void func_8010AE4C_ridiculous_relay(omObjData *obj);
void func_8010AE80_ridiculous_relay(omObjData *obj);
void func_8010AEAC_ridiculous_relay(omObjData *obj);
void func_8010AED8_ridiculous_relay(omObjData *obj);
extern D_80111B50_vine_with_me_Struct D_80110CB0_ridiculous_relay;
extern const s16 D_80110E60_ridiculous_relay[];

/* Main sprite-model slot (D_800CBB60_main; 14EA0.c's, copied as the awful_tower overlay does). */
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8* unk20;
} RrSprModel; /* size 0x24 */

extern RrSprModel *D_800CBB60_main;
extern u16 D_800A1902_main;
s16 func_800329B4_main(void *);
void func_80012B14_main(s16 camIndex, Vec *worldPos, Vec2f *outPos);
void func_80106D4C_ridiculous_relay(omObjData *obj);
void func_8010AF04_ridiculous_relay(omObjData *obj, s8 idx);
void func_8010B4A8_ridiculous_relay(omObjData *);
f32 func_8010B474_ridiculous_relay(f32);
s16 func_80110BF4_ridiculous_relay(s16, s16);
s16 func_80110C3C_ridiculous_relay(s16, s16);

extern u32 D_80110D6C_ridiculous_relay; /* frame counter */
extern u32 D_80110D70_ridiculous_relay; /* runner 1 finish state */
extern u32 D_80110D74_ridiculous_relay; /* runner 4 finish state */
extern u8 D_80110D78_ridiculous_relay;  /* current leg */
extern u16 D_80110D7C_ridiculous_relay[18]; /* hurdle knocked timers */
extern f32 D_80110DA0_ridiculous_relay[2]; /* last frame's camera x */
extern u16 D_80110DA8_ridiculous_relay;
extern f32 D_80110DAC_ridiculous_relay[4]; /* runner x */
extern f32 D_80110DBC_ridiculous_relay[4]; /* runner 1 y */
extern f32 D_80110DCC_ridiculous_relay[4]; /* runner speed */
extern f32 D_80110DDC_ridiculous_relay;
extern s16 D_80110DEE_ridiculous_relay;
extern s16 D_80110DF0_ridiculous_relay;
extern s16 D_80110DF2_ridiculous_relay;
extern s16 D_80110DF4_ridiculous_relay[2];
extern s16 D_80110DF8_ridiculous_relay[2];
extern u32 D_80110DFC_ridiculous_relay[2];
extern u8 D_80110E04_ridiculous_relay;
extern f32 D_80110E08_ridiculous_relay;
extern u8 D_80110E0C_ridiculous_relay[4];
extern u8 D_80110E10_ridiculous_relay[4];
extern f32 D_80110E14_ridiculous_relay;
extern u8 D_80110E18_ridiculous_relay;
extern f32 D_80110E1C_ridiculous_relay;
extern f32 D_80110E20_ridiculous_relay[2];
extern f32 D_80110E28_ridiculous_relay[2];
extern f32 D_80110E30_ridiculous_relay[2];
extern u16 D_80110E38_ridiculous_relay[2];
extern u8 D_80110E3C_ridiculous_relay[4];
extern u32 D_80110E40_ridiculous_relay;
extern u32 D_80110E44_ridiculous_relay;
extern u32 D_80110E48_ridiculous_relay;
extern u32 D_80110E4C_ridiculous_relay;
extern u8 D_80110E50_ridiculous_relay;
extern f32 D_80110E54_ridiculous_relay;

extern f32 D_801117F0_ridiculous_relay;
extern f32 D_801117F8_ridiculous_relay[18];
extern f32 D_80111840_ridiculous_relay[18];
extern f32 D_80111888_ridiculous_relay[18];
extern f32 D_801118D0_ridiculous_relay[18];
extern f32 D_80111918_ridiculous_relay;
extern f32 D_8011191C_ridiculous_relay;
extern f32 D_80111920_ridiculous_relay;
extern f32 D_80111924_ridiculous_relay;
extern f32 D_80111928_ridiculous_relay;
extern f32 D_8011192C_ridiculous_relay;
extern f32 D_80111930_ridiculous_relay;
extern f32 D_80111934_ridiculous_relay;
extern f32 D_80111938_ridiculous_relay;
extern f32 D_8011193C_ridiculous_relay;
extern RrPlayer D_80111940_ridiculous_relay[4];
extern RrPlayer *D_80111970_ridiculous_relay[4];
extern f32 D_80111980_ridiculous_relay[7];
extern f32 D_80111998_ridiculous_relay;
extern f32 D_8011199C_ridiculous_relay[2];
extern f32 D_801119A8_ridiculous_relay[4];
extern u8 D_801119B8_ridiculous_relay[4];
extern omObjData *D_801119BC_ridiculous_relay;
extern s8 D_801119C0_ridiculous_relay;
extern f32 D_801119C4_ridiculous_relay;
extern s32 D_801119C8_ridiculous_relay;
extern u16 D_801119CC_ridiculous_relay;
extern f32 D_801119D0_ridiculous_relay;
extern s32 D_801119D4_ridiculous_relay;
extern s16 D_801119D8_ridiculous_relay;
extern u8 D_801119DA_ridiculous_relay;
extern f32 D_801119DC_ridiculous_relay;
extern omObjData *D_80111A20_ridiculous_relay[4];
extern f32 D_80111A50_ridiculous_relay;

#define RR_K 0.028935185185185185
#define RR_GROUND ((D_801119DC_ridiculous_relay * 100.0f) * 0.125 + -25.0)

#ifdef NON_MATCHING
void func_801059A0_ridiculous_relay(void) {
    omObjData *obj;
    omObjData *view;

    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCamSetPerspective(0, 22.619865f, 375.0f, 1250.0f);
    Hu3DCamSetPerspective(1, 22.619865f, 375.0f, 1250.0f);
    HmfLightMaxSet(1);
    HmfLightDirSet(0, 0.0f, 0.0f, 90.0f);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(1, 0.0f, 40.0f, 110.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 468.75f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 468.75f;
    omAddObj(0, 0, 0, -1, func_80105D40_ridiculous_relay);
    D_801119BC_ridiculous_relay = obj = omAddObj(8, 35, 35, -1, func_801066A0_ridiculous_relay);
    omSetStatBit(obj, 0xA0);
    D_80111A20_ridiculous_relay[0] = omAddObj(3, 3, 12, -1, func_8010AE4C_ridiculous_relay);
    D_80111A20_ridiculous_relay[1] = omAddObj(3, 3, 12, -1, func_8010AE80_ridiculous_relay);
    D_80111A20_ridiculous_relay[2] = omAddObj(3, 3, 12, -1, func_8010AEAC_ridiculous_relay);
    D_80111A20_ridiculous_relay[3] = omAddObj(3, 3, 12, -1, func_8010AED8_ridiculous_relay);
    view = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    view->work[0] = 2;
    omSetStatBit(view, 0xA0);
    func_80045010_main(D_80110E60_ridiculous_relay, 1);
    WipeCreateIn(0xFF, 0x10);
    D_80110CB0_ridiculous_relay.unk01 = 2;
    D_80110CB0_ridiculous_relay.unk1C = 45;
    D_80110CB0_ridiculous_relay.unk1E = 9000;
    D_80110CB0_ridiculous_relay.unk03 = 0;
    D_80110CB0_ridiculous_relay.unk02 = 1;
    D_80110CB0_ridiculous_relay.unk22 = 45;
    D_80110CB0_ridiculous_relay.unk24 = 165;
    D_80110CB0_ridiculous_relay.unk04 = 0;
    D_80110CB0_ridiculous_relay.unk05 = 0;
    D_80110CB0_ridiculous_relay.unk20 = -1;
    func_800E5EA0_minigame(&D_80110CB0_ridiculous_relay);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_801059A0_ridiculous_relay);
#endif

void func_80105D40_ridiculous_relay(omObjData *obj) {
    s32 i;

    D_801119CC_ridiculous_relay = 0;
    D_801119D8_ridiculous_relay = 0;
    D_801119D4_ridiculous_relay = 0;
    D_801119C8_ridiculous_relay = 0;
    D_801119C0_ridiculous_relay = 5;
    D_801119DA_ridiculous_relay = 0;
    D_801119D0_ridiculous_relay = D_801119DC_ridiculous_relay = D_80111A50_ridiculous_relay = D_801119C4_ridiculous_relay = D_8011199C_ridiculous_relay[0] = D_8011199C_ridiculous_relay[1] = 0.0f;
    D_801119A8_ridiculous_relay[0] = D_801119A8_ridiculous_relay[1] = D_801119A8_ridiculous_relay[2] = D_801119A8_ridiculous_relay[3] = 0.0f;
    D_80111980_ridiculous_relay[0] = D_80111980_ridiculous_relay[1] = D_80111980_ridiculous_relay[2] = D_80111980_ridiculous_relay[3] = D_80111980_ridiculous_relay[4] = D_80111980_ridiculous_relay[5] = D_80111980_ridiculous_relay[6] = 0.0f;
    D_80111A30_ridiculous_relay[0] = D_80111A30_ridiculous_relay[1] = D_80111A30_ridiculous_relay[2] = -1;
    for (i = 0; i < 4; i++) {
        D_80111970_ridiculous_relay[i] = &D_80111940_ridiculous_relay[i];
        bzero(D_80111970_ridiculous_relay[i], sizeof(RrPlayer));
    }
    for (i = 0; i < 4; i++) {
        u8 group = GwPlayer[i].group;

        D_801119B8_ridiculous_relay[i] = group;
        D_80111970_ridiculous_relay[group]->unk0 = i;
        D_80111970_ridiculous_relay[group]->unk2 = GwPlayer[i].pad;
        D_80111970_ridiculous_relay[group]->unk3 = GwPlayer[i].chr;
        D_80111970_ridiculous_relay[group]->unk1 = group;
        D_80111970_ridiculous_relay[group]->unk4 = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    func_8001AC8C_main(0, func_80108DE8_ridiculous_relay, 2);
    obj->func = func_80105F48_ridiculous_relay;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110E60_ridiculous_relay);

void func_80105F48_ridiculous_relay(omObjData *obj) {
    s32 i;
    u8 j;
    s8 last;

    D_801119D4_ridiculous_relay++;
    D_801119C8_ridiculous_relay++;
    if (D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay == 31 && D_801119CC_ridiculous_relay == 0 && D_800D530C_main == 0) {
        HuAudSeqPlay(0x32);
    }
    func_800E6F40_minigame();
    switch (D_801119D8_ridiculous_relay) {
        case 0:
            if (D_801119D4_ridiculous_relay == 1 && D_801119CC_ridiculous_relay == 0 && D_800D530C_main == 0) {
                D_80111A30_ridiculous_relay[0] = HuAudFXPlay(0x32D);
                D_80111A30_ridiculous_relay[1] = HuAudFXPlay(0x32E);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_801119D8_ridiculous_relay = 1;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 1:
            if (func_800E6E8C_minigame() == 2) {
                D_801119D8_ridiculous_relay = 2;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 2:
            last = D_801119C0_ridiculous_relay;
            if (last == 5) {
                if (func_800E6E8C_minigame() == 3) {
                    if (D_801119C0_ridiculous_relay == last) {
                        D_801119D8_ridiculous_relay = 5;
                        D_801119C0_ridiculous_relay = 4;
                    } else {
                        D_801119D8_ridiculous_relay = 3;
                    }
                    D_801119D4_ridiculous_relay = 0;
                }
            } else {
                D_801119D8_ridiculous_relay = 3;
                D_801119D4_ridiculous_relay = 0;
            }
            if (D_801119D8_ridiculous_relay != 3) {
                break;
            }
            /* fallthrough */
        case 3:
            if (D_801119D4_ridiculous_relay == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                if (D_80111A30_ridiculous_relay[2] != -1) {
                    HuAudFXStop((s16)D_80111A30_ridiculous_relay[2]);
                    D_80111A30_ridiculous_relay[2] = -1;
                }
                if (D_801119C0_ridiculous_relay == 0) {
                    D_80110CB0_ridiculous_relay.unk06 = 0;
                    D_80110CB0_ridiculous_relay.unk18 = D_80111970_ridiculous_relay[0]->unk0;
                    GwPlayer[D_80111970_ridiculous_relay[0]->unk0].bonusCoin = 10;
                } else {
                    D_80110CB0_ridiculous_relay.unk06 = 2;
                    D_80110CB0_ridiculous_relay.unk18 = D_80111970_ridiculous_relay[3]->unk0;
                    D_80110CB0_ridiculous_relay.unk19[0] = D_80111970_ridiculous_relay[1]->unk0;
                    D_80110CB0_ridiculous_relay.unk19[1] = D_80111970_ridiculous_relay[2]->unk0;
                    GwPlayer[D_80111970_ridiculous_relay[1]->unk0].bonusCoin = 10;
                    GwPlayer[D_80111970_ridiculous_relay[2]->unk0].bonusCoin = 10;
                    GwPlayer[D_80111970_ridiculous_relay[3]->unk0].bonusCoin = 10;
                }
            }
            if (D_801119D4_ridiculous_relay == 2) {
                func_800E6F34_minigame(30);
            }
            if (D_801119D4_ridiculous_relay == 15) {
                for (i = 0; i < 3; i++) {
                    if (D_80111A30_ridiculous_relay[i] != -1) {
                        func_8004AEF0_main(D_80111A30_ridiculous_relay[i], 15);
                        D_80111A30_ridiculous_relay[i] = -1;
                    }
                }
            }
            if (func_800E6E8C_minigame() == 4) {
                D_801119D8_ridiculous_relay = 4;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 5:
            if (D_801119D4_ridiculous_relay == 1) {
                D_80110CB0_ridiculous_relay.unk06 = 4;
                D_80110CB0_ridiculous_relay.unk22 = 75;
                D_80110CB0_ridiculous_relay.unk24 = 144;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_801119D8_ridiculous_relay = 6;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 4:
            if (D_801119D4_ridiculous_relay == 30) {
                if (D_801119C0_ridiculous_relay == 0) {
                    func_8001C5B4_main(D_80111A20_ridiculous_relay[0]->model[0], D_80111A20_ridiculous_relay[0]->motion[3]);
                    func_8001C814_main(D_80111A20_ridiculous_relay[0]->model[0], 3, 0);
                    func_80045ED0_main(D_80111970_ridiculous_relay[0]->unk8);
                } else if (D_801119C0_ridiculous_relay == 1) {
                    func_8001C5B4_main(D_80111A20_ridiculous_relay[3]->model[0], D_80111A20_ridiculous_relay[3]->motion[3]);
                    func_8001C814_main(D_80111A20_ridiculous_relay[3]->model[0], 3, 0);
                    func_80045ED0_main(D_80111970_ridiculous_relay[3]->unk8);
                }
            }
            /* fallthrough */
        case 6:
            if (func_800E6E8C_minigame() == 5) {
                D_801119D8_ridiculous_relay = 7;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 7:
            if (D_801119D4_ridiculous_relay == 1) {
                WipeCreateOut(0, 20);
            } else if (D_801119D4_ridiculous_relay >= 32) {
                D_801119CC_ridiculous_relay = 1;
            }
            break;
    }
    if (_CheckFlag(0xF) && D_800D530C_main == 0 && D_801119DA_ridiculous_relay == 0 && D_801119D8_ridiculous_relay == 2U) {
        for (j = 0; j < 2; j++) {
            if (D_80111970_ridiculous_relay[j]->unk4 == -1 && (D_800D5558_main[D_80111970_ridiculous_relay[j]->unk2] & 0x10)) {
                D_801119DA_ridiculous_relay = 1;
            }
        }
    }
    if (D_801119CC_ridiculous_relay == 0 && D_800D530C_main == 0 && D_801119DA_ridiculous_relay == 0) {
        return;
    }
    if (D_800D530C_main != 0 && D_801119DA_ridiculous_relay == 0) {
        D_801119DA_ridiculous_relay = 1;
    }
    if (D_801119DA_ridiculous_relay != 0) {
        if (D_801119DA_ridiculous_relay == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(20);
            func_8004AB0C_main(20);
        }
        D_801119DA_ridiculous_relay++;
        if (D_801119DA_ridiculous_relay < 25) {
            return;
        }
    }
    HuAudSeqFadeOut(30);
    omOvlReturnEx(1);
}

s16 func_80106610_ridiculous_relay(s32 file, u16 *spr, u16 mdl) {
    void *data;
    s16 sprite;
    u16 idx;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    *spr = idx = HmfSprModelCreate((void *)-1, mdl, 0);
    D_800CBB60_main[idx].unk02 = sprite;
    return D_800CBB60_main[idx].unk00;
}

void func_801066A0_ridiculous_relay(omObjData *obj) {
    s32 files[31] = {
        0x0028001B, 0x0028001C, 0x0028001E, 0x0028001F, 0x00280020, 0x0028001D, 0x00280021, 0x00280022,
        0x00280023, 0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E,
        0x0021000F, 0x00280029, 0x00280024, 0x00280025, 0x00280026, 0x00280027, 0x00280028, 0x00280013,
        0x00280014, 0x00280015, 0x00280016, 0x00280017, 0x00280018, 0x00280019, 0x0028001A,
    };
    s16 i;

    for (i = 0; i < 31; i++) {
        D_801119E0_ridiculous_relay[i] = func_8000B838_main(files[i]);
        D_80111A58_ridiculous_relay[i] = InitEspriteSlot(D_801119E0_ridiculous_relay[i], 0, 0);
        func_8000BB94_main(D_80111A58_ridiculous_relay[i]);
    }
    obj->model[0] = func_8000B108_main(0xA00E7, 0x4B9);
    omSetSca(obj, 0.3125f, 0.3125f, 0.3125f);
    func_8001C8A8_main(obj->model[0], 2);
    obj->model[2] = func_8000B108_main(0x28000E, 0x39);
    Hu3DModelPosSet(obj->model[2], 3787.5f, -26.25f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 0.125f, 0.125f, 0.125f);
    func_8001C8A8_main(obj->model[2], 1);
    obj->model[3] = func_8000B108_main(0x28000F, 0x4B9);
    Hu3DModelPosSet(obj->model[3], 3787.5f, -31.25f, 0.0f);
    Hu3DModelScaleSet(obj->model[3], 0.125f, 0.125f, 0.125f);
    func_8001C8A8_main(obj->model[3], 2);
    obj->model[1] = func_8000B108_main(0x280010, 0x4B9);
    Hu3DModelScaleSet(obj->model[1], 0.125f, 0.125f, 0.125f);
    func_8001C8A8_main(obj->model[1], 2);
    for (i = 0; i < 5; i++) {
        obj->model[12 + i] = func_80106610_ridiculous_relay(0x280011, &D_80111A40_ridiculous_relay[i], 0x639);
        func_8001C8A8_main(obj->model[12 + i], 1);
        Hu3DModelScaleSet(obj->model[12 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    for (i = 0; i < 2; i++) {
        obj->model[10 + i] = func_80106610_ridiculous_relay(0x280012, &D_80111A40_ridiculous_relay[5], 0x639);
        func_8001C8A8_main(obj->model[10 + i], 1);
        Hu3DModelScaleSet(obj->model[10 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    obj->model[4] = func_80106610_ridiculous_relay(0xB, &D_80111A40_ridiculous_relay[7], 0x639);
    func_8001C258_main(obj->model[4], 4, 4);
    Hu3DModelScaleSet(obj->model[4], 1.6549804f, 0.9457031f, 0.9457031f);
    func_8001C8A8_main(obj->model[4], 1);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            obj->model[17] = func_8000B108_main(0x280006, 0x4B9);
        } else {
            obj->model[17 + i] = Hu3DModelLink(obj->model[17]);
        }
        func_8001C258_main(obj->model[17 + i], 4, 4);
        func_8001C2FC_main(obj->model[17 + i], 0x70000000, 0x70000000);
        Hu3DModelScaleSet(obj->model[17 + i], 0.15625f, 0.15625f, 0.15625f);
        func_8001C8A8_main(obj->model[17 + i], 2);
    }
    obj->model[6] = func_8000B108_main(0x28000C, 0x4B9);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C814_main(obj->model[6], 2, 2);
    Hu3DModelScaleSet(obj->model[6], 0.15625f, 0.15625f, 0.15625f);
    func_8001C8A8_main(obj->model[6], 2);
    obj->model[7] = func_8000B108_main(0x28000D, 0x4B9);
    func_8001C258_main(obj->model[7], 4, 4);
    Hu3DModelScaleSet(obj->model[7], 0.15625f, 0.15625f, 0.15625f);
    func_8001C8A8_main(obj->model[7], 2);
    obj->model[8] = Hu3DModelLink(obj->model[7]);
    func_8001C258_main(obj->model[8], 4, 4);
    Hu3DModelScaleSet(obj->model[8], 0.15625f, 0.15625f, 0.15625f);
    func_8001C8A8_main(obj->model[8], 2);
    func_8001C814_main(obj->model[8], 2, 2);
    obj->model[9] = func_8000B108_main(0x28000D, 0x839);
    func_8001C258_main(obj->model[9], 4, 4);
    Hu3DModelScaleSet(obj->model[9], 0.15625f, 0.15625f, 0.15625f);
    func_8001C8A8_main(obj->model[9], 2);
    func_8001C814_main(obj->model[9], 2, 2);
    obj->model[5] = func_8000B108_main(0x370003, 0x82D);
    func_8001FA68_main(obj->model[5]);
    func_8001C8A8_main(obj->model[5], 1);
    Hu3DModelScaleSet(obj->model[5], 0.125f, 0.125f, 0.125f);
    obj->func = func_80106D28_ridiculous_relay;
}

void func_80106D28_ridiculous_relay(omObjData *obj) {
    func_80106D4C_ridiculous_relay(obj);
    func_80049F98_main();
}


INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F34_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F40_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F7C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F84_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F8C_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106D4C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FA8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FC8_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80108DE8_ridiculous_relay);

void func_8010AE4C_ridiculous_relay(omObjData *obj) {
    func_8010AF04_ridiculous_relay(obj, 0);
    obj->func = func_8010B4A8_ridiculous_relay;
}

void func_8010AE80_ridiculous_relay(omObjData *obj) {
    func_8010AF04_ridiculous_relay(obj, 1);
    obj->func = NULL;
}

void func_8010AEAC_ridiculous_relay(omObjData *obj) {
    func_8010AF04_ridiculous_relay(obj, 2);
    obj->func = NULL;
}

void func_8010AED8_ridiculous_relay(omObjData *obj) {
    func_8010AF04_ridiculous_relay(obj, 3);
    obj->func = NULL;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111030_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111050_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111070_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AF04_ridiculous_relay);

f32 func_8010B474_ridiculous_relay(f32 x) {
    Vec pos;
    Vec2f out;

    pos.x = x;
    pos.y = 0.0f;
    pos.z = 0.0f;
    func_80012B14_main(1, &pos, &out);
    return out.x;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011108C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801110D4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011111C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111164_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111178_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111184_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111194_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111A4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111B4_ridiculous_relay);

#ifdef NON_MATCHING
void func_8010B4A8_ridiculous_relay(omObjData *arg0) {
    f32 xs[18] = { 0.0f, 32.0f, 64.0f, 96.0f, 128.0f, 128.0f, 160.0f, 192.0f, 224.0f,
                   256.0f, 288.0f, 320.0f, 352.0f, 384.0f, 384.0f, 416.0f, 448.0f, 480.0f };
    f32 lanes[18] = { 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f,
                      1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
    f32 hx[5];
    f32 hy[5];
    u8 hidx[5];
    f32 cam[2] = { CenterM[0].x, CenterM[1].x };
    s16 cpuTbl[3][3][4] = {
        { { 4, 3, 3, 2 }, { 12, 10, 9, 8 }, { 3, 2, 2, 2 } },
        { { 2, 3, 2, 2 }, { 6, 7, 6, 6 }, { 3, 5, 4, 3 } },
        { { 0, 0, 0, 0 }, { 10, 15, 30, 40 }, { 0, 0, 0, 0 } },
    };
    f32 bob[5] = { 0.0f, 27.0f, 54.0f, 81.0f, 54.0f };
    f32 wave[3];
    s32 n;
    s32 i;
    s32 j;
    u8 mode;
    omObjData *obj;
    RrPlayer *pl;
    f32 sx;
    f32 sy;
    f32 vx;
    f32 rot;
    f32 step;
    f32 cx;
    s32 s;
    u32 t;
    f32 y;

    n = 0;
    if ((D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay >= 63) || D_801119D8_ridiculous_relay == 2) {
        mode = 1;
    } else if ((D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay < 63) || D_801119D8_ridiculous_relay == 0) {
        mode = 2;
    } else {
        mode = 0;
    }
    for (i = 0; i < 7; i++) {
        D_80111980_ridiculous_relay[i] = 0.0f;
    }
    D_801119D0_ridiculous_relay = (D_80110D6C_ridiculous_relay % 1200) / 1200.0 * 20.0;
    D_801119DC_ridiculous_relay = sindf(D_80110D6C_ridiculous_relay * 4) * 0.2;
    wave[0] = sindf((D_80110D6C_ridiculous_relay % 60) * 6) * 20.0f;
    wave[1] = sindf((D_80110D6C_ridiculous_relay % 60) * 6 + 120) * 20.0f;
    wave[2] = sindf((D_80110D6C_ridiculous_relay % 60) * 6 + 240) * 20.0f;

    /* hurdles in view */
    for (i = 0; i < 18; i++) {
        f32 x = 2.0 * (xs[i] + 60.0f) * 100.0 / 4.0 * 0.125;

        if (CenterM[0].x - 137.5 < x && x < CenterM[0].x + 137.5) {
            if (n >= 5) {
                break;
            }
            hidx[n] = i;
            hx[n] = x;
            hy[n] = (lanes[i] * 200.0 + wave[i % 3] + D_80110D7C_ridiculous_relay[i] * 10.5) * 0.125;
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[12 + n], hx[n], hy[n], -250.0f);
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[12 + n], hx[n], hy[n], 0.0f);
            func_8001C258_main(D_801119BC_ridiculous_relay->model[12 + n], 4, 0);
            n++;
        }
    }
    for (i = n; i < 5; i++) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[12 + i], 4, 4);
    }

    /* the two fireballs */
    for (j = 0; j < 2; j++) {
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f && D_80110E38_ridiculous_relay[j] != 0 && D_801119D8_ridiculous_relay == 2
            && D_80110DAC_ridiculous_relay[0] >= 50.0 && D_80110DAC_ridiculous_relay[0] < 1775.0) {
            D_80110E38_ridiculous_relay[j]--;
        }
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f && D_80110E38_ridiculous_relay[j] == 0 && D_801119D8_ridiculous_relay == 2
            && D_80110DAC_ridiculous_relay[0] >= 50.0 && D_80110DAC_ridiculous_relay[0] < 1775.0) {
            u8 k;

            D_80110E20_ridiculous_relay[j] = CenterM[0].x + 125.0;
            HuAudFXPlay(0x332);
            k = rand8() % 9;
            if (D_801119D8_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[D_80110D78_ridiculous_relay + 1] < D_80110DAC_ridiculous_relay[0]) {
                f32 gap[3] = { 16382.0f, 16382.0f, 16382.0f };
                f32 best = 0.0f;
                u8 start = rand8() % 3;
                s32 yi = D_80111A20_ridiculous_relay[0]->trans.y / 0.125 + 125.0;
                s32 lane;
                s32 bestLane;
                s32 m;

                if (yi >= 100) {
                    lane = 2;
                } else {
                    lane = yi >= -99;
                }
                for (m = 0; m < n; m++) {
                    s32 h = hidx[m];
                    s32 l = (s32)lanes[h] + 1;

                    if (D_80110D7C_ridiculous_relay[h] == 0 && D_80111A20_ridiculous_relay[0]->trans.x < hx[m] + 12.5) {
                        f32 d = (hx[m] + 100.0f) - D_80111A20_ridiculous_relay[0]->trans.x;

                        gap[l] = (d < gap[l]) ? d : gap[l];
                    }
                }
                bestLane = 0;
                for (m = 0; m < 3; m++) {
                    if (best < gap[(m + start) % 3] + ((lane == (m + start) % 3) ? 1.0f : 0.0f)) {
                        bestLane = (m + start) % 3;
                        best = gap[(m + start) % 3] + ((lane == (m + start) % 3) ? 1.0f : 0.0f);
                    }
                }
                if (gap[0] == 16382.0f && gap[1] == 16382.0f && gap[2] == 16382.0f) {
                    k = rand8() % 9;
                } else {
                    k = bestLane * 3 + rand8() % 3;
                }
            }
            D_80110E28_ridiculous_relay[j] = (((k % 3) - 1) * 5 + ((k / 3) - 1) * 25) * 8 * 0.125;
        }
        D_80110E20_ridiculous_relay[j] = D_80110E20_ridiculous_relay[j] - D_80110E30_ridiculous_relay[j] * RR_K;
        if (D_80110E20_ridiculous_relay[j] <= CenterM[0].x - 137.5 && D_80110E20_ridiculous_relay[j] > -1000.0f) {
            D_80110E20_ridiculous_relay[j] = -1000.0f;
            if (D_80110DAC_ridiculous_relay[0] < 250.0) {
                s = 20;
            } else if (D_80110DAC_ridiculous_relay[0] > 1250.0) {
                s = 0;
            } else {
                s = (1250.0 - D_80110DAC_ridiculous_relay[0]) / 1000.0 * 20.0;
            }
            D_80110E38_ridiculous_relay[j] = s;
        }
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f) {
            func_8001C258_main(D_801119BC_ridiculous_relay->model[10 + j], 4, 4);
        } else {
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[10 + j], D_80110E20_ridiculous_relay[j], D_80110E28_ridiculous_relay[j], 0.0f);
            func_8001C258_main(D_801119BC_ridiculous_relay->model[10 + j], 4, 0);
        }
    }

    /* runner 1: hurdles */
    obj = D_80111A20_ridiculous_relay[0];
    pl = D_80111970_ridiculous_relay[0];
    D_80110D70_ridiculous_relay += (D_80110D70_ridiculous_relay != 0 && D_80110D70_ridiculous_relay != 99
                                    && D_80110D70_ridiculous_relay != 199 && D_80110D70_ridiculous_relay != 299);
    if (D_80110D70_ridiculous_relay != 0 && D_80110D70_ridiculous_relay < 100 && D_80110DAC_ridiculous_relay[0] > 1900.0) {
        D_80110D70_ridiculous_relay = 100;
        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[4], obj->trans.x + 12.5, obj->trans.y - 3.125, obj->trans.z);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[4], 4, 0);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (D_80110D70_ridiculous_relay >= 100) {
        func_8001C258_main(obj->model[0], 4, 0);
        if (D_80110D70_ridiculous_relay == 100) {
            D_80111918_ridiculous_relay = obj->trans.x;
            D_8011191C_ridiculous_relay = obj->trans.y;
            D_80111924_ridiculous_relay = 0.0f;
            D_80111928_ridiculous_relay = 90.0f;
            D_80111920_ridiculous_relay = 2.0 * (D_80110DCC_ridiculous_relay[0] * RR_K);
            func_8001C5B4_main(obj->model[0], obj->motion[5]);
            func_8001C814_main(obj->model[0], 2, 0);
            func_8001C6A8_main(obj->model[0], 14.0f);
        }
        if (D_80110D70_ridiculous_relay == 203) {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
        }
        if (D_80110D70_ridiculous_relay < 200) {
            D_80111918_ridiculous_relay += D_80111920_ridiculous_relay;
            D_8011191C_ridiculous_relay += D_80111924_ridiculous_relay;
            D_80111924_ridiculous_relay -= 0.8125;
            if (D_8011191C_ridiculous_relay <= -20.0) {
                D_8011191C_ridiculous_relay = -20.0f;
                D_80110D70_ridiculous_relay = 200;
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[6]].unk02, 10, 4, 0);
            }
        } else if (D_80110D70_ridiculous_relay >= 215) {
            if (D_801119C0_ridiculous_relay == 0) {
                D_80111928_ridiculous_relay = (D_80111928_ridiculous_relay < -10.0f) ? (D_80111928_ridiculous_relay + 9.0f) - D_80111928_ridiculous_relay * 0.1
                                            : (D_80111928_ridiculous_relay > 10.0f) ? (D_80111928_ridiculous_relay - 9.0f) - D_80111928_ridiculous_relay * 0.1
                                            : 0.0f;
            } else if (D_80110D70_ridiculous_relay >= 215) {
                if (D_801119D8_ridiculous_relay == 4
                    && ((D_801119D4_ridiculous_relay >= 31 && D_801119D4_ridiculous_relay < 120 && D_80110D70_ridiculous_relay == 215)
                        || (D_801119D4_ridiculous_relay == 30 && D_801119D4_ridiculous_relay < 120 && D_80110D70_ridiculous_relay >= 215))) {
                    D_80110D70_ridiculous_relay = 300;
                    func_8001C5B4_main(obj->model[0], obj->motion[4]);
                    func_8001C814_main(obj->model[0], 3, 0);
                }
                if (D_80110D70_ridiculous_relay >= 300) {
                    D_80111928_ridiculous_relay = (D_80111928_ridiculous_relay < -10.0f) ? (D_80111928_ridiculous_relay + 9.0f) - D_80111928_ridiculous_relay * 0.1
                                                : (D_80111928_ridiculous_relay > 10.0f) ? (D_80111928_ridiculous_relay - 9.0f) - D_80111928_ridiculous_relay * 0.1
                                                : 0.0f;
                }
            }
        }
        omSetTra(obj, D_80111918_ridiculous_relay, D_8011191C_ridiculous_relay, 0.0f);
        omSetRot(obj, 0.0f, D_80111928_ridiculous_relay, 0.0f);
    } else {
        sx = (mode == 1 && pl->unk4 == -1) ? D_800CBB6E_main[pl->unk2] : 0.0f;
        sy = (mode == 1 && pl->unk4 == -1) ? D_800D20A1_main[pl->unk2] : 0.0f;
        if (D_80110D70_ridiculous_relay != 0) {
            vx = 0.0f;
            rot = 0.0f;
            if (D_80110DBC_ridiculous_relay[0] < -135.0f) {
                rot = 60.0f;
            }
        } else {
            if (mode == 1 && pl->unk4 != -1) {
                f32 target[4] = { 35.0f, 39.0f, 42.0f, 46.0f };
                f32 room[3] = { D_80110E08_ridiculous_relay, D_80110E08_ridiculous_relay, D_80110E08_ridiculous_relay };
                f32 best = 0.0f;
                s32 sp = target[pl->unk4];
                s32 bestLane;
                s32 m;
                f32 a;

                if (D_80110DCC_ridiculous_relay[0] < (f32)(sp - 1)) {
                    a = 50.0f;
                } else if ((f32)(sp + 1) < D_80110DCC_ridiculous_relay[0]) {
                    a = -50.0f;
                } else {
                    a = (D_80110DCC_ridiculous_relay[0] - (f32)sp) * -50.0f;
                }
                sx = (a < 0.0f) ? 0.0f : a;
                for (m = 0; m < n; m++) {
                    s32 h = hidx[m];
                    s32 l = (s32)lanes[h] + 1;

                    if (D_80110D7C_ridiculous_relay[h] == 0 && obj->trans.x < hx[m] + 12.5) {
                        f32 d = (hx[m] + 100.0f) - obj->trans.x;

                        room[l] = (d < room[l]) ? d : room[l];
                    }
                }
                for (m = 0; m < 2; m++) {
                    f32 reach[4] = { 100.0f, 115.0f, 130.0f, 150.0f };
                    s32 l;
                    f32 fx;
                    f32 ox;
                    f32 dx;
                    f32 spd;
                    f32 fr;
                    f32 off;

                    if (D_80110E28_ridiculous_relay[m] < -12.5) {
                        l = 0;
                    } else if (D_80110E28_ridiculous_relay[m] < 12.5) {
                        l = 1;
                    } else {
                        l = 2;
                    }
                    fx = D_80110E20_ridiculous_relay[m];
                    ox = obj->trans.x;
                    dx = fx - ox;
                    spd = D_80110E30_ridiculous_relay[m];
                    fr = dx / ((D_80110DCC_ridiculous_relay[0] + spd) * RR_K);
                    off = (fr * -spd) * RR_K;
                    if (off < 0.0f && ox < (off + fx) + 12.5 && dx < reach[pl->unk4]) {
                        f32 d = ((off + fx) + 100.0f) - ox;

                        room[l] = (d < room[l]) ? d : room[l];
                    }
                }
                bestLane = 0;
                for (m = 0; m < 3; m++) {
                    if (best < room[m] - (f32)((D_80110E04_ridiculous_relay - m > 0) ? D_80110E04_ridiculous_relay - m : m - D_80110E04_ridiculous_relay)) {
                        best = room[m] - (f32)((D_80110E04_ridiculous_relay - m > 0) ? D_80110E04_ridiculous_relay - m : m - D_80110E04_ridiculous_relay);
                        bestLane = m;
                    }
                }
                if (!(room[0] == D_80110E08_ridiculous_relay && room[1] == D_80110E08_ridiculous_relay && room[2] == D_80110E08_ridiculous_relay)) {
                    f32 lag[4] = { 185.0f, 200.0f, 215.0f, 230.0f };
                    f32 tol[4] = { 30.0f, 37.0f, 44.0f, 50.0f };
                    s32 tl;

                    if (D_80110E04_ridiculous_relay != bestLane) {
                        D_80110E08_ridiculous_relay = lag[pl->unk4];
                    }
                    D_80110E04_ridiculous_relay = bestLane;
                    tl = tol[pl->unk4];
                    if (obj->trans.y + 15.625 < ((D_80110E04_ridiculous_relay - 1) * 200.0 - tl) * 0.125) {
                        sy = tl;
                    } else if (((D_80110E04_ridiculous_relay - 1) * 200.0 + tl) * 0.125 < obj->trans.y + 15.625) {
                        sy = -tl;
                    }
                }
            }
            if (D_80110DF4_ridiculous_relay[0] != 0) {
                vx = -50.0f;
            } else {
                vx = (sx < -50.0f) ? -50.0f : (sx > 50.0f) ? 50.0f : sx;
            }
            if (D_80110DF4_ridiculous_relay[0] != 0) {
                sy = 0.0f;
            } else {
                sy = (sy < -50.0f) ? -50.0f : (sy > 50.0f) ? 50.0f : sy;
            }
            if (!(D_80110DBC_ridiculous_relay[0] >= 46.0f && sy > 0.0f)) {
                if (!(D_80110DBC_ridiculous_relay[0] <= -330.0f && sy < 0.0f)) {
                    rot = sy;
                } else {
                    rot = 0.0f;
                }
            } else {
                rot = 0.0f;
            }
        }
        if (D_80110E18_ridiculous_relay < 31) {
            D_80110DCC_ridiculous_relay[0] = D_80110DCC_ridiculous_relay[0] + vx / 50.0 * 5.0 / 30.0;
            D_80110DCC_ridiculous_relay[0] = (mode == 2) ? 40.0f
                : (D_80110DCC_ridiculous_relay[0] < 35.0 - 1.0 / 6) ? D_80110DCC_ridiculous_relay[0] + 1.0 / 6
                : (D_80110DCC_ridiculous_relay[0] < 35.0f) ? 35.0f
                : (D_80110DCC_ridiculous_relay[0] > 46.0f) ? 46.0f
                : D_80110DCC_ridiculous_relay[0];
        }
        D_80110DAC_ridiculous_relay[0] = D_80110DAC_ridiculous_relay[0] + D_80110DCC_ridiculous_relay[0] * RR_K;
        if (D_80110DAC_ridiculous_relay[0] > 1871.875 && D_80110D70_ridiculous_relay == 0) {
            D_80110D70_ridiculous_relay = 1;
            if (D_801119C0_ridiculous_relay == 5) {
                D_801119C0_ridiculous_relay = 0;
            }
            D_80110E40_ridiculous_relay = D_80110D6C_ridiculous_relay;
        }
        D_80110DAC_ridiculous_relay[0] -= D_80110E54_ridiculous_relay;
        CenterM[0].x = 2.0 * D_80110DAC_ridiculous_relay[0] + 56.25;
        D_80110E54_ridiculous_relay = (D_80110DCC_ridiculous_relay[0] + -40.0f) * 3.0f;
        D_80110DAC_ridiculous_relay[0] += D_80110E54_ridiculous_relay;
        s = (D_80110D70_ridiculous_relay != 0) ? 6 : 3;
        if (D_80110DDC_ridiculous_relay < rot - s) {
            rot = s + D_80110DDC_ridiculous_relay;
        } else if (rot + s < D_80110DDC_ridiculous_relay) {
            rot = D_80110DDC_ridiculous_relay - s;
        }
        D_80110DDC_ridiculous_relay = rot;
        D_80110DBC_ridiculous_relay[0] = D_80110DBC_ridiculous_relay[0] + D_80110DDC_ridiculous_relay / 5.0;
        D_80110DBC_ridiculous_relay[0] = (D_80110DBC_ridiculous_relay[0] > 30.0f) ? 30.0f
            : (D_80110DBC_ridiculous_relay[0] < -330.0f) ? -330.0f : D_80110DBC_ridiculous_relay[0];
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[0], D_80110DBC_ridiculous_relay[0] * 0.125, 0.0f);
        omSetRot(obj, -90.0f, 90.0 - D_80110DDC_ridiculous_relay / 8.0, D_80110DDC_ridiculous_relay / 4.0 + -90.0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (D_80110D70_ridiculous_relay < 100) {
        s32 hit;

        for (i = 0; i < n + 2; i++) {
            f32 px = (i < n) ? hx[i] : D_80110E20_ridiculous_relay[i - n];
            f32 py = (i < n) ? hy[i] : D_80110E28_ridiculous_relay[i - n];

            if ((i < n || !(D_80110E20_ridiculous_relay[i - n] <= -1000.0f)) && mode == 1 && D_80110DF4_ridiculous_relay[0] == 0
                && (i >= n || D_80110D7C_ridiculous_relay[hidx[i]] == 0) && D_80110E18_ridiculous_relay == 0) {
                f32 dx = px - obj->trans.x;

                if (dx < 15.625 && dx > -15.625) {
                    f32 ax;
                    f32 ay;
                    f64 dy;

                    if (!(dx > 0.0f)) {
                        dx = -dx;
                    }
                    ax = dx * 0.75;
                    dy = py - (obj->trans.y + 15.625);
                    if (!(dy > 0.0)) {
                        dy = -dy;
                    }
                    if (i >= n) {
                        dy *= 0.875;
                    }
                    ay = dy;
                    if (HuSqrtf(ax * ax + ay * ay) < 11.25) {
                        s16 se;

                        if (i < n) {
                            D_80110D7C_ridiculous_relay[hidx[i]] = 1;
                        }
                        D_80110E1C_ridiculous_relay = D_80110DCC_ridiculous_relay[0];
                        D_80110DF4_ridiculous_relay[0] = 60;
                        D_80110E18_ridiculous_relay = 60;
                        D_80110E50_ridiculous_relay = i >= n;
                        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[5], px * 0.5 + obj->trans.x * 0.5, py * 0.5 + obj->trans.y * 0.5 + 5.0, 0.0f);
                        Hu3DModelRotSet(D_801119BC_ridiculous_relay->model[5], 0.0f, 0.0f, rand8() / 256.0 * 360.0);
                        Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[5], 0.1875f, 0.1875f, 0.1875f);
                        func_8001C258_main(D_801119BC_ridiculous_relay->model[5], 4, 0);
                        func_8001F9E4_main(D_801119BC_ridiculous_relay->model[5], 0xFF);
                        obj->trans.y = obj->trans.y + -0.75;
                        omVibrate(D_80111970_ridiculous_relay[0]->unk0, 20, 0, 20);
                        func_80110C3C_ridiculous_relay(0x286, D_80111970_ridiculous_relay[0]->unk0);
                        func_80110BF4_ridiculous_relay((s8)D_80111970_ridiculous_relay[0]->unk3 + 0x95, D_80111970_ridiculous_relay[0]->unk0);
                        if (D_80110E50_ridiculous_relay == 0) {
                            se = HuAudFXPlay(0x333);
                            if (se != -1) {
                                func_8004AE00_main(se, (obj->trans.x - CenterM[0].x) / 90.0 * 32.0 + 64.0);
                            }
                        }
                    }
                }
            }
        }
        hit = D_80110DF4_ridiculous_relay[0] == 58;
        if (hit | (D_80110DF4_ridiculous_relay[0] == 56)) {
            func_8001F9E4_main(D_801119BC_ridiculous_relay->model[5], hit ? 0x80 : 0x30);
            Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[5], hit ? 0.28125f : 0.34375f, hit ? 0.28125f : 0.34375f, hit ? 0.28125f : 0.34375f);
            obj->trans.x += hit ? 0.5 : -0.75;
        } else if (D_80110DF4_ridiculous_relay[0] == 54) {
            func_8001C258_main(D_801119BC_ridiculous_relay->model[5], 4, 4);
            obj->trans.x += 0.25;
        }
        if (D_80110DF4_ridiculous_relay[0] != 0) {
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        }
        D_80110DF4_ridiculous_relay[0] = MAX((s16)(D_80110DF4_ridiculous_relay[0] - 2), 0);
        func_8001C6A8_main(obj->model[0], D_80110DF4_ridiculous_relay[0] ? (f32)(60 - D_80110DF4_ridiculous_relay[0]) : 0.0f);
        if (D_80110E18_ridiculous_relay != 0) {
            D_80110E18_ridiculous_relay--;
            if (D_80110E18_ridiculous_relay >= 30) {
                f32 f = sindf((60 - D_80110E18_ridiculous_relay) / 30.0 * 90.0);

                D_80110DCC_ridiculous_relay[0] = (1.0f - f) * D_80110E1C_ridiculous_relay + f * 35.0f;
                D_80110DAC_ridiculous_relay[0] = D_80110DAC_ridiculous_relay[0]
                    - ((1.0f - sindf((60 - D_80110E18_ridiculous_relay) / 30.0 * 90.0)) / 2.0f) * (D_80110E50_ridiculous_relay ? 4.0 : 2.5);
            }
            if (D_80110E18_ridiculous_relay < 31) {
                func_8001C258_main(obj->model[0], 4, (D_80110E18_ridiculous_relay & 1) * 4);
            }
        } else {
            func_8001C258_main(obj->model[0], 4, 0);
        }
        for (i = 0; i < 18; i++) {
            D_80110D7C_ridiculous_relay[i] += (D_80110D7C_ridiculous_relay[i] != 0 || D_801119D8_ridiculous_relay >= 3)
                                              && D_80110D7C_ridiculous_relay[i] < 0xFFFF;
        }
    }
    D_801119A8_ridiculous_relay[0] = (D_80110DAC_ridiculous_relay[0] < 0.0f) ? 0.0f : D_80110DAC_ridiculous_relay[0] / 1868.75f;
    D_801119A8_ridiculous_relay[0] = (D_801119A8_ridiculous_relay[0] >= 1.0f) ? 1.0f : D_801119A8_ridiculous_relay[0];

    /* runner 2: paddle the boat */
    obj = D_80111A20_ridiculous_relay[1];
    pl = D_80111970_ridiculous_relay[1];
    if (D_80110D78_ridiculous_relay == 0 || (D_80110D78_ridiculous_relay == 1 && D_80110DAC_ridiculous_relay[2] < 875.0)) {
        s32 old;
        f64 f;

        D_80110E0C_ridiculous_relay[0] -= (D_80110D78_ridiculous_relay == 0 && D_80110E0C_ridiculous_relay[0] != 0);
        if (D_80110D78_ridiculous_relay == 0 && mode == 1) {
            u16 btn = D_800D5558_main[pl->unk2];

            if ((D_80110DEE_ridiculous_relay ? (btn & 0x6000) : (btn & 0x8000)) || (pl->unk4 != -1 && D_80110E0C_ridiculous_relay[0] == 0)) {
                D_80110DEE_ridiculous_relay = 1 - D_80110DEE_ridiculous_relay;
                D_80110DF4_ridiculous_relay[1] = D_80110DF4_ridiculous_relay[1] ? D_80110DF4_ridiculous_relay[1] : 60;
                D_80110DCC_ridiculous_relay[1] = D_80110DCC_ridiculous_relay[1] + 40.0 / 9;
                if (pl->unk4 != -1) {
                    D_80110E0C_ridiculous_relay[0] = cpuTbl[0][0][pl->unk4] + rand8() % cpuTbl[1][0][pl->unk4];
                }
            }
        }
        if (mode == 2 && D_80110D6C_ridiculous_relay % 24 == 15) {
            D_80110DF4_ridiculous_relay[1] = D_80110DF4_ridiculous_relay[1] ? D_80110DF4_ridiculous_relay[1] : 60;
        }
        f = D_80110DCC_ridiculous_relay[1];
        D_80110DAC_ridiculous_relay[1] = D_80110DAC_ridiculous_relay[1] + f * RR_K;
        D_80110DCC_ridiculous_relay[1] = f - f / 6.0 / 5.0 * (29.0 / 30);
        if (mode == 2) {
            D_80110DCC_ridiculous_relay[1] = 40.0f;
        } else {
            D_80110DCC_ridiculous_relay[1] = (D_80110DCC_ridiculous_relay[1] > 43.5) ? 43.5f
                : (D_80110DCC_ridiculous_relay[1] < -43.5) ? -43.5f : D_80110DCC_ridiculous_relay[1];
        }
        if (D_80110DAC_ridiculous_relay[1] > 626.25) {
            D_80110DAC_ridiculous_relay[1] = 626.25f;
            D_80110DCC_ridiculous_relay[1] = (D_80110DCC_ridiculous_relay[1] > 0.0f) ? D_80110DCC_ridiculous_relay[1] * -0.25 : D_80110DCC_ridiculous_relay[1];
            if (D_80110D78_ridiculous_relay == 0) {
                D_80110D78_ridiculous_relay = 1;
                D_80110DFC_ridiculous_relay[0] = 1;
                D_80110DA8_ridiculous_relay = 1;
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 0.5) ? 0.5f : D_801117F0_ridiculous_relay;
                D_80110E44_ridiculous_relay = D_80110D6C_ridiculous_relay;
                omVibrate(D_80111970_ridiculous_relay[2]->unk0, 2, 3, 10);
            }
        }
        if (D_80110D78_ridiculous_relay == 0) {
            D_801117F0_ridiculous_relay = cam[1] - D_80110DA0_ridiculous_relay[1];
            CenterM[1].x = 2.0 * D_80110DAC_ridiculous_relay[1] + 56.25;
        }
        func_8001C258_main(obj->model[0], 4, 0);
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[1], RR_GROUND, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        old = D_80110DF4_ridiculous_relay[1] >= 58;
        f = D_80110DF4_ridiculous_relay[1];
        if (D_80110DCC_ridiculous_relay[1] < 0.0f) {
            f = f - 1.0;
        } else {
            f = f - D_80110DCC_ridiculous_relay[1] / 15.0;
        }
        D_80110DF4_ridiculous_relay[1] = f;
        D_80110DF4_ridiculous_relay[1] = MAX(D_80110DF4_ridiculous_relay[1], 0);
        if (D_80110DF4_ridiculous_relay[1] < 58 && old) {
            HuAudFXPlay(0x32F);
        }
        func_8001C6A8_main(obj->model[0], D_80110DF4_ridiculous_relay[1] ? (f32)(60 - D_80110DF4_ridiculous_relay[1]) : 0.0f);
        if (D_80110D78_ridiculous_relay == 0 && mode == 1) {
            D_80111980_ridiculous_relay[D_80110DEE_ridiculous_relay] = obj->trans.x;
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        func_8001C258_main(obj->model[2], 4, 4);
    }
    if (D_80110E3C_ridiculous_relay[0] == 1) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[7], 4, 4);
    }
    D_80110E3C_ridiculous_relay[0] = D_80110E3C_ridiculous_relay[0] ? D_80110E3C_ridiculous_relay[0] - 1 : 0;
    D_801119A8_ridiculous_relay[1] = (D_80110D78_ridiculous_relay != 0) ? 1.0f
        : (D_80110DAC_ridiculous_relay[1] < 0.0f) ? 0.0f : D_80110DAC_ridiculous_relay[1] / 626.5625f;
    D_801119A8_ridiculous_relay[1] = (D_801119A8_ridiculous_relay[1] >= 1.0f) ? 1.0f : D_801119A8_ridiculous_relay[1];

    /* runner 3: swim */
    obj = D_80111A20_ridiculous_relay[2];
    pl = D_80111970_ridiculous_relay[2];
    if (D_80110D78_ridiculous_relay == 1 || (D_80110D78_ridiculous_relay == 0 && D_80110DAC_ridiculous_relay[1] > 375.0)
        || (D_80110D78_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[3] < 1500.0)) {
        D_80110E0C_ridiculous_relay[1] -= (D_80110D78_ridiculous_relay == 1 && D_80110E0C_ridiculous_relay[1] != 0);
        if (D_80110D78_ridiculous_relay == 1 && mode == 1
            && ((((D_80110DF0_ridiculous_relay / 2) ? (D_800D5558_main[pl->unk2] & 0x4000) : (D_800D5558_main[pl->unk2] & 0x8000))
                 && !(((D_80110DF0_ridiculous_relay & 1) ? -D_800D20A1_main[pl->unk2] : D_800D20A1_main[pl->unk2]) < 33))
                || (pl->unk4 != -1 && D_80110E0C_ridiculous_relay[1] == 0))) {
            D_80110E0C_ridiculous_relay[3] = D_80110E10_ridiculous_relay[0];
            D_80110E10_ridiculous_relay[0] = D_80110DF0_ridiculous_relay;
            D_80110E10_ridiculous_relay[1] = 0;
            D_80110E10_ridiculous_relay[2] = 2;
            func_8001C624_main(obj->model[1], HmfModelData[obj->motion[D_80110DF0_ridiculous_relay + 7]].unk02,
                               (D_80110DF0_ridiculous_relay == 3) ? 7 : 5, 4, 0);
            D_80110DF0_ridiculous_relay = (D_80110DF0_ridiculous_relay + 1) % 4;
            if (D_80110DF0_ridiculous_relay == 0) {
                D_80110DF8_ridiculous_relay[0] = 50;
                D_80110DCC_ridiculous_relay[2] = 53.0f;
                if (D_80110D78_ridiculous_relay == 1) {
                    func_8001C258_main(D_801119BC_ridiculous_relay->model[8], 4, 0);
                    Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[8], 0.234375f, 0.234375f, 0.234375f);
                    func_8001C6A8_main(D_801119BC_ridiculous_relay->model[8], 0.0f);
                    func_8001C92C_main(D_801119BC_ridiculous_relay->model[8], 1.5f);
                    func_8001C258_main(D_801119BC_ridiculous_relay->model[9], 4, 0);
                    Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[9], 0.234375f, 0.234375f, 0.234375f);
                    func_8001C6A8_main(D_801119BC_ridiculous_relay->model[9], 0.0f);
                    func_8001C92C_main(D_801119BC_ridiculous_relay->model[9], 1.5f);
                    D_80110E3C_ridiculous_relay[1] = 10;
                    HuAudFXPlay(0x330);
                }
            }
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[8], obj->trans.x - 31.25, obj->trans.y - 3.90625, obj->trans.z);
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[9], obj->trans.x + 23.4375, obj->trans.y - 1.953125, obj->trans.z);
            if (pl->unk4 != -1) {
                D_80110E0C_ridiculous_relay[1] = cpuTbl[0][1][pl->unk4] + rand8() % cpuTbl[1][1][pl->unk4];
            }
        } else if (D_80110D78_ridiculous_relay == 1 && mode == 1 && D_80110E10_ridiculous_relay[0] != 4 && pl->unk4 == -1
                   && (D_800D5558_main[pl->unk2] & 0xC000)) {
            D_80110E0C_ridiculous_relay[3] = D_80110E10_ridiculous_relay[0];
            D_80110E10_ridiculous_relay[0] = 4;
            D_80110E10_ridiculous_relay[1] = 0;
            D_80110E10_ridiculous_relay[2] = 3;
            func_8001C624_main(obj->model[1], HmfModelData[obj->motion[11]].unk02, 0, 6, 0);
            omVibrate(D_80111970_ridiculous_relay[2]->unk0, 10, 0, 10);
        }
        step = D_80110DCC_ridiculous_relay[2] / 60.0 * 2.083333333333333;
        D_80110DAC_ridiculous_relay[2] += step;
        D_80110DCC_ridiculous_relay[2] = (D_80110DCC_ridiculous_relay[2] > 1.0f) ? D_80110DCC_ridiculous_relay[2] - 1.0f
            : (D_80110DCC_ridiculous_relay[2] < -1.0f) ? D_80110DCC_ridiculous_relay[2] + 1.0f : 0.0f;
        if (D_80110DAC_ridiculous_relay[2] > 1245.3125) {
            D_80110DAC_ridiculous_relay[2] = 1245.3125f;
            D_80110DCC_ridiculous_relay[2] = (D_80110DCC_ridiculous_relay[2] > 0.0f) ? D_80110DCC_ridiculous_relay[2] * -0.2 : D_80110DCC_ridiculous_relay[2];
            if (D_80110D78_ridiculous_relay < 2) {
                D_80110D78_ridiculous_relay = 2;
                D_80110DFC_ridiculous_relay[1] = 1;
                D_80110DA8_ridiculous_relay = 1;
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 0.5) ? 0.5f : D_801117F0_ridiculous_relay;
                if (D_801119D8_ridiculous_relay == 2) {
                    D_80111A30_ridiculous_relay[2] = HuAudFXPlay(0x331);
                    func_8004AAD0_main(D_80111A30_ridiculous_relay[2], 0x7F);
                }
                D_80110E48_ridiculous_relay = D_80110D6C_ridiculous_relay;
                omVibrate(D_80111970_ridiculous_relay[3]->unk0, 2, 3, 10);
            }
        }
        if (D_80110D78_ridiculous_relay == 1) {
            cx = 2.0 * D_80110DAC_ridiculous_relay[2] + 56.25;
            D_80110DA8_ridiculous_relay = (D_80110DA8_ridiculous_relay != 0 && CenterM[1].x + D_801117F0_ridiculous_relay <= cx) ? D_80110DA8_ridiculous_relay + 1 : 0;
            if (D_80110DA8_ridiculous_relay != 0) {
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 2.0 * step) ? 2.0 * step : D_801117F0_ridiculous_relay;
                CenterM[1].x = CenterM[1].x + D_801117F0_ridiculous_relay;
            } else {
                D_801117F0_ridiculous_relay = cam[1] - D_80110DA0_ridiculous_relay[1];
                CenterM[1].x = cx;
            }
        }
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[2], 4, 0);
        D_80110E10_ridiculous_relay[1] = (D_80110E0C_ridiculous_relay[3] == D_80110E10_ridiculous_relay[0]) ? 0 : D_80110E10_ridiculous_relay[1] + 1;
        if (D_80110E10_ridiculous_relay[2] < D_80110E10_ridiculous_relay[1]) {
            u8 prev = D_80110E0C_ridiculous_relay[3];

            D_80110E0C_ridiculous_relay[3] = D_80110E10_ridiculous_relay[0];
            D_80110E10_ridiculous_relay[1] = 0;
            if (D_80110E10_ridiculous_relay[0] == 4) {
                D_80110E10_ridiculous_relay[0] = prev;
                D_80110E10_ridiculous_relay[2] = 10;
                func_8001C624_main(obj->model[1], HmfModelData[obj->motion[D_80110E10_ridiculous_relay[0] + 7]].unk02, 60, 20, 0);
            } else {
                D_80110E10_ridiculous_relay[2] = 0;
            }
        }
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[2], RR_GROUND + 25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
#define RR_BOB() ((D_80110E10_ridiculous_relay[2] == 0) ? bob[D_80110E10_ridiculous_relay[0]] \
    : (1.0f - (f32)D_80110E10_ridiculous_relay[1] / (f32)D_80110E10_ridiculous_relay[2]) * bob[D_80110E0C_ridiculous_relay[3]] \
      + ((f32)D_80110E10_ridiculous_relay[1] / (f32)D_80110E10_ridiculous_relay[2]) * bob[D_80110E10_ridiculous_relay[0]])
        obj->trans.x = obj->trans.x - RR_BOB() * 0.125 * 1.25;
        obj->trans.y = (f32)(obj->trans.y - RR_BOB() * 0.125 * 1.25) + 1.875;
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        if (D_80110DF8_ridiculous_relay[0] > 0) {
            if (D_80110DF8_ridiculous_relay[0] == 2) {
                D_80110DF8_ridiculous_relay[0] = 0;
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C6A8_main(obj->model[2], 0.0f);
            } else {
                if (D_80110DF8_ridiculous_relay[0] == 50) {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 6, 2);
                }
                D_80110DF8_ridiculous_relay[0] = MAX((s16)(D_80110DF8_ridiculous_relay[0] - 2), 0);
                func_8001C6A8_main(obj->model[0], D_80110DF8_ridiculous_relay[0] ? (f32)(50 - D_80110DF8_ridiculous_relay[0]) : 0.0f);
                func_8001C6A8_main(obj->model[2], (D_80110DF8_ridiculous_relay[0] == 0) ? 0.0f
                    : (D_80110DF8_ridiculous_relay[0] < 25) ? (f32)D_80110DF8_ridiculous_relay[0]
                    : (f32)(50 - D_80110DF8_ridiculous_relay[0]));
            }
        }
        func_8001C814_main(obj->model[0], 3, 2);
        func_8001C814_main(obj->model[2], 3, 1);
        if (D_80110D78_ridiculous_relay == 1 && mode == 1) {
            D_80111980_ridiculous_relay[2 + D_80110DF0_ridiculous_relay] = HmfModelData[obj->model[1]].pos.x;
        }
        if (D_80110E0C_ridiculous_relay[3] == 4 && (D_80110E10_ridiculous_relay[1] == 0 || D_80110E10_ridiculous_relay[1] == 4)) {
            for (i = (D_80110E10_ridiculous_relay[1] != 0) ? 9 : 0; i < ((D_80110E10_ridiculous_relay[1] != 0) ? 18 : 9); i++) {
                f64 v;

                func_8001C258_main(D_801119BC_ridiculous_relay->model[17 + i], 4, 0);
                D_801117F8_ridiculous_relay[i] = HmfModelData[obj->model[1]].pos.x + ((D_80110E10_ridiculous_relay[1] != 0) ? 27.5 : -31.25);
                D_80111840_ridiculous_relay[i] = RR_GROUND;
                v = (rand8() / 256.0 * 30.0 - 10.0) * 0.125;
                D_80111888_ridiculous_relay[i] = (D_80110E10_ridiculous_relay[1] != 0) ? v : -v;
                D_801118D0_ridiculous_relay[i] = (rand8() / 256.0 * 30.0 + 20.0) * 0.125;
                Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[17 + i], D_801117F8_ridiculous_relay[i], D_80111840_ridiculous_relay[i], 0.0f);
            }
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        func_8001C258_main(obj->model[2], 4, 4);
    }
    if (D_80110E3C_ridiculous_relay[1] == 1) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[8], 4, 4);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[9], 4, 4);
    }
    D_80110E3C_ridiculous_relay[1] = D_80110E3C_ridiculous_relay[1] ? D_80110E3C_ridiculous_relay[1] - 1 : 0;
    D_801119A8_ridiculous_relay[2] = (D_80110D78_ridiculous_relay >= 2) ? 1.0f
        : (D_80110DAC_ridiculous_relay[2] < 0.0f) ? 0.0f : (D_80110DAC_ridiculous_relay[2] - 650.0) / 601.5625;
    D_801119A8_ridiculous_relay[2] = (D_801119A8_ridiculous_relay[2] >= 1.0f) ? 1.0f
        : (D_801119A8_ridiculous_relay[2] < 0.0f) ? 0.0f : D_801119A8_ridiculous_relay[2];
    /* splashes */
    for (i = 0; i < 18; i++) {
        if (D_80111840_ridiculous_relay[i] != -1000.0f) {
            D_801117F8_ridiculous_relay[i] += D_80111888_ridiculous_relay[i];
            D_80111840_ridiculous_relay[i] += D_801118D0_ridiculous_relay[i];
            D_801118D0_ridiculous_relay[i] -= 0.625;
            if (D_801118D0_ridiculous_relay[i] < 0.0f && D_80111840_ridiculous_relay[i] < RR_GROUND) {
                func_8001C258_main(D_801119BC_ridiculous_relay->model[17 + i], 4, 4);
                D_80111840_ridiculous_relay[i] = -1000.0f;
            } else {
                Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[17 + i], D_801117F8_ridiculous_relay[i], D_80111840_ridiculous_relay[i], 0.0f);
            }
        }
    }

    /* runner 4: bike */
    obj = D_80111A20_ridiculous_relay[3];
    pl = D_80111970_ridiculous_relay[3];
    if (D_80110D78_ridiculous_relay == 2 || D_80110D78_ridiculous_relay == 3 || (D_80110D78_ridiculous_relay == 1 && D_80110DAC_ridiculous_relay[2] > 1000.0)) {
        f64 f;
        f32 v;

        D_80110E0C_ridiculous_relay[2] -= (D_80110D78_ridiculous_relay == 2 && D_80110E0C_ridiculous_relay[2] != 0);
        if (D_80110D78_ridiculous_relay >= 2 && mode == 1) {
            if ((D_800D5558_main[pl->unk2] & 0x8000) || (pl->unk4 != -1 && D_80110E0C_ridiculous_relay[2] == 0)) {
                D_80110DCC_ridiculous_relay[3] += 5.0f;
                if (pl->unk4 != -1) {
                    D_80110E0C_ridiculous_relay[2] = cpuTbl[0][2][pl->unk4] + rand8() % cpuTbl[1][2][pl->unk4];
                }
            }
        }
        f = D_80110DCC_ridiculous_relay[3];
        step = f * RR_K;
        D_80110DAC_ridiculous_relay[3] = step + D_80110DAC_ridiculous_relay[3];
        D_80110DCC_ridiculous_relay[3] = f - f / 6.0 / 5.0;
        D_80110DCC_ridiculous_relay[3] = (D_80110DCC_ridiculous_relay[3] > 50.0f) ? 50.0f
            : (D_80110DCC_ridiculous_relay[3] < -50.0f) ? -50.0f : D_80110DCC_ridiculous_relay[3];
        if (D_80111A30_ridiculous_relay[2] != -1) {
            HuAudFXPitchSet((s16)D_80111A30_ridiculous_relay[2], (s16)(D_80110DCC_ridiculous_relay[3] / 50.0 * 400.0 - 400.0));
        }
        if (D_80110DAC_ridiculous_relay[3] > 1865.625 && D_80110D74_ridiculous_relay == 0) {
            if (D_801119C0_ridiculous_relay == 5
                || (D_801119C0_ridiculous_relay == 0 && D_80110D70_ridiculous_relay == 1 && D_80110DAC_ridiculous_relay[0] < D_80110DAC_ridiculous_relay[3])) {
                D_801119C0_ridiculous_relay = 1;
                D_80110D74_ridiculous_relay = 1;
            }
            if (D_80110E4C_ridiculous_relay == 0) {
                D_80110E4C_ridiculous_relay = D_80110D6C_ridiculous_relay;
            }
            D_80110DAC_ridiculous_relay[3] = 1865.625f;
            D_80110DCC_ridiculous_relay[3] = (D_80110DCC_ridiculous_relay[3] > 0.0f) ? D_80110DCC_ridiculous_relay[3] * -0.125 : D_80110DCC_ridiculous_relay[3];
        }
        if (D_80110D78_ridiculous_relay == 2) {
            cx = 2.0 * D_80110DAC_ridiculous_relay[3] + 56.25;
            D_80110DA8_ridiculous_relay = (D_80110DA8_ridiculous_relay != 0 && CenterM[1].x + D_801117F0_ridiculous_relay <= cx) ? D_80110DA8_ridiculous_relay + 1 : 0;
            if (D_80110DA8_ridiculous_relay != 0) {
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 2.0 * step) ? 2.0 * step : D_801117F0_ridiculous_relay;
                CenterM[1].x = CenterM[1].x + D_801117F0_ridiculous_relay;
            } else {
                D_801117F0_ridiculous_relay = cam[1] - D_80110DA0_ridiculous_relay[1];
                CenterM[1].x = cx;
            }
        }
        D_80110DF2_ridiculous_relay = D_80110DF2_ridiculous_relay * 0.875 + D_80110DCC_ridiculous_relay[3] / 50.0 * 10.0 * 1000.0 * 0.125;
        func_8001C258_main(obj->model[0], 4, 0);
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[3], RR_GROUND, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, D_80110DF2_ridiculous_relay / 1000.0);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        D_80110DF8_ridiculous_relay[1] = D_80110DF8_ridiculous_relay[1]
            + ((D_80110DCC_ridiculous_relay[3] > 0.0f) ? D_80110DCC_ridiculous_relay[3] : -D_80110DCC_ridiculous_relay[3]) / 50.0 * 350.0;
        D_80110DF8_ridiculous_relay[1] = D_80110DF8_ridiculous_relay[1] % 3000;
#define RR_PEDAL(x) (((x) < 20.0f) ? 2.0f * (x) - 20.0f : (x))
        D_80110E14_ridiculous_relay = (D_80110E14_ridiculous_relay - 4.0 / 47.5 < RR_PEDAL(D_80110DCC_ridiculous_relay[3]) / 47.5)
            ? RR_PEDAL(D_80110DCC_ridiculous_relay[3]) / 47.5 : D_80110E14_ridiculous_relay - 4.0 / 47.5;
        D_80110E14_ridiculous_relay = (D_80110E14_ridiculous_relay < 0.0f) ? 0.0f : D_80110E14_ridiculous_relay;
        func_8001C6A8_main(obj->model[1], D_80110DF8_ridiculous_relay[1] / 100.0);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[6], 4, 0);
        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[6],
                        obj->trans.x - ((D_80110E14_ridiculous_relay * 40.0f) + 200.0f) * 1.25 * 0.125,
                        obj->trans.y + (D_80110E14_ridiculous_relay * 100.0f) * 1.25 * 0.125, obj->trans.z);
        Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[6], D_80110E14_ridiculous_relay * 1.25 * 0.125 * 1.3,
                          D_80110E14_ridiculous_relay * 1.25 * 0.125, D_80110E14_ridiculous_relay * 1.25 * 0.125);
        if (D_80110D74_ridiculous_relay != 0) {
            if (D_80110D74_ridiculous_relay == 15) {
                D_80111930_ridiculous_relay = obj->trans.y + 4.375;
                D_80111938_ridiculous_relay = 7.5f;
                for (i = 0; i < 85; i++) {
                    D_80111930_ridiculous_relay += D_80111938_ridiculous_relay;
                    D_80111938_ridiculous_relay -= 0.8125;
                    if (D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay <= -13.75) {
                        break;
                    }
                }
                D_8011192C_ridiculous_relay = obj->trans.x + 4.375;
                D_80111930_ridiculous_relay = obj->trans.y + 4.375;
                D_8011193C_ridiculous_relay = 90.0f;
                D_80111934_ridiculous_relay = (3768.75 - obj->trans.x) / (f32)i;
                D_80111938_ridiculous_relay = 7.5f;
                func_8001C5B4_main(obj->model[0], obj->motion[5]);
                func_8001C814_main(obj->model[0], 3, 0);
                D_80110DCC_ridiculous_relay[3] -= 2.0;
            }
            if (D_80110D74_ridiculous_relay >= 16 && D_80110D74_ridiculous_relay < 100) {
                D_8011192C_ridiculous_relay += D_80111934_ridiculous_relay;
                D_80111930_ridiculous_relay += D_80111938_ridiculous_relay;
                D_80111938_ridiculous_relay -= 0.8125;
                if ((D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay <= -13.75) || D_80111930_ridiculous_relay < -1875.0) {
                    D_80111930_ridiculous_relay = -13.75f;
                    D_80110D74_ridiculous_relay = 100;
                } else if (D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay + D_80111938_ridiculous_relay <= -13.75) {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[6]].unk02, 10, 4, 0);
                }
            }
            if (D_80110D74_ridiculous_relay == 102) {
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
            }
            if (D_80110D74_ridiculous_relay >= 115 && D_801119C0_ridiculous_relay == 1) {
                D_8011193C_ridiculous_relay = (D_8011193C_ridiculous_relay < -10.0f) ? (D_8011193C_ridiculous_relay + 9.0f) - D_8011193C_ridiculous_relay * 0.1
                                            : (D_8011193C_ridiculous_relay > 10.0f) ? (D_8011193C_ridiculous_relay - 9.0f) - D_8011193C_ridiculous_relay * 0.1
                                            : 0.0f;
            }
            if (D_80110D74_ridiculous_relay >= 16) {
                omSetTra(obj, D_8011192C_ridiculous_relay, D_80111930_ridiculous_relay, 0.0f);
                omSetRot(obj, 0.0f, D_8011193C_ridiculous_relay, 0.0f);
            }
            D_80110D74_ridiculous_relay++;
        } else {
            func_8001C814_main(obj->model[0], 3, 2);
        }
        if (D_80110D78_ridiculous_relay >= 2 && mode == 1) {
            D_80111998_ridiculous_relay = obj->trans.x;
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    D_801119A8_ridiculous_relay[3] = (D_80110D78_ridiculous_relay >= 3) ? 1.0f
        : (D_80110DAC_ridiculous_relay[3] < 0.0f) ? 0.0f : (D_80110DAC_ridiculous_relay[3] - 1275.0) / 593.75;
    D_801119A8_ridiculous_relay[3] = (D_801119A8_ridiculous_relay[3] >= 1.0f || D_80110D74_ridiculous_relay != 0) ? 1.0f
        : (D_801119A8_ridiculous_relay[3] < 0.0f) ? 0.0f : D_801119A8_ridiculous_relay[3];

    /* cameras and the finish flags */
    CenterM[0].x = (CenterM[0].x > 3750.0) ? 3750.0f : CenterM[0].x;
    CenterM[1].x = (CenterM[1].x > 3750.0) ? 3750.0f : CenterM[1].x;
    s = (CenterM[1].x < 1875.0) ? 0 : 1;
    t = D_80110DFC_ridiculous_relay[s];
    if (t < 10) {
        y = 0.125 * (t * t / 100.0 * 100.0) + -46.875;
    } else if (D_80110DFC_ridiculous_relay[s] < 30) {
        y = ((D_80110DFC_ridiculous_relay[s] - 10) * 36 + 100) * 0.125 + -46.875;
    } else if ((D_80110DFC_ridiculous_relay[s] - 30) * (D_80110DFC_ridiculous_relay[s] - 30) * 2 < 460) {
        y = (460 - (D_80110DFC_ridiculous_relay[s] - 30) * (D_80110DFC_ridiculous_relay[s] - 30) * 2) * 0.125 + -46.875;
    } else {
        y = -46.875f;
    }
    omSetTra(D_801119BC_ridiculous_relay, (2.0 * ((s + 1) * 5000) + 950.0) * 0.125, y, 0.0f);
    Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[1], (2.0 * ((s + 1) * 5000) + 150.0) * 0.125, -25.0f, 0.0f);
    D_80110DFC_ridiculous_relay[0] += (D_80110DFC_ridiculous_relay[0] != 0 && D_80110DFC_ridiculous_relay[0] < 24)
                                      || (D_80110DFC_ridiculous_relay[0] >= 30 && D_80110DFC_ridiculous_relay[0] < 45);
    if (D_80110DFC_ridiculous_relay[1] == 44) {
        HuAudFXPlay(0x334);
    }
    D_80110DFC_ridiculous_relay[1] += (D_80110DFC_ridiculous_relay[1] != 0 && D_80110DFC_ridiculous_relay[1] < 20)
                                      || (D_80110DFC_ridiculous_relay[1] >= 30 && D_80110DFC_ridiculous_relay[1] < 45);
    if (D_80110DFC_ridiculous_relay[1] == 20 && CenterM[1].x > 2721.875) {
        D_80110DFC_ridiculous_relay[1] = 30;
    }
    if (D_80110D6C_ridiculous_relay < 123) {
        CenterM[0].x = CenterM[0].x * 0.75 + 14.5718165;
        CenterM[1].x = CenterM[1].x * 0.75 + 14.5718165;
    }
    D_80110DAC_ridiculous_relay[0] = (D_80110DAC_ridiculous_relay[0] < -2000.0f) ? -2000.0f : D_80110DAC_ridiculous_relay[0];
    D_8011199C_ridiculous_relay[0] = CenterM[0].x / 0.125 / 100.0 * 16.0;
    if (CenterM[0].x < 3750.0) {
        D_801119C4_ridiculous_relay = (D_80110DCC_ridiculous_relay[0] - 35.0f) / 10.0 * 0.25 - 0.5;
    }
    D_801119C4_ridiculous_relay = 0.0f;
    D_80111A50_ridiculous_relay += 0.0f;
    D_80111A50_ridiculous_relay -= (D_80111A50_ridiculous_relay >= 320.0f) ? 320.0f : 0.0f;
    D_80111A50_ridiculous_relay += (D_80111A50_ridiculous_relay < 0.0f) ? 320.0f : 0.0f;
    D_8011199C_ridiculous_relay[1] = CenterM[1].x / 0.125 / 100.0 * 16.0;
    for (i = 0; i < 7; i++) {
        if (D_80111980_ridiculous_relay[i] != 0.0f) {
            D_80111980_ridiculous_relay[i] = func_8010B474_ridiculous_relay(D_80111980_ridiculous_relay[i]);
        }
    }
    D_80110D6C_ridiculous_relay++;
    D_80110DA0_ridiculous_relay[0] = cam[0];
    D_80110DA0_ridiculous_relay[1] = cam[1];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010B4A8_ridiculous_relay);
#endif

s16 func_80110BF4_ridiculous_relay(s16 seId, s16 player) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_8004AC5C_main(seId, 0);
}

s16 func_80110C3C_ridiculous_relay(s16 seId, s16 player) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_8004AC5C_main(seId + GwPlayer[player].chr + 1, 0);
}
