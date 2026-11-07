/* include/game/window.h has only a partial TextWindow; this unit uses the full one below, so
   the header's struct and its D_800CC69C_main declaration are renamed out of the way. Some
   functions.us.h prototypes disagree with the code (see the list) and are renamed likewise. */
#define TextWindow TextWindow_window_h
#define D_800CC69C_main D_800CC69C_main_window_h
#define func_8005B63C_main func_8005B63C_main_functions_us_h
#define func_8005E1D8_main func_8005E1D8_main_functions_us_h
#define func_8005F698_main func_8005F698_main_functions_us_h
#define func_8005F744_main func_8005F744_main_functions_us_h
#define func_8005FBA4_main func_8005FBA4_main_functions_us_h
#define func_8005B68C_main func_8005B68C_main_functions_us_h
#define func_8005E0C0_main func_8005E0C0_main_functions_us_h
#define func_8005BB18_main func_8005BB18_main_functions_us_h
#define func_8005C154_main func_8005C154_main_functions_us_h
#define func_8005D2D4_main func_8005D2D4_main_functions_us_h
#define func_80060EA8_main func_80060EA8_main_functions_us_h
#define func_800610E0_main func_800610E0_main_functions_us_h
#define func_8005FE54_main func_8005FE54_main_functions_us_h
#define func_8006010C_main func_8006010C_main_functions_us_h
#define func_8005B43C_main func_8005B43C_main_window_h
#define func_8005BDFC_main func_8005BDFC_main_window_h
#define func_8005BE30_main func_8005BE30_main_window_h
#define func_8005C02C_main func_8005C02C_main_window_h
#define func_8005C060_main func_8005C060_main_window_h
#define func_8005E1A8_main func_8005E1A8_main_window_h
#define func_8005F364_main func_8005F364_main_window_h
#define func_8005FFA8_main func_8005FFA8_main_window_h
#define func_80060394_main func_80060394_main_window_h
#define func_800605A4_main func_800605A4_main_window_h
#define func_8005B7B8_main func_8005B7B8_main_window_h
#include "game/window.h"
#include "game/sprite.h"
#include "common.h"
#include "malloc.h"
#include "mallocblock.h"
#include "stdarg.h"
#undef TextWindow
#undef D_800CC69C_main
#undef func_8005B63C_main
#undef func_8005E1D8_main
#undef func_8005F698_main
#undef func_8005F744_main
#undef func_8005FBA4_main
#undef func_8005B68C_main
#undef func_8005E0C0_main
#undef func_8005BB18_main
#undef func_8005C154_main
#undef func_8005D2D4_main
#undef func_80060EA8_main
#undef func_800610E0_main
#undef func_8005FE54_main
#undef func_8006010C_main
#undef func_8005B43C_main
#undef func_8005BDFC_main
#undef func_8005BE30_main
#undef func_8005C02C_main
#undef func_8005C060_main
#undef func_8005E1A8_main
#undef func_8005F364_main
#undef func_8005FFA8_main
#undef func_80060394_main
#undef func_800605A4_main
#undef func_8005B7B8_main

/* Text windows, from MP2 src/84FF0.c (MP1 src/6D4E0.c). */

/* a choice entry or a placed sprite (MP1 SubTextWindow) */
typedef struct TWEntry {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ char unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
} TWEntry; // size 0x10

typedef struct TextWindow {
    /* 0x000 */ u16 unk_00[0x10]; /* palette (RGBA5551) */
    /* 0x020 */ u8 unk20;
    /* 0x021 */ u8 unk21; /* controller ports that drive the window */
    /* 0x022 */ u8 unk22; /* text colour */
    /* 0x023 */ s8 unk23;
    /* 0x024 */ u8 unk24; /* current unkE0 buffer */
    /* 0x025 */ u8 unk25;
    /* 0x026 */ u8 unk26;
    /* 0x027 */ u8 unk27;
    /* 0x028 */ u8 unk28;
    /* 0x029 */ u8 unk29;
    /* 0x02A */ u8 unk2A; /* line spacing */
    /* 0x02B */ char pad2B[2];
    /* 0x02D */ u8 unk_2D;
    /* 0x02E */ u8 unk_2E;
    /* 0x02F */ u8 unk_2F;
    /* 0x030 */ s8 unk_30;
    /* 0x031 */ s8 unk_31;
    /* 0x032 */ s8 unk32;
    /* 0x033 */ s8 unk33;
    /* 0x034 */ u8 unk34; /* character spacing */
    /* 0x035 */ u8 unk35; /* tab width */
    /* 0x036 */ char pad36[2];
    /* 0x038 */ u32 unk_38;
    /* 0x03C */ u16 unk3C; /* x */
    /* 0x03E */ u16 unk3E; /* y */
    /* 0x040 */ s16 unk40; /* width */
    /* 0x042 */ s16 unk42; /* height */
    /* 0x044 */ s16 unk44;
    /* 0x046 */ s16 unk46;
    /* 0x048 */ u16 unk48;
    /* 0x04A */ u16 unk4A;
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ s16 unk4E;
    /* 0x050 */ s16 unk50;
    /* 0x052 */ s16 unk52;
    /* 0x054 */ s16 unk54;
    /* 0x056 */ s16 unk56;
    /* 0x058 */ s16 unk58;
    /* 0x05A */ s16 unk5A;
    /* 0x05C */ s16 unk5C;
    /* 0x05E */ s16 unk5E; /* -1 = free */
    /* 0x060 */ u16 unk60; /* sprite priority */
    /* 0x062 */ s16 unk62; /* previous window in the list */
    /* 0x064 */ s16 unk64; /* next window in the list */
    /* 0x066 */ s16 unk66;
    /* 0x068 */ s16 unk68;
    /* 0x06A */ s16 unk6A;
    /* 0x06C */ s16 unk_6C; /* sprite group */
    /* 0x06E */ s16 unk_6E[0x16];
    /* 0x09A */ s16 unk9A;
    /* 0x09C */ s16 unk9C;
    /* 0x09E */ s16 unk9E;
    /* 0x0A0 */ s16 unkA0;
    /* 0x0A2 */ s16 unkA2;
    /* 0x0A4 */ s16 unkA4;
    /* 0x0A6 */ u16 unkA6; /* buttons that also close the window */
    /* 0x0A8 */ u16 unkA8; /* buttons that closed it */
    /* 0x0AA */ s16 unkAA;
    /* 0x0AC */ s8 unkAC;
    /* 0x0AD */ s8 usingStringIDBool[5];
    /* 0x0B2 */ s8 unk_B2[6];
    /* 0x0B8 */ void* unk_B8[5];
    /* 0x0CC */ u8* unkCC; /* text being shown */
    /* 0x0D0 */ void* unkD0; /* text read from the message file, or NULL */
    /* 0x0D4 */ u8 unkD4; /* unkD0 must be freed */
    /* 0x0D5 */ char padD5[3];
    /* 0x0D8 */ u8* unkD8; /* where the text resumes after an inserted string */
    /* 0x0DC */ u8* unkDC; /* window image (4-bit) */
    /* 0x0E0 */ u8* unkE0[3]; /* triple-buffered text image (4-bit) */
    /* 0x0EC */ f32 unkEC;
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ TWEntry unk_F4[0x18];
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ char pad278[4];
} TextWindow; // size 0x27C

typedef struct TWInput {
    /* 0x00 */ s16 v[4];
    /* 0x08 */ s16 count;
} TWInput; // size 0xA

typedef struct TWColor {
    u8 r, g, b;
} TWColor;

typedef struct TWIcon {
    /* 0x00 */ s32 file2; /* used when the window flag 0x2000 is set */
    /* 0x04 */ s32 file;
    /* 0x08 */ u8 anim;
    /* 0x09 */ u8 width;
} TWIcon; // size 0xC

extern TWInput D_800CDA88_main[32];
extern TWInput D_800CDA8A_main[]; /* labels for the fields of D_800CDA88_main[0] */
extern TWInput D_800CDA8C_main[];
extern TWInput D_800CDA8E_main[];
extern TWInput D_800CDA90_main[];
extern s32 D_800D209C_main; /* last advance */
extern u8 D_800A2194_main[256]; /* character widths */
extern TWIcon D_800A2294_main[22];
extern TWColor D_800A2154_main[10];
extern u8 D_800A2174_main[0x14]; /* a window template (bcopy of 0x20 bytes) */

