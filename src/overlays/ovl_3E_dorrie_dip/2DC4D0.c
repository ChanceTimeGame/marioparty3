#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// dr A: Dorrie Dip

/* omObjData::data of the splashes (D_8010A248), one under each Dorrie */
typedef struct DrSplash {
    /* 0x00 */ f32 unk00[6]; /* x */
    /* 0x18 */ f32 unk18[6]; /* y */
    /* 0x30 */ f32 unk30[6]; /* z */
    /* 0x48 */ s32 unk48[6]; /* 1: playing */
} DrSplash; /* size 0x60 */

/* The CPU's plan (D_8010A254) */
typedef struct DrCpu {
    /* 0x00 */ s32 unk00; /* frames to hold B after pressing A */
    /* 0x04 */ s32 unk04; /* the Dorrie to hook */
    /* 0x08 */ s32 unk08; /* A pressed */
} DrCpu; /* size 0xC */

/* omObjData::data of the wakes behind the Dorries (D_8010A260) */
typedef struct DrWake {
    /* 0x00 */ f32 unk00[6]; /* x */
    /* 0x18 */ f32 unk18[6]; /* y */
    /* 0x30 */ f32 unk30[6]; /* z */
    /* 0x48 */ f32 unk48[6]; /* x scale */
    /* 0x60 */ s32 unk60[6]; /* 1: shown */
} DrWake; /* size 0x78 */

/* omObjData::data of the ground (D_8010A224; the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct DrGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA8];
} DrGround; /* size 0xB4 */

/* omObjData::data of the ring of Dorries (D_8010A230): models 0-5 the Dorries, 6-11 their shadows */
typedef struct DrRing {
    /* 0x00 */ s32 unk00[6]; /* 1: swimming */
    /* 0x18 */ f32 unk18[6]; /* angle around the centre */
    /* 0x30 */ f32 unk30[6]; /* angular speed */
} DrRing; /* size 0x48 */

/* omObjData::data of the hook (D_8010A238) */
typedef struct DrHook {
    /* 0x00 */ s32 unk00; /* 2: dropping, 4: rising */
    /* 0x04 */ Vec unk04; /* "item_hook" position */
    /* 0x10 */ s32 unk10; /* frames at the bottom */
} DrHook; /* size 0x14 */

/* omObjData::data of the prizes (D_8010A23C): models 0-4 the prizes, 5-9 their shadows */
typedef struct DrPrize {
    /* 0x00 */ f32 unk00[5]; /* x */
    /* 0x14 */ f32 unk14[5]; /* y */
    /* 0x28 */ f32 unk28[5]; /* z */
    /* 0x3C */ f32 unk3C[5]; /* falling speed */
    /* 0x50 */ f32 unk50[5]; /* shadow scale */
    /* 0x64 */ f32 unk64[5]; /* shadow y */
    /* 0x78 */ f32 unk78[5]; /* bob angle */
    /* 0x8C */ f32 unk8C[5]; /* bob base y */
    /* 0xA0 */ s32 unkA0[5]; /* flags; 1: riding its Dorrie, 2: falling on it, 4: hooked, 8: bobbing (won) */
    /* 0xB4 */ s32 unkB4[5]; /* the Dorrie carrying it */
} DrPrize; /* size 0xC8 */

/* omObjData::data of the dud on the Dorrie with no prize (D_8010A234): model 0 it, 1 its shadow */
typedef struct DrDud {
    /* 0x00 */ f32 unk00; /* x */
    /* 0x04 */ f32 unk04; /* y */
    /* 0x08 */ f32 unk08; /* z */
    /* 0x0C */ f32 unk0C; /* falling speed */
    /* 0x10 */ f32 unk10; /* y rotation */
    /* 0x14 */ s32 unk14; /* flags; 1: falling on its Dorrie, 2: riding it, 4: hooked */
    /* 0x18 */ f32 unk18; /* shadow scale */
    /* 0x1C */ f32 unk1C; /* shadow y */
} DrDud; /* size 0x20 */

/* An entry of D_800CBB60_main (minigame BD210.c's MgSprModel) */
typedef struct DrSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8* unk20;
} DrSprModel; /* size 0x24 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8004AD70_main(void);
void func_800557A0_main(void);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
void GMesPosSet(s16 mesId, f32 x, f32 y);
void func_80016B00_main(s16 model, s16 frame, char* name, HuMtx4F mtx);
void func_80088800_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out);

extern s32 D_800A178C_main[][6];

extern s8 D_800CBB6E_main[];
extern DrSprModel* D_800CBB60_main;
extern u16 D_800A11D0_main[6]; /* the prize items */
extern u16 D_800A11DC_main[5]; /* CPU target odds, percent */
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[];

omObjData* func_80045ED0_main(u32 arg0);

// minigame
void func_800E5798_minigame(omObjData* obj, s32 motion);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E1490_minigame(u16 arg0);
void func_800DDD94_minigame(omObjData* obj);
void func_800E149C_minigame(omObjData* obj, s32 arg1, s32 arg2);
void func_800E6F0C_minigame(s8 arg0);
u16 func_800E6E9C_minigame(void);
extern s32 D_800EBEB0_minigame[];
extern f32 D_800EB774_minigame;

// this overlay
void func_80105B44_dorrie_dip(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z);
void func_80105C7C_dorrie_dip(omObjData* obj);
void func_80105FD0_dorrie_dip(omObjData* obj);
void func_8010601C_dorrie_dip(void);
void func_80106210_dorrie_dip(omObjData* obj);
void func_801064FC_dorrie_dip(void);
void func_80106538_dorrie_dip(void);
void func_80106668_dorrie_dip(omObjData* obj);
void func_80106BEC_dorrie_dip(void);
void func_80106D50_dorrie_dip(void);
void func_80106E14_dorrie_dip(omObjData* obj, s32 player);
void func_80107360_dorrie_dip(omObjData* obj);
void func_80106DB8_dorrie_dip(omObjData* obj);
void func_801074CC_dorrie_dip(void);
void func_801074F8_dorrie_dip(void);
void func_80107690_dorrie_dip(void);
void func_801079D4_dorrie_dip(omObjData* obj);
void func_80107D58_dorrie_dip(void);
void func_80107D08_dorrie_dip(void);
void func_80107EE0_dorrie_dip(omObjData* obj);
void func_80108128_dorrie_dip(void);
void func_80108148_dorrie_dip(void);
void func_80108174_dorrie_dip(void);
void func_801081D4_dorrie_dip(void);
void func_801081A8_dorrie_dip(void);
void func_80108458_dorrie_dip(void);
void func_80108484_dorrie_dip(void);
void func_80108678_dorrie_dip(void);
void func_80108700_dorrie_dip(void);
void func_80108800_dorrie_dip(void);
void func_80108A74_dorrie_dip(s16 model, char* name, s16 frame, Vec* out);
void func_801086A4_dorrie_dip(void);
void func_8010872C_dorrie_dip(void);
void func_8010898C_dorrie_dip(omObjData* obj);
void func_80108B98_dorrie_dip(void);
void func_80108C6C_dorrie_dip(omObjData* obj);
void func_80108EA0_dorrie_dip(s32 idx);
void func_801090C4_dorrie_dip(void);
void func_801090F0_dorrie_dip(void);
void func_801092E0_dorrie_dip(void);
void func_8010930C_dorrie_dip(void);
void func_801095FC_dorrie_dip(omObjData* obj);
void func_80109520_dorrie_dip(void);
void func_801096F0_dorrie_dip(void);
void func_8010971C_dorrie_dip(void);
void func_80109738_dorrie_dip(void);
void func_80109978_dorrie_dip(void);
void func_80109B28_dorrie_dip(void);
void func_80109C14_dorrie_dip(omObjData* obj);
void func_80109E1C_dorrie_dip(s32 idx);
void func_80109F00_dorrie_dip(void);

