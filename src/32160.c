/* functions.us.h declares these with argument/return types that disagree with the code (an s32
   where the function takes or returns an s16); keep its declarations out of this unit. */
#define HmfAnimCreate HmfAnimCreate_functions_us_h
#define func_80032694_main func_80032694_main_functions_us_h
#define func_80032FF8_main func_80032FF8_main_functions_us_h
#define func_8003302C_main func_8003302C_main_functions_us_h
#include "common.h"
#include "mallocblock.h"
#undef HmfAnimCreate
#undef func_80032694_main
#undef func_80032FF8_main
#undef func_8003302C_main

/* Model textures, palettes and texture animations, from MP2 src/3D6A0.c (MP1 src/388E0.c).
   func_80031B30_main (texture image load) has no reference and stays asm. */

/* a texture animation slot */
typedef struct unk388E0Struct40 {
    /* 0x00 */ s16 unk_00; /* sprite bank, -1 for a free slot */
    /* 0x02 */ s16 unk_02; /* step */
    /* 0x04 */ s16 unk_04; /* animation */
    /* 0x06 */ s16 unk_06; /* ticks into the step */
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A; /* flags */
    /* 0x0B */ u8 unk_0B; /* speed, 16 = 1 */
} unk388E0Struct40; //sizeof 0xC

typedef struct unk388E0Struct44 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk388E0Struct44; //sizeof 4

/* one step of a sprite animation */
typedef struct unk388E0StructC4 {
    /* 0x00 */ s16 unk_00; /* frame, -1 for none */
    /* 0x02 */ s16 unk_02; /* duration */
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ char unk_07;
} unk388E0StructC4; //sizeof 8

typedef struct unk388E0StructC8 {
    /* 0x00 */ s16 unk_00; /* step count */
    /* 0x02 */ s16 unk_02; /* total duration */
    /* 0x04 */ unk388E0StructC4* unk_04;
} unk388E0StructC8; //sizeof 8

/* one sprite frame */
typedef struct unk388E0StructCC {
    /* 0x00 */ s16 unk_00; /* width */
    /* 0x02 */ s16 unk_02; /* height */
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08; /* palette size */
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ u16* unk_0C; /* palette */
    /* 0x10 */ void* unk_10; /* image */
} unk388E0StructCC; //sizeof 0x14

/* a sprite bank */
typedef struct unk388E0StructC0 {
    /* 0x00 */ s16 unk_00; /* frame count */
    /* 0x02 */ s16 unk_02; /* animation count */
    /* 0x04 */ s16 unk_04; /* palette size */
    /* 0x06 */ s16 unk_06; /* format */
    /* 0x08 */ s16 unk_08; /* users */
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ unk388E0StructCC* unk_0C;
    /* 0x10 */ unk388E0StructC8* unk_10;
    /* 0x14 */ u16* unk_14;
} unk388E0StructC0; //sizeof 0x18

typedef struct HmfPal {
    /* 0x00 */ char unk00[0x1C]; /* name */
    /* 0x1C */ u8 unk1C; /* users */
    /* 0x1D */ char unk1D;
    /* 0x1E */ s16 unk1E; /* colour count */
    /* 0x20 */ s16 unk20; /* name hash, 0 for a free entry */
    /* 0x22 */ char unk22[2];
    /* 0x24 */ void* unk24; /* owner */
    /* 0x28 */ u16* unk28; /* the palette */
} HmfPal; /* size = 0x2C */

/* MP3's texture entry: MP2's with the name hash at 0x22 and 16-bit dimensions */
typedef struct HmfTex {
    /* 0x00 */ char unk00[0x1C]; /* name */
    /* 0x1C */ u8 unk1C; /* format */
    /* 0x1D */ char unk1D[5];
    /* 0x22 */ u16 unk22; /* name hash, 0 for a free entry */
    /* 0x24 */ u16 unk24; /* width */
    /* 0x26 */ u16 unk26; /* height */
    /* 0x28 */ u8* unk28; /* image */
    /* 0x2C */ void* unk2C; /* owner */
    /* 0x30 */ HmfPal* unk30;
} HmfTex; /* size = 0x34 */

typedef struct HmfTexRef {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03; /* image segment, -1 for none */
    /* 0x04 */ s8 unk04; /* palette segment */
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ char unk08;
    /* 0x09 */ u8 unk09; /* texture animation slot; bit 7 pauses it */
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ HmfTex* unk0C;
} HmfTexRef; /* size = 0x10 (MP3 HmfData_Unk84_Entry) */

/* HmfData as the texture code reads it (MP3 layout: MP2's HmfData fields from 0x54 on sit
   4 bytes later) */
typedef struct HmfTexData {
    /* 0x00 */ char unk00[0xE];
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12; /* texture count */
    /* 0x14 */ char unk14[0x14];
    /* 0x28 */ char unk28[2];
    /* 0x2A */ s16 unk2A; /* texture animation count (MP2 0x28) */
    /* 0x2C */ char unk2C[4];
    /* 0x30 */ u8* unk30; /* chunk end */
    /* 0x34 */ u8* unk34; /* chunk start */
    /* 0x38 */ char unk38[0x4C];
    /* 0x84 */ HmfTexRef* unk84;
    /* 0x88 */ char unk88[0x40];
    /* 0xC8 */ u8* unkC8; /* texture animation slots (unk2A entries) */
} HmfTexData;