void func_8005A6B0_main(void);
s16 func_8005A968_main(s16 x, s16 y, s16 w, s16 h, s32 arg4, s16 flags);
void func_8005B040_main(u8* mask, s16 w, s16 h); /* window corner masks */
void func_8005B238_main(u8* mask, s16 w, s16 h);
void func_8005B43C_main(s16 win_id, void* str, s16 x, s16 y);
s16 func_8005B5EC_main(u8* str);
s16 func_8005B614_main(u8* str);
void func_8005B63C_main(s16 winId, s32 mask, s32 bits);
u32 func_8005B68C_main(s16 winId);
void func_8005B6BC_main(s16 win_id, u32 arg1, s8 arg2);
s16 func_8005B7B8_main(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, s16 arg4);
void func_8005B8F8_main(s16 arg0, s16 arg1);
s16 func_8005B974_main(s16 winId, u32 file, s16 x, s16 y, s16 arg4);
TextWindow* func_8005BA28_main(s16 arg0);
s16 func_8005BA54_main(s16 winId, s16 idx);
void func_8005BA90_main(s16 winId, s16 arg1, s16 arg2);
void func_8005BB18_main(s16 winId, f32 sx, f32 sy);
void func_8005BBC0_main(s16 winId, f32 sx, f32 sy);
void func_8005BCA4_main(s16 winId, s16 x, s16 y);
void func_8005BDA8_main(s16 winId, f32 arg1);
void func_8005BDFC_main(s16 winId, s8 arg1);
void func_8005BE30_main(s16 winId, s16 prio);
void func_8005BEE0_main(s16 winId, s16 arg1);
void func_8005BF70_main(s16 winId, s32 alpha);
void func_8005C02C_main(s16 winId, u8 arg1);
void func_8005C060_main(s16 winId, u8 idx, u8 r, u8 g, u8 b);
void func_8005C154_main(s16 winId, u8 r, u8 g, u8 b);
s32 func_8005CC18_main(TextWindow* tw);
s32 func_8005CC3C_main(TextWindow* tw, s16 w);
s32 func_8005CCF0_main(TextWindow* tw);
s32 func_8005CD38_main(TextWindow* tw);
void func_8005CD84_main(TextWindow* tw);
void func_8005CE10_main(TextWindow* tw);
void func_8005CEB0_main(s16 winId);
void func_8005CF94_main(s16 winId);
s16 func_8005CFE0_main(s16 winId, s16 idx);
void func_8005D294_main(s16 win_id);
void func_8005D2D4_main(s16 winId);
void func_8005D83C_main(s16 winId, s16 x, s16 y, s16 w, s16 h);
u8* func_8005DAA4_main(s16 winId);
void func_8005DC94_main(s16 winId);
void func_8005DD14_main(s16 win_id);
void func_8005DD54_main(TextWindow* tw);
s16 func_8005E0C0_main(s16 winId);
void func_8005E1A8_main(s16 winId, u8 tab);
s32 func_8005E1D8_main(s16 winId, s8 start, s32 arg2);
s32 func_8005E348_main(s16 winId);
void func_8005EEE4_main(TextWindow* tw, TWEntry* e);
void func_8005F364_main(s16 winId);
void func_8005F524_main(void);
void func_8005F698_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4);
void func_8005F744_main(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8005F784_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_8005F7F4_main(s16* arg0);
s16 func_8005F918_main(TextWindow* tw);
u8 func_8005FA90_main(u8 *arg0);
void func_8005FBA4_main(u8* arg0, u8* arg1);
void func_8005FE54_main(s16 winId, s16 ports);
void func_8005FE90_main(s16 winId);
void func_8005FFA8_main(s16 winId);
void func_800600C0_main(s16 winId, s32 arg1);
void func_8006010C_main(s32 arg0, s16 arg1);
void func_80060144_main(s16 obj);
s16 func_8006014C_main(s32 winId);
void func_80060174_main(u8* arg0, u8* arg1);
void func_800601BC_main(s16 winId, void* str, s8 idx);
void func_8006022C_main(u32 str, s16 index);
void func_80060290_main(u8* str, s16 idx);
void func_8006034C_main(s16 winId, s16 idx, s8 color);
void func_80060388_main(s8 arg0);
void func_80060394_main(s16 count, s16* out, ...);
void func_800604A8_main(s16 *arg0, s16 arg1, s16 arg2);
void func_800605A4_main(u8* str);
void func_80060848_main();
void func_80060858_main(s32 winId, u16 btn);
void func_80060EA8_main(s32 winId, s32 sound);
void func_800610E0_main(s16 arg0);
s32 func_80061188_main(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5);
void func_80061934_main(s16 winId, s16 arg1);
void func_80061A5C_main(s16 arg0, s16 arg1);


extern TextWindow *D_800CC69C_main;
extern u8 D_800A2150_main;
extern u8 gLanguageIndex;
extern u8 D_800A232C_main[];
extern u8 *D_800A2344_main[];
extern s16 D_800BDA50_main[12];
extern s8 D_800BDA6D_main;
extern s16 D_800BDA68_main;
extern s8 D_800CD2A4_main;
extern void *D_800CE2C4_main;
extern Process *D_800D040C_main;
extern u8 D_800D1F34_main;
extern void *D_800D1FE4_main;
extern void *D_800D4084_main;
extern u8 D_800D5206_main[5];
extern s8 D_800D5540_main;
extern u8 D_800D6A26_main;
extern s16 D_800D6B62_main;
extern s32 D_800A25D0_main[];
extern s8 D_800BDA6A_main;
extern u16 D_800BDA6C_main;
extern u16 D_800BDA6E_main;
extern u8 D_800D5206_main[5];
extern s8 D_800D5540_main;

s16 func_8005BA54_main(s16, s16);
void func_8005BB18_main(s16, f32, f32);
void func_800615B8_main(s16, s32);

void func_8005A6B0_main(void) {
    Process *temp_v0_4;
    void *temp_v0_6;
    s16 i;

    if (D_800A2150_main == 0) {
        D_800CC69C_main = HuMemMemoryAllocTemp(sizeof(TextWindow) * WINDOWS_MAX);

        for (i = 0; i < WINDOWS_MAX; i++) {
            D_800CC69C_main[i].unk5E = -1;
        }

        D_800CC69C_main[0].unk62 = -1;
        D_800CC69C_main[0].unk64 = 1;
        D_800CC69C_main[0].unk5E = 0;
        D_800CC69C_main[1].unk62 = 0;
        D_800CC69C_main[1].unk64 = -1;
        D_800CC69C_main[1].unk5E = -0x218;
        D_800D6A26_main = 0;
        D_800D1F34_main = 0;
        D_800D6B62_main = 0x2710;
        gLanguageIndex = GwCommon.languageIndex;

        if (gLanguageIndex >= LANGUAGE_MAX || gLanguageIndex == LANGUAGE_NONE) {
            gLanguageIndex = LANGUAGE_ENGLISH;
        }
        if (gLanguageIndex == LANGUAGE_JAPANESE) {
            D_800D1FE4_main = DataReadTemp(0x0000002B);
            func_80036414_main((u32)strings_japanese_ROM_START);
        } else {
            D_800D1FE4_main = DataReadTemp(0x0000002C);
            switch (gLanguageIndex) {
                case LANGUAGE_ENGLISH:
                    func_80036414_main((u32)strings_english_ROM_START);
                    break;
                case LANGUAGE_FRENCH:
                    func_80036414_main((u32)strings_french_ROM_START);
                    break;
                case LANGUAGE_GERMAN:
                    func_80036414_main((u32)strings_german_ROM_START);
                    break;
                case LANGUAGE_SPANISH:
                    func_80036414_main((u32)strings_spanish_ROM_START);
                    break;
                case LANGUAGE_ITALIAN:
                    func_80036414_main((u32)strings_italian_ROM_START);
                    break;
            }
        }

        temp_v0_4 = omAddPrcObj(func_8005DDDC_main, 0x1001, 0x800, 0);
        D_800D040C_main = temp_v0_4;
        omPrcSetStatBit(temp_v0_4, 0xA0);

        D_800A2150_main = 1;
        D_800CB99C_main = 0;
        D_800D4084_main = DataReadTemp(0x00000029);
        D_800CE2C4_main = DataReadTemp(0x0000002A);

        for (i = 0; i < ARRAY_COUNT(D_800BDA50_main); i++) {
            D_800BDA50_main[i] = -1;
        }

        temp_v0_6 = DataRead(0x00000033);
        D_800BDA68_main = func_80055810_main(temp_v0_6);
        DataClose(temp_v0_6);

        for (i = 0; i < ARRAY_COUNT(D_800D5206_main); i++) {
            D_800D5206_main[i] = 0;
        }

        D_800D5540_main = 0xC;
        D_800CD2A4_main = 0;
    }
}

// register allocation (masked 15): retail keeps (s16)w, (s16)h in s6/s5 from the HuMemFree call
// on and reuses them for func_8005B238_main; declaration order does not change it. MP3 has 16
// windows, other default colours and timer, and two corner-mask styles (flag 0x10)
#ifdef NON_MATCHING
/* MP1 func_8006D010: opens a window, returns its id or -1 */
s16 func_8005A968_main(s16 x, s16 y, s16 w, s16 h, s32 arg4, s16 flags) {
    TextWindow* tw;
    HuSprite* spr;
    s16 id;
    s16 i;
    s16 grp;
    s32 size;

    for (id = 2; id < WINDOWS_MAX; id++) {
        if (D_800CC69C_main[id].unk5E == -1) {
            break;
        }
    }
    if (id == WINDOWS_MAX) {
        return -1;
    }
    if (w & 1) {
        w++;
    }
    tw = &D_800CC69C_main[id];
    tw->unk64 = 1;
    tw->unk62 = D_800CC69C_main[1].unk62;
    tw->unk5E = 0x7D00;
    D_800CC69C_main[D_800CC69C_main[1].unk62].unk64 = id;
    D_800CC69C_main[1].unk62 = id;
    tw->unk40 = w;
    tw->unk42 = h;
    if (flags & 2) {
        tw->unk3C = (320 - w) / 2;
        tw->unk3E = (240 - h) / 2;
    } else if (!(flags & 4)) {
        if (x + w > 0x128) {
            tw->unk3C = 0x128 - w;
        } else {
            tw->unk3C = x;
        }
        if (y + h > 0xE0) {
            tw->unk3E = 0xE0 - h;
        } else {
            tw->unk3E = y;
        }
    } else {
        tw->unk3C = x;
        tw->unk3E = y;
    }
    tw->unk44 = (w + 0xF) & 0xFFF0;
    tw->unk46 = h + 0x10;
    tw->unkEC = tw->unkF0 = 1.0f;
    tw->unk4C = tw->unk4E = tw->unk54 = tw->unk56 = 4;
    tw->unk50 = w - 8;
    tw->unk52 = h - 8;
    tw->unk20 = 0;
    tw->unk23 = tw->unk22 = 7;
    tw->unk33 = 0;
    tw->unk25 = tw->unk26 = 1;
    tw->unk27 = 10;
    tw->unk28 = 12;
    tw->unk29 = 0;
    tw->unk2A = 2;
    tw->unk58 = tw->unk40 - tw->unk27 - 4;
    tw->unk5A = tw->unk42 - tw->unk28;
    tw->unk48 = tw->unk4A = 0;
    tw->unk_2D = D_800A2154_main[0].r;
    tw->unk_2E = D_800A2154_main[0].g;
    tw->unk_2F = D_800A2154_main[0].b;
    tw->unk21 = 0xF;
    tw->unk32 = 0;
    tw->unk_31 = 0;
    tw->unk_38 = 0;
    tw->unkD0 = NULL;
    tw->unkA6 = 0;
    tw->unkAC = -1;
    tw->unk35 = 0xC;
    for (i = 0; i < 5; i++) {
        tw->unk_B8[i] = NULL;
        tw->unk_B2[i] = -1;
    }
    tw->unkE0[0] = NULL;
    tw->unk6A = -1;
    tw->unk24 = 0;
    for (i = 0; i < 0x16; i++) {
        tw->unk_6E[i] = (i >= 3) ? -1 : 0;
    }
    tw->unk9A = 0;
    tw->unk66 = func_80055810_main(D_800D4084_main);
    tw->unk68 = func_80055810_main(D_800CE2C4_main);
    tw->unk_6C = grp = HuSprGrpCreate(0x16, 5);
    func_80055458_main(grp, 0, 0x100);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x01009000);
    func_80055024_main(grp, 0, tw->unk66, 0);
    func_800550F4_main(grp, 0, 0);
    func_800554C4_main(grp, 0, -1);
    func_80054904_main(grp, 0, tw->unk3C, tw->unk3E);
    func_80055420_main(tw->unk_6C, 0, 0x40, 0x20, 0xB0);
    spr = HuSprGet(grp, 0);
    if (!(flags & 8)) {
        spr->unk_84->unk00->unk04 = w;
        spr->unk_84->unk00->unk06 = h;
        HuMemFree(spr->unk_84->unk00->unk00);
        size = (w * h) / 2;
        spr->unk_84->unk00->unk00 = tw->unkDC = HuMemAlloc(size);
        memset(tw->unkDC, 0xFF, size);
        if (!(flags & 1)) {
            if (flags & 0x10) {
                func_8005B238_main(tw->unkDC, w, h);
            } else {
                func_8005B040_main(tw->unkDC, w, h);
            }
        }
        func_80055458_main(grp, 0, 100);
        HuSprAttrReset(grp, 0, 0x8000);
    } else {
        func_80055458_main(grp, 0, 0);
        HuSprAttrSet(grp, 0, 0x8000);
    }
    func_800550F4_main(grp, 0, 0);
    func_80055458_main(grp, 1, 0x100);
    HuSprAttrReset(grp, 1, 0xFFFF);
    HuSprAttrSet(grp, 1, 0x01009000);
    func_80055024_main(grp, 1, tw->unk68, 0);
    func_800550F4_main(grp, 1, 0);
    func_80054904_main(grp, 1, 0, 0);
    func_800554C4_main(grp, 1, 0);
    bcopy(D_800A2174_main, tw, 0x20);
    for (i = 0; i < 0x16; i++) {
        HuSprPriSet(grp, i, D_800D6B62_main);
    }
    HuSprPriSet(grp, 2, D_800D6B62_main - 1);
    tw->unk60 = D_800D6B62_main;
    D_800D6B62_main -= 0x20;
    tw->unkAA = 0x138;
    return id;
}
#else
INCLUDE_ASM("asm/nonmatchings/window", func_8005A968_main);
#endif

