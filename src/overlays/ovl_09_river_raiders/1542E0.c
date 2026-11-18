#include "common.h"
// m5 rv: River Raiders (2 vs 2 raft race)
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

typedef func_800E1BA8_minigame_ObjData MgWork;

/* One slot of the overlay's object table (D_8010D9F0_river_raiders, 100 x 0x84; Coconut Conk's layout). */
typedef struct RrEnt {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} RrEnt; // Size 0x84

typedef struct RrXY {
    f32 x;
    f32 y;
} RrXY;

void func_8000BC48_main(u16, s32);
void func_8000BD50_main(u16 spriteId, s16 arg1);
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_800335BC_main(char *arg0, void *arg1);

/* A texture's size (func_800335BC_main). */
typedef struct RrTexSize {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
} RrTexSize;

/* A rope anchor path per raft seat, by animation frame / 2. */
typedef struct RrPath {
    /* 0x00 */ f32 x[16];
    /* 0x40 */ f32 y[16];
    /* 0x80 */ f32 z[16];
} RrPath; // Size 0xC0

/* .data */
extern RrPath D_8010D570_river_raiders[4]; /* inner labels D_8010D5F0/630/6B0/6F0/770/7B0/830 */
extern s32 D_8010D3B8_river_raiders[3];
extern f32 D_8010D3C4_river_raiders[3];
extern f32 D_8010D888_river_raiders[]; /* [team * 4 + digit] x, y pairs */
extern f32 D_8010D88C_river_raiders[]; /* = D_8010D888_river_raiders[1]: the y column */

/* .bss */
extern RrEnt D_8010D9F0_river_raiders[100];
extern RrEnt D_8010DA74_river_raiders[]; /* = D_8010D9F0_river_raiders[1] */
extern RrEnt D_8010DAF8_river_raiders[]; /* = D_8010D9F0_river_raiders[2] */
extern RrEnt D_8010DB7C_river_raiders[3]; /* = D_8010D9F0_river_raiders[3..5] */
extern RrEnt D_8010DD08_river_raiders[3]; /* = D_8010D9F0_river_raiders[6..8] */
extern omObjData *D_8010DE94_river_raiders; /* = D_8010D9F0_river_raiders[9].obj */
extern s16 D_8010DED4_river_raiders; /* = D_8010D9F0_river_raiders[9].grp */
extern s16 D_8010DED6_river_raiders; /* = D_8010D9F0_river_raiders[9].spr */
extern RrEnt D_8010DF18_river_raiders[]; /* = D_8010D9F0_river_raiders[10..]: river objects (rocks, coins) */
extern RrEnt D_8010EE90_river_raiders; /* = D_8010D9F0_river_raiders[40]: the water */
extern f32 D_8010EEA8_river_raiders;   /* = D_8010EE90_river_raiders.unk18: the water's texture scroll */
extern u8 D_80110D84_river_raiders;
extern s32 D_8010D3D0_river_raiders[]; /* portrait sprite per character */
extern s32 D_800A178C_main[][6];
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
extern s16 D_80110DE2_river_raiders; /* the race timer */
extern s16 D_8010D3B6_river_raiders; /* the engine sound id */
extern f32 D_8010D9DC_river_raiders[]; /* [0] paddle yaw, [1] = D_8010D9E0_river_raiders[0] */
extern s8 D_8010D9E6_river_raiders;
extern f32 D_80110DC8_river_raiders[6]; /* x bounds of the three lanes (min, max pairs) around the raft */
extern s16 D_80110DE0_river_raiders;    /* the engine sound, -1 none */
extern s16 D_80110DE4_river_raiders;    /* its pitch */
extern f32 D_8010D9E0_river_raiders[]; /* [0]: the steering lean, -10..10 */
extern RrTexSize D_80110D88_river_raiders;
extern s8 D_80110D90_river_raiders;
extern u8 D_80110DBD_river_raiders;