int strcmp(const char*, const char*);
char* strcpy(char*, const char*);
u8* func_80010A38_main(s32, u8*, u8*);
u8* func_80010AC8_main(u8*);
s16 func_80011334_main(void*, u8*, s16);
s16 func_80011460_main(u8*);

extern HmfTex D_800A1190_main; /* the default texture */
extern HmfTex* D_800D1FCC_main; /* 128 textures */
extern HmfPal* D_800CD2F8_main; /* 128 palettes */
extern u8 D_800CCF85_main; /* model load flags */
extern unk388E0Struct40* D_800D1714_main; /* 128 texture animation slots */
extern unk388E0StructC0* D_800D408C_main; /* 32 sprite banks */
extern Gfx* gMainGfxPos;

HmfPal* func_80032038_main(HmfTexData*, s16);
void func_80032194_main(HmfPal*);
void func_80032950_main(void);
void func_800333B0_main(s16);
HmfTex* func_80031A60_main(HmfTexData*, u8*);
void func_80031B30_main(u8*, HmfTexData*, HmfTex*);
void func_80031DF4_main(HmfTexData*);
void func_800321B8_main(u8*, HmfTexData*, HmfPal*);
void func_8003235C_main(void);
s16 func_800329B4_main(void*);
s16 func_80033F8C_main(void);
s16 func_80033FEC_main(void);
s16 func_80033D0C_main(HmfTexData*, u8*);

void func_80031560_main(void) {
    s16 i;

    D_800D1FCC_main = HuMemAlloc(128 * sizeof(HmfTex));
    D_800CD2F8_main = HuMemAlloc(128 * sizeof(HmfPal));

    for (i = 0; i < 128; i++) {
        D_800D1FCC_main[i].unk22 = 0;
    }

    for (i = 0; i < 128; i++) {
        D_800CD2F8_main[i].unk20 = 0;
    }

    D_800CCF85_main = 0;
    func_8003235C_main();
}

/* MP1 func_80037DA0 (src/388E0.c); MP2 prints and stops when the table is full */
void func_80031630_main(HmfTexData* arg0) {
    HmfTex* var_s0;
    s16 temp_s4;
    u8* var_s1;
    u8 sp10[32];
    s16 i;

    func_80031DF4_main(arg0);

    for (var_s1 = arg0->unk34; var_s1 < arg0->unk30;) {
        var_s1 = func_80010A38_main(0x424D5031, var_s1, arg0->unk30);
        if (var_s1 == NULL) {
            break;
        }

        temp_s4 = func_80011334_main(arg0, sp10, (var_s1[8] << 8) + var_s1[9]);
        for (i = 0; i < 128; i++) {
            if (D_800D1FCC_main[i].unk22 == temp_s4 && strcmp((char *)&D_800D1FCC_main[i], (char *)sp10) == 0) {
                break;
            }
        }

        if (i == 128) {
            for (i = 0; i < 128; i++) {
                if (D_800D1FCC_main[i].unk22 == 0) {
                    break;
                }
            }
            if (i == 128) {
                osSyncPrintf("TEXTURE OVER!\n");
                break;
            }
            var_s0 = &D_800D1FCC_main[i];
            var_s0->unk22 = temp_s4;
            strcpy((char *)var_s0, (char *)sp10);
            var_s0->unk2C = arg0;
            func_80031B30_main(var_s1, arg0, var_s0);
        } else {
            var_s0 = &D_800D1FCC_main[i];
            if (D_800CCF85_main & 2) {
                func_80019C00_main(var_s0->unk28);
                var_s0->unk2C = arg0;
                func_80031B30_main(var_s1, arg0, var_s0);
            }
        }

        var_s1 = func_80010AC8_main(var_s1 + 4);
    }
}

/* same c: marioparty func_80037FA0 (src/388E0.c) */
void func_8003186C_main(HmfTexData* arg0) {
    HmfTex* tex;
    HmfTexData* m;
    s16 i;
    s16 j;
    s16 k;

    if (arg0->unk84 != NULL) {
        for (i = 0; i < arg0->unk12; i++) {
            tex = arg0->unk84[i].unk0C;
            if (tex->unk22 == 0) {
                continue;
            }
            for (j = 0; j < 128; j++) {
                m = (HmfTexData*) HmfModelData[j].hmf;
                if (m == NULL) {
                    continue;
                }
                if (((u8) HmfModelData[j].unk00 != 0) | (arg0 == m)) {
                    continue;
                }
                if (m->unk84 == NULL) {
                    continue;
                }
                for (k = 0; k < m->unk12; k++) {
                    if (m->unk84[k].unk0C == tex) {
                        break;
                    }
                }
                if (k != m->unk12) {
                    break;
                }
            }
            if (j == 128) {
                tex->unk22 = 0;
                tex->unk2C = NULL;
                if (tex->unk1C == 2) {
                    func_80032194_main((HmfPal*) tex->unk30);
                }
                func_80019C00_main(tex->unk28);
            }
        }
    }
}

