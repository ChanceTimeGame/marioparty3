#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// et A: Etch 'n' Catch (2 vs 2)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (as Hyper Hydrants' HhCtrl) */
typedef struct EtCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result: 1 a team won, 4 draw */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winners, 0xFF none */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} EtCtrl; /* size 0x28 */

/* omObjData::data of a ground object (the framework's ground block, as Hyper Hydrants' HhGround) */
typedef struct EtGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA8];
} EtGround; /* size 0xB4 */

typedef struct EtVec2 {
    f32 x;
    f32 y;
} EtVec2;

#define ET_FABS(x) (((x) < 0.0f) ? -(x) : (x))
#define ET_IABS(x) (((x) >= 0) ? (x) : -(x))
#define ET_ABS(x) (((x) > 0.0f) ? (x) : 0.0f - (x))

/* omObjData::data of a catcher (the two Chain Chomp-like hunters), MgWork plus its own fields */
typedef struct EtCatcher {
    /* 0x000 */ MgWork mg;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ u8 unk160; /* index 0/1 */
    /* 0x161 */ u8 unk161; /* swing direction */
    /* 0x164 */ f32 unk164; /* sprite scale */
    /* 0x168 */ f32 unk168;
    /* 0x16C */ f32 unk16C; /* target sprite angle */
    /* 0x170 */ f32 unk170; /* sprite angle */
    /* 0x174 */ f32 unk174; /* swing centre */
    /* 0x178 */ Vec unk178[5];
    /* 0x1B4 */ f32 unk1B4; /* burst radius */
} EtCatcher; /* size 0x1B8 */

/* omObjData::data of a cage */
typedef struct EtCage {
    /* 0x00 */ u8 unk00; /* index 0/1 */
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ char unk03;
    /* 0x04 */ f32 unk04; /* shadow scale */
    /* 0x08 */ f32 unk08; /* drop speed */
} EtCage; /* size 0xC */

/* A trail node: 256 per player in D_801113D8[player] */
typedef struct EtNode {
    /* 0x00 */ u8 unk00; /* in use */
    /* 0x01 */ char unk01[3];
    /* 0x04 */ struct EtNode* prev;
    /* 0x08 */ struct EtNode* next;
    /* 0x0C */ struct EtNode* unk0C; /* previous node of the trail */
    /* 0x10 */ struct EtNode* unk10; /* next node of the trail */
    /* 0x14 */ u8 unk14; /* team bits */
    /* 0x15 */ u8 unk15; /* grid value */
    /* 0x16 */ s16 unk16; /* life: 106 new, 17 expiring, 16 off the grid, 0 freed */
    /* 0x18 */ s16 unk18; /* cell x */
    /* 0x1A */ s16 unk1A; /* cell y */
    /* 0x1C */ u8 unk1C; /* player */
    /* 0x1D */ char unk1D;
    /* 0x1E */ s16 unk1E; /* puff model, -1 none */
    /* 0x20 */ Vec unk20; /* puff position */
    /* 0x2C */ s8 unk2C; /* puff frame */
    /* 0x2D */ char unk2D[3];
    /* 0x30 */ f32 unk30; /* puff scale */
    /* 0x34 */ u8 unk34; /* puff model slot */
    /* 0x35 */ char unk35[3];
} EtNode; /* size 0x38 */

// Heap-allocated (0x20 bytes) per-player work (D_8010C868[player]); unk0C is the head of a linked list
// of nodes (func_80108B64 inserts, func_80108BCC removes, func_80108C08 walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ u8 unk00; /* team member bit: 1/2 team 0, 4/8 team 1 */
    /* 0x01 */ u8 unk01; /* 3 team 0, 12 team 1 */
    /* 0x02 */ u8 unk02; /* 8 team 0, 1 team 1 */
    /* 0x03 */ char unk03;
    /* 0x04 */ s16 unk04; /* pen cell x */
    /* 0x06 */ s16 unk06; /* pen cell y */
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ struct EtNode* unk_0C;
    /* 0x10 */ s16 unk10; /* drawing sound */
    /* 0x12 */ u8 unk12; /* drawing sound playing */
    /* 0x13 */ char unk13;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[2];
} EtchNCatchWork; // sizeof 0x20

// main
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004A208_main(void);
void func_8004AD70_main(void);
void func_8004A950_main(void);
u16 func_80049F98_main(void);
s32 func_8000B638_main(void);
omObjData* func_80045ED0_main(u32 arg0);
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
extern f32 D_800EB740_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern s32 D_800EBEB0_minigame[];

// this overlay
void func_80105CD0_etch_n_catch(EtCtrl* ctrl);
void func_80105D5C_etch_n_catch(void);
void func_80105ED4_etch_n_catch(omObjData* obj);
void func_80106334_etch_n_catch(omObjData* obj);
void func_80109A54_etch_n_catch(omObjData* obj);
void func_8010B24C_etch_n_catch(omObjData* obj);
void func_8010BBE4_etch_n_catch(omObjData* obj);
void func_8010BE84_etch_n_catch(omObjData* obj);
void func_8010C2F4_etch_n_catch(void);
void func_8010C390_etch_n_catch(omObjData* obj);
void func_8010C444_etch_n_catch(omObjData* obj);

void func_80106A64_etch_n_catch(omObjData* obj);
void func_80108B20_etch_n_catch(EtchNCatchWork* arg0);
s32 func_80107D38_etch_n_catch(f32 x, f32 z, EtchNCatchWork* w);
EtNode* func_80108B28_etch_n_catch(s8 player);
void func_80108B64_etch_n_catch(EtNode** head, EtNode* node);
void func_80108BCC_etch_n_catch(EtNode** head, EtNode* node);
s32 func_80108C08_etch_n_catch(EtchNCatchWork* w);
void func_80108D84_etch_n_catch(u8** end);
s32 func_80108DD0_etch_n_catch(s16 x, s16 y);
u8* func_801090E0_etch_n_catch(s16 x, s16 y);
u8 func_80109114_etch_n_catch(s16 x, s16 y);
void func_8010914C_etch_n_catch(s16 x, s16 y, s32 v);
f32 func_8010C4F8_etch_n_catch(f32 angle);
EtVec2 func_8010C574_etch_n_catch(s32 x0, s32 y0, s32 x1, s32 y1);
void func_8010C628_etch_n_catch(omObjData* obj, f32 scale);
void func_8010BD98_etch_n_catch(omObjData* obj);
void func_8010B3B4_etch_n_catch(omObjData* obj);
void func_80109EB8_etch_n_catch(omObjData* obj);
void func_8010AB7C_etch_n_catch(omObjData* obj);
void func_8010AD6C_etch_n_catch(EtCatcher* cw);
void func_8010AEE4_etch_n_catch(EtCatcher* cw);
void func_8010AFB8_etch_n_catch(EtCatcher* cw);
void func_80107EA4_etch_n_catch(omObjData* obj);
void func_8010880C_etch_n_catch(MgWork* pw);
void func_80109370_etch_n_catch(EtNode* node, u8 v);
void func_801097B4_etch_n_catch(EtNode* node);
s32 func_8010B154_etch_n_catch(s16 x, s16 y);
// main (more)
extern u16 D_800D5558_main[4];
extern f32 D_800EB770_minigame;
s32 func_800E4A90_minigame(omObjData* obj);
void func_800DDD94_minigame(omObjData* obj);
s16 func_8004ACE0_main(s16, s16);
void HuAudFXStop(s32 seNo);
void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
void func_8000BB54_main(u16 arg0);
void func_8001C6A8_main(s32 model, f32 arg1);
extern D_800CCF58_main_Struct* D_800CCF58_main;
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_8004AE00_main(s16 handle, s16 pan);
void func_8004AAD0_main(s16, s8);
extern s8 D_800CBB6E_main[]; /* stick x per pad */
extern s8 D_800D20A1_main[]; /* stick y per pad */
f32 HuSqrtf(f32 x);
f32 atan2df(f32 y, f32 x);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_8000B460_main(omObjData*, u16, s32);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16, u8);
void func_8000BB94_main(u16 arg0);
s16 func_8000B838_main(s32 arg0);
void func_8000BBD4_main(u16 spriteId, s16 x, s16 y);
s16 InitEspriteSlot(s16 arg0, s16 arg1, u16 arg2);
void func_8000BD50_main(u16 id, s8 digit);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BF00_main(u16 spriteId, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E1468_minigame(omObjData* obj);
extern s32 D_800A178C_main[][6];
extern s16 D_800EB784_minigame[][14];
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
s16 func_8000B0D4_main(s32, s32);

// data
extern s8 D_8010C6D9_etch_n_catch; /* next player to set up */
extern s8 D_8010C6DA_etch_n_catch[2]; /* players set up per team */
extern s32 D_8010C6D4_etch_n_catch;
extern s8 D_8010C6AC_etch_n_catch; /* team 0 score */
extern s8 D_8010C6AD_etch_n_catch; /* team 1 score */
extern s8 D_8010C6D8_etch_n_catch;

extern s16 D_8010C6A4_etch_n_catch[2][2]; /* score digit positions */
extern Vec D_8010C6B0_etch_n_catch[3]; /* catcher/cage start positions (x negated for index 1) */
extern s8 D_8010C6A0_etch_n_catch; /* next catcher index */
extern u8 D_8010C6E8_etch_n_catch[4][3]; /* puff model slots in use */
extern u8 D_8010C6F4_etch_n_catch[4]; /* puff spacing counters */
extern u8 D_8010C6E4_etch_n_catch[4]; /* CPU state per player */
extern u8 D_8010C6F8_etch_n_catch[2]; /* catcher jumped (5) */
extern f32 D_8010C6DC_etch_n_catch; /* pen scale during the intro */
extern u8 D_8010C6E0_etch_n_catch; /* team 0 may have closed an area */
extern u8 D_8010C6E1_etch_n_catch; /* team 1 may have closed an area */
extern u8 D_8010C6E2_etch_n_catch; /* team checked this frame */
// bss
extern f32 D_8010C834_etch_n_catch; /* intro drop speed */
extern EtchNCatchWork* D_8010C838_etch_n_catch; /* work of the player being updated */
extern s16 D_8010C850_etch_n_catch[2][2]; /* catcher screen positions / 2 */
extern s16 D_8010C842_etch_n_catch; /* board sprite group */
extern s16 D_8010C844_etch_n_catch; /* grid sprite group */
extern s16 D_8010C848_etch_n_catch; /* grid height */
extern s16 D_8010C83C_etch_n_catch; /* first catcher's model (linked by the second) */
extern s16 D_8010C83E_etch_n_catch; /* first catcher's shadow model */
extern u8 D_8010C840_etch_n_catch; /* next cage index */
extern u16 D_801113A8_etch_n_catch[2]; /* score digit sprites */
extern u16 D_801113E8_etch_n_catch[2]; /* catcher sprites */
extern u8 D_8010C830_etch_n_catch; /* start layout, 0..4 */
extern EtchNCatchWork* D_8010C868_etch_n_catch[4];
extern s16 D_8010C846_etch_n_catch; /* grid width */
extern u8* D_8010C84C_etch_n_catch; /* grid */
extern u8** D_8010C878_etch_n_catch; /* cells visited by the flood fill */
extern u8** D_8010C87C_etch_n_catch[2]; /* flood-fill frontiers */
extern u8 D_8010C890_etch_n_catch[120][160]; /* region bits per 2x2 cell */
extern s16 D_80111390_etch_n_catch[4][3];
extern omObjData* D_8010C858_etch_n_catch[2];
extern omObjData* D_8010C860_etch_n_catch[2];
extern EtCtrl D_801113B0_etch_n_catch;
extern u8 D_801113C8_etch_n_catch; /* view: D_801113B0.unk18[0] */
extern u8 D_801113C9_etch_n_catch; /* view: D_801113B0.unk18[1] */
extern EtNode* D_801113D8_etch_n_catch[4]; /* trail node pools, 256 each */


void func_801059A0_etch_n_catch(void) {
    s32 i;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CD0_etch_n_catch(&D_801113B0_etch_n_catch);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_801113B0_etch_n_catch);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105ED4_etch_n_catch), 0xA0);
    func_80105D5C_etch_n_catch();
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C390_etch_n_catch);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C444_etch_n_catch);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 0, 0, -1, func_8010BE84_etch_n_catch);
    func_800E18D8_minigame();
    D_800EB740_minigame = 0.5f;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 5, 0x3C, -1, func_80106334_etch_n_catch);
        omSetStatBit(D_800EC598_minigame[i], 0xA0);
        D_801113D8_etch_n_catch[i] = HuMemAllocTag(256 * sizeof(EtNode), 0x7918);
        memset(D_801113D8_etch_n_catch[i], 0, 256 * sizeof(EtNode));
    }
    for (i = 0; i < 2; i++) {
        D_8010C860_etch_n_catch[i] = omAddObj(2, 3, 0, -1, func_8010B24C_etch_n_catch);
        D_8010C858_etch_n_catch[i] = omAddObj(2, 7, 2, -1, func_80109A54_etch_n_catch);
    }
    omAddObj(3, 0, 0, -1, func_8010BBE4_etch_n_catch);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105CD0_etch_n_catch(EtCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 60;
    ctrl->unk00 = 0;
    ctrl->unk01 = 1;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 0;
    ctrl->unk1C = 90;
    ctrl->unk1E = 900;
    ctrl->unk20 = -1;
    ctrl->unk22 = 75;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105D5C_etch_n_catch(void) {
    s32 cam;
    HuCamera* c;

    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 27.211f, 80.0f, 8000.0f);
    c = &gCameraList[cam];
    c->pos.x = -1.965f;
    c->pos.y = 1392.72f;
    c->pos.z = 1374.455f;
    c->at.x = -1.965f;
    c->at.y = 60.495f;
    c->at.z = 20.66f;
    c->up.x = 0.0f;
    c->up.y = 0.5f;
    c->up.z = -0.8660254f;
}

