#include "common.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/hmfman.h"

// pz A: Mario's Puzzle Party block batches (many copies of one sprite drawn in one display list)

typedef struct PzBatchEnt {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 sx;
    /* 0x0C */ f32 sy;
    /* 0x10 */ s16 used;
} PzBatchEnt; /* size 0x14 */

typedef struct PzBatch {
    /* 0x00 */ PzBatchEnt* ents;
    /* 0x04 */ s16 spr;
    /* 0x06 */ s16 grp;
    /* 0x08 */ s16 n;
} PzBatch; /* size 0xC */

void* HuMemAllocTag(s32 size, s16 tag);
s16 func_8000B838_main(s32 arg0);
s32 func_8001A894_main(s32, void*, s32);
void func_8001ACDC_main(s16);
void HuSprAttrReset(s16 group, s16 member, s32 attr);
extern u8 D_800D2008_main;
extern u8 D_800D6A90_main;
extern Gfx D_80110230_marios_puzzle_party[];
void func_8010F810_marios_puzzle_party(omObjData* obj);

extern PzBatch* D_801168B0_marios_puzzle_party;
extern s16 D_801168B4_marios_puzzle_party;
extern s16 D_801168B6_marios_puzzle_party;
extern Gfx* D_801168B8_marios_puzzle_party[3];
extern omObjData* D_801168C4_marios_puzzle_party;
extern s32 D_801168C8_marios_puzzle_party[4];

void func_8010F570_marios_puzzle_party(s16 n) {
    Gfx* gfx;
    s16 i;

    D_801168B0_marios_puzzle_party = HuMemAllocTag(n * sizeof(PzBatch), 0x7918);
    D_801168B4_marios_puzzle_party = 0;
    for (i = 0; i < 3; i++) {
        gfx = HuMemAllocTag(0x3E80, 0x7918);
        D_801168B8_marios_puzzle_party[i] = gfx;
        gSPEndDisplayList(gfx);
    }
    D_801168C4_marios_puzzle_party = omAddObj(0x7D0, 0, 0, -1, func_8010F810_marios_puzzle_party);
    omSetStatBit(D_801168C4_marios_puzzle_party, 0xA0);
    D_801168B6_marios_puzzle_party = func_8001A894_main(0, D_801168B8_marios_puzzle_party[D_800D2008_main], 2);
}

#ifdef NON_MATCHING
void func_8010F678_marios_puzzle_party(s32 file, s16 n) {
    PzBatchEnt* e;
    s16 spr;
    s16 grp;
    s16 i;

    e = HuMemAllocTag(n * sizeof(PzBatchEnt), 0x7918);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].ents = e;
    spr = func_8000B838_main(file);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].spr = spr;
    grp = HuSprGrpCreate(1, 0);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].grp = grp;
    func_80055024_main(grp, 0, spr, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x8000);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].n = n;
    for (i = 0; i < n; i++, e++) {
        e->used = 0;
    }
    D_801168B4_marios_puzzle_party++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F678_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
/* Draw object: one display list per frame with every used entry of every batch as a textured
   rectangle (batches 0-27 belong to the boards, seven per player, and follow the board's y offset). */
void func_8010F810_marios_puzzle_party(omObjData* obj) {
    Gfx* gfx;
    PzBatch* b;
    PzBatchEnt* e;
    HuSprite_Unk84_Struct* tex;
    void* img;
    s16 w;
    s16 h;
    s16 yoff;
    s16 i;
    s16 j;

    HmfModelData[D_801168B6_marios_puzzle_party].hmf->unk3C =
        (HmfModelData_Unk64_Unk3C_Struct*)(gfx = D_801168B8_marios_puzzle_party[D_800D2008_main]);
    if (D_801168B4_marios_puzzle_party == 0) {
        gSPEndDisplayList(gfx++);
        return;
    }
    b = D_801168B0_marios_puzzle_party;
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80110230_marios_puzzle_party));
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        for (i = 0; i < D_801168B4_marios_puzzle_party; i++, b++) {
            e = b->ents;
            tex = HuSprGet(b->grp, 0)->unk_84;
            img = tex->unk00->unk00;
            w = tex->unk14;
            h = tex->unk16;
            gDPLoadTextureTile(gfx++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, 0, 0, w, h, 0,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            for (j = 0; j < b->n; j++, e++) {
                if (e->used & 1) {
                    yoff = 0;
                    if (i < 28) {
                        yoff = D_801168C8_marios_puzzle_party[i / 7];
                    }
                    gSPScisTextureRectangle(gfx++, e->x * 4.0f, (yoff + e->y - h * e->sy) * 4.0f,
                                            (w * e->sx + e->x) * 4.0f, (yoff + e->y) * 4.0f, G_TX_RENDERTILE, 0, 0,
                                            1024.0f / e->sx, 1024.0f / e->sy);
                }
            }
        }
    }
    gSPEndDisplayList(gfx++);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F810_marios_puzzle_party);
#endif

s16 func_8010FEDC_marios_puzzle_party(s16 id, f32 x, f32 y) {
    PzBatch* b = &D_801168B0_marios_puzzle_party[id];
    PzBatchEnt* e = b->ents;
    s16 i;

    for (i = 0; i < b->n; i++, e++) {
        if (e->used == 0) {
            e->used = 1;
            e->x = x;
            e->y = y;
            e->sy = 1.0f;
            e->sx = 1.0f;
            break;
        }
    }
    return i + (id << 10);
}

void func_8010FF78_marios_puzzle_party(s16 handle, f32 x, f32 y) {
    PzBatchEnt* e = D_801168B0_marios_puzzle_party[handle >> 10].ents;

    e = &e[handle & 0x3FF];

    e->x = x;
    e->y = y;
}

void func_8010FFBC_marios_puzzle_party(s16 handle, f32 sx, f32 sy) {
    PzBatchEnt* e = D_801168B0_marios_puzzle_party[handle >> 10].ents;

    e = &e[handle & 0x3FF];

    e->sx = sx;
    e->sy = sy;
}

void func_80110000_marios_puzzle_party(s16 handle) {
    PzBatchEnt* e = D_801168B0_marios_puzzle_party[handle >> 10].ents;

    e = &e[handle & 0x3FF];
    e->used = 0;
}

void func_80110040_marios_puzzle_party(void) {
    func_8001ACDC_main(D_801168B6_marios_puzzle_party);
    omDelObj(D_801168C4_marios_puzzle_party);
}

void func_8011006C_marios_puzzle_party(s32 player, s32 y) {
    D_801168C8_marios_puzzle_party[player] = y;
}
