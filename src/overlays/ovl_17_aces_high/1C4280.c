#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/hmflight.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// ah A: Aces High

/* omObjData::data of a player's plane (func_801062DC_aces_high, 0xC0) */
typedef struct AhPlayer {
    /* 0x00 */ u16 unk00; /* state */
    /* 0x02 */ u16 unk02; /* player */
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ f32 unk08; /* speed */
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10; /* heading x */
    /* 0x14 */ f32 unk14; /* heading y */
    /* 0x18 */ f32 unk18; /* heading z */
    /* 0x1C */ s16 unk1C; /* esprite */
    /* 0x1E */ s16 unk1E; /* esprite */
    /* 0x20 */ u16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ u16 unk24;
    /* 0x26 */ s16 unk26; /* lives */
    /* 0x28 */ s16 unk28[2]; /* esprites */
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E; /* esprite */
    /* 0x30 */ s16 unk30; /* esprite */
    /* 0x32 */ s16 unk32; /* turning: 0 no, 1 left, 2 right */
    /* 0x34 */ s16 unk34; /* CPU: mirror the chase turn */
    /* 0x36 */ s16 unk36; /* fell below the floor */
    /* 0x38 */ f32 unk38; /* pitch */
    /* 0x3C */ f32 unk3C; /* roll */
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48; /* climb back step */
    /* 0x4C */ u16 unk4C; /* engine model: 0 slow, 1 cruise, 2 fast, 3 none */
    /* 0x4E */ u16 unk4E; /* timer */
    /* 0x50 */ u16 unk50; /* hit flash timer */
    /* 0x52 */ u16 unk52;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ char unk5A[2];
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s16 unk70;
    /* 0x72 */ char unk72[2];
    /* 0x74 */ omObjData *unk74;
    /* 0x78 */ omObjData *unk78;
    /* 0x7C */ f32 unk7C; /* pitch step */
    /* 0x80 */ f32 unk80; /* roll step */
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u16 unk88;
    /* 0x8A */ char unk8A[2];
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u16 unk90;
    /* 0x92 */ u16 unk92; /* CPU state */
    /* 0x94 */ u16 unk94; /* CPU: state to resume */
    /* 0x96 */ char unk96[2];
    /* 0x98 */ omObjData *unk98; /* CPU: chased plane */
    /* 0x9C */ Vec unk9C; /* CPU: goal point */
    /* 0xA8 */ f32 unkA8; /* CPU: heading back into the arena */
    /* 0xAC */ u16 unkAC;
    /* 0xAE */ u16 unkAE;
    /* 0xB0 */ u16 unkB0; /* CPU: state timer */
    /* 0xB2 */ char unkB2[0xE];
} AhPlayer; /* size 0xC0 */

/* omObjData::data of a shot */
typedef struct AhShot {
    /* 0x00 */ u16 unk00; /* 1 flying */
} AhShot;

/* the scrolled sky texture's size (func_800335BC_main) */
typedef struct AhTexSize {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
} AhTexSize;

typedef struct AhUV {
    /* 0x00 */ f32 u;
    /* 0x04 */ f32 v;
} AhUV;

double fabs(double); /* the GCC builtin (abs.d) */
float fabsf(float); /* the GCC builtin (abs.s) */
void HmfLightStatSet(s16, u8, u8);
void func_8000B710_main(s32);
void func_80047C0C_main(u16 group, u16 max_objs);
omObjData **func_80047DBC_main(s16 arg0);
void func_800335BC_main(char *name, void *size);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern u8 D_800D6A90_main;
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];

extern D_80111B50_vine_with_me_Struct D_8010DB40_aces_high;
extern u16 D_8010DB68_aces_high[4]; /* camera bit per player */
extern f32 D_8010DB70_aces_high[4][4]; /* scissor per camera */
extern f32 D_8010DBB0_aces_high[4][4]; /* viewport per camera */
extern Vec D_8010DBF0_aces_high; /* background colour */
extern u16 D_8010DC08_aces_high; /* ending */
extern f32 D_8010DC0C_aces_high; /* sky rotation */
extern s32 D_8010DC10_aces_high[8]; /* plane model per character */
extern s32 D_8010DC30_aces_high[8]; /* esprite per character */
extern s16 D_8010DC50_aces_high[4][2][2];
extern s16 D_8010DC70_aces_high[4][2];
extern f32 D_8010DC80_aces_high[4]; /* start angle per player */

extern AhTexSize D_8010DE50_aces_high;
extern AhUV D_8010DE54_aces_high;
extern omObjData *D_8010DE5C_aces_high;
extern omObjData *D_8010DE60_aces_high;
extern omObjData *D_8010DE64_aces_high;
extern omObjData **D_8010DE68_aces_high; /* the players */
extern omObjData **D_8010DE70_aces_high[4]; /* each player's shots */
extern omObjData *D_8010DE84_aces_high;
extern s16 D_8010DE88_aces_high;
extern s16 D_8010DE8A_aces_high;
extern s16 D_8010DE8C_aces_high;
extern s16 D_8010DE8E_aces_high; /* winner */
extern s16 D_8010DE90_aces_high;
extern s16 D_8010DE92_aces_high;
extern s16 D_8010DE94_aces_high;
extern s16 D_8010DE96_aces_high;
extern Vec D_8010DE98_aces_high;
extern Vec D_8010DEA8_aces_high; /* ending camera eye */
extern Vec D_8010DEB4_aces_high; /* ending camera target */
extern Vec D_8010DEC0_aces_high; /* ending camera up */
extern s16 D_8010DEA4_aces_high;
extern s16 D_8010DEA6_aces_high;

void func_801059A0_aces_high(void);
void func_80105E44_aces_high(omObjData *obj);
void func_80105E84_aces_high(omObjData *obj);
void func_80105FC8_aces_high(omObjData *obj);
void func_801061E0_aces_high(omObjData *obj);
void func_801062DC_aces_high(omObjData *obj);
void func_801068F4_aces_high(omObjData *obj);
void func_80106B70_aces_high(omObjData *obj);
void func_80106D2C_aces_high(omObjData *obj);
void func_80106EC0_aces_high(omObjData *obj);
void func_801071D4_aces_high(omObjData *obj);
void func_80107654_aces_high(omObjData *obj);
void func_80107F98_aces_high(omObjData *obj);
void func_801081A8_aces_high(omObjData *obj);
void func_8010843C_aces_high(omObjData *obj);
void func_801085B0_aces_high(void);
void func_8010862C_aces_high(omObjData *obj);
void func_801088A4_aces_high(omObjData *obj, s8 *stickX, s8 *stickY, s16 *btn, u16 *btn2);
u16 func_8010951C_aces_high(omObjData *obj, Vec *target, f32 turn, f32 arg3, s8 *stickX, s8 *stickY);
s16 func_80109EEC_aces_high(omObjData *obj, f32 fov, omObjData **list, omObjData **nearest, f32 *nearDist);
f32 func_8010A0F0_aces_high(omObjData *obj);
void func_80109928_aces_high(omObjData *obj);
void func_8010A214_aces_high(omObjData *obj);
void func_8010A51C_aces_high(omObjData *obj);
void func_8010A884_aces_high(omObjData *obj);
void func_8010A9D4_aces_high(omObjData *obj);
void func_8010AADC_aces_high(omObjData *obj);
void func_8010ACE0_aces_high(omObjData *obj);
void func_8010AD4C_aces_high(omObjData *obj);
void func_8010AE30_aces_high(omObjData *obj);
void func_8010B0E8_aces_high(omObjData *obj);
void func_8010B224_aces_high(omObjData *obj);
void func_8010B26C_aces_high(omObjData *obj);
void func_8010B4BC_aces_high(omObjData *obj);
void func_8010B618_aces_high(void);
void func_8010B760_aces_high(omObjData *obj);
void func_8010B9F4_aces_high(omObjData *obj);
void func_8010BCC4_aces_high(omObjData *obj);
void func_8010BD84_aces_high(omObjData *obj);
void func_8010BF3C_aces_high(omObjData *obj);
void func_8010C288_aces_high(omObjData *obj);
void func_8010C9DC_aces_high(void);
void func_8010CA6C_aces_high(omObjData *obj);
void func_8010CD88_aces_high(omObjData *obj);
void func_8010CE5C_aces_high(omObjData *obj);
void func_8010CFF8_aces_high(omObjData *obj);
void func_8010D1D8_aces_high(omObjData *obj);
void func_8010D6D4_aces_high(omObjData *obj);
void func_8010D994_aces_high(omObjData *obj);
void func_8010DB20_aces_high(void);


