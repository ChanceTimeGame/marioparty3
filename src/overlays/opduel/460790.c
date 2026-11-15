#include "common.h"
#include "malloc.h"
#include "../ovl_81_name/ovl_81.h"

// duel c1
/* opduel (0x64): Duel Mode's opening, the counterpart of opboard (party mode). */

/* A list of motion file ids (count, then ids); D_8010940C_opduel[chr] points at one per
   character: [0] holds the template file ids, [1..7] get each character's ids at init. */
typedef struct OdMotList {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[5];
} OdMotList; /* size = 0x18 */

/* opboard's ring-of-sparks effect (ObFxPart/ObFxWork) */
/* a board-indexed file/message id list, copied onto the stack before use (retail keeps these in
   .data, not as local initializers) */
typedef struct OdBoardIds {
    /* 0x00 */ s32 ids[6];
} OdBoardIds; /* size = 0x18 */

typedef struct OdFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 phase; /* 0..180 while live, >= 180 idle */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ f32 angle;
    /* 0x1C */ f32 radiusStep;
    /* 0x20 */ f32 radius;
    /* 0x24 */ Vec vel; /* x = angle step, y/z = height/radius factors */
} OdFxPart; /* size = 0x30 */

typedef struct OdFxWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* frames to full radius */
    /* 0x0C */ f32 unk0C; /* degrees turned over unk08 */
    /* 0x10 */ f32 unk10; /* full radius */
    /* 0x14 */ f32 unk14; /* phase step, also scale */
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ Vec center;
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ OdFxPart *parts;
} OdFxWork; /* size = 0x5C */

typedef struct OdFxHmf { /* HmfData's face group count */
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} OdFxHmf;

void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_80007EC0_main(s32);
void func_800F3C98_name_81(s16 playerNo, s32 *arg1, s32 arg2);

void func_80105E20_opduel(s16 model);
void func_80106070_opduel(omObjData *obj);
void func_801061C4_opduel(omObjData *obj);
void func_80106294_opduel(omObjData *obj);
void func_80106350_opduel(void);
void func_801066B8_opduel(void);
void func_80106CB4_opduel(omObjData *obj);
void func_80106D18_opduel(void);
void func_80108FDC_opduel(void);
void func_80109050_opduel(omObjData *obj);
void func_801090AC_opduel(omObjData *obj);
void func_801090F8_opduel(void);
void func_8010911C_opduel(void);
void func_80109158_opduel(void);
void func_801091DC_opduel(void);

extern s32 D_80109200_opduel;
extern Process *D_80109204_opduel;
extern Object *D_80109208_opduel;
extern Object *D_8010920C_opduel;
extern omObjData *D_80109210_opduel;
extern s16 D_80109214_opduel;
extern Process *D_80109218_opduel;
extern UnkBoard4 *D_8010921C_opduel;
extern UnkBoard4 *D_80109220_opduel;
extern omObjData *D_80109224_opduel;
extern s32 D_80109228_opduel;
extern Vec D_8010922C_opduel[3];
extern Vec D_8010925C_opduel[4];
extern OdMotList D_8010934C_opduel;
extern OdMotList *D_8010940C_opduel[8];
extern OdBoardIds D_80109490_opduel;
extern OdBoardIds D_801094A8_opduel;

extern u8 D_80109570_opduel;
extern GW_PLAYER *D_80109574_opduel[2]; /* bss: splat splits it at D_80109578_opduel */

// s0/s1 swapped between the player loop's index and its -1 (masked 0)
#ifdef NON_MATCHING
void func_801059A0_opduel(void) {
    GW_PLAYER *player;
    s32 i;
    s32 chr;
    u32 j;

    D_80109570_opduel = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x14);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_80109158_opduel();
    func_801090F8_opduel();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    func_8005A6B0_main();
    omAddPrcObj(func_80108FDC_opduel, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801090AC_opduel);
    for (i = 0; i < 2; i++) {
        player = MBDGetPlayerStruct(i);
        player->stats.prize.gamblePrize = -1;
        player->stats.prize.duelNo = -1;
    }
    for (chr = 1; chr < 8; chr++) {
        for (j = 0; j < D_8010934C_opduel.count; j++) {
            D_8010940C_opduel[chr]->ids[j] = func_80017BB8_main(chr, D_8010934C_opduel.ids[j]);
        }
    }
    func_8004A208_main();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801059A0_opduel);
