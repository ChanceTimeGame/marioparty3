#include "common.h"
// m1 sy1: Slot Synch (two teams of two; each team stops the reels of one slot machine)
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"

/* One player (D_8010DF60_slot_synch, 4 x 0x30). Log Jam's player block has the same shape. */
typedef struct SsPlayer {
    /* 0x00 */ s16 unk00; /* slot 0..3 (also the reel index) */
    /* 0x02 */ s16 unk02; /* team */
    /* 0x04 */ s16 unk04; /* pending result motion: 0 win, 1 lose, -1 none */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u16 unk0A; /* frame counter */
    /* 0x0C */ f32 unk0C; /* position */
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u32 unk18; /* win message (func_80045F1C_main) */
    /* 0x1C */ s16 unk1C; /* GwPlayer index */
    /* 0x1E */ s16 unk1E; /* controller port */
    /* 0x20 */ s16 unk20; /* character */
    /* 0x22 */ s16 unk22; /* CPU */
    /* 0x24 */ s16 unk24; /* CPU difficulty */
    /* 0x26 */ s16 unk26; /* CPU: last reel symbol seen */
    /* 0x28 */ s16 unk28; /* CPU: 1 = stop on a miss */
    /* 0x2A */ s16 unk2A; /* CPU: frames to wait */
    /* 0x2C */ s16 unk2C; /* CPU: target symbol, -1 none */
    /* 0x2E */ char unk2E[2];
} SsPlayer; // Size 0x30

/* One team (D_8010DF5C_slot_synch, 2 x 0x20). */
typedef struct SsTeam {
    /* 0x00 */ omObjData* unk00; /* player objects */
    /* 0x04 */ omObjData* unk04;
    /* 0x08 */ SsPlayer* unk08;
    /* 0x0C */ SsPlayer* unk0C;
    /* 0x10 */ s16 unk10; /* team index */
    /* 0x12 */ s16 unk12; /* state */
    /* 0x14 */ s16 unk14; /* state timer */
    /* 0x16 */ s16 unk16; /* score */
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A; /* result symbol, 4 = no match */
    /* 0x1C */ s16 unk1C; /* reels running */
    /* 0x1E */ s16 unk1E; /* CPU: symbol the team aims at */
} SsTeam; // Size 0x20

void func_80105B98_slot_synch(omObjData* obj);
void func_80105C08_slot_synch(omObjData* obj);
void func_80106080_slot_synch(omObjData* obj);
void func_801060A4_slot_synch(omObjData* obj);
void func_8010614C_slot_synch(void);
void func_80106560_slot_synch(omObjData* obj);
void func_80106878_slot_synch(omObjData* obj);
void func_80106E8C_slot_synch(omObjData* obj);
void func_80107108_slot_synch(omObjData* obj);
void func_801075D4_slot_synch(void);
void func_80109508_slot_synch(void);
s16 func_80106CF0_slot_synch(s16 team);
void func_8010A1D0_slot_synch(void);
void func_8010A39C_slot_synch(void);
void func_8010A480_slot_synch(s16 team, u8 chr0, u8 chr1, s32 arg3);
void func_8010AAB8_slot_synch(void);
void func_8010AF38_slot_synch(void);
void func_8010C3FC_slot_synch(omObjData* obj, void* data);
void* func_8010C428_slot_synch(omObjData* obj);

void func_8000B5F0_main(u8);
u8 func_8000B638_main(void);
void func_8004AD70_main(void);
void func_800E6F0C_minigame(s32);
void func_800E18D8_minigame(void);
void func_800E19F0_minigame(s8);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);

extern s32 D_800A178C_main[][6];

extern Vec D_8010D7F0_slot_synch[4];
extern s32 D_8010D8B0_slot_synch;
extern s32 D_8010D8B4_slot_synch[4];
extern s16 D_8010D8C4_slot_synch[4][2][2];
extern s16 D_8010D8E4_slot_synch[4];
extern s32 D_8010D8EC_slot_synch[8];
extern s32 D_8010D90C_slot_synch[4];
extern omObjData* D_8010DF40_slot_synch;
extern s32 D_8010DF44_slot_synch;
extern s32 D_8010DF48_slot_synch;
extern s32 D_8010DF4C_slot_synch;
extern s32 D_8010DF50_slot_synch;
extern s32 D_8010DF54_slot_synch;
extern s32 D_8010DF58_slot_synch;
extern SsTeam* D_8010DF5C_slot_synch;
extern SsPlayer* D_8010DF60_slot_synch;
extern s16 D_8010DF64_slot_synch;
extern void* D_8010DF8C_slot_synch;
extern D_80111B50_vine_with_me_Struct D_8010DFF8_slot_synch;
// end m1 sy1

void func_801059A0_slot_synch(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x40);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010DF50_slot_synch = 900;
    D_8010DF4C_slot_synch = 0;
    D_8010DF48_slot_synch = 0;
    D_8010DF54_slot_synch = 0;
    D_8010DF58_slot_synch = 0;
    D_8010DF64_slot_synch = -1;
    D_8010DF8C_slot_synch = HuMemAllocTag(0x40, 31000);
    D_8010DF40_slot_synch = omAddObj(0x20, 0, 0, -1, func_80105B98_slot_synch);
    memset(&D_8010DFF8_slot_synch, 0, 0x28);
    D_8010DFF8_slot_synch.unk01 = 4;
    func_800E5EA0_minigame(&D_8010DFF8_slot_synch);
}

