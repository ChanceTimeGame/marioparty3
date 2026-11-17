#include "common.h"
#include "mallocblock.h"
#include "math.h"
#include "game/process.h"
#include "game/vibrator.h"
#include "gcc/string.h"

/* 47D880.c's sprite list. */
typedef struct MgModeSprDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ u16 prio;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
} MgModeSprDef; // Size 0xC

typedef struct MgModeSpr {
    /* 0x00 */ s16 sprite;
    /* 0x02 */ u16 grp;
} MgModeSpr; // Size 0x4

#define MG_SPR_NONE ((MgModeSpr*)-1)

/* gamemes.c's GAMEMES (not in a header). */
typedef struct MgGameMes {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 len;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} MgGameMes; // Size 0x74

/* The minigame info table (stride 0x14); unk06 holds the picture file. */
typedef struct MgInfo {
    /* 0x00 */ char unk00[6];
    /* 0x06 */ u16 pic;
    /* 0x08 */ char unk08[0xC];
} MgInfo; // Size 0x14

typedef struct MgCB890 {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s16 unk04; /* coin rate */
} MgCB890;

typedef struct MgD1FDC {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 coins;
} MgD1FDC;

typedef struct MgD1F2A {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
} MgD1F2A;

MgModeSpr* func_80116794_mgmode(MgModeSprDef* defs);
void func_801168E0_mgmode(MgModeSpr* list);
void func_80116968_mgmode(MgModeSpr* list, s16 idx, s16 x, s16 y);
void func_801169A0_mgmode(MgModeSpr* list, s16 idx);
void func_801169C8_mgmode(MgModeSpr* list, s16 idx);
void func_80116A48_mgmode(MgModeSpr* list, s16 idx, f32 x, f32 y);
void func_80116AA8_mgmode(MgModeSpr* list, s16 idx, s16 arg2);
void func_80116AEC_mgmode(MgModeSpr* list, s16 idx, u16 arg2);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_80116D4C_mgmode(void);
void func_80118888_mgmode(s16 arg0);
void func_801188A4_mgmode(s16 arg0);
void func_80118624_mgmode(s16 dst, s16 src);

void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
s16 func_8003A37C_main(MgGameMes* gMes, char* str, u8 flag, s16 x, s16 arg4);
void GMesSprKill(MgGameMes* gMes);
void func_80088800_main(f32* mtx, f32 x, f32 y, f32 z);

extern MgInfo D_800A6D40_main[];
extern MgCB890 D_800CB890_main;
extern MgD1FDC D_800D1FDC_main;
extern MgD1F2A D_800D1F2A_main;
extern u16 D_800D0418_main[];
extern u8 D_800D2008_main;

extern MgModeSpr* D_801194C0_mgmode;
extern s16 D_801194C4_mgmode;
extern s32 D_801194C8_mgmode;
extern s16 D_801195BC_mgmode[];
extern MgModeSpr* D_801195D0_mgmode;
extern MgModeSprDef D_8011A270_mgmode[];
extern MgModeSprDef D_8011A2C4_mgmode[];
extern char D_8011B510_mgmode[];
extern u8* D_8011B610_mgmode[3];
extern s16 D_8011B61C_mgmode;
extern s16 D_8011B61E_mgmode;
extern s16 D_8011B624_mgmode;
extern s16 D_8011B6A8_mgmode;
extern s16 D_8011B790_mgmode;
extern s16 D_8011B792_mgmode;
extern s16 D_8011B794_mgmode;
extern s16 D_8011B796_mgmode;
extern s16 D_8011B798_mgmode;
extern s16 D_8011B79C_mgmode;
extern s16 D_8011B808_mgmode;
extern MgGameMes D_8011B810_mgmode;
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B8B8_mgmode[];

void func_80114614_mgmode(s16 idx);
void func_80114804_mgmode(s16 rate, s16 count, s16 total);
void func_80115A9C_mgmode(s32 x, s32 y, s32 coins);
void func_80115BB8_mgmode(s16 n);
void func_80115CAC_mgmode(s16 n);
void func_80115CDC_mgmode(MgModeSpr* list, s16 first, s16 n, s16 digits);
void func_80115E9C_mgmode(s32 mes, s16 x, s16 y);
void func_80116024_mgmode(void);
void func_801160A0_mgmode(s16 alpha);
void func_80116260_mgmode(void);
void func_801162B4_mgmode(f32 cx, f32 angle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112CF4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112F98_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80113204_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801134C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801136EC_mgmode);