/* .data */
extern D_80111B50_vine_with_me_Struct D_8010A040_dorrie_dip;
extern s8 D_8010A046_dorrie_dip; /* result message (D_8010A040.unk06) */
extern s32 D_8010A068_dorrie_dip; /* frame of the next ambient sound 1 */
extern s32 D_8010A06C_dorrie_dip; /* frame of the next ambient sound 2 */

/* .bss (ovl_3E_bss) */
extern f32 D_8010A1F0_dorrie_dip;
extern s32 D_8010A1F4_dorrie_dip; /* camera */
extern u8 D_8010A1F8_dorrie_dip;
extern s16 D_8010A1FA_dorrie_dip; /* prize sparkle effect */
extern s32 D_8010A1FC_dorrie_dip; /* the player (D_8010A1FE: its low half, read by narrowing loads) */
extern s32 D_8010A200_dorrie_dip; /* the Dorrie with no prize */
extern s32 D_8010A208_dorrie_dip[6]; /* prize under each Dorrie, 0x11 none */
extern s32 D_8010A220_dorrie_dip; /* hooked Dorrie, -1 none */
extern omObjData* D_8010A224_dorrie_dip;
extern f32 D_8010A22C_dorrie_dip; /* Dorrie height */
extern omObjData* D_8010A230_dorrie_dip;
extern omObjData* D_8010A234_dorrie_dip;
extern omObjData* D_8010A238_dorrie_dip;
extern omObjData* D_8010A23C_dorrie_dip;
extern s32 D_8010A240_dorrie_dip;
extern f32 D_8010A244_dorrie_dip; /* Dorrie bob angle */
extern omObjData* D_8010A248_dorrie_dip;
extern omObjData* D_8010A24C_dorrie_dip;
extern s32 D_8010A250_dorrie_dip; /* 2: ripples running */
extern DrCpu D_8010A254_dorrie_dip;
extern omObjData* D_8010A260_dorrie_dip;

void func_801059A0_dorrie_dip(void) {
    omObjData* obj;

    omInitObjMan(30, 10);
    Hu3DAnimInit(16);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_80105B44_dorrie_dip(500.0f, 345.0f, 0.0f, 0.0f, 0.0f, 190.0f, 0.0f);
    omOutView(obj);
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame(&D_8010A040_dorrie_dip);
    D_800EBE28_minigame = 0;
    D_800EC280_minigame = 0;
    func_800E18D8_minigame();
    D_800EB774_minigame = 1.0f;
    WipeCreateIn(0xFF, 16);
    func_80108800_dorrie_dip();
    omAddObj(0x50, 0, 0, -1, func_80105C7C_dorrie_dip);
    func_8010601C_dorrie_dip();
    func_80106538_dorrie_dip();
    omAddObj(4, 10, 60, -1, func_80106DB8_dorrie_dip);
    func_80107690_dorrie_dip();
    func_80107D58_dorrie_dip();
    func_80108B98_dorrie_dip();
    func_80109520_dorrie_dip();
    func_801096F0_dorrie_dip();
    func_80109978_dorrie_dip();
    func_80109B28_dorrie_dip();
    D_8010A1F8_dorrie_dip = 0;
}

void func_80105B44_dorrie_dip(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    D_8010A1F4_dorrie_dip = func_8000B638_main();
    ScissorSet(D_8010A1F4_dorrie_dip, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010A1F4_dorrie_dip, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
    Hu3DCamSetPerspective(D_8010A1F4_dorrie_dip, 41.5f, 80.0f, 8000.0f);
}

/* The main loop: framework state, ambient sounds, finish and result. Retail passes obj to
   func_800E6F40_minigame, which takes no argument. */
void func_80105C7C_dorrie_dip(omObjData* obj) {
    u8 (*state)(omObjData*) = (u8 (*)(omObjData*))(void (*)(void))func_800E6F40_minigame;
    s32 i;

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (state(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 30) {
                func_801074CC_dorrie_dip();
            }
            if (func_800E6E9C_minigame() == 60) {
                func_80108148_dorrie_dip();
            }
            if (func_800E6E9C_minigame() == 120) {
                func_80106D50_dorrie_dip();
            }
            if (D_8010A068_dorrie_dip == func_800E6E9C_minigame()) {
                if (D_8010A068_dorrie_dip == 1) {
                    HuAudSeqPlay(0x44);
                }
                HuAudFXPlay(0x4E7);
                D_8010A068_dorrie_dip += 30 + (rand8() >> 3);
            }
            if (D_8010A06C_dorrie_dip == func_800E6E9C_minigame()) {
                HuAudFXPlay(0x4E8);
                D_8010A06C_dorrie_dip += 30 + (rand8() >> 3);
            }
            break;
        case 1:
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                func_80108700_dorrie_dip();
                func_80108678_dorrie_dip();
            }
            break;
        case 3:
            if (func_800E6E9C_minigame() == 1) {
                if (D_8010A1F8_dorrie_dip == 2) {
                    func_80108458_dorrie_dip();
                } else {
                    func_801081A8_dorrie_dip();
                    for (i = 0; i < 6; i++) {
                        if (i != D_8010A220_dorrie_dip) {
                            func_80108EA0_dorrie_dip(i);
                        }
                    }
                }
                if (D_8010A220_dorrie_dip == -1 || D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] == 0x11) {
                    D_8010A046_dorrie_dip = 7;
                } else {
                    D_8010A046_dorrie_dip = 5;
                }
            }
            if (func_800E6E9C_minigame() == 15 && D_8010A220_dorrie_dip != -1 &&
                D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 0x11) {
                func_80108EA0_dorrie_dip(D_8010A220_dorrie_dip);
                func_801092E0_dorrie_dip();
            }
            break;
        case 4:
            if (func_800E6E9C_minigame() == 1) {
                func_801090C4_dorrie_dip();
            }
            break;
        case 5:
            if (D_8010A220_dorrie_dip != -1 && D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 0x11) {
                GwPlayer[D_8010A1FC_dorrie_dip].bonusCoin = D_8010A208_dorrie_dip[D_8010A220_dorrie_dip];
            } else {
                GwPlayer[D_8010A1FC_dorrie_dip].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80105FD0_dorrie_dip;
            break;
    }
}

