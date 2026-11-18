#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/hmflight.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// bt A: Bounce 'n' Trounce (4 players bounce on each other on a floor of tiles that drop away)

/* omObjData::data of a floor tile */
typedef struct BtTile {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ u16 unk02; /* state: 0 solid, 1 shaking, 2 falling, 3 gone */
    /* 0x04 */ f32 unk04; /* shake offset / fall speed */
    /* 0x08 */ u16 unk08; /* shake timer */
    /* 0x0A */ char unk0A[2];
} BtTile; /* size 0xC */

/* omObjData::data of a player */
typedef struct BtPlayer {
    /* 0x00 */ u16 unk00; /* player */
    /* 0x02 */ u16 unk02; /* state: 2/3 out */
    /* 0x04 */ u16 unk04; /* motion state */
    /* 0x06 */ u16 unk06; /* spin effect shown */
    /* 0x08 */ u16 unk08; /* airborne */
    /* 0x0A */ u16 unk0A; /* bounce combo */
    /* 0x0C */ u16 unk0C; /* jump buffered */
    /* 0x0E */ u16 unk0E[4]; /* contact with each player: 1 above, 2 side, 4 below */
    /* 0x16 */ u16 unk16; /* knocked back */
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ omObjData* unk1C; /* tile underfoot */
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28; /* shadow scale */
    /* 0x2C */ f32 unk2C; /* jump speed */
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34; /* walk velocity x */
    /* 0x38 */ f32 unk38; /* walk velocity z */
    /* 0x3C */ f32 unk3C; /* jump time */
    /* 0x40 */ f32 unk40; /* jump start height */
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ Vec unk4C;
    /* 0x58 */ Vec unk58; /* podium position */
    /* 0x64 */ f32 unk64; /* knockback x */
    /* 0x68 */ f32 unk68; /* knockback z */
    /* 0x6C */ f32 unk6C; /* knockback decay */
    /* 0x70 */ f32 unk70; /* radius */
    /* 0x74 */ f32 unk74;
    /* 0x78 */ omObjData* unk78;
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ char unk80[0x1C];
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ char unkA4[4];
    /* 0xA8 */ u16 unkA8; /* rumble timer */
    /* 0xAA */ char unkAA[2];
} BtPlayer; /* size 0xAC */

/* omObjData::data of a player's spin effect (func_8010A8F0_bounce_n_trounce) */
typedef struct BtSpin {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ f32 unk04; /* heading */
    /* 0x08 */ f32 unk08; /* speed */
} BtSpin; /* size 0xC */

/* An entry of D_800CD1DC_main (src/esprite.c's D_800CD1DC_main_Struct) */
typedef struct BtEsprite {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} BtEsprite; /* size 0x24 */

/* One scattered polygon of a vertex-scatter model (13F90.c's HmfFxPart). */
typedef struct BtFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir;
    /* 0x24 */ Vec vel;
} BtFxPart; /* size 0x30 */

/* HmfModel.unkBC for a vertex-scatter model (13F90.c's HmfFxWork). */
typedef struct BtFxWork {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ char unk28[0x30];
    /* 0x58 */ BtFxPart* parts;
} BtFxWork;

/* HmfData as the effect reads it (13F90.c's HmfFxData). */
typedef struct BtFxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count;
} BtFxData;

// main
void func_8000B638_main(s32 arg0);
void func_80045C2C_main(void);
void func_80047C0C_main(u16 group, u16 max_objs);
omObjData** func_80047DBC_main(s16 group);
void HmfLightStatSet(s16 arg0, u8 arg1, u8 arg2);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_8004BCE4_main(void* work);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
f64 fabs(f64);
void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);

extern BtEsprite* D_800CD1DC_main;
extern s32 D_800A178C_main[][6];
extern Vec Center;
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */
extern f32 D_800D2120_main;
extern Vec CRot;
extern f32 CZoom;

// minigame
void func_800E6F0C_minigame(s8 arg0);

// LOCAL
void func_80105C84_bounce_n_trounce(omObjData* obj);
void func_80105CBC_bounce_n_trounce(omObjData* obj);
void func_80105E4C_bounce_n_trounce(omObjData* obj);
void func_80106268_bounce_n_trounce(omObjData* obj);
f32 func_80106434_bounce_n_trounce(omObjData* obj);
void func_8010675C_bounce_n_trounce(omObjData* obj);
void func_80106764_bounce_n_trounce(omObjData* obj);
void func_80106854_bounce_n_trounce(omObjData* obj);
void func_801068F4_bounce_n_trounce(omObjData* obj);
void func_801069F0_bounce_n_trounce(omObjData* obj);
void func_801070CC_bounce_n_trounce(omObjData* obj);
void func_80107114_bounce_n_trounce(omObjData* obj, s8 stickX, s8 stickY, u16 btn);
void func_80107EDC_bounce_n_trounce(omObjData* obj);
void func_80108350_bounce_n_trounce(omObjData* obj);
void func_80108398_bounce_n_trounce(omObjData* obj, omObjData* other);
void func_80108454_bounce_n_trounce(omObjData* obj, f32 arg1);
void func_8010846C_bounce_n_trounce(omObjData* obj);
void func_801085EC_bounce_n_trounce(omObjData* obj);
void func_80108940_bounce_n_trounce(void);
void func_80108EFC_bounce_n_trounce(omObjData* obj, f32 x, f32 y, f32 z);
void func_80108F98_bounce_n_trounce(omObjData* obj);
void func_80108C18_bounce_n_trounce(omObjData* obj);
void func_80108CA8_bounce_n_trounce(omObjData* obj);
void func_80108D28_bounce_n_trounce(omObjData* obj);
void func_80109018_bounce_n_trounce(omObjData* obj, s8* stickX, s8* stickY, u16* btn);
void func_80109AF0_bounce_n_trounce(omObjData* obj);
void func_80109F68_bounce_n_trounce(omObjData* obj);
void func_8010A664_bounce_n_trounce(omObjData* obj);
void func_8010A740_bounce_n_trounce(s16 model);
void func_8010A8F0_bounce_n_trounce(omObjData* obj);
f32 func_8010AAE0_bounce_n_trounce(f32 x0, f32 z0, f32 x1, f32 z1);
void func_8010AB90_bounce_n_trounce(void);

