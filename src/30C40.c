#include "common.h"
#include "mallocblock.h"

/* Model vertex animation (MP2 src/30560.c's tail, MP3 layouts): 16 animation slots, a model's
   vertex copy, and morph targets. Local views of MP3's HmfData (src/hmfman.c HmfDataM) and
   HmfModel (HmfModelM), only the fields used here. */

/* A vertex animation slot (MP2 HmfTexAnimSlot, 4 bytes longer in MP3) */
typedef struct HmfVtxAnimSlot {
    /* 0x00 */ void* unk00;
    /* 0x04 */ u8* unk04;  /* animation data */
    /* 0x08 */ u8* unk08;  /* frame table (data + 0xE); NULL when free */
    /* 0x0C */ s16 unk0C;  /* frame count */
    /* 0x0E */ s16 unk0E;  /* frame length */
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[2];
} HmfVtxAnimSlot; /* size = 0x14 */

typedef struct HmfVtxPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} HmfVtxPos; /* size = 0x6 */

/* A model's working copy of its vertices (HmfData 0x58; MP2 HmfVtxCopy, two buffers in MP3) */
typedef struct HmfVtxCopyM {
    /* 0x00 */ s16 unk00; /* vertex count */
    /* 0x02 */ s16 unk02; /* decoded frame, -1 none */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ HmfVtxPos* unk08;
    /* 0x0C */ HmfVtxPos* unk0C;
    /* 0x10 */ u8* unk10; /* colours, 3 bytes each */
    /* 0x14 */ u8* unk14;
    /* 0x18 */ u8* unk18; /* one bit per vertex */
} HmfVtxCopyM; /* size = 0x1C */

typedef struct HmfVtx30C40 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 unk0C[3];
    /* 0x0F */ u8 unk0F;
} HmfVtx30C40; /* size = 0x10 (src/hmfman.c HmfVtxM) */

/* A morph target (HmfData 0xB4 array) */
typedef struct HmfMorphM {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ s16 unk1C; /* vertex count */
    /* 0x1E */ char unk1E[0xA];
    /* 0x28 */ s16* unk28; /* vertex indices */
    /* 0x2C */ HmfVtxPos* unk2C;
    /* 0x30 */ u8* unk30; /* colours, 3 bytes each */
} HmfMorphM; /* size = 0x34 */

/* Per morph channel: the target of each frame (HmfData 0xB8 array) */
typedef struct HmfMorphAnimM {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* frame count */
    /* 0x04 */ s16* unk04; /* target per frame */
} HmfMorphAnimM; /* size = 0x8 */

typedef struct HmfData30C40 {
    /* 0x00 */ char unk00[0x18];
    /* 0x18 */ s16 unk18; /* vertex count */
    /* 0x1A */ char unk1A[0xA];
    /* 0x24 */ s16 unk24; /* morph channel count */
    /* 0x26 */ char unk26[0x1A];
    /* 0x40 */ HmfVtx30C40* unk40;
    /* 0x44 */ HmfVtx30C40* unk44[3]; /* per frame buffer */
    /* 0x50 */ char unk50[8];
    /* 0x58 */ HmfVtxCopyM* unk58;
    /* 0x5C */ s16* unk5C; /* vertex remap */
    /* 0x60 */ char unk60[0x54];
    /* 0xB4 */ HmfMorphM* unkB4;
    /* 0xB8 */ HmfMorphAnimM* unkB8;
} HmfData30C40;

typedef struct HmfModel30C40 {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ u8 unk08; /* vertex animation slot */
    /* 0x09 */ char unk09[0x5B];
    /* 0x64 */ HmfData30C40* hmf;
} HmfModel30C40;

extern HmfVtxAnimSlot* D_800D59F8_main;
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

void func_80030178_main(s32 arg0);
void func_80030414_main(HmfData30C40* arg0, s16 arg1, f32 arg2);
void func_80031324_main(HmfData30C40* arg0, f32 arg1);

void func_80030040_main(void) {
    s16 i;

    D_800D59F8_main = HuMemAlloc(16 * sizeof(HmfVtxAnimSlot));
    for (i = 0; i < 16; i++) {
        D_800D59F8_main[i].unk08 = NULL;
    }
}

