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
    /* 0x02 */ s16 unk02; /* role in the team: 0 or 1 (1 carries the hook) */
    /* 0x04 */ s16 unk04; /* team */
    /* 0x06 */ s16 unk06; /* pending result motion: 0 win, 1 lose, -1 none */
    /* 0x08 */ s16 unk08; /* state */
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C; /* frame counter */
    /* 0x0E */ s16 unk0E; /* jump length */
    /* 0x10 */ f32 unk10; /* vertical speed */
    /* 0x14 */ s32 unk14; /* win voice file */
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A; /* controller port */
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ s16 unk1E; /* CPU */
    /* 0x20 */ s16 unk20; /* CPU difficulty */
    /* 0x22 */ s16 unk22; /* log held, -1 none */
    /* 0x24 */ s16 unk24; /* CPU: target, -1 none */
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28; /* CPU: frames since the last press */
    /* 0x2A */ s16 unk2A; /* CPU: frames to wait */
    /* 0x2C */ u16 unk2C; /* CPU: buttons to press */
    /* 0x2E */ s16 unk2E; /* CPU: misses in a row */
    /* 0x30 */ s16 unk30; /* CPU: 4 - difficulty */
    /* 0x32 */ s16 unk32; /* motion */
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[2];
} LjPlayer; // Size 0x38

/* One team (D_8010E5AC_log_jam, 2 x 0x48). */
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} LjRGBA;

/* One log (D_8010E5C4_log_jam, 32 x 0x78). */
typedef struct LjLog {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02[3]; /* models */
    /* 0x08 */ s16 unk08; /* active */
    /* 0x0A */ s16 unk0A; /* kind */
    /* 0x0C */ s16 unk0C; /* state */
    /* 0x0E */ s16 unk0E; /* state timer */
    /* 0x10 */ Vec unk10; /* position */
    /* 0x1C */ Vec unk1C; /* rotation */
    /* 0x28 */ Vec unk28; /* velocity */
    /* 0x34 */ s16 unk34; /* piece: 0 left half, 1 right half */
    /* 0x36 */ char unk36[0x1C];
    /* 0x52 */ s16 unk52; /* piece state */
    /* 0x54 */ f32 unk54; /* spin speed */
    /* 0x58 */ f32 unk58; /* wobble amplitude */
    /* 0x5C */ f32 unk5C; /* wobble decay */
    /* 0x60 */ f32 unk60; /* wobble phase */
    /* 0x64 */ f32 unk64; /* wobble speed */
    /* 0x68 */ f32 unk68; /* resting roll */
    /* 0x6C */ char unk6C[8];
    /* 0x74 */ void (*unk74)(struct LjLog*);
} LjLog; // Size 0x78

