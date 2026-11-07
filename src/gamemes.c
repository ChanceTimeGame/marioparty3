#include "game/gamemes.h"
#include "game/audio.h"
#include "game/sprite.h"
#include "stdarg.h"
#include "game/data.h"
#include "math.h"
#include "include_asm.h"

f32 sindf(f32);

extern Gfx *gMainGfxPos;
extern s8 HmfPauseF;

typedef struct {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} GAMEMES; // Size 0x74

s32 func_80037574_main(GAMEMES *gMes, Gfx **);
s32 func_80037878_main(GAMEMES *gMes, Gfx **);
s32 func_80037C44_main(GAMEMES *gMes, Gfx **);
s32 func_8003843C_main(GAMEMES *gMes, Gfx **);
s32 func_80038934_main(GAMEMES *gMes, Gfx **);
s32 func_80038D78_main(GAMEMES *gMes, Gfx **);
s32 func_800392AC_main(GAMEMES *gMes, Gfx **);
s32 func_8003966C_main(GAMEMES *gMes, Gfx **);
s32 func_80039A6C_main(GAMEMES *gMes, Gfx **);
s32 func_80039E80_main(GAMEMES *gMes, Gfx **);
s32 func_8003A2EC_main(GAMEMES *gMes, Gfx **);
s32 func_8003B14C_main(GAMEMES *gMes, Gfx **);
s32 func_8003B7E8_main(GAMEMES *gMes, Gfx **);
s32 func_8003BB84_main(GAMEMES *gMes, Gfx **);
s32 func_8003C248_main(GAMEMES *gMes, Gfx **);
s32 func_8003C644_main(GAMEMES *gMes, Gfx **);
s32 func_8003CA24_main(GAMEMES *gMes, Gfx **);
s32 func_8003CE20_main(GAMEMES *gMes, Gfx **);
s32 func_8003D134_main(GAMEMES *gMes, Gfx **);
s32 func_8003D4DC_main(GAMEMES *gMes, Gfx **);
s32 func_8003D890_main(GAMEMES *gMes, Gfx **);
s32 func_8003DC88_main(GAMEMES *gMes, Gfx **);
s32 func_8003DE60_main(GAMEMES *gMes, Gfx **);
s32 func_8003E4A4_main(GAMEMES *gMes, Gfx **);
s32 func_8003EBC8_main(GAMEMES *gMes, Gfx **);
s32 func_8003EE98_main(GAMEMES *gMes, Gfx **);
s32 GMesTimerExec(GAMEMES *gMes, Gfx **);
s32 func_8003F604_main(GAMEMES *gMes, Gfx **);
s32 func_8003FD34_main(GAMEMES *gMes, Gfx **);
s32 func_8003FFD0_main(GAMEMES *gMes, Gfx **);
s32 func_80040290_main(GAMEMES *gMes, Gfx **);
s32 func_800407B8_main(GAMEMES *gMes, Gfx **);
s32 func_80040CF4_main(GAMEMES *gMes, Gfx **);
s32 func_80041700_main(GAMEMES *gMes, Gfx **);
s32 func_80041B68_main(GAMEMES *gMes, Gfx **);
s32 func_80042AC8_main(GAMEMES *gMes, Gfx **);
s32 func_800440D4_main(GAMEMES *gMes, Gfx **);
s32 func_800448C0_main(GAMEMES *gMes, Gfx **);
s32 func_800452C4_main(void);
void func_800452BC_main(s32 arg0);
s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4);
extern char D_800A7450_main[];
s32 func_80045314_main(void);

extern s8 D_800B1A50_main;
extern u8 gMesCloseF;
extern u8 D_800B1A52_main;
extern s8 gMesTimerId;
extern s16 D_800B1A54_main;
extern s16 D_800B1A58_main[];
extern s16 D_800B1A70_main[];
extern s16 D_800B1A88_main[];
extern s16 D_800B1AC0_main[];
extern s16 D_800B1AF8_main[];
extern s16 D_800B1B30_main[];
extern s16 D_800B1B50_main[];
extern s16 D_800B1B70_main[];
extern GAMEMES gMesData[];
extern s32 omovl;
extern u16 D_800D530C_main;
extern s8 D_800D6A58_main;
extern u16 D_800D1100_main;

unsigned int strlen(const char *);

#define GMES_ABSF(x) (((x) < 0.0f) ? -(x) : (x))
void *HuMemMemoryAllocPerm(u32 size);
void HuMemMemoryFreePerm(void *ptr);

/* wave 2c A */
#include "game/gamework_data.h"

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 scaleX;
    /* 0x24 */ f32 scaleY;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 alpha;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u32 unk38;
} GMesChr; // Size 0x3C

extern GMesChr D_800B1BC0_main[];
extern f32 D_800A1380_main[][2];
s32 func_80038208_main(GAMEMES *gMes, Gfx **arg1);
s32 func_8003C058_main(GAMEMES *gMes, Gfx **arg1);
s16 func_8003A3C4_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4, f32 sx, f32 sy);
u32 func_8003A81C_main(u8 *str, u8 flag);
s16 func_8005B5EC_main(u8 *str);
s32 func_8003A9C8_main(u8 *str, s32 arg1, s32 *frame);
s32 func_8003AC9C_main(u8 *str, s32 arg1, s32 flag, s32 *width);
s16 func_8003AE44_main(s16 arg0);
extern u8 D_800A1334_main[];
extern u8 D_800A136C_main[];
extern u8 D_800A13B0_main[];
s16 func_8003AE9C_main(u8 c, u8 flag);

s32 func_80036610_main(void) {
    return GwSystem.minigame_index;
}