void func_80105B98_slot_synch(omObjData* obj) {
    obj->func = func_80105C08_slot_synch;
    func_8010A39C_slot_synch();
    func_80109508_slot_synch();
    func_801075D4_slot_synch();
    func_8010AAB8_slot_synch();
    func_8010614C_slot_synch();
    func_8010AF38_slot_synch();
    if (_CheckFlag(0xA) != 0) {
        D_8010DF44_slot_synch = 1;
    }
    WipeCreateIn(0xFF, 0x10);
}

void func_80105C08_slot_synch(omObjData* obj) {
    SsTeam* t0 = D_8010DF5C_slot_synch;
    SsTeam* t1 = t0 + 1;

    switch (D_8010DF54_slot_synch) {
    case 0:
        if (WipeStatGet() == 0) {
            GMesCreate(5);
            HuAudFXPlay(0xE);
            D_8010DF54_slot_synch++;
            D_8010DF4C_slot_synch = 0;
        }
        break;
    case 1:
        if (D_8010DF4C_slot_synch == 30) {
            HuAudSeqPlay(0x2E);
        }
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010DF50_slot_synch + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010DF54_slot_synch++;
        }
        break;
    case 2:
        func_8003F578_main((D_8010DF50_slot_synch-- + 28) / 30);
        if (D_8010DF50_slot_synch <= 0) {
            func_8004AD70_main();
            func_8003F5C0_main();
            GMesCreate(0x10);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            D_8010DF50_slot_synch = 0;
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 3:
        if (GMesStatGet() == 0 && func_80106CF0_slot_synch(0) == 0 && func_80106CF0_slot_synch(1) == 0) {
            func_800E6F0C_minigame(4);
            func_8010A1D0_slot_synch();
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 4:
        if (D_8010DF4C_slot_synch >= 15) {
            if (t0->unk16 > t1->unk16) {
                GMesCreate(0x1E, t0->unk08->unk20, t0->unk0C->unk20);
                GwPlayer[t0->unk08->unk1C].bonusCoin += 10;
                GwPlayer[t0->unk0C->unk1C].bonusCoin += 10;
                t0->unk08->unk04 = t0->unk0C->unk04 = 0;
                t1->unk08->unk04 = t1->unk0C->unk04 = 1;
                HuAudSeqPlay(0x66);
                D_8010DF58_slot_synch = 0x8C;
            } else if (t0->unk16 < t1->unk16) {
                GMesCreate(0x1E, t1->unk08->unk20, t1->unk0C->unk20);
                GwPlayer[t1->unk08->unk1C].bonusCoin += 10;
                GwPlayer[t1->unk0C->unk1C].bonusCoin += 10;
                t0->unk08->unk04 = t0->unk0C->unk04 = 1;
                t1->unk08->unk04 = t1->unk0C->unk04 = 0;
                HuAudSeqPlay(0x66);
                D_8010DF58_slot_synch = 0x8C;
            } else {
                GMesCreate(0x20);
                t0->unk08->unk04 = t0->unk0C->unk04 = 1;
                t1->unk08->unk04 = t1->unk0C->unk04 = 1;
                HuAudSeqPlay(0x6C);
                D_8010DF58_slot_synch = 0x90;
            }
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 6:
        if (D_8010DF4C_slot_synch >= 15) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_80106080_slot_synch;
        }
        break;
    }
    func_801060A4_slot_synch(obj);
    D_8010DF48_slot_synch++;
    D_8010DF4C_slot_synch++;
}

void func_80106080_slot_synch(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801060A4_slot_synch(omObjData* obj) {
    if (D_8010D8B0_slot_synch != 0) {
        if (D_8010D8B0_slot_synch == 1) {
            obj->func = func_80106080_slot_synch;
        }
        D_8010D8B0_slot_synch--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010D8B0_slot_synch = 0x10;
        WipeCreateOut(0, (s16)D_8010D8B0_slot_synch);
        HuAudSeqFadeOut((s16)D_8010D8B0_slot_synch);
        func_8004AB0C_main((s16)D_8010D8B0_slot_synch);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010614C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106560_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106878_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106CCC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106CF0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106D0C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106E8C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107108_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801075D4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107794_slot_synch);

void func_80107A80_slot_synch(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107A88_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107B00_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107BAC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107D54_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010800C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108238_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108428_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108848_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801089F8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108A7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108AA8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108B74_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108C88_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108CD0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108D14_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108D3C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801091D8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801092B8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801094E0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109508_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC78_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109754_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109FA4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A178_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A1D0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A2C4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A308_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A39C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A480_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A7D0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AA9C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AAB8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AC14_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AD68_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AF38_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DD28_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B064_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B754_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BB90_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BD7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BF6C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C0C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C1C4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C384_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C39C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C3FC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C428_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C47C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C4C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D0A8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D2AC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D3E0_slot_synch);
