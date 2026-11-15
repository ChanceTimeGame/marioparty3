#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/process.h"
#include "game/util.h"
#include "variables.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "game/data.h"
#include "math.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

/* An entry of D_800CBB60_main (src/14EA0.c unk_800ECDE0): its model at 0x00. */
typedef struct RbSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8 *unk20;
} RbSprModel; // sizeof 0x24 on N64

/* One falling coin: obj->model[i + 1] falls, obj->model[i + 41] is the landing splash. */
typedef struct RbCoin {
    /* 0x00 */ u8 state; // 1 idle, 2 falling, 4 waiting for delay
    /* 0x02 */ u16 sprFall;
    /* 0x04 */ u16 sprLand;
    /* 0x08 */ s32 delay;
    /* 0x0C */ Vec pos;
    /* 0x18 */ f32 vel;
    /* 0x1C */ f32 floor;
} RbCoin; // sizeof 0x20

extern RbSprModel *D_800CBB60_main;
extern RbCoin D_80108A30_mgresultbattle[40];
extern omObjData *D_80108F74_mgresultbattle;
extern void (*D_80108F78_mgresultbattle)(omObjData *);
extern s32 D_801088E0_mgresultbattle[4];
extern s32 D_80108F70_mgresultbattle;
extern const s32 D_801089C0_mgresultbattle[4];

typedef struct RbHooked {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} RbHooked; // sizeof 0x08 on N64

extern RbHooked D_80108F50_mgresultbattle[4];
extern RbHooked D_80108F90_mgresultbattle;
extern s8 D_80108F8C_mgresultbattle[4];
extern const Vec D_801089D0_mgresultbattle[4];

u16 func_80014618_main(s16 index, u16 arg1);
void func_80014714_main(s16 index, u16 arg1);
void func_80106E98_mgresultbattle(void);
void func_801075EC_mgresultbattle(void);
void func_801075F4_mgresultbattle(omObjData *);
void func_80107610_mgresultbattle(omObjData *);
void func_80107B5C_mgresultbattle(f32, f32, f32);
void func_80107BDC_mgresultbattle(f32);
void func_80107C44_mgresultbattle(void);
void func_80107CA4_mgresultbattle(void);
void func_801082AC_mgresultbattle(void);
void func_80106EA0_mgresultbattle(void);
void func_80107260_mgresultbattle(f32, f32, f32, s32, f32);
void func_8001EF6C_main(s16, s16, char *);
void func_80106ED0_mgresultbattle(omObjData *);

// Creates the 40 coin sprite models (falling coin and landing splash) and runs the coin hook.
void func_80106BA0_mgresultbattle(void) {
    omObjData *obj;
    void *data;
    s32 i;
    u16 sprFall;
    u16 sprLand;

    obj = omAddObj(0x14, 0x58, 8, -1, NULL);
    D_80108F74_mgresultbattle = obj;
    data = DataRead(0x210026);
    sprFall = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprFall].unk00, 0x70000000, 0x70000000);
    data = DataRead(0xC);
    sprLand = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprLand].unk00, 0x70000000, 0x70000000);
    for (i = 0; i < 40; i++) {
        D_80108A30_mgresultbattle[i].state = 1;
        D_80108A30_mgresultbattle[i].sprFall = func_80014618_main(sprFall, 8);
        D_80108A30_mgresultbattle[i].sprLand = func_80014618_main(sprLand, 8);
        D_80108A30_mgresultbattle[i].delay = 0;
        D_80108A30_mgresultbattle[i].vel = 0;
        D_80108A30_mgresultbattle[i].floor = 0;
        obj->model[i + 1] = D_800CBB60_main[D_80108A30_mgresultbattle[i].sprFall].unk00;
        func_8001C92C_main(obj->model[i + 1], 2.0f);
        // Retail scales D_800CBB60_main[i + 1] and [i + 41], not the clones made above.
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].unk00, 3.0f, 3.0f, 3.0f);
        func_8001C258_main(obj->model[i + 1], 4, 4);
        obj->model[i + 41] = D_800CBB60_main[D_80108A30_mgresultbattle[i].sprLand].unk00;
        Hu3DModelScaleSet(D_800CBB60_main[i + 41].unk00, 3.0f, 3.0f, 3.0f);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106E98_mgresultbattle);
    D_80108F78_mgresultbattle = func_80106ED0_mgresultbattle;
    while (1) {
        D_80108F78_mgresultbattle(obj);
        HuPrcVSleep();
    }
}