/* MP1 func_8003813C (src/388E0.c) */
HmfTex* func_80031A08_main(HmfTexData* arg0, s16 arg1) {
    u8 sp10[32];

    func_80011334_main(arg0, sp10, arg1);
    return func_80031A60_main(arg0, sp10);
}

/* exact c: marioparty func_800F7310_PaddleBattle (src/overlays/ovl_33_PaddleBattle/2341E0.c) */
/* 274D0 uses the result */
HmfTex* func_80031A44_main(HmfTexData* arg0, u8* arg1) {
    return func_80031A60_main(arg0, arg1);
}

/* MP1 func_80038194 (src/388E0.c) */
HmfTex* func_80031A60_main(HmfTexData* arg0, u8* arg1) {
    u16 temp_s2;
    u16 i;

    temp_s2 = func_80011460_main(arg1);

    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].unk22 != 0 && D_800D1FCC_main[i].unk22 == temp_s2
            && strcmp((char *)&D_800D1FCC_main[i], (char *)arg1) == 0) {
            break;
        }
    }

    if (i == 128) {
        return NULL;
    }

    return &D_800D1FCC_main[i];
}

INCLUDE_ASM("asm/nonmatchings/32160", func_80031B30_main);

/* MP1 func_800384FC (src/388E0.c) */
void func_80031DF4_main(HmfTexData* arg0) {
    HmfPal* var_s0;
    s16 temp_s4;
    u8* var_s1;
    u8 sp10[32];
    s16 i;

    for (var_s1 = arg0->unk34; var_s1 < arg0->unk30;) {
        var_s1 = func_80010A38_main(0x50414C31, var_s1, arg0->unk30);
        if (var_s1 == NULL) {
            break;
        }

        temp_s4 = func_80011334_main(arg0, sp10, (var_s1[8] << 8) + var_s1[9]);
        for (i = 0; i < 128; i++) {
            if (D_800CD2F8_main[i].unk20 == temp_s4 && strcmp((char *)&D_800CD2F8_main[i], (char *)sp10) == 0) {
                break;
            }
        }

        if (i == 128) {
            for (i = 0; i < 128; i++) {
                if (D_800CD2F8_main[i].unk20 == 0) {
                    break;
                }
            }
            if (i == 128) {
                break;
            }
            var_s0 = &D_800CD2F8_main[i];
            var_s0->unk20 = temp_s4;
            strcpy((char *)var_s0, (char *)sp10);
            var_s0->unk24 = arg0;
            var_s0->unk1C = 1;
            func_800321B8_main(var_s1, arg0, var_s0);
        } else {
            var_s0 = &D_800CD2F8_main[i];
            if (D_800CCF85_main & 2) {
                func_80019C00_main(var_s0->unk28);
                var_s0->unk24 = arg0;
                func_800321B8_main(var_s1, arg0, var_s0);
            }
            var_s0->unk1C++;
        }

        var_s1 = func_80010AC8_main(var_s1 + 4);
    }
}

/* MP1 func_80038720 (src/388E0.c) */
HmfPal* func_80032038_main(HmfTexData* arg0, s16 arg1) {
    u8 sp10[32];
    u16 id;
    u16 i;

    id = func_80011334_main(arg0, sp10, arg1);

    for (i = 0; i < 128; i++) {
        if ((u16) D_800CD2F8_main[i].unk20 != 0 && (u16) D_800CD2F8_main[i].unk20 == id
            && strcmp((char *)&D_800CD2F8_main[i], (char *)sp10) == 0) {
            break;
        }
    }

    if (i == 128) {
        return NULL;
    }

    return &D_800CD2F8_main[i];
}

/* MP1 func_800387DC (src/388E0.c) */
void func_80032104_main(HmfTexData* arg0) {
    s16 i;

    for (i = 0; i < 128; i++) {
        if (D_800CD2F8_main[i].unk20 != 0 && D_800CD2F8_main[i].unk24 == arg0) {
            func_80032194_main(&D_800CD2F8_main[i]);
        }
    }
}

/* MP1 func_80038864 (src/388E0.c) */
void func_80032194_main(HmfPal* arg0) {
    arg0->unk20 = 0;
    arg0->unk24 = NULL;
    func_80019C00_main(arg0->unk28);
}

/* MP1 func_80038888 (src/388E0.c, NON_MATCHING there) */
void func_800321B8_main(u8* arg0, HmfTexData* arg1, HmfPal* arg2) {
    u16* tbl;
    s16 count;
    s16 i;
    s32 c;

    arg0 += 0xA;
    count = (arg0[0] << 8) + arg0[1];
    arg2->unk28 = HuMemAllocTag(count * 2, 15000);
    arg2->unk1E = count;
    arg0 += 2;
    tbl = arg2->unk28;
    for (i = 0; i < count; i++) {
        tbl[i] = (c = ((arg0[i * 4 + 0] & 0xF8) << 8) + ((arg0[i * 4 + 1] & 0xF8) << 3) + ((arg0[i * 4 + 2] & 0xF8) >> 2),
                  (arg0[i * 4 + 3] >= 0x80) ? c + 1 : c);
    }
}

