#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"

// tg A: Treadmill Grill

typedef func_800E1BA8_minigame_ObjData MgWork;

// main
void Hu3DAnimInit(s32);
void func_80021BE0_main(s32* arg0, s32 arg1);
void func_800142A0_main(s32);
u8 func_8000B638_main(void);

// minigame
void func_800E1490_minigame(u16 arg0);

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
extern D_80111B50_vine_with_me_Struct D_8010B03C_treadmill_grill;
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
    func_800E5EA0_minigame(&D_8010B03C_treadmill_grill);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801062DC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801065DC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801067A8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106DA0_treadmill_grill);

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", D_8010B288_treadmill_grill);

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
