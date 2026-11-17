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
s32 func_800E1854_minigame(s32 id);
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
void func_80106808_opdueltutorial(Object *host);
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
extern Vec D_80108968_opdueltutorial;
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

extern u8 D_80108C10_opdueltutorial;
extern GW_PLAYER *D_80108C14_opdueltutorial[2];
extern Object *D_80108C1C_opdueltutorial; /* the board's centre model */
extern Object *D_80108C20_opdueltutorial[2];
extern Object *D_80108C28_opdueltutorial; /* the host model */
extern s16 D_80108C2C_opdueltutorial; /* the host's message window */
extern s16 D_80108C30_opdueltutorial[10]; /* the host's texture animations */
extern s16 D_80108C44_opdueltutorial;
extern s16 D_80108C46_opdueltutorial; /* texture-animation slot, 0xFF none */


INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_801059A0_opdueltutorial);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_801062E0_opdueltutorial);

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_80106808_opdueltutorial);

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_8010686C_opdueltutorial);

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_80106BF0_opdueltutorial);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_80108854_opdueltutorial);

INCLUDE_ASM("asm/nonmatchings/overlays/opdueltutorial/464360", func_80108880_opdueltutorial);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/opdueltutorial/464360", D_80108BBC_opdueltutorial);

INCLUDE_RODATA("asm/nonmatchings/overlays/opdueltutorial/464360", D_80108BC4_opdueltutorial);

INCLUDE_RODATA("asm/nonmatchings/overlays/opdueltutorial/464360", D_80108BE4_opdueltutorial);

INCLUDE_RODATA("asm/nonmatchings/overlays/opdueltutorial/464360", D_80108C08_opdueltutorial);
