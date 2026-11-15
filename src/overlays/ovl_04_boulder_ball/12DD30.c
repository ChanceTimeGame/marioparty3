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
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
f64 fabs(f64);
void func_80088800_main(f32 (*mf)[4], f32 x, f32 y, f32 z);
void func_80017D24_main(f32 (*mf)[4], f32 rx, f32 ry, f32 rz);
void func_8004AE00_main(s16 handle, s16 pan);
f32 HuVecDot3F(Vec* a, Vec* b);
void func_80088700_main(f32 (*mf)[4], f32 x, f32 y, f32 z);

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
void func_800D6B70_minigame(omObjData* obj);
void func_800D861C_minigame(BbBall* w, s32 slot, void* fn);
s32 func_800E4A90_minigame(omObjData* obj);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1804_minigame(void);
void func_800E3568_minigame(MgWork* work, s32 slot, void* hook);
void func_800E3584_minigame(s16 mdl);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_800E561C_minigame(omObjData* obj, u8 flags);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern f32 D_800EB724_minigame;
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
extern Vec D_800EC298_minigame[]; /* wall normal of the last wall hit */

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
void func_801083D8_boulder_ball(omObjData* obj);
void func_80108000_boulder_ball(omObjData* obj);
void func_80108798_boulder_ball(omObjData* obj);
void func_80108A08_boulder_ball(omObjData* obj);
s32 func_80108CF4_boulder_ball(void);
void func_80108CFC_boulder_ball(omObjData* obj);
s32 func_80108E5C_boulder_ball(omObjData* obj);
void func_801093B8_boulder_ball(omObjData* obj);
s32 func_80109410_boulder_ball(omObjData* obj);
s32 func_801095A0_boulder_ball(omObjData* obj);

extern s32 D_80109700_boulder_ball[8]; /* per boulder: state */
extern Vec D_80109720_boulder_ball[3]; /* the runners' start positions */
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
extern s32 D_801097C4_boulder_ball; /* the next runner's player */
extern s32 D_801097CC_boulder_ball; /* frames since the finish */
extern s32 D_801097D0_boulder_ball; /* boulders created */
extern f32 D_801097D4_boulder_ball[8]; /* per boulder: roll angle */
extern s32 D_801097F4_boulder_ball; /* the boulder whose turn it is */
extern s32 D_801097C8_boulder_ball; /* lone CPU: target runner 0-2, 3/4 a side, 5 choose */

extern f32 D_80109880_boulder_ball; /* finish camera steps */
extern f32 D_80109884_boulder_ball;
extern f32 D_80109888_boulder_ball;
extern s32 D_8010988C_boulder_ball; /* saved stick/button state of the CPU's controller */
extern s32 D_80109890_boulder_ball;
extern s32 D_80109894_boulder_ball;
extern s32 D_80109898_boulder_ball;
extern s32 D_8010989C_boulder_ball; /* the lone player (group 0) */
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
            func_8004AC98_main(0x31F, (s16)D_8010989C_boulder_ball);
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
                        D_80109760_boulder_ball.unk18[0] = (u8)D_8010989C_boulder_ball;
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
        D_800D5558_main[w->unk57] = (u16)D_80109890_boulder_ball;
        D_800CDA7C_main[w->unk57] = (u16)D_8010988C_boulder_ball;
        D_800CBB6E_main[w->unk57] = (s8)D_80109894_boulder_ball;
        D_800D20A1_main[w->unk57] = (s8)D_80109898_boulder_ball;
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

/* The three runners: each takes the next player that is not the lone one. */
void func_80107924_boulder_ball(omObjData* obj) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(obj, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], (u16)D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_80109720_boulder_ball[0].x - 80.0f;
    obj->trans.x = D_80109720_boulder_ball[0].x;
    obj->trans.y = D_80109720_boulder_ball[0].y;
    obj->trans.z = D_80109720_boulder_ball[0].z;
    D_801097C4_boulder_ball++;
}