extern D_80111B50_vine_with_me_Struct D_8010ABB0_bounce_n_trounce;
extern s8 D_8010ABD8_bounce_n_trounce[4];
extern s8 D_8010ABDC_bounce_n_trounce[4];
extern u16 D_8010ABE0_bounce_n_trounce[4];
extern u16 D_8010ABE8_bounce_n_trounce;
extern Vec D_8010ABEC_bounce_n_trounce[9]; /* tile positions */
extern Vec D_8010AC58_bounce_n_trounce[7];
extern s32 D_8010ACAC_bounce_n_trounce[7];
extern s32 D_8010ACC8_bounce_n_trounce[7];
extern s16 D_8010ACE4_bounce_n_trounce[9]; /* tile dropped */
extern u16 D_8010ACF6_bounce_n_trounce;    /* frames before tiles start dropping */
extern u16 D_8010ACF8_bounce_n_trounce; /* frames to the next drop */
extern Vec D_8010ACFC_bounce_n_trounce[4]; /* start positions */
extern s32 D_8010AD2C_bounce_n_trounce[8]; /* shadow model per character */
extern Vec D_8010AD4C_bounce_n_trounce[4]; /* podium positions */
extern u16 D_8010AD7C_bounce_n_trounce[4]; /* podium taken */

extern u16 D_8010AEBC_bounce_n_trounce;
extern omObjData* D_8010AEC0_bounce_n_trounce;
extern omObjData* D_8010AEC4_bounce_n_trounce;
extern s16 D_8010AEC8_bounce_n_trounce;
extern s16 D_8010AECA_bounce_n_trounce;
extern s16 D_8010AECC_bounce_n_trounce;
extern omObjData* D_8010AED0_bounce_n_trounce;
extern omObjData* D_8010AED4_bounce_n_trounce;
extern omObjData** D_8010AED8_bounce_n_trounce; /* tiles */
extern omObjData** D_8010AEDC_bounce_n_trounce; /* players */
extern omObjData** D_8010AEE0_bounce_n_trounce;
extern s16 D_8010AEE4_bounce_n_trounce[4]; /* start slot per player */

#ifdef NON_MATCHING
/* retail masks the random slot twice (andi 3, andi 0xFF); everything else matches */
void func_801059A0_bounce_n_trounce(void) {
    omObjData* obj;
    s32 i;
    s16* slot;

    omInitObjMan(0x28, 0);
    i = 0;
    func_8004A208_main();
    func_80045C2C_main();
    func_8000B5F0_main(1);
    func_8000B638_main(1);
    Center.x = 0.0f;
    Center.y = 30.0f;
    Center.z = 0.0f;
    CRot.x = -30.0f;
    CRot.y = 45.0f;
    CRot.z = 0.0f;
    CZoom = 2100.0f;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    HmfLightMaxSet(3);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, 3.0f, 89.0f, 80.0f);
    HmfLightStatSet(1, 1, 1);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(3, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105C84_bounce_n_trounce);
    D_8010AED0_bounce_n_trounce = omAddObj(10, 0, 0, -1, func_80105E4C_bounce_n_trounce);
    obj = omAddObj(50, 0, 0, -1, func_8010A664_bounce_n_trounce);
    D_8010AED4_bounce_n_trounce = obj;
    obj->work[0] = 0;
    func_80047C0C_main(0, 4);
    D_8010AEDC_bounce_n_trounce = func_80047DBC_main(0);
    do {
        omAddObj(30, 7, 6, 0, func_801069F0_bounce_n_trounce)->work[0] = i;
        i++;
    } while (i < 4);
    for (i = 0; i < 4; i++) {
        D_8010AEE4_bounce_n_trounce[i] = -1;
    }
    i = 0;
    while (i < 4) {
        slot = &D_8010AEE4_bounce_n_trounce[rand8() & 3];
        if (*slot == -1) {
            *slot = i;
            i++;
        }
    }
    func_800E5EA0_minigame(&D_8010ABB0_bounce_n_trounce);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801059A0_bounce_n_trounce);
#endif

void func_80105C84_bounce_n_trounce(omObjData* obj) {
    D_8010AEBC_bounce_n_trounce = 4;
    D_8010AEC4_bounce_n_trounce = NULL;
    D_8010AEC0_bounce_n_trounce = NULL;
    D_8010AECC_bounce_n_trounce = 1;
    obj->func = func_80105CBC_bounce_n_trounce;
}

void func_80105CBC_bounce_n_trounce(omObjData* obj) {
    if (D_8010ABE8_bounce_n_trounce == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010AEC0_bounce_n_trounce == NULL) {
                    D_8010AEC8_bounce_n_trounce = 0;
                    D_8010AEC0_bounce_n_trounce = omAddObj(4, 0, 0, -1, func_80109AF0_bounce_n_trounce);
                    D_8010AED4_bounce_n_trounce->work[0] = 1;
                }
                break;
            case 2:
                func_80108940_bounce_n_trounce();
                if (D_8010AEBC_bounce_n_trounce == 0) {
                    D_8010AECC_bounce_n_trounce = 0;
                    D_8010AED0_bounce_n_trounce->work[0] = 0;
                    func_800E6F0C_minigame(3);
                } else if (D_8010AEBC_bounce_n_trounce == 1) {
                    D_8010AECC_bounce_n_trounce = 0;
                    D_8010AED0_bounce_n_trounce->work[0] = 0;
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                D_8010AED0_bounce_n_trounce->work[0] = 0;
                func_80108940_bounce_n_trounce();
                if (D_8010AEC4_bounce_n_trounce == NULL) {
                    D_8010AECA_bounce_n_trounce = 0;
                    D_8010AEC4_bounce_n_trounce = omAddObj(4, 0, 0, -1, func_80109F68_bounce_n_trounce);
                }
                break;
            case 4:
                func_80108940_bounce_n_trounce();
                break;
            case 5:
                WipeCreateOut(0, 20);
                HuAudSeqFadeOut(30);
                func_8004AB0C_main(30);
                D_8010ABE8_bounce_n_trounce = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010AB90_bounce_n_trounce();
    }
}