/* same c: marioparty func_8003897C (src/388E0.c) */
void func_800322AC_main(HmfTex* arg0) {
    s16 i;
    s16 j;
    HmfTexData* m;

    for (i = 0; i < 128; i++) {
        if (HmfModelData[i].hmf != NULL) {
            m = (HmfTexData*) HmfModelData[i].hmf;
            for (j = 0; j < m->unk12; j++) {
                if (m->unk84[j].unk0C == arg0) {
                    m->unk84[j].unk0C = &D_800A1190_main;
                }
            }
        }
    }
}

/* exact c: marioparty func_80038A2C (src/388E0.c) */
void func_8003235C_main(void) {
    s16 i;

    D_800D1714_main = HuMemAlloc(128 * sizeof(unk388E0Struct40));

    for (i = 0; i < 128; i++) {
        D_800D1714_main[i].unk_00 = -1;
    }

    func_80032950_main();
}

/* MP1 func_80038A9C (src/388E0.c); MP3 sets the bank's user count in func_800329B4_main:
   start a texture animation (sprite bank arg1) on the texture
   named arg3 in model arg0, or in every model when arg0 is -1 */
s16 HmfAnimCreate(HmfTexData* arg0, void* arg1, s16 arg2, char* arg3) {
    HmfTex* tex;
    s16 id;
    s16 i;
    s16 slot;
    s16 j;

    id = func_80011460_main((u8*) arg3);
    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].unk22 == id && strcmp((char *)&D_800D1FCC_main[i], arg3) == 0) {
            break;
        }
    }
    if (i == 128) {
        osSyncPrintf("Can't Find TextureName! EntryAnimMAn\n");
        return -1;
    }

    for (slot = 0; slot < 128; slot++) {
        if (D_800D1714_main[slot].unk_00 == -1) {
            break;
        }
    }
    if (slot == 128) {
        return -1;
    }

    D_800D1714_main[slot].unk_00 = func_800329B4_main(arg1);
    D_800D1714_main[slot].unk_04 = arg2;
    D_800D1714_main[slot].unk_02 = 0;
    D_800D1714_main[slot].unk_06 = 0;
    D_800D1714_main[slot].unk_0B = 0x10;
    D_800D1714_main[slot].unk_0A = 0;
    tex = &D_800D1FCC_main[i];
    if (arg0 != (HmfTexData*) -1) {
        for (i = 0; i < arg0->unk12; i++) {
            if (arg0->unk84[i].unk0C == tex) {
                arg0->unk84[i].unk09 = slot;
            }
        }
    } else {
        for (j = 0; j < 128; j++) {
            if (HmfModelData[j].hmf != NULL && (u8) HmfModelData[j].unk00 == 0) {
                arg0 = (HmfTexData*) HmfModelData[j].hmf;
                for (i = 0; i < arg0->unk12; i++) {
                    if (arg0->unk84[i].unk0C == tex) {
                        arg0->unk84[i].unk09 = slot;
                    }
                }
            }
        }
    }
    return slot;
}

/* MP1 func_80038D5C (src/388E0.c): link the texture named arg3 to the sprite bank of
   animation arg1 */
s16 func_80032694_main(HmfTexData* arg0, u16 arg1, s16 arg2, char* arg3) {
    HmfTex* tex;
    unk388E0Struct40* p;
    s16 id;
    s16 i;
    s16 slot;
    s16 j;

    id = func_80011460_main((u8*) arg3);
    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].unk22 == id && strcmp((char *)&D_800D1FCC_main[i], arg3) == 0) {
            break;
        }
    }
    if (i == 128) {
        osSyncPrintf("Can't Find TextureName! LinkAnimMAn\n");
        return -1;
    }

    slot = func_80033F8C_main();
    if (slot == -1) {
        return -1;
    }

    p = &D_800D1714_main[slot];
    p->unk_00 = D_800D1714_main[arg1].unk_00;
    p->unk_04 = arg2;
    p->unk_0A = 0;
    p->unk_06 = 0;
    p->unk_02 = 0;
    p->unk_0B = 0x10;
    D_800D408C_main[p->unk_00].unk_08++;
    tex = &D_800D1FCC_main[i];
    if (arg0 != (HmfTexData*) -1) {
        for (i = 0; i < arg0->unk12; i++) {
            if (arg0->unk84[i].unk0C == tex) {
                arg0->unk84[i].unk09 = slot;
            }
        }
    } else {
        for (j = 0; j < 128; j++) {
            if (HmfModelData[j].hmf != NULL && (u8) HmfModelData[j].unk00 == 0) {
                arg0 = (HmfTexData*) HmfModelData[j].hmf;
                for (i = 0; i < arg0->unk12; i++) {
                    if (arg0->unk84[i].unk0C == tex) {
                        arg0->unk84[i].unk09 = slot;
                    }
                }
            }
        }
    }
    return slot;
}

