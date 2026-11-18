#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// water whirled A: Water Whirled (players ride the water whirl; the sea engine is Dizzy Dinghies')

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct WwCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* 4: nobody won */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winners */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ Vec unk28;
} WwCtrl; /* size 0x34 */

/* omObjData::data of the sea (the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct WwGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} WwGround; /* size 0xB4 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_800142A0_main(s32);
void Hu3DAnimInit(s32);
s32 func_800202FC_main(Vec* v);

extern f32 D_800D5210_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);

extern f32 D_800EB73C_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105EA0_water_whirled(omObjData* obj);
f32 func_801061E4_water_whirled(f32 x, f32 z);
void func_801071BC_water_whirled(omObjData* obj);
void func_8010750C_water_whirled(omObjData* obj, s32 player);
void func_80107880_water_whirled(omObjData* obj);
void func_8010789C_water_whirled(omObjData* obj);
void func_801078B8_water_whirled(omObjData* obj);
void func_801078D4_water_whirled(omObjData* obj);
void func_8010860C_water_whirled(Vec* a, Vec* b, Vec* c, Vec* n);
void func_80108DF8_water_whirled(omObjData* obj);

extern f32 D_8010A190_water_whirled[4];
extern f32 D_8010A250_water_whirled; /* wave 1 phase */
extern f32 D_8010A254_water_whirled; /* wave 1 period */
extern f32 D_8010A258_water_whirled; /* wave 1 wavelength */
extern f32 D_8010A25C_water_whirled; /* wave 1 amplitude */
extern f32 D_8010A260_water_whirled; /* wave 2 phase */
extern f32 D_8010A264_water_whirled;
extern f32 D_8010A268_water_whirled;
extern f32 D_8010A26C_water_whirled;
extern s32 D_8010A280_water_whirled; /* player the camera closes in on, -1 none */
extern s32 D_8010A284_water_whirled; /* looping sound handle */
extern s32 D_8010A288_water_whirled; /* its volume */
extern Vec D_8010A2D4_water_whirled; /* light direction */
void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
f32 fabsf(f32);
void func_80105D64_water_whirled(void);
extern Vec D_8010A1D0_water_whirled[4]; /* rider positions */
extern u8 D_800D2008_main;
extern u8 D_800D6A90_main;
u16 func_800E6E9C_minigame(void);
f32 func_800202A8_main(f32 angle);
extern s32 D_8010A240_water_whirled[4]; /* laps per player */
extern f32 D_8010A2E0_water_whirled[4]; /* value per place, best first */
extern WwCtrl D_8010A2AC_water_whirled;
void func_800E6F0C_minigame(s8 arg0);
extern s16 D_800EB934_minigame;
extern s32 D_8010A270_water_whirled[4]; /* per player state; 5: reached the goal */
extern s32 D_8010A28C_water_whirled[4]; /* sound handles, -1 none */
void func_80106308_water_whirled(omObjData* obj);
void func_80106680_water_whirled(void);
void func_8010616C_water_whirled(omObjData* obj);
void func_8010698C_water_whirled(void);
void func_80106A58_water_whirled(void);
void func_800E147C_minigame(omObjData* obj);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_80106DB8_water_whirled(omObjData* obj);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
void func_800E134C_minigame(omObjData* obj, f32 arg1);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
u8 rand8(void);
void func_80107F08_water_whirled(omObjData* obj);
extern Vec D_8010A160_water_whirled[4]; /* start positions */
extern s8 D_8010A2F0_water_whirled[4]; /* player on each start position, -1 free */
extern s16 D_8010A2F4_water_whirled; /* shared models, -1 until loaded */
extern s16 D_8010A2F6_water_whirled;
extern s16 D_8010A2F8_water_whirled;
// LOCAL END