void func_80105FD0_dorrie_dip(omObjData* obj) {
    func_8004AB0C_main(30);
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        GMesClose();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

/* The ring of six Dorries and their shadows. */
void func_8010601C_dorrie_dip(void) {
    s32 attr = 0x699;
    s32 attr2 = 0x69D;
    omObjData* obj;
    DrRing* work;
    s32 i;

    obj = omAddObj(0xFA, 12, 0, -1, func_80106210_dorrie_dip);
    D_8010A230_dorrie_dip = obj;
    work = obj->data = HuMemAllocTag(sizeof(DrRing), 0x7918);
    for (i = 0; i < 6; i++) {
        work->unk00[i] = 0;
        work->unk18[i] = i * 60.0f;
        work->unk30[i] = 0;
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5F0002, attr);
            omSetRot(obj, 0.0f, work->unk18[0], 0.0f);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelRotSet(obj->model[i], 0.0f, work->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[6] = func_8000B108_main(0x5F000B, attr2);
            Hu3DModelRotSet(obj->model[6], 0.0f, 0.0f, 0.0f);
        } else {
            obj->model[i + 6] = Hu3DModelLink(obj->model[6]);
            Hu3DModelRotSet(obj->model[i + 6], 0.0f, 0.0f, 0.0f);
        }
        func_8001C814_main(obj->model[i + 6], 2, 2);
    }
}

void func_80106210_dorrie_dip(omObjData* obj) {
    DrRing* work = obj->data;
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 6; i++) {
        x = sindf(work->unk18[i]) * 450.0f;
        y = D_8010A22C_dorrie_dip;
        z = cosdf(work->unk18[i]) * 450.0f;
        if (i == 0) {
            omSetTra(obj, x, y, z);
            omSetRot(obj, 0.0f, work->unk18[0], 0.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], x, y, z);
            Hu3DModelRotSet(obj->model[i], 0.0f, work->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        Hu3DModelPosSet(obj->model[i + 6], sindf(work->unk18[i]) * 450.0f, 0.0f, cosdf(work->unk18[i]) * 450.0f);
        Hu3DModelRotSet(obj->model[i + 6], 0.0f, work->unk18[i], 0.0f);
    }
    for (i = 0; i < 6; i++) {
        if (work->unk00[i] & 1) {
            work->unk18[i] -= work->unk30[i];
            if (work->unk18[i] <= 0.0f) {
                work->unk18[i] += 360.0f;
            }
            work->unk30[i] += 0.2f;
            if (work->unk30[i] > 4.8f) {
                work->unk30[i] = 4.8f;
            }
            if (work->unk30[i] >= 4.0f && work->unk30[i] < 4.2f) {
                func_8001C258_main(D_8010A230_dorrie_dip->model[i + 6], 4, 0);
                func_8001C814_main(D_8010A230_dorrie_dip->model[i + 6], 2, 2);
            }
        }
    }
}

/* Set every Dorrie swimming. */
void func_801064FC_dorrie_dip(void) {
    DrRing* work = D_8010A230_dorrie_dip->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        work->unk00[i] |= 1;
    }
}

/* The hook and its five motions. */
void func_80106538_dorrie_dip(void) {
    omObjData* obj;
    DrHook* work;

    obj = omAddObj(0xFF, 1, 5, -1, func_80106668_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DrHook), 0x7918);
    D_8010A238_dorrie_dip = obj;
    work = obj->data;
    obj->model[0] = func_8000B108_main(0x5F0005, 0x699);
    func_8000B460_main(obj, 0, 0x5F0006);
    func_8000B460_main(obj, 1, 0x5F0007);
    func_8000B460_main(obj, 2, 0x5F0008);
    func_8000B460_main(obj, 3, 0x5F0009);
    func_8000B460_main(obj, 4, 0x5F000A);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    work->unk00 = 0;
    work->unk10 = 0;
    D_8010A220_dorrie_dip = -1;
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
}

/* NON_MATCHING: masked 0; retail keeps `found` in v1 and the D_8010A220 load in a0 (raw 5) */
#ifdef NON_MATCHING
/* The hook: catch the Dorrie under it at the bottom of the drop, then rise. */
void func_80106668_dorrie_dip(omObjData* obj) {
    DrHook* work = obj->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    DrPrize* prize = D_8010A23C_dorrie_dip->data;
    DrDud* w234 = D_8010A234_dorrie_dip->data;
    s32 found;
    s32 i;
    f32 frame;
    Vec pos;

    if (work->unk00 & 2) {
        if (HmfModelData[obj->model[0]].unk40 == 50.0f && work->unk04.y < 20.0f && D_8010A220_dorrie_dip == -1 &&
            work->unk10 < 15) {
            if (work->unk10 == 0) {
                func_8001C814_main(obj->model[0], 8, 8);
            }
            for (i = 0; i < 6; i++) {
                if (ring->unk18[i] >= 265.0f && ring->unk18[i] < 275.0f) {
                    D_8010A220_dorrie_dip = i;
                    omVibrate(D_8010A1FC_dorrie_dip, 10, 0, 10);
                    break;
                }
            }
            if (D_8010A220_dorrie_dip != -1) {
                func_8001EF6C_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip], obj->model[0], "item_hook");
                func_8001C258_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip], 0x4000, 0x4000);
                func_8001C258_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip + 6], 4, 4);
                ring->unk00[D_8010A220_dorrie_dip] &= ~1;
                func_8001C814_main(obj->model[0], 8, 0);
                found = -1;
                if (D_8010A220_dorrie_dip == D_8010A200_dorrie_dip) {
                    w234->unk14 |= 4;
                } else {
                    for (i = 0; i < 5; i++) {
                        if (D_8010A220_dorrie_dip == prize->unkB4[i]) {
                            found = i;
                        }
                    }
                    prize->unkA0[found] |= 4;
                    HuAudFXPlay(0x4E6);
                }
            }
            if (++work->unk10 == 15) {
                func_8001C814_main(obj->model[0], 8, 0);
            }
        }
    }
    if (work->unk00 & 4) {
        frame = HmfModelData[obj->model[0]].unk40;
        if ((frame >= 28.0f) & (frame < 30.0f)) {
            HuAudFXPlay(0x4E3);
        }
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= frame) {
            work->unk00 &= ~4;
            func_8001C624_main(obj->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[0]].unk02, 0, 10, 0);
            func_8001C814_main(obj->model[0], 2, 2);
        }
        if (HmfModelData[obj->model[0]].unk40 == 50.0f) {
            func_8001C814_main(D_8010A224_dorrie_dip->model[1], 8, 0);
            func_8001C814_main(D_8010A224_dorrie_dip->model[1], 2, 2);
            func_8010971C_dorrie_dip();
            func_801064FC_dorrie_dip();
            for (i = 0; i < 6; i++) {
                func_80109E1C_dorrie_dip(i);
            }
        }
    }
    func_80108A74_dorrie_dip(obj->model[0], "item_hook", HmfModelData[obj->model[0]].unk40, &pos);
    work->unk04.x = pos.x;
    work->unk04.y = pos.y;
    work->unk04.z = pos.z;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106668_dorrie_dip);
