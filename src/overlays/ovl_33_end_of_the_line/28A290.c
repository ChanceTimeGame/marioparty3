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


// EXTERN

// C1F0
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_8000BBFC_main(u16, u8);
void func_8000BC48_main(u16, u16);
s32 func_8000B710_main(s32 arg0);

// 44C2C
void func_80045C2C_main(void);

// 1D3D0
void func_8001FB34_main(s16 arg0, u8 arg1);
void func_8001FBBC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3);

// hmflight
void HmfLightStatSet(s16, u8, u8);

// minigame
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s32);

// LOCAL

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[2];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[2];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ Vec unk24;
    /* 0x30 */ Vec unk30;
    /* 0x3C */ char unk3C[4];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ char unk44[0x18];
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ u16 unk64;
    /* 0x66 */ char unk66[0xA];
    /* 0x70 */ s16 unk70;
    /* 0x72 */ char unk72[6];
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A[3];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ char unk84[2];
    /* 0x86 */ s16 unk86;
    /* 0x88 */ char unk88[2];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ char unk8E[6];
} EotlPlayer; // Size 0x94

typedef struct {
    /* 0x00 */ s16 unk00[2];
    /* 0x04 */ s16 unk04[2];
    /* 0x08 */ s16 unk08[2];
    /* 0x0C */ s16 unk0C[2];
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char unk16[2];
    /* 0x18 */ f32 unk18[2][2];
} EotlHud; // Size 0x28

void func_80105E0C_end_of_the_line(omObjData *obj);
void func_80105E88_end_of_the_line(omObjData *obj);
void func_80106444_end_of_the_line(omObjData *obj);
void func_80106CDC_end_of_the_line(omObjData *arg0, omObjData *arg1, s32 arg2);
void func_80107FF0_end_of_the_line(u16 arg0);
void func_8010A434_end_of_the_line(omObjData *obj);
void func_8010AA7C_end_of_the_line(EotlPlayer *pw);
void func_8010AC34_end_of_the_line(EotlPlayer *pw);
void func_8010AF28_end_of_the_line(omObjData *obj);
void func_8010B064_end_of_the_line(omObjData *obj);
void func_8010B640_end_of_the_line(omObjData *obj);
void func_8010BF64_end_of_the_line(omObjData *obj);
void func_8010C580_end_of_the_line(void);
void func_80107F0C_end_of_the_line(void);
void func_801082D8_end_of_the_line(omObjData *obj);
void func_8010C060_end_of_the_line(omObjData *obj);
void func_8010C3F4_end_of_the_line(void);

extern D_80111B50_vine_with_me_Struct D_8010C5A0_end_of_the_line;
extern s16 D_8010C5C8_end_of_the_line[];
extern s32 D_8010C5D8_end_of_the_line[5];
extern s32 D_8010C5EC_end_of_the_line[5];
extern s16 D_8010C600_end_of_the_line[2][4];
extern s16 D_8010C610_end_of_the_line[2][4];

extern u16 D_8010C650_end_of_the_line;
extern s32 D_8010C658_end_of_the_line[3];

extern omObjData *D_8010C730_end_of_the_line;
extern omObjData *D_8010C734_end_of_the_line;
extern omObjData *D_8010C738_end_of_the_line;
extern omObjData *D_8010C73C_end_of_the_line[2];
extern u16 D_8010C754_end_of_the_line;
extern u16 D_8010C756_end_of_the_line;
extern u16 D_8010C758_end_of_the_line;
extern u16 D_8010C75A_end_of_the_line;
extern u16 D_8010C75C_end_of_the_line;
extern u16 D_8010C75E_end_of_the_line[2];
extern s16 D_8010C762_end_of_the_line;
extern s16 D_8010C764_end_of_the_line;
extern u16 D_8010C766_end_of_the_line;
extern u16 D_8010C768_end_of_the_line[3];
extern s16 D_8010C76E_end_of_the_line;
extern s16 D_8010C770_end_of_the_line;
extern s16 D_8010C772_end_of_the_line;
extern s16 D_8010C774_end_of_the_line;
extern s16 D_8010C776_end_of_the_line;
extern s16 D_8010C778_end_of_the_line[2];
extern s16 D_8010C77C_end_of_the_line[2];
extern s16 D_8010C780_end_of_the_line;
extern s16 D_8010C782_end_of_the_line[2];
extern Vec D_8010C788_end_of_the_line[2];
extern Vec D_8010C7A0_end_of_the_line[2];
extern Vec D_8010C7B8_end_of_the_line[2];
extern s16 D_8010C7D0_end_of_the_line;

