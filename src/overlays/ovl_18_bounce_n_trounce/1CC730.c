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
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E[4];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ omObjData* unk1C; /* tile underfoot */
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28; /* shadow scale */
    /* 0x2C */ char unk2C[4];
    /* 0x30 */ Vec unk30;
    /* 0x3C */ char unk3C[8];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ Vec unk4C;
    /* 0x58 */ char unk58[0xC];
    /* 0x64 */ Vec unk64;
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
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ char unkAA[2];
} BtPlayer; /* size 0xAC */

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
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);

extern BtEsprite* D_800CD1DC_main;
extern s32 D_800A178C_main[][6];
extern Vec Center;
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
void func_80108940_bounce_n_trounce(void);
void func_80109AF0_bounce_n_trounce(omObjData* obj);
void func_80109F68_bounce_n_trounce(omObjData* obj);
void func_8010A664_bounce_n_trounce(omObjData* obj);
void func_8010A740_bounce_n_trounce(s16 model);
void func_8010A8F0_bounce_n_trounce(omObjData* obj);
f32 func_8010AAE0_bounce_n_trounce(f32 x0, f32 z0, f32 x1, f32 z1);
void func_8010AB90_bounce_n_trounce(void);

extern D_80111B50_vine_with_me_Struct D_8010ABB0_bounce_n_trounce;
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
    player->unk30.x = player->unk30.y = player->unk30.z = 0.0f;
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
    player->unk64.x = player->unk64.y = player->unk64.z = 0.0f;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106F78_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801070CC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107114_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107EDC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108350_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108398_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108454_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010846C_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801085EC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108940_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108994_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108C18_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108CA8_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108D28_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108EFC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108F98_bounce_n_trounce);

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
