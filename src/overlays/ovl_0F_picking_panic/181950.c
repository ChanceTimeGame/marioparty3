#include "ultra64.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"
#include "math.h"

// EXTERN

void func_8000B5F0_main(u8 arg0);
void func_8000B710_main(s32);
void func_800142A0_main(s32);
void func_80017954_main(s16, s16, s16, s16);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80045010_main(s16 *, s32);
void func_80045ED0_main(s32);
s32 _CheckFlag(s32);
f32 atan2df(f32, f32);
f32 cosdf(f32);
f32 sindf(f32);

extern u8 D_800CD280_main;
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];
extern s16 D_800CDA7C_main[];
extern Gfx *gMainGfxPos;

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} D_800CD1DC_main_Struct; // Size 0x24

extern D_800CD1DC_main_Struct *D_800CD1DC_main;

// LOCAL

typedef struct {
    /* 0x00 */ s8 unk00; /* player number */
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02; /* pad */
    /* 0x03 */ s8 unk03; /* character */
    /* 0x04 */ s8 unk04; /* CPU difficulty, -1 for a human */
    /* 0x05 */ char unk05[1];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ s32 unk0C;
} PkPlayer; // Size 0x10

/* Per-team CPU state; the halves are split labels D_8010E704..D_8010E70A. */
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} PkTeamAi; // Size 8

typedef struct {
    u8 unk00[8];
    u8 unk08[8];
    u8 unk10[8];
    u8 unk18[8];
} PkCpuTable;

void func_80105D3C_picking_panic(omObjData *obj);
void func_80106020_picking_panic(omObjData *obj);
void func_8010664C_picking_panic(omObjData *obj);
void func_80106E84_picking_panic(omObjData *obj);
void func_80107A48_picking_panic(void);
void func_8010B160_picking_panic(omObjData *obj);
void func_8010B194_picking_panic(omObjData *obj);
void func_8010B1C0_picking_panic(omObjData *obj);
void func_8010B1F4_picking_panic(omObjData *obj);
void func_80109C00_picking_panic(Gfx **arg0, s32 arg1, s32 arg2);
void func_8010B220_picking_panic(omObjData *obj, u8 arg1);
void func_8010B8D0_picking_panic(omObjData *obj);
void func_8010B8EC_picking_panic(omObjData *obj);
void func_8010B908_picking_panic(omObjData *arg0, s8 arg1);
void func_8010B11C_picking_panic(s16 model, s16 frame);

typedef struct {
    s32 unk00[8];
} PkChrTable;

/* data */
extern Gfx D_8010E5E0_picking_panic[];
extern D_80111B50_vine_with_me_Struct D_8010E5B0_picking_panic;
extern u8 D_8010E628_picking_panic;
extern f32 D_8010E62C_picking_panic[3][16];
extern u32 D_8010E6EC_picking_panic;
extern s8 D_8010E6F0_picking_panic[2][4];
extern u8 D_8010E6F8_picking_panic[4];
extern u8 D_8010E6FC_picking_panic[4];
extern s8 D_8010E700_picking_panic[4];
extern PkTeamAi D_8010E704_picking_panic[2];
extern u8 D_8010E714_picking_panic[4];
extern u8 D_8010E718_picking_panic[8];

/* rodata */
extern s16 D_8010E720_picking_panic[];
extern PkChrTable D_8010E758_picking_panic;
extern PkCpuTable D_8010EA8C_picking_panic;

/* bss */
extern f32 D_8010EC20_picking_panic[3][16];
extern f32 D_8010ECE0_picking_panic[3][16];
extern u8 D_8010EDA0_picking_panic[2][4];
extern u8 D_8010EDA8_picking_panic[2][4];
extern f32 D_8010EDB0_picking_panic[2][4];
extern f32 D_8010EDD0_picking_panic[2][4];
extern f32 D_8010EDF0_picking_panic[2][4];
extern f32 D_8010EE10_picking_panic[2][4];
extern f32 D_8010EE30_picking_panic[2][4];
extern f32 D_8010EE50_picking_panic[2][4];
extern f32 D_8010EE70_picking_panic;
extern f32 D_8010EE74_picking_panic;
extern f32 D_8010EE78_picking_panic;
extern f32 D_8010EE7C_picking_panic;
extern f32 D_8010EE80_picking_panic;
extern f32 D_8010EE84_picking_panic;
extern f32 D_8010EE88_picking_panic;
extern f32 D_8010EE8C_picking_panic;
extern f32 D_8010EE90_picking_panic;
extern f32 D_8010EE94_picking_panic;
extern f32 D_8010EE98_picking_panic;
extern PkPlayer D_8010EEA0_picking_panic[4];
extern PkPlayer *D_8010EEE0_picking_panic[4];
extern u8 D_8010EEF0_picking_panic[4];
extern f32 D_8010EEF4_picking_panic[2];
extern omObjData *D_8010EEFC_picking_panic;
extern omObjData *D_8010EF00_picking_panic[4];
extern u16 D_8010EF10_picking_panic[2];
extern s8 D_8010EF14_picking_panic;
extern u8 D_8010EF15_picking_panic[2];
extern s16 *D_8010EF18_picking_panic[2][4][3];
extern f32 D_8010EF78_picking_panic;
extern s32 D_8010EF7C_picking_panic;
extern s16 D_8010EF80_picking_panic;
extern f32 D_8010EF84_picking_panic[2];
extern f32 D_8010EF8C_picking_panic[2];
extern f32 D_8010EF94_picking_panic;
extern s8 D_8010EF98_picking_panic[2];
extern f32 D_8010EF9C_picking_panic[2];
extern u8 D_8010EFA4_picking_panic;
extern u8 D_8010EFA5_picking_panic;
extern s32 D_8010EFA8_picking_panic;
extern u8 D_8010EFBC_picking_panic[2];
extern u16 D_8010EFBE_picking_panic;
extern u8 D_8010EFC0_picking_panic[4];
extern f32 D_8010EFAC_picking_panic[2];
extern f32 D_8010EFC4_picking_panic[2];
extern s16 D_8010EFD0_picking_panic[10];
extern f32 D_8010EFEC_picking_panic[2];
extern s16 D_8010EFF8_picking_panic[10];


