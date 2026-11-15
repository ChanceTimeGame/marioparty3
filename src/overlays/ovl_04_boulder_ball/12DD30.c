#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"

// boulder A: Boulder Ball (1 vs 3: the lone player rolls boulders down a slope at the three others)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* omObjData::data of a boulder: the framework's item actor (minigame mgcol.h ColActorWork) */
typedef struct BbBall {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ char unk20[0x14];
    /* 0x34 */ f32 unk34; /* height */
    /* 0x38 */ f32 unk38; /* vertical speed */
    /* 0x3C */ f32 unk3C; /* heading */
    /* 0x40 */ f32 unk40; /* speed */
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48; /* radius */
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ char unk55;
    /* 0x56 */ u16 unk56; /* boulder index */
    /* 0x58 */ char unk58[0x1C];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])();
    /* 0xA8 */ void* unkA8;
} BbBall; /* size 0xAC */

/* omObjData::data of the slope (the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct BbGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} BbGround; /* size 0xB4 */

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct BbCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result message: winners - 1 */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winner player indices */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} BbCtrl;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
s32 func_800202FC_main(Vec* v);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
omObjData* func_80045ED0_main(u32 arg0);
f64 fabs(f64);

extern s32 D_800A178C_main[][6];
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[];
extern u8 D_800D6A90_main;

// minigame
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E1468_minigame(omObjData* obj);
void func_800E147C_minigame(omObjData* obj);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1804_minigame(void);
void func_800E3568_minigame(MgWork* work, s32 slot, void* hook);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_800E561C_minigame(omObjData* obj, u8 flags);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern f32 D_800EB73C_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB774_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame[];
extern omObjData* D_800EBE70_minigame[];
extern s32 D_800EBEB0_minigame[];
extern u16 D_800EC288_minigame;

// LOCAL
void func_80105E74_boulder_ball(omObjData* obj);
void func_80105EA0_boulder_ball(void);
void func_801060D0_boulder_ball(void);
void func_80106410_boulder_ball(omObjData* obj);
void func_80106B58_boulder_ball(omObjData* obj);
void func_80106C8C_boulder_ball(omObjData* obj);
void func_80106DAC_boulder_ball(omObjData* obj, s32 arg1, s32 arg2, u16 arg3);
s32 func_8010707C_boulder_ball(omObjData* obj, omObjData* other);
s32 func_80107194_boulder_ball(omObjData* obj);
s32 func_80107298_boulder_ball(omObjData* obj);
void func_80107924_boulder_ball(omObjData* obj);
void func_80107A20_boulder_ball(omObjData* obj);
void func_80107B0C_boulder_ball(omObjData* obj);
void func_80107C08_boulder_ball(omObjData* obj);
void func_80108798_boulder_ball(omObjData* obj);
void func_80108A08_boulder_ball(omObjData* obj);

extern s32 D_80109700_boulder_ball[8]; /* per boulder: state */
extern s32 D_80109744_boulder_ball[4]; /* per boulder: rolling sound, -1 none */
extern f32 D_80109754_boulder_ball; /* slope bounce speed, 1000.0f none */
extern s32 D_80109758_boulder_ball;
extern s32 D_8010975C_boulder_ball; /* 1: the three won */
extern BbCtrl D_80109760_boulder_ball;
extern s32 D_80109794_boulder_ball; /* the first boulder released */
extern f32 D_80109798_boulder_ball; /* slope bounce height */
extern s32 D_801097A0_boulder_ball; /* the finish was set up */
extern f32 D_801097A4_boulder_ball[4]; /* per player: CPU target x */
extern s32 D_801097B4_boulder_ball[4]; /* per player: CPU mode */

extern f32 D_80109880_boulder_ball; /* finish camera steps */
extern f32 D_80109884_boulder_ball;
extern f32 D_80109888_boulder_ball;
extern s32 D_8010988C_boulder_ball; /* saved stick/button state of the CPU's controller */
extern u16 D_8010988E_boulder_ball; /* the low half of D_8010988C */
extern s32 D_80109890_boulder_ball;
extern u16 D_80109892_boulder_ball; /* the low half of D_80109890 */
extern s32 D_80109894_boulder_ball;
extern s8 D_80109897_boulder_ball; /* the low byte of D_80109894 */
extern s32 D_80109898_boulder_ball;
extern s8 D_8010989B_boulder_ball; /* the low byte of D_80109898 */
extern s32 D_8010989C_boulder_ball; /* the lone player (group 0) */
extern s16 D_8010989E_boulder_ball; /* the low half of D_8010989C */
extern u8 D_8010989F_boulder_ball; /* the low byte of D_8010989C */
extern omObjData* D_801098A0_boulder_ball; /* the first boulder */
extern omObjData* D_801098A4_boulder_ball; /* the lone player */