void func_801059A0_water_whirled(void) {
    u8 cam;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800D5210_main = 30000.0f;
    Hu3DCamSetPerspective(0, 20.0f, 80.0f, 16000.0f);
    HmfLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_801071BC_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_80107880_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_8010789C_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078B8_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078D4_water_whirled);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    omSetStatBit(omAddObj(4, 0, 0, -1, func_80105EA0_water_whirled), 0xA0);
    omSetStatBit(omAddObj(100, 0, 0, -1, func_80108DF8_water_whirled), 0xA0);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010A2AC_water_whirled);
    D_800EB930_minigame = 0x32;
    D_800EB932_minigame = 0x3C;
    func_800EA0FC_minigame(0, 0.0f, D_8010A190_water_whirled[0]);
    func_800EA0FC_minigame(1, 0.0f, D_8010A190_water_whirled[1]);
    func_800EA0FC_minigame(2, 0.0f, D_8010A190_water_whirled[2]);
    func_800EA0FC_minigame(3, 0.0f, D_8010A190_water_whirled[3]);
    HmfLightDirSet(1, D_8010A2D4_water_whirled.x, D_8010A2D4_water_whirled.y, D_8010A2D4_water_whirled.z);
}

/* Camera: place it from CRot/CZoom around Center. */
void func_80105D64_water_whirled(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    pos.y = -sindf(rx) * CZoom + Center.y;
    pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(ry) * sindf(rx);
    up.y = cosdf(rx);
    up.z = cosdf(ry) * sindf(rx);
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
}

/* Camera during play (state 2): centre on the riders and zoom so all four stay on screen. */
void func_80105EA0_water_whirled(omObjData* obj) {
    Vec pos;
    Vec2f scr;
    f32 lo;
    f32 hi;
    s32 i;

    if (func_800E6E8C_minigame() == 2) {
        lo = 50000.0f;
        hi = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].x < lo) {
                lo = D_8010A1D0_water_whirled[i].x;
            }
            if (hi < D_8010A1D0_water_whirled[i].x) {
                hi = D_8010A1D0_water_whirled[i].x;
            }
        }
        Center.x = (lo + hi) * 0.5f;
        lo = 50000.0f;
        hi = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].z < lo) {
                lo = D_8010A1D0_water_whirled[i].z;
            }
            if (hi < D_8010A1D0_water_whirled[i].z) {
                hi = D_8010A1D0_water_whirled[i].z;
            }
        }
        Center.z = (lo + hi) * 0.5f;
        CZoom = 12000.0f;
        func_80105D64_water_whirled();
        hi = 0.0f;
        for (i = 0; i < 4; i++) {
            pos.x = D_8010A1D0_water_whirled[i].x;
            pos.y = 0.0f;
            pos.z = D_8010A1D0_water_whirled[i].z;
            func_80012B14_main(0, &pos, &scr);
            scr.x = fabsf(scr.x - 160.0f);
            scr.y = fabsf(scr.y - 120.0f);
            scr.x = (scr.x + 40.0f) / 160.0f;
            scr.y = (scr.y + 20.0f) / 120.0f;
            if (hi < scr.x) {
                hi = scr.x;
            }
            if (hi < scr.y) {
                hi = scr.y;
            }
        }
        CZoom = hi * 12000.0f;
        if (CZoom < 7000.0f) {
            CZoom = 7000.0f;
        }
    }
}

