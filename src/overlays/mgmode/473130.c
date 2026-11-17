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
    /* 0x00 */ char unk_00[0x58];
    /* 0x58 */ MgMtx mtx;
} MgHmfPart;

void func_8000BB54_main(u16 arg0);
void func_8000BB94_main(u16 arg0);
void func_8000BBD4_main(u16 spriteId, s16 x, s16 y);
void func_8000BBFC_main(u16, u8);
void func_8000BC48_main(u16, u16);
void func_8000BCC8_main(u16, s32);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
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

/* other mgmode units */
void func_8011667C_mgmode(MgModelDesc *desc);
void func_80116E24_mgmode(s16 arg0);
void func_80116ED4_mgmode(s16 arg0, s16 arg1, s16 arg2, void (*arg3)(s16 *));
void func_801181F4_mgmode(s16 arg0);
void func_8011822C_mgmode(void *arg0);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
void func_801182B4_mgmode(s16 arg0);
s16 func_80118678_mgmode(f32 arg0, f32 arg1, f32 arg2, f32 arg3);

#define MG_NOFUNC ((void (*)(s16 *))-1)

extern u8 D_80118EB1_mgmode;
extern s16 D_80118EB4_mgmode;
extern u8 D_80119344_mgmode[];
extern u8 D_80119424_mgmode[];
extern u8 D_80119434_mgmode[];
extern MgModelDesc D_8011997C_mgmode[];
extern MgModelDesc D_80119A78_mgmode[]; /* D_8011997C_mgmode[7] */
extern MgMtx D_8011B3F0_mgmode;
extern s16 D_8011B436_mgmode[4];
extern s16 D_8011B43E_mgmode[4];
extern s16 D_8011B446_mgmode[4];
extern s16 D_8011B6A8_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_8011B78A_mgmode;
extern s16 D_8011B808_mgmode;
extern s16 D_8011B884_mgmode;
extern f32 D_8011B888_mgmode;
extern u16 D_8011B8A8_mgmode[];
extern u16 D_8011B8B0_mgmode;
extern u16 D_8011B8B6_mgmode[];
extern void *D_8011B954_mgmode;
extern u8 D_8011B958_mgmode;

s32 func_8010F648_mgmode(void);
void func_8010CB20_mgmode(void);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010CB20_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010CBFC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D308_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D3B0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D98C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010DAB8_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E1F0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E494_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E6F0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010EE84_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F648_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110420_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110554_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111B08_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111BB0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111ED8_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111F9C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80112060_mgmode);
