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

/* One reel (D_8010DF7C_slot_synch, 4 x 0x3C): reels 0-1 are team 0's machine, 2-3 team 1's. */
typedef struct SsReel {
    /* 0x00 */ s16 unk00; /* model */
    /* 0x02 */ u8 unk02; /* reel index */
    /* 0x03 */ u8 unk03; /* reel strip (D_8010D854_slot_synch row) */
    /* 0x04 */ s8 unk04; /* 0 left, 1 right */
    /* 0x05 */ u8 unk05; /* face in front, 0..3 */
    /* 0x06 */ u8 unk06; /* symbol in front */
    /* 0x07 */ char unk07;
    /* 0x08 */ s16 unk08; /* symbol to stop on, -1 any */
    /* 0x0A */ u16 unk0A; /* state timer */
    /* 0x0C */ s16 unk0C; /* state: 0 idle, 1 speeding up, 2 spinning, 3 dropping, 4/5 broken */
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10; /* drop speed */
    /* 0x14 */ f32 unk14; /* spin speed */
    /* 0x18 */ f32 unk18; /* spin acceleration */
    /* 0x1C */ f32 unk1C; /* top spin speed */
    /* 0x20 */ s32 unk20; /* spin sound, -1 none */
    /* 0x24 */ Vec unk24; /* position */
    /* 0x30 */ Vec unk30; /* rotation */
} SsReel; // Size 0x3C

/* One row of machine-body vertices sharing a height (func_80108D3C_slot_synch). */
typedef struct SsRow {
    /* 0x00 */ u16 unk00[72]; /* vertex indices */
    /* 0x90 */ s16 unk90; /* height (Vtx ob[1]) */
    /* 0x92 */ s16 unk92; /* vertex count */
} SsRow; // Size 0x94

/* One machine body (D_8010DF80_slot_synch, 2 x 0x20): a bulge that runs up the cabinet. */
typedef struct SsBody {
    /* 0x00 */ s16 unk00; /* model */
    /* 0x02 */ s16 unk02; /* machine index */
    /* 0x04 */ s16 unk04; /* 1 = bulge moving */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* bulge height */
    /* 0x0C */ f32 unk0C; /* bulge half-width */
    /* 0x10 */ f32 unk10; /* bulge strength */
    /* 0x14 */ f32 unk14; /* bulge speed */
    /* 0x18 */ s16 unk18; /* row count */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ SsRow* unk1C; /* rows, shared by both bodies */
} SsBody; // Size 0x20

/* One score sprite (D_8010DF70_slot_synch.unk08, up to 24 x 0x2C). */
typedef struct SsSpr {
    /* 0x00 */ s16 unk00; /* group member */
    /* 0x02 */ u16 unk02; /* priority */
    /* 0x04 */ char unk04[2];
    /* 0x06 */ u8 unk06; /* graphic */
    /* 0x07 */ u8 unk07; /* team */
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ Vec2f unk14; /* start position */
    /* 0x1C */ Vec2f unk1C; /* target position */
    /* 0x24 */ Vec2f unk24; /* position */
} SsSpr; // Size 0x2C

/* The score sprites' manager (D_8010DF70_slot_synch, 0xC). */
typedef struct SsSprMan {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ s16 unk04; /* sprite group */
    /* 0x06 */ u16 unk06; /* sprite count */
    /* 0x08 */ SsSpr* unk08;
} SsSprMan;

/* A sprite position table entry (D_8010D938_slot_synch, D_8010D980_slot_synch). */
typedef struct SsSprPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05; /* graphic */
} SsSprPos;

/* The camera/ground object's data (func_80107794_slot_synch); Boulder Ball's BbGround. */
typedef struct SsGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} SsGround; // Size 0xB4