const s32 D_800A6D40_main = 1;

/* exact c: marioparty func_80039020 (src/388E0.c) */
void func_80032950_main(void) {
    s16 i;

    D_800D408C_main = HuMemAlloc(32 * sizeof(unk388E0StructC0));

    for (i = 0; i < 32; i++) {
        D_800D408C_main[i].unk_0C = 0;
    }
}

// register allocation: retail keeps nframes on the stack and data in s4 (masked ~297 words from
// the first frame on, 2 instructions short), as in MP2; u16 nframes does not move it. MP3 sets the
// bank's user count here (MP2 did it in the caller)
#ifdef NON_MATCHING
/* MP1 func_80039084 (src/388E0.c, NON_MATCHING there): load a sprite bank file into a free slot;
   MP2 frames carry their own palette */
s16 func_800329B4_main(void* arg) {
    u8* arg0 = arg;
    u8* data;
    s16 nframes;
    unk388E0StructC0* spr;
    s16 w;
    s16 h;
    unk388E0StructCC* fr;
    unk388E0StructC4* af;
    u8* p;
    u8* q;
    s16 bpp;
    s32 npal;
    s16 slot;
    s16 i;
    s16 j;
    s16 n;
    s16 t;
    s16 total;
    s16 d;

    for (slot = 0; slot < 32; slot++) {
        if (D_800D408C_main[slot].unk_0C == NULL) {
            break;
        }
    }
    if (slot == 32) {
        return -1;
    }

    spr = &D_800D408C_main[slot];
    spr->unk_06 = (arg0[0x18] << 8) + arg0[0x19];
    bpp = spr->unk_06 & 0xFF;
    npal = arg0[0x1A];
    spr->unk_04 = npal;
    p = arg0 + (arg0[0xD] << 16) + (arg0[0xE] << 8) + arg0[0xF];
    if (bpp < 9) {
        if (npal >= 2 && !(spr->unk_06 & 0x8000)) {
            spr->unk_14 = HuMemAllocTag(npal * 2, slot + 20000);
            bcopy(p, spr->unk_14, npal * 2);
        } else {
            spr->unk_04 = 0;
            spr->unk_14 = NULL;
        }
    } else {
        spr->unk_04 = 0;
        spr->unk_14 = NULL;
    }

    nframes = arg0[0x10];
    nframes = (nframes << 8) + arg0[0x11];
    spr->unk_00 = nframes;
    spr->unk_0C = HuMemAllocTag(nframes * sizeof(*spr->unk_0C), slot + 20000);
    p = arg0 + (arg0[1] << 16) + (arg0[2] << 8) + arg0[3];
    for (i = 0; i < nframes; i++) {
        fr = &spr->unk_0C[i];
        data = arg0 + (p[1] << 16) + (p[2] << 8) + p[3];
        w = fr->unk_00 = (p[4] << 8) + p[5];
        h = fr->unk_02 = (p[6] << 8) + p[7];
        fr->unk_04 = (p[8] << 8) + p[9];
        fr->unk_06 = (p[10] << 8) + p[11];
        fr->unk_10 = HuMemAllocTag(w * h * bpp / 8, slot + 20000);
        bcopy(data, fr->unk_10, w * h * bpp / 8);
        fr->unk_0C = spr->unk_14;
        fr->unk_08 = spr->unk_04;
        p += 12;
    }

    spr->unk_02 = n = (arg0[0x12] << 8) + arg0[0x13];
    if (n != 0) {
        spr->unk_10 = HuMemAllocTag(n * sizeof(*spr->unk_10), slot + 20000);
        p = arg0 + (arg0[5] << 16) + (arg0[6] << 8) + arg0[7];
        for (i = 0; i < n; i++) {
            q = arg0 + (p[i * 4 + 1] << 16) + (p[i * 4 + 2] << 8) + p[i * 4 + 3];
            spr->unk_10[i].unk_00 = t = (q[0] << 8) + q[1];
            spr->unk_10[i].unk_04 = HuMemAllocTag(t * sizeof(*spr->unk_10->unk_04), slot + 20000);
            q += 2;
            total = 0;
            for (j = 0; j < t; j++) {
                af = &spr->unk_10[i].unk_04[j];
                af->unk_00 = (q[0] << 8) + q[1];
                af->unk_02 = d = (q[2] << 8) + q[3];
                if (d > 0) {
                    total += d;
                }
                af->unk_04 = q[4];
                af->unk_05 = q[5];
                af->unk_06 = q[6];
                q += 7;
            }
            spr->unk_10[i].unk_02 = total;
        }
    } else {
        spr->unk_02 = 1;
        spr->unk_10 = HuMemAllocTag(sizeof(*spr->unk_10), slot + 20000);
        spr->unk_10->unk_00 = nframes;
        spr->unk_10->unk_04 = HuMemAllocTag(nframes * sizeof(*spr->unk_10->unk_04), slot + 20000);
        for (j = 0; j < nframes; j++) {
            af = &spr->unk_10->unk_04[j];
            af->unk_00 = j;
            af->unk_02 = 1;
            af->unk_05 = 0;
            af->unk_04 = 0;
            af->unk_06 = 0;
        }
        spr->unk_10->unk_02 = nframes;
    }
    D_800D408C_main[slot].unk_08 = 1;
    return slot;
}
#else
INCLUDE_ASM("asm/nonmatchings/32160", func_800329B4_main);
#endif

