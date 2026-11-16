#include "common.h"

extern OvlEntrypoint D_8010B7D0_w10[];

void func_801059A0_w10(void) {
    ovlEventCall(D_8010B7D0_w10, omovlevtno);
}

// board h2: the overlay's .data (0x3B9420..0x3B9590)
#include "game/board.h"

void func_801059D0_w10(void);
void func_80105A0C_w10(void);
void func_80105E10_w10(void);
void func_8010B5A4_w10(void);

/* .data */
OvlEntrypoint D_8010B7D0_w10[] = {
    { 0, func_801059D0_w10 },
    { 1, func_80105A0C_w10 },
    { 2, func_8010B5A4_w10 },
    { -1, NULL },
};
s16 D_8010B7F0_w10[4] = { 4, 0, 1, 2 }; /* character ids */
s32 D_8010B7F8_w10[6] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083 }; /* guide faces */
s32 D_8010B810_w10[2] = { 0xA0084, 0xA0085 };
Vec D_8010B818_w10[5] = {
    { -3.0f, 0.0f, -2.0f }, { 0.0f, 2.0f, 2.0f }, { 1.0f, 5.5f, -3.0f }, { 3.5f, 8.0f, 4.0f }, { -1.0f, 12.0f, 11.0f },
};
/* func_80105C48_w10 reads .z through the alias D_8010B85C_w10 (undefined_syms.txt) */
Vec D_8010B854_w10[5] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 0.0f, -30.0f }, { 45.0f, 0.0f, 45.0f },
};
s16 D_8010B890_w10[4] = { 0x1F, 0x18, -1, 0 };
s16 D_8010B898_w10[4] = { 1, 0, 0, 0 };
event_list_entry D_8010B8A0_w10[] = {
    { 1, 2, func_80105E10_w10 },
    { 0, 0, NULL },
};
event_table_entry D_8010B8B0_w10[] = {
    { 0x27, D_8010B8A0_w10 },
    { -1, NULL },
};
s32 D_8010B8C0_w10[10] = { 0x13000A, 0x13000B, 0x13000C, 0x13000D, 0x13000E, 0x13000F, 0x130010, 0x130011, 0x130012, 0x130013 }; /* DataRead ids */
s32 D_8010B8E8_w10[3] = { 0x130115, 0x130012, 0x130011 }; /* DataRead ids */
u32 D_8010B8F4_w10[2] = { 1, 0xA005E }; /* model file list (count, ids); no reference found */
s16 D_8010B8FC_w10 = -1;
u32 D_8010B900_w10[2] = { 1, 0xA0017 }; /* model file lists (count, ids) */
u32 D_8010B908_w10[2] = { 1, 0xA00F0 };
u32 D_8010B910_w10[2] = { 1, 0xA009D };
s32 D_8010B918_w10 = 0;
f32 D_8010B91C_w10[4][2] = { { 0.0f, 0.0f }, { -10.0f, 0.0f }, { 10.0f, 0.0f }, { 0.0f, -10.0f } }; /* x, z offsets */