#endif

void func_80106BC0_dorrie_dip(void) {
    omAddPrcObj(func_80106BEC_dorrie_dip, 0x50, 0, 0);
}

/* Process: drop the hook (motion 1), then back to idle (motion 0) and the game goes on. */
void func_80106BEC_dorrie_dip(void) {
    DrHook* work = D_8010A238_dorrie_dip->data;

    func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[1]].unk02, 0, 10, 0);
    work->unk00 |= 2;
    while (HmfModelData[D_8010A238_dorrie_dip->model[0]].unk40 <
           D_800CCF58_main[HmfModelData[D_8010A238_dorrie_dip->model[0]].unk02].unk02) {
        HuPrcVSleep();
    }
    func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[0]].unk02, 0, 10, 0);
    func_8001C814_main(D_8010A238_dorrie_dip->model[0], 2, 2);
    work->unk00 &= ~2;
    func_800E6F0C_minigame(3);
    omDelPrcObj(NULL);
}

/* Raise the hook (motion 2). */
void func_80106D50_dorrie_dip(void) {
    DrHook* work = D_8010A238_dorrie_dip->data;

    work->unk00 |= 4;
    func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[2]].unk02, 0, 10, 0);
}

/* Find the playing player (group 0). */
void func_80106DB8_dorrie_dip(omObjData* obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010A1FC_dorrie_dip = i;
            break;
        }
    }
    func_80106E14_dorrie_dip(obj, D_8010A1FC_dorrie_dip);
}

/* NON_MATCHING: masked 10; retail loads the two 0x20A99 stack arguments after the table loads (scheduling) */
#ifdef NON_MATCHING
/* The player: character model, the extra models and the motions. */
void func_80106E14_dorrie_dip(omObjData* obj, s32 player) {
    s32 mot0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    s32 mot1[8] = { 4, 4, 4, 4, 4, 4, 4, 4 };
    s32 mot2[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
    s32 mot3[8] = { 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36 };
    s32 mot4[8] = { 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35 };
    s32 mot5[8] = { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F };
    s32 mot6[8] = { 6, 6, 6, 6, 6, 6, 6, 6 };
    s32 mot7[8] = { 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C };
    func_800E1BA8_minigame_ObjData* work;
    s32 chr;

    D_800EC598_minigame[D_800EC280_minigame++] = obj;
    chr = GwPlayer[player].chr;
    func_800E1BA8_minigame(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][3], player, 0x20A99, 0x20A99);
    work = obj->data;
    obj->model[3] = func_8000B108_main(3, 0x6DD);
    obj->model[4] = func_8000B108_main(4, 0x6DD);
    obj->model[6] = func_8000B108_main(5, 0x6DD);
    obj->model[5] = func_8000B108_main(6, 0x6DD);
    obj->model[7] = func_8000B108_main(8, 0x6DD);
    obj->model[8] = func_8000B108_main(7, 0x6DD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, mot0[chr]), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, mot1[chr]), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, mot2[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, mot3[chr]), 1, 0x78);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, mot4[chr]), 1, 0x78);
    func_800E5A00_minigame(obj, 0x12, func_80017BB8_main(chr, mot5[chr]), 2, 0);
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, mot6[chr]), 1, 0x1D);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, mot7[chr]), 0, 0);
    omSetTra(obj, 50.0f, 133.0f, 0.0f);
    work->unk3C = 270.0f;
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 2);
    func_800E149C_minigame(obj, 2, 2);
    func_800E149C_minigame(obj, 3, 2);
    func_800E149C_minigame(obj, 4, 2);
    func_800E5690_minigame(obj, 0);
    D_8010A240_dorrie_dip = 0;
    obj->func = func_80107360_dorrie_dip;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A094_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0B4_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0D4_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0F4_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A114_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A134_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A154_dorrie_dip);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A174_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106E14_dorrie_dip);
#endif

/* The player's object function: the framework moves it, its position stays put. */
void func_80107360_dorrie_dip(omObjData* obj) {
    func_800E1BA8_minigame_ObjData* work = obj->data;
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    D_800CBB6E_main[work->unk57] = 0;
    D_800D20A1_main[work->unk57] = 0;
    if (GwPlayer[work->unk59].stat & 1) {
        D_800CDA7C_main[work->unk57] = 0;
        D_800D5558_main[work->unk57] = 0;
    }
    if (func_800E6E8C_minigame() == 2 && (GwPlayer[work->unk59].stat & 1)) {
        func_80109F00_dorrie_dip();
    }
    func_800DDD94_minigame(obj);
    if (work->unk5C == 0x200) {
        D_8010A1F8_dorrie_dip = 3;
        if (work->unk5C == 0x200 && work->unk50 == 0x80 && !(D_8010A240_dorrie_dip & 1)) {
            D_8010A240_dorrie_dip |= 1;
            func_80106BC0_dorrie_dip();
        }
    }
    work->unk60 = 0.0f;
    obj->trans.x = x;
    obj->trans.z = z;
}

void func_801074CC_dorrie_dip(void) {
    omAddPrcObj(func_801074F8_dorrie_dip, 0x50, 0, 0);
}

/* Process: move the camera over 30 frames to its playing view. */
void func_801074F8_dorrie_dip(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += 34.7f;
        CRot.x += -1.44666648f;
        if (CRot.x < 301.6f) {
            CRot.x = 301.6f;
        }
        Center.x += -0.0966666713f;
        Center.y += -3.04666662f;
        Center.z += 2.75333333f;
        HuPrcVSleep();
    }
    CZoom = 1541.0f;
    CRot.x = 301.6f;
    Center.x = -2.9f;
    Center.y = 98.6f;
    Center.z = 82.6f;
    omDelPrcObj(NULL);
}

