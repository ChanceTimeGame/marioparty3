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

/* a model part from func_8001D33C_main (the host's eyebrows and moustache) */
typedef struct OdMotObj {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ f32 unk18;
} OdMotObj;

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
void func_800461B4_main(s16 arg0);
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void *func_8001D33C_main(s16 arg0, char *arg1);
void func_800EB708_name_81(Vec *arg0, Vec *arg1, Vec *arg2);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Process *func_800EBF2C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void func_800EB7BC_name_81(Vec *out);
void func_800EB4DC_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6);
void func_800EB164_name_81(s16 arg0, s32 arg1);
void func_800EB5E8_name_81(void);
s32 func_800EFE8C_name_81(Object *arg0, Vec *arg1, f32 arg2);
void func_800F6550_name_81(s32 playerNo, s16 x, s16 y);
void func_800F7458_name_81(s32 playerNo, f32 x, f32 y);
void func_800F79E8_name_81(s32 playerNo);
void func_800F79DC_name_81(s32 arg0);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800F76F8_name_81(s32 playerNo, s32 x, s32 y, s32 back);
void func_800F7228_name_81(s32 playerIndex, s32 coinAmount, s32 arg2);

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
extern Vec D_80109250_opduel;
extern Vec D_8010928C_opduel[2];
extern Vec D_801092A4_opduel[2];
extern Vec D_801092BC_opduel[2];
extern Vec D_801092D4_opduel[2];
extern Vec D_801092EC_opduel[2];
extern Vec D_80109304_opduel[2];
extern Vec D_8010931C_opduel[4];
extern OdMotList D_8010934C_opduel;
extern OdMotList *D_8010940C_opduel[8];
extern s32 *D_80109464_opduel[8];
extern s32 D_80109484_opduel[3];
extern OdBoardIds D_80109490_opduel;
extern OdBoardIds D_801094A8_opduel;
extern OdBoardIds D_801094C0_opduel;
extern OdBoardIds D_801094D8_opduel;

extern s32 D_80101200_name_81[]; /* ovl_81 .data (still asm): each character's name message */
extern u8 D_80101960_name_81[]; /* ovl_81 .data (still asm): each character's partner-display index */

extern u8 D_80109570_opduel;
extern GW_PLAYER *D_80109574_opduel[2]; /* bss: splat splits it at D_80109578_opduel */
extern Object *D_8010957C_opduel[2]; /* bss: the two partner models */

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

/* the host's introduction: the host flies in, each player is named, a coin toss decides who goes
   first, each player picks a starting partner side, then the status displays come in */
