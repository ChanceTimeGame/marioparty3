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
extern s8 D_80108F8C_mgresultbattle[4];
extern const Vec D_801089D0_mgresultbattle[4];

u16 func_80014618_main(s16 index, u16 arg1);
void func_80014714_main(s16 index, u16 arg1);
void func_80106E98_mgresultbattle(void);
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

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107400_mgresultbattle);

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_801075FC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107610_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107B5C_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107BDC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107C44_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107CA4_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089C0_mgresultbattle);