void func_8003661C_main(void) {
    s16 i;

    D_800B1A50_main = 0;
    for (i = 0; i < 8; i++) {
        gMesData[i].mesNo = 0;
    }
    for (i = 0; i < 9; i++) {
        D_800B1A58_main[i] = D_800B1A70_main[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        D_800B1A88_main[i] = D_800B1AC0_main[i] = D_800B1AF8_main[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        D_800B1B30_main[i] = D_800B1B50_main[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        D_800B1B70_main[i] = -1;
    }
    gMesCloseF = FALSE;
    gMesTimerId = -1;
    D_800B1A52_main = 0;
}

void GMesExec(Gfx **arg0) {
    s16 result = FALSE;
    s16 i, j;

    if (HmfPauseF != 0 && !gMesCloseF) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (gMesData[i].stat != GMES_STAT_NONE) {
            GAMEMES *gMes = &gMesData[i];

            switch (gMes->mesNo) {
                case GMES_MES_0:
                    result = func_80037574_main(gMes, arg0);
                    break;
                case GMES_MES_1:
                    result = func_80037878_main(gMes, arg0);
                    break;
                case GMES_MES_2:
                    result = func_80037C44_main(gMes, arg0);
                    break;
                case GMES_MES_3:
                    result = func_8003843C_main(gMes, arg0);
                    break;
                case GMES_MES_4:
                    result = func_80038934_main(gMes, arg0);
                    break;
                case GMES_MES_5:
                    result = func_80038D78_main(gMes, arg0);
                    break;
                case GMES_MES_MG_START:
                    result = func_800392AC_main(gMes, arg0);
                    break;
                case GMES_MES_7:
                    result = func_8003966C_main(gMes, arg0);
                    break;
                case GMES_MES_8:
                    result = func_80039A6C_main(gMes, arg0);
                    break;
                case GMES_MES_9:
                    result = func_80039E80_main(gMes, arg0);
                    break;
                case GMES_MES_10:
                    result = func_8003A2EC_main(gMes, arg0);
                    break;
                case GMES_MES_11:
                    result = func_8003B14C_main(gMes, arg0);
                    break;
                case GMES_MES_12:
                    result = func_8003B7E8_main(gMes, arg0);
                    break;
                case GMES_MES_13:
                    result = func_8003BB84_main(gMes, arg0);
                    break;
                case GMES_MES_14:
                    result = func_8003C248_main(gMes, arg0);
                    break;
                case GMES_MES_15:
                    result = func_8003C644_main(gMes, arg0);
                    break;
                case GMES_MES_16:
                    result = func_8003CA24_main(gMes, arg0);
                    break;
                case GMES_MES_MG_FINISH:
                    result = func_8003CE20_main(gMes, arg0);
                    break;
                case GMES_MES_18:
                    result = func_8003D134_main(gMes, arg0);
                    break;
                case GMES_MES_19:
                    result = func_8003D4DC_main(gMes, arg0);
                    break;
                case GMES_MES_20:
                    result = func_8003D890_main(gMes, arg0);
                    break;
                case GMES_MES_21:
                    result = func_8003DC88_main(gMes, arg0);
                    break;
                case GMES_MES_MG_LOSER:
                    result = func_8003E4A4_main(gMes, arg0);
                    break;
                case GMES_MES_24:
                    result = func_8003EBC8_main(gMes, arg0);
                    break;
                case GMES_MES_25:
                    result = func_8003EE98_main(gMes, arg0);
                    break;
                case GMES_MES_TIMER:
                    result = GMesTimerExec(gMes, arg0);
                    break;
                case GMES_MES_MG_RECORD:
                    result = func_8003F604_main(gMes, arg0);
                    break;
                case GMES_MES_31:
                    result = func_8003FD34_main(gMes, arg0);
                    break;
                case GMES_MES_33:
                    result = func_8003FFD0_main(gMes, arg0);
                    break;
                case GMES_MES_29:
                    result = func_80040290_main(gMes, arg0);
                    break;
                case GMES_MES_28:
                    result = func_800407B8_main(gMes, arg0);
                    break;
                case GMES_MES_MG_DRAW:
                    result = func_80041700_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNER:
                    result = func_8003DE60_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_2:
                    result = func_80040CF4_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_3:
                    result = func_80041B68_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_4:
                    result = func_80042AC8_main(gMes, arg0);
                    break;
                case GMES_MES_36:
                    result = func_800440D4_main(gMes, arg0);
                    break;
                case GMES_MES_37:
                    result = func_800448C0_main(gMes, arg0);
                    break;
            }
            gMes->unk04++;
            if (gMes->unk04 >= 0x4000) {
                gMes->unk04 = 0x2000;
            }
            if (result == FALSE) {
                gMes->stat = GMES_STAT_NONE;
                if (D_800B1A52_main == 0) {
                    for (j = 0; j < GMES_MAX; j++) {
                        if (gMesData[j].stat != GMES_STAT_NONE && gMesData[j].mesNo != GMES_MES_TIMER) {
                            break;
                        }
                    }
                    if (j == GMES_MAX) {
                        func_80037258_main();
                    }
                }
            }
        }
    }
}

s16 GMesCreate(s16 mesNo, ...) {
    GAMEMES *gMes;
    va_list args;
    s32 chr;
    s16 mesId;
    s16 i;

    va_start(args, mesNo);
    for (mesId = 0; mesId < GMES_MAX; mesId++) {
        if (gMesData[mesId].stat == GMES_STAT_NONE) {
            break;
        }
    }
    if (mesId == GMES_MAX) {
        return GMES_ID_NONE;
    }
    gMes = &gMesData[mesId];
    gMes->stat = GMES_STAT_EXIST;
    gMes->mesNo = mesNo;
    gMes->unk04 = 0;
    gMes->unk60 = 160.0f;
    gMes->unk64 = 120.0f;
    gMes->unk6C = 1.0f;
    gMes->unk68 = 1.0f;
    gMes->unk70 = 0;
    gMes->unk03 = 0xFF;
    gMes->unk06 = 0x3C;
    gMes->unk0E = 0;
    gMes->unk0C = 0;
    gMes->unk0A = 0;
    gMes->unk08 = 0;
    gMes->unk10 = gMes->unk14 = 0.0f;
    for (i = 0; i < GMES_STRMAX; i++) {
        gMes->strSprId[i] = gMes->strGId[i] = HUSPR_NONE;
    }
    switch (mesNo) {
        case GMES_MES_0:
        case GMES_MES_1:
        case GMES_MES_2:
        case GMES_MES_11:
        case GMES_MES_12:
        case GMES_MES_13:
        case GMES_MES_31:
        case GMES_MES_33:
            gMes->unk06 = 0x2D;
            break;
        case GMES_MES_MG_DRAW:
            gMes->unk06 = 0x82;
            break;
        case GMES_MES_MG_RECORD:
            gMes->unk60 = 160.0f;
            gMes->unk64 = 180.0f;
            break;
        case GMES_MES_MG_WINNER:
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk64 = func_800452C4_main();
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_29:
        case GMES_MES_36:
        case GMES_MES_37:
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_LOSER:
            gMes->unk0E = chr = va_arg(args, s32);
            break;
        case GMES_MES_24:
        case GMES_MES_25:
            gMes->unk1C = va_arg(args, s32);
            gMes->unk60 = va_arg(args, s32);
            gMes->unk64 = va_arg(args, s32);
            gMes->unk68 = va_arg(args, f64);
            gMes->unk6C = va_arg(args, f64);
            gMes->unk02 = va_arg(args, s32);
            break;
        case GMES_MES_TIMER:
            gMesTimerId = mesId;
            gMes->unk08 = va_arg(args, s32);
            gMes->unk60 = va_arg(args, s32);
            gMes->unk64 = va_arg(args, s32);
            gMes->unk60 = 160.0f;
            gMes->unk64 = 28.0f;
            break;
        case GMES_MES_MG_WINNERS_2:
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_WINNERS_3:
            gMes->unk0A = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk64 = func_80045314_main();
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_WINNERS_4:
            gMes->unk08 = chr = va_arg(args, s32);
            gMes->unk0A = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk06 = 0x78;
            break;
    }
    D_800B1A54_main = 0x5A;
    va_end(args);
    return mesId;
}

s32 GMesStatGet(void) {
    s16 stat;
    s16 i;

    for (i = 0, stat = GMES_STAT_NONE; i < GMES_MAX; i++) {
        if (gMesData[i].mesNo != GMES_MES_TIMER) {
            stat |= gMesData[i].stat;
        }
    }
    return stat;
}

u8 func_800370A4_main(s16 mesId) {
    return gMesData[mesId].stat;
}

void GMesMaxTimeGet(s16 mesId, s16 time) {
    if (time == -1) {
        time = 0x7FFF;
    }
    gMesData[mesId].unk06 = time;
}

void GMesPosSet(s16 mesId, f32 x, f32 y) {
    gMesData[mesId].unk60 = x;
    gMesData[mesId].unk64 = y;
}

void func_8003714C_main(s16 mesId) {
    if (gMesData[mesId].stat != GMES_STAT_NONE) {
        gMesData[mesId].stat = 4;
    }
}

void GMesClose(void) {
    gMesTimerId = -1;
    gMesCloseF = TRUE;
    GMesExec(&gMainGfxPos);
    gMesCloseF = FALSE;
    func_80037258_main();
    D_800B1A52_main = 0;
}

s32 GMesWait(void) {
    s32 stat;

    if (HmfPauseF == 0 && D_800D530C_main == 0) {
        stat = GMesStatGet();
        if (stat == 0 || stat & 2) {
            D_800B1A54_main--;
            if (D_800B1A54_main < 0) {
                return 0;
            }
        }
    }
    return 1;
}

void GMesMaxWaitSet(s16 time) {
    D_800B1A54_main = time;
}

void func_80037258_main(void) {
    s16 i;

    for (i = 0; i < 9; i++) {
        if (i == 2 && gMesTimerId != -1) {
            continue;
        }
        if (D_800B1A58_main[i] != -1) {
            HuSprKill(D_800B1A58_main[i]);
        }
        if (D_800B1A70_main[i] != -1) {
            HuSprKill(D_800B1A70_main[i]);
        }
        D_800B1A58_main[i] = D_800B1A70_main[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        if (D_800B1A88_main[i] != -1) {
            HuSprKill(D_800B1A88_main[i]);
        }
        if (D_800B1AC0_main[i] != -1) {
            HuSprKill(D_800B1AC0_main[i]);
        }
        if (D_800B1AF8_main[i] != -1) {
            HuSprKill(D_800B1AF8_main[i]);
        }
        D_800B1A88_main[i] = D_800B1AC0_main[i] = D_800B1AF8_main[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_800B1B30_main[i] != -1) {
            HuSprKill(D_800B1B30_main[i]);
        }
        if (D_800B1B50_main[i] != -1) {
            HuSprKill(D_800B1B50_main[i]);
        }
        D_800B1B30_main[i] = D_800B1B50_main[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        if (D_800B1B70_main[i] != -1) {
            HuSprKill(D_800B1B70_main[i]);
        }
        D_800B1B70_main[i] = -1;
    }
}

void GMesSprKill(GAMEMES *gMes) {
    s16 i;

    for (i = 0; i < 16; i++) {
        if (gMes->strGId[i] != -1) {
            HuSprGrpKill(gMes->strGId[i]);
        }
        if (gMes->strSprId[i] != -1) {
            HuSprKill(gMes->strSprId[i]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7450_main);

// "START": register allocation in the i + 1 loops (masked 21), as MP2 func_800698F0_6A4F0; logic follows MP3
#ifdef NON_MATCHING
s32 func_80037574_main(GAMEMES *gMes, Gfx **arg1) {
    s32 n = 5;
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, D_800A7450_main, 1, -1, -1);
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 0.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 0);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, gMes->unk04 * 0.05f);
                func_80055458_main(gMes->strGId[0], i, gMes->unk04 * 12);
            }
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 2;
                for (i = 0; i < n;) {
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 255);
                }
            }
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 3;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            gMes->stat = 2;
            gMes->unk0A += 6;
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, cosdf(gMes->unk0A));
            }
            if (gMes->unk04 >= gMes->unk06) {
                for (i = 0; i < n;) {
                    i++;
                    HuSprAttrSet(gMes->strGId[0], i, 0x8000);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            ret = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037574_main);
#endif

// "START" bouncing in: register allocation in the i + 1 loops (masked 20), as MP2 func_80069C20_6A820; logic follows MP3
#ifdef NON_MATCHING
s32 func_80037878_main(GAMEMES *gMes, Gfx **arg1) {
    char *str = D_800A7450_main;
    s32 len = strlen(str);
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 3;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str, 1, -1, -1);
            gMes->unk6C = gMes->unk68 = 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk03 = 0;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk68 = gMes->unk10 + 0.3f;
            gMes->unk6C = gMes->unk10 + 0.3f;
            gMes->unk64 = 120.0f - sindf(gMes->unk0A) * 20.0f;
            gMes->unk03 += 12;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 2;
                func_80054904_main(gMes->strGId[0], 0, 160, 120);
                for (i = 0; i < len;) {
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 255);
                }
            }
            break;
        case 2:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            ret = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037878_main);
#endif

// "START" dropping in: register allocation in the i + 1 loop (masked 20), as MP2 func_8006A018_6AC18; logic follows MP3
#ifdef NON_MATCHING
s32 func_80037C44_main(GAMEMES *gMes, Gfx **arg1) {
    char *str = D_800A7450_main;
    s32 len = strlen(str);
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 5;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str, 1, -1, -1);
            gMes->unk6C = gMes->unk68 = 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 40.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, 0);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            gMes->unk68 = gMes->unk10 + 0.3f;
            gMes->unk6C = gMes->unk10 + 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 += gMes->unk14;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len;) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], ++i, sindf(gMes->unk0C) * 255.0f);
            }
            gMes->unk0C += 6;
            gMes->unk10 += 0.046666667f;
            gMes->unk14 += 0.8f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -5.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                for (i = 0; i < len;) {
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -3.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                gMes->unk08 = 3;
            }
            break;
        case 3:
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                gMes->unk08 = 4;
            }
            break;
        case 4:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            ret = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037C44_main);