/* The prizes: one on each Dorrie except a random one (D_8010A200). */
void func_80107690_dorrie_dip(void) {
    s32 unused[16]; /* cleared, never read */
    s32 files[16] = { 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C };
    omObjData* obj;
    DrPrize* work;
    DrRing* ring;
    void* data;
    s32 spr;
    s32 i;
    s32 n;

    obj = omAddObj(0xFE, 10, 0, -1, func_801079D4_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DrPrize), 0x7918);
    D_8010A23C_dorrie_dip = obj;
    work = obj->data;
    ring = D_8010A230_dorrie_dip->data;
    for (i = 0; i < 16; i++) {
        unused[i] = 0;
    }
    (void)unused;
    D_8010A200_dorrie_dip = (u8)(rand8() % 6);
    D_8010A208_dorrie_dip[D_8010A200_dorrie_dip] = 0x11;
    for (n = 0, i = 0; i < 6; i++) {
        if (i != D_8010A200_dorrie_dip) {
            D_8010A208_dorrie_dip[i] = D_800A11D0_main[n];
            data = DataRead(files[D_8010A208_dorrie_dip[i]] | 0x210000);
            spr = HmfSprModelCreate(data, 0xA99, 8);
            DataClose(data);
            obj->model[n] = D_800CBB60_main[(s16)spr].unk00;
            func_8001C2FC_main(obj->model[n], 0x70000000, 0x70000000);
            work->unk00[n] = sindf(ring->unk18[i]) * 450.0f;
            work->unk14[n] = 1500.0f;
            work->unk28[n] = cosdf(ring->unk18[i]) * 450.0f;
            work->unkB4[n] = i;
            work->unk64[n] = 30.0f;
            work->unk8C[n] = 0.0f;
            work->unk78[n] = 0.0f;
            if (n == 0) {
                omSetTra(obj, work->unk00[0], work->unk14[0], work->unk28[0]);
                omSetSca(obj, 3.0f, 3.0f, 3.0f);
            } else {
                Hu3DModelPosSet(obj->model[n], work->unk00[n], work->unk14[n], work->unk28[n]);
                Hu3DModelScaleSet(obj->model[n], 3.0f, 3.0f, 3.0f);
            }
            work->unkA0[n] = 0;
            if (n == 0) {
                obj->model[5] = func_8000B108_main(9, 0x4A9);
            } else {
                obj->model[n + 5] = Hu3DModelLink(obj->model[5]);
            }
            n++;
        }
    }
}

void func_801079D4_dorrie_dip(omObjData* obj) {
    DrPrize* work = obj->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    DrHook* hook = D_8010A238_dorrie_dip->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, work->unk00[0], work->unk14[0], work->unk28[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk14[i], work->unk28[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], work->unk00[i], work->unk64[i], work->unk28[i]);
        if (work->unkA0[i] & 4) {
            work->unk50[i] = 1.0f;
        } else {
            work->unk50[i] = (1440.0f - work->unk14[i]) / 1440.0f;
        }
        Hu3DModelScaleSet(obj->model[i + 5], work->unk50[i], 1.0f, work->unk50[i]);
        if (work->unkA0[i] & 1) {
            work->unk00[i] = sindf(ring->unk18[work->unkB4[i]]) * 450.0f;
            work->unk14[i] = D_8010A22C_dorrie_dip + 60.0f;
            work->unk28[i] = cosdf(ring->unk18[work->unkB4[i]]) * 450.0f;
        }
        if (work->unkA0[i] & 2) {
            work->unk14[i] += work->unk3C[i];
            work->unk3C[i] -= 3.0f;
            if (work->unk14[i] <= 60.0f) {
                work->unk14[i] = 60.0f;
                work->unkA0[i] = (work->unkA0[i] & ~2) | 1;
            }
        }
        if (work->unkA0[i] & 4) {
            work->unk00[i] = hook->unk04.x;
            work->unk14[i] = hook->unk04.y + 80.0f;
            work->unk28[i] = hook->unk04.z;
            work->unk64[i] = hook->unk04.y + 30.0f;
        }
        if (work->unkA0[i] & 8) {
            work->unk14[i] = sindf(work->unk78[i]) * 50.0f + work->unk8C[i];
            work->unk78[i] += 5.0f;
            if (work->unk78[i] >= 360.0f) {
                work->unk78[i] -= 360.0f;
            }
            func_8000CFA4_main(D_8010A1FA_dorrie_dip, work->unk00[i], work->unk14[i], work->unk28[i]);
        }
    }
}

/* Drop every prize from the sky. */
void func_80107D08_dorrie_dip(void) {
    DrPrize* work = D_8010A23C_dorrie_dip->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        work->unkA0[i] |= 2;
        work->unk3C[i] = 0.0f;
        work->unk14[i] = 1500.0f;
    }
}

/* The dud on the Dorrie with no prize. */
void func_80107D58_dorrie_dip(void) {
    omObjData* obj;
    DrDud* work;
    DrRing* ring;

    obj = omAddObj(0xFE, 2, 3, -1, func_80107EE0_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DrDud), 0x7918);
    D_8010A234_dorrie_dip = obj;
    work = obj->data;
    ring = D_8010A230_dorrie_dip->data;
    obj->model[0] = func_8000B108_main(0xA00EE, 0x4B9);
    obj->model[1] = func_8000B108_main(9, 0x4A9);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F6);
    func_8000B460_main(obj, 2, 0xA00F1);
    func_8001C814_main(obj->model[0], 2, 2);
    work->unk00 = sindf(ring->unk18[D_8010A200_dorrie_dip]) * 450.0f;
    work->unk04 = 1500.0f;
    work->unk08 = cosdf(ring->unk18[D_8010A200_dorrie_dip]) * 450.0f;
    work->unk1C = 30.0f;
    work->unk10 = 0.0f;
    work->unk14 = 0;
    omSetTra(obj, work->unk00, work->unk04, work->unk08);
}

void func_80107EE0_dorrie_dip(omObjData* obj) {
    DrDud* work = obj->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    DrHook* hook = D_8010A238_dorrie_dip->data;

    omSetTra(obj, work->unk00, work->unk04, work->unk08);
    omSetRot(obj, 0.0f, work->unk10, 0.0f);
    Hu3DModelPosSet(obj->model[1], work->unk00, work->unk1C, work->unk08);
    if (work->unk14 & 4) {
        work->unk18 = 1.0f;
    } else {
        work->unk18 = (1440.0f - work->unk04) / 1440.0f;
    }
    Hu3DModelScaleSet(obj->model[1], work->unk18, 1.0f, work->unk18);
    if (work->unk14 & 2) {
        work->unk00 = sindf(ring->unk18[D_8010A200_dorrie_dip]) * 450.0f;
        work->unk04 = 50.0f;
        work->unk08 = cosdf(ring->unk18[D_8010A200_dorrie_dip]) * 450.0f;
        work->unk10 = ring->unk18[D_8010A200_dorrie_dip];
    }
    if (work->unk14 & 1) {
        work->unk04 += work->unk0C;
        work->unk0C -= 3.0f;
        work->unk10 = ring->unk18[D_8010A200_dorrie_dip];
        if (work->unk04 <= 60.0f) {
            work->unk04 = 60.0f;
            work->unk14 = (work->unk14 & ~1) | 2;
        }
    }
    if (work->unk14 & 4) {
        work->unk00 = hook->unk04.x;
        work->unk04 = hook->unk04.y + 60.0f;
        work->unk08 = hook->unk04.z;
        work->unk1C = hook->unk04.y + 30.0f;
    }
}

/* Drop the dud from the sky. */
void func_80108128_dorrie_dip(void) {
    DrDud* work = D_8010A234_dorrie_dip->data;

    work->unk14 |= 1;
    work->unk0C = 0.0f;
}

void func_80108148_dorrie_dip(void) {
    omAddPrcObj(func_80108174_dorrie_dip, 0x50, 0, 0);
}

