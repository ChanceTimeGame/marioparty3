#include "mgresultdealer.h"

#ifdef NON_MATCHING
/* masked 34, 7 short: retail rematerialises &D_80109A70_mgresultdealer after each call (the same residue as mgresultduel func_80107710) */
/* the coins' process: 40 coin sprites and 40 sparkles */
void func_801074A0_mgresultdealer(void) {
    omObjData *obj;
    void *data;
    s8 i;

    obj = omAddObj(0x14, 0x51, 0, -1, NULL);
    D_8010A274_mgresultdealer.obj = obj;
    data = DataRead(0x210026);
    D_80109A70_mgresultdealer[0] = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80109A70_mgresultdealer[0]].model, 0x70000000, 0x70000000);
    for (i = 0; i < 40; i++) {
        D_80109A78_mgresultdealer[i].active = 0;
        D_80109A78_mgresultdealer[i].spr = func_80014618_main(D_80109A70_mgresultdealer[0], 8);
        D_80109A78_mgresultdealer[i].time = 0;
        obj->model[i + 1] = D_800CBB60_main[D_80109A78_mgresultdealer[i].spr].model;
        Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        func_8001C8A8_main(obj->model[i + 1], 1);
        func_8001C92C_main(obj->model[i + 1], 2.0f);
        /* retail scales sprite slot i + 1's model, not this coin's */
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].model, 1.5f, 1.5f, 1.5f);
    }
    data = DataRead(0xC);
    D_80109A70_mgresultdealer[1] = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80109A70_mgresultdealer[1]].model, 0x70000000, 0x70000000);
    Hu3DModelScaleSet(D_800CBB60_main[D_80109A70_mgresultdealer[1]].model, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 40; i++) {
        D_80109E38_mgresultdealer[i].active = 0;
        D_80109E38_mgresultdealer[i].spr = func_80014618_main(D_80109A70_mgresultdealer[1], 8);
        D_80109E38_mgresultdealer[i].time = 0;
        obj->model[i + 41] = D_800CBB60_main[D_80109E38_mgresultdealer[i].spr].model;
        Hu3DModelPosSet(obj->model[i + 41], 0.0f, 400.0f, 0.0f);
        func_8001C8A8_main(obj->model[i + 41], 1);
        func_8001C92C_main(obj->model[i + 41], 1.0f);
        /* likewise slot i + 41 */
        Hu3DModelScaleSet(D_800CBB60_main[i + 41].model, 3.0f, 3.0f, 3.0f);
    }
    obj->model[0] = -1;
    D_80109910_mgresultdealer = 0;
    D_80109911_mgresultdealer = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_80107E3C_mgresultdealer);
    D_8010A274_mgresultdealer.func = func_80107888_mgresultdealer;
    while (1) {
        D_8010A274_mgresultdealer.func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801074A0_mgresultdealer);
#endif

