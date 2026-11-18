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
extern RrEnt D_8010DD08_river_raiders[3]; /* = D_8010D9F0_river_raiders[6..8] */
extern omObjData *D_8010DE94_river_raiders; /* = D_8010D9F0_river_raiders[9].obj */
extern RrEnt D_8010EE90_river_raiders; /* = D_8010D9F0_river_raiders[40]: the water */
extern f32 D_8010EEA8_river_raiders;   /* = D_8010EE90_river_raiders.unk18: the water's texture scroll */
extern u8 D_80110D84_river_raiders;
extern RrTexSize D_80110D88_river_raiders;
extern s8 D_80110D90_river_raiders;
extern u8 D_80110DBD_river_raiders;


void func_8010D268_river_raiders(void);
void func_80105BA4_river_raiders(omObjData *obj);
void func_80105D1C_river_raiders(omObjData *obj);
void func_80105FA0_river_raiders(omObjData *obj);
void func_801060BC_river_raiders(omObjData *obj);
void func_80106244_river_raiders(omObjData *obj);
void func_80106300_river_raiders(omObjData *obj);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801069A4_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106A54_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106AF8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010716C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80107188_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801072FC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80107B14_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108188_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108574_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108678_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108ACC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108F40_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801093F0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010940C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010957C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80109C08_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010A6A8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ABA0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ACD8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010BE88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C494_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C890_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C980_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA20_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA4C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA84_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CADC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CF00_river_raiders);

void func_8010D0F0_river_raiders(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D0F8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D268_river_raiders);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", D_8010D9BC_river_raiders);
