#include "common.h"
#include "ovl_81.h"
#include "game/sprite.h"

// duel n3: minigame call list (2-player roulette) and coin change popups.

typedef struct ItemSlotEntry {
    /* 0x00 */ s16 obj;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 w;
    /* 0x08 */ s16 h;
} ItemSlotEntry; // sizeof 0xA

#define PREV_MINIGAME_LIST_LENGTH 10

typedef struct UnkData_CD0A0 {
    s16 unk_00;
    char unk_02[6];
    s8 recentMinigames[1][PREV_MINIGAME_LIST_LENGTH];
} UnkData_CD0A0;

typedef struct UnkSize10 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk_04[0x0C];
} UnkSize10;

extern u32 D_800D2094_main;
extern UnkData_CD0A0 D_800CC4A0_main;
extern s8 D_800CC3E0_main[];

extern u32 D_80100F38_name_81;
extern u8 D_80100ECC_name_81[];
extern u8 D_80100ED0_name_81[];
extern f32 D_80100F50_name_81[2][2];

extern ItemSlotEntry D_80102B70_name_81[5];
extern omObjData *D_80102BA4_name_81;
extern s8 D_80102BA8_name_81[5]; // generated minigame list
extern s8 D_80102BAD_name_81;
extern s16 D_80102BB0_name_81;
extern s16 D_80102BB2_name_81;
extern s16 D_80102BB4_name_81;
extern s16 D_80102BB6_name_81;
extern s32 D_80102BB8_name_81;
extern s16 D_80102BC0_name_81[2];
extern s16 D_80102BC4_name_81[2][2];
extern omObjData *D_80102BCC_name_81[2];
extern u8 D_80102BD4_name_81;
extern f32 D_80102BD8_name_81[2][2];

void func_800DF348_name_81(void);
void func_800DF49C_name_81(void);
void func_800DF594_name_81(s32);
void func_800DFBF4_name_81(void);
void func_800E0300_name_81(void);
void func_800E03F0_name_81(void);
void func_800E08D8_name_81(void);
void func_800E0D64_name_81(s32);
void func_800E0E70_name_81(s32, s32, s32, s32);

void func_800DD9A0_name_81(void) {
    if (D_800D2094_main >= (D_80100F38_name_81 + 4)) {
        HuAudFXPlay(0x104);
        D_80100F38_name_81 = D_800D2094_main;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DD9EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DE4D0_name_81);

void func_800DF154_name_81(void) {
    s32 category;
    s32 i;

    for (category = 0; category < 1; category++) {
        for (i = 0; i < PREV_MINIGAME_LIST_LENGTH; i++) {
            D_800CC4A0_main.recentMinigames[category][i] = -1;
        }
        D_800CC3E0_main[category] = 0;
    }
}

void func_800DF1B0_name_81(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80102B70_name_81); i++) {
        D_80102B70_name_81[i].obj = -1;
    }

    D_80102BA4_name_81 = NULL;
    D_80102BB2_name_81 = -1;
    D_80102BB0_name_81 = -1;
    D_80102BB6_name_81 = -1;
    D_80102BB4_name_81 = -1;
}

void func_800DF210_name_81(void) {
    ItemSlotEntry *entry;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80102B70_name_81); i++) {
        entry = &D_80102B70_name_81[i];
        if (entry->obj != -1) {
            func_8005F364_main(entry->obj);
            entry->obj = -1;
        }
    }

    if (D_80102BA4_name_81 != NULL) {
        omDelObj(D_80102BA4_name_81);
        D_80102BA4_name_81 = NULL;
    }

    if (D_80102BB0_name_81 != -1) {
        HuSprGrpKill(D_80102BB0_name_81);
        D_80102BB0_name_81 = -1;
    }

    if (D_80102BB2_name_81 != -1) {
        HuSprKill(D_80102BB2_name_81);
        D_80102BB2_name_81 = -1;
    }

    if (D_80102BB4_name_81 != -1) {
        HuSprGrpKill(D_80102BB4_name_81);
        D_80102BB4_name_81 = -1;
    }

    if (D_80102BB6_name_81 != -1) {
        HuSprKill(D_80102BB6_name_81);
        D_80102BB6_name_81 = -1;
    }
}

void func_800DF348_name_81(void) {
    void *data;

    if (D_80102BB0_name_81 == -1) {
        D_80102BB0_name_81 = HuSprGrpCreate(1, 0);
        if (D_80102BAD_name_81 == 1) {
            data = DataRead(0x130106);
        } else {
            data = DataRead(0x130116);
        }
        D_80102BB2_name_81 = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80102BB0_name_81, 0, D_80102BB2_name_81, 0);
        HuSprPriSet(D_80102BB0_name_81, 0, 0x4770);
        HuSprAttrSet(D_80102BB0_name_81, 0, 0x1000);
        func_80054904_main(D_80102BB0_name_81, 0, 0xA0, D_80100ECC_name_81[D_80102BAD_name_81] + D_80102B70_name_81[0].y);
        if (D_80102BAD_name_81 != 1) {
            func_80055420_main(D_80102BB0_name_81, 0, 0xD7, 0x3D, 0xBE);
        } else {
            func_80055420_main(D_80102BB0_name_81, 0, 0, 0x64, 0);
        }
    }
}