void func_801059A0_aces_high(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(0x50, 0);
    i = 0;
    func_8004A208_main();
    func_8000B690_main(4);
    func_8000B710_main(4);
    do {
        CZoomM[i] = 1500.0f;
        CRotM[i].x = -5.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 0.0f;
        CenterM[i].z = 0.0f;
        Hu3DCamSetPerspective(i, 90.0f, 80.0f, 14000.0f);
        ScissorSet(i, D_8010DB70_aces_high[i][0], D_8010DB70_aces_high[i][1], D_8010DB70_aces_high[i][2],
                   D_8010DB70_aces_high[i][3]);
        ViewportSet(i, D_8010DBB0_aces_high[i][0], D_8010DBB0_aces_high[i][1], 511.0f, D_8010DBB0_aces_high[i][2],
                    D_8010DBB0_aces_high[i][3], 511.0f);
        i++;
    } while (i < 4);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    D_8010DE84_aces_high = obj;
    obj->work[0] = 4;
    omSetStatBit(obj, 0xA0);
    D_8010DE98_aces_high.x = D_8010DBF0_aces_high.x;
    D_8010DE98_aces_high.y = D_8010DBF0_aces_high.y;
    D_8010DE98_aces_high.z = D_8010DBF0_aces_high.z;
    func_8001F38C_main((u8)D_8010DE98_aces_high.x, (u8)D_8010DE98_aces_high.y, (u8)D_8010DE98_aces_high.z);
    HmfLightMaxSet(3);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, 3.0f, 89.0f, 80.0f);
    HmfLightStatSet(1, 1, 1);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(3, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105E44_aces_high);
    D_8010DE64_aces_high = omAddObj(0xA, 4, 0, -1, func_80105FC8_aces_high);
    omSetStatBit(D_8010DE64_aces_high, 0xA0);
    omSetStatBit(D_8010DE64_aces_high, 0x100);
    i = 0;
    func_800E5EA0_minigame(&D_8010DB40_aces_high);
    D_800EB930_minigame = 0x32;
    D_800EB932_minigame = 0xA;
    func_80047C0C_main(0, 4);
    D_8010DE68_aces_high = func_80047DBC_main(0);
    do {
        omAddObj(0x14, 7, 0, 0, func_801062DC_aces_high)->work[0] = i;
        i++;
    } while (i < 4);
    func_8010C9DC_aces_high();
    func_8010B618_aces_high();
    D_8010DEA4_aces_high = func_8000B838_main(0x380027);
    D_8010DEA6_aces_high = func_8000B838_main(0x380028);
}

void func_80105E44_aces_high(omObjData *obj) {
    D_8010DE60_aces_high = NULL;
    D_8010DE5C_aces_high = NULL;
    D_8010DE8C_aces_high = 4;
    D_8010DE8E_aces_high = -1;
    D_8010DE90_aces_high = 0;
    obj->func = func_80105E84_aces_high;
}

/* Game flow: start, the race, results, end. */
void func_80105E84_aces_high(omObjData *obj) {
    if (D_8010DC08_aces_high == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010DE5C_aces_high == NULL) {
                    D_8010DE88_aces_high = 0;
                    D_8010DE5C_aces_high = omAddObj(4, 0, 0, -1, func_8010CD88_aces_high);
                }
                break;
            case 2:
                if (D_8010DE8C_aces_high < 2) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 1:
            case 4:
                break;
            case 3:
                if (D_8010DE60_aces_high == NULL) {
                    D_8010DE8A_aces_high = 0;
                    D_8010DE60_aces_high = omAddObj(4, 0, 0, -1, func_8010CE5C_aces_high);
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                HuAudFXStop(D_8010DE96_aces_high);
                HuAudSeqFadeOut(30);
                func_8004AB0C_main(30);
                D_8010DC08_aces_high = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010DB20_aces_high();
    }
}

void func_80105FC8_aces_high(omObjData *obj) {
    s16 spr;

    obj->model[0] = func_8000B108_main(0x38000A, 0x6D9);
    Hu3DModelPosSet(obj->model[0], 0.0f, -1000.0f, 0.0f);
    obj->model[1] = func_8000B108_main(0x380025, 0x699);
    Hu3DModelPosSet(obj->model[1], 0.0f, 900.0f, -8000.0f);
    obj->model[2] = func_8000B108_main(0x380026, 0x699);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 8000.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 180.0f, 0.0f);
    obj->model[3] = func_8000B108_main(0x38000B, 0x6C9);
    Hu3DModelPosSet(obj->model[3], 0.0f, -1000.0f, 0.0f);
    HmfModelData[obj->model[3]].hmf->unk84->unk0[2] = 0;
    func_8001C448_main(obj->model[3]);
    func_8001C514_main(obj->model[3]);
    D_8010DE92_aces_high = spr = InitEspriteSlot(func_8000B838_main(0x38001E), 0, 0);
    func_8000BBD4_main(spr, 0xA0, 0x78);
    func_8000BCC8_main(spr, 0x8096);
    D_8010DE94_aces_high = spr = InitEspriteSlot(func_8000B838_main(0x38001F), 0, 0);
    func_8000BBD4_main(spr, 0xA0, 0x78);
    func_8000BCC8_main(spr, 0x8096);
    D_8010DE54_aces_high.u = D_8010DE54_aces_high.v = 0.0f;
    func_800335BC_main("m223_03kaze_IA88", &D_8010DE50_aces_high);
    func_8001C954_main(obj->model[3]);
    obj->func = func_801061E0_aces_high;
}

void func_801061E0_aces_high(omObjData *obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010DE54_aces_high.v += 2.0f;
        D_8010DC0C_aces_high -= 0.0f;
        if (D_8010DC0C_aces_high < 0.0f) {
            D_8010DC0C_aces_high += 360.0f;
        }
    }
    func_8001E888_main(obj->model[3], D_8010DE54_aces_high.u, D_8010DE54_aces_high.v, D_8010DE50_aces_high.w,
                       D_8010DE50_aces_high.h, "m223_4-cyl11", 0);
    Hu3DModelRotSet(obj->model[3], 0.0f, D_8010DC0C_aces_high, 0.0f);
}

void func_801062DC_aces_high(omObjData *obj) {
    AhPlayer *work;
    u16 player;
    s8 chr;
    s16 grp;
    s16 i;
    s16 spr;

    player = obj->work[0];
    work = obj->data = HuMemAllocTag(sizeof(AhPlayer), 0x7918);
    work->unk02 = player;
    chr = GwPlayer[player].chr;
    obj->model[0] = func_8000B108_main(D_8010DC10_aces_high[chr], 0x6B9);
    if (player == 0) {
        obj->model[1] = func_8000B108_main(0x380008, 0x6D9);
        obj->model[2] = func_8000B108_main(0x380009, 0x6D9);
        obj->model[3] = func_8000B108_main(0x380021, 0x6D9);
        obj->model[4] = func_8000B108_main(0x380022, 0x6D9);
        obj->model[5] = func_8000B108_main(0x380023, 0x6D9);
        obj->model[6] = func_8000B108_main(0x380024, 0x6D9);
    } else {
        obj->model[1] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[1]);
        obj->model[2] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[2]);
        obj->model[3] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[3]);
        obj->model[4] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[4]);
        obj->model[5] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[5]);
        obj->model[6] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[6]);
    }
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C2FC_main(obj->model[3], 0x70000000, 0x70000000);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C814_main(obj->model[4], 3, 2);
    func_8001C814_main(obj->model[5], 3, 2);
    func_8001C814_main(obj->model[6], 3, 2);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8001C258_main(obj->model[6], 4, 4);
    omSetTra(obj, sindf(D_8010DC80_aces_high[player]) * 1150.0f, -250.0f, cosdf(D_8010DC80_aces_high[player]) * 1150.0f);
    omSetRot(obj, 0.0f, atan2df(-obj->trans.x, -obj->trans.z), 0.0f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    grp = func_8000B838_main(D_8010DC30_aces_high[chr]);
    work->unk1C = InitEspriteSlot(grp, 0, 0);
    work->unk1E = InitEspriteSlot(grp, 0, 0);
    i = 0;
    func_8000BB94_main(work->unk1E);
    grp = func_8000B838_main(0x38001D);
    do {
        work->unk28[i] = InitEspriteSlot(grp, 0, 0);
        func_8000BBD4_main(work->unk28[i], D_8010DC50_aces_high[player][i][0], D_8010DC50_aces_high[player][i][1]);
        i++;
    } while (i < 2);
    work->unk2E = spr = InitEspriteSlot(D_8010DEA4_aces_high, 0, 0);
    func_8000BCC8_main(spr, 0x80C8);
    func_8000BB94_main(spr);
    work->unk30 = spr = InitEspriteSlot(D_8010DEA6_aces_high, 0, 0);
    func_8000BCC8_main(spr, 0x80C8);
    func_8000BBD4_main(spr, D_8010DC70_aces_high[player][0], D_8010DC70_aces_high[player][1]);
    func_8000BB94_main(spr);
    work->unk0C = 0;
    work->unk3C = 0.0f;
    work->unk38 = 0.0f;
    work->unk40 = 0.0f;
    work->unk32 = 0;
    work->unk34 = 0;
    work->unk20 = 0;
    work->unk24 = 4;
    work->unk00 = 0;
    work->unk26 = 2;
    work->unk2C = -1;
    work->unk36 = 0;
    work->unk52 = 0;
    work->unk54 = 1;
    work->unk56 = 1;
    work->unk58 = 0;
    work->unk4C = 1;
    work->unk6C = 0.0f;
    work->unk5C = 0.0f;
    work->unk60 = 0.0f;
    work->unk68 = 0.0f;
    work->unk64 = 0.0f;
    work->unk08 = 27.777777f;
    work->unk10 = sindf(obj->rot.y);
    work->unk14 = 0.0f;
    work->unk18 = cosdf(obj->rot.y);
    work->unk88 = 0;
    work->unk44 = 0.0f;
    work->unk90 = 1;
    work->unk8C = obj->rot.y;
    work->unk94 = 0;
    work->unk92 = 0;
    work->unkAE = 0;
    work->unk70 = 0;
    work->unk74 = omAddObj(0x3C, 0, 0, -1, func_8010D6D4_aces_high);
    work->unk74->work[2] = 0;
    work->unk74->work[3] = (u32)obj;
    work->unk78 = omAddObj(0x3C, 0, 0, -1, func_8010D994_aces_high);
    work->unk78->work[0] = (u32)obj;
    work->unk78->work[1] = 0;
    work->unk78->scale.x = 0.0f;
    obj->work[0] = 0x1E;
    work->unk04 = omAddObj(0x32, 0, 0, -1, func_8010A9D4_aces_high);
    work->unk04->work[0] = 1;
    work->unk04->work[1] = (u32)obj;
    obj->func = func_80106EC0_aces_high;
}

