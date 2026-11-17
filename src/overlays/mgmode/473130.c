#include "common.h"
#include "game/gamework_data.h"
#include "game/hmfman.h"
#include "game/vibrator.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/data.h"
#include "game/object.h"
#include "game/gamemes.h"
#include "game/pause.h"
#include "game/board.h"
#include "input.h"
#include "variables.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

/* wave 3t m2: Minigame mode menus (Game Room / Mini-Game House doors). */

typedef f32 MgMtx[4][4];

/* A model descriptor: func_8011667C_mgmode creates D_8011B8A8_mgmode[i] from entry i. */
typedef struct MgModelDesc {
    /* 0x00 */ s32 file; /* -1 ends the table */
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} MgModelDesc; /* size 0x24 */

/* A model part looked up by name (func_8001D33C_main). */
typedef struct MgHmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk_18[0x20];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ char unk_3C[0x1C];
    /* 0x58 */ MgMtx mtx;
} MgHmfPart;

void func_8000BB54_main(u16 arg0);
void func_8000BB94_main(u16 arg0);
void func_8000BBD4_main(u16 spriteId, s16 x, s16 y);
void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, u16);
void func_8000BCC8_main(u16, s32);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000C184_main(u16);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
s32 func_80017BB8_main(s16, s16);
void func_80017D24_main(MgMtx, f32, f32, f32);
void func_8001C258_main(s16 arg0, s32 arg1, s32 arg2);
void func_8001C448_main(s16);
s32 func_8001C514_main(s16);
void func_8001C624_main(s16, s16, s16, s16, s16);
void func_8001C814_main(s16, s16, s16);
void func_8001C8A8_main(s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_8001F304_main(s16, s16);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002367C_main(MgMtx, MgMtx);
void func_8005B43C_main(s16, s32, s32, s32);
void func_8005BE30_main(s16, s32);
s16 func_8005E0C0_main(s16);
s32 func_8005E1D8_main(s16, s16, s32);
void func_8005FE54_main(s16, s16);
void func_800604A8_main(s16 *, s16, s16);
s32 func_80061188_main(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5);
void func_80061388_main(s16);
void func_80061A5C_main(s16, s16);

/* A sprite slot of a group created by func_80116794_mgmode; unk00 == -1 ends the group. */
typedef struct MgSprSlot {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u16 espId;
} MgSprSlot;

/* A cursor position of a menu (func_8011822C_mgmode); x == -1 and y == -1 end the table. */
typedef struct MgCursorPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MgCursorPos;

/* other mgmode units */
void func_80116968_mgmode(MgSprSlot *grp, s16 idx, s16 x, s16 y);
void func_801169A0_mgmode(MgSprSlot *grp, s16 idx);
void func_801169C8_mgmode(MgSprSlot *grp, s16 idx);
void func_801169F0_mgmode(MgSprSlot *grp, s16 idx, u16 arg2);
void func_80116A48_mgmode(MgSprSlot *grp, s16 idx, f32 sx, f32 sy);
void func_80116A78_mgmode(MgSprSlot *grp, s16 idx, s16 alpha);
MgSprSlot *func_80116794_mgmode(void *def);
void func_801168E0_mgmode(MgSprSlot *grp);
void func_80116D4C_mgmode(void);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
s16 func_8010A148_mgmode(s16 event);
void func_8010A5F0_mgmode(void);
void func_8011667C_mgmode(MgModelDesc *desc);
void func_80116E24_mgmode(s16 arg0);
void func_80116ED4_mgmode(s16 arg0, s16 arg1, s16 arg2, void (*arg3)(s16 *));
void func_801181F4_mgmode(s16 arg0);
void func_8011822C_mgmode(MgCursorPos *table);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
void func_801182B4_mgmode(s16 arg0);
s16 func_80118678_mgmode(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80118D0C_mgmode(void);
void func_80118888_mgmode(s16 idx);
void func_801188A4_mgmode(s16 idx);
void func_80118624_mgmode(s16 shadow, s16 model);
s16 func_801182DC_mgmode(s16 x, s16 y);

#define MG_NOFUNC ((void (*)(s16 *))-1)

extern u8 D_80118EB1_mgmode;
extern s16 D_80118EB4_mgmode;
extern u8 D_80119344_mgmode[];
extern MgCursorPos D_80119424_mgmode[];
extern u8 D_80119434_mgmode[];
extern MgModelDesc D_8011997C_mgmode[];
extern MgModelDesc D_80119A78_mgmode[]; /* D_8011997C_mgmode[7] */
extern MgMtx D_8011B3F0_mgmode;
extern s16 D_8011B436_mgmode[4];
extern s16 D_8011B43E_mgmode[4];
extern s16 D_8011B446_mgmode[4];
extern s16 D_8011B6A8_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_8011B78C_mgmode;
extern s16 D_8011B78E_mgmode[];
extern s16 D_8011B796_mgmode[];
extern s16 D_8011B78A_mgmode;
extern s16 D_8011B808_mgmode;
extern s16 D_8011B884_mgmode;
extern f32 D_8011B888_mgmode;
extern u16 D_8011B8A8_mgmode[];
extern u16 D_8011B8B0_mgmode;
extern s16 D_8011B8B6_mgmode[]; /* D_8011B8A8_mgmode[7] */
extern s16 D_8011B8E8_mgmode[]; /* D_8011B8A8_mgmode[32] */
extern u8 D_8011B6B0_mgmode[][25];
extern s16 D_8011B940_mgmode[];
extern void *D_8011B954_mgmode;
extern u8 D_8011B958_mgmode;
extern MgSprSlot *D_8011B450_mgmode;
extern MgSprSlot *D_8011B480_mgmode;
extern s16 D_8011B484_mgmode;
extern u16 D_8011B488_mgmode[28];
extern s16 D_8011B4C0_mgmode;
extern s16 D_80119490_mgmode[]; /* [D_800CC438_main][7] */
extern s16 D_8011B454_mgmode;
extern s16 D_8011B458_mgmode[];
extern u8 D_80119EB0_mgmode[];
extern s16 D_80119340_mgmode;
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;
extern u8 D_8011B430_mgmode[];
extern u8 D_8011B434_mgmode;
extern u8 D_80119430_mgmode[];
extern MgCursorPos D_8011943C_mgmode[];
extern MgCursorPos D_80119454_mgmode[];
extern MgCursorPos D_8011B468_mgmode[];
extern s16 D_8011944C_mgmode[];

/* The minigame table D_800A6D44_main seen from +2 (a second label inside each 0x14-byte entry). */
typedef struct MgMinigameEntry2 {
    /* 0x00 */ u16 unk00; /* MinigameTable +2 */
    /* 0x02 */ char unk02[0x12];
} MgMinigameEntry2;
extern MgMinigameEntry2 D_800A6D46_main[];

/* main-code variables with no name in the tree yet (undefined_syms.txt, wave 3t m2) */
extern s16 D_800CC438_main;
extern s16 D_800CB894_main;
extern s16 D_800CE29C_main; /* the chosen minigame; its low byte is also read as u8 at +1 */
extern s16 D_800D03FE_main[4]; /* read back as its low byte (lbu +1) */
extern u8 D_800D1F20_main[4];
extern s16 D_800D1F2C_main;
extern s16 D_800D4194_main; /* D_800D4190_main.event */
extern s16 D_800D0418_main[]; /* empstrline + 8: the minigame list of a round */

s32 func_8010F648_mgmode(void);
void func_8010CB20_mgmode(void);
void func_8010CBFC_mgmode(void);
void func_8010D308_mgmode(void);
s16 func_8010D3B0_mgmode(s32 back);
void func_8010D98C_mgmode(void);
s16 func_8010DAB8_mgmode(s32 back);
void func_8010E1F0_mgmode(void);
void func_8010E494_mgmode(s16 mode);
void func_8010E40C_mgmode(void);
void func_8010E6F0_mgmode(s16 event);
void func_8010EE84_mgmode(s16 event);
s16 func_8010F348_mgmode(s16 event);
u8 func_80110420_mgmode(s16 mg);

void func_8010BEC0_mgmode(void) {
    s16 size[2];
    MgHmfPart *door;
    s16 model;
    s16 choice;
    s16 i;
    s16 flag;
    s16 chr;
    u16 m;
    void *anim;
    MgModelDesc *desc;

    D_8011B954_mgmode = D_80119344_mgmode;
    D_8011B888_mgmode = 2500.0f;
    func_800604A8_main(size, 0x5600, 0x560E);
    D_8011B6A8_mgmode = func_80061188_main(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    func_8005FE54_main(D_8011B6A8_mgmode, 1 << D_8011B808_mgmode);
    func_8005BE30_main(D_8011B6A8_mgmode, 5);
    for (i = 0; i < 4; i++) {
        D_8011B43E_mgmode[i] = chr = GwPlayer[i].chr;
        D_8011997C_mgmode[i + 7].file = func_80017BB8_main(chr, 0xA1);
        D_8011997C_mgmode[i + 11].file = func_80017BB8_main(chr, 2);
        D_8011997C_mgmode[i + 15].file = func_80017BB8_main(chr, 0x33);
        D_8011997C_mgmode[i + 19].file = func_80017BB8_main(chr, 0x3A);
        D_8011997C_mgmode[i + 23].file = func_80017BB8_main(chr, 0x2F);
        D_8011997C_mgmode[i + 27].file = func_80017BB8_main(chr, D_80119434_mgmode[chr]);
        desc = &D_80119A78_mgmode[i];
        D_8011B446_mgmode[i] = func_80118678_mgmode(desc->pos.x, 400.0f, desc->pos.z, 30.0f);
    }
    func_8011667C_mgmode(D_8011997C_mgmode);
    door = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
    func_8002367C_main(D_8011B3F0_mgmode, door->mtx);
    func_8001C8A8_main(D_8011B8A8_mgmode[4], 2);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[4], 0.7f, 0.7f, 0.7f);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[31], 0.7f, 0.7f, 0.7f);
    for (i = 0; i < 4; i++) {
        model = D_8011B8B6_mgmode[i];
        func_8001C8A8_main(model, 2);
        func_8001C258_main(model, 4, 4);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        D_8011B436_mgmode[i] = func_80017790_main(model, 1, D_8011B43E_mgmode[i], func_80017B6C_main(D_8011B43E_mgmode[i], 1, 0));
        func_8001C514_main(model);
    }
    m = D_8011B8A8_mgmode[4];
    anim = DataRead(0xA002A);
    HmfAnimCreate(HmfModelData[(s16)m].hmf, anim, 0, "c180n_0_DEF");
    DataClose(anim);
    func_8001C448_main(m);
    func_8001C514_main(m);
    if (omovlevtno != 4) {
        func_8001F304_main(D_8011B8A8_mgmode[4], D_8011B78A_mgmode);
        func_8001C814_main(D_8011B8A8_mgmode[4], 2, 2);
        func_80116E24_mgmode(0);
        WipeCreateIn(0xFF, 0);
        RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
        HuAudFXPlay(0x2EB);
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
            func_8002367C_main(door->mtx, D_8011B3F0_mgmode);
            func_80017D24_main(door->mtx, 0, -i * 5, 0);
        }
        func_80116ED4_mgmode(1, 10, 1, MG_NOFUNC);
        HuPrcSleep(5);
        func_8002367C_main(door->mtx, D_8011B3F0_mgmode);
        func_80116ED4_mgmode(5, 20, 1, MG_NOFUNC);
        goto setup;
    }
    D_8011B884_mgmode = 1;
    if (func_8010F648_mgmode() == 0) {
        func_80116ED4_mgmode(5, 10, 1, MG_NOFUNC);
        HuAudSeqPlay(0x4C);
    setup:
        func_8011822C_mgmode(D_80119424_mgmode);
        func_801181F4_mgmode(0);
        func_801182B4_mgmode(1);
        func_8005B43C_main(D_8011B6A8_mgmode, 0x5600, -1, -1);
        func_80061388_main(D_8011B6A8_mgmode);
    } else {
        func_80061388_main(D_8011B6A8_mgmode);
        HuAudSeqPlay(0x4C);
        func_8010CB20_mgmode();
    }
    while (TRUE) {
        HuPrcVSleep();
        func_8011829C_mgmode(5);
        if (D_8011B958_mgmode != 3) {
            if (D_8011B958_mgmode == 5) {
                if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
                    HuAudFXPlay(2);
                    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
                    func_801182B4_mgmode(0);
                    HuAudFXPlay(0x299);
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5603, -1, -1);
                    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                        HuPrcVSleep();
                    }
                    while (TRUE) {
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5604, -1, -1);
                        while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                            HuPrcVSleep();
                        }
                        if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) != 0) {
                            choice = -1;
                            break;
                        }
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5605, -1, -1);
                        while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                            HuPrcVSleep();
                        }
                        choice = func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0);
                        if (choice != -1) {
                            if (choice == 0) {
                                func_8005B43C_main(D_8011B6A8_mgmode, 0x5606, -1, -1);
                                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                                    HuPrcVSleep();
                                }
                            }
                            break;
                        }
                    }
                    if (choice == -1) {
                        func_801182B4_mgmode(1);
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5600, -1, -1);
                        while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                            HuPrcVSleep();
                        }
                    } else {
                        func_8010CB20_mgmode();
                    }
                } else {
                    flag = 0;
                    if ((D_800C9520_main[D_8011B808_mgmode] & 0x200) || (D_800D5558_main[D_8011B808_mgmode] & 0x4000)) {
                        HuAudFXPlay(1);
                        func_80061A5C_main(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(20);
                        func_801182A8_mgmode(1);
                        func_80116ED4_mgmode(3, 20, 1, MG_NOFUNC);
                        flag = 1;
                    }
                    if (D_800C9520_main[D_8011B808_mgmode] & 0x100) {
                        HuAudFXPlay(1);
                        func_80061A5C_main(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(25);
                        func_801182A8_mgmode(1);
                        func_80116ED4_mgmode(6, 10, 0, MG_NOFUNC);
                        func_80116ED4_mgmode(3, 15, 1, MG_NOFUNC);
                        flag = 1;
                    }
                    if (flag) {
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5601, -1, -1);
                        func_80061388_main(D_8011B6A8_mgmode);
                    }
                }
            }
        } else {
            if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
                HuAudFXPlay(2);
                func_8005B43C_main(D_8011B6A8_mgmode, 0x5602, -1, -1);
                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                    HuPrcVSleep();
                }
                if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) != 0) {
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5601, -1, -1);
                    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                        HuPrcVSleep();
                    }
                } else {
                    func_801182B4_mgmode(0);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_80116ED4_mgmode(3, 20, 1, MG_NOFUNC);
                    door = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
                    RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
                    HuAudFXPlay(0x2EB);
                    for (i = 0; i < 19; i++) {
                        HuPrcVSleep();
                        func_8002367C_main(door->mtx, D_8011B3F0_mgmode);
                        func_80017D24_main(door->mtx, 0, -i * 5, 0);
                    }
                    func_80116ED4_mgmode(4, 20, 1, MG_NOFUNC);
                    D_80118EB1_mgmode = 1;
                    D_80118EB4_mgmode = 0x80;
                    HuAudSeqFadeOut(60);
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                }
            } else {
                flag = 0;
                if (D_800C9520_main[D_8011B808_mgmode] & 0x200) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(25);
                    func_801182A8_mgmode(0);
                    func_80116ED4_mgmode(6, 10, 0, MG_NOFUNC);
                    func_80116ED4_mgmode(5, 15, 1, MG_NOFUNC);
                    flag = 1;
                }
                if (D_800C9520_main[D_8011B808_mgmode] & 0x100) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(20);
                    func_801182A8_mgmode(0);
                    func_80116ED4_mgmode(5, 20, 1, MG_NOFUNC);
                    flag = 1;
                }
                if (flag) {
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5600, -1, -1);
                    func_80061388_main(D_8011B6A8_mgmode);
                }
            }
        }
        if (HmfModelData[(s16)D_8011B8A8_mgmode[4]].unk02 != D_8011B78A_mgmode &&
            HmfModelData[(s16)D_8011B8A8_mgmode[4]].unk04 != D_8011B78A_mgmode) {
            func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B78A_mgmode, 0, 8, 2);
        }
    }
}