/* A cloud sprite (D_8010E5D4_log_jam, 5 x 0x24). */
typedef struct LjCloud {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02; /* sprite group */
    /* 0x04 */ s16 unk04; /* phase, degrees */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* speed */
    /* 0x0C */ f32 unk0C; /* x */
    /* 0x10 */ f32 unk10; /* y */
    /* 0x14 */ f32 unk14; /* scale x */
    /* 0x18 */ f32 unk18; /* scale y */
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
} LjCloud; // Size 0x24

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
void func_80107080_log_jam(omObjData* obj, LjTeam* team);
void func_80107C84_log_jam(omObjData* obj, LjTeam* team);
void func_8010A6FC_log_jam(s16 team, s16 score);
LjLog* func_8010910C_log_jam(s16 idx);
void func_8010925C_log_jam(s16 idx);
s32 func_8010A9D4_log_jam(Vec* pos, Vec* vel, Vec* scale, f32 speed, LjRGBA* color);
f32 func_8010C514_log_jam(f32 target, f32 cur, f32 step);
void func_80106F48_log_jam(omObjData* obj);
void func_8010C5DC_log_jam(omObjData* obj, s16 arg1, s16 arg2);
void func_8010C714_log_jam(omObjData* obj, s16 arg1, s16 arg2);
void func_8010C7F8_log_jam(omObjData* obj);
void func_8010C8B0_log_jam(omObjData* obj);
s16 func_80109A7C_log_jam(s16 kind, s16 part);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char* arg2);
void func_80108840_log_jam(omObjData* obj, LjTeam* team);
void func_80108A80_log_jam(omObjData* obj, LjTeam* team);
s16 func_80108D1C_log_jam(f32 v, f32 g);
void func_80109140_log_jam(s16 idx, f32 x, f32 y, f32 z);
void func_80109190_log_jam(s16 idx, f32 x, f32 y, f32 z);
f32 func_8010C2DC_log_jam(f32 target, f32 cur, f32 step);
f32 func_8010C49C_log_jam(f32 t, f32 a, f32 b);
f32 func_8010C4B4_log_jam(f32 a, f32 b, f32 t);
void func_8010C7D0_log_jam(omObjData* obj);
void func_8010CAC0_log_jam(omObjData* obj, const char* name, f32 (*mf)[4]);
s32 func_8010AE58_log_jam(Vec* pos, Vec* vel, Vec* scale, f32 speed, LjRGBA* color);
omObjData* func_80045F1C_main(u32, s16, s16);
void func_800E4C88_minigame(omObjData* obj, s32 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_8010C6A4_log_jam(omObjData* obj, s16 arg1, s16 arg2);
void func_80109350_log_jam(s16 idx);
void func_8008A070_main(f32 (*mf)[4]);
void func_80017D24_main(f32 (*mf)[4], f32 rx, f32 ry, f32 rz);
void* func_8010C588_log_jam(omObjData* obj);
void func_80108E54_log_jam(omObjData* obj);
void func_80109B8C_log_jam(omObjData* obj);
void func_8010A0B0_log_jam(omObjData* obj);
u16 func_8010A300_log_jam(s32 dirAndFile);
s16 func_80109044_log_jam(s16 kind, s16 part);
void func_801094E4_log_jam(LjLog* log);

extern Vec D_8010DE90_log_jam[]; /* player start positions (D_8010DE98 = [0].z) */
extern f32 D_8010DF20_log_jam[]; /* player start rotations */
extern s32 D_8010DF90_log_jam; /* exit wipe countdown; D_8010DF92 = its low half */
extern s32 D_8010DF94_log_jam[4]; /* player order */
extern s16 D_8010DFA4_log_jam[4][2][2]; /* fallback teams */
extern s16 D_8010DFC4_log_jam[4]; /* position in the team per slot */
extern s16 D_8010DFCC_log_jam[4]; /* player object marks */
extern s32 D_8010DFD4_log_jam[]; /* per character: voice directory */
extern s32 D_8010DFF4_log_jam[]; /* voice files; (s16) = the low half (D_8010DFF6, D_8010DFFE) */
extern s32 D_800A178C_main[][6];
extern Vec D_8010DEC0_log_jam[4]; /* positions at the log (D_8010DEC8 = [0].z) */
extern Vec D_8010DEF0_log_jam[4]; /* jump landing positions (D_8010DEF8 = [0].z) */
extern s32 D_8010DF50_log_jam[8]; /* win motion per character */
extern s32 D_8010DF70_log_jam[8]; /* lose motion per character */
extern f32 D_8010E010_log_jam[8]; /* effect height per character */
extern s32 D_8010E004_log_jam[3]; /* model slots of the carried log */
extern u16 D_800D5558_main[];

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
extern s16* D_8010E5CC_log_jam; /* sprite files */
extern D_80111B50_vine_with_me_Struct D_8010E640_log_jam;
extern Vec D_8010DF30_log_jam[2]; /* D_8010DF38 = [0].z */
extern LjRGBA D_8010DF48_log_jam;
extern LjRGBA D_8010DF4C_log_jam;
extern LjLog* D_8010E5C4_log_jam;
extern omObjData* D_8010E5C0_log_jam;
extern LjCloud* D_8010E5D4_log_jam;
extern f32 D_8010E054_log_jam[5][2]; /* cloud positions (D_8010E058 = [0][1]) */
extern f32 D_8010E07C_log_jam[5]; /* cloud speeds */
extern s16* D_8010E5C8_log_jam; /* log model templates, 3 kinds x 3 parts */
extern s32 D_8010E030_log_jam[9]; /* log model files */
extern u8 D_800D6A90_main;
extern omObjData* D_800EC1C0_minigame[];
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


const Vec D_8010E1F0_log_jam = { 0.7f, 0.7f, 0.7f }; /* effect scale */

void func_801065E8_log_jam(omObjData* obj) {
    Vec pos;
    Vec scale = D_8010E1F0_log_jam;
    LjTeam* team;
    LjLog* log;
    s16 done;

    done = 0;
    team = func_8010C588_log_jam(obj);
    func_80107080_log_jam(team->unk00, team);
    func_80107C84_log_jam(team->unk04, team);
    if (team->unk12 >= 30) {
        team->unk12 = 29;
    }
    func_8010A6FC_log_jam(team->unk10, team->unk12);
    if (func_800E6E8C_minigame() == 3 && team->unk16 != -1) {
        log = func_8010910C_log_jam(team->unk16);
        pos.x = log->unk10.x;
        pos.z = log->unk10.z;
        pos.y = log->unk10.y + 40.00000059604645;
        func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
        func_8010925C_log_jam(team->unk16);
        team->unk16 = team->unk18 = -1;
    }
    if (team->unk1C != -1) {
        team->unk30.x += team->unk40;
        team->unk30.y += team->unk44;
        team->unk24.y += team->unk3C;
        team->unk3C -= 1.6333001f;
        team->unk24.x = func_8010C514_log_jam(D_8010DF30_log_jam[(s16)(team->unk10 ^ 1)].x, team->unk24.x, 7.0f);
        team->unk24.z = func_8010C514_log_jam(D_8010DF30_log_jam[(s16)(team->unk10 ^ 1)].z, team->unk24.z, 7.0f);
        if (team->unk24.y < 184.0000033378601 && team->unk3C <= 0.0f) {
            done = 1;
            team->unk30.x = -225.0f;
            team->unk24.y = 184.0f;
        }
        Hu3DModelPosSet(team->unk1C, team->unk24.x, team->unk24.y, team->unk24.z);
        Hu3DModelRotSet(team->unk1C, 0.0f, team->unk30.y, 0.0f);
        if (team->unk20 >= 0) {
            pos.x = team->unk24.x;
            pos.z = team->unk24.z;
            pos.y = team->unk24.y - 50.0;
            func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            func_8001C258_main(team->unk1C, 4, 4);
            done = 1;
        }
        func_8008A070_main((f32(*)[4])HmfModelData[team->unk1C].mtx);
        func_80017C10_main((Mtx*)HmfModelData[team->unk1C].mtx, 0.0f, -50.0f, 0.0f);
        func_80017D24_main((f32(*)[4])HmfModelData[team->unk1C].mtx, team->unk30.x, 0.0f, 0.0f);
        team->unk20++;
        if (done != 0) {
            team->unk1C = -1;
        }
    }
    team->unk1A++;
}

const char D_8010E218_log_jam[] = "item_hook"; /* hook attach point */

#ifdef NON_MATCHING
/* Differs: the character-table loads for func_800E1BA8_minigame and the voice pointer take other registers/slots. */
void func_80106968_log_jam(omObjData* obj) {
    LjPlayer* pl;
    s32* voice;
    s16 chr;
    s16 i;
    s16 gw;
    func_800E1BA8_minigame_ObjData* w;

    pl = func_8010C588_log_jam(obj);
    gw = pl->unk18;
    chr = GwPlayer[gw].chr;
    pl->unk1C = chr;
    pl->unk1A = GwPlayer[gw].pad;
    pl->unk1E = GwPlayer[gw].stat & 1;
    pl->unk20 = GwPlayer[gw].cpu_difficulty;
    func_800E1BA8_minigame(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][2], gw, 0x6A9, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    if (pl->unk02 == 1) {
        obj->model[2] = func_8000B108_main(0x340000, 0xB9);
        func_8001C258_main(obj->model[2], 0x4000, 0x4000);
        func_8001EF6C_main(obj->model[2], obj->model[0], D_8010E218_log_jam);
        for (i = 0; i < 3; i++) {
            obj->model[3 + i] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(obj->model[3 + i], 4, 4);
            func_8001C258_main(obj->model[3 + i], 0x4000, 0x4000);
            func_8001EF6C_main(obj->model[3 + i], obj->model[2], "m219-item-f");
        }
    } else {
        for (i = 0; i < 3; i++) {
            obj->model[3 + i] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(obj->model[3 + i], 4, 4);
            func_8001C258_main(obj->model[3 + i], 0x4000, 0x4000);
            func_8001EF6C_main(obj->model[3 + i], obj->model[0], D_8010E218_log_jam);
        }
    }
    obj->model[6] = func_8000B108_main(8, 0x68D);
    Hu3DModelScaleSet(obj->model[6], 0.5f, 0.5f, 0.5f);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 6), 1, 0x1B);
    if (pl->unk02 == 1) {
        func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x74), 0, 0x14);
        func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x75), 0, 0xA);
        func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x81), 0, 8);
        func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 0x76), 1, 0);
    } else {
        func_800E5A00_minigame(obj, 7, func_80017BB8_main(chr, 0x77), 0, 0x1E);
        func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 0x78), 0, 0x28);
    }
    if (chr == 5) {
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(5, 0x31), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[5] | 0x31;
    } else if (chr == 1 || chr == 6) {
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, (s16)D_8010DFF4_log_jam[0]), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[chr] | D_8010DFF4_log_jam[0];
    } else {
        voice = &D_8010DFF4_log_jam[rand8() & 1];
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, (s16)*voice), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[chr] | *voice;
    }
    func_800E5A00_minigame(obj, 10, func_80017BB8_main(chr, (s16)D_8010DFF4_log_jam[2]), 1, 0x78);
    pl->unk06 = -1;
    pl->unk0C = 0;
    pl->unk0A = 0;
    pl->unk22 = -1;
    pl->unk24 = -1;
    pl->unk26 = -1;
    pl->unk10 = 0.0f;
    pl->unk0E = 0;
    pl->unk28 = 0;
    pl->unk2A = 10;
    pl->unk2C = 0;
    pl->unk2E = 0;
    pl->unk30 = 4 - pl->unk20;
    if (pl->unk02 == 0) {
        pl->unk08 = 0;
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk32 = 0;
    } else {
        pl->unk08 = 5;
        func_8010C714_log_jam(obj, 4, 7);
        pl->unk32 = 4;
    }
    pl->unk34 = 0;
    obj->func = func_80106F48_log_jam;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106968_log_jam);
