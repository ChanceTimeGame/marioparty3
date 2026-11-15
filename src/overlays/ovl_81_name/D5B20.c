#include "common.h"
#include "ovl_81.h"

// duel n6: D5B20 local types and declarations (from ovl_80_shared_board)
typedef struct UnkUserData {
    Object* obj;
    f32 unk_04;
    f32 unk_08;
    f32 velocity;
} UnkUserData;

typedef struct UnkSharedBoard {
    s32 playerNo;
    s32 unk_04;
    char unk_08[8];
} UnkSharedBoard; //sizeof 0x10

typedef struct UnkPauseMesWork {
    /* 0x00 */ s32 *mes;
    /* 0x04 */ u16 unk_04;
} UnkPauseMesWork;

extern s32 D_800A12C0_main;
extern s32 D_800A12C4_main;
extern s8 D_800A176D_main;
extern s16 D_800D10F2_main;
extern s32 D_801011F0_name_81;
extern s32 D_801011FC_name_81;
extern s32 D_80101220_name_81;
extern s16 D_80101248_name_81;
extern s16 D_8010124A_name_81;
extern s32 D_8010124C_name_81;
extern s32 D_80101250_name_81;
extern u8 D_80101254_name_81[][3];
extern s32 D_80101260_name_81[];
extern s32 D_801012AC_name_81[];
extern s32 D_801012B4_name_81[];
extern s32 D_801012BC_name_81[];
extern s32 D_801012C8_name_81[];
extern s32 D_801012D4_name_81[];
extern s32 D_801012E0_name_81;
extern s32 D_801012E4_name_81;
extern s32 D_801012E8_name_81;
extern s32 D_8010128C_name_81[];
extern s32 D_8010126C_name_81[];
extern s32 D_801012EC_name_81[];
extern u8 D_80101370_name_81[];
extern u32 D_80101374_name_81[]; // count, then the ids (splat also labels +4 as D_80101378)
extern s16 D_80101348_name_81[];
extern s16 D_8010134C_name_81[];
extern s32 D_801012F4_name_81[];
extern s32 D_80101314_name_81[];
extern s8 D_80101338_name_81[];
extern s8 D_80101340_name_81[];
extern s16 D_80101350_name_81[][4];
extern s32 *D_80101494_name_81[];
extern u8 D_801014B4_name_81[];
extern u8 D_801014BC_name_81[];
extern UnkMBGuideData* D_801053E0_name_81;
extern s16 D_801053E4_name_81;
extern s16 D_801053E6_name_81;
extern s32 D_801053E8_name_81;
extern s16 D_801053EA_name_81;
extern s32 D_801053EC_name_81;
extern s16 D_801053EE_name_81;
extern s16 D_801053F0_name_81[];
extern s16 D_801053F4_name_81;
extern UnkBoard D_80105560_name_81[16];

u16 func_800D9234_name_81(Object* arg0);
void func_800E4EAC_name_81(UnkMBGuideData* arg0, s16 arg1, s16 arg2);
s32 func_800F73AC_name_81(void);
void func_800F3B54_name_81(s32 playerNo, u8 arg1);
UnkMBGuideData* func_800E4B64_name_81(s32 arg0, s32 arg1);
void func_800E4E64_name_81(UnkMBGuideData* arg0);
void func_800D8944_name_81(Object* arg0);
void func_800E9180_name_81(void);
void func_800E9190_name_81(void);
void Duel_ClearPartnerObjects(void);
void func_800D898C_name_81(Object* arg0, u8 arg1);
void func_800F3EC0_name_81(s16 playerNo);
void func_800EDFAC_name_81(void);
void func_800EE114_name_81(void);
static void func_800EED5C_name_81(s32 arg0);
static void func_800EEDA0_name_81(s32, s32, s32);
static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800EF3F8_name_81(s32 arg0, s32 arg1);
s32 func_800EFEC8_name_81(Object* arg0, Vec* arg1, f32 arg2, Vec* arg3);
void func_800EB708_name_81(Vec* arg0, Vec* arg1, Vec* arg2);
UnkBoard4* func_800F08BC_name_81(void);
s32 func_800F1784_name_81(s32 arg0);
s32 func_800F2618_name_81(s32 arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDD50_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDDBC_name_81);

static void func_800EDE1C_name_81(void) {
    UnkUserData* temp_v0 = HuPrcCurrentGet()->user_data;
    Object* temp_s0 = temp_v0->obj;
    f32 temp_f28 = temp_v0->unk_04;
    f32 temp_f26 = temp_v0->unk_08;
    f32 temp_f24 = temp_v0->velocity;
    f32 var_f20 = 0.0f;

    while (1) {
        f32 temp_f0 = temp_f24 - (sindf(var_f20) * temp_f26);
        var_f20 += temp_f28;
        temp_s0->velocity.x = temp_f0;
        if (var_f20 >= 360.0f) {
            var_f20 -= 360.0f;
        }
        HuPrcVSleep();        
    }
}

Process* func_800EDEC4_name_81(Object* arg0, f32 arg1, f32 arg2) {
    Process* temp_v0 = omAddPrcObj(func_800EDE1C_name_81, 0xA, 0, 0x40);
    UnkUserData* temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkUserData));

    temp_v0->user_data = temp_v0_2;
    temp_v0_2->obj = arg0;
    temp_v0_2->unk_04 = arg1;
    temp_v0_2->unk_08 = arg2;
    temp_v0_2->velocity = arg0->velocity.x;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDF48_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDF78_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDFAC_name_81);

void func_800EE0D0_name_81(void) {
    D_801011FC_name_81 = 1;
    func_800EDFAC_name_81();
}

void func_800EE0F4_name_81(void) {
    D_801011FC_name_81 = 0;
    func_800EDFAC_name_81();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE114_name_81);

Process* func_800EE40C_name_81(s32 playerNo) {
    Process* proc = omAddPrcObj(func_800EE114_name_81, 0xA, 0, 0x40);
    UnkSharedBoard* temp_v0_2 = HuMemMemoryAlloc(proc->heap, sizeof(UnkSharedBoard));

    proc->user_data = temp_v0_2;
    temp_v0_2->playerNo = playerNo;
    return proc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE468_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE74C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EEC40_name_81);

s32 func_800EED24_name_81(void) {
    return D_801011F0_name_81;
}

void func_800EED30_name_81(s32 arg0) {
    D_800A12C4_main = arg0;
    func_800EED5C_name_81(arg0);
}

s32 func_800EED50_name_81(void) {
    return D_800A12C4_main;
}

void func_800EED5C_name_81(s32 arg0) {
    D_800A12C0_main = arg0;
}

// retail takes an s32 window id (no sign extension); ovl_81.h declares s16, which DFD60's
// caller needs to match (see n6.header.patch)
#ifdef NON_MATCHING
void func_800EED68_name_81(s16 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED68_name_81);
#endif

void func_800EED84_name_81(s32 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 1);
}