void func_8010CB20_mgmode(void) {
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5607, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
        HuPrcVSleep();
    }
    func_80116ED4_mgmode(2, 10, 1, MG_NOFUNC);
    func_8010CBFC_mgmode();
    func_80116ED4_mgmode(5, 10, 1, MG_NOFUNC);
    func_8011822C_mgmode(D_80119424_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5600, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
        HuPrcVSleep();
    }
}

void func_8010CBFC_mgmode(void) {
    f32 t;
    f32 sx;
    f32 sy;
    s16 i;
    s16 step;
    s16 back;
    s16 ret;

    HuPrcSleep(3);
    D_8011B450_mgmode = func_80116794_mgmode(D_80119EB0_mgmode);
    func_80116968_mgmode(D_8011B450_mgmode, 0, 180, 110);
    for (i = 0; i < 9; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, i);
        func_801169F0_mgmode(D_8011B450_mgmode, i, 0x4000);
    }
    HuAudFXPlay(0x243);
    HuPrcSleep(5);
    func_801169A0_mgmode(D_8011B450_mgmode, 0);
    for (i = 0; i < 11; i++) {
        t = i / 10.0f;
        sx = sindf(t * 90.0f);
        sy = cosdf(t * 270.0f + 90.0f);
        if (sy < 0.0f) {
            sy = -sy;
        }
        func_80116A48_mgmode(D_8011B450_mgmode, 0, sx, sy);
        HuPrcVSleep();
    }
    for (i = 0, D_8011B454_mgmode = 0; i < 5; i++) {
        if (D_8011B928_mgmode[i] >= 3) {
            D_8011B458_mgmode[D_8011B454_mgmode] = i;
            D_8011B454_mgmode++;
        }
    }
    D_800D1F2C_main = 0;
    step = 0;
    back = 0;
    do {
        switch (step) {
            case 0:
                D_800CC438_main = func_8010D3B0_mgmode(back);
                if (D_800CC438_main == -1) {
                    step = 4;
                    func_8010D98C_mgmode();
                } else {
                    back = 0;
                    step++;
                }
                break;
            case 1:
                ret = func_8010DAB8_mgmode(back);
                if (ret == -1) {
                    back = 1;
                    func_8010E40C_mgmode();
                    step--;
                } else {
                    D_800D4194_main = D_8011B458_mgmode[ret];
                    if (!(D_800D4194_main == 1 || D_800D4194_main == 2)) {
                        for (i = 0; i < 4; i++) {
                            GwPlayer[i].group = i;
                        }
                        step++;
                    }
                    step++;
                }
                break;
            case 2:
                func_8005B43C_main(D_8011B6A8_mgmode, 0x560A, -1, -1);
                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                    HuPrcVSleep();
                }
                ret = func_8010A148_mgmode(D_800D4194_main);
                func_8010A5F0_mgmode();
                if (ret != 0) {
                    step++;
                } else {
                    back = 1;
                    step--;
                }
                break;
            case 3:
                for (i = 0; i < 4; i++) {
                    D_800D1F20_main[i] = GwPlayer[i].group;
                }
                func_8010E6F0_mgmode(D_800D4194_main);
                func_8010E1F0_mgmode();
                func_8005B43C_main(D_8011B6A8_mgmode, 0x560B, -1, -1);
                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                    HuPrcVSleep();
                }
                D_800CE29C_main = func_8010F348_mgmode(D_800D4194_main);
                HuPrcSleep(20);
                func_8005B6BC_main(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
                func_8005B43C_main(D_8011B6A8_mgmode, 0x560D, -1, -1);
                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                    HuPrcVSleep();
                }
                func_8005B43C_main(D_8011B6A8_mgmode, 0x560E, -1, -1);
                while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
                    HuPrcVSleep();
                }
                ret = func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0);
                if (ret == -1) {
                    func_8010EE84_mgmode(D_800D4194_main);
                    func_80116D4C_mgmode();
                    D_80119340_mgmode = -1;
                    step -= 2;
                    if (D_800D4194_main == 1 || D_800D4194_main == 2) {
                        step++;
                    }
                    break;
                }
                if (ret == 0) {
                    GwSystem.show_minigame_explanations = 1;
                } else {
                    GwSystem.show_minigame_explanations = 0;
                }
                _SetFlag(0xD);
                for (i = 0; i < 4; i++) {
                    D_800D03FE_main[i] = 0;
                }
                GwSystem.minigame_index = D_800CE29C_main + 1;
                D_800CB894_main = 100;
                omOvlHisChg(0, 0x69, 4, 0x84);
                D_80118EB1_mgmode = 1;
                D_8011B95A_mgmode = 0x70;
                D_8011B950_mgmode = 0;
                D_80118EB4_mgmode = 2;
                if (D_800D4194_main == 0 || D_800D4194_main == 3) {
                    for (i = 0; i < 4; i++) {
                        GwPlayer[i].star = D_800D03FE_main[i];
                        GwPlayer[i].coin = rand8() & 0xF;
                    }
                }
                while (TRUE) {
                    HuPrcVSleep();
                }
        }
    } while (step != 4);
    func_8010D308_mgmode();
    func_80116D4C_mgmode();
    D_80119340_mgmode = -1;
    func_801182B4_mgmode(0);
    func_801168E0_mgmode(D_8011B450_mgmode);
}