#ifdef NON_MATCHING
void func_80105ED4_etch_n_catch(omObjData* obj) {
    s32 voice;
    s8 i;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010C6D8_etch_n_catch == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010C6D8_etch_n_catch = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x38;
                break;
            case 2:
                if (D_8010C6AC_etch_n_catch >= 5 || D_8010C6AD_etch_n_catch >= 5) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (func_800E6E9C_minigame() == 74.0) {
                    if (D_8010C6AC_etch_n_catch == D_8010C6AD_etch_n_catch) {
                        D_801113B0_etch_n_catch.unk06 = 4;
                    } else {
                        D_801113B0_etch_n_catch.unk06 = 1;
                        for (i = 0; i < 4; i++) {
                            if (D_8010C6AC_etch_n_catch > D_8010C6AD_etch_n_catch && GwPlayer[i].group == 0) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            } else if (D_8010C6AC_etch_n_catch < D_8010C6AD_etch_n_catch && GwPlayer[i].group == 1) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            }
                        }
                    }
                }
                break;
            case 4:
                if (D_800EB934_minigame != 0) {
                    for (i = 0; i < 4; i++) {
                        if (D_801113B0_etch_n_catch.unk06 == 1
                            && (i == D_801113B0_etch_n_catch.unk18[0] || i == D_801113B0_etch_n_catch.unk18[1])) {
                            func_800E5690_minigame(D_800EC598_minigame[i], 13);
                            switch (GwPlayer[i].chr) {
                                case 0:
                                default:
                                    voice = 2;
                                    break;
                                case 1:
                                    voice = 3;
                                    break;
                                case 2:
                                    voice = 7;
                                    break;
                                case 3:
                                    voice = 4;
                                    break;
                                case 4:
                                    voice = 5;
                                    break;
                                case 5:
                                    voice = 6;
                                    break;
                                case 6:
                                    voice = 8;
                                    break;
                                case 7:
                                    voice = 9;
                                    break;
                            }
                            func_8004AD70_main();
                            func_80045ED0_main((voice << 16) | 0x2F);
                        } else {
                            func_800E5690_minigame(D_800EC598_minigame[i], 14);
                        }
                    }
                }
                break;
            case 5:
                if (D_8010C6D4_etch_n_catch == 0) {
                    WipeCreateOut(0, 20);
                    func_8010C2F4_etch_n_catch();
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010C6D4_etch_n_catch++;
                break;
        }
        Hu3DCamSetPositionOrientation(0, &gCameraList->pos, &gCameraList->at, &gCameraList->up);
        Hu3DCamUpdateMtx(0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105ED4_etch_n_catch);
#endif

/* A player object: places the player at its team's start, loads its pen and models. */
#ifdef NON_MATCHING
void func_80106334_etch_n_catch(omObjData* obj) {
    Vec pos0a[2] = { { -350.0f, 1000.0f, -200.0f }, { -150.0f, 1000.0f, 250.0f } };
    Vec pos0b[2] = { { -150.0f, 1000.0f, 250.0f }, { -350.0f, 1000.0f, -200.0f } };
    Vec pos1a[2] = { { 150.0f, 1000.0f, -200.0f }, { 350.0f, 1000.0f, 250.0f } };
    Vec pos1b[2] = { { 350.0f, 1000.0f, 250.0f }, { 150.0f, 1000.0f, -200.0f } };
    s8 chr;
    s32 dir;
    s32 file;
    s32 i;
    MgWork* pw;
    EtchNCatchWork* w;
    Vec* p;
    s32 mdl;
    f32 dx;

    chr = GwPlayer[D_8010C6D9_etch_n_catch].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(obj, dir, file, D_8010C6D9_etch_n_catch, 0xAA9, 0xAB9);
    pw = obj->data;
    D_800EB784_minigame[pw->unk59][0] = -1;
    D_800EB784_minigame[pw->unk59][1] = -1;
    pw->unk3C = 0.0f;
    D_8010C868_etch_n_catch[D_8010C6D9_etch_n_catch] = w = HuMemAllocTag(sizeof(EtchNCatchWork), 0x7918);
    memset(w, 0, sizeof(EtchNCatchWork));
    func_80108B20_etch_n_catch(w);
    obj->rot.y = 0.0f;
    obj->rot.x = obj->rot.z = obj->rot.y;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.75f;
    if (D_8010C6D9_etch_n_catch == 0) {
        D_8010C830_etch_n_catch = (u32)(rand8() * 5) >> 7;
    }
    switch (GwPlayer[pw->unk59].group) {
        case 0:
            if (!(D_8010C830_etch_n_catch & 1)) {
                p = &pos0a[D_8010C6DA_etch_n_catch[0]];
            } else {
                p = &pos0b[D_8010C6DA_etch_n_catch[0]];
            }
            obj->trans.x = p->x;
            obj->trans.y = p->y;
            obj->trans.z = p->z;
            w->unk02 = 8;
            w->unk01 = 3;
            w->unk00 = (D_8010C6DA_etch_n_catch[0] == 0) ? 1 : 2;
            func_800E149C_minigame(obj, 0, 2);
            func_800E149C_minigame(obj, 1, 1);
            D_8010C6DA_etch_n_catch[0]++;
            break;
        case 1:
            if (!(D_8010C830_etch_n_catch & 1)) {
                p = &pos1a[D_8010C6DA_etch_n_catch[1]];
            } else {
                p = &pos1b[D_8010C6DA_etch_n_catch[1]];
            }
            obj->trans.x = p->x;
            obj->trans.y = p->y;
            obj->trans.z = p->z;
            w->unk02 = 1;
            w->unk01 = 12;
            w->unk00 = (D_8010C6DA_etch_n_catch[1] == 0) ? 4 : 8;
            func_800E149C_minigame(obj, 0, 1);
            func_800E149C_minigame(obj, 1, 2);
            D_8010C6DA_etch_n_catch[1]++;
            break;
    }
    w->unk0A = 0;
    w->unk08 = 0;
    w->unk14 = 0;
    w->unk18 = 0;
    w->unk17 = 0;
    w->unk1C = 0;
    w->unk12 = 0;
    w->unk10 = 0;
    obj->func = func_80106A64_etch_n_catch;
    dx = sindf(pw->unk3C) * 65.0f * 0.75f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x - dx, 0.0f, obj->trans.z - cosdf(pw->unk3C) * 65.0f * 0.75f);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    if (w->unk02 == 8) {
        mdl = 0x330000;
    } else {
        mdl = 0x330001;
    }
    obj->model[2] = func_8000B108_main(mdl, 0xAB9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C814_main(obj->model[2], 2, 1);
    obj->model[3] = func_8000B108_main(3, 0x89D);
    obj->model[4] = func_8000B108_main(4, 0x89D);
    for (i = 0; i < 3; i++) {
        if (i == 0 && pw->unk59 == 0) {
            D_80111390_etch_n_catch[0][0] = func_8000B0D4_main(0x330006, 0x28D);
        } else {
            D_80111390_etch_n_catch[pw->unk59][i] = Hu3DModelLink(D_80111390_etch_n_catch[0][0]);
        }
        func_8001C814_main(D_80111390_etch_n_catch[pw->unk59][i], 2, 2);
        func_8001FA68_main(D_80111390_etch_n_catch[pw->unk59][i]);
    }
    func_800E1328_minigame(obj, 46.875f);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0x47), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 0x48), 1, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5690_minigame(obj, 0);
    D_8010C6D9_etch_n_catch++;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C740_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C758_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C770_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C788_etch_n_catch);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106334_etch_n_catch);
#endif

/* A player each frame: drop-in during the intro; then pen input (CPU or stick, turn-limited), collisions with the
   pen tips pushed out, pen model, and in play the trail: every grid cell the pen crosses gets a node and its marks.
   Player 3's object also runs the area checks for both teams (one per frame) and ages every player's trail. */