/* HmfData's vertex count (0x18 lies inside the header's unk16 padding). */
#define SS_HMF_VTXNUM(hmf) (*(s16*)&(hmf)->unk16[2])

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
s16 func_80108A7C_slot_synch(s16 reel);
s16 func_80108AA8_slot_synch(s16 reel);
s16 func_80108C88_slot_synch(s16 reel, s16 face);
void func_801089F8_slot_synch(s16 reel);
void func_80108CD0_slot_synch(s16 reel);
void func_8010800C_slot_synch(u8 sym, u8 team);
s16 func_80109FA4_slot_synch(s16 team, s16 sym);
s16 func_8010A178_slot_synch(s16 id);
void func_8010AA9C_slot_synch(s16 team, s16 score);
f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b);
void func_80108428_slot_synch(omObjData* obj);
s16 func_80108848_slot_synch(s16 idx);
void func_8010AD68_slot_synch(Vec* pos, s32 arg1, s32 arg2, f32 scale, void* arg4);
f64 fabs(f64);
f32 fabsf(f32);
void func_801091D8_slot_synch(omObjData* obj);
void func_801092B8_slot_synch(SsBody* b);
void func_80107794_slot_synch(omObjData* obj);
void func_80107A80_slot_synch(omObjData* obj);
void func_80107A88_slot_synch(void);
s16 func_80107B00_slot_synch(f32 x, f32 y, u8 gfx, u8 team, u16 prio);
void func_80107BAC_slot_synch(void);
void func_80107D54_slot_synch(omObjData* obj);
void func_80108238_slot_synch(void);
void func_80108D3C_slot_synch(void);
s16 func_8010A2C4_slot_synch(s32 file);
void func_8010A308_slot_synch(s16 grp, s16 member, f32 x, f32 y);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E1490_minigame(s32);
extern u8 D_800D2008_main;
extern u8 D_800D6A90_main;
void func_800DDD94_minigame(omObjData* obj);
omObjData* func_80045F1C_main(u32, s16, s16);
s32 func_80017BB8_main(s16, s16);
extern s16 D_800CDA7C_main[];
extern u16 D_800D5558_main[];

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
extern Vec D_8010D820_slot_synch[2];
extern SsSprPos D_8010D938_slot_synch[12];
extern SsSprPos D_8010D980_slot_synch[12];
extern f32 D_8010D840_slot_synch[5];
extern u8 D_8010D854_slot_synch[2][4];
extern s32 D_8010D86C_slot_synch;
extern s16 D_8010D9C8_slot_synch[4];
extern f32 D_8010D9D0_slot_synch[8];
extern s32 D_8010D870_slot_synch[8];
extern s32 D_8010D890_slot_synch[8];
extern s32 D_8010D90C_slot_synch[3];
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
extern u16 D_8010DF66_slot_synch[4]; /* sprite priorities */
extern SsSprMan D_8010DF70_slot_synch;
extern SsReel* D_8010DF7C_slot_synch;
extern SsBody* D_8010DF80_slot_synch;
extern s16* D_8010DF8C_slot_synch; /* sprite files, 0x20 */
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

