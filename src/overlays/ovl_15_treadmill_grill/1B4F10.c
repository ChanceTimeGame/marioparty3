#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// tg A: Treadmill Grill

typedef func_800E1BA8_minigame_ObjData MgWork;

/* omObjData::data of the stage (the framework's ground object) */
typedef struct TgGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} TgGround; /* size 0xB4 */

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct TgCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} TgCtrl; /* size 0x28 */

// main
void Hu3DAnimInit(s32);
void func_80021BE0_main(s32* arg0, s32 arg1);
void func_800142A0_main(s32);
u8 func_8000B638_main(void);
void func_8002FD8C_main(s16 arg0, s16 arg1, const char* arg2, s16 arg3, s16 arg4);

extern f32 D_800D51FC_main;
extern f32 D_800D5410_main;

extern s32 D_800A178C_main[][6];
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E147C_minigame(omObjData* obj);
void func_800E17F4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E5798_minigame(omObjData* obj, s32 arg1);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
extern s16 D_800EB934_minigame;

extern f32 D_800EB73C_minigame;
extern s32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];
extern omObjData* D_800EBE70_minigame[];

// LOCAL
void func_801065DC_treadmill_grill(omObjData* obj);
void func_801067A8_treadmill_grill(omObjData* obj);
void func_801084B4_treadmill_grill(omObjData* obj);
void func_801085D8_treadmill_grill(omObjData* obj);
void func_80108730_treadmill_grill(omObjData* obj);
void func_80108888_treadmill_grill(omObjData* obj);
void func_801089E0_treadmill_grill(void);
void func_80108DE0_treadmill_grill(omObjData* obj);

void func_80109108_treadmill_grill(omObjData* obj);

extern f32 D_8010B064_treadmill_grill[13]; /* grill object growth */
extern s32 D_8010B098_treadmill_grill[13]; /* grill object sound played */
void func_80106008_treadmill_grill(omObjData* obj);
void func_801062DC_treadmill_grill(omObjData* obj);
void func_80109FA8_treadmill_grill(omObjData* obj);
void func_8010AE6C_treadmill_grill(omObjData* obj);

extern s32 D_8010AF80_treadmill_grill; /* next free model in D_8010B310 */
extern u16 D_8010B310_treadmill_grill[16]; /* player models */

extern u8 D_8010AF84_treadmill_grill[4]; /* player out */
extern TgCtrl D_8010B03C_treadmill_grill;
extern Vec D_8010B378_treadmill_grill[13];

void func_801059A0_treadmill_grill(void) {
    u8 cam;

    Hu3DAnimInit(0x32);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(0x1E, 0);
    func_8004A208_main();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 20.0f, 80.0f, 8000.0f);
    HmfLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0;
    func_800E19F0_minigame(0);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 1, 0, -1, func_801065DC_treadmill_grill);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_801067A8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801084B4_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801085D8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108730_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108888_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010B03C_treadmill_grill);
    D_800EB930_minigame = 0x35;
    D_800EB932_minigame = 0x14;
    HmfLightDirSet(1, 86.0f, 45.0f, 74.0f);
    func_801089E0_treadmill_grill();
}