/* Fade the looping sound out, then leave once the wipe is done. */
void func_8010616C_water_whirled(omObjData* obj) {
    if (D_8010A288_water_whirled != 0) {
        D_8010A288_water_whirled = D_8010A288_water_whirled * 0.75f;
        func_8004AAD0_main(D_8010A284_water_whirled, D_8010A288_water_whirled);
    }
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

/* Sea height at (x, z): the mean of two circular waves. */
f32 func_801061E4_water_whirled(f32 x, f32 z) {
    f32 h;
    f32 x2;
    f32 z2;

    h = sindf((D_8010A250_water_whirled / D_8010A254_water_whirled - HuSqrtf(x * x + z * z) / D_8010A258_water_whirled) * 6.283185307179586) * D_8010A25C_water_whirled;
    x2 = x + 8000.0f;
    z2 = z + 5000.0f;
    return (h + sindf((D_8010A260_water_whirled / D_8010A264_water_whirled - HuSqrtf(x2 * x2 + z2 * z2) / D_8010A268_water_whirled) * 6.283185307179586) * D_8010A26C_water_whirled) / 2.0f;
}

/* Sea model: move its vertices to the wave height and shade them (crests white, troughs blue). */
void func_80106308_water_whirled(omObjData* obj) {
    HmfData* hmf;
    Vtx* dst;
    Vtx* src;
    f32 x;
    f32 z;
    f32 h;
    s32 i;

    hmf = HmfModelData[obj->model[1]].hmf;
    dst = hmf->unk44[D_800D2008_main];
    src = hmf->unk40;
    for (i = 0; i < *(s16*)&hmf->unk16[2]; dst++, i++, src++) {
        x = src->v.ob[0];
        z = src->v.ob[2];
        h = sindf((D_8010A250_water_whirled / D_8010A254_water_whirled - HuSqrtf(x * x + z * z) / D_8010A258_water_whirled) * 6.283185307179586) * D_8010A25C_water_whirled;
        x = x + 8000.0f;
        z = z + 5000.0;
        h = (h + sindf((D_8010A260_water_whirled / D_8010A264_water_whirled - HuSqrtf(x * x + z * z) / D_8010A268_water_whirled) * 6.283185307179586) * D_8010A26C_water_whirled) / 2.0f;
        dst->v.ob[1] = h;
        if (h > 0.0) {
            h = 256.0f - h;
            dst->v.cn[0] = 0xAA;
            dst->v.cn[1] = 0xAA;
            dst->v.cn[2] = h;
        } else {
            h = 175.0f - h;
            if (h > 255.0f) {
                h = 255.0f;
            }
            dst->v.cn[0] = h;
            dst->v.cn[1] = h;
            dst->v.cn[2] = 0xFF;
        }
    }
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010A250_water_whirled += 0.11f;
        D_8010A260_water_whirled += 0.09f;
    }
}

/* Intro camera: hold, then pan along z; at the start (or from tick 90) swing up and out to the play view. */
void func_80106680_water_whirled(void) {
    s32 t = func_800E6E9C_minigame();

    if (func_800E6E8C_minigame() == 0) {
        if (t < 15) {
            CRot.y = 100.0f;
            CRot.x = 350.0f;
            Center.z = 300.0f;
            Center.y = 0.0f;
            CZoom = 2500.0f;
        } else if (t < 75.0) {
            Center.z += 10.0f;
            if (Center.z > 1000.0f) {
                Center.z = 1000.0f;
            }
            if (t == 30) {
                HuAudSeqPlay(0x6D);
            }
        } else if (t >= 90) {
            goto swing;
        }
    } else {
    swing:
        D_8010A2D4_water_whirled.x -= 8.0f;
        D_8010A2D4_water_whirled.z += 3.0f;
        if (D_8010A2D4_water_whirled.x < -85.0f) {
            D_8010A2D4_water_whirled.x = -85.0f;
        }
        if (D_8010A2D4_water_whirled.z > 64.0f) {
            D_8010A2D4_water_whirled.z = 64.0f;
        }
        HmfLightDirSet(1, D_8010A2D4_water_whirled.x, D_8010A2D4_water_whirled.y, D_8010A2D4_water_whirled.z);
        CRot.x *= 0.995f;
        CRot.y -= 2.0f;
        CZoom *= 1.025f;
        Center.z *= 0.98f;
        Center.y += 5.0f;
        if (CRot.x < 319.0f) {
            CRot.x = 319.0f;
        }
        if (CRot.y < 1.0f) {
            CRot.y = 0.0f;
        }
        if (CZoom > 7000.0f) {
            CZoom = 7000.0f;
        }
        if (Center.z < 700.0f) {
            Center.z = 700.0f;
        }
    }
}