#endif

// "START" (unused variant): register allocation, i and chr swapped (masked 0)
#ifdef NON_MATCHING
s32 func_80038208_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 i;
    s32 n = 5;
    s32 ret;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 6;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            for (i = 0; i < 32; i++) {
                chr = &D_800B1BC0_main[i];
                chr->unk00 = chr->unk04 = chr->unk18 = chr->unk1C = chr->unk28 = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 0x80;
                chr->unk34 = 0;
                chr->unk38 = 0;
            }
            func_8003A37C_main(gMes, D_800A7450_main, 1, -1, -1);
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n;) {
                chr = &D_800B1BC0_main[i];
                i++;
                HuSprScaleSet(gMes->strGId[0], i, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i, chr->alpha);
            }
            gMes->unk06 = gMes->unk04 = gMes->unk0A = gMes->unk0C = gMes->unk0E = 0;
            gMes->unk60 = gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
            gMes->unk1C = 0;
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            ret = FALSE;
            break;
    }
    if (gMes->unk04 == 60) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 80) {
        func_800452BC_main(func_80036610_main());
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038208_main);
#endif

// "START" flipping in: register allocation in the i + 1 loops (masked 35: i and i + 1 swap registers, one move per loop)
#ifdef NON_MATCHING
s32 func_8003843C_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    f32 scale;
    s16 member;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n; i++) {
                chr = &D_800B1BC0_main[i];
                chr->unk00 = i * 22 - (n - 1) * 11;
                chr->unk28 = 180.0f;
                member = i + 1;
                HuSprScaleSet(gMes->strGId[0], member, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], member, chr->alpha);
                func_80054904_main(gMes->strGId[0], member, chr->unk00, chr->unk04);
                HuSprAttrSet(gMes->strGId[0], member, 2);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            chr = &D_800B1BC0_main[0];
            if (gMes->unk04 > 60) {
                for (i = 0; i < n; i++) {
                    member = i + 1;
                    HuSprAttrReset(gMes->strGId[0], member, 2);
                    HuSprScaleSet(gMes->strGId[0], member, 1.0f, 1.0f);
                }
                gMes->unk08 = 2;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            } else if (gMes->unk04 > 10) {
                chr->unk28 += 18.0f;
                if (chr->unk28 > 360.0f) {
                    chr->unk28 -= 360.0f;
                }
                scale = cosdf(chr->unk28);
                if (scale < 0.0f) {
                    scale = -scale;
                    for (i = 0; i < n; i++) {
                        member = i + 1;
                        HuSprAttrSet(gMes->strGId[0], member, 2);
                        HuSprScaleSet(gMes->strGId[0], member, 1.0f, scale);
                    }
                } else {
                    for (i = 0; i < n; i++) {
                        member = i + 1;
                        HuSprAttrReset(gMes->strGId[0], member, 2);
                        HuSprScaleSet(gMes->strGId[0], member, 1.0f, scale);
                    }
                }
            } else {
                for (i = 0; i < n; i++) {
                    member = i + 1;
                    HuSprAttrSet(gMes->strGId[0], member, 2);
                    HuSprScaleSet(gMes->strGId[0], member, 1.0f, 1.0f);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = gMes->unk0C = 0;
            }
            for (i = 0; i < n; i++) {
                member = i + 1;
                HuSprAttrReset(gMes->strGId[0], member, 2);
                HuSprScaleSet(gMes->strGId[0], member, 1.0f, 1.0f);
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003843C_main);
#endif

// "START" letters flying in: register allocation (masked 39: the i + 1 loops, and case 0 keeps D_800B1BC0_main in a register)
#ifdef NON_MATCHING
s32 func_80038934_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    f32 scale;
    f32 t;
    s16 member;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n; i++) {
                chr = &D_800B1BC0_main[i];
                chr->unk08 = chr->unk00 = D_800A1380_main[i][0];
                chr->unk0C = chr->unk04 = D_800A1380_main[i][1];
                chr->unk10 = i * 22 - (n - 1) * 11;
                chr->unk14 = 0.0f;
                chr->unk28 = chr->unk2C = 180.0f;
                member = i + 1;
                HuSprScaleSet(gMes->strGId[0], member, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], member, chr->unk00, chr->unk04);
            }
            gMes->unk08 = 1;
            gMes->unk0A = gMes->unk0C = 0;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                gMes->unk0C = 0;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            } else {
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    t = 0.0f;
                    if (gMes->unk04 > (30.0f / n) * i) {
                        if (chr->unk38 > 30) {
                            t = 1.0f;
                        } else {
                            t = chr->unk38 * (1.0f / 30.0f);
                            chr->unk38++;
                        }
                    }
                    chr->unk00 = t * (chr->unk10 - chr->unk08) + chr->unk08;
                    chr->unk04 = t * (chr->unk14 - chr->unk0C) + chr->unk0C;
                    i++;
                    func_80054904_main(gMes->strGId[0], i, chr->unk00, chr->unk04);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038934_main);
#endif

// "START" letters spinning in: register allocation (masked 16: i and chr swap registers; the flip loop keeps i + 1 in s0)
#ifdef NON_MATCHING
s32 func_80038D78_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    f32 scale;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n;) {
                chr = &D_800B1BC0_main[i];
                chr->unk00 = i * 22 - (n - 1) * 11;
                chr->unk04 = 0.0f;
                chr->unk28 = chr->unk2C = 180.0f;
                i++;
                HuSprScaleSet(gMes->strGId[0], i, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], i, chr->unk00, chr->unk04);
                HuSprAttrSet(gMes->strGId[0], i, 2);
            }
            gMes->unk08 = 1;
            gMes->unk0A = gMes->unk0C = gMes->unk0E = 0;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < n; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    func_80055458_main(gMes->strGId[0], i + 1, 0xFF);
                }
            } else if (gMes->unk04 > 10) {
                for (i = 0; i < n; i++) {
                    chr = &D_800B1BC0_main[i];
                    if (gMes->unk04 - 10 > (50.0f / n) * i) {
                        if (chr->unk38 > 50.0f / n) {
                            scale = 1.0f;
                            chr->unk28 = 0.0f;
                        } else {
                            chr->unk38++;
                            chr->unk28 += 18.0f;
                            if (chr->unk28 > 360.0f) {
                                chr->unk28 -= 360.0f;
                            }
                            scale = cosdf(chr->unk28);
                        }
                    } else {
                        chr->unk38 = 0;
                        chr->unk28 = 180.0f;
                        scale = -1.0f;
                    }
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                    }
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                }
            } else {
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->unk38 = 0;
                    i++;
                    HuSprAttrSet(gMes->strGId[0], i, 2);
                    HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038D78_main);
#endif

// "START" letters zooming in: register allocation (masked 32: the case 0 j + 1 loop increments in place)
#ifdef NON_MATCHING
s32 func_800392AC_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    s32 j;
    f32 scale;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            for (j = 0; j < n; j++) {
                HuSprScaleSet(gMes->strGId[0], j + 1, 0.3f, 0.3f);
                func_80055458_main(gMes->strGId[0], j + 1, 0x80);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            } else if (gMes->unk04 > 38) {
                scale = 1.0f;
                for (i = 0; i < n;) {
                    i++;
                    HuSprScaleSet(gMes->strGId[0], i, scale, scale);
                }
            } else if (gMes->unk04 > 30) {
                scale = 1.5f - (gMes->unk04 - 30.0f) * 0.5f * 0.125f;
                for (i = 0; i < n;) {
                    i++;
                    HuSprScaleSet(gMes->strGId[0], i, scale, scale);
                }
            } else if (gMes->unk04 > 10) {
                scale = (gMes->unk04 - 10) * 1.2f * 0.05f + 0.3f;
                for (i = 0; i < n;) {
                    i++;
                    HuSprScaleSet(gMes->strGId[0], i, scale, scale);
                }
            } else {
                scale = 0.3f;
                for (i = 0; i < n;) {
                    i++;
                    HuSprScaleSet(gMes->strGId[0], i, scale, scale);
                }
            }
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_800392AC_main);
#endif

// "START" letters dropping and bouncing: register allocation (masked 33: the case 0 j + 1 loop increments in place, case 1 keeps D_800B1BC0_main in a register)
#ifdef NON_MATCHING
s32 func_8003966C_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    s32 j;
    f32 scale;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (j = 0; j < n; j++) {
                chr = &D_800B1BC0_main[j];
                chr->unk00 = j * 22 - (n - 1) * 11;
                chr->unk04 = -120.0f - j * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], j + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], j + 1, chr->unk00, chr->unk04);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            } else if (gMes->unk0A == 0) {
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    if (chr->unk34 == 0) {
                        chr->unk1C += 0.71999997f;
                        chr->unk04 += chr->unk1C;
                        if (chr->unk04 > 0.0f) {
                            chr->unk04 = chr->unk1C = -chr->unk1C * 0.5f;
                            chr->unk34 = 1;
                        }
                    } else {
                        chr->unk1C += 0.71999997f;
                        chr->unk04 += chr->unk1C;
                        if (chr->unk04 > 0.0f) {
                            chr->unk1C = chr->unk04 = 0.0f;
                        }
                    }
                    i++;
                    func_80054904_main(gMes->strGId[0], i, chr->unk00, chr->unk04);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003966C_main);
#endif

