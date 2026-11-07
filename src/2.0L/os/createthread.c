#include "common.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/osint.h"
#include "osthread_full.h"

extern ThreadProf D_800D55E0_main[]; // thprof
extern void D_80080930_main(void);            // __osCleanupThread

#define THPROF_IDMAX 64

#define T(x) ((OSThreadFull *)(x))

void osCreateThread(OSThread *t, OSId id, void (*entry)(void *), void *arg, void *sp, OSPri p) {
    register u32 saveMask;
    OSIntMask mask;

    T(t)->id = id;
    T(t)->priority = p;
    T(t)->next = NULL;
    T(t)->queue = NULL;
    T(t)->context.pc = (u32)entry;
    T(t)->context.a0 = (s64)(s32)arg;
    T(t)->context.sp = (s64)(s32)sp - 16;
    T(t)->context.ra = (s64)(s32)D_80080930_main;
    mask = OS_IM_ALL;
    T(t)->context.sr = (mask & (SR_IMASK | SR_IE)) | SR_EXL;
    T(t)->context.rcp = (mask & RCP_IMASK) >> RCP_IMASKSHIFT;
    T(t)->context.fpcsr = FPCSR_FS | FPCSR_EV | FPCSR_RM_RN;
    T(t)->fp = 0;
    T(t)->state = OS_STATE_STOPPED;
    T(t)->flags = 0;

    if (id < THPROF_IDMAX) {
        T(t)->thprof = &D_800D55E0_main[id];
    } else {
        T(t)->thprof = &D_800D55E0_main[THPROF_IDMAX - 1];
    }

    saveMask = __osDisableInt();
    T(t)->tlnext = (OSThreadFull *)__osActiveQueue;
    __osActiveQueue = t;
    __osRestoreInt(saveMask);
}