/* Asks to spend the coins (message 0x5813); with 11 or more coins asks again (0x5814) in a
   centred window. Returns 1 for yes. */
s32 func_80114048_mgmode(void) {
    s16 size[2];
    s16 win;
    s32 choice;
    s32 ret = 0;

    func_8005B43C_main(D_8011B6A8_mgmode, 0x5813, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) == 0) {
        if (D_800D1FDC_main.coins < 11) {
            ret = 1;
        } else {
            func_80061A5C_main(D_8011B6A8_mgmode, 0);
            func_80060394_main(1, size, 0x5814);
            win = func_80061188_main(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
            func_8005FE54_main(win, 1 << D_8011B808_mgmode);
            func_80061388_main(win);
            func_8005B43C_main(win, 0x5814, -1, -1);
            while (func_8005E0C0_main(win) != 0) {
                HuPrcVSleep();
            }
            choice = func_8005E1D8_main(win, 0, 0);
            func_80061A5C_main(win, 0);
            func_8005F364_main(win);
            if ((s16)choice == 0) {
                ret = 1;
            }
        }
    }
    return ret;
}

/* Shows the coin panel, optionally popping it in. */
void func_801141EC_mgmode(s32 pop) {
    f32 t;
    f32 sx;
    f32 sy;
    s16 i;

    if (D_801194C0_mgmode == MG_SPR_NONE) {
        D_801194C0_mgmode = func_80116794_mgmode(D_8011A2C4_mgmode);
        if (pop) {
            HuAudFXPlay(0x243);
            func_80116A48_mgmode(D_801194C0_mgmode, 0, 0.0f, 0.0f);
            HuPrcSleep(5);
            for (i = 0; i < 11; i++) {
                t = i / 10.0f;
                sx = sindf(t * 90.0f);
                sy = cosdf(t * 270.0f + 90.0f);
                if (sy < 0.0f) {
                    sy = -sy;
                }
                func_80116A48_mgmode(D_801194C0_mgmode, 0, sx, sy);
                HuPrcVSleep();
            }
        }
        func_80116AEC_mgmode(D_801194C0_mgmode, 0, 20);
    }
}

void func_80114344_mgmode(void) {
    f32 s;
    s16 i;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        s = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_801194C0_mgmode, 0, s, s);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_801194C0_mgmode);
    D_801194C0_mgmode = MG_SPR_NONE;
}

/* Counts the bonus coins into the total, then plays the win or lose motion and voice. */
#ifdef NON_MATCHING
/* WIP */
void func_80114404_mgmode(void) {
    s16 rate = D_800CB890_main.unk04;
    s16 count = GwPlayer[0].bonusCoin;
    s16 total;
    s16 voice;
    s16 i;

    func_801169A0_mgmode(D_801194C0_mgmode, 1);
    func_80116968_mgmode(D_801194C0_mgmode, 1, 184, 46);
    func_801169A0_mgmode(D_801194C0_mgmode, 2);
    func_80116968_mgmode(D_801194C0_mgmode, 2, 184, 98);
    func_80115A9C_mgmode(184, 122, D_800D1FDC_main.coins);
    func_80114804_mgmode(rate, 0, 0);
    func_80115BB8_mgmode(D_800D1FDC_main.coins);
    func_80115CAC_mgmode(D_800D1FDC_main.coins);
    HuPrcSleep(10);
    for (i = 0; i <= count; i++) {
        total = rate * i;
        func_80114804_mgmode(rate, i, total);
        func_80115BB8_mgmode(D_800D1FDC_main.coins + total);
        func_80115CAC_mgmode(D_800D1FDC_main.coins + total);
        HuAudFXPlay(9);
        HuPrcSleep(2);
    }
    D_800D1FDC_main.coins += count * rate;
    if (count == 0) {
        func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B796_mgmode, 0, 8, 0);
        voice = GwPlayer[0].chr + 0x287;
    } else {
        func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
        voice = GwPlayer[0].chr + 0x275;
    }
    func_8004AC5C_main(voice, 0);
    func_80114614_mgmode(8);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114404_mgmode);