#ifdef NON_MATCHING
void func_80106A64_etch_n_catch(omObjData* obj) {
    EtNode* near[32];
    Vec pos;
    Vec2f scr;
    EtVec2 d;
    f32 dx[4];
    f32 dz[4];
    f32 px[4];
    f32 pz[4];
    MgWork* pw;
    MgWork* ow;
    EtNode* n;
    EtNode* m;
    s32 side;
    s32 i;
    s32 j;
    s32 found;
    s32 cnt;
    s32 cx;
    s32 cy;
    s32 btn;
    f32 fx;
    f32 fz;

    if (func_80049F98_main() + D_800D6A90_main != 0 || func_800E6E8C_minigame() == 5) {
        return;
    }
    pw = obj->data;
    D_8010C838_etch_n_catch = D_8010C868_etch_n_catch[pw->unk59];
    if (func_800E6E8C_minigame() == 0) {
        if (D_8010C860_etch_n_catch[0]->work[0] != 3) {
            Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 0.0f);
        } else {
            obj->trans.y -= D_8010C834_etch_n_catch + 5.0f;
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
            } else if (pw->unk59 == 0) {
                D_8010C834_etch_n_catch += 5.0f;
                D_8010C6DC_etch_n_catch += 0.05f;
                if (D_8010C6DC_etch_n_catch > 0.75f) {
                    D_8010C6DC_etch_n_catch = 0.75f;
                }
            }
            func_800DDD94_minigame(obj);
            Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
            func_8010C628_etch_n_catch(obj, 0.75f);
            fx = sindf(pw->unk3C) * 65.0f * 0.75f;
            Hu3DModelPosSet(obj->model[1], obj->trans.x - fx, 0.0f, obj->trans.z - cosdf(pw->unk3C) * 65.0f * 0.75f);
            Hu3DModelScaleSet(obj->model[1], D_8010C6DC_etch_n_catch, obj->scale.y, D_8010C6DC_etch_n_catch);
        }
        return;
    }
    btn = D_800D5558_main[pw->unk57];
    D_800D5558_main[pw->unk57] = 0;
    side = (obj->trans.x < 0.0f) ? 0 : 1;
    if ((u32)D_8010C858_etch_n_catch[side]->work[0] >= 6 || D_8010C860_etch_n_catch[side]->work[0] != 3) {
        D_800CBB6E_main[pw->unk57] = 0;
        D_800D20A1_main[pw->unk57] = 0;
    }
    if (GwPlayer[pw->unk59].stat & 1) {
        func_80107EA4_etch_n_catch(obj);
    }
    pw->unk40 *= 0.9f;
    func_8010880C_etch_n_catch(pw);
    /* collide with the pen tips: move every player to its pen tip for the framework's collision pass */
    for (i = 0; i < 4; i++) {
        px[i] = D_800EC598_minigame[i]->trans.x;
        pz[i] = D_800EC598_minigame[i]->trans.z;
        ow = D_800EC598_minigame[i]->data;
        dx[i] = sindf(ow->unk3C) * 46.875f;
        dz[i] = cosdf(ow->unk3C) * 46.875f;
        D_800EC598_minigame[i]->trans.x -= dx[i];
        D_800EC598_minigame[i]->trans.z -= dz[i];
    }
    (void)px; /* retail saves the positions and never reads them */
    (void)pz;
    func_800DDD94_minigame(obj);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i]->trans.x += dx[i];
        D_800EC598_minigame[i]->trans.z += dz[i];
    }
    fx = sindf(pw->unk3C) * 65.0f * 0.75f;
    fz = cosdf(pw->unk3C) * 65.0f * 0.75f;
    switch (func_800E6E8C_minigame()) {
        case 3:
            if (func_800E6E9C_minigame() == 0) {
                func_800E1328_minigame(obj, 60.0f);
                obj->trans.x -= fx;
                obj->trans.z -= fz;
            }
            if (pw->unk3C == 0.0f) {
                Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
            } else {
                Hu3DModelPosSet(obj->model[1], obj->trans.x - fx, 0.0f, obj->trans.z - fz);
            }
            break;
        case 4:
        case 5:
            Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
            break;
        default:
            Hu3DModelPosSet(obj->model[1], obj->trans.x - fx, 0.0f, obj->trans.z - fz);
            break;
    }
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, pw->unk3C, obj->rot.z);
    if (func_800E4A90_minigame(obj) == 2) {
        func_8001C814_main(obj->model[2], 2, 1);
    } else {
        func_8001C814_main(obj->model[2], 2, 2);
    }
    switch (func_800E6E8C_minigame()) {
        case 0:
        case 1:
        case 5:
            func_8010C628_etch_n_catch(obj, 0.75f);
            return; /* retail: skips the button restore below */
        case 3:
            if (func_800E6E9C_minigame() == 0) {
                func_8001C258_main(obj->model[2], 4, 4);
                func_800E5690_minigame(obj, 38);
            }
            pw->unk3C = func_8010C4F8_etch_n_catch(pw->unk3C);
            if (pw->unk3C < 0.0f) {
                pw->unk3C += 360.0f;
            } else if (pw->unk3C > 360.0f) {
                pw->unk3C -= 360.0f;
            }
            if (pw->unk3C > 10.0f && pw->unk3C < 180.0f) {
                pw->unk3C -= 10.0f;
            } else if (pw->unk3C >= 180.0f && pw->unk3C < 350.0f) {
                pw->unk3C += 10.0f;
            } else {
                pw->unk3C = 0.0f;
            }
            func_8010C628_etch_n_catch(obj, 0.75f);
            break;
    }
    pos.x = obj->trans.x;
    pos.y = obj->trans.y;
    pos.z = obj->trans.z;
    func_80012B14_main(0, &pos, &scr);
    /* retail compares each (x, y) cell pair as one word */
    if (D_8010C838_etch_n_catch->unk08 != D_8010C838_etch_n_catch->unk04 || D_8010C838_etch_n_catch->unk0A != D_8010C838_etch_n_catch->unk06) {
        D_8010C838_etch_n_catch->unk08 = D_8010C838_etch_n_catch->unk04;
        D_8010C838_etch_n_catch->unk0A = D_8010C838_etch_n_catch->unk06;
    }
    D_8010C838_etch_n_catch->unk04 = scr.x;
    D_8010C838_etch_n_catch->unk06 = scr.y;
    if (func_800E6E8C_minigame() == 2) {
        if (D_8010C838_etch_n_catch->unk12 == 0 && (pw->unk5C & 4) && HmfModelData[obj->model[0]].unk40 == 0.0f) {
            D_8010C838_etch_n_catch->unk10 = func_8004ACE0_main(0x37F, pw->unk59);
            if (D_8010C838_etch_n_catch->unk02 == 8) {
                func_8004AE00_main(D_8010C838_etch_n_catch->unk10, 0x20);
            } else {
                func_8004AE00_main(D_8010C838_etch_n_catch->unk10, 0x5F);
            }
            D_8010C838_etch_n_catch->unk12 = 1;
        } else if (D_8010C838_etch_n_catch->unk12 == 1 && pw->unk40 == D_800EB770_minigame) {
            HuAudFXStop(D_8010C838_etch_n_catch->unk10);
            D_8010C838_etch_n_catch->unk12 = 0;
        }
    } else if (func_800E6E8C_minigame() == 3) {
        HuAudFXStop(D_8010C838_etch_n_catch->unk10);
        D_8010C838_etch_n_catch->unk12 = 0;
    }
    if (func_800E6E8C_minigame() == 2 && D_8010C838_etch_n_catch->unk08 != 0 && D_8010C838_etch_n_catch->unk0A != 0 && (D_8010C838_etch_n_catch->unk08 != D_8010C838_etch_n_catch->unk04 || D_8010C838_etch_n_catch->unk0A != D_8010C838_etch_n_catch->unk06)) {
        do {
            n = func_80108B28_etch_n_catch(pw->unk59);
            memset(n, 0, sizeof(EtNode));
            n->unk00 = 1;
            n->unk16 = 106;
            n->unk18 = D_8010C838_etch_n_catch->unk08;
            n->unk1A = D_8010C838_etch_n_catch->unk0A;
            n->unk1C = pw->unk59;
            n->unk10 = NULL;
            n->unk0C = NULL;
            n->next = NULL;
            n->prev = NULL;
            func_80108B64_etch_n_catch(&D_8010C838_etch_n_catch->unk_0C, n);
            n->unk2C = 0;
            n->unk30 = 1.0f;
            switch (rand8() >> 6) {
                case 0:
                    n->unk20.x = obj->trans.x + 10.0f;
                    n->unk20.z = obj->trans.z + 10.0f;
                    break;
                case 1:
                    n->unk20.x = obj->trans.x - 10.0f;
                    n->unk20.z = obj->trans.z - 10.0f;
                    break;
                case 2:
                    n->unk20.x = obj->trans.x + 10.0f;
                    n->unk20.z = obj->trans.z - 10.0f;
                    break;
                default:
                    n->unk20.x = obj->trans.x - 10.0f;
                    n->unk20.z = obj->trans.z + 10.0f;
                    break;
            }
            n->unk20.y = obj->trans.y;
            found = 0;
            if (func_80109114_etch_n_catch(D_8010C838_etch_n_catch->unk08, D_8010C838_etch_n_catch->unk0A) == D_8010C838_etch_n_catch->unk02) {
                /* continue the trail of the node already on this cell */
                for (i = 0; i < 4 && found != 1; i++) {
                    for (m = D_8010C868_etch_n_catch[i]->unk_0C; m != NULL; m = m->next) {
                        /* retail compares the cell (x, y) as one word */
                        if (n != m && m->unk18 == n->unk18 && m->unk1A == n->unk1A) {
                            while (m->unk0C != NULL) {
                                m = m->unk0C;
                            }
                            found = 1;
                            m->unk0C = n;
                            n->unk10 = m;
                            break;
                        }
                    }
                }
            }
            n->unk14 |= D_8010C838_etch_n_catch->unk00;
            func_8010914C_etch_n_catch(D_8010C838_etch_n_catch->unk08, D_8010C838_etch_n_catch->unk0A, D_8010C838_etch_n_catch->unk02);
            n->unk15 = D_8010C838_etch_n_catch->unk02;
            D_8010C890_etch_n_catch[D_8010C838_etch_n_catch->unk06 / 2][D_8010C838_etch_n_catch->unk04 / 2] |= D_8010C838_etch_n_catch->unk00;
            if ((D_800CBB6E_main[pw->unk57] != 0 || D_800D20A1_main[pw->unk57] != 0) && func_80108C08_etch_n_catch(D_8010C838_etch_n_catch) != 0) {
                if (obj->trans.x < 0.0f) {
                    D_8010C6E0_etch_n_catch = 1;
                } else {
                    D_8010C6E1_etch_n_catch = 1;
                }
            }
            d = func_8010C574_etch_n_catch(D_8010C838_etch_n_catch->unk08, D_8010C838_etch_n_catch->unk0A, D_8010C838_etch_n_catch->unk04, D_8010C838_etch_n_catch->unk06);
            if (d.x <= -0.5f) {
                D_8010C838_etch_n_catch->unk08--;
            } else if (d.x >= 0.5f) {
                D_8010C838_etch_n_catch->unk08++;
            }
            if (d.y <= -0.5f) {
                D_8010C838_etch_n_catch->unk0A--;
            } else if (d.y >= 0.5f) {
                D_8010C838_etch_n_catch->unk0A++;
            }
        } while (D_8010C838_etch_n_catch->unk08 != D_8010C838_etch_n_catch->unk04 || D_8010C838_etch_n_catch->unk0A != D_8010C838_etch_n_catch->unk06);
    }
    if (pw->unk59 == 3) {
        /* one team's area check per frame */
        if (D_8010C6E2_etch_n_catch == 0) {
            if (D_8010C6E0_etch_n_catch != 0 && D_8010C860_etch_n_catch[0]->work[0] == 3
                && (u32)D_8010C858_etch_n_catch[0]->work[0] < 5) {
                D_8010C858_etch_n_catch[0]->work[1] =
                    func_80108DD0_etch_n_catch(D_8010C850_etch_n_catch[0][0], D_8010C850_etch_n_catch[0][1]);
                if (D_8010C858_etch_n_catch[0]->work[1] != 0) {
                    D_8010C858_etch_n_catch[0]->work[0] = 5;
                    for (i = 0; i < 4; i++) {
                        if (D_8010C868_etch_n_catch[i]->unk01 == 3) {
                            omVibrate(((MgWork*)D_800EC598_minigame[i]->data)->unk59, 2, 3, 10);
                        }
                    }
                }
                D_8010C6E0_etch_n_catch = 0;
            }
        } else if (D_8010C6E1_etch_n_catch != 0 && D_8010C860_etch_n_catch[1]->work[0] == 3
                   && (u32)D_8010C858_etch_n_catch[1]->work[0] < 5) {
            D_8010C858_etch_n_catch[1]->work[1] =
                func_80108DD0_etch_n_catch(D_8010C850_etch_n_catch[1][0], D_8010C850_etch_n_catch[1][1]);
            if (D_8010C858_etch_n_catch[1]->work[1] != 0) {
                D_8010C858_etch_n_catch[1]->work[0] = 5;
                for (i = 0; i < 4; i++) {
                    if (D_8010C868_etch_n_catch[i]->unk01 == 12) {
                        omVibrate(((MgWork*)D_800EC598_minigame[i]->data)->unk59, 2, 3, 10);
                    }
                }
            }
            D_8010C6E1_etch_n_catch = 0;
        }
        D_8010C6E2_etch_n_catch ^= 1;
    }
    func_8010C628_etch_n_catch(obj, 0.75f);
    /* the catcher of this side stands on the trail: make the nodes around it (and their older nodes) expire */
    cx = D_8010C850_etch_n_catch[side][0] * 2;
    cy = D_8010C850_etch_n_catch[side][1] * 2;
    if (func_8010B154_etch_n_catch(cx, cy) != 0) {
        for (i = 0; i < 32; i++) {
            near[i] = NULL;
        }
        cnt = 0;
        for (m = D_8010C838_etch_n_catch->unk_0C; m != NULL; m = m->next) {
            if (ET_IABS(cx - m->unk18) < 2 && ET_IABS(cy - m->unk1A) < 2) {
                near[cnt++] = m;
            }
        }
        for (i = 0; i < cnt; i++) {
            for (m = near[i]; m != NULL; m = m->prev) {
                m->unk16 = 17;
            }
        }
    }
    if (pw->unk59 == 3) {
        /* age every trail node: at 16 it is taken off the grid, then its puff plays, then it is freed */
        for (j = 0; j < 4; j++) {
            D_8010C838_etch_n_catch = D_8010C868_etch_n_catch[j];
            if (D_8010C838_etch_n_catch != NULL) {
                for (m = D_8010C838_etch_n_catch->unk_0C; m != NULL; m = m->next) {
                    m->unk16--;
                    if (m->unk16 < 17) {
                        if (m->unk16 == 16) {
                            for (i = 0; i < 4; i++) {
                                if (m->unk0C != NULL) {
                                    if (m->unk0C->unk15 != D_8010C868_etch_n_catch[i]->unk02) {
                                        D_8010C890_etch_n_catch[m->unk1A / 2][m->unk18 / 2] &= ~D_8010C868_etch_n_catch[i]->unk00;
                                    }
                                } else {
                                    D_8010C890_etch_n_catch[m->unk1A / 2][m->unk18 / 2] &= ~D_8010C868_etch_n_catch[i]->unk00;
                                }
                            }
                            func_80109370_etch_n_catch(m, D_8010C838_etch_n_catch->unk02);
                        } else if (m->unk16 > 0) {
                            if (m->unk1E != -1) {
                                func_801097B4_etch_n_catch(m);
                            }
                        } else {
                            func_8001C258_main(m->unk1E, 4, 4);
                            func_80108BCC_etch_n_catch(&D_8010C838_etch_n_catch->unk_0C, m);
                        }
                    }
                }
            }
        }
        D_800D5558_main[pw->unk57] = btn;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106A64_etch_n_catch);
