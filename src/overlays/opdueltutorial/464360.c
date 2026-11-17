#include "common.h"
#include "malloc.h"
#include "../ovl_81_name/ovl_81.h"

// duel k1
/* opdueltutorial (0x65): the Duel Mode tutorial's opening (opduel's layout with opboardtutorial's
   ring-of-sparks effect and host). */

/* A list of motion file ids (count, then ids); D_80108B24_opdueltutorial[chr] points at one per
   character: [0] holds the template file ids, [1..7] get each character's ids at init. */
typedef struct OtMotList {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[5];
} OtMotList; /* size = 0x18 */

/* The ring-of-sparks particle effect of a model (HmfModelData[model].unkBC; opboard's ObFxWork). */
typedef struct OtFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 phase; /* 0..180 while live, >= 180 idle */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ f32 angle;
    /* 0x1C */ f32 radiusStep;
    /* 0x20 */ f32 radius;
    /* 0x24 */ Vec vel; /* x = angle step, y/z = height/radius factors */
} OtFxPart; /* size = 0x30 */

typedef struct OtFxWork {
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
    /* 0x58 */ OtFxPart *parts;
} OtFxWork; /* size = 0x5C */

typedef struct OtFxHmf { /* HmfData's face group count */
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} OtFxHmf;

/* Texture-animation slot (14EA0.c TexAnimSlot). */
typedef struct OtTexAnimSlot {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ char unk08[2];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
} OtTexAnimSlot; /* size = 0xC */

/* a one-entry motion list (count, id) */
typedef struct OtMotList1 {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[1];
} OtMotList1; /* size = 0x8 */

extern u16 D_800D530C_main;
extern OtTexAnimSlot *D_800D1714_main;
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800461B4_main(s16 arg0);
void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
s32 func_80017BB8_main(s16, s16);
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);
void func_800EF754_name_81(s32 winId);
void func_800F3C98_name_81(s16 playerNo, s32 *arg1, s32 arg2);
void func_800EB708_name_81(Vec *arg0, Vec *arg1, Vec *arg2);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Process *func_800EBF2C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void func_800EB7BC_name_81(Vec *out);
s32 func_800EFE8C_name_81(Object *arg0, Vec *arg1, f32 arg2);
void func_800F6550_name_81(s32 playerNo, s16 x, s16 y);
void func_800F7458_name_81(s32 playerNo, f32 x, f32 y);
void func_800F79E8_name_81(s32 playerNo);
void func_800F79DC_name_81(s32 arg0);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800F76F8_name_81(s32 playerNo, s32 x, s32 y, s32 back);
void func_800F7228_name_81(s32 playerIndex, s32 coinAmount, s32 arg2);

s16 func_80105B54_opdueltutorial(s32 dir, s32 file);
s32 func_80105CD4_opdueltutorial(s16 model, f32 x, f32 y, f32 z);
void func_80105E38_opdueltutorial(s16 model);
s16 func_80106000_opdueltutorial(s16 model, s32 file, char *name);
void func_8010610C_opdueltutorial(s16 model, s16 frame);
s16 func_801061DC_opdueltutorial(s32 file);
void func_80106224_opdueltutorial(omObjData *obj);
void func_801062E0_opdueltutorial(void);
void func_80106808_opdueltutorial(omObjData *obj);
void func_8010686C_opdueltutorial(void);
void func_80106BF0_opdueltutorial(void);
void func_80108774_opdueltutorial(void);
void func_801087B4_opdueltutorial(omObjData *obj);
void func_80108810_opdueltutorial(omObjData *obj);
void func_80108854_opdueltutorial(void);
void func_80108880_opdueltutorial(void);
void func_801088C4_opdueltutorial(void);
void func_80108908_opdueltutorial(void);

extern s32 D_80108930_opdueltutorial; /* set once the tutorial ends: the exit starts the status display */
extern Process *D_80108934_opdueltutorial;
extern Vec D_80108938_opdueltutorial; /* the host's position */
extern Vec D_80108944_opdueltutorial[3];
extern Vec D_80108968_opdueltutorial; /* the coin host's position */
extern Vec D_80108974_opdueltutorial[4];
extern Vec D_801089A4_opdueltutorial[2];
extern Vec D_801089BC_opdueltutorial[4];
extern Vec D_801089EC_opdueltutorial[2];
extern Vec D_80108A04_opdueltutorial[2];
extern Vec D_80108A1C_opdueltutorial[2];
extern Vec D_80108A34_opdueltutorial[4];
extern OtMotList D_80108A64_opdueltutorial;
extern OtMotList *D_80108B24_opdueltutorial[8];
extern OtMotList1 *D_80108B74_opdueltutorial[8];
extern OtMotList1 D_80108B94_opdueltutorial;