/* exact c: marioparty func_80039644 (src/388E0.c) */
void func_80032FC0_main(s16 arg0, u8 arg1, u8 arg2) {
    unk388E0Struct40* p = &D_800D1714_main[arg0];

    p->unk_0A = (p->unk_0A & ~arg1) | arg2;
}

/* exact c: marioparty func_8003967C (src/388E0.c) */
void func_80032FF8_main(s16 arg0, u8 arg1) {
    unk388E0Struct40* p = &D_800D1714_main[arg0];

    p->unk_04 = arg1;
    p->unk_02 = 0;
    p->unk_06 = 0;
}

/* exact c: marioparty func_800396B0 (src/388E0.c) */
void func_8003302C_main(s16 arg0, s32 arg1)
{
  unk388E0Struct40 *new_var2;
  unk388E0StructC8 *new_var;
  unk388E0Struct40 *p = &D_800D1714_main[arg0];
  new_var2 = p;
  new_var2->unk_02 = (u8) arg1;
  new_var = p->unk_04 + D_800D408C_main[new_var2->unk_00].unk_10;
  if (new_var->unk_00 <= ((u8) arg1))
  {
    p->unk_02 = ((u8) arg1) % new_var->unk_00;
  }
  p->unk_06 = 0;
  p->unk_0B = 0x10;
}

/* exact c: marioparty func_80039758 (src/388E0.c) */
u8 func_800330D4_main(s16 arg0)
{
  unk388E0StructC8 *new_var;
  unk388E0Struct40 *p = &D_800D1714_main[arg0];
  new_var = &D_800D408C_main[p->unk_00].unk_10[p->unk_04];
  return (*new_var).unk_00;
}

/* MP1 func_800397AC (src/388E0.c): advance every texture animation by arg0 ticks; MP2 adds
   the pause flag 4 and restarts a looping animation at its first tick */
void func_80033128_main(u16 arg0) {
    unk388E0Struct40* p;
    unk388E0StructC8* bank;
    s16 i;
    s16 k;

    for (i = 0; i < 128; i++) {
        if (D_800D1714_main[i].unk_00 == -1) {
            continue;
        }
        if (D_800D1714_main[i].unk_0A & 4) {
            continue;
        }
        p = &D_800D1714_main[i];
        if (p->unk_0A & 1) {
            continue;
        }
        bank = &D_800D408C_main[p->unk_00].unk_10[p->unk_04];
        for (k = 0; k < arg0; k++) {
            p->unk_06 += p->unk_0B;
            while (p->unk_06 >= bank->unk_04[p->unk_02].unk_02 * 16) {
                p->unk_06 -= bank->unk_04[p->unk_02].unk_02 * 16;
                p->unk_02++;
                if (bank->unk_00 <= p->unk_02) {
                    if ((p->unk_0A & 2) || bank->unk_04[p->unk_02 - 1].unk_02 != -1) {
                        p->unk_02--;
                    } else {
                        p->unk_02 = 0;
                        p->unk_06 = 0;
                    }
                }
            }
        }
    }
}

/* exact c: marioparty func_80039970 (src/388E0.c) */
void func_800332D4_main(s16 arg0, f32 arg1) {
    D_800D1714_main[arg0].unk_0B = arg1 * 16.0f;
}

/* exact c: marioparty func_800399F0 (src/388E0.c) */
void func_80033354_main(s16 arg0) {
    unk388E0Struct40* p = &D_800D1714_main[arg0];

    if (p->unk_00 != -1) {
        func_800333B0_main(p->unk_00);
        p->unk_00 = -1;
    }
}

/* exact c: marioparty func_80039A4C (src/388E0.c) */
void func_800333B0_main(s16 arg0) {
    if (D_800D408C_main[arg0].unk_0C != 0) {
        if (--D_800D408C_main[arg0].unk_08 == 0) {
            func_80019C68_main(arg0 + 20000);
            D_800D408C_main[arg0].unk_0C = 0;
        }
    }
}

/* exact c: marioparty func_80039ACC (src/388E0.c) */
void func_80033430_main(s16 arg0) {
    func_80033354_main(arg0);
}

/* exact c: marioparty func_80039AEC (src/388E0.c) */
void func_80033450_main(void) {
    s16 i;

    for (i = 0; i < 32; i++) {
        if (D_800D408C_main[i].unk_0C != NULL) {
            D_800D408C_main[i].unk_0C = NULL;
            func_80019C68_main(i + 20000);
        }
    }

    for (i = 0; i < 128; i++) {
        D_800D1714_main[i].unk_00 = -1;
    }
}