#ifdef NON_MATCHING
void func_8010614C_slot_synch(void) {
    s32 grp[2][2];
    s32 g;
    SsTeam* team;
    SsPlayer* pl;
    omObjData* o;
    s32 bad;
    s32 n0;
    s32 n1;
    s32 i;
    s32 j;
    s32 tmp;
    s32 r;

    team = D_8010DF5C_slot_synch = HuMemAllocTag(sizeof(SsTeam) * 2, 31000);
    D_8010DF60_slot_synch = HuMemAllocTag(sizeof(SsPlayer) * 4, 31000);
    memset(D_8010DF60_slot_synch, 0, sizeof(SsPlayer) * 4);
    bad = 0;
    n1 = 0;
    n0 = 0;
    for (i = 0; i < 4; i++) {
        g = GwPlayer[D_8010D8B4_slot_synch[i]].group;
        switch (g) {
        case 0:
            if (n0 < 2) {
                grp[g][n0++] = D_8010D8B4_slot_synch[i];
            } else {
                bad = 1;
            }
            break;
        case 1:
            if (n1 < 2) {
                grp[g][n1++] = D_8010D8B4_slot_synch[i];
            } else {
                bad = 1;
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
        r = rand8() & 3;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                grp[i][j] = D_8010D8C4_slot_synch[r][i][j];
            }
        }
    } else {
        if (rand8() & 1) {
            tmp = grp[0][0];
            grp[0][0] = grp[0][1];
            grp[0][1] = tmp;
        }
        if (rand8() & 1) {
            tmp = grp[1][0];
            grp[1][0] = grp[1][1];
            grp[1][1] = tmp;
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        func_8010C3FC_slot_synch(omAddObj(i + 0x10, 0, 0, -1, func_80106878_slot_synch), team);
        team->unk10 = i;
        team->unk12 = 0;
        team->unk14 = 0;
        team->unk16 = 0;
        team->unk18 = -1;
        team->unk1A = -1;
        team->unk1C = 0;
        team->unk1E = -1;
        for (j = 0; j < 2; j++) {
            pl = &D_8010DF60_slot_synch[i * 2 + j];
            pl->unk00 = i * 2 + j;
            pl->unk02 = i;
            pl->unk1C = grp[i][j];
            o = D_800EC598_minigame[D_800EC280_minigame] = omAddObj(D_8010D8E4_slot_synch[pl->unk00], 9, 60, -1, func_80106560_slot_synch);
            D_800EC280_minigame++;
            o->trans.x = D_8010D7F0_slot_synch[pl->unk00].x;
            o->trans.z = D_8010D7F0_slot_synch[pl->unk00].z;
            if (j == 0) {
                team->unk00 = o;
                team->unk08 = pl;
            } else {
                team->unk04 = o;
                team->unk0C = pl;
            }
            func_8010C3FC_slot_synch(o, pl);
        }
        func_8010A480_slot_synch(i, GwPlayer[team->unk08->unk1C].chr, GwPlayer[team->unk0C->unk1C].chr, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010614C_slot_synch);
#endif

#ifdef NON_MATCHING
void func_80106560_slot_synch(omObjData* obj) {
    SsPlayer* pl;
    func_800E1BA8_minigame_ObjData* w;
    s32* msg;
    s16 chr;
    s16 idx;
    s32 dir;
    s32 r;
    s32 file;

    pl = func_8010C428_slot_synch(obj);
    idx = pl->unk1C;
    pl->unk20 = chr = GwPlayer[idx].chr;
    pl->unk1E = GwPlayer[idx].pad;
    pl->unk22 = GwPlayer[idx].stat & 1;
    pl->unk24 = GwPlayer[idx].cpu_difficulty;
    pl->unk26 = 0;
    pl->unk28 = 0;
    pl->unk2A = 0;
    pl->unk2C = -1;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, dir, file, idx, 0x2A9, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x33), 1, 0x3C);
    func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, 0x3A), 1, 0x3C);
    if (chr != 5) {
        r = rand8() & 1;
        msg = &D_8010D90C_slot_synch[r];
        func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, *msg), 1, 0x78);
        pl->unk18 = D_8010D8EC_slot_synch[chr] | *msg;
    } else {
        func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, D_8010D90C_slot_synch[1]), 1, 0x78);
        pl->unk18 = D_8010D8EC_slot_synch[chr] | D_8010D90C_slot_synch[1];
    }
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, D_8010D90C_slot_synch[2]), 1, 0x78);
    func_800E5690_minigame(obj, 0);
    func_800E149C_minigame(obj, 0, 2);
    pl->unk04 = -1;
    pl->unk0A = 0;
    pl->unk08 = 0;
    pl->unk0C = pl->unk10 = pl->unk14 = 0.0f;
    obj->func = func_80106E8C_slot_synch;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106560_slot_synch);
#endif

