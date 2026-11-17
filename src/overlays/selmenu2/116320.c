#include "common.h"

/* Second select menu (a later revision of selmenu's: 8 pages, its own name tables). */

/* m5: data and bss the C functions use */
extern s32 fontcolor;
extern GW_PLAYER D_80109B20_selmenu2[4];
extern s8 D_80109C80_selmenu2[4]; /* last stick x per pad */
extern s8 D_80109C84_selmenu2[4]; /* last stick y per pad */
extern u8 D_80109CF8_selmenu2[4]; /* menu input bits per pad */
extern u16 D_80109CFC_selmenu2[4]; /* held direction per pad */
extern u16 D_80109D04_selmenu2[4]; /* hold time */
extern u16 D_80109D0C_selmenu2[4]; /* repeat delay */
void func_80107DA4_selmenu2(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801059A0_selmenu2);

/* selmenu func_80105F30_selmenu */
void func_80105F74_selmenu2(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
}

/* selmenu func_80105FC8 */
void func_8010600C_selmenu2(omObjData *obj) {
    s32 i;
    s8 x;
    s8 y;
    s32 last;

    for (i = 0; i < 4; i++) {
        D_80109CF8_selmenu2[i] = 0;
        if (CheckControllerRead(i) == 0) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        x = D_800CBB6E_main[i];
        y = D_800D20A1_main[i];
        if (D_800D5558_main[i] & 0x808) {
            D_80109CF8_selmenu2[i] |= 1;
        }
        if (D_800D5558_main[i] & 0x404) {
            D_80109CF8_selmenu2[i] |= 2;
        }
        if (D_800D5558_main[i] & 0x202) {
            D_80109CF8_selmenu2[i] |= 4;
        }
        if (D_800D5558_main[i] & 0x101) {
            D_80109CF8_selmenu2[i] |= 8;
        }
        if (y < -10) {
            last = D_80109C84_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 2;
            }
        }
        if (y > 10) {
            last = D_80109C84_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 1;
            }
        }
        if (x < -10) {
            last = D_80109C80_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 4;
            }
        }
        if (x > 10) {
            last = D_80109C80_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 8;
            }
        }
        D_80109C80_selmenu2[i] = x;
        D_80109C84_selmenu2[i] = y;
        if (D_800D5558_main[i] & 0x2000) {
            D_80109CF8_selmenu2[i] |= 0x40;
        }
        if (((D_800CDA7C_main[i] & 0x808) != 0) | (y > 10)) {
            if (D_80109CFC_selmenu2[i] & 1) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 1) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 1;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 1;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x404) != 0) | (y < -10)) {
            if (D_80109CFC_selmenu2[i] & 2) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 2) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 2;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 2;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x202) != 0) | (x < -10)) {
            if (D_80109CFC_selmenu2[i] & 4) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 4) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 4;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 4;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x101) != 0) | (x > 10)) {
            if (D_80109CFC_selmenu2[i] & 8) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 8) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 8;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 8;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else {
            D_80109D04_selmenu2[i] = 0;
        }
        if (D_800D5558_main[i] & 0x8000) {
            D_80109CF8_selmenu2[i] |= 0x10;
        }
        if (D_800D5558_main[i] & 0x4000) {
            D_80109CF8_selmenu2[i] |= 0x20;
        }
        if (D_800D5558_main[i] & 0x1000) {
            D_80109CF8_selmenu2[i] |= 0x80;
        }
        if ((D_800CDA7C_main[i] & 0x30) == 0x30) {
            omOvlReturnEx(0);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801067B4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106A54_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106D94_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801078CC_selmenu2);

/* selmenu func_80107DEC_selmenu */
void func_80107D94_selmenu2(omObjData *obj) {
    obj->func = func_80107DA4_selmenu2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80107DA4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108718_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108764_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801087E0_selmenu2);

/* selmenu func_801089C0_selmenu */
void func_80108910_selmenu2(u16 x, u16 y, char *str, u16 color, u16 shadow) {
    fontcolor = shadow;
    print8(x + 1, y + 1, str);
    fontcolor = color;
    print8(x, y, str);
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108990_selmenu2);

/* selmenu func_80108AB4_selmenu */
void func_80108A04_selmenu2(void) {
    s32 i;

    GW_PLAYER *src;
    GW_PLAYER *dst;

    for (i = 0; i < 4; i++) {
        src = &D_80109B20_selmenu2[i];
        dst = &GwPlayer[i];
        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

/* selmenu func_80108B1C_selmenu */
void func_80108A6C_selmenu2(void) {
    u8 group[4];
    u8 used[4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        group[i] = D_80109B20_selmenu2[i].group;
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        do {
            j = rand8() & 3;
        } while (used[j] == 1);
        used[j] = 1;
        D_80109B20_selmenu2[i].group = group[j];
    }
}

/* selmenu func_80108BE8_selmenu */
void func_80108B38_selmenu2(void) {
    u8 used[4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        do {
            j = rand8() & 3;
        } while (used[j] == 1);
        used[j] = 1;
        D_80109B20_selmenu2[i].pad = j;
    }
}