INCLUDE_ASM("asm/nonmatchings/window", func_8005B040_main);

INCLUDE_ASM("asm/nonmatchings/window", func_8005B238_main);

/* MP1 LoadStringIntoWindow: sets the window's text (a message id, or a pointer above 0x80000000)
   and its position (-2 = centred). Host: the id/pointer test assumes N64 addresses. */
void func_8005B43C_main(s16 win_id, void* str, s16 x, s16 y) {
    TextWindow* tw = &D_800CC69C_main[win_id];
    s16 w;

    if (tw->unkD0 != NULL) {
        if (tw->unkD4 != 0) {
            func_800365E8_main(tw->unkD0);
        }
    }
    if (tw->unk20 == 2) {
        func_8005CF94_main(win_id);
    }
    tw->unk5C = 1;
    if ((u32)str > 0x80000000) {
        tw->unkD4 = 0;
        tw->unkCC = str;
    } else {
        tw->unkD4 = 1;
        tw->unkCC = tw->unkD0 = func_800364DC_main(str);
    }
    if (x >= 0) {
        tw->unk54 = x;
    } else if (x == -2) {
        if (tw->unk_38 & 0x40000) {
            func_80060848_main();
        }
        w = func_8005B614_main(tw->unkCC);
        D_800CD2A4_main = 0;
        tw->unk54 = (tw->unk40 - w) / 2;
        tw->unk_38 |= 0x800;
    }
    if (y >= 0) {
        tw->unk56 = y;
    } else if (y == -2) {
        tw->unk56 = (tw->unk42 - 12) / 2;
        tw->unk_38 |= 0x1000;
    }
    tw->unk20 = 1;
    tw->unk_30 = 0;
}

/* MP1 func_8006D93C: string length */
s16 func_8005B5EC_main(u8* str) {
    s16 len = 0;

    while (*str != 0) {
        str++;
        len++;
    }
    return len;
}

/* text width of str */
s16 func_8005B614_main(u8* str) {
    s16 size[2];

    func_80060394_main(1, size, str);
    return size[0];
}

/* clears the window flags in mask, then sets bits */
void func_8005B63C_main(s16 winId, s32 mask, s32 bits) {
    TextWindow* tw = &D_800CC69C_main[winId];

    tw->unk_38 = bits | (~mask & tw->unk_38);
    if (bits & 0x20) {
        tw->unkAA = 0;
    }
}

u32 func_8005B68C_main(s16 winId) {
    return D_800CC69C_main[winId].unk_38;
}

void func_8005B6BC_main(s16 win_id, u32 arg1, s8 arg2) {
    TextWindow *textWindow = &D_800CC69C_main[win_id];

    if (textWindow->unk_B8[arg2] != 0) {
        if (textWindow->usingStringIDBool[arg2] != 0) {
            func_800365E8_main(textWindow->unk_B8[arg2]);
        }
    }
    // pointer check
    if (0x80000000 < arg1) {
        textWindow->usingStringIDBool[arg2] = 0;
        textWindow->unk_B8[arg2] = (char *)arg1;
    } else {
        textWindow->usingStringIDBool[arg2] = 1;
        textWindow->unk_B8[arg2] = func_800364DC_main((void *)arg1);
    }
    textWindow->unk_B2[arg2] = -1;
}

s16 func_8005B7B8_main(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, s16 arg4) {
    TextWindow *window = &D_800CC69C_main[win_id];
    s16 spriteId;
    void *spriteBytes;
    s16 i;

    for (i = 4; i < 12; i++) {
        if (window->unk_6E[i] != -1) {
            continue;
        }
        break;
    }
    if (i >= 12) {
        return -1;
    }

    spriteBytes = DataRead(spriteMainFsPair);
    spriteId = func_80055810_main(spriteBytes);
    window->unk_6E[i] = spriteId;
    HuMemMemoryFreePerm(spriteBytes);
    func_80055024_main(window->unk_6C, i, spriteId, arg4);
    func_80054904_main(window->unk_6C, i, arg2, arg3);
    func_800554C4_main(window->unk_6C, i, 0);
    return i;
}