#endif

/* Whether (x, z) is outside the drawing area of the player's team. */
s32 func_80107D38_etch_n_catch(f32 x, f32 z, EtchNCatchWork* w) {
    if (w->unk01 == 3) {
        if ((x < -80.0f) & (x > -450.0f)) {
            if ((z < 300.0f) & (z > -400.0f)) {
                return FALSE;
            }
        }
        return TRUE;
    }
    if ((x > 80.0f) & (x < 450.0f)) {
        if ((z < 300.0f) & (z > -400.0f)) {
            return FALSE;
        }
    }
    return TRUE;
}

/* CPU player input: chases a point beside its team's catcher, then circles the catcher (D_8010C6E4 state 0 approach,
   1 turn to face along the pen, 2 circle); radius and speed by difficulty. Steers away from the area's edge. */
#ifdef NON_MATCHING
void func_80107EA4_etch_n_catch(omObjData* obj) {
    MgWork* pw = obj->data;
    EtchNCatchWork* w = D_8010C868_etch_n_catch[pw->unk59];
    omObjData* c;
    EtVec2 v;
    f32 radius;
    s32 speed;
    s32 side;
    f32 x;
    f32 z;

    if (func_800E6E8C_minigame() == 2) {
        switch (GwPlayer[pw->unk59].cpu_difficulty) {
            case 3:
                speed = 60;
                radius = 200.0f;
                break;
            case 2:
                radius = 250.0f;
                speed = 60;
                break;
            case 1:
            default:
                radius = 300.0f;
                speed = 57;
                break;
            case 0:
                speed = 54;
                radius = 350.0f;
                break;
        }
        side = (obj->trans.x < 0.0f) ? 0 : 1;
        if ((u32)D_8010C858_etch_n_catch[side]->work[0] >= 6 || D_8010C860_etch_n_catch[side]->work[0] != 3) {
            D_800CBB6E_main[pw->unk57] = 0;
            D_800D20A1_main[pw->unk57] = 0;
            return;
        }
        if (obj->trans.x < 0.0f) {
            c = D_8010C858_etch_n_catch[0];
        } else {
            c = D_8010C858_etch_n_catch[1];
        }
        x = ET_ABS(c->trans.x - obj->trans.x);
        z = ET_ABS(c->trans.z - obj->trans.z);
        if (HuSqrtf(x * x + z * z) > 375.0f) {
            D_8010C6E4_etch_n_catch[pw->unk59] = 0;
        }
        switch (D_8010C6E4_etch_n_catch[pw->unk59]) {
            case 0:
                if ((w->unk00 == 1) | (w->unk00 == 4)) {
                    z = c->trans.z - 75.0f;
                } else {
                    z = c->trans.z + 75.0f;
                }
                v = func_8010C574_etch_n_catch(obj->trans.x, obj->trans.z, c->trans.x, z);
                D_800CBB6E_main[pw->unk57] = speed * v.x;
                D_800D20A1_main[pw->unk57] = -(speed * v.y);
                x = ET_ABS(c->trans.x - obj->trans.x);
                if ((w->unk00 == 1) | (w->unk00 == 4)) {
                    z = ET_ABS((c->trans.z - 75.0f) - obj->trans.z);
                } else {
                    z = ET_ABS((c->trans.z + 75.0f) - obj->trans.z);
                }
                if (HuSqrtf(x * x + z * z) < 50.0f) {
                    D_8010C6E4_etch_n_catch[pw->unk59] = 1;
                }
                break;
            case 1:
                if ((w->unk00 == 1) | (w->unk00 == 4)) {
                    pw->unk3C = func_8010C4F8_etch_n_catch(pw->unk3C);
                    if (ET_ABS(pw->unk3C - 90.0f) < 5.0f) {
                        pw->unk3C = 90.0f;
                        D_8010C6E4_etch_n_catch[pw->unk59] = 2;
                    } else {
                        D_800CBB6E_main[pw->unk57] = speed >> 1;
                        D_800D20A1_main[pw->unk57] = 0;
                    }
                }
                if ((w->unk00 == 2) | (w->unk00 == 8)) {
                    pw->unk3C = func_8010C4F8_etch_n_catch(pw->unk3C);
                    if (ET_ABS(pw->unk3C - 270.0f) < 5.0f) {
                        pw->unk3C = 270.0f;
                        D_8010C6E4_etch_n_catch[pw->unk59] = 2;
                    } else {
                        D_800CBB6E_main[pw->unk57] = -speed / 2;
                        D_800D20A1_main[pw->unk57] = 0;
                    }
                }
                break;
            case 2:
                pw->unk3C += 5.0f;
                if (pw->unk3C > 360.0f) {
                    pw->unk3C -= 360.0f;
                }
                radius += 75.0f;
                x = sindf(pw->unk3C) * radius + c->trans.x;
                v = func_8010C574_etch_n_catch(obj->trans.x, obj->trans.z, x,
                                               cosdf(pw->unk3C) * radius + c->trans.z);
                D_800CBB6E_main[pw->unk57] = speed * v.x;
                D_800D20A1_main[pw->unk57] = -(speed * v.y);
                break;
        }
        x = sindf(pw->unk3C) * 65.0f * 0.75f + obj->trans.x;
        if (func_80107D38_etch_n_catch(x, cosdf(pw->unk3C) * 65.0f * 0.75f + obj->trans.z, w) != 0) {
            pw->unk3C += 20.0f;
            if (pw->unk3C > 360.0f) {
                pw->unk3C -= 360.0f;
            }
            x = sindf(pw->unk3C) * 10.0f + obj->trans.x;
            v = func_8010C574_etch_n_catch(obj->trans.x, obj->trans.z, x, cosdf(pw->unk3C) * 10.0f + obj->trans.z);
            D_800CBB6E_main[pw->unk57] = speed * v.x;
            D_800D20A1_main[pw->unk57] = -(speed * v.y);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107EA4_etch_n_catch);
#endif

/* Limits how fast the player's stick direction may turn: rewrites the stick input so that its angle moves at
   most 30 degrees a frame from the facing pw->unk3C, keeping its magnitude. */
void func_8010880C_etch_n_catch(MgWork* pw) {
    f32 sx;
    f32 sy;
    f32 target;
    f32 d;
    f32 mag;

    sx = D_800CBB6E_main[pw->unk57];
    sy = -D_800D20A1_main[pw->unk57];
    if (ET_FABS(sx) < 8.0f && ET_FABS(sy) < 8.0f) {
        target = pw->unk3C;
    } else {
        target = atan2df(sx, sy);
    }
    target = func_8010C4F8_etch_n_catch(target);
    pw->unk3C = func_8010C4F8_etch_n_catch(pw->unk3C);
    d = target - pw->unk3C;
    if (ET_ABS(d) > 30.0f) {
        if (((d > 0.0f) & (d < 180.0f)) || ((d < -180.0f) & (d > -360.0f))) {
            target = pw->unk3C + 30.0f;
        } else {
            target = pw->unk3C - 30.0f;
        }
    } else {
        target = d + pw->unk3C;
    }
    target = func_8010C4F8_etch_n_catch(target);
    mag = HuSqrtf(sx * sx + sy * sy);
    D_800CBB6E_main[pw->unk57] = sindf(target) * mag;
    D_800D20A1_main[pw->unk57] = -cosdf(target) * mag;
}

void func_80108B20_etch_n_catch(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

/* A free trail node of the player's pool (one past the pool when all 256 are used). */
EtNode* func_80108B28_etch_n_catch(s8 player) {
    EtNode* node = D_801113D8_etch_n_catch[player];
    s32 i;

    for (i = 0; i < 256; i++, node++) {
        if (node->unk00 == 0) {
            break;
        }
    }
    return node;
}

/* Appends `node` to the list at `head`. */
void func_80108B64_etch_n_catch(EtNode** head, EtNode* node) {
    EtNode* last = *head;

    if (last != NULL) {
        while (last->next != NULL) {
            last = last->next;
        }
        node->next = last->next;
        node->prev = last;
        last->next = node;
        if (node->next != NULL) {
            node->next->prev = node;
        }
    } else {
        node->next = *head;
        node->prev = NULL;
        *head = node;
        if (last != NULL) {
            last->prev = node;
        }
    }
}

/* Unlinks `node` from the list at `head` and frees it. */
void func_80108BCC_etch_n_catch(EtNode** head, EtNode* node) {
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }
    node->unk00 = 0;
}

/* Whether three or more trail nodes of any player lie around the pen of `w`. */
s32 func_80108C08_etch_n_catch(EtchNCatchWork* w) {
    s32 n = 0;
    s32 i;
    EtNode* node;

    if (D_8010C868_etch_n_catch[0]->unk_0C == NULL && D_8010C868_etch_n_catch[1]->unk_0C == NULL
        && D_8010C868_etch_n_catch[2]->unk_0C == NULL && D_8010C868_etch_n_catch[3]->unk_0C == NULL) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        for (node = D_8010C868_etch_n_catch[i]->unk_0C; node != NULL; node = node->next) {
            if (node->unk18 == w->unk04 - 1) {
                n += node->unk1A == w->unk06 - 1;
                n += node->unk1A == w->unk06;
                n += node->unk1A == w->unk06 + 1;
            }
            if (node->unk18 == w->unk04) {
                n += node->unk1A == w->unk06 - 1;
                n += node->unk1A == w->unk06 + 1;
            }
            if (node->unk18 == w->unk04 + 1) {
                n += node->unk1A == w->unk06 - 1;
                n += node->unk1A == w->unk06;
                n += node->unk1A == w->unk06 + 1;
            }
            if (n >= 3) {
                return 1;
            }
        }
    }
    return 0;
}

/* Clears the fill mark (0x21) of every cell visited since the start of D_8010C878 up to `end`. */
void func_80108D84_etch_n_catch(u8** end) {
    u8** p = D_8010C878_etch_n_catch;
    s32 n = end - p;
    u8* c;
    s32 i;

    for (i = 0; i < n; i++) {
        c = *p++;
        if (*c == 0x21) {
            *c = 0;
        }
    }
}

/* Flood-fills the empty area around grid cell (2x, 2y). Returns 0 if it reaches a 0x22 cell, otherwise whether
   the walls it meets belong to one team only (region bits 3 or 12). The fill marks are cleared again. */
// masked 31 (H1, was 52): retail multiplies y by (width << 1) where GCC here moves the shift onto y, then the
// loop's registers differ throughout; row is (d / 320) >> 1 as retail computes it
#ifdef NON_MATCHING
s32 func_80108DD0_etch_n_catch(s16 x, s16 y) {
    s32 bits = 0;
    u8* cell;
    u8* c;
    u8** vis;
    u8** cur;
    u8** next;
    u8** curBuf;
    u8** nextBuf;
    u8*** fr;
    s32 n;
    s32 i;
    s32 col;
    s32 row;

    cell = D_8010C84C_etch_n_catch + x * 2 + y * (D_8010C846_etch_n_catch * 2);
    vis = D_8010C878_etch_n_catch;
    fr = D_8010C87C_etch_n_catch;
    *cell = 0x21;
    *vis = cell;
    fr[0][0] = cell;
    vis++;
    n = 1;
    next = nextBuf = fr[1];
    cur = curBuf = fr[0];
    do {
        for (i = 0; i < n; i++) {
            c = *cur++;
            *c = 0x21;
            col = ((c - D_8010C84C_etch_n_catch) % 320) >> 1;
            row = ((c - D_8010C84C_etch_n_catch) / 320) >> 1;
            c++;
            if (*c == 0) {
                *c = 0x21;
                *vis++ = c;
                *next++ = c;
            } else if (*c == 0x22) {
                func_80108D84_etch_n_catch(vis);
                return 0;
            } else if (!(*c & 9)) {
                *vis++ = c;
            } else {
                bits |= D_8010C890_etch_n_catch[row][col + 1];
            }
            c -= 2;
            if (*c == 0) {
                *c = 0x21;
                *vis++ = c;
                *next++ = c;
            } else if (*c == 0x22) {
                func_80108D84_etch_n_catch(vis);
                return 0;
            } else if (!(*c & 9)) {
                *vis++ = c;
            } else {
                bits |= D_8010C890_etch_n_catch[row][col - 1];
            }
            c += D_8010C846_etch_n_catch + 1;
            if (*c == 0) {
                *c = 0x21;
                *vis++ = c;
                *next++ = c;
            } else if (*c == 0x22) {
                func_80108D84_etch_n_catch(vis);
                return 0;
            } else if (!(*c & 9)) {
                *vis++ = c;
            } else {
                bits |= D_8010C890_etch_n_catch[row + 1][col];
            }
            c -= D_8010C846_etch_n_catch * 2;
            if (*c == 0) {
                *c = 0x21;
                *vis++ = c;
                *next++ = c;
            } else if (*c == 0x22) {
                func_80108D84_etch_n_catch(vis);
                return 0;
            } else if (!(*c & 9)) {
                *vis++ = c;
            } else {
                bits |= D_8010C890_etch_n_catch[row - 1][col];
            }
        }
        n = next - nextBuf;
        next = curBuf;
        curBuf = nextBuf;
        nextBuf = next;
        cur = curBuf;
    } while (n != 0);
    func_80108D84_etch_n_catch(vis);
    return (bits == 3) | (bits == 12);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108DD0_etch_n_catch);
#endif

u8* func_801090E0_etch_n_catch(s16 x, s16 y) {
    return D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
}

u8 func_80109114_etch_n_catch(s16 x, s16 y) {
    u8* p = D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;

    return *p;
}

/* Sets cell (x, y) to `v`, its 4 neighbours to v * 2 and its diagonal neighbours to v * 4, unless already set. */
// H1: masked 17; retail takes x/y unextended (s32 parameters, extended at each call) and keeps two copies of x, y and v;
// s32 parameters alone give masked 21
#ifdef NON_MATCHING
void func_8010914C_etch_n_catch(s16 x, s16 y, s32 v) {
    u8* p;

    *func_801090E0_etch_n_catch(x, y) = v;
    p = func_801090E0_etch_n_catch(x - 1, y);
    if (*p != (u8)v) {
        *p = v * 2;
    }
    p = func_801090E0_etch_n_catch(x + 1, y);
    if (*p != (u8)v) {
        *p = v * 2;
    }
    p = func_801090E0_etch_n_catch(x, y - 1);
    if (*p != (u8)v) {
        *p = v * 2;
    }
    p = func_801090E0_etch_n_catch(x, y + 1);
    if (*p != (u8)v) {
        *p = v * 2;
    }
    p = func_801090E0_etch_n_catch(x - 1, y - 1);
    if (*p != (u8)v && *p != (u8)v * 2) {
        *p = v * 4;
    }
    p = func_801090E0_etch_n_catch(x - 1, y + 1);
    if (*p != (u8)v && *p != (u8)v * 2) {
        *p = v * 4;
    }
    p = func_801090E0_etch_n_catch(x + 1, y + 1);
    if (*p != (u8)v && *p != (u8)v * 2) {
        *p = v * 4;
    }
    p = func_801090E0_etch_n_catch(x + 1, y - 1);
    if (*p != (u8)v && *p != (u8)v * 2) {
        *p = v * 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010914C_etch_n_catch);
#endif

/* Removes trail node `node` (drawn with value v) from the grid: unlinks it from its trail, then re-derives the
   marks of its 8 neighbours (v * 2 next to a v cell, v * 4 diagonal to one, else 0). */
#ifdef NON_MATCHING
void func_80109370_etch_n_catch(EtNode* node, u8 v) {
    u8* cell;
    u8* p;
    u8* a;
    u8* b;
    u8* c;
    u8* d;
    u8* e;
    u8* f;
    u8* g;
    u8* h;
    s32 i;
    s16 nx;
    s16 ny;

    cell = func_801090E0_etch_n_catch(node->unk18, node->unk1A);
    if (node->unk0C == NULL && node->unk10 == NULL) {
        *cell = 0;
    }
    if (node->unk10 != NULL && node->unk0C != NULL) {
        node->unk10->unk0C = node->unk0C;
        node->unk0C->unk10 = node->unk10;
    } else if (node->unk10 != NULL && node->unk0C == NULL) {
        node->unk10->unk0C = NULL;
    } else if (node->unk0C != NULL && node->unk10 == NULL) {
        node->unk0C->unk10 = NULL;
    }
    for (i = 0; i < 8; i++) {
        switch (i) {
            case 0:
                nx = node->unk18;
                ny = node->unk1A - 1;
                break;
            case 1:
                nx = node->unk18;
                ny = node->unk1A + 1;
                break;
            case 2:
                ny = node->unk1A;
                nx = node->unk18 - 1;
                break;
            case 3:
                ny = node->unk1A;
                nx = node->unk18 + 1;
                break;
            case 4:
                nx = node->unk18 - 1;
                ny = node->unk1A - 1;
                break;
            case 5:
                nx = node->unk18 + 1;
                ny = node->unk1A + 1;
                break;
            case 6:
                nx = node->unk18 - 1;
                ny = node->unk1A + 1;
                break;
            default:
                nx = node->unk18 + 1;
                ny = node->unk1A - 1;
                break;
        }
        p = func_801090E0_etch_n_catch(nx, ny);
        if (node->unk10 != NULL || node->unk0C != NULL) {
            switch (i) {
                case 0:
                case 1:
                case 2:
                case 3:
                    if (*p != v) {
                        *p = v * 2;
                    }
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    if (*p != v && *p != v * 2) {
                        *p = v * 4;
                    }
                    break;
            }
        }
        a = func_801090E0_etch_n_catch(nx, ny + 1);
        b = func_801090E0_etch_n_catch(nx, ny - 1);
        c = func_801090E0_etch_n_catch(nx - 1, ny);
        d = func_801090E0_etch_n_catch(nx + 1, ny);
        e = func_801090E0_etch_n_catch(nx - 1, ny - 1);
        f = func_801090E0_etch_n_catch(nx + 1, ny + 1);
        g = func_801090E0_etch_n_catch(nx - 1, ny + 1);
        h = func_801090E0_etch_n_catch(nx + 1, ny - 1);
        if (*a != v && *b != v && *c != v && *d != v && *e != v && *f != v && *g != v && *h != v) {
            *p = 0;
        } else if (*a == v || *b == v || *c == v || *d == v) {
            if (*p != v) {
                *p = v * 2;
            }
        } else if (*e == v || *f == v || *g == v || *h == v) {
            if (*p != v && *p != v * 2) {
                *p = v * 4;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109370_etch_n_catch);
#endif


/* A trail node's puff: takes one of the player's three puff models (every 9th node), then grows, rises and fades. */
void func_801097B4_etch_n_catch(EtNode* node) {
    if (node->unk2C == 0) {
        if (D_8010C6F4_etch_n_catch[node->unk1C] == 0) {
            if (D_8010C6E8_etch_n_catch[node->unk1C][0] == 0) {
                node->unk1E = D_80111390_etch_n_catch[node->unk1C][0];
                node->unk34 = 0;
                D_8010C6E8_etch_n_catch[node->unk1C][0] = 1;
            } else if (D_8010C6E8_etch_n_catch[node->unk1C][1] == 0) {
                node->unk1E = D_80111390_etch_n_catch[node->unk1C][1];
                node->unk34 = 1;
                D_8010C6E8_etch_n_catch[node->unk1C][1] = 1;
            } else if (D_8010C6E8_etch_n_catch[node->unk1C][2] == 0) {
                node->unk1E = D_80111390_etch_n_catch[node->unk1C][2];
                node->unk34 = 2;
                D_8010C6E8_etch_n_catch[node->unk1C][2] = 1;
            } else {
                goto none;
            }
        } else {
        none:
            node->unk1E = -1;
            node->unk34 = 0xFF;
        }
        D_8010C6F4_etch_n_catch[node->unk1C]++;
        if (D_8010C6F4_etch_n_catch[node->unk1C] >= 9) {
            D_8010C6F4_etch_n_catch[node->unk1C] = 0;
        }
    }
    if (node->unk1E != -1) {
        node->unk2C++;
        node->unk30 += 0.05f;
        if (node->unk30 > 1.5f) {
            node->unk30 = 1.5f;
        }
        Hu3DModelScaleSet(node->unk1E, node->unk30, node->unk30, node->unk30);
        Hu3DModelPosSet(node->unk1E, node->unk20.x, node->unk20.y, node->unk20.z);
        node->unk20.y += 5.0f;
        if (node->unk2C >= 15) {
            func_8001C258_main(node->unk1E, 4, 4);
            D_8010C6E8_etch_n_catch[node->unk1C][node->unk34] = 0;
            return;
        }
        func_8001F9E4_main(node->unk1E, ~(node->unk2C * 16));
        func_8001C258_main(node->unk1E, 4, 0);
    }
}

/* A catcher object (two): its model, the five spark models of its catch burst and its pointer sprite. */
void func_80109A54_etch_n_catch(omObjData* obj) {
    s32 dir = 0xA0000;
    EtCatcher* cw;
    s32 i;

    if (D_8010C6A0_etch_n_catch == 0) {
        D_8010C83C_etch_n_catch = obj->model[0] = func_8000B108_main(0xA0000, 0x8BD);
    } else {
        obj->model[0] = Hu3DModelLink(D_8010C83C_etch_n_catch);
    }
    func_8001C258_main(obj->model[0], 4, 0);
    obj->data = HuMemAllocTag(sizeof(EtCatcher), 0x7918);
    memset(obj->data, 0, sizeof(EtCatcher));
    cw = obj->data;
    cw->mg.unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 0x7918);
    cw->mg.unk5A = obj->model[0];
    cw->mg.unk5B = 0;
    cw->unk160 = D_8010C6A0_etch_n_catch % 2;
    cw->unk168 = 0.0f;
    func_8000B460_main(obj, 2, dir | 8);
    func_8000B460_main(obj, 3, dir);
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
    switch (cw->unk160) {
        case 0:
            obj->trans.x = D_8010C6B0_etch_n_catch[0].x;
            break;
        case 1:
            obj->trans.x = -D_8010C6B0_etch_n_catch[0].x;
            break;
    }
    obj->trans.y = D_8010C6B0_etch_n_catch[0].y;
    obj->trans.z = D_8010C6B0_etch_n_catch[0].z;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->work[0] = 10;
    obj->work[1] = 0;
    cw->unk15C = 0;
    cw->unk164 = 0.5f;
    cw->unk170 = cw->unk174 = 0.0f;
    cw->unk161 = 0;
    if (D_8010C6A0_etch_n_catch == 0) {
        D_8010C83E_etch_n_catch = obj->model[6] = func_8000B108_main(9, 0x8BD);
    } else {
        obj->model[6] = Hu3DModelLink(D_8010C83E_etch_n_catch);
    }
    Hu3DModelPosSet(obj->model[6], obj->trans.x, 0.0f, obj->trans.z);
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            obj->model[1] = func_8000B108_main(0x330006, 0x8AD);
        } else {
            obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        }
        func_8001C814_main(obj->model[i + 1], 2, 2);
        func_8001FA68_main(obj->model[i + 1]);
        cw->unk1B4 = 0.0f;
        cw->unk178[i].y = 1.0f;
    }
    cw->unk178[0].x = 0.8660254f;
    cw->unk178[0].z = -0.5f;
    cw->unk178[1].x = 0.8660254f;
    cw->unk178[1].z = 0.5f;
    cw->unk178[2].x = 0.0f;
    cw->unk178[2].z = 1.0f;
    cw->unk178[3].x = -0.8660254f;
    cw->unk178[3].z = 0.5f;
    cw->unk178[4].x = -0.8660254f;
    cw->unk178[4].z = -0.5f;
    D_801113E8_etch_n_catch[cw->unk160] = InitEspriteSlot(func_8000B838_main(0x330005), 0, 1);
    func_8000BC48_main(D_801113E8_etch_n_catch[cw->unk160], 0x5000);
    func_8000BBD4_main(D_801113E8_etch_n_catch[cw->unk160], 0, 0);
    func_8000BE5C_main(D_801113E8_etch_n_catch[cw->unk160], 0.5f, 0.5f);
    func_8000BBFC_main(D_801113E8_etch_n_catch[cw->unk160], 0xCC);
    func_8000BB94_main(D_801113E8_etch_n_catch[cw->unk160]);
    obj->func = func_80109EB8_etch_n_catch;
    D_8010C6A0_etch_n_catch++;
}

/* A catcher. work[0]: 0 start at its cage; 1 swing its pointer; 2 pulse; 3 pick a heading that stays in its
   team's area and turn to it; 4 walk; 5 jump up (first time: sound and jump motion; on landing again: score a
   point for the team and burst); 6 burst; 8 lift the cage; 9 rise; 10 done. */
#ifdef NON_MATCHING
void func_80109EB8_etch_n_catch(omObjData* obj) {
    Vec2f scr;
    Vec pos;
    f32 headings[8] = { 1.0f, 46.0f, 91.0f, 136.0f, 181.0f, 226.0f, 271.0f, 316.0f };
    EtCatcher* cw = obj->data;
    s32 i;
    f32 x;
    f32 z;

    pos.x = obj->trans.x;
    pos.y = 0.0f;
    pos.z = obj->trans.z;
    func_80012B14_main(0, &pos, &scr);
    D_8010C850_etch_n_catch[cw->unk160][0] = scr.x / 2.0f;
    D_8010C850_etch_n_catch[cw->unk160][1] = scr.y / 2.0f;
    switch (obj->work[0]) {
        case 0:
            obj->trans.x = D_8010C860_etch_n_catch[cw->unk160]->trans.x;
            obj->trans.y = 0.0f;
            obj->trans.z = D_8010C860_etch_n_catch[cw->unk160]->trans.z;
            pos.x = obj->trans.x;
            pos.y = 0.0f;
            pos.z = obj->trans.z;
            func_80012B14_main(0, &pos, &scr);
            func_8000BBD4_main(D_801113E8_etch_n_catch[cw->unk160], scr.x, scr.y);
            cw->unk164 = 0.5f;
            func_8000BE5C_main(D_801113E8_etch_n_catch[cw->unk160], cw->unk164, cw->unk164);
            cw->unk170 = cw->unk174 = 0.0f;
            func_8000BF00_main(D_801113E8_etch_n_catch[cw->unk160], 0.0f);
            func_8000BB54_main(D_801113E8_etch_n_catch[cw->unk160]);
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[6], 4, 4);
            for (i = 0; i < 5; i++) {
                func_8001C258_main(obj->model[i + 1], 4, 4);
            }
            cw->unk15C = 0;
            obj->work[0] = 1;
            break;
        case 5:
            cw->unk168 += 2.0f;
            obj->trans.y += cw->unk168 + 5.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, 0.0f, obj->trans.z);
            Hu3DModelPosSet(obj->model[6], obj->trans.x, 0.0f, obj->trans.z);
            if (D_8010C6F8_etch_n_catch[cw->unk160] == 0) {
                if (cw->unk160 == 0) {
                    func_8004AE00_main(HuAudFXPlay(0x37D), 0x20);
                } else {
                    func_8004AE00_main(HuAudFXPlay(0x37E), 0x5F);
                }
                cw->unk164 = 1.0f;
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
                func_8001C6A8_main(obj->model[0], 0.0f);
                cw->unk15C = 0;
                cw->unk1B4 = 0.0f;
                D_8010C6F8_etch_n_catch[cw->unk160] = 1;
            } else {
                func_8000BB94_main(D_801113E8_etch_n_catch[cw->unk160]);
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[6], 4, 0);
                for (i = 0; i < 5; i++) {
                    func_8001C6A8_main(obj->model[i + 1], 0.0f);
                }
                func_8010AB7C_etch_n_catch(obj);
                if (cw->unk160 == 0) {
                    D_8010C6AC_etch_n_catch++;
                } else {
                    D_8010C6AD_etch_n_catch++;
                }
                D_8010C6F8_etch_n_catch[cw->unk160] = 0;
                cw->unk15C = 0;
                obj->work[0] = 6;
            }
            break;
        case 6:
            if (cw->unk15C < 10) {
                func_8010AB7C_etch_n_catch(obj);
            } else {
                for (i = 0; i < 5; i++) {
                    func_8001C258_main(obj->model[i + 1], 4, 4);
                }
            }
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 / 2.0f - 2.0f <= cw->unk15C) {
                func_8001C814_main(obj->model[0], 2, 1);
                obj->work[0] = 8;
                cw->unk15C = 0;
            } else {
                cw->unk168 += 2.0f;
                obj->trans.y += cw->unk168 + 5.0f;
                cw->unk15C++;
            }
            break;
        case 8:
            cw->unk168 += 2.0f;
            obj->trans.y += cw->unk168 + 5.0f;
            for (i = 0; i < 5; i++) {
                func_8001C258_main(obj->model[i + 1], 4, 4);
            }
            obj->work[0] = 9;
            D_8010C860_etch_n_catch[cw->unk160]->work[0] = 0;
            break;
        case 9:
            for (i = 0; i < 5; i++) {
                func_8001C258_main(obj->model[i + 1], 4, 4);
            }
            cw->unk15C++;
            obj->trans.y += cw->unk168 + 5.0f;
            if (obj->trans.y > 800.0f && cw->unk164 == 0.0f) {
                cw->unk168 = 0.0f;
                cw->unk15C = 0;
                obj->work[0] = 10;
            } else {
                cw->unk168 += 2.0f;
                cw->unk164 -= 0.05f;
                if (cw->unk164 < 0.0f) {
                    cw->unk164 = 0.0f;
                }
            }
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelScaleSet(obj->model[6], cw->unk164, cw->unk164, cw->unk164);
            break;
        case 10:
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[6], 4, 4);
            cw->unk164 = 1.0f;
            Hu3DModelScaleSet(obj->model[6], cw->unk164, cw->unk164, cw->unk164);
            break;
        default:
            if (func_800E6E8C_minigame()) {
                switch (obj->work[0]) {
                    case 1:
                        if (cw->unk15C > 120) {
                            cw->unk15C = 0;
                            obj->work[0] = 2;
                            break;
                        }
                        goto swing;
                    case 2:
                        if (cw->unk15C > 16) {
                            cw->unk15C = 0;
                            cw->unk164 = 0.5f;
                            func_8000BE5C_main(D_801113E8_etch_n_catch[cw->unk160], cw->unk164, cw->unk164);
                            obj->work[0] = 3;
                            break;
                        }
                        cw->unk15C++;
                        func_8010AEE4_etch_n_catch(cw);
                        break;
                    case 3:
                        if (cw->unk15C == 0) {
                            do {
                                cw->unk16C = headings[rand8() >> 5];
                                x = obj->trans.x - sindf(cw->unk16C) * 100.0f;
                                z = obj->trans.z - cosdf(cw->unk16C) * 100.0f;
                                if (!((z > -300.0f) & (z < 200.0f))) {
                                    continue;
                                }
                                if (cw->unk160 == 0) {
                                    if ((x < -180.0f) & (x > -350.0f)) {
                                        break;
                                    }
                                } else if ((x > 180.0f) & (x < 350.0f)) {
                                    break;
                                }
                            } while (TRUE);
                        }
                        cw->unk15C++;
                        if (cw->unk16C == cw->unk170) {
                            cw->unk15C = 0;
                            obj->work[0] = 4;
                            break;
                        }
                        func_8010AFB8_etch_n_catch(cw);
                        break;
                    case 4:
                        obj->trans.x -= sindf(cw->unk170) * 3.0f;
                        obj->trans.z -= cosdf(cw->unk170) * 3.0f;
                        pos.x = obj->trans.x;
                        pos.y = 0.0f;
                        pos.z = obj->trans.z;
                        func_80012B14_main(0, &pos, &scr);
                        func_8000BBD4_main(D_801113E8_etch_n_catch[cw->unk160], scr.x, scr.y);
                        D_8010C850_etch_n_catch[cw->unk160][0] = scr.x / 2.0f;
                        D_8010C850_etch_n_catch[cw->unk160][1] = scr.y / 2.0f;
                        if (cw->unk15C == cw->unk15C / 10 * 10) {
                            /* retail: results unused */
                            sindf(cw->unk170);
                            cosdf(cw->unk170);
                        }
                        if (obj->trans.z < -300.0f || obj->trans.z > 200.0f) {
                            cw->unk15C = 0;
                            obj->work[0] = 1;
                        } else if (cw->unk160 == 0) {
                            if (obj->trans.x > -180.0f || obj->trans.x < -350.0f) {
                                cw->unk15C = 0;
                                obj->work[0] = 1;
                            }
                        } else if (obj->trans.x < 180.0f || obj->trans.x > 350.0f) {
                            cw->unk15C = 0;
                            obj->work[0] = 1;
                        }
                        if (cw->unk15C > 60) {
                            cw->unk15C = 0;
                            obj->work[0] = 1;
                            break;
                        }
                    swing:
                        if (cw->unk15C == 0) {
                            cw->unk174 = cw->unk170;
                        }
                        func_8010AD6C_etch_n_catch(cw);
                        cw->unk15C++;
                        break;
                }
            }
            break;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7BC_etch_n_catch);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109EB8_etch_n_catch);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7F0_etch_n_catch);
