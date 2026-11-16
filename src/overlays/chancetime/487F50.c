#include "common.h"

// event e3
typedef struct {
    /* 0x00 */ s8 state;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 pos;
    /* 0x0C */ f32 target;
    /* 0x10 */ s16 top;
    /* 0x12 */ s16 next;
    /* 0x14 */ s16 anim[3];
    /* 0x1A */ s8 count;
    /* 0x1B */ s8 items[13];
} ChanceWheel; /* sizeof 0x28 */

typedef struct {
    s16 x;
    s16 y;
} ChancePos16;

void func_80032FC0_main(s16, u8, u8);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s16 func_8000B0D4_main(s32, s32);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800F5E30_shared_board(void);
void func_800F5F4C_shared_board(s32 arg0, s32 arg1);
void func_800F5F60_shared_board(void);
void func_800F5F7C_shared_board(void);
void func_800F7108_shared_board(void);
s32 func_800EDC40_shared_board(void);

void func_80108704_chancetime(void);
s32 func_8010872C_chancetime(void);
void func_80108A88_chancetime(void);
void func_80108B50_chancetime(void);
void func_80106F10_chancetime(s32);
void func_8010705C_chancetime(s32);
void func_801071A8_chancetime(s32);

void func_8010C5F4_chancetime(omObjData *obj);
void func_8010C610_chancetime(omObjData *obj);
void func_8010C870_chancetime(omObjData *obj);
void func_8010C98C_chancetime(void);
void func_8010C994_chancetime(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010CF78_chancetime(s8 set);
void func_8010D320_chancetime(omObjData *obj);
void func_8010D6A4_chancetime(s8 wheel);
void func_8010D92C_chancetime(s8 wheel);
void func_8010DAB0_chancetime(void);
void func_8010DB1C_chancetime(s8 wheel);
void func_8010DF68_chancetime(void);
void func_8010DF70_chancetime(void);
void func_8010DFA4_chancetime(void);
void func_8010E210_chancetime(void);
void func_8010E280_chancetime(void);
void func_8010E4D0_chancetime(void);
void func_8010F1F8_chancetime(void);

extern s8 D_8010FB80_chancetime;
extern s8 D_8010FB81_chancetime;
extern ChancePos16 D_8010FB84_chancetime;
extern f32 D_8010FB88_chancetime;
extern f32 D_8010FB8C_chancetime;
extern Vec D_8010FB94_chancetime[];
extern char *D_8010FBD8_chancetime[];
extern s32 D_8010FBF0_chancetime;
extern s32 D_8010FBF4_chancetime[3];
extern s32 D_8010FC00_chancetime;
extern s32 D_8010FC10_chancetime;
extern s32 D_8010FC14_chancetime;
extern s32 D_8010FC18_chancetime;
extern s32 D_8010FC1C_chancetime;
extern s32 D_8010FAE4_chancetime;

extern s16 D_8010FE90_chancetime;
extern s16 D_8010FE92_chancetime;
extern s16 D_8010FE94_chancetime[3];
extern s16 D_8010FE9A_chancetime;
extern HuSprite *D_8010FE9C_chancetime;
extern void *D_8010FEA0_chancetime;
extern void *D_8010FEA4_chancetime;
extern ChancePos16 D_8010FEA8_chancetime;
extern s16 D_8010FEB0_chancetime[3][3];
extern s32 D_8010FEC4_chancetime;
extern s8 D_8010FEC8_chancetime;
extern s8 D_8010FEC9_chancetime;
extern ChanceWheel D_8010FED0_chancetime[3];
extern s32 D_8010FF48_chancetime[3];
extern s16 D_8010FF4A_chancetime;
extern s16 D_8010FF4E_chancetime;
extern s16 D_8010FF52_chancetime;
extern s8 D_80110000_chancetime;
extern s32 D_80110004_chancetime;
extern s16 D_80110006_chancetime;
extern s32 D_80110008_chancetime;
extern s16 D_80110010_chancetime[10];
extern s16 D_80110028_chancetime[20];
extern omObjData *D_80110080_chancetime;
extern void (*D_80110084_chancetime)(void);
extern omObjData *D_801100C8_chancetime;
extern void (*D_801100CC_chancetime)(omObjData *);
extern s8 D_801100D0_chancetime[4];
extern s8 D_801100DC_chancetime;
extern s8 D_801100DD_chancetime[3];

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010BF80_chancetime);

void func_8010C5F4_chancetime(omObjData *obj) {
    func_8010D320_chancetime(obj);
}