void func_801068F4_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;

    func_80088910_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, work->unk38, 0.0f, work->unk3C + work->unk44);
    omSetRot(obj, 0.0f, obj->rot.y, 0.0f);
    if (work->unk90 == 0) {
        func_8001C258_main(obj->model[0], 4, 4);
    } else {
        func_8001C258_main(obj->model[0], 4, 0);
    }
    if (work->unk56 == 1) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x + work->unk60, obj->trans.y + work->unk68, obj->trans.z + work->unk64);
        func_80088910_main((f32(*)[4])HmfModelData[obj->model[1]].mtx, work->unk38, 0.0f, work->unk3C + work->unk44);
        Hu3DModelRotSet(obj->model[1], 0.0f, obj->rot.y, 0.0f);
        Hu3DModelPosSet(obj->model[2], obj->trans.x + work->unk60, obj->trans.y + work->unk68, obj->trans.z + work->unk64);
        func_80088910_main((f32(*)[4])HmfModelData[obj->model[2]].mtx, work->unk38, 0.0f, work->unk3C + work->unk44);
        Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
        if (work->unk58 == 0) {
            func_8001C258_main(obj->model[2], 4, 4);
            func_8001C258_main(obj->model[1], 4, 0);
        } else {
            func_8001C258_main(obj->model[1], 4, 4);
            func_8001C258_main(obj->model[2], 4, 0);
        }
        if (work->unk90 == 0) {
            func_8001C258_main(obj->model[1], 4, 4);
            func_8001C258_main(obj->model[2], 4, 4);
        }
    }
}

void func_80106B70_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    s16 mdl;

    switch (work->unk4C) {
        case 0:
            mdl = obj->model[4];
            func_8001C258_main(obj->model[5], 4, 4);
            func_8001C258_main(obj->model[6], 4, 4);
            break;
        case 1:
            mdl = obj->model[5];
            func_8001C258_main(obj->model[4], 4, 4);
            func_8001C258_main(obj->model[6], 4, 4);
            break;
        case 2:
            mdl = obj->model[6];
            func_8001C258_main(obj->model[4], 4, 4);
            func_8001C258_main(obj->model[5], 4, 4);
            break;
        case 3:
            mdl = -1;
            func_8001C258_main(obj->model[4], 4, 4);
            func_8001C258_main(obj->model[5], 4, 4);
            func_8001C258_main(obj->model[6], 4, 4);
            break;
    }
    if (mdl >= 0) {
        func_8001C258_main(mdl, 4, 0);
        Hu3DModelPosSet(mdl, obj->trans.x, obj->trans.y, obj->trans.z);
        func_80088910_main((f32(*)[4])HmfModelData[mdl].mtx, work->unk38, 0.0f, work->unk3C + work->unk44);
        Hu3DModelRotSet(mdl, 0.0f, obj->rot.y, 0.0f);
    }
    if (work->unk90 == 0) {
        func_8001C258_main(obj->model[4], 4, 4);
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[6], 4, 4);
    }
}

/* Debug: the D-pad and C buttons of pad 0 turn, pitch and roll the plane. */
void func_80106D2C_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;

    if (D_800CDA7C_main[0] & 0x200) {
        obj->rot.y -= 2.0f;
    }
    if (D_800CDA7C_main[0] & 0x100) {
        obj->rot.y += 2.0f;
    }
    if (obj->rot.y < 0.0f) {
        obj->rot.y += 360.0f;
    }
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    if (D_800CDA7C_main[0] & 0x800) {
        work->unk38 += 2.0f;
    }
    if (D_800CDA7C_main[0] & 0x400) {
        work->unk38 -= 2.0f;
    }
    if (D_800CDA7C_main[0] & 2) {
        work->unk3C -= 2.0f;
    }
    if (D_800CDA7C_main[0] & 1) {
        work->unk3C += 2.0f;
    }
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
}

void func_80106EC0_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    f32 s;

    if (obj->work[0] != 0) {
        obj->work[0]--;
    } else {
        switch (work->unk88) {
            case 0:
                work->unk38 -= 4.0f;
                if (work->unk38 <= -90.0f) {
                    work->unk38 += 180.0f;
                    work->unk3C += 180.0f;
                    obj->rot.y += 180.0f;
                    work->unk88 = 1;
                }
                break;
            case 1:
                work->unk38 -= 4.0f;
                if (work->unk38 <= 0.0f) {
                    work->unk88 = 2;
                }
                break;
            case 2:
                work->unk38 += 4.0f;
                work->unk3C -= 8.0f;
                if (work->unk38 >= 90.0f) {
                    work->unk38 = 90.0f;
                    work->unk3C = 0.0f;
                    work->unk88 = 3;
                }
                break;
            case 3:
                work->unk38 -= 4.0f;
                if (work->unk38 <= 0.0f) {
                    work->unk38 = 0.0f;
                    obj->work[1] = 0x1E;
                    work->unk04->func = func_8010AADC_aces_high;
                    work->unk04->work[2] = 0;
                    work->unk04->scale.x = CRotM[work->unk02].x;
                    work->unk88 = 4;
                    if (work->unk02 == 3) {
                        func_800E6F0C_minigame(1);
                    }
                }
                break;
            case 4:
                if (--obj->work[1] == 0) {
                    work->unk04->func = func_8010A51C_aces_high;
                    obj->func = func_80107654_aces_high;
                }
                break;
        }
    }
    s = sindf(work->unk38);
    work->unk14 = -s * cosdf(work->unk3C);
    work->unk10 = sindf(obj->rot.y) * (1.0 - fabs(work->unk14));
    work->unk18 = cosdf(obj->rot.y) * (1.0 - fabs(work->unk14));
    obj->trans.x += work->unk10 * work->unk08;
    obj->trans.y += work->unk14 * work->unk08;
    obj->trans.z += work->unk18 * work->unk08;
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
}