void func_80107A20_boulder_ball(omObjData* obj) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(obj, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], (u16)D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_80109720_boulder_ball[1].x;
    obj->trans.x = D_80109720_boulder_ball[1].x;
    obj->trans.y = D_80109720_boulder_ball[1].y;
    obj->trans.z = D_80109720_boulder_ball[1].z;
    D_801097C4_boulder_ball++;
}

void func_80107B0C_boulder_ball(omObjData* obj) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(obj, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], (u16)D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_80109720_boulder_ball[2].x + 80.0f;
    obj->trans.x = D_80109720_boulder_ball[2].x;
    obj->trans.y = D_80109720_boulder_ball[2].y;
    obj->trans.z = D_80109720_boulder_ball[2].z;
    D_801097C4_boulder_ball++;
}

/* The lone player (group 0): the framework's func_800E1BA8_minigame cut down, standing on top of the slope. */
void func_80107C08_boulder_ball(omObjData* obj) {
    MgWork* w;
    s32 file0;
    s32 file1;
    s32 i;
    s32 chr;
    s32 attrFx;
    s32 attr;

    attrFx = 0x89D;
    file1 = D_800A178C_main[GwPlayer[D_8010989C_boulder_ball].chr][2];
    file0 = D_800A178C_main[GwPlayer[D_8010989C_boulder_ball].chr][0];
    attr = 0xAD9;
    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = HuMemAllocTag(sizeof(MgWork), 31000);
    memset(obj->data, 0, sizeof(MgWork));
    w = obj->data;
    w->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 31000);
    for (i = 0; i < obj->mtncnt; i++) {
        obj->motion[i] = -1;
    }
    for (i = 0; i < obj->mtncnt; i++) {
        w->unkE8[i].unk00 = 0;
        w->unkE8[i].unk02 = 0;
        w->unkE8[i].unk04 = -1;
        w->unkE8[i].unk08 = -1;
    }
    chr = GwPlayer[D_8010989C_boulder_ball].chr;
    obj->model[0] = func_8000B108_main(file0 | file1, attr | 4);
    obj->model[1] = func_8000B108_main((GwPlayer[D_8010989C_boulder_ball].chr + 4) | 0x250000, attr);
    obj->model[5] = func_8000B0D4_main(9, attr);
    obj->model[2] = func_8000B108_main(4, attrFx);
    obj->model[3] = func_8000B108_main(4, attrFx);
    obj->model[4] = func_8000B108_main(4, attrFx);
    Hu3DModelScaleSet(obj->model[2], 2.1f, 2.1f, 2.1f);
    Hu3DModelScaleSet(obj->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[4], 2.2f, 2.2f, 2.2f);
    func_800E5978_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5978_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5978_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    w->unk57 = GwPlayer[D_8010989C_boulder_ball].pad;
    w->unk59 = (u8)D_8010989C_boulder_ball;
    w->unk50 = 0;
    obj->func = func_801083D8_boulder_ball;
    obj->trans.x = 0.0f;
    obj->trans.y = 700.0f;
    obj->trans.z = -900.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.5f, 1.5f);
    func_8001C92C_main(obj->model[1], 1.5f);
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
}


#ifndef NON_MATCHING /* func_80107298's local arrays */
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109818_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109828_boulder_ball);

/* func_80108000's local arrays */
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109838_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109848_boulder_ball);
#endif

// masked 0; raw: the target index and the hoisted runner count swap a1/a2 (register allocation only)
#ifdef NON_MATCHING
/* CPU control of the lone player: aim at the highest runner still standing, or at a side, then throw.
   Writes the stick (D_80109894) and the buttons (D_80109890, 0x8000 = throw). */