void func_801059A0_end_of_the_line(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(0x1E, 0);
    i = 0;
    func_8004A208_main();
    func_80045C2C_main();
    func_8000B690_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        D_8010C7A0_end_of_the_line[i].x = 0.0f;
        D_8010C7A0_end_of_the_line[i].y = 200.0f;
        D_8010C7A0_end_of_the_line[i].z = 0.0f;
        D_8010C788_end_of_the_line[i].x = 0.0f;
        D_8010C788_end_of_the_line[i].y = 300.0f;
        D_8010C788_end_of_the_line[i].z = 1000.0f;
        D_8010C7B8_end_of_the_line[i].x = 0.0f;
        D_8010C7B8_end_of_the_line[i].y = 0.1f;
        D_8010C7B8_end_of_the_line[i].z = 0.0f;
        Hu3DCamSetPerspective(i, 60.0f, 80.0f, 20000.0f);
        ScissorSet(i, D_8010C600_end_of_the_line[i][0], D_8010C600_end_of_the_line[i][1],
                   D_8010C600_end_of_the_line[i][2], D_8010C600_end_of_the_line[i][3]);
        ViewportSet(i, D_8010C610_end_of_the_line[i][0], D_8010C610_end_of_the_line[i][1], 511.0f,
                    D_8010C610_end_of_the_line[i][2], D_8010C610_end_of_the_line[i][3], 511.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, func_8010C060_end_of_the_line);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    HmfLightMaxSet(3);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, 3.0f, 89.0f, 80.0f);
    HmfLightStatSet(1, 1, 1);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(3, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105E0C_end_of_the_line);
    D_8010C738_end_of_the_line = omAddObj(0xA, 0x1E, 0, -1, func_80106444_end_of_the_line);
    omSetStatBit(D_8010C738_end_of_the_line, 0x100);
    for (i = 0; i < 2; i++) {
        D_8010C73C_end_of_the_line[i] = obj = omAddObj(0x14, 6, 0xC, -1, func_801082D8_end_of_the_line);
        obj->work[0] = i;
    }
    D_8010C76E_end_of_the_line = func_8000B838_main(0x54001A);
    D_8010C770_end_of_the_line = func_8000B838_main(0x540018);
    D_8010C772_end_of_the_line = func_8000B838_main(0x540019);
    D_8010C774_end_of_the_line = func_8000B838_main(0x540013);
    D_8010C776_end_of_the_line = func_8000B838_main(0x54001B);
    D_8010C778_end_of_the_line[0] = func_8000B838_main(0x540015);
    D_8010C778_end_of_the_line[1] = func_8000B838_main(0x540014);
    D_8010C77C_end_of_the_line[0] = func_8000B838_main(0x540017);
    D_8010C77C_end_of_the_line[1] = func_8000B838_main(0x540016);
    D_8010C780_end_of_the_line = func_8000B838_main(0x38001F);
    func_80107F0C_end_of_the_line();
    func_8010C3F4_end_of_the_line();
    func_800E5EA0_minigame(&D_8010C5A0_end_of_the_line);
}

void func_80105E0C_end_of_the_line(omObjData *obj) {
    D_8010C734_end_of_the_line = NULL;
    D_8010C730_end_of_the_line = NULL;
    D_8010C7D0_end_of_the_line = -1;
    D_8010C75A_end_of_the_line = 0;
    D_8010C75C_end_of_the_line = 0;
    D_8010C758_end_of_the_line = 0;
    D_8010C766_end_of_the_line = 0;
    D_8010C75E_end_of_the_line[0] = D_8010C75E_end_of_the_line[1] = 0;
    D_8010C762_end_of_the_line = -1;
    D_8010C764_end_of_the_line = -1;
    D_8010C782_end_of_the_line[0] = D_8010C782_end_of_the_line[1] = -1;
    obj->func = func_80105E88_end_of_the_line;
}

