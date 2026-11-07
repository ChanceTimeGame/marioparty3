/* functions.us.h declares these with other parameter types: HmfSprModelCreate's third is u8 there
   but 16-bit in retail (the callee stores it with sh unmasked and func_80014618_main passes it
   masked to 0xFFFF); func_800142A0_main's is s32 there (s16 here), func_80014A3C_main's u32 (a signed compare here). Keep the header's out of this unit. */
#define HmfSprModelCreate HmfSprModelCreate_header
#define func_800142A0_main func_800142A0_main_header
#define func_80014A3C_main func_80014A3C_main_header
#include "common.h"
#undef HmfSprModelCreate
#undef func_800142A0_main
#undef func_80014A3C_main
#include "mallocblock.h"

/* Sprite-model slots and the matrix helpers. C from MP2 src/21920.c / src/26370.c and MP1
   src/1EA70.c / src/engine/math.c; functions with no reference stay in asm. */

typedef f32 Matrix4f[4][4];

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

/* The fields of HmfData this unit reads (include/game/hmfman.h leaves 0x16 and 0x80 unnamed). */
typedef struct HmfDataView {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[4];
    /* 0x16 */ s16 unk16; /* motion object count */
    /* 0x18 */ char unk18[0x68];
    /* 0x80 */ HmfMotionObj* unk80;
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

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017358_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001766C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017790_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017954_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017A84_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017AD8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017B20_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017B6C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017BB8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017C10_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017CD0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017D24_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018044_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800183A0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018544_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800185A4_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001866C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018978_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018ACC_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018D68_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018DD8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E50_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E74_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018F18_main);

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
