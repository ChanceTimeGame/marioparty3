#include "common.h"
#include "../ovl_80_shared_board/FA250.h"

#include "common.h"
#include "game/board.h"
#include "malloc.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106640.h"

/* opboard (0x53): the board's opening. */

/* A list of motion file ids (count, then ids); D_80108EF4_opboard[chr] points at one per
   character: [0] holds the template file ids, [1..7] get each character's ids from
   func_80017BB8_main at init. */
typedef struct ObMotList {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[5];
} ObMotList; /* size = 0x18 */

/* The ring-of-sparks particle effect of a model (HmfModelData[model].unkBC; msetup's MsFxWork,
   13F90.c HmfFxWork): one ObFxPart per face group. */
typedef struct ObFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 phase; /* 0..180 while live, >= 180 idle */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ f32 angle;
    /* 0x1C */ f32 radiusStep;
    /* 0x20 */ f32 radius;
    /* 0x24 */ Vec vel; /* x = angle step, y/z = height/radius factors */
} ObFxPart; /* size = 0x30 */

typedef struct ObFxWork {
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
    /* 0x58 */ ObFxPart *parts;
} ObFxWork; /* size = 0x5C */

typedef struct ObFxHmf { /* HmfData's face group count (hmfman.h does not name it) */
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} ObFxHmf;

void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
s32 func_80017BB8_main(s16, s16);
void func_80007EC0_main(s32);

void func_80105DC4_opboard(s16 model);
void func_80105F8C_opboard(s32 a, s32 b);
void func_801060A8_opboard(omObjData *obj);
void func_80108B3C_opboard(void);
void func_80108C0C_opboard(omObjData *obj);
void func_80108C58_opboard(void);
void func_80108CC0_opboard(void);

extern ObMotList D_80108E34_opboard;
extern ObMotList *D_80108EF4_opboard[8];
extern Object *D_80108F1C_opboard;
extern Object *D_80108F24_opboard;
extern omObjData *D_80108F28_opboard;
extern s16 D_80108F2C_opboard;
extern Process *D_80108F30_opboard;
extern UnkBoard8 *D_80108F34_opboard;
extern UnkBoard8 *D_80108F38_opboard;
extern s32 D_80108F40_opboard;
extern u8 D_80109060_opboard;
extern GW_PLAYER *D_80109068_opboard[];


void func_801059A0_opboard(void) {
    s32 i;
    u32 j;

    D_80109060_opboard = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_80108CC0_opboard();
    func_80108C58_opboard();
    func_800D95C4_shared_board(1000.0f);
    func_8005A6B0_main();
    omAddPrcObj(func_80108B3C_opboard, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80108C0C_opboard);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80108E34_opboard.count; j++) {
            D_80108EF4_opboard[i]->ids[j] = func_80017BB8_main(i, D_80108E34_opboard.ids[j]);
        }
    }
    func_8004A208_main();
}

s16 func_80105AE0_opboard(s32 dir, s32 file) {
    ObFxHmf *hmf;
    ObFxWork *work;
    ObFxPart *part;
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
    func_80013390_main(model, -1, NULL, func_80105DC4_opboard);
    hmf = (ObFxHmf *)HmfModelData[model].hmf;
    work = (ObFxWork *)HmfModelData[model].unkBC;
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

s32 func_80105C60_opboard(s16 model, f32 x, f32 y, f32 z) {
    ObFxHmf *hmf;
    ObFxWork *work;
    ObFxPart *part;
    s16 i;
    f32 tilt;

    hmf = (ObFxHmf *)HmfModelData[model].hmf;
    work = (ObFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->phase >= 180.0f) {
            part->angle = MBRand(360.0f);
            part->radius = work->unk10 / 10.0f;
            tilt = MBRand(150.0f);
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

void func_80105DC4_opboard(s16 model) {
    ObFxHmf *hmf;
    ObFxWork *work;
    ObFxPart *part;
    s16 i;
    s16 count;
    f32 r;

    hmf = (ObFxHmf *)HmfModelData[model].hmf;
    work = (ObFxWork *)HmfModelData[model].unkBC;
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

void func_80105F8C_opboard(s32 a, s32 b) {
    GW_PLAYER *pa;
    GW_PLAYER *pb;
    void *tmp;

    pa = MBPlayerGet(a);
    pb = MBPlayerGet(b);
    tmp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));
    bcopy(pa, tmp, sizeof(GW_PLAYER));
    bcopy(pb, pa, sizeof(GW_PLAYER));
    bcopy(tmp, pb, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(tmp);
}

/* sorts the players by turn order */
void func_80106014_opboard(void) {
    s32 i;
    s32 j;

    for (i = 3; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (GwPlayer[j].turn > GwPlayer[j + 1].turn) {
                func_80105F8C_opboard(j, j + 1);
            }
        }
    }
}

void func_801060A8_opboard(omObjData *obj) {
    s32 i;

    if (WipeStatGet() == 0) {
        if (D_80108F2C_opboard != -1) {
            func_8000D044_main(D_80108F2C_opboard);
            D_80108F2C_opboard = -1;
        }
        if (D_80108F1C_opboard != NULL) {
            MBModelKill(D_80108F1C_opboard);
            D_80108F1C_opboard = NULL;
        }
        if (D_80108F24_opboard != NULL) {
            MBModelKill(D_80108F24_opboard);
            D_80108F24_opboard = NULL;
        }
        if (D_80108F28_opboard != NULL) {
            omDelObj(D_80108F28_opboard);
            D_80108F28_opboard = NULL;
        }
        if (D_80108F30_opboard != NULL) {
            omDelPrcObj(D_80108F30_opboard);
            D_80108F30_opboard = NULL;
        }
        if (D_80108F34_opboard != NULL) {
            func_800F2CA4_shared_board(D_80108F34_opboard);
            D_80108F34_opboard = NULL;
        }
        if (D_80108F38_opboard != NULL) {
            func_800F2CA4_shared_board(D_80108F38_opboard);
            D_80108F38_opboard = NULL;
        }
        for (i = 0; i < 4; i++) {
            MBModelDispOff(D_80109068_opboard[i]->player_obj);
        }
        omDelObj(obj);
    }
}

/* any human player pressing START skips the opening */
void func_801061FC_opboard(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & 1) && (D_800C9520_main[GwPlayer[i].pad] & 0x1000)) {
            break;
        }
    }
    if (i != 4) {
        D_80108F40_opboard = 1;
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(0xB, 0x10);
        HuAudSeqFadeOut(0x20);
        func_80007EC0_main(0x20);
        obj->func = func_801060A8_opboard;
    }
}

