#include "game/audio.h"
#include "game/vibrator.h"
#include "common.h" // TODO: remove.

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[0x1D];
} UnkAudStruct; // Size unknown (min: 0x29, max: 0x30)

void func_8000086C_main(str800D5298 *);
s32 func_80007064_main(s32);
s32 func_80007080_main(s16, UnkAudStruct *);
void func_80007BD4_main(s16, s16);
void func_80007C80_main(s16, s16);
void func_80007DD8_main(s16);

extern u8 D_800D09A8_main;
extern str800D5298 D_800D5298_main;
extern s32 D_800D52C0_main;

/* Per-slot sound fades (MP2 7AA60.c's SndFadeWork; D_800D6A40_main->data) */
typedef struct SndFadeWork {
    /* 0x00 */ f32* vol;
    /* 0x04 */ f32* volStep;
    /* 0x08 */ f32* vol2;
    /* 0x0C */ f32* vol2Step;
    /* 0x10 */ u8* flags;
} SndFadeWork; /* size 0x14 */

extern s16 D_800CDBC8_main; /* current music player */
extern s16 D_800CE218_main[]; /* per-slot sound volume */
extern omObjData* D_800D6A40_main; /* sound fade object */
extern s8 D_800D6A4C_main[4];
extern s8 D_800D123C_main[4];
extern u16 D_800CCF7C_main[4];
extern u16 D_800CDD5C_main[4];
extern u16 D_800CB9A4_main[4];
extern u16 D_800D1244_main[4];

void func_80003810_main(s8);
void func_80003848_main(s32, s32);
s32 func_800038EC_main(s32);
s32 func_800078F8_main(s32);
s32 func_8000793C_main(s32);
void func_80007AF0_main(s32);
void func_80007B28_main(s32, s32);

u16 D_800A1900_main = 1;
u16 D_800A1902_main = 1;
s16 D_800A1904_main = -1; // active musId
u16 D_800A1906_main = 1;  // stat/attr
s16 D_800A1908_main = 0;
s16 D_800A190A_main = 0;
s16 D_800A190C_main = 1;
s16 D_800A190E_main = 1;
s16 D_800A1910_main = 0x40; // sound slot count

s16 HuAudSeqPlay(s16 musId) {
    if (D_800A1900_main == 0) {
        return 0;
    }
    if (D_800A1904_main == musId) {
        return 0;
    }
    if (musId == 0) {
        return -1;
    }
    func_800035E8_main(D_800CDBC8_main);
    D_800A1904_main = musId;
    D_800A1906_main |= 2;
    D_800A1906_main &= ~(1 | 8);
    D_800CDBC8_main = func_80003310_main(musId);
    return D_800CDBC8_main;
}

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A5C4_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A650_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A670_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A72C_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A7C4_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A880_main);

INCLUDE_ASM("asm/nonmatchings/audio", func_8004A918_main);

// HuAudSeqStop?
void func_8004A950_main(void) {
    D_800A1904_main = -1;
    func_800035E8_main(D_800CDBC8_main);
    D_800A1906_main &= ~(2 | 8);
    D_800A1906_main |= 1;
}

void HuAudSeqFadeOut(s16 speed) {
    D_800A1904_main = -1;
    func_800039A4_main(D_800CDBC8_main, speed);
    D_800A1906_main |= 8;
}

/* MP2 func_800794F0_7A0F0: current music volume */
void func_8004A9DC_main(s8 vol) {
    func_800036E8_main(D_800CDBC8_main, vol);
}

void func_8004AA04_main(s8 arg0) {
    func_80003810_main(arg0);
    D_800A1906_main &= ~8;
}

/* MP2 func_8007954C_7A14C: current music tempo */
void func_8004AA38_main(s16 bpm) {
    func_80003848_main(D_800CDBC8_main, bpm);
}

/* MP2 func_80079574_7A174: the current music's tempo */
s16 func_8004AA60_main(void) {
    return func_800038EC_main(D_800CDBC8_main);
}

s16 HuAudFXPlay(s16 seId) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_80007064_main(seId);
}

void func_8004AAD0_main(s16 index, s8 val) {
    D_800CE218_main[index] = val;
    func_80007B28_main(index, val);
}

/* MP2 func_80079614_7A214: fade out every sound slot over time frames */
void func_8004AB0C_main(s32 time) {
    s32 i;

    if (D_800D6A40_main != NULL) {
        for (i = 0; i < D_800A1910_main; i++) {
            func_8004AEF0_main(i, (s16)time);
        }
    }
}

/* MP2 func_80079684_7A284: every sound slot's volume */
void func_8004AB7C_main(s8 vol) {
    s32 i;

    for (i = 0; i < D_800A1910_main; i++) {
        D_800CE218_main[i] = vol;
    }
    func_80007AF0_main(vol);
}

void HuAudFXPitchSet(s32 seNo, s32 pitch) {
    func_80007BD4_main(seNo, pitch);
}