void func_8005B8F8_main(s16 arg0, s16 arg1) {
    HuSprKill(func_8005BA54_main(arg0, arg1));
    D_800CC69C_main[arg0].unk_6E[arg1] = -1;
}

/* MP1 func_8006DC7C: adds a sprite to the window and records it as a text entry */
s16 func_8005B974_main(s16 winId, u32 file, s16 x, s16 y, s16 arg4) {
    TextWindow* tw = &D_800CC69C_main[winId];
    TWEntry* e;
    s16 ret;

    ret = func_8005B7B8_main(winId, file, x, y, arg4);
    e = &tw->unk_F4[tw->unk_30];
    e->unk2 = x;
    e->unk4 = y;
    e->unk6 = 0;
    e->unk8 = 0;
    e->unk0 = 1;
    tw->unk_30++;
    return ret;
}

TextWindow* func_8005BA28_main(s16 arg0) {
    return &D_800CC69C_main[arg0];
}

s16 func_8005BA54_main(s16 winId, s16 idx) {
    TextWindow* tw = &D_800CC69C_main[winId];

    return tw->unk_6E[idx];
}

void func_8005BA90_main(s16 winId, s16 arg1, s16 arg2) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];

    func_80054904_main(window->unk_6C, 0, arg1, arg2);
    window->unk3C = arg1;
    window->unk3E = arg2;
}

/* MP1 func_8006DE20: window scale */
void func_8005BB18_main(s16 winId, f32 sx, f32 sy) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    tw->unkEC = sx;
    tw->unkF0 = sy;
    for (i = 0; i < 0x16; i++) {
        HuSprScaleSet(tw->unk_6C, i, sx, sy);
    }
}

/* func_8005BB18_main without the window's own sprites 4-11 */
void func_8005BBC0_main(s16 winId, f32 sx, f32 sy) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    tw->unkEC = sx;
    tw->unkF0 = sy;
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(tw->unk_6C, i, sx, sy);
    }
    for (i = 12; i < 0x16; i++) {
        HuSprScaleSet(tw->unk_6C, i, sx, sy);
    }
}

/* MP1 func_8006DEC8: sets the frame and cursor sprites' cel offsets */
void func_8005BCA4_main(s16 winId, s16 x, s16 y) {
    TextWindow* tw = &D_800CC69C_main[winId];
    HuSprite* spr;
    s16 i;

    tw->unk48 = x;
    tw->unk4A = y;
    spr = HuSprGet(tw->unk_6C, 0);
    spr->unk_84->unk00->unk08 = x;
    spr->unk_84->unk00->unk0A = y;
    spr = HuSprGet(tw->unk_6C, 1);
    for (i = 0; i < spr->unk_84->unk12; i++) {
        spr->unk_84->unk00[i].unk08 = x;
        spr->unk_84->unk00[i].unk0A = y;
    }
}

void func_8005BDA8_main(s16 winId, f32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    func_800552DC_main(window->unk_6C, 0, arg1);
}

void func_8005BDFC_main(s16 winId, s8 arg1) {
    TextWindow* tw = &D_800CC69C_main[winId];

    tw->unk25 = arg1;
    tw->unk26 = arg1;
}

/* MP1 func_8006E0A4: window sprite priority */
void func_8005BE30_main(s16 winId, s16 prio) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    tw->unk60 = prio;
    for (i = 0; i < 0x16; i++) {
        HuSprPriSet(tw->unk_6C, i, prio);
    }
    if (tw->unk6A != -1) {
        HuSprPriSet(tw->unk_6C, 2, prio - 1);
    }
}

void func_8005BEE0_main(s16 winId, s16 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];

    if (arg1 == 0) {
        HuSprAttrSet(window->unk_6C, 0, 0x8000);
    } else {
        HuSprAttrReset(window->unk_6C, 0, 0x8000);
    }
    func_80055458_main(window->unk_6C, 0, arg1 & 0xFFFF);
}

/* sets the alpha of the cursor and the added sprites */
void func_8005BF70_main(s16 winId, s32 alpha) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    func_80055458_main(tw->unk_6C, 1, alpha);
    for (i = 12; i < 0x16; i++) {
        if (tw->unk_6E[i] != -1) {
            func_80055458_main(tw->unk_6C, i, alpha);
        }
    }
}

void func_8005C02C_main(s16 winId, u8 arg1) {
    TextWindow* tw = &D_800CC69C_main[winId];

    tw->unk22 = arg1;
    tw->unk23 = arg1;
}

/* sets palette entry idx + 1 (RGBA5551) and gives the cursor sprite a fresh copy of the palette */
void func_8005C060_main(s16 winId, u8 idx, u8 r, u8 g, u8 b) {
    TextWindow* tw = &D_800CC69C_main[winId];
    HuSprite* spr = HuSprGet(tw->unk_6C, 1);
    void* pal;

    tw->unk_00[idx + 1] = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
    pal = HuMemAlloc(0x20);
    bcopy(tw, pal, 0x20);
    func_80019C00_main(spr->unk_84->unk0C);
    spr->unk_84->unk0C = pal;
}

void func_8005C154_main(s16 winId, u8 r, u8 g, u8 b) {
    func_8005C060_main(winId, 0, r, g, b);
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005C190_main);

/* MP1 func_8006E87C's caller: advances past one character */
s32 func_8005CC18_main(TextWindow* tw) {
    return func_8005CC3C_main(tw, tw->unk34 + tw->unk29);
}

/* MP1 func_8006E87C: advances the cursor by w (MP3: fixed 10-pixel cells under flag 0x80000); wraps the line when the next character does not fit */
s32 func_8005CC3C_main(TextWindow* tw, s16 w) {
    s32 cw;

    D_800D209C_main = w;
    tw->unk54 += w;
    if (gLanguageIndex == 1) {
        cw = tw->unk27;
    } else if (tw->unk_38 & 0x80000) {
        cw = 10;
    } else {
        cw = D_800A2194_main[*tw->unkCC];
    }
    if (cw + tw->unk54 > tw->unk4C + tw->unk50) {
        if (*tw->unkCC >= 0x20) {
            return func_8005CCF0_main(tw);
        }
    }
    return 1;
}

/* MP1 func_8006E93C: new line; 0 when the window is full */
s32 func_8005CCF0_main(TextWindow* tw) {
    tw->unk54 = tw->unk4C;
    tw->unk56 = tw->unk56 + (tw->unk28 + tw->unk2A);
    return (tw->unk56 + tw->unk28 > tw->unk4E + tw->unk52) ^ 1;
}

/* func_8005CCF0_main with a quarter-height line */
s32 func_8005CD38_main(TextWindow* tw) {
    tw->unk54 = tw->unk4C;
    tw->unk56 = tw->unk56 + ((tw->unk28 >> 2) + tw->unk2A);
    return (tw->unk56 + tw->unk28 > tw->unk4E + tw->unk52) ^ 1;
}

/* clears the window's text */
void func_8005CD84_main(TextWindow* tw) {
    u8* buf;

    func_8005DD54_main(tw);
    buf = func_8005DAA4_main(((u8*)tw - (u8*)D_800CC69C_main) / sizeof(TextWindow));
    if (tw->unkE0[0] != NULL) {
        memset(buf, 0, (tw->unk44 * tw->unk46) / 2);
    }
    func_8005CE10_main(tw);
}

/* resets the text cursor and removes the added sprites */
void func_8005CE10_main(TextWindow* tw) {
    s16 i;

    tw->unk54 = tw->unk4C;
    tw->unk56 = tw->unk4E;
    tw->unk_30 = 0;
    tw->unk9A = 0;
    for (i = 12; i < 0x16; i++) {
        if (tw->unk_6E[i] != -1) {
            HuSprAttrSet(tw->unk_6C, i, 0x8000);
            tw->unk_6E[i] = -1;
        }
    }
}

/* shows the "more text" cursor (sprite 3) at the end of the text */
void func_8005CEB0_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];

    func_80055024_main(tw->unk_6C, 3, D_800BDA68_main, 0);
    HuSprAttrReset(tw->unk_6C, 3, 0xFFFF);
    HuSprAttrSet(tw->unk_6C, 3, 0x01000000);
    HuSprPriSet(tw->unk_6C, 3, tw->unk60 - 1);
    func_80054904_main(tw->unk_6C, 3, tw->unk58 - tw->unk48, tw->unk5A - tw->unk4A);
    if (tw->unk_38 & 8) {
        HuSprAttrSet(tw->unk_6C, 3, 0x8000);
    }
}