/* A camera (D_8010D8C8_river_raiders; Curtain Call's layout). */
typedef struct RrCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} RrCamera; // Size 0x2C
extern RrCamera D_8010D8C8_river_raiders[1];
extern const s16 D_8010D9BC_river_raiders[];
s32 func_8000B710_main(s32 arg0);


void func_8010D268_river_raiders(void);
void func_80105A3C_river_raiders(void);
void func_80106AF8_river_raiders(omObjData *obj);
void func_80108188_river_raiders(omObjData *obj);
void func_80108F40_river_raiders(omObjData *obj);
void func_8010CA20_river_raiders(omObjData *obj);
void func_8010CA4C_river_raiders(omObjData *obj);
void func_8010CA84_river_raiders(omObjData *obj);
void func_8010CF00_river_raiders(omObjData *obj);
void func_8010D0F8_river_raiders(void);
void func_80105BA4_river_raiders(omObjData *obj);
void func_80105D1C_river_raiders(omObjData *obj);
void func_80105FA0_river_raiders(omObjData *obj);
void func_801060BC_river_raiders(omObjData *obj);
void func_80106244_river_raiders(omObjData *obj);
void func_80106300_river_raiders(omObjData *obj);
void func_80106448_river_raiders(omObjData *obj);
void func_801069A4_river_raiders(omObjData *obj);

void func_801059A0_river_raiders(void) {
    func_8010D268_river_raiders();
}