void func_801059A0_boulder_ball(void) {
    u8 cam;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 32.0f, 80.0f, 5000.0f);
    HmfLightDirSet(1, -94.0f, 65.0f, 34.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_80106B58_boulder_ball);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 5, 0, -1, func_80106C8C_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107924_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107A20_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107B0C_boulder_ball);
    D_801098A4_boulder_ball = omAddObj(3, 10, 60, -1, func_80107C08_boulder_ball);
    D_801098A0_boulder_ball = D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] =
        omAddObj(2, 4, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 900.0f;
    CRot.x = 358.0f;
    CRot.y = 0.0f;
    CZoom = 1400.0f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_80109760_boulder_ball);
    if (GwPlayer[0].group == 0) {
        D_8010989C_boulder_ball = 0;
    }
    if (GwPlayer[1].group == 0) {
        D_8010989C_boulder_ball = 1;
    }
    if (GwPlayer[2].group == 0) {
        D_8010989C_boulder_ball = 2;
    }
    if (GwPlayer[3].group == 0) {
        D_8010989C_boulder_ball = 3;
    }
    D_800EB930_minigame = 0x2F;
    D_800EB932_minigame = 0x24;
}

void func_80105E74_boulder_ball(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

/* Follow the three runners: the camera tracks the furthest (z) and lowest (y) of them. */
void func_80105EA0_boulder_ball(void) {
    f32 minY = 2000.0f;
    f32 maxZ = 0.0f;
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        if (maxZ < D_800EC598_minigame[i]->trans.z) {
            maxZ = D_800EC598_minigame[i]->trans.z;
        }
        if (D_800EC598_minigame[i]->trans.y < minY) {
            minY = D_800EC598_minigame[i]->trans.y;
        }
    }
    Center.x = 0.0f;
    Center.y = minY + 200.0f;
    Center.z = maxZ;
    if (maxZ > 890.0f) {
        Center.z = 890.0f;
    }
    if (Center.y < 325.0f) {
        Center.y = 325.0f;
    }
    if (Center.y > 550.0f) {
        Center.y = 550.0f;
    }
    CRot.x = 362.0f - (Center.z - 600.0f) / 60.0f;
    CZoom = 1500.0f - (Center.y - 325.0f);
    if (CRot.x > 370.0f) {
        CRot.x = 370.0f;
    }
    if (CRot.x < 358.0f) {
        CRot.x = 358.0f;
    }
    if (CZoom < 1300.0f) {
        CZoom = 1300.0f;
    }
}