void func_80105E4C_bounce_n_trounce(omObjData* obj) {
    Vec eye;
    Vec at;
    omObjData* tileObj;
    omObjData* obj2;
    BtTile* tile;
    s32 i;
    s16 sprId;

    func_80047C0C_main(2, 9);
    D_8010AED8_bounce_n_trounce = func_80047DBC_main(2);
    func_80047C0C_main(3, 7);
    D_8010AEE0_bounce_n_trounce = func_80047DBC_main(3);
    for (i = 0; i < 9; i++) {
        tileObj = omAddObj(20, 1, 0, 2, func_8010675C_bounce_n_trounce);
        tile = tileObj->data = HuMemAllocTag(sizeof(BtTile), 0x7918);
        tile->unk00 = i;
        if (i & 1) {
            if (i == 1) {
                tileObj->model[0] = func_8000B108_main(0x390001, 0x6B9);
            } else {
                tileObj->model[0] = Hu3DModelLink(D_8010AED8_bounce_n_trounce[1]->model[0]);
            }
        } else {
            if (i == 0) {
                tileObj->model[0] = func_8000B108_main(0x390000, 0x6B9);
            } else {
                tileObj->model[0] = Hu3DModelLink(D_8010AED8_bounce_n_trounce[0]->model[0]);
            }
        }
        omSetTra(tileObj, D_8010ABEC_bounce_n_trounce[i].x, D_8010ABEC_bounce_n_trounce[i].y, D_8010ABEC_bounce_n_trounce[i].z);
        tile->unk02 = 0;
    }
    for (i = 0; i < 7; i++) {
        obj2 = omAddObj(20, 1, 0, 3, func_801068F4_bounce_n_trounce);
        obj2->model[0] = func_8000B108_main(D_8010ACAC_bounce_n_trounce[i], 0x6B9);
        HuSqrtf(D_8010AC58_bounce_n_trounce[i].x * D_8010AC58_bounce_n_trounce[i].x
                + D_8010AC58_bounce_n_trounce[i].z * D_8010AC58_bounce_n_trounce[i].z);
        omSetTra(obj2,
                 cosdf(-45.0f) * D_8010AC58_bounce_n_trounce[i].x - sindf(-45.0f) * D_8010AC58_bounce_n_trounce[i].z,
                 D_8010AC58_bounce_n_trounce[i].y,
                 sindf(-45.0f) * D_8010AC58_bounce_n_trounce[i].x + cosdf(-45.0f) * D_8010AC58_bounce_n_trounce[i].z);
        omSetRot(obj2, 0.0f, 45.0f, 0.0f);
        omSetSca(obj2, 1.5f, 1.5f, 1.5f);
        obj2->work[0] = 0;
        obj2->work[1] = D_8010ACC8_bounce_n_trounce[i];
    }
    sprId = InitEspriteSlot(func_8000B838_main(0x390002), 0, 1);
    func_8000BB94_main(sprId);
    at.x = 0.0f;
    at.y = 120.0f;
    at.z = 0.0f;
    eye.x = sindf(45.0f) * 2800.0f;
    eye.y = 1400.0f;
    eye.z = cosdf(45.0f) * 2800.0f;
    func_8004B760_main(0x7FDA, D_800CD1DC_main[sprId].unk04, func_8004BCE4_main, 45.0f, &eye, &at);
    Hu3DCamSetPerspective(0, 45.0f, 500.0f, 4500.0f);
    CZoom = 2100.0f;
    obj->work[0] = 1;
    D_8010ACE4_bounce_n_trounce[4] = 1; /* the centre tile never drops */
    obj->func = func_80106268_bounce_n_trounce;
}

void func_80106268_bounce_n_trounce(omObjData* obj) {
    u16 free[9];
    s16 n;
    s32 i;
    s16 idx;
    BtTile* tile;

    if (func_800E6E8C_minigame() == 2 && obj->work[0] != 0) {
        if (D_8010ACF6_bounce_n_trounce != 0) {
            D_8010ACF6_bounce_n_trounce--;
            return;
        }
        if (D_8010ACF8_bounce_n_trounce != 0) {
            D_8010ACF8_bounce_n_trounce--;
            return;
        }
        D_8010ACF8_bounce_n_trounce = 60;
        n = 0;
        for (i = 0; i < 9; i++) {
            if (D_8010ACE4_bounce_n_trounce[i] == 0) {
                free[n++] = i;
            }
        }
        if (n != 0) {
            if (n == 1) {
                idx = free[0];
            } else {
                idx = free[rand8() % n];
            }
            D_8010ACE4_bounce_n_trounce[idx] = 1;
            tile = D_8010AED8_bounce_n_trounce[idx]->data;
            tile->unk02 = 1;
            tile->unk04 = -15.0f;
            tile->unk08 = 40;
            HuAudFXPlay(0x3D1);
            D_8010AED8_bounce_n_trounce[idx]->func = func_80106764_bounce_n_trounce;
        }
    }
}

/* The height of the highest tile the player stands on (or overlaps by its radius); sets BtPlayer::unk1C. */
f32 func_80106434_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player;
    omObjData* tileObj;
    f32 top;
    f32 radius;
    f32 x;
    f32 z;
    f32 x1;
    f32 z1;
    f32 dist;
    s32 i;
    s32 j;

    top = -100000.0f;
    player = obj->data;
    radius = player->unk70;
    player->unk1C = NULL;
    for (i = 0; i < 9; i++) {
        tileObj = D_8010AED8_bounce_n_trounce[i];
        if (((BtTile*)tileObj->data)->unk02 == 3) {
            continue;
        }
        x = tileObj->trans.x - 150.0f;
        z = tileObj->trans.z - 150.0f;
        x1 = tileObj->trans.x + 150.0f;
        z1 = tileObj->trans.z + 150.0f;
        if (x <= obj->trans.x && z <= obj->trans.z && obj->trans.x <= x1 && obj->trans.z <= z1
            && top < tileObj->trans.y) {
            top = tileObj->trans.y;
            player->unk1C = tileObj;
            continue;
        }
        for (j = 0; j < 2; j++) {
            x = tileObj->trans.x - 150.0f;
            z = (tileObj->trans.z - 150.0f) + (j * 150.0f + j * 150.0f);
            x1 = tileObj->trans.x + 150.0f;
            if (x <= obj->trans.x && obj->trans.x <= x1) {
                dist = HuSqrtf((obj->trans.z - z) * (obj->trans.z - z));
            } else if (obj->trans.x < x) {
                dist = func_8010AAE0_bounce_n_trounce(obj->trans.x, obj->trans.z, x, z);
            } else if (x1 < obj->trans.x) {
                dist = func_8010AAE0_bounce_n_trounce(obj->trans.x, obj->trans.z, x1, z);
            }
            if (dist <= radius && top < tileObj->trans.y) {
                top = tileObj->trans.y;
                player->unk1C = tileObj;
            }
        }
        for (j = 0; j < 2; j++) {
            x = (tileObj->trans.x - 150.0f) + (j * 150.0f + j * 150.0f);
            z = tileObj->trans.z - 150.0f;
            z1 = tileObj->trans.z + 150.0f;
            if (z <= obj->trans.z && obj->trans.z <= z1) {
                dist = HuSqrtf((obj->trans.x - x) * (obj->trans.x - x));
            } else if (obj->trans.z < z) {
                dist = func_8010AAE0_bounce_n_trounce(obj->trans.x, obj->trans.z, x, z);
            } else if (z1 < obj->trans.z) {
                /* retail measures to the x1 / z corner here, not to (x, z1) */
                dist = func_8010AAE0_bounce_n_trounce(obj->trans.x, obj->trans.z, x1, z);
            }
            if (dist <= radius && top < tileObj->trans.y) {
                top = tileObj->trans.y;
                player->unk1C = tileObj;
            }
        }
    }
    return top;
}