void func_80106D18_opduel(void) {
    Vec dir[2];
    OdBoardIds back;
    s16 fx[2];
    OdBoardIds msg;
    s32 i;
    s32 j;
    s32 side;
    s32 edge;
    f32 angle;
    f32 scale;
    f32 radius;
    f32 speed;
    f32 base;
    OdMotObj *part;
    s16 model;

    back = D_801094C0_opduel;
    MBDBackKill();
    MBDBackLoad(back.ids[GwSystem.current_board_index]);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_80109208_opduel = func_800D8010_name_81(0x3B, D_80109484_opduel);
    func_800461B4_main(D_80109208_opduel->omObj1->model[0]);
    HuVecCopy3F(&D_80109208_opduel->coords, &D_80109250_opduel);
    D_80109208_opduel->velocity.x = 900.0f;
    D_80109214_opduel = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80109214_opduel, 15.0f, 20.0f, 8.0f);
    func_8000D018_main(D_80109214_opduel, 200.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&D_80109574_opduel[i]->player_obj->coords, &D_801092D4_opduel[i]);
        fx[i] = func_80105B3C_opduel(0xB0004, 0x689);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            func_80105CBC_opduel(fx[i], D_80109574_opduel[i]->player_obj->coords.x,
                                 D_80109574_opduel[i]->player_obj->coords.y + 50.0f,
                                 D_80109574_opduel[i]->player_obj->coords.z);
            if (j == 0) {
                func_800FFAE0_name_81(i, 1);
            }
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            func_800D8E88_name_81(D_80109574_opduel[i]->player_obj);
            HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuAudFXPlay(0x2DD);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    /* the host circles in */
    for (angle = 0.0f, radius = 500.0f, j = 0; D_80109208_opduel->velocity.x >= 300.0f;) {
        D_80109208_opduel->coords.x = sindf(angle) * radius;
        D_80109208_opduel->coords.z = cosdf(angle) * radius + D_80109250_opduel.z;
        D_80109208_opduel->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        j++;
        func_8000CFA4_main(D_80109214_opduel, D_80109208_opduel->coords.x, D_80109208_opduel->velocity.x - 50.0f,
                           D_80109208_opduel->coords.z);
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80109574_opduel[i]->player_obj->coords, &D_8010928C_opduel[i],
                                      &D_80109574_opduel[i]->player_obj->rot);
                func_800EBF2C_name_81(&D_80109574_opduel[i]->player_obj->coords, &D_8010928C_opduel[i],
                                      &D_80109574_opduel[i]->player_obj->coords, 20);
                func_800D90D0_name_81(D_80109574_opduel[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80109574_opduel[i]->player_obj->coords, &D_80109250_opduel, &dir[i]);
                func_800EBC60_name_81(&D_80109574_opduel[i]->player_obj->rot, &dir[i],
                                      &D_80109574_opduel[i]->player_obj->rot, 10);
                func_800D918C_name_81(D_80109574_opduel[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    omAddObj(0x1000, 0, 0, -1, func_80106CB4_opduel)->trans.y = D_80109208_opduel->velocity.x;
    func_800138EC_main(D_80109214_opduel, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800EBF2C_name_81(&D_80109574_opduel[i]->player_obj->coords, &D_801092A4_opduel[i],
                                             &D_80109574_opduel[i]->player_obj->coords, 20));
        func_800D90D0_name_81(D_80109574_opduel[i]->player_obj, 2, 2);
    }
    HuPrcChildWait();
    for (i = 0; i < 2; i++) {
        func_800D918C_name_81(D_80109574_opduel[i]->player_obj, -1, 0, 5, 2);
    }
    HuAudSeqPlay(0xD);
    HuAudFXPlay(0x159);
    msg = D_801094D8_opduel;
    /* the board's welcome */
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x2700, msg.ids[D_80109570_opduel], 0, 0, 0, 0);
    func_800EB5E8_name_81();
    func_800EB5E8_name_81();
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    /* names player 1 */
    func_800EB7BC_name_81(&dir[0]);
    func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &dir[0], &D_80109574_opduel[0]->player_obj->rot, 10);
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x2707, D_80101200_name_81[GwPlayer[0].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    func_800EB708_name_81(&D_80109574_opduel[0]->player_obj->coords, &D_80109208_opduel->coords, &dir[0]);
    func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &dir[0], &D_80109574_opduel[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    /* names player 2 */
    func_800EB7BC_name_81(&dir[1]);
    func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &dir[1], &D_80109574_opduel[1]->player_obj->rot, 10);
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x2708, D_80101200_name_81[GwPlayer[1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    func_800EB708_name_81(&D_80109574_opduel[1]->player_obj->coords, &D_80109208_opduel->coords, &dir[1]);
    func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &dir[1], &D_80109574_opduel[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    edge = 0;
    D_80109208_opduel->rot.x = sindf(0.0f);
    D_80109208_opduel->rot.z = cosdf(0.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    /* the coin toss */
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x2709);
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    side = func_800EFE20_name_81(2.0f);
retry:
    HuAudFXPlay(0x2DE);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    switch (func_800EFE20_name_81(20.0f)) {
        case 0:
            if (edge == 0) {
                edge = 1;
                /* the first toss lands on its edge: toss again */
                while (!(angle >= 160.0f && angle <= 200.0f)) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    D_80109208_opduel->rot.x = sindf(angle);
                    D_80109208_opduel->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                for (speed = 30.0f; speed >= 0.0f; speed -= 1.0f) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    D_80109208_opduel->rot.x = sindf(angle);
                    D_80109208_opduel->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                func_800138EC_main(D_80109214_opduel, 1, 0);
                HuPrcSleep(30);
                func_800D90D0_name_81(D_80109208_opduel, 0, 2);
                func_800EB164_name_81(-1, 0x270A);
                func_800D90D0_name_81(D_80109208_opduel, -1, 2);
                goto retry;
            }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            /* a wobble: the coin nearly settles on the other face, then tips over */
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (side != 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else if (angle >= 70.0f && angle <= 110.0f) {
                    break;
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.0f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            func_800138EC_main(D_80109214_opduel, 1, 0);
            HuPrcSleep(20);
            func_800138EC_main(D_80109214_opduel, 0, 1);
            speed = -25.0f;
            for (i = 0; i < 6; i++) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = (side == 0) ? 0.0f : 180.0f;
            D_80109208_opduel->rot.x = sindf(angle);
            D_80109208_opduel->rot.z = cosdf(angle);
            for (i = 0; i < 30; i++) {
                angle += 90.0f;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle) / (i + 10.0f);
                HuPrcVSleep();
            }
            break;
        default:
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (side == 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else if (angle >= 70.0f && angle <= 110.0f) {
                    break;
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.04f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = (side == 0) ? 0.0f : 180.0f;
            D_80109208_opduel->rot.x = sindf(angle);
            D_80109208_opduel->rot.z = cosdf(angle);
            break;
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    func_800FFAE0_name_81(side, 2);
    HuPrcSleep(20);
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x270B);
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    if (side == 0) {
        func_800D90D0_name_81(D_80109208_opduel, 0, 2);
        func_800EB4DC_name_81(-1, 0x270C, D_80101200_name_81[GwPlayer[0].chr], 0, 0, 0, 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    } else {
        /* player 2 goes first: the two swap places, and records */
        func_800D90D0_name_81(D_80109208_opduel, 0, 2);
        func_800EB4DC_name_81(-1, 0x270C, D_80101200_name_81[GwPlayer[1].chr], 0, 0, 0, 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_800D90D0_name_81(D_80109208_opduel, -1, 2);
        func_800EB708_name_81(&D_80109574_opduel[0]->player_obj->coords, &D_80109574_opduel[1]->player_obj->coords,
                              &D_80109574_opduel[0]->player_obj->rot);
        func_800EB708_name_81(&D_80109574_opduel[1]->player_obj->coords, &D_80109574_opduel[0]->player_obj->coords,
                              &D_80109574_opduel[1]->player_obj->rot);
        func_800D90D0_name_81(D_80109574_opduel[0]->player_obj, 2, 2);
        func_800D90D0_name_81(D_80109574_opduel[1]->player_obj, 2, 2);
        /* side is reused for the walk results (nonzero when the loops end) */
        while (TRUE) {
            side = func_800EFE8C_name_81(D_80109574_opduel[0]->player_obj, &D_801092BC_opduel[0], 10.0f);
            if (func_800EFE8C_name_81(D_80109574_opduel[1]->player_obj, &D_801092BC_opduel[1], 10.0f) != 0 &&
                side != 0) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            side = func_800EFE8C_name_81(D_80109574_opduel[0]->player_obj, &D_801092A4_opduel[1], 10.0f);
            if (func_800EFE8C_name_81(D_80109574_opduel[1]->player_obj, &D_801092A4_opduel[0], 10.0f) != 0 &&
                side != 0) {
                break;
            }
            HuPrcVSleep();
        }
        func_80105FE8_opduel(0, 1);
        func_800EB708_name_81(&D_80109574_opduel[1]->player_obj->coords, &D_80109208_opduel->coords, &dir[1]);
        func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &dir[1], &D_80109574_opduel[1]->player_obj->rot, 5);
        func_800D90D0_name_81(D_80109574_opduel[0]->player_obj, 0, 2);
        func_800D90D0_name_81(D_80109574_opduel[1]->player_obj, 0, 2);
    }
    /* each player's status display */
    func_800EB7BC_name_81(&D_80109574_opduel[0]->player_obj->rot);
    func_800D90D0_name_81(D_80109574_opduel[0]->player_obj, 3, 0);
    func_8004ACE0_main(0x274, 0);
    func_800F6390_name_81();
    {
        s16 pos[2][2] = { { 30, 40 }, { 194, 40 } };

        func_800F6550_name_81(0, pos[0][0], pos[0][1]);
        func_800F6550_name_81(1, pos[1][0], pos[1][1]);
    }
    func_800F7458_name_81(0, 0, 0);
    func_800F7458_name_81(1, 0, 0);
    D_80109200_opduel = 1;
    func_800F79E8_name_81(0);
    func_800FFAE0_name_81(0, 3);
    func_800EFABC_name_81(D_80109574_opduel[0]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80109574_opduel[0]->player_obj, 0, 2);
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x270D, D_80101200_name_81[GwPlayer[1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    func_800EB7BC_name_81(&D_80109574_opduel[1]->player_obj->rot);
    func_800D90D0_name_81(D_80109574_opduel[1]->player_obj, 3, 0);
    func_8004ACE0_main(0x274, 1);
    func_800F79E8_name_81(1);
    func_800FFAE0_name_81(1, 3);
    func_800EFABC_name_81(D_80109574_opduel[1]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80109574_opduel[1]->player_obj, 0, 2);
    if (side != 0) {
        func_800138EC_main(D_80109214_opduel, 0, 1);
        func_800EB7BC_name_81(&dir[0]);
        func_800EBC60_name_81(&D_80109208_opduel->rot, &dir[0], &D_80109208_opduel->rot, 5);
        HuPrcSleep(6);
        func_800138EC_main(D_80109214_opduel, 1, 0);
    }
    /* the partners */
    func_800D90D0_name_81(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x270E);
    func_800D90D0_name_81(D_80109208_opduel, -1, 2);
    model = D_80109208_opduel->omObj1->model[0];
    func_8002FD8C_main(model, HmfModelData[model].unk02, "l_mayu", 0x4C, 0x47);
    part = func_8001D33C_main(D_80109208_opduel->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        part->unk18 = i;
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 0, 1);
    HuAudFXPlay(0x174);
    model = D_80109208_opduel->omObj1->model[0];
    func_8002FD8C_main(model, HmfModelData[model].unk02, "hige", 0x17, 0x46);
    part = func_8001D33C_main(D_80109208_opduel->omObj1->model[0], "hige");
    base = part->unk08;
    for (i = 0; i < 30; i += 2) {
        part->unk08 = sindf(i * 45) * 10.0f + base;
        HuPrcVSleep();
    }
    part->unk08 = base;
    func_800138EC_main(D_80109214_opduel, 1, 0);
    {
        s32 partner[8] = { 0x25, 0xC, 9, 0xA, 0x26, 0xB, 0x2C, 0x24 };
        s32 sfx[8] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };
        s32 choice[2];
        s32 win0; /* DuelHelpWin pointers through ovl_81.h's s32 prototype */
        s32 win1;

        for (i = 0; i < 2; i++) {
            D_8010957C_opduel[i] = func_800D8010_name_81(partner[GwPlayer[i].chr], D_80109464_opduel[GwPlayer[i].chr]);
            HuVecCopy3F(&D_8010957C_opduel[i]->coords, &D_801092EC_opduel[i]);
            HuAudFXPlay(sfx[GwPlayer[i].chr]);
        }
        func_800D90D0_name_81(D_8010957C_opduel[0], 0, 2);
        func_800D90D0_name_81(D_8010957C_opduel[1], 0, 2);
        while (TRUE) {
            side = func_800EFE8C_name_81(D_8010957C_opduel[0], &D_80109304_opduel[0], 20.0f);
            if (func_800EFE8C_name_81(D_8010957C_opduel[1], &D_80109304_opduel[1], 20.0f) != 0 && side != 0) {
                break;
            }
            HuPrcVSleep();
        }
        func_800EB7BC_name_81(&dir[0]);
        func_800EB7BC_name_81(&dir[1]);
        func_800EBC60_name_81(&D_8010957C_opduel[0]->rot, &dir[0], &D_8010957C_opduel[0]->rot, 10);
        func_800EBC60_name_81(&D_8010957C_opduel[1]->rot, &dir[1], &D_8010957C_opduel[1]->rot, 10);
        HuPrcSleep(10);
        func_800D90D0_name_81(D_8010957C_opduel[0], -1, 2);
        func_800D90D0_name_81(D_8010957C_opduel[1], -1, 2);
        func_800EB708_name_81(&D_80109574_opduel[0]->player_obj->coords, &D_80109574_opduel[1]->player_obj->coords, &dir[0]);
        func_800EB708_name_81(&D_80109574_opduel[1]->player_obj->coords, &D_80109574_opduel[0]->player_obj->coords, &dir[1]);
        func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &dir[0], &D_80109574_opduel[0]->player_obj->rot, 5);
        func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &dir[1], &D_80109574_opduel[1]->player_obj->rot, 5);
        func_800D918C_name_81(D_80109208_opduel, 0, 0, 5, 2);
        func_800EB164_name_81(-1, 0x270F);
        func_800D918C_name_81(D_80109208_opduel, -1, 0, 5, 2);
        /* A: front, B: back; CPUs pick by character */
        choice[0] = 0;
        choice[1] = 0;
        win0 = func_800E1824_name_81(0x14, 0xAE, 1);
        win1 = func_800E1824_name_81(0x15, 0xBC, 1);
        while (choice[0] == 0 || choice[1] == 0) {
            for (i = 0; i < 2; i++) {
                if (choice[i] != 0) {
                    continue;
                }
                if (func_800F37B8_name_81(i) == 0) {
                    if (D_800C9520_main[GwPlayer[i].pad] & 0x8000) {
                        choice[i] = 1;
                    } else if (D_800C9520_main[GwPlayer[i].pad] & 0x4000) {
                        choice[i] = 2;
                    }
                } else {
                    choice[i] = 1;
                    switch (GwPlayer[i].chr) {
                        case 5:
                            choice[i] = 2;
                            break;
                        case 2:
                            if (func_800EFE20_name_81(100.0f) < 50) {
                                choice[i] = 2;
                            }
                            break;
                        case 0:
                            if (func_800EFE20_name_81(100.0f) < 20) {
                                choice[i] = 2;
                            }
                            break;
                    }
                }
            }
            HuPrcVSleep();
        }
        func_800E1854_name_81(win0);
        func_800E1854_name_81(win1);
        func_800D90D0_name_81(D_8010957C_opduel[0], 0, 2);
        func_800D90D0_name_81(D_8010957C_opduel[1], 0, 2);
        func_800EB708_name_81(&D_8010957C_opduel[0]->coords, &D_8010931C_opduel[(choice[0] - 1) * 2 + 0], &D_8010957C_opduel[0]->rot);
        func_800EB708_name_81(&D_8010957C_opduel[1]->coords, &D_8010931C_opduel[(choice[1] - 1) * 2 + 1], &D_8010957C_opduel[1]->rot);
        func_800EBF2C_name_81(&D_8010957C_opduel[0]->coords, &D_8010931C_opduel[(choice[0] - 1) * 2 + 0], &D_8010957C_opduel[0]->coords, 20);
        func_800EBF2C_name_81(&D_8010957C_opduel[1]->coords, &D_8010931C_opduel[(choice[1] - 1) * 2 + 1], &D_8010957C_opduel[1]->coords, 20);
        HuPrcSleep(20);
        func_800EB708_name_81(&D_8010957C_opduel[0]->coords, &D_80109574_opduel[1]->player_obj->coords, &dir[0]);
        func_800EB708_name_81(&D_8010957C_opduel[1]->coords, &D_80109574_opduel[0]->player_obj->coords, &dir[1]);
        func_800EBC60_name_81(&D_8010957C_opduel[0]->rot, &dir[0], &D_8010957C_opduel[0]->rot, 10);
        func_800EBC60_name_81(&D_8010957C_opduel[1]->rot, &dir[1], &D_8010957C_opduel[1]->rot, 10);
        HuPrcSleep(10);
        func_800D90D0_name_81(D_8010957C_opduel[0], -1, 2);
        func_800D90D0_name_81(D_8010957C_opduel[1], -1, 2);
        /* the partners join the status displays, sliding in */
        func_800F8418_name_81(0, D_80101960_name_81[GwPlayer[0].chr], choice[0] - 1);
        func_800F79DC_name_81(0);
        if (choice[0] == 1) {
            func_800F5BB4_name_81(0);
            func_800F76F8_name_81(0, 0, 28, 0);
        } else {
            func_800F5EB0_name_81(0);
            func_800F76F8_name_81(0, 0, -28, 1);
        }
        func_800F8418_name_81(1, D_80101960_name_81[GwPlayer[1].chr], choice[1] - 1);
        if (choice[1] == 1) {
            func_800F5BB4_name_81(1);
            func_800F76F8_name_81(1, 0, 28, 0);
        } else {
            func_800F5EB0_name_81(1);
            func_800F76F8_name_81(1, 0, -28, 1);
        }
        for (i = 28; i >= 0; i--) {
            if (choice[0] == 1) {
                func_800F76F8_name_81(0, 0, (s16)i, 0);
            } else {
                func_800F76F8_name_81(0, 0, (s16)-i, 1);
            }
            if (choice[1] == 1) {
                func_800F76F8_name_81(1, 0, (s16)i, 0);
            } else {
                func_800F76F8_name_81(1, 0, (s16)-i, 1);
            }
            HuPrcVSleep();
        }
    }
    func_800F79DC_name_81(1);
    func_800D918C_name_81(D_80109208_opduel, 0, 0, 5, 2);
    func_800EB164_name_81(-1, 0x2710);
    func_800D918C_name_81(D_80109208_opduel, -1, 0, 5, 2);
    /* the starting coins */
    func_800F7228_name_81(0, 10, 1);
    func_800F7228_name_81(1, 10, 0);
    func_800EB7BC_name_81(&D_80109574_opduel[0]->player_obj->rot);
    func_800EB7BC_name_81(&D_80109574_opduel[1]->player_obj->rot);
    func_800D90D0_name_81(D_80109574_opduel[0]->player_obj, 4, 0);
    func_800D90D0_name_81(D_80109574_opduel[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    func_800D918C_name_81(D_80109574_opduel[0]->player_obj, 0, 0, 5, 2);
    func_800D918C_name_81(D_80109574_opduel[1]->player_obj, 0, 0, 5, 2);
    func_800D918C_name_81(D_80109208_opduel, 0, 0, 5, 2);
    func_800EB164_name_81(-1, 0x2711);
    func_800D918C_name_81(D_80109208_opduel, -1, 0, 5, 2);
}


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
Vec D_8010931C_opduel[4] = { /* [(side chosen - 1) * 2 + player] */
    { -100.0f, 0.0f, 2000.0f }, { 100.0f, 0.0f, 2000.0f }, { -300.0f, 0.0f, 2000.0f }, { 300.0f, 0.0f, 2000.0f },
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
