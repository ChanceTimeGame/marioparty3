#include "common.h"
#include "game/board.h"
#include "malloc.h"
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

// board t1
/* opboardtutorial (0x54): the tutorial board's opening (the party-mode opening opboard, with a
   host model introducing the players and a scripted turn-order roll). */

/* A list of motion file ids (count, then ids); D_80107720_opboardtutorial[chr] points at one per
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

extern u16 D_800D530C_main;
extern s32 D_80100D90_shared_board;
extern OtTexAnimSlot *D_800D1714_main;
void func_800EE700_shared_board(void);
void func_800EE740_shared_board(void);
void func_800DCCE0_shared_board(void);
void func_800DCD64_shared_board(s32 player, s32 roll);
void func_800EE614_shared_board(s16 win);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800461B4_main(s16 arg0);
void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
s32 func_80017BB8_main(s16, s16);
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);

void func_80105DE0_opboardtutorial(s16 model);
void func_80106254_opboardtutorial(void);
void func_801062E8_opboardtutorial(omObjData *obj);
void func_801063A4_opboardtutorial(void);
void func_801068E4_opboardtutorial(Object *host);
void func_80106990_opboardtutorial(void);
void func_80106F40_opboardtutorial(void);
void func_80107408_opboardtutorial(void);
void func_80107448_opboardtutorial(omObjData *obj);
void func_801074A4_opboardtutorial(omObjData *obj);
void func_801074E8_opboardtutorial(void);
void func_8010751C_opboardtutorial(void);
void func_80107550_opboardtutorial(void);
void func_80107594_opboardtutorial(void);

extern s32 D_801075C0_opboardtutorial;
extern Vec D_801075C4_opboardtutorial;
extern Vec D_801075D0_opboardtutorial[3];
extern Vec D_801075F4_opboardtutorial;
extern Vec D_80107600_opboardtutorial[4];
extern Vec D_80107630_opboardtutorial[4];
extern OtMotList D_80107660_opboardtutorial;
extern OtMotList *D_80107720_opboardtutorial[8];
extern u8 D_80107760_opboardtutorial;
extern Object *D_80107764_opboardtutorial; /* the host model */
extern s16 D_80107768_opboardtutorial; /* the host's message window */
extern s16 D_80107770_opboardtutorial[10]; /* the host's texture animations */
extern s16 D_80107784_opboardtutorial;
extern s16 D_80107786_opboardtutorial; /* texture-animation slot, 0xFF none */
extern GW_PLAYER *D_80107788_opboardtutorial[4];
extern Object *D_80107798_opboardtutorial; /* the board's centre model */

void func_801059A0_opboardtutorial(void) {
    s32 i;
    u32 j;

    D_80107760_opboardtutorial = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_80107550_opboardtutorial();
    func_801074E8_opboardtutorial();
    func_800D95C4_shared_board(1000.0f);
    func_8005A6B0_main();
    omAddPrcObj(func_80107408_opboardtutorial, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801074A4_opboardtutorial);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80107660_opboardtutorial.count; j++) {
            D_80107720_opboardtutorial[i]->ids[j] = func_80017BB8_main(i, D_80107660_opboardtutorial.ids[j]);
        }
    }
    GwPlayer[0].chr = 3;
    GwPlayer[1].chr = 2;
    GwPlayer[2].chr = 0;
    GwPlayer[3].chr = 4;
    func_8004A208_main();
}

