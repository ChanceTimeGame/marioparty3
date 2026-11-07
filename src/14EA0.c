/* functions.us.h declares these with other parameter types: HmfSprModelCreate's third is u8 there
   but 16-bit in retail (the callee stores it with sh unmasked and func_80014618_main passes it
   masked to 0xFFFF); func_800142A0_main's is s32 there (s16 here), func_80014A3C_main's u32 (a signed
   compare here), func_80017790_main's second s32 (sign-extended here),
   func_80017AD8_main's return u8 (s16 here). Keep the header's out of this unit. */
#define HmfSprModelCreate HmfSprModelCreate_header
#define func_800142A0_main func_800142A0_main_header
#define func_80014A3C_main func_80014A3C_main_header
#define func_80017790_main func_80017790_main_header
#define func_80017AD8_main func_80017AD8_main_header
#include "common.h"
#undef HmfSprModelCreate
#undef func_800142A0_main
#undef func_80014A3C_main
#undef func_80017790_main
#undef func_80017AD8_main
#include "mallocblock.h"
#include "malloc.h"
#include "gcc/string.h"

/* Sprite-model slots and the matrix helpers. C from MP2 src/21920.c / src/26370.c and MP1
   src/1EA70.c / src/engine/math.c; functions with no reference stay in asm. */

typedef f32 Matrix4f[4][4];
typedef f32 Matrix3f[3][3];

/* Sprite-model slot (MP2 unk_800ECDE0, include/game/sprite.h there). */
typedef struct unk_800ECDE0 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8* unk20; /* key-frame list */
} unk_800ECDE0; /* size = 0x24 */

#define TEX_MASK(x) ((x) < 3 ? 1 : (x) < 5 ? 2 : (x) < 9 ? 3 : (x) < 17 ? 4 : (x) < 33 ? 5 : (x) < 65 ? 6 : (x) < 129 ? 7 : (x) < 257 ? 8 : 9)

typedef struct SprBankFrame {
    /* 0x00 */ s16 unk_00; /* width */
    /* 0x02 */ s16 unk_02; /* height */
    /* 0x04 */ s16 unk_04; /* x origin */
    /* 0x06 */ s16 unk_06; /* y origin */
    /* 0x08 */ u16 unk_08; /* palette size */
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ u16* unk_0C; /* palette */
    /* 0x10 */ void* unk_10; /* image */
} SprBankFrame; // sizeof 0x14

typedef struct SprBankStep {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02; /* duration, -1 to hold */
    /* 0x04 */ char unk_04[4];
} SprBankStep; // sizeof 8

typedef struct SprBankAnim {
    /* 0x00 */ s16 unk_00; /* step count */
    /* 0x02 */ s16 unk_02; /* total duration */
    /* 0x04 */ SprBankStep* unk_04;
} SprBankAnim; // sizeof 8

typedef struct SprBank {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04; /* 0: intensity image (flag 0x8000: 4-bit), else colour-index bits */
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08; /* reference count */
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ SprBankFrame* unk_0C;
    /* 0x10 */ SprBankAnim* unk_10;
    /* 0x14 */ u16* unk_14; /* palette */
} SprBank; // sizeof 0x18

extern u8 D_800A0620_main; /* slots initialised */
extern unk_800ECDE0* D_800CBB60_main;
extern Vtx* D_800CC080_main[]; /* per frame buffer: vertex pool */
extern u16 D_800CDD4E_main; /* slot count */
extern Vtx* D_800CDD54_main;
extern Gfx* D_800D1F30_main;
extern u8 D_800D2008_main;
extern SprBank* D_800D408C_main;
extern s16 D_800A0624_main[4]; /* texture filter by slot flags 0x18 */
extern s8 HmfPauseF;
/* D_800D1360 (variables.h: UnkOvl81) is, in main, the per-frame-buffer display-list pool. */
#define SPR_GFX_POOL ((Gfx**) &D_800D1360)

/* Matrix bake record (MP1/MP2 unk1EA70StructC). */
typedef struct unk1EA70StructC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16* unk_04;
    /* 0x08 */ Matrix4f* unk_08;
} unk1EA70StructC; // sizeof 0xC

/* HmfData's motion objects (MP2 HmfMotionObj; MP1 unk2C0C0Struct50). */
typedef struct HmfMotionObj {
    /* 0x00 */ s16 unk00; /* child count */
    /* 0x02 */ char unk02[2];
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ Vec unk28;
    /* 0x34 */ Vec unk34;
    /* 0x40 */ Vec unk40;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ char unk4F;
    /* 0x50 */ s16* unk50; /* children: part index, or 0x8000 | motion object index */
    /* 0x54 */ HmfData* unk54; /* the model owning the parts */
    /* 0x58 */ f32 unk58[4][4];
} HmfMotionObj; /* size = 0x98 */

/* A model part (MP2 HmfPart, there with its name at 0x12). */
typedef struct HmfPartView {
    /* 0x00 */ char unk00[0x26]; /* name */
    /* 0x26 */ s16 unk26; /* name hash (func_80011460_main of unk00) */
    /* 0x28 */ char unk28[0x40];
} HmfPartView; /* size = 0x68 */

/* A transform-tree node (MP2 HitXform). */
typedef struct HitXformView {
    /* 0x00 */ s16 unk00; /* part index, < 0 for none */
    /* 0x02 */ char unk02[0x46];
    /* 0x48 */ HmfData* unk48;
    /* 0x4C */ f32 unk4C[4][4];
} HitXformView; /* size 0x8C */

/* The fields of HmfData this unit reads (include/game/hmfman.h leaves most of them unnamed). */
typedef struct HmfDataView {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s16 unk10; /* part count */
    /* 0x12 */ char unk12[4];
    /* 0x16 */ s16 unk16; /* motion object count */
    /* 0x18 */ char unk18[0x48];
    /* 0x60 */ HmfPartView* unk60;
    /* 0x64 */ s16 unk64; /* transform-tree node count */
    /* 0x66 */ char unk66[2];
    /* 0x68 */ HitXformView* unk68;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ HmfMotionObj* unk80; /* motion objects (unk16), -1 for none */
} HmfDataView;

extern Matrix4f* D_800D1358_main; /* matrix table being filled */
extern s16* D_800D04B4_main; /* per matrix: its motion object */
extern s16 D_800CD1B0_main; /* matrices written */
extern s16 D_800D138A_main; /* matrix stack depth */
extern Matrix4f D_800D5A00_main[]; /* matrix stack */

void func_8002DFF8_main(HmfData*, f32, D_800CCF58_main_Struct*, s32); /* motion apply (MP2 func_80039B54_3A754) */
s16 func_8002C834_main(HmfData*, char*); /* part by name (MP2 func_80038398_38F98) */
void func_8002367C_main(Matrix4f, Matrix4f); /* matrix copy (MP1 func_8002C37C) */
void func_8008A070_main(Matrix4f); /* identity */
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_800169E0_main(s16 arg0, s16 arg1, unk1EA70StructC* arg2, s16 arg3);
void func_80016C2C_main(HmfData* arg0, s16 arg1, s16 arg2);
s16 func_80011460_main(char*); /* name hash */