/* Intro: the lone player turns the first boulder round, then the camera pulls back to the slope. */
void func_801060D0_boulder_ball(void) {
    s32 t;
    MgWork* w;
    BbBall* ball;

    t = func_800E6E9C_minigame();
    w = D_801098A4_boulder_ball->data;
    ball = D_801098A0_boulder_ball->data;
    if (t < 5) {
        Center.x = 0.0f;
        Center.y = 800.0f;
        Center.z = -700.0f;
        CZoom = 1000.0f;
        D_801098A0_boulder_ball->trans.x = sindf(D_801098A4_boulder_ball->rot.y) * 150.0f + 0.0f;
        D_801098A0_boulder_ball->trans.y = 700.0f;
        D_801098A0_boulder_ball->trans.z = cosdf(D_801098A4_boulder_ball->rot.y) * 150.0f + -900.0f;
    } else if (t < 40 && D_80109794_boulder_ball == 0) {
        D_801098A4_boulder_ball->rot.y -= 1.5f;
        if (D_801098A4_boulder_ball->rot.y < -26.0f) {
            D_801098A4_boulder_ball->rot.y = -26.0f;
        }
        if (D_801098A4_boulder_ball->rot.y == -26.0f) {
            func_8001C6A8_main(D_801098A4_boulder_ball->model[1], 0.0f);
            w->unk50 = 0;
            D_80109758_boulder_ball = 0;
            D_801098A0_boulder_ball->rot.y = ball->unk3C = D_801098A4_boulder_ball->rot.y;
            ball->unk40 = 7.0f;
            ball->unk78 = 0;
            ball->unk38 = -0.75f;
            D_80109794_boulder_ball = 1;
            func_8004AC98_main(0x31F, D_8010989E_boulder_ball);
        }
        D_801098A0_boulder_ball->trans.x = sindf(D_801098A4_boulder_ball->rot.y) * 150.0f + 0.0f;
        D_801098A0_boulder_ball->trans.y = 700.0f;
        D_801098A0_boulder_ball->trans.z = cosdf(D_801098A4_boulder_ball->rot.y) * 150.0f + -900.0f;
    } else {
        D_801098A4_boulder_ball->rot.y *= 0.8f;
        Center.y -= 6.6666665f;
        Center.z += 17.777779f;
        CZoom += 4.4444447f;
        if (Center.y < 325.0f) {
            Center.y = 325.0f;
        }
        if (Center.z > 890.0f) {
            Center.z = 890.0f;
        }
        if (CZoom > 1500.0f) {
            CZoom = 1500.0f;
        }
    }
    Hu3DModelRotSet(D_801098A4_boulder_ball->model[1], 0.0f, D_801098A4_boulder_ball->rot.y, 0.0f);
}