/* Player control: stick to pitch and roll, speed. */
// register allocation only (masked 0, raw 3): retail holds the direction constant in v0, here v1
#ifdef NON_MATCHING
void func_801071D4_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    s8 stickX;
    s8 stickY;
    s16 btn;
    u16 btn2;
    f32 target;
    f32 speed;

    func_801088A4_aces_high(obj, &stickX, &stickY, &btn, &btn2);
    btn2 = 0;
    btn = 0;
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = (stickY / 70.0f) * 30.0f;
    if (target < work->unk38) {
        if (target - work->unk38 < -10.0f) {
            work->unk38 -= 10.0f;
            work->unk7C = -10.0f;
        } else {
            work->unk38 = target;
            work->unk7C = target;
        }
    } else if (target - work->unk38 > 10.0f) {
        work->unk38 += 10.0f;
        work->unk7C = 10.0f;
    } else {
        work->unk38 = target;
        work->unk7C = target;
    }
    target = (stickX / 70.0f) * 60.0f;
    if (target < work->unk3C) {
        if (target - work->unk3C < -10.0f) {
            work->unk3C -= 10.0f;
            work->unk80 = -10.0f;
        } else {
            work->unk3C = target;
            work->unk80 = target;
        }
    } else if (target - work->unk3C > 10.0f) {
        work->unk3C += 10.0f;
        work->unk80 = 10.0f;
    } else {
        work->unk3C = target;
        work->unk80 = target;
    }
    work->unk84 = work->unk80 / 30.0f;
    if (btn2 & 0x4000) {
        speed = 16.666666f;
        work->unk4C = 0;
    } else if (btn2 & 0x8000) {
        speed = 41.666664f;
        work->unk4C = 2;
    } else {
        speed = 27.777777f;
        work->unk4C = 1;
    }
    if (work->unk0C == 1) {
        speed *= 2.0f;
    }
    if (speed < work->unk08) {
        work->unk08 -= 2.0f;
        if (work->unk08 < speed) {
            work->unk08 = speed;
        }
    } else if (work->unk08 < speed) {
        work->unk08 += 2.0f;
        if (speed < work->unk08) {
            work->unk08 = speed;
        }
    }
    if (stickX == 0) {
        work->unk32 = 0;
    } else {
        s16 dir;
        if (stickX < 0) {
            dir = 1;
        } else {
            dir = 2;
        }
        work->unk32 = dir;
    }
    obj->rot.y -= work->unk3C / 30.0f;
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    if (obj->rot.y < 0.0f) {
        obj->rot.y += 360.0f;
    }
    work->unk14 = -sindf(work->unk38);
    work->unk10 = sindf(obj->rot.y) * (1.0 - fabs(work->unk14));
    work->unk18 = cosdf(obj->rot.y) * (1.0 - fabs(work->unk14));
    obj->trans.x += work->unk10 * work->unk08;
    obj->trans.y += work->unk14 * work->unk08;
    obj->trans.z += work->unk18 * work->unk08;
    func_8010862C_aces_high(obj);
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801071D4_aces_high);
#endif

// masked 0 apart from one instruction: retail copies mode to a0 (move a0,s2) before the mode == 3 test of the input select; the same operations otherwise
#ifdef NON_MATCHING
/* Main flight: hits taken, input (pad or CPU), steering, shots and the arena edge. */
void func_80107654_aces_high(omObjData *obj) {
    f32 shake[4] = { 10.0f, 0.0f, -10.0f, 0.0f };
    s8 stickX;
    s8 stickY;
    u16 btn;
    u16 btnHeld;
    AhPlayer *work;
    u32 hit;
    s32 mode;
    s32 t;
    f32 target;
    f32 speed;

    work = obj->data;
    hit = obj->unk10;
    obj->unk10 = 0;
    if (hit & 1) {
        func_8004AC5C_main(0x3AF, work->unk02);
        func_8000BB94_main(work->unk28[--work->unk26]);
        if (work->unk26 == 0) {
            work->unk00 = 4;
            work->unk4E = 0x2D;
            work->unk4C = 3;
            work->unk58 = 0;
            func_8010A884_aces_high(obj);
            func_8001C258_main(obj->model[3], 4, 0);
            func_8001C814_main(obj->model[3], 3, 2);
            func_8001C6A8_main(obj->model[3], 0.0f);
            Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
            D_8010DE8C_aces_high--;
            work->unk98 = 0;
            HuAudFXPlay(0x3B0);
            obj->func = func_801081A8_aces_high;
            omVibrate(work->unk02, 0x1E, 0, 0x1E);
            func_8004ACE0_main(0x286, work->unk02);
            return;
        }
        work->unk00 = 3;
        work->unk50 = 0x1E;
        omVibrate(work->unk02, 0x14, 0, 0x14);
        func_8004ACE0_main(0x2AB, work->unk02);
    }
    if (hit & 2) {
        work->unk56 = 1;
        work->unk5C = 50.0f;
        func_8001C258_main(obj->model[1], 4, 0);
    }
    if (hit & 4) {
        work->unk74->work[0] = 0x2D;
        work->unk74->work[1] = 6;
        work->unk74->work[2] = 1;
    }
    func_8010843C_aces_high(obj);
    mode = func_800E6E8C_minigame();
    if (mode == 2 || mode == 3 || func_800E6E8C_minigame() == 4) {
        if (((GwPlayer[work->unk02].stat & 1) | (t = (mode == 3))) || mode == 4) {
            func_801088A4_aces_high(obj, &stickX, &stickY, &btn, &btnHeld);
            if (mode == 3 || mode == 4) {
                btnHeld = 0;
                btn = 0;
            }
        } else {
            s8 pad = GwPlayer[work->unk02].pad;
            stickX = D_800CBB6E_main[pad];
            stickY = D_800D20A1_main[pad];
            btn = D_800D5558_main[pad];
            btnHeld = D_800CDA7C_main[pad];
        }
    } else {
        btnHeld = 0;
        btn = 0;
        stickY = 0;
        stickX = 0;
    }
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = (stickY / 70.0f) * 30.0f;
    if (target < work->unk38) {
        if (target - work->unk38 < -10.0f) {
            work->unk38 -= 10.0f;
            work->unk7C = -10.0f;
        } else {
            work->unk38 = target;
            work->unk7C = target;
        }
    } else if (target - work->unk38 > 10.0f) {
        work->unk38 += 10.0f;
        work->unk7C = 10.0f;
    } else {
        work->unk38 = target;
        work->unk7C = target;
    }
    target = (stickX / 70.0f) * 60.0f;
    if (target < work->unk3C) {
        if (target - work->unk3C < -10.0f) {
            work->unk3C -= 10.0f;
            work->unk80 = -10.0f;
        } else {
            work->unk3C = target;
            work->unk80 = target;
        }
    } else if (target - work->unk3C > 10.0f) {
        work->unk3C += 10.0f;
        work->unk80 = 10.0f;
    } else {
        work->unk3C = target;
        work->unk80 = target;
    }
    work->unk84 = work->unk80 / 30.0f;
    if (btnHeld & 0x4000) {
        speed = 16.666666f;
        work->unk4C = 0;
    } else if (btnHeld & 0x8000) {
        speed = 41.666664f;
        work->unk4C = 2;
    } else {
        speed = 27.777777f;
        work->unk4C = 1;
    }
    if (speed < work->unk08) {
        work->unk08 -= 2.0f;
        if (work->unk08 < speed) {
            work->unk08 = speed;
        }
    } else if (work->unk08 < speed) {
        work->unk08 += 2.0f;
        if (speed < work->unk08) {
            work->unk08 = speed;
        }
    }
    if (stickX == 0) {
        work->unk32 = 0;
    } else {
        s16 dir;
        if (stickX < 0) {
            dir = 1;
        } else {
            dir = 2;
        }
        work->unk32 = dir;
    }
    obj->rot.y -= work->unk3C / 30.0f;
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    if (obj->rot.y < 0.0f) {
        obj->rot.y += 360.0f;
    }
    work->unk14 = -sindf(work->unk38);
    work->unk10 = sindf(obj->rot.y) * (1.0 - fabs(work->unk14));
    work->unk18 = cosdf(obj->rot.y) * (1.0 - fabs(work->unk14));
    obj->trans.x += work->unk10 * work->unk08;
    obj->trans.y += work->unk14 * work->unk08;
    obj->trans.z += work->unk18 * work->unk08;
    if (obj->trans.y < -500.0f) {
        obj->trans.y = -500.0f;
    }
    if (obj->trans.y > 500.0f) {
        obj->trans.y = 500.0f;
    }
    work->unk44 = 0.0f;
    if (work->unk00 == 3) {
        if (work->unk50 == 0) {
            work->unk90 = 1;
            work->unk00 = 0;
        } else {
            if (--work->unk50 & 1) {
                work->unk90 = 0;
            } else {
                work->unk90 = 1;
            }
            work->unk44 = shake[work->unk50 & 3];
        }
    }
    func_8010862C_aces_high(obj);
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
    if (btnHeld & 0x2000) {
        if (work->unk54 == 1) {
            work->unk52++;
            if (work->unk52 >= 0x1E) {
                work->unk58 ^= 1;
            }
        }
    } else {
        if (work->unk52 >= 0x1E && work->unk54 == 1) {
            func_8010BF3C_aces_high(obj);
            func_8004AC5C_main(0x3B2, work->unk02);
        }
        work->unk52 = 0;
        work->unk58 = 0;
    }
    if (work->unk20 == 0) {
        if ((btn & 0x2000) && work->unk24 != 0) {
            func_8010B9F4_aces_high(obj);
            func_8004AC5C_main(0x3AD, work->unk02);
        }
    } else {
        work->unk20--;
    }
    if (HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) >= 3950.0f) {
        work->unk00 = 1;
        work->unk48 = (500.0f - obj->trans.y) / 45.0f;
        work->unk4E = 0x2D;
        work->unk52 = 0;
        work->unk92 = 0;
        obj->func = func_80107F98_aces_high;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DD48_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80107654_aces_high);
#endif