void func_8010C610_chancetime(omObjData *obj) {
    Vec pos;
    Vec2f screen;

    D_8010FB8C_chancetime += 1.2f;
    D_8010FB8C_chancetime = (D_8010FB8C_chancetime > 30.0f) ? 30.0f : D_8010FB8C_chancetime;
    if ((D_8010FB88_chancetime -= D_8010FB8C_chancetime) < 0.0f) {
        D_8010FB8C_chancetime = D_8010FB8C_chancetime * -0.1f;
        D_8010FB88_chancetime = 0.0f;
        if (D_8010FC00_chancetime == 0) {
            func_80108704_chancetime();
            D_8010FC00_chancetime = 1;
        }
        if (D_8010FB8C_chancetime >= -0.24000001f) {
            D_8010FC00_chancetime = 0;
            D_801100CC_chancetime = func_8010C870_chancetime;
            D_8010FB88_chancetime = 0.0f;
            return;
        }
    }
    pos.x = 0.0f;
    pos.y = (D_8010FB94_chancetime[0].x + D_8010FB88_chancetime) - 168.0f;
    pos.z = D_8010FB94_chancetime[0].y;
    Hu3DCam3DToScreen(0, &pos, &screen);
    D_8010FB84_chancetime.x = 74;
    D_8010FB84_chancetime.y = (screen.y - 120.0f) + 25.0f;
    func_8000BBD4_main(D_8010FE9A_chancetime, 161, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[0], D_8010FB84_chancetime.x + 51, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[1], D_8010FB84_chancetime.x + 124, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[2], D_8010FB84_chancetime.x + 87, D_8010FB84_chancetime.y + 116);
}

void func_8010C870_chancetime(omObjData *obj) {
    D_8010FB84_chancetime.x = 74;
    D_8010FB84_chancetime.y = 25;
    func_8000BBD4_main(D_8010FE9A_chancetime, 161, 71);
    func_8000BBD4_main(D_8010FE94_chancetime[0], D_8010FB84_chancetime.x + 51, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[1], D_8010FB84_chancetime.x + 124, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[2], D_8010FB84_chancetime.x + 87, D_8010FB84_chancetime.y + 116);
    if (func_8010872C_chancetime() == 1) {
        D_8010FB88_chancetime = 600.0f;
        D_8010FB8C_chancetime = 0.0f;
        D_8010FB80_chancetime = 0;
        D_8010FB81_chancetime = 1;
        D_801100CC_chancetime = func_8010C5F4_chancetime;
    }
}

void func_8010C98C_chancetime(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C994_chancetime);