/* The slope: runs the minigame's states. */
// masked 0; raw: the finish loop that slows the three runners (unk3C *= 0.8f) loads the object into a0, GCC here
// into v0 (register allocation only)
#ifdef NON_MATCHING
void func_80106410_boulder_ball(omObjData* obj) {
    s32 i;
    s32 n;
    MgWork* w;
    f32 t;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        func_800E6E9C_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                func_801060D0_boulder_ball();
                break;
            case 2:
                func_80105EA0_boulder_ball();
                break;
            case 3:
                if (D_801097A0_boulder_ball == 0) {
                    D_801098A4_boulder_ball->func = func_80108798_boulder_ball;
                    func_800E131C_minigame(D_800EC1C0_minigame[0], 0.0f);
                    for (i = 0; i < (u16)D_800EC1B8_minigame; i++) {
                        func_8001C258_main(D_800EBE70_minigame[i]->model[0], 4, 4);
                        func_8001C258_main(D_800EBE70_minigame[i]->model[1], 4, 4);
                        if (D_80109744_boulder_ball[i] != -1) {
                            HuAudFXStop((s16)D_80109744_boulder_ball[i]);
                            D_80109744_boulder_ball[i] = -1;
                        }
                    }
                    if (D_8010975C_boulder_ball == 0) {
                        /* the lone player wins */
                        D_80109760_boulder_ball.unk06 = 0;
                        D_80109760_boulder_ball.unk18[0] = D_8010989F_boulder_ball;
                        func_8001C258_main(D_801098A4_boulder_ball->model[0], 4, 0);
                        func_8001C258_main(D_801098A4_boulder_ball->model[1], 4, 4);
                        func_800E5798_minigame(D_801098A4_boulder_ball, 6);
                        ((MgWork*)D_801098A4_boulder_ball->data)->unk38 = -D_800EB744_minigame;
                    } else {
                        /* the three win */
                        D_80109760_boulder_ball.unk06 = 2;
                        n = 0;
                        for (i = 0; i < 4; i++) {
                            if (D_8010989C_boulder_ball != i) {
                                D_80109760_boulder_ball.unk18[n++] = i;
                            }
                        }
                    }
                    D_80109880_boulder_ball = (CRot.x - 340.0f) / 60.0f;
                    D_80109884_boulder_ball = (Center.y - 700.0f) / 60.0f;
                    D_80109888_boulder_ball = (Center.z - -800.0f) / 60.0f;
                    D_801097A0_boulder_ball = 1;
                }
                for (i = 0; i < 3; i++) {
                    ((MgWork*)D_800EC598_minigame[i]->data)->unk3C *= 0.8f;
                }
                D_801098A4_boulder_ball->rot.y *= 0.8f;
                if (D_8010975C_boulder_ball == 0) {
                    CRot.x -= D_80109880_boulder_ball;
                    if (CRot.x < 340.0f) {
                        CRot.x = 340.0f;
                    }
                    Center.y -= D_80109884_boulder_ball;
                    if (Center.y > 700.0f) {
                        Center.y = 700.0f;
                    }
                    Center.z -= D_80109888_boulder_ball;
                    if (Center.z < -800.0f) {
                        Center.z = -800.0f;
                    }
                }
                break;
            case 4:
                if (D_800EB934_minigame[0] == 1) {
                    if (D_8010975C_boulder_ball == D_800EB934_minigame[0]) {
                        for (i = 0; i < 3; i++) {
                            w = D_800EC598_minigame[i]->data;
                            func_800E5798_minigame(D_800EC598_minigame[i], 0xD);
                            func_80045ED0_main(D_800A178C_main[GwPlayer[w->unk59].chr][0] | 0x2F);
                            GwPlayer[w->unk59].bonusCoin += 10;
                        }
                    } else {
                        GwPlayer[D_8010989C_boulder_ball].bonusCoin += 10;
                        for (i = 0; i < 3; i++) {
                            func_800E5798_minigame(D_800EC598_minigame[i], 0xE);
                        }
                        func_800E5798_minigame(D_801098A4_boulder_ball, 0xD);
                        func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010989C_boulder_ball].chr][0] | 0x2F);
                    }
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                obj->func = func_80105E74_boulder_ball;
                break;
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80105E74_boulder_ball;
        }
        if (D_80109754_boulder_ball != 1000.0f) {
            /* the slope's bounce after a boulder lands */
            t = D_80109754_boulder_ball;
            if (D_800EB774_minigame < t) {
                t = D_800EB774_minigame;
            }
            D_80109798_boulder_ball += t * t * (D_80109754_boulder_ball >= 0.0f ? -36.75f : 36.75f);
            D_80109754_boulder_ball += D_800EB748_minigame;
            if (D_80109798_boulder_ball < 0.0f) {
                D_80109798_boulder_ball = 0.0f;
                if (D_80109754_boulder_ball > 0.5f) {
                    D_80109754_boulder_ball = -D_80109754_boulder_ball * 0.5f;
                } else {
                    D_80109754_boulder_ball = 1000.0f;
                }
            }
            Hu3DModelPosSet(obj->model[1], 0.0f, D_80109798_boulder_ball, 0.0f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106410_boulder_ball);
#endif

/* The slope (ground object). */
void func_80106B58_boulder_ball(omObjData* obj) {
    BbGround* gw;

    D_800EB73C_minigame = 15.0f;
    obj->model[0] = func_8000B0A0_main(0x250000, 0x6B9);
    obj->model[1] = func_8000B0A0_main(0x250003, 0xAB9);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(BbGround), 31000);
    memset(gw, 0, sizeof(BbGround));
    obj->func = func_80106410_boulder_ball;
    gw->unk03 = 1;
    func_800E147C_minigame(obj);
    func_800E1370_minigame(obj, 1, 0.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 22.5f);
    func_800E1468_minigame(obj);
    gw->unk04 = 0;
    omSetStatBit(obj, 0xA0);
}

/* The second ground object (the finish area). */
void func_80106C8C_boulder_ball(omObjData* obj) {
    BbGround* gw;

    D_800EB73C_minigame = 15.0f;
    obj->model[0] = func_8000B0A0_main(0x250001, 0x29D);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(BbGround), 31000);
    memset(gw, 0, sizeof(BbGround));
    obj->func = NULL;
    gw->unk03 = 1;
    func_800E147C_minigame(obj);
    func_800E1370_minigame(obj, 1, 0.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 22.5f);
    func_800E1468_minigame(obj);
    gw->unk04 = 1;
    omSetStatBit(obj, 0xA0);
}