static void func_800EEDA0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp18[MB_MAX_PLAYERS];
    s32 hasCom = 0;
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 sp2C;
    s32 i;

    hasCom = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg1) {
            if (GwPlayer[i].stat & 1) {
                hasCom = 1;
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                func_8005FE54_main(arg0, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (hasCom != 0) {
        func_8005B63C_main(arg0, 2, 2);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    if (arg2 == 0) {
        while (func_8005E0C0_main(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((func_8005E0C0_main(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        D_800CC69C_main[arg0].unk20 = 7;
    }
    func_8005F904_main();
}

void func_800EF0A0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 0);
}

void func_800EF0BC_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 1);
}

static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i == arg1) || (i == arg2)) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (mask) {
        func_8005FE54_main(arg0, mask);
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    } else {
        func_8005B63C_main(arg0, 2, 2);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    }

    if (arg3 == 0) {
        while (func_8005E0C0_main(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((func_8005E0C0_main(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        D_800CC69C_main[arg0].unk20 = 7;
    }
    func_8005F904_main();
}

// retail takes an s32 window id (no sign extension); ovl_81.h declares s16, which DFD60's
// caller needs to match (see n6.header.patch)
#ifdef NON_MATCHING
void func_800EF3B4_name_81(s16 arg0) {
    func_800EF3F8_name_81(arg0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF3B4_name_81);
#endif

void func_800EF3D0_name_81(s32 arg0) {
    func_800EF3F8_name_81(arg0, 1);
}

void func_800EF3EC_name_81(s32 arg0) {
    D_80101220_name_81 = arg0;
}

void func_800EF3F8_name_81(s32 arg0, s32 arg1) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    u8 sp24[1]; // unused; sizes the frame as retail
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < D_80101220_name_81; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == D_80101220_name_81) {
        func_8005B63C_main(arg0, 2, 2);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
        if (arg1 == 0) {
            while (func_8005E0C0_main(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((func_8005E0C0_main(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            D_800CC69C_main[arg0].unk20 = 7;
        }
    } else {
        for (i = 0; i < D_80101220_name_81; i++) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = 0;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        }
        func_8005FE54_main(arg0, mask);
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
        if (arg1 == 0) {
            while (func_8005E0C0_main(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((func_8005E0C0_main(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            D_800CC69C_main[arg0].unk20 = 7;
        }
    }
    func_8005F904_main();
}

void func_800EF754_name_81(s32 arg0) {
    func_8005FE54_main(arg0, 0xF);
    func_8005F744_main(-1, -1, -1, -1);
    while ((func_8005E0C0_main(arg0)) != 0) {
        HuPrcVSleep();
    }
    func_8005F904_main();
}

void func_800EF7C8_name_81(Object* arg0, f32 arg1, f32 arg2) {
    arg0->velocity.y = arg1;
    arg0->velocity.z = arg2;
}

s32 func_800EF7D4_name_81(Object* arg0) {
    if (arg0->velocity.z == 0.0f) {
        return 0;
    } else {
        return 1;
    }
}

void func_800EF800_name_81(Object* arg0) {
    while (func_800EF7D4_name_81(arg0) != 0) {
        HuPrcVSleep();
    }
}

void func_800EF840_name_81(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80105560_name_81); i++) {
        D_80105560_name_81[i].unk_04 = NULL;
        D_80105560_name_81[i].unk_08 = NULL;
    }
}

void func_800EF880_name_81(void) {
    UnkBoard* temp_s1;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80105560_name_81); i++) {
        temp_s1 = &D_80105560_name_81[i];
        if (temp_s1->unk_08 != NULL) {
            omDelObj(temp_s1->unk_08);
            temp_s1->unk_08 = NULL;
        }
    }
}

static void func_800EF8EC_name_81(omObjData *func) {
    UnkBoard *temp_s0;

    temp_s0 = &D_80105560_name_81[func->work[0]];
    if (HmfModelData[temp_s0->unk_04->omObj1->model[0]].unk40 ==
        D_800CCF58_main[HmfModelData[temp_s0->unk_04->omObj1->model[0]].unk02].unk02) {
        func_800D918C_name_81(temp_s0->unk_04, temp_s0->unk_00, 0, 0xA, (u16)temp_s0->unk_02);
        temp_s0->unk_04 = NULL;
        temp_s0->unk_08 = NULL;
        omDelObj(func);
    }
}

u32 func_800EF9C4_name_81(Object *arg0, s16 arg1, s16 arg2) {
    omObjData *obj;
    UnkBoard *temp_s1;
    s32 i;
    s32 ret;

    for (i = 0; i < ARRAY_COUNT(D_80105560_name_81); i++) {
        temp_s1 = &D_80105560_name_81[i];
        if (temp_s1->unk_08 == NULL) {
            break;
        }
    }

    if (i != ARRAY_COUNT(D_80105560_name_81)) {
        obj = omAddObj(0x2000, 0, 0, -1, func_800EF8EC_name_81);
        temp_s1->unk_08 = obj;
        obj->work[0] = i;
        temp_s1->unk_04 = arg0;
        temp_s1->unk_00 = arg1;
        temp_s1->unk_02 = arg2;
        ret = i;
    } else {
        ret = -1;
    }
    return ret;
}

void func_800EFA8C_name_81(Object *arg0, s16 arg1, u16 arg2) {
    func_800D918C_name_81(arg0, arg1, 0, 0xA, arg2);
}

void func_800EFABC_name_81(Object *arg0) {
    while (!(func_800D9234_name_81(arg0) & 1)) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFB00_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFB3C_name_81);

s32 func_800EFBE8_name_81(s32 arg0) {
    return GwPlayer[arg0].star * 1000 + GwPlayer[arg0].coin;
}

void func_800EFC28_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MBD_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) &&
                (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MBD_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

void func_800EFD24_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MB_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) &&
                (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MB_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

s32 func_800EFE20_name_81(f32 arg0) { // 800EEF80 in party mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

s32 func_800EFE8C_name_81(Object* arg0, Vec* arg1, f32 arg2) {
    return func_800EFEC8_name_81(arg0, arg1, arg2, &arg0->rot);
}

s32 func_800EFEAC_name_81(Object* arg0, Vec* arg1, f32 arg2) {
    Vec dir;

    return func_800EFEC8_name_81(arg0, arg1, arg2, &dir);
}

// Moves arg0 toward arg1 by arg2; arg3 receives the unit direction. Returns 1 on arrival.
s32 func_800EFEC8_name_81(Object* arg0, Vec* arg1, f32 arg2, Vec* arg3) {
    f32 dist = HuVecDistance(&arg0->coords, arg1);
    Vec* pos;

    if (dist == 0.0f) {
        return 1;
    }
    pos = &arg0->coords;
    func_800EB708_name_81(pos, arg1, arg3);
    if (arg2 <= dist) {
        arg0->coords.x = arg2 * arg3->x + arg0->coords.x;
        arg0->coords.y = arg2 * arg3->y + arg0->coords.y;
        arg0->coords.z = arg2 * arg3->z + arg0->coords.z;
        return 0;
    } else {
        HuVecCopy3F(pos, arg1);
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFFBC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F001C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F008C_name_81);


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0208_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0378_name_81);

void func_800F03C8_name_81(s16 arg0) {
    func_8001C258_main(arg0, 0x4000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F03F0_name_81);

void func_800F0480_name_81(Object *arg0, s16 arg1, s16 arg2, s32 arg3) {
    arg0->omObj1->work[0] = (u8)func_80017790_main(arg0->omObj1->model[0], arg1, arg2, arg3);
    arg0->omObj1->work[1] = (u8)arg1;
    arg0->omObj1->work[2] = (u8)arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F04FC_name_81);

void func_800F05AC_name_81(void) {
}

void func_800F05B4_name_81(Object* arg0, s32 arg1) {
    func_800333B0_main(arg0->omObj1->work[0]);
    arg0->omObj1->work[0] = func_80017AD8_main(arg1);
    func_80017954_main(arg0->omObj1->model[0], arg0->omObj1->work[1], arg0->omObj1->work[2], arg0->omObj1->work[0]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F061C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06D4_name_81);

s32 func_800F0700_name_81(s32 arg0) {
    return arg0;
}

static void func_800F0708_name_81(UnkBoard4* arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    u8 temp_s0;
    void* temp_s5;
    s32 i;

    temp_s5 = DataRead(0x13008A);
    sprintf(D_800D5218_main, "%2d", arg2);
    
    for (i = 0; i < 2; i++) {
        temp_s0 = D_800D5218_main[i];
        arg0->unk_0C[arg1] = func_80055810_main(temp_s5);
        if (temp_s0 != 0x20) {
            func_80055024_main(arg0->unk_0A, arg1, arg0->unk_0C[arg1], temp_s0 - 0x30);
        } else {
            func_80055024_main(arg0->unk_0A, arg1, arg0->unk_0C[arg1], 0xA);
        }
        
        HuSprPriSet(arg0->unk_0A, arg1, 7);
        HuSprAttrSet(arg0->unk_0A, arg1, 0x01001000);
        func_80054904_main(arg0->unk_0A, arg1, arg3, arg4);
        func_80055420_main(arg0->unk_0A, arg1, D_80101254_name_81[D_80101250_name_81][0], D_80101254_name_81[D_80101250_name_81][1], D_80101254_name_81[D_80101250_name_81][2]);
        arg1 += 1;
        arg3 += 0xE;        
    }
    DataClose(temp_s5);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F08BC_name_81);

static void func_800F0C30_name_81(UnkBoard4* arg0) {
    func_800F4584_name_81(arg0);
}

static s16 func_800F0C4C_name_81(s32 arg0) {
    s32 temp_s2;
    s32 temp_s3;
    s16 var_s0;
    UnkBoard4* temp_s1;

    temp_s3 = func_800E1824_name_81(0xA, 0xAE, 0);
    temp_s2 = func_800E1824_name_81(5, 0xBC, 0);
    temp_s1 = func_800F08BC_name_81();
    HuPrcVSleep();

    while (1) {
        HuPrcVSleep();
        if (D_800D5558_main[arg0] & 0x8000) {
            var_s0 = 4;
            break;
        } else if (D_800D5558_main[arg0] & 0x1000) {
            var_s0 = 0;
            break;
        }       
    }

    func_800F0C30_name_81(temp_s1);
    func_800E1854_name_81(temp_s3);
    func_800E1854_name_81(temp_s2);
    return var_s0;
}

static void func_800F0D1C_name_81(UnkMBGuideData* arg0, s16 arg1) {
    s32 i;
    Object* obj;
    s16 temp_s2;
    s16 temp = arg0->spriteGroup;
    
    obj = arg0->obj;
    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    temp_s2 = (arg1 - temp) / 14;

    for (i = 0; i < 14; i++) {
        temp = arg0->spriteGroup;
        func_800E4EAC_name_81(arg0, (temp + temp_s2), 8);
        HuPrcVSleep();        
    }
    func_800E4EAC_name_81(arg0, arg1, 8);
}

static void func_800F0DF8_name_81(s16 arg0, s32 arg1) {
    func_8005D294_main(arg0);
    func_8005B43C_main(arg0, func_800F0700_name_81(arg1), -1, -1);
}

static void func_800F0E4C_name_81(s32 arg0, s16 arg1) {
    func_8005D294_main(arg0);
    func_8005B43C_main(arg0, D_80101260_name_81[arg1], -2, -2);
}

static s32 func_800F0EA8_name_81(s16 arg0, s16 arg1, s16 arg2) {
    s16 sp18[2];
    s16 sp20[2];
    s32 win;

    func_80060394_main(1, sp18, D_80101260_name_81[0]);
    func_80060394_main(1, sp20, D_80101260_name_81[1]);

    if (sp20[0] > sp18[0]) {
        D_801053F0_name_81[0] = sp20[0];
    } else {
        D_801053F0_name_81[0] = sp18[0];
    }
    D_801053F0_name_81[1] = sp18[1];
    arg1 += 0xA0;
    win = func_8005A968_main(arg1 - (D_801053F0_name_81[0] / 2), arg2,
                              D_801053F0_name_81[0], D_801053F0_name_81[1], 0, 4);
    func_8005BE30_main(win, 9);
    func_8005BEE0_main(win, 0);
    func_8005BDFC_main(win, 0);
    func_8005B63C_main(win, 0, 0x20000);
    func_800F0E4C_name_81(win, arg0);
    return win;
}

static void func_800F0FE8_name_81(void) {
    UnkPauseMesWork *work;
    s32 *mes;
    s16 sel;
    s16 sel2;
    s16 prev;
    s32 help;
    s32 i;
    GW_SYSTEM* system;

    work = HuPrcCurrentGet()->user_data;
    
    mes = work->mes;
    sel = work->unk_04;
    system = &GwSystem;
    prev = -1;

    if (D_8010124C_name_81 != 0) {
        D_801053E8_name_81 = func_800F0EA8_name_81(0, 0, 0x92);
        D_801053EC_name_81 = func_800F0EA8_name_81(2, 0x64, 0x92);
    }

    while (1) {
        if (D_8010124C_name_81 != 0) {
            sel2 = D_80101248_name_81;
        } else {
            sel2 = func_8006014C_main(sel);
        }

        if (((sel2 != prev) && (sel2 != -1)) || (D_8010124A_name_81 != 0)) {
            if ((D_8010124A_name_81 == 0) && (D_8010124C_name_81 != 0)) {
                switch (sel2) {
                case 0:
                case 7:
                    func_800F0E4C_name_81(D_801053E8_name_81, 0);
                    break;
                default:
                    func_800F0E4C_name_81(D_801053E8_name_81, 1);
                }
            }

            prev = sel2;
            D_8010124A_name_81 = 0;

            switch (mes[prev]) {
            case 0x5102:
                for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                    if (GwPlayer[i].stat & 1) {
                        func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5104), i);
                    } else {
                        func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5103), i);
                    }
                }
                break;

            case 0x5105:
                if (system->show_minigame_explanations == 0) {
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5106), 0);
                } else {
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5107), 0);
                }
                break;

            case 0x5108:
                switch (system->message_speed) {
                case 0:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5109), 0);
                    break;
                case 1:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x510A), 0);
                    break;
                case 2:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x510B), 0);
                    break;
                }
                break;

            case 0x510C:
                switch (system->save_mode) {
                case 0:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x510D), 0);
                    break;
                case 1:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x510E), 0);
                    break;
                case 2:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x510F), 0);
                    break;
                }
                break;

            case 0x5121:
                switch (system->walk_speed) {
                case 0:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5122), 0);
                    break;
                case 1:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5123), 0);
                    break;
                case 2:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5124), 0);
                    break;
                }
                break;

            case 0x5127:
                switch (system->show_com_minigames) {
                case 0:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5128), 0);
                    break;
                case 1:
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x5129), 0);
                    break;
                }
                break;

            case 0x512C:
                if (_CheckFlag(0x20) != 0) {
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x512B), 0);
                } else {
                    func_8005B6BC_main(D_801053E0_name_81->amount, func_800F0700_name_81(0x512A), 0);
                }
                break;
            }

            func_800F0DF8_name_81(D_801053E0_name_81->amount, mes[prev]);
        }
        HuPrcVSleep();
    }
}