/* Texture-animation slot (MP2 TexAnimSlot). */
typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; //sizeof 0xC

extern TexAnimSlot* D_800D1714_main;
extern s16 D_800D4090_main[6][3][7]; /* loaded texture animations, -1 none */
extern u8 D_800D6A50_main[6]; /* set while a character has one loaded */
extern u8 D_800D20B8_main[16][3];
extern s16 D_800A06FC_main[]; /* [entry * 3 + set]: file index */
extern s32 D_800A0728_main[7];    /* per character: data directory << 16 */
extern u16 D_800A0748_main[];     /* character 7: directory << 8 | index */
extern u8 D_800D5570_main[16][3];
extern char* D_800A063C_main[3 * 16]; /* per set (x16) and animation: texture-animation name */
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData*);
void func_80033970_main(HmfData*);
s16 func_800329B4_main(void*);
s32 HmfSprModelCreate(void* arg0, s32 arg1, u16 arg2);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);

void func_800142A0_main(s16 arg0) {
    s16 i;
    unk_800ECDE0* temp_v1;

    D_800CDD4E_main = arg0;
    for (i = 0; i < D_800D1FF0_main; i++) {
        D_800CC080_main[i] = HuMemAllocTag(arg0 * (8 * sizeof(Vtx)), 0x7530);
        SPR_GFX_POOL[i] = HuMemAllocTag(arg0 * (32 * sizeof(Gfx)), 0x7530);
    }
    D_800CBB60_main = HuMemAllocTag(arg0 * sizeof(*D_800CBB60_main), 0x7530);
    for (i = 0; i < arg0; i++) {
        temp_v1 = &D_800CBB60_main[i];
        temp_v1->unk00 = -1;
    }
    D_800A0620_main = 1;
    func_800143F0_main();
}

void func_800143F0_main(void) {
    u8 temp_v0;

    if (D_800A0620_main != 0) {
        temp_v0 = D_800D2008_main;
        D_800CDD54_main = D_800CC080_main[temp_v0];
        D_800D1F30_main = SPR_GFX_POOL[temp_v0];
    }
}

s32 HmfSprModelCreate(void* arg0, s32 arg1, u16 arg2) {
    s16 temp;
    s16 i;
    unk_800ECDE0* p2;

    for (i = 0; i < D_800CDD4E_main; i++) {
        if (D_800CBB60_main[i].unk00 == -1) {
            break;
        }
    }
    if (i == D_800CDD4E_main || (temp = func_8001A894_main(arg1, 0, 4)) == -1) {
        return 0xFFFF;
    }
    D_800CBB60_main[i].unk00 = temp;
    if (arg0 != (void*) -1) {
        temp = func_800329B4_main(arg0);
        D_800D408C_main[temp].unk_08 = 1;
        if (temp == -1) {
            func_8001ACDC_main(D_800CBB60_main[i].unk00);
            D_800CBB60_main[i].unk00 = -1;
        }
    } else {
        temp = -1;
    }
    D_800CBB60_main[i].unk02 = temp;
    D_800CBB60_main[i].unk10 = arg2;
    D_800CBB60_main[i].unk12 = D_800CBB60_main[i].unk13 = D_800CBB60_main[i].unk14 = D_800CBB60_main[i].unk15 = 0xFF;
    p2 = &D_800CBB60_main[i];
    p2->unk0A = 0;
    p2->unk08 = 0;
    p2->unk04 = 0;
    p2->unk06 = 0;
    p2->unk20 = 0;
    return (u16) i;
}

/* Copies slot index's model into a new slot sharing its sprite bank (one more reference). */
u16 func_80014618_main(s16 index, u16 arg1) {
    s16 temp_v0;

    temp_v0 = HmfSprModelCreate((void*) -1, HmfModelData[D_800CBB60_main[index].unk00].unk18, arg1);
    D_800CBB60_main[temp_v0].unk02 = D_800CBB60_main[index].unk02;
    D_800D408C_main[D_800CBB60_main[temp_v0].unk02].unk_08++;
    return temp_v0;
}

void func_800146DC_main(s16 index, s32 arg1, s32 arg2) {
    unk_800ECDE0* temp_v1;

    temp_v1 = &D_800CBB60_main[index];
    temp_v1->unk10 = temp_v1->unk10 & ~arg1;
    temp_v1->unk10 = arg2 | temp_v1->unk10;
}

void func_80014714_main(s16 index, u16 arg1) {
    D_800CBB60_main[index].unk04 = arg1;
}

/* Starts animation arg1 from its first step. */
void func_8001473C_main(s16 index, s16 arg1) {
    D_800CBB60_main[index].unk06 = arg1;
    D_800CBB60_main[index].unk04 = 0;
    D_800CBB60_main[index].unk08 = 0;
}

u16 func_8001476C_main(s16 index) {
    return D_800CBB60_main[index].unk04;
}

void func_80014794_main(s16 index, u8 arg1) {
    s32 unk_var;

    if (index != -1) {
        D_800CBB60_main[index].unk12 = arg1;
        unk_var = (arg1 != 0xFF) << 0x10;
        func_8001C2FC_main(D_800CBB60_main[index].unk00, 0x10000, unk_var);
    }
}

void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3) {
    if (index != -1) {
        D_800CBB60_main[index].unk13 = arg1;
        D_800CBB60_main[index].unk14 = arg2;
        D_800CBB60_main[index].unk15 = arg3;
    }
}

void func_80014850_main(s16 index) {
    unk_800ECDE0* temp_v1;

    temp_v1 = &D_800CBB60_main[index];
    temp_v1->unk0A = 0;
    temp_v1->unk04 = 0;
    temp_v1->unk10 = temp_v1->unk10 & 0xFF7F;
    func_8001C258_main(temp_v1->unk00, 4, 0);
}

void func_800148A8_main(s16 index, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    if (index != -1) {
        func_800146DC_main(index, 0x40, 0x40);
        D_800CBB60_main[index].unk16 = arg1;
        D_800CBB60_main[index].unk17 = arg2;
        D_800CBB60_main[index].unk18 = arg3;
        D_800CBB60_main[index].unk19 = arg4;
        D_800CBB60_main[index].unk1A = arg5;
        D_800CBB60_main[index].unk1B = arg6;
        D_800CBB60_main[index].unk1C = arg7;
        D_800CBB60_main[index].unk1D = arg8;
    }
}

void func_800149D0_main(s16 index, u8* arg1) {
    if (index != -1) {
        func_800146DC_main(index, 0x40, 0x40);
        D_800CBB60_main[index].unk20 = arg1;
        D_800CBB60_main[index].unk0E = 0;
        D_800CBB60_main[index].unk0C = 0;
    }
}

/* Draws every live sprite-model slot into its model's display list and advances its animation
   by arg0 ticks (MP2 func_80021490_22090, MP1 func_8001E5A0). */