#endif

void func_80106F48_log_jam(omObjData* obj) {
    LjPlayer* pl = func_8010C588_log_jam(obj);

    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    pl->unk0C++;
    func_8010C7F8_log_jam(obj);
    func_8010C8B0_log_jam(obj);
}

void func_80106FAC_log_jam(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] != -1) {
                func_8001ACDC_main(D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]]);
                D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] = -1;
            }
        }
    }
}

/* The player without the hook (role 0): take a log from the chute and pass it to the partner. */
void func_80107080_log_jam(omObjData* obj, LjTeam* team) {
    f32 mtx[4][4];
    Vec scale = D_8010E1F0_log_jam;
    Vec pos;
    LjPlayer* pl;
    HmfModel* hmf;
    LjPlayer* partner;
    f32 t;
    s32 sym;

    t = 0.0f;
    pl = func_8010C588_log_jam(obj);
    hmf = &HmfModelData[obj->model[0]];
    partner = team->unk0C;
    if (pl->unk1E != 0) {
        func_80108840_log_jam(obj, team);
    }
    if (func_800E6E8C_minigame() == 3 && pl->unk08 < 13) {
        pl->unk08 = 13;
        pl->unk0C = 0;
    }
    if (*(s32*)&pl->unk08 != 0x10000 && pl->unk08 < 13) {
        obj->rot.y = func_8010C2DC_log_jam(D_8010DF20_log_jam[pl->unk00], obj->rot.y, 10.0f);
    }
    switch (pl->unk08) {
    case 0:
        if (pl->unk0C >= 3.0f && func_800E6E8C_minigame() == 2) {
            func_8010C5DC_log_jam(obj, 7, 5);
            func_8004AC98_main(0x38A, pl->unk18);
            pl->unk08 = 1;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 1:
        if (pl->unk0A == 0) {
            t = pl->unk0C / 14.0f;
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->rot.y = func_8010C4B4_log_jam(D_8010DF20_log_jam[pl->unk00], 0.0f, t);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 14.0f && hmf->unk02 == obj->motion[7]) {
                pl->unk24 = (u8)(rand8() % 3);
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 0);
                pl->unk0A++;
                pl->unk0C = 0;
            }
        } else if (hmf->unk04 == 0xFF && hmf->unk40 >= 29.0f && hmf->unk02 == obj->motion[7]) {
            pl->unk08 = 2;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 2:
        if ((D_800D5558_main[pl->unk1A] & 0xE000) && team->unk16 == -1 && partner->unk22 == -1 &&
            (u16)(partner->unk08 - 6) < 2) {
            switch (D_800D5558_main[pl->unk1A]) {
            case 0x8000:
                sym = 0;
                break;
            case 0x4000:
                sym = 1;
                break;
            case 0x2000:
                sym = 2;
                break;
            default:
                sym = 3;
                break;
            }
            if (sym == pl->unk24) {
                func_8010C5DC_log_jam(obj, 8, 5);
                pl->unk08 = 3;
            } else {
                func_8010C714_log_jam(obj, 8, 0);
                hmf->unk40 = 0.0f;
                hmf->unk44 = 0.0f;
                omVibrate(pl->unk18, 2, 3, 10);
                pl->unk08 = 4;
            }
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 4:
        if (pl->unk0A == 0) {
            if ((hmf->unk40 += 2.0f) >= 10.0f) {
                pos.x = obj->trans.x;
                pos.y = obj->trans.y + D_8010E010_log_jam[pl->unk1C];
                pos.z = obj->trans.z;
                func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
                pl->unk0A++;
            }
        } else if (!(pl->unk0A & 1)) {
            if ((hmf->unk40 += 2.0f) >= 6.0f) {
                pl->unk0A++;
            }
        } else if ((hmf->unk40 -= 2.0f) <= 0.0f) {
            if (pl->unk0A == 1 || pl->unk0A == 5 || pl->unk0A == 9) {
                pos.x = obj->trans.x;
                pos.y = obj->trans.y + D_8010E010_log_jam[pl->unk1C];
                pos.z = obj->trans.z;
                func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
            }
            pl->unk0A++;
        }
        if (pl->unk0A >= 9) {
            func_8010C7D0_log_jam(obj);
            hmf->unk40 = 0.0f;
            pl->unk08 = 2;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 3:
        if (pl->unk0A == 0) {
            if (hmf->unk04 == 0xFF && hmf->unk02 == obj->motion[8]) {
                t = hmf->unk40 / 20.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEC0_log_jam[pl->unk00].x);
            obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEC0_log_jam[pl->unk00].z);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 19.0f && hmf->unk02 == obj->motion[8]) {
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
                pl->unk22 = func_80109044_log_jam(pl->unk24, 0);
                func_80109140_log_jam(pl->unk22, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                      D_8010DF30_log_jam[team->unk10].z);
                func_80109190_log_jam(pl->unk22, 0.0f, 0.0f, 0.0f);
                team->unk16 = pl->unk22;
                team->unk18 = pl->unk24;
                team->unk1A = 0;
                pl->unk22 = pl->unk24 = -1;
                omVibrate(pl->unk18, 10, 0, 10);
                pl->unk0A++;
                pl->unk0C = 0;
            }
        } else {
            if (hmf->unk04 == 0xFF && hmf->unk02 == obj->motion[8]) {
                t = (hmf->unk40 - 19.0f) / 20.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->trans.x = func_8010C49C_log_jam(t, D_8010DEC0_log_jam[pl->unk00].x, D_8010DE90_log_jam[pl->unk00].x);
            obj->trans.z = func_8010C49C_log_jam(t, D_8010DEC0_log_jam[pl->unk00].z, D_8010DE90_log_jam[pl->unk00].z);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 39.0f && hmf->unk02 == obj->motion[8]) {
                func_8010C5DC_log_jam(obj, 0, 5);
                pl->unk08 = 0;
                pl->unk0A = 0;
                pl->unk0C = 0;
            }
        }
        break;
    case 13:
        if (pl->unk24 != -1) {
            func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
            func_8010CAC0_log_jam(obj, D_8010E218_log_jam, mtx);
            func_8010A9D4_log_jam((Vec*)mtx[3], NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            pl->unk22 = pl->unk24 = -1;
        }
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk08 = 14;
        /* fallthrough */
    case 14:
        obj->rot.y = func_8010C2DC_log_jam(0.0f, obj->rot.y, 10.0f);
        obj->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].x, obj->trans.x, 10.0f);
        obj->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].z, obj->trans.z, 10.0f);
        if (func_800E6E8C_minigame() == 4) {
            func_8010C5DC_log_jam(obj, 1, 5);
            pl->unk10 = 32.0f;
            pl->unk0E = func_80108D1C_log_jam(32.0f, 1.6333001f);
            pl->unk08 = 15;
            pl->unk0C = 0;
        }
        break;
    case 15:
        t = (f32)pl->unk0C / pl->unk0E;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (t < 0.0f) {
            t = 0.0f;
        }
        if (pl->unk0C == 6) {
            func_8010C5DC_log_jam(obj, 2, 6);
        } else if (pl->unk0C == pl->unk0E - 10) {
            func_8010C5DC_log_jam(obj, 1, 7);
        }
        obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEF0_log_jam[pl->unk00].x);
        obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEF0_log_jam[pl->unk00].z);
        obj->trans.y += pl->unk10;
        pl->unk10 -= 1.6333001f;
        if (obj->trans.y <= 0.0f) {
            func_8010C5DC_log_jam(obj, 0, 5);
            obj->trans.y = 0.0f;
            pl->unk08 = 16;
            pl->unk0C = 0;
        }
        break;
    case 16:
        pl->unk08 = 17;
        pl->unk0C = 0;
        break;
    case 17:
        if (pl->unk06 != -1) {
            switch (pl->unk06) {
            case 0:
                func_8010C5DC_log_jam(obj, 9, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF50_log_jam[pl->unk1C]);
                func_80045F1C_main(pl->unk14, -1, pl->unk18);
                break;
            case 1:
                func_8010C5DC_log_jam(obj, 10, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF70_log_jam[pl->unk1C]);
                break;
            }
            pl->unk06 = -1;
        }
        break;
    }
}