#endif

/* Waits until model slot idx has finished its motion. */
void func_80114614_mgmode(s16 idx) {
    while (func_8001C7D0_main(D_8011B8A8_mgmode[idx]) != -1.0f ||
           HmfModelData[D_8011B8A8_mgmode[idx]].unk40 <
               D_800CCF58_main[HmfModelData[D_8011B8A8_mgmode[idx]].unk02].unk02) {
        HuPrcVSleep();
    }
}

void func_801146D8_mgmode(void) {
    f32 s;
    s16 i;
    s16 j;

    for (i = 0; i < 10; i++) {
        s = 1.0f - i / 10.0f;
        for (j = 1; j < 21; j++) {
            func_80116A48_mgmode(D_801194C0_mgmode, j, s, s);
        }
        HuPrcVSleep();
    }
    for (j = 1; j < 21; j++) {
        func_801169C8_mgmode(D_801194C0_mgmode, j);
        func_80116A48_mgmode(D_801194C0_mgmode, j, 1.0f, 1.0f);
    }
}

/* Shows "rate x count = total" with the panel's digit sprites. */
void func_80114804_mgmode(s16 rate, s16 count, s16 total) {
    s16 i;

    if (total >= 10000) {
        total = 9999;
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 3, rate, 3);
    for (i = 0; i < 3; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 3, i * 16 + 104, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 8, count, 2);
    for (i = 0; i < 2; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 8, i * 16 + 168, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 11, total, 4);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 11, i * 16 + 216, 70);
    }
    func_801169A0_mgmode(D_801194C0_mgmode, 7);
    func_80116968_mgmode(D_801194C0_mgmode, 7, 152, 70);
    func_801169A0_mgmode(D_801194C0_mgmode, 10);
    func_80116AA8_mgmode(D_801194C0_mgmode, 10, 3);
    func_80116968_mgmode(D_801194C0_mgmode, 10, 200, 70);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801149F4_mgmode);

/* Lets the player pick how many coins to spend (D-pad: +-10, +-1); A confirms a non-zero amount,
   B returns -1. */
#ifdef NON_MATCHING
/* WIP */
s16 func_80114C80_mgmode(void) {
    s16 n = 0;
    s16 step;

    func_80115A9C_mgmode(184, 126, 0);
    while (TRUE) {
        HuPrcVSleep();
        if ((D_800D5558_main[D_8011B808_mgmode] >> 15) & (n != 0)) {
            HuAudFXPlay(0x247);
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            n = -1;
            break;
        }
        if (D_800D0590_main[D_8011B808_mgmode] & 0x200) {
            step = 10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & 0x100) {
            step = -10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & 0x800) {
            step = 1;
        } else {
            step = -((D_800D0590_main[D_8011B808_mgmode] & 0x400) != 0);
        }
        if (step != 0) {
            HuAudFXPlay(0x246);
        }
        if (((n == D_800D1FDC_main.coins) | (n == 100)) && step > 0) {
            n = 0;
        } else if (n + step >= 100 || n + step > D_800D1FDC_main.coins || n + step < 0) {
            n = D_800D1FDC_main.coins;
            if (n > 100) {
                n = 100;
            }
        } else {
            n += step;
        }
        func_80115BB8_mgmode(n);
        func_80115CAC_mgmode(D_800D1FDC_main.coins - n);
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114C80_mgmode);
#endif

void func_80114EBC_mgmode(void) {
    s16 alpha;
    s16 i;

    for (i = 0; i < 10; i++) {
        alpha = (1.0f - i / 10.0f) * 255.0f;
        func_8000BBFC_main(D_801194C4_mgmode, alpha);
        func_801160A0_mgmode(alpha);
        HuPrcVSleep();
    }
    func_80116024_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
}

/* A coin block drops onto the player, who jumps and hits it. */
void func_80114FA0_mgmode(void) {
    s16 block = D_8011B8B8_mgmode[7];
    s16 shadow;
    s16 i;
    f32 y;
    f32 scale;

    shadow = func_8000CED8_main(0xB0004, 0x2A9);
    func_8001C8A8_main(shadow, 2);
    func_8000D018_main(shadow, 50.0f);
    func_8000CD00_main(shadow, 2.0f, 20.0f, 0.0f);
    func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B790_mgmode, 0, 8, 0);
    func_8001C258_main(block, 4, 0);
    Hu3DModelPosSet(block, 2.0f, 500.0f, -382.0f);
    func_8000CFA4_main(shadow, 2.0f, 500.0f, -332.0f);
    Hu3DModelRotSet(block, 30.0f, 80.0f, 3.0f);
    func_80088800_main(HmfModelData[block].mtx, 0.0f, 0.0f, 20.0f);
    scale = 1.0f;
    HuAudFXPlay(0x249);
    for (i = 0; i < 51; i++) {
        y = (1.0f - sindf(i / 50.0f * 90.0f)) * 400.0f + 100.0f;
        HmfModelData[block].pos.y = y;
        func_8000CFA4_main(shadow, 2.0f, y + 30.0f, -332.0f);
        if (i == 10) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B79C_mgmode, 0, 8, 0);
        }
        if (i == 40) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
            RepeatVibrator(D_8011B808_mgmode, 20, 0, 20);
        }
        if (i >= 31) {
            scale -= 0.1f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            Hu3DModelScaleSet(block, scale, scale, scale);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(block, 4, 4);
    func_8000D044_main(shadow);
}