/* MP1 func_80039BAC (src/388E0.c) */
void func_80033510_main(void) {
    s16 i;

    for (i = 0; i < 128; i++) {
        D_800D1FCC_main[i].unk22 = 0;
    }

    for (i = 0; i < 128; i++) {
        D_800CD2F8_main[i].unk20 = 0;
    }

    func_80019C68_main(15000);
}

/* MP1 func_80039C48 (src/388E0.c): the size of the texture named arg0 */
void func_800335BC_main(char* arg0, void* arg1) {
    unk388E0Struct44* out = arg1;
    u16 id;
    u16 i;

    id = func_80011460_main((u8*) arg0);

    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].unk22 == id && strcmp((char *)&D_800D1FCC_main[i], arg0) == 0) {
            break;
        }
    }

    if (i == 128) {
        return;
    }
    out->unk_00 = D_800D1FCC_main[i].unk24;
    out->unk_02 = D_800D1FCC_main[i].unk26;
}


// register allocation and scheduling of the animation-slot lookup (masked 25), as in MP1/MP2;
// testing unk09 directly or a u8 slot does not fix it
#ifdef NON_MATCHING
/* MP1 func_80039D10 (src/388E0.c, NON_MATCHING there): point each texture's segments at its
   image and palette, or at the current frame of its texture animation */
void func_80033694_main(HmfTexData* arg0) {
    unk388E0Struct40* p;
    unk388E0StructC0* spr;
    HmfTex* tex;
    s16 frame;
    s16 i;
    s32 idx;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk03 == -1) {
            continue;
        }
        idx = arg0->unk84[i].unk09;
        if (!(idx & 0x80)) {
            p = &D_800D1714_main[idx];
            if (p->unk_00 != -1) {
                spr = &D_800D408C_main[p->unk_00];
                frame = spr->unk_10[p->unk_04].unk_04[p->unk_02].unk_00;
                if (frame != -1) {
                    gSPSegment(gMainGfxPos++, arg0->unk84[i].unk03,
                               osVirtualToPhysical(spr->unk_0C[frame].unk_10));
                    if (D_800D408C_main[p->unk_00].unk_14 != NULL) {
                        gSPSegment(gMainGfxPos++, arg0->unk84[i].unk04,
                                   osVirtualToPhysical(spr->unk_0C[frame].unk_0C));
                    }
                    continue;
                }
            }
        }
        tex = arg0->unk84[i].unk0C;
        gSPSegment(gMainGfxPos++, arg0->unk84[i].unk03, osVirtualToPhysical(tex->unk28));
        if (tex->unk30 != NULL) {
            gSPSegment(gMainGfxPos++, arg0->unk84[i].unk04, osVirtualToPhysical(tex->unk30->unk28));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/32160", func_80033694_main);
#endif

/* same c: marioparty func_80039F9C (src/388E0.c) */
void func_80033910_main(HmfTexData* arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk03 != -1) {
            arg0->unk84[i].unk09 |= 0x80;
        }
    }
}

/* same c: marioparty func_80039FFC (src/388E0.c) */
void func_80033970_main(HmfTexData* arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk03 != -1) {
            arg0->unk84[i].unk09 &= 0x7F;
        }
    }
}

/* start the texture animations a model file defines ("VX" entries of its MTN1 chunks); their
   slots are kept in the model (unkC8, unk28). Returns 0 when it has none */
s32 func_800339D0_main(HmfTexData* arg0) {
    u8 sp10[32];
    HmfTexRef* ref;
    HmfTex* tex;
    u8* chunk;
    u8* p;
    u8* e;
    s16 n;
    s16 k;
    s16 cnt;
    s16 slot;
    s16 id;
    s16 i;

    n = 0;
    chunk = arg0->unk34;
    while (TRUE) {
        chunk = func_80010A38_main(0x4D544E31, chunk, arg0->unk30);
        if (chunk == NULL) {
            break;
        }
        p = chunk + 0xD;
        cnt = chunk[0xA];
        for (k = 0; k < cnt; k++) {
            e = p;
            p += (p[0] << 8) + p[1] + 2;
            if (e[2] != 'V' || e[3] != 'X') {
                continue;
            }
            e += 4;
            slot = func_80033F8C_main();
            if (slot == -1) {
                break;
            }
            sp10[n] = slot;
            D_800D1714_main[slot].unk_00 = func_80033D0C_main(arg0, e);
            D_800D1714_main[slot].unk_04 = 0;
            D_800D1714_main[slot].unk_02 = 0;
            D_800D1714_main[slot].unk_06 = 0;
            D_800D1714_main[slot].unk_0B = 0x10;
            D_800D1714_main[slot].unk_0A = 4;
            D_800D408C_main[D_800D1714_main[slot].unk_00].unk_08 = 1;
            ref = &arg0->unk84[(e[2] << 8) + e[3]];
            id = ref->unk0C->unk22;
            for (i = 0; i < 128; i++) {
                if (D_800D1FCC_main[i].unk22 == id && strcmp((char *)&D_800D1FCC_main[i], (char *)ref->unk0C) == 0) {
                    break;
                }
            }
            tex = &D_800D1FCC_main[i];
            for (i = 0; i < arg0->unk12; i++) {
                if (arg0->unk84[i].unk0C == tex) {
                    arg0->unk84[i].unk09 = slot;
                }
            }
            n++;
        }
        chunk = func_80010AC8_main(chunk + 4);
    }
    if (n == 0) {
        arg0->unkC8 = NULL;
        return 0;
    }
    arg0->unkC8 = HuMemAllocTag(n, arg0->unk0E + 1);
    for (i = 0; i < n; i++) {
        arg0->unkC8[i] = sp10[i];
    }
    arg0->unk2A = n;
    return 1;
}

