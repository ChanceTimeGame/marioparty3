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
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10; /* heading x */
    /* 0x14 */ f32 unk14; /* heading y */
    /* 0x18 */ f32 unk18; /* heading z */
    /* 0x1C */ s16 unk1C; /* esprite */
    /* 0x1E */ s16 unk1E; /* esprite */
    /* 0x20 */ u16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ s16 unk28[2]; /* esprites */
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E; /* esprite */
    /* 0x30 */ s16 unk30; /* esprite */
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u16 unk36;
    /* 0x38 */ f32 unk38; /* pitch */
    /* 0x3C */ f32 unk3C; /* roll */
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ char unk48[4];
    /* 0x4C */ u16 unk4C;
    /* 0x4E */ char unk4E[4];
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
    /* 0x70 */ u16 unk70;
    /* 0x72 */ char unk72[2];
    /* 0x74 */ omObjData *unk74;
    /* 0x78 */ omObjData *unk78;
    /* 0x7C */ char unk7C[0xC];
    /* 0x88 */ u16 unk88;
    /* 0x8A */ char unk8A[2];
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u16 unk90;
    /* 0x92 */ u16 unk92;
    /* 0x94 */ u16 unk94;
    /* 0x96 */ char unk96[0x18];
    /* 0xAE */ u16 unkAE;
    /* 0xB0 */ char unkB0[0x10];
} AhPlayer; /* size 0xC0 */

/* the scrolled sky texture's size (func_800335BC_main) */
typedef struct AhTexSize {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
} AhTexSize;

typedef struct AhUV {
    /* 0x00 */ f32 u;
    /* 0x04 */ f32 v;
} AhUV;

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

extern D_80111B50_vine_with_me_Struct D_8010DB40_aces_high;
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
void func_801085B0_aces_high(omObjData *obj);
void func_8010862C_aces_high(omObjData *obj);
void func_801088A4_aces_high(omObjData *obj);
void func_8010951C_aces_high(omObjData *obj);
void func_80109928_aces_high(omObjData *obj);
void func_80109EEC_aces_high(omObjData *obj);
void func_8010A0F0_aces_high(omObjData *obj);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80106EC0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801071D4_aces_high);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DD48_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80107654_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80107F98_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801081A8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010843C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801085B0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010862C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801088A4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010951C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80109928_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80109EEC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A0F0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A214_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A51C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A884_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A9D4_aces_high);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DDA8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AADC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010ACE0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AD4C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AE30_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B0E8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B224_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B26C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B4BC_aces_high);

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
