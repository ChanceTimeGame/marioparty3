#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// bowloons A: Bobbing Bow-loons (1 player: drop the hook on a bobbing balloon to win its prize)

/* omObjData::data of the player on the boat (D_80109B1C) */
typedef struct BlPlayer {
    /* 0x00 */ s32 unk00; /* 1: bobbing */
    /* 0x04 */ f32 unk04; /* x */
    /* 0x08 */ f32 unk08; /* y */
    /* 0x0C */ f32 unk0C; /* z */
    /* 0x10 */ f32 unk10; /* scale */
    /* 0x14 */ f32 unk14; /* bob angle */
} BlPlayer; /* size 0x18 */

/* omObjData::data of the scrolling water (D_80109B28): 8 models */
typedef struct BlWater {
    /* 0x00 */ f32 unk00[8]; /* x */
    /* 0x20 */ f32 unk20[8]; /* y */
    /* 0x40 */ f32 unk40[8]; /* z */
} BlWater; /* size 0x60 */

/* omObjData::data of the balloons (D_80109B2C): models 0-4 balloons, 5-9 their second part */
typedef struct BlBalloon {
    /* 0x00 */ s32 unk00[5]; /* 1: bobbing, 2: flying away */
    /* 0x14 */ f32 unk14[5]; /* x */
    /* 0x28 */ f32 unk28[5]; /* y */
    /* 0x3C */ f32 unk3C[5]; /* z */
    /* 0x50 */ f32 unk50[5]; /* bob angle */
    /* 0x64 */ f32 unk64[5]; /* bob speed */
    /* 0x78 */ f32 unk78;    /* fly-away speed */
} BlBalloon; /* size 0x7C */

/* omObjData::data of the strings (D_80109B34): 0-4 balloons, 5 the player's */
typedef struct BlString {
    /* 0x00 */ f32 unk00[7]; /* x */
    /* 0x1C */ f32 unk1C[7]; /* y */
    /* 0x38 */ f32 unk38[7]; /* z */
} BlString; /* size 0x54 */

/* omObjData::data of the prizes under the balloons (D_80109B38) */
typedef struct BlPrize {
    /* 0x00 */ f32 unk00[5]; /* x */
    /* 0x14 */ f32 unk14[5]; /* y */
    /* 0x28 */ f32 unk28[5]; /* z */
    /* 0x3C */ s32 unk3C[5]; /* 1: under its balloon, 2: flying to the player */
    /* 0x50 */ f32 unk50;    /* wobble angle */
    /* 0x54 */ f32 unk54;    /* flying x */
    /* 0x58 */ f32 unk58;    /* flying y */
} BlPrize; /* size 0x5C */

/* omObjData::data of the hook (D_80109B30) */
typedef struct BlHook {
    /* 0x00 */ s32 unk00; /* 1: flying */
    /* 0x04 */ f32 unk04; /* x */
    /* 0x08 */ f32 unk08; /* y */
    /* 0x0C */ f32 unk0C; /* z */
    /* 0x10 */ f32 unk10; /* z rotation */
} BlHook; /* size 0x14 */

/* omObjData::data of the pop effect (D_80109B5C) */
typedef struct BlPop {
    /* 0x00 */ f32 unk00; /* x */
    /* 0x04 */ f32 unk04; /* y */
    /* 0x08 */ f32 unk08; /* z */
    /* 0x0C */ s32 unk0C; /* 1: growing */
    /* 0x10 */ f32 unk10; /* scale */
    /* 0x14 */ s32 unk14; /* frames */
    /* 0x18 */ char unk18[4];
} BlPop; /* size 0x1C */

/* omObjData::data of the burst balloons (D_80109B60) */
typedef struct BlBurst {
    /* 0x00 */ f32 unk00[5]; /* x */
    /* 0x14 */ f32 unk14[5]; /* y */
    /* 0x28 */ f32 unk28[5]; /* z */
} BlBurst; /* size 0x3C */

/* omObjData::data of the host (D_80109B64) */
typedef struct BlHost {
    /* 0x00 */ f32 unk00; /* y */
    /* 0x04 */ f32 unk04; /* head angle */
} BlHost; /* size 8 */

/* The minigame control block (as ovl_19's IrCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct BlCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result message */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} BlCtrl;

/* An entry of D_800CD1DC_main (src/esprite.c's D_800CD1DC_main_Struct) */
typedef struct BlEsprite {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} BlEsprite; /* size 0x24 */

/* An entry of D_800CBB60_main (minigame BD210.c's MgSprModel) */
typedef struct BlSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8* unk20; /* src/14EA0.c unk_800ECDE0: key-frame list */
} BlSprModel; /* size 0x24 */

/* What func_8001D33C_main returns (a model's named object) */
typedef struct BlHmfObj {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ char unk14[0x20];
    /* 0x34 */ f32 unk34;
} BlHmfObj;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_8004BCE4_main(void* work);
void func_80017358_main(s16 arg0, char* arg1, s16 arg2, char* arg3);
void func_8004AD70_main(void);
void func_8004AE00_main(s16, s16);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
void func_8001E500_main(s16 arg0, char* arg1, char* arg2);
void* func_8001D33C_main(s16 model, char* name);
void func_8002FD8C_main(s16 arg0, s16 arg1, char* arg2, s16 arg3, s16 arg4);
void GMesPosSet(s16 mesId, f32 x, f32 y);
f64 fabs(f64);
omObjData* func_80045ED0_main(u32 arg0);

extern BlEsprite* D_800CD1DC_main;
extern BlSprModel* D_800CBB60_main;
extern D_800CCF58_main_Struct* D_800CCF58_main;
extern u16 D_800A11D0_main[6];
extern u16 D_800A11DC_main[5]; /* CPU target odds, percent */
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];

// minigame
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
extern s32 D_800EBEB0_minigame[];
extern s32 D_800EBE24_minigame;

