#include "common.h"
#include "ovl_81.h"
#include "game/sprite.h"

// duel n3: minigame call list (2-player roulette) and coin change popups.

typedef struct ItemRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ItemRect;

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
    s8 recentMinigames[2][PREV_MINIGAME_LIST_LENGTH];
} UnkData_CD0A0;

typedef struct UnkSize10 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk_04[0x0C];
} UnkSize10;

extern u32 D_800D2094_main;
extern UnkData_CD0A0 D_800CC4A0_main;
extern s8 D_800CC3E0_main[];

extern u32 D_80100F38_name_81;
extern s32 D_80100F3C_name_81;
extern s32 D_80100F40_name_81;
extern u8 D_80100E50_name_81[]; // duel minigame pools (minigame ids)
extern u8 D_80100E5C_name_81[];
extern u8 D_80100E64_name_81[];
extern u8 D_80100E84_name_81[]; // list length per category
extern u8 D_80100E88_name_81[]; // recent-minigame avoid count
extern s32 D_80100EE4_name_81[]; // first board-call file per category
extern ItemRect D_80100E8C_name_81[];
extern ItemRect D_80100EB4_name_81[];
extern u8 D_80100EEB_name_81[]; // indexed by minigame id: the table starts at 0x80100EEC
extern u8 D_80100ECC_name_81[];
extern u8 D_80100ED0_name_81[];
extern u8 D_80100ED4_name_81[];
extern u8 D_80100ED8_name_81[];
extern s8 D_80100EDC_name_81[][2];
extern f32 D_80100F50_name_81[2][2];

extern ItemSlotEntry D_80102B70_name_81[5];
extern omObjData *D_80102BA4_name_81;
extern s8 D_80102BA8_name_81[5]; // generated minigame list
extern s8 D_80102BAD_name_81;
extern s8 D_80102BAE_name_81;
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

void func_800E3868_name_81(void);
void func_800DF348_name_81(void);
s32 func_800EAA7C_name_81(s32);
void func_800DF49C_name_81(void);
void func_800DD9EC_name_81(omObjData *);
void func_800DE4D0_name_81(omObjData *);
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