void func_8010675C_bounce_n_trounce(omObjData* obj) {
}

void func_80106764_bounce_n_trounce(omObjData* obj) {
    BtTile* tile;

    tile = obj->data;
    if (D_8010AED0_bounce_n_trounce->work[0] == 0) {
        omSetTra(obj, obj->trans.x, 0.0f, obj->trans.z);
        obj->func = NULL;
        return;
    }
    if (tile->unk04 == 0.0f) {
        omSetTra(obj, obj->trans.x, 0.0f, obj->trans.z);
        tile->unk04 = -15.0f;
    } else {
        omSetTra(obj, obj->trans.x, tile->unk04, obj->trans.z);
        tile->unk04 = 0.0f;
    }
    if (--tile->unk08 == 0) {
        tile->unk04 = -4.4f;
        tile->unk02 = 2;
        obj->func = func_80106854_bounce_n_trounce;
    }
}

void func_80106854_bounce_n_trounce(omObjData* obj) {
    BtTile* tile;

    tile = obj->data;
    obj->trans.y += tile->unk04;
    tile->unk04 *= 1.22f;
    if (obj->trans.y < -1500.0f) {
        obj->trans.y = -1500.0f;
        func_8001C258_main(obj->model[0], 4, 4);
        tile->unk02 = 3;
        obj->func = NULL;
    }
}

void func_801068F4_bounce_n_trounce(omObjData* obj) {
    f32 angle;

    angle = obj->work[0] / 10.0f;
    obj->work[0] += obj->work[1];
    if (obj->work[0] >= 3600) {
        obj->work[0] -= 3600;
    }
    omSetSca(obj, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f);
}

void func_801069F0_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player;
    omObjData* shadowObj;
    BtFxData* hmf;
    BtFxWork* fx;
    BtFxPart* part;
    s32 i;
    u16 p;
    s8 chr;
    s32 mdl0;
    s32 mdl1;
    f32 rotY;

    player = obj->data = HuMemAllocTag(sizeof(BtPlayer), 0x7918);
    p = player->unk00 = obj->work[0];
    player->unk02 = 0;
    player->unk04 = 2;
    player->unk20 = 4.0f;
    player->unk24 = 1.0f;
    player->unk28 = 1.5f;
    player->unk30 = player->unk34 = player->unk38 = 0.0f;
    player->unk08 = 0;
    player->unk0A = 0;
    player->unk0C = 0;
    player->unk18 = 0;
    player->unk44 = 0.0f;
    player->unk48 = 0.0f;
    player->unk06 = 0;
    player->unk16 = 0;
    player->unk70 = 40.0f;
    player->unk74 = 55.0f;
    player->unk1C = NULL;
    player->unk7C = 0;
    player->unk7E = 0;
    player->unkA0 = 0;
    player->unk9C = 0;
    player->unkA2 = 0;
    player->unk64 = player->unk68 = player->unk6C = 0.0f;
    for (i = 0; i < 4; i++) {
        player->unk0E[i] = 0;
    }
    chr = GwPlayer[p].chr;
    mdl0 = D_800A178C_main[chr][0];
    mdl1 = D_800A178C_main[chr][1];
    obj->model[0] = func_8000B108_main(D_8010AD2C_bounce_n_trounce[chr], 0x6D9);
    omSetTra(obj, D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[p]].x,
             D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[p]].y,
             D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[p]].z);
    obj->model[1] = func_8000B108_main(mdl0 | mdl1, 0x206B9);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[2] = func_8000B0D4_main(0, 0xA89);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y + 1.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], player->unk28, 1.0f, player->unk28);
    obj->model[3] = func_8000B108_main(0x39000B, 0x68D);
    obj->model[4] = func_8000B108_main(0x39000C, 0x68D);
    obj->model[6] = func_8000B108_main(0x82, 0xA8D);
    Hu3DModelScaleSet(obj->model[3], 1.2f, 1.0f, 1.2f);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x73));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x1F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x36));
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 3, 1);
    func_8001C814_main(obj->model[0], 3, 1);
    rotY = atan2df(-obj->trans.x, -obj->trans.z);
    omSetRot(obj, 0.0f, rotY, 0.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
    obj->model[5] = func_8000B108_main(0x39000F, 0x6A9);
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C2FC_main(obj->model[5], 0x20000, 0x20000);
    func_8001C448_main(obj->model[5]);
    func_8001C954_main(obj->model[5]);
    func_8001C514_main(obj->model[5]);
    func_80013390_main(obj->model[5], -1, NULL, func_8010A740_bounce_n_trounce);
    hmf = (BtFxData*)HmfModelData[obj->model[5]].hmf;
    fx = (BtFxWork*)HmfModelData[obj->model[5]].unkBC;
    part = fx->parts;
    fx->unk1C = 0;
    fx->unk20 = 0;
    fx->unk24 = 0;
    func_800138EC_main(obj->model[5], 1, 1);
    for (i = 0; i < hmf->count; i++, part++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->dir.x = part->dir.y = part->dir.z = 0.0f;
        part->speed = part->scale = 0.0f;
    }
    shadowObj = omAddObj(60, 0, 0, -1, func_8010A8F0_bounce_n_trounce);
    player->unk78 = shadowObj;
    shadowObj->data = HuMemAllocTag(0xC, 0x7918);
    shadowObj->work[0] = 0;
    shadowObj->work[1] = (u32)obj;
    player->unkA8 = 0;
    player->unk4C.x = obj->trans.x;
    player->unk4C.y = obj->trans.y;
    player->unk4C.z = obj->trans.z;
    obj->func = func_801070CC_bounce_n_trounce;
}