void func_801059A0_picking_panic(void) {
    omObjData *temp_v0;
    omObjData *temp_v0_2;

    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCamSetPerspective(0, 22.619865f, 4000.0f, 10000.0f);
    Hu3DCamSetPerspective(1, 22.619865f, 4000.0f, 10000.0f);
    HmfLightMaxSet(1);
    HmfLightDirSet(0, 0.0f, 0.0f, 90.0f);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(1, 0.0f, 65.0f, 90.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 4687.5f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 4687.5f;
    omAddObj(0, 0, 0, -1, func_80105D3C_picking_panic);
    temp_v0 = omAddObj(8, 38, 38, -1, func_8010664C_picking_panic);
    D_8010EEFC_picking_panic = temp_v0;
    omSetStatBit(temp_v0, 0xA0);
    D_8010EF00_picking_panic[0] = omAddObj(3, 8, 5, -1, func_8010B160_picking_panic);
    D_8010EF00_picking_panic[1] = omAddObj(3, 8, 5, -1, func_8010B194_picking_panic);
    D_8010EF00_picking_panic[2] = omAddObj(3, 8, 5, -1, func_8010B1C0_picking_panic);
    D_8010EF00_picking_panic[3] = omAddObj(3, 8, 5, -1, func_8010B1F4_picking_panic);
    temp_v0_2 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0_2->work[0] = 2;
    omSetStatBit(temp_v0_2, 0xA0);
    func_80045010_main(D_8010E720_picking_panic, 1);
    WipeCreateIn(0xFF, 0x10);
    D_8010E5B0_picking_panic.unk01 = 1;
    D_8010E5B0_picking_panic.unk1C = 60;
    D_8010E5B0_picking_panic.unk1E = 900;
    D_8010E5B0_picking_panic.unk03 = 2;
    D_8010E5B0_picking_panic.unk02 = 1;
    D_8010E5B0_picking_panic.unk22 = 75;
    D_8010E5B0_picking_panic.unk24 = 165;
    D_8010E5B0_picking_panic.unk04 = 0;
    D_8010E5B0_picking_panic.unk05 = 0;
    D_8010E5B0_picking_panic.unk20 = -1;
    func_800E5EA0_minigame(&D_8010E5B0_picking_panic);
}

#ifdef NON_MATCHING
void func_80105D3C_picking_panic(omObjData *obj) {
    u8 sp10[4];
    PkPlayer *p;
    s32 i;
    s32 j;

    D_8010EFBE_picking_panic = 0;
    D_8010EF80_picking_panic = 0;
    D_8010EFA8_picking_panic = 0;
    D_8010EF7C_picking_panic = 0;
    D_8010EF14_picking_panic = 5;
    D_8010EF10_picking_panic[0] = D_8010EF10_picking_panic[1] = 1;
    D_8010EF98_picking_panic[0] = D_8010EF98_picking_panic[1] = -1;
    D_8010EFBC_picking_panic[0] = D_8010EFBC_picking_panic[1] = 0;
    D_8010EEF0_picking_panic[0] = D_8010EEF0_picking_panic[1] = 0;
    D_8010EF15_picking_panic[0] = D_8010EF15_picking_panic[1] = 0;
    D_8010EFA4_picking_panic = 0xFF;
    D_8010EF84_picking_panic[0] = D_8010EF84_picking_panic[1] = 0.0f;
    D_8010EF94_picking_panic = 0.0f;
    for (i = 0; i < 4; i++) {
        p = &D_8010EEA0_picking_panic[i];
        D_8010EEE0_picking_panic[i] = p;
        bzero(p, sizeof(PkPlayer));
    }
    for (j = 0; j < 4; j++) {
        sp10[j] = GwPlayer[j].group;
        D_8010EFC0_picking_panic[sp10[j]] = j;
    }
    for (j = 0; j < 4; j++) {
        D_8010EEE0_picking_panic[sp10[j]]->unk00 = j;
        D_8010EEE0_picking_panic[j]->unk02 = GwPlayer[D_8010EFC0_picking_panic[j]].pad;
        D_8010EEE0_picking_panic[j]->unk03 = GwPlayer[D_8010EFC0_picking_panic[j]].chr;
        D_8010EEE0_picking_panic[j]->unk01 = j;
        D_8010EEE0_picking_panic[j]->unk04 = (GwPlayer[D_8010EFC0_picking_panic[j]].stat & 1)
                                                 ? GwPlayer[D_8010EFC0_picking_panic[j]].cpu_difficulty
                                                 : -1;
    }
    for (i = 0; i < 4; i++) {
        if (D_8010EEE0_picking_panic[i]->unk04 != -1 &&
            D_8010EEE0_picking_panic[(i & 1) ? i - 1 : i + 1]->unk04 == -1) {
            D_8010EEE0_picking_panic[i]->unk04 += 4;
        }
    }
    func_8001AC8C_main(0, func_80109C00_picking_panic, 2);
    obj->func = func_80106020_picking_panic;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80105D3C_picking_panic);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E720_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E758_picking_panic);