#endif

/* The burst of a catch: five sparks fly out along unk178[] and fade. */
void func_8010AB7C_etch_n_catch(omObjData* obj) {
    EtCatcher* cw = obj->data;
    s32 i;

    cw->unk1B4 += 7.0f;
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(obj->model[i + 1], cw->unk178[i].x * cw->unk1B4 * 1.5f + obj->trans.x,
                        cw->unk178[i].y * cw->unk1B4 + obj->trans.y,
                        cw->unk178[i].z * cw->unk1B4 * 1.5f + obj->trans.z);
        func_8001F9E4_main(obj->model[i + 1], 255.0f - cw->unk1B4 * 8.0f);
        Hu3DModelScaleSet(obj->model[i + 1], 3.0f, 3.0f, 3.0f);
        Hu3DModelRotSet(obj->model[i + 1], 0.0f, 90.0f, 0.0f);
        func_8001C258_main(obj->model[i + 1], 4, 0);
    }
}

/* Swings the catcher's sprite angle back and forth by 30 degrees around unk174. */
void func_8010AD6C_etch_n_catch(EtCatcher* cw) {
    if (cw->unk161 == 0) {
        cw->unk170 += 2.0f;
        if (ET_ABS(cw->unk170 - cw->unk174) >= 30.0f) {
            cw->unk161 = 1;
        }
    } else {
        cw->unk170 -= 2.0f;
        if (ET_ABS(cw->unk170 - cw->unk174) >= 30.0f) {
            cw->unk161 = 0;
        }
    }
    func_8000BF00_main(D_801113E8_etch_n_catch[cw->unk160], cw->unk170);
}