void func_80106F78_bounce_n_trounce(omObjData* obj) {
    s8 stickX;
    s8 stickY;
    u16 btn;
    BtPlayer* player;
    u16 pad;

    player = obj->data;
    pad = GwPlayer[player->unk00].pad;
    if (player->unk02 == 3) {
        return;
    }
    if (GwPlayer[player->unk00].stat & 1) {
        func_80109018_bounce_n_trounce(obj, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        btn = D_800D5558_main[pad];
    }
    if (func_800E6E8C_minigame() == 0 || func_800E6E8C_minigame() == 1 || func_800E6E8C_minigame() == 3) {
        stickY = 0;
        stickX = 0;
        btn = 0;
    }
    if (player->unk02 == 2 || player->unk02 == 3) {
        stickY = 0;
        stickX = 0;
        btn = 0;
        func_80107EDC_bounce_n_trounce(obj);
        return;
    }
    func_80107114_bounce_n_trounce(obj, stickX, stickY, btn);
}

void func_801070CC_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player = obj->data;

    func_80107114_bounce_n_trounce(obj, D_8010ABD8_bounce_n_trounce[player->unk00],
                                   D_8010ABDC_bounce_n_trounce[player->unk00], D_8010ABE0_bounce_n_trounce[player->unk00]);
}