/* Process: drop the prizes, then the dud 30 frames later. */
void func_80108174_dorrie_dip(void) {
    func_80107D08_dorrie_dip();
    HuPrcSleep(30);
    func_80108128_dorrie_dip();
    omDelPrcObj(NULL);
}

void func_801081A8_dorrie_dip(void) {
    omAddPrcObj(func_801081D4_dorrie_dip, 0x50, 0, 0);
}

/* Process: the dud turns to face out; hooked, it plays motion 1; otherwise it jumps off its Dorrie. */
void func_801081D4_dorrie_dip(void) {
    DrDud* work = D_8010A234_dorrie_dip->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    f32 dist;
    f32 vy;
    s32 landed;

    work->unk14 &= ~2;
    if (D_8010A220_dorrie_dip == D_8010A200_dorrie_dip) {
        while (work->unk10 != 0.0f) {
            work->unk10 += 9.0f;
            if (work->unk10 >= 360.0f) {
                work->unk10 = 0.0f;
            }
            HuPrcVSleep();
        }
        func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
        func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
        HuAudFXPlay(0x4E2);
        omDelPrcObj(NULL);
    }
    dist = 450.0f;
    vy = 90.0f;
    work->unk10 = ring->unk18[D_8010A200_dorrie_dip];
    landed = 0;
    func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
    do {
        work->unk00 = dist * sindf(ring->unk18[D_8010A200_dorrie_dip]);
        work->unk04 += vy;
        vy -= 10.0f;
        dist += 30.0f;
        if (work->unk04 < 80.0f) {
            work->unk04 = 80.0f;
            if (landed == 0) {
                landed = 1;
                func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[2]);
                func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
            }
        }
        work->unk08 = dist * cosdf(ring->unk18[D_8010A200_dorrie_dip]);
        HuPrcVSleep();
    } while (dist < 1050.0f);
    omDelPrcObj(NULL);
}

void func_80108458_dorrie_dip(void) {
    omAddPrcObj(func_80108484_dorrie_dip, 0x50, 0, 0);
}

/* Process: time up. Stop the Dorries, sink the others, and turn the dud back to 0. */
void func_80108484_dorrie_dip(void) {
    DrDud* work = D_8010A234_dorrie_dip->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    s32 i;
    f32 step;

    for (i = 0; i < 6; i++) {
        ring->unk00[i] &= ~1;
        func_8001C258_main(D_8010A230_dorrie_dip->model[i + 6], 4, 4);
        if (i != D_8010A200_dorrie_dip) {
            func_80108EA0_dorrie_dip(i);
        }
    }
    func_8001C814_main(D_8010A224_dorrie_dip->model[1], 1, 1);
    func_801096F0_dorrie_dip();
    work->unk14 &= ~2;
    if (work->unk10 >= 180.0) {
        step = 9.0f;
    } else {
        step = -9.0f;
    }
    while (work->unk10 != 0.0f) {
        work->unk10 += step;
        if (work->unk10 >= 360.0f) {
            work->unk10 = 0.0f;
        }
        if (work->unk10 < 0.0f) {
            work->unk10 = 0.0f;
        }
        HuPrcVSleep();
    }
    func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
    func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
    omDelPrcObj(NULL);
}

void func_80108678_dorrie_dip(void) {
    omAddPrcObj(func_801086A4_dorrie_dip, 0x50, 0, 0);
}

/* Process: wait for the player's A press. */
void func_801086A4_dorrie_dip(void) {
    while (1) {
        if (D_800D5558_main[D_8010A1FC_dorrie_dip] & 0x8000) {
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80108700_dorrie_dip(void) {
    omAddPrcObj(func_8010872C_dorrie_dip, 0x50, 0, 0);
}

/* The 10-second timer. */
void func_8010872C_dorrie_dip(void) {
    s32 sec = 10;
    s32 t = 30;

    GMesPosSet(GMesCreate(0x1A, 10, 160, 28), 160.0f, 28.0f);
    do {
        if (--t == 0) {
            t = 30;
            sec--;
        }
        func_8003F578_main(sec);
        HuPrcVSleep();
    } while (func_800E6E8C_minigame() != 3 && sec > 0);
    if (D_8010A1F8_dorrie_dip == 0) {
        D_8010A1F8_dorrie_dip = 2;
        func_800E6F0C_minigame(3);
    }
    func_8003F5C0_main();
    omDelPrcObj(NULL);
}

/* The ground: the island and the sea. */
void func_80108800_dorrie_dip(void) {
    omObjData* obj;
    DrGround* work;

    obj = omAddObj(0xFF, 4, 0, -1, func_8010898C_dorrie_dip);
    D_8010A224_dorrie_dip = obj;
    obj->data = work = HuMemAllocTag(sizeof(DrGround), 0x7918);
    obj->model[0] = func_8000B0A0_main(0x5F0000, 0x699);
    obj->model[1] = func_8000B0A0_main(0x5F0001, 0x699);
    obj->model[2] = func_8000B0A0_main(0x5F0003, 0x699);
    obj->model[3] = func_8000B0A0_main(0x5F0004, 0x699);
    D_8010A1F0_dorrie_dip = 1.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    memset(obj->data, 0, sizeof(DrGround));
    work->unk03 = 1;
    work->unk08 = 0.5f;
    work->unk04 = 0;
    func_800E1370_minigame(obj, 2, 133.0f);
    func_8001C814_main(obj->model[1], 8, 8);
    func_8001C814_main(obj->model[1], 2, 2);
    omSetTra(obj, 0.0f, 13.0f, 0.0f);
    D_8010A244_dorrie_dip = 0.0f;
}

/* The Dorries bob in the water. */
void func_8010898C_dorrie_dip(omObjData* obj) {
    D_8010A22C_dorrie_dip = sindf(D_8010A244_dorrie_dip) * 10.0f - 10.0f;
    D_8010A244_dorrie_dip += 5.0f;
    if (D_8010A244_dorrie_dip >= 360.0f) {
        D_8010A244_dorrie_dip -= 360.0f;
    }
    HmfModelData[obj->model[1]].pos.y = D_8010A22C_dorrie_dip;
    HmfModelData[obj->model[3]].pos.y = D_8010A22C_dorrie_dip + 5.0f;
}

/* The world position of a model's named object at a frame. */
void func_80108A74_dorrie_dip(s16 model, char* name, s16 frame, Vec* out) {
    HuMtx4F mdl;
    HuMtx4F res;
    HuMtx4F obj;
    HmfModel* m;

    func_80016B00_main(model, frame, name, obj);
    m = &HmfModelData[model];
    func_80088800_main(mdl, m->pos.x, m->pos.y, m->pos.z);
    func_80017D24_main(mdl, m->rot.x, m->rot.y, m->rot.z);
    func_80017CD0_main(mdl, m->scale.x, m->scale.y, m->scale.z);
    func_80018044_main(obj, mdl, res);
    out->x = res[0][0] + res[1][0] + res[2][0] + res[3][0];
    out->y = res[0][1] + res[1][1] + res[2][1] + res[3][1];
    out->z = res[0][2] + res[1][2] + res[2][2] + res[3][2];
}

/* The splashes, one under each Dorrie. */
void func_80108B98_dorrie_dip(void) {
    s32 attr = 0xA3D;
    omObjData* obj;
    DrSplash* work;
    s32 i;

    obj = omAddObj(0xFF, 6, 0, -1, func_80108C6C_dorrie_dip);
    D_8010A248_dorrie_dip = obj;
    work = obj->data = HuMemAllocTag(sizeof(DrSplash), 0x7918);
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5D0008, attr);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        work->unk48[i] = 0;
    }
}

void func_80108C6C_dorrie_dip(omObjData* obj) {
    DrSplash* work = obj->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    s32 i;
    f32 x;
    f32 z;

    for (i = 0; i < 6; i++) {
        x = sindf(ring->unk18[i]) * 450.0f;
        z = cosdf(ring->unk18[i]) * 450.0f;
        work->unk00[i] = x;
        work->unk18[i] = 50.0f;
        work->unk30[i] = z;
        if (i == 0) {
            omSetTra(obj, work->unk00[0], work->unk18[0], work->unk30[0]);
            omSetRot(obj, CRot.x, 0.0f, 0.0f);
            omSetSca(obj, 1.5f, 1.5f, 1.5f);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk18[i], work->unk30[i]);
            Hu3DModelRotSet(obj->model[i], CRot.x, 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], 1.5f, 1.5f, 1.5f);
        }
        if (work->unk48[i] & 1) {
            if (D_800CCF58_main[HmfModelData[obj->model[i]].unk02].unk02 <= HmfModelData[obj->model[i]].unk40) {
                func_8001C258_main(obj->model[i], 4, 4);
                work->unk48[i] &= ~1;
            }
        }
    }
}

