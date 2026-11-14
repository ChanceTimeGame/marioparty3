
#include "common.h"
#include "game/board.h"
#include "malloc.h"
#include "mallocblock.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/1006F0.h"

extern u16 D_800D530C_main;
void func_800EE700_shared_board(void);
void func_800EE740_shared_board(void);
void func_80108BB0_opboard(omObjData *obj);
void func_80108C8C_opboard(void);
void func_80108D44_opboard(void);


void func_800461B4_main(s16 arg0);
void func_8001C258_main(s16 arg0, s32 arg1, s32 arg2);

extern Vec D_80108D98_opboard;
extern Vec D_80108DD4_opboard[4];
extern Vec D_80108E04_opboard[4];
extern u32 D_80108F14_opboard[2];
extern Object *D_80108F20_opboard;
extern Vec D_80108F44_opboard[];


f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);


extern s32 D_80100D90_shared_board;
extern s32 D_80108D70_opboard;
void func_800DCCE0_shared_board(void);


void func_800138EC_main(s16 model, u16 mask, u16 flags);

extern Vec D_80108D74_opboard[3];
extern Vec D_80108DA4_opboard[4];
extern omObjData *D_80108F3C_opboard;


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

struct ObPath;
void func_80105DC4_opboard(s16 model);
void func_80105F8C_opboard(s32 a, s32 b);
void func_801060A8_opboard(omObjData *obj);
void func_80108B3C_opboard(void);
void func_80108C0C_opboard(omObjData *obj);
void func_80108C58_opboard(void);
void func_80108CC0_opboard(void);
void func_801066F0_opboard(void);
void func_80107E58_opboard(void);
s16 func_80105AE0_opboard(s32 dir, s32 file);
s32 func_80105C60_opboard(s16 model, f32 x, f32 y, f32 z);
void func_80106CFC_opboard(void);
void func_801071F4_opboard(omObjData *obj);
void func_80107580_opboard(struct ObPath *path, f32 t, Vec *out);
void func_80107E28_opboard(struct ObPath *path);

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

/* the opening: players and the board's centre model rise out of the ground, the logo shows,
   then the centre model zooms in under a white wipe */