/* bobs the board's centre model and the four player models with it */
void func_801062CC_opboard(omObjData *obj) {
    s32 i;

    D_80108F1C_opboard->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 4; i++) {
        D_80109068_opboard[i]->player_obj->coords.y = D_80108F1C_opboard->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* the board's logo: drops in with a wobble, then its subtitle */
void func_80106388_opboard(void) {
    s32 logo[6] = { 0x130016, 0x130017, 0x130018, 0x130019, 0x13001A, 0x13001B };
    s32 subtitle[6] = { 0x13001C, 0x13001D, 0x13001E, 0x13001F, 0x130020, 0x130021 };
    void *data;
    f32 amp;
    f32 angle;

    HuPrcSleep(10);
    D_80108F34_opboard = func_800F2C48_shared_board(1, 0);
    data = DataRead(logo[GwSystem.current_board_index]);
    D_80108F34_opboard->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108F34_opboard->spriteGroup, 0, D_80108F34_opboard->model[0], 0);
    HuSprPriSet(D_80108F34_opboard->spriteGroup, 0, 10);
    HuSprAttrSet(D_80108F34_opboard->spriteGroup, 0, 0);
    func_80054904_main(D_80108F34_opboard->spriteGroup, 0, 160, 100);
    HuSprScaleSet(D_80108F34_opboard->spriteGroup, 0, 0.0f, 0.0f);
    for (amp = 0.5f, angle = 0.0f; angle <= 720.0f; angle += 45.0f) {
        HuSprScaleSet(D_80108F34_opboard->spriteGroup, 0, sindf(angle) * amp + 1.0f, sindf(angle) * amp + 1.0f);
        amp -= 0.03125f;
        if (amp < 0.0f) {
            amp = 0.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuSprScaleSet(D_80108F34_opboard->spriteGroup, 0, 1.0f, 1.0f);
    D_80108F38_opboard = func_800F2C48_shared_board(1, 0);
    data = DataRead(subtitle[GwSystem.current_board_index]);
    D_80108F38_opboard->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108F38_opboard->spriteGroup, 0, D_80108F38_opboard->model[0], 0);
    HuSprPriSet(D_80108F38_opboard->spriteGroup, 0, 9);
    HuSprAttrSet(D_80108F38_opboard->spriteGroup, 0, 0);
    func_80054904_main(D_80108F38_opboard->spriteGroup, 0, 160, 70);
    HuPrcSleep(75);
    func_800F2CA4_shared_board(D_80108F38_opboard);
    func_800F2CA4_shared_board(D_80108F34_opboard);
    D_80108F38_opboard = NULL;
    D_80108F34_opboard = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_801066F0_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80106CFC_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_801071F4_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_8010727C_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80107580_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80107E28_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80107E58_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80108B3C_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80108BB0_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80108C0C_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80108C58_opboard);

INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80108C8C_opboard);



INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80108FB0_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80108FC0_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80108FD8_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80108FF0_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80109008_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80109020_opboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80109038_opboard);

void func_80108CC0_opboard(void) {
    s32 sp10[] = { 3, 6, 9, 0xC, 0xF, 0x12 };

    Hu3DCamInit(1);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(sp10[GwSystem.current_board_index]);
}

void func_80108D44_opboard() {
    MBBackKill();
    MBBackClose();
}
