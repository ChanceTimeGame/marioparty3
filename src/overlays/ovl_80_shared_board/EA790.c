#include "common.h"
#include "game/board.h"
#include "ECA50.h"
#include "malloc.h"
#include "F2910.h"

/* This unit's .data (0x801007A0-0x80100F20) also holds the data of the units after it in the
 * ROM (EB2F0, ECA50, EDDB0, EE660, F2910, F5070): retail linked them from 16-byte-aligned files,
 * so each of their starts is padded to 16 (SB_DATA_FILE_END). Their C keeps `extern`s. */
#ifdef NON_MATCHING
#define SB_DATA_FILE_END()
#else
#define SB_DATA_FILE_END() __asm__(".section .data\n    .align 4\n");
#endif

/* EB2F0 */
s32 D_801007A0_shared_board[] = {
    0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F,
    0x001301CF, 0x001301D0, 0x001301D1, 0x001301D2, 0x001301DD,
};
s16 D_801007D4_shared_board[][4] = {
    { 0, 2, 0, 1 }, { 0, 2, -1, 0 }, { -2, 0, 0, 1 }, { -2, 0, -1, 0 },
};
s16 D_801007F4_shared_board[] = { 66, 252, 66, 252 };
s16 D_801007FC_shared_board[] = { 30, 30, 210, 210 };
s32 D_80100804_shared_board[] = {
    0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F,
};
s32 D_80100824_shared_board[] = {
    0x001301D5, 0x001301D6, 0x001301D7, 0x001301D8, 0x001301D9, 0x001301DA, 0x001301DB, 0x001301DC,
};
SB_DATA_FILE_END()

/* ECA50 */
/* model files: { file, ?, ?, ? } (ECA50) */
UnkTemp D_80100850_shared_board[] = {
    { 0x200A2, 9, 0.9f, 0.8f }, { 0x300A2, 9, 0.9f, 0.8f }, { 0x700A2, 9, 0.9f, 1.1f },
    { 0x400A2, 9, 0.9f, 1.0f }, { 0x500A2, 9, 0.9f, 1.0f }, { 0x600A2, 9, 0.9f, 1.4f },
    { 0x800A2, 9, 0.9f, 0.8f }, { 0x90003, 9, 0.9f, 1.1f }, { 0xA002D, 9, 0.7f, 1.4f },
    { 0xA0000, 9, 1.0f, 1.0f }, { 0xA00C4, 9, 1.0f, 1.5f }, { 0xA00CE, 9, 0.5f, 0.0f },
    { 0xA00A5, 9, 1.0f, 1.0f }, { 0xA00E7, 1245791, 1.0f, 2.0f }, { 0x200A0, 9, 1.0f, 0.9f },
    { 0x300A0, 9, 1.0f, 0.9f }, { 0x700A0, 9, 1.0f, 1.2f }, { 0x400A0, 9, 1.0f, 1.1f },
    { 0x500A0, 9, 1.0f, 1.1f }, { 0x600A0, 9, 1.0f, 1.5f }, { 0x800A0, 9, 1.0f, 0.9f },
    { 0x90000, 9, 1.0f, 1.2f }, { 0x130145, 9, 1.0f, 0.0f }, { 0x1301CB, 9, 1.0f, 0.0f },
    { 0xA0022, 9, 1.2f, 0.7f }, { 0x1301CA, 9, 0.25f, 0.0f }, { 0x1301CC, 9, 1.0f, 0.0f },
    { 0xA0000, 9, 1.0f, 0.0f }, { 0xB000D, 9, 1.0f, 0.0f }, { 0xA00FF, 9, 1.2f, 0.7f },
    { 0x130158, 9, 1.0f, 0.0f }, { 0x130200, 9, 1.0f, 0.0f }, { 0x1301ED, 9, 1.0f, 0.0f },
    { 0x1301EE, 9, 1.0f, 0.0f }, { 0xB0026, 9, 1.0f, 0.0f }, { 0xA004B, 9, 0.7f, 1.4f },
    { 0x1301F9, 9, 1.0f, 0.0f }, { 0x1301F4, 9, 1.0f, 0.0f }, { 0x130162, 9, 1.0f, 0.0f },
    { 0x130167, 9, 1.0f, 0.0f }, { 0x13016E, 9, 1.0f, 0.0f }, { 0x130175, 9, 1.0f, 0.0f },
    { 0x13017F, 9, 1.0f, 0.0f }, { 0x130183, 9, 1.0f, 0.0f }, { 0xA005B, 9, 1.0f, 1.0f },
    { 0x130161, 9, 1.0f, 0.0f }, { 0x130166, 9, 1.0f, 0.0f }, { 0x130164, 9, 1.0f, 2.0f },
    { 0x130157, 9, 1.0f, 0.0f }, { 0x13015A, 9, 1.0f, 0.0f }, { 0x130155, 9, 1.0f, 0.0f },
    { 0x130159, 9, 1.0f, 0.0f }, { 0x130156, 9, 1.0f, 0.0f }, { 0xA008E, 9, 1.0f, 0.0f },
    { 0x330008, 9, 5.0f, 0.0f }, { 0x83, 9, 2.0f, 0.0f }, { 0x84, 9, 2.0f, 0.0f },
    { 0xA00EE, 9, 1.0f, 1.0f }, { 0xA0122, 9, 2.0f, 3.0f }, { 0xA0075, 9, 1.0f, 0.0f },
    { 0x1301F5, 9, 1.0f, 3.0f }, { 0x1301FA, 9, 1.0f, 0.0f }, { 0xA0063, 9, 1.5f, 0.0f },
    { 0x1301F0, 9, 1.0f, 0.0f }, { 0x1301F1, 9, 1.0f, 0.0f }, { 0x130201, 9, 0.5f, 0.0f },
    { 0x130202, 9, 0.5f, 0.0f }, { 0x1301F2, 9, 1.0f, 0.0f }, { 0x1301F3, 9, 1.0f, 0.0f },
    { 0xB0006, 9, 5.0f, 0.0f }, { 0xB003A, 9, 1.0f, 0.0f }, { 0x130172, 9, 1.0f, 0.0f },
    { 0x130173, 9, 1.0f, 0.0f }, { 0x130174, 9, 1.0f, 0.0f }, { 0x130170, 9, 0.9f, 0.0f },
    { 0x130171, 9, 0.9f, 0.0f }, { 0x130181, 9, 1.0f, 0.0f }, { 0x130182, 9, 1.0f, 0.0f },
    { 0x13018D, 9, 1.0f, 0.0f },
};
f32 D_80100D40_shared_board = 100.0f;
SB_DATA_FILE_END()