void func_80106878_slot_synch(omObjData* obj) {
    SsTeam* t;
    SsReel* reel;
    func_800E1BA8_minigame_ObjData* w0;
    func_800E1BA8_minigame_ObjData* w1;
    s16 a;
    s16 b;

    t = func_8010C428_slot_synch(obj);
    switch (t->unk12) {
    case 0:
        if (func_800E6E8C_minigame() == 2) {
            func_801089F8_slot_synch(t->unk08->unk00);
            func_801089F8_slot_synch(t->unk0C->unk00);
            reel = &D_8010DF7C_slot_synch[t->unk08->unk00];
            if (reel->unk20 != -1) {
                HuAudFXStop((s16)reel->unk20);
                reel->unk20 = -1;
            }
            reel->unk20 = HuAudFXPlay(t->unk10 == 0 ? 0x38F : 0x395);
            t->unk14 = 0;
            t->unk12 = 1;
        } else if (func_800E6E8C_minigame() == 3 || func_800E6E8C_minigame() == 4) {
            func_80108CD0_slot_synch(t->unk08->unk00);
            func_80108CD0_slot_synch(t->unk0C->unk00);
        }
        break;
    case 1:
        if (func_800E6E8C_minigame() != 2) {
            t->unk1C = 0;
            t->unk14 = 0;
            t->unk12 = 0;
        }
        if (t->unk14 >= 30) {
            t->unk1C = 1;
            t->unk14 = 0;
            t->unk12 = 2;
        }
        break;
    case 2:
        if (func_80108A7C_slot_synch(t->unk08->unk00) != 0 && func_80108A7C_slot_synch(t->unk0C->unk00) != 0) {
            if (func_800E6E8C_minigame() == 2) {
                reel = &D_8010DF7C_slot_synch[t->unk08->unk00];
                if (reel->unk20 != -1) {
                    HuAudFXStop((s16)reel->unk20);
                    reel->unk20 = -1;
                }
            }
            t->unk1C = 0;
            a = func_80108AA8_slot_synch(t->unk08->unk00);
            b = func_80108AA8_slot_synch(t->unk0C->unk00);
            if (func_800E6E8C_minigame() == 3) {
                func_80108CD0_slot_synch(t->unk08->unk00);
                func_80108CD0_slot_synch(t->unk0C->unk00);
            }
            if (a == b) {
                t->unk1A = a;
            } else {
                t->unk1A = 4;
            }
            t->unk18 = func_80109FA4_slot_synch(t->unk10, t->unk1A);
            t->unk14 = 0;
            t->unk12 = 3;
        } else if (func_800E6E8C_minigame() != 2) {
            t->unk1C = 0;
            w0 = t->unk00->data;
            w1 = t->unk04->data;
            if (w0->unk38 == 1000.0f && w1->unk38 == 1000.0f) {
                if (func_800E6E8C_minigame() == 3) {
                    func_80108CD0_slot_synch(t->unk08->unk00);
                    func_80108CD0_slot_synch(t->unk0C->unk00);
                }
                t->unk14 = 0;
                t->unk12 = 0;
            }
        }
        break;
    case 3:
        if (func_8010A178_slot_synch(t->unk18) != 0) {
            if (t->unk1A != 4) {
                func_8010800C_slot_synch(t->unk1A, t->unk10);
            }
            if (t->unk1A != 3 && t->unk1A != 4) {
                func_800E5690_minigame(t->unk00, 0x26);
                func_800E5690_minigame(t->unk04, 0x26);
            } else {
                func_800E5690_minigame(t->unk00, 0x27);
                func_800E5690_minigame(t->unk04, 0x27);
            }
            t->unk14 = 0;
            t->unk12 = 4;
        }
        break;
    case 4:
        if (t->unk14 >= 30.0f) {
            func_800E5690_minigame(t->unk00, 0);
            func_800E5690_minigame(t->unk04, 0);
            t->unk14 = 0;
            t->unk12 = 0;
        }
        break;
    }
    t->unk14++;
    if (t->unk16 >= 100) {
        t->unk16 = 99;
    } else if (t->unk16 < 0) {
        t->unk16 = 0;
    }
    func_8010AA9C_slot_synch(t->unk10, t->unk16);
}

void func_80106CCC_slot_synch(s16 team, s16 add) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];
    t->unk16 += add;
}

s16 func_80106CF0_slot_synch(s16 team) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];
    return t->unk12;
}

