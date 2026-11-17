#include "common.h"
// m1 lj1: Log Jam (two teams of two)
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

/* One player (D_8010E5B8_log_jam, 4 x 0x38). */
typedef struct LjPlayer {
    /* 0x00 */ s16 unk00; /* slot 0..3 */
    /* 0x02 */ s16 unk02; /* position in the team: 0 or 1 */
    /* 0x04 */ s16 unk04; /* team */
    /* 0x06 */ s16 unk06; /* pending result motion: 0 win, 1 lose */
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ char unk1E[0x1A];
} LjPlayer; // Size 0x38

/* One team (D_8010E5AC_log_jam, 2 x 0x48). */
typedef struct LjTeam {
    /* 0x00 */ omObjData* unk00; /* player objects */
    /* 0x04 */ omObjData* unk04;
    /* 0x08 */ LjPlayer* unk08;
    /* 0x0C */ LjPlayer* unk0C;
    /* 0x10 */ s16 unk10; /* team index */
    /* 0x12 */ s16 unk12; /* score */
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ Vec unk24;
    /* 0x30 */ Vec unk30;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} LjTeam; // Size 0x48


u8 func_8000B638_main(void);
void func_800E6F0C_minigame(s32);

void func_80105B9C_log_jam(omObjData* obj);
void func_80105C10_log_jam(omObjData* obj);
void func_801060C4_log_jam(omObjData* obj);
void func_801060E8_log_jam(omObjData* obj);
void func_80106190_log_jam(void);
void func_801065E8_log_jam(omObjData* obj);
void func_80106968_log_jam(omObjData* obj);
void func_80106FAC_log_jam(void);
void func_80108D50_log_jam(void);
s16 func_80108CE0_log_jam(s16 arg0);
void func_801091DC_log_jam(void);
void func_80109A00_log_jam(void);
void func_80109AD8_log_jam(void);
void func_80109B34_log_jam(void);
void func_8010A344_log_jam(void);
void func_8010A724_log_jam(void);
void func_8010ABA4_log_jam(void);
void func_8010B04C_log_jam(void);
void func_8010C55C_log_jam(omObjData* obj, void* data);
void* func_8010C588_log_jam(omObjData* obj);

extern Vec D_8010DE90_log_jam[]; /* player start positions (D_8010DE98 = [0].z) */
extern f32 D_8010DF20_log_jam[]; /* player start rotations */
extern s32 D_8010DF90_log_jam; /* exit wipe countdown; D_8010DF92 = its low half */
extern s32 D_8010DF94_log_jam[4]; /* player order */
extern s16 D_8010DFA4_log_jam[4][2][2]; /* fallback teams */
extern s16 D_8010DFC4_log_jam[4]; /* position in the team per slot */
extern s16 D_8010DFCC_log_jam[4]; /* player object marks */

extern omObjData* D_8010E590_log_jam;
extern s32 D_8010E594_log_jam;
extern s32 D_8010E598_log_jam;
extern s32 D_8010E59C_log_jam;
extern s32 D_8010E5A0_log_jam;
extern s32 D_8010E5A4_log_jam;
extern s32 D_8010E5A8_log_jam;
extern LjTeam* D_8010E5AC_log_jam;
extern omObjData* D_8010E5B0_log_jam[2]; /* team objects */
extern LjPlayer* D_8010E5B8_log_jam;
extern s16 D_8010E5BC_log_jam;
extern void* D_8010E5CC_log_jam;
extern D_80111B50_vine_with_me_Struct D_8010E640_log_jam;
// end m1 lj1

void func_801059A0_log_jam(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x10);
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
    D_8010E5A0_log_jam = 900;
    D_8010E59C_log_jam = 0;
    D_8010E598_log_jam = 0;
    D_8010E5A4_log_jam = -1;
    D_8010E5A8_log_jam = 0;
    D_8010E5BC_log_jam = -1;
    D_8010E5CC_log_jam = HuMemAllocTag(0x40, 31000);
    D_8010E590_log_jam = omAddObj(0x20, 0, 0, -1, func_80105B9C_log_jam);
    memset(&D_8010E640_log_jam, 0, 0x28);
    D_8010E640_log_jam.unk01 = 4;
    func_800E5EA0_minigame(&D_8010E640_log_jam);
}