/* A player: models, motions and hooks. */
// masked 2: retail loads both stack constants (0xAC9, 0xA99) before storing them, GCC here interleaves (scheduling only)
#ifdef NON_MATCHING
void func_80106DAC_boulder_ball(omObjData* obj, s32 arg1, s32 arg2, u16 arg3) {
    MgWork* w;
    s32 chr;

    func_800E1BA8_minigame(obj, arg1, arg2, arg3, 0xAC9, 0xA99);
    w = obj->data;
    chr = GwPlayer[w->unk59].chr;
    obj->model[3] = func_8000B108_main(3, 0x88D);
    obj->model[4] = func_8000B108_main(4, 0x88D);
    obj->model[5] = func_8000B108_main(6, 0x88D);
    obj->model[7] = func_8000B108_main(8, 0x88D);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 0x11, func_80017BB8_main(chr, 0xE), 1, 0xF);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 0x1E, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(obj, 0x1F, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5A00_minigame(obj, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5978_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5978_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x78);
    w->unk4C = 0.05f;
    w->unkB4 = 0.8f;
    w->unkEC = func_8010707C_boulder_ball;
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 1);
    func_800E3568_minigame(w, 0, func_80107298_boulder_ball);
    func_800E3568_minigame(w, 1, func_80107194_boulder_ball);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106DAC_boulder_ball);
#endif

/* A player touched by a boulder: knocked flat. */
s32 func_8010707C_boulder_ball(omObjData* obj, omObjData* other) {
    MgWork* w;
    f32 x;
    f32 y;
    f32 z;

    w = obj->data;
    if (func_800E6E8C_minigame() == 2) {
        if (w->unkBE != 0) {
            D_800EC288_minigame++;
            return 1;
        }
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z;
        func_8004AC98_main(GwPlayer[w->unk59].chr + 0x287, w->unk59);
        func_8004AC98_main(0x320, w->unk59);
        func_800E561C_minigame(obj, 1);
        func_800E5690_minigame(obj, 0);
        func_800E4C88_minigame(obj, 7, x, y, z, 0.0f, 0.0f);
        w->unkBE = 0x69;
        omVibrate(w->unk59, 20, 0, 20);
    }
    return 1;
}

/* A player's per-frame hook: a CPU's controller state is restored; a runner past the line wins for the three. */
s32 func_80107194_boulder_ball(omObjData* obj) {
    MgWork* w;

    w = obj->data;
    if (GwPlayer[w->unk59].stat & 1) {
        D_800D5558_main[w->unk57] = D_80109892_boulder_ball;
        D_800CDA7C_main[w->unk57] = D_8010988E_boulder_ball;
        D_800CBB6E_main[w->unk57] = D_80109897_boulder_ball;
        D_800D20A1_main[w->unk57] = D_8010989B_boulder_ball;
    }
    if (func_800E6E8C_minigame() == 2 && obj->trans.z <= -600.0f) {
        func_800E6F0C_minigame(3);
        D_8010975C_boulder_ball = 1;
    }
    return 0;
}

// masked ~30: retail recomputes GwPlayer[player]'s offset for cpu_difficulty and keeps diff in s7 where GCC here
// CSEs the offset and spills diff, which shifts the loop registers; two nops after sindf/cosdf; logic checked
// block by block against the asm
#ifdef NON_MATCHING
/* CPU control of a runner: dodge the boulder nearest the slope's centre line. Saves the CPU's controller state
   (D_8010988C..D_80109898, restored by func_80107194) and writes its stick. */