/* Process: opens the iris mask, plays the jump, waits for D_801194C8 to clear, closes it. */
void func_801152C0_mgmode(void) {
    s16 i;

    D_801194C8_mgmode = 0;
    HuAudFXPlay(0x248);
    func_80116260_mgmode();
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0x8000);
    for (i = 0; i < 31; i++) {
        if (i == 15) {
            func_80118888_mgmode(D_8011B624_mgmode);
        }
        if (i == 25) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B798_mgmode, 0, 8, 0);
            func_8004AC5C_main(GwPlayer[0].chr + 0x263, 0);
        }
        func_80055458_main(D_8011B61E_mgmode, 0, (f32)i / 30.0f * 220.0f);
        func_801162B4_mgmode(186.0f, sindf((f32)i / 30.0f * 90.0f) * 10.0f);
        HuPrcVSleep();
    }
    func_80114614_mgmode(8);
    D_801194C8_mgmode = 1;
    do {
        HuPrcVSleep();
    } while (D_801194C8_mgmode != 0);
    for (i = 0; i < 11; i++) {
        func_80055458_main(D_8011B61E_mgmode, 0, (1.0f - (f32)i / 30.0f) * 220.0f);
        HuPrcVSleep();
    }
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x8000);
    func_801188A4_mgmode(D_8011B624_mgmode);
    omDelPrcObj(NULL);
}

