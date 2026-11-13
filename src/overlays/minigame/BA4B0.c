#include "common.h"

#include "mallocblock.h"

/* Story-mode record board: a process (func_800E7F60_minigame) draws a slot's results. */
typedef struct MgPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MgPos;

typedef struct MgPartDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ MgPos pos;
} MgPartDef; /* size 8 */

typedef struct MgRect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} MgRect; /* size 8 */

typedef struct MgRGB {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
} MgRGB; /* size 3 */

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
s16 func_800E7E08_minigame(s16 page, MgRecWork *w);
void func_800E7F60_minigame(void);
s16 func_800E905C_minigame(s16 slot);

void func_8005BF70_main(s16 winId, s32 alpha);

extern s16 D_800D6B62_main;
extern MgPartDef D_800EB950_minigame[15];
extern s32 D_800EB9C8_minigame[];
extern s32 D_800EB9E4_minigame[];
extern s32 D_800EB9FC_minigame[];
extern s32 D_800EBA14_minigame[];
extern s32 D_800EBA24_minigame[];
extern MgRGB D_800EBA40_minigame[];
extern MgRGB D_800EBA4C_minigame[];
extern MgRGB D_800EBA58_minigame[];
extern MgRect D_800EBA70_minigame[];
extern MgPos D_800EBAA0_minigame[];
extern s32 D_800EBABC_minigame[];
extern u8 D_800EBACC_minigame[];
extern u8 D_800EBAD4_minigame[];
extern u8 D_800EBADC_minigame[];
extern u8 D_800EBAE4_minigame[];
extern u8 D_800EBAEC_minigame[];
extern u8 D_800EBAF4_minigame[];
extern s16 D_800EBAF0_minigame;

void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
Process *func_800E8EC4_minigame(s16 mode, s16 slot);
s32 func_800E8F78_minigame(Process *prc);
s16 func_800E8FE4_minigame(Process *prc, s16 cmd);
s16 func_800E8FF8_minigame(Process *prc);
void func_800E9004_minigame(Process *prc, s16 cmd);


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