// this overlay
void func_80105AE8_bobbing_bow_loons(void);
void func_80105B64_bobbing_bow_loons(void);
void func_80105D04_bobbing_bow_loons(void);
void func_80106260_bobbing_bow_loons(omObjData* obj);
void func_801063F8_bobbing_bow_loons(void);
void func_801064C0_bobbing_bow_loons(void);
void func_801065C8_bobbing_bow_loons(void);
void func_801068B0_bobbing_bow_loons(omObjData* obj);
void func_80106A00_bobbing_bow_loons(omObjData* obj);
void func_80106A34_bobbing_bow_loons(omObjData* obj);
void func_80106CC0_bobbing_bow_loons(void);
void func_80106F44_bobbing_bow_loons(omObjData* obj);
void func_80107130_bobbing_bow_loons(void);
s32 func_80107174_bobbing_bow_loons(void);
void func_8010728C_bobbing_bow_loons(void);
void func_80107368_bobbing_bow_loons(omObjData* obj);
void func_801074CC_bobbing_bow_loons(void);
void func_80107830_bobbing_bow_loons(omObjData* obj);
void func_801079E8_bobbing_bow_loons(s32 idx);
void func_80107A7C_bobbing_bow_loons(void);
void func_80107C48_bobbing_bow_loons(void);
void func_80107C74_bobbing_bow_loons(void);
void func_80107D4C_bobbing_bow_loons(void);
void func_80107D78_bobbing_bow_loons(void);
void func_80107E68_bobbing_bow_loons(void);
void func_80107E94_bobbing_bow_loons(void);
void func_80107F68_bobbing_bow_loons(void);
void func_80107F94_bobbing_bow_loons(void);
void func_8010805C_bobbing_bow_loons(void);
void func_8010817C_bobbing_bow_loons(omObjData* obj);
void func_8010829C_bobbing_bow_loons(void);
void func_80108328_bobbing_bow_loons(void);
void func_80108354_bobbing_bow_loons(void);
void func_80108894_bobbing_bow_loons(void);
void func_801088C0_bobbing_bow_loons(void);
void func_80108C18_bobbing_bow_loons(s32 arg0);
void func_80108E5C_bobbing_bow_loons(omObjData* obj);
void func_80108F2C_bobbing_bow_loons(f32 x, f32 y);
void func_80109044_bobbing_bow_loons(void);
void func_801090EC_bobbing_bow_loons(omObjData* obj);
void func_801091FC_bobbing_bow_loons(void);
void func_8010934C_bobbing_bow_loons(void);
void func_801093DC_bobbing_bow_loons(void);
void func_801094B0_bobbing_bow_loons(omObjData* obj);
void func_80109568_bobbing_bow_loons(void);
void func_80109594_bobbing_bow_loons(void);
void func_80109680_bobbing_bow_loons(void);
void func_801096E8_bobbing_bow_loons(void);

/* .bss (ovl_3D_bss) */
extern u8 D_80109B04_bobbing_bow_loons;  /* 0 missed, 2 time up, 3 drop the hook, 4 dropped */
extern s16 D_80109B06_bobbing_bow_loons;
extern s16 D_80109B08_bobbing_bow_loons; /* prize sparkle effect */
extern s32 D_80109B0C_bobbing_bow_loons; /* the playing player */
extern s32 D_80109B10_bobbing_bow_loons; /* won prize, -1 none */
extern s32 D_80109B14_bobbing_bow_loons; /* CPU target balloon */
extern s16 D_80109B18_bobbing_bow_loons; /* camera */
extern omObjData* D_80109B1C_bobbing_bow_loons;
extern s16 D_80109B20_bobbing_bow_loons[2];
extern omObjData* D_80109B28_bobbing_bow_loons;
extern omObjData* D_80109B2C_bobbing_bow_loons;
extern omObjData* D_80109B30_bobbing_bow_loons;
extern omObjData* D_80109B34_bobbing_bow_loons;
extern omObjData* D_80109B38_bobbing_bow_loons;
extern s32 D_80109B40_bobbing_bow_loons[5]; /* prize kind under each balloon */
extern s32 D_80109B54_bobbing_bow_loons;    /* hooked balloon */
extern omObjData* D_80109B58_bobbing_bow_loons;
extern omObjData* D_80109B5C_bobbing_bow_loons;
extern omObjData* D_80109B60_bobbing_bow_loons;
extern omObjData* D_80109B64_bobbing_bow_loons;

/* .data (0x80109720-0x801097D0). Defined before the functions: retail emits the hand names in
   .rodata ahead of every function's constants. */
