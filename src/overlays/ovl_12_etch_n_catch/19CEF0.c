#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// et A: Etch 'n' Catch (2 vs 2)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (as Hyper Hydrants' HhCtrl) */
typedef struct EtCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result: 1 a team won, 4 draw */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winners, 0xFF none */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} EtCtrl; /* size 0x28 */

// Heap-allocated (0x20 bytes) per-player work (D_8010C868[player]); unk0C is the head of a linked list
// of nodes (func_80108B64 inserts, func_80108BCC removes, func_80108C08 walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ s8 unk00; /* team member bit: 1/2 team 0, 4/8 team 1 */
    /* 0x01 */ s8 unk01;
    /* 0x02 */ u8 unk02; /* 8 team 0, 1 team 1 */
    /* 0x03 */ char unk03[5];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ char unk13;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[2];
} EtchNCatchWork; // sizeof 0x20

// main
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004A208_main(void);
void func_8004AD70_main(void);
void func_8004A950_main(void);
u16 func_80049F98_main(void);
s32 func_8000B638_main(void);
omObjData* func_80045ED0_main(u32 arg0);
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
extern f32 D_800EB740_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern s32 D_800EBEB0_minigame[];

// this overlay
void func_80105CD0_etch_n_catch(EtCtrl* ctrl);
void func_80105D5C_etch_n_catch(void);
void func_80105ED4_etch_n_catch(omObjData* obj);
void func_80106334_etch_n_catch(omObjData* obj);
void func_80109A54_etch_n_catch(omObjData* obj);
void func_8010B24C_etch_n_catch(omObjData* obj);
void func_8010BBE4_etch_n_catch(omObjData* obj);
void func_8010BE84_etch_n_catch(omObjData* obj);
void func_8010C2F4_etch_n_catch(void);
void func_8010C390_etch_n_catch(omObjData* obj);
void func_8010C444_etch_n_catch(omObjData* obj);

void func_80106A64_etch_n_catch(omObjData* obj);
void func_80108B20_etch_n_catch(EtchNCatchWork* arg0);
// main (more)
extern s32 D_800A178C_main[][6];
extern s16 D_800EB784_minigame[][14];
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
s16 func_8000B0D4_main(s32, s32);

// data
extern s8 D_8010C6D9_etch_n_catch; /* next player to set up */
extern s8 D_8010C6DA_etch_n_catch[2]; /* players set up per team */
extern s32 D_8010C6D4_etch_n_catch;
extern s8 D_8010C6AC_etch_n_catch; /* team 0 score */
extern s8 D_8010C6AD_etch_n_catch; /* team 1 score */
extern s8 D_8010C6D8_etch_n_catch;

// bss
extern u8 D_8010C830_etch_n_catch; /* start layout, 0..4 */
extern EtchNCatchWork* D_8010C868_etch_n_catch[4];
extern s16 D_80111390_etch_n_catch[4][3];
extern omObjData* D_8010C858_etch_n_catch[2];
extern omObjData* D_8010C860_etch_n_catch[2];
extern EtCtrl D_801113B0_etch_n_catch;
extern u8 D_801113C8_etch_n_catch; /* view: D_801113B0.unk18[0] */
extern u8 D_801113C9_etch_n_catch; /* view: D_801113B0.unk18[1] */
extern void* D_801113D8_etch_n_catch[4];


void func_801059A0_etch_n_catch(void) {
    s32 i;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CD0_etch_n_catch(&D_801113B0_etch_n_catch);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_801113B0_etch_n_catch);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105ED4_etch_n_catch), 0xA0);
    func_80105D5C_etch_n_catch();
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C390_etch_n_catch);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C444_etch_n_catch);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 0, 0, -1, func_8010BE84_etch_n_catch);
    func_800E18D8_minigame();
    D_800EB740_minigame = 0.5f;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 5, 0x3C, -1, func_80106334_etch_n_catch);
        omSetStatBit(D_800EC598_minigame[i], 0xA0);
        D_801113D8_etch_n_catch[i] = HuMemAllocTag(0x3800, 0x7918);
        memset(D_801113D8_etch_n_catch[i], 0, 0x3800);
    }
    for (i = 0; i < 2; i++) {
        D_8010C860_etch_n_catch[i] = omAddObj(2, 3, 0, -1, func_8010B24C_etch_n_catch);
        D_8010C858_etch_n_catch[i] = omAddObj(2, 7, 2, -1, func_80109A54_etch_n_catch);
    }
    omAddObj(3, 0, 0, -1, func_8010BBE4_etch_n_catch);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105CD0_etch_n_catch(EtCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 60;
    ctrl->unk00 = 0;
    ctrl->unk01 = 1;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 0;
    ctrl->unk1C = 90;
    ctrl->unk1E = 900;
    ctrl->unk20 = -1;
    ctrl->unk22 = 75;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105D5C_etch_n_catch(void) {
    s32 cam;
    HuCamera* c;

    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 27.211f, 80.0f, 8000.0f);
    c = &gCameraList[cam];
    c->pos.x = -1.965f;
    c->pos.y = 1392.72f;
    c->pos.z = 1374.455f;
    c->at.x = -1.965f;
    c->at.y = 60.495f;
    c->at.z = 20.66f;
    c->up.x = 0.0f;
    c->up.y = 0.5f;
    c->up.z = -0.8660254f;
}