void func_8005CF94_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];

    HuSprAttrSet(tw->unk_6C, 3, 0x8000);
}

/* places icon idx (a sprite, cached in D_800BDA50_main) at the text cursor; returns its width */
s16 func_8005CFE0_main(s16 winId, s16 idx) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 anim;
    s16 i;
    void* data;

    anim = D_800BDA50_main[idx];
    if (anim == -1) {
        if (tw->unk_38 & 0x2000) {
            data = DataRead(D_800A2294_main[idx].file2);
        } else {
            data = DataRead(D_800A2294_main[idx].file);
        }
        D_800BDA50_main[idx] = anim = func_80055810_main(data);
        HuMemMemoryFreePerm(data);
    }
    for (i = 12; i < 0x16; i++) {
        if (tw->unk_6E[i] == -1) {
            break;
        }
    }
    if (i >= 0x16) {
        return 0;
    }
    tw->unk_6E[i] = anim;
    HuSprAttrSet(tw->unk_6C, i, 0x1000);
    func_80055024_main(tw->unk_6C, i, anim, D_800A2294_main[idx].anim);
    func_80054904_main(tw->unk_6C, i, tw->unk54 - tw->unk48, tw->unk56 - tw->unk4A);
    func_800554C4_main(tw->unk_6C, i, 0);
    if (tw->unk22 == 0) {
        func_80055420_main(tw->unk_6C, i, 0, 0, 0);
    } else if (tw->unk_38 & 0x2000) {
        func_80055420_main(tw->unk_6C, i, 0x61, 0x61, 0xF8);
    } else {
        func_80055420_main(tw->unk_6C, i, 0x38, 0xF8, 0x25);
    }
    if (tw->unk_38 & 8) {
        HuSprAttrSet(tw->unk_6C, i, 0x8000);
    } else {
        HuSprAttrReset(tw->unk_6C, i, 0x8000);
    }
    return D_800A2294_main[idx].width;
}

void func_8005D294_main(s16 win_id) {
    func_8005CD84_main(&D_800CC69C_main[win_id]);
}

void func_8005D2D4_main(s16 winId) {
    func_8005B63C_main(winId, 0x40000, 0x40000);
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005D2FC_main);

INCLUDE_ASM("asm/nonmatchings/window", func_8005D30C_main);

/* MP1 func_8006F3BC: clears a w x h box of the text image */
void func_8005D83C_main(s16 winId, s16 x, s16 y, s16 w, s16 h) {
    TextWindow* tw = &D_800CC69C_main[winId];
    u8* dst;
    s16 row;
    s16 col;

    func_8005DD14_main(winId);
    y = (y < 0) ? 0 : y;
    x = (x < 0) ? 0 : x;
    if (tw->unkE0[0] != NULL) {
        dst = func_8005DAA4_main(winId) + (x + y * tw->unk44) / 2;
        if (x & 1) {
            for (row = 0; row < h; row++) {
                for (col = 0; col < w / 2; col++) {
                    dst[col] &= 0xF0;
                    dst[col + 1] &= 0xF;
                }
                dst += tw->unk44 / 2;
            }
        } else {
            for (row = 0; row < h; row++) {
                for (col = 0; col < w / 2; col++) {
                    dst[col] = 0;
                }
                dst += tw->unk44 / 2;
            }
        }
    }
}

/* MP1 func_8006F718: the current text image, allocating the three buffers on first use */
u8* func_8005DAA4_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 grp = tw->unk_6C;
    HuSprite* spr;
    s16 i;
    s16 w;
    s16 h;

    if (tw->unkE0[0] != NULL) {
        return HuSprGet(grp, 1)->unk_84->unk00[tw->unk24].unk00;
    }
    w = tw->unk44;
    h = tw->unk46;
    spr = HuSprGet(grp, 1);
    for (i = 0; i < 3; i++) {
        HuMemFree(spr->unk_84->unk00[i].unk00);
        spr->unk_84->unk00[i].unk04 = w;
        spr->unk_84->unk00[i].unk06 = tw->unk42;
        spr->unk_84->unk00[i].unk00 = tw->unkE0[i] = HuMemAlloc((w * h) / 2);
        memset(tw->unkE0[i], 0, (w * h) / 2);
    }
    HuMemFree(spr->unk_84->unk0C);
    spr->unk_84->unk0C = HuMemAlloc(0x20);
    bcopy(tw, spr->unk_84->unk0C, 0x20);
    if (!(tw->unk_38 & 8)) {
        HuSprAttrReset(grp, 1, 0x8000);
    }
    return spr->unk_84->unk00[tw->unk24].unk00;
}

/* shows the current text image and moves to the next buffer */
void func_8005DC94_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];

    func_80054FF8_main(tw->unk_6C, 1, tw->unk24);
    tw->unk24++;
    if (tw->unk24 >= 3) {
        tw->unk24 = 0;
    }
    tw->unk_38 &= ~0x100;
}

void func_8005DD14_main(s16 win_id) {
    func_8005DD54_main(&D_800CC69C_main[win_id]);
}