#ifdef NON_MATCHING
/* masked 4: retail loads D_800D408C_main after the bank index arithmetic */
/* drop coins (one, or with 20+ to go one or two, every D_80109924 frames) and let them fall onto the table */
void func_80107888_mgresultdealer(omObjData *obj) {
    DealerSprModel *spr;
    DealerSprAnim *anim;
    f32 x;
    f32 y;
    f32 z;
    s8 i;
    s8 n;
    s32 drops;
    s16 falling;
    s8 dropping;

    if (D_80109910_mgresultdealer != 0) {
        if ((dropping = D_8010991C_mgresultdealer < D_80109920_mgresultdealer) == 1) {
            n = 0;
            for (i = 0; i < 40; i++) {
                if (D_80109A78_mgresultdealer[i].active == 0
                    && D_80109914_mgresultdealer % D_80109924_mgresultdealer == 0) {
                    spr = &D_800CBB60_main[D_80109A78_mgresultdealer[i].spr];
                    anim = &D_800D408C_main[spr->bank].anims[spr->anim];
                    func_8001C258_main(obj->model[i + 1], 4, 0);
                    if (D_80109918_mgresultdealer >= 20) {
                        drops = (rand8() & 1) + 1;
                    } else {
                        drops = 1;
                    }
                    Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
                    D_80109A78_mgresultdealer[i].x = (rand8() % 60) - 30;
                    D_80109A78_mgresultdealer[i].y = 400.0f;
                    D_80109A78_mgresultdealer[i].z = (rand8() % 60) - 30;
                    D_80109A78_mgresultdealer[i].active = 1;
                    D_80109A78_mgresultdealer[i].vy = 0.98f;
                    spr->step = rand8() % anim->stepCount;
                    spr->time = 0;
                    if (++D_8010991C_mgresultdealer >= D_80109920_mgresultdealer) {
                        break;
                    }
                    if (++n >= drops) {
                        break;
                    }
                }
            }
        }
        falling = 0;
        for (i = 0; i < 40; i++) {
            if (D_80109A78_mgresultdealer[i].active == 1) {
                x = D_80109A78_mgresultdealer[i].x;
                y = D_80109A78_mgresultdealer[i].y;
                z = D_80109A78_mgresultdealer[i].z;
                Hu3DModelPosSet(obj->model[i + 1], x, y, z);
                D_80109A78_mgresultdealer[i].y -= D_80109A78_mgresultdealer[i].vy;
                D_80109A78_mgresultdealer[i].vy += 0.98f;
                D_80109A78_mgresultdealer[i].time++;
                if (y <= 152.5f) {
                    D_80109A78_mgresultdealer[i].active = 0;
                    func_8001C258_main(obj->model[i + 1], 4, 4);
                    func_8001C258_main(obj->model[i + 41], 4, 0);
                    Hu3DModelPosSet(obj->model[i + 41], x, y, z);
                    func_8001C6A8_main(obj->model[i + 41], 0.0f);
                    func_80014714_main(D_80109E38_mgresultdealer[i].spr, 0);
                    HuAudFXPlay(9);
                    if (D_8010992C_mgresultdealer == 0) {
                        if (!(GwPlayer[D_8010A266_mgresultdealer[0]].stat & 1)) {
                            omVibrate(D_8010A266_mgresultdealer[0], 5, 0, 5);
                        }
                        D_8010992C_mgresultdealer = 1;
                    }
                }
                falling++;
            }
        }
        if (falling == 0 && dropping != 1) {
            if (D_80109928_mgresultdealer == 0) {
                HuAudFXPlay(0x517);
                D_80109928_mgresultdealer = 1;
            }
            D_80109911_mgresultdealer = 1;
        }
        D_80109914_mgresultdealer++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80107888_mgresultdealer);
#endif

void func_80107E3C_mgresultdealer(void) {
}

/* start dropping coins coins (capped at 999; at most 50 shown, faster the more there are) */
void func_80107E44_mgresultdealer(s32 coins) {
    omObjData *obj;
    s32 n;
    s8 i;

    obj = D_8010A274_mgresultdealer.obj;
    if (coins > 0) {
        n = 999;
        if (coins < 1000) {
            n = coins;
        }
        coins = n;
        D_80109918_mgresultdealer = coins;
        D_8010991C_mgresultdealer = 0;
        D_80109914_mgresultdealer = 0;
        if (coins <= 50) {
            D_80109920_mgresultdealer = coins;
        } else {
            D_80109920_mgresultdealer = 50;
        }
        if (coins > 40) {
            D_80109924_mgresultdealer = 100 / (D_80109920_mgresultdealer + 1);
        } else if (coins > 20) {
            D_80109924_mgresultdealer = 80 / (D_80109920_mgresultdealer + 1);
        } else {
            D_80109924_mgresultdealer = 60 / (D_80109920_mgresultdealer + 1);
        }
        for (i = 0; i < 40; i++) {
            D_80109A78_mgresultdealer[i].active = 0;
            D_80109A78_mgresultdealer[i].time = 0;
            D_80109A78_mgresultdealer[i].x = D_80109A78_mgresultdealer[i].y = D_80109A78_mgresultdealer[i].z = 0.0f;
            D_80109A78_mgresultdealer[i].vy = 0.98f;
            func_8001C258_main(obj->model[i + 1], 4, 4);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
        D_80109910_mgresultdealer = 1;
        D_80109911_mgresultdealer = 0;
    }
}

s8 func_80108034_mgresultdealer(void) {
    return D_80109911_mgresultdealer;
}

/* the fade process: a full-screen IA4 picture drawn with a fading alpha */
void func_80108040_mgresultdealer(void) {
    omObjData *obj;
    s16 spr;
    s16 grp;
    HuSprite *sprite;

    obj = omAddObj(0x14, 1, 0, -1, NULL);
    D_8010A26C_mgresultdealer.obj = obj;
    spr = func_8000B838_main(0x190001);
    D_8010A204_mgresultdealer = spr;
    grp = HuSprGrpCreate(1, 0);
    HuSprAttrSet(grp, 0, 0x8000);
    func_80055024_main(grp, 0, spr, 0);
    sprite = HuSprGet(grp, 0);
    D_8010A208_mgresultdealer = sprite;
    D_8010A20C_mgresultdealer = sprite->unk_84->unk00->unk00;
    D_8010A200_mgresultdealer = func_8001AC8C_main(0, func_801082A8_mgresultdealer, 2);
    func_8001C8A8_main(D_8010A200_mgresultdealer, 1);
    D_80109930_mgresultdealer = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_80108258_mgresultdealer);
    D_8010A26C_mgresultdealer.func = func_80108194_mgresultdealer;
    while (1) {
        D_8010A26C_mgresultdealer.func(obj);
        HuPrcVSleep();
    }
}

void func_80108194_mgresultdealer(omObjData *obj) {
    f32 step;

    if (D_80109930_mgresultdealer != 0) {
        step = 8.5f;
        func_80108560_mgresultdealer(D_80109934_mgresultdealer * step);
        if (++D_80109934_mgresultdealer >= 30) {
            func_80108560_mgresultdealer(0xFF);
            D_80109931_mgresultdealer = 1;
            D_80109930_mgresultdealer = 0;
        }
    }
}

void func_80108258_mgresultdealer(void) {
}

void func_80108260_mgresultdealer(void) {
    D_80109930_mgresultdealer = 1;
    D_80109931_mgresultdealer = 0;
    D_80109934_mgresultdealer = 0;
    func_80108544_mgresultdealer();
    func_80108560_mgresultdealer(0);
}

s8 func_8010829C_mgresultdealer(void) {
    return D_80109931_mgresultdealer;
}

/* draw hook: the picture in 24 bands of 10 lines */
void func_801082A8_mgresultdealer(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *g;
    s32 y;
    s32 alpha;

    if (D_80109938_mgresultdealer != 0) {
        alpha = D_8010993A_mgresultdealer;
        g = *gfx;
        gDPPipeSync(g++);
        gDPSetCycleType(g++, G_CYC_1CYCLE);
        gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                      G_LOD | G_SHADING_SMOOTH);
        gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPSetTexturePersp(g++, G_TP_NONE);
        gDPSetPrimColor(g++, 0, 0, 0, 0, 0, alpha);
        gDPSetRenderMode(g++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(g++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetTextureLUT(g++, G_TT_NONE);
        for (y = 0; y < 240; y += 10) {
            gDPLoadTextureTile_4b(g++, D_8010A20C_mgresultdealer, G_IM_FMT_I, 320, 0, 0, y, 319, y + 9, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 320 << G_TEXTURE_IMAGE_FRAC, 10 << G_TEXTURE_IMAGE_FRAC);
            gSPTextureRectangle(g++, 0 << 2, y << 2, 320 << 2, (y + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        *gfx = g;
    }
}

void func_80108544_mgresultdealer(void) {
    D_80109938_mgresultdealer = 1;
}

void func_80108554_mgresultdealer(void) {
    D_80109938_mgresultdealer = 0;
}

void func_80108560_mgresultdealer(u8 alpha) {
    D_8010993A_mgresultdealer = alpha;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108570_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108AEC_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108BD4_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109044_mgresultdealer);

void func_801090AC_mgresultdealer(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801090B4_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801090E8_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801090F4_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109100_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801093A0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109478_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109484_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109710_mgresultdealer);