void func_80106E98_mgresultbattle(void) {
}

void func_80106EA0_mgresultbattle(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_801088E0_mgresultbattle[i] = 0;
    }
}

// Coin hook: counts down each waiting coin, drops the falling ones, and on landing rumbles the first
// human player under it (within 100 units in x) once.
void func_80106ED0_mgresultbattle(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        switch (D_80108A30_mgresultbattle[i].state) {
        case 1:
            break;
        case 4:
            if (--D_80108A30_mgresultbattle[i].delay > 0) {
                break;
            }
            D_80108A30_mgresultbattle[i].state = 2;
        case 2:
            Hu3DModelScaleSet(obj->model[i + 1], 1.5f, 1.5f, 1.5f);
            func_8001C258_main(obj->model[i + 1], 4, 0);
            Hu3DModelPosSet(obj->model[i + 1], D_80108A30_mgresultbattle[i].pos.x, D_80108A30_mgresultbattle[i].pos.y,
                            D_80108A30_mgresultbattle[i].pos.z);
            D_80108A30_mgresultbattle[i].pos.y -= D_80108A30_mgresultbattle[i].vel;
            D_80108A30_mgresultbattle[i].vel += 4.0f;
            if (D_80108A30_mgresultbattle[i].pos.y <= D_80108A30_mgresultbattle[i].floor) {
                HuAudFXPlay(0x106);
                for (j = 0; j < 4; j++) {
                    if (GwPlayer[D_80108F8C_mgresultbattle[j]].stat & 1) {
                        continue;
                    }
                    if (D_801088E0_mgresultbattle[j] != 0) {
                        continue;
                    }
                    if (ABS(D_801089D0_mgresultbattle[j].x - D_80108A30_mgresultbattle[i].pos.x) < 100.0f) {
                        omVibrate(D_80108F8C_mgresultbattle[j], 5, 0, 5);
                        D_801088E0_mgresultbattle[j] = 1;
                        break;
                    }
                }
                D_80108A30_mgresultbattle[i].state = 1;
                func_8001C258_main(obj->model[i + 1], 4, 4);
                func_80014714_main(D_80108A30_mgresultbattle[i].sprLand, 0);
                Hu3DModelPosSet(obj->model[i + 41], D_80108A30_mgresultbattle[i].pos.x, D_80108A30_mgresultbattle[i].floor,
                                D_80108A30_mgresultbattle[i].pos.z);
                func_8001C258_main(obj->model[i + 41], 4, 0);
            }
            break;
        }
    }
}

// Queues up to count idle coins to fall from (x + 0..49, y, z + 0..49) onto floor, one frame apart.
void func_80107260_mgresultbattle(f32 x, f32 y, f32 z, s32 count, f32 floor) {
    s32 n;
    s32 i;

    for (n = 0, i = 0; i < 40; i++) {
        if (D_80108A30_mgresultbattle[i].state == 1) {
            D_80108A30_mgresultbattle[i].state = 4;
            D_80108A30_mgresultbattle[i].delay = n++;
            D_80108A30_mgresultbattle[i].pos.x = x + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].pos.y = y;
            D_80108A30_mgresultbattle[i].pos.z = z + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].vel = 0;
            D_80108A30_mgresultbattle[i].floor = floor;
        }
        if (n >= count) {
            break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089A8_mgresultbattle);

// Creates the coin-dropping flyer (body, held item and a third model) and runs its hook.
void func_80107400_mgresultbattle(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80108F90_mgresultbattle.obj = obj;
    obj->model[1] = func_8000B108_main(0xA00A5, 0x2B9);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->model[2] = func_8000B108_main(0x1B0000, 0x2B9);
    func_8001C258_main(obj->model[2], 0x4000, 0x4000);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001EF6C_main(obj->model[2], obj->model[1], "item_hook");
    obj->model[3] = func_8000B108_main(0x130200, 0x2B9);
    func_8001C814_main(obj->model[3], 2, 2);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, 0xA00A6);
    func_8000B460_main(obj, 1, 0xA00B6);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_80107CA4_mgresultbattle();
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_801075EC_mgresultbattle);
    D_80108F90_mgresultbattle.func = func_801075F4_mgresultbattle;
    while (1) {
        D_80108F90_mgresultbattle.func(obj);
        HuPrcVSleep();
    }
}

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(omObjData *obj) {
}

void func_801075FC_mgresultbattle(void) {
    D_80108F90_mgresultbattle.func = func_80107610_mgresultbattle;
}