s32 func_80107298_boulder_ball(omObjData* obj) {
    Vec v;
    f32 reach[4] = { 70.0f, 80.0f, 90.0f, 100.0f }; /* per difficulty: dodge distance beyond the two radii */
    f32 gain[4] = { 0.5f, 0.55f, 0.6f, 0.65f }; /* per difficulty: stick gain */
    MgWork* w;
    BbBall* ball;
    omObjData* b;
    s32 i;
    s32 near;
    f32 bx;
    f32 bz;
    f32 d;
    f32 dist;
    f32 heading;
    f32 speed;
    s32 player;
    s32 pad;
    s32 diff;

    w = obj->data;
    player = w->unk59;
    pad = w->unk57;
    if (func_800E6E8C_minigame() == 2) {
        if (GwPlayer[player].stat & 1) {
            D_80109890_boulder_ball = D_800D5558_main[pad];
            D_8010988C_boulder_ball = (u16)D_800CDA7C_main[pad];
            D_80109894_boulder_ball = D_800CBB6E_main[pad];
            D_80109898_boulder_ball = D_800D20A1_main[pad];
            D_800D20A1_main[pad] = 0;
            D_800CBB6E_main[pad] = 0;
            D_800D5558_main[pad] = 0;
            D_800CDA7C_main[pad] = 0;
            diff = GwPlayer[player].cpu_difficulty;
            bx = bz = v.x = v.y = v.z = 0.0f;
            near = -1;
            d = 30000.0f;
            for (i = 0; i < (u16)D_800EC1B8_minigame; i++) {
                b = D_800EBE70_minigame[i];
                ball = b->data;
                if (D_80109700_boulder_ball[ball->unk56] == 3) {
                    bx = b->trans.x;
                    bz = b->trans.z;
                    dist = HuSqrtf(bx * bx + bz * bz);
                    if (dist < d) {
                        d = dist;
                        near = i;
                    }
                }
            }
            if (near != -1) {
                /* step the boulder forward until it passes the runner */
                b = D_800EBE70_minigame[near];
                ball = b->data;
                bx = b->trans.x;
                bz = b->trans.z;
                heading = b->rot.y;
                speed = ball->unk40;
                for (i = 0; i < 100; i++) {
                    bx += sindf(heading) * speed;
                    bz += cosdf(heading) * speed;
                    speed += 0.3f;
                    if (speed > 35.0f) {
                        speed = 35.0f;
                    }
                    if (fabs(bx) > 450.0f - ball->unk48) {
                        heading = -heading;
                    }
                    if (obj->trans.z < bz) {
                        break;
                    }
                }
                v.x = obj->trans.x - bx;
                v.z = obj->trans.z - bz;
                v.y = 0.0f;
                func_800202FC_main(&v);
            }
            switch (D_801097B4_boulder_ball[player]) {
                case 0: /* wait */
                    D_800D20A1_main[pad] = 60;
                    if (near != -1) {
                        bx = obj->trans.x - bx;
                        bz = obj->trans.z - bz;
                        if (HuSqrtf(bx * bx + bz * bz) < w->unk48 + ball->unk48 + reach[diff]) {
                            D_800CBB6E_main[pad] = v.x * 60.0f * gain[diff];
                            D_801097B4_boulder_ball[player] = 1;
                        }
                    }
                    break;
                case 1: /* dodge away from the boulder */
                    v.x = obj->trans.x - bx;
                    v.z = obj->trans.z - bz;
                    v.y = 0.0f;
                    func_800202FC_main(&v);
                    D_800CBB6E_main[pad] = v.x * 60.0f * gain[diff];
                    D_800D20A1_main[pad] = 60;
                    bx = obj->trans.x - bx;
                    bz = obj->trans.z - bz;
                    d = HuSqrtf(bx * bx + bz * bz);
                    if (near == -1) {
                        D_801097B4_boulder_ball[player] = 2;
                    } else if (w->unk48 + ball->unk48 + reach[diff] < d) {
                        D_801097B4_boulder_ball[player] = 2;
                    }
                    break;
                case 2: /* return to its lane */
                    D_800D20A1_main[pad] = 60;
                    v.x = obj->trans.x - D_801097A4_boulder_ball[player];
                    v.z = 0.0f;
                    v.y = 0.0f;
                    func_800202FC_main(&v);
                    D_800CBB6E_main[pad] = -v.x * 60.0f * gain[diff];
                    if (D_801097A4_boulder_ball[player] - 50.0f < obj->trans.x &&
                        obj->trans.x < D_801097A4_boulder_ball[player] + 50.0f) {
                        D_801097B4_boulder_ball[player] = 0;
                    }
                    if (near != -1) {
                        bx = obj->trans.x - bx;
                        bz = obj->trans.z - bz;
                        if (HuSqrtf(bx * bx + bz * bz) < w->unk48 + ball->unk48 + reach[diff]) {
                            D_801097B4_boulder_ball[player] = 1;
                        }
                    }
                    break;
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107298_boulder_ball);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107924_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107A20_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107B0C_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107C08_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108000_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109818_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109828_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109838_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109848_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801083D8_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108798_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108A08_boulder_ball);

s32 func_80108CF4_boulder_ball(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108CFC_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108E5C_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801093B8_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80109410_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801095A0_boulder_ball);