/* The hook player (role 1): hook the log the partner passes, split it, throw the hook at the end. */
void func_80107C84_log_jam(omObjData* obj, LjTeam* team) {
    f32 mtx[4][4];
    Vec scale = D_8010E1F0_log_jam;
    LjPlayer* pl;
    HmfModel* hmf;
    LjPlayer* partner;
    f32 t;
    f32 frame;
    s32 target;

    pl = func_8010C588_log_jam(obj);
    hmf = &HmfModelData[obj->model[0]];
    partner = team->unk08;
    if (pl->unk1E != 0) {
        func_80108A80_log_jam(obj, team);
    }
    if (func_800E6E8C_minigame() == 3 && pl->unk08 < 13) {
        pl->unk08 = 13;
        pl->unk0C = 0;
    }
    switch (pl->unk08) {
    case 5:
        if (func_800E6E8C_minigame() == 2) {
            func_8010C5DC_log_jam(obj, 3, 7);
            pl->unk08 = 6;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 6:
        if (hmf->unk04 == 0xFF && hmf->unk40 >= 19.0f && hmf->unk02 == obj->motion[3]) {
            pl->unk08 = 7;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 7:
        if ((D_800D5558_main[pl->unk1A] & 0xE000) && *(s32*)&partner->unk08 != 0x30000) {
            if (D_800D5558_main[pl->unk1A] == 0x8000) {
                pl->unk26 = 0;
            } else if (D_800D5558_main[pl->unk1A] == 0x4000) {
                pl->unk26 = 1;
            } else if (D_800D5558_main[pl->unk1A] == 0x2000) {
                pl->unk26 = 2;
            } else {
                pl->unk26 = 3;
            }
            if (pl->unk22 == 32) {
                target = pl->unk24;
            } else {
                target = team->unk18;
            }
            func_8004AC98_main(0x38D, pl->unk18);
            if (target == -1 || target == pl->unk26) {
                func_8010C5DC_log_jam(obj, 4, 2);
                pl->unk08 = 8;
            } else {
                func_8010C5DC_log_jam(obj, 5, 2);
                pl->unk08 = 9;
            }
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 8:
        if (pl->unk22 == 32) {
            target = pl->unk24;
        } else {
            target = team->unk18;
        }
        frame = 9.0f;
        if (hmf->unk04 == 0xFF && hmf->unk40 >= frame && hmf->unk02 == obj->motion[4]) {
            if (target == -1) {
                func_8004AC98_main(0x38C, pl->unk18);
                pl->unk08 = 12;
                pl->unk0A = 0;
                pl->unk0C = 0;
                func_8010C5DC_log_jam(obj, 6, 5);
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            } else {
                func_8004AC98_main(0x38B, pl->unk18);
                omVibrate(pl->unk18, 10, 0, 10);
                pl->unk08 = 10;
                pl->unk0A = 0;
                pl->unk0C = 0;
                if (team->unk16 != -1) {
                    pl->unk22 = team->unk16;
                    team->unk16 = team->unk18 = -1;
                    team->unk1A = 0;
                } else {
                    func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
                    pl->unk24 = pl->unk22 = -1;
                    pl->unk22 = func_80109044_log_jam(target, 0);
                    func_80109140_log_jam(pl->unk22, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                          D_8010DF30_log_jam[team->unk10].z);
                    func_80109190_log_jam(pl->unk22, 0.0f, 0.0f, 0.0f);
                }
                if (pl->unk22 != -1) {
                    func_80109350_log_jam(pl->unk22);
                    pl->unk22 = pl->unk24 = -1;
                }
                if (func_800E6E8C_minigame() == 2) {
                    team->unk12++;
                }
            }
        }
        break;
    case 9:
        if (hmf->unk04 == 0xFF && hmf->unk40 >= 8.0f && hmf->unk02 == obj->motion[5]) {
            func_8004AC98_main(0x38C, pl->unk18);
            pl->unk08 = 11;
            pl->unk0A = 0;
            pl->unk0C = 0;
            if (team->unk16 != -1) {
                pl->unk22 = 32;
                pl->unk24 = team->unk18;
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 0);
                func_8010925C_log_jam(team->unk16);
                team->unk16 = team->unk18 = -1;
                team->unk1A = 0;
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y + 50.0,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            } else {
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            }
            omVibrate(pl->unk18, 2, 2, 20);
            func_8010C7D0_log_jam(obj);
        }
        break;
    case 10:
        if (pl->unk0C >= 9.0f) {
            pl->unk08 = 5;
            pl->unk0A = 0;
            pl->unk0C = 0;
            func_8010C5DC_log_jam(obj, 3, 5);
        }
        break;
    case 11:
        if (pl->unk0C >= 15.0f) {
            pl->unk08 = 6;
            pl->unk0A = 0;
            pl->unk0C = 0;
            func_8010C6A4_log_jam(obj, 3, 12);
        }
        break;
    case 12:
        if (pl->unk0C >= 90.0f) {
            func_8010C5DC_log_jam(obj, 3, 7);
            pl->unk08 = 5;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 13:
        func_8010CAC0_log_jam(obj, D_8010E218_log_jam, mtx);
        team->unk1C = obj->model[2];
        if (team->unk1C != -1) {
            func_8008A070_main((f32(*)[4])HmfModelData[team->unk1C].mtx);
            func_80017C10_main((Mtx*)HmfModelData[team->unk1C].mtx, 0.0f, -50.0f, 0.0f);
            func_8001C258_main(team->unk1C, 0x4000, 0);
            team->unk20 = 0;
            team->unk24.x = mtx[3][0];
            team->unk24.z = mtx[3][2];
            team->unk24.y = mtx[3][1] + 50.0;
            team->unk3C = 30.000001907348633f;
            team->unk40 = (u8)(rand8() % 10) + 40;
            team->unk44 = 3 - (u8)(rand8() % 6);
        }
        if (pl->unk24 != -1) {
            func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
            func_8010A9D4_log_jam((Vec*)mtx[3], NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            pl->unk22 = pl->unk24 = -1;
        }
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk08 = 14;
        /* fallthrough */
    case 14:
        obj->rot.y = func_8010C2DC_log_jam(0.0f, obj->rot.y, 10.0f);
        obj->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].x, obj->trans.x, 10.0f);
        obj->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].z, obj->trans.z, 10.0f);
        if (func_800E6E8C_minigame() == 4) {
            func_8010C5DC_log_jam(obj, 1, 5);
            pl->unk10 = 25.0f;
            pl->unk0E = func_80108D1C_log_jam(25.0f, 1.6333001f);
            pl->unk08 = 15;
            pl->unk0C = 0;
        }
        break;
    case 15:
        t = (f32)pl->unk0C / pl->unk0E;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (t < 0.0f) {
            t = 0.0f;
        }
        if (pl->unk0C == 6) {
            func_8010C5DC_log_jam(obj, 2, 6);
        } else if (pl->unk0C == pl->unk0E - 6) {
            func_8010C5DC_log_jam(obj, 1, 6);
        }
        obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEF0_log_jam[pl->unk00].x);
        obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEF0_log_jam[pl->unk00].z);
        obj->trans.y += pl->unk10;
        pl->unk10 -= 1.6333001f;
        if (obj->trans.y <= 0.0f) {
            func_8010C5DC_log_jam(obj, 0, 5);
            obj->trans.y = 0.0f;
            pl->unk08 = 16;
            pl->unk0C = 0;
        }
        break;
    case 16:
        pl->unk08 = 17;
        pl->unk0C = 0;
        break;
    case 17:
        if (pl->unk06 != -1) {
            switch (pl->unk06) {
            case 0:
                func_8010C5DC_log_jam(obj, 9, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF50_log_jam[pl->unk1C]);
                func_80045F1C_main(pl->unk14, -1, pl->unk18);
                break;
            case 1:
                func_8010C5DC_log_jam(obj, 10, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF70_log_jam[pl->unk1C]);
                break;
            }
            pl->unk06 = -1;
        }
        break;
    }
}