// register allocation and stack layout (frame 16 bytes larger); the command switch compiles to a compare tree without retail's case 0 test
#ifdef NON_MATCHING
void func_800E7F60_minigame(void) {
    s16 cur[3];
    s16 step[3];
    s32 msg0;
    s32 msg1;
    s32 msg2;
    s32 msg3;
    MgRecInfo *info;
    s16 *rankWin;
    MgRGB *colorStart;
    MgRGB *color;
    s16 grp;
    s16 lastCmd;
    s16 shown;
    s16 pending;
    s16 alphaStep;
    s16 winAlpha;
    u16 colorFrames;
    s16 colorTimer;
    s16 colorCycle;
    s16 page;
    s16 shownPage;
    s16 changing;
    s16 hasRank;
    s16 rank;
    s32 rank32;
    s32 grpShift;
    MgRecWork *w;
    MgRecPart *part;
    MgPartDef *def;
    s16 *win;
    s16 *fade;
    s16 *gfx;
    s16 alpha;
    s16 winStep;
    s16 done;
    s16 n;
    u16 gfx15;
    u16 grp2;
    s16 py;
    s32 prio;
    s16 spr;
    u16 x;
    u16 y;
    s32 i;

    info = HuPrcCurrentGet()->user_data;
    w = HuMemAllocTag(sizeof(MgRecWork), 0x7918);
    memset(w, 0, sizeof(MgRecWork));
    w->info = info;
    page = 0;
    shownPage = 0;
    for (part = w->part, i = 0; i < 23; i++, part++) {
        part->spr = -1;
        part->alpha = 0x100;
        part->fade = 0;
        part->shown = 0;
    }
    w->gfx2 = -1;
    w->grp2 = -1;
    hasRank = 0;
    rank = -1;
    switch (info->mode) {
    case 0:
    default:
        hasRank = 1;
        rank = func_800E905C_minigame(info->slot);
        msg0 = 0x6101;
        msg2 = D_800EBA14_minigame[GwStory.unk5E[info->slot]];
        msg3 = D_800EBA24_minigame[rank];
        w->slot = info->slot;
        break;
    case 1:
        info->slot = GwStory.unk1;
        hasRank = 1;
        rank = func_800E905C_minigame(-1);
        msg0 = 0x6101;
        msg2 = D_800EBA14_minigame[GwStory.unk2];
        msg3 = D_800EBA24_minigame[rank];
        w->slot = -1;
        break;
    case 2:
        info->slot = GwStory.unk1;
        msg0 = 0x6100;
        msg2 = D_800EBA14_minigame[GwStory.unk2];
        w->slot = -1;
        if (GwStory.unk0 == 12) {
            hasRank = 1;
            rank = func_800E905C_minigame(-1);
            page = 2;
            shownPage = 2;
            msg3 = D_800EBA24_minigame[rank];
        } else {
            page = D_800EBAF4_minigame[GwStory.unk0];
            shownPage = page;
        }
        break;
    }
    msg1 = D_800EB9FC_minigame[info->slot];
    grp = HuSprGrpCreate(23, 0);
    n = 0;
    def = D_800EB950_minigame;
    part = w->part;
    for (i = 0; i < ARRAY_COUNTU(D_800EB950_minigame); i++, n++, def++, part++) {
        prio = 1200;
        spr = func_8000B838_main(def->file);
        part->spr = spr;
        part->pos = def->pos;
        x = part->pos.x + info->x;
        y = part->pos.y + info->y;
        if (i >= 2) {
            prio = 1199;
        }
        func_800E7930_minigame(grp, n, spr, prio, (s16)x, (s16)y);
    }
    HuSprScaleSet(grp, 1, 1.0f, 1.02f);
    func_80055420_main(grp, 1, 0, 0, 0);
    func_80055458_main(grp, 1, 0xFF);
    w->part[1].alpha = 0xFF;
    w->grp = grp;
    gfx15 = w->part[15].spr = func_8000B838_main(D_800EB9E4_minigame[info->slot]);
    w->part[15].pos.x = -96;
    w->part[15].pos.y = -74;
    x = w->part[15].pos.x + info->x;
    y = info->y - 74;
    func_800E7930_minigame(grp, 15, gfx15, 1200, (s16)x, (s16)y);
    for (gfx = w->gfx, i = 0; i < 4; i++, gfx++) {
        *gfx = func_8000B838_main(D_800EB9C8_minigame[i]);
    }
    w->grp2 = HuSprGrpCreate(13, 0);
    w->gfx2 = func_8000B838_main(0x15001D);
    py = info->y - 28;
    for (i = 0; i < 13; i++) {
        x = info->x + (i * 12 - 24);
        func_800E7930_minigame(w->grp2, i, w->gfx2, 1200, (s16)x, py);
    }
    D_800D6B62_main = 400;
    win = w->win;
    fade = w->winFade;
    x = info->x;
    y = info->y;
    for (i = 0; i < ARRAY_COUNTU(w->win); i++, win++, fade++) {
        *win = func_8005A968_main(x + D_800EBA70_minigame[i].x, y + D_800EBA70_minigame[i].y,
                                  D_800EBA70_minigame[i].w, D_800EBA70_minigame[i].h, 0, 12);
        func_8005BDFC_main(*win, 0);
        func_8005BEE0_main(*win, 0);
        func_8005C060_main(*win, 2, 0xFF, 0, 0);
        func_8005C060_main(*win, 4, 0, 0x90, 0);
        func_8005C060_main(*win, 5, 0, 0xB0, 0xC0);
        func_8005C060_main(*win, 6, 0xFF, 0xAD, 0);
        func_8005C154_main(*win, 0x40, 0x40, 0x40);
        func_8005FBF8_main(*win, 0, 0, 0);
        func_8005C02C_main(*win, 7);
        func_8005BF70_main(*win, 0);
        *fade = 0;
    }
    win = w->win;
    func_8005B43C_main(w->win[0], msg0, -1, -1);
    func_8005B43C_main(w->win[1], msg1, -1, -1);
    func_8005B43C_main(w->win[2], msg2, -1, -1);
    w->winFade[2] = 1;
    w->winFade[1] = 1;
    w->winFade[0] = 1;
    if (hasRank) {
        func_8005B43C_main(w->win[3], msg3, -1, -1);
        w->winFade[3] = 1;
        func_8005C060_main(w->win[3], 7, D_800EBA58_minigame[rank].r, D_800EBA58_minigame[rank].g,
                           D_800EBA58_minigame[rank].b);
    }
    func_8005B43C_main(win[5], 0x6111, -1, -1);
    func_800E7E08_minigame(page, w);
    lastCmd = 0;
    w->unk140 = 0;
    shown = 0;
    pending = 0;
    changing = 0;
    alphaStep = 0;
    alpha = 0;
    winStep = 0;
    winAlpha = 0;
    colorCycle = 0;
    colorTimer = 0;
    colorFrames = 0;
    rankWin = &w->win[3];
    rank32 = rank;
    grpShift = grp << 16;
    do {
        if ((lastCmd == 1 || lastCmd == 2) && w->winFade[0] == 0) {
            info->cmd = 0;
        }
        if (pending && ((alphaStep == 0) & (winStep == 0))) {
            pending = 0;
            info->cmd = 0;
        }
        if (changing) {
            if ((alphaStep == 0) & (winStep == 0)) {
                changing = 0;
                func_800E7E08_minigame(page, w);
                alpha = 0;
                alphaStep = 51;
                winAlpha = 0;
                winStep = 51;
                pending = 1;
            }
        } else if (shownPage != page) {
            alpha = 0xFF;
            alphaStep = -51;
            winAlpha = 0xFF;
            winStep = -51;
            w->winFade[4] = 1;
            if (shownPage == 3) {
                w->winFade[5] = 1;
                w->unk140 = 1;
            }
            for (part = w->part, i = 0; i < 23; i++, part++) {
                if (part->shown > 0) {
                    part->shown = 0;
                    part->fade = 1;
                }
            }
            shownPage = page;
            changing = 1;
        }
        if (lastCmd != info->cmd) {
            part = w->part;
            switch (info->cmd) {
            case 1:
                if (shown == 0) {
                    shown = 1;
                    alpha = 0;
                    alphaStep = 36;
                    winAlpha = 0;
                    part[0].fade = 1;
                    part[1].fade = 1;
                    part[15].fade = 1;
                    winStep = 36;
                    if (rank32 == 4) {
                        colorCycle = 1;
                        color = colorStart = D_800EBA40_minigame;
                        colorFrames = 6;
                    } else if (rank32 == 3) {
                        colorCycle = 1;
                        color = colorStart = D_800EBA4C_minigame;
                        colorFrames = 8;
                    }
                }
                break;
            case 2:
                if (shown != 0) {
                    shown = 0;
                    alpha = 0xFF;
                    alphaStep = -36;
                    winAlpha = 0xFF;
                    winStep = -36;
                    part[0].fade = 1;
                    part[1].fade = 1;
                    part[15].fade = 1;
                    for (fade = w->winFade, i = 0; i < 5; i++, fade++) {
                        *fade = 1;
                    }
                    part = w->part;
                    if (shownPage == 3) {
                        w->winFade[5] = 1;
                        w->unk140 = 1;
                    }
                    for (i = 0; i < 23; i++, part++) {
                        if (part->shown > 0) {
                            part->shown = 0;
                            part->fade = 1;
                        }
                    }
                }
                break;
            case 3:
                page++;
                if (page >= 4) {
                    page = 0;
                }
                break;
            case 4:
                page--;
                if (page < 0) {
                    page = 3;
                }
                break;
            }
            lastCmd = info->cmd;
        }
        if (colorCycle) {
            if (colorTimer != 0) {
                colorTimer--;
                cur[0] -= step[0];
                cur[1] -= step[1];
                cur[2] -= step[2];
                func_8005C060_main(*rankWin, 7, (u8)cur[0], (u8)cur[1], (u8)cur[2]);
            } else {
                cur[0] = color->r;
                cur[1] = color->g;
                cur[2] = color->b;
                func_8005C060_main(*rankWin, 7, (u8)cur[0], (u8)cur[1], (u8)cur[2]);
                color++;
                if (color->r == 0 && color->g == 0 && color->b == 0) {
                    color = colorStart;
                }
                step[0] = (cur[0] - color->r) / colorFrames;
                step[1] = (cur[1] - color->g) / colorFrames;
                step[2] = (cur[2] - color->b) / colorFrames;
                colorTimer = colorFrames - 1;
            }
        }
        if (alphaStep != 0) {
            done = 0;
            alpha += alphaStep;
            if (alpha >= 0xFF) {
                alphaStep = 0;
                alpha = 0xFF;
                done = 1;
            } else if (alpha <= 0) {
                alphaStep = 0;
                alpha = 0;
                done = 1;
            }
            for (part = w->part, i = 0; i < 23; i++, part++) {
                if (part->fade > 0) {
                    if (part->fade == 1) {
                        part->fade = 2;
                        HuSprAttrReset(grpShift >> 16, i, 0x8000);
                    }
                    if (done) {
                        part->fade = 0;
                    }
                    if (alpha == 0) {
                        HuSprAttrSet(grpShift >> 16, i, 0x8000);
                    }
                    if (alpha >= part->alpha) {
                        func_80055458_main(grpShift >> 16, i, part->alpha);
                    } else {
                        func_80055458_main(grpShift >> 16, i, alpha);
                    }
                }
            }
            if (w->unk140 != 0) {
                if (done) {
                    w->unk140 = 0;
                }
                grp2 = w->grp2;
                for (i = 0; i < 13; i++) {
                    if (alpha == 0) {
                        HuSprAttrSet(grp2, i, 0x8000);
                    }
                    func_80055458_main(grp2, i, alpha);
                }
            }
        }
        if (winStep != 0) {
            done = 0;
            winAlpha += winStep;
            if (winAlpha >= 0xFF) {
                winStep = 0;
                winAlpha = 0xFF;
                done = 1;
            } else if (winAlpha <= 0) {
                winStep = 0;
                winAlpha = 0;
                done = 1;
            }
            win = w->win;
            for (fade = w->winFade, i = 0; i < 6; i++, win++, fade++) {
                if (*fade > 0) {
                    if (done) {
                        *fade = 0;
                    }
                    func_8005BF70_main(*win, winAlpha);
                }
            }
        }
        HuPrcVSleep();
    } while (lastCmd != 0xFF);
    HuSprGrpKill(grp);
    for (part = w->part, i = 0; i < ARRAY_COUNTU(w->part); i++, part++) {
        if (part->spr >= 0) {
            HuSprKill(part->spr);
        }
    }
    HuSprGrpKill(w->grp2);
    HuSprKill(w->gfx2);
    for (gfx = w->gfx, i = 0; i < 4; i++, gfx++) {
        if (*gfx >= 0) {
            HuSprKill(*gfx);
        }
    }
    for (win = w->win, i = 0; i < ARRAY_COUNTU(w->win); i++, win++) {
        func_8005F364_main(*win);
    }
    HuMemFree(w);
    info->cmd = 0;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7F60_minigame);
