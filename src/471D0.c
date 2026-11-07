#include "common.h"

/* Debug light editor (func_80046600_main .. func_80046728_main), from MP2 src/74AA0.c
   func_80075560_76160 .. func_80075688_76288. MP3 keeps the two window ids as s16s at work+0 and work+8
   (MP2: work+0 and work+2). */

/* hmflight.c's UnkLightData as the light editor reads it: unsigned colours, 1-based lights */
typedef struct LightEditEntry {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 stat;
    /* 0x04 */ s8 x;
    /* 0x05 */ s8 y;
    /* 0x06 */ s8 z;
} LightEditEntry; /* size 7 */

typedef struct LightEditSet {
    /* 0x00 */ s16 count;
    /* 0x02 */ LightEditEntry light[8];
} LightEditSet;

/* printfunc.c's Unk_D_800CC440 */
typedef struct PfWin {
    /* 0x00 */ u16 activeBool;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 xPosStart;
    /* 0x08 */ s32 yPosStart;
    /* 0x0C */ s32 width;
    /* 0x10 */ s32 height;
    /* 0x14 */ u32 rgba;
} PfWin; /* size 0x18 */

#define LIGHTEDIT_WIN(obj) ((s16 *)(obj)->work)

extern s8 D_800B23B0_main;
extern omObjData *D_800A1660_main;
extern s16 D_800A1664_main;
extern s16 D_800A1666_main;
extern u8 D_800A1668_main;
extern u8 D_800A1669_main;
extern s8 D_800A166A_main;
extern char *D_800A166C_main[2];
extern s16 D_800A1674_main[6];
extern s16 D_800A1680_main[6];
extern s16 D_800A168C_main[6];
extern s16 D_800A1698_main[6];
extern LightEditSet *D_800CE1D4_main;
extern PfWin D_800CC440_main[4];
extern s32 fontcolor;
extern u16 D_800D1244_main[4];

s16 func_8004DE24_main(s32, s32, s32, s32, s32);
void func_8004DEC8_main(s16);
void HmfLightStatSet(s16, u8, u8);
int sprintf(char *s, const char *fmt, ...);
void func_80046728_main(omObjData *);

s32 func_800465D0_main(void) {
    return D_800B23B0_main;
}

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465DC_main);

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465E8_main);

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465F4_main);

void func_80046600_main(void) {
    omObjData* obj;

    D_800A1660_main = omAddObj(0x7FD0, 0, 0, -1, func_80046728_main);
    omSetStatBit(D_800A1660_main, 0xA0);
    obj = D_800A1660_main;
    LIGHTEDIT_WIN(obj)[0] = func_8004DE24_main(14, 14, 0x132, 0x22, 0xDF70);
    LIGHTEDIT_WIN(obj)[4] =
        func_8004DE24_main(D_800A1674_main[D_800A1666_main], D_800A1680_main[D_800A1666_main],
                    D_800A168C_main[D_800A1666_main], D_800A1698_main[D_800A1666_main], (D_800A1668_main << 24) | 0x80);
    D_800A1669_main = 0;
}

void func_800466D8_main(void) {
    omObjData* obj = D_800A1660_main;

    if (obj != NULL) {
        func_8004DEC8_main(LIGHTEDIT_WIN(obj)[0]);
        func_8004DEC8_main(LIGHTEDIT_WIN(obj)[4]);
        omDelObj(D_800A1660_main);
        D_800A1660_main = NULL;
    }
}

const char D_800A7A38_main[] = "LIGHT%1d DIR%4d,%4d,%4d  STAT %s";
const char D_800A7A5C_main[] = "COLOR    RED %3d GREEN %3d BLUE %3d";
/* The light editor's frame: A on STAT (cursor 1) toggles the stick mode, which turns the light's
   direction; otherwise the cursor (3 x 2 cells) picks LIGHT / STAT / R / G / B and up/down change them. */
