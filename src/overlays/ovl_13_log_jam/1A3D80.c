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
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14; /* win voice file */
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A; /* controller port */
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ s16 unk1E; /* CPU */
    /* 0x20 */ s16 unk20; /* CPU difficulty */
    /* 0x22 */ s16 unk22;
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
    /* 0x0E */ u16 unk0E; /* state timer */
    /* 0x10 */ Vec unk10; /* position */
    /* 0x1C */ Vec unk1C; /* rotation */
    /* 0x28 */ Vec unk28;
    /* 0x34 */ u8 unk34[0x20]; /* work for unk74 */
    /* 0x54 */ u8 unk54[0x20];
    /* 0x74 */ void (*unk74)(struct LjLog*);
} LjLog; // Size 0x78

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
void func_8008A070_main(f32 (*mf)[4]);
void func_80017D24_main(f32 (*mf)[4], f32 rx, f32 ry, f32 rz);
void* func_8010C588_log_jam(omObjData* obj);

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
extern void* D_8010E5CC_log_jam;
extern D_80111B50_vine_with_me_Struct D_8010E640_log_jam;
extern Vec D_8010DF30_log_jam[2]; /* D_8010DF38 = [0].z */
extern LjRGBA D_8010DF48_log_jam;
extern LjRGBA D_8010DF4C_log_jam;
extern LjLog* D_8010E5C4_log_jam;
extern omObjData* D_8010E5C0_log_jam;
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
    pl->unk10 = 0;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107080_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107C84_log_jam);

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