f32 func_801059BC_river_raiders(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_river_raiders(void) {
    RrEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010D9F0_river_raiders; i < 100; i++, ent++) {
        ent->obj = NULL;
        ent->unk04 = 0;
        ent->unk06 = 0;
        ent->unk08 = 0;
        ent->unk0A = 0;
        ent->unk0C = 0;
        ent->unk0E = 0;
        ent->unk10 = 0;
        ent->unk12 = 0;
        ent->unk14 = 0;
        ent->unk16 = 0;
        ent->unk18 = 0;
        ent->unk1C = 0;
        ent->unk20 = 0;
        ent->unk24 = 0;
        ent->unk28 = 0;
        ent->unk2C = 0;
        ent->unk30 = 0;
        ent->unk34 = 0;
        ent->unk38 = 0;
        ent->unk3C = 0;
        ent->grp = -1;
        ent->spr = -1;
        ent->pos.x = ent->pos.y = ent->pos.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->unk5C.x = ent->unk5C.y = ent->unk5C.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105B04_river_raiders(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105B7C_river_raiders(s8 arg0) {
    D_80110D90_river_raiders = arg0;
}

f32 func_80105B88_river_raiders(f32 pos, f32 *vel, f32 accel) {
    f32 v = *vel;

    *vel = v - accel;
    return pos + v;
}

/* A team score digit sprite: work[0] team, work[1] 2 tens, 3 ones. */
void func_80105BA4_river_raiders(omObjData *obj) {
    RrEnt *ent = &D_8010D9F0_river_raiders[obj->work[0] * 4 + 43 + obj->work[1]];

    switch (obj->work[0]) {
        case 0:
            if (obj->work[1] == 2) {
                if ((u8)(D_80110D84_river_raiders / 10) != 0) {
                    func_8000BB54_main(ent->spr);
                    func_8000BD50_main(ent->spr, (u8)(D_80110D84_river_raiders / 10));
                }
            } else if (obj->work[1] == 3) {
                func_8000BD50_main(ent->spr, (u8)(D_80110D84_river_raiders % 10));
            }
            break;
        case 1:
            if (obj->work[1] == 2) {
                if ((u8)(D_80110DBD_river_raiders / 10) != 0) {
                    func_8000BB54_main(ent->spr);
                    func_8000BD50_main(ent->spr, (u8)(D_80110DBD_river_raiders / 10));
                }
            } else if (obj->work[1] == 3) {
                func_8000BD50_main(ent->spr, (u8)(D_80110DBD_river_raiders % 10));
            }
            break;
    }
}

void func_80105D1C_river_raiders(omObjData *obj) {
    RrEnt *ent = &D_8010D9F0_river_raiders[obj->work[0] * 4 + 43 + obj->work[1]];

    switch (obj->work[1]) {
        case 0:
            ent->grp = func_8000B838_main(0x2A0013);
            ent->spr = InitEspriteSlot(ent->grp, 0, 0);
            func_8000BC48_main(ent->spr, 0x1000);
            break;
        case 1:
            ent->grp = func_8000B838_main(0x2A0012);
            ent->spr = InitEspriteSlot(ent->grp, 0, 0);
            func_8000BC48_main(ent->spr, 0x1000);
            break;
        case 2:
        case 3:
            ent->grp = func_8000B838_main(0x31);
            ent->spr = InitEspriteSlot(ent->grp, 0, 0);
            func_8000BC48_main(ent->spr, 0x1000);
            if (obj->work[1] == 2) {
                func_8000BB94_main(ent->spr);
            }
            break;
    }
    ent->pos.x = D_8010D888_river_raiders[(obj->work[0] * 4 + obj->work[1]) * 2];
    ent->pos.y = D_8010D88C_river_raiders[(obj->work[0] * 4 + obj->work[1]) * 2];
    func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
    obj->func = func_80105BA4_river_raiders;
}

void func_80105EAC_river_raiders(void) {
    omObjData *obj;
    RrEnt *ent;
    s16 i;
    s16 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            ent = &D_8010D9F0_river_raiders[i * 4 + 43 + j];
            obj = omAddObj(990, 1, 10, -1, func_80105D1C_river_raiders);
            obj->work[0] = i;
            obj->work[1] = j;
            ent->obj = obj;
        }
    }
}

/* The three river sections scroll toward the camera; one passing the end moves behind the last. */
void func_80105FA0_river_raiders(omObjData *obj) {
    RrEnt *ent = &D_8010D9F0_river_raiders[obj->work[0]];
    omObjData *sect;
    s16 i;

    obj->trans.z += 17.0f;
    if (obj->work[0] == 2) {
        for (i = 0; i < 3; i++) {
            sect = (&D_8010D9F0_river_raiders[i])->obj;
            if (sect->trans.z >= 1875.0f) {
                switch (i) {
                    case 0:
                        ent = D_8010DAF8_river_raiders;
                        break;
                    case 1:
                        ent = D_8010D9F0_river_raiders;
                        break;
                    case 2:
                        ent = D_8010DA74_river_raiders;
                        break;
                }
                sect->trans.z = ent->obj->trans.z - 1875.0f;
            }
        }
    }
}

void func_801060BC_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(D_8010D3B8_river_raiders[obj->work[0]], 0x288);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = D_8010D3C4_river_raiders[obj->work[0]];
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    obj->func = func_80105FA0_river_raiders;
}

void func_801061A0_river_raiders(void) {
    omObjData *obj;
    RrEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_8010D9F0_river_raiders[i];
        obj = omAddObj(500, 1, 10, -1, func_801060BC_river_raiders);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

void func_80106244_river_raiders(omObjData *obj) {
    RrEnt *ent = &D_8010EE90_river_raiders;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010EEA8_river_raiders += 1.5f;
    }
    func_8001E888_main(obj->model[0], 0, ent->unk18, D_80110D88_river_raiders.w, D_80110D88_river_raiders.h,
                       "suki-m209_04_1_3", 0);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_80106300_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2A0004, 0x2A8);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0x80);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main("209_water_00_DEF", &D_80110D88_river_raiders);
    D_8010EEA8_river_raiders = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->func = func_80106244_river_raiders;
}

void func_801063FC_river_raiders(void) {
    omObjData *obj = omAddObj(950, 1, 10, -1, func_80106300_river_raiders);

    obj->work[0] = 0;
    D_8010EE90_river_raiders.obj = obj;
    omSetStatBit(obj, 0xA0);
}