/* CPU input of the hook player (role 1). */
void func_80108840_log_jam(omObjData* obj, LjTeam* team) {
    LjPlayer* pl = func_8010C588_log_jam(obj);
    LjPlayer* partner = team->unk0C;

    D_800D5558_main[pl->unk1A] = 0;
    switch (pl->unk08) {
    case 1:
    case 3:
    case 4:
        pl->unk2C = 0;
        break;
    case 2:
        if (pl->unk2C != 0) {
            D_800D5558_main[pl->unk1A] |= pl->unk2C;
        } else if (pl->unk28 > pl->unk2A) {
            if ((u8)(rand8() % 100) < pl->unk20 * 13 + 50 || pl->unk2E >= pl->unk30 || partner->unk1E == 0) {
                switch (pl->unk24) {
                case 0:
                    pl->unk2C |= 0x8000;
                    break;
                case 1:
                    pl->unk2C |= 0x4000;
                    break;
                default:
                    pl->unk2C |= 0x2000;
                    break;
                }
                pl->unk2E = 0;
            } else {
                switch (pl->unk24) {
                case 0:
                    pl->unk2C |= 0x2000;
                    break;
                case 1:
                    pl->unk2C |= 0x8000;
                    break;
                default:
                    pl->unk2C |= 0x4000;
                    break;
                }
                pl->unk2E++;
            }
            pl->unk28 = 0;
            pl->unk2A = (u8)(rand8() % 3) + (6 - pl->unk20 * 2) * 2;
        }
        break;
    }
    pl->unk28++;
}