// Flyer hook: flies right to left over the figures dropping each one's winnings (at most 10 coins
// shown), then, if coins are left over, gives them to a player picked at random (weights by placing)
// and flies back dropping them over that player.
void func_80107610_mgresultbattle(omObjData *obj) {
    s32 weight[4];
    f32 pos[2];
    f32 angle;
    f32 t;
    f32 sway;
    s32 i;
    s32 k;
    s32 n;
    s32 sum;
    s32 r;

    k = 3;
    func_80107C44_mgresultbattle();
    sway = 0.0f;
    HuAudFXPlay(0x25B);
    t = sway;
    func_80106EA0_mgresultbattle();
    for (i = 0; i < 60; i++) {
        angle = t * 2.6666667f + 10.0f;
        t += 1.0f;
        pos[0] = cosdf(angle) * 750.0f;
        pos[1] = -sindf(angle) * 400.0f;
        func_80107B5C_mgresultbattle(pos[0] + 0.0f, pos[1] + 950.0f, 0.0f);
        func_80107BDC_mgresultbattle(sindf(sway) * 25.0f);
        sway += 1.5f;
        if (k >= 0 && pos[0] + 0.0f <= D_801089D0_mgresultbattle[k].x) {
            n = GwPlayer[D_80108F8C_mgresultbattle[k]].gameCoin;
            if (n > 0) {
                if (n > 10) {
                    n = 10;
                }
                func_80107260_mgresultbattle(D_801089D0_mgresultbattle[k].x, pos[1] + 950.0f + 0.0f, 0.0f, n,
                                             HmfModelData[D_80108F50_mgresultbattle[k].obj->model[1]].pos.y + 160.0f);
            }
            k--;
        }
        HuPrcVSleep();
    }

    sway = 0.0f;
    if (D_80108F70_mgresultbattle > 0) {
        HuPrcSleep(30);
        sum = 0;
        func_80106EA0_mgresultbattle();
        for (i = 0; i < 4; i++) {
            weight[i] = D_801089C0_mgresultbattle[GwPlayer[i].bonusCoin];
            sum += weight[i];
        }
        i = 0;
        r = rand16() % sum + 1;
        for (sum = 0, k = 4; i < 4; i++) {
            sum += weight[i];
            if (sum >= r) {
                k = i;
                break;
            }
        }
        GwPlayer[D_80108F8C_mgresultbattle[k]].gameCoin += D_80108F70_mgresultbattle;
        t = 0.0f;
        for (i = 0; i < 40; i++) {
            angle = t * 4.0f + 10.0f;
            t += 1.0f;
            pos[0] = -cosdf(angle) * 750.0f;
            pos[1] = -sindf(angle) * 400.0f;
            func_80107B5C_mgresultbattle(pos[0] + 0.0f, pos[1] + 950.0f, 0.0f);
            func_80107BDC_mgresultbattle(-sindf(sway) * 25.0f);
            sway += 1.5f;
            if (k >= 0 && pos[0] + 0.0f >= D_801089D0_mgresultbattle[k].x) {
                n = D_80108F70_mgresultbattle;
                if (n > 0) {
                    if (n > 10) {
                        n = 10;
                    }
                    func_80107260_mgresultbattle(D_801089D0_mgresultbattle[k].x, pos[1] + 950.0f + 0.0f, 0.0f, n,
                                                 HmfModelData[D_80108F50_mgresultbattle[k].obj->model[1]].pos.y + 160.0f);
                }
                k = -1;
            }
            HuPrcVSleep();
        }
    }
    func_80107CA4_mgresultbattle();
    func_801082AC_mgresultbattle();
    D_80108F90_mgresultbattle.func = func_801075F4_mgresultbattle;
}

void func_80107B5C_mgresultbattle(f32 x, f32 y, f32 z) {
    omObjData *obj = D_80108F90_mgresultbattle.obj;

    Hu3DModelPosSet(obj->model[1], x, y, z);
    Hu3DModelPosSet(obj->model[3], x, y, z);
}

void func_80107BDC_mgresultbattle(f32 rot) {
    omObjData *obj = D_80108F90_mgresultbattle.obj;

    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, rot);
    Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, rot);
}

void func_80107C44_mgresultbattle(void) {
    omObjData *obj = D_80108F90_mgresultbattle.obj;

    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
}

void func_80107CA4_mgresultbattle(void) {
    omObjData *obj = D_80108F90_mgresultbattle.obj;

    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089C0_mgresultbattle);