void func_8010CF78_chancetime(s8 set) {
    static const s8 D_8010FC98_chancetime[3][13] = {
        { 4, 2, 8, 3, 7, 4, 8, 2, 3, 0, 3, 5, 8 },
        { 0, 3, 6, 1, 8, 7, 2, 8, 4, 5, 0, 7, 2 },
        { 1, 7, 5, 4, 7, 1, 0, 6, 2, 0, 7, 8, 6 },
    };
    s8 i;
    s8 j;
    s8 k;

    D_8010FBF0_chancetime = 0;
    for (i = 0; i < 3; i++) {
        D_8010FBF4_chancetime[i] = 0;
        D_801100DD_chancetime[i] = -1;
        D_8010FED0_chancetime[i].state = 0;
        D_8010FED0_chancetime[i].top = 2;
        D_8010FED0_chancetime[i].next = 4;
        D_8010FED0_chancetime[i].speed = 0.0f;
        D_8010FED0_chancetime[i].target = -1.0f;
    }
    for (i = 0; i < 2; i++) {
        k = rand8() & 3;
        for (j = 0; j < 4; j++) {
            D_8010FED0_chancetime[i].items[k] = GwPlayer[D_801100D0_chancetime[j]].chr;
            k++;
            if (k >= 4) {
                k = 0;
            }
        }
        D_8010FED0_chancetime[i].count = 4;
    }
    k = rand8() % 13;
    for (j = 0; j < 13; j++) {
        D_8010FED0_chancetime[2].items[k] = D_8010FC98_chancetime[set][j];
        k++;
        if (k >= 13) {
            k = 0;
        }
    }
    D_8010FED0_chancetime[2].count = 13;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            D_8010FED0_chancetime[i].anim[j] = D_8010FEB0_chancetime[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            func_8003302C_main(D_8010FED0_chancetime[i].anim[j], D_8010FED0_chancetime[i].items[2 - j]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCE8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCF8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D320_chancetime);

void func_8010D6A4_chancetime(s8 wheel) {
    s8 i;
    s8 n;

    D_8010FBF0_chancetime++;
    switch (D_8010FBF0_chancetime) {
    case 1:
        D_8010FF48_chancetime[0] = HuAudFXPlay(0x4F9);
        D_8010FBF4_chancetime[0] = 1;
        break;
    case 2:
        D_8010FF48_chancetime[1] = HuAudFXPlay(0x4FA);
        D_8010FBF4_chancetime[1] = 1;
        break;
    case 3:
        D_8010FF48_chancetime[2] = HuAudFXPlay(0x4FB);
        D_8010FBF4_chancetime[2] = 1;
        break;
    }
    D_8010FED0_chancetime[wheel].state = 4;
    if (wheel < 2 && D_801100DD_chancetime[1 - wheel] != -1) {
        n = 0;
        for (i = 0; i < 4; i++) {
            if (D_801100DD_chancetime[1 - wheel] != GwPlayer[D_801100D0_chancetime[i]].chr) {
                D_8010FED0_chancetime[wheel].items[n] = GwPlayer[D_801100D0_chancetime[i]].chr;
                n++;
            }
        }
        D_8010FED0_chancetime[wheel].count = 3;
        for (i = 0; i < 3; i++) {
            func_8003302C_main(D_8010FED0_chancetime[wheel].anim[i], D_8010FED0_chancetime[wheel].items[2 - i]);
        }
    }
    func_8010DB1C_chancetime(wheel);
}

void func_8010D92C_chancetime(s8 wheel) {
    switch (D_8010FBF0_chancetime) {
    case 1:
        if (D_8010FBF4_chancetime[0] == 1) {
            HuAudFXStop(D_8010FF4A_chancetime);
        }
        HuAudFXPlay(0x4FC);
        break;
    case 2:
        if (D_8010FBF4_chancetime[1] == 1) {
            HuAudFXStop(D_8010FF4E_chancetime);
        }
        HuAudFXPlay(0x4FD);
        break;
    case 3:
        if (D_8010FBF4_chancetime[2] == 1) {
            HuAudFXStop(D_8010FF52_chancetime);
        }
        HuAudFXPlay(0x4FE);
        break;
    }
    D_8010FED0_chancetime[wheel].state = 1;
}

void func_8010DA24_chancetime(void) {
    s32 i;

    D_8010FB80_chancetime = 1;
    D_8010FB81_chancetime = 0;
    for (i = 0; i < 3; i++) {
        func_8000BB54_main(D_8010FE94_chancetime[i]);
    }
    func_8000BB54_main(D_8010FE9A_chancetime);
    D_801100CC_chancetime = func_8010C610_chancetime;
}

s8 func_8010DAA4_chancetime(void) {
    return D_8010FB81_chancetime;
}

void func_8010DAB0_chancetime(void) {
    omObjData *obj = D_801100C8_chancetime;
    s8 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(obj->model[i + 1], 4, 4);
    }
}

void func_8010DB1C_chancetime(s8 wheel) {
    omObjData *obj = D_801100C8_chancetime;

    func_8000BB94_main(D_8010FE94_chancetime[wheel]);
    func_8001C258_main(obj->model[wheel + 1], 4, 0);
}

void func_8010DB78_chancetime(void) {
    D_8010FEC4_chancetime = 0;
    D_8010FEC8_chancetime = 1;
    D_8010FEC9_chancetime = 0;
}

void func_8010DB98_chancetime(void) {
    D_8010FEC8_chancetime = 0;
    D_8010FEC9_chancetime = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DBB0_chancetime);

void func_8010DF68_chancetime(void) {
}

void func_8010DF70_chancetime(void) {
}

void func_8010DF78_chancetime(s8 arg0) {
    D_8010FC14_chancetime = 0;
    D_80110008_chancetime = arg0;
    D_80110084_chancetime = func_8010DFA4_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DFA4_chancetime);

void func_8010E1E0_chancetime(void) {
    func_8010D6A4_chancetime(D_80110000_chancetime);
    D_80110084_chancetime = func_8010E210_chancetime;
}

void func_8010E210_chancetime(void) {
    if (++D_8010FC1C_chancetime >= 10) {
        D_8010FC14_chancetime = 1;
        D_8010FC1C_chancetime = 0;
        D_80110084_chancetime = func_8010DF70_chancetime;
    }
}

s32 func_8010E258_chancetime(void) {
    return D_8010FC14_chancetime;
}

void func_8010E264_chancetime(void) {
    D_8010FC18_chancetime = 0;
    D_80110084_chancetime = func_8010E280_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E280_chancetime);

s32 func_8010E4C4_chancetime(void) {
    return D_8010FC18_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4D0_chancetime);

void func_8010F1DC_chancetime(void) {
    D_8010FC10_chancetime = 0;
    D_80110084_chancetime = func_8010F1F8_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F1F8_chancetime);

s32 func_8010F420_chancetime(void) {
    return D_8010FC10_chancetime;
}

void func_8010F42C_chancetime(void) {
    D_8010FC10_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F44C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F984_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD0C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD20_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD38_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD3C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD40_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD5C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD68_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD8C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDB0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDD4_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDF8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE1C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE3C_chancetime);