static Process* func_800F1340_name_81(s32* arg0, s32 arg1, s16 arg2) {
    Process* proc;
    UnkPauseMesWork* temp_v0_2;

    proc = omAddPrcObj(func_800F0FE8_name_81, 0x1005, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(proc->heap, sizeof(UnkPauseMesWork));
    proc->user_data = temp_v0_2;
    temp_v0_2->mes = arg0;
    temp_v0_2->unk_04 = arg2;
    D_8010124C_name_81 = arg1;
    return proc;
}

static void func_800F13C0_name_81(Process* arg0) {
    if (D_8010124C_name_81 != 0) {
        func_8005F364_main(D_801053EA_name_81);
        func_8005F364_main(D_801053EE_name_81);
    }
    omDelPrcObj(arg0);
}

static s16 func_800F140C_name_81(s32 arg0, s16 arg1) {
    s16 sp18[2];
    s16 temp_v0;

    func_80060394_main(1, sp18, arg0);
    temp_v0 = func_8005A968_main(0xA0 - sp18[0] / 2, arg1, sp18[0], sp18[1], 0, 0);
    func_8005B43C_main(temp_v0, arg0, -1, -1);
    return temp_v0;
}

static s16 func_800F14A8_name_81(void) {
    s16 var_t0;
    s16 var_a1;

    var_t0 = 0;
    var_a1 = D_800CC69C_main->unk64;
    while (D_800CC69C_main[var_a1].unk64 != -1) {
        if (D_800CC69C_main[var_a1].unk_38 & 0x40) {
            var_t0 |= (u8)D_800CC69C_main[var_a1].unk20; //TODO: why required cast?
        }
        var_a1 = D_800CC69C_main[var_a1].unk64;
    }

    if (GwSystem.playMode & 4) {
        var_t0 = 1;
    }
    return var_t0;
}

static void func_800F159C_name_81(UnkBoard4 *arg0, s32 arg1) {
    void *data;
    s32 dataNum;
    GW_SYSTEM* system = &GwSystem;

    switch (arg1) {
    case 1:
        dataNum = D_801012AC_name_81[system->show_minigame_explanations];
        break;
    case 2:
        dataNum = D_801012B4_name_81[system->show_com_minigames];
        break;
    case 5:
        dataNum = D_801012BC_name_81[system->message_speed];
        break;
    case 4:
        dataNum = D_801012C8_name_81[system->walk_speed];
        break;
    case 6:
        dataNum = D_801012D4_name_81[system->save_mode];
        break;
    case 3:
        if (_CheckFlag(0x20) != 0) {
            dataNum = D_801012E4_name_81;
        } else {
            dataNum = D_801012E0_name_81;
        }
        break;
    default:
        return;
    }

    data = DataRead(dataNum);
    HuSprKill(arg0->unk_0C[arg1]);
    arg0->unk_0C[arg1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(arg0->unk_0A, arg1, arg0->unk_0C[arg1], 0);
    HuSprPriSet(arg0->unk_0A, arg1, 8);
    HuSprAttrSet(arg0->unk_0A, arg1, 0x1000);
    func_80054904_main(arg0->unk_0A, arg1,
                        ((arg1 % 4) << 6) + 0x46,
                        ((arg1 / 4) * 0x3C) + 0x3C);
    D_8010124A_name_81 = 1;
}

s32 func_800F1784_name_81(s32 arg0) {
    void *data;
    Process *mesProc;
    UnkBoard4 *icons;
    UnkBoard4 *cursor;
    s32 dataNum;
    s8 ret;
    s16 sel;
    s16 prevSel;
    s32 i;
    u8 sleepFlag;
    GW_SYSTEM* system;
    GW_COMMON* common = &GwCommon;
    s8 temp;

    ret = 4;
    sel = 0;
    prevSel = 0;
    mesProc =  NULL;
    icons = NULL; // s4
    cursor = NULL;
    sleepFlag = 0;
    system = &GwSystem;
    
    if (!D_801053E6_name_81) {
        sel = D_80101248_name_81;
        prevSel = sel;
        icons = func_800F4528_name_81(8, 0);
        
        for (i = 0; i < 8; i++) {
            switch (i) {
            case 0:
                if ((func_800F14A8_name_81()) != 0) {
                    dataNum = D_801012E8_name_81;
                } else {
                    dataNum = D_8010128C_name_81[0];
                }
                break;
            case 1:
                dataNum = D_801012AC_name_81[system->show_minigame_explanations];
                break;
            case 2:
                dataNum = D_801012B4_name_81[system->show_com_minigames];
                break;
            case 5:
                dataNum = D_801012BC_name_81[system->message_speed];
                break;
            case 4:
                dataNum = D_801012C8_name_81[system->walk_speed];
                break;
            case 6:
                dataNum = D_801012D4_name_81[system->save_mode];
                break;
            case 3:
                if (_CheckFlag(0x20) != 0) {
                    dataNum = D_801012E4_name_81;
                } else {
                    dataNum = D_801012E0_name_81;
                }
                break;
            default:
                dataNum = D_8010128C_name_81[i];
                break;
            }
    
            data = DataRead(dataNum);
            icons->unk_0C[i] = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(icons->unk_0A, i, icons->unk_0C[i], 0);
            HuSprPriSet(icons->unk_0A, i, 8);
            HuSprAttrSet(icons->unk_0A, i, 0x1000);
            func_80054904_main(icons->unk_0A, i,
                                ((i % 4) << 6) + 0x46,
                                ((i / 4) * 0x3C) + 0x3C);
        }
    
        if (D_801053E0_name_81 == NULL) {
            HuPrcVSleep();
            D_801053E0_name_81 = func_800E4B64_name_81(0, 8);
            HuVecCopyXYZ(&D_801053E0_name_81->obj->scale, 1.0f, 1.0f, 1.0f);
            func_8005E1A8_main(D_801053E0_name_81->amount, 0x2C);
            func_800D8944_name_81(D_801053E0_name_81->obj);
            func_8001C258_main(D_801053E0_name_81->obj->omObj1->model[0], 0x8000, 0x8000);
            D_801053E0_name_81->obj->flags |= 0x10;
            func_800E4EAC_name_81(D_801053E0_name_81, 0x104, 8);
            func_800F0D1C_name_81(D_801053E0_name_81, 0x69);
            func_80061100_main(D_801053E0_name_81->amount, 5);
            func_80060C14_main(D_801053E0_name_81->amount, 1);
        }
    
        cursor = func_800F4528_name_81(1, 0);
        data = DataRead(0x13009C);
        cursor->unk_0C[0] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(cursor->unk_0A, 0, cursor->unk_0C[0], 0);
        HuSprPriSet(cursor->unk_0A, 0, 7);
        HuSprAttrSet(cursor->unk_0A, 0, 0x1000);
        func_80054904_main(cursor->unk_0A, 0,
                            ((D_80101248_name_81 % 4) * 64) + 0x2A,
                            ((D_80101248_name_81 / 4) * 60) + 0x20);
    
        mesProc = func_800F1340_name_81(D_8010126C_name_81, 1, -1);
    
    restart:
        while (1) {
            HuPrcVSleep();
    
            if (D_800D0590_main[arg0] & 0x200) {
                sel--;
                if ((sel == 3) || (sel == -1)) {
                    sel += 4;
                }
            }
            if (D_800D0590_main[arg0] & 0x100) {
                sel++;
                if ((sel == 4) || (sel == 8)) {
                    sel -= 4;
                }
            }
            if (D_800D0590_main[arg0] & 0x800) {
                sel -= 4;
                if (sel < 0) {
                    sel += 8;
                }
            }
            if (D_800D0590_main[arg0] & 0x400) {
                sel += 4;
                if (sel >= 8) {
                    sel -= 8;
                }
            }
    
            if (D_800C9520_main[arg0] & 0x8000) {
                HuAudFXPlay(2);
                break;
            }
            if (D_800C9520_main[arg0] & 0x4000) {
                HuAudFXPlay(4);
                sel = -1;
                break;
            }
    
            if (sel != -1) {
                D_80101248_name_81 = sel;
            }
            if (prevSel != sel) {
                prevSel = sel;
                HuAudFXPlay(1);
            }
            func_80054904_main(cursor->unk_0A, 0,
                                ((D_80101248_name_81 % 4) * 64) + 0x2A,
                                ((D_80101248_name_81 / 4) * 0x3C) + 0x20);
        }
    
        switch (sel) {
        case 0:
            if ((func_800F14A8_name_81()) == 0) {
                ret = 2;
            }
            break;
        case 1:
            system->show_minigame_explanations ^= 1;
            func_800F159C_name_81(icons, 1);
            break;
        case 2:
            system->show_com_minigames ^= 1;
            func_800F159C_name_81(icons, 2);
            break;
        case 5:
            temp = (system->message_speed + 1);
            system->message_speed = temp % 3;
            func_800F159C_name_81(icons, 5);
            break;
        case 4:
            temp = (system->walk_speed + 1);
            system->walk_speed = temp % 3;
            func_800F159C_name_81(icons, 4);
            break;
        case 6:
            temp = (system->save_mode + 1);
            system->save_mode = temp % 3;
            func_800F159C_name_81(icons, 6);
            break;
        case 3:
            if (_CheckFlag(0x20) != 0) {
                _ClearFlag(0x20);
            } else {
                _SetFlag(0x20);
            }
            func_800F159C_name_81(icons, 3);
            break;
        case 7:
            ret = 9;
            break;
        case -1:
            ret = 1;
            break;
        }
    
        common->unk9E = system->save_mode;
        common->unk9F = system->show_minigame_explanations;
        common->unkA0 = system->message_speed;
        common->unkA1 = system->walk_speed;
        common->unkA2 = system->show_com_minigames;
        func_800EBAD4_name_81(common->unkA0);
        if ((ret == 2) || (ret == 9)) {
            func_800F4584_name_81(icons);
            func_800F4584_name_81(cursor);
            icons = NULL;
            cursor = NULL;
        }
    } else {
        ret = 0;
    }

    switch (ret) {
    case 0:
    case 1:
        if (D_801053E0_name_81 != NULL) {
            func_80060EA8_main(D_801053E0_name_81->amount, 1);
            func_800F0D1C_name_81(D_801053E0_name_81, 0x104);
            func_800E4E64_name_81(D_801053E0_name_81);
            D_801053E0_name_81 = NULL;
            if (icons != NULL) {
                func_800F4584_name_81(icons);
                func_800F4584_name_81(cursor);
            }
            sleepFlag = 1;
        }
        break;
    case 4:
        goto restart;
    }

    if (mesProc != NULL) {
        func_800F13C0_name_81(mesProc);
    }
    if (sleepFlag != 0) {
        HuPrcSleep(5);
    }
    return ret;
}

static s32 func_800F2090_name_81(s32 arg0) {
    Process* temp_s3;
    s16 temp_v0;
    s16 temp;

    temp_v0 = func_800F140C_name_81(func_800F0700_name_81(0x511E), 0x36);
    func_8005BE30_main(temp_v0, 5);
    func_8005BEE0_main(temp_v0, 0xFF);
    func_8005B43C_main(temp_v0, func_800F0700_name_81(0x511E), -1, -1);
    func_8005BDFC_main(temp_v0, 0);
    
    while ((func_8005E0C0_main(temp_v0)) != 0) {
        HuPrcVSleep();
    }
    
    temp_s3 = func_800F1340_name_81(D_801012EC_name_81, 0, temp_v0);
    func_8005FE54_main(temp_v0, 1 << arg0);
    temp = func_8005E1D8_main(temp_v0, 0, 0);
    if (temp == 1) {
        D_801053E6_name_81 = 1;
    }
    func_800F13C0_name_81(temp_s3);
    func_8005F364_main(temp_v0);
    return 4;
}

static s32 func_800F21CC_name_81(s16 arg0) {
    GW_PLAYER* player;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        player = MBDGetPlayerStruct(i);
        if (!(player->stat & 1)) {
            if (player->pad == arg0) {
                return 1;
            }
        }
    }
    return 0;
}

static void func_800F2238_name_81(GW_PLAYER* arg0, s16 arg1) {
    GW_PLAYER* player;
    s32 i;
    u8 pad;

    pad = arg0->pad;
    if (arg1 < 4) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = MBDGetPlayerStruct(i);
            if (player->pad != arg1) {
                continue;
            }
            player->pad = pad;
            arg0->pad = arg1;
            arg0->stat &= ~1;
            return;
        }        
    } else {
        arg0->stat |= 1;
    }
}

