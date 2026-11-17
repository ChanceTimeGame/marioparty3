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

/* .data (0x801195E0): the overlay's model and sprite tables. Inner labels (undefined_syms.txt):
   D_801198BC_mgmode, D_801198C8_mgmode = D_8011988C_mgmode[4], [5]; D_80119A78_mgmode = D_8011997C_mgmode[7];
   D_80119F34_mgmode, D_80119F64_mgmode = D_80119F28_mgmode[1], [5]; D_8011A0C0_mgmode = D_80119FA0_mgmode[8]. */
MgModeModelDef D_801195E0_mgmode[19] = {
    { 0x120000, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120001, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120002, 0x220, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120003, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120004, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x140001, 0x231, 0, 0, { 0.0f, 0.0f, 1125.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120005, 0x231, 0, 0, { 90.0f, 65.0f, -440.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12000A, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120007, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120008, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120006, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120009, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12000B, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12000C, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12000D, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA0000, 0x220, 0, 2, { 0.0f, 33.5f, -540.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA001A, 0x231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA0021, 0x231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
};
MgModeSprDef D_8011988C_mgmode[20] = {
    { 0x130036, 0x1000, 0, 0 }, { 0x130036, 0x1000, 0, 0 }, { 0x130036, 0x1000, 0, 0 },
    { 0x130036, 0x1000, 0, 0 }, { 0x120011, 0x1000, 0, 0 }, { 0x120011, 0x1000, 0, 0 },
    { 0x120011, 0x1000, 0, 0 }, { 0x120011, 0x1000, 0, 0 }, { 0x140012, 0x1000, 0, 0 },
    { 0x140013, 0x1000, 0, 0 }, { 0x140043, 0x1000, 0, 0 }, { 0x140044, 0x1000, 0, 0 },
    { 0x140045, 0x1000, 0, 0 }, { 0x140046, 0x1000, 0, 0 }, { 0x1300D1, 0x1000, 0, 0 },
    { 0x1300D1, 0x1000, 0, 0 }, { 0x1300D1, 0x1000, 0, 0 }, { 0x1300D1, 0x1000, 0, 0 },
    { 0x120010, 0x1000, 0, 0 }, { -1, 0x0, 0, 0 },
};
MgModeModelDef D_8011997C_mgmode[37] = {
    { 0x120015, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120017, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120018, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120019, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA0028, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0xA0029, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0xA0019, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0x800A1, 0x220, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x800A1, 0x220, 0, 2, { -42.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x800A1, 0x220, 0, 2, { 38.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x800A1, 0x220, 0, 2, { 118.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x231, 0, 0, { -222.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
};
MgModeSprDef D_80119EB0_mgmode[10] = {
    { 0x12001A, 0x1000, 160, 120 }, { 0x12001B, 0x9000, 0, 0 }, { 0x12001C, 0x9000, 0, 0 },
    { 0x12001D, 0x9000, 0, 0 }, { 0x12001E, 0x9000, 0, 0 }, { 0x120020, 0x9000, 0, 0 },
    { 0x12001F, 0x9000, 0, 0 }, { 0x120021, 0x9000, 0, 0 }, { 0x120022, 0x9000, 0, 0 },
    { -1, 0x0, 0, 0 },
};
MgModeSprDef D_80119F28_mgmode[10] = {
    { 0x120014, 0x5000, 160, 120 }, { 0x120023, 0xD000, 160, 120 }, { 0x120023, 0xD000, 160, 120 },
    { 0x120023, 0xD000, 160, 120 }, { 0x120023, 0xD000, 160, 120 }, { 0x12002D, 0x5000, 160, 120 },
    { 0x12002D, 0x5000, 160, 120 }, { 0x12002D, 0x5000, 160, 120 }, { 0x12002D, 0x5000, 160, 120 },
    { -1, 0x0, 0, 0 },
};
/* D_80119F28_mgmode + 0x78 */
MgModeModelDef D_80119FA0_mgmode[20] = {
    { 0x120035, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120036, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120038, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x120039, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA0063, 0xA31, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0xA0072, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0xA0070, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0xA006A, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0x800A1, 0x224, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x80000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12000C, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x12003A, 0x624, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
};
MgModeSprDef D_8011A270_mgmode[7] = {
    { 0x21001A, 0x1000, 29, 22 }, { 0x21001B, 0x1000, 39, 21 }, { 0x31, 0x1000, 49, 21 },
    { 0x31, 0x1000, 59, 21 }, { 0x31, 0x1000, 69, 21 }, { 0x31, 0x1000, 79, 21 },
    { -1, 0x0, 0, 0 },
};
MgModeSprDef D_8011A2C4_mgmode[22] = {
    { 0x12001A, 0x5000, 184, 108 }, { 0x12003B, 0xD000, 160, 120 }, { 0x12003C, 0xD000, 160, 120 },
    { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { 0xC0086, 0xD000, 160, 120 }, { 0xC008C, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { 0xC0086, 0xD000, 160, 120 }, { 0xC008C, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { 0x190009, 0xD000, 160, 120 }, { 0xC008C, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 }, { 0xC0086, 0xD000, 160, 120 },
    { -1, 0x0, 0, 0 },
};
/* per character */
u8 D_8011A3CC_mgmode[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
