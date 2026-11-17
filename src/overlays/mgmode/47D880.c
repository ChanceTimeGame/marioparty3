#include "common.h"
#include "mallocblock.h"
#include "game/esprite.h"
#include "game/hmfman.h"
#include "game/util.h"

/* Model table entry: a model file, placed and turned; the table ends with dir == -1. */
typedef struct MgModeModelDef {
    /* 0x00 */ s32 dir;
    /* 0x04 */ s32 file;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 motion;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} MgModeModelDef; // Size 0x24

/* Sprite table entry; the table ends with file == -1. */
typedef struct MgModeSprDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ u16 prio;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
} MgModeSprDef; // Size 0xC

/* One created sprite; a list of them ends with sprite == -1. */
typedef struct MgModeSpr {
    /* 0x00 */ s16 sprite;
    /* 0x02 */ u16 grp;
} MgModeSpr; // Size 0x4

void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);

extern s16 D_8011B780_mgmode[];
extern s16 D_8011B8A8_mgmode[];

void func_80116610_mgmode(MgModeModelDef* defs, s16 idx, s16 model) {
    MgModeModelDef* def = &defs[idx];

    Hu3DModelPosSet(model, def->pos.x, def->pos.y, def->pos.z);
    Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
}

void func_8011667C_mgmode(MgModeModelDef* defs) {
    MgModeModelDef* def = defs;
    s16 i;
    s16 model;

    for (i = 0; def->dir != -1; def++, i++) {
        D_8011B8A8_mgmode[i] = model = func_8000B108_main(def->dir, def->file | 0x288);
        func_8001C8A8_main(model, 1);
        func_80116610_mgmode(defs, i, model);
        if ((D_8011B780_mgmode[i] = HmfModelData[model].unk02) != -1) {
            func_8001C814_main(model, -1, def->motion);
        }
    }
}

MgModeSpr* func_80116794_mgmode(MgModeSprDef* defs) {
    MgModeSpr* list;
    s16 count;
    s16 i;
    u16 grp;

    for (count = 0; count < 0x40; count++) {
        if (defs[count].file == -1) {
            break;
        }
    }
    list = HuMemAllocTag((count + 1) * sizeof(MgModeSpr), 0x7918);
    for (i = 0; i < count; i++, defs++) {
        list[i].sprite = func_8000B838_main(defs->file);
        list[i].grp = grp = InitEspriteSlot(list[i].sprite, 0, 1);
        func_8000BBD4_main(grp, defs->x, defs->y);
        func_8000BC88_main(grp, 0xFFFF);
        func_8000BC48_main(grp, defs->prio);
    }
    list[i].sprite = -1;
    return list;
}

void func_801168E0_mgmode(MgModeSpr* list) {
    MgModeSpr* spr = list;
    s16 i;

    for (i = 0; i < 0x40; i++) {
        if (spr->sprite == -1) {
            break;
        }
        func_8000C184_main(spr->grp);
        HuSprKill(spr++->sprite);
    }
    HuMemFree(list);
}

void func_80116968_mgmode(MgModeSpr* list, s16 idx, s16 x, s16 y) {
    func_8000BBD4_main(list[idx].grp, x, y);
}

void func_801169A0_mgmode(MgModeSpr* list, s16 idx) {
    func_8000BB54_main(list[idx].grp);
}

void func_801169C8_mgmode(MgModeSpr* list, s16 idx) {
    func_8000BB94_main(list[idx].grp);
}

void func_801169F0_mgmode(MgModeSpr* list, s16 idx, u16 prio) {
    func_8000BC48_main(list[idx].grp, prio);
}

void func_80116A1C_mgmode(MgModeSpr* list, s16 idx, u16 arg2) {
    func_8000BC88_main(list[idx].grp, arg2);
}

void func_80116A48_mgmode(MgModeSpr* list, s16 idx, f32 x, f32 y) {
    func_8000BE5C_main(list[idx].grp, x, y);
}

void func_80116A78_mgmode(MgModeSpr* list, s16 idx, s16 arg2) {
    func_8000BBFC_main(list[idx].grp, arg2);
}

#ifdef NON_MATCHING
/* Register allocation only: retail builds the entry address straight into $s0. */
void func_80116AA8_mgmode(MgModeSpr* list, s16 idx, s16 arg2) {
    MgModeSpr* spr = &list[idx];

    func_8000BD50_main(spr->grp, arg2);
    func_8000BDDC_main(spr->grp, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116AA8_mgmode);
#endif

void func_80116AEC_mgmode(MgModeSpr* list, s16 idx, u16 arg2) {
    func_8000BCC8_main(list[idx].grp, arg2);
}
