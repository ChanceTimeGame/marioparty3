#include "common.h"
#include "PR/os_internal.h"
#include "piint.h"

OSMesgQueue* osPiGetCmdQueue() {
    if (!__osPiDevMgr.active) {
        return NULL;
    } else {
        return __osPiDevMgr.cmdQueue;
    }
}
