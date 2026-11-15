#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"

void func_80105E0C_mgresultbattle(void);
void func_80105EF4_mgresultbattle(void);
void func_801060A4_mgresultbattle(void);
void func_80106660_mgresultbattle(void);
void func_80106BA0_mgresultbattle(void);
void func_80107400_mgresultbattle(void);
void func_80107D10_mgresultbattle(void);
void func_80108130_mgresultbattle(void);
void MBBackCreate(s32, s32);
void func_80105CAC_mgresultbattle(omObjData *);
void func_80105E64_mgresultbattle(omObjData *);
void func_80105F50_mgresultbattle(void);
void func_80106908_mgresultbattle(void);
void func_80106910_mgresultbattle(omObjData *);
void func_80105F78_mgresultbattle(Gfx **, s32, s32);
void func_801075FC_mgresultbattle(void);
void MBBackKill(void);
void MBBackClose(void);

extern s8 D_801088D0_mgresultbattle;
extern s32 D_801088D4_mgresultbattle;
extern s8 D_801088D8_mgresultbattle;

extern s8 D_80108F8C_mgresultbattle[4];
extern s32 D_80108F70_mgresultbattle;
extern s32 D_800A178C_main[][6];

typedef struct ResultFigure {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ResultFigure; // sizeof 0x08 on N64

extern ResultFigure D_80108F50_mgresultbattle[4];
extern const Vec D_801089D0_mgresultbattle[4];
extern u16 D_800CC698_main;
extern const f32 D_80108920_mgresultbattle[8][4];
extern const s8 D_801089A0_mgresultbattle[8];
extern s32 D_80108908_mgresultbattle[];

void func_801059A0_mgresultbattle(void) {
    s16 var_a0_2;
    s16 var_a1;
    s16 i;
    s16 j;

    var_a1 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_80108F8C_mgresultbattle[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    func_800142A0_main(0x78);
    omInitObjMan(0x1E, 0x1E);
    func_8000B690_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);

    for (var_a0_2 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].bonusCoin == 3) {
            var_a0_2++;
        }
    }

    if (var_a0_2 >= 4) {
        func_80037258_main();
        MBBackKill();
        MBBackClose();
        omOvlReturnEx(1);
        return;
    }
    func_801060A4_mgresultbattle();
    omAddPrcObj(func_80108130_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107400_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107D10_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106660_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106BA0_mgresultbattle, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, func_80105CAC_mgresultbattle);
    omAddObj(0, 0, 0, -1, func_80105E64_mgresultbattle);
    func_80105EF4_mgresultbattle();
    func_80105E0C_mgresultbattle();
    WipeCreateIn(0xFF, 0x10);
}

void func_80105CAC_mgresultbattle(omObjData *obj) {
    s32 state = D_801088D0_mgresultbattle;
    s32 i;
    s32 coin;
    s16 newCoin;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x15);
        D_801088D4_mgresultbattle = 0;
        state++;
        break;
    case 1:
        state++;
        break;
    case 2:
        if (D_801088D4_mgresultbattle++ >= 6) {
            func_801075FC_mgresultbattle();
            D_801088D4_mgresultbattle = 0;
            state++;
        }
        break;
    case 4:
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            coin = (s16)GwPlayer[i].coin + (s16)GwPlayer[i].gameCoin;
            newCoin = 999;
            if (coin < 1000) {
                newCoin = coin;
            }
            GwPlayer[i].coin = newCoin;
            MBPlayerCoinAdd(i, 0);
        }
        WipeCreateOut(0, 0x14);
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
        state++;
        break;
    case 5:
        if (WipeStatGet() == 0) {
            func_80037258_main();
            MBBackKill();
            MBBackClose();
            omOvlReturnEx(1);
        }
        break;
    }
    D_801088D0_mgresultbattle = state;
}

void func_80105E0C_mgresultbattle(void) {
    CZoom = 2300.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 390.0f;
    Center.z = -460.0f;
}

void func_80105E64_mgresultbattle(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_801088D8_mgresultbattle == 0) {
            WipeCreateOut(0, 0x14);
            D_801088D8_mgresultbattle = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(0x1E);
            func_8004AB0C_main(0x1E);
            func_80037258_main();
            MBBackKill();
            MBBackClose();
            omOvlReturnEx(1);
        }
    }
}

void func_80105EF4_mgresultbattle(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E6630_shared_board((u32)hvq_data_ROM_START);

    if (!(system->playMode & 2)) {
        MBBackCreate(D_80108908_mgresultbattle[system->current_board_index], 0);
    } else {
        MBBackCreate(0x17, 0);
    }
    func_80105F50_mgresultbattle();
}

void func_80105F50_mgresultbattle(void) {
    func_8001AC8C_main(0, func_80105F78_mgresultbattle, 0);
}