void func_80105E88_end_of_the_line(omObjData *obj) {
    EotlPlayer *pw;
    EotlPlayer *pw2;
    s32 n;
    s32 i;

    if (D_8010C650_end_of_the_line == 0) {
        switch (func_800E6F40_minigame()) {
        case 0:
            if (D_8010C730_end_of_the_line == NULL) {
                D_8010C754_end_of_the_line = 0;
                D_8010C730_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010AF28_end_of_the_line);
                D_8010C730_end_of_the_line->work[0] = 0;
                D_8010C730_end_of_the_line->work[1] = 0;
            }
            break;
        case 2:
            if (D_8010C758_end_of_the_line == 1) {
                n = 0;
                for (i = 0; i < 2; i++) {
                    if (D_8010C75E_end_of_the_line[i] == 1) {
                        D_8010C7D0_end_of_the_line = i;
                        n++;
                    }
                }
                if (n == 2) {
                    D_8010C5A0_end_of_the_line.unk06 = 4;
                    D_8010C75C_end_of_the_line = 1;
                } else if (D_8010C75A_end_of_the_line == 0) {
                    pw = D_8010C73C_end_of_the_line[(s16)(D_8010C7D0_end_of_the_line ^ 1)]->data;
                    if (pw->unk18 == 2) {
                        pw->unk0C = 0.0f;
                    }
                    if (pw->unk86 != -1) {
                        HuAudFXStop(pw->unk86);
                        pw->unk86 = -1;
                    }
                }
                func_800E6F0C_minigame(3);
            } else if (func_800E6E9C_minigame() == 9000 || D_8010C75A_end_of_the_line == 1) {
                D_8010C75A_end_of_the_line = 1;
                D_8010C75C_end_of_the_line = 1;
                func_8003F578_main(0);
                pw = D_8010C73C_end_of_the_line[0]->data;
                pw2 = D_8010C73C_end_of_the_line[1]->data;
                if (pw->unk18 == 1 && pw2->unk18 == 1) {
                    D_8010C5A0_end_of_the_line.unk06 = 4;
                    func_800E6F0C_minigame(3);
                    D_8010C5A0_end_of_the_line.unk22 = 60;
                    D_8010C734_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010B064_end_of_the_line);
                    D_8010C756_end_of_the_line = 3;
                }
            }
            break;
        case 1:
        case 3:
        case 4:
            break;
        case 5:
            WipeCreateOut(0, 20);
            D_8010C650_end_of_the_line = 1;
            break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010C580_end_of_the_line();
    }
    for (i = 0; i < 2; i++) {
        if (D_8010C782_end_of_the_line[i] >= 0) {
            pw = D_8010C73C_end_of_the_line[i]->data;
            if ((D_8010C782_end_of_the_line[i] & 0xF) == 4) {
                if (D_8010C75C_end_of_the_line == 0) {
                    if (D_8010C782_end_of_the_line[i] & 0x10) {
                        func_8010AA7C_end_of_the_line(pw);
                    }
                    if (D_8010C782_end_of_the_line[i] & 0x20) {
                        func_8010AC34_end_of_the_line(D_8010C73C_end_of_the_line[i]->data);
                    }
                    func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i],
                                                  D_8010C782_end_of_the_line[i] & 0xF);
                    pw->unk5C = 7;
                    D_8010C73C_end_of_the_line[i]->func = func_8010A434_end_of_the_line;
                    func_80107FF0_end_of_the_line(pw->unk00);
                    pw->unk04->work[2] = 0;
                    pw->unk04->func = func_8010B640_end_of_the_line;
                } else {
                    if (D_8010C782_end_of_the_line[i] & 0x10) {
                        func_8010AA7C_end_of_the_line(D_8010C73C_end_of_the_line[i]->data);
                    }
                    if (D_8010C782_end_of_the_line[i] & 0x20) {
                        func_8010AC34_end_of_the_line(D_8010C73C_end_of_the_line[i]->data);
                    }
                    func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i], 6);
                    pw->unk5C = 7;
                    D_8010C73C_end_of_the_line[i]->func = func_8010A434_end_of_the_line;
                    func_80107FF0_end_of_the_line(pw->unk00);
                    pw->unk04->work[2] = 0;
                    pw->unk04->func = func_8010BF64_end_of_the_line;
                }
                if (D_8010C734_end_of_the_line == NULL) {
                    if (D_8010C75C_end_of_the_line == 0) {
                        D_8010C756_end_of_the_line = 0;
                    } else {
                        D_8010C756_end_of_the_line = 1;
                    }
                    D_8010C734_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010B064_end_of_the_line);
                }
            } else {
                if (D_8010C782_end_of_the_line[i] & 0x10) {
                    func_8010AA7C_end_of_the_line(D_8010C73C_end_of_the_line[i]->data);
                }
                if (D_8010C782_end_of_the_line[i] & 0x20) {
                    func_8010AC34_end_of_the_line(D_8010C73C_end_of_the_line[i]->data);
                }
                func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i],
                                              D_8010C782_end_of_the_line[i] & 0xF);
                if (D_8010C782_end_of_the_line[i] & 0x40) {
                    pw->unk40 = 200.0f;
                }
                if (D_8010C782_end_of_the_line[i] & 0x80) {
                    pw->unk04->func = pw->unk08;
                }
                if ((D_8010C782_end_of_the_line[i] & 0xF) == 3) {
                    omVibrate(pw->unk02, 20, 0, 20);
                }
            }
            D_8010C782_end_of_the_line[i] = -1;
        }
    }
}