/* A player's frame: walking, jumping, the spin attack, bounces off the others, landing and falling off. */
void func_80107114_bounce_n_trounce(omObjData* obj, s8 stickX, s8 stickY, u16 btn) {
    BtPlayer* player;
    BtPlayer* od;
    BtSpin* spin;
    omObjData* tile;
    omObjData* other;
    f32 angle;
    f32 mag;
    f32 rotY;
    f32 top;
    f32 jump;
    f32 mine;
    f32 theirs;
    s16 se;
    s32 i;

    player = obj->data;
    angle = atan2df(stickX, -stickY) + CRot.y;
    mag = HuSqrtf(stickX * stickX + stickY * stickY) * 0.1f;
    rotY = obj->rot.y;
    top = func_80106434_bounce_n_trounce(obj);
    tile = player->unk1C;
    if (tile != NULL) {
        if (((BtTile*)tile->data)->unk02 == 1) {
            if (player->unkA8 == 0) {
                omVibrate(player->unk00, 2, 3, 10);
                player->unkA8 = 10;
            } else {
                player->unkA8--;
            }
        } else if (player->unkA8 >= 6) {
            player->unkA8--;
        } else {
            player->unkA8 = 0;
        }
    } else if (player->unkA8 >= 6) {
        player->unkA8--;
    } else {
        player->unkA8 = 0;
    }
    switch (player->unk04) {
        case 4:
            if (player->unk0C == 1) {
                se = func_8004ACE0_main(0x3BE, player->unk00);
                if (func_800E6E8C_minigame() != 2) {
                    func_8004AAD0_main(se, 0x75);
                }
                player->unk0A++;
                if (player->unk0A >= 4) {
                    player->unk0A = 1;
                }
                jump = (player->unk0A - 1) * 50.0f * 0.24f + 70.0f;
                player->unk0C = 0;
            } else {
                player->unk0A = 0;
                jump = 37.5f;
                se = func_8004ACE0_main(0x3B5, player->unk00);
                if (func_800E6E8C_minigame() != 2) {
                    func_8004AAD0_main(se, 0x75);
                }
            }
            func_80108454_bounce_n_trounce(obj, jump);
            player->unk08 = 1;
            player->unk04 = 3;
        case 2:
            player->unk34 = sindf(angle) * mag;
            player->unk38 = cosdf(angle) * mag;
            if (stickX != 0 || stickY != 0) {
                rotY = angle;
            }
            if (btn & 0x8000) {
                player->unk0C = 1;
            }
            break;
    }
    if (player->unk08 == 1) {
        if (player->unk44 == 0.0f && (btn & 0x2000) && player->unk0A != 0 && player->unk02 == 0) {
            se = func_8004ACE0_main(0x3C7, player->unk00);
            if (func_800E6E8C_minigame() != 2) {
                func_8004AAD0_main(se, 0x75);
            }
            player->unk02 = 1;
            player->unk44 = (obj->trans.y / 1500.0f) * 140.0f + 20.0f;
            if (player->unk44 > 160.0f) {
                player->unk44 = 160.0f;
            }
            player->unk2C = 0.0f;
            player->unk3C = 0.0f;
            player->unk40 = obj->trans.y;
            player->unk74 = 85.0f;
            func_8001C258_main(obj->model[3], 4, 0);
            func_8001C814_main(obj->model[3], 3, 2);
            func_8001C6A8_main(obj->model[3], 0.0f);
            player->unk06 = 1;
            spin = player->unk78->data;
            spin->unk00 = 3;
            spin->unk04 = obj->rot.y + 180.0f;
            if (spin->unk04 >= 360.0f) {
                spin->unk04 -= 360.0f;
            }
            spin->unk08 = player->unk44 / 0.6666667f;
            if (spin->unk08 < 15.0f) {
                spin->unk08 = 15.0f;
            }
            if (spin->unk08 > 100.0f) {
                spin->unk08 = 100.0f;
            }
            player->unk78->work[2] = 0;
            player->unk78->work[0] = 1;
        }
        if (player->unk44 != 0.0f) {
            rotY += player->unk44;
        }
        player->unk3C += 1.0f;
        obj->trans.y = player->unk2C * player->unk3C + player->unk40 - player->unk3C * 2.4f * player->unk3C;
        if (player->unk16 == 0) {
            player->unk34 = sindf(angle) * mag;
            player->unk38 = cosdf(angle) * mag;
            if ((stickX != 0 || stickY != 0) && player->unk44 == 0.0f) {
                rotY = angle;
            }
        } else {
            obj->trans.x += player->unk64;
            obj->trans.z += player->unk68;
        }
        obj->trans.x += player->unk34;
        obj->trans.z += player->unk38;
        func_801085EC_bounce_n_trounce(obj);
        for (i = 0; i < 4; i++) {
            if (i == player->unk00) {
                continue;
            }
            other = D_8010AEDC_bounce_n_trounce[i];
            od = other->data;
            if (player->unk02 != 1) {
                if (player->unk0E[i] & 1) {
                    if (od->unk02 == 1) {
                        player->unk16 = 1;
                        atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                        func_80108398_bounce_n_trounce(other, obj);
                        func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y + 120.0f, obj->trans.z);
                    } else {
                        player->unk2C = 0.0f;
                        player->unk3C = 0.0f;
                        player->unk40 = obj->trans.y;
                    }
                } else if (player->unk0E[i] & 2) {
                    if (od->unk02 == 1) {
                        player->unk16 = 1;
                        atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                        func_80108398_bounce_n_trounce(other, obj);
                        func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y + 70.0f, obj->trans.z);
                    } else {
                        player->unk38 = -player->unk38;
                        player->unk34 = -player->unk34;
                        player->unk16 = 1;
                    }
                } else if (player->unk0E[i] & 4) {
                    if (od->unk02 == 1) {
                        player->unk16 = 1;
                        atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                        func_80108398_bounce_n_trounce(other, obj);
                        func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y, obj->trans.z);
                    } else {
                        player->unk2C = 50.0f;
                        player->unk3C = 0.0f;
                        player->unk40 = obj->trans.y;
                    }
                }
            } else {
                player->unkA2 = 1;
                if (player->unk0E[i] & 1) {
                    func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y + 120.0f, obj->trans.z);
                    omVibrate(player->unk00, 2, 2, 20);
                    if (od->unk02 == 1) {
                        if ((theirs = od->unk44) == (mine = player->unk44)) {
                            func_80108350_bounce_n_trounce(obj);
                            func_80108350_bounce_n_trounce(other);
                        } else if (mine < theirs) {
                            player->unk16 = 1;
                            atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                            func_80108398_bounce_n_trounce(other, obj);
                            func_80108350_bounce_n_trounce(obj);
                        } else {
                            od->unk16 = 1;
                            atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                            func_80108398_bounce_n_trounce(obj, other);
                            func_80108350_bounce_n_trounce(other);
                        }
                    } else {
                        od->unk16 = 1;
                        atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                        func_80108398_bounce_n_trounce(obj, other);
                    }
                } else if (player->unk0E[i] & 2) {
                    func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y + 70.0f, obj->trans.z);
                    omVibrate(player->unk00, 2, 2, 20);
                    if (od->unk02 == 1) {
                        if ((theirs = od->unk44) == (mine = player->unk44)) {
                            func_80108350_bounce_n_trounce(obj);
                            func_80108350_bounce_n_trounce(other);
                        } else if (mine < theirs) {
                            player->unk16 = 1;
                            atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                            func_80108398_bounce_n_trounce(other, obj);
                            func_80108350_bounce_n_trounce(obj);
                        } else {
                            od->unk16 = 1;
                            atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                            func_80108398_bounce_n_trounce(obj, other);
                            func_80108350_bounce_n_trounce(other);
                        }
                    } else {
                        od->unk16 = 1;
                        atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                        func_80108398_bounce_n_trounce(obj, other);
                    }
                } else if (player->unk0E[i] & 4) {
                    func_80108EFC_bounce_n_trounce(obj, obj->trans.x, obj->trans.y, obj->trans.z);
                    omVibrate(player->unk00, 2, 2, 20);
                    if (od->unk02 == 1) {
                        if ((theirs = od->unk44) == (mine = player->unk44)) {
                            func_80108350_bounce_n_trounce(obj);
                            func_80108350_bounce_n_trounce(other);
                        } else if (mine < theirs) {
                            player->unk16 = 1;
                            atan2df(obj->trans.x - other->trans.x, -(obj->trans.z - other->trans.z));
                            func_80108398_bounce_n_trounce(other, obj);
                            func_80108350_bounce_n_trounce(obj);
                        } else {
                            od->unk16 = 1;
                            atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                            func_80108398_bounce_n_trounce(obj, other);
                            func_80108350_bounce_n_trounce(other);
                        }
                    } else {
                        od->unk16 = 1;
                        atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                        func_80108398_bounce_n_trounce(obj, other);
                    }
                }
            }
        }
        if (obj->trans.y < top) {
            obj->trans.y = top;
            player->unk20 = 4.0f;
            player->unk24 = 1.0f;
            player->unk04 = 2;
            player->unk34 = player->unk38 = 0.0f;
            player->unk0C = 0;
            func_80108350_bounce_n_trounce(obj);
            player->unk78->work[0] = 0;
            player->unk06 = 0;
            player->unk08 = 0;
            player->unk64 = player->unk68 = 0.0f;
            player->unk74 = 55.0f;
            func_80108F98_bounce_n_trounce(obj);
        }
    }
    player->unk64 *= player->unk6C;
    player->unk68 *= player->unk6C;
    if (fabs(player->unk64) < 0.01f) {
        player->unk64 = 0.0f;
    }
    if (fabs(player->unk68) < 0.01f) {
        player->unk68 = 0.0f;
    }
    if (player->unk64 == 0.0f && player->unk68 == 0.0f) {
        player->unk16 = 0;
    } else {
        obj->trans.x += player->unk64;
        obj->trans.z += player->unk68;
    }
    omSetRot(obj, obj->rot.x, rotY, obj->rot.z);
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    if (top == -100000.0f) {
        func_8001C258_main(obj->model[2], 4, 4);
    } else {
        player->unk28 = 1.5f - fabs(obj->trans.y - top) / 900.0f * 1.2f;
        if (player->unk28 < 0.3f) {
            player->unk28 = 0.3f;
        }
        func_8001C258_main(obj->model[2], 4, 0);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, top + 1.0f, obj->trans.z);
        Hu3DModelScaleSet(obj->model[2], player->unk28, 1.0f, player->unk28);
    }
    if (player->unk06 == 1) {
        Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y + 60.0f, obj->trans.z);
    }
    func_8010846C_bounce_n_trounce(obj);
    if (obj->trans.y < -45.0f && player->unk08 == 1 && player->unk02 != 2) {
        func_8004AC98_main(0x3D0, player->unk00);
        player->unk02 = 2;
        player->unk64 = player->unk68 = 0.0f;
        player->unk34 = player->unk38 = 0.0f;
        D_8010AEBC_bounce_n_trounce--;
    }
    player->unk4C.x = obj->trans.x;
    player->unk4C.y = obj->trans.y;
    player->unk4C.z = obj->trans.z;
}