/* Pulses the catcher's sprite scale. Retail: the second and later tests are unreachable or never true
   as written (unk15C < 16 is checked first). */
void func_8010AEE4_etch_n_catch(EtCatcher* cw) {
    if (cw->unk15C < 16) {
        cw->unk164 -= 0.01f;
    } else if (cw->unk15C < 8) {
        cw->unk164 += 0.01f;
    } else if (cw->unk15C < 10) {
        cw->unk164 -= 0.01;
    } else {
        cw->unk164 += 0.01;
    }
    func_8000BE5C_main(D_801113E8_etch_n_catch[cw->unk160], cw->unk164, cw->unk164);
}

/* Turns the catcher's sprite angle toward unk16C by at most 5 degrees. */
void func_8010AFB8_etch_n_catch(EtCatcher* cw) {
    f32 d;

    cw->unk170 = func_8010C4F8_etch_n_catch(cw->unk170);
    d = cw->unk16C - cw->unk170;
    if (ET_ABS(d) > 5.0f) {
        if (((d > 0.0f) & (d < 180.0f)) || ((d < -180.0f) & (d > -360.0f))) {
            cw->unk170 = cw->unk170 + 5.0f;
        } else {
            cw->unk170 = cw->unk170 - 5.0f;
        }
    } else {
        cw->unk170 = d + cw->unk170;
    }
    cw->unk170 = func_8010C4F8_etch_n_catch(cw->unk170);
    func_8000BF00_main(D_801113E8_etch_n_catch[cw->unk160], cw->unk170);
}

