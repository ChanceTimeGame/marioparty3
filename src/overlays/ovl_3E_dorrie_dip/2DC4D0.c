#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// dr A: Dorrie Dip

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
    /* 0x3C */ f32 unk3C[5];
    /* 0x50 */ f32 unk50[5];
    /* 0x64 */ f32 unk64[5];
    /* 0x78 */ f32 unk78[5];
    /* 0x8C */ f32 unk8C[5];
    /* 0xA0 */ s32 unkA0[5]; /* flags; 4: hooked */
    /* 0xB4 */ s32 unkB4[5]; /* the Dorrie carrying it */
} DrPrize; /* size 0xC8 */

/* omObjData::data of D_8010A234 */
typedef struct DrUnk234 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ s32 unk14; /* flags; 4: hooked */
    /* 0x18 */ char unk18[8];
} DrUnk234; /* size 0x20 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8004AD70_main(void);
void func_800557A0_main(void);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);

extern s32 D_800A178C_main[][6];

// minigame
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
void func_80107690_dorrie_dip(void);
void func_80107D58_dorrie_dip(void);
void func_80108148_dorrie_dip(void);
void func_801081A8_dorrie_dip(void);
void func_80108458_dorrie_dip(void);
void func_80108678_dorrie_dip(void);
void func_80108700_dorrie_dip(void);
void func_80108800_dorrie_dip(void);
void func_80108A74_dorrie_dip(s16 model, char* name, s16 frame, Vec* out);
void func_80108B98_dorrie_dip(void);
void func_80108EA0_dorrie_dip(s32 idx);
void func_801090C4_dorrie_dip(void);
void func_801092E0_dorrie_dip(void);
void func_80109520_dorrie_dip(void);
void func_801096F0_dorrie_dip(void);
void func_8010971C_dorrie_dip(void);
void func_80109978_dorrie_dip(void);
void func_80109B28_dorrie_dip(void);
void func_80109E1C_dorrie_dip(s32 idx);

/* .data */
extern D_80111B50_vine_with_me_Struct D_8010A040_dorrie_dip;
extern s8 D_8010A046_dorrie_dip; /* result message (D_8010A040.unk06) */
extern s32 D_8010A068_dorrie_dip; /* frame of the next ambient sound 1 */
extern s32 D_8010A06C_dorrie_dip; /* frame of the next ambient sound 2 */

/* .bss (ovl_3E_bss) */
extern s32 D_8010A1F4_dorrie_dip; /* camera */
extern u8 D_8010A1F8_dorrie_dip;
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
    DrUnk234* w234 = D_8010A234_dorrie_dip->data;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107360_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801074CC_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801074F8_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107690_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801079D4_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107D08_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107D58_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107EE0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108128_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108148_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108174_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801081A8_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801081D4_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108458_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A194_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108484_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108678_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801086A4_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108700_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010872C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108800_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010898C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108A74_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108B98_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108C6C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108EA0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801090C4_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801090F0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801092E0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010930C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109520_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801095FC_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801096F0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010971C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109738_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109978_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109B28_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109C14_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109E1C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109F00_dorrie_dip);