void func_800DF49C_name_81(void) {
    s32 files[2] = { 0x130210, 0x130105 };
    void *data;

    if (D_80102BB4_name_81 == -1) {
        D_80102BB4_name_81 = HuSprGrpCreate(1, 4);
        data = DataRead(files[D_80102BAD_name_81]);
        D_80102BB6_name_81 = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80102BB4_name_81, 0, D_80102BB6_name_81, 0);
        HuSprPriSet(D_80102BB4_name_81, 0, 0x100);
        HuSprAttrSet(D_80102BB4_name_81, 0, 0);
        func_80054904_main(D_80102BB4_name_81, 0, D_80100ED0_name_81[D_80102BAD_name_81], 0x9A);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023C8_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF594_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DFBF4_name_81);

void func_800E02B4_name_81(s32 arg0) {
    D_80102BB8_name_81 = arg0;
    if (arg0 != 1) {
        omAddPrcObj(func_800DFBF4_name_81, 0, 0, 0);
    } else {
        func_800DF594_name_81(arg0);
    }
}

void func_800E0300_name_81(void) {
    D_80102BA4_name_81->work[0] = 0;
}

void func_800E0310_name_81(u8 *output, s32 count) {
    s8 pool[256];
    s32 i;
    s32 j;
    s32 randIndex;

    for (i = 0; i <= count; i++) {
        pool[i] = i;
    }

    for (i = 0; i <= count; i++) {
        randIndex = func_800EFE20_name_81((f32)(count - i + 1));
        output[i] = pool[randIndex];

        for (j = randIndex; j < count; j++) {
            pool[j] = pool[j + 1];
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E03F0_name_81);

Process *func_800E0888_name_81(void) {
    Process *proc;
    UnkSize10 *data;

    proc = omAddPrcObj(func_800E03F0_name_81, 0, 0x2000, 0x40);
    data = HuMemMemoryAlloc(proc->heap, sizeof(UnkSize10));
    proc->user_data = data;
    data->unk_00 = 0;
    return proc;
}

void func_800E08D8_name_81(void) {
    func_800E02B4_name_81(1);
    HuPrcVSleep();
    func_800E0300_name_81();
    do {
        HuPrcVSleep();
    } while (D_80102BA4_name_81 != NULL);
    omDelPrcObj(NULL);
}

void func_800E0924_name_81(void) {
    omAddPrcObj(func_800E08D8_name_81, 0, 0x2000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0950_name_81);

void func_800E0CEC_name_81(void) {
    s32 i, j;

    for (i = 0; i < 2; i++) {
        D_80102BC0_name_81[i] = -1;
        D_80102BCC_name_81[i] = NULL;
        for (j = 0; j < 2; j++) {
            D_80102BC4_name_81[i][j] = -1;
        }
    }
}

void func_800E0D64_name_81(s32 arg0) {
    s32 i;

    if (D_80102BC0_name_81[arg0] != -1) {
        HuSprGrpKill(D_80102BC0_name_81[arg0]);
        D_80102BC0_name_81[arg0] = -1;
    }
    if (D_80102BCC_name_81[arg0] != NULL) {
        omDelObj(D_80102BCC_name_81[arg0]);
        D_80102BCC_name_81[arg0] = NULL;
    }

    for (i = 0; i < 2; i++) {
        if (D_80102BC4_name_81[arg0][i] != -1) {
            HuSprKill(D_80102BC4_name_81[arg0][i]);
            D_80102BC4_name_81[arg0][i] = -1;
        }
    }
}

void func_800E0E38_name_81(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800E0D64_name_81(i);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0E70_name_81);

void func_800E14B0_name_81(s32 player, s32 coins) {
    D_80102BD4_name_81 = 0;
    func_800E0E70_name_81(player, coins, -1, -1);
}

void func_800E14D8_name_81(s32 player, s32 coins) {
    D_80102BD4_name_81 = 1;
    func_800E0E70_name_81(player, coins, -1, -1);
}

void func_800E1504_name_81(s32 player, s32 coins, s32 x, s32 y) {
    D_80102BD4_name_81 = 2;
    D_80102BD8_name_81[player][0] = x;
    D_80102BD8_name_81[player][1] = y;
    func_800E0E70_name_81(player, coins, x, y);
}