/* Past the arena edge: dive, turn back towards the centre and climb back in. */
void func_80107F98_aces_high(omObjData *obj) {
    u32 hit;
    AhPlayer *work;
    f32 angle;

    hit = obj->unk10;
    obj->unk10 = 0;
    work = obj->data;
    if (hit & 2) {
        work->unk56 = 1;
        work->unk5C = 50.0f;
        func_8001C258_main(obj->model[1], 4, 0);
    }
    if (hit & 4) {
        work->unk74->work[0] = 0x2D;
        work->unk74->work[1] = 6;
        work->unk74->work[2] = 1;
    }
    angle = atan2df(-obj->trans.x, -obj->trans.z);
    work->unk58 = 0;
    switch (work->unk00) {
        case 1:
            work->unk38 -= 15.0f;
            if (work->unk38 < -90.0f) {
                work->unk38 = -90.0f;
            }
            obj->rot.y += 20.0f;
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
            obj->trans.y += work->unk48;
            if (--work->unk4E == 0) {
                obj->trans.y = 500.0f;
                obj->rot.y = angle;
                work->unk3C = 0.0f;
                work->unk00 = 2;
                work->unk90 = 1;
            } else if (work->unk4E & 1) {
                work->unk90 = 0;
            } else {
                work->unk90 = 1;
            }
            break;
        case 2:
            work->unk38 += 15.0f;
            if (work->unk38 >= 0.0f) {
                work->unk38 = 0.0f;
                work->unk00 = 0;
                obj->func = func_80107654_aces_high;
            }
            work->unk90 = 1;
            break;
    }
    func_8010843C_aces_high(obj);
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
}

/* Shot down: nose over and fall out of the sky, then leave the game. */
void func_801081A8_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    s16 mdl;

    switch (work->unk00) {
        case 4:
            work->unk38 += 10.0f;
            if (work->unk38 >= 90.0f) {
                work->unk38 = 90.0f;
                work->unk00 = 5;
            }
            break;
        case 5:
            if (work->unk36 == 0 && obj->trans.y < -1000.0f) {
                work->unk36 = 1;
            }
            if (obj->trans.y < -3000.0f) {
                work->unk00 = 6;
                obj->func = NULL;
                work->unk90 = 0;
                func_8001C258_main(obj->model[3], 4, 4);
                work->unk04->func = func_8010ACE0_aces_high;
                mdl = D_8010DE64_aces_high->model[3];
                func_8001C8A8_main(mdl, HmfModelData[mdl].unk01 & ~D_8010DB68_aces_high[work->unk02]);
            }
            break;
    }
    work->unk14 = -sindf(work->unk38);
    work->unk10 = sindf(obj->rot.y) * (1.0 - fabs(work->unk14));
    work->unk18 = cosdf(obj->rot.y) * (1.0 - fabs(work->unk14));
    obj->trans.x += work->unk10 * work->unk08;
    obj->trans.y += work->unk14 * work->unk08;
    obj->trans.z += work->unk18 * work->unk08;
    func_8010843C_aces_high(obj);
    func_801068F4_aces_high(obj);
    func_80106B70_aces_high(obj);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    work->unk74->work[2] = 0;
    work->unk78->work[1] = 0;
    func_8000BB94_main(work->unk2E);
    func_8000BB94_main(work->unk30);
    if (work->unk2C != -1) {
        HuAudFXStop(work->unk2C);
        work->unk2C = -1;
    }
}

/* Recoil after a collision: the plane's offset dies away. */
void func_8010843C_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    f32 x;
    f32 y;

    if (work->unk5C > 0.0f) {
        work->unk5C -= 10.0f;
        x = -sindf(work->unk3C);
        y = sindf(work->unk38);
        work->unk60 = x * cosdf(-obj->rot.y) - y * sindf(-obj->rot.y);
        work->unk64 = x * sindf(-obj->rot.y) + y * cosdf(-obj->rot.y);
        work->unk68 = 1.0f - HuSqrtf(work->unk60 * work->unk60 + work->unk64 * work->unk64);
        work->unk60 *= work->unk5C;
        work->unk68 *= work->unk5C;
        work->unk64 *= work->unk5C;
        if (work->unk5C <= 0.0f) {
            work->unk5C = 0.0f;
            work->unk54 = 1;
            work->unk52 = 0;
        }
    }
}

/* Hides every player's two life icons. */
void func_801085B0_aces_high(void) {
    AhPlayer *work;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        work = D_8010DE68_aces_high[i]->data;
        for (j = 0; j < 2; j++) {
            func_8000BB94_main(work->unk28[j]);
        }
    }
}

