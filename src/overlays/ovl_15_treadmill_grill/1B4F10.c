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
s32 func_80017BB8_main(s16, s16);
void func_8002FD8C_main(s16 arg0, s16 arg1, const char* arg2, s16 arg3, s16 arg4);

extern f32 D_800D51FC_main;
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s16 D_800CDA7C_main[]; /* CPU buttons pressed */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */
extern f32 D_800D5410_main;

extern s32 D_800A178C_main[][6];
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
void func_800E1490_minigame(u16 arg0);
extern f32 D_800EB744_minigame; /* jump speed */
extern f32 D_800EB748_minigame; /* gravity */
extern f32 D_800EB774_minigame; /* max fall speed */
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E3568_minigame(MgWork* work, s32 slot, void* hook);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
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
void func_80107238_treadmill_grill(omObjData* obj);
void func_80107454_treadmill_grill(omObjData* obj, f32* x, f32* y, f32* z);
void func_80108C64_treadmill_grill(omObjData* obj, f32 x, f32 y, f32 z);
s32 func_80107798_treadmill_grill(omObjData* obj);
void func_8010AE6C_treadmill_grill(omObjData* obj);

extern s32 D_8010AF80_treadmill_grill; /* next free model in D_8010B310 */
extern u16 D_8010B310_treadmill_grill[16]; /* player models */
extern Vec D_8010B000_treadmill_grill[4]; /* hazard positions */
extern s32 D_8010B300_treadmill_grill; /* CPU input: buttons pressed */
extern s32 D_8010B304_treadmill_grill; /* CPU input: buttons */
extern s32 D_8010B308_treadmill_grill; /* CPU input: stick x */
extern s32 D_8010B30C_treadmill_grill; /* CPU input: stick y */
extern s16 D_8010B0D4_treadmill_grill;
extern s32 D_8010B0D8_treadmill_grill[4]; /* landings per player */ /* shared player part model, -1 until loaded */

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

void func_80106DA0_treadmill_grill(omObjData* obj, u32 arg1, s32 arg2, u16 arg3, f32 x, f32 y, f32 z) {
    MgWork* work;
    s32 chr;
    s32 i;
    s32 attr = 0xA99;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    func_800E1BA8_minigame(obj, arg1, arg2, arg3, attr, attr);
    work = obj->data;
    chr = GwPlayer[work->unk59].chr;
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[3] = func_8000B108_main(3, 0x89D);
    obj->model[4] = func_8000B108_main(4, 0x89D);
    obj->model[6] = func_8000B108_main(5, 0x89D);
    obj->model[5] = func_8000B108_main(6, 0x89D);
    obj->model[7] = func_8000B108_main(8, 0x89D);
    obj->model[8] = func_8000B108_main(7, 0x89D);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 3), 0, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 6), 1, 27);
    func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 0xE), 1, 15);
    func_800E5A00_minigame(obj, 32, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 18, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 30, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(obj, 31, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5978_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5978_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    func_800E5978_minigame(obj, 38, func_80017BB8_main(chr, 0x1A), 1, 0);
    for (i = 10; i < 14; i++) {
        if (D_8010B0D4_treadmill_grill < 0) {
            obj->model[i] = D_8010B0D4_treadmill_grill = func_8000B108_main(0x10014, 0x89D);
        } else {
            obj->model[i] = Hu3DModelLink(D_8010B0D4_treadmill_grill);
        }
    }
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
    work = obj->data;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 2);
    func_800E3568_minigame(work, 0, func_80107798_treadmill_grill);
    func_800E3568_minigame(work, 1, func_80107238_treadmill_grill);
    func_800E3568_minigame(work, 20, func_80107454_treadmill_grill);
}

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