/* CPU input of the other player (role 0). */
void func_80108A80_log_jam(omObjData* obj, LjTeam* team) {
    LjPlayer* pl = func_8010C588_log_jam(obj);
    LjPlayer* partner = team->unk08;
    s16 target;

    D_800D5558_main[pl->unk1A] = 0;
    if (team->unk16 != -1) {
        target = team->unk18;
    } else {
        target = pl->unk24;
    }
    switch (pl->unk08) {
    case 7:
        if (pl->unk2C & 0xE000) {
            D_800D5558_main[pl->unk1A] |= pl->unk2C;
        } else if (pl->unk28 > pl->unk2A && target != -1) {
            if ((u8)(rand8() % 100) < pl->unk20 * 13 + 50 || pl->unk2E >= pl->unk30 || partner->unk1E == 0) {
                switch (target) {
                case 0:
                    pl->unk2C |= 0x8000;
                    break;
                case 1:
                    pl->unk2C |= 0x4000;
                    break;
                default:
                    pl->unk2C |= 0x2000;
                    break;
                }
                pl->unk2E = 0;
            } else {
                switch (target) {
                case 0:
                    pl->unk2C |= 0x2000;
                    break;
                case 1:
                    pl->unk2C |= 0x8000;
                    break;
                default:
                    pl->unk2C |= 0x4000;
                    break;
                }
                pl->unk2E++;
            }
            pl->unk28 = 0;
            pl->unk2A = (u8)(rand8() % 10) + 16 - pl->unk20 * 2;
        }
        break;
    case 8:
    case 9:
        pl->unk2C = 0;
        break;
    }
    pl->unk28++;
}

/* 1 when all four players are in this state. */
s16 func_80108CE0_log_jam(s16 state) {
    LjPlayer* pl;
    s32 i;

    for (i = 0, pl = D_8010E5B8_log_jam; i < 4; i++, pl++) {
        if (pl->unk08 != state) {
            return 0;
        }
    }
    return 1;
}

/* Frames a throw at speed v under gravity g stays above its start height. */
s16 func_80108D1C_log_jam(f32 v, f32 g) {
    f32 y = 0.0f;
    s16 n = 0;

    do {
        y += v;
        v -= g;
        n++;
    } while (y > 0.0f);
    return n;
}

void func_80108D50_log_jam(void) {
    LjLog* log;
    s32 i;

    log = D_8010E5C4_log_jam = HuMemAllocTag(sizeof(LjLog) * 32, 31000);
    for (i = 0; i < 32; i++, log++) {
        log->unk00 = i;
        log->unk02[0] = -1;
        log->unk02[1] = -1;
        log->unk02[2] = -1;
        log->unk08 = 0;
        log->unk0A = 0;
        log->unk0C = 0;
        log->unk0E = 0;
        log->unk10.x = log->unk10.y = log->unk10.z = 0.0f;
        log->unk1C.x = log->unk1C.y = log->unk1C.z = 0.0f;
        log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
        memset(&log->unk34, 0, 0x20);
        memset(&log->unk54, 0, 0x20);
        log->unk74 = NULL;
    }
    D_8010E5C0_log_jam = omAddObj(0x18, 0, 0, -1, func_80108E54_log_jam);
    omSetStatBit(D_8010E5C0_log_jam, 0xA0);
}