static s32 func_800F22E8_name_81(GW_PLAYER *arg0, s16 arg1) {
    s32 count;
    s32 port;
    u32 i;

    if (func_800F37B8_name_81(arg0->turn) != 0) {
        count = 4;
        if (arg1 > 0) {
            port = 0;
        } else {
            port = 3;
        }
        for (; count != 0; count--) {
            if ((func_800F21CC_name_81(port) == 0) &&
                (CheckControllerRead(port) != 0)) {
                return port;
            }
            port += arg1;
        }
        return 4;
    }

    //TODO: reg alloc hack
    port = (arg1 - 1) >= 0;
    if (port) {
        i = arg0->pad + 1;
    } else {
        i = arg0->pad - 1;
    }
    
    for (; i < 4; i += arg1) {
        if ((func_800F21CC_name_81(i) == 0)) {
            if (CheckControllerRead(i) != 0) {
                return i;
            }
            
        }
    }
    return 4;
}

static void func_800F23FC_name_81(s16 arg0) {
    D_801053F4_name_81 = arg0;
}

static void func_800F2408_name_81(UnkBoard4* arg0, s16 arg1) {
    func_80054904_main(arg0->unk_0A, 0, (D_80101348_name_81[arg1] - 50), (D_8010134C_name_81[arg1] - 8));
    func_80054904_main(arg0->unk_0A, 1, (D_80101348_name_81[arg1] + 50), ((u16)D_8010134C_name_81[arg1] + 4));
    func_80054904_main(arg0->unk_0A, 2, (D_80101348_name_81[arg1] - 50), ((u16)D_8010134C_name_81[arg1] + 4));
}

