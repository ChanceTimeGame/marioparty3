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

/* A model's working copy of its vertices (HmfData 0x58; MP2 HmfVtxCopy): two decoded frames,
   between which func_80030414_main interpolates */
typedef struct HmfVtxCopyM {
    /* 0x00 */ s16 unk00;    /* vertex count */
    /* 0x02 */ s16 unk02[2]; /* frame decoded in each buffer, -1 none */
    /* 0x06 */ s16 unk06;    /* current buffer */
    /* 0x08 */ HmfVtxPos* unk08[2];
    /* 0x10 */ s8* unk10[2]; /* colours, 3 bytes each (read signed) */
    /* 0x18 */ u8* unk18;    /* one bit per vertex */
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
void func_800308C0_main(HmfVtxAnimSlot* slot, HmfData30C40* arg0, HmfVtxCopyM* c, s16 frame);

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
    s8* col;
    s16 n;
    s16 i;

    if (arg0->unk58 != NULL) {
        c = arg0->unk58;
        HuMemFree(c->unk08[0]);
        HuMemFree(c->unk08[1]);
        HuMemFree(c->unk10[0]);
        HuMemFree(c->unk10[1]);
        HuMemFree(c->unk18);
        HuMemFree(c);
    }

    n = arg0->unk18;
    c = HuMemAllocTag(sizeof(HmfVtxCopyM), D_800CDD6A_main);
    arg0->unk58 = c;
    c->unk00 = n;
    pos = HuMemAllocTag(n * sizeof(HmfVtxPos), D_800CDD6A_main);
    c->unk08[0] = pos;
    col = HuMemAllocTag(n * 3, D_800CDD6A_main);
    c->unk10[0] = col;
    c->unk08[1] = HuMemAllocTag(n * sizeof(HmfVtxPos), D_800CDD6A_main);
    c->unk10[1] = HuMemAllocTag(n * 3, D_800CDD6A_main);
    c->unk18 = HuMemAllocTag((n + 7) / 8, D_800CDD6A_main);
    c->unk02[0] = c->unk02[1] = -1;
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

/* Interpolate model arg0's vertices at time arg2 of vertex animation slot arg1 between the two
   decoded frames around it, into this frame's vertex buffer */
void func_80030414_main(HmfData30C40* arg0, s16 arg1, f32 arg2) {
    HmfVtxAnimSlot* slot;
    HmfVtxCopyM* c;
    HmfVtx30C40* v;
    HmfVtxPos* pos0;
    HmfVtxPos* pos1;
    s8* col0;
    s8* col1;
    f32 t;
    s16 f;
    s16 next;
    s16 start;
    s16 b;
    s16 n;
    s16 i;

    slot = &D_800D59F8_main[arg1];
    c = arg0->unk58;
    f = arg2 / slot->unk10;
    if (f >= slot->unk0E - 1) {
        f = slot->unk0E - 1;
    }
    t = (arg2 - f * slot->unk10) / slot->unk10;
    next = f + 1;
    if (next >= slot->unk0E) {
        if ((slot->unk0C - 1) % slot->unk10 != 0) {
            next = slot->unk0E;
            t = 1.0f - (slot->unk0C - arg2) / (slot->unk0C - (slot->unk0E - 1) * slot->unk10);
        } else {
            next = slot->unk0E - 1;
        }
    }

    if (c->unk02[0] != f && c->unk02[1] != f) {
        start = c->unk02[c->unk06];
        if (start < 0) {
            start = 0;
        }
        if (start > f) {
            start = 0;
        }
        for (i = start; i <= f; i++) {
            func_800308C0_main(slot, arg0, c, i);
        }
        b = c->unk06;
    } else if (c->unk02[0] == f) {
        c->unk06 = 0;
        b = 0;
    } else {
        c->unk06 = 1;
        b = 1;
    }
    if (c->unk02[0] != next && c->unk02[1] != next) {
        func_800308C0_main(slot, arg0, c, next);
    }
    if (f == next) {
        t = 0.0f;
    }

    pos0 = c->unk08[b];
    col0 = c->unk10[b];
    pos1 = c->unk08[(b + 1) & 1];
    col1 = c->unk10[(b + 1) & 1];
    v = arg0->unk44[D_800D2008_main];
    n = arg0->unk18;
    for (i = 0; i < n; i++) {
        v->unk00 = pos0->x * (1.0f - t) + pos1->x * t;
        v->unk02 = pos0->y * (1.0f - t) + pos1->y * t;
        v->unk04 = pos0->z * (1.0f - t) + pos1->z * t;
        v->unk0C[0] = (s32) (col0[0] * (1.0f - t) + col1[0] * t);
        v->unk0C[1] = (s32) (col0[1] * (1.0f - t) + col1[1] * t);
        v->unk0C[2] = (s32) (col0[2] * (1.0f - t) + col1[2] * t);
        v++;
        pos0++;
        col0 += 3;
        pos1++;
        col1 += 3;
    }
}

/* Logic checked against the asm block by block. Not matching (masked 134, 672 vs 692): retail
   saves s0 for a held -0x100 (frame 8), sign-extends the 16-bit delta's high byte at the join,
   ORs the nibble/byte sign masks from registers (here ori 0xFFF0/0xFF00), keeps a copy of the
   entry word for the skip path's second test, and schedules the target-buffer index
   ((unk06 + 1) & 1) after the vertex remap load. rd/d as s32/u32/s16 and split per-width
   readers were worse. */
#ifdef NON_MATCHING
/* Packed vertex animation reader: half != 0 means the next value starts at the low nibble of *p */
#define HMF_RD4(v) \
    if (half == 0) { \
        v = *p >> 4; \
    } else { \
        v = (u8) (*p & 0xF); \
        p++; \
    } \
    half ^= 1
#define HMF_RD8(v) \
    if (half == 0) { \
        v = *p; \
    } else { \
        v = ((*p & 0xF) << 4) | (p[1] >> 4); \
    } \
    p++
#define HMF_RD16(v) \
    if (half == 0) { \
        hi = *p << 8; \
    } else { \
        hi = (((u8) (*p & 0xF) << 4) | (p[1] >> 4)) << 8; \
    } \
    p++; \
    if (half == 0) { \
        v = hi | *p; \
    } else { \
        v = hi | (((*p & 0xF) << 4) | (p[1] >> 4)); \
    } \
    p++
#define HMF_S4(v) ((v & 8) ? (s16) v | 0xFFF0 : (s16) v)

/* Decode frame `frame` of vertex animation slot `slot` into the vertex copy's other buffer: start
   from the current buffer (from the model's base vertices at frame 0), then apply the frame's
   deltas. Per entry: bits 0-11 the vertex, 14-15 the position delta (3 nibbles, 3 bytes, 3
   16-bit adds, none), 12-13 the colour delta (3 nibbles, none, 3 bytes). A vertex already set
   this frame skips its data. */
void func_800308C0_main(HmfVtxAnimSlot* slot, HmfData30C40* arg0, HmfVtxCopyM* c, s16 frame) {
    HmfVtx30C40* v;
    HmfVtxPos* pos;
    HmfVtxPos* dpos;
    HmfVtxPos* pv;
    s8* col;
    s8* dcol;
    s8* pc;
    u8* q;
    u8* ent;
    u8* p;
    s32 e;
    s32 vi;
    s32 t;
    u16 sv;
    s32 bit;
    u8 half;
    u16 rd;
    u16 d;
    u8 by;
    s16 hi;
    s16 count;
    s16 n;
    s16 i;

    q = &slot->unk08[frame * 4];
    count = (q[0] << 8) + q[1];
    p = slot->unk08 + (slot->unk0E + 1) * 4;
    q = slot->unk08;
    for (i = 0; i < frame; i++) {
        p += ((q[0] << 8) + q[1]) * 2 + (q[2] << 8) + q[3];
        q += 4;
    }
    ent = p;
    p = ent + count * 2;
    c->unk02[(c->unk06 + 1) & 1] = frame;
    n = c->unk00;
    if (frame == 0) {
        pos = c->unk08[c->unk06];
        col = c->unk10[c->unk06];
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
    pos = c->unk08[c->unk06];
    dpos = c->unk08[(c->unk06 + 1) & 1];
    col = c->unk10[c->unk06];
    dcol = c->unk10[(c->unk06 + 1) & 1];
    for (i = 0; i < n; i++) {
        dpos->x = pos->x;
        dpos->y = pos->y;
        dpos->z = pos->z;
        dcol[0] = col[0];
        dcol[1] = col[1];
        dcol[2] = col[2];
        pos++;
        col += 3;
        dpos++;
        dcol += 3;
    }
    for (i = 0; i < (n + 7) / 8; i++) {
        c->unk18[i] = 0;
    }
    half = 0;
    for (i = 0; i < count; i++) {
        e = (ent[0] << 8) + ent[1];
        vi = e & 0xFFF;
        sv = arg0->unk5C[vi];
        bit = 1 << (sv & 7);
        by = sv >> 3;
        if (c->unk18[by] & bit) {
            t = e & 0xC000;
            if (t != 0xC000) {
                if (t == 0x8000) {
                    p = p + 1 + (half != 0);
                    half ^= 1;
                } else if ((e & 0xC000) != 0x4000) {
                    p += 6;
                } else {
                    p += 3;
                }
            }
            t = e & 0x3000;
            if (t != 0x2000) {
                if (t != 0x1000) {
                    p += 3;
                } else {
                    p = p + 1 + (half != 0);
                    half ^= 1;
                }
            }
        } else {
            c->unk18[by] |= bit;
            pv = &c->unk08[(c->unk06 + 1) & 1][arg0->unk5C[vi]];
            t = e & 0xC000;
            if (t != 0xC000) {
                if (t == 0x8000) {
                    HMF_RD4(rd);
                    d = rd;
                    if (rd & 8) {
                        d = rd | ~0xF;
                    }
                    pv->x = pv->x + (f32) (s16) d;
                    HMF_RD4(rd);
                    d = rd;
                    if (rd & 8) {
                        d = rd | ~0xF;
                    }
                    pv->y = pv->y + (f32) (s16) d;
                    HMF_RD4(rd);
                    d = rd;
                    if (rd & 8) {
                        d = rd | ~0xF;
                    }
                    pv->z = pv->z + (f32) (s16) d;
                } else if (t == 0x4000) {
                    HMF_RD8(rd);
                    d = rd;
                    if (rd & 0x80) {
                        d = rd | ~0xFF;
                    }
                    pv->x = pv->x + (f32) (s16) d;
                    HMF_RD8(rd);
                    d = rd;
                    if (rd & 0x80) {
                        d = rd | ~0xFF;
                    }
                    pv->y = pv->y + (f32) (s16) d;
                    HMF_RD8(rd);
                    d = rd;
                    if (rd & 0x80) {
                        d = rd | ~0xFF;
                    }
                    pv->z = pv->z + (f32) (s16) d;
                } else {
                    HMF_RD16(d);
                    pv->x = pv->x + (f32) (s16) d;
                    HMF_RD16(d);
                    pv->y = pv->y + (f32) (s16) d;
                    HMF_RD16(d);
                    pv->z = pv->z + (f32) (s16) d;
                }
            }
            pc = &c->unk10[(c->unk06 + 1) & 1][arg0->unk5C[vi] * 3];
            t = e & 0x3000;
            if (t != 0x2000) {
                if (t == 0x1000) {
                    HMF_RD4(rd);
                    pc[0] += HMF_S4(rd);
                    HMF_RD4(rd);
                    pc[1] += HMF_S4(rd);
                    HMF_RD4(rd);
                    pc[2] += HMF_S4(rd);
                } else {
                    HMF_RD8(rd);
                    pc[0] += rd;
                    HMF_RD8(rd);
                    pc[1] += rd;
                    HMF_RD8(rd);
                    pc[2] += rd;
                }
            }
        }
        ent += 2;
    }
    c->unk06 = (c->unk06 + 1) & 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/30C40", func_800308C0_main);
#endif

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