/* Aims and stretches a rope model from the raft object toward each of its three riders' hands. */
void func_80106448_river_raiders(omObjData *obj) {
    omObjData *raft = D_8010DE94_river_raiders;
    f32 dx, dy, dz;
    f32 x, y, z;
    f32 yaw, pitch;
    f32 dist;
    omObjData *rider;
    RrEnt *ent;
    s16 frame;
    u8 i;

    z = 0.0f;
    y = z;
    x = z;
    for (i = 0; i < 3; i++) {
        ent = &D_8010DD08_river_raiders[i];
        rider = ent->obj;
        if (rider->work[2] != obj->work[0]) {
            continue;
        }
        switch (ent->unk08) {
            case 0:
                frame = HmfModelData[rider->model[0]].unk40;
                x = -D_8010D570_river_raiders[0].x[frame / 2] * 5.0f + rider->trans.x;
                y = D_8010D570_river_raiders[0].y[frame / 2] * 5.0f + rider->trans.y;
                z = -D_8010D570_river_raiders[0].z[frame / 2] * 5.0f + rider->trans.z + 20.0f;
                break;
            case 1:
                frame = HmfModelData[rider->model[0]].unk40;
                x = -D_8010D570_river_raiders[1].x[frame / 2] * 5.0f + rider->trans.x;
                y = D_8010D570_river_raiders[1].y[frame / 2] * 5.0f + rider->trans.y;
                z = -D_8010D570_river_raiders[1].z[frame / 2] * 5.0f + rider->trans.z;
                break;
            case 2:
                frame = HmfModelData[rider->model[0]].unk40;
                x = -D_8010D570_river_raiders[2].x[frame / 2] * 5.0f + rider->trans.x;
                y = D_8010D570_river_raiders[2].y[frame / 2] * 5.0f + rider->trans.y;
                z = -D_8010D570_river_raiders[2].z[frame / 2] * 5.0f + rider->trans.z;
                break;
            case 3:
                frame = HmfModelData[rider->model[0]].unk40;
                x = -D_8010D570_river_raiders[3].x[frame / 2] * 5.0f + rider->trans.x;
                y = D_8010D570_river_raiders[3].y[frame / 2] * 5.0f + rider->trans.y;
                z = -D_8010D570_river_raiders[3].z[frame / 2] * 5.0f + rider->trans.z + 20.0f;
                break;
        }
        dx = x - raft->trans.x;
        dy = y - (raft->trans.y + 15.0f);
        dz = z - (raft->trans.z + 60.0f);
        yaw = atan2df(dx, dz);
        pitch = atan2df(dy, sqrtf(dx * dx + dz * dz));
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        obj->rot.y = 0.0f;
        obj->scale.z = dist / 450.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
        obj->rot.y = yaw;
        obj->rot.x = -pitch;
        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->trans.x = raft->trans.x;
        obj->trans.y = raft->trans.y + 15.0f;
        obj->trans.z = raft->trans.z + 60.0f;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_801069A4_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2A0000, 0x99);
    obj->trans.x = 0.0f;
    obj->trans.y = 15.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    func_8001C258_main(obj->model[0], 4, 0);
    obj->func = func_80106448_river_raiders;
}