s16 func_80105AFC_opboardtutorial(s32 dir, s32 file) {
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
    func_80013390_main(model, -1, NULL, func_80105DE0_opboardtutorial);
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

s32 func_80105C7C_opboardtutorial(s16 model, f32 x, f32 y, f32 z) {
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

void func_80105DE0_opboardtutorial(s16 model) {
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

/* Loads texture animation file `file` (texture `name`) onto model `model` and starts it; returns
   its first frame (14EA0.c func_80017790_main without the per-character slots). */
s16 func_80105FA8_opboardtutorial(s16 model, s32 file, char *name) {
    void *data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80107784_opboardtutorial = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].frame;
    D_80107786_opboardtutorial = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

/* Pauses (frame -1) or restarts at `frame` the host's texture animation
   (14EA0.c func_80017954_main). */
void func_801060B4_opboardtutorial(s16 model, s16 frame) {
    OtTexAnimSlot *p;

    if (D_80107786_opboardtutorial != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80107786_opboardtutorial];
        p->frame = frame;
        p->unk04 = 0;
        p->unk0A = 0;
        p->unk06 = 0;
        p->unk02 = 0;
    }
}

/* Loads sprite bank file `file` (14EA0.c func_80017AD8_main). */
s16 func_80106184_opboardtutorial(s32 file) {
    void *data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}

void func_801061CC_opboardtutorial(s32 a, s32 b) {
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
void func_80106254_opboardtutorial(void) {
    s32 i;
    s32 j;

    for (i = 3; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (GwPlayer[j].turn > GwPlayer[j + 1].turn) {
                func_801061CC_opboardtutorial(j, j + 1);
            }
        }
    }
}

/* bobs the board's centre model and the four player models with it */
void func_801062E8_opboardtutorial(omObjData *obj) {
    s32 i;

    D_80107798_opboardtutorial->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 4; i++) {
        D_80107788_opboardtutorial[i]->player_obj->coords.y = D_80107798_opboardtutorial->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* the opening: players and the board's centre model rise out of the ground, then the centre
   model zooms in under a white wipe */
void func_801063A4_opboardtutorial(void) {
    omObjData *obj;
    Object *ring;
    s16 effect;
    s32 i;
    f32 scale;
    f32 rise;

    for (i = 0; i < 4; i++) {
        D_80107788_opboardtutorial[i] = MBPlayerGet(i);
        MBPlayerModelCreate(i, (u32 *)D_80107720_opboardtutorial[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80107788_opboardtutorial[i]->player_obj->coords, &D_80107600_opboardtutorial[i]);
        MBModelTempAllocFree(D_80107788_opboardtutorial[i]->player_obj);
        D_80107788_opboardtutorial[i]->stat |= 4;
    }
    D_80107798_opboardtutorial = MBModelFileCreate(0x1301FE, -1, 1.0f, 0.0f, NULL);
    ring = MBModelFileCreate(0x1301FD, -1, 1.0f, 0.0f, NULL);
    HuVecCopy3F(&D_80107798_opboardtutorial->coords, &D_801075D0_opboardtutorial[0]);
    HuVecCopy3F(&ring->coords, &D_801075D0_opboardtutorial[0]);
    ring->coords.y = 0.0f;
    HuVecCopyXYZ(&ring->scale, ring->coords.y, ring->coords.y, ring->coords.y);
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 40.0f);
    func_800138EC_main(effect, 1, 0);
    MBBackTPLvlSet(0x80);
    WipeCreateIn(2, 0x10);
    HuPrcSleep(17);
    for (i = 0x80; i < 0x100; i += 8) {
        MBBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBBackTPLvlSet(0xFF);
    HuAudFXPlay(0x2ED);
    while (D_80107798_opboardtutorial->coords.y >= 10.0f) {
        D_80107798_opboardtutorial->coords.y -= 3.0f;
        for (i = 0; i < 4; i++) {
            D_80107788_opboardtutorial[i]->player_obj->coords.y -= 3.0f;
        }
        rise = 1.0f - D_80107798_opboardtutorial->coords.y / 250.0f;
        HuVecCopyXYZ(&ring->scale, rise, rise, rise);
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_801062E8_opboardtutorial);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = D_80107798_opboardtutorial->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(effect, D_80107798_opboardtutorial->coords.x, D_80107798_opboardtutorial->coords.y + 40.0f,
                       D_80107798_opboardtutorial->coords.z);
    func_800138EC_main(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 4; i++) {
            HuVecCopyXYZ(&D_80107788_opboardtutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(D_80107788_opboardtutorial[i]->player_obj);
    }
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; scale += 0.5f, i++) {
        HuVecCopyXYZ(&D_80107798_opboardtutorial->scale, scale, scale, scale);
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
    MBModelKill(D_80107798_opboardtutorial);
    MBModelKill(ring);
    omDelObj(obj);
}

/* the host hops: a short upward velocity, then a new message window */
void func_801068E4_opboardtutorial(Object *host) {
    HuPrcSleep(5);
    host->velocity.y = 20.0f;
    host->velocity.z = -2.5f;
    HuPrcSleep(10);
    host->velocity.y = 0.0f;
    host->velocity.z = 0.0f;
    func_800610E0_main(D_80107768_opboardtutorial);
    D_80107768_opboardtutorial = func_80060880_main(0x4B, 0x9F, 0x10);
    func_8005C060_main(D_80107768_opboardtutorial, 4, 0, 0xE0, 0xE0);
    func_8005BDFC_main(D_80107768_opboardtutorial, 0);
}

// board t1: register allocation in the roll sort (masked 0; opboard's twin has the same residue)
#ifdef NON_MATCHING
/* deciding the turn order (scripted): every player hits a dice block at once, the rolls are
   fixed (player 0: 2..5, 1: 6..9, 2: 10, 3: 1); then the host introduces each player in the new
   order */
void func_80106990_opboardtutorial(void) {
    s32 state[4];
    s32 count[4];
    s32 order[4];
    u8 anim[4] = { 3, 6, 5, 0 };
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
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1601, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    help = func_800E210C_shared_board(2, 0xBE, 1);
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            tmp = (rand8() & 3) + 2;
            break;
        case 1:
            tmp = (rand8() & 3) + 6;
            break;
        case 2:
            tmp = 10;
            break;
        case 3:
            tmp = 1;
            break;
        default:
            tmp = 5;
            break;
        }
        func_800DCD64_shared_board(i, tmp);
    }
    for (i = 0; i < 4; i++) {
        state[i] = 1;
        count[i] = 0;
    }
    HuPrcSleep(20);
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (state[i] == 1) {
                state[i] = 2;
                MBMotionSet(D_80107788_opboardtutorial[i]->player_obj, 2, 0);
                func_800EE884_shared_board(D_80107788_opboardtutorial[i]->player_obj, -1, 2);
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
                s32 t = state[i];
                state[i] = state[j];
                state[j] = t;
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
    func_80106254_opboardtutorial();
    func_800F453C_shared_board();
    D_801075C0_opboardtutorial = 1;
    for (i = 0; i < 4; i++) {
        MBStatusDispSideSet(i, 1);
    }
    HuPrcSleep(5);
    func_8005C060_main(D_80107768_opboardtutorial, 4, 0, 0xFF, 0xFF);
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1602, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    for (i = 0; i < 4; i++) {
        s32 mes[4] = { 0x1603, 0x1604, 0x1605, 0x1606 };

        func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0],
                                      D_80107770_opboardtutorial[anim[i]]);
        func_8005B43C_main(D_80107768_opboardtutorial, mes[i], -1, -1);
        if (i != 0) {
            func_80060C14_main(D_80107768_opboardtutorial, 1);
        }
        func_800EE614_shared_board(D_80107768_opboardtutorial);
        func_80060EA8_main(D_80107768_opboardtutorial, 1);
        func_8004ACE0_main(0x274, i);
        func_800EE94C_shared_board(D_80107788_opboardtutorial[i]->player_obj, 3, 0);
        func_800EE884_shared_board(D_80107788_opboardtutorial[i]->player_obj, -1, 2);
        func_800DBEC0_shared_board(order[i]);
        if (i == 2) {
            func_801068E4_opboardtutorial(D_80107764_opboardtutorial);
        }
        MBStatusDispMoveSet(i + 10);
        while (func_800F5278_shared_board() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(20);
    }
    func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], D_80107770_opboardtutorial[0]);
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/opboardtutorial/3CDEC0", func_80106990_opboardtutorial);
INCLUDE_RODATA("asm/nonmatchings/overlays/opboardtutorial/3CDEC0", D_80107740_opboardtutorial);
INCLUDE_RODATA("asm/nonmatchings/overlays/opboardtutorial/3CDEC0", D_80107744_opboardtutorial);
#endif

void func_80106F40_opboardtutorial(void) {
    s16 fx[4];
    s32 i;
    s32 n;
    f32 scale;

    MBBackKill();
    MBBackLoad(0x16);
    func_800E9344_shared_board(1000.0f, 10000.0f);
    D_80107764_opboardtutorial = MBModelCreate(0x3B, NULL);
    HuVecCopy3F(&D_80107764_opboardtutorial->coords, &D_801075C4_opboardtutorial);
    HuVecCopyXYZ(&D_80107764_opboardtutorial->scale, 0.9f, 0.9f, 0.9f);
    D_80107764_opboardtutorial->rot.x = sindf(10.0f);
    D_80107764_opboardtutorial->rot.z = cosdf(10.0f);
    D_80107764_opboardtutorial->flags |= 1;
    D_80107768_opboardtutorial = func_80060880_main(0x4B, 0xC5, 0x10);
    func_8005BDFC_main(D_80107768_opboardtutorial, 0);
    D_80107770_opboardtutorial[0] =
        func_80105FA8_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80107770_opboardtutorial[1] = func_80106184_opboardtutorial(0xA007F);
    D_80107770_opboardtutorial[2] = func_80106184_opboardtutorial(0xA0080);
    D_80107770_opboardtutorial[3] = func_80106184_opboardtutorial(0xA0081);
    D_80107770_opboardtutorial[4] = func_80106184_opboardtutorial(0xA0082);
    D_80107770_opboardtutorial[5] = func_80106184_opboardtutorial(0xA0083);
    D_80107770_opboardtutorial[6] = func_80106184_opboardtutorial(0xA0084);
    func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], D_80107770_opboardtutorial[0]);
    D_80107798_opboardtutorial = MBModelCreate(0x3A, NULL);
    func_800461B4_main(D_80107798_opboardtutorial->omObj1->model[0]);
    HuVecCopy3F(&D_80107798_opboardtutorial->coords, &D_801075F4_opboardtutorial);
    D_80107798_opboardtutorial->velocity.x = 1000.0f;
    for (i = 0; i < 4; i++) {
        HuVecCopy3F(&D_80107788_opboardtutorial[i]->player_obj->coords, &D_80107630_opboardtutorial[i]);
        fx[i] = func_80105AFC_opboardtutorial(0xB0004, 0x689);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (n = 0; n < 20; n++) {
        for (i = 0; i < 4; i++) {
            func_80105C7C_opboardtutorial(fx[i], D_80107788_opboardtutorial[i]->player_obj->coords.x,
                                          D_80107788_opboardtutorial[i]->player_obj->coords.y + 50.0f,
                                          D_80107788_opboardtutorial[i]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 4; i++) {
            MBModelDispOn(D_80107788_opboardtutorial[i]->player_obj);
            HuVecCopyXYZ(&D_80107788_opboardtutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuVecCopyXYZ(&D_80107788_opboardtutorial[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(0xB);
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1600, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    func_80106990_opboardtutorial();
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1607, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    func_800610E0_main(D_80107768_opboardtutorial);
}

/* the overlay's main process */
void func_80107408_opboardtutorial(void) {
    func_801063A4_opboardtutorial();
    func_80106F40_opboardtutorial();
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107448_opboardtutorial(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80107594_opboardtutorial();
        func_8010751C_opboardtutorial();
        func_8005F524_main();
        if (D_801075C0_opboardtutorial != 0) {
            func_800F4730_shared_board();
        }
        omOvlReturnEx(1);
    }
}

void func_801074A4_opboardtutorial(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 0x14);
        obj->func = func_80107448_opboardtutorial;
    }
}

void func_801074E8_opboardtutorial(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
    func_800F2A20_shared_board();
}

void func_8010751C_opboardtutorial(void) {
    func_800F2A34_shared_board();
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_80107550_opboardtutorial(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(0x15);
}

void func_80107594_opboardtutorial() {
    MBBackKill();
    MBBackClose();
}