void func_80106D0C_slot_synch(s16 team, s16 kind) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];

    switch (kind) {
    case 1:
        omVibrate(t->unk08->unk1C, 5, 0, 5);
        omVibrate(t->unk0C->unk1C, 5, 0, 5);
        break;
    case 2:
        omVibrate(t->unk08->unk1C, 2, 3, 10);
        omVibrate(t->unk0C->unk1C, 2, 3, 10);
        break;
    case 3:
        omVibrate(t->unk08->unk1C, 10, 0, 10);
        omVibrate(t->unk0C->unk1C, 10, 0, 10);
        break;
    case 4:
        omVibrate(t->unk08->unk1C, 2, 2, 20);
        omVibrate(t->unk0C->unk1C, 2, 2, 20);
        break;
    case 5:
        omVibrate(t->unk08->unk1C, 20, 0, 20);
        omVibrate(t->unk0C->unk1C, 20, 0, 20);
        break;
    default:
        omVibrate(t->unk08->unk1C, 30, 0, 30);
        omVibrate(t->unk0C->unk1C, 30, 0, 30);
        break;
    }
}

#ifdef NON_MATCHING
void func_80106E8C_slot_synch(omObjData* obj) {
    SsPlayer* pl;
    SsTeam* t;
    u16 btn;
    u16 btn2;
    s8 sx;
    s8 sy;

    pl = func_8010C428_slot_synch(obj);
    t = &D_8010DF5C_slot_synch[pl->unk02];
    if (pl->unk22 != 0) {
        func_80107108_slot_synch(obj);
    }
    if (pl->unk04 != -1) {
        switch (pl->unk04) {
        case 0:
            func_800E5690_minigame(obj, 0xD);
            func_80017790_main(obj->model[0], 2, pl->unk20, D_8010D870_slot_synch[pl->unk20]);
            func_80045F1C_main(pl->unk18, -1, pl->unk1C);
            break;
        case 1:
            func_800E5690_minigame(obj, 0xE);
            func_80017790_main(obj->model[0], 2, pl->unk20, D_8010D890_slot_synch[pl->unk20]);
            break;
        }
        pl->unk04 = -1;
    }
    pl->unk0C = obj->trans.x;
    pl->unk10 = obj->trans.y;
    pl->unk14 = obj->trans.z;
    btn2 = 0;
    if ((t->unk1C == 0) | ((func_80108A7C_slot_synch(pl->unk00) == 0) ^ 1)) {
        btn = D_800CDA7C_main[pl->unk1E];
        btn2 = D_800D5558_main[pl->unk1E];
        D_800CDA7C_main[pl->unk1E] = 0;
        D_800D5558_main[pl->unk1E] = 0;
    } else {
        btn = 0;
    }
    sx = (u8)D_800CBB6E_main[pl->unk1E];
    sy = (u8)D_800D20A1_main[pl->unk1E];
    D_800CBB6E_main[pl->unk1E] = 0;
    D_800D20A1_main[pl->unk1E] = 0;
    func_800DDD94_minigame(obj);
    D_800CBB6E_main[pl->unk1E] = sx;
    D_800D20A1_main[pl->unk1E] = sy;
    if (t->unk1C == 0) {
        D_800CDA7C_main[pl->unk1E] = btn;
        D_800D5558_main[pl->unk1E] = btn2;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    pl->unk0A++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106E8C_slot_synch);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107108_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801075D4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107794_slot_synch);

void func_80107A80_slot_synch(omObjData* obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107A88_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107B00_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107BAC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107D54_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010800C_slot_synch);