/* Pushes the plane out of any other plane it overlaps: down, up, right, then left. */
void func_8010862C_aces_high(omObjData *obj) {
    AhPlayer *work;
    AhPlayer *ow;
    omObjData *other;
    s32 i;
    u16 tries;
    f32 y;
    f32 d;

    work = obj->data;
    for (tries = 0; tries < 4; tries++) {
        for (i = 0; i < 4; i++) {
            if (i == work->unk02) {
                continue;
            }
            other = D_8010DE68_aces_high[i];
            ow = other->data;
            if ((ow->unk00 == 6) | (ow->unk00 == 1)) {
                continue;
            }
            if (ow->unk00 == 3) {
                continue;
            }
            if (HuSqrtf((obj->trans.x - other->trans.x) * (obj->trans.x - other->trans.x) +
                        (obj->trans.y - other->trans.y) * (obj->trans.y - other->trans.y) +
                        (obj->trans.z - other->trans.z) * (obj->trans.z - other->trans.z)) <= HuSqrtf(32400.0f)) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        omVibrate(work->unk02, 2, 3, 10);
        omVibrate(ow->unk02, 2, 3, 10);
        switch (tries) {
            case 0:
                d = -90.0f;
                y = obj->trans.y + d;
                if (y >= -500.0f) {
                    obj->trans.y = y;
                }
                break;
            case 1:
                d = 90.0f;
                y = obj->trans.y + d;
                if (y <= 500.0f) {
                    obj->trans.y = y;
                }
                break;
            case 2:
                d = 90.0f;
                obj->trans.x += sindf(obj->rot.y + d) * d;
                obj->trans.z += cosdf(obj->rot.y + d) * d;
                break;
            case 3:
                d = 90.0f;
                obj->trans.x += sindf(obj->rot.y - d) * d;
                obj->trans.z += cosdf(obj->rot.y - d) * d;
                break;
        }
    }
}

// register allocation only (masked 0): retail keeps stickX in s5 and stickY in s4, here the reverse; abs.s source register
#ifdef NON_MATCHING
/* CPU control: per difficulty, pick a target (chase a plane, dodge, return to the arena) and steer to it. */
void func_801088A4_aces_high(omObjData *obj, s8 *stickX, s8 *stickY, s16 *btn, u16 *btn2) {
    omObjData *list[4];
    Vec target;
    omObjData *nearest;
    f32 nearDist;
    AhPlayer *work;
    AhPlayer *tw;
    omObjData *other;
    u16 state;
    f32 farLimit;
    f32 nearLimit;
    f32 fov;
    f32 turn;
    f32 fleeDist;
    f32 dist;
    f32 a;
    f32 b;
    f32 d;
    u16 res;

    *stickY = 0;
    *stickX = 0;
    *btn2 = 0;
    *btn = 0;
    work = obj->data;
    switch (GwPlayer[work->unk02].cpu_difficulty) {
        case 0:
            farLimit = 1000.0f;
            nearLimit = 500.0f;
            fov = 30.0f;
            turn = 5.0f;
            fleeDist = 500.0f;
            break;
        case 1:
            farLimit = 900.0f;
            nearLimit = 500.0f;
            fov = 30.0f;
            turn = 4.0f;
            fleeDist = 700.0f;
            break;
        case 2:
            farLimit = 800.0f;
            nearLimit = 400.0f;
            fov = 40.0f;
            turn = 3.0f;
            fleeDist = 900.0f;
            break;
        case 3:
            farLimit = 700.0f;
            nearLimit = 400.0f;
            fov = 40.0f;
            turn = 3.0f;
            fleeDist = 1200.0f;
            break;
    }
    state = work->unk92;
    if ((HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) > 3150.0f) & (state != 2) && state != 5 &&
        state != 6) {
        a = atan2df(obj->trans.x, obj->trans.z);
        if (a < 0.0f) {
            a += 360.0f;
        }
        b = obj->rot.y;
        if (b < 0.0f) {
            b += 360.0f;
        }
        d = b - a;
        if (fabs(d) < 75.0) {
            work->unk94 = work->unk92;
            work->unk92 = 2;
            work->unkA8 = a - 180.0f;
            if (work->unkA8 < 0.0f) {
                work->unkA8 += 360.0f;
            }
        }
    }
    if (state == 0) {
        func_80109928_aces_high(obj);
    }
    switch (state) {
        case 1:
            other = work->unk98;
            tw = other->data;
            if (tw->unk00 != 4 && tw->unk00 != 5 && tw->unk00 != 6) {
                dist = HuSqrtf((other->trans.x - obj->trans.x) * (other->trans.x - obj->trans.x) +
                               (other->trans.z - obj->trans.z) * (other->trans.z - obj->trans.z)) * 0.8f;
                if (dist > 1500.0f) {
                    dist = 1500.0f;
                }
                if (dist < 100.0f) {
                    dist = 100.0f;
                }
                target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
                target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
                target.y = other->trans.y;
                dist = HuSqrtf((obj->trans.x - other->trans.x) * (obj->trans.x - other->trans.x) +
                               (obj->trans.y - other->trans.y) * (obj->trans.y - other->trans.y) +
                               (obj->trans.z - other->trans.z) * (obj->trans.z - other->trans.z));
                res = func_8010951C_aces_high(obj, &target, turn, 60.0f, stickX, stickY);
                if (dist < 2400.0f) {
                    *btn |= 0x2000;
                }
                if ((farLimit < dist && !(res & 0x4000)) || (res & 0x8000)) {
                    *btn2 |= 0x8000;
                }
                if ((dist < nearLimit && !(res & 0x8000)) || (res & 0x4000)) {
                    *btn2 |= 0x4000;
                }
                if (--work->unkB0 == 0) {
                    work->unk92 = 0;
                    work->unk34 = 0;
                }
            } else {
                work->unk92 = 0;
                work->unk34 = 0;
            }
            break;
        case 3:
            other = work->unk98;
            tw = other->data;
            if (tw->unk00 == 4 || tw->unk00 == 5 || tw->unk00 == 6 || work->unkAE == 0) {
                work->unk92 = 0;
                work->unk34 = 0;
                break;
            }
            dist = HuSqrtf((other->trans.x - obj->trans.x) * (other->trans.x - obj->trans.x) +
                           (other->trans.z - obj->trans.z) * (other->trans.z - obj->trans.z)) * 0.8f;
            if (dist > 1500.0f) {
                dist = 1500.0f;
            }
            if (dist < 100.0f) {
                dist = 100.0f;
            }
            target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
            target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
            target.y = other->trans.y;
            dist = HuSqrtf((obj->trans.x - other->trans.x) * (obj->trans.x - other->trans.x) +
                           (obj->trans.y - other->trans.y) * (obj->trans.y - other->trans.y) +
                           (obj->trans.z - other->trans.z) * (obj->trans.z - other->trans.z));
            res = func_8010951C_aces_high(obj, &target, turn, 60.0f, stickX, stickY);
            if ((farLimit < dist && !(res & 0x4000)) || (res & 0x8000)) {
                *btn2 |= 0x8000;
            }
            if ((dist < nearLimit && !(res & 0x8000)) || (res & 0x4000)) {
                *btn2 |= 0x4000;
            }
            break;
        case 4:
            target = work->unk9C;
            dist = HuSqrtf((obj->trans.x - work->unk9C.x) * (obj->trans.x - work->unk9C.x) +
                           (obj->trans.y - work->unk9C.y) * (obj->trans.y - work->unk9C.y) +
                           (obj->trans.z - work->unk9C.z) * (obj->trans.z - work->unk9C.z));
            res = func_8010951C_aces_high(obj, &target, turn, 20.0f, stickX, stickY);
            if ((farLimit < dist && !(res & 0x4000)) || (res & 0x8000)) {
                *btn2 |= 0x8000;
            }
            if ((dist < nearLimit && !(res & 0x8000)) || (res & 0x4000)) {
                *btn2 |= 0x4000;
            }
            if (dist < 100.0f) {
                work->unk92 = 0;
            }
            if (--work->unkB0 == 0) {
                work->unk92 = 0;
            }
            break;
        case 2:
            a = work->unkA8;
            b = obj->rot.y;
            if (b < 0.0f) {
                b += 360.0f;
            }
            d = b - a;
            if (fabs(d) < 5.0) {
                work->unk92 = work->unk94;
            } else {
                if (fabs(d) > 35.0) {
                    b = 70.0f;
                } else {
                    b = fabsf(d / 2.0f);
                }
                if (b < 10.0f) {
                    b = 10.0f;
                }
                if (d < 0.0f) {
                    d += 360.0f;
                }
                if (d < 180.0f) {
                    *stickX = b;
                } else {
                    *stickX = -b;
                }
                if (HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) > 3600.0f) {
                    *btn2 |= 0x4000;
                }
            }
            break;
        case 5:
            target = work->unk9C;
            dist = HuSqrtf((obj->trans.x - work->unk9C.x) * (obj->trans.x - work->unk9C.x) +
                           (obj->trans.y - work->unk9C.y) * (obj->trans.y - work->unk9C.y) +
                           (obj->trans.z - work->unk9C.z) * (obj->trans.z - work->unk9C.z));
            res = func_8010951C_aces_high(obj, &target, 3.0f, 20.0f, stickX, stickY);
            if ((farLimit < dist && !(res & 0x4000)) || (res & 0x8000)) {
                *btn2 |= 0x8000;
            }
            if ((dist < nearLimit && !(res & 0x8000)) || (res & 0x4000)) {
                *btn2 |= 0x4000;
            }
            if (func_800E6E8C_minigame() == 4) {
                work->unk92 = 6;
                func_8010B26C_aces_high(obj);
                work->unk04->func = func_8010B4BC_aces_high;
                obj->func = func_801071D4_aces_high;
                work->unk4E = 0x19;
            }
            break;
        case 6:
            if (work->unk4E != 0) {
                *stickY = -0x2D;
                *stickX = -0x41;
                work->unk4E--;
            } else {
                *stickY = -0x46;
                work->unk0C = 1;
            }
            *btn2 |= 0x8000;
            break;
    }
    if (state != 5 && state != 6) {
        if (func_80109EEC_aces_high(obj, fov, list, &nearest, &nearDist) != 0) {
            if (nearDist <= 2750.0f) {
                *btn |= 0x2000;
            }
            if (work->unk92 == 1 && nearDist < 1000.0f) {
                work->unkB0 = (u8)(rand8() % 181) + 0x3C;
                work->unk92 = 1;
                work->unk98 = nearest;
            }
        }
        if (work->unk70 != 0 && func_8010A0F0_aces_high(obj) < fleeDist) {
            *btn2 = (*btn2 & ~0x4000) | 0x8000;
        }
        if (work->unkAE != 0) {
            if (work->unk52 < work->unkAC) {
                *btn2 |= 0x2000;
            } else {
                work->unkAE = 0;
            }
        }
        func_8010A214_aces_high(obj);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801088A4_aces_high);
#endif

// register allocation only (masked 0): retail keeps the angle difference in f4 and the stick value in f6, here the reverse
#ifdef NON_MATCHING
/* CPU steering towards target: stick values; returns 0x4000 when the turn is sharp (slow down). */
u16 func_8010951C_aces_high(omObjData *obj, Vec *target, f32 turn, f32 arg3, s8 *stickX, s8 *stickY) {
    AhPlayer *work;
    AhPlayer *tw;
    f32 scale;
    f32 dir;
    f32 heading;
    f32 v;
    f32 d;
    u16 res;

    work = obj->data;
    scale = HuSqrtf((target->x - obj->trans.x) * (target->x - obj->trans.x) +
                    (target->z - obj->trans.z) * (target->z - obj->trans.z)) / 600.0f;
    if (scale > 2.0f) {
        scale = 2.0f;
    }
    if (scale < 0.3f) {
        scale = 0.3f;
    }
    res = 0;
    dir = atan2df(target->x - obj->trans.x, target->z - obj->trans.z);
    heading = obj->rot.y;
    if (heading > 180.0f) {
        heading -= 360.0f;
    }
    d = heading - dir;
    if (fabs(d) < turn) {
        *stickX = 0;
    } else {
        if (fabs(d * scale) > 70.0) {
            v = 70.0f;
            res = 0x4000;
        } else {
            v = fabsf(d * scale);
        }
        if (v < 10.0f) {
            v = 0.0f;
        }
        if (dir < 0.0f) {
            dir += 360.0f;
        }
        if (heading < 0.0f) {
            heading += 360.0f;
        }
        d = dir - heading;
        if (d < 0.0f) {
            d += 360.0f;
        }
        if (d > 180.0f) {
            *stickX = v;
        } else {
            *stickX = -v;
        }
        if ((work->unk92 == 1) | (work->unk92 == 3)) {
            tw = work->unk98->data;
            if (tw->unk32 == work->unk32 && tw->unk34 == 0 && (u8)(rand8() % 10) < 5) {
                work->unk34 ^= 1;
            }
            if (work->unk34 != 0) {
                *stickX = -*stickX;
            }
        }
    }
    d = target->y - obj->trans.y;
    if (fabs(d) > arg3) {
        if (fabs(d * scale) > 70.0) {
            v = 70.0f;
        } else {
            v = fabsf(d * scale);
        }
        if (v < 10.0f) {
            v = 0.0f;
        }
        if (target->y > obj->trans.y) {
            *stickY = -v;
        } else {
            *stickY = v;
        }
    }
    return res;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010951C_aces_high);