void func_80106A54_river_raiders(void) {
    omObjData *obj;
    RrEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_8010DB7C_river_raiders[i];
        obj = omAddObj(800, 1, 10, -1, func_801069A4_river_raiders);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

#ifdef NON_MATCHING
/* CPU steering for a raft: picks the nearest target ahead and steers toward it (D_8010DE94: the raft's
 * entity; unk04 the chosen direction 0 none, 1 left, 2 right; unk06 a countdown; unk0A a repeat delay). */
void func_80106AF8_river_raiders(omObjData *obj) {
    RrEnt *raft = (RrEnt *)&D_8010DE94_river_raiders;
    u16 player = obj->work[0];
    s16 best = 0;
    f32 bestDist = 5000.0f;
    u8 dir = 0;
    omObjData *tgt;
    RrEnt *ent;
    f32 dx, dz;
    f32 dist;
    s16 i;

    if (--raft->unk06 <= 0) {
        raft->unk06 = 0;
    }
    if ((u16)(raft->unk06 % 3) < 2) {
        func_8001C258_main(obj->model[5], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (raft->unk06 < 31) {
        dir = rand8();
        if ((GwPlayer[player].cpu_difficulty == 0 && dir < 30) || (GwPlayer[player].cpu_difficulty == 1 && dir < 150) ||
            (GwPlayer[player].cpu_difficulty == 2 && dir < 200) || (GwPlayer[player].cpu_difficulty == 3 && dir < 255)) {
            for (i = 19; i >= 0; i--) {
                ent = &D_8010DF18_river_raiders[i];
                tgt = ent->obj;
                dx = tgt->trans.x - obj->trans.x;
                dz = tgt->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (tgt->trans.z < obj->trans.z && tgt->trans.z > -1500.0f) {
                    if (ent->unk04 == 1 && dist < bestDist) {
                        best = i;
                        bestDist = dist;
                    }
                }
            }
            tgt = D_8010DF18_river_raiders[best].obj;
            if (tgt->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < tgt->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= tgt->trans.x + 50.0f + 30.0f && tgt->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
            bestDist = 5000.0f;
            for (i = 23; i >= 20; i--) {
                ent = &D_8010DF18_river_raiders[i];
                tgt = ent->obj;
                dx = tgt->trans.x - obj->trans.x;
                dz = tgt->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (tgt->trans.z < obj->trans.z && tgt->trans.z > -1500.0f) {
                    if (ent->unk04 == 1 && dist < bestDist) {
                        best = i;
                        bestDist = dist;
                    }
                }
            }
            tgt = D_8010DF18_river_raiders[best].obj;
            if (tgt->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < tgt->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= tgt->trans.x + 50.0f + 30.0f && tgt->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
        }
    }
    if (--raft->unk0A <= 0) {
        raft->unk0A = 0;
    }
    if (dir == 0) {
        raft->unk04 = 0;
    }
    if (dir % 5 == 1 && raft->unk0A == 0) {
        raft->unk04 = 1;
        raft->unk0A = 30;
    }
    if (dir % 5 == 2 && raft->unk0A == 0) {
        raft->unk04 = 2;
        raft->unk0A = 30;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106AF8_river_raiders);
#endif

void func_8010716C_river_raiders(omObjData *obj) {
    func_80106AF8_river_raiders(obj);
}

/* Player steering for a raft: the stick picks the rope side (unk04: 0 none, 1 left, 2 right). */
void func_80107188_river_raiders(omObjData *obj) {
    RrEnt *raft = &D_8010D9F0_river_raiders[9];
    u16 player = obj->work[0];

    raft->unk04 = 0;
    if (--raft->unk06 <= 0) {
        raft->unk06 = 0;
    }
    if ((u16)(raft->unk06 % 3) < 2) {
        func_8001C258_main(obj->model[5], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (raft->unk06 < 31) {
        if (D_800CBB6E_main[GwPlayer[player].pad] < -29) {
            raft->unk04 = 1;
        }
        if (D_800CBB6E_main[GwPlayer[player].pad] >= 30) {
            raft->unk04 = 2;
        }
    }
}

/* Raft motion: tilt (rot.z), sideways drift (raft unk18) and the engine sound's pitch by steering direction. */
void func_801072FC_river_raiders(omObjData *obj) {
    RrEnt *raft = &D_8010D9F0_river_raiders[9];

    switch (raft->unk04) {
        case 0:
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (raft->unk06 < 31) {
                if (raft->unk08 == 1) {
                    func_8001C624_main(obj->model[5], HmfModelData[obj->motion[0]].unk02, 0, 1, 2);
                    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
                    raft->unk08 = 0;
                }
            } else {
                D_80110DE4_river_raiders = -500;
                if (raft->unk08 == 0) {
                    func_8001C624_main(obj->model[5], HmfModelData[obj->motion[1]].unk02, 0, 1, 0);
                    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 1, 0);
                    raft->unk08 = 1;
                }
            }
            if (raft->unk18 < 0.0f) {
                raft->unk18 += 0.05;
            }
            if (raft->unk18 > 0.0f) {
                raft->unk18 -= 0.05;
            }
            if ((s16)raft->unk18 == 0) {
                raft->unk18 = 0.0f;
                obj->trans.x = (s16)obj->trans.x;
            }
            if (D_8010D9E0_river_raiders[0] < 0.0f) {
                D_8010D9E0_river_raiders[0] += 1.0f;
            }
            if (D_8010D9E0_river_raiders[0] > 0.0f) {
                D_8010D9E0_river_raiders[0] -= 1.0f;
            }
            if ((s16)D_8010D9E0_river_raiders[0] == 0) {
                D_8010D9E0_river_raiders[0] = 0.0f;
            }
            D_80110DE4_river_raiders -= 5;
            if (D_80110DE4_river_raiders < -300) {
                D_80110DE4_river_raiders = -300;
            }
            break;
        case 1:
            if (raft->unk08 == 1) {
                func_8001C624_main(obj->model[5], HmfModelData[obj->motion[0]].unk02, 0, 1, 2);
                func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
                raft->unk08 = 0;
            }
            obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            if ((s16)obj->rot.z == 20.0f) {
                obj->rot.z = 19.0f;
            }
            if (raft->unk18 > -5.0f) {
                raft->unk18 -= 0.1f;
                if (raft->unk18 < -5.0f) {
                    raft->unk18 = -5.0f;
                }
            }
            D_8010D9E0_river_raiders[0] += 1.0f;
            if (D_8010D9E0_river_raiders[0] >= 10.0f) {
                D_8010D9E0_river_raiders[0] = 10.0f;
            }
            D_80110DE4_river_raiders += 5;
            if (D_80110DE4_river_raiders > 0) {
                D_80110DE4_river_raiders = 0;
            }
            break;
        case 2:
            if (raft->unk08 == 1) {
                func_8001C624_main(obj->model[5], HmfModelData[obj->motion[0]].unk02, 0, 1, 2);
                func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
                raft->unk08 = 0;
            }
            obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            if ((s16)obj->rot.z == 340.0f) {
                obj->rot.z = 341.0f;
            }
            if (raft->unk18 < 5.0f) {
                raft->unk18 += 0.1f;
                if (raft->unk18 > 5.0f) {
                    raft->unk18 = 5.0f;
                }
            }
            D_8010D9E0_river_raiders[0] -= 1.0f;
            if (D_8010D9E0_river_raiders[0] <= -10.0f) {
                D_8010D9E0_river_raiders[0] = -10.0f;
            }
            D_80110DE4_river_raiders += 5;
            if (D_80110DE4_river_raiders > 0) {
                D_80110DE4_river_raiders = 0;
            }
            break;
    }
    if (obj->trans.x + raft->unk18 + 60.0f >= 580.0f || obj->trans.x + raft->unk18 - 60.0f <= -580.0f) {
        raft->unk18 = 0.0f;
    }
    obj->trans.x += raft->unk18;
    if (D_80110DE0_river_raiders != -1) {
        HuAudFXPitchSet(D_80110DE0_river_raiders, D_80110DE4_river_raiders);
    }
    D_80110DC8_river_raiders[0] = obj->trans.x - 450.0f;
    D_80110DC8_river_raiders[1] = obj->trans.x + 150.0f;
    D_80110DC8_river_raiders[2] = obj->trans.x - 300.0f;
    D_80110DC8_river_raiders[3] = obj->trans.x + 300.0f;
    D_80110DC8_river_raiders[4] = obj->trans.x - 150.0f;
    D_80110DC8_river_raiders[5] = obj->trans.x + 450.0f;
}

/* The raft (team 0): engine sound, steering while racing, the crash wobble, the finish bounce; then places its
 * models (raft, two riders, paddle, rope). */
void func_80107B14_river_raiders(omObjData *obj) {
    RrEnt *raft = &D_8010D9F0_river_raiders[9];
    u16 player = obj->work[0];

    if ((u8)D_80110D90_river_raiders == 10) {
        if (D_80110DE0_river_raiders != -1) {
            func_8004AEF0_main(D_80110DE0_river_raiders, 30);
            D_80110DE0_river_raiders = -1;
        }
    } else if (D_80110DE0_river_raiders == -1) {
        D_80110DE0_river_raiders = HuAudFXPlay(D_8010D3B6_river_raiders);
    }
    switch ((u8)D_80110D90_river_raiders) {
        case 0:
        case 1:
            D_80110DE4_river_raiders = -300;
            if (D_80110DE0_river_raiders != -1) {
                HuAudFXPitchSet(D_80110DE0_river_raiders, -300);
            }
            break;
        case 2:
            if (D_80110DE2_river_raiders > 0) {
                if (GwPlayer[player].stat & 1) {
                    func_8010716C_river_raiders(obj);
                } else {
                    func_80107188_river_raiders(obj);
                }
                func_801072FC_river_raiders(obj);
            }
            break;
        case 3:
            D_80110DE4_river_raiders = -300;
            if (D_80110DE0_river_raiders != -1) {
                HuAudFXPitchSet(D_80110DE0_river_raiders, -300);
            }
            raft->unk1C = 10.0f;
            if (++raft->unk0C >= 20) {
                D_8010D9E6_river_raiders = 3;
            }
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (raft->unk08 == 1) {
                func_8001C624_main(obj->model[5], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
                func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
                raft->unk08 = 0;
            }
            if (D_8010D9E0_river_raiders[0] < 0.0f) {
                D_8010D9E0_river_raiders[0] += 1.0f;
            }
            if (D_8010D9E0_river_raiders[0] > 0.0f) {
                D_8010D9E0_river_raiders[0] -= 1.0f;
            }
            if ((s16)D_8010D9E0_river_raiders[0] == 0) {
                D_8010D9E0_river_raiders[0] = 0.0f;
            }
            break;
        case 5:
        case 10:
            if (D_80110D84_river_raiders != 0) {
                if (raft->unk16 == 0) {
                    func_8004ACE0_main(0x28F, obj->work[0]);
                    raft->unk16 = 1;
                }
                if (raft->unk0E <= 0) {
                    obj->trans.y = func_80105B88_river_raiders(obj->trans.y, &raft->unk1C, 1.0f);
                    if (raft->unk1C < -10.0f) {
                        raft->unk1C = 10.0f;
                        raft->unk0E = 5;
                    }
                }
                if (raft->unk0E > 0) {
                    raft->unk0E--;
                }
                if (obj->trans.y <= 1.0f) {
                    func_8001C258_main(obj->model[2], 4, 0);
                    func_8001C258_main(obj->model[3], 4, 0);
                } else {
                    func_8001C258_main(obj->model[2], 4, 4);
                    func_8001C258_main(obj->model[3], 4, 4);
                }
            }
            break;
    }
    switch (GwPlayer[obj->work[0]].chr) {
        case 0:
        case 1:
        case 6:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z + 40.0f);
            break;
        default:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
            break;
    }
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, D_8010D9DC_river_raiders[0], obj->rot.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], obj->rot.x, D_8010D9DC_river_raiders[1], 0.0f);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[4], obj->rot.x, obj->rot.y, obj->rot.z);
}

/* Team-0 raft setup: rider, second rider, paddle, rope, shadow; the team's portrait sprite. */
void func_80108188_river_raiders(omObjData *obj) {
    s8 chr = GwPlayer[obj->work[0]].chr;

    obj->model[5] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x6A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x27));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x28));
    func_8001C5B4_main(obj->model[5], obj->motion[0]);
    func_8001C6A8_main(obj->model[5], 0.0f);
    func_8001C814_main(obj->model[5], 2, 2);
    func_8001C448_main(obj->model[5]);
    func_8001C514_main(obj->model[5]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = func_8000B108_main(0x2A0008, 0x4B9);
    func_8000B460_main(obj, 2, 0x2A0009);
    func_8000B460_main(obj, 3, 0x2A000A);
    func_8001C5B4_main(obj->model[1], obj->motion[2]);
    func_8001C6A8_main(obj->model[1], 0.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[2] = func_8000B108_main(0x2A0010, 0x4A9);
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    obj->model[3] = func_8000B108_main(0x2A0011, 0x4A9);
    func_8001C814_main(obj->model[3], 2, 2);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[4] = func_8000B0A0_main(0, 0x4A9);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelScaleSet(obj->model[4], 2.0f, 2.0f, 2.0f);
    func_8001C2FC_main(obj->model[4], 0x80000000, 0);
    func_8001C448_main(obj->model[4]);
    func_8001C514_main(obj->model[4]);
    D_8010DED4_river_raiders = func_8000B838_main(D_8010D3D0_river_raiders[chr]);
    D_8010DED6_river_raiders = InitEspriteSlot(D_8010DED4_river_raiders, 0, 0);
    func_8000BC48_main(D_8010DED6_river_raiders, 0x1000);
    func_8000BBD4_main(D_8010DED6_river_raiders, 30, 210);
    func_8000BE5C_main(D_8010DED6_river_raiders, 1.0f, 1.0f);
    D_80110DE4_river_raiders = -300;
    obj->func = func_80107B14_river_raiders;
}

/* Creates the CPU-or-player raft controller for the team-0 lead player (D_8010DE94_river_raiders). */
void func_80108574_river_raiders(void) {
    omObjData *obj;
    u16 player = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            switch (i) {
                case 0:
                    player = 0;
                    break;
                case 1:
                    player = 1;
                    break;
                case 2:
                    player = 2;
                    break;
                case 3:
                    player = 3;
                    break;
            }
            obj = omAddObj(700, 9, 60, -1, func_80108188_river_raiders);
            obj->work[0] = player;
            D_8010DE94_river_raiders = obj;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108678_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108ACC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108F40_river_raiders);

void func_801093F0_river_raiders(omObjData *obj) {
    func_80108F40_river_raiders(obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010940C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010957C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80109C08_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010A6A8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ABA0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ACD8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010BE88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C494_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C890_river_raiders);

void func_8010C980_river_raiders(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 2275.0f;
        CRotM[i].x = 319.3f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -195.0f;
        CenterM[i].z = 0.0f;
    }
}

void func_8010CA20_river_raiders(omObjData *obj) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010CA4C_river_raiders(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010CA20_river_raiders;
    }
}

void func_8010CA84_river_raiders(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010CA4C_river_raiders;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CADC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CF00_river_raiders);

void func_8010D0F0_river_raiders(void) {
}

void func_8010D0F8_river_raiders(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010D8C8_river_raiders[i].scissor[0], D_8010D8C8_river_raiders[i].scissor[1],
                   D_8010D8C8_river_raiders[i].scissor[2], D_8010D8C8_river_raiders[i].scissor[3]);
        ViewportSet(i, D_8010D8C8_river_raiders[i].viewport[0], D_8010D8C8_river_raiders[i].viewport[1],
                    D_8010D8C8_river_raiders[i].viewport[2], D_8010D8C8_river_raiders[i].viewport[3],
                    D_8010D8C8_river_raiders[i].viewport[4], D_8010D8C8_river_raiders[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010D8C8_river_raiders[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010D268_river_raiders(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(100);
    omInitObjMan(100, 0);
    func_8004A208_main();
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x40, 0x40, 0x40);
    HmfLightDirSet(0, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(2, 0x40, 0x40, 0x40);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    func_8010D0F8_river_raiders();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010D9BC_river_raiders, 0);
    func_80045010_main(D_8010D9BC_river_raiders, 1);
    omAddObj(1000, 0, 0, -1, func_8010CF00_river_raiders);
    omAddObj(1000, 0, 0, -1, func_8010CA84_river_raiders);
    func_80105A3C_river_raiders();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", D_8010D9BC_river_raiders);