s16 CharFXPlay(s16 seId, u8 charNo) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_80007064_main(seId + charNo + 1);
}

s32 func_8004AC5C_main(s16 arg0, s16 arg1) {
    UnkAudStruct sp10;

    sp10.unk00 = 0x200;
    sp10.unk08 = arg1 + 1;
    return func_80007080_main(arg0, &sp10);
}

s16 func_8004AC98_main(s16 arg0, s16 arg1) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return func_8004AC5C_main(arg0, arg1);
}

// Matches once include/game/audio.h declares s16 func_8004ACE0_main(s16, s16)
// (2b-D.header.patch; the header has void (s32, s16)).
/* MP2 func_800797DC_7A3DC: play player's character voice id + character + 1 */
s16 func_8004ACE0_main(s16 id, s16 player) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (id == 0) {
        return 0;
    }
    return func_8004AC5C_main(id + GwPlayer[player].chr + 1, player);
}

void HuAudFXStop(s32 seNo) {
    func_80007DD8_main(seNo);
}

void func_8004AD70_main() {
    func_80007DD8_main(-1);
}

/* Looks up defNo's voice slot and stops it; returns the slot. */
s16 func_8004AD8C_main(s16 defNo) {
    s16 slot = func_8000793C_main(defNo);

    if (slot != -1) {
        func_80007DD8_main(slot);
    }
    return slot;
}

void func_8004ADDC_main(s16 arg0) {
    func_80007C80_main(-1, arg0);
}

void func_8004AE00_main(s16 arg0, s16 arg1) {
    func_80007C80_main(arg0, arg1);
}

INCLUDE_ASM("asm/nonmatchings/audio", func_8004AE28_main);

/* MP2 func_800799A4_7A5A4: fade sound slot ch out over frames, then stop it */
void func_8004AEF0_main(s16 ch, s32 frames) {
    SndFadeWork* work;

    if (D_800D6A40_main != NULL && func_800078F8_main(ch) != 0) {
        work = D_800D6A40_main->data;
        work->flags[ch] |= 1;
        work->vol[ch] = D_800CE218_main[ch];
        work->volStep[ch] = (f32)D_800CE218_main[ch] / (s16)frames;
    }
}

/* MP2 func_80079A70_7A670: fade every slot to silence over frames (pause) */
void func_8004AFBC_main(s16 frames) {
    SndFadeWork* work;
    s32 i;

    if (D_800D6A40_main != NULL) {
        work = D_800D6A40_main->data;
        for (i = 0; i < D_800A1910_main; i++) {
            work->flags[i] |= 6;
            if (work->flags[i] & 1) {
                work->vol2[i] = work->vol[i];
                work->vol2Step[i] = work->vol[i] / frames;
            } else {
                work->vol2[i] = D_800CE218_main[i];
                work->vol2Step[i] = (f32)D_800CE218_main[i] / frames;
            }
        }
    }
}

/* MP2 func_80079B88_7A788: end the pause fade, restore every slot's volume */
void func_8004B0D4_main(void) {
    SndFadeWork* work;
    s32 i;
    s16 vol;

    if (D_800D6A40_main != NULL) {
        work = D_800D6A40_main->data;
        for (i = 0; i < D_800A1910_main; i++) {
            work->flags[i] &= ~6;
            if (work->flags[i] & 1) {
                vol = work->vol[i];
            } else {
                vol = D_800CE218_main[i];
            }
            func_80007B28_main(i, vol);
        }
    }
}

/* MP1 func_80060E54: copy this frame's controller state */
void func_8004B1AC_main(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800D6A4C_main[i] = D_800CBB6E_main[i];
        D_800D123C_main[i] = D_800D20A1_main[i];
        D_800CCF7C_main[i] = D_800CDA7C_main[i];
        D_800CDD5C_main[i] = D_800D5558_main[i];
        D_800CB9A4_main[i] = D_800D1244_main[i];
    }
}

// Doesn't seem to be audio related? Maybe part of the next file.
void omVibrate(s16 player, s16 duration, s16 off, s16 on) {
    if (!(GwPlayer[player].stat & PLAYER_IS_CPU)) {
        RepeatVibrator(GwPlayer[player].pad, duration, off, on);
    }
}

s32 func_8004B2C0_main() {
    return 0;
}

void func_8004B2C8_main(void) {
    str800D5298 *temp;

    func_80000EA8_main(&D_800D5298_main);
    temp = &D_800D5298_main;
    temp->unk28 = 1; //?
    D_800D5298_main.unk8 = audio_mbf0_ROM_START;
    D_800D5298_main.unkC = audio_sbf0_ROM_START;
    func_8000086C_main(&D_800D5298_main);
    if (!(D_800D09A8_main & 1)) {
        func_80000F30_main(0);
    } else {
        func_80000F30_main(1);
    }
}