/* A player out of play: finishes the fall, then hides; screams once on leaving the screen. */
void func_80107EDC_bounce_n_trounce(omObjData* obj) {
    Vec pos;
    Vec2f screen;
    BtPlayer* player;
    f32 rotY;
    f32 top;

    player = obj->data;
    rotY = obj->rot.y;
    top = func_80106434_bounce_n_trounce(obj);
    if (player->unk08 == 1) {
        if (player->unk44 != 0.0f) {
            rotY += player->unk44;
        }
        player->unk3C += 1.0f;
        obj->trans.y = player->unk2C * player->unk3C + player->unk40 - player->unk3C * 2.4f * player->unk3C;
        if (player->unk16 == 1) {
            obj->trans.x += player->unk64;
            obj->trans.z += player->unk68;
        }
        obj->trans.x += player->unk34;
        obj->trans.z += player->unk38;
    }
    player->unk64 *= player->unk6C;
    player->unk68 *= player->unk6C;
    if (fabs(player->unk64) < 0.01f) {
        player->unk64 = 0.0f;
    }
    if (fabs(player->unk68) < 0.01f) {
        player->unk68 = 0.0f;
    }
    if (player->unk64 == 0.0f && player->unk68 == 0.0f) {
        player->unk16 = 0;
    } else {
        obj->trans.x += player->unk64;
        obj->trans.z += player->unk68;
    }
    omSetRot(obj, obj->rot.x, rotY, obj->rot.z);
    if (obj->rot.y >= 360.0f) {
        obj->rot.y -= 360.0f;
    }
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    if (top == -100000.0f) {
        func_8001C258_main(obj->model[2], 4, 4);
    } else {
        player->unk28 = 1.5f - fabs(obj->trans.y - top) / 900.0f * 1.2f;
        if (player->unk28 < 0.3f) {
            player->unk28 = 0.3f;
        }
        func_8001C258_main(obj->model[2], 4, 0);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, top + 1.0f, obj->trans.z);
        Hu3DModelScaleSet(obj->model[2], player->unk28, 1.0f, player->unk28);
    }
    if (player->unk06 == 1) {
        Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y + 60.0f, obj->trans.z);
    }
    func_8010846C_bounce_n_trounce(obj);
    if (obj->trans.y < -5000.0f) {
        player->unk02 = 3;
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        player->unk06 = 0;
        func_8001C258_main(obj->model[3], 4, 4);
        obj->func = NULL;
    }
    pos.x = obj->trans.x;
    pos.y = obj->trans.y;
    pos.z = obj->trans.z;
    func_80012B14_main(0, &pos, &screen);
    if (screen.y > 240.0f && player->unk18 == 0) {
        player->unk18 = 1;
        func_8004ACE0_main(0x286, player->unk00);
    }
    player->unk4C.x = obj->trans.x;
    player->unk4C.y = obj->trans.y;
    player->unk4C.z = obj->trans.z;
}

void func_80108350_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player = obj->data;

    if (player->unk02 != 2 && player->unk02 != 3) {
        player->unk02 = 0;
    }
    player->unk44 = 0;
    player->unk48 = 0;
    func_8001C258_main(obj->model[3], 4, 4);
}

/* obj bounces off other: knock other away from obj */
void func_80108398_bounce_n_trounce(omObjData* obj, omObjData* other) {
    BtPlayer* me;
    BtPlayer* player;
    f32 speed;
    f32 angle;

    me = obj->data;
    player = other->data;
    speed = (me->unk44 / 160.0f) * 22.0f + 20.0f;
    angle = atan2df(other->trans.x - obj->trans.x, other->trans.z - obj->trans.z);
    player->unk64 = sindf(angle) * speed;
    player->unk68 = cosdf(angle) * speed;
    player->unk6C = 0.8f;
}

void func_80108454_bounce_n_trounce(omObjData* obj, f32 arg1) {
    BtPlayer* player = obj->data;

    player->unk2C = arg1;
    player->unk3C = 0;
    player->unk40 = obj->trans.y;
}

void func_8010846C_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player;
    f32 frame;
    f32 dir;
    f32 rate;

    player = obj->data;
    dir = player->unk24;
    rate = D_800D2120_main;
    frame = HmfModelData[obj->model[0]].unk40;
    if (player->unk04 == 2) {
        frame += dir * player->unk20 * rate;
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 < frame) {
            player->unk24 = -1.0f;
            frame = D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02;
            player->unk04 = 4;
        }
    } else if (player->unk04 == 3) {
        frame += player->unk24 * player->unk20 * D_800D2120_main;
        if (frame < 0.0f) {
            frame = 0.0f;
            player->unk04 = 1;
        }
    }
    func_8001C6A8_main(obj->model[0], frame);
    func_8001C6A8_main(obj->model[1], frame);
}