/* EDDB0 */
s16 D_80100D50_shared_board[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

/* EE660 */
s32 D_80100D60_shared_board[] = { 0x00130207, 0x00130207, 0x00130207, 0x00130207, 0x00130207, 0x00130208 };
s32 D_80100D78_shared_board[] = { 0x001300FE, 0x00130206, 0x001301E7, 0x00130266, 0x001301E8, 0x0013020B };
s32 D_80100D90_shared_board = 1;
s16 D_80100D94_shared_board[][2] = { { 110, 64 }, { 210, 64 }, { 160, 64 } };

/* F2910: minigame lists */
u8 D_80100DA0_shared_board[] = {
    0x15, 0x16, 0x17, 0x18, 0x19, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2C,
};
u8 D_80100DB4_shared_board[] = { 0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28 };
u8 D_80100DC0_shared_board[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
u8 D_80100DCC_shared_board[] = { 0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0A };
u8 D_80100DD4_shared_board[] = { 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14 };
u8 D_80100DE0_shared_board[] = { 0x0B, 0x0C, 0x10, 0x11, 0x13 };
u8 D_80100DE8_shared_board[] = { 0x1A, 0x29, 0x2A, 0x2B, 0x2D, 0x2E, 0x2F, 0x30 };
u8 D_80100DF0_shared_board[] = { 0x2A, 0x2B, 0x2D, 0x2E };
u8 D_80100DF4_shared_board[] = { 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40 };
u8 D_80100DFC_shared_board[] = { 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40 };
u8 D_80100E04_shared_board[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A };
u8 D_80100E10_shared_board[] = { 0x31, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39 };
u8 D_80100E18_shared_board[] = { 5, 3, 3, 3, 3, 5 };
u8 D_80100E20_shared_board[] = { 10, 5, 5, 3, 3, 5 };
u8 D_80100E28_shared_board[] = { 3, 3, 1, 3, 1, 2 };
/* RGB colours */
u8 D_80100E30_shared_board[][3] = {
    { 0x19, 0xA3, 0x5C }, { 0x34, 0x56, 0xCE }, { 0xDB, 0x2A, 0x6A },
    { 0xDE, 0x77, 0x1F }, { 0x1A, 0x8E, 0xB1 }, { 0xD7, 0x3D, 0x6D },
};
ItemRect D_80100E44_shared_board[] = { { 60, 348, 200, 20 }, { 60, 368, 200, 20 }, { 60, 388, 200, 20 } };
ItemRect D_80100E5C_shared_board[] = {
    { 60, 328, 200, 20 }, { 60, 348, 200, 20 }, { 60, 368, 200, 20 }, { 60, 388, 200, 20 }, { 60, 408, 200, 20 },
};
u8 D_80100E84_shared_board[] = { 50, 30, 30, 30, 30, 50 };
u8 D_80100E8C_shared_board[] = { 114, 134, 134, 134, 134, 114 };
s8 D_80100E94_shared_board[][2] = { { 1, 0 }, { 9, 15 }, { 11, 8 }, { 13, 0 } };
/* per minigame, indexed by id - 1 */
u8 D_80100E9C_shared_board[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};
u32 D_80100EE8_shared_board = 0;
u8 D_80100EEC_shared_board[] = { 20, 10, 10, 6, 8, 10 };
u8 D_80100EF4_shared_board[] = { 9, 7, 5, 6, 4, 7 };
SB_DATA_FILE_END()

/* F5070 */
f32 D_80100F00_shared_board[][2] = { { 78.0f, 64.0f }, { 245.0f, 64.0f }, { 78.0f, 170.0f }, { 245.0f, 170.0f } };

//this file matches BE940.c in ovl_81

UnkBoard2 *func_800D6B70_shared_board(s32 arg0) {
    s32 sp10[3] = { 0x00000016, 0x00000016, 0x00000016 };
    UnkBoard2 *temp_v0;
    Object *temp_v0_2;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkBoard2));
    temp_v0->unk_00 = 0;
    temp_v0->obj = MBModelCreate(sp10[arg0], NULL);
    func_8001C258_main(temp_v0->obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(temp_v0->obj->omObj1->model[0], 0x1400);
    func_8001C448_main(temp_v0->obj->omObj1->model[0]);
    MBModelTempAllocFree(temp_v0->obj);
    return temp_v0;
}

static void func_800D6C3C_shared_board(UnkBoard2* arg0) {
    MBModelKill(arg0->obj);
    HuMemMemoryFreeTemp(arg0);
}

UnkEA790Struct* func_800D6C6C_shared_board(void) {
    UnkEA790Struct* temp_v0;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkEA790Struct));
    temp_v0->unk_00 = 0;
    temp_v0->unk_02 = 0;
    temp_v0->unk_04 = 0;
    temp_v0->proc = NULL;
    temp_v0->unk_0C = 0;
    temp_v0->player = NULL;
    return temp_v0;
}