/* Whether cell (x, y) is set or at least three of its 4 neighbours are. */
s32 func_8010B154_etch_n_catch(s16 x, s16 y) {
    s32 n = 0;

    if (func_80109114_etch_n_catch(x, y) == 0) {
        n += func_80109114_etch_n_catch(x - 1, y) != 0;
        n += func_80109114_etch_n_catch(x + 1, y) != 0;
        n += func_80109114_etch_n_catch(x, y - 1) != 0;
        n += func_80109114_etch_n_catch(x, y + 1) != 0;
        return n >= 3;
    }
    return 1;
}

/* A cage object (one per catcher): its model drops from above onto the catcher's start. */
void func_8010B24C_etch_n_catch(omObjData* obj) {
    EtCage* cg;

    obj->data = HuMemAllocTag(sizeof(EtCage), 0x7918);
    memset(obj->data, 0, sizeof(EtCage));
    cg = obj->data;
    cg->unk01 = 0;
    cg->unk00 = D_8010C840_etch_n_catch;
    cg->unk04 = 0;
    cg->unk08 = 0;
    cg->unk02 = 0;
    obj->work[0] = 0;
    switch (cg->unk00) {
        case 0:
            obj->trans.x = D_8010C6B0_etch_n_catch[0].x;
            break;
        case 1:
            obj->trans.x = -D_8010C6B0_etch_n_catch[0].x;
            break;
    }
    obj->trans.y = 800.0f;
    obj->trans.z = D_8010C6B0_etch_n_catch[0].z;
    obj->model[0] = func_8000B108_main(0x330002, 0x8B9);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[1] = func_8000B108_main(0x330008, 0x89D);
    obj->model[2] = func_8000B108_main(9, 0x8B9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->func = func_8010B3B4_etch_n_catch;
    D_8010C840_etch_n_catch++;
}

/* A cage: state 0 picks a spot away from the team's players and drops onto it (landing burst at frame 45, sound at
   50); 1 waits for its catcher (work[0] == 10) and rumbles the team; 2 rises again; 3 idle. */
#ifdef NON_MATCHING
void func_8010B3B4_etch_n_catch(omObjData* obj) {
    omObjData* p0 = NULL;
    EtCage* cg = obj->data;
    omObjData* p1 = NULL;
    s32 i;
    u8 r;
    s16 se;

    switch (obj->work[0]) {
        case 0:
            if (cg->unk01 == 0) {
                cg->unk01 = 1;
            } else if (cg->unk08 == 0.0f) {
                for (i = 0; i < 4; i++) {
                    if ((cg->unk00 == 0 && D_8010C868_etch_n_catch[i]->unk01 == 3)
                        || (cg->unk00 == 1 && D_8010C868_etch_n_catch[i]->unk01 == 12)) {
                        if (p0 == NULL) {
                            p0 = D_800EC598_minigame[i];
                        } else {
                            p1 = D_800EC598_minigame[i];
                        }
                    }
                }
                r = (rand8() * 3) >> 8;
                switch (cg->unk00) {
                    case 0:
                        obj->trans.x = D_8010C6B0_etch_n_catch[r].x;
                        break;
                    case 1:
                        obj->trans.x = -D_8010C6B0_etch_n_catch[r].x;
                        break;
                }
                obj->trans.z = D_8010C6B0_etch_n_catch[r].z;
                if (ET_ABS(p0->trans.x - obj->trans.x) < 75.0f && ET_ABS(p0->trans.z - obj->trans.z) < 75.0f) {
                    return;
                }
                if (ET_ABS(p1->trans.x - obj->trans.x) < 75.0f && ET_ABS(p1->trans.z - obj->trans.z) < 75.0f) {
                    return;
                }
            }
            obj->trans.y -= cg->unk08 + 5.0f;
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
                cg->unk08 = 0.0f;
                obj->work[0] = 1;
            } else {
                cg->unk08 += 5.0f;
                cg->unk04 += 0.1f;
                if (cg->unk04 > 1.5f) {
                    cg->unk04 = 1.5f;
                }
                if (cg->unk08 == 45.0f) {
                    Hu3DModelScaleSet(obj->model[1], 3.6f, 3.6f, 3.6f);
                    func_800E4C88_minigame(obj, 1, obj->trans.x, 0.0f, obj->trans.z, 0.0f, 0.0f);
                } else if (cg->unk08 == 50.0f) {
                    if (cg->unk00 == 0) {
                        se = HuAudFXPlay(0x37B);
                        func_8004AE00_main(se, 0x20);
                        if (D_8010C6AC_etch_n_catch == 0) {
                            func_8004AAD0_main(se, 0x66);
                        } else {
                            func_8004AAD0_main(se, 0x7F);
                        }
                    } else {
                        func_8004AE00_main(HuAudFXPlay(0x37C), 0x5F);
                    }
                }
            }
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
            Hu3DModelScaleSet(obj->model[2], cg->unk04, cg->unk04, cg->unk04);
            func_8001C258_main(obj->model[2], 4, 0);
            break;
        case 1:
            if (D_8010C858_etch_n_catch[cg->unk00]->work[0] == 10) {
                if (cg->unk02 >= 5) {
                    cg->unk02 = 0;
                    D_8010C858_etch_n_catch[cg->unk00]->work[0] = 0;
                    obj->work[0] = 2;
                    return;
                }
                if (cg->unk02 == 0) {
                    if (cg->unk00 == 0) {
                        for (i = 0; i < 4; i++) {
                            if (D_8010C868_etch_n_catch[i]->unk01 == 3) {
                                omVibrate(((MgWork*)D_800EC598_minigame[i]->data)->unk59, 10, 0, 10);
                            }
                        }
                    } else {
                        for (i = 0; i < 4; i++) {
                            if (D_8010C868_etch_n_catch[i]->unk01 == 12) {
                                omVibrate(((MgWork*)D_800EC598_minigame[i]->data)->unk59, 10, 0, 10);
                            }
                        }
                    }
                }
                cg->unk02++;
            }
            break;
        case 2:
            obj->trans.y += cg->unk08 + 5.0f;
            if (obj->trans.y > 800.0f && cg->unk04 == 0.0f) {
                obj->trans.y = 800.0f;
                cg->unk08 = 0.0f;
                obj->work[0] = 3;
            } else {
                cg->unk08 += 5.0f;
                cg->unk04 -= 0.1f;
                if (cg->unk04 < 0.0f) {
                    cg->unk04 = 0.0f;
                }
            }
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelScaleSet(obj->model[2], cg->unk04, cg->unk04, cg->unk04);
            break;
        case 3:
            cg->unk04 = 1.0f;
            func_8001C258_main(obj->model[2], 4, 4);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B3B4_etch_n_catch);
#endif

/* The score display: two frames, two labels and a digit per team. */
void func_8010BBE4_etch_n_catch(omObjData* obj) {
    s16 pos[2][2] = { { 0x23, 0x26 }, { 0xFC, 0x26 } };
    s16 i;
    s16 id;

    id = func_8000B838_main(0x21002A);
    for (i = 0; i < 2; i++) {
        func_8000BBD4_main(InitEspriteSlot(id, 0, 1), pos[i][0], pos[i][1]);
    }
    id = func_8000B838_main(0x21001B);
    for (i = 0; i < 2; i++) {
        func_8000BBD4_main(InitEspriteSlot(id, 0, 1), pos[i][0] + 16, pos[i][1]);
    }
    id = func_8000B838_main(0x31);
    for (i = 0; i < 2; i++) {
        D_801113A8_etch_n_catch[i] = InitEspriteSlot(id, 0, 1);
        func_8000BBD4_main(D_801113A8_etch_n_catch[i], D_8010C6A4_etch_n_catch[i][0], D_8010C6A4_etch_n_catch[i][1]);
    }
    obj->func = func_8010BD98_etch_n_catch;
}

/* Shows the two team scores. */
void func_8010BD98_etch_n_catch(omObjData* obj) {
    func_8000BD50_main(D_801113A8_etch_n_catch[0], D_8010C6AC_etch_n_catch % 10);
    func_8000BBD4_main(D_801113A8_etch_n_catch[0], D_8010C6A4_etch_n_catch[0][0], D_8010C6A4_etch_n_catch[0][1]);
    func_8000BD50_main(D_801113A8_etch_n_catch[1], D_8010C6AD_etch_n_catch % 10);
    func_8000BBD4_main(D_801113A8_etch_n_catch[1], D_8010C6A4_etch_n_catch[1][0], D_8010C6A4_etch_n_catch[1][1]);
}

/* The drawing board: two sprite layers, the 8-bit grid (the second layer's texels) and its palette, the walls,
   the flood-fill lists, and the framework ground block. */
// masked 15 (H1, was 37): the first wall-band test of the clear loop: retail branches over a `j` (beqz; nop; j with the
// store in the slot) where every spelling tried here (else-if, ||, continue) gives bnezl; 3 instructions short
#ifdef NON_MATCHING
void func_8010BE84_etch_n_catch(omObjData* obj) {
    u16 id;
    HuSprite* spr;
    u16* pal;
    u8* p;
    s32 i;
    EtGround* gw;

    id = func_8000B838_main(0x330003);
    D_8010C842_etch_n_catch = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010C842_etch_n_catch, 0, id, 0);
    HuSprAttrReset(D_8010C842_etch_n_catch, 0, 0xFFFF);
    HuSprAttrSet(D_8010C842_etch_n_catch, 0, 0x5000);
    func_80054904_main(D_8010C842_etch_n_catch, 0, 160, 120);
    id = func_8000B838_main(0x330004);
    D_8010C844_etch_n_catch = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010C844_etch_n_catch, 0, id, 0);
    HuSprAttrReset(D_8010C844_etch_n_catch, 0, 0xFFFF);
    HuSprAttrSet(D_8010C844_etch_n_catch, 0, 0x5000);
    func_80054904_main(D_8010C844_etch_n_catch, 0, 160, 120);
    D_8010C878_etch_n_catch = HuMemAlloc(14400 * sizeof(u8*));
    D_8010C87C_etch_n_catch[0] = HuMemAlloc(1000 * sizeof(u8*));
    D_8010C87C_etch_n_catch[1] = HuMemAlloc(1000 * sizeof(u8*));
    spr = HuSprGet(D_8010C844_etch_n_catch, 0);
    D_8010C84C_etch_n_catch = p = spr->unk_84->unk00->unk00;
    pal = spr->unk_84->unk0C;
    D_8010C846_etch_n_catch = spr->unk_84->unk14;
    D_8010C848_etch_n_catch = spr->unk_84->unk16;
    pal[0] = 0;
    pal[1] = 0xF801;
    pal[2] = 0xFC21;
    pal[4] = 0xFE31;
    pal[8] = 0x3F;
    pal[16] = 0x843F;
    pal[32] = 0xC63F;
    pal[33] = 0x400;
    pal[34] = 0xFFFE;
    for (i = 0; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i++, p++) {
        if (D_8010C846_etch_n_catch * 50 < i && i < D_8010C846_etch_n_catch * 51) {
            *p = 0x22;
        } else if (D_8010C846_etch_n_catch * 200 < i && i < D_8010C846_etch_n_catch * 201) {
            *p = 0x22;
        } else {
            *p = 0;
        }
    }
    p = D_8010C84C_etch_n_catch;
    for (i = 30; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        p[i] = 0x22;
    }
    for (i = 160; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        p[i] = 0x22;
    }
    for (i = 290; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        p[i] = 0x22;
    }
    obj->func = NULL;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->data = gw = HuMemAllocTag(sizeof(EtGround), 0x7918);
    memset(gw, 0, sizeof(EtGround));
    gw->unk03 = 1;
    gw->unk08 = 0.5f;
    func_800E1370_minigame(obj, 2, 0.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BE84_etch_n_catch);
