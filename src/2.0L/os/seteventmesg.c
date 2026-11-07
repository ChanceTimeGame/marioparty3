#include "common.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

extern u32 _osPreNMI; /* MP1: __osShutdown */
extern u32 _osShutdown; /* MP1: __osPreNMI */

void osSetEventMesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
    register u32 saveMask;
    __OSEventState* es;

    saveMask = __osDisableInt();
    es = &__osEventStateTab[event];
    es->messageQueue = mq;
    es->message = msg;
    if (event == OS_EVENT_PRENMI) {
        if (_osPreNMI && !_osShutdown) {
            osSendMesg(mq, msg, OS_MESG_NOBLOCK);
        }
        _osShutdown = TRUE;
    }
    __osRestoreInt(saveMask);
}