static void func_800F24DC_name_81(void) {
    f32 var_f20;
    s32 var_v0;
    UnkBoard4* temp_s1;

    temp_s1 = HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    while (1) {
        HuPrcVSleep();
        if (D_801053F4_name_81 != 0) {
            var_v0 = (s16) (sindf(var_f20) * 255.0f); //TODO: s16 cast
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            var_f20 += 6.0f;
            if (var_f20 > 360.0f) {
                var_f20 -= 360.0f;
            }
            func_80055420_main(temp_s1->unk_0A, 1, 0xFFU, var_v0, 0U);
            func_80055420_main(temp_s1->unk_0A, 2, 0xFFU, var_v0, 0U);
            HuSprAttrReset(temp_s1->unk_0A, 1, 0x8000);
            HuSprAttrReset(temp_s1->unk_0A, 2, 0x8000);
        } else {
            var_f20 = 0.0f;
            HuSprAttrSet(temp_s1->unk_0A, 1, 0x8000);
            HuSprAttrSet(temp_s1->unk_0A, 2, 0x8000);
        }
    }
}

s32 func_800F2618_name_81(s32 arg0) {
    s16 sel;
    UnkBoard4* panel;
    UnkBoard4* chr;
    UnkBoard4* icon;
    UnkBoard4* cursor;
    UnkBoard4* bg;
    Process* proc;
    GW_PLAYER* player;
    void* data;
    u16* trg;
    u16* dwn;
    s32 mess;
    s32 setting;
    s16 dir;
    s32 i;
    s32 diff;

    mess = 0;
    sel = 0;
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if ((func_800F37B8_name_81(i) == 0) && (GwPlayer[i].pad == arg0)) {
            sel = i;
            break;
        }
    }

    bg = func_800F4528_name_81(1, 0);
    data = DataRead(0x1300AA);
    bg->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(bg->unk_0A, 0, bg->unk_0C[0], 0);
    HuSprPriSet(bg->unk_0A, 0, 8);
    HuSprAttrSet(bg->unk_0A, 0, 0x1000);
    func_80054904_main(bg->unk_0A, 0, 0xA0, (D_8010134C_name_81[0] + D_8010134C_name_81[1]) / 2);

    panel = func_800F4528_name_81(4, 0);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == 0) {
            data = DataRead(0x1300A7);
            panel->unk_0C[2] = func_80055810_main(data);
            DataClose(data);
        }
        func_80055024_main(panel->unk_0A, i + 2, panel->unk_0C[2], 0);
        HuSprPriSet(panel->unk_0A, i + 2, 8);
        HuSprAttrSet(panel->unk_0A, i + 2, 0x1000);
        func_80054904_main(panel->unk_0A, i + 2, D_80101348_name_81[i], D_8010134C_name_81[i]);
    }

    chr = func_800F4528_name_81(2, 0);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        data = DataRead(D_801012F4_name_81[MBDGetPlayerStruct(i)->chr]);
        chr->unk_0C[i] = func_80055810_main(data);
        func_80055024_main(chr->unk_0A, i, chr->unk_0C[i], 0);
        HuSprPriSet(chr->unk_0A, i, 7);
        HuSprAttrSet(chr->unk_0A, i, 0x1000);
        func_80054904_main(chr->unk_0A, i, D_80101348_name_81[i] - 0x14, D_8010134C_name_81[i] + 4);
        DataClose(data);
        if (i != 0) {
            HuSprAttrSet(chr->unk_0A, i, 1);
        }
    }

    icon = func_800F4528_name_81(9, 0);
    for (i = 0; i < 9; i++) {
        data = DataRead(D_80101314_name_81[i]);
        icon->unk_0C[i] = func_80055810_main(data);
        DataClose(data);
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (func_800F37B8_name_81(i) != 0) {
            func_80055024_main(icon->unk_0A, i,
                icon->unk_0C[D_80101340_name_81[GwPlayer[i].cpu_difficulty * 2 + 0]], 0);
            func_80055024_main(icon->unk_0A, i + 2,
                icon->unk_0C[D_80101340_name_81[GwPlayer[i].cpu_difficulty * 2 + 1]], 0);
            func_80054904_main(icon->unk_0A, i,
                D_80101348_name_81[i] + 0x10,
                D_8010134C_name_81[i] - 6);
        } else {
            func_80055024_main(icon->unk_0A, i,
                icon->unk_0C[D_80101338_name_81[GwPlayer[i].pad * 2]], 0);
            func_80055024_main(icon->unk_0A, i + 2,
                icon->unk_0C[D_80101338_name_81[GwPlayer[i].pad * 2]], 0);
            func_80054904_main(icon->unk_0A, i,
                D_80101348_name_81[i] + 0x10,
                D_8010134C_name_81[i] + 2);
            HuSprAttrSet(icon->unk_0A, i + 2, 0x8000);
        }
        HuSprPriSet(icon->unk_0A, i, 7);
        HuSprAttrSet(icon->unk_0A, i, 0x01001000);
        HuSprPriSet(icon->unk_0A, i + 2, 7);
        HuSprAttrSet(icon->unk_0A, i + 2, 0x01001000);
        func_80054904_main(icon->unk_0A, i + 2,
            D_80101348_name_81[i] + 0x10,
            D_8010134C_name_81[i] + 0xA);
    }

    cursor = func_800F4528_name_81(3, 0);
    data = DataRead(0x13009C);
    cursor->unk_0C[0] = func_80055810_main(data);
    func_80055024_main(cursor->unk_0A, 0, cursor->unk_0C[0], 0);
    HuSprAttrSet(cursor->unk_0A, 0, 0x1808);
    HuSprPriSet(cursor->unk_0A, 0, 8);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->unk_0C[1] = func_80055810_main(data);
    func_80055024_main(cursor->unk_0A, 1, cursor->unk_0C[1], 0);
    HuSprAttrSet(cursor->unk_0A, 1, 0x9808);
    HuSprPriSet(cursor->unk_0A, 1, 8);
    func_80055420_main(cursor->unk_0A, 1, 0xFF, 0, 0);
    HuSprAttrSet(cursor->unk_0A, 1, 1);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->unk_0C[2] = func_80055810_main(data);
    func_80055024_main(cursor->unk_0A, 2, cursor->unk_0C[2], 0);
    HuSprAttrSet(cursor->unk_0A, 2, 0x9808);
    HuSprPriSet(cursor->unk_0A, 2, 8);
    func_80055420_main(cursor->unk_0A, 2, 0xFF, 0, 0);
    DataClose(data);

    func_800F2408_name_81(cursor, sel);
    func_800F23FC_name_81(0);
    proc = omAddPrcObj(func_800F24DC_name_81, 0x1005, 0, 0);
    proc->user_data = cursor;

    do {
        if (mess != 0x5112) {
            mess = 0x5112;
            func_800F0DF8_name_81(D_801053E0_name_81->amount, 0x5112);
        }
        HuPrcVSleep();

        dir = -1;
        if (D_800C9520_main[arg0] & 0x800) dir = 0;
        if (D_800C9520_main[arg0] & 0x400) dir = 1;
        if (D_800C9520_main[arg0] & 0x200) dir = 2;
        if (D_800C9520_main[arg0] & 0x100) dir = 3;

        if (dir != -1) {
            sel += D_80101350_name_81[sel][dir];
            func_800F2408_name_81(cursor, sel);
            HuAudFXPlay(1);
        } else if (D_800D5558_main[arg0] & 0x8000) {
            HuAudFXPlay(2);
            player = MBDGetPlayerStruct(sel);
            func_800F23FC_name_81(1);
            diff = player->cpu_difficulty;
            i = (func_800F37B8_name_81(sel) != 0) ? 4 : -1;

            while (1) {
                HuPrcVSleep();
                if (mess != 0x5113) {
                    mess = 0x5113;
                    func_800F0DF8_name_81(D_801053E0_name_81->amount, 0x5113);
                }

                if (D_800C9520_main[arg0] & 0x200) {
                    if ((i != 4) || (diff == 0)) {
                        i = func_800F22E8_name_81(player, -1);
                        if (i == 4) {
                            diff = _CheckFlag(0x2D) ? 3 : 2;
                        }
                    } else {
                        diff--;
                    }
                    func_800F3B54_name_81(sel, diff);
                    HuAudFXPlay(1);
                } else if (D_800C9520_main[arg0] & 0x100) {
                    if (_CheckFlag(0x2D) != 0) {
                        if ((i != 4) || (diff == 3)) {
                            i = func_800F22E8_name_81(player, 1);
                            diff = -(i != 4) & diff;
                        } else {
                            diff++;
                        }
                        
                    } else if ((i != 4) || (diff == 2)) {
                        i = func_800F22E8_name_81(player, 1);
                        diff = -(i != 4) & diff;
                    } else {
                        diff++;
                    }
                    func_800F3B54_name_81(sel, diff);
                    HuAudFXPlay(1);
                }

                if (i >= 0) {
                    func_800F2238_name_81(player, i);
                    if (func_800F37B8_name_81(sel) != 0) {
                        func_80055024_main(icon->unk_0A, sel,
                            icon->unk_0C[D_80101340_name_81[GwPlayer[sel].cpu_difficulty * 2 + 0]], 0);
                        func_80055024_main(icon->unk_0A, sel + 2,
                            icon->unk_0C[D_80101340_name_81[GwPlayer[sel].cpu_difficulty * 2 + 1]], 0);
                        func_80054904_main(icon->unk_0A, sel,
                            D_80101348_name_81[sel] + 0x10,
                            D_8010134C_name_81[sel] - 6);
                        HuSprAttrReset(icon->unk_0A, sel + 2, 0x8000);
                    } else {
                        func_80055024_main(icon->unk_0A, sel,
                            icon->unk_0C[D_80101338_name_81[GwPlayer[sel].pad * 2]], 0);
                        func_80054904_main(icon->unk_0A, sel,
                            D_80101348_name_81[sel] + 0x10,
                            D_8010134C_name_81[sel] + 2);
                        HuSprAttrSet(icon->unk_0A, sel + 2, 0x8000);
                    }
                }

                if (D_800C9520_main[arg0] & 0x8000) {
                    HuAudFXPlay(2);
                    func_800F3B54_name_81(sel, diff);
                    break;
                }
                if (D_800C9520_main[arg0] & 0x4000) {
                    HuAudFXPlay(4);
                    break;
                }
            }

            func_800F23FC_name_81(0);
            HuPrcVSleep();
        }
    } while (!(D_800D5558_main[arg0] & 0x4000));

    HuAudFXPlay(4);
    omDelPrcObj(proc);
    func_800F4584_name_81(cursor);
    func_800F4584_name_81(icon);
    func_800F4584_name_81(chr);
    func_800F4584_name_81(panel);
    func_800F4584_name_81(bg);
    return 4;
}