BlCtrl D_80109720_bobbing_bow_loons = {
    0, 3, 2, 0, 0, 0, 5, 0, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0, 0, 0, 0 }, 30, 300, -1, 90, 135,
};
f32 D_80109748_bobbing_bow_loons[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_80109768_bobbing_bow_loons[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
char* D_80109788_bobbing_bow_loons[8] = {
    "migi-te3_2_1",       "c001_000-migi-te2_3", "C002_000b-bmerge16", "c003_000-bmerge1_8",
    "Luigi1-migi-te1_1", "c005_000-bmerge6",    "c001_000-migi-te2_3", "C002_000b-bmerge16",
};
s32 D_801097A8_bobbing_bow_loons[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

void func_801059A0_bobbing_bow_loons(void) {
    omInitObjMan(30, 10);
    Hu3DAnimInit(16);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_80105AE8_bobbing_bow_loons();
    func_8004A208_main();
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_80109720_bobbing_bow_loons);
    WipeCreateIn(0xFF, 16);
    func_80105B64_bobbing_bow_loons();
    func_80105D04_bobbing_bow_loons();
    func_801065C8_bobbing_bow_loons();
    func_80106CC0_bobbing_bow_loons();
    func_801074CC_bobbing_bow_loons();
    func_801093DC_bobbing_bow_loons();
    D_80109B06_bobbing_bow_loons = 0;
    D_800EBE24_minigame = 0;
    D_80109B04_bobbing_bow_loons = 0;
    D_80109B10_bobbing_bow_loons = -1;
    omAddObj(0x50, 0, 0, -1, func_80106A34_bobbing_bow_loons);
    func_8010728C_bobbing_bow_loons();
    func_8010805C_bobbing_bow_loons();
    func_80109044_bobbing_bow_loons();
    func_80109680_bobbing_bow_loons();
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    Center.z = 0.0f;
}

void func_80105AE8_bobbing_bow_loons(void) {
    func_8000B5F0_main(1);
    D_80109B18_bobbing_bow_loons = func_8000B638_main();
    Hu3DCamSetPerspective(D_80109B18_bobbing_bow_loons, 30.0f, 80.0f, 8000.0f);
    CZoom = 500.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
}

/* The background sprite and the boat. */
void func_80105B64_bobbing_bow_loons(void) {
    Vec eye;
    Vec at;
    omObjData* obj;
    s16 sprId;

    sprId = InitEspriteSlot(func_8000B838_main(0x5E0000), 0, 1);
    func_8000BB94_main(sprId);
    eye.x = 0.0f;
    eye.y = 1.0f;
    eye.z = 1500.0f;
    at.x = 0.0f;
    at.y = 0.0f;
    at.z = 0.0f;
    func_8004B760_main(100, D_800CD1DC_main[sprId].unk04, func_8004BCE4_main, 30.0f, &eye, &at);
    obj = omAddObj(0x50, 3, 0, -1, NULL);
    obj->model[0] = func_8000B108_main(0x5E0003, 0x6D9);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = func_8000B108_main(0x5E0004, 0x6D9);
    omSetTra(obj, -550.0f, -400.0f, 10.0f);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    Hu3DModelPosSet(obj->model[1], 400.0f, -400.0f, 4.0f);
    Hu3DModelPosSet(obj->model[2], 340.0f, -50.0f, -100.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 2.0f, 1.0f);
}

/* NON_MATCHING: masked 0 with func_80017AD8_main returning s16 (header says u8: an extra andi 0xFF) */
#ifdef NON_MATCHING
/* The player's character, its hand and its balloon. */
void func_80105D04_bobbing_bow_loons(void) {
    s32 sp18[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 sp38[8] = { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0 };
    s32 sp58[8][3] = {
        { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 }, { 0x6E, 0x6F, 0x29 },
    };
    s32 spB8[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    s32 spD8[8] = { 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C };
    s32 spF8[8] = { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B };
    s32 sp118[8] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C };
    omObjData* obj;
    BlPlayer* work;
    s32 i;
    s16 chr;
    s32 dir;
    s32 file;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_80109B0C_bobbing_bow_loons = i;
            break;
        }
    }
    obj = omAddObj(0x50, 4, 10, -1, func_80106260_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BlPlayer), 31000);
    D_80109B1C_bobbing_bow_loons = obj;
    work = obj->data;
    work->unk00 = 1;
    work->unk10 = 1.0f;
    work->unk00 = 1;
    chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;
    dir = D_80109768_bobbing_bow_loons[chr] << 16;
    file = dir | sp38[chr];
    obj->model[0] = func_8000B108_main(file, 0x6A9);
    obj->model[2] = func_8000B108_main(spD8[chr] | 0x5E0000, 0x6BD);
    obj->model[3] = func_8000B108_main(file, 0x6BD);
    work->unk04 = 400.0f;
    work->unk08 = 0.0f;
    work->unk0C = 80.0f;
    work->unk14 = 0.0f;
    omSetTra(obj, work->unk04, work->unk08, work->unk0C);
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 270.0f, 0.0f);
    D_80109B20_bobbing_bow_loons[0] =
        func_80017790_main(obj->model[0], 1, (s16)D_801097A8_bobbing_bow_loons[chr], dir | spF8[chr]);
    D_80109B20_bobbing_bow_loons[1] = func_80017AD8_main(dir | sp118[chr]);
    func_8001C514_main(obj->model[0]);
    /* i == 3 reads the next character's row (retail) */
    for (i = 0; i < 4; i++) {
        func_8000B460_main(obj, i, func_80017BB8_main(chr, (s16)sp58[chr][i]));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_80017358_main(obj->model[2], D_80109788_bobbing_bow_loons[chr], obj->model[0],
                       D_80109788_bobbing_bow_loons[chr]);
    obj->model[1] = func_8000B108_main(spB8[chr] | 0x5E0000, 0x6B9);
    Hu3DModelPosSet(obj->model[1],
                    work->unk04 + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr],
                    work->unk08 + 150.0f, work->unk0C + 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.5f, 1.5f);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109844_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109864_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109884_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801098E4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109904_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109924_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109944_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80105D04_bobbing_bow_loons);
#endif

void func_80106260_bobbing_bow_loons(omObjData* obj) {
    BlPlayer* work = obj->data;
    f32 s;

    omSetSca(obj, work->unk10, work->unk10, work->unk10);
    omSetTra(obj, work->unk04, work->unk08 - 50.0f, work->unk0C);
    Hu3DModelPosSet(obj->model[1],
                    work->unk04 + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr],
                    work->unk08 + 150.0f, work->unk0C + 0.0f);
    Hu3DModelPosSet(obj->model[3], work->unk04, work->unk08 - 50.0f, work->unk0C + 2.0f);
    s = work->unk10 * 1.5f;
    Hu3DModelScaleSet(obj->model[1], s, s, s);
    if (work->unk00 & 1) {
        work->unk08 = sindf(work->unk14) * 10.0f;
        work->unk14 += 10.0f;
        if (work->unk14 >= 360.0f) {
            work->unk14 -= 360.0f;
        }
    }
}

/* The player wins: happy motion and the win jingle. */
void func_801063F8_bobbing_bow_loons(void) {
    u8 chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;

    func_8001C624_main(D_80109B1C_bobbing_bow_loons->model[0],
                       HmfModelData[D_80109B1C_bobbing_bow_loons->motion[1]].unk02, 0, 10, 0);
    func_80017954_main(D_80109B1C_bobbing_bow_loons->model[0], 1, (s16)D_801097A8_bobbing_bow_loons[chr],
                       D_80109B20_bobbing_bow_loons[1]);
    func_80045ED0_main((D_80109768_bobbing_bow_loons[chr] << 16) | 0x6F);
}

/* The player loses his balloon. */
void func_801064C0_bobbing_bow_loons(void) {
    u8 chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;

    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[0], 4, 4);
    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[3], 4, 0);
    func_8001C624_main(D_80109B1C_bobbing_bow_loons->model[3],
                       HmfModelData[D_80109B1C_bobbing_bow_loons->motion[2]].unk02, 0, 10, 0);
    func_8001C814_main(D_80109B1C_bobbing_bow_loons->model[3], 2, 2);
    func_80017358_main(D_80109B1C_bobbing_bow_loons->model[3], D_80109788_bobbing_bow_loons[chr],
                       D_80109B1C_bobbing_bow_loons->model[0], D_80109788_bobbing_bow_loons[chr]);
    func_8010934C_bobbing_bow_loons();
}