void func_80106008_treadmill_grill(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80106034_treadmill_grill(omObjData* obj) {
    omObjData* o;
    f32 scale;
    s32 i;

    if (WipeStatGet() != 0) {
        return;
    }
    func_80109108_treadmill_grill(obj);
    for (i = 0; i < (u16)D_800EC1B8_minigame; i++) {
        o = D_800EBE70_minigame[i];
        o->trans.x = D_8010B378_treadmill_grill[i].x;
        o->trans.y = D_8010B378_treadmill_grill[i].y;
        o->trans.z = D_8010B378_treadmill_grill[i].z;
        o->rot.y = atan2df(-o->trans.x, -o->trans.z);
        scale = D_8010B064_treadmill_grill[i] += 0.125f;
        if (scale > 2.3f) {
            scale = 2.3f;
        }
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        o->scale.x = o->scale.y = o->scale.z = scale;
        if (scale > 1.0f && D_8010B098_treadmill_grill[i] == 0) {
            HuAudFXPlay(0x39F);
            D_8010B098_treadmill_grill[i]++;
        }
    }
}

void func_801061E8_treadmill_grill(omObjData* obj) {
    f32 scale;
    s32 i;

    for (i = 0; i < 3; i++) {
        scale = HmfModelData[obj->model[i + 10]].scale.x;
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(obj->model[i + 10], scale, scale, scale);
        Hu3DModelScaleSet(obj->model[i + 13], scale, scale, scale);
    }
}

void func_801062DC_treadmill_grill(omObjData* obj) {
    MgWork* work;
    omObjData* o;
    s32 last;
    s32 left;
    s32 i;

    last = 0;
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        left = 0;
        for (i = 0; i < D_800EC280_minigame; i++) {
            if (D_8010AF84_treadmill_grill[i] == 0) {
                left++;
                last = i;
            }
        }
        switch (func_800E6F40_minigame()) {
            case 0:
                if (func_800E6E9C_minigame() == 10) {
                    HuAudSeqPlay(0);
                }
                break;
            case 2:
                if (left < 2) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (left != 1) {
                    D_8010B03C_treadmill_grill.unk06 = 4;
                } else {
                    D_8010B03C_treadmill_grill.unk18[0] = last;
                    D_8010B03C_treadmill_grill.unk06 = 0;
                }
                break;
            case 4:
                if (D_800EB934_minigame == 1) {
                    if (D_8010B03C_treadmill_grill.unk06 == 4) {
                        for (i = 0; i < 4; i++) {
                            o = D_800EC598_minigame[i];
                            if (D_8010AF84_treadmill_grill[i] == 0) {
                                func_800E5798_minigame(o, 14);
                            }
                        }
                    } else {
                        o = D_800EC598_minigame[last];
                        func_800E5798_minigame(o, 13);
                        work = o->data;
                        GwPlayer[work->unk59].bonusCoin += 10;
                        func_80045ED0_main(D_800A178C_main[GwPlayer[work->unk59].chr][0] | 0x2F);
                    }
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                obj->func = func_80106008_treadmill_grill;
                break;
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80106008_treadmill_grill;
        }
        Center.y = 150.0f;
        Center.z = -350.0f;
    }
}

void func_801065DC_treadmill_grill(omObjData* obj) {
    TgGround* gw;

    obj->model[0] = func_8000B0A0_main(0x360005, 0xA9);
    obj->trans.x = 100.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -1200.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(TgGround), 31000);
    memset(gw, 0, sizeof(TgGround));
    obj->func = func_801062DC_treadmill_grill;
    gw->unk03 = 1;
    CZoom = 3736.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = 0.0f;
    Center.y = 50.0f;
    Center.z = -350.0f;
    func_800E147C_minigame(obj);
    func_800E139C_minigame(obj, 0.0f, -1500.0f, -1500.0f, 1500.0f, 1500.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    gw->unk04 = 0;
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    omSetStatBit(obj, 0xA0);
}

const char D_8010B288_treadmill_grill[] = "c201_000-eyes";

void func_801067A8_treadmill_grill(omObjData* obj) {
    TgGround* gw;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[0] = func_8000B0A0_main(0x360000, 0xAA9);
    obj->model[1] = func_8000B0A0_main(0x360001, 0xAA9);
    obj->model[2] = func_8000B0A0_main(0x360000, 0xAA9);
    obj->model[3] = func_8000B0A0_main(0x360001, 0xAA9);
    obj->model[4] = func_8000B0A0_main(0x360002, 0xA99);
    obj->model[5] = func_8000B0A0_main(0x360003, 0xA99);
    obj->model[6] = func_8000B0A0_main(0x360003, 0xA99);
    obj->model[7] = func_8000B0A0_main(0x360004, 0xA99);
    obj->model[8] = func_8000B0A0_main(0x360004, 0xA99);
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[9] = func_8000B0A0_main(0x360006, 0x299);
    obj->model[10] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    obj->model[11] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    obj->model[12] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    func_8001C2FC_main(obj->model[10], 0x70000000, 0);
    func_8001C2FC_main(obj->model[11], 0x70000000, 0);
    func_8001C2FC_main(obj->model[12], 0x70000000, 0);
    func_8002FD8C_main(obj->model[10], HmfModelData[obj->model[10]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    func_8002FD8C_main(obj->model[11], HmfModelData[obj->model[11]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    func_8002FD8C_main(obj->model[12], HmfModelData[obj->model[12]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    obj->model[13] = func_8000B0A0_main(0x360007, 0xAC9);
    obj->model[14] = Hu3DModelLink(obj->model[13]);
    obj->model[15] = Hu3DModelLink(obj->model[13]);
    func_8001C2FC_main(obj->model[13], 0x80000000, 0x80000000);
    func_8001C2FC_main(obj->model[14], 0x80000000, 0x80000000);
    func_8001C2FC_main(obj->model[15], 0x80000000, 0x80000000);
    func_8001C448_main(obj->model[13]);
    func_8001C448_main(obj->model[14]);
    func_8001C448_main(obj->model[15]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.y = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(TgGround), 31000);
    memset(gw, 0, sizeof(TgGround));
    obj->func = func_80109FA8_treadmill_grill;
    gw->unk03 = 1;
    func_800E13CC_minigame(obj, 250.0f, 250.0f, -550.0f, -1050.0f, 550.0f, 150.0f);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    func_8001C2FC_main(obj->model[1], 0x20000, 0x20000);
    func_8001C448_main(obj->model[1]);
    func_8001C954_main(obj->model[1]);
    func_8001C2FC_main(obj->model[2], 0x20000, 0x20000);
    func_8001C448_main(obj->model[2]);
    func_8001C954_main(obj->model[2]);
    func_8001C2FC_main(obj->model[3], 0x20000, 0x20000);
    func_8001C448_main(obj->model[3]);
    func_8001C954_main(obj->model[3]);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, -300.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, -600.0f);
    Hu3DModelPosSet(obj->model[3], 0.0f, 0.0f, -900.0f);
    func_800E147C_minigame(obj);
    func_800E1304_minigame(obj, 0.3f);
    func_800E131C_minigame(obj, 15.0f);
    func_800E17F4_minigame(obj, 1.0f, 1.0f, 1.0f);
    gw->unk04 = 1;
    Hu3DModelPosSet(obj->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[5], 480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[6], -480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[7], 430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(obj->model[8], -430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(obj->model[9], 0.0f, 0.0f, -450.0f);
    Hu3DModelScaleSet(obj->model[9], 1.1f, 1.0f, 0.8f);
    omSetStatBit(obj, 0xA0);
    func_8010AE6C_treadmill_grill(obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106DA0_treadmill_grill);

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107454_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107798_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801084B4_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801085D8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108730_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108888_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801089E0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108C64_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108DE0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108FCC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109108_treadmill_grill);

void func_801093E0_treadmill_grill(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801093E8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010980C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109FA8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A548_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A6A4_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A754_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A9AC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010AA2C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010AB9C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010ACBC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010AE6C_treadmill_grill);