void func_80108000_boulder_ball(omObjData* obj) {
    MgWork* w = obj->data;
    f32 speed[4] = { 0.8f, 0.85f, 0.9f, 1.0f }; /* per difficulty: aiming speed */
    f32 margin[4] = { 100.0f, 75.0f, 50.0f, 0.0f }; /* per difficulty: below this height + 300 it throws to a side */
    s32 target = -1;
    omObjData* o;
    s32 i;
    f32 x;
    f32 z;
    f32 maxY;
    f32 a;
    u8 diff;

    if (w->unk50 == 1) {
        diff = GwPlayer[w->unk59].cpu_difficulty;
        D_80109894_boulder_ball = 0;
        D_8010988C_boulder_ball = 0;
        D_80109890_boulder_ball = 0;
        x = 0.0f;
        z = 0.0f;
        maxY = -10.0f;
        for (i = 0; i < D_800EC280_minigame; i++) {
            o = D_800EC598_minigame[i];
            if (((MgWork*)o->data)->unkBE == 0) {
                if (maxY < o->trans.y) {
                    x = o->trans.x;
                    maxY = o->trans.y;
                    z = o->trans.z;
                    target = i;
                }
            }
        }
        if (D_801097C8_boulder_ball == 5) {
            if (maxY < margin[diff] + 300.0f) {
                if (rand8() > 0x80) {
                    D_801097C8_boulder_ball = 3;
                } else {
                    D_801097C8_boulder_ball = 4;
                }
            } else {
                D_801097C8_boulder_ball = target;
            }
        }
        switch (D_801097C8_boulder_ball) {
            case 0:
            case 1:
            case 2:
                a = atan2df(x, z - obj->trans.z);
                if (a > 0.0f) {
                    D_80109894_boulder_ball = speed[diff] * 60.0f;
                    if (w->unk3C > 30.0f) {
                        D_80109890_boulder_ball |= 0x8000;
                    }
                    if (a < w->unk3C) {
                        D_80109890_boulder_ball |= 0x8000;
                    }
                } else {
                    D_80109894_boulder_ball = speed[diff] * -60.0f;
                    if (w->unk3C < -30.0f) {
                        D_80109890_boulder_ball |= 0x8000;
                    }
                    if (w->unk3C < a) {
                        D_80109890_boulder_ball |= 0x8000;
                    }
                }
                break;
            case 3:
                D_80109894_boulder_ball = speed[diff] * 60.0f;
                if (speed[diff] * 55.0f < w->unk3C) {
                    D_80109890_boulder_ball |= 0x8000;
                }
                break;
            case 4:
                D_80109894_boulder_ball = speed[diff] * -60.0f;
                if (w->unk3C < speed[diff] * -55.0f) {
                    D_80109890_boulder_ball |= 0x8000;
                }
                break;
        }
        if (D_80109890_boulder_ball != 0) {
            D_801097C8_boulder_ball = 5;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108000_boulder_ball);
#endif

/* The lone player's per-frame function: turn the boulder, throw it, then pick up the next. */
void func_801083D8_boulder_ball(omObjData* obj) {
    MgWork* w;
    BbBall* ball;
    s32 player;
    s32 pad;

    w = obj->data;
    player = w->unk59;
    pad = w->unk57;
    if (func_800E6E8C_minigame() == 2) {
        D_80109890_boulder_ball = D_800D5558_main[pad];
        D_8010988C_boulder_ball = (u16)D_800CDA7C_main[pad];
        D_80109894_boulder_ball = D_800CBB6E_main[pad];
        D_80109898_boulder_ball = D_800D20A1_main[pad];
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
        D_800D5558_main[pad] = 0;
        D_800CDA7C_main[pad] = 0;
        if (GwPlayer[player].stat & 1) {
            func_80108000_boulder_ball(obj);
        }
        switch (w->unk50) {
            case 0: /* the boulder is rolling: turn back to the centre */
                w->unk3C *= 0.8f;
                if (fabs(w->unk3C) < 1.0) {
                    w->unk3C = 0.0f;
                }
                if (fabs(w->unk3C) < 1.0) {
                    w->unk3C = 0.0f;
                }
                if (D_80109758_boulder_ball == 1) {
                    w->unk50 = 1;
                }
                break;
            case 1: /* holding a boulder: aim with the stick, throw with B */
                ball = D_801098A0_boulder_ball->data;
                w->unk3C += D_80109894_boulder_ball / 15.0f;
                if (w->unk3C > 60.0f) {
                    w->unk3C = 60.0f;
                }
                if (w->unk3C < -60.0f) {
                    w->unk3C = -60.0f;
                }
                if (D_80109890_boulder_ball & 0x8000) {
                    func_8001C6A8_main(obj->model[1], 0.0f);
                    w->unk50 = 0;
                    D_80109758_boulder_ball = 0;
                    ball->unk3C = w->unk3C;
                    ball->unk40 = rand8() / 64.0f + 7.0f;
                    ball->unk78 = 0;
                    ball->unk38 = -0.75f;
                    func_8004AC98_main(0x31F, player);
                }
                D_801098A0_boulder_ball->trans.x = sindf(w->unk3C) * 150.0f + 0.0f;
                D_801098A0_boulder_ball->trans.y = 700.0f;
                D_801098A0_boulder_ball->trans.z = cosdf(w->unk3C) * 150.0f + -900.0f;
                Hu3DModelPosSet(D_801098A0_boulder_ball->model[1], D_801098A0_boulder_ball->trans.x, 705.0f,
                                D_801098A0_boulder_ball->trans.z);
                ball->unk3C = w->unk3C;
                break;
        }
        obj->rot.y = w->unk3C;
        Hu3DModelRotSet(obj->model[1], 0.0f, obj->rot.y, 0.0f);
        D_800D5558_main[pad] = (u16)D_80109890_boulder_ball;
        D_800CDA7C_main[pad] = (u16)D_8010988C_boulder_ball;
        D_800CBB6E_main[pad] = (s8)D_80109894_boulder_ball;
        D_800D20A1_main[pad] = (s8)D_80109898_boulder_ball;
    }
}

/* The lone player after the finish: lands, and shows an effect per frame count. */
void func_80108798_boulder_ball(omObjData* obj) {
    MgWork* w;
    f32 t;
    f32 y;

    if (func_800E4A90_minigame(obj) & 0x20) {
        w = obj->data;
        t = w->unk38;
        y = obj->trans.y;
        if (D_800EB774_minigame < t) {
            t = D_800EB774_minigame;
        }
        y += t * t * (w->unk38 >= 0.0f ? -35.0f : 35.0f);
        w->unk38 += D_800EB748_minigame;
        if (y < 700.0f) {
            func_800E5690_minigame(obj, 0);
            y = 700.0f;
        }
        obj->trans.y = y;
    }
    switch (D_801097CC_boulder_ball) {
        case 1:
            Hu3DModelPosSet(obj->model[2], obj->trans.x - 10.0f, obj->trans.y + 20.0f, obj->trans.z + 30.0f);
            func_8001C6A8_main(obj->model[2], 0.0f);
            func_8001C258_main(obj->model[2], 4, 0);
            break;
        case 4:
            Hu3DModelPosSet(obj->model[3], obj->trans.x + 10.0f, obj->trans.y + 40.0f, obj->trans.z + 30.0f);
            func_8001C6A8_main(obj->model[3], 0.0f);
            func_8001C258_main(obj->model[3], 4, 0);
            break;
        case 6:
            Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y + 30.0f, obj->trans.z + 30.0f);
            func_8001C6A8_main(obj->model[4], 0.0f);
            func_8001C258_main(obj->model[4], 4, 0);
            break;
    }
    func_800E4E30_minigame(obj);
    D_801097CC_boulder_ball++;
}

/* A boulder: the framework's item actor with this game's hooks. */
void func_80108A08_boulder_ball(omObjData* obj) {
    BbBall* ball;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(BbBall), 31000);
    memset(obj->data, 0, sizeof(BbBall));
    ball = obj->data;
    obj->model[0] = func_8000B0A0_main(0x250002, 0xAD9);
    obj->model[1] = func_8000B0D4_main(9, 0xAD9);
    func_800E3584_minigame(obj->model[1]);
    obj->model[2] = func_8000B108_main(4, 0x89D);
    obj->model[3] = func_8000B108_main(4, 0x89D);
    obj->model[4] = func_8000B108_main(4, 0x89D);
    obj->model[5] = func_8000B108_main(4, 0x89D);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[4], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    obj->func = func_800D6B70_minigame;
    ball->unk44 = 0.3f;
    ball->unk48 = 70.0f;
    ball->unk34 = 180.0f;
    ball->unk3C = 0.0f;
    ball->unk78 = 0;
    ball->unk52 = 7;
    ball->unk7C = 0;
    ball->unk50 = 0;
    ball->unk40 = 0.0f;
    ball->unk74 = 0.5f;
    ball->unk56 = (u16)D_801097D0_boulder_ball;
    ball->unk54 = 1;
    for (i = 0; i < 9; i++) {
        ball->unk84[i] = NULL;
    }
    func_800E149C_minigame(obj, 0, 1);
    func_800E149C_minigame(obj, 1, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 700.0f;
    obj->trans.z = -600.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    func_80088700_main((f32(*)[4])HmfModelData[obj->model[1]].mtx, 2.0f, 2.0f, 2.0f);
    D_801097D0_boulder_ball++;
    func_800D861C_minigame(ball, 2, func_80108CF4_boulder_ball);
    func_800D861C_minigame(ball, 0, func_80108E5C_boulder_ball);
    func_800D861C_minigame(ball, 1, func_801093B8_boulder_ball);
    func_800D861C_minigame(ball, 4, func_80109410_boulder_ball);
    func_800D861C_minigame(ball, 5, func_801095A0_boulder_ball);
    D_800EB724_minigame = 35.0f;
}

s32 func_80108CF4_boulder_ball(void) {
    return 1;
}

/* A boulder hook: on frames 1 and 6 of a bounce, puff dust from a free (or the oldest) dust model. */
void func_80108CFC_boulder_ball(omObjData* obj) {
    s32 i;
    s32 sel;
    s32 st;
    s32 t;
    f32 max;
    f32 v;

    sel = ((BbBall*)obj->data)->unk56;
    st = D_80109700_boulder_ball[sel];
    if (st < 4) {
        if (st > 0) {
            if ((t = func_800E6E9C_minigame()) == 1 || t == 6) {
                max = 0.0f;
                for (i = 0; i < 4; i++) {
                    v = HmfModelData[obj->model[i + 2]].unk40;
                    if (v == 0.0f) {
                        sel = i;
                        break;
                    }
                    if (max < v) {
                        max = v;
                        sel = i;
                    }
                }
                Hu3DModelPosSet(obj->model[sel + 2], obj->trans.x, t * 10.0f + obj->trans.y, obj->trans.z);
                func_8001C6A8_main(obj->model[sel + 2], 0.0f);
                func_8001C258_main(obj->model[sel + 2], 4, 0);
            }
        }
    }
}

// masked: one instruction; retail schedules D_80109744[idx]'s index shift into the mfc1 delay slot of the pan
// argument, GCC here computes it before (an extra nop shifts the rest); logic checked against the asm
#ifdef NON_MATCHING
/* A boulder hook (slot 0): the boulder's states. 0 waits above the lone player for its turn, 1 drops onto the
   slope, 2 waits to be thrown, 3 rolls down, 4 fell off the bottom. */
s32 func_80108E5C_boulder_ball(omObjData* obj) {
    BbBall* ball;
    s32 idx;
    s32 ret;
    s32 i;
    f32 pan;
    f32 step;

    ret = 0;
    switch (func_800E6E8C_minigame()) {
        case 3:
            func_80108CFC_boulder_ball(obj);
            return 1;
        case 0:
        case 2:
            break;
        default:
            return 1;
    }
    ball = obj->data;
    idx = ball->unk56;
    func_80088800_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, 90.0f, 0.0f);
    func_80017D24_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, D_801097D4_boulder_ball[idx], 0.0f, 0.0f);
    obj->rot.y = ball->unk3C;
    switch (D_80109700_boulder_ball[idx]) {
        case 0:
            obj->trans.x = 0.0f;
            obj->trans.y = 1500.0f;
            obj->trans.z = -900.0f;
            ball->unk38 = 0.0f;
            ball->unk40 = 0.0f;
            ball->unk3C = 0.0f;
            D_801097D4_boulder_ball[idx] = 0.0f;
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            if (D_801097F4_boulder_ball == idx) {
                ball->unk78++;
                if (ball->unk78 >= 26) {
                    D_80109700_boulder_ball[idx] = 1;
                    ball->unk78 = 0;
                    func_8001C258_main(obj->model[0], 4, 0);
                    func_8001C258_main(obj->model[1], 4, 0);
                }
            }
            ret = 1;
            break;
        case 1:
            if (obj->trans.y == 700.0f) {
                D_80109700_boulder_ball[idx] = 2;
                D_80109758_boulder_ball = 1;
                D_801098A0_boulder_ball = D_800EBE70_minigame[D_801097F4_boulder_ball];
                D_80109754_boulder_ball = -D_800EB744_minigame * 0.5f;
                for (i = 0; i < 4; i++) {
                    omVibrate(i, 2, 2, 20);
                }
            }
            break;
        case 2:
            if (D_80109758_boulder_ball == 0) {
                D_80109700_boulder_ball[idx] = 3;
                D_801097F4_boulder_ball++;
                if (D_801097F4_boulder_ball == (u16)D_800EC1B8_minigame) {
                    D_801097F4_boulder_ball = 0;
                }
                D_80109744_boulder_ball[idx] = HuAudFXPlay(0x31D);
            }
            ret = 1;
            break;
        case 3:
            step = ball->unk40 / 502.64f * 360.0f;
            D_801097D4_boulder_ball[idx] = step + D_801097D4_boulder_ball[idx];
            if (D_80109744_boulder_ball[idx] != -1) {
                if (ball->unk38 > 0.0f) {
                    func_8004AAD0_main((s16)D_80109744_boulder_ball[idx], 0x7F);
                } else {
                    func_8004AAD0_main((s16)D_80109744_boulder_ball[idx], 0x60);
                }
                pan = obj->trans.x / 400.0f;
                if (pan > 1.0f) {
                    pan = 1.0f;
                }
                if (pan < -1.0f) {
                    pan = -1.0f;
                }
                func_8004AE00_main((s16)D_80109744_boulder_ball[idx], pan * 32.0f + 64.0f);
            }
            if (obj->trans.z > 1400.0f) {
                D_80109700_boulder_ball[idx] = 4;
                ball->unk40 = 0.0f;
                D_801097D4_boulder_ball[idx] = 0.0f;
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C258_main(obj->model[3], 4, 4);
                func_8001C258_main(obj->model[4], 4, 4);
                func_8001C258_main(obj->model[5], 4, 4);
                HuAudFXStop((s16)D_80109744_boulder_ball[idx]);
                D_80109744_boulder_ball[idx] = -1;
            }
            break;
        case 4:
            ball->unk78++;
            if (ball->unk78 >= 11) {
                D_80109700_boulder_ball[idx] = 0;
                ball->unk78 = 0;
            }
            ret = 1;
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108E5C_boulder_ball);
#endif