void func_80108E54_log_jam(omObjData* obj) {
    LjLog* log;
    s32 i;
    s32 j;

    for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
        if (log->unk08 == 0) {
            continue;
        }
        switch (log->unk0C) {
        case 0:
            break;
        case 1:
            if ((log->unk0E & 1) || func_80049F98_main() + D_800D6A90_main != 0) {
                for (j = 0; j < 3; j++) {
                    if (log->unk02[j] != -1) {
                        func_8001C258_main(log->unk02[j], 4, 0);
                    }
                }
            } else {
                for (j = 0; j < 3; j++) {
                    if (log->unk02[j] != -1) {
                        func_8001C258_main(log->unk02[j], 4, 4);
                    }
                }
            }
            if (log->unk0E >= 30.0f) {
                log->unk0E = 0;
                log->unk0C++;
            }
            break;
        default:
            func_8010925C_log_jam(log->unk00);
            continue;
        }
        if (log->unk74 != NULL && func_80049F98_main() + D_800D6A90_main == 0) {
            log->unk74(log);
        }
        if (log->unk08 == 0) {
            continue;
        }
        if (log->unk02[0] != -1) {
            Hu3DModelPosSet(log->unk02[0], log->unk10.x, log->unk10.y, log->unk10.z);
            Hu3DModelRotSet(log->unk02[0], log->unk1C.x, log->unk1C.y, log->unk1C.z);
        }
        if (func_80049F98_main() + D_800D6A90_main == 0) {
            log->unk0E++;
        }
    }
}

/* Spawn a log of a kind; returns its index or -1. */
s16 func_80109044_log_jam(s16 kind, s16 part) {
    LjLog* log;
    s32 i;

    if (D_8010E5C4_log_jam == NULL) {
        return -1;
    }
    for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
        if (log->unk08 == 0) {
            log->unk02[0] = func_80109A7C_log_jam(kind, part);
            if (log->unk02[0] != -1) {
                func_8001C258_main(log->unk02[0], 4, 0);
            }
            log->unk08 = 1;
            log->unk0A = kind;
            log->unk0C = 0;
            log->unk0E = 0;
            return i;
        }
    }
    return -1;
}

#ifdef NON_MATCHING
/* Differs: retail adds offset + base, this adds base + offset (operand order only). */
LjLog* func_8010910C_log_jam(s16 idx) {
    LjLog* logs = D_8010E5C4_log_jam;

    if (logs != NULL) {
        return &logs[idx];
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010910C_log_jam);
#endif

void func_80109140_log_jam(s16 idx, f32 x, f32 y, f32 z) {
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            log->unk10.x = x;
            log->unk10.y = y;
            log->unk10.z = z;
        }
    }
}

void func_80109190_log_jam(s16 idx, f32 x, f32 y, f32 z) {
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            log->unk1C.x = x;
            log->unk1C.y = y;
            log->unk1C.z = x; /* retail: z is ignored */
        }
    }
}

void func_801091DC_log_jam(void) {
    s32 i;
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
            if (log->unk08 != 0) {
                func_8010925C_log_jam(i);
            }
        }
        HuMemFree(D_8010E5C4_log_jam);
        D_8010E5C4_log_jam = NULL;
        D_8010E5C0_log_jam->func = NULL;
    }
}

void func_8010925C_log_jam(s16 idx) {
    LjLog* log;
    s32 i;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            for (i = 0; i < 3; i++) {
                if (log->unk02[i] != -1) {
                    func_8001ACDC_main(log->unk02[i]);
                    log->unk02[i] = -1;
                }
            }
            log->unk08 = 0;
            log->unk0E = 0;
            log->unk0C = 0;
            log->unk0A = 0;
            log->unk10.x = log->unk10.y = log->unk10.z = 0.0f;
            log->unk1C.x = log->unk1C.y = log->unk1C.z = 0.0f;
            log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
            memset(&log->unk34, 0, 0x20);
            memset(&log->unk54, 0, 0x20);
            log->unk74 = NULL;
        }
    }
}

const Vec D_8010E2C0_log_jam = { 0.0f, 0.0f, 0.0f };
const Vec D_8010E2CC_log_jam = { 0.5f, 0.5f, 0.5f }; /* split effect scale */

#ifdef NON_MATCHING
/* Differs: register allocation of the log pointer and one delay slot. */
/* Split a log in two halves that fly apart. */
void func_80109350_log_jam(s16 idx) {
    Vec pos = D_8010E2C0_log_jam;
    Vec scale = D_8010E2CC_log_jam;
    LjLog* log;
    LjLog* half;
    f32 x;
    f32 y;
    f32 z;
    s32 kind;
    s16 n;
    s32 i;

    if (D_8010E5C4_log_jam == NULL) {
        return;
    }
    log = &D_8010E5C4_log_jam[idx];
    if (log->unk08 == 0) {
        return;
    }
    kind = log->unk0A;
    x = log->unk10.x;
    y = log->unk10.y;
    z = log->unk10.z;
    pos.x = x;
    pos.y = log->unk10.y;
    pos.z = log->unk10.z;
    func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF48_log_jam);
    func_8010925C_log_jam(idx);
    for (i = 0; i < 2; i++) {
        n = func_80109044_log_jam(kind, i + 1);
        if (n != -1) {
            half = &D_8010E5C4_log_jam[n];
            half->unk10.x = x;
            half->unk10.y = y;
            half->unk10.z = z;
            half->unk34 = i;
            half->unk52 = 0;
            half->unk74 = func_801094E4_log_jam;
            half->unk74(half);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109350_log_jam);
#endif

#define LJ_RANDF() ((f32)(u8)(rand8() % 100) * 0.01)

/* Motion of a split half: fly out, land, then wobble to rest. */
void func_801094E4_log_jam(LjLog* log) {
    Vec pos = D_8010E2C0_log_jam;
    Vec scale = D_8010E2CC_log_jam;
    f32 f;

    switch (log->unk52) {
    case 0:
        if (log->unk34 == 0) {
            log->unk28.x = (LJ_RANDF() * 0.02 + 0.03f) * 100.0;
            log->unk54 = -(LJ_RANDF() * 0.75 + 4.0);
            log->unk68 = -90.0f;
        } else {
            log->unk28.x = -((LJ_RANDF() * 0.02 + 0.03f) * 100.0);
            log->unk54 = LJ_RANDF() * 0.75 + 4.0;
            log->unk68 = 90.0f;
        }
        log->unk28.y = LJ_RANDF() * 2.0 + 10.999999940395355;
        log->unk28.z = LJ_RANDF() * 1.2500000186264515 + 0.6250000093132257;
        log->unk52++;
        break;
    case 1:
        log->unk1C.z += log->unk54;
        log->unk28.y -= 1.6333001f;
        if (log->unk10.y <= 0.0f) {
            log->unk10.y = 0.0f;
            log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
            log->unk58 = 20.0f;
            log->unk5C = 1.0f;
            log->unk60 = 0.0f;
            log->unk64 = 55.0f;
            log->unk52++;
            pos.x = log->unk10.x;
            pos.y = log->unk10.y;
            pos.z = log->unk10.z;
            func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF48_log_jam);
        }
        break;
    case 2:
        log->unk60 += log->unk64;
        if (log->unk60 >= 360.0f) {
            log->unk60 -= 360.0f;
        }
        f = log->unk58 - log->unk5C;
        if (f > 0.0f) {
            log->unk58 = f;
        } else {
            log->unk58 = 0.0f;
        }
        log->unk1C.z = sindf(log->unk60) * log->unk58 + log->unk68;
        if (log->unk0C == 0) {
            log->unk0C = 1;
        }
        break;
    }
    log->unk10.x += log->unk28.x;
    log->unk10.y += log->unk28.y;
    log->unk10.z += log->unk28.z;
}