void func_80106020_picking_panic(omObjData *obj) {
    s32 i;
    u8 j;

    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    D_8010EFA8_picking_panic++;
    D_8010EF7C_picking_panic++;
    func_800E6F40_minigame();
    switch (D_8010EF80_picking_panic) {
        case 0:
            if (D_8010EFA8_picking_panic == 2) {
                HuAudFXPlay(0x371);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_8010EF80_picking_panic = 1;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 1:
            if (D_8010EFA8_picking_panic == 33 && D_8010EFBE_picking_panic == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x38);
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010EF80_picking_panic = 2;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 2:
            if (D_8010EF14_picking_panic == 5 && func_800E6E8C_minigame() == 3) {
                if (D_8010EF15_picking_panic[0] == D_8010EF15_picking_panic[1]) {
                    D_8010EF80_picking_panic = 4;
                    D_8010EF14_picking_panic = 4;
                } else {
                    D_8010EF80_picking_panic = 3;
                    D_8010EF14_picking_panic = D_8010EF15_picking_panic[0] <= D_8010EF15_picking_panic[1];
                }
                D_8010EFA8_picking_panic = 0;
            }
            if (D_8010EF80_picking_panic != 3) {
                break;
            }
            /* fallthrough */
        case 3:
            if (D_8010EFA8_picking_panic == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010E5B0_picking_panic.unk06 = 1;
                D_8010E5B0_picking_panic.unk18 = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk00;
                D_8010E5B0_picking_panic.unk19[0] = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk00;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk00].bonusCoin = 10;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk00].bonusCoin = 10;
            }
            if (D_8010EFA8_picking_panic == 2) {
                func_800E6F34_minigame(30);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010EF80_picking_panic = 5;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 4:
            if (D_8010EFA8_picking_panic == 1) {
                D_8010E5B0_picking_panic.unk06 = 4;
                D_8010E5B0_picking_panic.unk22 = 75;
                D_8010E5B0_picking_panic.unk24 = 144;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010EF80_picking_panic = 6;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 5:
            if (D_8010EFA8_picking_panic == 31) {
                for (i = D_8010EF14_picking_panic * 2; i < D_8010EF14_picking_panic * 2 + 2; i++) {
                    PkChrTable sp10 = D_8010E758_picking_panic;

                    func_80017954_main(D_8010EF00_picking_panic[i]->model[1], 1,
                                       sp10.unk00[D_8010EEE0_picking_panic[i]->unk03], D_8010EEE0_picking_panic[i]->unk08);
                    func_8001C5B4_main(D_8010EF00_picking_panic[i]->model[1], D_8010EF00_picking_panic[i]->motion[4]);
                    func_80045ED0_main(D_8010EEE0_picking_panic[i]->unk0C);
                }
            }
            /* fallthrough */
        case 6:
            if (func_800E6E8C_minigame() == 5) {
                D_8010EF80_picking_panic = 7;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 7:
            if (D_8010EFA8_picking_panic == 1) {
                WipeCreateOut(0, 0x14);
            } else if (D_8010EFA8_picking_panic >= 32) {
                D_8010EFBE_picking_panic = 1;
            }
            break;
    }
    if (_CheckFlag(0xF) && D_800D530C_main == 0 && D_8010EFA5_picking_panic == 0 && D_8010EF80_picking_panic == 2U) {
        for (j = 0; j < 2; j++) {
            if (D_8010EEE0_picking_panic[j]->unk04 == -1 &&
                (D_800D5558_main[D_8010EEE0_picking_panic[j]->unk02] & 0x10)) {
                D_8010EFA5_picking_panic = 1;
            }
        }
    }
    if (D_8010EFBE_picking_panic == 0 && D_800D530C_main == 0 && D_8010EFA5_picking_panic == 0) {
        return;
    }
    if (D_800D530C_main != 0 && D_8010EFA5_picking_panic == 0) {
        D_8010EFA5_picking_panic = 1;
    }
    if (D_8010EFA5_picking_panic != 0) {
        if (D_8010EFA5_picking_panic == 1) {
            WipeCreateOut(0, 0x14);
            HuAudSeqFadeOut(0x14);
            func_8004AB0C_main(0x14);
        }
        D_8010EFA5_picking_panic++;
        if (D_8010EFA5_picking_panic < 25) {
            return;
        }
    }
    HuAudSeqFadeOut(0x1E);
    omOvlReturnEx(1);
}

#ifdef NON_MATCHING
void func_8010664C_picking_panic(omObjData *obj) {
    s32 sp10[10] = { 0x0030000A, 0x0030000B, 0x0030000C, 0x0030000D, 0x0030000E,
                     0x00000031, 0x002A0012, 0x0030000F, 0x00300011, 0x00300010 };
    s16 i;
    s16 j;

    for (i = 0; i < 10; i++) {
        D_8010EFF8_picking_panic[i] = func_8000B838_main(sp10[i]);
        D_8010EFD0_picking_panic[i] = InitEspriteSlot(D_8010EFF8_picking_panic[i], 0, 0);
        func_8000BB94_main(D_8010EFD0_picking_panic[i]);
    }
    obj->model[0] = func_8000B108_main(0x300000, 0x499);
    omSetTra(obj, 0.0f, -525.0f, -450.0f);
    omSetSca(obj, 1.75f, 1.75f, 1.75f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C8A8_main(obj->model[0], 1);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    Hu3DModelPosSet(obj->model[1], 0.0f, -525.0f, -450.0f);
    Hu3DModelScaleSet(obj->model[1], 1.75f, 1.75f, 1.75f);
    func_8001C814_main(obj->model[1], 1, 1);
    func_8001C8A8_main(obj->model[1], 2);
    for (i = 0; i < 2; i++) {
        obj->model[i + 4] = func_8000B108_main((i == 1) ? 0x300005 : 0x300006, 0x43D);
        Hu3DModelPosSet(obj->model[i + 4], (i == 0) ? 450.0f : 750.0f, (i == 0) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(obj->model[i + 4], 2.75f, 2.75f, 2.75f);
        func_8001C814_main(obj->model[i + 4], 2, 2);
        obj->model[i + 6] = Hu3DModelLink(obj->model[i + 4]);
        Hu3DModelPosSet(obj->model[i + 6], (i == 1) ? -450.0f : -750.0f, (i == 1) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(obj->model[i + 6], 2.75f, 2.75f, 2.75f);
        func_8001C814_main(obj->model[i + 6], 2, 2);
    }
    for (i = 0; i < 2; i++) {
        obj->model[i + 2] = func_8000B108_main(0x300001, 0x4B9);
        Hu3DModelPosSet(obj->model[i + 2], 890.0f, -222.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i + 2], 1.38125f, 1.3f, 1.3f);
        func_8001C814_main(obj->model[i + 2], 1, 1);
        func_8001C8A8_main(obj->model[i + 2], (i == 0) ? 1 : 2);
    }
    obj->model[32] = func_8000B108_main(0x300007, 0x499);
    Hu3DModelScaleSet(obj->model[32], 1.0f, 1.1f, 1.0f);
    for (i = 1; i < 6; i++) {
        obj->model[i + 32] = Hu3DModelLink(obj->model[32]);
        Hu3DModelScaleSet(obj->model[i + 32], 1.0f, 1.1f, 1.0f);
    }
    for (i = 0; i < 2; i++) {
        obj->model[i + 10] = func_8000B108_main(0x300009, 0x4BD);
        Hu3DModelPosSet(obj->model[i + 10], -855.0f, 125.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i + 10], 2.0f, 2.0f, 2.0f);
        func_8001C8A8_main(obj->model[i + 10], (i == 0) ? 1 : 2);
    }
    obj->model[8] = func_8000B108_main(0x300008, 0x4B9);
    obj->model[9] = Hu3DModelLink(obj->model[8]);
    obj->model[12] = func_8000B108_main(0x300002, 0x4B9);
    for (i = 1; i < 20; i++) {
        obj->model[i + 12] = Hu3DModelLink(obj->model[12]);
    }
    {
    f32 sp38[10] = { -510.0f, -555.0f, -663.0f, -692.0f, -797.0f, -823.0f, -947.0f, -1012.0f, -1121.0f, -1169.0f };
    f32 sp60[10] = { 449.0f, 331.0f, 470.0f, 341.0f, 237.0f, 403.0f, 293.0f, 409.0f, 276.0f, 432.0f };
    f32 zero = 0.0f;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DModelPosSet(obj->model[(j == 0) ? i + 12 : i + 22], sp38[i] / 4687.5 * 5187.5,
                            sp60[i] / 4687.5 * 5187.5, -500.0f);
            Hu3DModelPosSet(obj->model[(j == 0) ? i + 12 : i + 22], zero, zero, -500.0f);
            func_8001C814_main(obj->model[(j == 0) ? i + 12 : i + 22], 1, 1);
            func_8001C8A8_main(obj->model[(j == 0) ? i + 12 : i + 22], (j == 0) ? 1 : 2);
        }
    }
    }
    obj->func = func_80106E84_picking_panic;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E798_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7C0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7E8_picking_panic);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010664C_picking_panic);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106E84_picking_panic);