static s16 func_800F32CC_name_81(s16 arg0, s32 arg1) {
    switch (arg0) {
    case 1:
        return func_800F0C4C_name_81(arg1);
    case 2:
        return func_800F2618_name_81(arg1);
    case 4:
        return func_800F1784_name_81(arg1);
    case 9:
        return func_800F2090_name_81(arg1);
    default:
        return 0;
    }
}

static void func_800F336C_name_81(void) {
    UnkBoard4* temp_s1;
    s16 var_s2;
    s16 temp_v0;
    s32 temp_s3;
    void* temp_v0_2;

    temp_s3 = (s32)HuPrcCurrentGet()->user_data;
    var_s2 = 1;
    temp_v0 = func_800F73AC_name_81();
    
    if (temp_v0 != 0) {
        func_800F73C0_name_81();
    }
    
    HuPrcVSleep();
    HmfPauseF = 1;
    temp_s1 = func_800F4528_name_81(1, 0);
    temp_v0_2 = DataRead(0x13025D);
    temp_s1->unk_0C[0] = func_80055810_main(temp_v0_2);
    func_80055024_main(temp_s1->unk_0A, 0, temp_s1->unk_0C[0], 0U);
    HuSprPriSet(temp_s1->unk_0A, 0, 9U);
    HuSprAttrSet(temp_s1->unk_0A, 0, 0x1000);
    func_80054904_main(temp_s1->unk_0A, 0, 0xA0, 0x78);
    HuSprScaleSet(temp_s1->unk_0A, 0, 40.0f, 30.0f);
    func_80055484_main(temp_s1->unk_0A, 0, 0, 0, 0, 0xC0);
    DataClose(temp_v0_2);
    
    do {
        HuPrcVSleep();
        var_s2 = func_800F32CC_name_81(var_s2, temp_s3);
    } while (var_s2 != 0);
    
    if (D_801053E6_name_81 == 0) {
        HmfPauseF = 0;
    }
    
    func_800F4584_name_81(temp_s1);
    
    if (temp_v0 != 0) {
        func_800F740C_name_81();
    }
    
    omDelPrcObj(NULL);
}