/* NON_MATCHING: masked 0; i and j swap saved registers (s5/s2) */
#ifdef NON_MATCHING
/* The water planes. */
void func_801065C8_bobbing_bow_loons(void) {
    s32 attr[2];
    s32 file[2] = { 0x13, 0x14 };
    s32 alpha[2] = { 0x40, 0xB3 };
    omObjData* obj;
    BlWater* work;
    s32 j;
    s32 i;

    attr[0] = 0xAC9;
    attr[1] = 0x2C9;

    obj = omAddObj(0xFF, 8, 0, -1, func_801068B0_bobbing_bow_loons);
    D_80109B28_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(sizeof(BlWater), 31000);
    work = obj->data;
    work->unk00[0] = 0.0f;
    work->unk00[1] = 1000.0f;
    work->unk00[2] = 0.0f;
    work->unk00[3] = 1000.0f;
    work->unk00[4] = 50.0f;
    work->unk00[5] = -950.0f;
    work->unk00[6] = 50.0f;
    work->unk00[7] = -950.0f;
    work->unk20[0] = -400.0f;
    work->unk20[1] = -400.0f;
    work->unk20[2] = -400.0f;
    work->unk20[3] = -400.0f;
    work->unk20[4] = -400.0f;
    work->unk20[5] = -400.0f;
    work->unk20[6] = -400.0f;
    work->unk20[7] = -400.0f;
    work->unk40[0] = 16.0f;
    work->unk40[1] = 16.0f;
    work->unk40[2] = 2.0f;
    work->unk40[3] = 2.0f;
    work->unk40[4] = 18.0f;
    work->unk40[5] = 18.0f;
    work->unk40[6] = 0.0f;
    work->unk40[7] = 0.0f;
    obj->model[0] = func_8000B108_main(0x5E0001, 0x1699);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = func_8000B108_main(0x5E0002, 0x699);
    obj->model[3] = Hu3DModelLink(obj->model[2]);
    for (i = 0, j = 4; j < 8; i++, j += 2) {
        obj->model[j] = func_8000B108_main(file[i] | 0x5E0000, attr[i]);
        func_8001C2FC_main(obj->model[j], 0x20000, 0x20000);
        func_8001C954_main(obj->model[j]);
        func_8001FA68_main(obj->model[j]);
        func_8001F9E4_main(obj->model[j], alpha[i]);
        func_8001C448_main(obj->model[j]);
        func_8001C514_main(obj->model[j]);
        obj->model[j + 1] = Hu3DModelLink(obj->model[j]);
    }
    omSetTra(obj, work->unk00[0], work->unk20[0], work->unk40[0]);
    for (i = 1; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk20[i], work->unk40[i]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801065C8_bobbing_bow_loons);
#endif

void func_801068B0_bobbing_bow_loons(omObjData* obj) {
    BlWater* work = obj->data;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (i == 0) {
            omSetTra(obj, work->unk00[i], work->unk20[i], work->unk40[i]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk20[i], work->unk40[i]);
        }
    }
    work->unk00[0] += -3.0f;
    work->unk00[1] += -3.0f;
    work->unk00[2] += -1.0f;
    work->unk00[3] += -1.0f;
    work->unk00[4] += -3.0f;
    work->unk00[5] += -3.0f;
    work->unk00[6] += -1.0f;
    work->unk00[7] += -1.0f;
    for (i = 0; i < 8; i++) {
        if (work->unk00[i] <= -1000.0f) {
            work->unk00[i] += 2000.0f;
        }
    }
}

void func_80106A00_bobbing_bow_loons(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

/* NON_MATCHING: only differs by retail passing obj to func_800E6F40_minigame (declared (void)) */
#ifdef NON_MATCHING
/* The main loop: framework state, finish and result. */
void func_80106A34_bobbing_bow_loons(omObjData* obj) {
    f32 frame[8] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f };

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (func_800E6F40_minigame()) {
        case 0:
            if (func_800E6E9C_minigame() == 1) {
                HuAudSeqPlay(0x44);
            }
            if (HmfModelData[D_80109B1C_bobbing_bow_loons->model[0]].unk40 ==
                frame[GwPlayer[D_80109B0C_bobbing_bow_loons].chr]) {
                HuAudFXPlay(0x4DA);
            }
            if (func_800E6E9C_minigame() == 15) {
                func_80107C48_bobbing_bow_loons();
                HuAudFXPlay(0x4E0);
            }
            break;
        case 1:
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                func_80107F68_bobbing_bow_loons();
                func_80108894_bobbing_bow_loons();
            }
            if (D_80109B04_bobbing_bow_loons == 2 || D_80109B04_bobbing_bow_loons == 3) {
                if (D_80109B04_bobbing_bow_loons == 2) {
                    func_801091FC_bobbing_bow_loons();
                }
                func_8010829C_bobbing_bow_loons();
                D_80109B04_bobbing_bow_loons = 4;
            }
            break;
        case 3:
            break;
        case 4:
            if (D_80109B10_bobbing_bow_loons != -1) {
                D_80109720_bobbing_bow_loons.unk06 = 5;
            } else {
                D_80109720_bobbing_bow_loons.unk06 = 7;
            }
            break;
        case 5:
            if (D_80109B10_bobbing_bow_loons != -1) {
                GwPlayer[D_80109B0C_bobbing_bow_loons].bonusCoin = (u16)D_80109B10_bobbing_bow_loons;
            } else {
                GwPlayer[D_80109B0C_bobbing_bow_loons].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80106A00_bobbing_bow_loons;
            break;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109964_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106A34_bobbing_bow_loons);
#endif

/* NON_MATCHING: retail recomputes &work[i] after the rand8 calls; this keeps it in a saved register (masked 12) */
#ifdef NON_MATCHING
/* The five balloons. */
void func_80106CC0_bobbing_bow_loons(void) {
    omObjData* obj;
    BlBalloon* work;
    BlPlayer* pw;
    s32 i;
    s32 attr = 0x699;

    obj = omAddObj(0xFF, 10, 0, -1, func_80106F44_bobbing_bow_loons);
    D_80109B2C_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(sizeof(BlBalloon), 31000);
    work = obj->data;
    pw = D_80109B1C_bobbing_bow_loons->data;
    for (i = 0; i < 5; i++) {
        work->unk00[i] = 1;
        work->unk14[i] = i * 120.0f - 280.0f;
        work->unk28[i] = 0.0f;
        work->unk3C[i] = pw->unk0C;
        work->unk50[i] = 0.0f;
        rand8();
        rand8();
        work->unk64[i] = (i + 1) * 1.3f;
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5E0007, attr);
            omSetTra(obj, work->unk14[0], work->unk28[0], work->unk3C[0]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], work->unk14[i % 5], work->unk28[i % 5], work->unk3C[i % 5]);
        }
    }
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            obj->model[5] = func_8000B108_main(0x5E0010, attr);
            omSetTra(obj, work->unk14[0], work->unk28[0], work->unk3C[0]);
        } else {
            obj->model[i + 5] = Hu3DModelLink(obj->model[5]);
            /* positions model[i], not model[i + 5] (retail) */
            Hu3DModelPosSet(obj->model[i], work->unk14[i % 5], work->unk28[i % 5], work->unk3C[i % 5]);
        }
    }
    work->unk78 = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106CC0_bobbing_bow_loons);
#endif

void func_80106F44_bobbing_bow_loons(omObjData* obj) {
    BlBalloon* work = obj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, work->unk14[i], work->unk28[i], work->unk3C[i]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk14[i], work->unk28[i], work->unk3C[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], work->unk14[i], work->unk28[i], work->unk3C[i] - 4.0f);
        if (work->unk00[i] & 1) {
            work->unk28[i] = sindf(work->unk50[i]) * 200.0f;
            work->unk50[i] += work->unk64[i];
            if (work->unk50[i] >= 360.0f) {
                work->unk50[i] -= 360.0f;
            }
            if (work->unk50[i] <= 0.0f) {
                work->unk50[i] += 360.0f;
            }
        }
        if (work->unk00[i] & 2) {
            work->unk28[i] += work->unk78;
            work->unk78 += 0.1f;
            if (work->unk28[i] >= 500.0f) {
                work->unk00[i] &= ~2;
            }
        }
    }
}