/* The player walks from the door to the block spot and turns to face the camera. */
#ifdef NON_MATCHING
/* WIP */
void func_80115590_mgmode(void) {
    s16 shadow = D_8011B8B8_mgmode[9];
    s16 player = D_8011B8B8_mgmode[0];
    s16 i;
    f32 t;
    f32 yaw;
    f32 dx;
    f32 dz;

    func_8001C258_main(player, 4, 0);
    func_8001C258_main(shadow, 4, 0);
    func_8001F304_main(player, D_8011B792_mgmode);
    func_8001C814_main(player, 2, 2);
    dx = 198.0f;
    dz = 210.0f;
    yaw = atan2df(dx, dz) + 180.0f;
    Hu3DModelPosSet(player, 200.0f, 0.0f, -122.0f);
    Hu3DModelRotSet(player, 0.0f, yaw, 0.0f);
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        Hu3DModelPosSet(player, dx * t + 2.0f, 0.0f, dz * t + -332.0f);
        func_80118624_mgmode(shadow, player);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    func_8001C624_main(player, D_8011B790_mgmode, 0, 8, 2);
    for (i = 0; i < 9; i++) {
        HmfModelData[player].rot.y = (1.0f - i / 8.0f) * yaw;
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115590_mgmode);
#endif

/* The player turns round and walks back to the door. */
#ifdef NON_MATCHING
/* WIP */
void func_80115848_mgmode(void) {
    s16 shadow = D_8011B8B8_mgmode[9];
    s16 player = D_8011B8B8_mgmode[0];
    s16 i;
    f32 t;
    f32 yaw;
    f32 dx;
    f32 dz;

    func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B792_mgmode, 0, 8, 2);
    dx = -198.0f;
    dz = -210.0f;
    yaw = atan2df(dx, dz) + 180.0f;
    for (i = 0; i < 9; i++) {
        HmfModelData[player].rot.y = i / 8.0f * yaw;
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        Hu3DModelPosSet(player, dx * t + 200.0f, 0.0f, dz * t + -122.0f);
        func_80118624_mgmode(shadow, player);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(player, 4, 4);
    func_8001C258_main(shadow, 4, 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115848_mgmode);
#endif

/* Places the coin counter (label, icon, four digits) at (x, y) showing coins. */
#ifdef NON_MATCHING
/* WIP */
void func_80115A9C_mgmode(s32 x, s32 y, s32 coins) {
    s16 i;
    s32 left = x - 40;

    func_80116968_mgmode(D_801194C0_mgmode, 15, left, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 15);
    func_80116968_mgmode(D_801194C0_mgmode, 16, x - 24, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 16);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 17, left + (i * 16 + 32), y);
    }
    func_80115BB8_mgmode(coins);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115A9C_mgmode);
#endif

void func_80115BB8_mgmode(s16 n) {
    func_80115CDC_mgmode(D_801194C0_mgmode, 17, n, 4);
}

void func_80115BE8_mgmode(void) {
    s16 i;

    func_801169C8_mgmode(D_801194C0_mgmode, 15);
    func_801169C8_mgmode(D_801194C0_mgmode, 16);
    for (i = 0; i < 4; i++) {
        func_801169C8_mgmode(D_801194C0_mgmode, i + 17);
    }
}

void func_80115C5C_mgmode(s16 n) {
    if (D_801195D0_mgmode == MG_SPR_NONE) {
        D_801195D0_mgmode = func_80116794_mgmode(D_8011A270_mgmode);
        func_80115CAC_mgmode(n);
    }
}