// "START" letters rising and bouncing: register allocation (masked 25: the case 0 j + 1 loop increments in place)
#ifdef NON_MATCHING
s32 func_80039A6C_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 5;
    s32 ret;
    s32 i;
    s32 j;
    f32 scale;

    ret = func_80038208_main(gMes, arg1);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (j = 0; j < n; j++) {
                chr = &D_800B1BC0_main[j];
                chr->unk00 = j * 22 - (n - 1) * 11;
                chr->unk04 = j * 7.2000003f + 144.0f;
                HuSprScaleSet(gMes->strGId[0], j + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], j + 1, chr->unk00, chr->unk04);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            } else if (gMes->unk0A == 0) {
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    if (chr->unk34 == 0) {
                        chr->unk1C += -0.71999997f;
                        chr->unk04 += chr->unk1C;
                        if (chr->unk04 < 0.0f) {
                            chr->unk04 = chr->unk1C = chr->unk1C * 0.5f;
                            chr->unk34 = 1;
                        }
                    } else {
                        chr->unk1C += 0.71999997f;
                        chr->unk04 += chr->unk1C;
                        if (chr->unk04 > 0.0f) {
                            chr->unk1C = chr->unk04 = 0.0f;
                        }
                    }
                    i++;
                    func_80054904_main(gMes->strGId[0], i, chr->unk00, chr->unk04);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80039A6C_main);
#endif

// "START" tracing a path in: register allocation (masked 30: the case 0 j + 1 loop increments in place)
#ifdef NON_MATCHING
s32 func_80039E80_main(GAMEMES *gMes, Gfx **arg1) {
    f32 sy = 0.0f;
    f32 sx = 0.0f;
    f32 ex = 0.0f;
    f32 ey = 0.0f;
    s32 ret = func_80038208_main(gMes, arg1);
    f32 t = 1.0f;
    f32 left = 55.0f;
    f32 right = 265.0f;
    f32 top = 12.0f;
    f32 bottom = 228.0f;
    GMesChr *chr;
    s32 n = 5;
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 scale;

    switch (gMes->unk08) {
        case 0:
            for (j = 0; j < n; j++) {
                HuSprScaleSet(gMes->strGId[0], j + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], j + 1, 0x80);
            }
            func_80054904_main(gMes->strGId[0], 0, 0, 0);
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            break;
        case 1:
            if (gMes->unk0A < 4) {
                if (gMes->unk0A == 0) {
                    sx = left;
                    sy = top;
                    ex = right;
                    ey = (bottom - top) * 0.5f;
                    if (gMes->unk0C < 5) {
                        t = gMes->unk0C * 0.2f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 1;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 1) {
                    sx = right;
                    sy = (bottom - top) * 0.5f;
                    ex = (right - left) * 0.5f;
                    ey = bottom;
                    if (gMes->unk0C < 7) {
                        t = gMes->unk0C * 0.14285715f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 2;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 2) {
                    sx = (right - left) * 0.5f;
                    sy = bottom;
                    ex = left;
                    ey = 120.0f;
                    if (gMes->unk0C < 8) {
                        t = gMes->unk0C * 0.125f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 3;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 3) {
                    sx = left;
                    sy = 120.0f;
                    ex = 160.0f;
                    ey = 120.0f;
                    if (gMes->unk0C < 10) {
                        t = gMes->unk0C * 0.1f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 4;
                        gMes->unk0C = 0;
                    }
                }
                x = (ex - sx) * t + sx;
                y = (ey - sy) * t + sy;
            } else {
                x = 160.0f;
                y = 120.0f;
                gMes->unk08 = 2;
                gMes->unk0C = 0;
                for (i = 0; i < n;) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 0xFF;
                    i++;
                    func_80055458_main(gMes->strGId[0], i, 0xFF);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, x, y);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80039E80_main);
#endif

s32 func_8003A2EC_main(GAMEMES *gMes, Gfx **arg1) {
    return func_80039E80_main(gMes, arg1);
}

s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4);

s16 func_8003A308_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4) {
    s16 i;

    for (i = 0; i < 16; i++) {
        gMes->strGId[i] = -1;
        gMes->strSprId[i] = -1;
    }
    return func_8003A37C_main(gMes, str, flag, x, arg4);
}

s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4) {
    return func_8003A3C4_main(gMes, str, flag, x, arg4, 1.0f, 1.0f);
}

/* A sprite group with one member per character of str, as MP2 func_8006A67C_6B27C with an x scale
   (sy is unused); flag bit 0 picks the large font, x0 == -1 centres the string. Returns the strGId slot. */
// register allocation (masked 22): retail also loads the reused arg4 at entry, and adds str + skip the other way round
#ifdef NON_MATCHING
s16 func_8003A3C4_main(GAMEMES *gMes, char *arg1, u8 flag, s16 x0, s16 arg4, f32 sx, f32 sy) {
    s16 id;
    s16 hi = -1;
    u8 *str;
    u8 *p;
    s16 i;
    s16 len;
    s16 total;
    s16 x;
    s16 idx;
    s16 y;
    s16 w;
    u32 v;

    str = (u8 *)arg1;
    len = func_8005B5EC_main(str);

    for (i = 0; i < 16; i++) {
        if (gMes->strSprId[i] == -1 && gMes->strGId[i] == -1) {
            break;
        }
    }

    id = gMes->strGId[i] = HuSprGrpCreate(len + 1, 5);

    w = 15;
    if (flag & 1) {
        w = 22;
    }

    p = str;
    for (total = 0; *p != 0; p++) {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 0xD0 && *p < 0xF0)) {
            total += 10;
        } else if (*p == '\\') {
            total += (w == 15) ? 4 : 8;
        } else if ((*p == 0x10) | (*p == ' ')) {
            total += (w == 15) ? 8 : 11;
        } else {
            total = w + total;
        }
    }

    if (x0 == -1) {
        x = -(total / 2) + (w * sx) / 2.0f;
    } else {
        x = -x0 * sx;
    }

    for (idx = 1; *str != 0; idx++) {
        arg4 = id;
        v = func_8003A81C_main(str, flag);
        hi = v >> 16;
        func_80055024_main(id, idx, hi, v & 0xFF);
        /* retail tests the 0xD0 range's upper bound on p, which is at the string's end here */
        y = 0;
        if (*str >= 0xD0) {
            y = (*p < 0xF0) ? -2 : 0;
        }
        func_80054904_main(arg4, idx, x, y);
        func_80055458_main(arg4, idx, 255);
        HuSprPriSet(arg4, idx, 5);
        HuSprAttrReset(arg4, idx, 0xFFFF);
        HuSprAttrSet(arg4, idx, 0x1008);
        if ((*str >= 'a' && *str <= 'z') || (*str >= 0xD0 && *str < 0xF0)) {
            x += 10;
        } else if (*str == '\\') {
            x += (w != 15) ? 12 : 8;
        } else if ((*str == 0x10) | (*str == ' ')) {
            x += (w == 15) ? 8 : 11;
        } else {
            x = x + w * sx;
        }
        func_800554C4_main(id, idx, 0);
        str = &str[(u8)(str[1] + 0x80) < 2];
        str++;
    }

    func_80055024_main(id, 0, hi, 0);
    HuSprAttrSet(id, 0, 0x8000);
    func_800554C4_main(id, 0, -1);
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A3C4_main);
#endif

/* The font sprite (high half, loaded on first use) and frame (low half) for the character at str;
   flag bit 0 is the large font. */
// register allocation (masked 0): flag, its copy and c take s0-s2 in another order
#ifdef NON_MATCHING
u32 func_8003A81C_main(u8 *str, u8 flag) {
    s32 frame;
    u16 anim;
    u8 c;
    s32 type;

    c = *str;
    frame = 0;
    type = func_8003A9C8_main(str, 0, &frame);
    if (type == 2) {
        if (flag & 1) {
            if (D_800B1A70_main[2] == -1) {
                anim = D_800B1A70_main[2] = func_8003AE44_main(0x87);
            } else {
                anim = D_800B1A70_main[2];
            }
        } else {
            if (D_800B1A58_main[2] == -1) {
                anim = D_800B1A58_main[2] = func_8003AE44_main(0x86);
            } else {
                anim = D_800B1A58_main[2];
            }
        }
    } else if (type == 4) {
        if (D_800B1A58_main[4] == -1) {
            anim = D_800B1A58_main[4] = func_8003AE44_main(0x88);
        } else {
            anim = D_800B1A58_main[4];
        }
    } else if (type == 5) {
        if (D_800B1A58_main[5] == -1) {
            anim = D_800B1A58_main[5] = func_8003AE44_main(0x89);
        } else {
            anim = D_800B1A58_main[5];
        }
    } else if (type == 6) {
        if (D_800B1A58_main[6] == -1) {
            anim = D_800B1A58_main[6] = func_8003AE44_main(0x8A);
        } else {
            anim = D_800B1A58_main[6];
        }
    } else if (type == 7) {
        if (D_800B1A58_main[7] == -1) {
            anim = D_800B1A58_main[7] = func_8003AE44_main(0x8B);
        } else {
            anim = D_800B1A58_main[7];
        }
    } else {
        if (type != 8) {
            if (type != 0) {
                if (type != 1) {
                    frame = 0;
                }
            }
        }
        anim = func_8003AE9C_main(c, flag);
    }
    return (anim << 16) | frame;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A81C_main);
#endif

/* Classifies the character at str for the font: returns the font type (0 upper case, 1 lower case,
   2 digit, 3 symbol, 4-7 kana tables, 8 a character the large font lacks) and its frame in *frame.
   arg1 != 0 is the large font. */
