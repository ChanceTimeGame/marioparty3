#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

// m7 bw: Bowser Toss (1 vs 1 x 2: spin and throw Bowser; two players on split screens)

/* A player's work (D_8010FB74_bowser_toss, 2 x 0x5C; packed into obj->work). */
typedef struct BtPlayer {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02; /* result motion: 0 win, 1 lose, -1 none */
    /* 0x04 */ f32 unk04; /* distance */
    /* 0x08 */ s32 unk08; /* frame counter */
    /* 0x0C */ s16 unk0C; /* state */
    /* 0x0E */ u16 unk0E; /* press counter */
    /* 0x10 */ s16 unk10; /* spin sound, -1 none */
    /* 0x12 */ char unk12[2];
    /* 0x14 */ s32 unk14; /* win voice file */
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A; /* controller port */
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ s16 unk1E; /* CPU */
    /* 0x20 */ s16 unk20; /* CPU difficulty */
    /* 0x22 */ char unk22[2];
    /* 0x24 */ f32 unk24; /* minimum angle */
    /* 0x28 */ f32 unk28; /* maximum angle */
    /* 0x2C */ f32 unk2C; /* angle range */
    /* 0x30 */ s16 unk30; /* motion blend frames */
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34; /* vertical speed */
    /* 0x38 */ f32 unk38; /* horizontal speed */
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ char unk3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ f32 unk44; /* spin speed */
    /* 0x48 */ f32 unk48; /* target angle */
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54; /* CPU: stick */
    /* 0x58 */ f32 unk58; /* CPU: release speed */
} BtPlayer; // Size 0x5C

typedef f32 Matrix4f[4][4];
/* Matrix bake record (src/14EA0.c's unk1EA70StructC). */
typedef struct unk1EA70StructC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16* unk_04;
    /* 0x08 */ Matrix4f* unk_08;
} unk1EA70StructC; // sizeof 0xC

/* A thrown Bowser (D_8010FB8C_bowser_toss, 2 x 0x64). */
typedef struct BtBowser {
    /* 0x00 */ omObjData* unk00; /* thrower */
    /* 0x04 */ s16 unk04; /* models */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A; /* state */
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28; /* spin speed, 0..1 */
    /* 0x2C */ f32 unk2C; /* angle, 0..1 */
    /* 0x30 */ Vec unk30; /* position */
    /* 0x3C */ char unk3C[0x20];
    /* 0x5C */ unk1EA70StructC* unk5C;
    /* 0x60 */ void* unk60;
} BtBowser; // Size 0x64

typedef struct BtBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} BtBytes;

typedef union BtPack {
    void* p;
    BtBytes b;
} BtPack;

typedef struct BtVoice {
    s16 unk0;
    s16 unk2;
} BtVoice;

u16 GWMgRecordGet(s16 arg0);
s32 func_8000B710_main(s32 arg0);
void func_800E6F0C_minigame(s32);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char* arg2);
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y);

void func_80105C80_bowser_toss(omObjData* obj);
void func_80105CEC_bowser_toss(omObjData* obj);
void func_8010649C_bowser_toss(omObjData* obj);
void func_801064C0_bowser_toss(omObjData* obj);
void func_80106568_bowser_toss(void);
void func_801067B0_bowser_toss(omObjData* obj);
void func_80106BC4_bowser_toss(omObjData* obj);
void func_80107E84_bowser_toss(omObjData* obj);
f32 func_801080D0_bowser_toss(f32 arg0, f32 arg1, f32 arg2);
s32 func_8010840C_bowser_toss(void);
s32 func_80108444_bowser_toss(void);
void func_8010847C_bowser_toss(omObjData* obj, s16 a, s16 b);
void func_801084DC_bowser_toss(void);
void func_8010858C_bowser_toss(s16 idx);
BtBowser* func_80108800_bowser_toss(s16 idx);
void func_8010882C_bowser_toss(omObjData* obj);
s32 func_80109F20_bowser_toss(void);
void func_8010A028_bowser_toss(void);
void func_8010A2D4_bowser_toss(Vec* pos, Vec* vel, Vec* scale, f32 speed, s32 player);
void func_8010A4A8_bowser_toss(void);
void func_8010AD98_bowser_toss(void);
void func_8010B41C_bowser_toss(void);
void func_8010C1A0_bowser_toss(s16 idx, s32 value);
s32 func_8010C23C_bowser_toss(void);
void func_8010C274_bowser_toss(void);
s32 func_8010C2A4_bowser_toss(void);
void func_8010C2DC_bowser_toss(void);
void func_8010D250_bowser_toss(s16 idx, f32 x, f32 y, f32 a, f32 b, f32 c, f32 d, f32 zoom, s32 frames);
f32 func_8010D6E0_bowser_toss(f32 target, f32 cur, f32 step);
void func_8010D960_bowser_toss(omObjData* obj, u32 value);
void* func_8010D98C_bowser_toss(omObjData* obj);
unk1EA70StructC* func_8010D9E0_bowser_toss(s16 model, s16 arg1, const char* part, s16 arg3, u16 arg4);
void func_8010DDC4_bowser_toss(unk1EA70StructC* arg0);