/* A boulder hook (slot 1): accelerate while rolling. Returns nothing although the hook table is s32 (*)(). */
void func_801093B8_boulder_ball(omObjData* obj) {
    BbBall* ball = obj->data;

    ball->unk40 += 0.3f;
    ball->unk78++;
    if (ball->unk40 > 35.0f) {
        ball->unk40 = 35.0f;
    }
}

/* A boulder hook (slot 4): a bounce while rolling puffs dust; sets a new random bounce. */
s32 func_80109410_boulder_ball(omObjData* obj) {
    BbBall* ball;
    s32 i;
    s32 sel;
    f32 max;
    f32 v;

    ball = obj->data;
    sel = ball->unk56;
    if (D_80109700_boulder_ball[sel] == 3) {
        sel = 0;
        if (ball->unk38 > 0.4f) {
            max = 0.0f;
            for (i = 0; i < 4; i++) {
                v = HmfModelData[obj->model[i + 2]].unk40;
                if (v == 0.0f) {
                    sel = i;
                    break;
                }
                if (max < v) {
                    max = v;
                    sel = i;
                }
            }
            Hu3DModelPosSet(obj->model[sel + 2], obj->trans.x, obj->trans.y + 10.0f, obj->trans.z);
            func_8001C6A8_main(obj->model[sel + 2], 0.0f);
            func_8001C258_main(obj->model[sel + 2], 4, 0);
        }
    }
    ball->unk38 = rand8() / 500.0f + 0.0f;
    return 1;
}