/* starts a new text image from a copy of the previous one (once per frame) */
void func_8005DD54_main(TextWindow* tw) {
    u8 prev = 2;

    if (tw->unk24 != 0) {
        prev = tw->unk24 - 1;
    }
    if (!(tw->unk_38 & 0x100)) {
        tw->unk_38 |= 0x100;
        if (tw->unkE0[0] != NULL) {
            bcopy(tw->unkE0[prev], tw->unkE0[tw->unk24], (tw->unk44 * tw->unk46) / 2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005DDDC_main);

/* MP1 func_8006FCC0: the window's state; for -1 the states of all windows or'ed */
s16 func_8005E0C0_main(s16 winId) {
    s16 state = 0;
    s16 i;

    if (winId != -1) {
        return D_800CC69C_main[winId].unk20;
    }
    i = D_800CC69C_main[0].unk64;
    while (D_800CC69C_main[i].unk64 != -1) {
        state |= D_800CC69C_main[i].unk20;
        i = D_800CC69C_main[i].unk64;
    }
    return state;
}

void func_8005E1A8_main(s16 winId, u8 tab) {
    D_800CC69C_main[winId].unk35 = tab;
}

/* MP1 func_8006FCF0: lets the player choose one of the window's entries; returns it, or -1 */
s32 func_8005E1D8_main(s16 winId, s8 start, s32 arg2) {
    TextWindow* tw = &D_800CC69C_main[winId];
    void* file;

    if (tw->unk_30 == 0) {
        return -1;
    }
    if (tw->unk6A == -1) {
        file = DataRead(0x30);
        tw->unk6A = func_80055810_main(file);
        HuMemMemoryFreePerm(file);
        func_80055024_main(tw->unk_6C, 2, tw->unk6A, 0);
        func_80055458_main(tw->unk_6C, 2, 0x100);
        HuSprAttrReset(tw->unk_6C, 2, 0xFFFF);
        HuSprAttrSet(tw->unk_6C, 2, 0x01009000);
        HuSprPriSet(tw->unk_6C, 2, tw->unk60 - 1);
    }
    if (arg2 != 0) {
        tw->unk_38 |= 1;
    }
    tw->unk_31 = start;
    tw->unk20 = 5;
    tw->unk9A = 1;
    tw->unkA4 = 0;
    while (func_8005E0C0_main(winId) == 5) {
        HuPrcVSleep();
    }
    return tw->unk_31;
}

// register allocation (one instruction short, the rest register renaming; MP1 func_8006FE4C and
// MP2 have the same residue): the new entry's index reuses the compare's sign extension of sel where
// retail re-extends it; an s32 sel is far worse. MP3 plays sound 0 when flag 0x20 is set. The (u16) on the unkA6 test lets btn
// go unextended as in retail (same result: unkA6 is a u16).
#ifdef NON_MATCHING
/* MP1 func_8006FE4C: moves the choice cursor between the entries; 0 once one is chosen or cancelled */
s32 func_8005E348_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];
    TWEntry* e;
    s16 cur;
    s16 sel;
    s16 dir;
    s16 x;
    s16 y;
    s16 count;
    s16 i;
    s16 best;
    s16 dy;
    s16 d2;
    s16 dx;
    s16 btn;
    s16 cancel;
    f32 d;
    f32 bestDx;
    f32 bestDy;

    sel = cur = tw->unk_31;
    dir = -1;
    if (tw->unk9A != 3) {
        btn = func_8005F918_main(tw);
    } else {
        btn = 0;
    }
    if (btn & 0x200) {
        dir = 0;
    }
    if (btn & 0x100) {
        dir = 2;
    }
    if (btn & 0x800) {
        dir = 1;
    }
    if (btn & 0x400) {
        dir = 3;
    }
    x = tw->unk_F4[cur].unk2;
    y = tw->unk_F4[cur].unk4;
    bestDx = 100000.0f;
    count = tw->unk_30;
    bestDy = bestDx;
    switch (dir) {
    case 0:
        for (i = 0; i < count; i++) {
            if (i != cur && tw->unk_F4[i].unk4 == y && tw->unk_F4[i].unk2 < x) {
                break;
            }
        }
        if (i != count) {
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == y && tw->unk_F4[i].unk2 < x) {
                    d = x - tw->unk_F4[i].unk2;
                    if (d < bestDy) {
                        bestDy = d;
                        sel = i;
                    }
                }
            }
        } else {
            best = -1000;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == y && tw->unk_F4[i].unk2 > best) {
                    best = tw->unk_F4[i].unk2;
                    sel = i;
                }
            }
        }
        break;
    case 1:
        for (i = 0; i < count; i++) {
            if (i != cur && tw->unk_F4[i].unk4 < y) {
                break;
            }
        }
        if (i != count) {
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 < y) {
                    dy = y - tw->unk_F4[i].unk4;
                    if (dy <= bestDy) {
                        if (dy < bestDy) {
                            bestDx = 100000.0f;
                        }
                        dx = x - tw->unk_F4[i].unk2;
                        d2 = dx * dx;
                        if (d2 < bestDx) {
                            bestDy = dy;
                            bestDx = d2;
                            sel = i;
                        }
                    }
                }
            }
        } else {
            best = -1000;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 > best) {
                    best = tw->unk_F4[i].unk4;
                }
            }
            bestDx = 100000.0f;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == best) {
                    dx = x - tw->unk_F4[i].unk2;
                    d2 = dx * dx;
                    if (d2 < bestDx) {
                        bestDx = d2;
                        sel = i;
                    }
                }
            }
        }
        break;
    case 2:
        for (i = 0; i < count; i++) {
            if (i != cur && tw->unk_F4[i].unk4 == y && x < tw->unk_F4[i].unk2) {
                break;
            }
        }
        if (i != count) {
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == y && x < tw->unk_F4[i].unk2) {
                    d = tw->unk_F4[i].unk2 - x;
                    if (d < bestDy) {
                        bestDy = d;
                        sel = i;
                    }
                }
            }
        } else {
            best = 1000;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == y && tw->unk_F4[i].unk2 < best) {
                    best = tw->unk_F4[i].unk2;
                    sel = i;
                }
            }
        }
        break;
    case 3:
        for (i = 0; i < count; i++) {
            if (i != cur && y < tw->unk_F4[i].unk4) {
                break;
            }
        }
        if (i != count) {
            for (i = 0; i < count; i++) {
                if (i != cur && y < tw->unk_F4[i].unk4) {
                    dy = tw->unk_F4[i].unk4 - y;
                    if (dy <= bestDy) {
                        if (dy < bestDy) {
                            bestDx = 100000.0f;
                        }
                        dx = x - tw->unk_F4[i].unk2;
                        d2 = dx * dx;
                        if (d2 < bestDx) {
                            bestDy = dy;
                            bestDx = d2;
                            sel = i;
                        }
                    }
                }
            }
        } else {
            best = 1000;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 < best) {
                    best = tw->unk_F4[i].unk4;
                }
            }
            bestDx = 100000.0f;
            for (i = 0; i < count; i++) {
                if (i != cur && tw->unk_F4[i].unk4 == best) {
                    dx = x - tw->unk_F4[i].unk2;
                    d2 = dx * dx;
                    if (d2 < bestDx) {
                        bestDx = d2;
                        sel = i;
                    }
                }
            }
        }
        break;
    }
    if (tw->unk_31 != sel) {
        e = &tw->unk_F4[tw->unk_31];
        tw->unk_31 = tw->unk32 = sel;
        tw->unk9A = 3;
        tw->unk9C = e->unk2 - 12;
        tw->unk9E = e->unk4 + 8;
        e = &tw->unk_F4[sel];
        tw->unkA0 = e->unk2 - 12;
        tw->unkA2 = e->unk4 + 8;
        tw->unkA4 = 0;
        if (tw->unk_38 & 0x20) {
            HuAudFXPlay(0);
        } else {
            HuAudFXPlay(1);
        }
    }
    cancel = (tw->unk_38 & 1) ? 0 : 0x4000;
    if (btn & 0x8000) {
        if (tw->unk_F4[tw->unk_31].unk0 == 2) {
            if (tw->unkAA != -1) {
                if (tw->unk_38 & 0x20) {
                    HuAudFXPlay(0);
                } else {
                    HuAudFXPlay(5);
                }
            }
            return 1;
        }
        tw->unk9A = 4;
        tw->unkA4 = 0;
        if (tw->unkAA != -1) {
            if (tw->unk_38 & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(3);
            }
        }
        tw->unk_38 |= 0x200;
        tw->unkA8 = btn;
        return 0;
    }
    if ((btn & cancel) || ((u16)btn & tw->unkA6)) {
        tw->unk9A = 0;
        tw->unkA4 = 0;
        tw->unk_31 = -1;
        if (btn & cancel) {
            if (tw->unkAA != -1) {
                if (tw->unk_38 & 0x20) {
                    HuAudFXPlay(0);
                } else {
                    HuAudFXPlay(4);
                }
            }
        }
        tw->unk_38 |= 0x200;
        tw->unkA8 = btn;
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/window", func_8005E348_main);
#endif

/* MP1 func_8007094C: animates and places the choice cursor (sprite 2) */
void func_8005EEE4_main(TextWindow* tw, TWEntry* e) {
    f32 sy;
    f32 px;
    f32 py;
    f32 sx;
    f32 dx;
    f32 dy;
    f32 len;
    f32 mx;
    f32 my;

    sx = sy = 1.0f;
    px = e->unk2 - 12;
    py = e->unk4 + 8;
    switch (tw->unk9A) {
        case 0:
            if (tw->unk6A != -1) {
                HuSprAttrSet(tw->unk_6C, 2, 0x8000);
            }
            return;
        case 1:
            if (!(tw->unk_38 & 0x8000)) {
                sx = sy = tw->unkA4 / 8.0f;
                if (++tw->unkA4 >= 8) {
                    tw->unkA4 = 0;
                    tw->unk9A = 2;
                }
            } else {
                tw->unkA4 = 0;
                tw->unk9A = 2;
            }
            break;
        case 3:
            tw->unkA4++;
            dx = tw->unkA0 - tw->unk9C;
            dy = tw->unkA2 - tw->unk9E;
            len = HuSqrtf(dx * dx + dy * dy);
            mx = dx / len * 10.0f * tw->unkA4;
            my = dy / len * 10.0f * tw->unkA4;
            dx = tw->unk9C + mx - tw->unkA0;
            dy = tw->unk9E + my - tw->unkA2;
            if (dx * dx + dy * dy < 100.0f) {
                px = tw->unkA0;
                py = tw->unkA2;
                tw->unkA4 = 0;
                tw->unk9A = 2;
            } else {
                px = tw->unk9C + mx;
                py = tw->unk9E + my;
            }
            break;
        case 2:
            tw->unkA4 = tw->unkA4 + 10.0f;
            if (tw->unkA4 >= 181) {
                tw->unkA4 = 0;
            }
            px += sindf(tw->unkA4) * 4.0f;
            break;
        case 4:
            if (tw->unk_38 & 0x8000) {
                sx = sy = 0.0f;
            } else if (tw->unkA4 >= 11) {
                sx = sy = 4.0f / 3.0f;
            } else {
                sx = sy = ++tw->unkA4 / 30.0f + 1.0f;
            }
            break;
        case 5:
            if (--tw->unkA4 == 0) {
                tw->unkA4 = 0;
                tw->unk9A = 2;
            }
            break;
    }
    if (sx == 0.0f || sy == 0.0f) {
        HuSprAttrSet(tw->unk_6C, 2, 0x8000);
        return;
    }
    dy = 0.8f;
    dx = sx * dy;
    HuSprScaleSet(tw->unk_6C, 2, dx * tw->unkEC, (dy = sy * dy) * tw->unkF0);
    dx = px / dx * tw->unkEC;
    func_80054904_main(tw->unk_6C, 2, dx, dy = py / dy * tw->unkF0);
    if (!(tw->unk_38 & 8)) {
        HuSprAttrReset(tw->unk_6C, 2, 0x8000);
    }
}

/* MP1 func_80070D90: closes a window */
void func_8005F364_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    if (tw->unkD0 != NULL && tw->unkD4 != 0) {
        func_800365E8_main(tw->unkD0);
    }
    for (i = 0; i < 5; i++) {
        if (tw->unk_B8[i] != NULL && tw->usingStringIDBool[i] != 0) {
            func_800365E8_main(tw->unk_B8[i]);
        }
    }
    HuSprGrpKill(tw->unk_6C);
    HuSprKill(tw->unk66);
    HuSprKill(tw->unk68);
    for (i = 4; i < 12; i++) {
        if (tw->unk_6E[i] != -1) {
            HuSprKill(func_8005BA54_main(winId, i));
        }
    }
    if (tw->unk6A != -1) {
        HuSprKill(tw->unk6A);
    }
    tw->unk5E = -1;
    D_800CC69C_main[tw->unk64].unk62 = tw->unk62;
    D_800CC69C_main[tw->unk62].unk64 = tw->unk64;
    D_800D6B62_main += 32;
}