void func_80046728_main(omObjData* object) {
    s16* panel;
    s16* cursor;
    char* stat;
    s16 col;
    s16 row;
    u16 btn;
    f32 x;
    f32 y;
    f32 z;
    f32 yaw;
    f32 pitch;
    f32 sinPitch;
    f32 cosPitch;
    f32 sinYaw;
    f32 cosYaw;

    panel = &LIGHTEDIT_WIN(D_800A1660_main)[0];
    cursor = &LIGHTEDIT_WIN(D_800A1660_main)[4];
    stat = D_800A166C_main[(D_800CE1D4_main->light[D_800A1664_main].stat ^ 1) & 1];
    fontcolor = 14;
    sprintf(D_800D5218_main, D_800A7A38_main, D_800A1664_main, D_800CE1D4_main->light[D_800A1664_main].x, D_800CE1D4_main->light[D_800A1664_main].y, D_800CE1D4_main->light[D_800A1664_main].z, stat);
    print8(16, 16, D_800D5218_main);
    sprintf(D_800D5218_main, D_800A7A5C_main, D_800CE1D4_main->light[D_800A1664_main].r, D_800CE1D4_main->light[D_800A1664_main].g, D_800CE1D4_main->light[D_800A1664_main].b);
    print8(16, 24, D_800D5218_main);
    switch (D_800A1669_main) {
        case 0:
            if ((D_800D5558_main[0] & 0x8000) && D_800A1666_main == 1) {
                D_800CC440_main[*panel].rgba = 0x7070;
                D_800A1668_main = 0xF0;
                D_800A166A_main = -4;
                D_800A1669_main = 1;
                break;
            }
            D_800A1668_main += D_800A166A_main;
            if (D_800A166A_main < 0) {
                if (D_800A1668_main <= 0x80) {
                    D_800A166A_main = 4;
                }
            } else if (D_800A1668_main >= 0xF0) {
                D_800A166A_main = -4;
            }
            btn = D_800D0590_main[0];
            row = D_800A1666_main / 3;
            col = D_800A1666_main % 3;
            if (btn & 0x200) {
                if (col == 0) {
                    D_800A1666_main = row * 3 + 2;
                } else {
                    D_800A1666_main--;
                }
            } else if (btn & 0x100) {
                if (col == 2) {
                    D_800A1666_main = row * 3;
                } else {
                    D_800A1666_main++;
                }
            } else if (btn & 0x800) {
                if (row == 0) {
                    D_800A1666_main = col + 3;
                } else {
                    D_800A1666_main -= 3;
                }
            } else if (btn & 0x400) {
                if (row == 1) {
                    D_800A1666_main = col;
                } else {
                    D_800A1666_main += 3;
                }
            }
            switch (D_800A1666_main) {
                case 0:
                    if ((D_800D1244_main[0] & 4) && D_800A1664_main >= 2) {
                        D_800A1664_main--;
                    }
                    if ((D_800D1244_main[0] & 8) && D_800A1664_main < D_800CE1D4_main->count) {
                        D_800A1664_main++;
                    }
                    break;
                case 2:
                    if (D_800D1244_main[0] & 0x800C) {
                        if (D_800CE1D4_main->light[D_800A1664_main].stat & 1) {
                            HmfLightStatSet(D_800A1664_main, 1, 0);
                        } else {
                            HmfLightStatSet(D_800A1664_main, 1, 1);
                        }
                    }
                    break;
                case 3:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->light[D_800A1664_main].r--;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->light[D_800A1664_main].r++;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->light[D_800A1664_main].r -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->light[D_800A1664_main].r += 5;
                    }
                    break;
                case 4:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->light[D_800A1664_main].g--;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->light[D_800A1664_main].g++;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->light[D_800A1664_main].g -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->light[D_800A1664_main].g += 5;
                    }
                    break;
                case 5:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->light[D_800A1664_main].b--;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->light[D_800A1664_main].b++;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->light[D_800A1664_main].b -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->light[D_800A1664_main].b += 5;
                    }
                    break;
            }
            break;
        case 1:
            if (D_800D5558_main[0] & 0xC000) {
                D_800A1669_main = 0;
                D_800CC440_main[*panel].rgba = 0xDF70;
            }
            x = D_800CE1D4_main->light[D_800A1664_main].x;
            y = D_800CE1D4_main->light[D_800A1664_main].y;
            z = D_800CE1D4_main->light[D_800A1664_main].z;
            yaw = -D_800CBB6E_main[0] / 10;
            if (yaw >= 360.0f) {
                yaw -= 360.0f;
            } else if (yaw < 0.0f) {
                yaw += 360.0f;
            }
            pitch = -D_800D20A1_main[0] / 10;
            if (pitch >= 360.0f) {
                pitch -= 360.0f;
            } else if (pitch < 0.0f) {
                pitch += 360.0f;
            }
            sinPitch = sindf(pitch);
            cosPitch = cosdf(pitch);
            sinYaw = sindf(yaw);
            cosYaw = cosdf(yaw);
            x = x * cosYaw - z * sinYaw;
            y = x * sinPitch * sinYaw + y * cosPitch + z * sinPitch * cosYaw;
            z = x * cosPitch * sinYaw - y * sinPitch + z * cosPitch * cosYaw;
            HmfLightDirSet(D_800A1664_main, x, y, z);
            break;
    }
    D_800CC440_main[*cursor].rgba = (D_800A1668_main << 24) | 0x80;
    D_800CC440_main[*cursor].xPosStart = D_800A1674_main[D_800A1666_main];
    D_800CC440_main[*cursor].yPosStart = D_800A1680_main[D_800A1666_main];
    D_800CC440_main[*cursor].width = D_800A168C_main[D_800A1666_main];
    D_800CC440_main[*cursor].height = D_800A1698_main[D_800A1666_main];
}