#ifdef NON_MATCHING
/* Instruction scheduling only: one addu of the model index is placed before the reload of obj->model. */
void func_80106444_end_of_the_line(omObjData *obj) {
    EotlHud *hud;
    s32 i;
    s32 j;
    s16 x;

    hud = (EotlHud *)(obj->data = HuMemAllocTag(sizeof(EotlHud), 0x7918));
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x540002, 0x6DD);
            obj->model[4] = func_8000B108_main(0x540003, 0x6DD);
            obj->model[12] = func_8000B108_main(0x540004, 0x6DD);
            obj->model[14] = func_8000B108_main(0x540008, 0x6DD);
            obj->model[16] = func_8000B108_main(0x540009, 0x6DD);
            obj->model[18] = func_8000B108_main(0x54000A, 0x6DD);
            for (j = 0; j < 5; j++) {
                obj->model[20 + j * 2] = func_8000B108_main(D_8010C5D8_end_of_the_line[j], D_8010C5EC_end_of_the_line[j]);
            }
        } else {
            obj->model[2] = Hu3DModelLink(obj->model[0]);
            obj->model[5] = Hu3DModelLink(obj->model[4]);
            obj->model[13] = Hu3DModelLink(obj->model[12]);
            obj->model[15] = Hu3DModelLink(obj->model[14]);
            obj->model[17] = Hu3DModelLink(obj->model[16]);
            obj->model[19] = Hu3DModelLink(obj->model[18]);
            for (j = 0; j < 5; j++) {
                obj->model[21 + j * 2] = Hu3DModelLink(obj->model[20 + j * 2]);
            }
        }
        func_8001C8A8_main(obj->model[i * 2], D_8010C5C8_end_of_the_line[i]);
        func_8001C8A8_main(obj->model[4 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C8A8_main(obj->model[12 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C8A8_main(obj->model[14 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C8A8_main(obj->model[16 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C8A8_main(obj->model[18 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C2FC_main(obj->model[18 + i], 0x70000000, 0x70000000);
        for (j = 0; j < 5; j++) {
            func_8001C2FC_main(obj->model[20 + j * 2 + i], 0x70000000, 0x70000000);
            func_8001C8A8_main(obj->model[20 + j * 2 + i], D_8010C5C8_end_of_the_line[i]);
        }
        for (j = 0; j < 1; j++) {
            obj->model[j + i * 2 + 1] = Hu3DModelLink(obj->model[0]);
            func_8001C8A8_main(obj->model[j + i * 2 + 1], D_8010C5C8_end_of_the_line[i]);
        }
        for (j = 0; j < 3; j++) {
            if (i == 0) {
                obj->model[6 + j] = func_8000B108_main(D_8010C658_end_of_the_line[j], 0x6DD);
            } else {
                obj->model[9 + j] = Hu3DModelLink(obj->model[6 + j]);
            }
            func_8001C8A8_main(obj->model[6 + i * 3 + j], D_8010C5C8_end_of_the_line[i]);
        }
        hud->unk00[i] = InitEspriteSlot(D_8010C76E_end_of_the_line, 0, 0);
        hud->unk04[i] = InitEspriteSlot(D_8010C772_end_of_the_line, 0, 0);
        hud->unk08[i] = InitEspriteSlot(D_8010C770_end_of_the_line, 0, 0);
        hud->unk0C[i] = InitEspriteSlot(D_8010C774_end_of_the_line, 0, 0);
        hud->unk10[i] = InitEspriteSlot(D_8010C776_end_of_the_line, 0, 0);
        x = i * 160 + 80;
        func_8000BBD4_main(hud->unk00[i], x, 120);
        func_8000BBD4_main(hud->unk04[i], x, 120);
        func_8000BBD4_main(hud->unk08[i], x, 120);
        func_8000BBD4_main(hud->unk10[i], x, 120);
        func_8000BB94_main(hud->unk00[i]);
        func_8000BB94_main(hud->unk04[i]);
        func_8000BB94_main(hud->unk08[i]);
        func_8000BB94_main(hud->unk0C[i]);
        func_8000BB94_main(hud->unk10[i]);
        func_8000BC48_main(hud->unk00[i], 0x4000);
        func_8000BC48_main(hud->unk0C[i], 0x4008);
        func_8000BC48_main(hud->unk10[i], 0x4008);
        func_8000BCC8_main(hud->unk04[i], 0x80C8);
        func_8000BCC8_main(hud->unk08[i], 0x8190);
    }
    hud->unk14 = InitEspriteSlot(D_8010C780_end_of_the_line, 0, 0);
    func_8000BBD4_main(hud->unk14, 160, 120);
    func_8000BCC8_main(hud->unk14, 0x8064);
    for (i = 0; i < 3; i++) {
        D_8010C768_end_of_the_line[i] = rand8() < 0x80;
    }
    obj->work[0] = 0;
    obj->func = NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106444_end_of_the_line);
#endif

#ifdef NON_MATCHING
/* Float register allocation: the x offset is loaded into $f2 instead of $f20 (two extra nops). */
void func_801069D8_end_of_the_line(omObjData *obj) {
    EotlHud *hud;
    EotlPlayer *pw;
    omObjData *pobj;
    s32 i;
    s32 j;
    s32 k;
    f32 dz;
    f32 x;

    hud = obj->data;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            hud->unk18[i][j] += 37.037037f;
            Hu3DModelPosSet(obj->model[i * 2 + j], 0.0f, 0.0f, hud->unk18[i][j]);
            if (hud->unk18[i][j] >= 3300.0f) {
                hud->unk18[i][j] -= 6600.0f;
            }
        }
        if (obj->work[0] == 1) {
            k = 0;
            if (hud->unk18[0][0] > hud->unk18[0][1]) {
                k = 1;
            }
            func_80106CDC_end_of_the_line(obj, D_8010C73C_end_of_the_line[0], 1);
            func_80106CDC_end_of_the_line(obj, D_8010C73C_end_of_the_line[1], 1);
            dz = hud->unk18[0][k];
            for (j = 0; j < 2; j++) {
                pobj = D_8010C73C_end_of_the_line[j];
                pw = pobj->data;
                pobj->trans.z -= dz;
                pw->unk24.z -= dz;
                Hu3DModelPosSet(pobj->model[1], pw->unk24.x, pw->unk24.y, pw->unk24.z);
                Hu3DModelRotSet(pobj->model[1], pw->unk30.x, pw->unk30.y, pw->unk30.z);
                x = pw->unk24.x - sindf(pw->unk30.y) * 20.0f;
                Hu3DModelPosSet(pobj->model[2], x, pw->unk24.y + 100.0f, pw->unk24.z - cosdf(pw->unk30.y) * 20.0f);
                Hu3DModelRotSet(pobj->model[2], 0.0f, pw->unk30.y, 0.0f);
                Hu3DModelScaleSet(pobj->model[4], 1.0f, 1.0f, 1.0f);
                x = pw->unk24.x - sindf(pw->unk30.y) * 20.0f;
                Hu3DModelPosSet(pobj->model[4], x, pw->unk24.y + 100.0f, pw->unk24.z - cosdf(pw->unk30.y) * 20.0f);
            }
            obj->func = NULL;
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801069D8_end_of_the_line);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106CDC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107FF0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801080C8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801082D8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801088A4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80108F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010937C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80109E70_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A17C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A434_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A708_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A7D0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A8B4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A91C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AA1C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AA7C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AAC8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010ABD4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AC34_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AC80_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AF28_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B064_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B190_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B234_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B300_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B420_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B4EC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B588_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B640_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BE24_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BF64_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C060_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C110_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C3F4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C47C_end_of_the_line);

void func_8010C574_end_of_the_line(void) {
}