void func_80115CAC_mgmode(s16 n) {
    func_80115CDC_mgmode(D_801195D0_mgmode, 2, n, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/479470", D_8011A688_mgmode);

/* Shows n (at most 9999) right-aligned in sprites first.. of list, digits wide; leading blanks
   are hidden. */
void func_80115CDC_mgmode(MgModeSpr* list, s16 first, s16 n, s16 digits) {
    char buf[8];
    s16 skip;
    s16 i;

    if (n >= 10000) {
        n = 9999;
    }
    sprintf(buf, "%4d", n);
    skip = 4 - digits;
    for (i = 0; i < digits; i++) {
        if ((u8)buf[skip + i] < '0') {
            func_801169C8_mgmode(list, first + i);
        } else {
            func_801169A0_mgmode(list, first + i);
            func_80116AA8_mgmode(list, first + i, (u8)buf[skip + i] & 0xF);
        }
    }
}

void func_80115E20_mgmode(void) {
    func_801168E0_mgmode(D_801195D0_mgmode);
    D_801195D0_mgmode = MG_SPR_NONE;
}

void func_80115E4C_mgmode(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = -1;
    }
}

/* Shows message mes without its control codes as a sprite string at (x, y). */
void func_80115E9C_mgmode(s32 mes, s16 x, s16 y) {
    char* str;
    s16 len;
    s16 n;
    s16 i;

    str = func_800364DC_main((void*)mes);
    len = strlen(str);
    n = 0;
    for (i = 0; i <= len; i++) {
        if ((u8)str[i] >= '0') {
            D_8011B510_mgmode[n++] = str[i];
        }
    }
    D_8011B510_mgmode[n] = 0;
    func_800365E8_main(str);
    D_8011B810_mgmode.len = n;
    func_8003A37C_main(&D_8011B810_mgmode, D_8011B510_mgmode, 0, -1, -1);
    for (i = 0; i < D_8011B810_mgmode.len; i++) {
        HuSprPriSet(D_8011B810_mgmode.strGId[0], i + 1, 10);
        HuSprScaleSet(D_8011B810_mgmode.strGId[0], i + 1, 0.7f, 1.0f);
    }
    func_80054904_main(D_8011B810_mgmode.strGId[0], 0, x, y);
}

void func_80116024_mgmode(void) {
    s16 i;

    if (D_8011B810_mgmode.strGId[0] != -1) {
        GMesSprKill(&D_8011B810_mgmode);
        for (i = 0; i < 16; i++) {
            D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = -1;
        }
    }
}

void func_801160A0_mgmode(s16 alpha) {
    s16 i;

    for (i = 0; i < D_8011B810_mgmode.len; i++) {
        func_80055458_main(D_8011B810_mgmode.strGId[0], i + 1, alpha);
    }
}

/* Creates the full-screen iris mask sprite and its three 4-bit 320x120 frame buffers. */
void func_8011611C_mgmode(void) {
    HuSprite* spr;

    D_8011B61C_mgmode = func_8000B838_main(0x12003D);
    D_8011B61E_mgmode = HuSprGrpCreate(5, 0);
    func_80055024_main(D_8011B61E_mgmode, 0, D_8011B61C_mgmode, 0);
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0xFFFF);
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x9008);
    func_80054904_main(D_8011B61E_mgmode, 0, 160, 120);
    HuSprPriSet(D_8011B61E_mgmode, 0, 15);
    HuSprScaleSet(D_8011B61E_mgmode, 0, 1.0f, 2.0f);
    spr = HuSprGet(D_8011B61E_mgmode, 0);
    HuMemFree(spr->unk_84->unk00->unk00);
    D_8011B610_mgmode[0] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[1] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[2] = HuMemAllocTag(0x4B00, 0x7918);
    spr->unk_84->unk00->unk00 = D_8011B610_mgmode[0];
    func_80116260_mgmode();
}

void func_80116260_mgmode(void) {
    memset(D_8011B610_mgmode[0], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[1], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[2], 0xFF, 0x4B00);
}

#define MG_PIX_CLR(p, x) (*(p) = ((x) & 1) ? (*(p) & 0xF0) : (*(p) & 0xF))
#define MG_PIX_SET(p, x, c) (*(p) = ((x) & 1) ? (*(p) | (c)) : (*(p) | ((c) << 4)))

/* Draws the iris mask into this frame's buffer: a wedge centred on cx, open by angle, with a
   two-pixel rim. */
#ifdef NON_MATCHING
/* WIP */
void func_801162B4_mgmode(f32 cx, f32 angle) {
    u8* p = D_8011B610_mgmode[D_800D2008_main];
    u8* q;
    f32 s = sindf(angle);
    f32 w;
    s16 l;
    s16 r;
    s16 x;
    s16 y;

    for (y = 0; y < 120; y++) {
        w = s * (y + 100);
        l = cx - w;
        r = cx + w;
        for (x = 0; x < 320; x++) {
            if ((l < x) & (x < r)) {
                MG_PIX_CLR(p, x);
            } else {
                MG_PIX_SET(p, x, 0xF);
            }
            p += x & 1;
        }
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + l - 1) / 2];
        MG_PIX_CLR(q, l - 1);
        MG_PIX_SET(q, l - 1, 0xA);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + r + 1) / 2];
        MG_PIX_CLR(q, r + 1);
        MG_PIX_SET(q, r + 1, 0xA);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + l) / 2];
        MG_PIX_CLR(q, l);
        MG_PIX_SET(q, l, 4);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + r) / 2];
        MG_PIX_CLR(q, r);
        MG_PIX_SET(q, r, 4);
    }
    HuSprGet(D_8011B61E_mgmode, 0)->unk_84->unk00->unk00 = D_8011B610_mgmode[D_800D2008_main];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801162B4_mgmode);
#endif