/* Camera: close in on player D_8010A280 once it is set. */
void func_8010698C_water_whirled(void) {
    omObjData* player;

    if (D_8010A280_water_whirled != -1) {
        player = D_800EC598_minigame[D_8010A280_water_whirled];
        Center.x -= (Center.x - player->trans.x) * 0.25f;
        Center.z -= (Center.z - player->trans.z) * 0.25f;
        Center.y -= (Center.y - player->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

/* Rank the riders by distance round the oval course (laps * 1500 plus the position on the lap: straights
   along x in -1000..1000, half circles beyond) and give each the value of its place in D_8010A190. */
void func_80106A58_water_whirled(void) {
    s32 idx[4];
    f32 dist[4];
    omObjData* player;
    f32 x;
    f32 z;
    f32 a;
    s32 i;
    s32 j;
    s32 swapped;
    s32 ti;
    f32 tf;

    for (i = 0; i < 4; i++) {
        dist[i] = D_8010A240_water_whirled[i] * 1500.0f;
        player = D_800EC598_minigame[i];
        x = player->trans.x;
        z = player->trans.z;
        if (x > 0.0f) {
            if (z > 0.0f) {
                if (x > 1000.0f) {
                    dist[i] = atan2df(x - 1000.0f, z) / 90.0f * 500.0f + 1000.0f + dist[i];
                } else {
                    dist[i] = x + dist[i];
                }
            } else {
                if (x > 1000.0f) {
                    dist[i] = (atan2df(x - 1000.0f, z) - 90.0f) / 90.0f * 500.0f + dist[i];
                } else {
                    dist[i] = 1000.0f - x + 500.0f + dist[i];
                }
            }
        } else {
            a = func_800202A8_main(atan2df(x + 1000.0f, z));
            if (z > 0.0f) {
                if (x < -1000.0f) {
                    dist[i] = (a - 270.0f) / 90.0f * 500.0f + dist[i];
                } else {
                    dist[i] = x + 1000.0f + 500.0f + dist[i];
                }
            } else {
                if (x < -1000.0f) {
                    dist[i] = (a - 180.0f) / 90.0f * 500.0f + 1000.0f + dist[i];
                } else {
                    dist[i] = dist[i] - x;
                }
            }
        }
        idx[i] = i;
    }
    do {
        swapped = 0;
        for (i = 0; i < 3; i++) {
            for (j = i + 1; j < 4; j++) {
                if (j == 4) { /* never true; the retail code tests it */
                    break;
                }
                if (dist[i] > dist[j]) {
                    tf = dist[j];
                    dist[j] = dist[i];
                    dist[i] = tf;
                    ti = idx[j];
                    idx[j] = idx[i];
                    idx[i] = ti;
                    swapped = 1;
                }
            }
        }
    } while (swapped != 0);
    for (i = 0; i < 4; i++) {
        D_8010A190_water_whirled[idx[i]] = D_8010A2E0_water_whirled[i];
    }
}

/* Sea and game flow by minigame state: start sounds, intro, play (first rider to state 5 wins 10 bonus
   coins), finish, results, leave. */
void func_80106DB8_water_whirled(omObjData* obj) {
    s32 t;
    s32 i;

    func_80106308_water_whirled(obj);
    if (func_80049F98_main() + D_800D6A90_main != 0) {
        return;
    }
    t = func_800E6E9C_minigame();
    switch (func_800E6F40_minigame()) {
        case 0:
            if (t == 1) {
                D_8010A28C_water_whirled[0] = func_8004ACE0_main(0x41A, 0);
                D_8010A28C_water_whirled[1] = func_8004ACE0_main(0x41A, 1);
                D_8010A28C_water_whirled[2] = func_8004ACE0_main(0x41A, 2);
                D_8010A28C_water_whirled[3] = func_8004ACE0_main(0x41A, 3);
                HuAudFXPlay(0x424);
            }
        case 1:
            func_80106680_water_whirled();
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_8010A270_water_whirled[i] == 5) {
                    D_8010A280_water_whirled = i;
                    func_800E6F0C_minigame(3);
                    D_8010A2AC_water_whirled.unk18[0] = D_8010A280_water_whirled;
                    D_8010A2AC_water_whirled.unk06 = 0;
                    GwPlayer[((MgWork*)D_800EC598_minigame[D_8010A280_water_whirled]->data)->unk59].bonusCoin += 10;
                    break;
                }
            }
            if (D_8010A284_water_whirled != 0) {
                D_8010A288_water_whirled += 7;
                if (D_8010A288_water_whirled > 110) {
                    D_8010A288_water_whirled = 110;
                }
            }
            func_80106A58_water_whirled();
            break;
        case 3:
            if (t == 15.0) {
                func_8004AEF0_main(D_8010A28C_water_whirled[0], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[1], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[2], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[3], 30);
                D_8010A28C_water_whirled[0] = -1;
                D_8010A28C_water_whirled[1] = -1;
                D_8010A28C_water_whirled[2] = -1;
                D_8010A28C_water_whirled[3] = -1;
            }
            if (D_8010A280_water_whirled == -1) {
                D_8010A2AC_water_whirled.unk06 = 4;
            } else {
                D_8010A288_water_whirled += 3;
                if (D_8010A288_water_whirled > 127) {
                    D_8010A288_water_whirled = 127;
                }
            }
            func_8010698C_water_whirled();
            break;
        case 4:
            if (D_8010A280_water_whirled != -1 && D_800EB934_minigame == 1) {
                func_8004AC98_main(GwPlayer[D_8010A280_water_whirled].chr + 0x290, D_8010A280_water_whirled);
            }
            if (t >= 150) {
                D_8010A288_water_whirled -= 4;
                if (D_8010A288_water_whirled < 0) {
                    D_8010A288_water_whirled = 0;
                }
            }
            func_8010698C_water_whirled();
            break;
        case 5:
            WipeCreateOut(0, 20);
            obj->func = func_8010616C_water_whirled;
            break;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
    }
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        obj->func = func_8010616C_water_whirled;
    }
    if (D_8010A284_water_whirled != 0) {
        func_8004AAD0_main(D_8010A284_water_whirled, D_8010A288_water_whirled);
    }
}