extern s16 D_8010F530_bowser_toss[];
extern s16 D_8010F53C_bowser_toss[];
extern s32 D_8010F154_bowser_toss[];
extern s32 D_8010F174_bowser_toss[];
extern s32 D_8010F194_bowser_toss;
extern Vec D_8010F198_bowser_toss[];
extern s32 D_8010F1B0_bowser_toss[];
extern s32 D_8010F1C0_bowser_toss[];
extern f32 D_8010F1E0_bowser_toss[];
extern f32 D_8010F200_bowser_toss[];
extern BtVoice D_8010F220_bowser_toss[];
extern BtVoice D_8010F228_bowser_toss[];
extern f32 D_8010F230_bowser_toss[];
extern f32 D_8010F240_bowser_toss[];
extern f32 D_8010F250_bowser_toss[];
extern f32 D_8010F260_bowser_toss[];
extern f32 D_8010F270_bowser_toss[2];

extern omObjData* D_8010FB50_bowser_toss;
extern s32 D_8010FB54_bowser_toss;
extern s32 D_8010FB58_bowser_toss;
extern s32 D_8010FB5C_bowser_toss;
extern s32 D_8010FB60_bowser_toss;
extern u32 D_8010FB64_bowser_toss;
extern s32 D_8010FB68_bowser_toss;
extern s32 D_8010FB6C_bowser_toss;
extern s16 D_8010FB70_bowser_toss;
extern s16 D_8010FB72_bowser_toss;
extern BtPlayer* D_8010FB74_bowser_toss;
extern s16 D_8010FB78_bowser_toss;
extern s32 D_8010FB7C_bowser_toss;
extern s32 D_8010FB80_bowser_toss;
extern s32 D_8010FB84_bowser_toss;
extern omObjData* D_8010FB88_bowser_toss;
extern BtBowser* D_8010FB8C_bowser_toss;
extern void* D_8010FB98_bowser_toss;
extern D_80111B50_vine_with_me_Struct D_8010FBB8_bowser_toss;

void func_801059A0_bowser_toss(void) {
    omObjData* obj;
    s32 i;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x10);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 2;
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 121.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    for (i = 0; i < 2; i++) {
        Hu3DCamSetPerspective(i, 45.0f, 80.0f, 4000.0f);
    }
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010FB60_bowser_toss = 300;
    D_8010FB5C_bowser_toss = 0;
    D_8010FB58_bowser_toss = 0;
    D_8010FB64_bowser_toss = 0;
    D_8010FB68_bowser_toss = 0;
    D_8010FB6C_bowser_toss = 0;
    D_8010FB78_bowser_toss = -1;
    D_8010FB7C_bowser_toss = 0;
    D_8010FB70_bowser_toss = -1;
    D_8010FB84_bowser_toss = -1;
    D_8010FB80_bowser_toss = GWMgRecordGet(4);
    D_8010FB72_bowser_toss = 0;
    D_8010FB50_bowser_toss = omAddObj(0x40, 0, 0, -1, func_80105C80_bowser_toss);
    memset(&D_8010FBB8_bowser_toss, 0, 0x28);
    D_8010FBB8_bowser_toss.unk01 = 4;
    func_800E5EA0_minigame(&D_8010FBB8_bowser_toss);
    D_8010FB98_bowser_toss = HuMemAllocTag(0x20, 31000);
    memset(D_8010FB98_bowser_toss, 0, 0x20);
    func_80045010_main(D_8010F530_bowser_toss, 1);
    func_80045010_main(D_8010F53C_bowser_toss, 1);
}

