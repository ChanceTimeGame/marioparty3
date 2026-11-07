#include "common.h"
#include "PR/os_internal.h"
#include "piint.h"

#define PI_Q_BUF_LEN 1
extern OSMesgQueue __osPiAccessQueue;
extern u32 __osPiAccessQueueEnabled;
extern OSMesg piAccessBuf[PI_Q_BUF_LEN];

void __osPiCrateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, piAccessBuf, PI_Q_BUF_LEN);
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osPiAccessQueueEnabled)
        __osPiCrateAccessQueue();
    osRecvMesg(&__osPiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