#endif

/* CPU: choose the next goal, chasing a live plane (often, at higher difficulty) or flying to a random point. */
void func_80109928_aces_high(omObjData *obj) {
    u16 choices[4][8] = {
        { 4, 1, 4, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
    };
    AhPlayer *work;
    omObjData *other;
    s32 i;
    s16 chance;
    u16 done;
    u16 choice;
    u16 st;
    f32 angle;
    f32 r;

    work = obj->data;
    switch (GwPlayer[work->unk02].cpu_difficulty) {
        case 0:
            chance = 2;
            break;
        case 1:
            chance = 3;
            break;
        case 2:
            chance = 4;
            break;
        case 3:
            chance = 4;
            break;
    }
    if (D_8010DE8C_aces_high == 2) {
        chance *= 2;
    }
    done = 0;
    choice = choices[GwPlayer[work->unk02].cpu_difficulty][rand8() & 7];
    do {
        i = 0;
        switch (choice) {
        case 1:
            do {
                if (i == work->unk02) {
                    continue;
                }
                other = D_8010DE68_aces_high[i];
                st = ((AhPlayer *)other->data)->unk00;
                if ((st == 6) | (st == 4)) {
                    continue;
                }
                if ((st == 5) | (st == 1)) {
                    continue;
                }
                break;
            } while (++i < 4);
            if (i == 4) {
                choice = 4;
            } else {
                work->unk98 = other;
                if (work->unk54 == 1 && (u8)(rand8() % 10) < chance) {
                    work->unkAC = (rand8() & 0xF) + 0x1E;
                    work->unkAE = 1;
                    work->unk92 = 3;
                    done = 1;
                } else {
                    work->unkB0 = (u8)(rand8() % 181) + 0x3C;
                    work->unk92 = 1;
                    done = 1;
                }
            }
            break;
        case 4:
            if (D_8010DE8C_aces_high == 2 && (u8)(rand8() % 10) < 2) {
                choice = 1;
            } else {
                angle = atan2df(obj->trans.x, obj->trans.z) - 180.0f;
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                angle *= 10.0f;
                angle = (angle + ((f32)((rand8() * rand8()) % 900) - 450.0f)) / 10.0f;
                r = (f32)((rand8() * rand8()) % 2750) + 200.0f;
                work->unk9C.x = sindf(angle) * r;
                work->unk9C.z = cosdf(angle) * r;
                work->unk9C.y = (f32)((rand8() * rand8()) % 1000) + -500.0f;
                work->unk92 = 4;
                work->unkB0 = (u8)(rand8() % 121) + 0x3C;
                done = 1;
            }
            break;
        }
    } while (done == 0);
}

/* CPU: the live planes within fov degrees ahead (list), and the nearest of them. */
s16 func_80109EEC_aces_high(omObjData *obj, f32 fov, omObjData **list, omObjData **nearest, f32 *nearDist) {
    AhPlayer *work;
    omObjData *other;
    s16 n;
    s32 i;
    u16 st;
    f32 dir;
    f32 heading;
    f32 dist;

    n = 0;
    work = obj->data;
    *list = NULL;
    *nearDist = 1000000.0f;
    *nearest = NULL;
    for (i = 0; i < 4; i++) {
        if (work->unk02 == i) {
            continue;
        }
        other = D_8010DE68_aces_high[i];
        st = ((AhPlayer *)other->data)->unk00;
        if ((st == 6) | (st == 4)) {
            continue;
        }
        if ((st == 5) | (st == 1)) {
            continue;
        }
        dir = atan2df(other->trans.x - obj->trans.x, other->trans.z - obj->trans.z);
        heading = obj->rot.y;
        if (heading > 180.0f) {
            heading -= 360.0f;
        }
        if (fabs(heading - dir) <= fov / 2.0f) {
            list[n++] = other;
            dist = HuSqrtf((obj->trans.x - other->trans.x) * (obj->trans.x - other->trans.x) +
                           (obj->trans.y - other->trans.y) * (obj->trans.y - other->trans.y) +
                           (obj->trans.z - other->trans.z) * (obj->trans.z - other->trans.z));
            if (dist < *nearDist) {
                *nearDist = dist;
                *nearest = other;
            }
        }
    }
    return n;
}

/* CPU: distance to the nearest flying enemy shot. */
f32 func_8010A0F0_aces_high(omObjData *obj) {
    AhPlayer *work;
    omObjData **shots;
    omObjData *shot;
    f32 best;
    f32 dist;
    s32 i;
    s32 j;

    work = obj->data;
    best = 1e7f;
    for (i = 0; i < 4; i++) {
        if (i == work->unk02) {
            continue;
        }
        shots = D_8010DE70_aces_high[i];
        for (j = 0; j < 5; j++) {
            shot = shots[j];
            if (shot != NULL && ((AhShot *)shot->data)->unk00 == 1) {
                dist = HuSqrtf((shot->trans.x - obj->trans.x) * (shot->trans.x - obj->trans.x) +
                               (shot->trans.y - obj->trans.y) * (shot->trans.y - obj->trans.y) +
                               (shot->trans.z - obj->trans.z) * (shot->trans.z - obj->trans.z));
                if (dist < best) {
                    best = dist;
                }
            }
        }
    }
    return best;
}

/* CPU: when another plane is chasing this one, sometimes break off to a random point. */
void func_8010A214_aces_high(omObjData *obj) {
    AhPlayer *work;
    s32 i;
    f32 angle;
    f32 r;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        if (((AhPlayer *)D_8010DE68_aces_high[i]->data)->unk98 == obj && work->unk92 != 4 && (u8)(rand8() % 10) < 5) {
            work->unk98 = NULL;
            angle = atan2df(obj->trans.x, obj->trans.z) - 180.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            angle *= 10.0f;
            angle += (f32)((rand8() * rand8()) % 900) - 450.0f;
            angle /= 10.0f;
            r = (f32)((rand8() * rand8()) % 2750) + 200.0f;
            work->unk9C.x = sindf(angle) * r;
            work->unk9C.z = cosdf(angle) * r;
            work->unk9C.y = (f32)((rand8() * rand8()) % 1000) + -500.0f;
            work->unk92 = 4;
            work->unkB0 = (u8)(rand8() % 121) + 0x3C;
        }
    }
}

// register allocation only (masked 0): retail multiplies sindf(rot.y) * 300 into f0, here straight into f22
#ifdef NON_MATCHING
/* Player camera: behind the plane; zoom follows the speed. When shot down, look at the falling plane. */
void func_8010A51C_aces_high(omObjData *obj) {
    omObjData *plane;
    AhPlayer *work;
    f32 x;
    f32 z;
    f32 y;
    f32 zoom;
    f32 rx;

    plane = (omObjData *)obj->work[1];
    work = plane->data;
    if (work->unk00 != 4 && work->unk00 != 5) {
        rx = plane->rot.y - 180.0f;
        CRotM[work->unk02].y = rx;
        rx = plane->trans.y * 0.06f;
        CRotM[work->unk02].x = rx;
        x = sindf(plane->rot.y) * 300.0f + plane->trans.x;
        z = cosdf(plane->rot.y) * 300.0f + plane->trans.z;
        y = plane->trans.y + 100.0f;
        CenterM[work->unk02].x = x;
        CenterM[work->unk02].y = y;
        CenterM[work->unk02].z = z;
        if (work->unk08 > 27.777777f) {
            zoom = (work->unk08 - 27.777777f) / 13.888887f * 150.0f + 1000.0f;
        } else if (work->unk08 < 27.777777f) {
            zoom = 1000.0f - (27.777777f - work->unk08) / 11.111111f * 150.0f;
        } else {
            zoom = 1000.0f;
        }
        CZoomM[work->unk02] = zoom;
        return;
    }
    rx = plane->trans.y * 0.06f;
    if (rx < -90.0f) {
        rx = -90.0f;
    }
    CRotM[work->unk02].x = rx;
    x = sindf(plane->rot.y) * 300.0f + plane->trans.x;
    z = cosdf(plane->rot.y) * 300.0f + plane->trans.z;
    y = plane->trans.y + 100.0f;
    CenterM[work->unk02].x = x;
    CenterM[work->unk02].y = y;
    CenterM[work->unk02].z = z;
    CZoomM[work->unk02] = HuSqrtf((obj->trans.x - plane->trans.x) * (obj->trans.x - plane->trans.x) +
                                  (obj->trans.y - plane->trans.y) * (obj->trans.y - plane->trans.y) +
                                  (obj->trans.z - plane->trans.z) * (obj->trans.z - plane->trans.z));
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A51C_aces_high);
#endif