/* The sea (ground object): sea and scenery models, camera start. */
void func_801071BC_water_whirled(omObjData* obj) {
    WwGround* gw;

    obj->model[0] = func_8000B0A0_main(0x440000, 0x4C9);
    obj->model[1] = func_8000B0A0_main(0x440001, 0x4C9);
    obj->model[2] = func_8000B0A0_main(0x440003, 0x8C9);
    obj->model[3] = Hu3DModelLink(obj->model[2]);
    obj->model[4] = func_8000B0A0_main(0x440004, 0x8C9);
    obj->model[5] = Hu3DModelLink(obj->model[4]);
    obj->model[6] = func_8000B0A0_main(0x440005, 0x8C9);
    obj->model[7] = Hu3DModelLink(obj->model[6]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(WwGround), 31000);
    memset(gw, 0, sizeof(WwGround));
    obj->func = func_80106DB8_water_whirled;
    gw->unk03 = 1;
    CZoom = 12000.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    func_800E147C_minigame(obj);
    func_800E1370_minigame(obj, 1, 0.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    gw->unk04 = 0;
    func_8001C2FC_main(obj->model[1], 0x20000, 0x20000);
    func_8001C448_main(obj->model[1]);
    func_8001C954_main(obj->model[1]);
    Hu3DModelPosSet(obj->model[2], -2400.0f, 0.0f, -1400.0f);
    Hu3DModelPosSet(obj->model[3], 2700.0f, 0.0f, -900.0f);
    Hu3DModelPosSet(obj->model[4], 1000.0f, 300.0f, -1950.0f);
    Hu3DModelPosSet(obj->model[5], -2400.0f, 500.0f, -2000.0f);
    Hu3DModelPosSet(obj->model[6], -1300.0f, 500.0f, -2050.0f);
    Hu3DModelPosSet(obj->model[7], 2000.0f, 100.0f, -2500.0f);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C814_main(obj->model[3], 2, 2);
    func_8001C814_main(obj->model[4], 2, 2);
    func_8001C814_main(obj->model[5], 2, 2);
    func_8001C814_main(obj->model[6], 2, 2);
    func_8001C814_main(obj->model[7], 2, 2);
    omSetStatBit(obj, 0xA0);
}

/* A rider: character model, work, the six shared effect models, a random free start position. */
void func_8010750C_water_whirled(omObjData* obj, s32 player) {
    MgWork* work;
    s32 i;

    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = HuMemAllocTag(sizeof(MgWork), 0x7918);
    memset(obj->data, 0, sizeof(MgWork));
    work = obj->data;
    obj->model[0] = func_8000B108_main((GwPlayer[(u16)player].chr + 9) | 0x440000, 0x6D9);
    work->unk57 = GwPlayer[(u16)player].pad;
    obj->func = func_80107F08_water_whirled;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unk8C = 65536.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unk60 = 0;
    func_800E1328_minigame(obj, 100.0f);
    func_800E1334_minigame(obj, 150.0f);
    func_800E1340_minigame(obj, 20.0f);
    func_800E134C_minigame(obj, 30.0f);
    func_800E12EC_minigame(obj, 1000.0f);
    work->unk9C = work->unkA0 = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unkC3 = -1;
    work->unkC4 = -1;
    work->unkB0 = 1.0f;
    work->unkAC = 1.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.1f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (D_8010A2F4_water_whirled < 0) {
                obj->model[i + 1] = D_8010A2F4_water_whirled = func_8000B108_main(0x440006, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_8010A2F4_water_whirled);
            }
        } else if (i == 4 || i == 1) {
            if (D_8010A2F6_water_whirled < 0) {
                obj->model[i + 1] = D_8010A2F6_water_whirled = func_8000B108_main(0x440007, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_8010A2F6_water_whirled);
            }
        } else {
            if (D_8010A2F8_water_whirled < 0) {
                obj->model[i + 1] = D_8010A2F8_water_whirled = func_8000B108_main(0x440008, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_8010A2F8_water_whirled);
            }
        }
        func_8001C2FC_main(obj->model[i + 1], 0x70000000, 0x70000000);
    }
    work = obj->data;
    work->unk3C = 90.0f;
    func_800E149C_minigame(obj, 0, 2);
    do {
        i = rand8() & 3;
    } while (D_8010A2F0_water_whirled[i] != -1);
    D_8010A2F0_water_whirled[i] = player;
    obj->trans.x = D_8010A160_water_whirled[i].x;
    obj->trans.y = D_8010A160_water_whirled[i].y;
    obj->trans.z = D_8010A160_water_whirled[i].z;
}