void func_800F3500_name_81(s32 arg0) {
    Process* temp_s1_2;
    Process* temp_v0;
    s16 var_a0;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;
    s32 i;

    func_800E9190_name_81();
    D_800CB99C_main = 1;
    func_80049FB8_main();
    temp_s2 = _CheckFlag(0x20) != 0;
    
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            ResetVibrator(i);
        }        
    }

    func_8004A9DC_main(0x60);
    if (D_800C9930_main != -1) {
        func_800036E8_main(D_800C9930_main, 0x60);
    }
    
    func_8001AC34_main(D_800D10F2_main, 2);
    func_8001C8A8_main(D_800D10F2_main, 1);
    D_801053E0_name_81 = 0;
    D_801053E4_name_81 = 0;
    D_801053E6_name_81 = 0;
    temp_s1_2 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(func_800F336C_name_81, 0xEFFFU, 0x1000, 0);
    temp_v0->user_data = (void*)arg0;
    omPrcSetStatBit(temp_v0, 0x80);
    HuPrcChildLink(temp_s1_2, temp_v0);
    HuPrcChildWait();
    func_8001AC34_main(D_800D10F2_main, 6);
    func_8004A9DC_main(0x7F);
    if (D_800C9930_main != -1) {
        func_800036E8_main(D_800C9930_main, 0x7F);
    }
    if (((_CheckFlag(0x20) != 0) && (temp_s2 == 0)) || ((_CheckFlag(0x20) == 0) && (temp_s2 != 0))) {
        func_800DF154_name_81();
    }
    if (D_801053E6_name_81 != 0) {
        D_800A176D_main = 0;
        HuAudSeqFadeOut(0x5A);
        if (D_800C9930_main != -1) {
            func_800039A4_main(D_800C9930_main, 0x5A);
            D_800C9930_main = -1;
            func_8004A950_main();
        }
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x11);
        func_800FC4E4_name_81();
        func_800FC108_name_81();
        if (GwSystem.playMode & 4) {
            omOvlReturnEx(3);
        } else {
            omOvlReturnEx(1);
        }
        
        omOvlKill();
        HuPrcVSleep();
    }
    func_8004A0E0_main();
    D_800CB99C_main = 0;
    func_800E9180_name_81();
}