void func_80107130_bobbing_bow_loons(void) {
    BlBalloon* work = D_80109B2C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        work->unk00[i] = (work->unk00[i] | 2) & ~1;
    }
    work->unk78 = 0.0f;
}

/* NON_MATCHING: scheduling of the balloon y load around the first fabs test (masked 6) */
#ifdef NON_MATCHING
/* The balloon the hook touches, or -1. */
s32 func_80107174_bobbing_bow_loons(void) {
    BlBalloon* bw;
    BlHook* hook;
    s32 ret = -1;
    s32 i;
    s16 se;
    f32 x;
    f32 y;
    f32 by;

    bw = D_80109B2C_bobbing_bow_loons->data;
    hook = D_80109B30_bobbing_bow_loons->data;
    x = hook->unk04 - 25.0f;
    y = hook->unk08 - 100.0f;
    for (i = 0; i < 5; i++) {
        by = bw->unk28[i] - 50.0f;
        if (fabs(x - bw->unk14[i]) < 50.0 && fabs(y - by) < 50.0) {
            ret = i;
            se = HuAudFXPlay(0x4DC);
            if (se >= 0) {
                func_8004AE00_main(se, i * 10 + 0x2C);
            }
            break;
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107174_bobbing_bow_loons);
#endif

/* The strings. */
void func_8010728C_bobbing_bow_loons(void) {
    omObjData* obj;
    s32 i;

    obj = omAddObj(0x50, 7, 0, -1, func_80107368_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BlString), 31000);
    D_80109B34_bobbing_bow_loons = obj;
    obj->model[0] = func_8000B108_main(0x5E0006, 0x4B9);
    for (i = 1; i < 7; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
    HmfModelData[obj->model[5]].scale.y = 1.2f;
}

void func_80107368_bobbing_bow_loons(omObjData* obj) {
    BlString* work = obj->data;
    BlBalloon* bw = D_80109B2C_bobbing_bow_loons->data;
    BlPlayer* pw = D_80109B1C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        work->unk00[i] = bw->unk14[i];
        work->unk1C[i] = bw->unk28[i] - 100.0f;
        work->unk38[i] = bw->unk3C[i] - 2.0f;
    }
    work->unk00[5] = pw->unk04 + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    work->unk1C[5] = pw->unk08 + 42.0f;
    work->unk38[5] = pw->unk0C - 2.0f;
    omSetTra(obj, work->unk00[0], work->unk1C[0], work->unk38[0]);
    for (i = 1; i < 7; i++) {
        Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk1C[i], work->unk38[i]);
    }
    func_8001C258_main(obj->model[6], 4, 4);
}

/* NON_MATCHING: masked 0; kind lives in a0, retail a1 */
#ifdef NON_MATCHING
/* The prizes, one random kind under each balloon; a CPU picks its target. */
void func_801074CC_bobbing_bow_loons(void) {
    s32 count[16];
    s32 files[16] = { 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
                      0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C };
    omObjData* obj;
    BlPrize* work;
    BlBalloon* bw;
    void* data;
    s32 id;
    s32 i;
    s32 j;
    s32 r;
    s32 sum;
    s32 kind;

    obj = omAddObj(0xFE, 5, 0, -1, func_80107830_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BlPrize), 31000);
    D_80109B38_bobbing_bow_loons = obj;
    work = obj->data;
    bw = D_80109B2C_bobbing_bow_loons->data;
    for (i = 0; i < 16; i++) {
        count[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        kind = D_800A11D0_main[4 - i];
        count[kind]++;
        D_80109B40_bobbing_bow_loons[i] = kind;
        data = DataRead(files[kind] | 0x210000);
        id = HmfSprModelCreate(data, 0x699, 8);
        DataClose(data);
        obj->model[i] = D_800CBB60_main[(s16)id].unk00;
        work->unk00[i] = bw->unk14[i];
        work->unk14[i] = bw->unk28[i];
        work->unk28[i] = bw->unk3C[i] - 2.0f;
        if (i == 0) {
            omSetTra(obj, work->unk00[0], work->unk14[0], work->unk28[0]);
            omSetSca(obj, 1.8f, 1.8f, 1.8f);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk14[i], work->unk28[i]);
            Hu3DModelScaleSet(obj->model[i], 1.8f, 1.8f, 1.8f);
        }
        work->unk3C[i] = 1;
    }
    work->unk50 = 0.0f;
    work->unk54 = 0.0f;
    work->unk58 = 0.0f;
    if (GwPlayer[D_80109B0C_bobbing_bow_loons].stat & 1) {
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
        D_80109B14_bobbing_bow_loons = j;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801099A8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801074CC_bobbing_bow_loons);
#endif

void func_80107830_bobbing_bow_loons(omObjData* obj) {
    BlPrize* work = obj->data;
    BlBalloon* bw = D_80109B2C_bobbing_bow_loons->data;
    BlPlayer* pw = D_80109B1C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (work->unk3C[i] & 1) {
            work->unk14[i] = bw->unk28[i] + 50.0f;
        }
        if (work->unk3C[i] & 2) {
            work->unk00[i] = work->unk54;
            work->unk14[i] = sindf(work->unk50) * 20.0f + work->unk58;
            work->unk28[i] = pw->unk0C + 2.0f;
            work->unk50 += 10.0f;
            if (work->unk50 >= 360.0f) {
                work->unk50 -= 360.0f;
            }
            func_8000CFA4_main(D_80109B08_bobbing_bow_loons, work->unk00[i], work->unk14[i], work->unk28[i]);
        }
        if (i == 0) {
            omSetTra(obj, work->unk00[i], work->unk14[i], work->unk28[i]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk14[i], work->unk28[i]);
        }
    }
}

/* Balloon idx hooked: its prize flies to the player. */
void func_801079E8_bobbing_bow_loons(s32 idx) {
    BlPrize* work = D_80109B38_bobbing_bow_loons->data;

    work->unk3C[idx] |= 2;
    work->unk50 = 0.0f;
    work->unk54 = 0.0f;
    work->unk58 = 0.0f;
    D_80109B54_bobbing_bow_loons = idx;
    D_80109B10_bobbing_bow_loons = D_80109B40_bobbing_bow_loons[idx];
    D_80109B08_bobbing_bow_loons = func_8000CED8_main(0xB0004, 0x6A9);
    omAddPrcObj(func_80107A7C_bobbing_bow_loons, 0x50, 0, 0);
    HuAudFXPlay(0x4DD);
}