#ifdef NON_MATCHING
void func_80107A48_picking_panic(void) {
    f32 sp10[2];
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *spr;
    f32 lo;
    f32 hi;
    f32 scl;
    f32 cx;
    f32 cy;
    s32 i;
    s32 row;
    s32 col;
    s32 vp;
    s32 w;
    s32 h;
    s32 dx;
    f32 *p;

    lo = (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f;
    hi = (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f;
    gSPDisplayList(gMainGfxPos++, D_8010E5E0_picking_panic);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);

    /* Two 161x160 / 160x160 background halves, drawn in 40x40 tiles. */
    for (i = 0; i < 2; i++) {
        spr = HuSprGet(D_800CD1DC_main[*((i != 0) ? &D_8010EFD0_picking_panic[1] : &D_8010EFD0_picking_panic[0])].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        for (col = 0; col < 4; col++) {
            for (row = 0; row < 3; row++) {
                w = ((i == 1) & (col == 3)) ? 40 : 41;
                h = (row != 2) ? 41 : 40;
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 161 : 160, 0,
                                   col * 40, row * 40, col * 40 + w, row * 40 + h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                for (vp = 0; vp < 2; vp++) {
                    if (vp == 0) {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                    } else {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                    }
                    gSPScisTextureRectangle(
                        gMainGfxPos++,
                        (s32)((col * 40 + i * 160) * 4 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                        (s32)((vp * 120 + row * 40) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                        (s32)((col * 40 + i * 160 + w) * 4 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                        (s32)((vp * 120 + row * 40 + h) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                        0, (col * 40) << 5, (row * 40) << 5, (s32)(D_8010EFEC_picking_panic[vp] * 1024.0f),
                        (s32)(D_8010EF8C_picking_panic[vp] * 1024.0f));
                }
            }
        }
    }
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);

    /* Counter item rising: progress of each team's next item. */
    cx = 51.0f;
    cy = 64.0f;
    scl = 0.2875f;
    for (i = 0; i < 2; i++) {
        p = &sp10[i];
        if (D_8010EF10_picking_panic[i] >= 26) {
            if (D_8010EF10_picking_panic[i] < 30) {
                *p = (D_8010EF10_picking_panic[i] - 26) / 4.0;
            } else if (D_8010EF10_picking_panic[i] < 37) {
                *p = 1.0f;
            } else if (D_8010EF10_picking_panic[i] < 45) {
                *p = (D_8010EF10_picking_panic[i] - 37) / 7.0;
            } else {
                *p = 0.0f;
            }
        } else {
            *p = 0.0f;
        }
        if (D_8010EF10_picking_panic[i] - 37 < 8u) {
            sp10[i] = (1.0f - sp10[i] * sp10[i]) * 0.75 + (1.0f - sp10[i]) * 0.25;
        }
        if (D_8010EF10_picking_panic[i] == 26) {
            func_8001C258_main(D_8010EEFC_picking_panic->model[i + 10], 4, 0);
            func_8001C6A8_main(D_8010EEFC_picking_panic->model[i + 10], 0.0f);
            func_8001C814_main(D_8010EEFC_picking_panic->model[i + 10], 3, 0);
            func_8010B11C_picking_panic(D_8010EEFC_picking_panic->model[i + 10], 0);
        }
        if (D_8010EF10_picking_panic[i] == 27) {
            func_8001C258_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 4, 0);
            func_8001C6A8_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 0.0f);
            func_8001C814_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 1, 1);
        }
        if (D_8010EF10_picking_panic[i] - 26 < 5u) {
            Hu3DModelPosSet(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], -855.0f,
                            (1.0f - sp10[i]) * 175.0f + -25.0f, 0.0f);
        }
        if (D_8010EF10_picking_panic[i] == 30) {
            func_8001C6A8_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 0.0f);
            func_8001C814_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 1, 0);
        }
        if (D_8010EF10_picking_panic[i] - 10 < 11u) {
            D_8010EF84_picking_panic[i] = sindf((D_8010EF10_picking_panic[i] - 10) / 15.0 * 1440.0) * 0.625;
        }
    }

    /* The counter's item panel, 64x97 in four loads, scaled by scl. */
    if (sp10[0] != 0.0f || sp10[1] != 0.0f) {
        spr = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[4]].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        for (row = 0; row < 4; row++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 0, 0, row * 24, 64,
                               (row < 3) ? row * 24 + 25 : row * 24 + 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (vp = 0; vp < 2; vp++) {
                if (sp10[vp] == 0.0f) {
                    continue;
                }
                if (vp == 0) {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                } else {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                }
                gSPScisTextureRectangle(
                    gMainGfxPos++,
                    (s32)((cx - scl * 32.0f) * 4.0 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)((cy + sp10[vp] * 21.0f - 48.0f + (row * 24) * scl + (vp * 120)) * 4.0 *
                              D_8010EFC4_picking_panic[vp] +
                          D_8010EFAC_picking_panic[vp]),
                    (s32)((cx + scl * 32.0f) * 4.0 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)((cy + sp10[vp] * 21.0f - 48.0f + ((row < 3) ? row * 24 + 25 : row * 24 + 23) * scl +
                           (vp * 120)) *
                              4.0 * D_8010EFC4_picking_panic[vp] +
                          D_8010EFAC_picking_panic[vp]),
                    0, 0, (row * 24) << 5, (s32)(1024.0f / scl * D_8010EFEC_picking_panic[vp]),
                    (s32)(1024.0f / scl * D_8010EF8C_picking_panic[vp]));
            }
        }
    }

    /* The two score boards (CI8 115x48 and RGBA16 108x48), the first shaking with D_8010EF84. */
    for (i = 0; i < 2; i++) {
        spr = HuSprGet(D_800CD1DC_main[*((i != 0) ? &D_8010EFD0_picking_panic[3] : &D_8010EFD0_picking_panic[2])].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        if (i == 0) {
            gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        }
        for (col = 0; col < 3; col++) {
            w = ((i == 1) & (col == 2)) ? 32 : 39;
            if (i == 0) {
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 115 : 108, 0,
                                   col * 38, 0, col * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_RGBA, G_IM_SIZ_16b, (i == 0) ? 115 : 108,
                                   0, col * 38, 0, col * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            }
            for (vp = 0; vp < 2; vp++) {
                dx = 0;
                if (i == 0) {
                    dx = D_8010EF84_picking_panic[vp] * 4.0;
                }
                if (vp == 0) {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                } else {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                }
                gSPScisTextureRectangle(
                    gMainGfxPos++,
                    (s32)(((col * 38 + i * 212) * 4 + dx) * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)(vp * 120 * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                    (s32)(((col * 38 + i * 212 + w) * 4 + dx) * D_8010EEF4_picking_panic[vp] +
                          D_8010EF9C_picking_panic[vp]),
                    (s32)((vp * 120 + 48) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]), 0,
                    (col * 38) << 5, 0, (s32)(D_8010EFEC_picking_panic[vp] * 1024.0f),
                    (s32)(D_8010EF8C_picking_panic[vp] * 1024.0f));
            }
        }
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80107A48_picking_panic);
#endif

#ifdef NON_MATCHING
void func_80109C00_picking_panic(Gfx **arg0, s32 arg1, s32 arg2) {
    s32 sp10[2][7] = {
        { 23, 39, 25, 36, 20, 42, 0x400 },
        { 129, 145, 131, 142, 126, 148, 0x400 },
    };
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *spr;
    s32 alpha;
    f32 lo;
    f32 hi;
    f32 split;
    f32 f;
    s32 k;
    s32 vp;
    s32 i;
    s32 w;
    s32 other;

    alpha = 255;
    lo = (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f;
    hi = (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f;
    D_8010E628_picking_panic = D_8010E628_picking_panic == 0;
    split = D_8010EF78_picking_panic * 240.0f;
    if (D_8010E628_picking_panic != 0) {
        return;
    }
    /* The winners' half slides over the losers' at the end. */
    if (D_8010EF14_picking_panic < 2 && D_8010EFA4_picking_panic < 255) {
        f = 1.0 - D_8010EFA4_picking_panic / 46.0;
        other = 1 - D_8010EF14_picking_panic;
        f = (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f;
        for (k = 0; k < 6; k++) {
            sp10[D_8010EF14_picking_panic][k] -= D_8010EF14_picking_panic * f * 101.0f;
            sp10[other][k] = sp10[other][k] * (1.0f - f) + other * f * 240.0f;
        }
        if (1.0f - f <= 0.0625) {
            sp10[other][6] = 0x3FFF;
        } else {
            sp10[other][6] = 1024.0f / (1.0f - f);
        }
        alpha = (1.0f - f) * 255.0f;
    }
    gSPDisplayList(gMainGfxPos++, D_8010E5E0_picking_panic);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0xDA, alpha * 212 / 255);
    gDPSetCombine(gMainGfxPos++, 0xFF97FF, 0xFF2DFEFF);
    spr = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[9]].unk04, 0);
    frame = &spr->unk_84->unk00[spr->unk_90];
    for (vp = 0; vp < 2; vp++) {
        if (vp == 0) {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
        } else {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
        }
        gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_I, G_IM_SIZ_8b, 60, 0, 0, 0, 60, 22, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gSPScisTextureRectangle(gMainGfxPos++, 239 * 4, sp10[vp][4] * 4, 299 * 4, sp10[vp][5] * 4, 0, 0, 0, 0x400,
                                sp10[vp][6]);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);
    gDPSetCombine(gMainGfxPos++, 0xFFFFFF, 0xFFFCF279);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetCombine(gMainGfxPos++, 0xFF97FF, 0xFF2CFE7F);
    gDPPipeSync(gMainGfxPos++);

    /* Team icons (16x16, 12x12) and the two score digits. */
    for (i = 0; i < 4; i++) {
        spr = HuSprGet(D_800CD1DC_main[*((i != 0) ? ((i == 1) ? &D_8010EFD0_picking_panic[6] : &D_8010EFD0_picking_panic[5])
                                                  : &D_8010EFD0_picking_panic[7])]
                           .unk04,
                       0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        if (i < 2) {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, spr->unk_84->unk0C);
        } else {
            gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        }
        for (vp = 0; vp < 2; vp++) {
            if (vp == 0) {
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
            } else {
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
            }
            if (i == 3 && D_8010EF15_picking_panic[vp] < 10) {
                continue;
            }
            if (i < 2) {
                w = (i == 0) ? 16 : 12;
            } else {
                if (i == 2) {
                    w = (D_8010EF15_picking_panic[vp] >= 10) ? D_8010EF15_picking_panic[vp] / 10 : D_8010EF15_picking_panic[vp];
                } else {
                    w = D_8010EF15_picking_panic[vp] % 10;
                }
                frame = &spr->unk_84->unk00[w];
            }
            if (i < 2) {
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, w, 0, 0, 0, w, w, 0,
                                      G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                      G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 12, 0, 0, 0, 12, 12, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            }
            if (i == 0) {
                gSPScisTextureRectangle(gMainGfxPos++, 243 * 4, sp10[vp][0] * 4, 258 * 4, sp10[vp][1] * 4, 0, 0, 0,
                                        0x400, sp10[vp][6]);
            } else {
                gSPScisTextureRectangle(gMainGfxPos++, (i * 12 + 249) * 4, sp10[vp][2] * 4, (i * 12 + 260) * 4,
                                        sp10[vp][3] * 4, 0, 0, 0, 0x400, sp10[vp][6]);
            }
        }
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);
    gDPSetCombine(gMainGfxPos++, 0xFFFFFF, 0xFFFCF279);

    /* The divider between the two halves. */
    spr = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[8]].unk04, 0);
    frame = &spr->unk_84->unk00[spr->unk_90];
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, spr->unk_84->unk0C);
    gDPPipeSync(gMainGfxPos++);
    gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 320, 0, 0, 0, 320, 6, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
    if (D_8010EF78_picking_panic > 0.0f) {
        gSPScisTextureRectangle(gMainGfxPos++, 0, (s32)(split - 3.0f) * 4, 320 * 4, (s32)(split + 3.0f) * 4, 0, 0, 0,
                                0x400, 0x400);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 0xFF, 0xFF, 0xFF, 0x00);
    gDPPipeSync(gMainGfxPos++);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E990_picking_panic);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80109C00_picking_panic);