#ifdef NON_MATCHING
void func_80105ED4_etch_n_catch(omObjData* obj) {
    s32 voice;
    s8 i;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010C6D8_etch_n_catch == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010C6D8_etch_n_catch = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x38;
                break;
            case 2:
                if (D_8010C6AC_etch_n_catch >= 5 || D_8010C6AD_etch_n_catch >= 5) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (func_800E6E9C_minigame() == 74.0) {
                    if (D_8010C6AC_etch_n_catch == D_8010C6AD_etch_n_catch) {
                        D_801113B0_etch_n_catch.unk06 = 4;
                    } else {
                        D_801113B0_etch_n_catch.unk06 = 1;
                        for (i = 0; i < 4; i++) {
                            if (D_8010C6AC_etch_n_catch > D_8010C6AD_etch_n_catch && GwPlayer[i].group == 0) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            } else if (D_8010C6AC_etch_n_catch < D_8010C6AD_etch_n_catch && GwPlayer[i].group == 1) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            }
                        }
                    }
                }
                break;
            case 4:
                if (D_800EB934_minigame != 0) {
                    for (i = 0; i < 4; i++) {
                        if (D_801113B0_etch_n_catch.unk06 == 1
                            && (i == D_801113B0_etch_n_catch.unk18[0] || i == D_801113B0_etch_n_catch.unk18[1])) {
                            func_800E5690_minigame(D_800EC598_minigame[i], 13);
                            switch (GwPlayer[i].chr) {
                                case 0:
                                default:
                                    voice = 2;
                                    break;
                                case 1:
                                    voice = 3;
                                    break;
                                case 2:
                                    voice = 7;
                                    break;
                                case 3:
                                    voice = 4;
                                    break;
                                case 4:
                                    voice = 5;
                                    break;
                                case 5:
                                    voice = 6;
                                    break;
                                case 6:
                                    voice = 8;
                                    break;
                                case 7:
                                    voice = 9;
                                    break;
                            }
                            func_8004AD70_main();
                            func_80045ED0_main((voice << 16) | 0x2F);
                        } else {
                            func_800E5690_minigame(D_800EC598_minigame[i], 14);
                        }
                    }
                }
                break;
            case 5:
                if (D_8010C6D4_etch_n_catch == 0) {
                    WipeCreateOut(0, 20);
                    func_8010C2F4_etch_n_catch();
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010C6D4_etch_n_catch++;
                break;
        }
        Hu3DCamSetPositionOrientation(0, &gCameraList->pos, &gCameraList->at, &gCameraList->up);
        Hu3DCamUpdateMtx(0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105ED4_etch_n_catch);
#endif