void func_8010D308_mgmode(void) {
    f32 scale;
    s16 i;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_8011B450_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
}

s16 func_8010D3B0_mgmode(s32 back) {
    f32 dist;
    s16 i;
    s16 j;
    s16 t;
    s16 cur;
    s16 sel;

    if (back != 0) {
        for (i = 1; i < 6; i++) {
            func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        func_801169C8_mgmode(D_8011B450_mgmode, D_800CC438_main + 1);
    }
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5608, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
        HuPrcVSleep();
    }
    func_80116968_mgmode(D_8011B450_mgmode, 1, 180, 91);
    func_80116968_mgmode(D_8011B450_mgmode, 2, 180, 121);
    func_80116968_mgmode(D_8011B450_mgmode, 3, 180, 151);
    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            t = i - j * 3;
            if (t < 0) {
                func_801169C8_mgmode(D_8011B450_mgmode, j + 1);
            } else if (t < 9) {
                func_801169A0_mgmode(D_8011B450_mgmode, j + 1);
                func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, sindf(t / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    cur = 0;
    func_8011822C_mgmode(D_8011943C_mgmode);
    func_801181F4_mgmode(0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            sel = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (sel != -1) {
                HuAudFXPlay(1);
                func_801182A8_mgmode(sel);
                HuPrcSleep(5);
                cur = sel;
            }
            continue;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
            HuAudFXPlay(2);
            dist = 47 - D_8011944C_mgmode[cur];
            for (i = 1; i < 6; i++) {
                for (j = 0; j < 3; j++) {
                    if (j == cur) {
                        func_80116968_mgmode(D_8011B450_mgmode, cur + 1, 180, D_8011944C_mgmode[j] + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            func_801169C8_mgmode(D_8011B450_mgmode, 1);
            func_801169C8_mgmode(D_8011B450_mgmode, 2);
            func_801169C8_mgmode(D_8011B450_mgmode, 3);
            func_801169A0_mgmode(D_8011B450_mgmode, cur + 1);
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            cur = -1;
            break;
        }
    }
    func_801182B4_mgmode(0);
    HuPrcSleep(5);
    return cur;
}

void func_8010D98C_mgmode(void) {
    s16 t;
    s16 i;
    s16 frame;

    for (frame = 1; frame < 15; frame++) {
        for (i = 0; i < 3; i++) {
            t = frame - (2 - i) * 3;
            if (t >= 0) {
                if (t >= 9) {
                    func_801169C8_mgmode(D_8011B450_mgmode, i + 1);
                } else {
                    func_80116A48_mgmode(D_8011B450_mgmode, i + 1, 1.0f, cosdf(t / 8.0f * 90.0f));
                }
            }
        }
        HuPrcVSleep();
    }
}

/* NON_MATCHING: masked 0 except register allocation and a frame 8 bytes smaller than retail's. */
#ifdef NON_MATCHING
s16 func_8010DAB8_mgmode(s32 back) {
    f32 dist;
    s16 cur;
    s16 t;
    s16 j;
    s16 i;

    if (back != 0) {
        for (i = 1; i < 6; i++) {
            func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        func_801169C8_mgmode(D_8011B450_mgmode, D_800D4194_main + 4);
    }
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5609, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode)) {
        HuPrcVSleep();
    }
    for (i = 1; i <= D_8011B454_mgmode * 3 + 8; i++) {
        for (j = 0; j < D_8011B454_mgmode; j++) {
            func_80116968_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 180, j * 22 + 79);
            t = i - j * 3;
            if (t < 0) {
                func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4);
            } else if (t < 9) {
                func_801169A0_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4);
                func_80116A48_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 1.0f, sindf(t / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < D_8011B454_mgmode; i++) {
        D_8011B468_mgmode[i] = D_80119454_mgmode[i];
    }
    D_8011B468_mgmode[i].x = -1;
    D_8011B468_mgmode[i].y = -1;
    cur = 0;
    func_8011822C_mgmode(D_8011B468_mgmode);
    func_801181F4_mgmode(0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            t = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (t != -1) {
                HuAudFXPlay(1);
                func_801182A8_mgmode(t);
                HuPrcSleep(5);
                cur = t;
            }
            continue;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
            HuAudFXPlay(2);
            dist = -9 - cur * 22;
            for (i = 1; i < 6; i++) {
                for (j = 0; j < D_8011B454_mgmode; j++) {
                    if (j == cur) {
                        func_80116968_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 180,
                                             (j * 22 + 79) + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        func_80116A48_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 1.0f, cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            for (i = 0; i < 5; i++) {
                func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[i] + 4);
            }
            func_801169A0_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[cur] + 4);
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            cur = -1;
            break;
        }
    }
    func_801182B4_mgmode(0);
    HuPrcSleep(5);
    return cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010DAB8_mgmode);
#endif

void func_8010E1F0_mgmode(void) {
    s16 list[20];
    s16 n;
    s16 i;
    s16 tmp;
    s16 j;
    s16 k;
    s16 ev;

    ev = D_800D4194_main;
    n = 0;
    for (i = 0; i < D_8011B940_mgmode[ev]; i++) {
        if (D_8011B6B0_mgmode[ev][i] != 0xFF) {
            list[n++] = D_8011B6B0_mgmode[ev][i];
        }
    }
    for (i = 0; i < n * 2; i++) {
        j = i % n;
        k = (rand8() * n) >> 8;
        tmp = list[j];
        list[j] = list[k];
        list[k] = tmp;
    }
    for (i = 0; i < D_8011B928_mgmode[ev]; i++) {
        D_800D0418_main[i] = list[i];
    }
}

void func_8010E40C_mgmode(void) {
    s16 i;

    for (i = 0; i < D_8011B454_mgmode; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[i] + 4);
    }
}

/* NON_MATCHING: masked 0; register allocation only (n in t1 for t0, g's zero not copied from k's). */
#ifdef NON_MATCHING
void func_8010E494_mgmode(s16 mode) {
    Vec pos[4];
    s16 grp[4];
    s16 n;
    s16 i;
    s16 k;
    s16 g;

    n = 2;
    if (mode != 4) {
        n = 4;
    }
    for (i = 0; i < n; i++) {
        grp[i] = D_800D1F20_main[i];
    }
    g = k = 0;
    for (; g < n || k < n; g++) {
        for (i = 0; i < n; i++) {
            if (g == grp[i]) {
                pos[i].x = k * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                grp[i] = -1;
                k++;
            }
        }
    }
    for (i = 0; i < n; i++) {
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8B6_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
        func_8001C258_main(D_8011B8E8_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8E8_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E494_mgmode);
#endif

/* NON_MATCHING: register allocation (retail spills n and keeps the model-array bases in s7/s8), 5 instructions over. */
#ifdef NON_MATCHING
void func_8010E6F0_mgmode(s16 mode) {
    Vec pos[4];
    Vec dir[4];
    s16 grp[4];
    f32 rotY[4];
    s16 n;
    MgHmfPart *head;
    f32 tilt;
    f32 s;
    s16 i;
    s16 k;
    s16 g;
    s16 t;
    s16 m;

    tilt = 0.0f;
    n = 2;
    if (mode != 4) {
        n = 4;
    }
    for (i = 0; i < n; i++) {
        grp[i] = D_800D1F20_main[i];
    }
    g = k = 0;
    for (; g < n || k < n; g++) {
        for (i = 0; i < n; i++) {
            if (g == grp[i]) {
                pos[i].x = k * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                grp[i] = -1;
                k++;
            }
        }
    }
    for (i = 0; i < n; i++) {
        dir[i].x = 400.0f - pos[i].x;
        dir[i].z = 900.0f - pos[i].z;
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 0);
        func_8001F304_main(D_8011B8B6_mgmode[i], D_8011B796_mgmode[i]);
        func_8001C814_main(D_8011B8B6_mgmode[i], 2, 2);
        func_8001C258_main(D_8011B8E8_mgmode[i], 4, 0);
        rotY[i] = atan2df(dir[i].x, dir[i].z) + 180.0f;
        Hu3DModelRotSet(D_8011B8B6_mgmode[i], 0.0f, rotY[i], 0.0f);
    }
    m = D_8011B8A8_mgmode[4];
    func_8002FD8C_main(m, HmfModelData[m].unk02, "c100_1-atama", 0x4C, 0x46);
    head = func_8001D33C_main(m, "c100_1-atama");
    for (t = 0; t < 31; t++) {
        s = 1.0f - sindf(t * 3.0f);
        for (i = 0; i < n; i++) {
            /* retail moves both x and z by the x distance */
            Hu3DModelPosSet(D_8011B8B6_mgmode[i], s * dir[i].x + pos[i].x, pos[i].y, s * dir[i].x + pos[i].z);
            func_80118624_mgmode(D_8011B8E8_mgmode[i], D_8011B8B6_mgmode[i]);
            if (t < 25 && t % 5 == 0) {
                func_8004AC5C_main(GwPlayer[i].chr + 0x29, i);
            }
        }
        if (t < 10) {
            tilt = (atan2df(HmfModelData[D_8011B8A8_mgmode[7]].pos.x - HmfModelData[D_8011B8A8_mgmode[4]].pos.x,
                            HmfModelData[D_8011B8A8_mgmode[7]].pos.z - HmfModelData[D_8011B8A8_mgmode[4]].pos.z) -
                    HmfModelData[D_8011B8A8_mgmode[4]].rot.y) * (t / 10.0f);
        } else if (t < 20) {
            tilt = atan2df(HmfModelData[D_8011B8A8_mgmode[7]].pos.x - HmfModelData[D_8011B8A8_mgmode[4]].pos.x,
                           HmfModelData[D_8011B8A8_mgmode[7]].pos.z - HmfModelData[D_8011B8A8_mgmode[4]].pos.z) -
                   HmfModelData[D_8011B8A8_mgmode[4]].rot.y;
        } else {
            tilt -= 5.0f;
        }
        head->unk38 = tilt;
        head->unk14 = tilt;
        HuPrcVSleep();
    }
    for (i = 0; i < n; i++) {
        func_8001C624_main(D_8011B8B6_mgmode[i], D_8011B78E_mgmode[i], 0, 8, 2);
    }
    for (t = 0; t < 9; t++) {
        for (i = 0; i < n; i++) {
            Hu3DModelRotSet(D_8011B8B6_mgmode[i], 0.0f, (1.0f - t / 8.0f) * rotY[i], 0.0f);
        }
        tilt -= 5.0f;
        if (tilt < 0.0f) {
            tilt = 0.0f;
        }
        head->unk38 = tilt;
        head->unk14 = tilt;
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E6F0_mgmode);
#endif

/* NON_MATCHING: masked 7; register allocation and the shadow-model address formed differently. */
#ifdef NON_MATCHING
void func_8010EE84_mgmode(s16 mode) {
    Vec pos[4];
    Vec dir[4];
    f32 rotY[4];
    f32 s;
    Vec *p;
    Vec *d;
    s16 *m;
    s16 *m2;
    s16 n;
    s16 i;
    s16 t;

    n = 2;
    if (mode != 4) {
        n = 4;
    }
    for (i = 0; i < n; i++) {
        pos[i].x = HmfModelData[D_8011B8B6_mgmode[i]].pos.x;
        pos[i].y = HmfModelData[D_8011B8B6_mgmode[i]].pos.y;
        pos[i].z = HmfModelData[D_8011B8B6_mgmode[i]].pos.z;
        dir[i].x = 400.0f - pos[i].x;
        dir[i].z = 900.0f - pos[i].z;
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 0);
        func_8001C624_main(D_8011B8B6_mgmode[i], D_8011B796_mgmode[i], 0, 8, 2);
        rotY[i] = atan2df(dir[i].x, dir[i].z);
    }
    for (t = 0; t < 9; t++) {
        s = t / 8.0f;
        for (i = 0; i < n; i++) {
            Hu3DModelRotSet(D_8011B8B6_mgmode[i], 0.0f, s * rotY[i], 0.0f);
        }
        HuPrcVSleep();
    }
    for (t = 0; t < 31; t++) {
        if (t == 10) {
            func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B78C_mgmode, 0, 8, 2);
        }
        s = 1.0f - sindf(t / 30.0f * 90.0f + 90.0f);
        for (i = 0; i < n; i++) {
            m = &D_8011B8B6_mgmode[i];
            p = &pos[i];
            d = &dir[i];
            Hu3DModelPosSet(*m, s * d->x + p->x, p->y, s * d->z + p->z);
            m2 = &D_8011B8E8_mgmode[i];
            func_80118624_mgmode(*m2, *m);
            if (t < 25 && t % 5 == 0) {
                func_8004AC5C_main(GwPlayer[i].chr + 0x29, i);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < n; i++) {
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 4);
        func_8001C258_main(D_8011B8E8_mgmode[i], 4, 4);
    }
    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010EE84_mgmode);
#endif

/* NON_MATCHING: one register (list[] indexed through prev's copy of sel). */
#ifdef NON_MATCHING
s16 func_8010F348_mgmode(s16 ev) {
    s16 list[32];
    s16 i;
    s16 n;
    s16 sel;
    s16 prev;

    if (D_80119340_mgmode == -1) {
        D_80119340_mgmode = func_80116B20_mgmode();
        func_8000BC48_main(D_80119340_mgmode, 0x4008);
        func_8000BBD4_main(D_80119340_mgmode, 180, 134);
        for (i = 0; i < 10; i++) {
            func_8000BBFC_main(D_80119340_mgmode, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    n = 0;
    for (i = 0; i < D_8011B940_mgmode[ev]; i++) {
        if (D_8011B6B0_mgmode[ev][i] != 0xFF) {
            list[n++] = D_8011B6B0_mgmode[ev][i];
        }
    }
    prev = -1;
    sel = (rand8() * n) >> 8;
    func_80116C18_mgmode(D_800A6D46_main[list[sel]].unk00 & 0x7FF);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        while (sel == prev) {
            sel = (rand8() * n) >> 8;
        }
        prev = sel;
        func_80116C18_mgmode(D_800A6D46_main[list[sel]].unk00 & 0x7FF);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    prev = D_800D0418_main[D_800D1F2C_main];
    func_80116C18_mgmode(D_800A6D46_main[prev].unk00 & 0x7FF);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return prev;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F648_mgmode);

u8 func_80110420_mgmode(s16 mg) {
    s16 i;

    D_8011B434_mgmode = 0;
    if (D_800A6D44_main[mg].minigameType != 3) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin + GwPlayer[i].gameCoin >= 10) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin == 0) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    }
    return D_8011B434_mgmode;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110554_mgmode);

/* NON_MATCHING: masked 29: GCC forms the sound id with a store-flag sequence where retail branches,
 * and case 4 shares the spr[n] address (retail computes it twice); register allocation. */
#ifdef NON_MATCHING
s32 func_80111380_mgmode(void) {
    u16 spr[4];
    f32 alpha;
    f32 scale;
    s16 i;
    s16 n;
    s32 y;
    s16 t;
    s32 se;
    u16 *ptr;
    s16 mask;
    s16 p;

    n = 0;
    if (D_8011B434_mgmode == 0) {
        return 0;
    }
    switch (D_800D4194_main) {
        case 0:
        case 3:
            for (i = 0; i < D_8011B434_mgmode; i++) {
                p = D_8011B430_mgmode[i];
                spr[i] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                n++;
                func_8000BB54_main(spr[i]);
                func_8000BBD4_main(spr[i], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[p]] + 180, p * 24 + 80);
                D_8011B4C0_mgmode++;
            }
            break;
        case 1:
            mask = 0;
            for (i = 0; i < D_8011B434_mgmode; i++) {
                p = D_8011B430_mgmode[i];
                if (!((mask >> D_800D1F20_main[p]) & 1)) {
                    mask |= 1 << D_800D1F20_main[p];
                    spr[n] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                    func_8000BB54_main(spr[n]);
                    func_8000BBD4_main(spr[n], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[p]] + 180,
                                       D_800D1F20_main[p] * 48 + 93);
                    n++;
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 2:
            mask = 0;
            for (i = 0; i < D_8011B434_mgmode; i++) {
                p = D_8011B430_mgmode[i];
                if (!((mask >> D_800D1F20_main[p]) & 1)) {
                    mask |= 1 << D_800D1F20_main[p];
                    spr[n] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                    y = 128;
                    if (D_800D1F20_main[p] == 0) {
                        y = 80;
                    }
                    func_8000BB54_main(spr[n]);
                    func_8000BBD4_main(spr[n], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[p]] + 180, y);
                    n++;
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 4:
            for (i = 0; i < D_8011B434_mgmode; i++) {
                p = D_8011B430_mgmode[i];
                spr[n] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                ptr = &spr[n];
                n++;
                func_8000BB54_main(*ptr);
                func_8000BBD4_main(*ptr, D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[p]] + 180, p * 24 + 104);
                D_8011B4C0_mgmode++;
            }
            break;
    }
    for (i = 0; i < D_8011B434_mgmode; i++) {
        D_800D03FE_main[D_8011B430_mgmode[i]]++;
    }
    D_8011B434_mgmode = 0;
    for (i = 0; i < 4; i++) {
        if (D_800D03FE_main[i] >= D_80119430_mgmode[D_800CC438_main]) {
            D_8011B430_mgmode[D_8011B434_mgmode] = i;
            D_8011B434_mgmode++;
            if (!(GwPlayer[i].stat & 1)) {
                RepeatVibrator(GwPlayer[i].pad, 10, 0, 10);
            }
        }
    }
    se = 0x24A;
    if (D_8011B434_mgmode != 0) {
        se = 0x24B;
    }
    HuAudFXPlay(se);
    for (t = 0; t < 31; t++) {
        alpha = sindf(t * 3.0f) * 255.0f;
        scale = 2.0f * sindf(t * 5.0f);
        for (i = 0; i < n; i++) {
            func_8000BBFC_main(spr[i], alpha);
            func_8000BE5C_main(spr[i], scale, scale);
        }
        HuPrcVSleep();
    }
    return D_8011B434_mgmode != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);
#endif

s32 func_80111B08_mgmode(void) {
    s16 i;

    func_80110420_mgmode(D_800CE29C_main);
    for (i = 0; i < D_8011B434_mgmode; i++) {
        if (D_800D03FE_main[D_8011B430_mgmode[i]] + 1 >= D_80119430_mgmode[D_800CC438_main]) {
            return 1;
        }
    }
    return 0;
}

void func_80111BB0_mgmode(void) {
    f32 scale;
    s16 i;
    s16 j;
    s16 alpha;

    for (j = 0; j < 28; j++) {
        func_8000BE5C_main(D_8011B488_mgmode[j], 0.0f, 0.0f);
    }
    for (j = 0; j < 4; j++) {
        func_80116A78_mgmode(D_8011B480_mgmode, j + 5, 0);
    }
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            func_80116A78_mgmode(D_8011B480_mgmode, j + 5, (1.0 - i / 5.0) * 255.0);
        }
        for (j = 0, scale = 1.0 - i / 5.0; j < 28; j++) {
            func_8000BE5C_main(D_8011B488_mgmode[j], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            func_80116A78_mgmode(D_8011B480_mgmode, j + 1, (1.0 - i / 5.0) * 255.0);
        }
        func_80116A78_mgmode(D_8011B480_mgmode, 0, (1.0 - i / 5.0) * 192.0);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_8011B480_mgmode);
    for (j = 0; j < 28; j++) {
        func_8000C184_main(D_8011B488_mgmode[j]);
    }
    HuSprKill(D_8011B484_mgmode);
}

void func_80111ED8_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80111F9C_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80112060_mgmode(s32 on) {
    s16 grp[4];
    s16 i;
    s16 j;
    s16 g;
    s16 k;

    for (i = 0; i < 4; i++) {
        grp[i] = D_800D1F20_main[i];
    }
    k = 0;
    for (g = 0; g < 4; g++) {
        for (i = 0; i < 4; i++) {
            if (g == grp[i]) {
                for (j = 0; j < D_8011B434_mgmode; j++) {
                    if (D_8011B430_mgmode[j] == i) {
                        break;
                    }
                }
                if (j != D_8011B434_mgmode) {
                    if (on) {
                        func_80118888_mgmode(k);
                    } else {
                        func_801188A4_mgmode(k);
                    }
                    grp[i] = -1;
                }
                k++;
            }
        }
    }
}
