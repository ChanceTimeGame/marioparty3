#include "common.h"
#include "msetup.h"
#include "game/vibrator.h"
#include "mallocblock.h"

s16 HmfAnimRead(HmfData *hmf, s32 dataNum, char *name);
void func_800332D4_main(s16 arg0, f32 arg1);
extern char D_8011A6D8_msetup[]; /* "03tex_DEF" (INCLUDE_RODATA; asm users remain) */
extern s32 D_8011A098_msetup[4]; /* the lifts' sign data numbers */
extern f32 D_8011A0A8_msetup[4]; /* Star Lift rotY per position (D_8011A028_msetup) */


extern u8 D_800D20B8_main[16][3];
extern u8 D_800D5570_main[16][3];


/* fork B: main declarations without a shared prototype */
typedef struct MsTexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} MsTexAnimSlot; /* size = 0xC (MP2 TexAnimSlot) */
extern MsTexAnimSlot *D_800D1714_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);
void func_80032FC0_main(s16, u8, u8);
void func_8006105C_main(s32 winId, u8 alpha);


/* Matches with 506F20.c in the Makefile's W2DC_BLANKSTRIP list (only residue: KMC as adds a nop
   before each mul.s after the sindf/cosdf calls). */
void func_8010ACC0_msetup(s16 model, s16 shadow) {
    f32 angle;
    f32 dAngle;
    f32 t;
    f32 dt;
    f32 y;
    f32 dy;
    f32 x;
    f32 z;
    f32 f;
    s32 i;

    angle = 330.0f;
    dAngle = -4.0f;
    t = 0.0f;
    dt = 5.625f;
    y = 260.0f;
    dy = -18.571428f;
    x = -86.0f;
    z = 617.0f;
    for (i = 0; i < 15; i++) {
        Hu3DModelPosSet(model, x, y, z);
        Hu3DModelPosSet(shadow, x, 0.0f, z);
        f = y + 100.0f;
        func_8010E044_msetup(D_80119AF0_msetup, 0, 100, x, f, z);
        func_8010E044_msetup(D_80119AF0_msetup, 1, 100, x, f, z);
        f = (1.0 - y * 0.009) * 0.6;
        if (f < 0.0f) {
            f = 0.0f;
        }
        Hu3DModelScaleSet(shadow, f, 1.0f, f);
        angle += dAngle;
        y += dy;
        t += dt;
        f = 500.0f - sindf(t) * 500.0f;
        x = f * sindf(angle) + 194.0f;
        z = f * cosdf(angle) + 197.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, 194.0f, 0.0f, 197.0f);
    Hu3DModelPosSet(shadow, 194.0f, 0.0f, 197.0f);
}

void func_8010AF40_msetup(MsModelSlot *slots, MsTexAnim *anim, s16 *frame) {
    s16 model = slots[0].model;
    s16 shadow = slots[3].model;

    D_80119AF0_msetup->work[0] = 1;
    D_80119AF0_msetup->work[1] = 1;
    func_8010E00C_msetup(D_80119AF0_msetup, 2);
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(shadow, 4, 0);
    func_8010ACC0_msetup(model, shadow);
    D_80119AF0_msetup->work[0] = 0;
    HuAudFXPlay(0x135);
    func_8001C814_main(model, 2, 0);
    while (HmfModelData[model].unk40 < 40.0) {
        HuPrcVSleep();
    }
    func_8001C5B4_main(model, slots[2].model);
    while (HmfModelData[model].unk40 < 45.0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A8);
    func_8010B4B8_msetup(model, anim, *frame);
    while (HmfModelData[model].unk40 < 80.0) {
        HuPrcVSleep();
    }
    func_8001F304_main(model, slots[0].unk2);
    func_8001C814_main(model, 2, 2);
}

/* register allocation only: model and shadow swap s2/s3 (tried declaration and assignment order,
   an s32 model). */