s16 MBDGetCurrentPlayerIndex(void) {
    return GwSystem.current_player_index;
}

GW_PLAYER *MBDGetPlayerStruct(s32 player) {
    if (player < 0) {
        player = MBDGetCurrentPlayerIndex();
    }
    return &GwPlayer[player];
}

s32 func_800F379C_name_81(s16 playerNo) {
    if (playerNo == GwSystem.current_player_index) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_800F37B8_name_81(s16 playerNo) {
    return MBDGetPlayerStruct(playerNo)->stat & PLAYER_IS_CPU;
}

void func_800F37E0_name_81(s32 playerNo, s32 amount) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(playerNo);
    player->coin = player->coin + amount;
    if (player->coin > 999) {
        player->coin = 999;
    }
    if (player->coin < 0) {
        player->coin = 0;
    }
    if (player->coinPrize <= player->coin) {
        player->coinPrize = player->coin;
    }
}

s32 func_800F3850_name_81(s32 playerNo, s32 requiredCoins) {
    if (MBDGetPlayerStruct(playerNo)->coin >= requiredCoins) {
        return TRUE;
    } else {
        return FALSE;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3880_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F38DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F397C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3A04_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3AF4_name_81);

void func_800F3B54_name_81(s32 playerNo, u8 arg1) {
    MBDGetPlayerStruct(playerNo)->cpu_difficulty = D_80101370_name_81[arg1];
}

void func_800F3B8C_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3B94_name_81);

static void func_800F3C28_name_81(void) {
    GW_PLAYER *player = HuPrcCurrentGet()->user_data;

    while (1) {
        HuPrcVSleep();
        if (player->stat & PLAYER_UNK_04) {
            continue;
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
}

void func_800F3C98_name_81(s16 playerNo, s32 *arg1, s32 arg2) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    Process *proc;
    u8 chr;

    player->turn = playerNo;
    chr = player->chr;

    switch (arg2) {
        case 0:
            player->player_obj = func_800D8010_name_81(D_801014B4_name_81[chr], arg1);
            break;
        case 1:
        case 2:
            player->player_obj = func_800D8010_name_81(D_801014BC_name_81[chr], arg1);
            break;
    }

    proc = omAddPrcObj(func_800F3C28_name_81, 0x5000, 0, 0);
    player->unk_20 = proc;
    proc->user_data = player;
}

void func_800F3D50_name_81(s16 arg0, s32* arg1) {
    func_800F3C98_name_81(arg0, arg1, 0);
}

void func_800F3D74_name_81(s16 playerNo) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);

    func_800F3C98_name_81(playerNo, D_80101494_name_81[player->chr], 0);
}

void func_800F3DC0_name_81(s16 playerNo) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo); // remnants of a debug build or the below function was changed to take a playerNo

    func_800F3C98_name_81(playerNo, 0, 0);
}

void func_800F3DFC_name_81(s32 arg0) {
    s16 playerNo = arg0;

    func_800F3C98_name_81(playerNo, D_80101494_name_81[MBDGetPlayerStruct(playerNo)->chr], 0);
    func_800F8108_name_81(playerNo);
    func_800ED214_name_81(playerNo);
}

u8 func_800F3E58_name_81(s16 playerNo) {
    return D_801014BC_name_81[MBDGetPlayerStruct(playerNo)->chr];
}

void func_800F3E88_name_81(s16 playerNo, s32 arg1) {
    func_800D898C_name_81(MBDGetPlayerStruct(playerNo)->player_obj, arg1);
}

void func_800F3EC0_name_81(s16 playerNo) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);

    if (player->player_obj != NULL) {
        if (player->unk_20 != NULL) {
            omDelPrcObj(player->unk_20);
        }
        func_800D8F3C_name_81(player->player_obj);
        player->player_obj = NULL;
    }
}

void func_800F3F18_name_81(s16 playerNo) {
    func_800F3EC0_name_81(playerNo);
    func_800F82EC_name_81(playerNo);
}

void func_800F3F4C_name_81(void) {
    s32 i, j;

    for (j = 0; j < 3; j++) {
        MBDGetPlayerStruct(j)->player_obj = NULL;
    }
    Duel_ClearPartnerObjects();

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80101374_name_81[0]; j++) {
            D_80101494_name_81[i][j + 1] = func_80017BB8_main(i, D_80101374_name_81[j + 1]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F4030_name_81);