#endif

s16 func_80105B3C_opduel(s32 dir, s32 file) {
    OdFxHmf *hmf;
    OdFxWork *work;
    OdFxPart *part;
    s16 model;
    s16 i;
    f32 radius;
    f32 step;
    f32 speed;

    model = func_8000B108_main(dir, file);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80105E20_opduel);
    hmf = (OdFxHmf *)HmfModelData[model].hmf;
    work = (OdFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->unk08 = 30.0f;
    work->unk0C = 720.0f;
    work->unk10 = 80.0f;
    work->unk14 = 5.0f;
    radius = work->unk10 / 10.0f;
    step = (work->unk10 - radius) / work->unk08;
    speed = work->unk0C / work->unk08;
    for (i = 0; i < hmf->groupCount; i++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->angle = 0.0f;
        part->radius = radius;
        part->radiusStep = step;
        part->vel.x = speed;
        part->vel.y = 0.0f;
        part->vel.z = 0.0f;
        part->scale = 0.0f;
        part->phase = 180.0f;
        part++;
    }
    return model;
}

s32 func_80105CBC_opduel(s16 model, f32 x, f32 y, f32 z) {
    OdFxHmf *hmf;
    OdFxWork *work;
    OdFxPart *part;
    s16 i;
    f32 tilt;

    hmf = (OdFxHmf *)HmfModelData[model].hmf;
    work = (OdFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->phase >= 180.0f) {
            part->angle = func_800EFE20_name_81(360.0f);
            part->radius = work->unk10 / 10.0f;
            tilt = func_800EFE20_name_81(150.0f);
            tilt -= 75.0f;
            if (tilt < 0.0f) {
                tilt += 360.0f;
            }
            part->vel.y = sindf(tilt);
            part->vel.z = cosdf(tilt);
            part->scale = 0.0f;
            part->phase = 0.0f;
            return 1;
        }
    }
    return 0;
}

void func_80105E20_opduel(s16 model) {
    OdFxHmf *hmf;
    OdFxWork *work;
    OdFxPart *part;
    s16 i;
    s16 count;
    f32 r;

    hmf = (OdFxHmf *)HmfModelData[model].hmf;
    work = (OdFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    count = hmf->groupCount;
    for (i = 0; i < count; i++, part++) {
        if (part->phase < 180.0f) {
            part->angle += part->vel.x;
            if (part->angle < 0.0f) {
                part->angle += 360.0f;
            } else if (part->angle >= 360.0f) {
                part->angle -= 360.0f;
            }
            part->radius += part->radiusStep;
            r = part->radius * part->vel.z;
            part->pos.x = r * sindf(part->angle) + work->center.x;
            part->pos.z = r * cosdf(part->angle) + work->center.z;
            part->pos.y = part->radius * part->vel.y + work->center.y;
            part->phase += work->unk14;
            if (part->phase > 180.0f) {
                part->phase = 180.0f;
            }
            part->scale = sindf(part->phase) * work->unk14;
        }
    }
    work->frame++;
}

/* swaps two players' records */
void func_80105FE8_opduel(s32 a, s32 b) {
    GW_PLAYER *pa;
    GW_PLAYER *pb;
    void *tmp;

    pa = MBDGetPlayerStruct(a);
    pb = MBDGetPlayerStruct(b);
    tmp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));
    bcopy(pa, tmp, sizeof(GW_PLAYER));
    bcopy(pb, pa, sizeof(GW_PLAYER));
    bcopy(tmp, pb, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(tmp);
}

void func_80106070_opduel(omObjData *obj) {
    s32 i;

    if (WipeStatGet() == 0) {
        if (D_80109214_opduel != -1) {
            func_8000D044_main(D_80109214_opduel);
            D_80109214_opduel = -1;
        }
        if (D_80109208_opduel != NULL) {
            func_800D8F3C_name_81(D_80109208_opduel);
            D_80109208_opduel = NULL;
        }
        if (D_8010920C_opduel != NULL) {
            func_800D8F3C_name_81(D_8010920C_opduel);
            D_8010920C_opduel = NULL;
        }
        if (D_80109210_opduel != NULL) {
            omDelObj(D_80109210_opduel);
            D_80109210_opduel = NULL;
        }
        if (D_80109218_opduel != NULL) {
            omDelPrcObj(D_80109218_opduel);
            D_80109218_opduel = NULL;
        }
        if (D_8010921C_opduel != NULL) {
            func_800F4584_name_81(D_8010921C_opduel);
            D_8010921C_opduel = NULL;
        }
        if (D_80109220_opduel != NULL) {
            func_800F4584_name_81(D_80109220_opduel);
            D_80109220_opduel = NULL;
        }
        for (i = 0; i < 2; i++) {
            func_800D8F0C_name_81(D_80109574_opduel[i]->player_obj);
        }
        omDelObj(obj);
    }
}