// decomp-permuter
void func_8005F524_main(void)
{
  s16 id;
  if (D_800A2150_main != 0)
  {
    id = D_800CC69C_main[0].unk64;
    while (D_800CC69C_main[id].unk64 != (-1))
    {
      func_8005F364_main(id);
      id = D_800CC69C_main[id].unk64;
    }

    DataCloseTemp(D_800D1FE4_main);
    DataCloseTemp(D_800D4084_main);
    DataCloseTemp(D_800CE2C4_main);
    HuMemMemoryFreeTemp(D_800CC69C_main);
    omDelPrcObj(D_800D040C_main);
    D_800A2150_main = 0;
    for (id = 0; id < 12; id++)
    {
      if (D_800BDA50_main[id] != (-1))
      {
        HuSprKill(D_800BDA50_main[id]);
      }
    }

    HuSprKill(D_800BDA68_main);
  }
}

void func_8005F698_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4) {
    func_8005F784_main(-(~arg0 == 0), -(~arg1 == 0), -(~arg2 == 0), -(~arg3 == 0), arg4);
    func_8005F784_main(arg0, arg1, arg2, arg3, 1);
}

void func_8005F744_main(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8005F784_main(arg0, arg1, arg2, arg3, 1);
}

void func_8005F784_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    D_800CDA88_main[D_800D1F34_main].v[0] = arg0;
    D_800CDA8A_main[D_800D1F34_main].v[0] = arg1;
    D_800CDA8C_main[D_800D1F34_main].v[0] = arg2;
    D_800CDA8E_main[D_800D1F34_main].v[0] = arg3;
    D_800CDA90_main[D_800D1F34_main].v[0] = arg4;
    D_800D1F34_main = (D_800D1F34_main + 1) & 0x1F;
}

void func_8005F7F4_main(s16* arg0) {
    s16 i;

    if (D_800D6A26_main == D_800D1F34_main) {
        arg0[0] = arg0[1] = arg0[2] = arg0[3] = 0;
        return;
    }
    for (i = 0; i < 4; i++) {
        arg0[i] = (D_800CDA88_main + D_800D6A26_main)->v[i];
        if (arg0[i] == -1) {
            arg0[i] = D_800D0590_main[i];
        }
    }
    D_800CDA90_main[D_800D6A26_main].v[0]--;
    if (D_800CDA90_main[D_800D6A26_main].v[0] == 0) {
        D_800D6A26_main = (D_800D6A26_main + 1) & 0x1F;
    }
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005F904_main);

/* MP1 func_80071278: the buttons pressed on the window's ports (or queued in D_800FA048) */
s16 func_8005F918_main(TextWindow* tw) {
    u16 sp10[4];
    s16 btn = 0;

    if (tw->unk_38 & 2) {
        func_8005F7F4_main((s16*)sp10);
    }
    if (tw->unk21 & 1) {
        if (tw->unk_38 & 2) {
            btn |= sp10[0];
        } else {
            btn |= (D_800D0590_main[0] & 0x3FFF) | (D_800C9520_main[0] & 0xC000);
        }
    }
    if (tw->unk21 & 2) {
        if (tw->unk_38 & 2) {
            btn |= sp10[1];
        } else {
            btn |= (D_800D0590_main[1] & 0x3FFF) | (D_800C9520_main[1] & 0xC000);
        }
    }
    if (tw->unk21 & 4) {
        if (tw->unk_38 & 2) {
            btn |= sp10[2];
        } else {
            btn |= (D_800D0590_main[2] & 0x3FFF) | (D_800C9520_main[2] & 0xC000);
        }
    }
    if (tw->unk21 & 8) {
        if (tw->unk_38 & 2) {
            btn |= sp10[3];
        } else {
            btn |= (D_800D0590_main[3] & 0x3FFF) | (D_800C9520_main[3] & 0xC000);
        }
    }
    return btn;
}

u8 func_8005FA90_main(u8 *arg0) {
    s16 i, j;

    for (i = 0; i < 10; i += 2) {
        if (D_800A232C_main[i] == arg0[0] && D_800A232C_main[i + 1] == arg0[1]) {
            return i / 2;
        }
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 32; j += 2) {
            if (D_800A2344_main[i][j] == arg0[0] && D_800A2344_main[i][j + 1] == arg0[1]) {
                return i * 16 + j / 2;
            }
        }
    }
    return 16;
}

void func_8005FBA4_main(u8* arg0, u8* arg1) {
    for (; *arg1 != 0; arg0++, arg1 += 2) {
        *arg0 = func_8005FA90_main(arg1);
    }
    *arg0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005FBF8_main);

/* MP1 func_8007155C: the controller ports that drive the window */
void func_8005FE54_main(s16 winId, s16 ports) {
    TextWindow* tw = &D_800CC69C_main[winId];

    tw->unk21 = (tw->unk21 & 0xF0) | ports;
}

/* MP1 func_80071598: hides the window */
void func_8005FE90_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    HuSprAttrSet(tw->unk_6C, 0, 0x8000);
    HuSprAttrSet(tw->unk_6C, 1, 0x8000);
    for (i = 4; i < 0x16; i++) {
        if (tw->unk_6E[i] != -1) {
            HuSprAttrSet(tw->unk_6C, i, 0x8000);
        }
    }
    if (tw->unk6A != -1) {
        HuSprAttrSet(tw->unk_6C, 2, 0x8000);
    }
    if (tw->unk20 & 2) {
        HuSprAttrSet(tw->unk_6C, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 8);
}

/* MP1 func_8007166C: shows the window again */
void func_8005FFA8_main(s16 winId) {
    TextWindow* tw = &D_800CC69C_main[winId];
    s16 i;

    HuSprAttrReset(tw->unk_6C, 0, 0x8000);
    HuSprAttrReset(tw->unk_6C, 1, 0x8000);
    for (i = 4; i < 0x16; i++) {
        if (tw->unk_6E[i] != -1) {
            HuSprAttrReset(tw->unk_6C, i, 0x8000);
        }
    }
    if (tw->unk6A != -1) {
        HuSprAttrReset(tw->unk_6C, 2, 0x8000);
    }
    if (tw->unk20 & 2) {
        HuSprAttrReset(tw->unk_6C, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 0x4000);
}

void func_800600C0_main(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    if (arg1 != 0) {
        window->unk_38 |= 0x10;
    } else {
        window->unk_38 &= ~0x10;
    }
}

// Sets an option disabled.
void func_8006010C_main(s32 arg0, s16 arg1) {
    TextWindow* textWindow = &D_800CC69C_main[arg0];
    textWindow->unk_F4[arg1].unk0 = 2;
}

void func_80060144_main(s16 obj) {
#ifdef DEBUG

#endif
}

s16 func_8006014C_main(s32 winId) {
    return D_800CC69C_main[winId].unk_31;
}

void func_80060174_main(u8* arg0, u8* arg1) {
    while (*arg0 != 0) {
        if (*arg0 == 10) {
            arg0++;
        } else {
            *arg1++ = *arg0++;
        }
    }
    *arg1 = *arg0;
}

/* MP1 func_800718DC: func_80089308 with the line breaks removed */
void func_800601BC_main(s16 winId, void* str, s8 idx) {
    TextWindow* tw = &D_800CC69C_main[winId];

    func_8005B6BC_main(winId, (u32)str, idx);
    func_80060174_main(tw->unk_B8[idx], tw->unk_B8[idx]);
}

// Called to indicate that `str` should be the replacement at a
// "replacement index" location in the main string.
void func_8006022C_main(u32 str, s16 index) {
    D_800BDA6A_main = 1;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    func_800605A4_main((u8*)str);
    D_800CD2A4_main = 0;
    D_800D5206_main[index] = D_800BDA6D_main;
}

/* measures a text (a message id, or a pointer above 0x80000000) into D_8010106E[idx].
   Host: the id/pointer test assumes N64 addresses, and the text is passed on as a u32. */
void func_80060290_main(u8* str, s16 idx) {
    u8 loaded;
    u8* text;

    D_800BDA6A_main = 1;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    if ((u32)str > 0x80000000) {
        loaded = 0;
        text = str;
    } else {
        loaded = 1;
        text = func_800364DC_main(str);
    }
    func_80060174_main(text, text);
    func_800605A4_main(text);
    D_800CD2A4_main = 0;
    if (loaded) {
        func_800365E8_main(text);
    }
    D_800D5206_main[idx] = D_800BDA6D_main;
}

void func_8006034C_main(s16 winId, s16 idx, s8 color) {
    D_800CC69C_main[winId].unk_B2[idx] = color;
}

void func_80060388_main(s8 arg0) {
    D_800D5540_main = arg0;
}

/* measures count texts (ids or pointers); out = width + 10, height + 6 */
void func_80060394_main(s16 count, s16* out, ...) {
    va_list args;
    s16 i;

    D_800BDA6A_main = 0;
    va_start(args, out);
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    for (i = 0; i < count; i++) {
        func_800605A4_main(va_arg(args, u8*));
    }
    for (i = 0; i < 5; i++) {
        D_800D5206_main[i] = 0;
    }
    D_800D5540_main = 0xC;
    out[0] = D_800BDA6C_main + 10;
    out[1] = D_800BDA6E_main + 6;
}

void func_800604A8_main(s16 *arg0, s16 arg1, s16 arg2) {
    u32 i;

    if (arg2 < arg1) {
        arg0[1] = 0x64;
        arg0[0] = 0x64;
        return;
    }

    D_800BDA6A_main = 0;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;

    for (i = arg1; arg2 >= i; i++) {
        func_800605A4_main((u8*)i);
    }

    for (i = 0; i < ARRAY_COUNT(D_800D5206_main); i++) {
        D_800D5206_main[i] = 0;
    }

    D_800D5540_main = 0xC;
    arg0[0] = D_800BDA6C_main + 10;
    arg0[1] = D_800BDA6E_main + 6;
}

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CB0_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CD4_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CF8_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D1C_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D40_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D64_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D88_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DAC_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DD0_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DF4_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E18_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E3C_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E60_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E84_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7EA8_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7ECC_main);