/* Sets BtPlayer::unk0E for every pair of players that touch and pushes this one out of the other. */
void func_801085EC_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player;
    BtPlayer* od;
    omObjData* other;
    f32 dist;
    f32 reach;
    f32 angle;
    s32 i;

    player = obj->data;
    for (i = 0; i < 4; i++) {
        other = D_8010AEDC_bounce_n_trounce[i];
        if (obj == other) {
            continue;
        }
        od = other->data;
        dist = func_8010AAE0_bounce_n_trounce(other->trans.x, other->trans.z, obj->trans.x, obj->trans.z);
        reach = HuSqrtf((player->unk74 + od->unk74) * (player->unk74 + od->unk74));
        if (dist < reach) {
            if (!(other->trans.y + 180.0f < obj->trans.y) && !(obj->trans.y + 180.0f < other->trans.y)) {
                if (other->trans.x == obj->trans.x && other->trans.z == obj->trans.z) {
                    rand8();
                    rand8();
                }
                angle = -atan2df(other->trans.x - obj->trans.x, -(other->trans.z - obj->trans.z));
                if (obj->trans.y < other->trans.y + 180.0f && other->trans.y + 180.0f - 40.0f < obj->trans.y) {
                    player->unk0E[od->unk00] |= 4;
                    od->unk0E[player->unk00] |= 1;
                    reach -= dist;
                    obj->trans.x = sindf(angle) * reach + obj->trans.x;
                    obj->trans.z = cosdf(angle) * reach + obj->trans.z;
                    obj->trans.y = other->trans.y + 180.0f + 1.0f;
                } else if (other->trans.y < obj->trans.y + 180.0f && obj->trans.y + 180.0f < other->trans.y + 40.0f) {
                    player->unk0E[od->unk00] |= 1;
                    od->unk0E[player->unk00] |= 4;
                    reach -= dist;
                    obj->trans.x = sindf(angle) * reach + obj->trans.x;
                    obj->trans.z = cosdf(angle) * reach + obj->trans.z;
                    obj->trans.y = other->trans.y - 180.0f - 1.0f;
                } else {
                    player->unk0E[od->unk00] |= 2;
                    od->unk0E[player->unk00] |= 2;
                    reach -= dist;
                    obj->trans.x = sindf(angle) * reach + obj->trans.x;
                    obj->trans.z = cosdf(angle) * reach + obj->trans.z;
                }
            }
        }
    }
}

void func_80108940_bounce_n_trounce(void) {
    BtPlayer* player;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        player = D_8010AEDC_bounce_n_trounce[i]->data;
        for (j = 0; j < 4; j++) {
            player->unk0E[j] = 0;
        }
    }
}

/* At the end: sends every standing player to the free podium nearest to it; TRUE once all are there or out. */
s32 func_80108994_bounce_n_trounce(void) {
    f32 dist[4];
    u16 idx[4];
    omObjData* obj;
    BtPlayer* player;
    f32 tf;
    u16 ti;
    s32 done;
    s32 i;
    s32 j;
    s32 k;

    done = 0;
    for (i = 0; i < 4; i++) {
        obj = D_8010AEDC_bounce_n_trounce[i];
        player = obj->data;
        done += player->unk02 == 3;
        if (player->unk04 == 2 || player->unk04 == 4) {
            if (player->unk02 != 4) {
                obj->func = func_80108C18_bounce_n_trounce;
                for (j = 0; j < 4; j++) {
                    dist[j] = func_8010AAE0_bounce_n_trounce(D_8010AD4C_bounce_n_trounce[j].x, D_8010AD4C_bounce_n_trounce[j].z,
                                                             D_8010AEDC_bounce_n_trounce[i]->trans.x,
                                                             D_8010AEDC_bounce_n_trounce[i]->trans.z);
                    idx[j] = j;
                }
                for (j = 0; j < 3; j++) {
                    for (k = j + 1; k < 4; k++) {
                        if (dist[idx[j]] > dist[idx[k]]) {
                            ti = idx[j];
                            tf = dist[idx[j]];
                            dist[idx[j]] = dist[idx[k]];
                            idx[j] = idx[k];
                            dist[idx[k]] = tf;
                            idx[k] = ti;
                        }
                    }
                }
                for (j = 0; j < 4; j++) {
                    if (D_8010AD7C_bounce_n_trounce[idx[j]] != 1) {
                        player->unk58 = D_8010AD4C_bounce_n_trounce[idx[j]];
                        D_8010AD7C_bounce_n_trounce[idx[j]] = 1;
                        break;
                    }
                }
            } else {
                done += D_8010AEDC_bounce_n_trounce[i]->work[0] == 0;
            }
        }
    }
    return done == 4;
}

void func_80108C18_bounce_n_trounce(omObjData* obj) {
    ((BtPlayer*)obj->data)->unk02 = 4;
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 6, 0);
    obj->work[0] = 8;
    obj->func = func_80108CA8_bounce_n_trounce;
}

void func_80108CA8_bounce_n_trounce(omObjData* obj) {
    if (obj->work[0] != 0) {
        obj->work[0]--;
        return;
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 6, 2);
    obj->func = func_80108D28_bounce_n_trounce;
}

/* Walks to the podium, pushing away the players it touches. */
void func_80108D28_bounce_n_trounce(omObjData* obj) {
    BtPlayer* player;
    BtPlayer* od;
    f32 angle;
    f32 step;
    f32 dist;
    s32 i;

    player = obj->data;
    for (i = 0; i < 4; i++) {
        od = D_8010AEDC_bounce_n_trounce[i]->data;
        if (od->unk02 != 4 && ((player->unk0E[i] & 1) || (player->unk0E[i] & 2))) {
            angle = atan2df(-D_8010AEDC_bounce_n_trounce[i]->trans.x, -D_8010AEDC_bounce_n_trounce[i]->trans.z);
            od->unk64 = sindf(angle) * 6.0f;
            od->unk68 = cosdf(angle) * 6.0f;
            od->unk6C = 0.9f;
            dist = func_8010AAE0_bounce_n_trounce(player->unk58.x, player->unk58.z, obj->trans.x, obj->trans.z);
            step = (dist < 50.0f) ? dist : 50.0f;
            angle = atan2df(player->unk58.x - obj->trans.x, player->unk58.z - obj->trans.z);
            obj->trans.x = sindf(angle) * step + obj->trans.x;
            obj->trans.z = cosdf(angle) * step + obj->trans.z;
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelPosSet(obj->model[2], obj->trans.x, 1.0f, obj->trans.z);
        }
    }
}

/* The bounce star above the player (x, y, z unused) */
void func_80108EFC_bounce_n_trounce(omObjData* obj, f32 x, f32 y, f32 z) {
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y + 200.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[4], 0.0f, CRot.y, 0.0f);
    func_8001C814_main(obj->model[4], 3, 0);
    func_8001C6A8_main(obj->model[4], 0.0f);
}

/* The landing dust */
void func_80108F98_bounce_n_trounce(omObjData* obj) {
    func_8001C258_main(obj->model[6], 4, 0);
    Hu3DModelPosSet(obj->model[6], obj->trans.x, obj->trans.y + 5.0f, obj->trans.z);
    func_8001C814_main(obj->model[6], 3, 0);
    func_8001C6A8_main(obj->model[6], 0.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109018_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109478_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109804_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109A00_bounce_n_trounce);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", D_8010AE14_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109AF0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109F68_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A664_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A740_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A8F0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010AAE0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010AB1C_bounce_n_trounce);