// masked 0: retail ORs the two flags into a temporary, this C into hit (raw 1)
#ifdef NON_MATCHING
void func_80107238_treadmill_grill(omObjData* obj) {
    MgWork* work = obj->data;
    s32 player = work->unk59;
    s32 hit = 0;
    f32 dx, dy, dz;
    s32 i;

    if (D_8010AF84_treadmill_grill[player] == 0) {
        for (i = 0; i < 3; i++) {
            dx = obj->trans.x - D_8010B000_treadmill_grill[i].x;
            dy = obj->trans.y - D_8010B000_treadmill_grill[i].y;
            dz = obj->trans.z - D_8010B000_treadmill_grill[i].z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < work->unk48 + 40.0f) {
                hit = 1;
                break;
            }
        }
        hit = (work->unk53 == 0) | hit;
        if (hit) {
            D_8010AF84_treadmill_grill[player] = 1;
            func_800E5798_minigame(obj, 38);
            work->unk50 |= 0x400;
            work->unk38 = -D_800EB744_minigame;
            func_8001C258_main(obj->model[1], 4, 4);
            func_8004AC98_main(0x39D, work->unk59);
            func_8004ACE0_main(0x286, work->unk59);
            omVibrate(work->unk59, 2, 2, 20);
        }
    }
    if (GwPlayer[work->unk59].stat & 1) {
        D_800D5558_main[work->unk57] = D_8010B304_treadmill_grill;
        D_800CDA7C_main[work->unk57] = D_8010B300_treadmill_grill;
        D_800CBB6E_main[work->unk57] = D_8010B308_treadmill_grill;
        D_800D20A1_main[work->unk57] = D_8010B30C_treadmill_grill;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);
#endif

void func_80107454_treadmill_grill(omObjData* obj, f32* x, f32* y, f32* z) {
    MgWork* work = obj->data;
    omObjData* ground = D_800EC1C0_minigame[1];
    MgWork* gw;
    f32 vy;
    s16 se;

    if (HuSqrtf(*x * *x + *z * *z) > 2000.0f) {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[10], 4, 4);
        func_8001C258_main(obj->model[11], 4, 4);
        func_8001C258_main(obj->model[12], 4, 4);
        func_8001C258_main(obj->model[13], 4, 4);
        return;
    }
    gw = ground->data;
    work->unk3C = atan2df(*x - ground->trans.x, *z - ground->trans.z);
    work->unk40 = 25.0f;
    vy = work->unk38;
    if (vy > D_800EB774_minigame) {
        vy = D_800EB774_minigame;
    }
    *y += vy * vy * ((work->unk38 >= 0.0f) ? -35.0f : 35.0f);
    if (*x > gw->unkA0 && *x < gw->unkA8.f && *z > gw->unkA4 && *z < gw->unkA8.f) {
        if (*y <= gw->unk14) {
            work->unk38 = -D_800EB744_minigame;
            *y = gw->unk14;
            switch (D_8010B0D8_treadmill_grill[work->unk59]) {
                case 0:
                    se = 0x39E;
                    break;
                case 1:
                    se = 0x3A0;
                    break;
                case 2:
                    se = 0x3A1;
                    break;
                case 3:
                    se = 0x3A2;
                    break;
                case 4:
                default:
                    se = 0x3A3;
                    break;
            }
            func_8004AC98_main(se, work->unk59);
            D_8010B0D8_treadmill_grill[work->unk59]++;
        }
    } else if (*y <= 0.0f) {
        work->unk38 = -D_800EB744_minigame;
        *y = 0.0f;
        switch (D_8010B0D8_treadmill_grill[work->unk59]) {
            case 0:
                se = 0x39E;
                break;
            case 1:
                se = 0x3A0;
                break;
            case 2:
                se = 0x3A1;
                break;
            case 3:
                se = 0x3A2;
                break;
            case 4:
            default:
                se = 0x3A3;
                break;
        }
        func_8004AC98_main(se, work->unk59);
        D_8010B0D8_treadmill_grill[work->unk59]++;
    }
    work->unk38 += D_800EB748_minigame * 0.6f;
    func_80108C64_treadmill_grill(obj, *x, *y, *z);
}

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