s16 func_800300A4_main(void* arg0, u8* arg1) {
    HmfVtxAnimSlot* slot;
    s16 i;

    for (i = 0; i < 16; i++) {
        if (D_800D59F8_main[i].unk08 == NULL) {
            break;
        }
    }
    if (i == 16) {
        return -1;
    }
    slot = &D_800D59F8_main[i];
    slot->unk00 = arg0;
    slot->unk04 = arg1;
    slot->unk0C = (arg1[8] << 8) + arg1[9];
    slot->unk0E = (arg1[10] << 8) + arg1[11];
    slot->unk10 = (arg1[12] << 8) + arg1[13];
    slot->unk08 = arg1 + 14;
    return i;
}

void func_80030178_main(s32 arg0) {
    D_800D59F8_main[arg0].unk08 = NULL;
}

void func_80030198_main(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        if (D_800D59F8_main[i].unk08 != NULL) {
            func_80030178_main(i);
        }
    }
}

void func_80030208_main(HmfData30C40* arg0) {
    HmfVtxCopyM* c;
    HmfVtx30C40* v;
    HmfVtxPos* pos;
    u8* col;
    s16 n;
    s16 i;

    if (arg0->unk58 != NULL) {
        c = arg0->unk58;
        HuMemFree(c->unk08);
        HuMemFree(c->unk0C);
        HuMemFree(c->unk10);
        HuMemFree(c->unk14);
        HuMemFree(c->unk18);
        HuMemFree(c);
    }

    n = arg0->unk18;
    c = HuMemAllocTag(sizeof(HmfVtxCopyM), D_800CDD6A_main);
    arg0->unk58 = c;
    c->unk00 = n;
    pos = HuMemAllocTag(n * sizeof(HmfVtxPos), D_800CDD6A_main);
    c->unk08 = pos;
    col = HuMemAllocTag(n * 3, D_800CDD6A_main);
    c->unk10 = col;
    c->unk0C = HuMemAllocTag(n * sizeof(HmfVtxPos), D_800CDD6A_main);
    c->unk14 = HuMemAllocTag(n * 3, D_800CDD6A_main);
    c->unk18 = HuMemAllocTag((n + 7) / 8, D_800CDD6A_main);
    c->unk02 = c->unk04 = -1;
    c->unk06 = 0;

    v = arg0->unk40;
    for (i = 0; i < n; i++) {
        pos->x = v->unk00;
        pos->y = v->unk02;
        pos->z = v->unk04;
        col[0] = v->unk0C[0];
        col[1] = v->unk0C[1];
        col[2] = v->unk0C[2];
        v++;
        pos++;
        col += 3;
    }
}

void func_800303C8_main(HmfModel30C40* arg0, f32 arg1) {
    HmfData30C40* hmf = arg0->hmf;

    if (hmf->unkB4 != NULL) {
        func_80031324_main(hmf, arg1);
        return;
    }
    func_80030414_main(hmf, arg0->unk08, arg1);
}

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030414_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800308C0_main);

/* Apply the morph targets of frame arg1 to this frame's vertex buffer */
void func_80031324_main(HmfData30C40* arg0, f32 arg1) {
    HmfMorphM* m;
    HmfVtx30C40* dst;
    HmfVtx30C40* src;
    s16* idx;
    HmfVtxPos* pos;
    s8* col;
    s16 n;
    s16 i;
    s16 j;

    if (arg0->unkB4 != NULL) {
        if (arg0->unkB8 != NULL) {
            src = arg0->unk40;
            dst = arg0->unk44[D_800D2008_main];
            n = arg0->unk18;
            for (j = 0; j < n; j++) {
                *dst = *src;
                src++;
                dst++;
            }
            src = arg0->unk44[D_800D2008_main];
            if (arg0->unkB8->unk02 - 1 <= arg1) {
                arg1 = arg0->unkB8->unk02 - 1;
            }
            for (i = 0; i < arg0->unk24; i++) {
                m = &arg0->unkB4[arg0->unkB8[i].unk04[(s16) arg1]];
                idx = m->unk28;
                pos = m->unk2C;
                col = (s8*) m->unk30;
                n = m->unk1C;
                for (j = 0; j < n; j++) {
                    dst = &src[arg0->unk5C[*idx]];
                    dst->unk00 = pos->x;
                    dst->unk02 = pos->y;
                    dst->unk04 = pos->z;
                    if (col[0] != 0 || col[1] != 0 || col[2] != 0) {
                        dst->unk0C[0] = col[0];
                        dst->unk0C[1] = col[1];
                        dst->unk0C[2] = col[2];
                    }
                    idx++;
                    pos++;
                    col += 3;
                }
            }
        }
    }
}