s32 func_8003A9C8_main(u8 *str, s32 arg1, s32 *frame) {
    u16 c;
    u8 next;
    s32 i;

    c = str[0];
    next = str[1];
    *frame = 0;
    if (c >= 'A' && c <= 'Z') {
        *frame = c - 'A';
        return 0;
    }
    if (c >= 'a' && c <= 'z') {
        *frame = c - 'a';
        return 1;
    }
    if (c >= '0' && c <= '9') {
        *frame = c - '0';
        return 2;
    }
    if (arg1 == 0) {
        if (c >= 0x86 && c < 0xBE) {
            if ((u8)(next + 0x80) < 2) {
                for (i = 0; i < 20; i++) {
                    if (c == D_800A136C_main[i]) {
                        break;
                    }
                }
                if (next == 0x81) {
                    i += 5;
                }
                *frame = i;
                return 5;
            }
            for (i = 0; i < 55; i++) {
                if (c == D_800A1334_main[i]) {
                    break;
                }
            }
            *frame = i;
            return 4;
        }
        if (c >= 0xC6 && c < 0xFE) {
            c -= 0x40;
            if ((u8)(next + 0x80) < 2) {
                for (i = 0; i < 20; i++) {
                    if (c == D_800A136C_main[i]) {
                        break;
                    }
                }
                if (next == 0x81) {
                    i += 5;
                }
                *frame = i;
                return 7;
            }
            for (i = 0; i < 55; i++) {
                if (c == D_800A1334_main[i]) {
                    break;
                }
            }
            *frame = i;
            return 6;
        }
    } else {
        if (c >= 0x90 && c < 0xB0) {
            return 8;
        }
        if (c >= 0xD0 && c < 0xF0) {
            return 8;
        }
    }
    switch (c) {
        case '}':
            *frame = 6;
            break;
        case 0x82:
            *frame = 10;
            break;
        case 0x84:
            *frame = 2;
            break;
        case 0x85:
            *frame = 7;
            break;
        case 0xC2:
            *frame = 1;
            break;
        case 0xC3:
            *frame = 3;
            break;
        case 0xC4:
            *frame = 1;
            break;
        case 0xC5:
            *frame = 3;
            break;
        case 0xC6:
            *frame = 8;
            break;
        case 0xC7:
            *frame = 9;
            break;
        case '\\':
            *frame = 5;
            break;
        case '=':
            *frame = 4;
            break;
    }
    return 3;
}

/* As func_8003A9C8_main, but returns the character's advance width in *width; flag bit 0 is the
   large font. Unused. */
// masked 37 (5 instructions short): retail keeps the empty case 0x84 as the switch-tree root and copies flag; same logic
#ifdef NON_MATCHING
s32 func_8003AC9C_main(u8 *str, s32 arg1, s32 flag, s32 *width) {
    s32 c;
    u8 next;
    s32 w;

    c = str[0];
    next = str[1];
    w = 15;
    if (flag & 1) {
        w = 22;
    }
    *width = w;
    if (c >= 'A' && c <= 'Z') {
        *width = w;
        return 0;
    }
    if (c >= 'a' && c <= 'z') {
        *width = 10;
        return 1;
    }
    if (c >= '0' && c <= '9') {
        *width = w;
        return 2;
    }
    if (arg1 == 0) {
        if (c >= 0x86 && c < 0xBE) {
            if ((u8)(next + 0x80) < 2) {
                *width = w;
                return 5;
            }
            *width = w;
            return 4;
        }
        if (c >= 0xC6 && c < 0xFE) {
            if ((u8)(next + 0x80) < 2) {
                *width = w;
                return 7;
            }
            *width = w;
            return 6;
        }
    } else {
        if (c >= 0x90 && c < 0xB0) {
            *width = w;
            return 8;
        }
        if (c >= 0xD0 && c < 0xF0) {
            *width = w;
            return 8;
        }
    }
    switch ((u16)c) {
        case 0x84:
            break;
        case '=':
            break;
        case '}':
            break;
        case 0x10:
        case ' ':
            *width = (flag & 1) ? 8 : 11;
            break;
        case '\\':
            if (*str == '\\') {
                *width = (flag & 1) ? 4 : 8;
            }
            break;
    }
    return 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AC9C_main);
#endif

s16 func_8003AE44_main(s16 arg0) {
    void *data = DataReadTemp(arg0 | 0xC0000);
    s16 ret = func_80055810_main(data);

    DataCloseTemp(data);
    return ret;
}

/* The font sprite for character c, loaded on first use: upper case, lower case, kana and symbols
   each have a cache of sprite ids; flag bit 0 is the large font. */
// masked 11 (one instruction short): retail masks the kana table byte with an extra andi 0xFF
#ifdef NON_MATCHING
s16 func_8003AE9C_main(u8 c, u8 flag) {
    s16 *slot;
    s32 fileId;
    s32 frame;
    s32 i;
    void *data;
    s16 id;

    frame = 0;
    switch (c) {
        case '}':
            frame = 6;
            break;
        case 0x82:
            frame = 10;
            break;
        case 0x84:
            frame = 2;
            break;
        case 0x85:
            frame = 7;
            break;
        case 0xC2:
        case 0xC4:
            frame = 1;
            break;
        case 0xC3:
        case 0xC5:
            frame = 3;
            break;
        case 0xC6:
            frame = 8;
            break;
        case 0xC7:
            frame = 8;
            break;
        case '\\':
            frame = 5;
            break;
        case '=':
            frame = 4;
            break;
    }
    if (c >= 'A' && c <= 'Z') {
        if (flag & 1) {
            fileId = c - 'A' + 0xC003F;
            slot = &D_800B1AF8_main[c - 'A'];
        } else {
            fileId = c - 'A' + 0xC0000;
            slot = &D_800B1AC0_main[c - 'A'];
        }
    } else if (c >= 'a' && c <= 'z') {
        fileId = c - 'a' + 0xC0025;
        slot = &D_800B1A88_main[c - 'a'];
    } else if ((c >= 0x90 && c < 0xB0) || (c >= 0xD0 && c < 0xF0)) {
        for (i = 0; i < 36; i++) {
            if (c == D_800A13B0_main[i]) {
                break;
            }
        }
        fileId = i + 0xC0061;
        slot = &D_800B1B70_main[i];
    } else if (flag & 1) {
        fileId = frame + 0xC0059;
        slot = &D_800B1B50_main[frame];
    } else {
        fileId = frame + 0xC001A;
        slot = &D_800B1B30_main[frame];
    }
    if (*slot != -1) {
        return *slot;
    }
    data = DataReadTemp(fileId);
    id = func_80055810_main(data);
    *slot = id;
    DataCloseTemp(data);
    return id;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AE9C_main);
#endif

void func_8003B128_main(GAMEMES *gMes) {
    GMesSprKill(gMes);
    func_80037258_main();
}

s32 func_8003B4D8_main(GAMEMES *gMes, s32 fileId, s16 sound);
void func_8003DCA4_main(GAMEMES *gMes, s32 fileId);

s32 func_8003B14C_main(GAMEMES *gMes, Gfx **arg1) {
    return func_8003B4D8_main(gMes, 0xC0090, 0x253);
}

s32 func_8003B170_main(GAMEMES *gMes, char *str, s16 sound) {
    f64 var_f2;
    f32 temp_f24;
    f32 temp_f30;
    f32 i;

    var_f2 = strlen(str);
    temp_f30 = var_f2;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, str, 1, -1, -1);
        func_80054904_main(gMes->strGId[0], 0, 160, gMes->unk64);
        gMes->unk08 = -1000;
        gMes->unk0A = 300;
        HuAudFXPlay(sound);
        D_800D6A58_main = 1;
        D_800D1100_main = 0;
    }

    if (gMes->unk04 > gMes->unk06 || gMesCloseF != 0 || gMes->stat == 4) {
        GMesSprKill(gMes);
        return 0;
    }

    if (gMes->unk04 > gMes->unk06 - 10) {
        gMes->stat = 2;
        temp_f24 = gMes->unk04 - (gMes->unk06 - 10);

        for (i = 0.0f; i < temp_f30; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1.0f, 1.8f - temp_f24 / 6.0f, 1.8f - temp_f24 / 6.0f);
            func_80055458_main(gMes->strGId[0], i + 1.0f, 255.0f - temp_f24 * 25.5f);
        }

        gMes->unk08 += gMes->unk0A;
        gMes->unk64 += gMes->unk08 / 100.0f;

        func_80054904_main(gMes->strGId[0], 0, 160, gMes->unk64);
    } else {
        for (i = 0.0f; i < temp_f30; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1.0f, 1.8f, 1.8f);
        }
    }

    return 1;
}

s32 func_8003B4D8_main(GAMEMES *gMes, s32 fileId, s16 sound) {
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, fileId);
            HuAudFXPlay(sound);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
            gMes->unk03 = 0xFF;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            func_800552DC_main(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk60 += 8.0f;
            gMes->unk64 -= 6.0f;
            gMes->unk6C = gMes->unk68 = gMes->unk68 - 0.06f;
            gMes->unk03 -= 17;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            if (gMes->unk04 >= 40) {
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            ret = FALSE;
            break;
    }
    return ret;
}

s32 func_8003B7E8_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, 255);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk68 = 1.0f - gMes->unk10;
            gMes->unk6C = 1.0f - gMes->unk10;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f - sindf(gMes->unk0A) * 50.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            gMes->unk0A += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            if (gMes->unk04 >= gMes->unk06) {
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            ret = FALSE;
            break;
    }
    return ret;
}

s32 func_8003BB84_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 5;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, 255);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 >= 10) {
                gMes->unk08 = 2;
                gMes->unk14 = -4.0f;
            }
            break;
        case 2:
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -6.0f;
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -10.0f;
                gMes->unk10 = 0.0f;
                gMes->unk08 = 4;
                gMes->unk0A = 0;
                gMes->unk0C = 0;
            }
            break;
        case 4:
            gMes->unk64 += gMes->unk14;
            gMes->unk10 += 0.058333334f;
            gMes->unk68 = 1.0f - gMes->unk10;
            gMes->unk6C = 1.0f - gMes->unk10;
            gMes->unk0C += 7;
            gMes->unk14 += 1.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            if (++gMes->unk0A >= 12) {
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
                gMes->unk08 = 5;
            }
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 6;
            }
            break;
        case 6:
            GMesSprKill(gMes);
            ret = FALSE;
            break;
    }
    return ret;
}

