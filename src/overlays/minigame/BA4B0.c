#include "common.h"

#include "mallocblock.h"

/* Story-mode record board: a process (func_800E7F60_minigame) draws a slot's results. */
typedef struct MgPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MgPos;

typedef struct MgRecInfo {
    /* 0x00 */ s16 mode;  /* 0 a saved slot, 1 the current story, 2 the current story's pages */
    /* 0x02 */ s16 slot;
    /* 0x04 */ s16 cmd;   /* 1 show, 2 hide, 3 next page, 4 previous page, 0xFF close */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} MgRecInfo; /* size 0xC */

typedef struct MgRecPart {
    /* 0x00 */ MgPos pos;
    /* 0x04 */ s16 spr;
    /* 0x06 */ s16 alpha; /* maximum alpha */
    /* 0x08 */ s16 fade;  /* 1 start, 2 fading */
    /* 0x0A */ s16 shown;
} MgRecPart; /* size 0xC */

typedef struct MgRecWork {
    /* 0x000 */ MgRecInfo *info;
    /* 0x004 */ MgRecPart part[23];
    /* 0x118 */ s16 slot;
    /* 0x11A */ s16 win[6];
    /* 0x126 */ s16 winFade[6];
    /* 0x132 */ s16 grp;
    /* 0x134 */ s16 gfx[4];
    /* 0x13C */ s16 grp2;
    /* 0x13E */ s16 gfx2;
    /* 0x140 */ s16 unk140;
} MgRecWork; /* size 0x144 */

void func_800E7930_minigame(s16 grp, s16 idx, s16 gfx, u16 prio, s32 x, s32 y);
s16 func_800E7A2C_minigame(u8 *rec, s16 odd, s16 start, s16 end, MgRecPart *mark, MgRecPart *num, MgRecWork *w);
s16 func_800E7BCC_minigame(MgRecWork *w);
void func_800E7F60_minigame(void);
s16 func_800E905C_minigame(s16 slot);

extern MgPos D_800EBAA0_minigame[];
extern s32 D_800EBABC_minigame[];
extern u8 D_800EBACC_minigame[];
extern u8 D_800EBAD4_minigame[];
extern u8 D_800EBADC_minigame[];
extern u8 D_800EBAE4_minigame[];
extern u8 D_800EBAEC_minigame[];


void func_800E7930_minigame(s16 grp, s16 idx, s16 gfx, u16 prio, s32 x, s32 y) {
    func_80055458_main(grp, idx, 0x100);
    HuSprAttrReset(grp, idx, 0xFFFF);
    HuSprAttrSet(grp, idx, 0x9000);
    HuSprScaleSet(grp, idx, 1.0f, 1.0f);
    func_800550F4_main(grp, idx, 0);
    func_80055024_main(grp, idx, gfx, 0);
    HuSprPriSet(grp, idx, prio);
    func_80054904_main(grp, idx, x, y);
}

s16 func_800E7A2C_minigame(u8 *rec, s16 odd, s16 start, s16 end, MgRecPart *mark, MgRecPart *num, MgRecWork *w) {
    u8 *idx;
    u16 grp;
    s16 *gfx;
    u16 x;
    u16 y;
    s32 i;
    s16 ret;
    s16 v;
    s16 g;
    s16 px;
    s16 py;

    idx = odd ? D_800EBAD4_minigame : D_800EBACC_minigame;
    grp = w->grp;
    gfx = w->gfx;
    x = w->info->x;
    y = w->info->y;
    ret = -1;
    for (i = start; i < end; i++, idx++, num++, mark++) {
        v = rec[*idx] - 1;
        if (v < 0) {
            ret = i;
            break;
        }
        mark->fade = 1;
        mark->shown = 1;
        g = gfx[v];
        num->pos = D_800EBAA0_minigame[i];
        px = x + num->pos.x;
        py = y + num->pos.y;
        func_800E7930_minigame(grp, i + 16, g, 1200, px, py);
        num->fade = 1;
        num->shown = 1;
    }
    return ret;
}

