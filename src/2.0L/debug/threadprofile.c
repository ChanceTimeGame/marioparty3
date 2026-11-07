#include "common.h"
#include "PR/os_internal.h"
#include "../os/osthread_full.h"

extern u32 __osThprofLastTimer;
extern u32 __osThprofCount;

void osThreadProfileCallback(OSThread *osthread) {
    register u32 now_time = osGetCount();
    ThreadProf *thprof = ((OSThreadFull *)osthread)->thprof;

    thprof->time += now_time - __osThprofLastTimer;
    thprof->count++;
    __osThprofCount++;
    __osThprofLastTimer = now_time;
}
