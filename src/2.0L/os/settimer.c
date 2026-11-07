#include "common.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

extern OSTimer *D_800A2DD0_main; // __osTimerList
extern u32 D_800D2000_main;      // __osTimerCounter

int osSetTimer(OSTimer *t, OSTime countdown, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    OSTime time;
    OSTimer *next;
    u32 count;
    u32 value;
    u32 saveMask;

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    t->value = (countdown != 0) ? countdown : interval;
    t->mq = mq;
    t->msg = msg;

    saveMask = __osDisableInt();

    if (D_800A2DD0_main->next == D_800A2DD0_main) {
    } else {
        next = D_800A2DD0_main->next;
        count = osGetCount();
        value = count - D_800D2000_main;
        if (value < next->value) {
            next->value -= value;
        } else {
            next->value = 1;
        }
    }

    time = __osInsertTimer(t);
    __osSetTimerIntr(D_800A2DD0_main->next->value);
    __osRestoreInt(saveMask);

    return 0;
}