void func_800D6CA0_shared_board(UnkEA790Struct* arg0) {
    UnkBoard2** var_s1;
    s32 i;

    if (arg0->unk_02 != 0) {
        var_s1 = arg0->unk_04;
        for (i = 0; i < arg0->unk_02; i++) {
            func_800D6C3C_shared_board(*var_s1++);
        }
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    
    if (arg0->proc != NULL) {
        omDelPrcObj(arg0->proc);
    }
    
    HuMemMemoryFreeTemp(arg0);
}

void func_800D6D2C_shared_board(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2) {
    UnkBoard2 **newList;
    UnkBoard2 **dst;
    UnkBoard2 **src;
    s32 i;

    newList = HuMemMemoryAllocTemp(++arg0->unk_02 * sizeof(UnkBoard2 *));
    dst = newList;
    if (arg0->unk_04 != NULL) {
        src = arg0->unk_04;
        for (i = 0; i < arg0->unk_02 - 1; i++) {
            *dst++ = *src++;
        }
    }

    if (1) {
        *dst = arg1;
    } else {
        *dst = arg1;
    }

    if (arg0->unk_04 != NULL) {
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    
    arg0->unk_04 = newList;

    arg1->unk_00 = arg2;
    if (arg2 & 1) {
        arg0->unk_0C = arg0->unk_02 - 1;
    }
}

//unused
void func_800D6E00_shared_board(UnkEA790Struct *arg0, UnkBoard2* arg1) {
    UnkBoard2 **newList;
    UnkBoard2 **dst;
    UnkBoard2 **src;
    s16 count;
    s32 i;

    count = arg0->unk_02;
    newList = NULL;
    if (count >= 2) {
        count--;
        arg0->unk_02 = count;
        newList = HuMemMemoryAllocTemp(count * sizeof(s32));
        dst = newList;
        src = arg0->unk_04;
        for (i = 0; i <= arg0->unk_02; i++) {
            if (*src == arg1) {
                src++;
            } else {
                *dst = *src;
                src++;
                dst++;
            }
        }
    } else {
        arg0->unk_02 = 0;
    }

    if (arg0->unk_04 != NULL) {
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    arg0->unk_04 = newList;
}

UnkBoard2* func_800D6EC8_shared_board(UnkEA790Struct* arg0, s16 arg1) {
    return arg0->unk_04[arg1];
}