void func_800DD9EC_name_81(omObjData *arg0) {
    ItemSlotEntry *entry = NULL;
    s32 i;
    s16 new_var;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.1f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                    new_var = 0xE0;
                    entry = &D_80102B70_name_81[i];
                    func_8005BA90_main(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                    func_8005BB18_main(entry->obj, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                func_80054904_main(D_80102BB0_name_81, 0, 0xA0, (D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var)));

                HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 5;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 10.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                new_var = 0xE0;
                entry = &D_80102B70_name_81[i];
                func_8005BA90_main(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                func_8005BB18_main(entry->obj, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            func_80054904_main(D_80102BB0_name_81, 0, 0xA0,
                                (D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var)));

            HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                func_800DD9A0_name_81();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = func_800EFE20_name_81((f32)D_80100E84_name_81[D_80102BAD_name_81]);
                arg0->work[3] = 0;
                func_800DF49C_name_81();
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y == 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % D_80100E84_name_81[D_80102BAD_name_81];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                    }
                }
                func_800DD9A0_name_81();
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                entry = &D_80102B70_name_81[i];
                if (i == arg0->work[1]) {
                    func_8005FBF8_main(entry->obj, 0, 0xC8, 0);
                    func_8005BEE0_main(entry->obj, 0x100);
                    func_8005BE30_main(entry->obj, 0x2328);
                } else {
                    func_8005FBF8_main(entry->obj, 0x40, 0x40, 0x80);
                    func_8005BEE0_main(entry->obj, 0);
                    func_8005BE30_main(entry->obj, 0x2710);
                }
            }

            if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                    if ((rand8() & 0xF) || (arg0->scale.y == 1.0f) || (arg0->work[1] == 0)) {
                        if ((GwSystem.show_minigame_explanations == FALSE) || (GwSystem.current_board_index == 6)) {
                            HuAudFXPlay(0x105);
                        } else {
                            HuAudFXPlay(0x112);
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 0x3C;
                        func_8005D2D4_main(D_80102B70_name_81[arg0->work[1]].obj);
                        func_8005D294_main(D_80102B70_name_81[arg0->work[1]].obj);
                        func_8005B43C_main(D_80102B70_name_81[arg0->work[1]].obj,
                                            D_80100EE4_name_81[D_80102BAD_name_81] + D_80102BA8_name_81[arg0->work[1]] - 1, -2, 4);
                        func_8005C02C_main(D_80102B70_name_81[arg0->work[1]].obj, 1);
                        func_8005C154_main(D_80102B70_name_81[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                        func_8005FBF8_main(D_80102B70_name_81[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                        func_8005BDFC_main(D_80102B70_name_81[arg0->work[1]].obj, 0);
                    } else {
                        arg0->scale.y = 1.0f;
                        arg0->work[2]--;
                        if (arg0->work[2] >= 128) {
                            arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                D_800CC4A0_main.recentMinigames[D_80102BAD_name_81][D_800CC3E0_main[D_80102BAD_name_81]] = D_80102BA8_name_81[arg0->work[2]];
                D_800CC3E0_main[D_80102BAD_name_81]++;
                D_800CC3E0_main[D_80102BAD_name_81] = D_800CC3E0_main[D_80102BAD_name_81] % (s32)D_80100E88_name_81[D_80102BAD_name_81 + D_80102BAE_name_81];
                GWMgNoSet(D_80102BA8_name_81[arg0->work[2]]);
                if ((GwSystem.current_board_index != 6) || (D_80102BAD_name_81 == 1)) {
                    func_800E3868_name_81();
                    func_800DF210_name_81();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }
    if (D_80102BB4_name_81 != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*D_80100EDC_name_81[i]); i++) {}

        func_80054904_main(D_80102BB4_name_81, 0,
                            (D_80100ED0_name_81[D_80102BAD_name_81] + D_80100EDC_name_81[i][1]),
                            (D_80100ED8_name_81[D_80102BAD_name_81] + (D_80100ED4_name_81[D_80102BAD_name_81] * arg0->work[1])));
    }
}

void func_800DE4D0_name_81(omObjData *arg0) {
    ItemSlotEntry *entry = NULL;
    s32 i;
    s16 new_var;
    s32 rnd;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.25f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                    new_var = 0xE0;
                    entry = &D_80102B70_name_81[i];
                    func_8005BA90_main(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                    func_8005BB18_main(entry->obj, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                func_80054904_main(D_80102BB0_name_81, 0, 0xA0, (D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var)));

                HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 0;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 30.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                new_var = 0xE0;
                entry = &D_80102B70_name_81[i];
                func_8005BA90_main(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                func_8005BB18_main(entry->obj, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            func_80054904_main(D_80102BB0_name_81, 0, 0xA0,
                                (D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var)));

            HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                func_800DD9A0_name_81();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = func_800EFE20_name_81((f32)D_80100E84_name_81[D_80102BAD_name_81]);
                arg0->work[3] = 0;
                func_800DF49C_name_81();
                D_80100F40_name_81 = func_800E1824_name_81(1, 0xC0, 1);
                D_80100F3C_name_81 = 0;
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y >= 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % D_80100E84_name_81[D_80102BAD_name_81];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                    }
                }
                func_800DD9A0_name_81();
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                entry = &D_80102B70_name_81[i];
                if (i == arg0->work[1]) {
                    func_8005FBF8_main(entry->obj, 0, 0xC8, 0);
                    func_8005BEE0_main(entry->obj, 0x100);
                    func_8005BE30_main(entry->obj, 0x2328);
                } else {
                    func_8005FBF8_main(entry->obj, 0x40, 0x40, 0x80);
                    func_8005BEE0_main(entry->obj, 0);
                    func_8005BE30_main(entry->obj, 0x2710);
                }
            }

            if (D_80100F3C_name_81 == 0) {
                if (func_800F37B8_name_81(GwSystem.current_player_index) != 0) {
                    D_80100F3C_name_81 = 1;
                } else if (D_800C9520_main[GwPlayer[GwSystem.current_player_index].pad] & A_BUTTON) {
                    D_80100F3C_name_81 = 1;
                }
            } else {
                if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
                    arg0->scale.x -= 0.02;
                }

                if (arg0->scale.x <= 0.08f) {
                    arg0->scale.x = 0.08f;
                    if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                        if (arg0->scale.y != 0.0f) {
                        pick:
                            HuAudFXPlay(0x105);
                            switch ((s8)(D_80102BA8_name_81[arg0->work[2]] - 1)) {
                                case 0:
                                case 5:
                                    func_800FFAE0_name_81(-1, 4);
                                    break;
                                case 1:
                                case 4:
                                case 6:
                                case 7:
                                    func_800FFAE0_name_81(-1, 2);
                                    break;
                                case 8:
                                    func_800FFAE0_name_81(-1, 1);
                                    break;
                                case 9:
                                    func_800FFAE0_name_81(-1, 3);
                                    break;
                            }

                            arg0->work[0] = 2;
                            arg0->work[3] = 0x3C;
                            func_8005D2D4_main(D_80102B70_name_81[arg0->work[1]].obj);
                            func_8005D294_main(D_80102B70_name_81[arg0->work[1]].obj);
                            func_8005B43C_main(D_80102B70_name_81[arg0->work[1]].obj,
                                                D_80100EE4_name_81[D_80102BAD_name_81] + D_80102BA8_name_81[arg0->work[1]] - 1, -2, 4);
                            func_8005C02C_main(D_80102B70_name_81[arg0->work[1]].obj, 1);
                            func_8005C154_main(D_80102B70_name_81[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                            func_8005FBF8_main(D_80102B70_name_81[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                            func_8005BDFC_main(D_80102B70_name_81[arg0->work[1]].obj, 0);
                        } else {
                            rnd = func_800EFE20_name_81(100.0f);
                            if (rnd < 15) {
                                goto pick;
                            }
                            if (rnd < 65) {
                                arg0->scale.y = 1.0f;
                                arg0->work[2] += 1;
                                arg0->work[2] = arg0->work[2] % D_80100E84_name_81[D_80102BAD_name_81];
                            } else if (rnd < 85) {
                                arg0->scale.y = 1.0f;
                                arg0->work[2] += 2;
                                arg0->work[2] = arg0->work[2] % D_80100E84_name_81[D_80102BAD_name_81];
                            } else {
                                if (rnd < 95) {
                                    arg0->scale.y = -1.0f;
                                } else {
                                    arg0->scale.y = -1.0f;
                                    arg0->work[2]--;
                                    if (arg0->work[2] >= 128) {
                                        arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                                    }
                                }
                                arg0->work[2]--;
                                if (arg0->work[2] >= 128) {
                                    arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                D_800CC4A0_main.recentMinigames[D_80102BAD_name_81][D_800CC3E0_main[D_80102BAD_name_81]] = D_80102BA8_name_81[arg0->work[2]];
                D_800CC3E0_main[D_80102BAD_name_81]++;
                D_800CC3E0_main[D_80102BAD_name_81] = D_800CC3E0_main[D_80102BAD_name_81] % (s32)D_80100E88_name_81[D_80102BAD_name_81 + D_80102BAE_name_81];
                GWMgNoSet(D_80102BA8_name_81[arg0->work[2]]);
                if ((GwSystem.current_board_index != 6) || (D_80102BAD_name_81 == 1)) {
                    func_800E1854_name_81(D_80100F40_name_81);
                    func_800DF210_name_81();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }
    if (D_80102BB4_name_81 != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*D_80100EDC_name_81[i]); i++) {}

        func_80054904_main(D_80102BB4_name_81, 0,
                            (D_80100ED0_name_81[D_80102BAD_name_81] + D_80100EDC_name_81[i][1]),
                            (D_80100ED8_name_81[D_80102BAD_name_81] + (D_80100ED4_name_81[D_80102BAD_name_81] * arg0->work[1])));
    }
}

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

// NON_MATCHING: logic checked against the asm; differs only in which loop invariants are hoisted
// (&D_80100E88_name_81[pool] vs the recent-minigame row base) and the register allocation that follows.
#ifdef NON_MATCHING
void func_800DF594_name_81(s32 arg0) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    ItemRect *rects[2] = { D_80100E8C_name_81, D_80100EB4_name_81 };
    u8 *lists[4] = { D_80100E50_name_81, D_80100E64_name_81, D_80100E5C_name_81, D_80100E64_name_81 };
    u8 counts[4] = { 10, 30, 7, 30 };
    s32 prio[2] = { 5, 20 };
    ItemSlotEntry *entry;
    omObjData *obj;
    s32 cat;
    s32 hard;
    s32 pool;
    s32 i;
    s32 j;
    s32 k;

    cat = arg0;
    D_80102BAD_name_81 = cat;
    D_80102BAE_name_81 = hard = (_CheckFlag(0x20) != 0) * 2;
    pool = cat + hard;

    for (i = 0; i < D_80100E84_name_81[cat]; i++) {
        entry = &D_80102B70_name_81[i];
        entry->x = rects[cat][i].x;
        entry->y = rects[cat][i].y;
        entry->w = rects[cat][i].w;
        entry->h = rects[cat][i].h;

        entry->obj = func_8005A968_main((entry->x + (entry->w / 2)), (entry->y + (entry->h / 2)), entry->w, entry->h, 0, prio[cat]);
        func_8005BE30_main(entry->obj, 0x2328);
        func_80060144_main(entry->obj);
        func_8005BCA4_main(entry->obj, entry->w / 2, entry->h / 2);
        func_8005BEE0_main(entry->obj, 0);

        while (1) {
            D_80102BA8_name_81[i] = lists[pool][func_800EFE20_name_81(counts[pool])];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (D_80102BA8_name_81[j] == D_80102BA8_name_81[i]) {
                    break;
                }
            }

            if (j != i) {
                continue;
            }

            if (cat != 1) {
                for (k = 0; k < D_80100E88_name_81[pool]; k++) {
                    if (D_80102BA8_name_81[i] == D_800CC4A0_main.recentMinigames[cat][k]) {
                        break;
                    }
                }

                if (k != D_80100E88_name_81[pool]) {
                    continue;
                }
            } else {
                switch ((s8)(D_80102BA8_name_81[i] - 1)) {
                    case 0:
                        if (player->star == 5) {
                            continue;
                        }
                        break;
                    case 1:
                        if ((GwPlayer[0].clink == GwPlayer[1].clink) && (GwPlayer[0].cidx == GwPlayer[1].cidx)) {
                            continue;
                        }
                        break;
                    case 2:
                        if (GwPlayer[GwSystem.current_player_index].coin == 0) {
                            continue;
                        }
                        break;
                    case 6:
                        if ((player->stats.partners.frontID != -1) && (player->stats.partners.frontPoweredUp == 2)) {
                            continue;
                        }
                        if ((player->stats.partners.backID != -1) && (player->stats.partners.backPoweredUp == 2)) {
                            continue;
                        }
                        if ((player->stats.partners.frontID == -1) && (player->stats.partners.backID == -1)) {
                            continue;
                        }
                        break;
                    case 7:
                        if ((player->stats.partners.frontID != -1) && (player->stats.partners.frontPoweredUp == 1)) {
                            continue;
                        }
                        if ((player->stats.partners.backID != -1) && (player->stats.partners.backPoweredUp == 1)) {
                            continue;
                        }
                        /* fallthrough */
                    case 8:
                        if ((player->stats.partners.frontID == -1) && (player->stats.partners.backID == -1)) {
                            continue;
                        }
                        break;
                    case 9:
                        if (func_800EAA7C_name_81(GwPlayer[GwSystem.current_player_index].chr + 0xB) != 0) {
                            break;
                        }
                        /* fallthrough */
                    case 5:
                        if (func_800EAA7C_name_81(GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr + 0xB) == 0) {
                            continue;
                        }
                        break;
                }
            }
            break;
        }

        func_8005D2D4_main(entry->obj);

        if ((D_80102BAD_name_81 != 1) && (GWMgUnlockCheck(D_80102BA8_name_81[i] - 1) == FALSE)) {
            func_8005B43C_main(entry->obj, 0x4748, -2, 4);
        } else {
            func_8005B43C_main(entry->obj, D_80102BA8_name_81[i] + D_80100EE4_name_81[cat] - 1, -2, 4);
        }

        func_8005C02C_main(entry->obj, D_80100EEB_name_81[D_80102BA8_name_81[i]]);
        func_8005BDFC_main(entry->obj, 0);
    }

    if (D_80102BAD_name_81 != 1) {
        D_80102BA4_name_81 = obj = omAddObj(-0x8000, 0, 0, -1, func_800DD9EC_name_81);
        obj->work[1] = 5;
    } else {
        D_80102BA4_name_81 = obj = omAddObj(-0x8000, 0, 0, -1, func_800DE4D0_name_81);
        obj->work[1] = 0;
    }
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    func_800DF348_name_81();
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023C8_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF594_name_81);
#endif

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

void func_800E0950_name_81(omObjData *arg0) {
    Vec sp10;
    f32 sp20[2];
    s32 i;

    switch (D_80102BD4_name_81) {
        case 1:
            sp10.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
            sp10.y = GwPlayer[arg0->work[3]].player_obj->coords.y + 30.0f;
            sp10.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
            MBDCamera3Dto2D(&sp10, (Vec2f *)sp20);
            break;
        case 0:
            sp20[0] = D_80100F50_name_81[arg0->work[3]][0];
            sp20[1] = D_80100F50_name_81[arg0->work[3]][1];
            break;
        default:
            sp20[0] = D_80102BD8_name_81[arg0->work[3]][0];
            sp20[1] = D_80102BD8_name_81[arg0->work[3]][1];
            break;
    }

    if (arg0->work[0] < 10) {
        if (arg0->rot.x > 0.0f) {
            arg0->trans.y -= 1.5f;
        } else {
            arg0->trans.y += 1.5f;
        }
        func_80054904_main(D_80102BC0_name_81[arg0->work[3]], 0, sp20[0], (sp20[1] + arg0->trans.y));
    } else if (arg0->work[0] >= 0x18U) {
        arg0->scale.x += 0.4f;
        arg0->scale.y -= 0.3f;

        if (arg0->scale.x < 0.0f) {
            arg0->scale.x = 0.0f;
        }
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(D_80102BC0_name_81[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    } else if (arg0->work[0] >= 22) {
        arg0->scale.y -= 0.3f;
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(D_80102BC0_name_81[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    }

    if (arg0->work[0] >= 30) {
        func_800E0D64_name_81(arg0->work[3]);
        return;
    }

    arg0->work[0]++;
}

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

void func_800E0E70_name_81(s32 arg0, s32 coins, s32 x, s32 y) {
    Vec sp18;
    f32 sp28[2];
    s16 temp_v0_2;
    s32 var_s1;
    s32 var_s2;
    void *temp_v0_3;
    s32 i;

    if (D_80102BC0_name_81[arg0] == -1) {
        if (coins < -999) {
            coins = -999;
        }
        if (coins > 999) {
            coins = 999;
        }
        if (coins == 0) {
            HuAudFXPlay(0x203);
        }
        D_80102BCC_name_81[arg0] = omAddObj(-0x8000, 0, 0, -1, func_800E0950_name_81);
        D_80102BCC_name_81[arg0]->work[0] = 0;
        D_80102BCC_name_81[arg0]->rot.x = coins;
        D_80102BCC_name_81[arg0]->trans.y = 0.0f;
        D_80102BCC_name_81[arg0]->scale.x = 1.0f;
        D_80102BCC_name_81[arg0]->scale.y = 2.0f;
        D_80102BCC_name_81[arg0]->work[3] = arg0;
        D_80102BCC_name_81[arg0]->work[1] = 6;
        D_80102BC0_name_81[arg0] = temp_v0_2 = HuSprGrpCreate(6, 5);
        temp_v0_3 = DataRead(0x00130112);
        D_80102BC4_name_81[arg0][0] = func_80055810_main(temp_v0_3);
        DataClose(temp_v0_3);

        if (coins > 0) {
            temp_v0_3 = DataRead(0x00130213);
        } else {
            temp_v0_3 = DataRead(0x00130214);
        }

        D_80102BC4_name_81[arg0][1] = func_80055810_main(temp_v0_3);
        DataClose(temp_v0_3);
        func_80055024_main(temp_v0_2, 1, D_80102BC4_name_81[arg0][0], 0);
        HuSprPriSet(temp_v0_2, 1, 0x2010U);
        HuSprAttrSet(temp_v0_2, 1, 0x1000);

        var_s2 = 2;
        func_80055024_main(temp_v0_2, 2, D_80102BC4_name_81[arg0][1], 0);
        func_800550F4_main(temp_v0_2, 2, 1);

        if (coins > 0) {
            func_80055140_main(temp_v0_2, var_s2, 0xA, 0);
        } else {
            func_80055140_main(temp_v0_2, var_s2, 0xB, 0);
        }

        HuSprPriSet(temp_v0_2, var_s2, 0x2010);
        HuSprAttrSet(temp_v0_2, var_s2, 0x1000);

        var_s2++;
        coins = (coins < 0) ? -coins : coins;

        if (coins >= 100) {
            func_80055024_main(temp_v0_2, var_s2, D_80102BC4_name_81[arg0][1], 0);
            func_800550F4_main(temp_v0_2, var_s2, 1);
            func_80055140_main(temp_v0_2, var_s2, (coins / 100), 0);
            HuSprPriSet(temp_v0_2, var_s2, 0x2010);
            HuSprAttrSet(temp_v0_2, var_s2, 0x1000);
            var_s2++;
        }

        if (coins >= 10) {
            func_80055024_main(temp_v0_2, var_s2, D_80102BC4_name_81[arg0][1], 0);
            func_800550F4_main(temp_v0_2, var_s2, 1);
            func_80055140_main(temp_v0_2, var_s2, ((coins / 10) % 10), 0);
            HuSprPriSet(temp_v0_2, var_s2, 0x2010U);
            HuSprAttrSet(temp_v0_2, var_s2, 0x1000);
            var_s2 += 1;
        }

        coins = coins % 10;

        func_80055024_main(temp_v0_2, var_s2, D_80102BC4_name_81[arg0][1], 0);
        func_800550F4_main(temp_v0_2, var_s2, 1);
        func_80055140_main(temp_v0_2, var_s2, coins, 0);
        HuSprPriSet(temp_v0_2, var_s2, 0x2010U);
        HuSprAttrSet(temp_v0_2, var_s2, 0x1000);
        var_s2++;

        if (x == -1 && y == -1) {
            if (D_80102BD4_name_81 != 0) {
                sp18.x = GwPlayer[arg0].player_obj->coords.x;
                sp18.y = GwPlayer[arg0].player_obj->coords.y + 30.0f;
                sp18.z = GwPlayer[arg0].player_obj->coords.z;
                MBDCamera3Dto2D(&sp18, (Vec2f *)sp28);
                func_80054904_main(temp_v0_2, 0, sp28[0], sp28[1]);
            } else {
                func_80054904_main(temp_v0_2, 0, D_80100F50_name_81[arg0][0], D_80100F50_name_81[arg0][1]);
            }
        } else {
            func_80054904_main(temp_v0_2, 0, x, y);
        }

        var_s1 = (var_s2 - 2);
        var_s1 = -(var_s1 * 8);

        for (i = 1; i < var_s2; i++) {
            func_80054904_main(temp_v0_2, i, var_s1, 0);
            var_s1 += 16;
        }

        for (; var_s2 < 6; var_s2++) {
            HuSprAttrSet(temp_v0_2, var_s2, 0x8000);
        }
    }
}

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