s32 func_8003C058_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n = 6;
    s32 ret;
    s32 i;

    if (gMesCloseF || gMes->stat == 4) {
        gMes->unk08 = 6;
    }
    ret = TRUE;
    switch (gMes->unk08) {
        case 0:
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            for (i = 0; i < 32; i++) {
                chr = &D_800B1BC0_main[i];
                chr->unk00 = chr->unk04 = chr->unk18 = chr->unk1C = chr->unk28 = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 0xFF;
                chr->unk34 = 0;
                chr->unk38 = 0;
            }
            gMes->unk06 = gMes->unk04 = gMes->unk0A = gMes->unk0C = gMes->unk0E = 0;
            gMes->unk60 = gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
            gMes->unk1C = 0;
            func_8003A37C_main(gMes, "FINISH", 1, -1, -1);
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n;) {
                i++;
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, 0.0f);
                func_80055458_main(gMes->strGId[0], i, 0);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            GMesSprKill(gMes);
            ret = FALSE;
            break;
    }
    if (gMes->unk04 == 0) {
        HuAudFXPlay(0x253);
    }
    return ret;
}

// "FINISH" letters flipping: register allocation (masked 30: i and chr swap registers, the flip loop extends i + 1 per call)
#ifdef NON_MATCHING
s32 func_8003C248_main(GAMEMES *gMes, Gfx **arg1) {
    GMesChr *chr;
    s32 n;
    s32 ret;
    s32 i;
    s32 member;
    f32 scale;

    ret = func_8003C058_main(gMes, arg1);
    n = 6;
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < n;) {
                chr = &D_800B1BC0_main[i];
                chr->unk00 = i * 22 - (n - 1) * 11;
                chr->unk04 = 0.0f;
                chr->unk28 = chr->unk2C = 180.0f;
                i++;
                member = i;
                HuSprScaleSet(gMes->strGId[0], member, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], member, chr->alpha);
                func_80054904_main(gMes->strGId[0], member, chr->unk00, chr->unk04);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0A = gMes->unk0C = 0;
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < n;) {
                    i++;
                    HuSprAttrSet(gMes->strGId[0], i, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                for (i = 0; i < n; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->unk28 += 42.0f;
                    if (chr->unk28 > 360.0f) {
                        chr->unk28 -= 360.0f;
                    }
                    scale = cosdf(chr->unk28);
                    member = i + 1;
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], member, 2);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], member, 2);
                    }
                    HuSprScaleSet(gMes->strGId[0], member, 1.0f, scale);
                }
            }
            scale = gMes->unk0C / 30.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            gMes->unk0C++;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f - scale * 180.0f * scale;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C248_main);
#endif

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C644_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CA24_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CE20_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D134_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D4DC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D890_main);

s32 func_8003DC88_main(GAMEMES *gMes, Gfx **arg1) {
    return func_8003D890_main(gMes, arg1);
}

void func_8003DCA4_main(GAMEMES *gMes, s32 fileId) {
    void *temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v0_5;

    temp_v0 = DataReadTemp(fileId);
    gMes->strSprId[0] = temp_v0_2 = func_80055810_main(temp_v0);
    DataCloseTemp(temp_v0);

    temp_v0 = DataReadTemp(fileId + 1);
    gMes->strSprId[1] = temp_v0_4 = func_80055810_main(temp_v0);
    DataCloseTemp(temp_v0);

    gMes->strGId[0] = temp_v0_5 = HuSprGrpCreate(2, 5);

    func_80055024_main(temp_v0_5, 0, temp_v0_2, 0);
    func_80055458_main(temp_v0_5, 0, 0xFF);
    HuSprPriSet(temp_v0_5, 0, 5);
    HuSprAttrReset(temp_v0_5, 0, 0xFFFF);
    HuSprAttrSet(temp_v0_5, 0, 0x1008);
    func_80054904_main(temp_v0_5, 0, 0xA0, gMes->unk64);
    func_800554C4_main(temp_v0_5, 0, -1);
    func_80055024_main(temp_v0_5, 1, temp_v0_4, 0);
    func_80055458_main(temp_v0_5, 1, 0xFF);
    HuSprPriSet(temp_v0_5, 1, 6);
    HuSprAttrReset(temp_v0_5, 1, 0xFFFF);
    HuSprAttrSet(temp_v0_5, 1, 0x1008);
    func_80055420_main(temp_v0_5, 1, 0x45, 2, 0x85);
    func_800554C4_main(temp_v0_5, 1, 0);
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A76F8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7700_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7708_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7714_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A771C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7724_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A772C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7734_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A773C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7744_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003DE60_main);

extern char *D_800A1410_main[];

typedef struct {
    char str[6];
} GMesStr6;
extern GMesStr6 D_800A7744_main;

s16 func_8003A3C4_main(GAMEMES *gMes, char *str, u8 flag, s16 x, s16 arg4, f32 sx, f32 sy);
u32 func_8003A81C_main(u8 *str, u8 flag);
s16 func_8005B5EC_main(u8 *str);
s32 func_8003A9C8_main(u8 *str, s32 arg1, s32 *frame);
s32 func_8003AC9C_main(u8 *str, s32 arg1, s32 flag, s32 *width);
s16 func_8003AE44_main(s16 arg0);
extern u8 D_800A1334_main[];
extern u8 D_800A136C_main[];
extern u8 D_800A13B0_main[];
s16 func_8003AE9C_main(u8 c, u8 flag);

s32 func_8003E4A4_main(GAMEMES *gMes, Gfx **arg1) {
    char sp18[] = "LOST";
    f64 var_f2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f2;
    f32 temp_f30;
    s16 i;

    var_f2 = strlen(D_800A1410_main[gMes->unk08]);
    temp_f30 = var_f2;

    var_f2 = strlen(sp18);
    temp_f2 = var_f2;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, D_800A1410_main[gMes->unk08], 1, -1, -1);
        func_8003A37C_main(gMes, sp18, 1, -1, -1);

        temp_f20 = (320.0f - (temp_f30 + temp_f2 + 1.0f) * 24.0f) / 2.0f;

        func_80054904_main(gMes->strGId[0], 0, temp_f20 + temp_f30 * 24.0f / 2.0f, gMes->unk64 + 40.0f);
        func_80054904_main(gMes->strGId[1], 0, (320.0f - temp_f20) - temp_f2 * 24.0f / 2.0f, gMes->unk64 + 40.0f);

        for (i = 0; i < temp_f30; i++) {
            HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
        }

        for (i = 0; i < temp_f2; i++) {
            HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
        }

        gMes->unk0A = 0;
    }

    if (gMesCloseF != 0 || gMes->stat == 4) {
        GMesSprKill(gMes);
        return 0;
    }

    if (gMes->unk04 >= 81) {
        gMes->stat = 2;
    }

    if (gMes->unk04 >= 51) {
        gMes->unk0A++;
        if (gMes->unk0A & 0x40) {
            temp_f20_3 = (u16)gMes->unk0A % 32;
            temp_f20_2 = cosdf(temp_f20_3 * (360.0f / 31)) * 55.0f + 200.0f;

            for (i = 0; i < temp_f30; i++) {
                func_80055458_main(gMes->strGId[0], i + 1, temp_f20_2);
            }

            for (i = 0; i < temp_f2; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, temp_f20_2);
            }
        }

        return 1;
    }

    temp_f20_3 = gMes->unk04;
    if (temp_f20_3 <= 30.0f) {
        for (i = 0; i < temp_f30; i++) {
            HuSprAttrReset(gMes->strGId[0], i + 1, 0x8000);
            func_80055458_main(gMes->strGId[0], i + 1, temp_f20_3 * 8.5f);
        }
    }

    temp_f20_3 = gMes->unk04 - 20;
    if (temp_f20_3 <= 30.0f && temp_f20_3 > 0.0f) {
        for (i = 0; i < temp_f2; i++) {
            HuSprAttrReset(gMes->strGId[1], i + 1, 0x8000);
            func_80055458_main(gMes->strGId[1], i + 1, temp_f20_3 * 8.5f);
        }
    }

    return 1;
}

s32 func_80045208_main(void *arg0, void *arg1);

s32 func_8003EBC8_main(GAMEMES *gMes, Gfx **arg1) {
    f32 temp_f22;
    f32 i;

    if (gMes->unk04 == 0) {
        char *temp_v0 = HuMemMemoryAllocPerm(256);

        func_80045208_main(temp_v0, (void *)gMes->unk1C);
        func_8003A37C_main(gMes, temp_v0, gMes->unk02, -1, -1);
        gMes->unk08 = strlen(temp_v0);
        func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);

        HuMemMemoryFreePerm(temp_v0);
    }

    if (gMes->unk04 > gMes->unk06 || gMesCloseF != 0 || gMes->stat == 4) {
        GMesSprKill(gMes);
        return 0;
    }

    if (gMes->unk04 < 14) {
        temp_f22 = sindf(gMes->unk04 * 10.0f) + (1.0f - sindf(130.0f));

        for (i = 0.0f; i < gMes->unk08; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1.0f, gMes->unk68, temp_f22 * gMes->unk6C);
        }
    }

    if (gMes->unk04 > gMes->unk06 - 10) {
        gMes->stat = 2;
        temp_f22 = cosdf((gMes->unk04 - (gMes->unk06 - 10)) * 9.0f);

        for (i = 0.0f; i < gMes->unk08; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1.0f, gMes->unk68, temp_f22 * gMes->unk6C);
        }
    }

    return 1;
}

s32 func_8003EE98_main(GAMEMES *gMes, Gfx **arg1) {
    f32 i;

    if (gMes->unk04 == 0) {
        char *temp_v0 = HuMemMemoryAllocPerm(256);

        func_80045208_main(temp_v0, (void *)gMes->unk1C);
        func_8003A37C_main(gMes, temp_v0, gMes->unk02, -1, -1);
        gMes->unk08 = strlen(temp_v0);

        HuMemMemoryFreePerm(temp_v0);
    }

    if (gMes->unk04 > gMes->unk06 || gMesCloseF != 0 || gMes->stat == 4) {
        GMesSprKill(gMes);
        return 0;
    }

    func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
    func_800552DC_main(gMes->strGId[0], 0, gMes->unk70);

    for (i = 0.0f; i < gMes->unk08; i++) {
        HuSprScaleSet(gMes->strGId[0], i + 1.0f, gMes->unk68, gMes->unk6C);
        func_80055458_main(gMes->strGId[0], i + 1.0f, gMes->unk03);
    }

    return 1;
}