void func_80014A3C_main(s32 arg0) {
    unk_800ECDE0* spr;
    HmfData* model;
    SprBank* info;
    SprBankAnim* anim;
    SprBankFrame* frame;
    u8* key;
    u16 end;
    u8* prev;
    f32 t;
    s16 pos;
    s16 len;
    u16 w;
    u16 h;
    s16 x;
    s16 y;
    s16 j;
    s16 i;
    s16 nh;

    if (D_800A0620_main == 0) {
        return;
    }
    for (i = 0; i < D_800CDD4E_main; i++) {
        if (D_800CBB60_main[i].unk00 == -1) {
            continue;
        }
        spr = &D_800CBB60_main[i];
        if (HmfModelData[spr->unk00].unk18 & 4) {
            continue;
        }
        if ((u16) spr->unk02 == 0xFFFF) {
            continue;
        }
        if (spr->unk10 & 0x80) {
            func_8001C258_main(spr->unk00, 4, 4);
            spr->unk10 &= ~0x80;
            continue;
        }
        model = HmfModelData[spr->unk00].hmf;
        *(Gfx**) model->unk3C = D_800D1F30_main; /* unk3C is a single Gfx* list here */
        info = &D_800D408C_main[(u16) spr->unk02];
        anim = &info->unk_10[spr->unk06];
        gDPSetCycleType(D_800D1F30_main++, G_CYC_1CYCLE);
        if (spr->unk10 & 0x40) {
            if (spr->unk20 != 0) {
                key = spr->unk20;
                while (*key != 0xFF) {
                    if (spr->unk0A < *key) {
                        break;
                    }
                    key += 5;
                }
                if (*key == 0xFF) {
                    end = anim->unk_02;
                } else {
                    end = *key;
                }
                prev = key - 5;
                pos = spr->unk0A - prev[0];
                len = end - prev[0];
                t = (f32) pos / (f32) len;
                spr->unk13 = prev[1] + (key[1] - prev[1]) * t;
                spr->unk14 = prev[2] + (key[2] - prev[2]) * t;
                spr->unk15 = prev[3] + (key[3] - prev[3]) * t;
                spr->unk12 = prev[4] + (key[4] - prev[4]) * t;
            } else {
                t = (f32) spr->unk0A / (f32) anim->unk_02;
                spr->unk13 = (u8) spr->unk16 + (spr->unk1A - (u8) spr->unk16) * t;
                spr->unk14 = (u8) spr->unk17 + (spr->unk1B - (u8) spr->unk17) * t;
                spr->unk15 = (u8) spr->unk18 + (spr->unk1C - (u8) spr->unk18) * t;
                spr->unk12 = spr->unk19 + (spr->unk1D - spr->unk19) * t;
            }
        }
        if (info->unk_04 == 0) {
            if (info->unk_06 & 0x8000) {
                gDPSetCombine(D_800D1F30_main++, 0xFF97FF, 0xFF2DFEFF);
            } else {
                gDPSetCombine(D_800D1F30_main++, 0x119623, 0xFF2FFFFF);
            }
            model->unk60->unk50 |= 0x10000;
            if (spr->unk10 & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, 0x5041C8, 0);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, 0x5049D8, 0);
            }
            gDPSetAlphaCompare(D_800D1F30_main++, G_AC_THRESHOLD);
            gDPSetBlendColor(D_800D1F30_main++, 0, 0, 0, 1);
            gDPSetPrimColor(D_800D1F30_main++, 0, 0, spr->unk13, spr->unk14, spr->unk15, spr->unk12);
        } else if (spr->unk12 == 0xFF) {
            if (spr->unk10 & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, 0x553048, 0);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, 0x553078, 0);
            }
            gDPSetCombine(D_800D1F30_main++, 0xFFFFFF, 0xFFFCF279);
        } else {
            model->unk60->unk50 |= 0x10000;
            gDPSetAlphaCompare(D_800D1F30_main++, G_AC_THRESHOLD);
            gDPSetBlendColor(D_800D1F30_main++, 0, 0, 0, 1);
            gDPSetPrimColor(D_800D1F30_main++, 0, 0, 0, 0, 0, spr->unk12);
            if (spr->unk10 & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, 0x5041C8, 0);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, 0x5049D8, 0);
            }
            gDPSetCombine(D_800D1F30_main++, 0x121624, 0xFF2FFFFF);
        }
        gDPSetTextureFilter(D_800D1F30_main++, D_800A0624_main[(spr->unk10 & 0x18) >> 3]);
        gSPClearGeometryMode(D_800D1F30_main++, G_LIGHTING | G_CULL_BACK);
        gSPSetGeometryMode(D_800D1F30_main++, G_ZBUFFER);
        frame = &info->unk_0C[anim->unk_04[(s16) spr->unk04].unk_00];
        w = frame->unk_00;
        h = frame->unk_02;
        if (info->unk_04 == 0) {
            gDPSetTextureLUT(D_800D1F30_main++, G_TT_NONE);
            if (info->unk_06 & 0x8000) {
                gDPLoadTextureBlock_4b(D_800D1F30_main++, frame->unk_10, G_IM_FMT_I, (s16) w, (s16) h, 0, G_TX_CLAMP, G_TX_CLAMP,
                                       TEX_MASK(frame->unk_00), TEX_MASK(frame->unk_02), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureBlock(D_800D1F30_main++, frame->unk_10, G_IM_FMT_IA, G_IM_SIZ_8b, (s16) w, (s16) h, 0, G_TX_CLAMP,
                                    G_TX_CLAMP, TEX_MASK(frame->unk_00), TEX_MASK(frame->unk_02), G_TX_NOLOD, G_TX_NOLOD);
            }
        } else {
            gDPSetTextureLUT(D_800D1F30_main++, G_TT_RGBA16);
            if (info->unk_04 < 0x11) {
                gDPLoadTLUT_pal16(D_800D1F30_main++, 0, info->unk_14);
                gDPLoadTextureBlock_4b(D_800D1F30_main++, frame->unk_10, G_IM_FMT_CI, (s16) w, (s16) h, 0, G_TX_CLAMP, G_TX_CLAMP,
                                       TEX_MASK(frame->unk_00), TEX_MASK(frame->unk_02), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTLUT_pal256(D_800D1F30_main++, info->unk_14);
                gDPLoadTextureBlock(D_800D1F30_main++, frame->unk_10, G_IM_FMT_CI, G_IM_SIZ_8b, (s16) w, (s16) h, 0, G_TX_CLAMP,
                                    G_TX_CLAMP, TEX_MASK(frame->unk_00), TEX_MASK(frame->unk_02), G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPVertex(D_800D1F30_main++, osVirtualToPhysical(D_800CDD54_main), 4, 0);
        gSP1Quadrangle(D_800D1F30_main++, 0, 1, 2, 3, 0);
        nh = -h;
        x = -frame->unk_04;
        y = frame->unk_06;
        D_800CDD54_main->v.ob[0] = x;
        D_800CDD54_main->v.ob[1] = y;
        D_800CDD54_main->v.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->v.tc[0] = 0;
        D_800CDD54_main->v.tc[1] = 0;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;
        D_800CDD54_main->v.ob[0] = x;
        D_800CDD54_main->v.ob[1] = nh + y;
        D_800CDD54_main->v.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->v.tc[0] = 0;
        D_800CDD54_main->v.tc[1] = (-nh - 1) << 5;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;
        D_800CDD54_main->v.ob[0] = (s16) w + x;
        D_800CDD54_main->v.ob[1] = nh + y;
        D_800CDD54_main->v.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->v.tc[0] = ((s16) w - 1) << 5;
        D_800CDD54_main->v.tc[1] = (-nh - 1) << 5;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;
        D_800CDD54_main->v.ob[0] = (s16) w + x;
        D_800CDD54_main->v.ob[1] = y;
        D_800CDD54_main->v.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->v.tc[0] = ((s16) w - 1) << 5;
        D_800CDD54_main->v.tc[1] = 0;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;
        gSPEndDisplayList(D_800D1F30_main++);
        if (!(spr->unk10 & 1) && (HmfPauseF == 0 || (HmfModelData[spr->unk00].unk18 & 0x8000))) {
            for (j = 0; j < arg0; j++) {
                spr->unk08++;
                spr->unk0A++;
                if (spr->unk08 >= anim->unk_04[(s16) spr->unk04].unk_02) {
                    spr->unk04++;
                    spr->unk08 = 0;
                    if (anim->unk_00 <= (s16) spr->unk04) {
                        if (spr->unk10 & 4) {
                            spr->unk10 |= 0x80;
                        }
                        if ((spr->unk10 & 2) || anim->unk_04[(s16) spr->unk04 - 1].unk_02 != -1) {
                            spr->unk04--;
                            spr->unk0A--;
                            break;
                        }
                        spr->unk04 = 0;
                        spr->unk0A = 0;
                    }
                }
            }
        }
    }
}

void func_80016638_main(s32 index) {
    if (D_800A0620_main != 0) {
        if ((u16) D_800CBB60_main[index].unk02 != 0xFFFF) {
            func_800333B0_main(D_800CBB60_main[index].unk02);
        }
        func_8001ACDC_main(D_800CBB60_main[index].unk00);
        D_800CBB60_main[index].unk00 = -1;
    }
}

void func_800166D0_main(void) {
    s16 i;

    if (D_800A0620_main != 0) {
        for (i = 0; i < D_800CDD4E_main; i++) {
            if (D_800CBB60_main[i].unk00 != -1) {
                func_800333B0_main(D_800CBB60_main[i].unk02);
            }
        }
        func_80019C68_main(0x7530);
        D_800A0620_main = 0;
    }
}

/* Bakes model arg0's motion into a matrix table, one set of part matrices every arg1 frames
   (MP2 func_800231D8_23DD8, MP1 func_800202E8). */
unk1EA70StructC* func_80016784_main(s16 arg0, s16 arg1) {
    HmfDataView* model;
    D_800CCF58_main_Struct* anim;
    unk1EA70StructC* ret;

    model = (HmfDataView*) HmfModelData[arg0].hmf;
    anim = &D_800CCF58_main[HmfModelData[arg0].unk02];
    ret = HuMemMemoryAllocPerm(sizeof(unk1EA70StructC));
    ret->unk_08 = HuMemMemoryAllocPerm(((anim->unk02 + arg1) / arg1) * (model->unk16 << 6));
    ret->unk_04 = HuMemMemoryAllocPerm(model->unk16 * 2);
    ret->unk_00 = anim->unk02;
    ret->unk_02 = arg1;
    func_800169E0_main(arg0, arg1, ret, -1);
    return ret;
}

/* The same for the one part named arg2 (MP2 func_800232FC_23EFC, MP1 func_8002040C). */
unk1EA70StructC* func_800168A8_main(s16 arg0, s16 arg1, char* arg2) {
    HmfDataView* model;
    D_800CCF58_main_Struct* anim;
    unk1EA70StructC* ret;
    s16 temp;

    model = (HmfDataView*) HmfModelData[arg0].hmf;
    anim = &D_800CCF58_main[HmfModelData[arg0].unk02];
    temp = func_8002C834_main((HmfData*) model, arg2);
    ret = HuMemMemoryAllocPerm(sizeof(unk1EA70StructC));
    ret->unk_08 = HuMemMemoryAllocPerm(((anim->unk02 + arg1) / arg1) << 6);
    ret->unk_04 = HuMemMemoryAllocPerm(model->unk16 * 2);
    ret->unk_00 = anim->unk02;
    ret->unk_02 = arg1;
    func_800169E0_main(arg0, arg1, ret, temp);
    return ret;
}

/* MP2 func_80023434_24034 (MP1 func_80020544). */
void func_800169E0_main(s16 arg0, s16 arg1, unk1EA70StructC* arg2, s16 arg3) {
    HmfData* model;
    D_800CCF58_main_Struct* anim;
    s16 i;

    model = HmfModelData[arg0].hmf;
    anim = &D_800CCF58_main[HmfModelData[arg0].unk02];
    D_800D1358_main = arg2->unk_08;
    D_800D04B4_main = arg2->unk_04;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    for (i = 0; i < anim->unk02; i += arg1) {
        func_8002DFF8_main(model, i, anim, 1);
        D_800D138A_main = 0;
        func_80016C2C_main(model, 0, arg3);
    }
}

/* Writes the matrix of model arg0's part arg2 at motion frame arg1 to arg3 (MP2 func_80023554_24154). */
void func_80016B00_main(s16 arg0, s16 arg1, char* arg2, Matrix4f* arg3) {
    HmfData* model;
    D_800CCF58_main_Struct* anim;
    s16 temp;
    s16 parts[4]; /* retail's frame leaves 8 bytes here; one entry per matching part */

    model = HmfModelData[arg0].hmf;
    temp = func_8002C834_main(model, arg2);
    anim = &D_800CCF58_main[HmfModelData[arg0].unk02];
    D_800D1358_main = arg3;
    D_800D04B4_main = parts;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(model, arg1, anim, 1);
    D_800D138A_main = 0;
    func_80016C2C_main(model, 0, temp);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

/* Walks the motion-object tree from node arg1, storing each part's matrix (all parts when arg2
   is -1, else only part arg2) and its node in the tables func_800169E0_main set up
   (MP2 func_80023680_24280, MP1 func_80020654 reshaped). */
void func_80016C2C_main(HmfData* arg0, s16 arg1, s16 arg2) {
    Matrix4f sp10;
    HmfMotionObj* node;
    s16 pushed;
    s16 i;

    node = &((HmfDataView*) arg0)->unk80[arg1];
    pushed = 0;
    func_8008A070_main(sp10);
    if (node->unk28.x != 0.0f || node->unk28.y != 0.0f || node->unk28.z != 0.0f) {
        func_80017C10_main((Mtx*) sp10, node->unk28.x, node->unk28.y, node->unk28.z);
        pushed = 1;
    }
    if (node->unk34.x != 0.0f || node->unk34.y != 0.0f || node->unk34.z != 0.0f) {
        func_80017D24_main(sp10, node->unk34.x, node->unk34.y, node->unk34.z);
        pushed = 1;
    }
    if (node->unk40.x != 1.0f || node->unk40.y != 1.0f || node->unk40.z != 1.0f) {
        func_80017CD0_main(sp10, node->unk40.x, node->unk40.y, node->unk40.z);
        pushed = 1;
    }
    if (pushed != 0) {
        D_800D138A_main++;
        func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
    }
    for (i = 0; i < node->unk00; i++) {
        if (node->unk50[i] & 0x8000) {
            if (node->unk50[i] == -1) {
                if ((D_800CD1B0_main < ((HmfDataView*) arg0)->unk16) & (arg2 == -1)) {
                    D_800D04B4_main[D_800CD1B0_main] = arg1;
                    func_8002367C_main(D_800D1358_main[D_800CD1B0_main++], D_800D5A00_main[D_800D138A_main]);
                }
            } else {
                func_80016C2C_main(arg0, node->unk50[i] & 0x7FFF, arg2);
            }
        } else if (arg2 == -1 || arg2 == (node->unk50[i] & 0x7FFF)) {
            if (D_800CD1B0_main < ((HmfDataView*) arg0)->unk16) {
                D_800D04B4_main[D_800CD1B0_main] = arg1;
            }
            func_8002367C_main(D_800D1358_main[D_800CD1B0_main++], D_800D5A00_main[D_800D138A_main]);
        }
    }
    if (pushed != 0) {
        D_800D138A_main--;
    }
}

/* Poses model arg0 from baked frame arg2 of arg1 and stops its own motion (MP2 func_80023A08_24608). */
void func_80016FB4_main(s16 arg0, unk1EA70StructC* arg1, s16 arg2) {
    HmfDataView* model;
    s16 i;
    s16 frame;

    if (arg2 >= arg1->unk_00) {
        arg2 = arg1->unk_00 - 1;
    }
    if (arg2 < 0) {
        arg2 = 0;
    }
    model = (HmfDataView*) HmfModelData[arg0].hmf;
    HmfModelData[arg0].unk02 = 0xFF;
    frame = model->unk16 * (arg2 / arg1->unk_02);
    D_800CD1B0_main = 0;
    D_800D1358_main = &arg1->unk_08[frame];
    for (i = 0; i < model->unk16; i++) {
        func_8002367C_main(model->unk80[i].unk58, D_800D1358_main[arg1->unk_04[i]]);
    }
}

/* Model arg0's world matrix times baked frame arg3 of arg1, into arg2 (MP2 func_80023B7C_2477C). */
void func_80017128_main(s16 arg0, unk1EA70StructC* arg1, Matrix4f arg2, s16 arg3) {
    HmfModel* obj;

    obj = &HmfModelData[arg0];
    if (arg3 >= arg1->unk_00) {
        arg3 = arg1->unk_00 - 1;
    }
    if (arg3 < 0) {
        arg3 = 0;
    }
    func_8008A070_main(arg2);
    if (obj->pos.x != 0.0f || obj->pos.y != 0.0f || obj->pos.z != 0.0f) {
        func_80017C10_main((Mtx*) arg2, obj->pos.x, obj->pos.y, obj->pos.z);
    }
    if (obj->rot.x != 0.0f || obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
        func_80017D24_main(arg2, obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (obj->scale.x != 1.0f || obj->scale.y != 1.0f || obj->scale.z != 1.0f) {
        func_80017CD0_main(arg2, obj->scale.x, obj->scale.y, obj->scale.z);
    }
    guMtxCatF(arg1->unk_08[arg3 / arg1->unk_02], arg2, arg2);
}

void func_80017320_main(unk1EA70StructC* arg0) {
    HuMemMemoryFreePerm(arg0->unk_08);
    HuMemMemoryFreePerm(arg0->unk_04);
    HuMemMemoryFreePerm(arg0);
}

/* Hangs model arg0's part arg1 onto model arg2's part arg3 (MP2 func_80023DAC_249AC, MP1
   func_80020EA0). Retail compares each name against the address of the name argument (&arg1,
   &arg3), and the first search reads the second model's part names, as MP1/MP2 do. */
void func_80017358_main(s16 arg0, char* arg1, s16 arg2, char* arg3) {
    HmfDataView* src;
    HmfDataView* dst;
    HitXformView* obj40;
    HmfMotionObj* obj50;
    s16 hash;
    s16 i;
    s16 j;
    s16 k;
    s16 l;

    src = (HmfDataView*) HmfModelData[arg0].hmf;
    dst = (HmfDataView*) HmfModelData[arg2].hmf;
    hash = func_80011460_main(arg1);
    for (i = 0; i < src->unk10; i++) {
        if (src->unk60[i].unk26 == hash && strcmp(dst->unk60[i].unk00, (const char*) &arg1) != 0) {
            break;
        }
    }
    if (i == src->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", arg1);
        return;
    }
    hash = func_80011460_main(arg3);
    for (j = 0; j < dst->unk10; j++) {
        if (dst->unk60[j].unk26 == hash && strcmp(dst->unk60[j].unk00, (const char*) &arg3) != 0) {
            break;
        }
    }
    if (j == dst->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", arg3);
        return;
    }
    if (dst->unk80 == (void*) -1) {
        for (k = 0; k < dst->unk64; k++) {
            obj40 = &dst->unk68[k];
            if (obj40->unk00 == j) {
                obj40->unk48 = (HmfData*) src;
                obj40->unk00 = i;
                return;
            }
        }
    } else {
        for (k = 0; k < dst->unk16; k++) {
            obj50 = &dst->unk80[k];
            for (l = 0; l < obj50->unk00; l++) {
                if (obj50->unk50[l] == j) {
                    obj50->unk54 = (HmfData*) src;
                    obj50->unk50[l] = i;
                    break;
                }
            }
        }
    }
}

/* Clears the per-character texture-animation slots (6 characters, 3 sets, 7 each) and the 16
   colours (MP2 func_8002480C_2540C). */
void func_8001766C_main(void) {
    s16 k;
    s16 j;
    s16 i;

    for (i = 0; i < 6; i++) {
        D_800D6A50_main[i] = 0;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 7; k++) {
                D_800D4090_main[i][j][k] = -1;
            }
        }
    }
    for (k = 0; k < 16; k++) {
        D_800D20B8_main[k][0] = D_800D20B8_main[k][1] = D_800D20B8_main[k][2] = 0xFF;
    }
}

/* Replaces texture animation arg2 of set arg1 on model arg0 with data file arg3; returns the
   new animation's first frame (MP2 func_80025384_25F84). */
// register allocation only: GCC keeps one more value live across the calls (s8 saved; masked
// differs only in registers). Tried s32 parameters with casts and a local for the name pointer.
#ifdef NON_MATCHING
s16 func_80017790_main(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    void* file;
    s16 slot;
    u16 ret;

    if (D_800D20B8_main[arg2][arg1] != 0xFF) {
        func_80033354_main(D_800D20B8_main[arg2][arg1]);
        func_80033354_main(D_800D5570_main[arg2][arg1]);
    }
    file = DataRead(arg3);
    slot = HmfAnimCreate(HmfModelData[arg0].hmf, file, 0, D_800A063C_main[arg2 + arg1 * 16]);
    D_800D5570_main[arg2][arg1] = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(file);
    ret = D_800D1714_main[slot].unk_00;
    D_800D20B8_main[arg2][arg1] = func_80032694_main(HmfModelData[arg0].hmf, slot, 0, D_800A063C_main[arg2 + arg1 * 16]);
    func_8001C448_main(arg0);
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017790_main);
#endif

/* Pauses (arg3 -1) or restarts at frame arg3 the texture animation arg2 of set arg1 on model arg0
   (MP2 func_80025554_26154). */
void func_80017954_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    TexAnimSlot* p;

    if (D_800D20B8_main[arg2][arg1] != 0xFF) {
        if (arg3 == -1) {
            func_80033910_main(HmfModelData[arg0].hmf);
            return;
        }
        func_80033970_main(HmfModelData[arg0].hmf);
        p = &D_800D1714_main[D_800D20B8_main[arg2][arg1]];
        p->unk_00 = arg3;
        p->unk_04 = 0;
        p->unk_0A = 0;
        p->unk_06 = 0;
        p->unk_02 = 0;
    }
}

/* Sets two fields of the texture-animation slot of animation arg2, set arg1. */
void func_80017A84_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    TexAnimSlot* p = &D_800D1714_main[D_800D20B8_main[arg2][arg1]];

    p->unk_02 = arg3;
    p->unk_06 = arg4;
}

/* Loads sprite bank file id (MP2 func_80025684_26284, MP1 func_800F6C80_CoinBlockBash). */
s16 func_80017AD8_main(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_800329B4_main(file);
    DataClose(file);
    return sprite;
}

void func_80017B20_main(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    func_80032FC0_main(D_800D20B8_main[arg1][arg0], arg2, arg3);
}

/* File id of entry arg2/arg1 of D_800A06FC_main for character arg0. */
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2) {
    return func_80017BB8_main(arg0, D_800A06FC_main[arg2 * 3 + arg1]);
}

/* File id: character arg0's data directory and index arg1 (character 7 has a table). */
s32 func_80017BB8_main(s16 arg0, s16 arg1) {
    if (arg0 == 7) {
        return ((D_800A0748_main[arg1] & 0xFF00) << 8) | (D_800A0748_main[arg1] & 0xFF);
    }
    return D_800A0728_main[arg0] | arg1;
}

/* MtxTranslate. functions.us.h declares it with an Mtx*; it is a float matrix. */
void func_80017C10_main(Mtx* arg0, f32 x, f32 y, f32 z) {
    f32 (*mtx)[4] = (f32 (*)[4]) arg0;

     mtx[3][0] = (x * mtx[0][0]) + (y * mtx[1][0]) + (z * mtx[2][0]) + mtx[3][0];
     mtx[3][1] = (x * mtx[0][1]) + (y * mtx[1][1]) + (z * mtx[2][1]) + mtx[3][1];
     mtx[3][2] = (x * mtx[0][2]) + (y * mtx[1][2]) + (z * mtx[2][2]) + mtx[3][2];
     mtx[3][3] = (x * mtx[0][3]) + (y * mtx[1][3]) + (z * mtx[2][3]) + mtx[3][3];
}

/* MtxScale. */
void func_80017CD0_main(Matrix4f mtx, f32 sx, f32 sy, f32 sz) {
    s32 i;
    for (i = 0; i < 3; i++) {
        mtx[0][i] *= sx;
        mtx[1][i] *= sy;
        mtx[2][i] *= sz;
    }
}

/* MtxRotate. */
void func_80017D24_main(Matrix4f mtx, f32 angle1, f32 angle2, f32 angle3) {
    Matrix3f rot;
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;

    /* Get sin and cosf for three angles. */
    sincosdf(angle1, &sx, &cx);
    if (angle1 == angle2){
        sy = sx;
        cy = cx;
    } else {
        sincosdf(angle2, &sy, &cy);
    }

    if (angle1 == angle3){
        sz = sx;
        cz = cx;
    } else if (angle2 == angle3) {
        sz = sy;
        cz = cy;
    } else {
        sincosdf(angle3, &sz, &cz);
    }

    /* Rotation Matrix First Column */
    rot[0][0] = cy * cz;
    rot[0][1] = cy * sz;
    rot[0][2] = -sy;
    /* Rotation Matrix Second Column */
    rot[1][0] = sx * sy * cz - cx * sz;
    rot[1][1] = sx * sy * sz + cx * cz;
    rot[1][2] = sx * cy;
    /* Rotation Matrix Third Column */
    rot[2][0] = cx * sy * cz + sx * sz;
    rot[2][1] = cx * sy * sz - sx * cz;
    rot[2][2] = cx * cy;

    {
        /* Multiply Matrices */
        f32 ret00, ret01, ret02;
        f32 ret10, ret11, ret12;

        ret00 = (rot[0][0] * mtx[0][0]) + (rot[0][1] * mtx[1][0]) + (rot[0][2] * mtx[2][0]);
        ret01 = (rot[0][0] * mtx[0][1]) + (rot[0][1] * mtx[1][1]) + (rot[0][2] * mtx[2][1]);
        ret02 = (rot[0][0] * mtx[0][2]) + (rot[0][1] * mtx[1][2]) + (rot[0][2] * mtx[2][2]);
        ret10 = (rot[1][0] * mtx[0][0]) + (rot[1][1] * mtx[1][0]) + (rot[1][2] * mtx[2][0]);
        ret11 = (rot[1][0] * mtx[0][1]) + (rot[1][1] * mtx[1][1]) + (rot[1][2] * mtx[2][1]);
        ret12 = (rot[1][0] * mtx[0][2]) + (rot[1][1] * mtx[1][2]) + (rot[1][2] * mtx[2][2]);

        /* Evaluate Result Matrix */
        mtx[2][0] = (rot[2][0] * mtx[0][0]) + (rot[2][1] * mtx[1][0]) + (rot[2][2] * mtx[2][0]);
        mtx[2][1] = (rot[2][0] * mtx[0][1]) + (rot[2][1] * mtx[1][1]) + (rot[2][2] * mtx[2][1]);
        mtx[2][2] = (rot[2][0] * mtx[0][2]) + (rot[2][1] * mtx[1][2]) + (rot[2][2] * mtx[2][2]);
        mtx[0][0] = ret00;
        mtx[0][1] = ret01;
        mtx[0][2] = ret02;
        mtx[1][0] = ret10;
        mtx[1][1] = ret11;
        mtx[1][2] = ret12;
    }
}

// retail sets i = 0 once before the test and runs both loops as do-while; the 3-row path keeps its loop's a0/a1/a2 and the
// last row's apart (one set, live across both, moves them to other registers)
/* MtxMult (c = a * b) with a fast path when a's last column is (0, 0, 0, 1). */
void func_80018044_main(Matrix4f a, Matrix4f b, Matrix4f c) {
    s32 i;

    i = 0;
    if (a[0][3] != 0.0f || a[1][3] != 0.0f || a[2][3] != 0.0f || a[3][3] != 1.0f) {
        f32 a0, a1, a2, a3;
        f32 b00, b10, b20, b30;
        f32 b01, b11, b21, b31;
        f32 b02, b12, b22, b32;
        f32 b03, b13, b23, b33;

        b00 = b[0][0]; b10 = b[1][0]; b20 = b[2][0]; b30 = b[3][0];
        b01 = b[0][1]; b11 = b[1][1]; b21 = b[2][1]; b31 = b[3][1];
        b02 = b[0][2]; b12 = b[1][2]; b22 = b[2][2]; b32 = b[3][2];
        b03 = b[0][3]; b13 = b[1][3]; b23 = b[2][3]; b33 = b[3][3];

        do {
            c[i][0] = (a0 = a[i][0]) * b00 + (a1 = a[i][1]) * b10 + (a2 = a[i][2]) * b20 + (a3 = a[i][3]) * b30;
            c[i][1] = a0 * b01 + a1 * b11 + a2 * b21 + a3 * b31;
            c[i][2] = a0 * b02 + a1 * b12 + a2 * b22 + a3 * b32;
            c[i][3] = a0 * b03 + a1 * b13 + a2 * b23 + a3 * b33;
        } while (++i < 4);
    } else {
        f32 b00, b10, b20;
        f32 b01, b11, b21;
        f32 b02, b12, b22;
        f32 b03, b13, b23;

        b00 = b[0][0]; b10 = b[1][0]; b20 = b[2][0];
        b01 = b[0][1]; b11 = b[1][1]; b21 = b[2][1];
        b02 = b[0][2]; b12 = b[1][2]; b22 = b[2][2];
        b03 = b[0][3]; b13 = b[1][3]; b23 = b[2][3];

        do {
            f32 a0, a1, a2;

            c[i][0] = (a0 = a[i][0]) * b00 + (a1 = a[i][1]) * b10 + (a2 = a[i][2]) * b20;
            c[i][1] = a0 * b01 + a1 * b11 + a2 * b21;
            c[i][2] = a0 * b02 + a1 * b12 + a2 * b22;
            c[i][3] = a0 * b03 + a1 * b13 + a2 * b23;
        } while (++i < 3);
        {
            f32 a0, a1, a2;

            c[3][0] = (a0 = a[3][0]) * b[0][0] + (a1 = a[3][1]) * b[1][0] + (a2 = a[3][2]) * b[2][0] + b[3][0];
            c[3][1] = a0 * b[0][1] + a1 * b[1][1] + a2 * b[2][1] + b[3][1];
            c[3][2] = a0 * b[0][2] + a1 * b[1][2] + a2 * b[2][2] + b[3][2];
            c[3][3] = a0 * b[0][3] + a1 * b[1][3] + a2 * b[2][3] + b[3][3];
        }
    }
}

/* MtxInv. */
s16 func_800183A0_main(Matrix4f a, Matrix4f b) {
    u32 success;
    f32 d0, d1, d2;
    f32 det;

    d0 = (a[1][1] * a[2][2]) - (a[1][2] * a[2][1]);
    d1 = (a[1][2] * a[2][0]) - (a[1][0] * a[2][2]);
    d2 = (a[1][0] * a[2][1]) - (a[1][1] * a[2][0]);
    det = (a[0][0] * d0) + (a[0][1] * d1) + (a[0][2] * d2);

    success = FALSE;
    if (det != 0.0f) {
        f32 idet = (det = 1.0f / det); // They use same var, but I prefer this alias.
        b[0][0] = d0 * idet;
        b[1][0] = d1 * idet;
        b[2][0] = d2 * idet;
        b[0][1] = ((a[0][2] * a[2][1]) - (a[0][1] * a[2][2])) * idet;
        b[0][2] = ((a[0][1] * a[1][2]) - (a[0][2] * a[1][1])) * idet;
        b[1][1] = ((a[0][0] * a[2][2]) - (a[0][2] * a[2][0])) * idet;
        b[1][2] = ((a[0][2] * a[1][0]) - (a[0][0] * a[1][2])) * idet;
        b[2][1] = ((a[0][1] * a[2][0]) - (a[0][0] * a[2][1])) * idet;
        b[2][2] = ((a[0][0] * a[1][1]) - (a[0][1] * a[1][0])) * idet;
        b[3][2] = 0.0f;
        b[3][1] = 0.0f;
        b[3][0] = 0.0f;
        b[2][3] = 0.0f;
        b[1][3] = 0.0f;
        b[0][3] = 0.0f;
        b[3][3] = 1.0f;
        success = TRUE;
    }
    return success;
}

/* MtxReset: a = inverse(a) * a, or identity. */
u32 func_80018544_main(Matrix4f a, Matrix4f b) {
    Matrix4f invA;
    u32 success;
    if (func_800183A0_main(a, invA)) {
        guMtxCatF(invA, a, b);
        success = TRUE;
    } else {
        guMtxIdentF(b);
        success = FALSE;
    }
    return success;
}

/* MtxRotateY (MP1 math.c); functions.us.h declares it with an Mtx*, as func_80017C10_main. */
#define mtx ((f32 (*)[4]) arg0)
void func_800185A4_main(Mtx* arg0, f32 angle) {
    s32 i;
    f32 s, c;
    f32 vec[4];

    s = sindf(angle);
    c = cosdf(angle);

    for (i = 0; i < 3; i++) {
        vec[i] = mtx[0][i];
    }

    for (i = 0; i < 3; i++) {
        mtx[0][i] = (c * vec[i]) - (s * mtx[2][i]);
        mtx[2][i] = (s * vec[i]) + (c * mtx[2][i]);
    }
}
#undef mtx


/* Rotates mtx's first three rows by angles x, y, z in another axis order than
   func_80017D24_main (chosen per HMF file in MP2 1D0B0's func_8001FFCC_20BCC). */
void func_8001866C_main(Matrix4f m, f32 x, f32 y, f32 z) {
    Matrix4f t;
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;
    f32 a, b, c;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    t[0][0] = m[0][0];
    t[0][1] = m[0][1];
    t[0][2] = m[0][2];
    t[0][3] = m[0][3];
    t[1][0] = m[1][0];
    t[1][1] = m[1][1];
    t[1][2] = m[1][2];
    t[1][3] = m[1][3];
    t[2][0] = m[2][0];
    t[2][1] = m[2][1];
    t[2][2] = m[2][2];
    t[2][3] = m[2][3];

    a = cx * sz;
    b = -cz * sy + cy * sx * sz;
    c = cy * cz + sx * sy * sz;
    m[0][0] = a * t[1][0] + b * t[2][0] + c * t[0][0];
    m[0][1] = a * t[1][1] + b * t[2][1] + c * t[0][1];
    m[0][2] = a * t[1][2] + b * t[2][2] + c * t[0][2];
    m[0][3] = a * t[1][3] + b * t[2][3] + c * t[0][3];

    a = cx * cz;
    b = cz * sx * sy - cy * sz;
    c = cy * cz * sx + sy * sz;
    m[1][0] = a * t[1][0] + b * t[0][0] + c * t[2][0];
    m[1][1] = a * t[1][1] + b * t[0][1] + c * t[2][1];
    m[1][2] = a * t[1][2] + b * t[0][2] + c * t[2][2];
    m[1][3] = a * t[1][3] + b * t[0][3] + c * t[2][3];

    a = cx * cy;
    b = cx * sy;
    m[2][0] = a * t[2][0] - t[1][0] * sx + b * t[0][0];
    m[2][1] = a * t[2][1] - t[1][1] * sx + b * t[0][1];
    m[2][2] = a * t[2][2] - t[1][2] * sx + b * t[0][2];
    m[2][3] = a * t[2][3] - t[1][3] * sx + b * t[0][3];
}

/* The rotation matrix for angles x, y, z in func_8001866C_main's axis order. */
void func_80018978_main(Matrix4f m, f32 x, f32 y, f32 z) {
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    m[0][0] = cy * cz + sx * sy * sz;
    m[1][0] = -cx * sz;
    m[2][0] = cz * sy + cy * sx * sz;
    m[0][1] = cz * sx * sy + cy * sz;
    m[1][1] = cx * cz;
    m[2][1] = -cy * cz * sx + sy * sz;
    m[0][2] = -cx * sy;
    m[1][2] = sx;
    m[2][2] = cx * cy;
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// MP1 func_80022D9C (src/engine/math.c), also NON_MATCHING there. NON_MATCHING: register
// allocation (masked 0, raw 26 since the unit is assembled with blank lines stripped, which removed
// the extra mul-fix nop): FPRs from the found branch's midSlope on. S3-Q05 tried: r = u / ... as its
// own statement (masked 6), midSlope/midVal and x0..s1 declared in other orders (no change).
#ifdef NON_MATCHING
// Piecewise-quadratic interpolation through four keys (y[], x[]) at time t.
f32 func_80018ACC_main(f32* y, f32* x, f32 t) {
    f32 slope[2];
    s32 i;
    f32 mid;
    f32 ds;
    f32 cross;
    s32 found;
    f32 u;
    f32 w;
    f32 b;
    f32 r;
    f32 midVal;
    f32 midSlope;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;
    f32 s0;
    f32 s1;

    if (y[0] == y[1] && y[0] == y[2] && y[0] == y[3]) {
        return y[0];
    }
    for (i = 1; i < 3; i++) {
        slope[i - 1] = ((y[i] - y[i - 1]) / (x[i] - x[i - 1]) + (y[i + 1] - y[i]) / (x[i + 1] - x[i])) * 0.5f;
    }
    mid = (x[2] + x[1]) * 0.5f;
    found = 0;
    if (slope[1] - slope[0] != 0.0f) {
        cross = ((slope[1] * x[2] - slope[0] * x[1]) - (y[2] - y[1])) / (slope[1] - slope[0]);
        if (x[1] <= cross && cross <= x[2]) {
            found = 1;
        }
    }
    if (found == 1) {
        u = mid - x[1];
        b = (y[2] - y[1]) / (x[2] - x[1]) - (slope[1] - slope[0]) / 2.0f;
        midVal = (slope[1] - slope[0]) / ((x[2] - x[1]) + (x[2] - x[1])) * u * u + b * u + y[1];
        midSlope = (slope[1] - slope[0]) / (x[2] - x[1]) * u + b;
    } else {
        u = mid - x[1];
        midVal = (y[2] + y[1]) * (r = u / (x[2] - x[1]));
        midSlope = ((y[2] - y[1]) + (y[2] - y[1])) / (x[2] - x[1]) - (slope[1] + slope[0]) * r;
    }
    if (t < mid) {
        x0 = x[1];
        y0 = y[1];
        s0 = slope[0];
        x1 = mid;
        y1 = midVal;
        s1 = midSlope;
    } else {
        x0 = mid;
        y0 = midVal;
        s0 = midSlope;
        x1 = x[2];
        y1 = y[2];
        s1 = slope[1];
    }
    ds = s1 - s0;
    w = x1 - x0;
    return ds / (w + w) * (t - x0) * (t - x0) + ((y1 - y0) / w - ds / 2.0f) * (t - x0) + y0;
}
#else
INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018ACC_main);
#endif

/* Determinant of a 3x3 matrix. */
f32 func_80018D68_main(Matrix3f m) {
    f32 m10 = m[1][0];
    f32 m11 = m[1][1];
    f32 m12 = m[1][2];
    f32 m20 = m[2][0];
    f32 m21 = m[2][1];
    f32 m22 = m[2][2];

    return (m11 * m22 - m12 * m21) * m[0][0] + (m12 * m20 - m10 * m22) * m[0][1] +
           (m10 * m21 - m11 * m20) * m[0][2];
}

/* The 3x3 minor of a without row and column col. */
void func_80018DD8_main(Matrix4f a, s32 row, s32 col, Matrix3f out) {
    s32 i, j;
    s32 oi, oj;

    oi = 0;
    for (i = 0; i < 4; i++) {
        if (i != row) {
            oj = 0;
            for (j = 0; j < 4; j++) {
                if (j != col) {
                    out[oi][oj] = a[i][j];
                    oj++;
                }
            }
            oi++;
        }
    }
}

/* Cofactor: the determinant of a with row arg1 and column arg2 removed (shaped like MP2
   func_8005A608_5B208, a wrapper passing a local to its neighbour). */
f32 func_80018D68_main(Matrix3f);
void func_80018DD8_main(Matrix4f, s32, s32, Matrix3f);

f32 func_80018E50_main(Matrix4f a, s32 arg1, s32 arg2) {
    Matrix3f minor;

    func_80018DD8_main(a, arg1, arg2, minor);
    return func_80018D68_main(minor);
}

/* Determinant of a 4x4 matrix (cofactor expansion along row 0). */
f32 func_80018E74_main(Matrix4f a) {
    f32 det = 0.0f;
    s32 i;
    s32 sign;

    for (i = 0; i < 4; i++) {
        sign = (i != i / 2 * 2) ? -1 : 1;
        det += func_80018E50_main(a, 0, i) * a[0][i] * sign;
    }
    return det;
}

/* Inverts a into out (adjugate / determinant); returns 0 if a is singular. */
s32 func_80018F18_main(Matrix4f a, Matrix4f out) {
    f32 det;
    s32 i, j;
    s32 sign;

    det = func_80018E74_main(a);
    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sign = i + j;
            sign = (sign != sign / 2 * 2) ? -1 : 1;
            out[j][i] = func_80018E50_main(a, i, j) * det * sign;
        }
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6A98_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AA4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AB0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6ABC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AC8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AD4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AE0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AEC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AF8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B04_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B10_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B1C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B28_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B34_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B40_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B4C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B58_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B64_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B70_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B7C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B88_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B94_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BA0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BAC_main);