void func_801066F0_opboard(void) {
    omObjData *obj;
    s32 i;
    f32 scale;
    f32 rise;
    Object *ring;

    for (i = 0; i < 4; i++) {
        D_80109068_opboard[i] = MBPlayerGet(i);
        MBPlayerModelCreate(i, (u32 *)D_80108EF4_opboard[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80109068_opboard[i]->player_obj->coords, &D_80108DA4_opboard[i]);
        MBModelTempAllocFree(D_80109068_opboard[i]->player_obj);
        D_80109068_opboard[i]->stat |= 4;
    }
    D_80108F1C_opboard = MBModelFileCreate(0x1301FE, -1, 1.0f, 0.0f, NULL);
    D_80108F24_opboard = MBModelFileCreate(0x1301FD, -1, 1.0f, 0.0f, NULL);
    HuVecCopy3F(&D_80108F1C_opboard->coords, &D_80108D74_opboard[0]);
    HuVecCopy3F(&D_80108F24_opboard->coords, &D_80108D74_opboard[0]);
    D_80108F24_opboard->coords.y = 0.0f;
    HuVecCopyXYZ(&D_80108F24_opboard->scale, D_80108F24_opboard->coords.y, D_80108F24_opboard->coords.y,
                 D_80108F24_opboard->coords.y);
    D_80108F2C_opboard = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80108F2C_opboard, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(D_80108F2C_opboard, 40.0f);
    func_800138EC_main(D_80108F2C_opboard, 1, 0);
    MBBackTPLvlSet(0x80);
    WipeCreateIn(2, 0x10);
    HuPrcSleep(17);
    D_80108F3C_opboard = omAddObj(0x1000, 0, 0, -1, func_801061FC_opboard);
    HuAudSeqPlay(0x6E);
    func_80106388_opboard();
    for (i = 0x80; i < 0x100; i += 8) {
        MBBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBBackTPLvlSet(0xFF);
    HuAudFXPlay(0x2ED);
    while (D_80108F1C_opboard->coords.y >= 10.0f) {
        D_80108F1C_opboard->coords.y -= 3.0f;
        for (i = 0; i < 4; i++) {
            D_80109068_opboard[i]->player_obj->coords.y -= 3.0f;
        }
        ring = D_80108F24_opboard;
        rise = 1.0f - D_80108F1C_opboard->coords.y / 250.0f;
        HuVecCopyXYZ(&ring->scale, rise, rise, rise);
        HuPrcVSleep();
    }
    obj = D_80108F28_opboard = omAddObj(0x1000, 0, 0, -1, func_801062CC_opboard);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = D_80108F1C_opboard->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(D_80108F2C_opboard, D_80108F1C_opboard->coords.x, D_80108F1C_opboard->coords.y + 40.0f,
                       D_80108F1C_opboard->coords.z);
    func_800138EC_main(D_80108F2C_opboard, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 4; i++) {
            HuVecCopyXYZ(&D_80109068_opboard[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(D_80109068_opboard[i]->player_obj);
    }
    func_800138EC_main(D_80108F2C_opboard, 1, 0);
    HuPrcSleep(20);
    if (D_80108F40_opboard != 0) {
        HuPrcSleep(-1);
    } else {
        omDelObj(D_80108F3C_opboard);
        D_80108F3C_opboard = NULL;
    }
    for (i = 0, scale = 1.0f; scale < 10.0f; scale += 0.5f, i++) {
        HuVecCopyXYZ(&D_80108F1C_opboard->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x10);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(D_80108F2C_opboard);
    D_80108F2C_opboard = -1;
    MBModelKill(D_80108F1C_opboard);
    D_80108F1C_opboard = NULL;
    MBModelKill(D_80108F24_opboard);
    D_80108F24_opboard = NULL;
    omDelObj(D_80108F28_opboard);
    D_80108F28_opboard = NULL;
    omDelPrcObj(NULL);
}

// register allocation and store order in the roll sort (masked 0)
#ifdef NON_MATCHING
/* deciding the turn order: each player hits a dice block (A, or a random delay for CPUs),
   the highest roll goes first; then each player is introduced in the new order */
void func_80106CFC_opboard(void) {
    s32 state[4];
    s32 count[4];
    s32 timer[4];
    s32 order[4];
    Unk3 *help;
    s32 i;
    s32 j;
    s32 tmp;

    func_800DB5DC_shared_board();
    func_800DB56C_shared_board();
    for (i = 0; i < 4; i++) {
        if (i != 0) {
            D_80100D90_shared_board = 0;
        }
        func_800DC128_shared_board(i);
        func_800DB6A8_shared_board(i);
    }
    func_800DCCE0_shared_board();
    HuPrcSleep(20);
    help = func_800E210C_shared_board(2, 0xBE, 1);
    for (i = 0; i < 4; i++) {
        state[i] = 1;
        count[i] = 0;
        timer[i] = (u8)(rand8() % 30) + 5;
    }
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            tmp = timer[i] - 1;
            timer[i] = tmp;
            if (state[i] == 1) {
                if (GwPlayer[i].stat & 1) {
                    if (tmp <= 0) {
                        goto hit;
                    }
                } else if (D_800C9520_main[GwPlayer[i].pad] & 0x8000) {
                hit:
                    state[i] = 2;
                    MBMotionSet(D_80109068_opboard[i]->player_obj, 2, 0);
                    func_800EE884_shared_board(D_80109068_opboard[i]->player_obj, -1, 2);
                }
            } else if (state[i] == 2) {
                if (++count[i] == 5) {
                    func_800DCBCC_shared_board(i);
                    state[i] = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (state[i] != 0) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        HuPrcVSleep();
    }
    MBHelpWinKill(help);
    HuPrcSleep(20);
    for (i = 0; i < 4; i++) {
        state[i] = func_800DCD9C_shared_board(i);
        order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if (state[i] < state[j]) {
                tmp = state[j];
                state[j] = state[i];
                state[i] = tmp;
                tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[order[i]].turn = i;
        func_800DBE6C_shared_board(i);
    }
    func_80106014_opboard();
    func_800F453C_shared_board();
    D_80108D70_opboard = 1;
    for (i = 0; i < 4; i++) {
        MBStatusDispSideSet(i, 1);
    }
    HuPrcSleep(5);
    for (i = 0; i < 4; i++) {
        s32 mes[4] = { 0x1812, 0x1813, 0x1814, 0x1815 };

        MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
        func_800EC92C_shared_board(-1, mes[i], mbCharNameMesTbl[GwPlayer[i].chr], 0, 0, 0, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
        func_8004ACE0_main(0x274, i);
        func_800EE94C_shared_board(D_80109068_opboard[i]->player_obj, 3, 0);
        func_800EE884_shared_board(D_80109068_opboard[i]->player_obj, -1, 2);
        func_800DBEC0_shared_board(order[i]);
        MBStatusDispMoveSet(i + 10);
        while (func_800F5278_shared_board() != 0) {
            HuPrcVSleep();
        }
        MBPlayerVibrate(i, 3);
        HuPrcSleep(20);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80106CFC_opboard);
INCLUDE_RODATA("asm/nonmatchings/overlays/opboard/3CA800", D_80108FB0_opboard);
#endif

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). */
typedef struct ObPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} ObPathSeg; /* size = 0x8 */

typedef struct ObPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ ObPathSeg *segs;
} ObPath; /* size = 0x10 */

/* sways the board's centre model */
void func_801071F4_opboard(omObjData *obj) {
    D_80108F1C_opboard->velocity.x = sindf(obj->rot.x) * 20.0f + obj->rot.y;
    obj->rot.x += 5.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

ObPath *func_8010727C_opboard(Vec *points, s16 flags) {
    ObPath *path;
    Vec *prev;
    Vec *cur;
    ObPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(ObPath), 0x7918);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    n = 0;
    while (cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
        n++;
        cur++;
        prev++;
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    n++;
    path->count = n;
    seg = HuMemAllocTag(n * sizeof(ObPathSeg), 0x7918);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    pos = 0.0f;
    for (i = 0; i < n; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == n - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = pos / total;
        seg->end = (pos + len) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        pos += len;
    }
    return path;
}

// register allocation in the closed-path neighbour loads (masked 3)
#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_80107580_opboard(ObPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    ObPathSeg *segs;
    Vec *pts;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    for (i = 0, segs = path->segs; i < path->count; i++, segs++) {
        if (t <= segs->start) {
            break;
        }
    }
    i--;
    i = (i < 0) ? 0 : i;
    if (i >= path->count - 1) {
        i--;
    }
    segs = path->segs;
    if (path->flags & 1) {
        times[0] = (i == 0) ? -(1.0f - segs[path->count - 1].start) : segs[i - 1].start;
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[path->count - 1].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[0].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[0].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[0].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].z : pts[i + 2].z;
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = segs[i - 1].start;
        }
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[0].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].z : pts[i + 2].z;
    }
    out->z = func_80018ACC_main(p, times, t);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opboard/3CA800", func_80107580_opboard);
#endif

void func_80107E28_opboard(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

void func_80107E58_opboard(void) {
    s32 backs[6] = { 4, 7, 10, 13, 16, 19 };
    Vec dirs[4];
    s16 fx[4];
    omObjData *sway;
    ObPath *path;
    s16 trail;
    s32 i;
    s32 n;
    f32 scale;
    f32 t;

    MBBackKill();
    MBBackLoad(backs[GwSystem.current_board_index]);
    func_800E9344_shared_board(1000.0f, 10000.0f);
    D_80108F1C_opboard = MBModelCreate(0x3A, D_80108F14_opboard);
    func_800461B4_main(D_80108F1C_opboard->omObj1->model[0]);
    HuVecCopy3F(&D_80108F1C_opboard->coords, &D_80108D98_opboard);
    D_80108F1C_opboard->velocity.x = 1000.0f;
    D_80108F2C_opboard = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80108F2C_opboard, 10.0f, 20.0f, 10.0f);
    func_8000D018_main(D_80108F2C_opboard, 300.0f);
    func_800138EC_main(D_80108F2C_opboard, 1, 0);
    for (i = 0; i < 4; i++) {
        HuVecCopy3F(&D_80109068_opboard[i]->player_obj->coords, &D_80108DD4_opboard[i]);
        fx[i] = func_80105AE0_opboard(0xB0004, 0x689);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (n = 0; n < 20; n++) {
        for (i = 0; i < 4; i++) {
            func_80105C60_opboard(fx[i], D_80109068_opboard[i]->player_obj->coords.x,
                                  D_80109068_opboard[i]->player_obj->coords.y + 50.0f,
                                  D_80109068_opboard[i]->player_obj->coords.z);
            if (n == 0) {
                MBPlayerVibrate(i, 1);
            }
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 4; i++) {
            MBModelDispOn(D_80109068_opboard[i]->player_obj);
            HuVecCopyXYZ(&D_80109068_opboard[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuVecCopyXYZ(&D_80109068_opboard[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    func_800138EC_main(D_80108F2C_opboard, 1, 0);
    HuPrcSleep(20);
    func_8000CD00_main(D_80108F2C_opboard, 10.0f, 20.0f, 15.0f);
    func_8000D018_main(D_80108F2C_opboard, 300.0f);
    func_800138EC_main(D_80108F2C_opboard, 0, 1);
    HuAudFXPlay(0x157);
    n = 0;
    while (D_80108F1C_opboard->velocity.x >= 400.0f) {
        D_80108F1C_opboard->velocity.x -= 10.0f;
        n++;
        func_8000CFA4_main(D_80108F2C_opboard, D_80108F1C_opboard->coords.x, D_80108F1C_opboard->velocity.x - 100.0f,
                           D_80108F1C_opboard->coords.z);
        if (n == 20) {
            for (i = 0; i < 4; i++) {
                MBVecDirGet(&D_80109068_opboard[i]->player_obj->coords, &D_80108E04_opboard[i],
                            &D_80109068_opboard[i]->player_obj->rot);
                MBPlayerPosMoveCreate(&D_80109068_opboard[i]->player_obj->coords, &D_80108E04_opboard[i],
                                      &D_80109068_opboard[i]->player_obj->coords, 20);
                MBMotionSet(D_80109068_opboard[i]->player_obj, 1, 2);
            }
        }
        if (n == 40) {
            for (i = 0; i < 4; i++) {
                MBVecDirGet(&D_80109068_opboard[i]->player_obj->coords, &D_80108F1C_opboard->coords, &dirs[i]);
                func_800ED128_shared_board(&D_80109068_opboard[i]->player_obj->rot, &dirs[i],
                                           &D_80109068_opboard[i]->player_obj->rot, 10);
                MBMotionShiftSet(D_80109068_opboard[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    sway = omAddObj(0x1000, 0, 0, -1, func_801071F4_opboard);
    sway->rot.y = D_80108F1C_opboard->velocity.x;
    sway->rot.x = 180.0f;
    HuAudSeqPlay(0xD);
    HuAudFXPlay(0x159);
    if (GwSystem.playMode & 4) {
        s32 mes[6] = { 0x1800, 0x1802, 0x1804, 0x1806, 0x1808, 0x180A };

        MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
        func_800EC92C_shared_board(-1, mes[GwSystem.current_board_index], mbCharNameMesTbl[GwStory.unk1], 0, 0, 0, 0);
        func_800ECA38_shared_board();
        func_800ECA38_shared_board();
        if (GwSystem.current_board_index == 5) {
            func_800ECA38_shared_board();
        }
        MBDlgWinClose();
        MBDlgWinKill();
        MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
        {
            s32 models[6] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006, 0x1D0007, 0x1D0008 };

            if (GwSystem.current_board_index != 5) {
                Vec pos;
                s32 k;

                D_80108F20_opboard = MBModelFileCreate(models[GwSystem.current_board_index], -1, 1.0f, 0.0f, NULL);
                path = func_8010727C_opboard(D_80108F44_opboard, 0);
                trail = func_8000CED8_main(0xB0004, 0x6A9);
                func_8000CD00_main(trail, 4.0f, 20.0f, 4.0f);
                func_8000D018_main(trail, 60.0f);
                func_800138EC_main(trail, 1, 1);
                func_8001C258_main(trail, 4, 0);
                HuAudFXPlay(0x215);
                for (k = 0; k < 50; k++) {
                    t = k * 0.02f;
                    func_80107580_opboard(path, t * t, &pos);
                    HuVecCopy3F(&D_80108F20_opboard->coords, &pos);
                    func_8000CFA4_main(trail, pos.x, pos.y - 50.0f, pos.z);
                    HuPrcVSleep();
                }
                func_80107E28_opboard(path);
            }
            {
                s32 mes[6] = { 0x1801, 0x1803, 0x1805, 0x1807, 0x1809, 0x180B };

                if (GwSystem.current_board_index != 5) {
                    MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
                    func_800EC92C_shared_board(-1, mes[GwSystem.current_board_index], 0, 0, 0, 0, 0);
                    func_800ECA38_shared_board();
                    MBDlgWinClose();
                    MBDlgWinKill();
                    MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
                }
            }
        }
    } else {
        {
            s32 mes[6] = { 0x180C, 0x180D, 0x180E, 0x180F, 0x1810, 0x1811 };

            MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
            func_800EC92C_shared_board(-1, mes[GwSystem.current_board_index], 0, 0, 0, 0, 0);
            func_800ECA38_shared_board();
            func_800ECA38_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
        }
    }
    for (i = 0; i < 4; i++) {
        MBVecDirGet(&D_80109068_opboard[i]->player_obj->coords, &D_80108DD4_opboard[i],
                    &D_80109068_opboard[i]->player_obj->rot);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&D_80109068_opboard[i]->player_obj->coords, &D_80108DD4_opboard[i],
                                             &D_80109068_opboard[i]->player_obj->coords, 20));
        MBMotionSet(D_80109068_opboard[i]->player_obj, 1, 2);
    }
    HuPrcChildWait();
    for (i = 0; i < 4; i++) {
        f32 angles[4] = { 5.0f, 0.0f, 0.0f, -5.0f };

        dirs[i].x = sindf(angles[i]);
        dirs[i].z = cosdf(angles[i]);
        dirs[i].y = 0.0f;
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_80109068_opboard[i]->player_obj->rot, &dirs[i],
                                                                     &D_80109068_opboard[i]->player_obj->rot, 10));
        MBMotionShiftSet(D_80109068_opboard[i]->player_obj, -1, 0, 5, 2);
    }
    HuPrcChildWait();
    func_80106CFC_opboard();
    MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
    func_800EC92C_shared_board(-1, 0x1816, 0, 0, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            MBCoinTakeCreate(0, 10);
        } else {
            MBCoinTakeCreateSound(i, 10, 0);
        }
        func_800EE94C_shared_board(D_80109068_opboard[i]->player_obj, 4, 0);
    }
    HuPrcSleep(60);
    for (i = 0; i < 4; i++) {
        func_800EE94C_shared_board(D_80109068_opboard[i]->player_obj, -1, 2);
    }
    MBMotionShiftSet(D_80108F1C_opboard, 0, 0, 5, 2);
    func_800EC92C_shared_board(-1, 0x1817, 0, 0, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MBMotionShiftSet(D_80108F1C_opboard, -1, 0, 5, 2);
    func_8000D044_main(D_80108F2C_opboard);
}

/* the overlay's main process */
void func_80108B3C_opboard(void) {
    D_80108F30_opboard = omAddPrcObj(func_801066F0_opboard, 0x300, 0x2000, 0);
    HuPrcChildLink(HuPrcCurrentGet(), D_80108F30_opboard);
    HuPrcChildWait();
    func_80107E58_opboard();
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80108BB0_opboard(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80108D44_opboard();
        func_80108C8C_opboard();
        func_8005F524_main();
        if (D_80108D70_opboard != 0) {
            func_800F4730_shared_board();
        }
        omOvlReturnEx(1);
    }
}

void func_80108C0C_opboard(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 0x14);
        HuAudSeqFadeOut(0x3C);
        obj->func = func_80108BB0_opboard;
    }
}

void func_80108C58_opboard(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
    func_800F2A20_shared_board();
}

void func_80108C8C_opboard(void) {
    func_800F2A34_shared_board();
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}










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

/* .data */
s32 D_80108D70_opboard = 0; /* set once the turn order is decided: the exit starts the status display */
Vec D_80108D74_opboard[3] = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }; /* only [0] read */
Vec D_80108D98_opboard = { 0.0f, 0.0f, 1750.0f };
Vec D_80108DA4_opboard[4] = {
    { -18.0f, 250.0f, 0.0f }, { -6.0f, 250.0f, 0.0f }, { 6.0f, 250.0f, 0.0f }, { 18.0f, 250.0f, 0.0f },
};
Vec D_80108DD4_opboard[4] = {
    { -300.0f, 0.0f, 2000.0f }, { -100.0f, 0.0f, 2000.0f }, { 100.0f, 0.0f, 2000.0f }, { 300.0f, 0.0f, 2000.0f },
};
Vec D_80108E04_opboard[4] = {
    { -300.0f, 0.0f, 2250.0f }, { -125.0f, 0.0f, 2450.0f }, { 125.0f, 0.0f, 2450.0f }, { 300.0f, 0.0f, 2250.0f },
};
ObMotList D_80108E34_opboard = { 5, { 0x20001, 0x20002, 0x2002B, 0x20033, 0x20031 } };
ObMotList D_80108E4C_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108E64_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108E7C_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108E94_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108EAC_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108EC4_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList D_80108EDC_opboard = { 5, { 0, 0, 0, 0, 0 } };
ObMotList *D_80108EF4_opboard[8] = {
    &D_80108E34_opboard, &D_80108E4C_opboard, &D_80108E64_opboard, &D_80108E7C_opboard,
    &D_80108E94_opboard, &D_80108EAC_opboard, &D_80108EC4_opboard, &D_80108EDC_opboard,
};
u32 D_80108F14_opboard[2] = { 1, 0xA0125 }; /* MBModelCreate's file list: count, then file ids */
Object *D_80108F1C_opboard = NULL; /* the board's centre (host) model */
Object *D_80108F20_opboard = NULL; /* story mode: the model flown in along D_80108F44_opboard */
Object *D_80108F24_opboard = NULL; /* the ring under the centre model */
omObjData *D_80108F28_opboard = NULL;
s16 D_80108F2C_opboard = -1; /* effect model, -1 none */
Process *D_80108F30_opboard = NULL;
UnkBoard8 *D_80108F34_opboard = NULL;
UnkBoard8 *D_80108F38_opboard = NULL;
omObjData *D_80108F3C_opboard = NULL;
s32 D_80108F40_opboard = 0; /* the opening was skipped */
Vec D_80108F44_opboard[4] = {
    { 0.0f, 400.0f, 1750.0f }, { -200.0f, 300.0f, 1550.0f }, { -100.0f, 480.0f, 1950.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