s32 GMesTimerExec(GAMEMES *gMes, Gfx **arg1) {
    f32 temp_f22;
    u8 temp_s2;
    u8 temp_s0;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, "99", 0, -1, -1);
        func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
        func_80055458_main(gMes->strGId[0], 1, 0x100);
        func_80055458_main(gMes->strGId[0], 2, 0x100);
        gMes->unk0A = 0;
    }
    temp_s2 = gMes->unk08 % 100;
    temp_s0 = temp_s2 / 10;
    if (temp_s0 == 0) {
        HuSprAttrSet(gMes->strGId[0], 1, 0x8000);
    } else {
        HuSprAttrReset(gMes->strGId[0], 1, 0x8000);
    }
    func_80055140_main(gMes->strGId[0], 1, temp_s0, 0);
    func_800550F4_main(gMes->strGId[0], 1, 1);
    temp_s0 = temp_s2 % 10;
    func_80055140_main(gMes->strGId[0], 2, temp_s0, 0);
    func_800550F4_main(gMes->strGId[0], 2, 1);
    switch (gMes->unk0A) {
        case 0:
            if (gMes->unk04 < 14) {
                temp_f22 = sindf(gMes->unk04 * 10.0f) * 5.0f + (1.0f - sindf(130.0f) * 5.0f);
                HuSprScaleSet(gMes->strGId[0], 1, temp_f22, temp_f22);
                HuSprScaleSet(gMes->strGId[0], 2, temp_f22, temp_f22);
            } else {
                gMes->unk0A = 1;
            }
            break;
        case 1:
            if (gMes->unk0E != gMes->unk08 && gMes->unk08 < 6) {
                gMes->unk0C = 0;
                if (gMes->unk08 != 0) {
                    gMes->unk0A = 3;
                    HuAudFXPlay(8);
                }
            } else {
                func_80055458_main(gMes->strGId[0], 1, 0x100);
                func_80055458_main(gMes->strGId[0], 2, 0x100);
            }
            break;
        case 2:
            if (gMes->unk0C < 10) {
                func_80055458_main(gMes->strGId[0], 1, 230 - gMes->unk0C * 23);
                func_80055458_main(gMes->strGId[0], 2, 230 - gMes->unk0C * 23);
            } else {
                gMes->unk0A = 1;
                gMes->stat = GMES_STAT_KILL;
            }
            gMes->unk0C++;
            break;
        case 3:
            if (gMes->unk0C < 11) {
                temp_f22 = 1.0f + sindf(gMes->unk0C * 18.0f);
                HuSprScaleSet(gMes->strGId[0], 1, temp_f22, temp_f22);
                HuSprScaleSet(gMes->strGId[0], 2, temp_f22, temp_f22);
                temp_f22 = 230.0f - sindf(gMes->unk0C * 18.0f) * 60.0f;
                func_80055458_main(gMes->strGId[0], 1, temp_f22);
                func_80055458_main(gMes->strGId[0], 2, temp_f22);
            } else {
                gMes->unk0A = 1;
            }
            gMes->unk0C++;
            break;
    }
    gMes->unk0E = gMes->unk08;
    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        gMesTimerId = -1;
        return FALSE;
    }
    return TRUE;
}

// GMesUpdate? GMesTimerUpdate? GMesTimerSet?
void func_8003F578_main(s16 arg0) {
    if (gMesTimerId < 0 || arg0 < 0) {
        return;
    }
    gMesData[gMesTimerId].unk08 = arg0;
}

// GMesKill? GMesTimerKill?
void func_8003F5C0_main(void) {
    if (gMesTimerId < 0) {
        return;
    }
    gMesData[gMesTimerId].unk0A = 2;
    gMesData[gMesTimerId].unk0C = 0;
}

s32 func_8003F604_main(GAMEMES *gMes, Gfx **arg1) {
    char *str1 = "NEW";
    char *str2 = "RECORD";
    s32 ret;
    s32 len1;
    s32 len2;
    s32 i;
    f32 x;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = 1;
    len1 = strlen(str1);
    len2 = strlen(str2);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str1, 1, -1, -1);
            func_8003A37C_main(gMes, str2, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            x = 160.0f - ((f32)((len1 + len2 + 1) * 11) * gMes->unk68 - (f32)(len1 * 11) * gMes->unk6C);
            func_80054904_main(gMes->strGId[0], 0, (gMes->unk60 - 160.0f) + x, gMes->unk64);
            gMes->unk03 = 0;
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            x = ((f32)((len1 + len2 + 1) * 11) * gMes->unk68 - (f32)(len2 * 11) * gMes->unk6C) + 160.0f;
            gMes->unk70 = 0.0f;
            func_80054904_main(gMes->strGId[1], 0, (gMes->unk60 - 160.0f) + x, gMes->unk64);
            func_800552DC_main(gMes->strGId[1], 0, gMes->unk70);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 90.0f;
            break;
        case 1:
            gMes->unk10 += 21.0f;
            gMes->unk68 += 0.016666668f;
            gMes->unk6C = 1.0f - sindf(gMes->unk10) * 0.5f;
            x = 160.0f - ((f32)((len1 + len2 + 1) * 11) * gMes->unk68 - (f32)(len1 * 11) * gMes->unk68);
            gMes->unk70 += 12.0f;
            gMes->unk03 += 8;
            func_80054904_main(gMes->strGId[0], 0, (gMes->unk60 - 160.0f) + x, gMes->unk64);
            func_800552DC_main(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            x = ((f32)((len1 + len2 + 1) * 11) * gMes->unk68 - (f32)(len2 * 11) * gMes->unk68) + 160.0f;
            func_80054904_main(gMes->strGId[1], 0, (gMes->unk60 - 160.0f) + x, gMes->unk64);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 30) {
                gMes->stat = 2;
                func_800552DC_main(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < len1; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 0xFF);
                }
                for (i = 0; i < len2; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, 0xFF);
                }
                gMes->unk0A = 30;
                gMes->unk08 = 2;
            }
            break;
        case 2:
            if (--gMes->unk0A == -1) {
                gMes->unk0A = 0xFF;
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk0A -= 16;
            if (gMes->unk0A <= 0) {
                gMes->unk0A = 0;
                gMes->unk08 = 4;
            }
            for (i = 0; i < len1; i++) {
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk0A);
            }
            for (i = 0; i < len2; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk0A);
            }
            if (gMes->unk04 >= 61) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x252);
    }
    if (gMes->unk04 >= 56) {
        gMes->stat = 2;
    }
    return ret;
}

s32 func_8003FD34_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 3;
    }
    ret = 1;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0092);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk03 = 0xFF;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.2f + 1.0f;
            gMes->unk10 += 15.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
                gMes->unk03 -= 25;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, gMes->unk03);
                }
            }
            if (gMes->unk04 > gMes->unk06) {
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    return ret;
}

s32 func_8003FFD0_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 3;
    }
    ret = 1;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0094);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk03 = 0xFF;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->unk04 >= 10) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.3f + 1.0f;
            gMes->unk10 += 20.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 >= 40) {
                gMes->unk03 -= 51;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, gMes->unk03);
                }
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->stat = 2;
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    return ret;
}

s32 func_80040290_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;
    f32 fade;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = 1;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0098);
            func_80055420_main(gMes->strGId[0], 1, 0x45, 2, 0x85);
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 0.0f, 2.0f);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk68 = sindf(gMes->unk10);
            gMes->unk6C = 2.0f - (1.0f - cosdf(gMes->unk10));
            gMes->unk10 += 9.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 < 10) {
                break;
            }
            gMes->unk08 = 2;
            gMes->unk10 = 90.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
            }
        case 2:
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            gMes->unk68 = 1.5f - GMES_ABSF(sindf(gMes->unk10)) * 0.5f;
            gMes->unk6C = GMES_ABSF(sindf(gMes->unk10)) * 0.7f + 0.3f;
            gMes->unk10 += 12.0f;
            if (gMes->unk04 >= 25) {
                for (i = 0; i < 2; i++) {
                }
                gMes->unk08 = 3;
                gMes->unk10 = 0.0f;
            }
            break;
        case 3:
            gMes->unk03 = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                fade = (f32)(gMes->unk06 - gMes->unk04) / 10.0f;
            } else {
                fade = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                func_80055458_main(gMes->strGId[0], i, gMes->unk03 * fade);
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x24F);
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return ret;
}

s32 func_800407B8_main(GAMEMES *gMes, Gfx **arg1) {
    char *str1 = "READY";
    char *str2 = "GO\xC4";
    s32 ret;
    s32 len1;
    s32 len2;
    s32 i;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 6;
    }
    ret = 1;
    len1 = strlen(str1);
    len2 = strlen(str2);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str1, 1, -1, -1);
            func_8003A37C_main(gMes, str2, 1, -1, -1);
            gMes->unk68 = 0.5f;
            gMes->unk03 = 0;
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            for (i = 0; i < len2; i++) {
                HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
            }
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            gMes->unk08 = 1;
            gMes->unk0C = 0;
            gMes->unk0A = 0;
            break;
        case 1:
            gMes->unk68 += 0.1f;
            gMes->unk03 += 25;
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 10) {
                for (i = 0; i < len1; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.5f, 1.5f);
                    func_80055458_main(gMes->strGId[0], i + 1, 0xFF);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            if (gMes->unk04 >= 35) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk68 += 0.05f;
            gMes->unk03 -= 51;
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 40) {
                for (i = 0; i < len1; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 0);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            gMes->unk68 = gMes->unk6C = sindf(gMes->unk0A * 15) * 3.0f;
            for (i = 0; i < len2; i++) {
                HuSprAttrReset(gMes->strGId[1], i + 1, 0x8000);
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68, gMes->unk6C);
            }
            gMes->unk0A++;
            if (gMes->unk04 >= 50) {
                func_800452BC_main(func_80036610_main());
                gMes->unk08 = 5;
                gMes->unk03 = 0xFF;
            }
            break;
        case 5:
            gMes->stat = 2;
            gMes->unk03 -= 51;
            for (i = 0; i < len2; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            gMes->unk0C++;
            if (gMes->unk04 >= 55) {
                for (i = 0; i < len2; i++) {
                    HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
                }
                gMes->unk08 = 6;
            }
            break;
        case 6:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            ret = 0;
            break;
    }
    return ret;
}