/* either human player pressing START skips the opening */
void func_801061C4_opduel(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & 1) && (D_800C9520_main[GwPlayer[i].pad] & 0x1000)) {
            break;
        }
    }
    if (i != 2) {
        D_80109228_opduel = 1;
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(0xB, 0x10);
        HuAudSeqFadeOut(0x20);
        func_80007EC0_main(0x20);
        obj->func = func_80106070_opduel;
    }
}

/* bobs the centre model and both player models with it */
void func_80106294_opduel(omObjData *obj) {
    s32 i;

    D_80109208_opduel->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        D_80109574_opduel[i]->player_obj->coords.y = D_80109208_opduel->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* the board's logo: drops in with a wobble, then its subtitle */
void func_80106350_opduel(void) {
    OdBoardIds logo = D_80109490_opduel;
    OdBoardIds subtitle = D_801094A8_opduel;
    void *data;
    f32 amp;
    f32 angle;

    HuPrcSleep(10);
    D_8010921C_opduel = func_800F4528_name_81(1, 0);
    data = DataRead(logo.ids[D_80109570_opduel]);
    D_8010921C_opduel->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_8010921C_opduel->unk_0A, 0, D_8010921C_opduel->unk_0C[0], 0);
    HuSprPriSet(D_8010921C_opduel->unk_0A, 0, 10);
    HuSprAttrSet(D_8010921C_opduel->unk_0A, 0, 0);
    func_80054904_main(D_8010921C_opduel->unk_0A, 0, 160, 100);
    HuSprScaleSet(D_8010921C_opduel->unk_0A, 0, 0.0f, 0.0f);
    for (amp = 0.5f, angle = 0.0f; angle <= 720.0f; angle += 45.0f) {
        HuSprScaleSet(D_8010921C_opduel->unk_0A, 0, sindf(angle) * amp + 1.0f, sindf(angle) * amp + 1.0f);
        amp -= 0.03125f;
        if (amp < 0.0f) {
            amp = 0.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuSprScaleSet(D_8010921C_opduel->unk_0A, 0, 1.0f, 1.0f);
    D_80109220_opduel = func_800F4528_name_81(1, 0);
    data = DataRead(subtitle.ids[D_80109570_opduel]);
    D_80109220_opduel->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80109220_opduel->unk_0A, 0, D_80109220_opduel->unk_0C[0], 0);
    HuSprPriSet(D_80109220_opduel->unk_0A, 0, 9);
    HuSprAttrSet(D_80109220_opduel->unk_0A, 0, 0);
    func_80054904_main(D_80109220_opduel->unk_0A, 0, 160, 130);
    HuPrcSleep(75);
    func_800F4584_name_81(D_80109220_opduel);
    func_800F4584_name_81(D_8010921C_opduel);
    D_80109220_opduel = NULL;
    D_8010921C_opduel = NULL;
}

/* the opening: both players and the centre model drop in, the logo shows,
   then the centre model zooms in under a white wipe */
void func_801066B8_opduel(void) {
    omObjData *obj;
    s32 i;
    f32 scale;
    f32 rise;
    Object *ring;

    for (i = 0; i < 2; i++) {
        D_80109574_opduel[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, (s32 *)D_8010940C_opduel[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80109574_opduel[i]->player_obj->coords, &D_8010925C_opduel[i]);
        func_800D8944_name_81(D_80109574_opduel[i]->player_obj);
        D_80109574_opduel[i]->stat |= 4;
    }
    D_80109208_opduel = func_800D8314_name_81(0x1301FF, -1, 1.0f, 0.0f, NULL);
    HuVecCopyXYZ(&D_80109208_opduel->scale, 0.625f, 0.625f, 0.625f);
    D_8010920C_opduel = func_800D8314_name_81(0x1301FD, -1, 1.0f, 0.0f, NULL);
    HuVecCopy3F(&D_80109208_opduel->coords, &D_8010922C_opduel[0]);
    HuVecCopy3F(&D_8010920C_opduel->coords, &D_8010922C_opduel[0]);
    D_8010920C_opduel->coords.y = 0.0f;
    HuVecCopyXYZ(&D_8010920C_opduel->scale, D_8010920C_opduel->coords.y, D_8010920C_opduel->coords.y,
                 D_8010920C_opduel->coords.y);
    D_80109214_opduel = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80109214_opduel, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(D_80109214_opduel, 40.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    WipeCreateIn(2, 0x10);
    HuPrcSleep(17);
    D_80109224_opduel = omAddObj(0x1000, 0, 0, -1, func_801061C4_opduel);
    HuAudSeqPlay(0x6E);
    func_80106350_opduel();
    HuPrcSleep(15);
    HuAudFXPlay(0x2ED);
    while (D_80109208_opduel->coords.y >= 10.0f) {
        D_80109208_opduel->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            D_80109574_opduel[i]->player_obj->coords.y -= 3.0f;
        }
        ring = D_8010920C_opduel;
        rise = 0.625f - D_80109208_opduel->coords.y * 0.625f / 250.0f;
        HuVecCopyXYZ(&ring->scale, rise, rise, rise);
        HuPrcVSleep();
    }
    obj = D_80109210_opduel = omAddObj(0x1000, 0, 0, -1, func_80106294_opduel);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = D_80109208_opduel->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(D_80109214_opduel, D_80109208_opduel->coords.x, D_80109208_opduel->coords.y + 40.0f,
                       D_80109208_opduel->coords.z);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        func_800D8F0C_name_81(D_80109574_opduel[i]->player_obj);
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    HuPrcSleep(20);
    if (D_80109228_opduel != 0) {
        HuPrcSleep(-1);
    } else {
        omDelObj(D_80109224_opduel);
        D_80109224_opduel = NULL;
    }
    for (i = 0, scale = 1.0f; scale < 10.0f; scale += 0.5f, i++) {
        HuVecCopyXYZ(&D_80109208_opduel->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x10);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(D_80109214_opduel);
    D_80109214_opduel = -1;
    func_800D8F3C_name_81(D_80109208_opduel);
    D_80109208_opduel = NULL;
    func_800D8F3C_name_81(D_8010920C_opduel);
    D_8010920C_opduel = NULL;
    omDelObj(D_80109210_opduel);
    D_80109210_opduel = NULL;
    omDelPrcObj(NULL);
}

/* the logo object's bounce: rises and falls with rot.y */
void func_80106CB4_opduel(omObjData *obj) {
    D_80109208_opduel->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_801094F0_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106D18_opduel);


void func_80108FDC_opduel(void) {
    D_80109218_opduel = omAddPrcObj(func_801066B8_opduel, 0x300, 0x2000, 0);
    HuPrcChildLink(HuPrcCurrentGet(), D_80109218_opduel);
    HuPrcChildWait();
    func_80106D18_opduel();
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80109050_opduel(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_801091DC_opduel();
        func_8010911C_opduel();
        func_8005F524_main();
        if (D_80109200_opduel != 0) {
            func_800F64FC_name_81();
        }
        omOvlReturnEx(1);
    }
}

void func_801090AC_opduel(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 0x14);
        HuAudSeqFadeOut(0x3C);
        obj->func = func_80109050_opduel;
    }
}

void func_801090F8_opduel(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
}

void func_8010911C_opduel(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    if (D_80109204_opduel != NULL) {
        omDelPrcObj(D_80109204_opduel);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109508_opduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109528_opduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109548_opduel);

void func_80109158_opduel(void) {
    s32 sp10[] = { 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };

    Hu3DCamInit(1);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(sp10[GwSystem.current_board_index]);
}

void func_801091DC_opduel(void) {
    MBDBackKill();
    MBDBackClose();
}

/* .data */
s32 D_80109200_opduel = 0; /* the players were introduced: the exit starts the status display */
Process *D_80109204_opduel = NULL;
Object *D_80109208_opduel = NULL; /* the centre (host) model */
Object *D_8010920C_opduel = NULL; /* the ring under the centre model */
omObjData *D_80109210_opduel = NULL;
s16 D_80109214_opduel = -1; /* effect model, -1 none */
Process *D_80109218_opduel = NULL;
UnkBoard4 *D_8010921C_opduel = NULL;
UnkBoard4 *D_80109220_opduel = NULL;
omObjData *D_80109224_opduel = NULL;
s32 D_80109228_opduel = 0; /* the opening was skipped */
Vec D_8010922C_opduel[3] = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }; /* only [0] read */
Vec D_80109250_opduel = { 0.0f, 0.0f, 1500.0f };
Vec D_8010925C_opduel[4] = { /* only [0] and [1] read */
    { -10.0f, 250.0f, 0.0f }, { 10.0f, 250.0f, 0.0f }, { -500.0f, 0.0f, 2360.0f }, { 500.0f, 0.0f, 2360.0f },
};
Vec D_8010928C_opduel[2] = { { -200.0f, 0.0f, 2360.0f }, { 200.0f, 0.0f, 2360.0f } };
Vec D_801092A4_opduel[2] = { { -175.0f, 0.0f, 2250.0f }, { 175.0f, 0.0f, 2250.0f } };
Vec D_801092BC_opduel[2] = { { 0.0f, 0.0f, 2150.0f }, { 0.0f, 0.0f, 2350.0f } };
Vec D_801092D4_opduel[2] = { { -125.0f, 0.0f, 2000.0f }, { 125.0f, 0.0f, 2000.0f } };
Vec D_801092EC_opduel[2] = { { -750.0f, 0.0f, 1750.0f }, { 750.0f, 0.0f, 1750.0f } };
Vec D_80109304_opduel[2] = { { -100.0f, 0.0f, 1750.0f }, { 100.0f, 0.0f, 1750.0f } };
Vec D_8010931C_opduel[2][2] = { /* [side chosen - 1][player] */
    { { -100.0f, 0.0f, 2000.0f }, { 100.0f, 0.0f, 2000.0f } },
    { { -300.0f, 0.0f, 2000.0f }, { 300.0f, 0.0f, 2000.0f } },
};
OdMotList D_8010934C_opduel = { 5, { 0x20000, 0x20001, 0x20002, 0x20033, 0x20031 } };
OdMotList D_80109364_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_8010937C_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_80109394_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_801093AC_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_801093C4_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_801093DC_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList D_801093F4_opduel = { 5, { 0, 0, 0, 0, 0 } };
OdMotList *D_8010940C_opduel[8] = {
    &D_8010934C_opduel, &D_80109364_opduel, &D_8010937C_opduel, &D_80109394_opduel,
    &D_801093AC_opduel, &D_801093C4_opduel, &D_801093DC_opduel, &D_801093F4_opduel,
};
/* func_800D8010_name_81's file lists (count, then file ids): each character's partner model */
s32 D_8010942C_opduel[2] = { 1, 0xA0090 };
s32 D_80109434_opduel[2] = { 1, 0xA00A7 };
s32 D_8010943C_opduel[2] = { 1, 0xA0002 };
s32 D_80109444_opduel[2] = { 1, 0xA00BD };
s32 D_8010944C_opduel[2] = { 1, 0xA00D0 };
s32 D_80109454_opduel[2] = { 1, 0xA0138 };
s32 D_8010945C_opduel[2] = { 1, 0xA010F };
s32 *D_80109464_opduel[8] = {
    D_8010942C_opduel, D_80109434_opduel, D_8010943C_opduel, NULL,
    D_80109444_opduel, D_8010944C_opduel, D_8010945C_opduel, D_80109454_opduel,
};
s32 D_80109484_opduel[3] = { 1, 0xA0125, 0 }; /* the host model's file list */
OdBoardIds D_80109490_opduel = { { 0x130022, 0x130023, 0x130024, 0x130025, 0x130026, 0x130027 } }; /* logos */
OdBoardIds D_801094A8_opduel = { { 0x130028, 0x130029, 0x13002A, 0x13002B, 0x13002C, 0x13002D } }; /* subtitles */
OdBoardIds D_801094C0_opduel = { { 0x17, 0x17, 0x17, 0x17, 0x17, 0x17 } }; /* backgrounds */
OdBoardIds D_801094D8_opduel = { { 0x2701, 0x2702, 0x2703, 0x2704, 0x2705, 0x2706 } }; /* host's board messages */