// register allocation (masked 100 of 169): the text pointer and the character width swap a0/a1,
// and GCC keeps D_800CD2A4_main and D_800BDA6A_main in registers (u8 globals do not fix it).
// MP3 no longer adds an icon's width for code 0x18.
#ifdef NON_MATCHING
/* measures one text (an id, or a pointer above 0x80000000) into the width D_800BDA6C_main and
   height D_800BDA6E_main. Host: the id/pointer test assumes N64 addresses. */
void func_800605A4_main(u8* str) {
    s32 cw;
    u8* p = str;
    u8* loaded = NULL;
    u8 freeIt;
    s16 w;
    s16 h;
    s32 dh;

    if ((u32)str > 0x80000000) {
        freeIt = 0;
    } else {
        freeIt = 1;
        loaded = func_800364DC_main(str);
        p = loaded;
    }
    h = 14;
    w = 0;
    for (; *p != 0; p++, h = dh + h) {
        dh = 0;
        if (gLanguageIndex == 1) {
            cw = ((u8)(*p + 0x80) >= 2) ? 10 : 0;
        } else {
            cw = D_800A2194_main[*p];
        }
        if (*p != 0 && *p < 9) {
            cw = 0;
        }
        switch (*p) {
            case 0x10:
            case 0x1A:
            case 0x20:
                cw = (gLanguageIndex == 1 || *p == 0x1A) ? 10 : 4;
                break;
            case 10:
                if (D_800CD2A4_main == 0) {
                    goto newline;
                }
            case 12:
            case 13:
            case 15:
            case 0x16:
            case 0x19:
                cw = 0;
                break;
            newline:
                cw = 0;
                if ((s16)D_800BDA6C_main < w) {
                    D_800BDA6C_main = w;
                }
                w = 0;
                if (p[1] != 0) {
                    dh = 14;
                }
                break;
            case 0x17:
                dh = 5;
                cw = 0;
                break;
            case 11:
                if (D_800BDA6A_main == 0) {
                    if ((s16)D_800BDA6C_main < w) {
                        D_800BDA6C_main = w;
                    }
                    if ((s16)D_800BDA6E_main < h) {
                        D_800BDA6E_main = h;
                    }
                    h = 14;
                    dh = 0;
                    cw = 0;
                    w = 0;
                }
                break;
            case 14:
                cw = (w + D_800D5540_main) / D_800D5540_main * D_800D5540_main - w;
                break;
            case 0x18:
                p++;
                break;
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
                cw = D_800D5206_main[*p - 0x11];
                break;
        }
        w += cw;
    }
    if ((s16)D_800BDA6C_main < w) {
        D_800BDA6C_main = w;
    }
    if ((s16)D_800BDA6E_main < h) {
        D_800BDA6E_main = h;
    }
    if (freeIt) {
        func_800365E8_main(loaded);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/window", func_800605A4_main);
#endif

void func_80060848_main() {
    D_800CD2A4_main = 1;
}

void func_80060858_main(s32 winId, u16 btn) {
    TextWindow* tw = &D_800CC69C_main[winId];

    tw->unkA6 = btn;
}

INCLUDE_ASM("asm/nonmatchings/window", func_80060880_main);

INCLUDE_ASM("asm/nonmatchings/window", func_80060C14_main);

INCLUDE_ASM("asm/nonmatchings/window", func_80060DEC_main);

/* MP1 func_80071E80: closes the window with a shrinking animation (MP3 also shrinks the
   second portrait sprite unk276) */
void func_80060EA8_main(s32 winId, s32 sound) {
    TextWindow* tw = &D_800CC69C_main[winId];
    f32 scale = 1.0f;

    if (tw->unk_38 & 0x4000) {
        func_800600C0_main(winId, 1);
        if (sound != 0) {
            if (tw->unk_38 & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(0x137);
            }
        }
        while (scale > 0.0f) {
            HuSprScaleSet(tw->unk_6C, tw->unk274, scale, scale);
            if (tw->unk276 != 0) {
                HuSprScaleSet(tw->unk_6C, tw->unk276, scale, scale);
            }
            func_8005BB18_main(winId, scale, scale);
            scale -= 0.1f;
            HuPrcVSleep();
        }
        HuSprScaleSet(tw->unk_6C, tw->unk274, scale, scale);
        if (tw->unk276 != 0) {
            HuSprScaleSet(tw->unk_6C, tw->unk276, scale, scale);
        }
        func_8005BB18_main(winId, scale, scale);
        func_800600C0_main(winId, 0);
        func_8005B63C_main(winId, 0x4000, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/window", func_8006105C_main);

void func_800610E0_main(s16 arg0) {
    func_8005F364_main(arg0);
}

INCLUDE_ASM("asm/nonmatchings/window", func_80061100_main);

// Obtains a window handle
s32 func_80061188_main(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    TextWindow *temp_s2;
    s32 temp_v0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s0 = arg3 + 2;

    if ((arg0 != -1) & (arg4 < 0x30)) {
        arg4 = 0x30;
    }

    temp_v0 = func_8005A968_main(arg1, arg2, temp_s0, arg4, 0, arg5);
    func_8005BDFC_main(temp_v0, 0);
    temp_s2 = &D_800CC69C_main[temp_v0];
    func_8005BCA4_main(temp_v0, temp_s0 / 2, arg4 / 2);
    func_8005BA90_main(temp_v0, (temp_s2->unk3C + temp_s0 / 2), (temp_s2->unk3E + arg4 / 2));
    temp_s2->unk276 = arg0;

    if (arg0 != -1) {
        temp_s2->unk274 = func_8005B7B8_main(temp_v0, D_800A25D0_main[arg0], (0x18 - temp_s2->unk48), (0x18 - temp_s2->unk4A), 0);
    }

    temp_s2->unk54 = 6;
    temp_s2->unk4C = 6;
    func_8005BEE0_main(temp_v0, 0xD0);
    func_8005C060_main(temp_v0, 1, 0x40, 0xF0, 0xFF);
    func_8005FBF8_main(temp_v0, 0x40, 0x20, 0xB0);
    func_8005D294_main(temp_v0);
    func_8005FE90_main(temp_v0);
    func_8005F904_main();
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/window", func_80061388_main);

INCLUDE_ASM("asm/nonmatchings/window", func_800615B8_main);

void func_80061934_main(s16 winId, s16 arg1) {
    s16 temp_v0;
    TextWindow *temp_s0;

    temp_s0 = &D_800CC69C_main[winId];
    func_800600C0_main(winId, 1);
    func_800615B8_main(winId, 0);
    func_8005B8F8_main(winId, temp_s0->unk274);
    temp_v0 = func_8005B7B8_main(winId, D_800A25D0_main[arg1], 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A, 0);
    temp_s0->unk274 = temp_v0;
    func_80054904_main(temp_s0->unk_6C, temp_v0, 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A);
    HuSprScaleSet(temp_s0->unk_6C, temp_s0->unk274, 1.0f, 1.0f);
    func_800615B8_main(winId, 1);
    func_800600C0_main(winId, 0);
}

void func_80061A5C_main(s16 arg0, s16 arg1) {
    s16 i;

    if (arg1 == 0) {
        func_8005D294_main(arg0);

        for (i = 0; i < 5; i++) {
            func_8005BB18_main(arg0, 1.0f, 1.0f - sindf(i * 18.0f));
            HuPrcVSleep();
        }

        func_8005FE90_main(arg0);
        HuPrcVSleep();
        return;
    }
    func_8005FE90_main(arg0);
}