s32 func_80040CF4_main(GAMEMES *gMes, Gfx **arg1) {
    GMesStr6 won = D_800A7744_main;
    s32 ret;
    f32 len1;
    f32 len2;
    f32 len3;
    f32 i;
    f32 scale;

    len1 = strlen(D_800A1410_main[gMes->unk0C]);
    len2 = strlen(D_800A1410_main[gMes->unk0E]);
    len3 = strlen(won.str);
    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 5;
    }
    ret = 1;
    switch (gMes->unk08) {
        case 0:
            func_8003A3C4_main(gMes, D_800A1410_main[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, D_800A1410_main[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            func_8003A37C_main(gMes, won.str, 1, -1, -1);
            gMes->unk60 = 80.0f;
            gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1.0f, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1.0f, 0xFF);
            }
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1.0f, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1.0f, 0xFF);
            }
            for (i = 0.0f; i < len3; i++) {
                HuSprAttrSet(gMes->strGId[2], i + 1.0f, 0x8000);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 1.5f;
            break;
        case 1:
            gMes->unk10 += gMes->unk14;
            gMes->unk64 += gMes->unk10;
            gMes->unk60 = 80.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 >= 15) {
                gMes->unk08 = 2;
                gMes->unk10 = -12.0f;
                gMes->unk14 = 1.0f;
            }
            break;
        case 2:
            gMes->unk10 += gMes->unk14;
            gMes->unk64 += gMes->unk10;
            gMes->unk60 = 80.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 3;
                gMes->unk0A = gMes->unk64;
            }
            break;
        case 3:
            gMes->unk60 = 170.0f;
            gMes->unk64 = 145.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            func_80054904_main(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < len3; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1.0f, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1.0f, 0xFF);
                HuSprAttrReset(gMes->strGId[2], i + 1.0f, 0x8000);
            }
            gMes->unk08 = 4;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 4:
            gMes->unk60 = sindf(gMes->unk10) + 160.0f;
            gMes->unk64 = sindf(gMes->unk14) + 145.0f;
            func_80054904_main(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                scale = (f32)(gMes->unk06 - gMes->unk04) / 10.0f;
                for (i = 0.0f; i < len1; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1.0f, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < len2; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1.0f, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < len3; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1.0f, 1.0f, scale);
                }
            }
            break;
        case 5:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return ret;
}

s32 func_80041700_main(GAMEMES *gMes, Gfx **arg1) {
    s32 ret;
    s32 i;
    f32 fade;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 3;
    }
    ret = 1;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0096);
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk70 = 0.0f;
            gMes->unk03 = 0xFF;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            func_800552DC_main(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk6C = gMes->unk68 += 0.05f;
            gMes->unk70 += 36.0f;
            func_800552DC_main(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 >= 10) {
                func_800552DC_main(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < 2; i++) {
                    HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
                }
                gMes->unk08 = 2;
                gMes->unk10 = 0.0f;
            }
            break;
        case 2:
            gMes->unk03 = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                fade = (f32)(gMes->unk06 - gMes->unk04) / 10.0f;
            } else {
                fade = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                func_80055458_main(gMes->strGId[0], i, gMes->unk03 * fade);
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 == 30) {
        HuAudFXPlay(0x255);
    }
    if (gMes->unk04 == gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7810_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7830_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80041B68_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80042AC8_main);

s32 func_800440D4_main(GAMEMES *gMes, Gfx **arg1) {
    char *str1 = "GOT";
    char *str2 = "ITEM\xC4";
    s32 ret;
    s32 len1;
    s32 len2;
    s32 i;
    f32 fade;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 4;
    }
    ret = 1;
    len1 = strlen(str1);
    len2 = strlen(str2);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str1, 1, -1, -1);
            func_8003A37C_main(gMes, str2, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk60 = cosdf(0.0f) * 55.0f + 149.0f;
            gMes->unk64 = sindf(0.0f) * 55.0f + 120.0f;
            gMes->unk03 = 0;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = cosdf(180.0f) * 55.0f + 149.0f;
            gMes->unk64 = sindf(180.0f) * 55.0f + 120.0f;
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, 0);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 180.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->unk14 += 12.0f;
            gMes->unk6C = gMes->unk68 += 0.033333335f;
            gMes->unk60 = cosdf(gMes->unk10) * 55.0f + 149.0f;
            gMes->unk64 = sindf(gMes->unk10) * 55.0f + 120.0f;
            gMes->unk03 += 17;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = cosdf(gMes->unk14) * 55.0f + 149.0f;
            gMes->unk64 = sindf(gMes->unk14) * 55.0f + 120.0f;
            func_80054904_main(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 15) {
                gMes->unk08 = 2;
                gMes->unk10 = 630.0f;
            }
            break;
        case 2:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.1f + 1.1f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
            }
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68, gMes->unk68);
            }
            if (gMes->unk04 >= 35) {
                for (i = 0; i < len1; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                for (i = 0; i < len2; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                }
                gMes->unk08 = 3;
            }
            break;
        case 3:
            if (gMes->unk04 > gMes->unk06 - 10) {
                fade = (f32)(gMes->unk06 - gMes->unk04) / 10.0f * 255.0f;
                for (i = 0; i < len1; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, fade);
                }
                for (i = 0; i < len2; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, fade);
                }
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 == 1) {
        HuAudFXPlay(0x260);
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return ret;
}

s32 func_800448C0_main(GAMEMES *gMes, Gfx **arg1) {
    char *str1 = "GOT";
    char *str2 = "ITEM";
    char *str3 = "\xC3";
    s32 ret;
    s32 len1;
    s32 len2;
    s32 len3;
    s32 i;

    if (gMesCloseF != 0 || gMes->stat == 4) {
        gMes->unk08 = 5;
    }
    ret = 1;
    len1 = strlen(str1);
    len2 = strlen(str2);
    len3 = strlen(str3);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str1, 1, -1, -1);
            func_8003A37C_main(gMes, str2, 1, -1, -1);
            func_8003A37C_main(gMes, str3, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk60 = 99.0f;
            gMes->unk64 = 45.0f;
            gMes->unk03 = 0;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A = 189;
            gMes->unk0C = 195;
            func_80054904_main(gMes->strGId[1], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            func_80054904_main(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < len3; i++) {
                /* retail hides member 1 every time, not member i + 1 (one character, so the same) */
                HuSprAttrSet(gMes->strGId[2], 1, 0x8000);
                HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[2], i + 1, 0xFF);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->unk6C = gMes->unk68 += 0.033333335f;
            gMes->unk60 = sindf(gMes->unk10) * 20.0f + 94.0f;
            gMes->unk64 += 5.0f;
            gMes->unk03 += 17;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len1; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A = sindf(gMes->unk10) * 20.0f + 194.0f;
            gMes->unk0C -= 5;
            func_80054904_main(gMes->strGId[1], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < len2; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 15) {
                gMes->unk0A = 330;
                func_80054904_main(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
                for (i = 0; i < len1; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[0], i + 1, 0xFF);
                }
                for (i = 0; i < len2; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[1], i + 1, 0xFF);
                }
                for (i = 0; i < len3; i++) {
                    HuSprAttrReset(gMes->strGId[2], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[2], i + 1, 0xFF);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk0A -= 16;
            func_80054904_main(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 3;
                gMes->unk10 = 630.0f;
            }
            break;
        case 3:
            gMes->unk68 = sindf(gMes->unk10) * 0.5f + 1.5f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < len3; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->unk68, gMes->unk68);
            }
            if (gMes->unk04 >= 40) {
                for (i = 0; i < len3; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            ret = 0;
            break;
    }
    if (gMes->unk04 >= 31) {
        gMes->stat = 2;
    }
    return ret;
}

u32 func_8003A81C_main(u8 *str, u8 arg1);

void func_80045010_main(const s16 *arg0, s32 arg1) {
    u8 *temp_v0;
    u8 *var_s1;

    var_s1 = temp_v0 = HuMemMemoryAllocPerm(512);
    func_80045208_main(temp_v0, (void *)arg0);

    for (; *var_s1 != 0; var_s1++) {
        func_8003A81C_main(var_s1, arg1);
        if (var_s1[1] == 128 || var_s1[1] == 129) {
            var_s1++;
        }
    }

    D_800B1A52_main = 1;
    HuMemMemoryFreePerm(temp_v0);
}

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800450B8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80045208_main);

s32 func_800452A0_main(void *arg0, void *arg1) {
    return func_80045208_main(arg0, arg1);
}

void func_800452BC_main(s32 arg0) {
}

s32 func_800452C4_main(void) {
    switch (omovl) {
        case 0x1:
        case 0x2:
        case 0x6:
        case 0x1B:
        case 0x1D:
        case 0x1E:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x34:
        case 0x38:
        case 0x41:
            return 120;
        case 0xF:
            return 190;
        case 0x13:
        case 0x27:
        case 0x2C:
        case 0x43:
            return 160;
        default:
            return 180;
    }
}

s32 func_80045314_main(void) {
    switch (omovl) {
        case 2:
            return 20;
        case 3:
            return -20;
        default:
            return 0;
    }
}