#endif

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

// register allocation only (masked 0)
#ifdef NON_MATCHING
void func_800E9170_minigame(void) {
    s16 arrow[2];
    MgPos pos[2];
    s16 *res;
    s16 gfxFrame;
    s16 gfxArrow;
    s16 win;
    s16 gfxBack;
    u16 back;
    u16 frame;
    s16 step;
    s16 ang;
    s16 side;
    s16 slot;
    f32 dx;
    Process *rec;
    s16 i;
    s16 a;

    res = HuPrcCurrentGet()->user_data;
    gfxBack = func_8000B838_main(0x140064);
    back = InitEspriteSlot(gfxBack, 0, 1);
    func_8000BCC8_main(back, 0x4BA);
    func_8000BE5C_main(back, 10.0f, 8.0f);
    func_8000BBD4_main(back, 160, 120);
    func_8000BEAC_main(back, 0, 0, 0);
    func_8000BBFC_main(back, 0);
    func_8000BB94_main(back);
    gfxFrame = func_8000B838_main(0x150001);
    frame = InitEspriteSlot(gfxFrame, 0, 1);
    func_8000BCC8_main(frame, 600);
    func_8000BBD4_main(frame, 160, 204);
    func_8000BBFC_main(frame, 0);
    func_8000BB94_main(frame);
    win = func_8005A968_main(48, 187, 224, 42, 0, 12);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0);
    func_8005BE30_main(win, 1);
    func_8005C060_main(win, 2, 0xFF, 0, 0);
    func_8005C060_main(win, 4, 0, 0x90, 0);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 6, 0xFF, 0xAD, 0);
    func_8005C154_main(win, 0x40, 0x40, 0x40);
    func_8005FBF8_main(win, 0, 0, 0);
    func_8005C02C_main(win, 7);
    func_8005BF70_main(win, 0xFF);
    pos[0].x = 25;
    pos[1].x = 295;
    pos[1].y = 130;
    pos[0].y = 130;
    gfxArrow = func_8000B838_main(0x150003);
    for (i = 0; i < 2; i++) {
        arrow[i] = InitEspriteSlot(gfxArrow, 0, 1);
        func_8000BCC8_main(arrow[i], 100);
        func_8000BBD4_main(arrow[i], pos[i].x, pos[i].y);
        func_8000BBFC_main(arrow[i], 0);
        func_8000BB94_main(arrow[i]);
    }
    func_8000BC48_main(arrow[1], 1);
    if (*res < 0) {
        slot = GwStory.unk1;
    } else {
        slot = *res;
    }
    rec = func_800E8EC4_minigame(0, slot);
    HuPrcVSleep();
    func_800E8FE4_minigame(rec, 1);
    func_8000BB54_main(frame);
    func_8000BB54_main(arrow[0]);
    func_8000BB54_main(arrow[1]);
    func_8000BB54_main(back);
    for (a = 0; a < 0x101; a += 36) {
        func_8000BBFC_main(frame, a);
        func_8000BBFC_main(arrow[0], a);
        func_8000BBFC_main(arrow[1], a);
        if (a < 0x81) {
            func_8000BBFC_main(back, a);
        }
        HuPrcVSleep();
    }
    func_8005B43C_main(win, 0x6125, -1, -1);
    side = 0;
    HuPrcVSleep();
    ang = 0;
    step = 0;
    while (TRUE) {
        if (D_800D5558_main[D_800EBAF0_minigame] & 0x4000) {
            HuAudFXPlay(4);
            *res = -2;
            break;
        }
        if (D_800D5558_main[D_800EBAF0_minigame] & 0x1000) {
            HuAudFXPlay(2);
            *res = -1;
            break;
        }
        if (func_800E8FF8_minigame(rec) == 0) {
            if ((D_800D5558_main[D_800EBAF0_minigame] & 0x100) || D_800CBB6E_main[D_800EBAF0_minigame] >= 31) {
                HuAudFXPlay(1);
                func_800E8FE4_minigame(rec, 3);
                ang = 180;
                step = -22;
                side = 1;
            } else if ((D_800D5558_main[D_800EBAF0_minigame] & 0x200) || D_800CBB6E_main[D_800EBAF0_minigame] < -30) {
                HuAudFXPlay(1);
                func_800E8FE4_minigame(rec, 4);
                ang = 180;
                step = 22;
                side = 0;
            }
        }
        if (step != 0) {
            if ((u16)(ang += step) >= 361) {
                step = 0;
                func_8000BBD4_main(arrow[0], pos[0].x, pos[0].y);
                func_8000BBD4_main(arrow[1], pos[1].x, pos[1].y);
            } else {
                dx = sindf(ang) * 8.0f;
                func_8000BBD4_main(arrow[side], pos[side].x + dx, pos[side].y);
            }
        }
        HuPrcVSleep();
    }
    func_800E8FE4_minigame(rec, 2);
    func_8005D294_main(win);
    for (a = 0x100; a >= 0; a -= 36) {
        func_8000BBFC_main(frame, a);
        func_8000BBFC_main(arrow[0], a);
        func_8000BBFC_main(arrow[1], a);
        if (a < 0x81) {
            func_8000BBFC_main(back, a);
        }
        HuPrcVSleep();
    }
    func_8000BB94_main(frame);
    func_8000BB94_main(arrow[0]);
    func_8000BB94_main(arrow[1]);
    func_8000BB94_main(back);
    func_800E9004_minigame(rec, 0);
    func_800E8F78_minigame(rec);
    func_8000C184_main(back);
    func_8000C184_main(frame);
    func_8000C184_main(arrow[0]);
    func_8000C184_main(arrow[1]);
    HuSprKill(gfxBack);
    HuSprKill(gfxFrame);
    HuSprKill(gfxArrow);
    func_8005F364_main(win);
    omDelPrcObj(NULL);
    *res = -3;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E9170_minigame);