#ifdef NON_MATCHING
void func_8010B1F4_msetup(void) {
    MsModelSlot slots[4];
    MsTexAnim anim;
    s16 frame;
    s16 *work;
    s16 state;
    s32 shadow;
    u16 model;
    s32 pad[2]; /* retail frame is 8 bytes larger */

    work = HuPrcCurrentGet()->user_data;
    omAddPrcObj(func_8010B5D0_msetup, 0x3F00, 0x800, 0);
    func_80106030_msetup(D_801198C4_msetup, slots, 4);
    model = slots[0].model;
    shadow = slots[3].model;
    Hu3DModelScaleSet(shadow, 0.6f, 1.0f, 0.6f);
    func_8001F304_main(model, slots[1].unk2);
    func_8001C814_main(model, 2, 2);
    anim.slot = -1;
    frame = func_8010B388_msetup(model, &anim, 0xA007E, "c204n_0_DEF");
    func_8010B4B8_msetup(model, &anim, -1);
    state = 0;
    while (TRUE) {
        if (state != *work) {
            state = *work;
        }
        switch (state) {
        case 0:
            break;
        case 1:
            func_8010AF40_msetup(slots, &anim, &frame);
            *work = 0;
            break;
        case 2:
            func_8001C258_main(model, 4, 4);
            func_8001C258_main(shadow, 4, 4);
            *work = 0;
            break;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B1F4_msetup);
#endif

s16 func_8010B388_msetup(s16 model, MsTexAnim *anim, s32 file, char *name) {
    void *data;
    s32 slot;
    u16 ret;

    if (anim->slot >= 0) {
        func_80033354_main(anim->slot);
        func_80033354_main(anim->anim);
    }
    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    anim->anim = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].unk_00;
    anim->frame = ret;
    anim->slot = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_8010B4B8_msetup(s16 model, MsTexAnim *anim, s16 frame) {
    MsTexAnimSlot *p;

    if (anim->slot >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            p = &D_800D1714_main[anim->slot];
            p->unk_00 = frame;
            p->unk_04 = 0;
            p->unk_0A = 0;
            p->unk_06 = 0;
            p->unk_02 = 0;
        }
    }
}

s16 func_8010B588_msetup(s32 file) {
    void *data;
    s16 ret;

    data = DataRead(file);
    ret = func_800329B4_main(data);
    DataClose(data);
    return ret;
}

void func_8010B5D0_msetup(void) {
    s16 win;
    s16 prev;

    win = func_80060880_main(0xFA, 0xCC, 8);
    func_8005FE54_main(win, 1 << D_8011A948_msetup);
    func_8006105C_main(win, 0xE0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    D_8011A890_msetup = D_8011A892_msetup[0] = win;
    win = func_80060880_main(0xFA, 0xCC, 0x12);
    func_8005FE54_main(win, 1 << D_8011A948_msetup);
    func_8006105C_main(win, 0xE0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    D_8011A892_msetup[1] = win;
    D_8011A990_msetup = 0;
    prev = 0;
    while (TRUE) {
        if (prev != D_8011A990_msetup) {
            switch (D_8011A990_msetup) {
            case 0:
                func_80060EA8_main(D_8011A890_msetup, 1);
                break;
            case 1:
                win = D_8011A890_msetup;
                D_8011A890_msetup = D_8011A892_msetup[0];
                if (prev != 0) {
                    func_80060EA8_main(win, 1);
                }
                func_8005D294_main(D_8011A890_msetup);
                func_80060C14_main(D_8011A890_msetup, 1);
                break;
            case 2:
                win = D_8011A890_msetup;
                D_8011A890_msetup = D_8011A892_msetup[1];
                if (prev != 0) {
                    func_80060EA8_main(win, 1);
                }
                func_8005D294_main(D_8011A890_msetup);
                func_80060C14_main(D_8011A890_msetup, 1);
                break;
            }
            prev = D_8011A990_msetup;
        }
        HuPrcVSleep();
    }
}

void func_8010B82C_msetup(s32 mes) {
    func_8005B43C_main(D_8011A890_msetup, mes, -1, -1);
}

s32 func_8010B858_msetup(void) {
    while (TRUE) {
        if (func_8005E0C0_main(D_8011A890_msetup) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    if (D_800CC69C_main[D_8011A890_msetup].unk_30 != 0) {
        return func_8005E1D8_main(D_8011A890_msetup, 0, 0);
    } else {
        return 0;
    }
}

s32 func_8010B8E0_msetup(void) {
    while (TRUE) {
        if (func_8005E0C0_main(D_8011A890_msetup) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    if (D_800CC69C_main[D_8011A890_msetup].unk_30 != 0) {
        return func_8005E1D8_main(D_8011A890_msetup, 1, 0);
    } else {
        return 0;
    }
}

void func_8010B968_msetup(u32 mes, s8 arg1) {
    func_8005B6BC_main(D_8011A890_msetup, mes, arg1);
}

void func_8010B998_msetup(void) {
    func_8005D294_main(D_8011A890_msetup);
}

void func_8010B9B8_msetup(s32 mask, s32 value) {
    while ((~func_8005B68C_main(D_8011A890_msetup) & mask) == value) {
        HuPrcVSleep();
    }
}

void func_8010BA10_msetup(s32 arg0, s32 arg1) {
    func_8005B63C_main(D_8011A890_msetup, arg0, arg1);
}

s16 func_8010BA3C_msetup(void) {
    /* TextWindow 0xA8 (inside window.h pad86) */
    return *(s16 *)&D_800CC69C_main[D_8011A890_msetup].pad86[0x22];
}

/* one operand order: retail `addu v0,v0,s5` (index + table) for &pos[i], GCC here `addu v0,s5,v0`
   (tried pos + i, i + pos, a direct struct copy, per-field copy). */
#ifdef NON_MATCHING
void func_8010BA6C_msetup(s16 start, s16 count) {
    Vec *pos;
    Vec *src;
    f32 *unkC;
    s32 i;
    s16 delay;
    MsPlayerWork *w;
    Process *proc;

    if (count != 2) {
        pos = D_80119A0C_msetup;
        unkC = D_80119A54_msetup;
    } else {
        pos = D_80119A3C_msetup;
        unkC = D_80119A64_msetup;
    }
    delay = D_80119A6C_msetup[D_8011A938_msetup];
    for (i = start; i < count; i++) {
        D_8011A9E0_msetup[i].state = 0;
        D_8011A9E0_msetup[i].player = i;
        src = &pos[i];
        w = &D_8011A9E0_msetup[i];
        w->pos = *src;
        D_8011A9E0_msetup[i].unkC = unkC[i];
        proc = omAddPrcObj(func_8010BEF8_msetup, 0x4000, 0xC00, 0);
        D_8011A898_msetup[i] = proc;
        proc->user_data = w;
        if (delay != 0) {
            HuPrcSleep(delay);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BA6C_msetup);
#endif

void func_8010BBF4_msetup(s16 arg0) {
    func_8010BA6C_msetup(0, arg0);
}

void func_8010BC18_msetup(s16 start, s16 count) {
    s32 i;
    s32 last = count - 1;

    for (i = start; i < count; i++) {
        D_8011A9E0_msetup[i].state = 0xC;
    }
    while (D_8011A9E0_msetup[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = start; i < count; i++) {
        D_8011A9E0_msetup[i].state = 2;
    }
    while (D_8011A9E0_msetup[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        HuPrcVSleep();
    }
    for (i = start; i < count; i++) {
        D_8011A9E0_msetup[i].state = 0x12;
    }
    HuPrcVSleep();
    while (D_8011A9E0_msetup[last].state != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    for (i = start; i < count; i++) {
        omDelPrcObj(D_8011A898_msetup[i]);
        D_8011A898_msetup[i] = NULL;
    }
    HuPrcVSleep();
    HuPrcVSleep();
}

void func_8010BE8C_msetup(s16 arg0) {
    func_8010BC18_msetup(0, arg0);
}

s16 func_8010BEB0_msetup(s16 player, s16 value) {
    s16 old = D_8011A9E0_msetup[player].state;

    if (value >= 0) {
        D_8011A9E0_msetup[player].state = value;
    }
    return old;
}

/* Register allocation only: retail keeps the model and character in s1/s2 across the first calls
   (GCC here reloads them from their spill slots, 8 bytes higher), and re-extends the badge index
   (`sll 16; sra 15`) at each use. Logic checked block by block against the asm. */
#ifdef NON_MATCHING
/* The per-player process (user_data MsPlayerWork): the character model on its pad, its shadow,
   a sparkle effect and up to three esprite badges (0 COM level, 1 handicap, 2 star) above it.
   work->state requests: 1 sparkle in, 2/4 shrink out, 3 grow in, 5/8/13 show badge 0/1/2,
   6/9/14 fade it out (7/10/15: and free it), 11/12 fade all in/out, 16/17 motions, 18 end. */
void func_8010BEF8_msetup(void) {
    s16 ofs[2];
    Vec2f scr;
    s16 spr[4];
    s16 slot[4];
    s16 alpha[4];
    s16 step[4];
    s16 target[4];
    s16 kill[4];
    s16 mot[2];
    MsPlayerWork *work;
    Vec *pos;
    s32 i;
    s16 idx;
    s32 file;
    s32 motFile;
    s32 n;
    s16 motDef;
    s16 model;
    u16 shadow;
    u16 fx;
    u16 chr;
    s16 noMot;
    s16 play;
    s16 state;
    f32 scale;
    f32 rate;
    HmfModel *m;

    work = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 4; i++) {
        spr[i] = slot[i] = -1;
        kill[i] = alpha[i] = target[i] = step[i] = 0;
    }
    mot[1] = mot[0] = -1;
    chr = D_8011AA34_msetup[work->player];
    model = func_8000B108_main(D_80119964_msetup[chr], 0x2A9);
    func_8001C814_main(model, 2, 2);
    func_8001C258_main(model, 4, 4);
    pos = &work->pos;
    Hu3DModelPosSet(model, work->pos.x, work->pos.y, work->pos.z);
    Hu3DModelRotSet(model, 0.0f, work->unkC, 0.0f);
    motDef = HmfModelData[model].unk02;
    HuPrcVSleep();
    if (D_80119984_msetup[chr] != 0) {
        func_80017790_main(model, 1, chr, func_80017BB8_main(chr, 0xA4));
    } else {
        func_80017790_main(model, 0, chr, func_80017BB8_main(chr, 0xA3));
    }
    func_8001C514_main(model);
    HuPrcVSleep();
    if (D_801198C0_msetup < 0) {
        shadow = D_801198C0_msetup = func_8000B108_main(9, 0x299);
    } else {
        shadow = Hu3DModelLink(D_801198C0_msetup);
    }
    func_8001C258_main(shadow, 4, 4);
    Hu3DModelPosSet(shadow, pos->x, 0.0f, pos->z);
    HuPrcVSleep();
    noMot = 0;
    if ((D_80119ACC_msetup[0] >> D_8011A938_msetup) & 1) {
        noMot = 1;
        motFile = D_801199AC_msetup[chr];
    } else {
        motFile = D_8011998C_msetup[chr];
    }
    state = 0;
    mot[0] = func_8000B13C_main(motFile);
    HuPrcVSleep();
    mot[1] = func_8000B13C_main(D_801199EC_msetup[chr]);
    HuPrcVSleep();
    fx = func_8010CAF0_msetup(0x110012, 0x289);
    scale = 0.0f;
    rate = scale;
    play = 0;
    do {
        HuPrcVSleep();
        if (state != work->state) {
            state = work->state;
        }
        switch (state) {
        case 0:
            break;
        case 1:
            for (i = 15; i != 0; i--) {
                func_8010CD14_msetup(fx, pos->x, pos->y + 50.0f, pos->z);
                HuPrcVSleep();
            }
            work->state = 3;
            break;
        case 3:
            func_8001C258_main(model, 4, 0);
            func_8001C258_main(shadow, 4, 0);
            if (mot[0] >= 0 && (noMot == 0 || work->player != 0)) {
                func_8001C5B4_main(model, mot[0]);
                play = 1;
            }
            scale = 0.0f;
            rate = 1.0f / 15;
            for (i = 15; i != 0; i--) {
                scale += rate;
                Hu3DModelScaleSet(model, scale, 1.0f, scale);
                Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
                HuPrcVSleep();
            }
            work->state = 0;
            break;
        case 2:
            scale = 1.0f;
            rate = 1.0f / 7;
            work->state = 4;
            break;
        case 4:
            scale -= rate;
            if (scale <= 0.0f) {
                scale = 0.0f;
                func_8001C258_main(model, 4, 4);
                func_8001C258_main(shadow, 4, 4);
                work->state = 0;
            }
            Hu3DModelScaleSet(model, scale, 1.0f, scale);
            Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
            func_8010CD14_msetup(fx, pos->x, pos->y + 50.0f, pos->z);
            break;
        case 11:
            for (i = 0; i < 4; i++) {
                if (slot[i] >= 0) {
                    func_8000BB54_main(slot[i]);
                    target[i] = D_80119AC8_msetup[i];
                    step[i] = (u8)(D_80119AC8_msetup[i] / 5);
                }
            }
            work->state = 0;
            break;
        case 12:
            for (i = 0; i < 4; i++) {
                target[i] = 0;
                step[i] = -alpha[i] / 5;
            }
            work->state = 0;
            break;
        case 13:
            n = D_8011AA3C_msetup[work->player] - 1;
            if (n < 0) {
                break;
            }
            file = D_80119AB4_msetup[n];
            idx = 2;
            ofs[0] = 28;
            ofs[1] = -48;
            goto show;
        case 15:
            kill[2] = 1;
        case 14:
            idx = 2;
            goto hide;
        case 5:
            file = D_80119A7C_msetup[D_8011AA38_msetup[work->player]];
            idx = 0;
            ofs[0] = 8;
            ofs[1] = -6;
            goto show;
        case 7:
            kill[0] = 1;
        case 6:
            idx = 0;
            goto hide;
        case 8:
            file = D_80119A8C_msetup[D_8011AA3C_msetup[work->player]];
            idx = 1;
            ofs[0] = 16;
            ofs[1] = -30;
        show:
            if (slot[idx] >= 0) {
                func_8000C184_main(slot[idx]);
            }
            if (spr[idx] >= 0) {
                HuSprKill(spr[idx]);
            }
            kill[idx] = 0;
            spr[idx] = func_8000B838_main(file);
            slot[idx] = InitEspriteSlot(spr[idx], 0, 1);
            func_8000BCC8_main(slot[idx], 1);
            func_80012B14_main(0, pos, &scr);
            func_8000BBD4_main(slot[idx], ofs[0] + scr.x, ofs[1] + scr.y);
            func_8000BBFC_main(slot[idx], 0);
            func_8000BB54_main(slot[idx]);
            target[idx] = D_80119AC8_msetup[idx];
            step[idx] = (u8)(D_80119AC8_msetup[idx] / 7);
            work->state = 0;
            break;
        case 10:
            kill[1] = 1;
        case 9:
            idx = 1;
        hide:
            target[idx] = 0;
            step[idx] = -alpha[idx] / 7;
            work->state = 0;
            if (alpha[idx] == 0 && kill[idx] != 0) {
                kill[idx] = 0;
                if (slot[idx] >= 0) {
                    func_8000C184_main(slot[idx]);
                    slot[idx] = -1;
                }
                if (spr[idx] >= 0) {
                    HuSprKill(spr[idx]);
                    spr[idx] = -1;
                }
            }
            break;
        case 16:
            if (mot[1] >= 0) {
                func_8001C5B4_main(model, mot[1]);
            }
            work->state = 0;
            break;
        case 17:
            if (mot[0] >= 0) {
                func_8001C624_main(model, HmfModelData[mot[0]].unk02, 0, 6, 0);
            }
            work->state = 0;
            play = 1;
            break;
        case 18:
            state = -1;
            break;
        }
        if (play != 0) {
            m = &HmfModelData[model];
            if (D_800CCF58_main[m->unk02].unk02 <= m->unk40) {
                func_8001C624_main(model, motDef, 0, 30, 2);
                play = 0;
            }
        }
        for (i = 0; i < 4; i++) {
            if (slot[i] < 0) {
                continue;
            }
            if (step[i] == 0) {
                continue;
            }
            alpha[i] += step[i];
            if (step[i] < 0) {
                if (alpha[i] <= target[i]) {
                    alpha[i] = target[i];
                    step[i] = 0;
                }
            } else if (alpha[i] >= target[i]) {
                alpha[i] = target[i];
                step[i] = 0;
            }
            func_8000BBFC_main(slot[i], alpha[i]);
            if (alpha[i] != 0) {
                continue;
            }
            func_8000BB94_main(slot[i]);
            if (kill[i] == 0) {
                continue;
            }
            kill[i] = 0;
            if (slot[i] >= 0) {
                func_8000C184_main(slot[i]);
                slot[i] = -1;
            }
            if (spr[i] >= 0) {
                HuSprKill(spr[i]);
                spr[i] = -1;
            }
        }
    } while (state >= 0);
    for (i = 0; i < 4; i++) {
        if (slot[i] >= 0) {
            func_8000C184_main(slot[i]);
        }
        if (spr[i] >= 0) {
            HuSprKill(spr[i]);
        }
    }
    if (D_800D20B8_main[chr][1] != 0xFF) {
        func_80033354_main(D_800D20B8_main[chr][1]);
        func_80033354_main(D_800D5570_main[chr][1]);
        D_800D20B8_main[chr][1] = 0xFF;
    }
    func_8001ACDC_main(model);
    func_8001ACDC_main(shadow);
    if (D_801198C0_msetup == (s16)shadow) {
        D_801198C0_msetup = -1;
    }
    for (i = 0; i < 2; i++) {
        if (mot[i] >= 0) {
            func_8001ACDC_main(mot[i]);
        }
    }
    func_8001ACDC_main(fx);
    work->state = 0;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BEF8_msetup);
#endif

s16 func_8010CAF0_msetup(s32 dir, s32 file) {
    MsFxHmf *hmf;
    MsFxWork *work;
    MsFxPart *part;
    s16 model;
    s16 i;
    f32 radius;
    f32 step;
    f32 speed;

    model = func_8000B108_main(dir, file);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010CE8C_msetup);
    hmf = (MsFxHmf *)HmfModelData[model].hmf;
    work = (MsFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->unk08 = 30.0f;
    work->unk0C = 720.0f;
    work->unk10 = 80.0f;
    work->unk14 = 5.0f;
    radius = work->unk10 / 10.0f;
    step = (work->unk10 - radius) / work->unk08;
    speed = work->unk0C / work->unk08;
    for (i = 0; i < hmf->groupCount; i++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->angle = 0.0f;
        part->radius = radius;
        part->radiusStep = step;
        part->vel.x = speed;
        part->vel.y = 0.0f;
        part->vel.z = 0.0f;
        part->scale = 0.0f;
        part->phase = 180.0f;
        part++;
    }
    return model;
}

void func_8010CC70_msetup(s16 model, f32 unk08, f32 unk0C, f32 unk10, f32 unk14) {
    MsFxHmf *hmf;
    MsFxWork *work;
    MsFxPart *part;
    s16 i;
    f32 step;
    f32 speed;

    hmf = (MsFxHmf *)HmfModelData[model].hmf;
    work = (MsFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->unk08 = unk08;
    work->unk0C = unk0C;
    work->unk10 = unk10;
    work->unk14 = unk14;
    step = (unk10 - unk10 / 10.0f) / unk08;
    speed = unk0C / unk08;
    for (i = 0; i < hmf->groupCount; i++) {
        part->radiusStep = step;
        part->vel.x = speed;
        part++;
    }
}

s32 func_8010CD14_msetup(s16 model, f32 x, f32 y, f32 z) {
    MsFxHmf *hmf;
    MsFxWork *work;
    MsFxPart *part;
    s16 i;
    f32 tilt;

    hmf = (MsFxHmf *)HmfModelData[model].hmf;
    work = (MsFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->phase >= 180.0f) {
            part->angle = func_80106208_msetup(360);
            part->radius = work->unk10 / 10.0f;
            tilt = func_80106208_msetup(150);
            tilt -= 75.0f;
            if (tilt < 0.0f) {
                tilt += 360.0f;
            }
            part->vel.y = sindf(tilt);
            part->vel.z = cosdf(tilt);
            part->scale = 0.0f;
            part->phase = 0.0f;
            return 1;
        }
    }
    return 0;
}

/* retail .rodata holds 8 zero bytes after func_8010CD14_msetup's 2^32 (unreferenced; likely the
   end of a retail object, as the text padding before func_8010D060_msetup) */
const s32 D_8011A688_msetup[2] = { 0, 0 };


/* Instruction-identical, but retail pads 12 bytes (nops) after it so func_8010D060_msetup starts
   16-aligned: func_8010D060_msetup probably begins another retail object (split the unit there). */
#ifdef NON_MATCHING
void func_8010CE8C_msetup(s16 model) {
    MsFxHmf *hmf;
    MsFxWork *work;
    MsFxPart *part;
    s16 i;
    s16 count;
    f32 r;

    hmf = (MsFxHmf *)HmfModelData[model].hmf;
    work = (MsFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    count = hmf->groupCount;
    for (i = 0; i < count; i++, part++) {
        if (part->phase < 180.0f) {
            part->angle += part->vel.x;
            if (part->angle < 0.0f) {
                part->angle += 360.0f;
            } else if (part->angle >= 360.0f) {
                part->angle -= 360.0f;
            }
            part->radius += part->radiusStep;
            r = part->radius * part->vel.z;
            part->pos.x = r * sindf(part->angle) + work->center.x;
            part->pos.z = r * cosdf(part->angle) + work->center.z;
            part->pos.y = part->radius * part->vel.y + work->center.y;
            part->phase += work->unk14;
            if (part->phase > 180.0f) {
                part->phase = 180.0f;
            }
            part->scale = sindf(part->phase) * work->unk14;
        }
    }
    work->frame++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CE8C_msetup);
#endif

void func_8010D060_msetup(HmfData *hmf, s16 idx) {
    if ((s8)hmf->unk84[idx].unk3 != -1) {
        hmf->unk84[idx].unk9 |= 0x80;
    }
}

void func_8010D094_msetup(HmfData *hmf, s16 idx) {
    if ((s8)hmf->unk84[idx].unk3 != -1) {
        hmf->unk84[idx].unk9 &= 0x7F;
    }
}

s16 func_8010D0C8_msetup(s16 model, char *name) {
    HmfData *hmf;
    MsTexEntry *found;
    s16 hash;
    s32 i;

    hmf = HmfModelData[model].hmf;
    hash = func_80011460_main(name);
    found = NULL;
    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].hash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
            found = &D_800D1FCC_main[i];
            break;
        }
    }
    if (i == 128 || found == NULL) {
        osSyncPrintf("Can't Find TextureName! mSetupGetMpAttrIdx\n");
        return -1;
    }
    for (i = 0; i < hmf->unk12; i++) {
        if ((MsTexEntry *)hmf->unk84[i].unkC == found) {
            break;
        }
    }
    if (i >= hmf->unk12) {
        i = -1;
    }
    return i;
}

/* logic checked; retail keeps dx/dy as words (lw, then sll/sra at each use) where GCC here reads
   the stack halfword, which changes the frame and register allocation. */
#ifdef NON_MATCHING
s16 func_8010D234_msetup(s16 (*pos)[2], u8 *used, s16 count, s16 cur, s32 dx, s32 dy) {
    f32 cx;
    f32 cy;
    f32 len;
    f32 fx;
    f32 fy;
    f32 best;
    f32 d;
    f32 ddx;
    f32 ddy;
    f32 nx;
    f32 ny;
    s16 bestIdx;
    s16 i;

    cx = pos[cur][0];
    cy = pos[cur][1];
    len = HuSqrtf((s16)dx * (s16)dx + (s16)dy * (s16)dy);
    if (len != 0.0f) {
        fx = (s16)dx / len;
        fy = (s16)dy / len;
        best = 100000.0f;
        bestIdx = -1;
        for (i = 0; i < count; i++) {
            if (i == cur || used[i] != 0) {
                continue;
            }
            ddx = cx - pos[i][0];
            ddy = cy - pos[i][1];
            d = HuSqrtf(ddx * ddx + ddy * ddy);
            if (d != 0.0f) {
                nx = ddx / d;
                ny = ddy / d;
            } else {
                nx = ny = 0.0f;
            }
            ddx = fx - nx;
            ddy = fy - ny;
            if (!(ddx * ddx + ddy * ddy > 0.25f) && d < best) {
                best = d;
                bestIdx = i;
            }
        }
        cur = bestIdx;
    }
    return cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D234_msetup);
#endif

// register allocation: retail copies arg0 to t3 and loads pad into a0 (masked 16, same blocks)
#ifdef NON_MATCHING
s16 func_8010D4DC_msetup(s16 (*arg0)[2], u8 *arg1, s32 arg2, s16 arg3, s16 pad, s32 btn) {
    s16 x = -D_800CBB6E_main[pad];
    s16 y = D_800D20A1_main[pad];

    if (btn & 0x200) {
        if (x < 30) {
            x = 100;
        }
    } else if (btn & 0x100) {
        if (x > -30) {
            x = -100;
        }
    }
    if (btn & 0x800) {
        if (y < 30) {
            y = 100;
        }
    } else if (btn & 0x400) {
        if (y > -30) {
            y = -100;
        }
    }
    return func_8010D234_msetup(arg0, arg1, arg2, arg3, x, y);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D4DC_msetup);
#endif

s16 func_8010D5EC_msetup(s16 pad) {
    u16 btn = D_800CDA7C_main[pad];
    s8 y = D_800D20A1_main[pad];
    s8 x = D_800CBB6E_main[pad];

    if (x > 30) {
        btn |= 0x100;
    } else if (x < -30) {
        btn |= 0x200;
    }
    if (y > 30) {
        btn |= 0x800;
    } else if (y < -30) {
        btn |= 0x400;
    }
    return btn;
}

s32 func_8010D684_msetup(s16 pad, s16 *prev) {
    u16 old = *prev;
    s16 now = func_8010D5EC_msetup(pad);

    old &= now;
    old ^= now;
    *prev = now;
    return (s16)old;
}

// retail passes work->prio with lh (called unprototyped?), lhu here (masked 1); s7/s8 swapped
#ifdef NON_MATCHING
void func_8010D6D0_msetup(void) {
    MsSprWork *work;
    s16 *xy;
    s16 spr;
    s16 slot;
    s16 prevState;
    s16 shown;
    s16 startX;
    s16 startY;
    s16 dx;
    s16 dy;
    s16 prevIdx;
    s16 alpha;
    s16 step;
    s16 tx;
    s16 ty;
    s16 x;
    s16 y;
    s16 t;
    f32 s;

    work = HuPrcCurrentGet()->user_data;
    xy = &work->x;
    spr = func_8000B838_main(work->file);
    slot = InitEspriteSlot(spr, work->prio, 1);
    func_8000BCC8_main(slot, 1);
    x = tx = work->x;
    y = ty = work->y;
    func_8000BBD4_main(slot, x, y);
    func_8000BB94_main(slot);
    shown = 0;
    alpha = 0;
    step = 0;
    prevIdx = work->idx;
    t = 0;
    prevState = work->state;
    startX = x;
    startY = y;
    dy = 0;
    dx = 0;
    while (1) {
        if (prevState != work->state) {
            switch (work->state) {
            case 0:
                break;
            case 1:
                step = 0x40;
                if (shown == 0) {
                    alpha = 0;
                    func_8000BBFC_main(slot, 0);
                    func_8000BB54_main(slot);
                    shown = 1;
                }
                break;
            case 2:
                if (shown != 0) {
                    step = -0x40;
                }
                break;
            case -1:
                func_8000C184_main(slot);
                HuSprKill(spr);
                work->state = 100;
                while (1) {
                    HuPrcVSleep();
                }
            }
            prevState = work->state;
        }
        if (prevIdx != work->idx) {
            prevIdx = work->idx;
            if (work->pos != NULL) {
                xy[0] = work->pos[prevIdx][0];
                xy[1] = work->pos[prevIdx][1];
            }
        }
        if (tx != xy[0] || ty != xy[1]) {
            tx = xy[0];
            ty = xy[1];
            t = work->time;
            if (t != 0) {
                startX = x;
                startY = y;
                dx = tx - x;
                dy = ty - y;
            }
        }
        if (step != 0) {
            alpha += step;
            if (alpha >= 0x100) {
                alpha = 0xFF;
                step = 0;
            } else if (alpha < 0) {
                alpha = 0;
                step = 0;
                func_8000BB94_main(slot);
                shown = 0;
            }
            func_8000BBFC_main(slot, alpha);
        }
        if ((x != tx) | (y != ty)) {
            if (t == 0) {
                x = tx;
                y = ty;
            } else {
                t--;
                s = sindf((90.0f / work->time) * (work->time - t));
                x = startX + dx * s;
                y = startY + dy * s;
            }
            func_8000BBD4_main(slot, x, y);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D6D0_msetup);
#endif

// register allocation only (masked 0): work/slot/y in s4/s3/s2
#ifdef NON_MATCHING
void func_8010DAC4_msetup(omObjData *obj) {
    MsArrowWork *work;
    s32 i;
    s16 slot;
    s16 x;
    s16 y;
    f32 s;

    work = obj->data;

    if (obj->work[0] != obj->work[3]) {
        switch (obj->work[0]) {
        case 0:
            break;
        case 1:
            obj->work[2] = 0;
            func_8000BB54_main(obj->model[0]);
            func_8000BB54_main(obj->model[1]);
            break;
        case 2:
            obj->work[2] = 0xFF;
            break;
        case 3:
            if (obj->work[3] == 4) {
                i = obj->work[2];
                func_8000BBD4_main(obj->model[i], work->pos[i][0], work->pos[i][1]);
            }
            obj->work[2] = 0;
            obj->work[1] = 5;
            work->angle = 360.0f;
            work->speed = -36.0f;
            break;
        case 4:
            if (obj->work[3] == 3) {
                i = obj->work[2];
                func_8000BBD4_main(obj->model[i], work->pos[i][0], work->pos[i][1]);
            }
            obj->work[2] = 1;
            obj->work[1] = 5;
            work->angle = 0.0f;
            work->speed = 36.0f;
            break;
        case 0xFF:
            func_8000C184_main(obj->model[0]);
            func_8000C184_main(obj->model[1]);
            HuSprKill(obj->model[2]);
            HuSprKill(obj->model[3]);
            obj->work[0] = 0;
            break;
        }
        obj->work[3] = obj->work[0];
    }
    switch (obj->work[3]) {
    case 0:
        break;
    case 1:
        i = obj->work[2] + obj->work[1];
        if (i >= 0x100) {
            i = 0xFF;
            obj->work[0] = 0;
        }
        obj->work[2] = i;
        func_8000BBFC_main(obj->model[0], i);
        func_8000BBFC_main(obj->model[1], i);
        break;
    case 2:
        i = obj->work[2] - obj->work[1];
        if (i < 0) {
            i = 0;
            func_8000BB94_main(obj->model[0]);
            func_8000BB94_main(obj->model[1]);
            obj->work[0] = 0;
        }
        obj->work[2] = i;
        func_8000BBFC_main(obj->model[0], i);
        func_8000BBFC_main(obj->model[1], i);
        break;
    case 3:
    case 4:
        i = obj->work[2];
        slot = obj->model[i];
        x = work->pos[i][0];
        y = work->pos[i][1];
        if (obj->work[1] == 0) {
            obj->work[0] = 0;
        } else {
            obj->work[1]--;
            work->angle += work->speed;
            s = sindf(work->angle) * 12.0f;
            x += s;
        }
        func_8000BBD4_main(slot, x, y);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DAC4_msetup);
#endif

void func_8010DDD8_msetup(omObjData *obj) {
    func_8000C184_main(obj->model[0]);
    func_8000C184_main(obj->model[1]);
    HuSprKill(obj->model[2]);
    HuSprKill(obj->model[3]);
    HuMemFree(obj->data);
    omDelObj(obj);
}

omObjData *func_8010DE38_msetup(s32 x0, s32 x1, s32 y) {
    omObjData *obj;
    MsArrowWork *work;
    s16 spr;
    s16 slot;

    obj = omAddObj(0x17D0, 4, 0, -1, func_8010DAC4_msetup);
    if (obj == NULL) {
        return NULL;
    }
    omSetStatBit(obj, 0x100);
    work = HuMemAllocTag(sizeof(MsArrowWork), 0x7918);
    memset(work, 0, sizeof(MsArrowWork));
    obj->data = work;
    spr = func_8000B838_main(0x140012);
    slot = InitEspriteSlot(spr, 0, 1);
    obj->model[0] = slot;
    obj->model[2] = spr;
    func_8000BCC8_main(slot, 0x4800);
    func_8000BBD4_main(slot, x0, y);
    func_8000BB94_main(slot);
    work->pos[0][0] = x0;
    work->pos[0][1] = y;
    spr = func_8000B838_main(0x140013);
    slot = InitEspriteSlot(spr, 0, 1);
    obj->model[1] = slot;
    obj->model[3] = spr;
    func_8000BCC8_main(slot, 0x4800);
    func_8000BBD4_main(slot, x1, y);
    func_8000BB94_main(slot);
    work->pos[1][0] = x1;
    work->pos[1][1] = y;
    for (slot = 0; slot < 4; slot++) {
        obj->work[slot] = 0;
    }
    return obj;
}

s16 func_8010E00C_msetup(omObjData *obj, s16 count) {
    MsEmitWork *work;

    if (obj == NULL) {
        return 0;
    }
    work = obj->data;
    if (count >= 5) {
        count = 4;
    }
    work->count = count;
    return count;
}

void func_8010E044_msetup(omObjData *obj, s16 idx, s16 arg2, f32 x, f32 y, f32 z) {
    MsEmitWork *work;

    if (obj != NULL) {
        work = obj->data;
        if (idx < work->count) {
            work->pos[idx].x = x;
            work->pos[idx].y = y;
            work->pos[idx].z = z;
            work->range[idx] = arg2;
        }
    }
}

// retail loads model[0] straight into a0 and copies it to s1 (one instruction fewer); otherwise the same
#ifdef NON_MATCHING
void func_8010E09C_msetup(omObjData *obj) {
    MsEmitWork *work;
    Vec *pos;
    s32 model;
    s32 range;
    s32 i;
    f32 dx;
    f32 dz;
    s32 pad[2]; /* retail's frame is 8 bytes larger */

    model = obj->model[0];
    if (obj->work[1] != obj->work[2]) {
        func_8000CD00_main(model, D_80119AF4_msetup, D_80119AF8_msetup, D_80119AFC_msetup[0]);
        obj->work[2] = obj->work[1];
    }
    work = obj->data;
    switch (obj->work[0]) {
    case 0:
        break;
    case 1:
        for (i = 0; i < work->count; i++) {
            range = work->range[i];
            pos = &work->pos[i];
            dx = (rand8() * range / 256 - range / 2);
            dz = (rand8() * range / 256 - range / 2);
            func_8000CD74_main(model, dx + pos->x, pos->y, dz + pos->z);
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E09C_msetup);
#endif

omObjData *func_8010E21C_msetup(void) {
    omObjData *obj;
    MsEmitWork *work;
    MsFxWork *fx;
    s16 model;

    D_80119AF0_msetup = obj = omAddObj(0x17D0, 1, 0, -1, func_8010E09C_msetup);
    if (obj == NULL) {
        return NULL;
    } else {
        omSetStatBit(obj, 0x100);
        work = HuMemAllocTag(sizeof(MsEmitWork), 0x7918);
        memset(work, 0, sizeof(MsEmitWork));
        obj->data = work;
        model = func_8000CBA0_main(0x110012, 0x289);
        obj->model[0] = model;
        fx = MS_FX_WORK(model);
        fx->center.x = fx->center.y = fx->center.z = 0.0f;
        fx->unk10 = 100.0f;
        obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
        obj->work[0] = 0;
        obj->work[1] = 0;
        obj->work[2] = 0xFF;
        obj->work[3] = 0;
        return obj;
    }
}

void func_8010E32C_msetup(MsLift *lifts, s32 count, f32 rotY, s32 link) {
    MsLift *lift;
    Vec *rot;
    s32 i;
    s16 model;
    s16 base;

    base = -1;
    for (i = 0; i < count; i++) {
        if ((base < 0) | (link == 0)) {
            model = base = func_8000B108_main(0x140003, 0x2A9);
        } else {
            model = Hu3DModelLink(base);
        }
        lifts[i].model = model;
        lifts[i].unk20 = 0;
        lift = &lifts[i];
        rot = &lift->rot;
        rot->x = rot->z = 0.0f;
        if (i != 0) {
            rot->y = rotY + 180.0f;
        } else {
            rot->y = rotY;
        }
        Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
        lift->pos = D_80119B20_msetup;
        Hu3DModelPosSet(model, lift->pos.x, lift->pos.y, lift->pos.z);
        Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
        HuPrcVSleep();
    }
}


void func_8010E4BC_msetup(MsLift *lifts, s32 count, f32 rotY) {
    func_8010E32C_msetup(lifts, count, rotY, 1);
}

void func_8010E4D8_msetup(MsLift *lifts, s32 count) {
    s32 i;

    for (i = 0; i < count; i++, lifts++) {
        func_8001C514_main(lifts->model);
    }
}

void func_8010E52C_msetup(MsLift *lifts, MsLiftKey *keys, s16 count, s16 frames, s16 *models, u16 nmodels,
                         f32 scale0, f32 scale1) {
    Vec pos;
    MsLift *lift;
    MsLiftKey *key;
    Vec *rot;
    f32 dscale;
    f32 t;
    f32 ry;
    f32 scale;
    s32 i;
    s32 j;
    s32 k;
    s16 model;

    dscale = scale1 - scale0;
    for (i = 0; i < frames; i++) {
        t = (f32)i / frames;
        for (j = 0; j < count; j++) {
            if (lifts[j].unk20 & 1) {
                continue;
            }
            model = lifts[j].model;
            lift = &lifts[j];
            key = &keys[j];
            pos.x = (key->pos.x - lift->pos.x) * t;
            pos.y = (key->pos.y - lift->pos.y) * t;
            pos.z = (key->pos.z - lift->pos.z) * t;
            pos.x += lift->pos.x;
            pos.y += lift->pos.y;
            pos.z += lift->pos.z;
            rot = &lift->rot;
            if (lift->rot.y > 180.0f) {
                scale = lift->rot.y - 360.0f;
                ry = (key->rotY - scale) * t + scale;
            } else {
                ry = (keys[j].rotY - rot->y) * t + rot->y;
            }
            Hu3DModelRotSet(model, rot->x, ry, rot->z);
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        }
        scale = scale0 + t * dscale;
        if (models != NULL) {
            for (k = 0; k < (s16)nmodels; k++) {
                if (models[k] >= 0) {
                    Hu3DModelScaleSet(models[k], scale, scale, scale);
                }
            }
        }
        HuPrcVSleep();
    }
    for (j = 0; j < count; j++) {
        if (lifts[j].unk20 & 1) {
            continue;
        }
        model = lifts[j].model;
        lift = &lifts[j];
        lift->pos = keys[j].pos;
        lift->rot.y = keys[j].rotY;
        Hu3DModelPosSet(model, lift->pos.x, lift->pos.y, lift->pos.z);
        Hu3DModelRotSet(model, lift->rot.x, lift->rot.y, lift->rot.z);
    }
    if (models != NULL) {
        for (k = 0; k < (s16)nmodels; k++) {
            if (models[k] >= 0) {
                Hu3DModelScaleSet(models[k], scale1, scale1, scale1);
            }
        }
    }
}

void func_8010E8C8_msetup(MsLift *lifts, s16 count, s16 frames, f32 rotY, f32 posY, f32 scale0, f32 scale1,
                         s16 nfx) {
    MsLift *lift;
    Vec *pos;
    Vec *rot;
    f32 drot;
    f32 dy;
    f32 dscale;
    s16 n;
    s32 i;
    s16 model;

    if ((D_80119AF0_msetup != NULL) & (nfx != 0)) {
        D_80119AF0_msetup->work[0] = 1;
        D_80119AF0_msetup->work[1] = 1;
        n = func_8010E00C_msetup(D_80119AF0_msetup, nfx);
    } else {
        n = 0;
    }
    drot = rotY / frames;
    dy = posY / frames;
    dscale = (scale1 - scale0) / frames;
    while (frames != 0) {
        lift = lifts;
        for (i = 0; i < count; i++) {
            if (lift->unk20 & 1) {
                continue;
            }
            model = lift->model;
            pos = &lift->pos;
            rot = &lift->rot;
            lift->rot.y += drot;
            if (lift->rot.y >= 360.0f) {
                lift->rot.y -= 360.0f;
            }
            if (rot->y < 0.0f) {
                rot->y += 360.0f;
            }
            pos->y += dy;
            Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
            Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
            Hu3DModelScaleSet(model, scale0, scale0, scale0);
            if (i < n) {
                func_8010E044_msetup(D_80119AF0_msetup, i, 0x78, pos->x, pos->y, pos->z);
            }
            lift++;
        }
        scale0 += dscale;
        HuPrcVSleep();
        frames--;
    }
    lift = lifts;
    for (i = 0; i < count; i++) {
        if (lift->unk20 & 1) {
            continue;
        }
        Hu3DModelScaleSet(lift->model, scale1, scale1, scale1);
        lift++;
    }
    if (n != 0) {
        D_80119AF0_msetup->work[0] = 0;
    }
}

// float registers: 0.8f and -1/7 hoisted into f24/f22 swapped (masked 2)
#ifdef NON_MATCHING
void func_8010EB94_msetup(void) {
    /* Retail's 8-entry loops (init, case 9) index kill[] up to 7: they reach step, alpha and the
       two halfwords after them (in-object here; past retail's 0x1C-byte block). Init zeroes them;
       case 9 sets kill[4..7] to 1 only for obj[4..7] >= 0, which nothing sets. */
    struct {
        f32 scale[2];
        f32 speed[2];
        s16 kill[4];
        s16 step[1];
        s16 alpha[1];
        s16 unk1C[2];
    } w;
    MsPreviewWork *work;
    s16 *obj;
    s16 *res;
    s32 i;
    s16 j;
    s16 m;
    s16 prev;
    f32 sc;

    work = HuPrcCurrentGet()->user_data;
    obj = work->obj;
    res = work->res;
    for (i = 0; i < 8; i++) {
        obj[i] = -1;
        res[i] = -1;
        w.kill[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        w.speed[i] = 0.0f;
    }
    for (i = 0; i < 1; i++) {
        w.step[i] = 0;
    }
    work->state = 0;
    prev = 0;
    sc = 0.8f;
    while (1) {
        if (prev != work->state) {
            switch (work->state) {
            case 0:
                break;
            case 1:
                if (obj[0] >= 0 && obj[2] >= 0) {
                    w.scale[0] = 0.0f;
                    w.speed[0] = 1.0f / 7.0f;
                    m = obj[0];
                    func_8001C258_main(m, 4, 0);
                    Hu3DModelPosSet(m, 260.0f, 345.0f, -40.0f);
                    Hu3DModelRotSet(m, 0.0f, 180.0f, 0.0f);
                    w.alpha[0] = 0;
                    w.step[0] = 25;
                    m = obj[2];
                    if (D_8011A938_msetup == 0) {
                        goto scale;
                    }
                    if (D_8011A938_msetup == 1) {
                    scale:
                        func_8000BE5C_main(m, sc, sc);
                    }
                    func_8000BBD4_main(m, 0x107, 0x30);
                    func_8000BB54_main(m);
                    w.kill[0] = 0;
                    w.kill[2] = 0;
                }
                work->state = 0;
                break;
            case 3:
                w.kill[0] = 1;
                w.kill[2] = 1;
                /* fallthrough */
            case 2:
                if (obj[0] >= 0 && obj[2] >= 0) {
                    w.speed[0] = -1.0f / 7.0f;
                    w.alpha[0] = 0xFF;
                    w.step[0] = -36;
                }
                work->state = 0;
                break;
            case 4:
                if (obj[1] >= 0) {
                    w.scale[1] = 0.0f;
                    w.speed[1] = 1.0f / 7.0f;
                    m = obj[1];
                    func_8001C258_main(m, 4, 0);
                    Hu3DModelPosSet(m, 260.0f, 175.0f, -80.0f);
                    Hu3DModelRotSet(m, 0.0f, 180.0f, 0.0f);
                    w.kill[1] = 0;
                }
                work->state = 0;
                break;
            case 6:
                w.kill[1] = 1;
                /* fallthrough */
            case 5:
                if (obj[1] >= 0) {
                    w.speed[1] = -1.0f / 7.0f;
                }
                work->state = 0;
                break;
            case 9:
                for (i = 0; i < 8; i++) {
                    if (obj[i] >= 0) {
                        w.kill[i] = 1;
                    }
                }
                /* fallthrough */
            case 8:
                for (m = 0, i = 0; i < 2; i++, m++) {
                    if (obj[m] >= 0) {
                        w.speed[i] = -1.0f / 7.0f;
                    }
                }
                for (m = 2, i = 0; i < 1; i++, m++) {
                    if (obj[m] >= 0) {
                        w.step[i] = -36;
                    }
                }
                break;
            case 0xFF:
                for (m = 0, i = 0; i < 2; i++, m++) {
                    if (res[m] >= 0) {
                        func_80033430_main(res[m]);
                    }
                    if (obj[m] >= 0) {
                        func_8001ACDC_main(obj[m]);
                    }
                }
                for (m = 2, i = 0; i < 1; i++) {
                    if (obj[m] >= 0) {
                        func_8000C184_main(obj[m]);
                    }
                    if (res[m] >= 0) {
                        HuSprKill(res[m]);
                    }
                }
                for (i = 0; i < 2; i++) {
                    w.speed[i] = 0.0f;
                }
                for (i = 0; i < 1; i++) {
                    w.step[i] = 0;
                }
                work->state = 0;
                break;
            }
            prev = work->state;
        }
        for (i = 0; i < 2; i++) {
            if (w.speed[i] == 0.0f) {
                continue;
            }
            j = i;
            m = obj[j];
            if (m < 0) {
                continue;
            }
            w.scale[i] += w.speed[i];
            if (D_80119B0C_msetup[j] <= w.scale[i]) {
                w.scale[i] = D_80119B0C_msetup[j];
                w.speed[i] = 0.0f;
            } else if (w.scale[i] <= 0.0f) {
                w.scale[i] = 0.0f;
                w.speed[i] = 0.0f;
                func_8001C258_main(m, 4, 4);
                if (w.kill[j] != 0) {
                    if (res[j] >= 0) {
                        func_80033430_main(res[j]);
                        res[j] = -1;
                    }
                    func_8001ACDC_main(m);
                    w.kill[j] = 0;
                    obj[j] = -1;
                    m = -1;
                }
            }
            if (m >= 0) {
                Hu3DModelScaleSet(m, w.scale[i], w.scale[i], w.scale[i]);
            }
        }
        for (i = 0; i < 1; i++) {
            if (w.step[i] == 0) {
                continue;
            }
            j = i + 2;
            m = obj[j];
            if (m < 0) {
                continue;
            }
            w.alpha[i] += w.step[i];
            if (w.alpha[i] >= 0x100) {
                w.alpha[i] = 0xFF;
                w.step[i] = 0;
            } else if (w.alpha[i] < 0) {
                w.alpha[i] = 0;
                w.step[i] = 0;
                func_8000BB94_main(m);
                if (w.kill[j] != 0) {
                    func_8000C184_main(m);
                    if (res[j] >= 0) {
                        HuSprKill(res[j]);
                        res[j] = -1;
                    }
                    w.kill[j] = 0;
                    obj[j] = -1;
                    m = -1;
                }
            }
            if (m >= 0) {
                func_8000BBFC_main(m, w.alpha[i]);
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010EB94_msetup);
#endif

Process *func_8010F2BC_msetup(void) {
    Process *proc = omAddPrcObj(func_8010EB94_msetup, 0x3F00, 0x600, 0);

    proc->user_data = &D_8011A8B0_msetup;
    return proc;
}

// retail sign-extends state at entry and loads the old state with lh (masked 6); same logic
#ifdef NON_MATCHING
s16 func_8010F2F4_msetup(Process *proc, s16 state) {
    MsPreviewWork *work = proc->user_data;

    if (state != 0) {
        work->state = state;
    } else {
        state = work->state;
    }
    return state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F2F4_msetup);
#endif

void func_8010F320_msetup(Process *proc, s16 idx, s16 obj, s16 res) {
    MsPreviewWork *work = proc->user_data;

    work->obj[idx] = obj;
    work->res[idx] = res;
}

void func_8010F33C_msetup(s16 model, Vec *out, f32 (*mtx)[4]) {
    f32 local[4][4];
    f32 world[4][4];
    HmfModel *m;

    m = &HmfModelData[model];
    func_80088800_main(local, m->pos.x, m->pos.y, m->pos.z);
    func_80017D24_main(local, m->rot.x, m->rot.y, m->rot.z);
    func_80017CD0_main(local, m->scale.x, m->scale.y, m->scale.z);
    func_80018044_main(mtx, local, world);
    out->x = world[0][0] + world[1][0] + world[2][0] + world[3][0];
    out->y = world[0][1] + world[1][1] + world[2][1] + world[3][1];
    out->z = world[0][2] + world[1][2] + world[2][2] + world[3][2];
}

// identical code, but retail pads it with a nop to 0x8010F4E0: a TU boundary (506F20.c needs a split there); asm keeps the pad
#ifdef NON_MATCHING
void func_8010F43C_msetup(s16 model, char *name, Vec2f *out) {
    f32 mtx[4][4];
    Vec pos;

    func_80016B00_main(model, HmfModelData[model].unk40, name, &mtx);
    func_8010F33C_msetup(model, &pos, mtx);
    Hu3DCam3DToScreen(0, &pos, out);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F43C_msetup);
#endif

// retail calls Hu3DModelRotSet in both branches (cross-jumped, 0 args set per branch) and keeps lift/from in s0/s1 (masked 10); same logic
#ifdef NON_MATCHING
void func_8010F4E0_msetup(MsLift *lifts, s16 count, s16 set) {
    Vec pos;
    s16 *tbl[4];
    MsLift *lift;
    Vec *from;
    f32 t;
    f32 ry;
    s32 i;
    s32 j;

    if (count == 3) {
        for (i = 0; i < 4; i++) {
            tbl[i] = D_8011A078_msetup[i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            tbl[i] = D_8011A058_msetup[i];
        }
    }
    for (i = 0; i < count; i++) {
        lifts[i].slot = tbl[set][i];
    }
    for (j = 0; j < 15; j++) {
        t = sindf(j * (90.0f / 14.0f));
        for (i = 0; i < count; i++) {
            lift = &lifts[i];
            from = &D_8011A028_msetup[lift->curSlot];
            pos = D_8011A028_msetup[lift->slot];
            pos.x -= from->x;
            pos.y -= from->y;
            pos.z -= from->z;
            pos.x = t * pos.x;
            pos.y = t * pos.y;
            pos.z = t * pos.z;
            pos.x += from->x;
            pos.y += from->y;
            pos.z += from->z;
            Hu3DModelPosSet(lift->model, pos.x, pos.y, pos.z);
            if (lift->slot == 0) {
                ry = sindf(j * (90.0f / 14.0f)) * 180.0f;
            } else {
                lift = &lifts[i];
                if (lift->curSlot != 0) {
                    continue;
                }
                ry = 180.0f - sindf(j * (90.0f / 14.0f)) * 180.0f;
            }
            Hu3DModelRotSet(lift->model, 0.0f, ry, 0.0f);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        lift = &lifts[i];
        from = &D_8011A028_msetup[lift->slot];
        Hu3DModelPosSet(lift->model, from->x, from->y, from->z);
        lift->pos = *from;
        lift->curSlot = lift->slot;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F4E0_msetup);
#endif

/* Register allocation and scheduling only (masked ~93): retail keeps the lift count in s7 and
   spills its copy for the move loop, and reads D_8011AA44/D_8011AA40 through one base register.
   Logic checked block by block against the asm. */
#ifdef NON_MATCHING
/* State: the human player count on up to four Star Lifts (D_8011AA30_msetup.unk14 lifts, at least
   two): work->unk4 is the choice, D_8011A0B8_msetup[choice] the count it stands for; B asks to quit
   (-1). Sets D_8011AA40/41 (humans, COMs) and buzzes the human players' controllers. */
s32 func_8010F87C_msetup(MsSetupWork *work) {
    MsLift lifts[4];
    Vec pos;
    s16 *sets[4];
    s16 prevBtn;
    omObjData *arrows;
    s16 n;
    s16 *set;
    s32 cnt;
    s32 i;
    s16 j;
    s16 sel;
    s32 count;
    u16 model;
    s32 redraw;
    s32 btn;
    s32 humans;
    f32 t;
    f32 rotY;
    MsLift *lift;
    Vec *dst;
    Vec *rot;
    s16 slot;
    s16 m;

    arrows = NULL;
    n = D_8011AA30_msetup.unk14;
    if (work->unk4 < 0) {
        for (sel = 0; sel < 4; sel++) {
            if ((f32)D_8011AA30_msetup.unk10 == D_8011A0B8_msetup[sel]) {
                break;
            }
        }
        work->unk4 = sel = (sel < 4) ? sel : 0;
    } else {
        if (work->unk4 >= 4) {
            work->unk4 = 0;
        }
        sel = work->unk4;
    }
    if ((f32)n < D_8011A0B8_msetup[sel]) {
        for (sel = 0; sel < 4; sel++) {
            if ((f32)n == D_8011A0B8_msetup[sel]) {
                break;
            }
        }
        work->unk4 = sel = (sel < 4) ? sel : 0;
    }
    func_8010B998_msetup();
    count = (u16)n;
    if (count < 2) {
        count = 2;
    }
    for (i = 0; i < count; i++) {
        model = func_8000B108_main(0x140003, 0x2A9);
        lift = &lifts[i];
        lift->model = model;
        lift->unk1A = HmfAnimRead(HmfModelData[(s16)model].hmf, D_8011A098_msetup[i], D_8011A6D8_msetup);
        func_800332D4_main(lift->unk1A, 0.75f);
        func_8001C448_main(model);
        func_8001C514_main(model);
        lift->unk20 = 0;
        rot = &lift->rot;
        lift->rot.x = lift->rot.y = lift->rot.z = 0.0f;
        if (i & 1) {
            lift->rot.y = 180.0f;
        }
        Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
        lift->pos = D_80119B20_msetup;
        Hu3DModelPosSet(model, lift->pos.x, lift->pos.y, lift->pos.z);
        Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
        HuPrcVSleep();
    }
    if (count == 3) {
        for (i = 0; i < 4; i++) {
            sets[i] = D_8011A078_msetup[i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            sets[i] = D_8011A058_msetup[i];
        }
    }
    if (n >= 2) {
        arrows = func_8010DE38_msetup(0x40, 0x100, 0x40);
    }
    func_8010B82C_msetup(0x1503);
    func_8010B858_msetup();
    redraw = 1;
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, count, 15, 720.0f, 565.0f, 0.1f, 1.0f, redraw);
    if (n >= 2) {
        arrows->work[0] = redraw;
        arrows->work[1] = 0x24;
        cnt = count;
        for (j = 0; j < 7; j++) {
            t = j / 7.0f;
            for (i = 0; i < cnt; i++) {
                slot = sets[sel][i];
                lift = &lifts[i];
                dst = &D_8011A028_msetup[slot];
                pos.x = (dst->x - lift->pos.x) * t;
                pos.y = (dst->y - lift->pos.y) * t;
                pos.z = (dst->z - lift->pos.z) * t;
                pos.x += lift->pos.x;
                pos.y += lift->pos.y;
                pos.z += lift->pos.z;
                rotY = (D_8011A0A8_msetup[slot] - lift->rot.y) * t;
                m = lift->model;
                Hu3DModelRotSet(m, lift->rot.x, rotY + lift->rot.y, lift->rot.z);
                Hu3DModelPosSet(m, pos.x, pos.y, pos.z);
            }
            HuPrcVSleep();
        }
        for (i = 0; i < count; i++) {
            slot = sets[sel][i];
            lift = &lifts[i];
            lift->pos = D_8011A028_msetup[slot];
            lift->rot.y = D_8011A0A8_msetup[slot];
            m = lift->model;
            Hu3DModelPosSet(m, lift->pos.x, lift->pos.y, lift->pos.z);
            Hu3DModelRotSet(m, lift->rot.x, lift->rot.y, lift->rot.z);
        }
    } else {
        func_8001C258_main(lifts[1].model, 4, 4);
        rotY = lifts[0].rot.y;
        m = lifts[0].model;
        for (j = 0; j < 7; j++) {
            rotY += 25.714285f;
            if (rotY > 360.0f) {
                rotY -= 360.0f;
            }
            Hu3DModelRotSet(m, 0.0f, rotY, 0.0f);
            HuPrcVSleep();
        }
        lifts[0].rot.y = rotY;
    }
    for (i = 0; i < (s16)count; i++) {
        lifts[i].slot = lifts[i].curSlot = sets[sel][i];
    }
    redraw = 1;
    func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
    while (TRUE) {
        if (redraw) {
            redraw = 0;
            func_8010B82C_msetup(D_80119B34_msetup[work->unk4]);
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                work->unk4 = -1;
                break;
            }
            func_8010B82C_msetup(0x1503);
            redraw = 1;
            func_8010B858_msetup();
            btn = func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        } else if (btn & 0x8000) {
            HuAudFXPlay(2);
            humans = D_8011A0B8_msetup[work->unk4];
            D_8011AA30_msetup.unk10 = humans;
            D_8011AA30_msetup.unk11 = 4 - humans;
            for (i = 0; i < D_8011AA40_msetup; i++) {
                RepeatVibrator(D_8011AA30_msetup.pad[i], 10, 0, 10);
            }
            break;
        }
        if (n >= 2) {
            if (btn & 0x900) {
                if (++work->unk4 >= n) {
                    work->unk4 = 0;
                }
                arrows->work[0] = 4;
            } else if (btn & 0x600) {
                if (--work->unk4 < 0) {
                    work->unk4 = n - 1;
                }
                arrows->work[0] = 3;
            }
        }
        if (sel != work->unk4) {
            HuAudFXPlay(1);
            func_8010F4E0_msetup(lifts, count, work->unk4);
            redraw = 1;
            sel = work->unk4;
        }
        HuPrcVSleep();
    }
    if (n >= 2) {
        arrows->work[0] = 2;
        arrows->work[1] = 0x11;
    } else {
        rotY = lifts[0].rot.y;
        m = lifts[0].model;
        for (j = 0; j < 7; j++) {
            rotY += 25.714285f;
            if (rotY > 360.0f) {
                rotY -= 360.0f;
            }
            Hu3DModelRotSet(m, 0.0f, rotY, 0.0f);
            HuPrcVSleep();
        }
        lifts[0].rot.y = rotY;
        func_8001C258_main(lifts[1].model, 4, 0);
    }
    func_8010B998_msetup();
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, count, 7, 360.0f, 400.0f, 1.0f, 0.1f, 4);
    if (n >= 2) {
        func_8010DDD8_msetup(arrows);
    }
    for (i = 0; i < count; i++) {
        lift = &lifts[i];
        func_80033430_main(lift->unk1A);
        func_8001ACDC_main(lift->model);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F87C_msetup);
#endif

// register allocation and operand order around the D_80119C10 rows (masked 28, 3 fewer instructions: retail re-extends cur for the second row); same logic
#ifdef NON_MATCHING
void func_8011035C_msetup(void) {
    struct {
        s16 spr[8];
        s16 unk10[8];
        s16 chr[8];
        s16 win[2];
    } w;
    MsInfoWork *work;
    s32 i;
    s16 j;
    s16 grp;
    s16 grp2;
    s16 spr;
    s16 cur;
    s16 prev;
    s16 shown;
    s16 win;
    u8 *row;

    grp2 = -1;
    work = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 8; i++) {
        w.spr[i] = w.unk10[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        w.win[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        w.chr[i] = func_8000B838_main(D_80119BA0_msetup[i]);
        if (i & 1) {
            HuPrcVSleep();
        }
    }
    grp = HuSprGrpCreate(8, 0);
    for (j = 0; j < 8; j++) {
        if (j == 7) {
            spr = w.chr[work->sel];
        } else {
            spr = func_8000B838_main(D_80119B44_msetup[j]);
            w.spr[j] = spr;
        }
        func_80055458_main(grp, j, 0x100);
        HuSprAttrReset(grp, j, 0xFFFF);
        HuSprAttrSet(grp, j, 0x9000);
        HuSprScaleSet(grp, j, 1.0f, 1.0f);
        func_800550F4_main(grp, j, 1);
        func_80055024_main(grp, j, spr, 0);
        HuSprPriSet(grp, j, 0x3A98);
        func_80054904_main(grp, j, D_80119B60_msetup[j][0], D_80119B60_msetup[j][1]);
        HuPrcVSleep();
    }
    row = D_80119C10_msetup[work->sel];
    for (i = 0, j = 4; i < 2; i++, j++) {
        func_80054FF8_main(grp, j, row[i]);
    }
    for (i = 0; i < 2; i++) {
        win = func_8005A968_main(D_80119B90_msetup[i][0], D_80119B90_msetup[i][1], D_80119B90_msetup[i][2],
                                 D_80119B90_msetup[i][3], 0, 12);
        w.win[i] = win;
        func_8005BDFC_main(win, 0);
        func_8005BEE0_main(win, 0);
        func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
        func_8005D294_main(win);
        func_8005FE90_main(win);
        HuPrcVSleep();
    }
    shown = 0;
    func_8005F904_main();
    cur = work->sel;
    prev = 0;
    do {
        if (prev != work->state) {
            switch (work->state) {
            case 0:
                break;
            case 1:
                for (i = 0; i < 8; i++) {
                    HuSprAttrReset(grp, i, 0x8000);
                }
                cur = -1;
                func_8005FFA8_main(w.win[0]);
                shown = 1;
                func_8005FFA8_main(w.win[1]);
                break;
            case 2:
                for (i = 0; i < 8; i++) {
                    HuSprAttrSet(grp, i, 0x8000);
                }
                shown = 0;
                func_8005FE90_main(w.win[0]);
                func_8005FE90_main(w.win[1]);
                break;
            }
            prev = work->state;
        }
        if (shown != 0 && cur != work->sel) {
            cur = work->sel;
            func_80055024_main(grp, 7, w.chr[cur], 0);
            row = D_80119C10_msetup[cur];
            for (i = 0, j = 4; i < 3; i++, j++) {
                func_80054FF8_main(grp, j, row[i]);
            }
            func_8005B43C_main(w.win[0], D_80119BD0_msetup[cur], -1, -1);
            func_8005D294_main(w.win[1]);
            func_8005B43C_main(w.win[1], D_80119BF0_msetup[cur], -2, -1);
            cur = work->sel;
        }
        HuPrcVSleep();
    } while (prev != 3);
    for (i = 0; i < 8; i++) {
        if (w.chr[i] >= 0) {
            HuSprKill(w.chr[i]);
        }
    }
    for (i = 0; i < 8; i++) {
        if (w.spr[i] >= 0) {
            HuSprKill(w.spr[i]);
        }
    }
    if (grp >= 0) {
        HuSprGrpKill(grp);
    }
    if (grp2 >= 0) {
        HuSprGrpKill(grp2);
    }
    for (i = 0; i < 2; i++) {
        if (w.win[i] >= 0) {
            func_8005F364_main(w.win[i]);
        }
    }
    work->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8011035C_msetup);
#endif

/* One cursor of the character select board (user_data MsChrWork, owner func_80111650_msetup):
   a player (or, player 4, the COMs) picks work->unk16 of the eight slots; each pick puts a badge
   esprite on the slot. work->state: 1 show, 2 hide, -1 kill. work->result: 1 done, -1 cancelled. */
void func_80110954_msetup(void) {
    s16 id[4];
    s16 chosen[4];
    s16 spr[4];
    s16 eslot[4];
    u8 used[8];
    s16 prevBtn;
    MsChrWork *work;
    s16 *cur;
    s32 *mess;
    s16 sprId;
    s16 slot;
    s16 prevState;
    s16 shown;
    s16 alpha;
    s16 alphaStep;
    s16 x;
    s16 y;
    s16 x0;
    s16 y0;
    s16 tx;
    s16 ty;
    s16 dx;
    s16 dy;
    s16 ofsX;
    s16 ofsY;
    s16 prevSel;
    s16 time;
    s16 help;
    s16 sel;
    s16 n;
    s32 i;
    s32 btn;
    s16 redraw;
    s16 active;
    s16 next;
    s32 j;
    MsChrSlot *slots;
    f32 s;

    work = HuPrcCurrentGet()->user_data;
    help = 0;
    switch (D_8011A938_msetup) {
    case 0:
    default:
        mess = D_80119CC0_msetup;
        break;
    case 1:
        mess = D_80119CE0_msetup;
        help = 1;
        break;
    case 5:
        mess = D_80119D00_msetup;
        break;
    case 6:
        mess = D_80119D20_msetup;
        break;
    }
    if (work->player < 0) {
        sprId = func_8000B838_main(0x11000E);
        slot = InitEspriteSlot(sprId, 0, 1);
    } else {
        sprId = func_8000B838_main(0x140042);
        /* retail called it unprototyped here (lh of the s16 player, promoted to int) */
        slot = ((s16 (*)())InitEspriteSlot)(sprId, work->player, 1);
    }
    func_8000BCC8_main(slot, 1);
    cur = work->cur;
    ofsX = -((work->player & 1) == 0) | 1;
    ofsY = -((work->player & 2) == 0) | 1;
    if (work->pos != NULL && work->sel >= 0) {
        work->cur[0] = ofsX + work->pos[work->sel][0];
        work->cur[1] = ofsY + work->pos[work->sel][1];
    }
    x = tx = cur[0];
    y = ty = cur[1];
    func_8000BBD4_main(slot, x, ty);
    func_8000BB94_main(slot);
    shown = 0;
    alpha = 0;
    alphaStep = 0;
    prevSel = work->sel;
    time = 0;
    prevState = work->state;
    x0 = x;
    y0 = y;
    dy = 0;
    dx = 0;
    sel = prevSel;
    work->result = 0;
    n = 0;
    active = 0;
    for (i = 0; i < work->unk16; i = j) {
        id[i] = work->player + (j = i + 1);
    }
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        spr[i] = eslot[i] = -1;
    }
    for (i = 0; i < work->unk16; i++) {
        spr[i] = func_8000B838_main(D_80119AD0_msetup[work->player]);
        eslot[i] = InitEspriteSlot(spr[i], 0, 1);
        func_8000BCC8_main(eslot[i], 2);
        func_8000BE5C_main(eslot[i], 0.75f, 0.75f);
        func_8000BBFC_main(eslot[i], 0x100);
        func_8000BB94_main(eslot[i]);
    }
    redraw = 0;
    HuPrcVSleep();
    if (help) {
        D_8011A906_msetup = sel;
    }
    while (TRUE) {
        if (prevState != work->state) {
            switch (work->state) {
            case 0:
                break;
            case 1:
                alphaStep = 0x40;
                if (shown != 0) {
                    break;
                }
                if (work->result == 1) {
                    n--;
                    i = chosen[n];
                    if (id[n] == work->slots[i].owner) {
                        work->slots[i].owner = 0;
                        HuSprAttrSet(work->slots[i].grp, work->slots[i].spr1, 0x8000);
                        HuSprAttrReset(work->slots[i].grp, work->slots[i].spr0, 0x8000);
                        func_8000BB94_main(eslot[n]);
                    }
                }
                work->result = 0;
                alpha = 0;
                func_8000BBFC_main(slot, 0);
                func_8000BB54_main(slot);
                func_8010D684_msetup(work->pad, &prevBtn);
                func_8010D684_msetup(work->pad, &prevBtn);
                shown = 1;
                redraw = 1;
                sel = prevSel;
                active = 1;
                if ((work->slots[sel].owner & 0xFFEF) == 0) {
                    work->slots[sel].owner = 0x10;
                }
                break;
            case 2:
                if (shown == 0) {
                    break;
                }
                alphaStep = -0x40;
                shown = 0;
                active = 0;
                if ((work->slots[sel].owner & 0xFFEF) == 0) {
                    work->slots[sel].owner = 0;
                }
                HuSprAttrSet(work->slots[sel].grp, work->slots[sel].spr1, 0x8000);
                HuSprAttrReset(work->slots[sel].grp, work->slots[sel].spr0, 0x8000);
                break;
            case -1:
                func_8000C184_main(slot);
                HuSprKill(sprId);
                for (i = 0; i < 4; i++) {
                    if (eslot[i] >= 0) {
                        func_8000C184_main(eslot[i]);
                    }
                    if (spr[i] >= 0) {
                        HuSprKill(spr[i]);
                    }
                }
                work->state = 100;
                while (TRUE) {
                    HuPrcVSleep();
                }
            }
            prevState = work->state;
        }
        if (shown != 0) {
            if (redraw != 0) {
                if (work->player == 4) {
                    func_8010B82C_msetup(mess[sel]);
                }
                if (help) {
                    D_8011A906_msetup = sel;
                }
                HuSprAttrSet(work->slots[sel].grp, work->slots[sel].spr0, 0x8000);
                HuSprAttrReset(work->slots[sel].grp, work->slots[sel].spr1, 0x8000);
                redraw = 0;
            }
            btn = func_8010D684_msetup(work->pad, &prevBtn);
            if (btn & 0x4000) {
                HuAudFXPlay(4);
                if (n != 0) {
                    n--;
                    i = chosen[n];
                    if (id[n] == work->slots[i].owner) {
                        work->slots[i].owner = 0;
                        if (i == sel) {
                            work->slots[i].owner = 0x10;
                        } else {
                            HuSprAttrSet(work->slots[i].grp, work->slots[i].spr1, 0x8000);
                            HuSprAttrReset(work->slots[i].grp, work->slots[i].spr0, 0x8000);
                        }
                        func_8000BB94_main(eslot[n]);
                    }
                    work->result = 0;
                    active = 1;
                } else {
                    work->result = -1;
                }
            } else if (active == 0) {
                goto moved;
            } else if (btn & 0x8000) {
                if ((work->slots[sel].owner & 0xFFEF) != 0) {
                    goto pick;
                }
                if (work->player != 4) {
                    func_8004AC5C_main(D_80119CB0_msetup[sel], work->pad);
                    RepeatVibrator(work->pad, 5, 0, 5);
                } else {
                    HuAudFXPlay(D_80119CB0_msetup[sel]);
                }
                work->slots[sel].owner = id[n];
                HuSprAttrSet(work->slots[sel].grp, work->slots[sel].spr0, 0x8000);
                HuSprAttrReset(work->slots[sel].grp, work->slots[sel].spr1, 0x8000);
                chosen[n] = sel;
                func_8000BBD4_main(eslot[n], tx, ty + 13);
                func_8000BB54_main(eslot[n]);
                if (++n >= work->unk16) {
                    work->result = 1;
                    active = 0;
                } else {
                    for (i = sel + 1; i < 8; i++) {
                        if (work->slots[i].owner == 0) {
                            break;
                        }
                    }
                    if (i < 8) {
                        sel = i;
                    } else {
                        for (i = 0; i < sel; i++) {
                            if (work->slots[i].owner == 0) {
                                break;
                            }
                        }
                        sel = i = (i < 8) ? i : 0;
                    }
                    work->sel = sel;
                    work->slots[(s16)i].owner = 0x10;
                    redraw = 1;
                }
            }
        pick:
            if (active != 0 && (btn & 0xF00)) {
                for (i = 0; i < 8; i++) {
                    used[i] = work->slots[i].owner;
                }
                next = func_8010D4DC_msetup(work->pos, used, 8, sel, work->pad, (s16)btn);
                if (next >= 0) {
                    HuAudFXPlay(1);
                    if ((work->slots[sel].owner & 0xFFEF) == 0) {
                        work->slots[sel].owner = 0;
                    }
                    HuSprAttrSet(work->slots[sel].grp, work->slots[sel].spr1, 0x8000);
                    HuSprAttrReset(work->slots[sel].grp, work->slots[sel].spr0, 0x8000);
                    sel = next;
                    work->sel = sel;
                    work->slots[sel].owner = 0x10;
                    redraw = 1;
                }
            }
        }
    moved:
        if (prevSel != work->sel) {
            prevSel = work->sel;
            if (work->pos != NULL) {
                cur[0] = ofsX + work->pos[prevSel][0];
                cur[1] = ofsY + work->pos[prevSel][1];
            }
            sel = prevSel;
        }
        if (tx != cur[0] || ty != cur[1]) {
            tx = cur[0];
            ty = cur[1];
            if ((time = work->unk10) != 0) {
                x0 = x;
                y0 = y;
                dx = tx - x;
                dy = ty - y;
            }
        }
        if (alphaStep != 0) {
            alpha += alphaStep;
            if (alpha >= 0x100) {
                alpha = 0xFF;
                alphaStep = 0;
                work->state = 0;
            } else if (alpha < 0) {
                alpha = 0;
                alphaStep = 0;
                func_8000BB94_main(slot);
                shown = 0;
                work->state = 0;
            }
            func_8000BBFC_main(slot, alpha);
        }
        if ((x != tx) | (y != ty)) {
            if (time == 0) {
                x = tx;
                y = ty;
            } else {
                time--;
                s = sindf((90.0f / work->unk10) * (work->unk10 - time));
                x = x0 + dx * s;
                y = y0 + dy * s;
            }
            func_8000BBD4_main(slot, x, y);
        }
        HuPrcVSleep();
    }
}

extern s32 D_80119C70_msetup[];  /* sprite files per character slot (8; 8 pointers follow) */
extern char *D_80119D68_msetup[8]; /* model part names of the 8 character slots */
extern s32 D_80119DA8_msetup[4]; /* party: messages (players, then by COM count) */
extern s32 D_80119DB8_msetup[4]; /* mini-game mode: same */
extern MsLiftKey D_80119C28_msetup[2];
extern MsLiftKey D_80119C48_msetup[2];

/* Character select lift (state of func_80117820_msetup): the board's eight character slots, one
   func_80110954_msetup cursor process per human player (then one for the COMs); writes the chosen
   characters to D_8011AA30_msetup.chr and .com; work->unk4 = -1 on cancel. */
#ifdef NON_MATCHING
s32 func_80111650_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    MsChrSlot slots[8];
    MsChrWork works[4];
    Process *procs[4];
    s16 sprites[16];
    Vec2f vec;
    s16 pos[8][2];
    s32 files[2];
    s8 sel[4];
    s16 model;
    s32 *mess;
    s16 grp;
    u16 nCom;
    s16 nHuman;
    s16 back;
    s16 esp;
    s16 espFile;
    s32 nProc;
    s32 i;
    s32 j;
    s32 k;
    s16 si;
    s16 sj;
    s16 lock;
    s16 alpha;
    s16 step;
    s16 cnt;
    s16 ok;
    s16 owner;
    MsChrWork *w;
    MsChrSlot *slot;

    func_8010B998_msetup();
    work->unk4 = 0;
    D_8011A900_msetup = NULL;
    espFile = -1;
    esp = -1;
    switch (D_8011A938_msetup) {
        case 0:
        default:
            mess = D_80119DA8_msetup;
            break;
        case 1:
            mess = D_80119DB8_msetup;
            D_8011A904_msetup.state = 0;
            D_8011A904_msetup.unk2 = 0;
            D_8011A900_msetup = omAddPrcObj(func_8011035C_msetup, 0x3F00, 0x600, 0);
            D_8011A900_msetup->user_data = &D_8011A904_msetup;
            break;
    }
    func_8010E4BC_msetup(lifts, 2, 90.0f);
    func_8010E4D8_msetup(lifts, 2);
    model = func_8000B108_main(0x140007, 0x289);
    func_8001C448_main(model);
    func_8001C258_main(model, 4, 4);
    Hu3DModelScaleSet(model, 1.2f, 1.2f, 1.2f);
    Hu3DModelPosSet(model, 0.0f, 300.0f, -280.0f);
    func_8001C814_main(model, 1, 1);
    grp = HuSprGrpCreate(0x10, 0);
    for (i = 0; i < 8; i++) {
        func_8010F43C_msetup(model, D_80119D68_msetup[i], &vec);
        files[0] = D_80119D88_msetup[i];
        files[1] = D_80119C70_msetup[i];
        lock = 0;
        if (i == 3) {
            lock = _CheckFlag(0x2E) ? 0 : -1;
        } else if (i == 7) {
            if (_CheckFlag(0x2F) == 0) {
                lock = -1;
            }
        }
        if (lock == -1) {
            files[1] = files[0] = 0x14001C;
        }
        slots[i].grp = grp;
        slots[i].spr0 = i;
        slots[i].spr1 = i + 8;
        slots[i].owner = lock;
        pos[i][0] = vec.x + 6.0f;
        pos[i][1] = vec.y - 2.0f;
        for (j = 0, k = i; j < 2; j++, k += 8) {
            s16 spr = func_8000B838_main(files[j]);

            sprites[k] = spr;
            func_80055458_main(grp, k, 0x100);
            HuSprAttrReset(grp, k, 0xFFFF);
            HuSprAttrSet(grp, k, 0x9000);
            HuSprScaleSet(grp, k, 1.0f, 1.0f);
            func_800550F4_main(grp, k, 0);
            func_80055024_main(grp, k, spr, 0);
            HuSprPriSet(grp, k, 0x258);
            func_80054904_main(grp, k, vec.x, vec.y);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        procs[i] = NULL;
        sel[i] = -1;
    }
    nHuman = D_8011AA30_msetup.unk10;
    nCom = D_8011AA30_msetup.unk11;
    if (nCom != 0) {
        nProc = nHuman + 1;
    } else {
        nProc = nHuman;
    }
    for (i = 0; i < nHuman; i++) {
        if (slots[i].owner == 0) {
            sel[i] = i;
        } else {
            for (sj = i + 1; sj < 8; sj++) {
                if (slots[sj].owner == 0) {
                    break;
                }
            }
            if (sj >= 8) {
                sj = i;
            }
            sel[i] = sj;
        }
    }
    for (i = 0; i < nProc; i++) {
        procs[i] = omAddPrcObj(func_80110954_msetup, 0x3F00, 0x800, 0);
        w = &works[i];
        procs[i]->user_data = w;
        w->slots = slots;
        w->pos = pos;
        w->state = 0;
        if (i < nHuman) {
            w->player = i;
            w->pad = D_8011AA30_msetup.pad[i];
            w->sel = sel[i];
            w->unk10 = 4;
            w->unk16 = 1;
        } else {
            w->player = 4;
            w->pad = D_8011A948_msetup;
            w->sel = 0;
            w->unk10 = 0;
            w->unk16 = nCom;
        }
        w->result = 0;
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    Hu3DModelPosSet(model, 0.0f, 300.0f, -280.0f);
    func_8001C258_main(model, 4, 0);
    func_8010E52C_msetup(lifts, D_80119C28_msetup, 2, 7, &model, 1, 0.1f, 1.2f);
    for (i = 0; i < 8; i++) {
        HuSprAttrReset(grp, i, 0x8000);
    }
    for (alpha = 0; alpha < 0x100; alpha += 0x24) {
        for (i = 0; i < 8; i++) {
            func_80055458_main(grp, i, alpha);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        func_80055458_main(grp, i, 0x100);
    }
    switch (D_8011A938_msetup) {
        case 0:
        default:
            back = 0;
            step = 0;
            break;
        case 1:
            back = 2;
            step = 2;
            D_8011A904_msetup.unk2 = 0;
            D_8011A904_msetup.state = 1;
            break;
        case 6:
            back = 3;
            step = 3;
            for (sj = 0; sj < 8; sj++) {
                if (D_80119C68_msetup[sj] == D_8011AA34_msetup[0]) {
                    break;
                }
            }
            si = (sj < 8) ? sj : 0;
            slot = &slots[si];
            slot->owner = 1;
            espFile = func_8000B838_main(D_80119AD0_msetup[0]);
            esp = InitEspriteSlot(espFile, 0, 1);
            func_8000BCC8_main(esp, 2);
            func_8000BE5C_main(esp, 0.75f, 0.75f);
            func_8000BBFC_main(esp, 0x100);
            func_8000BBD4_main(esp, pos[si][0], pos[si][1] + 12);
            HuSprAttrSet(grp, slot->spr0, 0x8000);
            HuSprAttrReset(grp, slot->spr1, 0x8000);
            break;
    }
    do {
        switch (step) {
            case 0:
                func_8010B82C_msetup(mess[0]);
                func_8010B858_msetup();
                for (i = 0; i < nHuman; i++) {
                    works[i].state = 1;
                }
                do {
                    cnt = 0;
                    HuPrcVSleep();
                    ok = 1;
                    for (i = 0; i < nHuman; i++) {
                        if (works[i].result > 0) {
                            cnt++;
                        }
                    }
                    if (works[0].result < 0) {
                        ok = 0;
                    }
                } while (ok && cnt < nHuman);
                for (i = 0; i < nHuman; i++) {
                    works[i].state = 2;
                    owner = works[i].player + 1;
                    for (sj = 0; sj < 8; sj++) {
                        if (owner == slots[sj].owner) {
                            break;
                        }
                    }
                    D_8011AA34_msetup[i] = D_80119C68_msetup[sj];
                    D_8011AA38_msetup[i] = 0xFF;
                }
                step = nCom ? 1 : -1;
                if (!ok) {
                    step = -1;
                    work->unk4 = step;
                }
                break;
            case 1:
                func_8010B82C_msetup(mess[nCom]);
                func_8010B858_msetup();
                w = &works[nHuman];
                for (i = 0; i < 8; i++) {
                    if (slots[i].owner == 0) {
                        break;
                    }
                }
                i = (i < 8) ? i : 0;
                w->unk10 = 0;
                w->sel = i;
                HuPrcVSleep();
                w->unk10 = 4;
                w->state = 1;
                do {
                    HuPrcVSleep();
                } while (w->result == 0);
                w->state = 2;
                if (w->result < 0) {
                    step = back;
                    break;
                }
                for (sj = 0; sj < 8; sj++) {
                    if (w->player < slots[sj].owner) {
                        k = nHuman + (s16)(slots[sj].owner - w->player - 1);
                        if (k < 4) {
                            D_8011AA34_msetup[k] = D_80119C68_msetup[sj];
                            D_8011AA38_msetup[k] = 1;
                        }
                    }
                }
                step = -1;
                break;
            case 2:
                func_8010B82C_msetup(mess[0]);
                func_8010B858_msetup();
                step = nCom ? 1 : -1;
                for (si = 0; si < nHuman; si++) {
                    w = &works[si];
                    owner = w->player + 1;
                    for (i = 0; i < 8; i++) {
                        if (owner == slots[i].owner) {
                            break;
                        }
                    }
                    if (i >= 8) {
                        for (i = 0; i < 8; i++) {
                            if (slots[i].owner == 0) {
                                break;
                            }
                        }
                        i = (i < 8) ? i : 0;
                    }
                    w->unk10 = 0;
                    w->sel = i;
                    HuPrcVSleep();
                    w->unk10 = 4;
                    w->state = 1;
                    do {
                        HuPrcVSleep();
                    } while (w->result == 0);
                    w->state = 2;
                    if (w->result < 0) {
                        if (--si < 0) {
                            step = -1;
                            work->unk4 = step;
                            break;
                        }
                        si--;
                        continue;
                    }
                    owner = works[si].player + 1;
                    for (i = 0; i < 8; i++) {
                        if (owner == slots[i].owner) {
                            break;
                        }
                    }
                    D_8011AA34_msetup[si] = D_80119C68_msetup[i];
                    D_8011AA38_msetup[si] = 0xFF;
                }
                break;
            case 3:
                func_8010B82C_msetup(mess[nCom]);
                func_8010B858_msetup();
                w = &works[nHuman];
                for (i = 0; i < 8; i++) {
                    if (slots[i].owner == 0) {
                        break;
                    }
                }
                i = (i < 8) ? i : 0;
                w->unk10 = 0;
                w->sel = i;
                HuPrcVSleep();
                w->unk10 = 4;
                w->state = 1;
                do {
                    HuPrcVSleep();
                } while (w->result == 0);
                w->state = 2;
                if (w->result < 0) {
                    func_8010B82C_msetup(0x1501);
                    step = 3;
                    if (func_8010B858_msetup() != 0) {
                        break;
                    }
                    work->unk4 = -1;
                } else {
                    for (sj = 0; sj < 8; sj++) {
                        if (w->player < slots[sj].owner) {
                            k = nHuman + (s16)(slots[sj].owner - w->player - 1);
                            if (k < 4) {
                                D_8011AA34_msetup[k] = D_80119C68_msetup[sj];
                                D_8011AA38_msetup[k] = 1;
                            }
                        }
                    }
                }
                func_8000BB94_main(esp);
                step = -1;
                break;
        }
        HuPrcVSleep();
    } while (step >= 0);
    func_8010B998_msetup();
    if (D_8011A900_msetup != NULL) {
        D_8011A904_msetup.state = 2;
    }
    for (i = 0; i < 4; i++) {
        if (procs[i] != NULL) {
            works[i].state = -1;
        }
    }
    for (alpha = 0x100; alpha > 0; alpha -= 0x24) {
        for (i = 0; i < 16; i++) {
            func_80055458_main(grp, i, alpha);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        HuSprAttrSet(grp, i, 0x8000);
    }
    func_8010E52C_msetup(lifts, D_80119C48_msetup, 2, 7, &model, 1, 1.2f, 0.0f);
    if (D_8011A900_msetup != NULL) {
        D_8011A904_msetup.state = 3;
    }
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);
    if (D_8011A900_msetup != NULL) {
        omDelPrcObj(D_8011A900_msetup);
    }
    for (i = 0; i < 4; i++) {
        if (procs[i] != NULL) {
            omDelPrcObj(procs[i]);
        }
    }
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    HuSprGrpKill(grp);
    for (i = 0; i < 16; i++) {
        HuSprKill(sprites[i]);
    }
    func_8001ACDC_main(model);
    if (esp >= 0) {
        func_8000C184_main(esp);
    }
    if (espFile >= 0) {
        HuSprKill(espFile);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80111650_msetup);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6E4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6FC_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A708_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A714_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A720_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A72C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A738_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A744_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A74C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A754_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A75C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A764_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A76C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A774_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A77C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A784_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A78C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A794_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A79C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7A4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7AC_msetup);

extern s32 D_80119E38_msetup[6];
extern char *D_80119E20_msetup[6]; /* part names (fork F: were s32) */

/* Process of func_801132C4_msetup's board (user_data its MsSetupWork: state = command, unk2 =
   board model, unk4 = COM level count): two sprite panels (sprites D_80119E50..E54_msetup[i]
   placed on the board's points) fade in (1, 3), out (2, 4), swap (5), all out (6); 7 ends. */
void func_80112804_msetup(void) {
    s16 spr[6];
    Vec2f pos;
    s16 alpha[2];
    s16 speed[2];
    s16 active[2];
    s16 delay[2];
    MsSetupWork *board;
    s16 model;
    s16 grp;
    s16 last;
    s16 first; /* n: sprite id, panel index, then the panel's old alpha (one variable in retail) */
    s16 end;
    s32 j;
    s16 n;
    s32 i;

    i = 0;
    board = HuPrcCurrentGet()->user_data;
    model = board->unk2;
    grp = HuSprGrpCreate(6, 0);
    for (; i < 6; i++) {
        n = func_8000B838_main(D_80119E38_msetup[i]);
        spr[i] = n;
        func_80055458_main(grp, i, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x9000);
        HuSprScaleSet(grp, i, 1.0f, 1.0f);
        func_800550F4_main(grp, i, 0);
        func_80055024_main(grp, i, n, 0);
        HuSprPriSet(grp, i, 0x258);
    }
    for (i = 0; i < 2; i++) {
        alpha[i] = 0;
        speed[i] = 0;
        active[i] = 0;
        delay[i] = 0;
    }
    last = 0;
    do {
        if (last != board->state) {
            switch (board->state) {
                case 0:
                    break;
                case 1:
                    n = 0;
                    goto show;
                case 3:
                    n = 1;
                show:
                    if (active[n] == 0) {
                        alpha[n] = 0;
                        speed[n] = 36;
                        active[n] = 1;
                        delay[n] = 3;
                    }
                    board->state = 0;
                    break;
                case 2:
                    n = 0;
                    goto hide;
                case 4:
                    n = 1;
                hide:
                    if (active[n] != 0) {
                        alpha[n] = 0x100;
                        speed[n] = -36;
                        delay[n] = 0;
                    }
                    board->state = 0;
                    break;
                case 5:
                    n = 0;
                    j = 0;
                    if (active[0] != 0 && active[1] == 0) {
                        j = 1;
                    } else if (active[1] != 0 && active[0] == 0) {
                        n = 1;
                        j = 0;
                    }
                    if (n != 0 || j != 0) {
                        alpha[n] = 0x100;
                        speed[n] = -85;
                        delay[n] = 0;
                        alpha[j] = 0;
                        speed[j] = 85;
                        active[j] = 1;
                        delay[j] = 4;
                    }
                    board->state = 0;
                    break;
                case 6:
                    for (n = 0; n < 2; n++) {
                        if (active[n] != 0) {
                            alpha[n] = 0x100;
                            speed[n] = -36;
                            delay[n] = 0;
                        }
                    }
                    board->state = 0;
                    break;
                case 7:
                    board->state = -1;
                    break;
            }
            last = board->state;
        }
        for (j = 0; j < 2; j++) {
            if (active[j] == 0) {
                continue;
            }
            if (delay[j] != 0) {
                delay[j]--;
                continue;
            }
            first = D_80119E50_msetup[j];
            end = D_80119E54_msetup[j];
            if (j == 1 && board->unk4 == 3) {
                end--;
            }
            for (i = first; i <= end; i++) {
                func_8010F43C_msetup(model, D_80119E20_msetup[i], &pos);
                func_80054904_main(grp, i, pos.x, pos.y);
            }
            if (speed[j] != 0) {
                n = alpha[j];
                alpha[j] = n + speed[j];
                if (alpha[j] <= 0) {
                    alpha[j] = 0;
                    speed[j] = 0;
                    active[j] = 0;
                    for (i = first; i <= end; i++) {
                        HuSprAttrSet(grp, i, 0x8000);
                    }
                } else if (alpha[j] >= 0x100) {
                    alpha[j] = 0x100;
                    speed[j] = 0;
                } else if (n == 0) {
                    for (i = first; i <= end; i++) {
                        HuSprAttrReset(grp, i, 0x8000);
                    }
                }
                for (i = first; i <= end; i++) {
                    func_80055458_main(grp, i, alpha[j]);
                }
            }
        }
        HuPrcVSleep();
    } while (last >= 0);
    HuSprGrpKill(grp);
    for (i = 0; i < 6; i++) {
        if (spr[i] >= 0) {
            HuSprKill(spr[i]);
        }
    }
    board->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}

extern s32 D_80119E18_msetup[2];

/* Two-way choice on a func_8010D6D0_msetup cursor: left/up = 0, right/down = 1; A keeps it,
   B returns -1. */
s16 func_80112E08_msetup(s16 sel, s16 *pad, MsCursorWork *cursor) {
    s16 prev;
    s32 btn;

    func_8010B82C_msetup(0x1514);
    prev = -1;
    func_8010B858_msetup();
    cursor->sel = sel;
    HuPrcVSleep();
    cursor->steps = 4;
    cursor->state = 1;
    func_8010D684_msetup(D_8011A948_msetup, pad);
    while (1) {
        if (prev != sel) {
            prev = sel;
            func_8010B82C_msetup(D_80119E18_msetup[sel]);
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, pad);
        if (btn & (U_JPAD | R_JPAD)) {
            sel = 0;
        } else if (btn & (D_JPAD | L_JPAD)) {
            sel = 1;
        }
        if (sel != cursor->sel) {
            HuAudFXPlay(1);
            cursor->sel = sel;
        }
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        HuPrcVSleep();
    }
    cursor->state = 2;
    return sel;
}

/* COM difficulty: `individual` != 0 sets each COM player (D_8011AA30_msetup.unk10 on) in turn, else all
   at once; `count` levels. Returns the level chosen, -1 on cancel. */
s16 func_80112F5C_msetup(s16 individual, s16 count, s16 *pad, MsCursorWork *cursor) {
    s16 players[4];
    s16 idx;
    s16 n;
    s16 p;
    s16 prev;
    s16 sel;
    s16 coms;
    s32 btn;
    s32 i;

    p = D_8011AA30_msetup.unk10;
    coms = D_8011AA30_msetup.unk11;
    for (n = 0; p < 4; n++, p++) {
        players[n] = p;
    }
    n = 0;
    prev = -1;
    cursor->steps = 0;
    sel = D_8011AA30_msetup.com[players[0]];
    cursor->sel = sel;
    HuPrcVSleep();
    HuPrcVSleep();
    cursor->steps = 4;
    cursor->state = 1;
    func_8010D684_msetup(D_8011A948_msetup, pad);
while (1) {
        if (prev != n) {
            s32 mess;

            if (individual != 0) {
                func_8010B968_msetup(D_8011AA30_msetup.chr[players[n]] + 0x1C00, 0);
                mess = 0x1518;
            } else {
                mess = 0x1517;
            }
            prev = n;
            func_8010B82C_msetup(mess);
            sel = D_8011AA30_msetup.com[players[n]];
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, pad);
        if (btn & (U_JPAD | R_JPAD)) {
            sel++;
            if (sel >= count) {
                sel = count - 1;
            }
        } else if (btn & (D_JPAD | L_JPAD)) {
            sel--;
            if (sel < 0) {
                sel = 0;
            }
        }
        if (sel != cursor->sel) {
            HuAudFXPlay(1);
            cursor->sel = sel;
        }
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            if (individual == 0 || --n < 0) {
                sel = -1;
                break;
            }
            idx = players[n];
            D_8011A9E0_msetup[idx].state = 6;
        }
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            if (individual != 0) {
                idx = players[n];
                D_8011AA38_msetup[idx] = sel;
                D_8011A9E0_msetup[idx].state = 5;
                if (++n >= coms) {
                    break;
                }
            } else {
                for (i = 0; i < coms; i++) {
                    idx = players[i];
                    D_8011AA38_msetup[idx] = sel;
                    D_8011A9E0_msetup[idx].state = 5;
                }
                break;
            }
        }
        HuPrcVSleep();
    }
    cursor->state = 2;
    return sel;
}


extern s16 (*D_80119E0C_msetup[3])[2];
extern s16 D_80119DFC_msetup[4][2];
extern s32 D_80119B2C_msetup[2];
extern MsLiftKey D_80119DC8_msetup[2];
extern MsLiftKey D_80119C48_msetup[2];

/* COM setup lift: a board with two cursors, first how COM levels are set (individual/all,
   func_80112E08_msetup), then the level (func_80112F5C_msetup); work->unk4 = -1 on cancel. */
s32 func_801132C4_msetup(MsSetupWork *work) {
    Process *cursorProcs[2];
    MsCursorWork cursors[2];
    MsSetupWork board;
    MsLift lifts[2];
    s16 model;
    s16 pad;
    Process *boardProc;
    s32 i;
    s16 levels;
    s16 step;
    s16 sel;
    s16 ret;
    f32 rot;
    MsCursorWork *cursor;

    work->unk4 = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 90.0f);
    func_8010E4D8_msetup(lifts, 2);
    model = func_8000B108_main(0x140007, 0x289);
    func_8001C448_main(model);
    func_8001C258_main(model, 4, 4);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(model, 0.0f, -300.0f, -280.0f);
    func_8001C814_main(model, 1, 1);
    if (_CheckFlag(0x2D) != 0) {
        func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
        levels = 4;
    } else {
        func_8001C6A8_main(model, 0.0f);
        levels = 3;
    }
    if (D_8011AA30_msetup.unk11 == 1) {
        Hu3DModelRotSet(model, 180.0f, 0.0f, 0.0f);
    }
    board.state = 0;
    board.unk2 = model;
    board.unk4 = levels;
    boardProc = omAddPrcObj(func_80112804_msetup, 0x3F00, 0x800, 0);
    boardProc->user_data = &board;
    for (i = 0; i < 2; i++) {
        cursorProcs[i] = omAddPrcObj(func_8010D6D0_msetup, 0x3F00, 0x800, 0);
        cursor = &cursors[i];
        cursorProcs[i]->user_data = cursor;
        cursor->x = 0xA0;
        cursor->y = 0x78;
        if (i == 1 && levels == 4) {
            cursor->pos = D_80119DFC_msetup;
        } else {
            cursor->pos = D_80119E0C_msetup[i];
        }
        cursor->file = D_80119B2C_msetup[1 - i];
        cursor->sel = -1;
        cursor->state = 0;
        cursor->steps = 0;
        cursor->attr = 0;
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    Hu3DModelPosSet(model, 0.0f, 300.0f, -280.0f);
    D_8011A990_msetup = 1;
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    func_8001C258_main(model, 4, 0);
    if (D_8011AA30_msetup.unk11 == 1) {
        board.state = 3;
    } else {
        board.state = 1;
    }
    func_8010E52C_msetup(lifts, D_80119DC8_msetup, 2, 7, &model, 1, 0.1f, 1.2f);
    step = 1;
    if (D_8011AA30_msetup.unk11 == 1) {
        step = 2;
    }
    sel = 0;
    do {
        switch (step) {
            case 1:
                ret = func_80112E08_msetup(sel, &pad, &cursors[0]);
                if (ret < 0) {
                    work->unk4 = -1;
                    step = -1;
                    break;
                }
                sel = ret;
                step++;
                rot = 0.0f;
                board.state = 5;
                for (i = 0; i < 7; i++) {
                    rot += 180.0f / 7.0f;
                    Hu3DModelRotSet(model, rot, 0.0f, 0.0f);
                    HuPrcVSleep();
                }
                break;
            case 2:
                if (func_80112F5C_msetup(sel, levels, &pad, &cursors[1]) < 0) {
                    if (D_8011AA30_msetup.unk11 == 1) {
                        work->unk4 = -1;
                        step = -1;
                        break;
                    }
                    step = 1;
                    rot = 180.0f;
                    board.state = 5;
                    for (i = 0; i < 7; i++) {
                        rot -= 180.0f / 7.0f;
                        Hu3DModelRotSet(model, rot, 0.0f, 0.0f);
                        HuPrcVSleep();
                    }
                    break;
                }
                step = -1;
                break;
        }
        HuPrcVSleep();
    } while (step > 0);
    board.state = 6;
    func_8010E52C_msetup(lifts, D_80119C48_msetup, 2, 7, &model, 1, 1.1f, 0.0f);
    cursors[0].state = -1;
    cursors[1].state = -1;
    board.state = 7;
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);
    omDelPrcObj(boardProc);
    omDelPrcObj(cursorProcs[0]);
    omDelPrcObj(cursorProcs[1]);
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    func_8001ACDC_main(model);
    return 0;
}

extern s32 D_80119E58_msetup[3];
extern s32 D_80119E64_msetup[3];
extern s32 D_80119E70_msetup[3];
extern s32 D_80119E7C_msetup[3];
extern s32 D_80119E88_msetup[3];

extern char D_8011A6D8_msetup[]; /* "03tex_DEF" (INCLUDE_RODATA; asm users remain) */
s16 HmfAnimRead(HmfData *arg0, s32 arg1, char *arg2);
void func_80032FC0_main(s16 arg0, u8 arg1, u8 arg2);

/* Two-choice lift: the lift spins in showing texture choice `sel` of motion arg1, left/right
   flips between the two, A keeps it (work->unk4 = choice), B cancels (-1). */
s32 func_801138F8_msetup(MsSetupWork *work, s32 arg1, s32 *mess, s16 sel) {
    MsLift lifts[2];
    s16 sp68;
    s16 model;
    s16 anim;
    s16 prev;
    s16 dir;
    omObjData *arrows;
    s32 btn;
    s32 i;
    f32 rot;
    f32 step;

    work->unk4 = sel;
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 0.0f);
    model = lifts[0].model;
    anim = HmfAnimRead(HmfModelData[model].hmf, arg1, D_8011A6D8_msetup);
    func_8001C448_main(model);
    func_80032FC0_main(anim, 1, 1);
    func_8010E4D8_msetup(lifts, 2);
    func_80032FF8_main(anim, sel);
    arrows = func_8010DE38_msetup(0x60, 0xE0, 0x48);
    if (mess != NULL) {
        func_8010B82C_msetup(*mess);
        func_8010B858_msetup();
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.52f, 1);
    arrows->work[0] = 1;
    arrows->work[1] = 36;
    func_8001C258_main(lifts[1].model, 4, 4);
    for (rot = 0.0f; rot < 180.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 180.0f, 0.0f);
    prev = -1;
    func_8010D684_msetup(D_8011A948_msetup, &sp68);
    while (1) {
        if (mess != NULL) {
            if (prev != sel) {
                prev = sel;
                func_8010B82C_msetup(mess[sel + 1]);
            }
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, &sp68);
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
        dir = 0;
        if (btn & (U_JPAD | R_JPAD)) {
            dir = 1;
        } else if (btn & (D_JPAD | L_JPAD)) {
            dir = -1;
        }
        if (dir != 0) {
            HuAudFXPlay(1);
            sel ^= 1;
            if (dir > 0) {
                arrows->work[0] = 4;
                step = 45.0f;
            } else {
                arrows->work[0] = 3;
                step = -45.0f;
            }
            i = 4;
            rot = 180.0f;
            do {
                rot += step;
                Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
                i--;
                HuPrcVSleep();
            } while (i != 0);
            func_80032FF8_main(anim, sel);
            i = 4;
            rot = 0.0f;
            do {
                rot += step;
                Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
                i--;
                HuPrcVSleep();
            } while (i != 0);
        }
        HuPrcVSleep();
    }
    work->unk4 = sel;
    arrows->work[0] = 2;
    arrows->work[1] = 17;
    for (rot = 180.0f; rot < 360.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C258_main(lifts[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.52f, 0.1f, 1);
    func_8010DDD8_msetup(arrows);
    if (anim >= 0) {
        func_80033430_main(anim);
    }
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    return 0;
}

s16 func_80113DEC_msetup(MsSetupWork *work) {
    return func_801138F8_msetup(work, 0x140021, D_80119E58_msetup, 1);
}

s16 func_80113E20_msetup(MsSetupWork *work) {
    return func_801138F8_msetup(work, 0x140022, D_80119E64_msetup, 0);
}

s16 func_80113E54_msetup(MsSetupWork *work) {
    return func_801138F8_msetup(work, 0x140021, D_80119E70_msetup, 1);
}

s16 func_80113E88_msetup(MsSetupWork *work) {
    s32 *mess = D_80119E88_msetup;

    if (D_8011A938_msetup == 1) {
        mess = D_80119E7C_msetup;
    }
    return func_801138F8_msetup(work, 0x140050, mess, 0);
}

s32 func_80113ED4_msetup(MsSetupWork *arg0) {
#define MODE_PARTY 0
#define MODE_DUEL 1
#define FLAG_WALUIGIS_ISLAND 0x31
#define FLAG_BACKTRACK 0x30
    MsLift sp20[2];
    s16 unk_68;
    s32 *mainFSArray;
    s32 boardCountMaxCopy;
    f32 var_f20;
    void *temp_v0_4;
    omObjData *temp_s5;
    s16 prevBoardIndex;
    s16 backgroundEspriteSlot;
    s16 var_s6;
    s32 pad;
    s32 var_fp;
    s32 boardCountMax;
    s32 *boardDescriptionId;
    s16 curBoardIndex;
    s16 temp;
    s32 i;
    f32 tempFloat;

    boardDescriptionId = NULL;
    mainFSArray = NULL;
    curBoardIndex = D_8011AA30_msetup.board;
    arg0->unk4 = 0;
    backgroundEspriteSlot = -1;
    var_s6 = -1;
    boardCountMax = 6;
    var_fp = 70;
    tempFloat = 1.0f;

    switch (D_8011A938_msetup) { // current mode
        case MODE_PARTY:
            boardDescriptionId = D_80119EC4_msetup;
            mainFSArray = D_80119E94_msetup; // party mode board backgrounds
            tempFloat = 1.0f;
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_WALUIGIS_ISLAND) != 0) {
                boardCountMax = 6;
            }
            break;
        case MODE_DUEL:
            boardDescriptionId = D_80119EE0_msetup;
            mainFSArray = D_80119EAC_msetup; // duel mode board backgrounds
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_BACKTRACK) != 0) {
                boardCountMax = 6;
            }
            break;
    }

    func_8010B998_msetup();
    func_8010E4BC_msetup(sp20, 2, 0.0f);
    func_8010E4D8_msetup(sp20, 2);
    temp = sp20[0].model;
    temp_s5 = func_8010DE38_msetup(0x40, 0x100, 0x48);
    func_8010B82C_msetup(boardDescriptionId[6]);
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(sp20, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(sp20[1].model, 4, 4);

    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 180.0f, 0);
    temp_s5->work[0] = 1;
    temp_s5->work[1] = 36;

    for (var_f20 = 1.0f; var_f20 < 2.5f; var_f20 += (3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 2.5f, 2.5f, 2.5f);
    prevBoardIndex = -1;
    pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
    boardCountMaxCopy = boardCountMax;
    while (1) {
        pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
        if (pad & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (pad & B_BUTTON) {
            HuAudFXPlay(4);
            curBoardIndex = -1;
            break;
        }
        if (pad & (U_JPAD | R_JPAD)) {
            curBoardIndex++;
            curBoardIndex = (boardCountMaxCopy <= curBoardIndex) ? 0 : curBoardIndex;
            HuAudFXPlay(1);
            temp_s5->work[0] = 4;
        } else {
            if (pad & (D_JPAD | L_JPAD)) {
                if (--curBoardIndex < 0) {
                    curBoardIndex = boardCountMax - 1;
                }
                HuAudFXPlay(1);
                temp_s5->work[0] = 3;
            }
        }
        // check if background image should update
        if (prevBoardIndex != curBoardIndex) {
            if (backgroundEspriteSlot >= 0) {
                for (i = 255; i > 0; i -= (255 / 5)) {
                    func_8000BBFC_main(backgroundEspriteSlot, i);
                    HuPrcVSleep();
                }
                func_8000C184_main(backgroundEspriteSlot);
                HuSprKill(var_s6);
            }
            temp_v0_4 = DataReadTemp(mainFSArray[curBoardIndex]);
            var_s6 = func_80055810_main(temp_v0_4);
            DataCloseTemp(temp_v0_4);
            backgroundEspriteSlot = InitEspriteSlot(var_s6, 0, 1);
            func_8000BC48_main(backgroundEspriteSlot, 0x1000);
            func_8000BCC8_main(backgroundEspriteSlot, 1);
            func_8000BBD4_main(backgroundEspriteSlot, 0xA0, var_fp);
            func_8000BE5C_main(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                func_8000BBFC_main(backgroundEspriteSlot, i);
                HuPrcVSleep();
            }
            func_8000BBFC_main(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_msetup(boardDescriptionId[curBoardIndex]);
        }
        HuPrcVSleep();
    }

    arg0->unk4 = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA30_msetup.board = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;

    for (i = 255; i > 0; i -= (255 / 5)) {
        func_8000BBFC_main(backgroundEspriteSlot, i);
        HuPrcVSleep();
    }

    func_8000BBFC_main(backgroundEspriteSlot, 0);

    for (var_f20 = 2.5f; var_f20 > 1.0f; var_f20 += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 1.0f, 1.0f, 1.0f);

    for (var_f20 = 180.0f; var_f20 < 360.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 0.0f, 0);
    func_8001C258_main(sp20[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(sp20, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);

    if (curBoardIndex >= 0) {
        func_8010F320_msetup(D_80119420_msetup, 0, sp20[0].model, -1);
        func_8010F320_msetup(D_80119420_msetup, 2, backgroundEspriteSlot, var_s6);
        func_8001ACDC_main(sp20[1].model);
    } else {
        for (i = 0; i < 2; i++) {
            func_8001ACDC_main(sp20[i].model);
        }
        func_8000C184_main(backgroundEspriteSlot);
        HuSprKill(var_s6);
    }
    func_8010DDD8_msetup(temp_s5);
    return 0;
}

extern s32 D_80119EFC_msetup[];
extern s32 D_80119F14_msetup[];

/* Board description lift (modes 2 and 3): shows the chosen board's (D_8011AA45_msetup) picture
   and description, then closes. */
s32 func_801145D0_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    s32 *mess;
    s32 *files;
    s16 board;
    s32 y;
    f32 scale;
    s16 model;
    void *data;
    s16 sprite;
    s16 slot;
    s32 i;
    f32 rot;

    mess = NULL;
    files = NULL;
    board = D_8011AA30_msetup.board;
    work->unk4 = 0;
    y = 70;
    scale = 1.0f;
    switch (D_8011A938_msetup) {
        case 2:
            mess = D_80119EFC_msetup;
            files = D_80119E94_msetup;
            scale = 1.0f;
            y = 74;
            break;
        case 3:
            mess = D_80119F14_msetup;
            files = D_80119EAC_msetup;
            scale = 1.0f;
            y = 74;
            break;
    }
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 0.0f);
    func_8010E4D8_msetup(lifts, 2);
    model = lifts[0].model;
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(lifts[1].model, 4, 4);
    for (rot = 0.0f; rot < 180.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0, rot, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 180.0f, 0);
    for (rot = 1.0f; rot < 2.5f; rot += (3.0f / 14.0f)) {
        Hu3DModelScaleSet(model, rot, rot, rot);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(model, 2.5f, 2.5f, 2.5f);
    data = DataReadTemp(files[board]);
    sprite = func_80055810_main(data);
    DataCloseTemp(data);
    slot = InitEspriteSlot(sprite, 0, 1);
    func_8000BC48_main(slot, 0x1000);
    func_8000BCC8_main(slot, 1);
    func_8000BBD4_main(slot, 0xA0, y);
    func_8000BE5C_main(slot, scale, scale);
    for (i = 0; i < 255; i += (255 / 7)) {
        func_8000BBFC_main(slot, i);
        HuPrcVSleep();
    }
    func_8000BBFC_main(slot, 0xFF);
    func_8010B82C_msetup(mess[board]);
    func_8010B858_msetup();
    for (i = 255; i > 0; i -= (255 / 7)) {
        func_8000BBFC_main(slot, i);
        HuPrcVSleep();
    }
    for (rot = 2.5f; rot > 1.0f; rot += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(model, rot, rot, rot);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
    for (rot = 180.0f; rot < 360.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0, rot, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 0.0f, 0);
    func_8001C258_main(lifts[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    func_8000C184_main(slot);
    HuSprKill(sprite);
    return 0;
}

/* Per-player 0-9 setting lift (D_8011AA30_msetup.star[4], shown as texture `val` of motion 0x140023):
   left/right change it, A stores it and moves to the next player, B goes back. */
s32 func_80114AA0_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    s16 sp68;
    s16 anim;
    s16 model;
    s16 val;
    s16 n;
    s16 shown;
    s16 prev;
    s16 dir;
    omObjData *arrows;
    s32 btn;
    s32 i;
    f32 rot;
    f32 step;

    work->unk4 = 0;
    val = D_8011AA30_msetup.star[0];
    n = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 0.0f);
    model = lifts[0].model;
    anim = HmfAnimRead(HmfModelData[model].hmf, 0x140023, D_8011A6D8_msetup);
    func_8001C448_main(model);
    func_80032FC0_main(anim, 1, 1);
    func_8010E4D8_msetup(lifts, 2);
    func_80032FF8_main(anim, val);
    arrows = func_8010DE38_msetup(0x60, 0xE0, 0x48);
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.4f, 1);
    arrows->work[0] = 1;
    arrows->work[1] = 36;
    func_8001C258_main(lifts[1].model, 4, 4);
    for (rot = 0.0f; rot < 180.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 180.0f, 0.0f);
    shown = val;
    prev = -1;
    func_8010D684_msetup(D_8011A948_msetup, &sp68);
    while (1) {
        if (prev != n) {
            func_8010B968_msetup(D_8011AA30_msetup.chr[n] + 0x1C00, 0);
            func_8010B82C_msetup(0x151C);
            prev = n;
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, &sp68);
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            D_8011AA30_msetup.star[n] = val;
            if (val != 0) {
                D_8011A9E0_msetup[n].state = 8;
            } else {
                D_8011A9E0_msetup[n].state = 10;
            }
            if (++n >= 4) {
                work->unk4 = 0;
                break;
            }
            val = D_8011AA30_msetup.star[n];
        } else if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            if (--n < 0) {
                work->unk4 = -1;
                break;
            }
            D_8011A9E0_msetup[n].state = 9;
            val = D_8011AA30_msetup.star[n];
        }
        dir = 0;
        if (btn & (U_JPAD | R_JPAD)) {
            val++;
            if (val >= 10) {
                val = 0;
            }
            arrows->work[0] = 4;
        } else if (btn & (D_JPAD | L_JPAD)) {
            val--;
            if (val < 0) {
                val = 9;
            }
            arrows->work[0] = 3;
            dir = 1;
        }
        if (shown != val) {
            HuAudFXPlay(1);
            if (dir != 0) {
                step = -45.0f;
            } else {
                step = 45.0f;
            }
            i = 4;
            rot = 180.0f;
            do {
                rot += step;
                Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
                i--;
                HuPrcVSleep();
            } while (i != 0);
            func_80032FF8_main(anim, val);
            i = 4;
            rot = 0.0f;
            do {
                rot += step;
                Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
                i--;
                HuPrcVSleep();
            } while (i != 0);
            shown = val;
        }
        HuPrcVSleep();
    }
    arrows->work[0] = 2;
    arrows->work[1] = 17;
    for (rot = 180.0f; rot < 360.0f; rot += (180.0f / 7.0f)) {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C258_main(lifts[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.4f, 0.1f, 1);
    func_8010DDD8_msetup(arrows);
    if (anim >= 0) {
        func_80033430_main(anim);
    }
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    return 0;
}

/* Stick direction of pad `pad` by quadrant of atan2(x, y): 0 [0, 90), 1, 2, 3; -1 inside the
   +-30 dead zone. */
s32 func_801150A0_msetup(s16 pad) {
    s8 x;
    s8 y;
    f32 angle;
    s32 dir;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];
    dir = 0;
    if (x >= -30 && x <= 30) {
        if (y >= -30 && y <= 30) {
            return -1;
        }
    }
    angle = atan2df(x, y);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle >= 0.0f && angle < 90.0f) {
        dir = 0;
    } else if (angle >= 90.0f && angle < 180.0f) {
        dir = 1;
    } else if (angle >= 180.0f && angle < 270.0f) {
        dir = 2;
    } else if (angle >= 270.0f && angle < 360.0f) {
        dir = 3;
    }
    return dir;
}

/* Rules lift helpers (fork D) */
void *func_8001D33C_main(s16 model, char *name);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
f32 fabsf(f32);
extern char D_8011A7D8_msetup[]; /* "20turn" (INCLUDE_RODATA: later asm uses these too) */
extern char D_8011A7E0_msetup[]; /* "35turn" */
extern char D_8011A7E8_msetup[]; /* "50turn" */
extern char D_8011A7F0_msetup[]; /* "q_turn" */
extern char D_8011A7F8_msetup[]; /* "hari" (the dial's hand) */
extern f32 D_8011A908_msetup;    /* hand angle (80115EE0 clears it with sw) */

/* Turn count dial on model `model`: four labelled parts (20/35/50 turns, ?), the selected one
   pulses; the hand ("hari", base matrix `hand`) turns to D_80119F4C_msetup[sel]. Returns the
   choice, -1 on B. */
#ifdef NON_MATCHING
/* Register allocation only: retail keeps `pad` in s8 and spills `hand`, keeps the dpad test in
   s0 (the later `dir`), and holds fabsf(diff) in f20 and the +-24 step in f2. */
s16 func_801152C4_msetup(s16 model, s32 arg1, HuMtx4F hand, s16 *pad, s16 sel) {
    MsPart *parts[4];
    u8 unused[4];
    HuMtx4F base[4];
    s16 i;
    s16 prev;
    s16 dir;
    s32 btn;
    f32 pulse;
    f32 angle;
    f32 target;
    f32 diff;
    f32 scale;
    HuMtx4F *mtx;

    parts[0] = func_8001D33C_main(model, D_8011A7D8_msetup);
    func_8002367C_main(base[0], parts[0]->mtx);
    parts[1] = func_8001D33C_main(model, D_8011A7E0_msetup);
    func_8002367C_main(base[1], parts[1]->mtx);
    parts[2] = func_8001D33C_main(model, D_8011A7E8_msetup);
    func_8002367C_main(base[2], parts[2]->mtx);
    parts[3] = func_8001D33C_main(model, D_8011A7F0_msetup);
    func_8002367C_main(base[3], parts[3]->mtx);
    pulse = 0.0f;
    for (i = 0; i < 4; i++) {
        unused[i] = 0;
    }
    angle = D_8011A908_msetup;
    target = D_80119F4C_msetup[sel];
    prev = -1;
    while (1) {
        btn = func_8010D684_msetup(D_8011A948_msetup, pad);
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
        if (btn & A_BUTTON) {
            if (sel < 3) {
                HuAudFXPlay(0x139);
            } else {
                HuAudFXPlay(2);
            }
            break;
        }
        dir = ((u32)btn >> 8) & 0xF;
        if (dir != 0) {
            if (D_800CDA7C_main[D_8011A948_msetup] & 0x300) {
                if (D_800CDA7C_main[D_8011A948_msetup] & 0x100) {
                    sel++;
                    if (sel >= 4) {
                        sel = 0;
                    }
                } else if (D_800CDA7C_main[D_8011A948_msetup] & 0x200) {
                    sel--;
                    if (sel < 0) {
                        sel = 3;
                    }
                } else {
                    goto moved;
                }
                HuAudFXPlay(1);
            } else {
                dir = func_801150A0_msetup(D_8011A948_msetup);
                if (dir >= 0) {
                    if (sel != dir) {
                        HuAudFXPlay(1);
                        sel = dir;
                    }
                }
            }
        }
    moved:
        if (prev != sel) {
            func_8010B82C_msetup(D_80119F3C_msetup[sel]);
            target = D_80119F4C_msetup[sel];
            D_8011A908_msetup = target;
            if (prev >= 0) {
                mtx = &parts[prev]->mtx;
                func_8002367C_main(*mtx, base[prev]);
                func_80017CD0_main(*mtx, 1.0f, 1.0f, 1.0f);
            }
            prev = sel;
        }
        if (target != angle) {
            diff = target - angle;
            if (fabsf(diff) > 180.0f) {
                diff = -diff;
            }
            if (diff < 0.0f) {
                angle += -24.0f;
            } else {
                angle += 24.0f;
            }
            if (angle > 360.0f) {
                angle -= 360.0f;
            } else if (angle < 0.0f) {
                angle += 360.0f;
            }
            mtx = &((MsPart *)func_8001D33C_main(model, D_8011A7F8_msetup))->mtx;
            func_8002367C_main(*mtx, hand);
            func_80017D24_main(*mtx, 0.0f, 0.0f, angle);
        }
        pulse += 12.0f;
        if (pulse >= 180.0f) {
            pulse -= 180.0f;
        }
        scale = sindf(pulse) * 0.5f + 1.0f;
        mtx = &parts[sel]->mtx;
        func_8002367C_main(*mtx, base[sel]);
        func_80017CD0_main(*mtx, scale, scale, scale);
        HuPrcVSleep();
    }
    mtx = &parts[prev]->mtx;
    func_8002367C_main(*mtx, base[prev]);
    func_80017CD0_main(*mtx, 1.0f, 1.0f, 1.0f);
    return sel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801152C4_msetup);
#endif

/* Turns the board model to its back and lets the player pick one of 9 values (left/right wrap);
   B cancels (-1). Returns the choice. */
#ifdef NON_MATCHING
/* masked 0; raw 8: s-register allocation (pad, arrows, sprModel, right rotated) */
s16 func_801157B8_msetup(s16 model, s16 sprModel, s16 *pad, s16 sel, MsLift *lifts, omObjData *arrows) {
    f32 rot;
    s16 prev;
    s32 btn;
    s16 lift;
    u32 right; /* GCC keeps this constant in a register across the goto loop */

    func_80032FF8_main(sprModel, sel);
    rot = 0.0f;
    do {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
        rot += 25.714285f;
    } while (rot <= 180.0f);
    func_8010B82C_msetup(0x1529);
    prev = -1;
    right = 4;
loop:
    btn = func_8010D684_msetup(D_8011A948_msetup, pad);
    if (btn & 0x4000) {
        goto cancel;
    }
    if (btn & 0x8000) {
        goto decide;
    }
    if (btn & 0x900) {
        sel++;
        if (sel >= 9) {
            sel = 0;
        }
        HuAudFXPlay(1);
        arrows->work[0] = right;
    } else if (btn & 0x600) {
        sel--;
        if (sel < 0) {
            sel = 8;
        }
        HuAudFXPlay(1);
        arrows->work[0] = 3;
    }
    if (prev != sel) {
        func_80032FF8_main(sprModel, sel);
        prev = sel;
    }
    HuPrcVSleep();
    goto loop;
done:
    if (sel < 0) {
        goto back;
    }
    lift = lifts->model;
    func_8001C258_main(lift, 4, 0);
    Hu3DModelRotSet(lift, 0.0f, 180.0f, 0.0f);
    rot = 180.0f;
    do {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        Hu3DModelRotSet(lift, 0.0f, rot, 0.0f);
        HuPrcVSleep();
        rot += 25.714285f;
    } while (rot < 360.0f);
    goto end;
decide:
    HuAudFXPlay(0x139);
    goto done;
cancel:
    HuAudFXPlay(4);
    sel = -1;
    goto done;
back:
    rot = 180.0f;
    do {
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        HuPrcVSleep();
        rot -= 25.714285f;
    } while (rot >= 0.0f);
end:
    return sel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801157B8_msetup);
#endif

f32 fabsf(f32);
f32 sindf(f32 angle);
void *func_8001D33C_main(s16 model, char *name);
void func_8002367C_main(HuMtx4F, HuMtx4F); /* matrix copy */
void func_80017CD0_main(HuMtx4F, f32, f32, f32); /* scale */
void func_80017D24_main(HuMtx4F, f32, f32, f32); /* rotate */

/* A model part (func_8001D33C_main; MP3 hmfman.c HmfMotionObjM): only its matrix is used here. */
typedef struct MseHmfPart {
    /* 0x00 */ char unk00[0x58];
    /* 0x58 */ HuMtx4F mtx;
} MseHmfPart; /* size = 0x98 */

extern char D_8011A7D8_msetup[]; /* "20turn" (shared with func_801152C4_msetup) */
extern char D_8011A7E0_msetup[]; /* "35turn" */
extern char D_8011A7E8_msetup[]; /* "50turn" */
extern char D_8011A7F0_msetup[]; /* "q_turn" */
extern char D_8011A7F8_msetup[]; /* "hari" */
extern char D_8011A800_msetup[]; /* "mugen" */

/* Two-way choice on the board model: the chosen part ("20turn" / "mugen") pulses, the "hari"
   needle turns to D_80119F60_msetup[sel]. Returns the choice, -1 on B. */
#ifdef NON_MATCHING
/* masked 49: loop.c hoists the 1.0f scale constant (retail loads it per call) and keeps 180.0f in a
   GPR, shifting the frame by 8 and the register allocation; the logic follows the asm */
s16 func_80115A9C_msetup(s16 model, s32 arg1, HuMtx4F needleMtx, s16 *pad, s32 selIn) {
    MseHmfPart *parts[2];
    HuMtx4F mtx[2];
    s16 sel;
    s16 prev;
    s32 btn;
    f32 phase;
    f32 rot;
    f32 target;
    f32 d;
    f32 scale;
    MseHmfPart *part;

    sel = selIn;
    parts[0] = func_8001D33C_main(model, D_8011A7D8_msetup);
    func_8002367C_main(mtx[0], parts[0]->mtx);
    parts[1] = func_8001D33C_main(model, D_8011A800_msetup);
    func_8002367C_main(mtx[1], parts[1]->mtx);
    phase = 0.0f;
    rot = D_8011A908_msetup;
    target = D_80119F60_msetup[sel];
    prev = -1;
    while (TRUE) {
        btn = func_8010D684_msetup(D_8011A948_msetup, pad);
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
        if (btn & 0x8000) {
            HuAudFXPlay(0x139);
            break;
        }
        if (btn & 0x900) {
            if (sel != 0) {
                HuAudFXPlay(1);
            }
            sel = 0;
        } else if (btn & 0x600) {
            if (sel == 0) {
                HuAudFXPlay(1);
            }
            sel = 1;
        }
        if (prev != sel) {
            func_8010B82C_msetup(D_80119F8C_msetup[sel]);
            target = D_80119F60_msetup[sel];
            D_8011A908_msetup = target;
            if (prev >= 0) {
                part = parts[prev];
                func_8002367C_main(part->mtx, mtx[prev]);
                func_80017CD0_main(part->mtx, 1.0f, 1.0f, 1.0f);
            }
            prev = sel;
        }
        if (target != rot) {
            d = target - rot;
            if (fabsf(d) > 180.0f) {
                d = -d;
            }
            if (d < 0.0f) {
                rot += -24.0f;
            } else {
                rot += 24.0f;
            }
            if (rot > 360.0f) {
                rot -= 360.0f;
            } else if (rot < 0.0f) {
                rot += 360.0f;
            }
            part = func_8001D33C_main(model, D_8011A7F8_msetup);
            func_8002367C_main(part->mtx, needleMtx);
            func_80017D24_main(part->mtx, 0.0f, 0.0f, rot);
        }
        phase += 12.0f;
        if (phase >= 180.0f) {
            phase -= 180.0f;
        }
        scale = sindf(phase) * 0.5f + 1.0f;
        part = parts[sel];
        func_8002367C_main(part->mtx, mtx[sel]);
        func_80017CD0_main(part->mtx, scale, scale, scale);
        HuPrcVSleep();
    }
    part = parts[prev];
    func_8002367C_main(part->mtx, mtx[prev]);
    func_80017CD0_main(part->mtx, 1.0f, 1.0f, 1.0f);
    return sel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115A9C_msetup);
#endif

/* Moves a model by (x, y, z). */
void func_80115E78_msetup(s16 model, f32 x, f32 y, f32 z) {
    if (model >= 0 && HmfModelData[model].hmf != NULL) {
        HmfModelData[model].pos.x += x;
        HmfModelData[model].pos.y += y;
        HmfModelData[model].pos.z += z;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A800_msetup);

s16 HmfAnimRead(HmfData *hmf, s32 dataNum, char *name);


/* Rules table (s16 values, 0x80119F6C..0x80119F8B in .data: entries 0-2 the party lengths
   (20/35/50 turns), 6-14 the nine picker values). Retail reads the low bytes through the split
   labels D_80119F6D/D_80119F79; C indexes D_80119F6C_msetup (the picker values from entry 6). */

/* State: the game-length board. Lifts bring the board model up; step 0 picks the length
   (func_801152C4_msetup), step 1 the custom turn count (func_801157B8_msetup), step 2 (duel) the
   two-way choice (func_80115A9C_msetup). B backs out (work->unk4 = -1). */
#ifdef NON_MATCHING
/* masked ~70: retail writes D_8011AA42/46 through a loop-hoisted base register (s4) where this C
   uses absolute addresses, which shifts the s-register allocation; the logic follows the asm */
s32 func_80115EE0_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    Vec pos;
    Vec rot;
    HuMtx4F needleMtx;
    s16 prevBtn;
    s16 sprModel;
    s16 model;
    s16 lift;
    s16 lift1;
    s16 sel;
    s16 step;
    s32 i;
    s32 mes;
    omObjData *arrows;
    f32 r;
    Vec *liftRot;
    f32 speed;

    work->unk4 = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 0.0f);
    func_8010E4D8_msetup(lifts, 2);
    model = func_8000B108_main(0x140008, 0x2A9);
    sprModel = HmfAnimRead(HmfModelData[model].hmf, 0x140024, "uramen_CIDX");
    func_8001C448_main(model);
    rot.x = rot.y = rot.z = 0.0f;
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
    pos = D_80119B20_msetup;
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    func_8002367C_main(needleMtx, ((MseHmfPart *)func_8001D33C_main(model, D_8011A7F8_msetup))->mtx);
    mes = 0;
    switch (D_8011A938_msetup) {
    case 0:
        func_80017CD0_main(((MseHmfPart *)func_8001D33C_main(model, D_8011A800_msetup))->mtx, 0.0f, 0.0f, 0.0f);
        mes = 0x1524;
        break;
    case 1:
        func_80017CD0_main(((MseHmfPart *)func_8001D33C_main(model, D_8011A7E0_msetup))->mtx, 0.0f, 0.0f, 0.0f);
        func_80017CD0_main(((MseHmfPart *)func_8001D33C_main(model, D_8011A7E8_msetup))->mtx, 0.0f, 0.0f, 0.0f);
        func_80017CD0_main(((MseHmfPart *)func_8001D33C_main(model, D_8011A7F0_msetup))->mtx, 0.0f, 0.0f, 0.0f);
        mes = 0x242E;
        break;
    }
    arrows = func_8010DE38_msetup(0x60, 0xE0, 0x48);
    func_8010B82C_msetup(mes);
    i = 0;
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 15, 720.0f, 565.0f, 0.1f, 1.5f, 1);
    lifts[0].pos.z -= 1.5f;
    lifts[1].pos.z -= 1.5f;
    lift1 = lifts[1].model;
    Hu3DModelPosSet(lift1, lifts[1].pos.x, lifts[1].pos.y, lifts[1].pos.z);
    func_8001C258_main(lift1, 4, 4);
    lift = lifts[0].model;
    Hu3DModelPosSet(lift, lifts[0].pos.x, lifts[0].pos.y, lifts[0].pos.z);
    pos.y += 565.0f;
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    rot.y = 180.0f;
    Hu3DModelScaleSet(model, 1.5f, 1.5f, 1.5f);
    liftRot = &lifts[0].rot;
    speed = 25.714285f;
    do {
        rot.y = speed + rot.y;
        if (rot.y > 360.0f) {
            rot.y -= 360.0f;
        }
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        liftRot->y = speed + liftRot->y;
        if (liftRot->y > 360.0f) {
            liftRot->y -= 360.0f;
        }
        Hu3DModelRotSet(lift, liftRot->x, liftRot->y, liftRot->z);
        i++;
        HuPrcVSleep();
    } while (i < 7);
    rot.y = 0.0f;
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
    func_8001C258_main(lift, 4, 4);
    step = 0;
    switch (D_8011A938_msetup) {
    case 1:
        step = 2;
    case 0:
        sel = 0;
        break;
    default:
        sel = 0;
        break;
    }
    D_8011A908_msetup = 0.0f;
    func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
    do {
        func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        switch (step) {
        case 0:
            sel = func_801152C4_msetup(model, sprModel, needleMtx, &prevBtn, sel);
            if (sel < 0) {
                work->unk4 = -1;
            } else if (sel < 3) {
                D_8011AA30_msetup.turns = D_80119F6C_msetup[sel];
                D_8011AA30_msetup.length = sel;
                sel = -1;
            } else {
                sel = 0;
                step++;
            }
            break;
        case 1:
            arrows->work[0] = 1;
            arrows->work[1] = 0x24;
            sel = func_801157B8_msetup(model, sprModel, &prevBtn, sel, lifts, arrows);
            if (sel < 0) {
                sel = 3;
                step--;
            } else {
                D_8011AA30_msetup.turns = D_80119F6C_msetup[6 + sel];
                D_8011AA30_msetup.length = 3;
                sel = -1;
            }
            arrows->work[0] = 2;
            arrows->work[1] = 0x24;
            break;
        case 2:
            sel = func_80115A9C_msetup(model, sprModel, needleMtx, &prevBtn, sel);
            if (sel < 0) {
                work->unk4 = -1;
            } else if (sel >= 2) {
                work->unk4 = -1;
                sel = -1;
            } else {
                D_8011AA42_msetup = (sel == 0) ? 20 : 0xFF;
                sel = -1;
            }
            break;
        }
        HuPrcVSleep();
    } while (sel >= 0);
    func_8010B998_msetup();
    lift1 = lifts[1].model;
    func_8001C258_main(lift1, 4, 0);
    Hu3DModelRotSet(lift1, 0.0f, 180.0f, 0.0f);
    r = 0.0f;
    do {
        Hu3DModelRotSet(model, 0.0f, r, 0.0f);
        Hu3DModelRotSet(lifts[0].model, 0.0f, r, 0.0f);
        Hu3DModelRotSet(lift1, 0.0f, r + 180.0f, 0.0f);
        HuPrcVSleep();
        r += 25.714285f;
    } while (r < 180.0f);
    func_8001C258_main(lifts[0].model, 4, 0);
    func_8001C258_main(model, 4, 4);
    lifts[0].rot.y = 0.0f;
    lifts[1].rot.y = 180.0f;
    lifts[0].pos.z += 1.5f;
    lifts[1].pos.z += 1.5f;
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.5f, 0.1f, 2);
    func_8010DDD8_msetup(arrows);
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    if (work->unk4 >= 0) {
        switch (D_8011A938_msetup) {
        case 0:
            for (i = 0; i < 9; i++) {
                if (D_8011AA42_msetup == D_80119F6C_msetup[6 + i]) {
                    break;
                }
            }
            if (i >= 9) {
                i = 0;
            }
            break;
        case 1:
            if (D_8011AA42_msetup == 0xFF) {
                i = 9;
            } else {
                i = 2;
            }
            break;
        }
        func_80032FF8_main(sprModel, i);
        func_8010F320_msetup(D_80119420_msetup, 1, model, sprModel);
        return 0;
    }
    if (sprModel >= 0) {
        func_80033430_main(sprModel);
    }
    func_8001ACDC_main(model);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115EE0_msetup);
#endif

void func_800332D4_main(s16 arg0, f32 arg1);
extern s32 D_80119FDC_msetup[2]; /* the two lifts' sign data numbers */
extern MsLiftKey D_80119F94_msetup[2]; /* func_8010E52C_msetup lift targets (two lifts) */
extern MsLiftKey D_80119FB4_msetup[2];
extern char D_8011A6D8_msetup[];  /* sign texture name (shared with earlier functions) */

/* State: the 1P/2P team choice on two lifts (only offered with 2+ players):
   work->unk4 is the choice, D_8011A0B8_msetup[choice] the human count it stands for; B asks to
   quit (-1). Sets D_8011AA40/41 and buzzes the chosen players' controllers. */
#ifdef NON_MATCHING
s32 func_801167B8_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    s16 prevBtn;
    s32 noArrows;
    s32 players;
    s16 sel;
    s16 prev;
    s32 i;
    s32 redraw;
    s32 btn;
    s32 n;
    f32 rotY;
    f32 a;
    f32 b;
    MsLift *lift;
    s16 m;
    omObjData *arrows;

    players = D_8011AA30_msetup.unk14;
    arrows = NULL;
    if (work->unk4 < 0) {
        for (sel = 0; sel < 2; sel++) {
            if ((f32)D_8011AA30_msetup.unk10 == D_8011A0B8_msetup[sel]) {
                break;
            }
        }
        if (sel >= 2) {
            sel = 0;
        }
        work->unk4 = sel;
    } else {
        if (work->unk4 >= 2) {
            work->unk4 = 0;
        }
        sel = work->unk4;
    }
    if ((f32)players < D_8011A0B8_msetup[sel]) {
        for (sel = 0; sel < 2; sel++) {
            if ((f32)players == D_8011A0B8_msetup[sel]) {
                break;
            }
        }
        if (sel >= 2) {
            sel = 0;
        }
        work->unk4 = sel;
    }
    func_8010B998_msetup();
    rotY = 0.0f;
    if (players >= 2) {
        rotY = 90.0f;
    }
    func_8010E32C_msetup(lifts, 2, rotY, 0);
    for (i = 0; i < 2; i++) {
        lift = &lifts[i];
        m = lift->model;
        lift->unk1A = HmfAnimRead(HmfModelData[m].hmf, D_80119FDC_msetup[i], D_8011A6D8_msetup);
        func_8001C448_main(m);
        func_800332D4_main(lift->unk1A, 0.75f);
    }
    func_8010E4D8_msetup(lifts, 2);
    if (players >= 2) {
        arrows = func_8010DE38_msetup(0x40, 0x100, 0x48);
    }
    func_8010B82C_msetup(0x2403);
    func_8010B858_msetup();
    redraw = 1;
    HuAudFXPlay(0x2D9);
    a = 1.0f;
    func_8010E8C8_msetup(lifts, 2, 15, 720.0f, 565.0f, 0.1f, a, redraw);
    if (players >= 2) {
        arrows->work[0] = redraw;
        arrows->work[1] = 0x24;
        func_8010E52C_msetup(lifts, D_80119F94_msetup, 2, 7, 0, 0, 0.0f, a);
        i = 4;
        do {
            a += 0.1f;
            Hu3DModelScaleSet(lifts[sel].model, a, a, a);
            i--;
            HuPrcVSleep();
        } while (i != 0);
    } else {
        func_8001C258_main(lifts[1].model, 4, 4);
        rotY = lifts[0].rot.y;
        m = lifts[0].model;
        i = 0;
        do {
            rotY += 25.714285f;
            if (rotY > 360.0f) {
                rotY -= 360.0f;
            }
            Hu3DModelRotSet(m, 0.0f, rotY, 0.0f);
            i++;
            HuPrcVSleep();
        } while (i < 7);
        lifts[0].rot.y = rotY;
    }
    prev = sel;
    redraw = 1;
    func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
    noArrows = players < 2;
    while (TRUE) {
        if (redraw) {
            func_8010B82C_msetup(D_80119FD4_msetup[sel]);
            redraw = 0;
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        if (btn & 0x8000) {
            HuAudFXPlay(2);
            work->unk4 = sel;
            break;
        }
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            func_8010B82C_msetup(0x2401);
            redraw = 1;
            if (func_8010B858_msetup() == 0) {
                work->unk4 = -1;
                break;
            }
            func_8010B82C_msetup(0x2403);
            func_8010B858_msetup();
            btn = func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        }
        if (!noArrows) {
            if (btn & 0x900) {
                sel++;
                if (sel >= 2) {
                    sel = 0;
                }
                arrows->work[0] = 4;
            } else if (btn & 0x600) {
                sel--;
                if (sel < 0) {
                    sel = 1;
                }
                arrows->work[0] = 3;
            }
        }
        if (prev != sel) {
            HuAudFXPlay(1);
            a = 1.0f;
            b = 1.4f;
            i = 4;
            do {
                a += 0.1f;
                b += -0.1f;
                Hu3DModelScaleSet(lifts[sel].model, a, a, a);
                Hu3DModelScaleSet(lifts[prev].model, b, b, b);
                i--;
                HuPrcVSleep();
            } while (i != 0);
            prev = sel;
            redraw = 1;
        }
        HuPrcVSleep();
    }
    if (work->unk4 >= 0) {
        n = D_8011A0B8_msetup[work->unk4];
        D_8011AA30_msetup.unk10 = n;
        D_8011AA30_msetup.unk11 = 2 - n;
        for (i = 0; i < D_8011AA30_msetup.unk10; i++) {
            RepeatVibrator(D_8011AA30_msetup.pad[i], 10, 0, 10);
        }
    }
    if (players < 2) {
        rotY = lifts[0].rot.y;
        m = lifts[0].model;
        i = 0;
        do {
            rotY += 25.714285f;
            if (rotY > 360.0f) {
                rotY -= 360.0f;
            }
            Hu3DModelRotSet(m, 0.0f, rotY, 0.0f);
            i++;
            HuPrcVSleep();
        } while (i < 7);
        lifts[0].rot.y = rotY;
        func_8001C258_main(lifts[1].model, 4, 0);
    } else {
        arrows->work[0] = 2;
        arrows->work[1] = 0x11;
        func_8010E52C_msetup(lifts, D_80119FB4_msetup, 2, 7, 0, 0, 0.0f, 1.0f);
    }
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 2);
    i = 0;
    if (players >= 2) {
        func_8010DDD8_msetup(arrows);
        i = 0;
    }
    for (; i < 2; i++) {
        lift = &lifts[i];
        func_80033430_main(lift->unk1A);
        func_8001ACDC_main(lift->model);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801167B8_msetup);
#endif

void func_80032FC0_main(s16, u8, u8);
extern s16 D_80119FE4_msetup[5]; /* the five star/handicap values; the low byte is stored */

/* State: per-team handicap board (MsConfig.star) for two players in turn: left/right turns the
   sign through D_80119FE4_msetup, A stores it and moves on, B goes back (-1 before the first). */
#ifdef NON_MATCHING
/* masked ~21: the scheduling around the turn direction flag and the loop counters (s0) differs */
s32 func_80116FE0_msetup(MsSetupWork *work) {
    MsLift lifts[2];
    s16 prevBtn;
    MsSetupWork *w;
    s16 sprModel;
    s16 prevPlayer;
    s16 model;
    s16 sel;
    s16 player;
    s16 shown;
    s32 btn;
    s16 back;
    s32 i;
    f32 r;
    f32 step;
    omObjData *arrows;

    w = work;
    work->unk4 = 0;
    for (sel = 0; sel < 5; sel++) {
        if (D_8011AA30_msetup.star[0] == D_80119FE4_msetup[sel]) {
            break;
        }
    }
    if (sel >= 5) {
        sel = 0;
    }
    player = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(lifts, 2, 0.0f);
    func_8010E4D8_msetup(lifts, 2);
    model = func_8000B108_main(0x14000A, 0x2A9);
    sprModel = HmfAnimRead(HmfModelData[model].hmf, 0x140034, "sitagocoro_DEF");
    func_8001C448_main(model);
    func_8001C514_main(model);
    func_80032FC0_main(sprModel, 1, 1);
    func_80032FF8_main(sprModel, sel);
    func_8001C258_main(model, 4, 4);
    arrows = func_8010DE38_msetup(0x60, 0xE0, 0x48);
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(lifts, 2, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    arrows->work[0] = 1;
    arrows->work[1] = 0x24;
    func_8001C258_main(lifts[1].model, 4, 4);
    Hu3DModelPosSet(model, D_80119B20_msetup.x, D_80119B20_msetup.y + 565.0f, D_80119B20_msetup.z + 0.5f);
    Hu3DModelRotSet(model, 0.0f, 180.0f, 0.0f);
    func_8001C258_main(model, 4, 0);
    r = 0.0f;
    do {
        Hu3DModelRotSet(lifts[0].model, 0.0f, r, 0.0f);
        Hu3DModelRotSet(model, 0.0f, r + 180.0f, 0.0f);
        HuPrcVSleep();
        r += 25.714285f;
    } while (r < 180.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lifts[0].model, 0.0f, 180.0f, 0.0f);
    shown = sel;
    prevPlayer = -1;
    func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
    while (TRUE) {
        if (prevPlayer != player) {
            func_8010B968_msetup(D_8011AA30_msetup.chr[player] + 0x1C00, 0);
            func_8010B82C_msetup(0x2413);
            prevPlayer = player;
        }
        btn = func_8010D684_msetup(D_8011A948_msetup, &prevBtn);
        if (btn & 0x8000) {
            HuAudFXPlay(2);
            D_8011AA30_msetup.star[player] = D_80119FE4_msetup[sel];
            D_8011A9E0_msetup[player].state = 0xD;
            player++;
            if (player >= 2) {
                w->unk4 = 0;
                break;
            }
            i = D_8011AA30_msetup.star[player];
            for (sel = 0; sel < 5; sel++) {
                if (i == D_80119FE4_msetup[sel]) {
                    break;
                }
            }
            if (sel >= 5) {
                sel = 0;
            }
        } else if (btn & 0x4000) {
            HuAudFXPlay(4);
            player--;
            if (player < 0) {
                w->unk4 = -1;
                break;
            }
            D_8011A9E0_msetup[player].state = 0xE;
            i = D_8011AA30_msetup.star[player];
            for (sel = 0; sel < 5; sel++) {
                if (i == D_80119FE4_msetup[sel]) {
                    break;
                }
            }
            if (sel >= 5) {
                sel = 0;
            }
        }
        back = 0;
        if (btn & 0x900) {
            sel++;
            if (sel >= 5) {
                sel = 0;
            }
            arrows->work[0] = 4;
        } else if (btn & 0x600) {
            sel--;
            if (sel < 0) {
                sel = 4;
            }
            arrows->work[0] = 3;
            back = 1;
        }
        if (shown != sel) {
            HuAudFXPlay(1);
            step = 45.0f;
            if (back) {
                step = -45.0f;
            }
            r = 0.0f;
            for (i = 4; i != 0; i--) {
                r += step;
                if (r < 0.0f) {
                    r += 360.0f;
                }
                Hu3DModelRotSet(model, 0.0f, r, 0.0f);
                Hu3DModelRotSet(lifts[0].model, 0.0f, r + 180.0f, 0.0f);
                HuPrcVSleep();
            }
            func_80032FF8_main(sprModel, sel);
            r = 180.0f;
            for (i = 4; i != 0; i--) {
                r += step;
                if (r >= 360.0f) {
                    r -= 360.0f;
                }
                Hu3DModelRotSet(model, 0.0f, r, 0.0f);
                Hu3DModelRotSet(lifts[0].model, 0.0f, r + 180.0f, 0.0f);
                HuPrcVSleep();
            }
            shown = sel;
        }
        HuPrcVSleep();
    }
    arrows->work[0] = 2;
    arrows->work[1] = 0x11;
    r = 0.0f;
    do {
        Hu3DModelRotSet(model, 0.0f, r, 0.0f);
        Hu3DModelRotSet(lifts[0].model, 0.0f, r + 180.0f, 0.0f);
        HuPrcVSleep();
        r += 25.714285f;
    } while (r < 180.0f);
    func_8001C258_main(lifts[1].model, 4, 0);
    Hu3DModelRotSet(lifts[1].model, 0.0f, 0.0f, 0.0f);
    func_8001C258_main(model, 4, 4);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(lifts, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 2);
    func_8010DDD8_msetup(arrows);
    if (sprModel >= 0) {
        func_80033430_main(sprModel);
    }
    if (model >= 0) {
        func_8001ACDC_main(model);
    }
    for (i = 0; i < 2; i++) {
        func_8001ACDC_main(lifts[i].model);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80116FE0_msetup);
#endif

s32 func_80117818_msetup(MsSetupWork *work) {
    return 0;
}

/* The overlay was linked from several source files, each 16-byte aligned (as modesel's MS_FILE_END). */
#ifndef MSETUP_FILE_END
#ifdef NON_MATCHING
#define MSETUP_FILE_END()
#else
#define MSETUP_FILE_END() __asm__(".section .text\n    .align 4\n");
#endif
#endif

extern s32 (*D_80119FF0_msetup[])(MsSetupWork *);

/* Runs the MsSetupWork state machine: each state function returns the next state. */
void func_80117820_msetup(void) {
    MsSetupWork *work = HuPrcCurrentGet()->user_data;
    s16 state; /* also the loop counter */

    for (state = 0; state < 4; state++) {
        D_8011A8E0_msetup[state][0] = -1;
        D_8011A8E0_msetup[state][1] = -1;
        D_8011A8E0_msetup[state][2] = -1;
        D_8011A8E0_msetup[state][3] = -1;
    }
    func_8010E21C_msetup();
    state = 0;
    while (TRUE) {
        if (state != work->state) {
            state = ((u16)work->state < 14) ? work->state : 0;
        }
        work->state = D_80119FF0_msetup[state](work);
        HuPrcVSleep();
    }
}

MSETUP_FILE_END()

f32 SprPos3DSet(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z);
extern s16 D_800D418E_main; /* the viewport being drawn */

/* SprPos3DSet plus a perspective scale (sprman's SprPosPerspectiveSet with a size factor). */
void func_80117910_msetup(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z, f32 scale) {
    HuSprite *sprite = HuSprGrpData[grpIdx]->members[idx];
    HuCamera *cam = &gCameraList[camIdx];
    HuCamera *vp;
    f64 dist;

    dist = SprPos3DSet(grpIdx, idx, camIdx, x, y, z);
    if (dist != 0.0) {
        vp = (HuCamera *)((u8 *)cam + D_800D418E_main * 16);
        sprite->unk_60 = vp->viewports[0].vp.vscale[0] * scale / 4.0 / dist / 1.3333334f;
        sprite->unk_64 = vp->viewports[0].vp.vscale[1] * scale / 4.0 / dist;
    }
}


extern Vec *D_8011A16C_msetup[3];     /* per page: the four positions it moves between */
extern MsStorySpr D_8011A178_msetup[10]; /* page 0 sprites (group 1) */
extern MsStorySpr D_8011A218_msetup[10]; /* page 1 */
extern MsStorySpr D_8011A2B8_msetup[11]; /* page 2 */
extern Vec D_8011A368_msetup[3];      /* per page: the two models' offset */
extern Vec D_8011A38C_msetup[3];      /* per page: the two models' rotation */
extern MsStorySpr D_8011A3B8_msetup[7]; /* page 0 choices (group 2) */
extern MsStorySpr D_8011A428_msetup[5]; /* page 1, flag 0x2D set */
extern MsStorySpr D_8011A478_msetup[5]; /* page 1, flag 0x2D clear */
extern MsStorySpr D_8011A4C8_msetup[4]; /* page 2 */
extern s16 D_8011A514_msetup[6][2];   /* page 0: choice positions (func_8010D4DC_msetup) */
extern s16 (*D_8011A544_msetup[3])[2]; /* per page: the cursor's positions */

/* Story-mode setup page process (user_data a MsStoryWork from func_80118D48_msetup; id 0-2): two
   sprite groups (and a shadow group on page 0) and two models that follow w->pos; w->state 1-7
   moves the page between its four positions, 5 runs its menu (w->result: the choice, -1 back). */
#ifdef NON_MATCHING
void func_80117A3C_msetup(void) {
    MsCursorWork cursor;
    Vec offs[16];
    Vec tmp;
    Vec prev;
    Vec from;
    Vec delta;
    s16 spr1[16];
    s16 spr2[8];
    s16 angles[16];
    u8 flags[6];
    s16 padv;
    MsStoryWork *w;
    MsStorySpr *tbl1;
    MsStorySpr *tbl2;
    Vec *keys;
    Vec *ofs;
    Vec *mofs;
    Vec *target;
    s16 n1;
    s16 n2;
    s16 nSel;
    s16 grp1;
    s16 grp2;
    s16 grp3;
    s16 spr;
    s16 model1;
    s16 model2;
    s16 last;
    s16 sel;
    s16 btn;
    s32 r;
    s32 key;
    s32 i;
    f32 t;
    f32 tmax;
    f32 s;
    f32 x;
    f32 y;
    f32 z;

    w = HuPrcCurrentGet()->user_data;
    switch (w->id) {
        case 0:
        default:
            tbl1 = D_8011A178_msetup;
            n1 = 10;
            tbl2 = D_8011A3B8_msetup;
            n2 = 7;
            break;
        case 1:
            tbl1 = D_8011A218_msetup;
            n1 = 10;
            if (_CheckFlag(0x2D) != 0) {
                tbl2 = D_8011A428_msetup;
                n2 = 5;
                nSel = 4;
            } else {
                tbl2 = D_8011A478_msetup;
                n2 = 5;
                nSel = 3;
            }
            break;
        case 2:
            tbl1 = D_8011A2B8_msetup;
            n1 = 11;
            tbl2 = D_8011A4C8_msetup;
            n2 = 4;
            break;
    }
    keys = D_8011A16C_msetup[w->id];
    for (i = 0; i < n1; i++) {
        spr1[i] = -1;
    }
    for (i = 0; i < n2; i++) {
        spr2[i] = -1;
    }
    grp3 = -1;
    w->pos = keys[0];
    grp1 = HuSprGrpCreate(n1, 0);
    for (i = 0; i < (u16)n1; i++) {
        spr1[i] = func_8000B838_main(tbl1[i].file);
        func_80055458_main(grp1, i, 0x100);
        HuSprAttrReset(grp1, i, 0xFFFF);
        HuSprAttrSet(grp1, i, 0x1000);
        HuSprScaleSet(grp1, i, 1.0f, 1.0f);
        func_800550F4_main(grp1, i, 0);
        func_80055024_main(grp1, i, spr1[i], 0);
        HuSprPriSet(grp1, i, 0x258);
        func_80055420_main(grp1, i, 0xFF, 0xFF, 0xFF);
        offs[i] = tbl1[i].pos;
        angles[i] = (i * 95) % 360;
    }
    if (w->id == 2) {
        HuSprScaleSet(grp1, 0, 4.0f, 2.0f);
    }
    grp2 = HuSprGrpCreate(n2, 0);
    for (i = 0; i < (u16)n2; i++) {
        spr2[i] = func_8000B838_main(tbl2[i].file);
        HuSprAttrReset(grp2, i, 0xFFFF);
        HuSprAttrSet(grp2, i, 0x1000);
        func_800550F4_main(grp2, i, 0);
        func_80055024_main(grp2, i, spr2[i], 0);
        func_80055458_main(grp2, i, 0x100);
        if (i != 0) {
            HuSprPriSet(grp2, i, 0x190);
            switch (w->id) {
                case 0:
                    HuSprAttrSet(grp2, i, 0x9000);
                    break;
                case 1:
                    func_80055458_main(grp2, i, 0x40);
                    break;
            }
        } else {
            HuSprPriSet(grp2, i, 0x1F4);
        }
    }
    if (w->id == 0) {
        grp3 = HuSprGrpCreate(n2, 0);
        spr = func_8000B838_main(0x140064);
        for (i = 0; i < (u16)n2; i++) {
            HuSprAttrReset(grp3, i, 0xFFFF);
            HuSprAttrSet(grp3, i, 0x9000);
            func_800550F4_main(grp3, i, 0);
            func_80055024_main(grp3, i, spr, 0);
            func_80055458_main(grp3, i, 0x80);
            HuSprPriSet(grp3, i, 0x1C2);
            func_80055420_main(grp3, i, 0, 0, 0);
        }
    } else if (w->id == 2) {
        HuSprPriSet(grp2, 1, 0x1F4);
        func_80055458_main(grp2, 0, 0x40);
        func_80055458_main(grp2, 1, 0x40);
    }
    model1 = func_8000B108_main(0xA0089, 0x29D);
    model2 = func_8000B108_main(0x140068, 0x29D);
    func_8001C814_main(model1, 2, 2);
    func_8001C258_main(model1, 4, 0);
    func_8001C258_main(model2, 4, 0);
    Hu3DModelScaleSet(model1, 0.8f, 0.8f, 0.8f);
    Hu3DModelScaleSet(model2, 0.8f, 0.8f, 0.8f);
    target = &D_8011A38C_msetup[w->id];
    Hu3DModelRotSet(model1, target->x, target->y, target->z);
    Hu3DModelRotSet(model2, target->x, target->y, target->z);
    mofs = &D_8011A368_msetup[w->id];
    tmp.x = w->pos.x + mofs->x;
    tmp.y = w->pos.y + mofs->y;
    tmp.z = w->pos.z + mofs->z;
    Hu3DModelPosSet(model1, tmp.x, tmp.y, tmp.z);
    Hu3DModelPosSet(model2, tmp.x, tmp.y, tmp.z);
    omAddPrcObj(func_8010D6D0_msetup, 0x3F00, 0x800, 0)->user_data = &cursor;
    cursor.x = 0xA0;
    cursor.y = 0x78;
    cursor.pos = D_8011A544_msetup[w->id];
    cursor.file = D_8011A508_msetup[w->id];
    cursor.sel = -1;
    cursor.state = 0;
    cursor.steps = 0;
    cursor.attr = 0;
    HuPrcVSleep();
    for (i = 0; i < ARRAY_COUNTU(flags); i++) {
        flags[i] = 0;
    }
    prev.z = prev.y = prev.x = 0.0f;
    key = 0;
    t = 0.0f;
    tmax = t;
    last = 0;
    sel = D_8011A550_msetup[w->id];
    cursor.sel = sel;
    cursor.steps = 4;
    func_8010D684_msetup(D_8011A948_msetup, &padv);
    while (TRUE) {
        if (last != w->state) {
            switch (w->state) {
                case 0:
                    break;
                case 6:
                    cursor.state = 2;
                    from = keys[key];
                    tmp = keys[key];
                    tmp.y += 800.0f;
                    target = &tmp;
                    key = 0;
                    goto move;
                case 4:
                    cursor.state = 2;
                    from = keys[key];
                    target = &keys[0];
                    key = 0;
                    goto move;
                case 3:
                    cursor.state = 2;
                    from = keys[key];
                    target = &keys[2];
                    key = 2;
                    goto move;
                case 7:
                    cursor.state = 2;
                    from = keys[key];
                    target = &keys[3];
                    key = 3;
                    goto move;
                case 2:
                    switch (w->id) {
                        case 0:
                            for (i = 0; i < (u16)n2; i++) {
                                HuSprAttrSet(grp3, i, 0x8000);
                            }
                            break;
                        case 1:
                            func_80055458_main(grp2, sel + 1, 0x40);
                            break;
                    }
                    /* fallthrough */
                case 1:
                    from = keys[key];
                    target = &keys[1];
                    key = 1;
                move:
                    delta.x = target->x - from.x;
                    delta.y = target->y - from.y;
                    delta.z = target->z - from.z;
                    if (delta.x == 0.0f && delta.y == 0.0f && delta.z == 0.0f) {
                        t = 0.0f;
                        tmax = t;
                        w->state = 0;
                    } else {
                        tmax = 30.0f;
                        t = 0.0f;
                    }
                    break;
                case 5:
                    func_8010D684_msetup(D_8011A948_msetup, &padv);
                    cursor.state = 1;
                    switch (w->id) {
                        case 0:
                            HuSprAttrReset(grp2, sel + 1, 0x8000);
                            break;
                        case 1:
                            func_80055458_main(grp2, sel + 1, 0x100);
                            break;
                        case 2:
                            func_80055458_main(grp2, sel, 0x100);
                            break;
                    }
                    break;
            }
            last = w->state;
        }
        if (tmax != 0.0f) {
            t += 1.0f;
            s = sindf(3.0f * t);
            w->pos.x = s * delta.x + from.x;
            w->pos.y = s * delta.y + from.y;
            w->pos.z = s * delta.z + from.z;
            if (tmax <= t) {
                t = 0.0f;
                tmax = t;
                w->state = 0;
            }
        }
        for (i = 0; i < (u16)n1; i++) {
            ofs = &offs[i];
            x = w->pos.x + ofs->x + sindf(angles[i]);
            y = w->pos.y + ofs->y + cosdf(angles[i] * 2);
            z = w->pos.z + ofs->z;
            angles[i] += 4;
            if (angles[i] > 360) {
                angles[i] -= 360;
            }
            func_80117910_msetup(grp1, i, 0, x, y, z, 2.5f);
        }
        for (i = 0; i < (u16)n2; i++) {
            x = w->pos.x + tbl2[i].pos.x;
            y = w->pos.y + tbl2[i].pos.y;
            z = w->pos.z + tbl2[i].pos.z;
            func_80117910_msetup(grp2, i, 0, x, y, z, 2.5f);
            if (w->id == 0) {
                func_80117910_msetup(grp3, i, 0, x, y, z, 2.5f);
            }
        }
        tmp.x = w->pos.x + mofs->x;
        tmp.y = w->pos.y + mofs->y;
        tmp.z = w->pos.z + mofs->z;
        Hu3DModelPosSet(model1, tmp.x, tmp.y, tmp.z);
        Hu3DModelPosSet(model2, tmp.x, tmp.y, tmp.z);
        if (key == 1 && prev.x == w->pos.x && prev.y == w->pos.y && prev.z == w->pos.z) {
            for (i = 0; i < (u16)n2; i++) {
                HuSprScaleSet(grp2, i, 1.0f, 1.0f);
            }
        }
        prev.x = w->pos.x;
        prev.y = w->pos.y;
        prev.z = w->pos.z;
        btn = func_8010D684_msetup(D_8011A948_msetup, &padv);
        if (last == 5) {
            switch (w->id) {
                case 0:
                    if (btn & 0xF00) {
                        r = func_8010D4DC_msetup(D_8011A514_msetup, flags, 6, sel, D_8011A948_msetup, btn);
                        if (r >= 0 && r < ARRAY_COUNTU(flags)) {
                            sel = r;
                        }
                        if (cursor.sel != sel) {
                            HuAudFXPlay(1);
                            HuSprAttrSet(grp2, cursor.sel + 1, 0x8000);
                            HuSprAttrReset(grp2, sel + 1, 0x8000);
                            cursor.sel = sel;
                        }
                    }
                    if (btn & 0x8000) {
                        w->state = 0;
                        w->result = sel;
                        HuSprAttrReset(grp2, sel + 1, 0x8000);
                        HuAudFXPlay(D_8011A0D0_msetup[sel]);
                        RepeatVibrator(D_8011A948_msetup, 5, 0, 5);
                        for (i = 1; i < (u16)n2; i++) {
                            if (i != sel + 1) {
                                HuSprAttrReset(grp3, i, 0x8000);
                            }
                        }
                    } else if (btn & 0x4000) {
                        switch (w->id) {
                            case 0:
                                HuAudFXPlay(5);
                                break;
                            case 1:
                                HuAudFXPlay(4);
                                w->state = 0;
                                w->result = -1;
                                break;
                        }
                    }
                    break;
                case 1:
                    if (btn & 0x600) {
                        sel++;
                        if (sel >= nSel) {
                            sel = nSel - 1;
                        }
                    } else if (btn & 0x900) {
                        sel--;
                        if (sel < 0) {
                            sel = 0;
                        }
                    }
                    if (cursor.sel != sel) {
                        HuAudFXPlay(1);
                        func_80055458_main(grp2, cursor.sel + 1, 0x40);
                        func_80055458_main(grp2, sel + 1, 0x100);
                        cursor.sel = sel;
                    }
                    if (btn & 0x8000) {
                        HuAudFXPlay(2);
                        w->state = 0;
                        w->result = sel;
                    } else if (btn & 0x4000) {
                        HuAudFXPlay(4);
                        w->state = 0;
                        w->result = -1;
                        func_80055458_main(grp2, cursor.sel + 1, 0x40);
                    }
                    break;
                case 2:
                    if (btn & 0x600) {
                        sel = 0;
                    } else if (btn & 0x900) {
                        sel = 1;
                    }
                    if (cursor.sel != sel) {
                        HuAudFXPlay(1);
                        func_80055458_main(grp2, cursor.sel, 0x40);
                        func_80055458_main(grp2, sel, 0x100);
                        cursor.sel = sel;
                        w->result = sel;
                    }
                    if (btn & 0x8000) {
                        HuAudFXPlay(2);
                        w->state = 0;
                        w->result = sel;
                    } else if (btn & 0x4000) {
                        HuAudFXPlay(4);
                        w->state = 0;
                        w->result = -1;
                        func_80055458_main(grp2, cursor.sel, 0x40);
                    }
                    break;
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117A3C_msetup);
#endif

extern u8 D_800CE20A_main;
extern MsCamKey D_8011A554_msetup;

/* Story-mode setup process: three func_80117A3C_msetup page processes (one MsStoryWork each, ids
   0-2) driven through a message window; on confirm it seeds GwStory and starts story play. */
#ifdef NON_MATCHING
/* masked ~70: retail reloads D_8011A910_msetup by address each time where this C keeps a base;
   otherwise branch offsets and one store order */
void func_80118D48_msetup(void) {
    MsStoryWork w[3];
    s16 unk60[16]; /* never read: two of its halfwords are set to -1 six times */
    s32 i;
    s32 step;
    s16 shown;
    u16 spr;

    D_800CD280_main = 1;
    func_80106260_msetup(&D_8011A554_msetup);
    for (i = 0; i < 6; i++) {
        unk60[14] = -1;
        unk60[6] = -1;
    }
    memset(&w[0], 0, 0x14);
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &w[0];
    w[0].id = 0;
    w[0].pos.x = 0.0f;
    w[0].pos.y = 0.0f;
    w[0].pos.z = 0.0f;
    memset(&w[1], 0, 0x14);
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &w[1];
    w[1].id = 1;
    w[1].pos.x = 0.0f;
    w[1].pos.y = 0.0f;
    w[1].pos.z = 0.0f;
    memset(&w[2], 0, 0x14);
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &w[2];
    w[2].id = 2;
    w[2].pos.x = 0.0f;
    w[2].pos.y = 0.0f;
    w[2].pos.z = 0.0f;
    spr = InitEspriteSlot(func_8000B838_main(0x140067), 0, 0);
    func_8000BC48_main(spr, 0x4000);
    func_8000BBD4_main(spr, 0xA0, 0x78);
    D_8011A910_msetup[0] = func_80060880_main(0xA0, 0xCC, 0x13);
    func_8005FE54_main(D_8011A910_msetup[0], 0x10000 << D_8011A948_msetup >> 16);
    func_8006105C_main(D_8011A910_msetup[0], 0xE0);
    func_8005C060_main(D_8011A910_msetup[0], 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(D_8011A910_msetup[0], 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(D_8011A910_msetup[0], 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(D_8011A910_msetup[0], 0);
    HuAudSeqPlay(0xA);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    step = 0;
    D_800CD280_main = 0;
    do {
        switch (step) {
        case 0:
            func_8005B43C_main(D_8011A910_msetup[0], 0x6000, -1, -1);
            while (func_8005E0C0_main(D_8011A910_msetup[0]) != 0) {
                HuPrcVSleep();
            }
            step++;
            break;
        case 1:
            HuAudFXPlay(0x213);
            w[0].state = 2;
            do {
                HuPrcVSleep();
            } while (w[0].state != 0);
            func_8005B43C_main(D_8011A910_msetup[0], 0x6001, -1, -1);
            w[0].state = 5;
            do {
                HuPrcVSleep();
            } while (w[0].state != 0);
            func_8005D294_main(D_8011A910_msetup[0]);
            if (w[0].result >= 0) {
                w[0].state = 3;
                step++;
            }
            break;
        case 2:
            HuAudFXPlay(0x213);
            w[1].state = 2;
            do {
                HuPrcVSleep();
            } while (w[1].state != 0);
            func_8005B43C_main(D_8011A910_msetup[0], 0x6002, -1, -1);
            w[1].state = 5;
            do {
                HuPrcVSleep();
            } while (w[1].state != 0);
            func_8005D294_main(D_8011A910_msetup[0]);
            if (w[1].result >= 0) {
                w[0].state = 4;
                w[1].state = 4;
                step++;
            } else {
                w[1].state = 3;
                step--;
            }
            break;
        case 3:
            HuAudFXPlay(0x213);
            w[2].state = 2;
            do {
                HuPrcVSleep();
            } while (w[2].state != 0);
            func_8005B43C_main(D_8011A910_msetup[0], 0x6004, -1, -1);
            while (func_8005E0C0_main(D_8011A910_msetup[0]) != 0) {
                HuPrcVSleep();
            }
            shown = -1;
            w[2].state = 5;
            do {
                if (shown != w[2].result) {
                    shown = w[2].result;
                    if (shown != 0) {
                        func_8005B43C_main(D_8011A910_msetup[0], 0x6006, -1, -1);
                    } else {
                        func_8005B43C_main(D_8011A910_msetup[0], 0x6005, -1, -1);
                    }
                }
                HuPrcVSleep();
            } while (w[2].state != 0);
            func_8005D294_main(D_8011A910_msetup[0]);
            if (w[2].result >= 0) {
                w[2].state = 7;
                step++;
            } else {
                w[2].state = 3;
                w[0].state = 3;
                step--;
            }
            break;
        case 4:
            HuAudFXPlay(0x213);
            w[0].state = 7;
            w[1].state = 7;
            do {
                HuPrcVSleep();
            } while (w[1].state != 0);
            func_8005B43C_main(D_8011A910_msetup[0], 0x6003, -1, -1);
            while (func_8005E0C0_main(D_8011A910_msetup[0]) != 0) {
                HuPrcVSleep();
            }
            if (func_8005E1D8_main(D_8011A910_msetup[0], 0, 0) != 0) {
                w[0].state = 4;
                w[1].state = 4;
                step--;
            } else {
                step = -2;
                if ((u16)w[0].result < 6) {
                    GwStory.unk1 = D_8011A3B0_msetup[w[0].result];
                    GwStory.unk2 = w[1].result;
                    GwStory.unk0 = 0;
                    GwStory.unkF = 0;
                    for (i = 0; i < 12; i++) {
                        GwStory.unk3[i] = 0;
                    }
                    GwSystem.playMode = 5;
                    if (w[2].result == 1) {
                        _SetFlag(0x29);
                    } else {
                        _ClearFlag(0x29);
                    }
                    _ClearFlag(0x18);
                    _ClearFlag(0x28);
                    _ClearFlag(0);
                    /* unk_64: a copy of the first 0x10 bytes */
                    GwStory.unk_64[1] = GwStory.unk1;
                    GwStory.unk_64[0] = 0;
                    GwStory.unk_64[0xF] = 0;
                    GwStory.unk_64[2] = GwStory.unk2;
                    for (i = 0; i < 12; i++) {
                        GwStory.unk_64[3 + i] = 0;
                    }
                    func_8005035C_main(1);
                }
                HuAudFXPlay(0x214);
                w[0].state = 6;
                w[1].state = 6;
                w[2].state = 6;
            }
            func_8005D294_main(D_8011A910_msetup[0]);
            break;
        }
        HuPrcVSleep();
    } while (step >= 0);
    if (step < -1) {
        D_8011A944_msetup = 1;
        D_8011AA4C_msetup[0] = 0x75;
        D_8011A946_msetup = 0;
        D_800CE20A_main = 1;
    }
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80118D48_msetup);
#endif