/* A boulder hook (slot 5): bounce off a side wall (reflect the heading about the wall normal). */
s32 func_801095A0_boulder_ball(omObjData* obj) {
    BbBall* ball;
    Vec n;
    Vec d;
    Vec r;
    f32 dot;
    s32 i;

    ball = obj->data;
    n.x = D_800EC298_minigame[0].x;
    n.y = d.y = 0.0f;
    n.z = D_800EC298_minigame[0].z;
    d.x = sindf(ball->unk3C + 180.0f);
    d.z = cosdf(ball->unk3C + 180.0f);
    dot = HuVecDot3F(&n, &d);
    n.x *= dot;
    n.z *= dot;
    HuVecSubtract(&r, &n, &d);
    HuVecAdd(&r, &n, &r);
    ball->unk3C = atan2df(r.x, r.z);
    for (i = 0; i < 4; i++) {
        omVibrate(i, 2, 3, 10);
    }
    func_8004AE00_main(HuAudFXPlay(0x31E), n.x > 0.0f ? 0x20 : 0x60);
    return 1;
}

s32 D_80109700_boulder_ball[8] = { 2, 0, 0, 0, 0, 0, 0, 0 }; /* per boulder: state */
Vec D_80109720_boulder_ball[3] = {
    { 320.0f, 0.0f, 1000.0f },
    { 0.0f, 0.0f, 1000.0f },
    { -320.0f, 0.0f, 1000.0f },
}; /* the runners' start positions (D_8010972C, D_80109738 are [1], [2]) */
s32 D_80109744_boulder_ball[4] = { -1, -1, -1, -1 }; /* per boulder: rolling sound; D_80109746 (undefined_syms.txt) is [0]'s low half */
f32 D_80109754_boulder_ball = 1000.0f;
s32 D_80109758_boulder_ball = 1;
s32 D_8010975C_boulder_ball = 0;
BbCtrl D_80109760_boulder_ball = {
    0, 2, 1, 2, 0, 0, 0, 0, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0, 0, 0, 0 }, 135, 900, -1, 75, 150, 0,
}; /* D_80109766, D_80109778 (undefined_syms.txt) are its unk06, unk18 */
s32 D_80109788_boulder_ball[3] = { 0, 0, 0 }; /* unreferenced */
s32 D_80109794_boulder_ball = 0;
f32 D_80109798_boulder_ball = 0.0f;
s32 D_8010979C_boulder_ball = 0; /* unreferenced */
s32 D_801097A0_boulder_ball = 0;
f32 D_801097A4_boulder_ball[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_801097B4_boulder_ball[4] = { 0, 0, 0, 0 };
s32 D_801097C4_boulder_ball = 0;
s32 D_801097C8_boulder_ball = 5;
s32 D_801097CC_boulder_ball = 0;
s32 D_801097D0_boulder_ball = 0;
f32 D_801097D4_boulder_ball[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_801097F4_boulder_ball = 0;
s32 D_801097F8_boulder_ball[2] = { 0, 0 }; /* unreferenced: pads .data to 0x100 (without it KMC as also shifts .text by a word) */