#endif

// register allocation: retail spills the player count, this spills the overlay status
#ifdef NON_MATCHING
void func_800E989C_minigame(void) {
    s32 n;
    GW_PLAYER *p;
    GW_PLAYER *p0;
    GW_PLAYER *tmp;
    s32 i;
    s32 first;
    u16 stat;
    s32 ovl;
    s32 evt;
    s8 stars;

    switch (D_800EBAF4_minigame[GwStory.unk0]) {
    case 0:
        _ClearFlag(0x28);
        _ClearFlag(0);
        _SetFlag(0x1B);
        stat = 0x92;
        ovl = 0x47;
        evt = 0;
        n = 4;
        stars = 0;
        break;
    case 1:
        _ClearFlag(0x28);
        _ClearFlag(0);
        stat = 0x4090;
        ovl = 0x5A;
        evt = 0;
        n = 2;
        stars = 5;
        break;
    case 2:
    default:
        stat = 0x92;
        ovl = 0x70;
        evt = 0;
        omOvlHisChg(-1, 0x70, 0, 0x92);
        GwSystem.minigame_index = 0x42;
        GwSystem.show_minigame_explanations = 0;
        GwPlayer[0].group = 0;
        GwPlayer[0].chr = GwStory.unk1;
        GwPlayer[0].cpu_difficulty = GwStory.unk2;
        for (i = 1; i < 4; i++) {
            GwPlayer[i].group = 1;
            GwPlayer[i].cpu_difficulty = GwStory.unk2;
            GwPlayer[i].chr = 6;
        }
        n = 2;
        stars = 0;
        break;
    }
    first = 1;
    for (i = 0; i < n; i++) {
        GwPlayer[i].star = stars;
        GwPlayer[i].coin = 0;
        if (GwPlayer[i].chr == GwStory.unk1) {
            GwPlayer[i].stat = 0;
            if (first) {
                first = 0;
                if (i != 0) {
                    p = &GwPlayer[i];
                    p0 = &GwPlayer[0];
                    tmp = HuMemAllocTag(sizeof(GW_PLAYER), 0x7918);
                    *tmp = *p0;
                    *p0 = *p;
                    *p = *tmp;
                    HuMemFree(tmp);
                }
            }
        } else {
            GwPlayer[i].stat = 1;
        }
    }
    omOvlHisChg(0, 0x7D, 0, 0x4090);
    omovlhisidx++;
    omOvlGotoEx(ovl, evt, stat);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E989C_minigame);
#endif