void func_80105C80_bowser_toss(omObjData* obj) {
    obj->func = func_80105CEC_bowser_toss;
    func_8010AD98_bowser_toss();
    func_8010B41C_bowser_toss();
    func_8010A028_bowser_toss();
    func_8010A4A8_bowser_toss();
    func_801084DC_bowser_toss();
    func_80106568_bowser_toss();
    func_8010C2DC_bowser_toss();
    if (_CheckFlag(0xA) != 0) {
        D_8010FB54_bowser_toss = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F530_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F53C_bowser_toss);

void func_80105CEC_bowser_toss(omObjData* obj) {
    BtPlayer* p0;
    BtPlayer* p1;
    omObjData* wobj;
    BtBowser* bw;
    s32 s0;
    s32 s1;
    f32 x;
    f32 y;
    f32 z;

    switch (D_8010FB64_bowser_toss) {
    case 0:
        if (D_8010FB5C_bowser_toss == 2) {
            WipeCreateIn(0xFF, 0x10);
        }
        if (D_8010FB68_bowser_toss > 0) {
            D_8010FB68_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 1:
        GMesCreate(6);
        HuAudFXPlay(0xE);
        HuAudSeqPlay(0x30);
        D_8010FB68_bowser_toss = 0;
        D_8010FB64_bowser_toss++;
        break;
    case 2:
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010FB60_bowser_toss + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010FB64_bowser_toss++;
        }
        break;
    case 3:
        func_8003F578_main((D_8010FB60_bowser_toss-- + 28) / 30);
        if (D_8010FB60_bowser_toss <= 0) {
            p0 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
            p1 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
            p0->unk0C = 3;
            p1->unk0C = 3;
            func_8003F5C0_main();
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 4:
        if ((s16)func_80109F20_bowser_toss() != 0 && (s16)func_8010840C_bowser_toss() != 0) {
            GMesCreate(0x11);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            func_8010847C_bowser_toss(D_800EC598_minigame[0], 0, 0xA);
            func_8010847C_bowser_toss(D_800EC598_minigame[1], 0, 0xA);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 6:
        if (D_8010FB5C_bowser_toss >= 15) {
            p0 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
            p1 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
            s0 = p0->unk04;
            s1 = p1->unk04;
            if (p0->unk04 == 0.0f && p1->unk04 == 0.0f) {
                D_8010FB78_bowser_toss = -1;
                D_8010FB7C_bowser_toss = -1;
                p0->unk02 = p1->unk02 = 1;
            } else if (s0 == s1) {
                if (rand8() & 1) {
                    s0 = s1 + 1;
                    p0->unk04 += 1.0f;
                } else {
                    s1++;
                    p1->unk04 += 1.0f;
                }
            }
            if (s0 > s1) {
                D_8010FB78_bowser_toss = p0->unk00;
                GwPlayer[p0->unk18].bonusCoin += 10;
                p0->unk02 = 0;
                p1->unk02 = 1;
                D_8010FB7C_bowser_toss = s0;
            } else if (s0 < s1) {
                D_8010FB78_bowser_toss = p1->unk00;
                GwPlayer[p1->unk18].bonusCoin += 10;
                p0->unk02 = 1;
                p1->unk02 = 0;
                D_8010FB7C_bowser_toss = s1;
            }
            func_8010C1A0_bowser_toss(p0->unk00, s0);
            func_8010C1A0_bowser_toss(p1->unk00, s1);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 7:
        if ((s16)func_8010C23C_bowser_toss() != 0) {
            if (D_8010FB70_bowser_toss != -1) {
                HuAudFXPlay(0x4AC);
                D_8010FB70_bowser_toss = -1;
            }
            func_8010C274_bowser_toss();
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 8:
        if ((s16)func_80108444_bowser_toss() != 0 && (s16)func_8010C2A4_bowser_toss() != 0) {
            if (D_8010FB78_bowser_toss == -1) {
                GMesCreate(0x20);
                HuAudSeqPlay(0x6C);
                D_8010FB68_bowser_toss = 0x90;
                func_800E6F0C_minigame(4);
                D_8010FB64_bowser_toss = 11;
            } else {
                if (D_8010FB78_bowser_toss != 0) {
                    D_8010FB78_bowser_toss = 1;
                }
                if (D_8010FB80_bowser_toss < D_8010FB7C_bowser_toss) {
                    D_8010FB80_bowser_toss = D_8010FB7C_bowser_toss;
                    func_8010C1A0_bowser_toss(2, D_8010FB7C_bowser_toss);
                    GWMgRecordSet(4, (u16)D_8010FB80_bowser_toss);
                    GMesCreate(0x1B);
                    D_8010FB72_bowser_toss = 1;
                    D_8010FB68_bowser_toss = 99;
                    D_8010FB64_bowser_toss = 9;
                } else {
                    HuAudSeqPlay(0x67);
                    D_8010FB68_bowser_toss = 0x8C;
                    D_8010FB64_bowser_toss = 10;
                }
                wobj = D_800EC598_minigame[D_8010FB78_bowser_toss];
                bw = &D_8010FB8C_bowser_toss[D_8010FB78_bowser_toss];
                func_8010D98C_bowser_toss(wobj);
                x = wobj->trans.x * 0.5f + bw->unk30.x * 0.5f;
                if (wobj->trans.x != 0.0f) {
                    y = wobj->trans.y * 0.5f + 100.0;
                } else {
                    y = wobj->trans.y * 0.5f + 150.0;
                }
                z = CZoom * 0.5f;
                if (D_8010FB78_bowser_toss == 1) {
                    y -= 15.000000596046448;
                }
                func_8010D250_bowser_toss(D_8010FB78_bowser_toss, x, y, 65535.0f, 65535.0f, 65535.0f, 65535.0f,
                                          z, 30);
                func_800E6F0C_minigame(4);
            }
            D_8010FB5C_bowser_toss = 0;
        }
        break;
    case 9:
        if (D_8010FB5C_bowser_toss >= 75.0f) {
            D_8010FB64_bowser_toss = 10;
            D_8010FB5C_bowser_toss = 0;
        }
        break;
    case 10:
        GMesCreate(0x16, ((BtPlayer*)func_8010D98C_bowser_toss(D_800EC598_minigame[D_8010FB78_bowser_toss]))->unk1C);
        if (D_8010FB72_bowser_toss != 0) {
            HuAudSeqPlay(0x6A);
        }
        D_8010FB5C_bowser_toss = 0;
        D_8010FB64_bowser_toss++;
        break;
    case 11:
        if (GMesStatGet() == 0) {
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 12:
        if (D_8010FB5C_bowser_toss >= 15) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_8010649C_bowser_toss;
        }
        break;
    }
    func_801064C0_bowser_toss(obj);
    D_8010FB58_bowser_toss++;
    D_8010FB5C_bowser_toss++;
}

void func_8010649C_bowser_toss(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801064C0_bowser_toss(omObjData* obj) {
    if (D_8010F194_bowser_toss != 0) {
        if (D_8010F194_bowser_toss == 1) {
            obj->func = func_8010649C_bowser_toss;
        }
        D_8010F194_bowser_toss--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010F194_bowser_toss = 0x10;
        WipeCreateOut(0, (s16)D_8010F194_bowser_toss);
        HuAudSeqFadeOut((s16)D_8010F194_bowser_toss);
        func_8004AB0C_main((s16)D_8010F194_bowser_toss);
    }
}

void func_80106568_bowser_toss(void) {
    s32 picked[2] = { -1, -1 };
    BtPlayer* p;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 min;

    p = D_8010FB74_bowser_toss = HuMemAllocTag(sizeof(BtPlayer) * 2, 31000);
    memset(p, 0, sizeof(BtPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, min = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (picked[k] == D_8010F1B0_bowser_toss[j]) {
                    found = 1;
                }
            }
            if (!found) {
                if (GwPlayer[D_8010F1B0_bowser_toss[j]].group < min) {
                    min = GwPlayer[D_8010F1B0_bowser_toss[j]].group;
                    D_8010FB74_bowser_toss[i].unk18 = D_8010F1B0_bowser_toss[j];
                }
            }
        }
        picked[i] = D_8010FB74_bowser_toss[i].unk18;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, p++) {
        p->unk00 = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(i + 0x10, 11, 60, -1, func_801067B0_bowser_toss);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010F198_bowser_toss[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = D_8010F198_bowser_toss[i].y;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010F198_bowser_toss[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->rot.y = 90.0f;
        func_8010D960_bowser_toss(D_800EC598_minigame[D_800EC280_minigame], (u32)p);
        D_800EC280_minigame++;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801067B0_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F5A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106BC4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80107E84_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801080D0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010840C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80108444_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010847C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801084DC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010858C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80108800_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010882C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109DB8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109E4C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109F20_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109F68_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A028_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A17C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A2D4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A4A8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A500_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A908_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AD54_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AD98_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AF38_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B41C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B7AC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C1A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C23C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C274_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C2A4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C2DC_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F998_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C570_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010CDB8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D080_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D250_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D43C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D5DC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D6E0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D8A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D8B8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D918_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D960_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D98C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D9E0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DB9C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DDC4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DDFC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010EA0C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010EC10_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010ED44_bowser_toss);