/* A Dorrie dives: hide it, its shadow and its prize, and splash. */
void func_80108EA0_dorrie_dip(s32 idx) {
    DrSplash* splash = D_8010A248_dorrie_dip->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    DrPrize* prize = D_8010A23C_dorrie_dip->data;
    DrHook* hook = D_8010A238_dorrie_dip->data;
    s32 found;
    s32 i;
    f32 x;
    f32 z;

    func_8001C258_main(D_8010A230_dorrie_dip->model[idx], 4, 4);
    func_8001C258_main(D_8010A230_dorrie_dip->model[idx + 6], 4, 4);
    found = -1;
    for (i = 0; i < 5; i++) {
        if (prize->unkB4[i] == idx) {
            found = i;
        }
    }
    if (found != -1) {
        if (idx != D_8010A220_dorrie_dip) {
            func_8001C258_main(D_8010A23C_dorrie_dip->model[found], 4, 4);
        }
        func_8001C258_main(D_8010A23C_dorrie_dip->model[found + 5], 4, 4);
    }
    x = sindf(ring->unk18[idx]) * 450.0f;
    z = cosdf(ring->unk18[idx]) * 450.0f;
    splash->unk00[idx] = x;
    splash->unk18[idx] = 50.0f;
    splash->unk30[idx] = z;
    if (idx == D_8010A220_dorrie_dip) {
        splash->unk00[idx] = hook->unk04.x;
        splash->unk18[idx] = hook->unk04.y;
        splash->unk30[idx] = hook->unk04.z;
    }
    ring->unk00[idx] &= ~1;
    splash->unk48[idx] |= 1;
    func_8001C258_main(D_8010A248_dorrie_dip->model[idx], 4, 0);
    func_8001C814_main(D_8010A224_dorrie_dip->model[1], 1, 1);
}

void func_801090C4_dorrie_dip(void) {
    omAddPrcObj(func_801090F0_dorrie_dip, 0x50, 0, 0);
}