#endif

void func_8010B11C_picking_panic(s16 model, s16 frame) {
    HmfModel *m = &HmfModelData[model];

    *(f32 *)&m->hmf->unk98->unk08 = frame;
}

void func_8010B160_picking_panic(omObjData *obj) {
    func_8010B220_picking_panic(obj, 0);
    obj->func = func_8010B8D0_picking_panic;
}

void func_8010B194_picking_panic(omObjData *obj) {
    func_8010B220_picking_panic(obj, 1);
    obj->func = NULL;
}

void func_8010B1C0_picking_panic(omObjData *obj) {
    func_8010B220_picking_panic(obj, 2);
    obj->func = func_8010B8EC_picking_panic;
}

void func_8010B1F4_picking_panic(omObjData *obj) {
    func_8010B220_picking_panic(obj, 3);
    obj->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B220_picking_panic);

void func_8010B8D0_picking_panic(omObjData *obj) {
    func_8010B908_picking_panic(obj, 0);
}

void func_8010B8EC_picking_panic(omObjData *obj) {
    func_8010B908_picking_panic(obj, 1);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E9E0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA20_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA40_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA80_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA8C_picking_panic);

#ifdef NON_MATCHING
void func_8010B908_picking_panic(omObjData *arg0, s8 arg1) {
    PkCpuTable tbl;
    f32 sp38[11];
    PkPlayer *p0;
    PkPlayer *p1;
    omObjData *o0;
    omObjData *o1;
    u8 i0;
    u8 i1;
    f32 prevY;
    HmfModel *m;
    s32 i;
    s32 j;
    s32 k;
    s32 t;
    u32 ut;
    s32 se;
    s16 mdl;
    f32 dir;
    f32 baseX;
    f32 x;
    f32 y;
    f32 rot;
    f32 c;
    f32 s;
    f32 f;
    f32 g;
    f32 wall;
    f32 h;
    f32 h2;
    f32 ang;
    f32 spd;

    p0 = D_8010EEE0_picking_panic[arg1 * 2];
    p1 = D_8010EEE0_picking_panic[arg1 * 2 + 1];
    o0 = D_8010EF00_picking_panic[arg1 * 2];
    o1 = D_8010EF00_picking_panic[arg1 * 2 + 1];
    i0 = arg1 * 2;
    i1 = arg1 * 2 + 1;
    tbl = D_8010EA8C_picking_panic;

    if (arg1 == 0 && D_8010E6EC_picking_panic == 45) {
        for (i = 1; i < 6; i++) {
            D_8010E718_picking_panic[i] = rand8() / 110;
        }
    }
    if (arg1 == 0) {
        D_8010EF94_picking_panic -= (D_8010EF94_picking_panic > 0.0f) ? 1.0f : 0.0f;
    }
    if (arg1 == 0 && D_8010EF94_picking_panic == 0.0f && D_8010EF80_picking_panic == 2 &&
        D_8010E6EC_picking_panic % 60 == 46) {
        D_8010EF94_picking_panic = 60.0f;
    }
    if (arg1 == 0) {
        t = D_8010E6EC_picking_panic % 30;
        t = (t < 16) ? t : 30 - t;
        if (D_8010E62C_picking_panic[0][t] == 0.0f) {
            f32 sx = 0.0f;
            f32 sy = 0.0f;
            f64 amp = sindf(t * 90.0 / 15.0) * 80.0f;

            for (i = 0; i < 3; i++) {
                D_8010E62C_picking_panic[i][t] = amp * (i * 0.125 / 3.0 + 0.875) + 270.0;
                sx += cosdf(D_8010E62C_picking_panic[i][t]) * 110.0f;
                sy += sindf(D_8010E62C_picking_panic[i][t]) * 110.0f;
                D_8010EC20_picking_panic[i][t] = sx;
                D_8010ECE0_picking_panic[i][t] = sy;
            }
        }
        for (i = 0; i < 2; i++) {
            dir = (D_8010E6EC_picking_panic % 60 < 30) ? 1.0f : -1.0f;
            baseX = (i == 0) ? -500.0f : 500.0f;
            ut = D_8010E6EC_picking_panic % 30;
            t = (ut < 16) ? ut : 30 - ut;
            if (i != 0) {
                dir = -dir;
            }
            for (j = 0; j < 3; j++) {
                Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(i == 0) ? j + 32 : j + 35],
                                baseX + dir * D_8010EC20_picking_panic[j][t],
                                D_8010ECE0_picking_panic[j][t] + 250.0f, 0.0f);
                Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(i == 0) ? j + 32 : j + 35], 0.0f, 0.0f,
                                (D_8010E62C_picking_panic[j][t] - 270.0f) * dir);
            }
            x = baseX + dir * D_8010EC20_picking_panic[2][t];
            y = D_8010ECE0_picking_panic[2][t] + 250.0f;
            rot = (D_8010E62C_picking_panic[2][t] - 270.0f) * dir;
            Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(i != 0) ? 9 : 8], x, y, 0.0f);
            Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(i == 0) ? 8 : 9], 0.0f, 0.0f, rot);
            rot += (i == 0) ? 35.0f : -35.0f;
            if (D_8010EF80_picking_panic == 0 && D_8010EFA8_picking_panic < 45) {
                if (D_8010EFA8_picking_panic >= 30) {
                    f = 180.0 - (D_8010EFA8_picking_panic + 30) * 180.0 / 15.0;
                } else {
                    f = 180.0f;
                }
                if (i != 0) {
                    rot += f;
                } else {
                    rot -= f;
                }
            }
            c = cosdf(rot + 270.0f + ((i == 0) ? -14.0f : 14.0f));
            s = sindf(rot + 270.0f + ((i == 0) ? -14.0f : 14.0f));
            if (!(i & 1)) {
                D_8010EE80_picking_panic = -D_8010EE70_picking_panic;
                D_8010EE84_picking_panic = -D_8010EE74_picking_panic;
                D_8010EE70_picking_panic = x + c * 86.0f;
                D_8010EE74_picking_panic = y + s * 86.0f;
                D_8010EE80_picking_panic += D_8010EE70_picking_panic;
                D_8010EE84_picking_panic += D_8010EE74_picking_panic;
            } else {
                D_8010EE78_picking_panic = x + c * 86.0f;
                D_8010EE7C_picking_panic = y + s * 86.0f;
            }
            x -= c * 86.0f;
            y -= s * 86.0f;
            omSetTra(D_8010EF00_picking_panic[i], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[i], 0.0f, (i == 0) ? -90.0f : 90.0f, rot + 180.0f);
            omSetTra(D_8010EF00_picking_panic[i + 2], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[i + 2], 0.0f, (i == 0) ? -90.0f : 90.0f, rot + 180.0f);
            if (D_8010EF80_picking_panic >= 3 && D_8010EF14_picking_panic < 2) {
                s32 n = 16;
                s32 vx = 13;
                s32 vy = 36;
                s32 w = D_8010EF14_picking_panic * 2;

                if (i == 0 && D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    D_8010EE88_picking_panic += D_8010EE94_picking_panic;
                    D_8010EE8C_picking_panic += D_8010EE98_picking_panic;
                    D_8010EE98_picking_panic -= 6.25;
                }
                if (D_8010EFA4_picking_panic == 255 && D_8010E6EC_picking_panic % 60 == 7) {
                    D_8010EFA4_picking_panic = n + 30;
                    D_8010EE88_picking_panic = x;
                    D_8010EE94_picking_panic = vx;
                    D_8010EE8C_picking_panic = y;
                    D_8010EE98_picking_panic = vy;
                    D_8010EE90_picking_panic = rot;
                    for (j = 0; j < 2; j++) {
                        func_8001C258_main(D_8010EF00_picking_panic[w + j]->model[0], 4, 4);
                        func_8001C258_main(D_8010EF00_picking_panic[w + j]->model[1], 4, 0);
                        func_8001C624_main(D_8010EF00_picking_panic[w + j]->model[1],
                                           HmfModelData[D_8010EF00_picking_panic[w + j]->motion[2]].unk02, 50, n, 0);
                    }
                }
                if (D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    f = (f32)(D_8010EFA4_picking_panic - 30) / (f32)n;
                    g = f * f * 0.5 + f * 0.5;
                    Hu3DModelPosSet(D_8010EF00_picking_panic[w + i]->model[1],
                                    (i != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[w + i]->model[1], 0.0f,
                                    (i == 0) ? -(f * 45.0f + 45.0f) : f * 45.0f + 45.0f,
                                    (i != 0) ? -(g * D_8010EE90_picking_panic + (1.0f - g) * 180.0f) + 180.0f
                                             : g * D_8010EE90_picking_panic + (1.0f - g) * 180.0f + 180.0f);
                }
                if (D_8010EFA4_picking_panic < 31) {
                    f = (D_8010EFA4_picking_panic - 1) / 10.0;
                    if (f > 1.0f) {
                        f = 45.0f;
                    } else {
                        f = (f < 0.0f) ? 0.0f : f * 45.0f;
                    }
                    Hu3DModelPosSet(D_8010EF00_picking_panic[w + i]->model[1],
                                    (i != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[w + i]->model[1], 0.0f, (i == 0) ? -f : f,
                                    (i == 0) ? 360.0f : 0.0f);
                }
                if (D_8010EFA4_picking_panic == 30) {
                    func_8004AC98_main(D_8010EEE0_picking_panic[w + i]->unk03 + 50,
                                       D_8010EEE0_picking_panic[w + i]->unk00);
                    func_8001C5B4_main(D_8010EF00_picking_panic[w + i]->model[1],
                                       D_8010EF00_picking_panic[w + i]->motion[3]);
                    func_8001C6A8_main(D_8010EF00_picking_panic[w + i]->model[1], 2.0f);
                    func_8001C814_main(D_8010EF00_picking_panic[w + i]->model[1], 3, 0);
                }
                if (D_8010EFA4_picking_panic == 26) {
                    func_8001C624_main(D_8010EF00_picking_panic[w + i]->model[1],
                                       HmfModelData[D_8010EF00_picking_panic[w + i]->motion[0]].unk02, 0, 20, 2);
                }
                if (i == 1 && D_8010EFA4_picking_panic < 255) {
                    if (D_8010EFA4_picking_panic == i) {
                        for (j = 0; j < 3; j++) {
                            func_8001C258_main(D_8010EEFC_picking_panic->model[j + 32], 4, 4);
                            func_8001C258_main(D_8010EEFC_picking_panic->model[j + 35], 4, 4);
                        }
                        func_8001C258_main(D_8010EEFC_picking_panic->model[8], 4, 4);
                        func_8001C258_main(D_8010EEFC_picking_panic->model[9], 4, 4);
                    }
                    D_8010EFA4_picking_panic = (D_8010EFA4_picking_panic != 0) ? D_8010EFA4_picking_panic - 1 : 0;
                }
            }
        }
    }

    m = &HmfModelData[D_8010EEFC_picking_panic->model[arg1 + 10]];
    if (m->unk40 >= 60.0f) {
        m->unk40 = 0.0f;
        func_8001C258_main(D_8010EEFC_picking_panic->model[arg1 + 10], 4, 4);
    }
    D_8010EF10_picking_panic[arg1] =
        (D_8010EF10_picking_panic[arg1] < 46 && D_8010EF10_picking_panic[arg1] != 0) ? D_8010EF10_picking_panic[arg1] + 1 : 0;
    if (D_8010EF80_picking_panic == 0 || (D_8010EF80_picking_panic == 1 && D_8010EFA8_picking_panic < 45)) {
        D_8010EF10_picking_panic[arg1] = 1;
    }
    if (D_8010EF10_picking_panic[arg1] == 15) {
        if (D_8010E6F0_picking_panic[arg1][(D_8010EEF0_picking_panic[arg1] + 1) % 4] == 0) {
            D_8010EEF0_picking_panic[arg1] = (D_8010EEF0_picking_panic[arg1] + 1) % 4;
            D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] = 1;
            if (D_8010E714_picking_panic[arg1] < 6) {
                D_8010EF98_picking_panic[arg1] = D_8010E718_picking_panic[D_8010E714_picking_panic[arg1]];
            } else {
                t = rand8();
                D_8010EF98_picking_panic[arg1] =
                    (u32)(t % (((D_8010EF15_picking_panic[arg1] >= 4) &&
                                (D_8010EF15_picking_panic[arg1] - D_8010EF15_picking_panic[1 - arg1] >= 4)) + 5)) >> 1;
            }
            if (D_8010EF98_picking_panic[arg1] == 2 && D_8010EF15_picking_panic[arg1] == 0 &&
                D_8010E5B0_picking_panic.unk1E < 451) {
                D_8010EF98_picking_panic[arg1] = 0;
            }
            D_8010E714_picking_panic[arg1] = (D_8010E714_picking_panic[arg1] < 6) ? D_8010E714_picking_panic[arg1] + 1 : D_8010E714_picking_panic[arg1];
        } else {
            D_8010EF10_picking_panic[arg1]--;
        }
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk00 = (D_8010E704_picking_panic[arg1].unk00 > 0) ? D_8010E704_picking_panic[arg1].unk00 - 1 : D_8010E704_picking_panic[arg1].unk00;
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk06 = (D_8010E704_picking_panic[arg1].unk06 > 0) ? D_8010E704_picking_panic[arg1].unk06 - 1 : D_8010E704_picking_panic[arg1].unk06;
    }

    /* Front player: hook the next item at the counter. */
    if (D_8010EF80_picking_panic == 2 && D_8010E700_picking_panic[i0] == -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] == 1 && D_8010EF98_picking_panic[arg1] != -1 &&
        ((D_8010EF10_picking_panic[arg1] == 0) | (D_8010EF10_picking_panic[arg1] >= 30)) &&
        ((p0->unk04 == -1) ? (D_800D5558_main[p0->unk02] & 0x8000) : (D_8010E704_picking_panic[arg1].unk00 == 0))) {
        f = D_8010EE70_picking_panic - -855.0f;
        g = D_8010EE74_picking_panic - -25.0f;
        if (f * f + g * g < 17929.21) {
            k = D_8010EEF0_picking_panic[arg1];
            D_8010E700_picking_panic[i0] = k;
            D_8010E6F0_picking_panic[arg1][k] = 2;
            D_8010EDA0_picking_panic[arg1][k] = D_8010EF98_picking_panic[arg1];
            D_8010EF98_picking_panic[arg1] = -1;
            D_8010EF10_picking_panic[arg1] = 1;
            D_8010E6F8_picking_panic[i0] = 6;
            D_8010E6FC_picking_panic[i0] = 23;
            func_8001EF6C_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], o0->model[0], "item_hook");
            func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0x4000);
            if (p0->unk04 != -1) {
                D_8010E704_picking_panic[arg1].unk00 = (rand8() < tbl.unk00[p0->unk04]) ? 2 : 1;
                D_8010E704_picking_panic[arg1].unk02 = rand8() % (tbl.unk08[p0->unk04] * 2) - tbl.unk08[p0->unk04];
            }
            if (p1->unk04 != -1) {
                D_8010E704_picking_panic[arg1].unk04 = tbl.unk10[p1->unk04];
            }
            t = D_8010EDA0_picking_panic[arg1][k];
            if (t == 0) {
                se = 0x36F;
            } else if (t == 1) {
                se = 0x36C;
            } else {
                se = 0x370;
            }
            func_8004AC98_main(se, arg1 * 2);
            omVibrate(p0->unk00, 2, 3, 10);
        }
    }
    /* Back player: hook a thrown item. */
    if (D_8010EF80_picking_panic == 2 && D_8010E700_picking_panic[i1] == -1 &&
        ((p1->unk04 == -1) ? (D_800D5558_main[p1->unk02] & 0x8000) : (rand8() < D_8010E704_picking_panic[arg1].unk04))) {
        for (j = 0; j < 4; j++) {
            if (D_8010E6F0_picking_panic[arg1][j] == 3) {
                f = D_8010EE78_picking_panic - D_8010EDB0_picking_panic[arg1][j];
                g = D_8010EE7C_picking_panic - D_8010EDD0_picking_panic[arg1][j];
                if (f * f + g * g < 16900.0) {
                    D_8010E700_picking_panic[i1] = j;
                    D_8010E6F0_picking_panic[arg1][j] = 4;
                    D_8010E6F8_picking_panic[i1] = 6;
                    D_8010E6FC_picking_panic[i1] = 23;
                    Hu3DModelPosSet(((j & 1) ? o1 : o0)->model[(j / 2 != 0) ? D_8010EDA0_picking_panic[arg1][j] + 5 : D_8010EDA0_picking_panic[arg1][j] + 2],
                                    0.0f, 0.0f, 0.0f);
                    func_8001EF6C_main(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], o1->model[0], "item_hook");
                    func_8001C258_main(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], 0x4000, 0x4000);
                    if (p1->unk04 != -1) {
                        D_8010E704_picking_panic[arg1].unk06 = rand8() < tbl.unk18[p1->unk04];
                    }
                    t = D_8010EDA0_picking_panic[arg1][j];
                    if (t == 0) {
                        se = 0x36F;
                    } else if (t == 1) {
                        se = 0x36C;
                    } else {
                        se = 0x370;
                    }
                    func_8004AC98_main(se, arg1 * 2 + 1);
                    omVibrate(p1->unk00, 2, 3, 10);
                    break;
                }
            }
        }
    }

    /* Front player: throw the hooked item. */
    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[i0] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[i0]] == 2 &&
        (D_8010EF80_picking_panic != 2 ||
         ((p0->unk04 == -1) ? !((u16)D_800CDA7C_main[p0->unk02] & 0x8000)
                            : (D_8010E6EC_picking_panic % 60 == (D_8010E704_picking_panic[arg1].unk02 + 68) % 60)))) {
        if (o0->rot.z > 210.0f) {
            f = 0.0f;
        } else if (o0->rot.z > 160.0f) {
            f = 1.0f;
        } else {
            f = (210.0f - o0->rot.z) / 50.0f;
        }
        k = D_8010E700_picking_panic[i0];
        D_8010E700_picking_panic[i0] = -1;
        D_8010E6F0_picking_panic[arg1][k] = 3;
        D_8010EDB0_picking_panic[arg1][k] = D_8010EE70_picking_panic;
        D_8010EDD0_picking_panic[arg1][k] = D_8010EE74_picking_panic;
        D_8010EDF0_picking_panic[arg1][k] = 0.0f;
        D_8010EE50_picking_panic[arg1][k] = 0.0f;
        if (D_8010EF80_picking_panic == 2) {
            D_8010EE10_picking_panic[arg1][k] =
                ((D_8010EE80_picking_panic * 0.875 - 5.0) * f + (1.0f - f) * 24.25) *
                (D_8010EDA0_picking_panic[arg1][k] * 0.15 + 0.85);
            D_8010EE30_picking_panic[arg1][k] =
                ((D_8010EE84_picking_panic * 0.875 + 10.0) * f + (1.0f - f) * 57.5) *
                (D_8010EDA0_picking_panic[arg1][k] * 0.15 + 0.85);
        } else {
            D_8010EE10_picking_panic[arg1][k] = D_8010EE30_picking_panic[arg1][k] = 0.0f;
        }
        func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0);
        D_8010E6F8_picking_panic[i0] = 18;
        D_8010E6FC_picking_panic[i0] = 0;
        func_8004AC98_main(0x36D, arg1 * 2);
    }
    /* Back player: throw the hooked item into the basket. */
    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[i1] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[i1]] == 4 &&
        (D_8010EF80_picking_panic != 2 ||
         ((p1->unk04 == -1) ? !((u16)D_800CDA7C_main[p1->unk02] & 0x8000)
                            : (D_8010E704_picking_panic[arg1].unk06 == 0 &&
                               ((D_8010E6EC_picking_panic % 60 - 43 < 5u && (u8)(rand8() % 3) == 0) ||
                                D_8010E6EC_picking_panic % 60 == 48))))) {
        f32 sp38init[11] = { 30.0f, 30.0f, 26.0f, 25.0f, 24.0f, 26.0f, 23.0f, 23.0f, 25.5f, 26.0f, 30.0f };
        f64 d;

        t = (D_8010E6EC_picking_panic + 15) % 60;
        t = (t - 30 > 0) ? 60 - t : t;
        k = D_8010E700_picking_panic[i1];
        D_8010E700_picking_panic[i1] = -1;
        D_8010E6F0_picking_panic[arg1][k] = 5;
        D_8010EDB0_picking_panic[arg1][k] = D_8010EE78_picking_panic;
        D_8010EDD0_picking_panic[arg1][k] = D_8010EE7C_picking_panic;
        D_8010EDF0_picking_panic[arg1][k] = 0.0f;
        D_8010EDA8_picking_panic[arg1][k] = 0;
        D_8010EE50_picking_panic[arg1][k] = 0.0f;
        d = (t - 7 < 11u) ? sp38init[t - 7] : 23.0;
        D_8010EE10_picking_panic[arg1][k] = d * ((t >= 5 && t < 14) ? (t - 5) / 9.0 : (t >= 5 && t < 22) ? 1.0 - (t - 14) / 8.0 : 0.0);
        if (t >= 5 && t < 14) {
            D_8010EE30_picking_panic[arg1][k] = (t - 5) / 9.0 * 60.0;
        } else if (t >= 5 && t < 22) {
            D_8010EE30_picking_panic[arg1][k] = (1.0 - (t - 14) / 8.0) * 60.0;
        } else {
            D_8010EE30_picking_panic[arg1][k] = 0.0f;
        }
        func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0);
        D_8010E6F8_picking_panic[i1] = 18;
        D_8010E6FC_picking_panic[i1] = 0;
        func_8004AC98_main(0x36D, arg1 * 2 + 1);
    }

    /* Ease the two arm motions towards their targets. */
    for (i = 0; i < 2; i++) {
        k = arg1 * 2 + i;
        if (D_8010E6F8_picking_panic[k] < D_8010E6FC_picking_panic[k]) {
            if (D_8010E6F8_picking_panic[k] + 2 <= D_8010E6FC_picking_panic[k]) {
                D_8010E6F8_picking_panic[k] = D_8010E6F8_picking_panic[k] + 2;
            } else {
                D_8010E6F8_picking_panic[k] = D_8010E6FC_picking_panic[k];
            }
        } else if (D_8010E6F8_picking_panic[k] > D_8010E6FC_picking_panic[k]) {
            if (D_8010E6F8_picking_panic[k] - 2 >= D_8010E6FC_picking_panic[k]) {
                D_8010E6F8_picking_panic[k] = D_8010E6F8_picking_panic[k] - 2;
            } else {
                D_8010E6F8_picking_panic[k] = D_8010E6FC_picking_panic[k];
            }
        }
        func_8001C6A8_main(D_8010EF00_picking_panic[k]->model[0], D_8010E6F8_picking_panic[k]);
    }

    /* Thrown items in flight. */
    for (j = 0; j < 4; j++) {
        prevY = D_8010EDD0_picking_panic[arg1][j];
        if (D_8010E6F0_picking_panic[arg1][j] == 3 || D_8010E6F0_picking_panic[arg1][j] == 5) {
            mdl = ((j & 1) ? o1 : o0)->model[(j / 2 != 0) ? D_8010EDA0_picking_panic[arg1][j] + 5 : D_8010EDA0_picking_panic[arg1][j] + 2];
            i = 2;
            D_8010EE30_picking_panic[arg1][j] -= 6.25;
            if (D_8010E6F0_picking_panic[arg1][j] == 5) {
                x = D_8010EDB0_picking_panic[arg1][j] + D_8010EE10_picking_panic[arg1][j];
                y = D_8010EDD0_picking_panic[arg1][j] + D_8010EE30_picking_panic[arg1][j];
                for (i = 0; i < 2; i++) {
                    wall = (i == 0) ? 827.0f : 953.0f;
                    if (y - 47.5 < -152.0 && -292.0 < y + 47.5 && x - 47.5 < wall && wall < x + 47.5) {
                        h2 = 2256.25 - (wall - x) * (wall - x);
                        h = (h2 <= 0.0f) ? 0.0f : HuSqrtf(h2);
                        if (y - h < -152.0f && y + h > -292.0f) {
                            h2 = 2256.25 - (wall - D_8010EDB0_picking_panic[arg1][j]) * (wall - D_8010EDB0_picking_panic[arg1][j]);
                            g = (h2 <= 0.0f) ? 0.0f : HuSqrtf(h2);
                            if (h2 > 0.0f && D_8010EDD0_picking_panic[arg1][j] - g < -152.0f &&
                                g + D_8010EDD0_picking_panic[arg1][j] > -292.0f) {
                                D_8010EDB0_picking_panic[arg1][j] = (i == 0) ? wall + 47.5 : wall - 47.5;
                                D_8010EE10_picking_panic[arg1][j] = 0.0f;
                            } else {
                                ang = atan2df(h, x - wall);
                                spd = HuSqrtf(D_8010EE10_picking_panic[arg1][j] * D_8010EE10_picking_panic[arg1][j] +
                                              D_8010EE30_picking_panic[arg1][j] * D_8010EE30_picking_panic[arg1][j]) * 0.25;
                                ang = ((ang < 0.0f) ? ang + 90.0f : ang + 0.0f) * 2.0f - 90.0f;
                                if ((D_8010EDA8_picking_panic[arg1][j] == 1) | (spd < 7.0f) ||
                                    (ang > 180.0f && ((i == 0) ? (x < wall) : (wall < x)))) {
                                    D_8010EDB0_picking_panic[arg1][j] = (i == 0) ? wall + 47.5 : wall - 47.5;
                                    D_8010EE10_picking_panic[arg1][j] = 0.0f;
                                } else {
                                    D_8010EDD0_picking_panic[arg1][j] = (D_8010EDD0_picking_panic[arg1][j] >= -222.0f) ? -104.5f : -339.5f;
                                    D_8010EE10_picking_panic[arg1][j] = cosdf(ang) * spd;
                                    D_8010EE30_picking_panic[arg1][j] = sindf(ang) * spd;
                                    D_8010EDB0_picking_panic[arg1][j] += D_8010EE10_picking_panic[arg1][j];
                                }
                            }
                            D_8010EDD0_picking_panic[arg1][j] += D_8010EE30_picking_panic[arg1][j];
                            break;
                        }
                    }
                }
            }
            if (i == 2) {
                D_8010EDB0_picking_panic[arg1][j] += D_8010EE10_picking_panic[arg1][j];
                D_8010EDD0_picking_panic[arg1][j] += D_8010EE30_picking_panic[arg1][j];
                D_8010EDA8_picking_panic[arg1][j] = 0;
            }
            D_8010EDF0_picking_panic[arg1][j] += D_8010EE50_picking_panic[arg1][j];
            if (D_8010E6F0_picking_panic[arg1][j] == 5 && 827.0 <= D_8010EDB0_picking_panic[arg1][j] - 47.5 &&
                D_8010EDB0_picking_panic[arg1][j] + 47.5 <= 953.0 && D_8010EDD0_picking_panic[arg1][j] - 47.5 <= -257.0 &&
                -257.0 < prevY - 47.5) {
                if (D_8010EF80_picking_panic < 3) {
                    D_8010EF15_picking_panic[arg1] += 3 - D_8010EDA0_picking_panic[arg1][j];
                    if (D_8010EF15_picking_panic[arg1] >= 100) {
                        D_8010EF15_picking_panic[arg1] = 99;
                    }
                    omVibrate(p0->unk00, 5, 0, 5);
                    omVibrate(p1->unk00, 5, 0, 5);
                }
                func_8001C258_main(mdl, 4, 4);
                func_8001C6A8_main(D_8010EEFC_picking_panic->model[arg1 + 2], 0.0f);
                func_8001C814_main(D_8010EEFC_picking_panic->model[arg1 + 2], 1, 0);
                func_8001C6A8_main(D_8010EEFC_picking_panic->model[arg1], 0.0f);
                func_8001C814_main(D_8010EEFC_picking_panic->model[arg1], 1, 0);
                func_8004AC98_main(0x36E, arg1);
                D_8010E6F0_picking_panic[arg1][j] = 0;
            } else if (D_8010EDD0_picking_panic[arg1][j] < -500.0f) {
                func_8001C258_main(mdl, 4, 4);
                D_8010E6F0_picking_panic[arg1][j] = 0;
            } else {
                Hu3DModelPosSet(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]],
                                D_8010EDB0_picking_panic[arg1][j], D_8010EDD0_picking_panic[arg1][j], 0.0f);
                Hu3DModelRotSet(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], 0.0f, 0.0f,
                                D_8010EDF0_picking_panic[arg1][j]);
            }
        }
    }
    if (arg1 == 1 && (D_8010EF80_picking_panic != 0 || D_8010EFA8_picking_panic >= 7)) {
        D_8010E6EC_picking_panic++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B908_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAB8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAE8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAFC_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB00_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB04_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB08_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB10_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB18_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB20_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB28_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB30_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB38_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB40_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB48_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB50_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB58_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB60_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB68_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB70_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB78_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB80_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB88_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB90_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB98_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC00_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC08_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC10_picking_panic);
#endif









