extern u8 D_80101960_name_81[]; /* ovl_81 .data (still asm): each character's partner-display index */

extern u8 D_80108C10_opdueltutorial;
extern GW_PLAYER *D_80108C14_opdueltutorial[2];
extern Object *D_80108C1C_opdueltutorial; /* the board's centre model */
extern Object *D_80108C20_opdueltutorial[2];
extern Object *D_80108C28_opdueltutorial; /* the host model */
extern s16 D_80108C2C_opdueltutorial; /* the host's message window */
extern s16 D_80108C30_opdueltutorial[10]; /* the host's texture animations */
extern s16 D_80108C44_opdueltutorial;
extern s16 D_80108C46_opdueltutorial; /* texture-animation slot, 0xFF none */


// s0/s1 swapped between the player loop's index and its -1 (masked 0; opduel's twin has the same residue)
#ifdef NON_MATCHING
void func_801059A0_opdueltutorial(void) {
    s32 i;
    GW_PLAYER *player;
    s32 chr;
    u32 j;

    GwSystem.current_board_index = 6;
    D_80108C10_opdueltutorial = 6;
    omInitObjMan(0x32, 0x14);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_801088C4_opdueltutorial();
    func_80108854_opdueltutorial();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    func_8005A6B0_main();
    omAddPrcObj(func_80108774_opdueltutorial, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80108810_opdueltutorial);
    for (i = 0; i < 2; i++) {
        player = MBDGetPlayerStruct(i);
        player->stats.prize.gamblePrize = -1;
        player->stats.prize.duelNo = -1;
    }
    for (chr = 1; chr < 8; chr++) {
        for (j = 0; j < D_80108A64_opdueltutorial.count; j++) {
            D_80108B24_opdueltutorial[chr]->ids[j] = func_80017BB8_main(chr, D_80108A64_opdueltutorial.ids[j]);
        }
    }
    GwPlayer[0].stat = 1;
    GwPlayer[1].stat = 1;
    GwPlayer[0].chr = 0;
    GwPlayer[1].chr = 1;
    func_8004A208_main();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_801059A0_opdueltutorial);
#endif