void func_80109A00_log_jam(void) {
    s32 i;

    D_8010E5C8_log_jam = HuMemAllocTag(9 * sizeof(s16), 31000);
    for (i = 0; i < 9; i++) {
        D_8010E5C8_log_jam[i] = func_8000B108_main(D_8010E030_log_jam[i], 0xBD);
    }
}

s16 func_80109A7C_log_jam(s16 kind, s16 part) {
    s16* mdl = D_8010E5C8_log_jam;

    return (mdl != NULL) ? Hu3DModelLink(mdl[kind * 3 + part]) : -1;
}

void func_80109AD8_log_jam(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        func_8001ACDC_main(D_8010E5C8_log_jam[i]);
    }
    HuMemFree(D_8010E5C8_log_jam);
    D_8010E5C8_log_jam = NULL;
}

void func_80109B34_log_jam(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 0x10, 0, -1, func_80109B8C_log_jam);
}

/* Stage setup: log chutes, the background, the score sprites and the clouds. */
void func_80109B8C_log_jam(omObjData* obj) {
    LjCloud* cloud;
    s16 mdl;
    s16 grp;
    s16 i;
    s16 j;

    obj->model[1] = mdl = func_8000B108_main(0x340001, 0xA9);
    Hu3DModelPosSet(mdl, -100.0f, 0.0f, 115.0f);
    obj->model[2] = mdl = Hu3DModelLink(mdl);
    Hu3DModelPosSet(mdl, 100.0f, 0.0f, 115.0f);
    obj->model[3] = mdl = func_8000B108_main(0x340002, 0x89);
    Hu3DModelPosSet(mdl, -230.0f, 0.0f, 195.0f);
    obj->model[4] = mdl = Hu3DModelLink(mdl);
    Hu3DModelPosSet(mdl, 230.0f, 0.0f, 195.0f);
    D_8010E5CC_log_jam[0] = func_8010A300_log_jam(0x34000C);
    grp = HuSprGrpCreate(3, 0);
    func_80055024_main(grp, 0, D_8010E5CC_log_jam[0], 0);
    func_80054904_main(grp, 0, 160, 120);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x4000580C);
    HuSprPriSet(grp, 0, 0xFF00);
    D_8010E5CC_log_jam[4] = func_8010A300_log_jam(0x340010);
    func_80055024_main(grp, 1, D_8010E5CC_log_jam[4], 0);
    func_80054904_main(grp, 1, 0, 40);
    func_800550F4_main(grp, 1, 0);
    func_80054FF8_main(grp, 1, 0);
    HuSprAttrSet(grp, 1, 0x4000580C);
    HuSprPriSet(grp, 1, 0xFF01);
    func_80055458_main(grp, 1, 200);
    D_8010E5CC_log_jam[1] = func_8010A300_log_jam(0x34000D);
    func_80055024_main(grp, 2, D_8010E5CC_log_jam[1], 0);
    func_80054904_main(grp, 2, 0, 0);
    func_800550F4_main(grp, 2, 0);
    func_80054FF8_main(grp, 2, 0);
    HuSprAttrSet(grp, 2, 0x403C);
    HuSprPriSet(grp, 2, 0xFFFF);
    D_8010E5CC_log_jam[2] = func_8010A300_log_jam(0x34000E);
    D_8010E5CC_log_jam[5] = func_8010A300_log_jam(0x340011);
    cloud = D_8010E5D4_log_jam = HuMemAllocTag(sizeof(LjCloud) * 5, 31000);
    for (i = 0; i < 5; i++, cloud++) {
        cloud->unk00 = i;
        cloud->unk02 = HuSprGrpCreate(2, 0);
        cloud->unk04 = rand8() % 360;
        cloud->unk08 = D_8010E07C_log_jam[i];
        cloud->unk0C = D_8010E054_log_jam[i][0];
        cloud->unk10 = D_8010E054_log_jam[i][1];
        cloud->unk14 = cloud->unk18 = 1.0f;
        cloud->unk1C = -0.5f;
        cloud->unk20 = 0;
        for (j = 0; j < 2; j++) {
            if (j == 0) {
                func_80055024_main(cloud->unk02, 0, D_8010E5CC_log_jam[2], 0);
            } else {
                func_80055024_main(cloud->unk02, j, D_8010E5CC_log_jam[5], 0);
                func_80055458_main(cloud->unk02, j, 190);
            }
            func_800550F4_main(cloud->unk02, j, 0);
            func_80054FF8_main(cloud->unk02, j, 0);
            HuSprAttrSet(cloud->unk02, j, 0x2000583C);
            func_80054904_main(cloud->unk02, j, cloud->unk0C, cloud->unk10);
            HuSprScaleSet(cloud->unk02, j, cloud->unk14, cloud->unk18);
            HuSprPriSet(cloud->unk02, j, j + i * 2 - 0xF1);
        }
    }
    obj->func = func_8010A0B0_log_jam;
}

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