void func_80108238_slot_synch(void) {
    SsReel* reel;
    s16 mdl1;
    s16 mdl0;
    s16 i;
    s32 m;

    mdl1 = -1;
    mdl0 = -1;
    reel = D_8010DF7C_slot_synch = HuMemAllocTag(sizeof(SsReel) * 4, 31000);
    memset(reel, 0, sizeof(SsReel) * 4);
    for (i = 0; i < 4; i++, reel++) {
        reel->unk03 = D_8010D9C8_slot_synch[i];
        if (reel->unk03 == 0) {
            m = mdl0;
            if (m == -1) {
                reel->unk00 = func_8000B108_main(0x350000, 0xB9);
                mdl0 = reel->unk00;
            } else {
                reel->unk00 = Hu3DModelLink(m);
            }
        } else {
            m = mdl1;
            if (m != -1) {
                reel->unk00 = Hu3DModelLink(m);
            } else {
                reel->unk00 = func_8000B108_main(0x350001, 0xB9);
                mdl1 = reel->unk00;
            }
        }
        reel->unk02 = i;
        reel->unk04 = i % 2;
        reel->unk0A = 0;
        reel->unk05 = 0;
        reel->unk06 = 0;
        reel->unk0C = 0;
        reel->unk10 = 0.0f;
        reel->unk08 = -1;
        reel->unk14 = 0.0f;
        reel->unk18 = 0.5f;
        reel->unk1C = 14.0f;
        reel->unk20 = -1;
        reel->unk24.x = D_8010D7F0_slot_synch[i].x;
        reel->unk24.z = D_8010D7F0_slot_synch[i].z;
        reel->unk24.y = 280.0f;
        reel->unk30.x = 0.0f;
        reel->unk30.y = reel->unk30.z = 0.0f;
    }
    omAddObj(0x1A, 0, 0, -1, func_80108428_slot_synch);
}

void func_80108428_slot_synch(omObjData* obj) {
    SsReel* reel;
    Vec pos;
    f32 a;
    s32 i;
    s32 j;

    reel = D_8010DF7C_slot_synch;
    i = 0;
    do {
        switch (reel->unk0C) {
        case 0:
        case 2:
        case 5:
            break;
        case 1:
            reel->unk14 += reel->unk18;
            if (reel->unk14 >= reel->unk1C) {
                reel->unk14 = reel->unk1C;
                reel->unk0C = 2;
                reel->unk0A = 0;
            }
            break;
        case 3:
            reel->unk24.y += reel->unk10;
            reel->unk10 -= 6.0;
            if (reel->unk24.y <= 280.0) {
                reel->unk24.y = 280.0f;
                reel->unk0A = 0;
                reel->unk0C = 0;
            }
            break;
        case 4:
            func_8001C258_main(reel->unk00, 4, 4);
            pos.x = reel->unk24.x;
            pos.y = reel->unk24.y;
            pos.z = reel->unk24.z;
            func_8010AD68_slot_synch(&pos, 0, 0, 1.0f, &D_8010D86C_slot_synch);
            reel->unk0C = 5;
            break;
        }
        a = reel->unk30.x + 45.0f;
        if (a > 360.0f) {
            a -= 360.0f;
        } else if (a < 0.0f) {
            a += 360.0f;
        }
        reel->unk05 = a / 90.0f;
        if (reel->unk05 >= 4) {
            reel->unk05 -= 4;
        }
        reel->unk06 = func_80108C88_slot_synch(reel->unk02, reel->unk05);
        reel->unk30.x += reel->unk14;
        if (reel->unk30.x >= 360.0f) {
            reel->unk30.x -= 360.0f;
        }
        if (func_80108848_slot_synch(reel->unk02) != -1 && (reel->unk0C == 1 || reel->unk0C == 2)) {
            func_8004AC98_main(0x38E, i);
            if (reel->unk08 == -1) {
                reel->unk14 = 0.0f;
                reel->unk30.x = D_8010D840_slot_synch[reel->unk05];
            } else {
                reel->unk14 = 0.0f;
                for (j = 0; j < 4; j++) {
                    reel->unk30.x = j * 90;
                    a = reel->unk30.x + 45.0f;
                    if (a > 360.0f) {
                        a -= 360.0f;
                    } else if (a < 0.0f) {
                        a += 360.0f;
                    }
                    reel->unk05 = a / 90.0f;
                    if (reel->unk05 >= 4) {
                        reel->unk05 -= 4;
                    }
                    reel->unk06 = func_80108C88_slot_synch(reel->unk02, reel->unk05);
                    if (reel->unk06 == reel->unk08) {
                        break;
                    }
                }
            }
            reel->unk24.y = 340.0f;
            reel->unk10 = 0.0f;
            reel->unk08 = -1;
            reel->unk0A = 0;
            reel->unk0C = 3;
        }
        i++;
        Hu3DModelPosSet(reel->unk00, reel->unk24.x, reel->unk24.y, reel->unk24.z);
        Hu3DModelRotSet(reel->unk00, reel->unk30.x, reel->unk30.y, reel->unk30.z);
        reel->unk0A++;
        reel++;
    } while (i < 4);
}