// register allocation; the per-rank count local gets a redundant andi (masked 1)
#ifdef NON_MATCHING
s16 func_800E7BCC_minigame(MgRecWork *w) {
    u8 count[4];
    u8 *rec;
    u8 last;
    s32 i;
    s16 r;
    s16 n;
    s16 grp;
    s16 y;
    u16 x0;
    u16 x;
    u8 c;
    s16 k;

    for (i = 0; i < 4; i++) {
        count[i] = 0;
    }
    if (w->slot < 0) {
        last = GwStory.unkF;
        rec = GwStory.unk3;
    } else {
        last = GwStory.unk58[w->slot];
        rec = GwStory.unk10[w->slot];
    }
    if (last != 0) {
        count[last - 1]++;
    }
    for (i = 0; i < 12; i++, rec++) {
        if (*rec != 0) {
            count[*rec - 1]++;
        }
    }
    y = w->info->y - 8;
    x0 = w->info->x - 54;
    n = 0;
    grp = w->grp2;
    for (r = 3; r >= 0; r--) {
        x = x0;
        c = count[r];
        for (i = 0; i < c; i++) {
            func_80054904_main(grp, n, x, y);
            func_80055458_main(grp, n, 0);
            HuSprAttrReset(grp, n, 0x8000);
            n++;
            x += 12;
        }
        y += 14;
    }
    for (k = n; k < 13; k++) {
        HuSprAttrSet(grp, k, 0x8000);
    }
    w->winFade[5] = 1;
    w->unk140 = 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7BCC_minigame);
#endif

// delay-slot filling in the page 2 branch (masked 9)
#ifdef NON_MATCHING
s16 func_800E7E08_minigame(s16 page, MgRecWork *w) {
    u8 *rec;
    s16 odd;
    MgRecPart *mark;
    MgRecPart *num;

    func_8005D294_main(w->win[4]);
    func_8005B43C_main(w->win[4], D_800EBABC_minigame[page], -2, -1);
    w->winFade[4] = 1;
    if (page < 2) {
        odd = 0;
        mark = &w->part[2];
        if (page == 1) {
            odd = 1;
            mark = &w->part[8];
        }
        if (w->slot < 0) {
            rec = GwStory.unk3;
            num = &w->part[16];
        } else {
            rec = GwStory.unk10[w->slot];
            num = &w->part[16];
        }
        return func_800E7A2C_minigame(rec, odd, 0, 6, mark, num, w);
    } else if (page == 2) {
        mark = &w->part[14];
        if (w->slot < 0) {
            rec = &GwStory.unkF;
        } else {
            rec = &GwStory.unk58[w->slot];
        }
        num = &w->part[22];
        return func_800E7A2C_minigame(rec, 0, 6, 7, mark, num, w);
    } else {
        return func_800E7BCC_minigame(w);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7E08_minigame);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7F60_minigame);

Process *func_800E8EC4_minigame(s16 mode, s16 slot) {
    MgRecInfo *info;
    Process *prc;

    if ((mode == 0 || mode == 1) && func_800E905C_minigame(slot) < 0) {
        return NULL;
    }
    info = HuMemAllocTag(sizeof(MgRecInfo), 0x7918);
    memset(info, 0, sizeof(MgRecInfo));
    info->x = 160;
    info->y = 120;
    info->mode = mode;
    info->slot = slot;
    prc = omAddPrcObj(func_800E7F60_minigame, 0x4000, 0x800, 0);
    prc->user_data = info;
    return prc;
}

s32 func_800E8F78_minigame(Process *prc) {
    MgRecInfo *info;
    s32 ret;

    if (prc == NULL) {
        return 0;
    }
    info = prc->user_data;
    info->cmd = 0xFF;
    do {
        HuPrcVSleep();
    } while (info->cmd != 0);
    ret = omDelPrcObj(prc);
    HuMemFree(info);
    return ret;
}

s16 func_800E8FE4_minigame(Process *prc, s16 cmd) {
    return ((MgRecInfo *)prc->user_data)->cmd = cmd;
}

s16 func_800E8FF8_minigame(Process *prc) {
    return ((MgRecInfo *)prc->user_data)->cmd;
}

void func_800E9004_minigame(Process *prc, s16 cmd) {
    MgRecInfo *info = prc->user_data;

    while (info->cmd != cmd) {
        HuPrcVSleep();
    }
}

// retail keeps a raw copy of slot and does not thread the slot >= 6 jump (one extra instruction, masked 15)
#ifdef NON_MATCHING
s16 func_800E905C_minigame(s16 slot) {
    u8 *last;
    u8 *rec;
    s16 score;
    s32 i;
    s16 rank;

    if (slot < 6) {
        if (slot < 0) {
            last = &GwStory.unkF;
            rec = GwStory.unk3;
        } else {
            last = &GwStory.unk58[slot];
            rec = GwStory.unk10[slot];
        }
        if (*last != 0) {
            goto ok;
        }
    }
fail:
    return -1;
ok:
    if (*last >= 5) {
        *last = 4;
    }
    score = D_800EBAE4_minigame[*last];
    for (i = 0; i < 12; i++, rec++) {
        if (*rec == 0) {
            goto fail;
        }
        if (*rec >= 5) {
            *rec = 4;
        }
        score += D_800EBADC_minigame[*rec];
    }
    for (rank = 0; rank < 4; rank++) {
        if (score < D_800EBAEC_minigame[rank]) {
            break;
        }
    }
    return rank;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E905C_minigame);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E9170_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E989C_minigame);