/* Puts the camera object at the camera's eye position. */
void func_8010A884_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    f32 rx;
    f32 ry;

    rx = CRotM[work->unk02].x;
    ry = CRotM[work->unk02].y;
    work->unk04->trans.x = CenterM[work->unk02].x + sindf(ry) * cosdf(rx) * CZoomM[work->unk02];
    work->unk04->trans.y = CenterM[work->unk02].y + -sindf(rx) * CZoomM[work->unk02];
    work->unk04->trans.z = CenterM[work->unk02].z + cosdf(ry) * cosdf(rx) * CZoomM[work->unk02];
}

/* Intro camera: low behind the plane. */
void func_8010A9D4_aces_high(omObjData *obj) {
    omObjData *plane = (omObjData *)obj->work[1];
    AhPlayer *work = plane->data;

    f32 rx;

    rx = (plane->trans.y - -250.0f) * 0.08f;
    CRotM[work->unk02].x = rx;
    CRotM[work->unk02].z = 0.0f;
    CRotM[work->unk02].y = work->unk8C;
    CenterM[work->unk02].x = plane->trans.x;
    CenterM[work->unk02].y = 0.0f;
    CenterM[work->unk02].z = plane->trans.z;
    CZoomM[work->unk02] = 650.0f;
}

/* Camera swings in behind the plane over 30 frames. */
void func_8010AADC_aces_high(omObjData *obj) {
    omObjData *plane = (omObjData *)obj->work[1];
    AhPlayer *work = plane->data;

    obj->work[2]++;
    CRotM[work->unk02].x += (plane->trans.y * 0.06f - obj->scale.x) / 30.0f;
    CenterM[work->unk02].x = sindf(plane->rot.y) * 300.0f / 30.0f * obj->work[2] + plane->trans.x;
    CenterM[work->unk02].z = cosdf(plane->rot.y) * 300.0f / 30.0f * obj->work[2] + plane->trans.z;
    CenterM[work->unk02].y += (plane->trans.y + 100.0f) / 30.0f;
    CZoomM[work->unk02] += 11.666667f;
}

/* Shot down: the camera looks straight down from high up. */
void func_8010ACE0_aces_high(omObjData *obj) {
    AhPlayer *work = ((omObjData *)obj->work[1])->data;

    CenterM[work->unk02].y = 0.0f;
    CZoomM[work->unk02] = 2700.0f;
    CRotM[work->unk02].x = 90.0f;
}

/* Starts the ending camera move (func_8010AE30_aces_high). */
void func_8010AD4C_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    omObjData *cam = work->unk04;

    cam->scale.x = -180.0f;
    cam->trans.x = (-10.0f - CRotM[work->unk02].x) / 60.0f;
    cam->trans.y = CRotM[work->unk02].x;
    cam->scale.y = -4.5f;
    cam->scale.z = (750.0f - CZoomM[work->unk02]) / 60.0f;
    cam->trans.z = CZoomM[work->unk02];
    cam->work[2] = 0;
    cam->func = func_8010AE30_aces_high;
}

// masked 6: retail computes the centre y (trans.y + 100) in both paths, here once after the join; registers of ry/rx/cx differ; same operations otherwise
#ifdef NON_MATCHING
/* Ending camera: circles round and closes in on the winner over 60 frames. */
void func_8010AE30_aces_high(omObjData *obj) {
    omObjData *plane = (omObjData *)obj->work[1];
    AhPlayer *work = plane->data;
    f32 ry;
    f32 rx;
    f32 cx;
    f32 cy;
    f32 cz;
    f32 zoom;

    ry = plane->rot.y + obj->scale.x;
    obj->scale.x += 3.0f;
    rx = obj->work[2] * obj->trans.x + obj->trans.y;
    cx = sindf(plane->rot.y) * (obj->work[2] * obj->scale.y + 300.0f) + plane->trans.x;
    cz = cosdf(plane->rot.y) * (obj->work[2] * obj->scale.y + 300.0f) + plane->trans.z;
    cy = plane->trans.y + 100.0f;
    zoom = obj->work[2] * obj->scale.z + obj->trans.z;
    if (obj->work[2]++ >= 0x3C) {
        ry = plane->rot.y;
        rx = -10.0f;
        cx = sindf(ry) * 30.0f + plane->trans.x;
        cz = cosdf(plane->rot.y) * 30.0f + plane->trans.z;
        cy = plane->trans.y + 100.0f;
        zoom = 750.0f;
        obj->func = func_8010B0E8_aces_high;
    }
    CRotM[work->unk02].y = ry;
    CRotM[work->unk02].x = rx;
    CenterM[work->unk02].x = cx;
    CenterM[work->unk02].y = cy;
    CenterM[work->unk02].z = cz;
    CZoomM[work->unk02] = zoom;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AE30_aces_high);
#endif

// register allocation only (masked 0): retail multiplies sindf(rot.y) * 30 into f0, here into f20
#ifdef NON_MATCHING
/* Ending camera, held: behind the winner. */
void func_8010B0E8_aces_high(omObjData *obj) {
    omObjData *plane = (omObjData *)obj->work[1];
    AhPlayer *work = plane->data;
    f32 x;
    f32 y;
    f32 z;

    y = plane->rot.y;
    CRotM[work->unk02].y = y;
    CRotM[work->unk02].x = -10.0f;
    x = sindf(plane->rot.y) * 30.0f + plane->trans.x;
    z = cosdf(plane->rot.y) * 30.0f + plane->trans.z;
    y = plane->trans.y + 100.0f;
    CenterM[work->unk02].x = x;
    CenterM[work->unk02].y = y;
    CenterM[work->unk02].z = z;
    y = 750.0f;
    CZoomM[work->unk02] = y;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B0E8_aces_high);
#endif

/* The single full-screen camera of the ending. */
void func_8010B224_aces_high(omObjData *obj) {
    Hu3DCamSetPositionOrientation(obj->work[0], &D_8010DEA8_aces_high, &D_8010DEB4_aces_high, &D_8010DEC0_aces_high);
    Hu3DCamUpdateMtx(obj->work[0]);
}

/* Ending: one full-screen camera from the winner's view. */
void func_8010B26C_aces_high(omObjData *obj) {
    AhPlayer *work = obj->data;
    omObjData *view;
    f32 rx;
    f32 ry;

    rx = CRotM[work->unk02].x;
    ry = CRotM[work->unk02].y;
    D_8010DEA8_aces_high.x = CenterM[work->unk02].x + sindf(ry) * cosdf(rx) * CZoomM[work->unk02];
    D_8010DEA8_aces_high.y = CenterM[work->unk02].y + -sindf(rx) * CZoomM[work->unk02];
    D_8010DEA8_aces_high.z = CenterM[work->unk02].z + cosdf(ry) * cosdf(rx) * CZoomM[work->unk02];
    D_8010DEB4_aces_high.x = CenterM[work->unk02].x;
    D_8010DEB4_aces_high.y = CenterM[work->unk02].y;
    D_8010DEB4_aces_high.z = CenterM[work->unk02].z;
    D_8010DEC0_aces_high.x = sindf(ry) * sindf(rx);
    D_8010DEC0_aces_high.y = cosdf(rx);
    D_8010DEC0_aces_high.z = cosdf(ry) * sindf(rx);
    omDelObj(D_8010DE84_aces_high);
    D_8010DE84_aces_high = view = omAddObj(0x7FDA, 0, 0, -1, func_8010B224_aces_high);
    view->work[0] = work->unk02;
    omSetStatBit(view, 0xA0);
}

/* Ending camera object: look at the winner. */
void func_8010B4BC_aces_high(omObjData *obj) {
    omObjData *plane = (omObjData *)obj->work[1];
    AhPlayer *work = plane->data;
    f32 rx;
    f32 ry;

    D_8010DEB4_aces_high.x = sindf(plane->rot.y) * 30.0f + plane->trans.x;
    D_8010DEB4_aces_high.z = cosdf(plane->rot.y) * 30.0f + plane->trans.z;
    D_8010DEB4_aces_high.y = plane->trans.y + 100.0f;
    CRotM[work->unk02].y = atan2df(plane->trans.x - D_8010DEA8_aces_high.x, plane->trans.z - D_8010DEA8_aces_high.z);
    rx = CRotM[work->unk02].x;
    ry = CRotM[work->unk02].y;
    D_8010DEC0_aces_high.x = sindf(ry) * sindf(rx);
    D_8010DEC0_aces_high.y = cosdf(rx);
    D_8010DEC0_aces_high.z = cosdf(ry) * sindf(rx);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B618_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B760_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B9F4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BCC4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BD84_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BF3C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010C288_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010C9DC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CA6C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CD88_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CE5C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CFF8_aces_high);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DE28_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D1D8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D6D4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D994_aces_high);