s16 func_80105B54_opdueltutorial(s32 dir, s32 file) {
    OtFxHmf *hmf;
    OtFxWork *work;
    OtFxPart *part;
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
    func_80013390_main(model, -1, NULL, func_80105E38_opdueltutorial);
    hmf = (OtFxHmf *)HmfModelData[model].hmf;
    work = (OtFxWork *)HmfModelData[model].unkBC;
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

s32 func_80105CD4_opdueltutorial(s16 model, f32 x, f32 y, f32 z) {
    OtFxHmf *hmf;
    OtFxWork *work;
    OtFxPart *part;
    s16 i;
    f32 tilt;

    hmf = (OtFxHmf *)HmfModelData[model].hmf;
    work = (OtFxWork *)HmfModelData[model].unkBC;
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

void func_80105E38_opdueltutorial(s16 model) {
    OtFxHmf *hmf;
    OtFxWork *work;
    OtFxPart *part;
    s16 i;
    s16 count;
    f32 r;

    hmf = (OtFxHmf *)HmfModelData[model].hmf;
    work = (OtFxWork *)HmfModelData[model].unkBC;
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

s16 func_80106000_opdueltutorial(s16 model, s32 file, char *name) {
    void *data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80108C44_opdueltutorial = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].frame;
    D_80108C46_opdueltutorial = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_8010610C_opdueltutorial(s16 model, s16 frame) {
    OtTexAnimSlot *p;

    if (D_80108C46_opdueltutorial != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80108C46_opdueltutorial];
        p->frame = frame;
        p->unk04 = 0;
        p->unk0A = 0;
        p->unk06 = 0;
        p->unk02 = 0;
    }
}

s16 func_801061DC_opdueltutorial(s32 file) {
    void *data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}

void func_80106224_opdueltutorial(omObjData *obj) {
    s32 i;

    D_80108C1C_opdueltutorial->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        D_80108C14_opdueltutorial[i]->player_obj->coords.y = D_80108C1C_opdueltutorial->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* the opening: the two players and the centre model sink into the stage, then the centre grows
   into a white wipe */
void func_801062E0_opdueltutorial(void) {
    omObjData *obj;
    Object *ring;
    s16 effect;
    s32 i;
    f32 scale;
    f32 rise;

    for (i = 0; i < 2; i++) {
        D_80108C14_opdueltutorial[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, (s32 *)D_80108B24_opdueltutorial[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_80108974_opdueltutorial[i]);
        func_800D8944_name_81(D_80108C14_opdueltutorial[i]->player_obj);
        D_80108C14_opdueltutorial[i]->stat |= 4;
    }
    D_80108C1C_opdueltutorial = func_800D8314_name_81(0x1301FF, -1, 1.0f, 0.0f, NULL);
    HuVecCopyXYZ(&D_80108C1C_opdueltutorial->scale, 0.625f, 0.625f, 0.625f);
    ring = func_800D8314_name_81(0x1301FD, -1, 1.0f, 0.0f, NULL);
    HuVecCopy3F(&D_80108C1C_opdueltutorial->coords, &D_80108944_opdueltutorial[0]);
    HuVecCopy3F(&ring->coords, &D_80108944_opdueltutorial[0]);
    ring->coords.y = 0.0f;
    HuVecCopyXYZ(&ring->scale, ring->coords.y, ring->coords.y, ring->coords.y);
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 40.0f);
    func_800138EC_main(effect, 1, 0);
    WipeCreateIn(2, 0x10);
    HuPrcSleep(17);
    HuAudFXPlay(0x2ED);
    while (D_80108C1C_opdueltutorial->coords.y >= 10.0f) {
        D_80108C1C_opdueltutorial->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            D_80108C14_opdueltutorial[i]->player_obj->coords.y -= 3.0f;
        }
        rise = 0.625f - D_80108C1C_opdueltutorial->coords.y * 0.625f / 250.0f;
        HuVecCopyXYZ(&ring->scale, rise, rise, rise);
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_80106224_opdueltutorial);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = D_80108C1C_opdueltutorial->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x, D_80108C1C_opdueltutorial->coords.y + 40.0f,
                       D_80108C1C_opdueltutorial->coords.z);
    func_800138EC_main(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        func_800D8F0C_name_81(D_80108C14_opdueltutorial[i]->player_obj);
    }
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; scale += 0.5f, i++) {
        HuVecCopyXYZ(&D_80108C1C_opdueltutorial->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x10);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(effect);
    func_800D8F3C_name_81(D_80108C1C_opdueltutorial);
    func_800D8F3C_name_81(ring);
    omDelObj(obj);
}

/* the coin host's hover: bobs its height (velocity.x) around obj->trans.y */
void func_80106808_opdueltutorial(omObjData *obj) {
    D_80108C1C_opdueltutorial->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

/* a process: a model plays a run of animation tracks (4..0) from one file, then fades out */
void func_8010686C_opdueltutorial(void) {
    void *data[2]; /* [0] the idle, [1] the data[1] */
    s32 slot;
    Object *model;
    s32 alpha;

    model = func_800D8314_name_81(0x14000A, -1, 1.0f, 0.0f, NULL);
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data[0] = DataRead(0x130135);
    HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    data[1] = DataRead(0x140034);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[1], 4, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuVecCopyXYZ(&model->coords, 0.0f, 150.0f, 500.0f);
    HuPrcSleep(15);
    func_80033430_main(slot);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[1], 3, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(slot);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[1], 2, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(slot);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[1], 1, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(slot);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[1], 0, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(slot);
    slot = (s16)HmfAnimCreate(HmfModelData[model->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    func_8001C448_main(model->omObj1->model[0]);
    HuPrcSleep(5);
    for (alpha = 0xFF; alpha > 0; alpha -= 10) {
        func_8001F9E4_main(model->omObj1->model[0], alpha);
        HuPrcVSleep();
    }
    func_80033430_main(slot);
    DataClose(data[0]);
    DataClose(data[1]);
    func_800D8F3C_name_81(model);
    omDelPrcObj(NULL);
}

/* the tutorial proper: the coin host flies in, the tutorial host explains the coin toss, the
   status displays, the partners (the choice is scripted: player 1 front, player 2 back) and the
   starting coins */
void func_80106BF0_opdueltutorial(void) {
    Vec dir[2];
    s16 fx[2];
    omObjData *obj;
    s32 i;
    s32 j;
    s32 side;
    f32 angle;
    f32 scale;
    f32 radius;
    f32 speed;
    s16 effect;

    MBDBackKill();
    MBDBackLoad(0x17);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_80108C28_opdueltutorial = func_800D8010_name_81(0x3E, NULL);
    HuVecCopy3F(&D_80108C28_opdueltutorial->coords, &D_80108938_opdueltutorial);
    HuVecCopyXYZ(&D_80108C28_opdueltutorial->scale, 0.6f, 0.6f, 0.6f);
    D_80108C28_opdueltutorial->rot.x = sindf(10.0f);
    D_80108C28_opdueltutorial->rot.z = cosdf(10.0f);
    D_80108C28_opdueltutorial->flags |= 1;
    D_80108C2C_opdueltutorial = func_80060880_main(0x4B, 0xC5, 0x10);
    func_8005C060_main(D_80108C2C_opdueltutorial, 4, 0, 0xE0, 0xE0);
    func_8005BDFC_main(D_80108C2C_opdueltutorial, 0);
    D_80108C30_opdueltutorial[0] = func_80106000_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80108C30_opdueltutorial[1] = func_801061DC_opdueltutorial(0xA007F);
    D_80108C30_opdueltutorial[2] = func_801061DC_opdueltutorial(0xA0080);
    D_80108C30_opdueltutorial[3] = func_801061DC_opdueltutorial(0xA0081);
    D_80108C30_opdueltutorial[4] = func_801061DC_opdueltutorial(0xA0082);
    D_80108C30_opdueltutorial[5] = func_801061DC_opdueltutorial(0xA0083);
    D_80108C30_opdueltutorial[6] = func_801061DC_opdueltutorial(0xA0084);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    D_80108C1C_opdueltutorial = func_800D8010_name_81(0x3B, (s32 *)&D_80108B94_opdueltutorial);
    func_800461B4_main(D_80108C1C_opdueltutorial->omObj1->model[0]);
    HuVecCopy3F(&D_80108C1C_opdueltutorial->coords, &D_80108968_opdueltutorial);
    D_80108C1C_opdueltutorial->velocity.x = 900.0f;
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 15.0f, 20.0f, 8.0f);
    func_8000D018_main(effect, 200.0f);
    func_800138EC_main(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_801089EC_opdueltutorial[i]);
        fx[i] = func_80105B54_opdueltutorial(0xB0004, 0x689);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            func_80105CD4_opdueltutorial(fx[i], D_80108C14_opdueltutorial[i]->player_obj->coords.x,
                                         D_80108C14_opdueltutorial[i]->player_obj->coords.y + 50.0f,
                                         D_80108C14_opdueltutorial[i]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            func_800D8E88_name_81(D_80108C14_opdueltutorial[i]->player_obj);
            HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(0xB);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 0x2500, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8010686C_opdueltutorial, 0x300, 0, 0));
    func_8005B43C_main(D_80108C2C_opdueltutorial, 0x2501, -1, -1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    HuPrcChildWait();
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9474, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[1]);
    HuAudFXPlay(0x2DD);
    func_800138EC_main(effect, 0, 1);
    /* the coin host circles in */
    for (angle = 0.0f, radius = 500.0f, j = 0; D_80108C1C_opdueltutorial->velocity.x >= 300.0f;) {
        D_80108C1C_opdueltutorial->coords.x = sindf(angle) * radius;
        D_80108C1C_opdueltutorial->coords.z = cosdf(angle) * radius + D_80108968_opdueltutorial.z;
        D_80108C1C_opdueltutorial->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x, D_80108C1C_opdueltutorial->velocity.x - 50.0f, D_80108C1C_opdueltutorial->coords.z);
        j++;
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_801089A4_opdueltutorial[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->rot);
                func_800EBF2C_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_801089A4_opdueltutorial[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->coords, 20);
                func_800D90D0_name_81(D_80108C14_opdueltutorial[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_80108968_opdueltutorial, &dir[i]);
                func_800EBC60_name_81(&D_80108C14_opdueltutorial[i]->player_obj->rot, &dir[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->rot, 10);
                func_800D918C_name_81(D_80108C14_opdueltutorial[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_80106808_opdueltutorial);
    obj->trans.y = D_80108C1C_opdueltutorial->velocity.x;
    func_800138EC_main(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800EBF2C_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_801089BC_opdueltutorial[i],
                                             &D_80108C14_opdueltutorial[i]->player_obj->coords, 20));
        func_800D90D0_name_81(D_80108C14_opdueltutorial[i]->player_obj, 2, 2);
    }
    HuPrcChildWait();
    for (i = 0; i < 2; i++) {
        func_800D918C_name_81(D_80108C14_opdueltutorial[i]->player_obj, -1, 0, 5, 2);
    }
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9475, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800138EC_main(effect, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    /* player 1 */
    func_800EB7BC_name_81(&dir[0]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &dir[0], &D_80108C14_opdueltutorial[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9476, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[0]->player_obj->coords, &D_80108C1C_opdueltutorial->coords, &dir[0]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &dir[0], &D_80108C14_opdueltutorial[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(effect, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    /* player 2 */
    func_800EB7BC_name_81(&dir[1]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &dir[1], &D_80108C14_opdueltutorial[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9477, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[1]->player_obj->coords, &D_80108C1C_opdueltutorial->coords, &dir[1]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &dir[1], &D_80108C14_opdueltutorial[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(effect, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    D_80108C1C_opdueltutorial->rot.x = sindf(0.0f);
    D_80108C1C_opdueltutorial->rot.z = cosdf(0.0f);
    func_800138EC_main(effect, 1, 0);
    /* the coin toss (scripted: player 1 wins) */
    func_8005B43C_main(D_80108C2C_opdueltutorial, 0x2506, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    side = 0;
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[5]);
    HuAudFXPlay(0x2DE);
    func_800138EC_main(effect, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    while (TRUE) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
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
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    angle = 0.0f;
    D_80108C1C_opdueltutorial->rot.x = sindf(angle);
    D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    /* the status displays */
    func_8005B43C_main(D_80108C2C_opdueltutorial, 0x2507, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[6]);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 3, 0);
    func_8004ACE0_main(0x274, 0);
    func_800F6390_name_81();
    {
        s16 pos[2][2] = { { 30, 40 }, { 194, 40 } };

        func_800F6550_name_81(0, pos[0][0], pos[0][1]);
        func_800F6550_name_81(1, pos[1][0], pos[1][1]);
    }
    func_800F7458_name_81(0, 0.0f, 0.0f);
    func_800F7458_name_81(1, 0.0f, 0.0f);
    D_80108930_opdueltutorial = 1;
    func_800F79E8_name_81(0);
    func_800EFABC_name_81(D_80108C14_opdueltutorial[0]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 0, 2);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 0x2508, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[3]);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 3, 0);
    func_8004ACE0_main(0x274, 1);
    func_800F79E8_name_81(1);
    func_800EFABC_name_81(D_80108C14_opdueltutorial[1]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 0, 2);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[6]);
    HuAudFXPlay(0x2E3);
    omDelObj(obj);
    func_800138EC_main(effect, 0, 1);
    /* the coin host flies off */
    while (D_80108C1C_opdueltutorial->velocity.x < 800.0f) {
        D_80108C1C_opdueltutorial->velocity.x += 10.0f;
        func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x, D_80108C1C_opdueltutorial->velocity.x - 50.0f, D_80108C1C_opdueltutorial->coords.z);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    HuPrcSleep(10);
    /* the partners */
    {
        s32 partner[8] = { 0x25, 0xC, 9, 0xA, 0x26, 0xB, 0x2C, 0x24 };
        s32 sfx[8] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };
        s32 choice[2];
        s32 win0; /* DuelHelpWin pointers through ovl_81.h's s32 prototype */
        s32 win1;

        for (i = 0; i < 2; i++) {
            D_80108C20_opdueltutorial[i] = func_800D8010_name_81(partner[GwPlayer[i].chr], (s32 *)D_80108B74_opdueltutorial[GwPlayer[i].chr]);
            HuVecCopy3F(&D_80108C20_opdueltutorial[i]->coords, &D_80108A04_opdueltutorial[i]);
            HuAudFXPlay(sfx[GwPlayer[i].chr]);
        }
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], 0, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], 0, 2);
        while (TRUE) {
            side = func_800EFE8C_name_81(D_80108C20_opdueltutorial[0], &D_80108A1C_opdueltutorial[0], 20.0f);
            if (func_800EFE8C_name_81(D_80108C20_opdueltutorial[1], &D_80108A1C_opdueltutorial[1], 20.0f) != 0 && side != 0) {
                break;
            }
            HuPrcVSleep();
        }
        func_800EB7BC_name_81(&dir[0]);
        func_800EB7BC_name_81(&dir[1]);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[0]->rot, &dir[0], &D_80108C20_opdueltutorial[0]->rot, 10);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[1]->rot, &dir[1], &D_80108C20_opdueltutorial[1]->rot, 10);
        HuPrcSleep(10);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], -1, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], -1, 2);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9481, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
        func_800EB708_name_81(&D_80108C14_opdueltutorial[0]->player_obj->coords, &D_80108C14_opdueltutorial[1]->player_obj->coords, &dir[0]);
        func_800EB708_name_81(&D_80108C14_opdueltutorial[1]->player_obj->coords, &D_80108C14_opdueltutorial[0]->player_obj->coords, &dir[1]);
        func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &dir[0], &D_80108C14_opdueltutorial[0]->player_obj->rot, 5);
        func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &dir[1], &D_80108C14_opdueltutorial[1]->player_obj->rot, 5);
        HuPrcSleep(5);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9482, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
        choice[0] = 0;
        choice[1] = 0;
        win0 = func_800E1824_name_81(0x14, 0xAE, 1);
        win1 = func_800E1824_name_81(0x15, 0xBC, 1);
        HuPrcSleep(20);
        choice[0] = 1;
        choice[1] = 2;
        func_800E1854_name_81(win0);
        func_800E1854_name_81(win1);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], 0, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], 0, 2);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108A34_opdueltutorial[(choice[0] - 1) * 2 + 0], &D_80108C20_opdueltutorial[0]->rot);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[1]->coords, &D_80108A34_opdueltutorial[(choice[1] - 1) * 2 + 1], &D_80108C20_opdueltutorial[1]->rot);
        func_800EBF2C_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108A34_opdueltutorial[(choice[0] - 1) * 2 + 0], &D_80108C20_opdueltutorial[0]->coords, 20);
        func_800EBF2C_name_81(&D_80108C20_opdueltutorial[1]->coords, &D_80108A34_opdueltutorial[(choice[1] - 1) * 2 + 1], &D_80108C20_opdueltutorial[1]->coords, 20);
        HuPrcSleep(20);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108C14_opdueltutorial[1]->player_obj->coords, &dir[0]);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[1]->coords, &D_80108C14_opdueltutorial[0]->player_obj->coords, &dir[1]);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[0]->rot, &dir[0], &D_80108C20_opdueltutorial[0]->rot, 10);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[1]->rot, &dir[1], &D_80108C20_opdueltutorial[1]->rot, 10);
        HuPrcSleep(10);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], -1, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], -1, 2);
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
    /* the starting coins */
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9483, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800F7228_name_81(0, 10, 1);
    func_800F7228_name_81(1, 10, 0);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 4, 0);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    func_800D918C_name_81(D_80108C14_opdueltutorial[0]->player_obj, 0, 0, 5, 2);
    func_800D918C_name_81(D_80108C14_opdueltutorial[1]->player_obj, 0, 0, 5, 2);
    func_8005B43C_main(D_80108C2C_opdueltutorial, 9484, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800610E0_main(D_80108C2C_opdueltutorial);
}