void func_80107A7C_bobbing_bow_loons(void) {
    BlBalloon* bw = D_80109B2C_bobbing_bow_loons->data;
    BlPrize* work = D_80109B38_bobbing_bow_loons->data;
    BlPlayer* pw = D_80109B1C_bobbing_bow_loons->data;
    f32 dx;
    f32 dy;
    s32 i;

    func_80107130_bobbing_bow_loons();
    func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons], 4, 4);
    func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons + 5], 4, 4);
    func_8001C258_main(D_80109B34_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons], 4, 4);
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 4);
    func_80108F2C_bobbing_bow_loons(bw->unk14[D_80109B54_bobbing_bow_loons],
                                    bw->unk28[D_80109B54_bobbing_bow_loons] + 50.0f);
    work->unk54 = work->unk00[D_80109B54_bobbing_bow_loons];
    work->unk58 = work->unk14[D_80109B54_bobbing_bow_loons] + 50.0f;
    dx = (pw->unk04 - work->unk00[D_80109B54_bobbing_bow_loons]) / 30.0f;
    dy = ((pw->unk08 + 150.0f) - work->unk14[D_80109B54_bobbing_bow_loons]) / 30.0f;
    for (i = 0; i < 30; i++) {
        work->unk54 = dx + work->unk54;
        work->unk58 = dy + work->unk58;
        HuPrcVSleep();
    }
    func_80107D4C_bobbing_bow_loons();
    omDelPrcObj(NULL);
}

void func_80107C48_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107C74_bobbing_bow_loons, 0x50, 0, 0);
}

/* Camera: zoom out to the whole sea. */
void func_80107C74_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += 16.666666f;
        Center.x += -6.6666665f;
        Center.y += -2.6666667f;
        HuPrcVSleep();
    }
    CZoom = 1500.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void func_80107D4C_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107D78_bobbing_bow_loons, 0x50, 0, 0);
}

/* Camera: back to the player, who cheers. */
void func_80107D78_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom -= 16.666666f;
        Center.x -= -6.6666665f;
        Center.y -= -2.6666667f;
        HuPrcVSleep();
    }
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    func_801063F8_bobbing_bow_loons();
    omDelPrcObj(NULL);
}

void func_80107E68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107E94_bobbing_bow_loons, 0x50, 0, 0);
}

/* Camera: to the falling player. */
void func_80107E94_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        CZoom -= 12.5f;
        Center.x -= -5.0f;
        Center.y -= 0.0f;
        HuPrcVSleep();
    }
    CZoom = 1250.0f;
    Center.x = 100.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void func_80107F68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107F94_bobbing_bow_loons, 0x50, 0, 0);
}

/* The 10-second timer. */
void func_80107F94_bobbing_bow_loons(void) {
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
        if (D_80109B04_bobbing_bow_loons == 4) {
            break;
        }
    } while (sec > 0);
    if (D_80109B04_bobbing_bow_loons == 0) {
        D_80109B04_bobbing_bow_loons = 2;
    }
    func_8003F5C0_main();
    omDelPrcObj(NULL);
}

/* The hook, held by the player. */
void func_8010805C_bobbing_bow_loons(void) {
    omObjData* obj;
    BlHook* work;
    BlPlayer* pw;

    obj = omAddObj(0xFF, 1, 0, -1, func_8010817C_bobbing_bow_loons);
    D_80109B30_bobbing_bow_loons = obj;
    work = HuMemAllocTag(sizeof(BlHook), 31000);
    obj->data = work;
    pw = D_80109B1C_bobbing_bow_loons->data;
    obj->model[0] = func_8000B108_main(0x5E0005, 0x699);
    work->unk00 = 0;
    work->unk04 = 0.0f;
    work->unk08 = 50.0f;
    work->unk0C = pw->unk0C;
    work->unk10 = 270.0f;
    omSetTra(obj, work->unk04, work->unk08, work->unk0C);
    omSetRot(obj, 0.0f, 0.0f, work->unk10);
    func_8001EF6C_main(obj->model[0], D_80109B1C_bobbing_bow_loons->model[0], "item_hook");
    func_8001C258_main(obj->model[0], 0x4000, 0x4000);
}

void func_8010817C_bobbing_bow_loons(omObjData* obj) {
    BlHook* work = obj->data;
    s32 idx;

    omSetTra(obj, work->unk04, work->unk08, work->unk0C);
    omSetRot(obj, 0.0f, 0.0f, work->unk10);
    if (work->unk00 & 1) {
        work->unk04 -= 23.0f;
        idx = func_80107174_bobbing_bow_loons();
        if (idx != -1) {
            func_800E6F0C_minigame(3);
            func_801079E8_bobbing_bow_loons(idx);
            work->unk00 &= ~1;
            omVibrate((s16)D_80109B0C_bobbing_bow_loons, 2, 2, 20);
        } else if (work->unk04 <= -290.0f) {
            D_80109B04_bobbing_bow_loons = 0;
            func_800E6F0C_minigame(3);
            func_80108328_bobbing_bow_loons();
            work->unk00 &= ~1;
            omVibrate((s16)D_80109B0C_bobbing_bow_loons, 20, 0, 20);
        }
    }
}

/* Throw the hook. */
void func_8010829C_bobbing_bow_loons(void) {
    BlHook* work = D_80109B30_bobbing_bow_loons->data;

    work->unk04 = D_80109B1C_bobbing_bow_loons->trans.x;
    work->unk08 = D_80109B1C_bobbing_bow_loons->trans.y + 100.0f;
    work->unk00 |= 1;
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 0);
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 0x4000, 0);
    HuAudFXPlay(0x4DB);
}

void func_80108328_bobbing_bow_loons(void) {
    omAddPrcObj(func_80108354_bobbing_bow_loons, 0x50, 0, 0);
}