void func_80105B9C_log_jam(omObjData* obj) {
    obj->func = func_80105C10_log_jam;
    func_80109B34_log_jam();
    func_8010A344_log_jam();
    func_8010A724_log_jam();
    func_8010ABA4_log_jam();
    func_80109A00_log_jam();
    func_80106190_log_jam();
    func_80108D50_log_jam();
    func_8010B04C_log_jam();
    if (_CheckFlag(0xA) != 0) {
        D_8010E594_log_jam = 1;
    }
}

void func_80105C10_log_jam(omObjData* obj) {
    LjTeam* t0;
    LjTeam* t1;

    switch (D_8010E5A4_log_jam) {
    case -1:
        if (D_8010E59C_log_jam >= 2) {
            WipeCreateIn(0xFF, 0x10);
            D_8010E5A4_log_jam = 0;
            D_8010E59C_log_jam = 0;
        }
        break;
    case 0:
        if (WipeStatGet() == 0) {
            GMesCreate(5);
            HuAudFXPlay(0xE);
            D_8010E5A4_log_jam++;
            D_8010E59C_log_jam = 0;
        }
        break;
    case 1:
        if (D_8010E59C_log_jam == 30) {
            HuAudSeqPlay(0x2E);
        }
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010E5A0_log_jam + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010E5A4_log_jam++;
        }
        break;
    case 2:
        func_8003F578_main((D_8010E5A0_log_jam-- + 28) / 30);
        if (D_8010E5A0_log_jam <= 0) {
            func_8003F5C0_main();
            GMesCreate(0x10);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            D_8010E5A0_log_jam = 0;
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 3:
        if (func_80108CE0_log_jam(0xE) != 0 && GMesStatGet() == 0) {
            func_800E6F0C_minigame(4);
            func_801091DC_log_jam();
            func_80106FAC_log_jam();
            func_80109AD8_log_jam();
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 4:
        if (func_80108CE0_log_jam(0x11) != 0) {
            t0 = func_8010C588_log_jam(D_8010E5B0_log_jam[0]);
            t1 = func_8010C588_log_jam(D_8010E5B0_log_jam[1]);
            if (t0->unk12 > t1->unk12) {
                GMesCreate(0x1E, t0->unk08->unk1C, t0->unk0C->unk1C);
                GwPlayer[t0->unk08->unk18].bonusCoin += 10;
                GwPlayer[t0->unk0C->unk18].bonusCoin += 10;
                t0->unk08->unk06 = t0->unk0C->unk06 = 0;
                t1->unk08->unk06 = t1->unk0C->unk06 = 1;
                HuAudSeqPlay(0x66);
                D_8010E5A8_log_jam = 0x8C;
            } else if (t0->unk12 < t1->unk12) {
                GMesCreate(0x1E, t1->unk08->unk1C, t1->unk0C->unk1C);
                GwPlayer[t1->unk08->unk18].bonusCoin += 10;
                GwPlayer[t1->unk0C->unk18].bonusCoin += 10;
                t0->unk08->unk06 = t0->unk0C->unk06 = 1;
                t1->unk08->unk06 = t1->unk0C->unk06 = 0;
                HuAudSeqPlay(0x66);
                D_8010E5A8_log_jam = 0x8C;
            } else {
                GMesCreate(0x20);
                t0->unk08->unk06 = t0->unk0C->unk06 = 1;
                t1->unk08->unk06 = t1->unk0C->unk06 = 1;
                HuAudSeqPlay(0x6C);
                D_8010E5A8_log_jam = 0x90;
            }
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 6:
        if (D_8010E59C_log_jam >= 16) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_801060C4_log_jam;
        }
        break;
    }
    func_801060E8_log_jam(obj);
    D_8010E598_log_jam++;
    D_8010E59C_log_jam++;
}

void func_801060C4_log_jam(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801060E8_log_jam(omObjData* obj) {
    if (D_8010DF90_log_jam != 0) {
        if (D_8010DF90_log_jam == 1) {
            obj->func = func_801060C4_log_jam;
        }
        D_8010DF90_log_jam--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010DF90_log_jam = 0x10;
        WipeCreateOut(0, (s16)D_8010DF90_log_jam);
        HuAudSeqFadeOut((s16)D_8010DF90_log_jam);
        func_8004AB0C_main((s16)D_8010DF90_log_jam);
    }
}

#ifdef NON_MATCHING
/* Differs: the group switch keeps one register copy fewer (retail moves the group into v1). */
void func_80106190_log_jam(void) {
    s32 grp[2][2];
    LjTeam* team;
    LjPlayer* pl;
    omObjData* o;
    s32 bad;
    s32 n0;
    s32 n1;
    s32 n2;
    s32 n3;
    s32 i;
    s32 j;
    s16 (*tbl)[2];
    s32 g;

    team = D_8010E5AC_log_jam = HuMemAllocTag(sizeof(LjTeam) * 2, 31000);
    memset(team, 0, sizeof(LjTeam) * 2);
    D_8010E5B8_log_jam = HuMemAllocTag(sizeof(LjPlayer) * 4, 31000);
    memset(D_8010E5B8_log_jam, 0, sizeof(LjPlayer) * 4);
    bad = 0;
    n3 = 0;
    n2 = 0;
    n1 = 0;
    n0 = 0;
    for (i = 0; i < 4; i++) {
        switch (g = GwPlayer[D_8010DF94_log_jam[i]].group) {
        case 0:
            if (n0 > 0) {
                bad = 1;
            } else {
                grp[0][1] = D_8010DF94_log_jam[i];
                n0++;
            }
            break;
        case 1:
            if (n1 > 0) {
                bad = 1;
            } else {
                grp[0][0] = D_8010DF94_log_jam[i];
                n1++;
            }
            break;
        case 2:
            if (n2 > 0) {
                bad = 1;
            } else {
                grp[1][0] = D_8010DF94_log_jam[i];
                n2++;
            }
            break;
        case 3:
            if (n3 > 0) {
                bad = 1;
            } else {
                grp[1][1] = D_8010DF94_log_jam[i];
                n3++;
            }
            break;
        default:
            bad = 1;
            break;
        }
        if (bad != 0) {
            break;
        }
    }
    if (bad != 0) {
        tbl = D_8010DFA4_log_jam[rand8() & 3];
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                grp[i][j] = tbl[i][j];
            }
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        team->unk10 = i;
        team->unk12 = 0;
        team->unk14 = 0;
        team->unk16 = -1;
        team->unk18 = -1;
        team->unk1A = 0;
        team->unk1C = -1;
        team->unk1E = 0;
        team->unk20 = 0;
        team->unk24.x = team->unk24.y = team->unk24.z = 0.0f;
        team->unk30.x = team->unk30.y = team->unk30.z = 0.0f;
        team->unk3C = 0.0f;
        team->unk40 = team->unk44 = 0.0f;
        D_8010E5B0_log_jam[i] = omAddObj(i + 0x10, 0, 0, -1, func_801065E8_log_jam);
        func_8010C55C_log_jam(D_8010E5B0_log_jam[i], team);
        for (j = 0; j < 2; j++) {
            pl = &D_8010E5B8_log_jam[i * 2 + j];
            pl->unk00 = i * 2 + j;
            pl->unk04 = i;
            pl->unk02 = D_8010DFC4_log_jam[pl->unk00];
            pl->unk18 = grp[i][j];
            o = D_800EC598_minigame[D_800EC280_minigame] = omAddObj(D_8010DFCC_log_jam[pl->unk00], 8, 11, -1, func_80106968_log_jam);
            D_800EC280_minigame++;
            o->trans.x = D_8010DE90_log_jam[pl->unk00].x;
            o->trans.z = D_8010DE90_log_jam[pl->unk00].z;
            o->rot.y = D_8010DF20_log_jam[pl->unk00];
            func_8010C55C_log_jam(o, pl);
            if (pl->unk02 == 0) {
                team->unk00 = o;
                team->unk08 = pl;
            } else {
                team->unk04 = o;
                team->unk0C = pl;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106190_log_jam);
#endif


INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E1F0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801065E8_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E218_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106968_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106F48_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106FAC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107080_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107C84_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108840_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108A80_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108CE0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108D1C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108D50_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108E54_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109044_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010910C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109140_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109190_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801091DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010925C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109350_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2C0_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2CC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801094E4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109A00_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109A7C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109AD8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109B34_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109B8C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A0B0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A300_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A344_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A4C0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A6FC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A724_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A880_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A9D4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010ABA4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010AD04_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010AE58_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B04C_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E370_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B17C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B86C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010BCA8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010BE94_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C084_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C1D8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C2DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C49C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C4B4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C514_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C55C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C588_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C5DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C6A4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C714_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C7D0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C7F8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C8B0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C8E0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010CAC0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010CB64_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010D74C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010D950_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010DA84_log_jam);