#endif

/* Frees the fill lists, the trail pools and the player work blocks. */
void func_8010C2F4_etch_n_catch(void) {
    s32 i;
    EtchNCatchWork* w;

    HuMemFree(D_8010C878_etch_n_catch);
    HuMemFree(D_8010C87C_etch_n_catch[0]);
    HuMemFree(D_8010C87C_etch_n_catch[1]);
    for (i = 0; i < 4; i++) {
        w = D_8010C868_etch_n_catch[i];
        HuMemFree(D_801113D8_etch_n_catch[i]);
        HuMemFree(w);
    }
}

/* The ground object of team 0 (the left half of the floor). */
void func_8010C390_etch_n_catch(omObjData* obj) {
    EtGround* gw;

    obj->model[0] = -1;
    obj->func = NULL;
    obj->data = gw = HuMemAllocTag(sizeof(EtGround), 0x7918);
    memset(gw, 0, sizeof(EtGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    gw->unk08 = 0.5f;
    func_800E139C_minigame(obj, 0.0f, -450.0f, -400.0f, -80.0f, 300.0f);
    func_800E1468_minigame(obj);
}

/* The ground object of team 1 (the right half of the floor). */
void func_8010C444_etch_n_catch(omObjData* obj) {
    EtGround* gw;

    obj->model[0] = -1;
    obj->func = NULL;
    obj->data = gw = HuMemAllocTag(sizeof(EtGround), 0x7918);
    memset(gw, 0, sizeof(EtGround));
    gw->unk03 = 1;
    gw->unk04 = 1;
    gw->unk08 = 0.5f;
    func_800E139C_minigame(obj, 0.0f, 80.0f, -400.0f, 450.0f, 300.0f);
    func_800E1468_minigame(obj);
}

/* `angle` wrapped into [0, 360). */
f32 func_8010C4F8_etch_n_catch(f32 angle) {
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

/* The unit vector from (x0, y0) to (x1, y1); zero when the points coincide. */
EtVec2 func_8010C574_etch_n_catch(s32 x0, s32 y0, s32 x1, s32 y1) {
    EtVec2 v;
    f32 len;

    v.x = x1 - x0;
    v.y = y1 - y0;
    len = HuSqrtf(v.x * v.x + v.y * v.y);
    if (len == 0.0f) {
        v.x = v.y = 0.0f;
    } else {
        v.x /= len;
        v.y /= len;
    }
    return v;
}

/* Sets the scale of the player and its two pen models. */
void func_8010C628_etch_n_catch(omObjData* obj, f32 scale) {
    obj->scale.x = obj->scale.y = obj->scale.z = scale;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[2], obj->scale.x, obj->scale.y, obj->scale.z);
}

