#include "common.h"
#include "ovl_81.h"

// duel n1: Duel Mode's copy of ovl_80 EE3B0 (debug print and a button-sequence watcher)

extern s32 fontcolor;

typedef struct DuelPadSeq {
    /* 0x00 */ Process *process;
    /* 0x04 */ u16 *seq;
    /* 0x08 */ s16 pos; /* -1: the sequence was entered */
} DuelPadSeq; // sizeof 0x0C

void func_800D9DD0_name_81(u16 arg0, u16 arg1, char *arg2, u8 arg3, u8 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_800D9E50_name_81(void) {
    DuelPadSeq *work;

    work = HuPrcCurrentGet()->user_data;

    for (;; HuPrcVSleep()) {
        if (*D_800D5558_main == 0) {
            continue;
        } else if (*D_800D5558_main != work->seq[work->pos]) {
            work->pos = 0;
            continue;
        } else if (work->seq[++work->pos] == 0) {
            work->pos = -1;
            break;
        }
    }

    while (1) {
        HuPrcVSleep();
    }
}

void func_800D9EFC_name_81(u16 *arg0) {
    Process *process;
    DuelPadSeq *work;

    process = omAddPrcObj(func_800D9E50_name_81, 0xEFFF, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(DuelPadSeq));
    process->user_data = work;
    work->seq = arg0;
    work->pos = 0;
    work->process = process;
}

void func_800D9F5C_name_81(DuelPadSeq *arg0) {
    omDelPrcObj(arg0->process);
}

s32 func_800D9F78_name_81(DuelPadSeq *arg0) {
    if (~arg0->pos) {
        return 0;
    } else {
        return 1;
    }
}