/* Process: the player turns to the camera and cheers (motion 13) or is let down (motion 14). */
void func_801090F0_dorrie_dip(void) {
    func_800E1BA8_minigame_ObjData* work = D_800EC598_minigame[0]->data;
    s32 i;

    func_800E5798_minigame(D_800EC598_minigame[0], 0x26);
    for (i = 0; i < 10; i++) {
        work->unk3C = i * 90.0f / 10.0f + 270.0f;
        HuPrcVSleep();
    }
    if (D_8010A220_dorrie_dip != -1 && D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 0x11) {
        func_800E5798_minigame(D_800EC598_minigame[0], 0xD);
        func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[4]].unk02, 0, 10, 0);
        func_80045ED0_main(D_800A178C_main[GwPlayer[work->unk59].chr][0] | 0x35);
        for (i = 0; i < 60; i++) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x4E4);
    } else {
        func_800E5798_minigame(D_800EC598_minigame[0], 0xE);
        if (D_8010A220_dorrie_dip == -1) {
            func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[3]].unk02, 0, 10, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801092E0_dorrie_dip(void) {
    omAddPrcObj(func_8010930C_dorrie_dip, 0x50, 0, 0);
}

/* Process: the won prize flies in an arc from the hook to above the player. */
void func_8010930C_dorrie_dip(void) {
    DrPrize* prize;
    DrHook* hook;
    s32 found;
    s32 i;
    f32 dx;
    f32 dz;
    f32 y;
    f32 angle;

    HuAudFXPlay(0x19);
    prize = D_8010A23C_dorrie_dip->data;
    hook = D_8010A238_dorrie_dip->data;
    D_8010A1FA_dorrie_dip = func_8000CED8_main(0xB0004, 0x6A9);
    found = -1;
    for (i = 0; i < 5; i++) {
        if (prize->unkB4[i] == D_8010A220_dorrie_dip) {
            found = i;
        }
    }
    if (found == -1) {
        osSyncPrintf("!!\n");
    }
    prize->unkA0[found] &= ~4;
    prize->unkA0[found] &= ~1;
    prize->unkA0[found] |= 8;
    dx = D_800EC598_minigame[0]->trans.x - hook->unk04.x;
    dz = D_800EC598_minigame[0]->trans.z - hook->unk04.z;
    y = prize->unk14[found];
    for (i = 0; i < 30; i++) {
        prize->unk00[found] += dx / 30.0f;
        angle = i * 180.0f / 30.0f;
        prize->unk8C[found] = sindf(angle) * 400.0f + y;
        if (angle > 90.0f && prize->unk8C[found] < D_800EC598_minigame[0]->trans.y + 300.0f) {
            prize->unk8C[found] = D_800EC598_minigame[0]->trans.y + 300.0f;
        }
        prize->unk28[found] += dz / 30.0f;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

/* The ripples (nine models). */
void func_80109520_dorrie_dip(void) {
    s32 attr = 0x69D;
    omObjData* obj;
    s32* work;
    s32 i;

    obj = omAddObj(0xFF, 9, 0, -1, func_801095FC_dorrie_dip);
    D_8010A24C_dorrie_dip = obj;
    work = obj->data = HuMemAllocTag(9 * sizeof(s32), 0x7918);
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5F000C, attr);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        work[i] = 0;
    }
    D_8010A250_dorrie_dip = 0;
}

void func_801095FC_dorrie_dip(omObjData* obj) {
    s32* work = obj->data;
    s32 i;

    for (i = 0; i < 9; i++) {
        if (work[i] & 1) {
            if (D_800CCF58_main[HmfModelData[obj->model[i]].unk02].unk02 <= HmfModelData[obj->model[i]].unk40) {
                func_8001C258_main(obj->model[i], 4, 4);
                work[i] &= ~1;
            }
        }
    }
}

void func_801096F0_dorrie_dip(void) {
    omAddPrcObj(func_80109738_dorrie_dip, 0x50, 0, 0);
}

/* Stop the ripples. */
void func_8010971C_dorrie_dip(void) {
    D_8010A250_dorrie_dip &= ~2;
}

/* Process: start a ripple at a random spot now and then, while D_8010A250 has 2. */
void func_80109738_dorrie_dip(void) {
    s32* work = D_8010A24C_dorrie_dip->data;
    s32 found;
    s32 i;
    s32 angle;
    s32 dist;
    f32 x;
    f32 z;

    D_8010A250_dorrie_dip |= 2;
    while (D_8010A250_dorrie_dip & 2) {
        if ((rand8() & 0xF) == 0) {
            found = -1;
            for (i = 0; i < 9; i++) {
                if (!(work[i] & 1)) {
                    found = i;
                    break;
                }
            }
            if (found != -1) {
                work[found] |= 1;
                angle = (rand8() * 2) % 360;
                dist = (rand8() * 2) % 500;
                x = dist * sindf(angle);
                z = dist * cosdf(angle);
                if (found == 0) {
                    omSetTra(D_8010A24C_dorrie_dip, x, 0.0f, z);
                } else {
                    Hu3DModelPosSet(D_8010A24C_dorrie_dip->model[found], x, 0.0f, z);
                }
                func_8001C258_main(D_8010A24C_dorrie_dip->model[found], 4, 0);
                func_8001C6A8_main(D_8010A24C_dorrie_dip->model[found], 0.0f);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

/* The CPU picks the Dorrie to hook: a prize by the odds table, or by difficulty the dud. */
void func_80109978_dorrie_dip(void) {
    s32 target;
    s32 sum;
    s32 j;
    s32 i;
    s32 r;

    r = (u8)(rand8() % 100);
    for (j = 0, sum = 0; j < 5; j++) {
        if (sum <= r && r < sum + D_800A11DC_main[j]) {
            break;
        }
        sum += D_800A11DC_main[j];
    }
    if (j == 5) {
        j = 4;
    }
    target = 0;
    for (i = 0; i < 6; i++) {
        if (D_8010A208_dorrie_dip[i] == j) {
            target = i;
        }
    }
    r = (u8)(rand8() % 100);
    switch (GwPlayer[D_8010A1FC_dorrie_dip].cpu_difficulty) {
        case 0:
            if (r < 20) {
                target = D_8010A200_dorrie_dip;
            }
            break;
        case 1:
            if (r < 15) {
                target = D_8010A200_dorrie_dip;
            }
            break;
        case 2:
            if (r < 10) {
                target = D_8010A200_dorrie_dip;
            }
            break;
        case 3:
            if (r < 5) {
                target = D_8010A200_dorrie_dip;
            }
            break;
    }
    D_8010A254_dorrie_dip.unk00 = 8;
    D_8010A254_dorrie_dip.unk04 = target;
    D_8010A254_dorrie_dip.unk08 = 0;
}

/* The wakes behind the Dorries. */
void func_80109B28_dorrie_dip(void) {
    s32 attr = 0x6BD;
    omObjData* obj;
    DrWake* work;
    s32 i;

    obj = omAddObj(0xFF, 6, 0, -1, func_80109C14_dorrie_dip);
    D_8010A260_dorrie_dip = obj;
    work = obj->data = HuMemAllocTag(sizeof(DrWake), 0x7918);
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5F000D, attr);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        work->unk60[i] = 0;
        work->unk48[i] = 1.0f;
    }
}

void func_80109C14_dorrie_dip(omObjData* obj) {
    DrWake* work = obj->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (i == 0) {
            omSetTra(obj, work->unk00[i], work->unk18[i], work->unk30[i]);
            omSetRot(obj, 0.0f, ring->unk18[i], 0.0f);
            omSetSca(obj, work->unk48[i], 1.0f, 1.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk18[i], work->unk30[i]);
            Hu3DModelRotSet(obj->model[i], 0.0f, ring->unk18[i], 0.0f);
            Hu3DModelScaleSet(obj->model[i], work->unk48[i], 1.0f, 1.0f);
        }
        if (work->unk60[i] & 1) {
            work->unk48[i] = (4.8f - ring->unk30[i]) / 4.8f;
            if (work->unk48[i] == 0.0f) {
                func_8001C258_main(obj->model[i], 4, 4);
                work->unk60[i] &= ~1;
            }
        }
        work->unk00[i] = sindf(ring->unk18[i]) * 450.0f;
        work->unk18[i] = D_8010A22C_dorrie_dip;
        work->unk30[i] = cosdf(ring->unk18[i]) * 450.0f;
    }
}

/* Show a Dorrie's wake. */
void func_80109E1C_dorrie_dip(s32 idx) {
    DrWake* work = D_8010A260_dorrie_dip->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;

    work->unk60[idx] |= 1;
    work->unk00[idx] = sindf(ring->unk18[idx]) * 450.0f;
    work->unk18[idx] = D_8010A22C_dorrie_dip;
    work->unk30[idx] = cosdf(ring->unk18[idx]) * 450.0f;
    func_8001C258_main(D_8010A260_dorrie_dip->model[idx], 4, 0);
    func_8001C814_main(D_8010A260_dorrie_dip->model[idx], 2, 2);
}

/* The CPU player: press A when its Dorrie passes under the hook, then B a few frames later. */
void func_80109F00_dorrie_dip(void) {
    func_800E1BA8_minigame_ObjData* work = D_800EC598_minigame[0]->data;
    DrRing* ring = D_8010A230_dorrie_dip->data;

    if (D_8010A254_dorrie_dip.unk08 == 0) {
        if (ring->unk18[D_8010A254_dorrie_dip.unk04] >= 175.0f && ring->unk18[D_8010A254_dorrie_dip.unk04] < 185.0f) {
            D_800CDA7C_main[work->unk57] |= 0x8000;
            D_800D5558_main[work->unk57] |= 0x8000;
            D_8010A254_dorrie_dip.unk08++;
        }
    }
    if (D_8010A254_dorrie_dip.unk08 != 0) {
        if (--D_8010A254_dorrie_dip.unk00 == 0) {
            D_800CDA7C_main[work->unk57] |= 0x2000;
            D_800D5558_main[work->unk57] |= 0x2000;
        }
    }
}