/* build a sprite bank whose frames are the model's own textures (a "VX" entry at arg1:
   frame count, then texture index and duration per frame); the last step loops */
s16 func_80033D0C_main(HmfTexData* arg0, u8* arg1) {
    unk388E0StructC0* spr;
    unk388E0StructCC* fr;
    unk388E0StructC4* af;
    HmfTex* tex;
    u8* p;
    s16 slot;
    s16 n;
    s16 id;
    s16 i;
    s16 total;

    af = NULL;
    slot = func_80033FEC_main();
    if (slot == -1) {
        return -1;
    }
    spr = &D_800D408C_main[slot];
    n = (arg1[4] << 8) + arg1[5];
    spr->unk_00 = n;
    spr->unk_0C = HuMemAllocTag(n * sizeof(*spr->unk_0C), id = slot + 20000);
    p = arg1 + 6;
    spr->unk_06 = (arg1[0x18] << 8) + arg1[0x19];
    spr->unk_02 = 1;
    spr->unk_10 = HuMemAllocTag(sizeof(*spr->unk_10), id);
    spr->unk_10->unk_00 = n + 1;
    spr->unk_10->unk_04 = HuMemAllocTag((n + 1) * sizeof(*spr->unk_10->unk_04), id);
    total = 0;
    for (i = 0; i < n; i++) {
        fr = &spr->unk_0C[i];
        af = &spr->unk_10->unk_04[i];
        tex = func_80031A08_main(arg0, (p[0] << 8) + p[1]);
        fr->unk_00 = tex->unk24;
        fr->unk_02 = tex->unk26;
        fr->unk_06 = 0;
        fr->unk_04 = 0;
        fr->unk_10 = tex->unk28;
        af->unk_00 = i;
        af->unk_02 = (p[2] << 8) + p[3];
        if (af->unk_02 == 0) {
            af->unk_02 = 1;
        }
        if (af->unk_02 > 0) {
            total += af->unk_02;
        }
        af->unk_06 = 0;
        af->unk_05 = 0;
        af->unk_04 = 0;
        if (tex->unk1C == 2) {
            fr->unk_08 = tex->unk30->unk1E;
            fr->unk_0C = tex->unk30->unk28;
        }
        p += 4;
    }
    af++; /* retail writes through NULL + 8 when n is 0 */
    af->unk_00 = 0;
    af->unk_02 = -1;
    spr->unk_10->unk_02 = total;
    spr->unk_04 = spr->unk_0C->unk_08;
    spr->unk_14 = spr->unk_0C->unk_0C;
    return slot;
}

/* a free texture animation slot, or -1 */
s16 func_80033F8C_main(void) {
    s16 i;

    for (i = 0; i < 128; i++) {
        if (D_800D1714_main[i].unk_00 == -1) {
            return i;
        }
    }
    return -1;
}

/* a free sprite bank slot, or -1 */
s16 func_80033FEC_main(void) {
    s16 i;

    for (i = 0; i < 32; i++) {
        if (D_800D408C_main[i].unk_0C == NULL) {
            return i;
        }
    }
    return -1;
}

/* restart texture animation arg0 and advance it by arg1 ticks (16 per frame unit at speed 1) */
void func_80034048_main(s16 arg0, s16 arg1) {
    unk388E0Struct40* p;
    unk388E0StructC8* bank;
    s16 k;

    if (D_800D1714_main[arg0].unk_00 == -1) {
        return;
    }
    p = &D_800D1714_main[arg0];
    bank = &D_800D408C_main[p->unk_00].unk_10[p->unk_04];
    p->unk_02 = 0;
    p->unk_06 = 0;
    for (k = 0; k < arg1; k++) {
        p->unk_06++;
        while (p->unk_06 >= bank->unk_04[p->unk_02].unk_02) {
            p->unk_06 -= bank->unk_04[p->unk_02].unk_02;
            p->unk_02++;
            if (bank->unk_00 <= p->unk_02) {
                if ((p->unk_0A & 2) || bank->unk_04[p->unk_02 - 1].unk_02 != -1) {
                    p->unk_02--;
                } else {
                    p->unk_02 = 0;
                    p->unk_06 = 0;
                }
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D44_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D4C_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D50_main);