void func_80107880_water_whirled(omObjData* obj) {
    func_8010750C_water_whirled(obj, 0);
}

void func_8010789C_water_whirled(omObjData* obj) {
    func_8010750C_water_whirled(obj, 1);
}

void func_801078B8_water_whirled(omObjData* obj) {
    func_8010750C_water_whirled(obj, 2);
}

void func_801078D4_water_whirled(omObjData* obj) {
    func_8010750C_water_whirled(obj, 3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801078F0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107D18_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107DD4_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107F08_water_whirled);

/* n = normalised (b - a) x (c - a). */
void func_8010860C_water_whirled(Vec* a, Vec* b, Vec* c, Vec* n) {
    f32 ux;
    f32 uy;
    f32 uz;
    f32 vx;
    f32 vy;
    f32 vz;

    ux = b->x - a->x;
    uy = b->y - a->y;
    uz = b->z - a->z;
    vx = c->x - a->x;
    vy = c->y - a->y;
    vz = c->z - a->z;
    n->x = uy * vz - uz * vy;
    n->y = uz * vx - ux * vz;
    n->z = ux * vy - uy * vx;
    func_800202FC_main(n);
}

/* Tilt the rider with the slope of the sea under (x, z). */
void func_801086A0_water_whirled(omObjData* obj, f32 x, f32 z) {
    Vec p0;
    Vec p1;
    Vec p2;
    Vec n;
    MgWork* work;

    p0.x = x;
    p0.y = func_801061E4_water_whirled(x, z);
    p0.z = z;
    p1.x = x + sindf(0.0f) * 10.0f;
    p1.z = z + cosdf(0.0f) * 10.0f;
    p1.y = func_801061E4_water_whirled(p1.x, p1.z);
    p2.x = x + sindf(90.0f) * 10.0f;
    p2.z = z + cosdf(90.0f) * 10.0f;
    p2.y = func_801061E4_water_whirled(p2.x, p2.z);
    func_8010860C_water_whirled(&p0, &p1, &p2, &n);
    n.y = 0.0f;
    func_800202FC_main(&n);
    work = obj->data;
    n.x *= 5.0f;
    n.z *= 20.0f;
    if (work->unk90 < n.x) {
        work->unk90 += 1.0f;
    } else if (work->unk90 > n.x) {
        work->unk90 -= 1.0f;
    }
    if (work->unk98 < n.z) {
        work->unk98 += 1.0f;
    } else if (work->unk98 > n.z) {
        work->unk98 -= 1.0f;
    }
    obj->rot.x = work->unk90;
    obj->rot.z = work->unk98;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108898_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801089C0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108B98_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108DF8_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109340_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109458_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010956C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010960C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801096BC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801098AC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109E2C_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A520_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A540_water_whirled);