void func_80105F78_mgresultbattle(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                   G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 127);
    gDPSetRenderMode(g++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode(g++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetTextureLUT(g++, G_TT_NONE);
    gDPSetFillColor(g++, 0x10001);
    gDPFillRectangle(g++, 0, 0, 319, 239);
    *gfx = g;
}

#ifdef NON_MATCHING
// battleres A: masked 0, raw 20 (register allocation of the counters).
// Splits the battle pot (D_800CC698_main) by placing; GwPlayer[].bonusCoin holds the placing here.
void func_801060A4_mgresultbattle(void) {
    s32 order[4];
    s32 rank[4];
    s8 count[4];
    s32 n;
    s32 i;
    s32 j;
    s32 r;
    s32 type;
    s32 total;

    for (n = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        n += GwPlayer[i].bonusCoin >= 3;
    }
    r = 0;
    if (n >= 4) {
        D_80108F70_mgresultbattle = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            GwPlayer[i].gameCoin = 0;
            GwPlayer[i].coin += GwPlayer[i].checkCoin;
        }
        return;
    }

    for (n = 0, j = 0; j < 4; j++) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (j == GwPlayer[i].bonusCoin) {
                n++;
                rank[i] = r;
            }
        }
        r += n;
        n = 0;
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        GwPlayer[i].bonusCoin = rank[i];
    }
    for (i = 0; i < 4; i++) {
        count[i] = 0;
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        count[GwPlayer[i].bonusCoin]++;
    }

    type = 0;
    if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1) {
    } else if (count[0] == 2 && count[2] == 2) {
        type = 2;
    } else if (count[0] == 2) {
        type = 1;
    } else if (count[0] == 3) {
        type = 3;
    } else if (count[1] == 2) {
        type = 4;
    } else if (count[1] == 3) {
        type = 5;
    } else if (count[2] == 2) {
        type = 6;
    } else if (count[0] == 4) {
        type = 7;
    }

    total = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (D_801089A0_mgresultbattle[type] == 0) {
            GwPlayer[i].gameCoin = D_800CC698_main * D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin];
        } else if (D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin] != 0.0f) {
            GwPlayer[i].gameCoin = D_800CC698_main / D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin];
        } else {
            GwPlayer[i].gameCoin = 0;
        }
        total += GwPlayer[i].gameCoin;
    }

    D_80108F70_mgresultbattle = D_800CC698_main - total;
    switch (type) {
    case 4:
        if (D_80108F70_mgresultbattle == 2) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (GwPlayer[i].bonusCoin == 1) {
                    GwPlayer[i].gameCoin += 1;
                }
            }
            D_80108F70_mgresultbattle = 0;
        }
        break;
    case 5:
        if (D_80108F70_mgresultbattle == 3) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (GwPlayer[i].bonusCoin == 1) {
                    GwPlayer[i].gameCoin += 1;
                }
            }
            D_80108F70_mgresultbattle = 0;
        }
        break;
    case 6:
        if (D_80108F70_mgresultbattle == 2) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (GwPlayer[i].bonusCoin == 0) {
                    GwPlayer[i].gameCoin += 2;
                    break;
                }
            }
            D_80108F70_mgresultbattle = 0;
        }
        break;
    }

    n = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r = D_80108F8C_mgresultbattle[j];
            if (i == GwPlayer[r].bonusCoin) {
                order[n] = r;
                n++;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_80108F8C_mgresultbattle[i] = order[i];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801060A4_mgresultbattle);
#endif

// Creates the four player figures (character and a shadow model) and runs their per-frame hooks.
void func_80106660_mgresultbattle(void) {
    omObjData *obj;
    s32 i;
    s32 chr;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(0x14, 4, 8, -1, NULL);
        D_80108F50_mgresultbattle[i].obj = obj;
        chr = GwPlayer[D_80108F8C_mgresultbattle[i]].chr;
        obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x2B9);
        func_8001C814_main(obj->model[1], 2, 2);
        obj->model[2] = func_8000B108_main(9, 0x2B9);
        Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 0.0f);
        func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
        func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
        func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x36));
        func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x25));
        func_8001C5B4_main(obj->model[1], obj->motion[0]);
        func_8001C814_main(obj->model[1], 2, 2);
        Hu3DModelPosSet(obj->model[1], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);
        Hu3DModelPosSet(obj->model[2], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);
        obj->trans.x = 0.0f;
        obj->trans.y = 0.0f;
        obj->trans.z = 0.0f;
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, 0.0f);
        omPrcSetDestructor(0, func_80106908_mgresultbattle);
        D_80108F50_mgresultbattle[i].func = func_80106910_mgresultbattle;
    }
    while (1) {
        for (i = 0; i < 4; i++) {
            D_80108F50_mgresultbattle[i].func(obj);
            HuPrcVSleep();
        }
    }
}

void func_80106908_mgresultbattle(void) {
}

void func_80106910_mgresultbattle(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80106918_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801069FC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80106BA0_mgresultbattle);

void func_80106E98_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80106EA0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80106ED0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107260_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108908_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108920_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_801089A0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107400_mgresultbattle);

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801075FC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107610_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107B5C_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107BDC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107C44_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107CA4_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107D10_mgresultbattle);

void func_80107F94_mgresultbattle(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_801089C0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_801089D0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_801089D4_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_801089D8_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108A00_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108A10_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80107F9C_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801080A0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80108130_mgresultbattle);

void func_8010829C_mgresultbattle(void) {
}

void func_801082A4_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801082AC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_801082C0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80108510_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F3780", func_80108858_mgresultbattle);