/* Missed: the hook comes back and bursts the player's balloon; the player falls in the sea. */
void func_80108354_bobbing_bow_loons(void) {
    f32 dx[8] = { -20.0f, 0.0f, -15.0f, 31.5f, 5.0f, 19.2f, -15.0f, 0.0f };
    f32 dy[8] = { 100.0f, -19.0f, 70.0f, -106.2f, -18.0f, -107.1f, 70.0f, -16.0f };
    f32 dz[8] = { 15.0f, -2.5f, 0.0f, 20.5f, 0.0f, 36.2f, 0.0f, 3.0f };
    BlHook* hook;
    BlPlayer* pw;
    BlBalloon* bw;
    f32 v;
    s32 i;

    hook = D_80109B30_bobbing_bow_loons->data;
    pw = D_80109B1C_bobbing_bow_loons->data;
    bw = D_80109B2C_bobbing_bow_loons->data;
    if (D_80109B04_bobbing_bow_loons != 2) {
        func_801091FC_bobbing_bow_loons();
    }
    for (i = 0; i < 5; i++) {
        bw->unk00[i] &= ~1;
    }
    omSetTra(D_80109B58_bobbing_bow_loons, hook->unk04 + 30.0f, hook->unk08 - 30.0f, hook->unk0C);
    func_801096E8_bobbing_bow_loons();
    HuAudFXPlay(0x4DE);
    hook->unk10 = 150.0f;
    while (hook->unk08 < 400.0f) {
        hook->unk04 = sindf(30.0f) * 23.0f + hook->unk04;
        hook->unk08 = cosdf(30.0f) * 23.0f + hook->unk08;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    hook->unk10 = 180.0f;
    hook->unk04 = D_80109B1C_bobbing_bow_loons->trans.x;
    while (D_80109B1C_bobbing_bow_loons->trans.y + 300.0f <= hook->unk08) {
        hook->unk08 -= 23.0f;
        HuPrcVSleep();
    }
    hook->unk08 = D_80109B1C_bobbing_bow_loons->trans.y - 200.0f;
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 4);
    func_8001C258_main(D_80109B34_bobbing_bow_loons->model[5], 4, 4);
    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[1], 4, 4);
    func_80108F2C_bobbing_bow_loons(
        pw->unk04 + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr], pw->unk08 + 230.0f);
    HuAudFXPlay(0x4DF);
    HuAudFXPlay(GwPlayer[D_80109B0C_bobbing_bow_loons].chr + 0x2AC);
    pw->unk00 &= ~1;
    pw->unk04 -= dx[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    pw->unk08 -= dy[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    pw->unk0C -= dz[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    func_801064C0_bobbing_bow_loons();
    HuPrcSleep(30);
    func_8004AC98_main(GwPlayer[D_80109B0C_bobbing_bow_loons].chr + 0x287, (s16)D_80109B0C_bobbing_bow_loons);
    func_8001C814_main(D_80109B1C_bobbing_bow_loons->model[3], 1, 1);
    v = -20.0f;
    while (pw->unk08 >= -500.0f) {
        pw->unk08 = v + pw->unk08;
        v -= 5.0f;
        HuPrcVSleep();
    }
    func_80109568_bobbing_bow_loons();
    func_800E6F0C_minigame(3);
    omDelPrcObj(NULL);
}

void func_80108894_bobbing_bow_loons(void) {
    omAddPrcObj(func_801088C0_bobbing_bow_loons, 0x50, 0, 0);
}

/* NON_MATCHING: masked 0; y and y - 20 swap $f4/$f6 */
#ifdef NON_MATCHING
/* Input: A drops the hook; a CPU drops it when its target balloon is in its window and clear. */
void func_801088C0_bobbing_bow_loons(void) {
    f32 y;
    f32 cur[5];
    f32 lo[5] = { 120.0f, 300.0f, 120.0f, 320.0f, 160.0f };
    f32 hi[5] = { 140.0f, 320.0f, 140.0f, 340.0f, 180.0f };
    f32 jit[5];
    BlBalloon* bw;
    s32 i;
    s32 hit;
    s32 d;
    s32 done = 0;

    bw = D_80109B2C_bobbing_bow_loons->data;
    while (done == 0) {
        if (GwPlayer[D_80109B0C_bobbing_bow_loons].stat & 1) {
            d = 4 - GwPlayer[D_80109B0C_bobbing_bow_loons].cpu_difficulty;
            for (i = 0; i < 5; i++) {
                jit[i] = (f32)((rand8() % (d * 10)) - d * 5) + lo[i];
            }
            cur[D_80109B14_bobbing_bow_loons] = bw->unk50[D_80109B14_bobbing_bow_loons];
            hit = 0;
            if (hi[D_80109B14_bobbing_bow_loons] < 360.0f) {
                if (jit[D_80109B14_bobbing_bow_loons] <= cur[D_80109B14_bobbing_bow_loons] &&
                    cur[D_80109B14_bobbing_bow_loons] < hi[D_80109B14_bobbing_bow_loons]) {
                    hit = 1;
                }
            } else if ((cur[D_80109B14_bobbing_bow_loons] >= 0.0f &&
                        cur[D_80109B14_bobbing_bow_loons] < hi[D_80109B14_bobbing_bow_loons] - 360.0f) ||
                       (cur[D_80109B14_bobbing_bow_loons] >= lo[D_80109B14_bobbing_bow_loons] &&
                        cur[D_80109B14_bobbing_bow_loons] < 360.0f)) {
                hit++;
            }
            if (hit != 0) {
                y = bw->unk28[D_80109B14_bobbing_bow_loons];
                hit = 0; /* now: balloons in the way */
                for (i = D_80109B14_bobbing_bow_loons + 1; i < 5; i++) {
                    if (y - 20.0f <= bw->unk28[i] && bw->unk28[i] < y + 20.0f) {
                        hit++;
                        break;
                    }
                }
                if (hit == 0) {
                    D_80109B04_bobbing_bow_loons = 3;
                    break;
                }
            }
        } else if (D_800D5558_main[GwPlayer[D_80109B0C_bobbing_bow_loons].pad] & 0x8000) {
            D_80109B04_bobbing_bow_loons = 3;
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A54_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A68_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801088C0_bobbing_bow_loons);
#endif

/* The pop effect; arg0: in the player's colours. */
void func_80108C18_bobbing_bow_loons(s32 arg0) {
    omObjData* obj;
    BlPop* work;

    obj = omAddObj(0xFF, 2, 0, -1, func_80108E5C_bobbing_bow_loons);
    D_80109B5C_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(sizeof(BlPop), 31000);
    work = obj->data;
    obj->model[0] = func_8000B108_main(0x5E0011, 0x6CD);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C954_main(obj->model[0]);
    obj->model[1] = func_8000B108_main(0x5E0012, 0x6DD);
    if (arg0 != 0) {
        switch (GwPlayer[D_80109B0C_bobbing_bow_loons].chr) {
            case 0:
                func_8001E500_main(obj->model[0], "c0_DEF", "c1_DEF");
                break;
            case 1:
                func_8001E500_main(obj->model[0], "c0_DEF", "c2_DEF");
                break;
            case 2:
                func_8001E500_main(obj->model[0], "c0_DEF", "c3_DEF");
                break;
            case 3:
                func_8001E500_main(obj->model[0], "c0_DEF", "c4_DEF");
                break;
            case 4:
                func_8001E500_main(obj->model[0], "c0_DEF", "c5_DEF");
                break;
            case 5:
                func_8001E500_main(obj->model[0], "c0_DEF", "c6_DEF");
                break;
            case 6:
                func_8001E500_main(obj->model[0], "c0_DEF", "c7_DEF");
                break;
            case 7:
                func_8001E500_main(obj->model[0], "c0_DEF", "c8_DEF");
                break;
        }
    }
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xA0);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    work->unk00 = 0.0f;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk0C = 0;
    work->unk14 = 0;
    work->unk10 = 0.1f;
}

void func_80108E5C_bobbing_bow_loons(omObjData* obj) {
    BlPop* work = obj->data;

    omSetTra(obj, work->unk00, work->unk04, work->unk08);
    if (work->unk0C & 1) {
        work->unk10 += 0.03f;
        func_8001D558_main(obj->model[0], work->unk10, work->unk10 * 25.0f, 2);
        if (++work->unk14 == 30) {
            func_8001C258_main(D_80109B5C_bobbing_bow_loons->model[0], 4, 4);
            work->unk0C &= ~1;
        }
    }
}

/* Pop a balloon at (x, y); bigger and in the player's colours for the player's own. */
void func_80108F2C_bobbing_bow_loons(f32 x, f32 y) {
    BlPop* work;
    f32 s;
    s32 own;

    if (x == ((BlPlayer*)D_80109B1C_bobbing_bow_loons->data)->unk04 +
                 D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr]) {
        s = 1.5f;
        own = 1;
    } else {
        own = 0;
        s = 1.0f;
    }
    func_80108C18_bobbing_bow_loons(own);
    work = D_80109B5C_bobbing_bow_loons->data;
    work->unk0C |= 1;
    func_8001C258_main(D_80109B5C_bobbing_bow_loons->model[0], 4, 0);
    work->unk00 = x;
    work->unk04 = y;
    work->unk08 = 16.0f;
    omSetSca(D_80109B5C_bobbing_bow_loons, s, s, s);
}

/* The burst balloons (5 models in an object created with 2: retail). */
void func_80109044_bobbing_bow_loons(void) {
    omObjData* obj;
    s32 i;

    obj = omAddObj(0xFF, 2, 0, -1, func_801090EC_bobbing_bow_loons);
    D_80109B60_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(sizeof(BlBurst), 31000);
    obj->model[0] = func_8000B108_main(0x5D0008, 0xA3D);
    for (i = 1; i < 5; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
}

void func_801090EC_bobbing_bow_loons(omObjData* obj) {
    BlBurst* work = obj->data;
    s32 i;

    omSetTra(obj, work->unk00[0], work->unk14[0], work->unk28[0]);
    for (i = 1; i < 5; i++) {
        Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk14[i], work->unk28[i]);
    }
    if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
        for (i = 0; i < 5; i++) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

/* Time up: every balloon bursts. */
void func_801091FC_bobbing_bow_loons(void) {
    BlBurst* work = D_80109B60_bobbing_bow_loons->data;
    BlBalloon* bw = D_80109B2C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[i], 4, 4);
        func_8001C258_main(D_80109B34_bobbing_bow_loons->model[i], 4, 4);
        func_8001C258_main(D_80109B38_bobbing_bow_loons->model[i], 4, 4);
        work->unk00[i] = bw->unk14[i];
        work->unk14[i] = bw->unk28[i] + 50.0f;
        work->unk28[i] = bw->unk3C[i] + 2.0f;
        bw->unk00[i] &= ~1;
        bw->unk28[i] = -1000.0f;
        func_8001C258_main(D_80109B60_bobbing_bow_loons->model[i], 4, 0);
    }
}

/* The player's balloon bursts. */
void func_8010934C_bobbing_bow_loons(void) {
    BlBurst* work = D_80109B60_bobbing_bow_loons->data;
    BlPlayer* pw = D_80109B1C_bobbing_bow_loons->data;

    work->unk00[0] = pw->unk04;
    work->unk14[0] = pw->unk08 + 50.0f;
    work->unk28[0] = pw->unk0C + 2.0f;
    func_8001C258_main(D_80109B60_bobbing_bow_loons->model[0], 4, 0);
    func_8001C6A8_main(D_80109B60_bobbing_bow_loons->model[0], 0.0f);
}

/* The host. */
void func_801093DC_bobbing_bow_loons(void) {
    omObjData* obj;
    BlHost* work;

    obj = omAddObj(0xFF, 2, 0, -1, func_801094B0_bobbing_bow_loons);
    D_80109B64_bobbing_bow_loons = obj;
    work = HuMemAllocTag(sizeof(BlHost), 31000);
    obj->data = work;
    obj->model[0] = func_8000B108_main(0xA00EE, 0x6D9);
    omSetSca(obj, 0.7f, 0.7f, 0.7f);
    omSetRot(obj, 0.0f, 325.0f, 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    work->unk00 = -130.0f;
    work->unk04 = 0.0f;
}

void func_801094B0_bobbing_bow_loons(omObjData* obj) {
    BlHost* work = obj->data;
    BlHmfObj* head;
    s16 mdl;

    omSetTra(obj, 370.0f, work->unk00, -70.0f);
    mdl = obj->model[0];
    func_8002FD8C_main(mdl, HmfModelData[mdl].unk02, "c162_000-atama", 0x4C, 0x45);
    head = func_8001D33C_main(mdl, "c162_000-atama");
    head->unk10 = work->unk04;
    head->unk34 = work->unk04;
    func_8001C814_main(obj->model[0], 1, 1);
}

void func_80109568_bobbing_bow_loons(void) {
    omAddPrcObj(func_80109594_bobbing_bow_loons, 0x50, 0, 0);
}

/* The host rises and laughs. */
void func_80109594_bobbing_bow_loons(void) {
    BlHost* work = D_80109B64_bobbing_bow_loons->data;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        work->unk00 += 10.0f;
        HuPrcVSleep();
    }
    func_80107E68_bobbing_bow_loons();
    HuPrcSleep(20);
    HuAudFXPlay(0x2A0);
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 2; j++) {
            work->unk04 += 8.0f;
            HuPrcVSleep();
        }
        for (j = 0; j < 2; j++) {
            work->unk04 -= 8.0f;
            HuPrcVSleep();
        }
    }
    omDelPrcObj(NULL);
}

/* The splash. */
void func_80109680_bobbing_bow_loons(void) {
    omObjData* obj;

    obj = omAddObj(0xFF, 1, 0, -1, NULL);
    D_80109B58_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(8, 31000);
    obj->model[0] = func_8000B108_main(0xB0003, 0x6DD);
}

void func_801096E8_bobbing_bow_loons(void) {
    func_8001C258_main(D_80109B58_bobbing_bow_loons->model[0], 4, 0);
}