/* A player object: places the player at its team's start, loads its pen and models. */
#ifdef NON_MATCHING
void func_80106334_etch_n_catch(omObjData* obj) {
    Vec pos0a[2] = { { -350.0f, 1000.0f, -200.0f }, { -150.0f, 1000.0f, 250.0f } };
    Vec pos0b[2] = { { -150.0f, 1000.0f, 250.0f }, { -350.0f, 1000.0f, -200.0f } };
    Vec pos1a[2] = { { 150.0f, 1000.0f, -200.0f }, { 350.0f, 1000.0f, 250.0f } };
    Vec pos1b[2] = { { 350.0f, 1000.0f, 250.0f }, { 150.0f, 1000.0f, -200.0f } };
    s8 chr;
    s32 dir;
    s32 file;
    s32 i;
    MgWork* pw;
    EtchNCatchWork* w;
    Vec* p;
    s32 mdl;
    f32 dx;

    chr = GwPlayer[D_8010C6D9_etch_n_catch].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(obj, dir, file, D_8010C6D9_etch_n_catch, 0xAA9, 0xAB9);
    pw = obj->data;
    D_800EB784_minigame[pw->unk59][0] = -1;
    D_800EB784_minigame[pw->unk59][1] = -1;
    pw->unk3C = 0.0f;
    D_8010C868_etch_n_catch[D_8010C6D9_etch_n_catch] = w = HuMemAllocTag(sizeof(EtchNCatchWork), 0x7918);
    memset(w, 0, sizeof(EtchNCatchWork));
    func_80108B20_etch_n_catch(w);
    obj->rot.y = 0.0f;
    obj->rot.x = obj->rot.z = obj->rot.y;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.75f;
    if (D_8010C6D9_etch_n_catch == 0) {
        D_8010C830_etch_n_catch = (u32)(rand8() * 5) >> 7;
    }
    switch (GwPlayer[pw->unk59].group) {
        case 0:
            if (!(D_8010C830_etch_n_catch & 1)) {
                p = &pos0a[D_8010C6DA_etch_n_catch[0]];
            } else {
                p = &pos0b[D_8010C6DA_etch_n_catch[0]];
            }
            obj->trans.x = p->x;
            obj->trans.y = p->y;
            obj->trans.z = p->z;
            w->unk02 = 8;
            w->unk01 = 3;
            w->unk00 = (D_8010C6DA_etch_n_catch[0] == 0) ? 1 : 2;
            func_800E149C_minigame(obj, 0, 2);
            func_800E149C_minigame(obj, 1, 1);
            D_8010C6DA_etch_n_catch[0]++;
            break;
        case 1:
            if (!(D_8010C830_etch_n_catch & 1)) {
                p = &pos1a[D_8010C6DA_etch_n_catch[1]];
            } else {
                p = &pos1b[D_8010C6DA_etch_n_catch[1]];
            }
            obj->trans.x = p->x;
            obj->trans.y = p->y;
            obj->trans.z = p->z;
            w->unk02 = 1;
            w->unk01 = 12;
            w->unk00 = (D_8010C6DA_etch_n_catch[1] == 0) ? 4 : 8;
            func_800E149C_minigame(obj, 0, 1);
            func_800E149C_minigame(obj, 1, 2);
            D_8010C6DA_etch_n_catch[1]++;
            break;
    }
    w->unk0A = 0;
    w->unk08 = 0;
    w->unk14 = 0;
    w->unk18 = 0;
    w->unk17 = 0;
    w->unk1C = 0;
    w->unk12 = 0;
    w->unk10 = 0;
    obj->func = func_80106A64_etch_n_catch;
    dx = sindf(pw->unk3C) * 65.0f * 0.75f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x - dx, 0.0f, obj->trans.z - cosdf(pw->unk3C) * 65.0f * 0.75f);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    if (w->unk02 == 8) {
        mdl = 0x330000;
    } else {
        mdl = 0x330001;
    }
    obj->model[2] = func_8000B108_main(mdl, 0xAB9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C814_main(obj->model[2], 2, 1);
    obj->model[3] = func_8000B108_main(3, 0x89D);
    obj->model[4] = func_8000B108_main(4, 0x89D);
    for (i = 0; i < 3; i++) {
        if (i == 0 && pw->unk59 == 0) {
            D_80111390_etch_n_catch[0][0] = func_8000B0D4_main(0x330006, 0x28D);
        } else {
            D_80111390_etch_n_catch[pw->unk59][i] = Hu3DModelLink(D_80111390_etch_n_catch[0][0]);
        }
        func_8001C814_main(D_80111390_etch_n_catch[pw->unk59][i], 2, 2);
        func_8001FA68_main(D_80111390_etch_n_catch[pw->unk59][i]);
    }
    func_800E1328_minigame(obj, 46.875f);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0x47), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 0x48), 1, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5690_minigame(obj, 0);
    D_8010C6D9_etch_n_catch++;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C740_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C758_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C770_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C788_etch_n_catch);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106334_etch_n_catch);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106A64_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107D38_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107EA4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010880C_etch_n_catch);

void func_80108B20_etch_n_catch(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108B28_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108B64_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108BCC_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108C08_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108D84_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108DD0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_801090E0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109114_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010914C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109370_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_801097B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109A54_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7BC_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109EB8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AB7C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AD6C_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7F0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AEE4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AFB8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B154_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B24C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B3B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BBE4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BD98_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BE84_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C2F4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C390_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C444_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C4F8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C574_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C628_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C820_etch_n_catch);