void func_80108774_opdueltutorial(void) {
    func_801062E0_opdueltutorial();
    func_80106BF0_opdueltutorial();
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801087B4_opdueltutorial(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80108908_opdueltutorial();
        func_80108880_opdueltutorial();
        func_8005F524_main();
        if (D_80108930_opdueltutorial != 0) {
            func_800F64FC_name_81();
        }
        omOvlReturnEx(1);
    }
}

void func_80108810_opdueltutorial(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 0x14);
        obj->func = func_801087B4_opdueltutorial;
    }
}

void func_80108854_opdueltutorial(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80108880_opdueltutorial(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
    if (D_80108934_opdueltutorial != NULL) {
        omDelPrcObj(D_80108934_opdueltutorial);
    }
}

void func_801088C4_opdueltutorial(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(30);
}

void func_80108908_opdueltutorial() {
    MBDBackKill();
    MBDBackClose();
}





/* .data */
s32 D_80108930_opdueltutorial = 0;
Process *D_80108934_opdueltutorial = NULL;
Vec D_80108938_opdueltutorial = { -170.0f, 125.0f, 3000.0f };
Vec D_80108944_opdueltutorial[3] = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }; /* only [0] read */
Vec D_80108968_opdueltutorial = { 0.0f, 0.0f, 1500.0f };
Vec D_80108974_opdueltutorial[4] = {
    { -10.0f, 250.0f, 0.0f }, { 10.0f, 250.0f, 0.0f }, { -500.0f, 0.0f, 2360.0f }, { 500.0f, 0.0f, 2360.0f },
}; /* only [0..1] read */
Vec D_801089A4_opdueltutorial[2] = { { -200.0f, 0.0f, 2360.0f }, { 200.0f, 0.0f, 2360.0f } };
Vec D_801089BC_opdueltutorial[4] = {
    { -175.0f, 0.0f, 2250.0f }, { 175.0f, 0.0f, 2250.0f }, { 0.0f, 0.0f, 2150.0f }, { 0.0f, 0.0f, 2350.0f },
}; /* only [0..1] read */
Vec D_801089EC_opdueltutorial[2] = { { -125.0f, 0.0f, 2000.0f }, { 125.0f, 0.0f, 2000.0f } };
Vec D_80108A04_opdueltutorial[2] = { { -750.0f, 0.0f, 1750.0f }, { 750.0f, 0.0f, 1750.0f } };
Vec D_80108A1C_opdueltutorial[2] = { { -100.0f, 0.0f, 1750.0f }, { 100.0f, 0.0f, 1750.0f } };
/* the partners' end points: [(choice - 1) * 2 + player], choice 1 front, 2 back */
Vec D_80108A34_opdueltutorial[4] = {
    { -100.0f, 0.0f, 2000.0f }, { 100.0f, 0.0f, 2000.0f }, { -300.0f, 0.0f, 2000.0f }, { 300.0f, 0.0f, 2000.0f },
};
OtMotList D_80108A64_opdueltutorial = { 5, { 0x20000, 0x20001, 0x20002, 0x20033, 0x20031 } };
OtMotList D_80108A7C_opdueltutorial = { 5, { 0 } };
OtMotList D_80108A94_opdueltutorial = { 5, { 0 } };
OtMotList D_80108AAC_opdueltutorial = { 5, { 0 } };
OtMotList D_80108AC4_opdueltutorial = { 5, { 0 } };
OtMotList D_80108ADC_opdueltutorial = { 5, { 0 } };
OtMotList D_80108AF4_opdueltutorial = { 5, { 0 } };
OtMotList D_80108B0C_opdueltutorial = { 5, { 0 } };
OtMotList *D_80108B24_opdueltutorial[8] = {
    &D_80108A64_opdueltutorial, &D_80108A7C_opdueltutorial, &D_80108A94_opdueltutorial, &D_80108AAC_opdueltutorial,
    &D_80108AC4_opdueltutorial, &D_80108ADC_opdueltutorial, &D_80108AF4_opdueltutorial, &D_80108B0C_opdueltutorial,
};
/* each character's partner model motions (none for 3 and 7) */
OtMotList1 D_80108B44_opdueltutorial = { 1, { 0xA0090 } };
OtMotList1 D_80108B4C_opdueltutorial = { 1, { 0xA00A7 } };
OtMotList1 D_80108B54_opdueltutorial = { 1, { 0xA0002 } };
OtMotList1 D_80108B5C_opdueltutorial = { 1, { 0xA00BD } };
OtMotList1 D_80108B64_opdueltutorial = { 1, { 0xA00D0 } };
OtMotList1 D_80108B6C_opdueltutorial = { 1, { 0xA010F } };
OtMotList1 *D_80108B74_opdueltutorial[8] = {
    &D_80108B44_opdueltutorial, &D_80108B4C_opdueltutorial, &D_80108B54_opdueltutorial, NULL,
    &D_80108B5C_opdueltutorial, &D_80108B64_opdueltutorial, &D_80108B6C_opdueltutorial, NULL,
};
OtMotList1 D_80108B94_opdueltutorial = { 1, { 0xA0125 } }; /* the coin host's motions */