s16 func_80108848_slot_synch(s16 idx) {
    SsReel* reel;
    omObjData* o;
    func_800E1BA8_minigame_ObjData* w;
    SsPlayer* pl;
    f32 h;
    s32 i;

    reel = &D_8010DF7C_slot_synch[idx];
    for (i = 0; i < 4; i++) {
        o = D_800EC598_minigame[i];
        w = o->data;
        pl = func_8010C428_slot_synch(o);
        if (fabs(o->trans.x - reel->unk24.x) > 50.0 || fabs(o->trans.x - reel->unk24.x) > 50.0) {
            continue;
        }
        if (reel->unk0C == 1 || reel->unk0C == 2) {
            h = D_8010D9D0_slot_synch[pl->unk20];
        } else {
            h = D_8010D9D0_slot_synch[pl->unk20] + 50.0;
        }
        if (reel->unk24.y <= h + o->trans.y && h + pl->unk10 <= reel->unk24.y) {
            o->trans.y = reel->unk24.y - D_8010D9D0_slot_synch[pl->unk20] * 1.1;
            w->unk38 = 0.0f;
            return i;
        }
    }
    return -1;
}

#ifdef NON_MATCHING
void func_801089F8_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];

    if (func_80108A7C_slot_synch(idx) != 0) {
        reel->unk1C = func_8010C384_slot_synch(D_8010DF50_slot_synch / 900.0f, 30.0f, 14.0f);
        reel->unk0C = 1;
        reel->unk0A = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801089F8_slot_synch);
#endif

s16 func_80108A7C_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    return reel->unk0C == 0;
}

#ifdef NON_MATCHING
s16 func_80108AA8_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    f32 a = reel->unk30.x + 45.0f;

    if (a > 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    return func_80108C88_slot_synch(idx, a / 90.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108AA8_slot_synch);
#endif

#ifdef NON_MATCHING
s16 func_80108B74_slot_synch(s16 idx, s16 steps) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    f32 a = steps * reel->unk14 + reel->unk30.x + 45.0f;

    while (a > 360.0f) {
        a -= 360.0f;
    }
    while (a < 0.0f) {
        a += 360.0f;
    }
    return func_80108C88_slot_synch(idx, a / 90.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108B74_slot_synch);
#endif

s16 func_80108C88_slot_synch(s16 idx, s16 face) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    return D_8010D854_slot_synch[reel->unk03][face];
}

void func_80108CD0_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];

    if (reel->unk0C != 4 && reel->unk0C != 5) {
        reel->unk0C = 4;
        reel->unk0A = 0;
    }
}

void func_80108D14_slot_synch(s16 idx, s16 sym) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    reel->unk08 = sym;
}

