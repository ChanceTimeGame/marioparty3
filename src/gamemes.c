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

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80036610_main);
s32 func_80036610_main(void);

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

void func_800370D0_main(s16 mesId, s16 time) {
    if (time == -1) {
        time = 0x7FFF;
    }
    gMesData[mesId].unk06 = time;
}

void func_80037114_main(s16 mesId, f32 x, f32 y) {
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

s32 func_800371DC_main(void) {
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

void func_8003724C_main(s16 time) {
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

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037574_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037878_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80037C44_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038208_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003843C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038934_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80038D78_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800392AC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003966C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80039A6C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80039E80_main);

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

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A37C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A3C4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A81C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A9C8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AC9C_main);

s16 func_8003AE44_main(s16 arg0) {
    void *data = DataReadTemp(arg0 | 0xC0000);
    s16 ret = func_80055810_main(data);

    DataCloseTemp(data);
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AE9C_main);

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

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C058_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C248_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C644_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CA24_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CE20_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D134_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D4DC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D890_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003DC88_main);

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

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80041700_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7810_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7830_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80041B68_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80042AC8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78C8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78CC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800440D4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800448C0_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80045010_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800450B8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80045208_main);

s32 func_800452A0_main(void *arg0, void *arg1) {
    return func_80045208_main(arg0, arg1);
}

void func_800452BC_main(s32 arg0) {
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78F4_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", jtbl_800A78F8_main);

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