void func_80108D3C_slot_synch(void) {
    s16 ys[256];
    SsBody* b;
    HmfData* hmf;
    Vtx* v;
    SsRow* row;
    s16 n;
    s16 i;
    s16 j;
    s16 k;
    s16 tmp;

    b = D_8010DF80_slot_synch = HuMemAllocTag(sizeof(SsBody) * 2, 31000);
    memset(b, 0, sizeof(SsBody) * 2);
    for (k = 0; k < 2; k++, b++) {
        b->unk00 = func_8000B108_main(0x350002, 0xB9);
        Hu3DModelPosSet(b->unk00, D_8010D820_slot_synch[k].x, D_8010D820_slot_synch[k].y, D_8010D820_slot_synch[k].z);
        Hu3DModelScaleSet(b->unk00, 1.0f, 0.85f, 1.0f);
        func_8001C954_main(b->unk00);
        hmf = HmfModelData[b->unk00].hmf;
        b->unk02 = k;
        b->unk04 = 0;
        b->unk08 = -75.0f;
        b->unk0C = 75.0f;
        b->unk10 = 0.75f;
        b->unk14 = 0.0f;
        if (k == 0) {
            v = hmf->unk40;
            n = 0;
            for (i = 0; i < SS_HMF_VTXNUM(hmf); i++, v++) {
                for (j = 0; j < n; j++) {
                    if (ys[j] == v->v.ob[1]) {
                        break;
                    }
                }
                if (j >= n) {
                    ys[j] = v->v.ob[1];
                    n++;
                }
                if (n >= 256) {
                    osSyncPrintf("VTX OVER!! \n");
                }
            }
            for (i = 0; i < n - 1; i++) {
                for (j = i + 1; j < n; j++) {
                    if (ys[i] < ys[j]) {
                        tmp = ys[i];
                        ys[i] = ys[j];
                        ys[j] = tmp;
                    }
                }
            }
            b->unk18 = n;
            row = b->unk1C = HuMemAllocTag(n * sizeof(SsRow), 31000);
            for (i = 0; i < b->unk18; i++, row++) {
                row->unk90 = ys[i];
                row->unk92 = 0;
            }
            v = hmf->unk40;
            for (i = 0; i < SS_HMF_VTXNUM(hmf); i++, v++) {
                for (j = 0; j < b->unk18; j++) {
                    row = &b->unk1C[j];
                    if (v->v.ob[1] == row->unk90) {
                        row->unk00[row->unk92] = i;
                        row->unk92++;
                        break;
                    }
                    if (row->unk92 >= 72) {
                        osSyncPrintf("VTX H OVER!! \n");
                    }
                }
            }
        } else {
            b->unk18 = D_8010DF80_slot_synch->unk18;
            b->unk1C = D_8010DF80_slot_synch->unk1C;
        }
    }
    omSetStatBit(omAddObj(0x1B, 0, 0, -1, func_801091D8_slot_synch), 0xA0);
}

void func_801091D8_slot_synch(omObjData* obj) {
    SsBody* b;
    s32 i;

    b = D_8010DF80_slot_synch;
    for (i = 0; i < 2; i++, b++) {
        if (func_80049F98_main() + D_800D6A90_main == 0 && b->unk04 == 1) {
            b->unk08 += b->unk14;
            if (b->unk08 >= 359.999990463256836 || b->unk08 <= -120.000004768371582) {
                b->unk14 = 0.0f;
                b->unk04 = 0;
            }
        }
        func_801092B8_slot_synch(b);
    }
}

void func_801092B8_slot_synch(SsBody* b) {
    SsRow* row;
    HmfData* hmf;
    Vtx* base;
    Vtx* cur;
    f32 d;
    f32 s;
    s32 i;
    s32 j;

    row = b->unk1C;
    hmf = HmfModelData[b->unk00].hmf;
    base = hmf->unk40;
    cur = hmf->unk44[D_800D2008_main];
    for (i = 0; i < b->unk18; i++, row++) {
        d = fabsf(b->unk08 - row->unk90 * 0.85f);
        if (b->unk0C < d) {
            s = 0.0f;
        } else {
            s = 1.0f - d / b->unk0C;
        }
        if (s >= 1.0f) {
            s = 1.0f;
        } else if (s <= 0.0f) {
            s = 0.0f;
        }
        if (s != 0.0f) {
            s = s * b->unk10 + 1.0f;
            for (j = 0; j < row->unk92; j++) {
                cur[row->unk00[j]].v.ob[0] = base[row->unk00[j]].v.ob[0] * s;
                cur[row->unk00[j]].v.ob[2] = base[row->unk00[j]].v.ob[2] * s;
            }
        } else {
            for (j = 0; j < row->unk92; j++) {
                cur[row->unk00[j]].v = base[row->unk00[j]].v;
            }
        }
    }
}

void func_801094E0_slot_synch(s16 idx, f32 height, f32 speed) {
    SsBody* b = &D_8010DF80_slot_synch[idx];

    b->unk04 = 1;
    b->unk08 = height;
    b->unk14 = speed;
}

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
