#include "common.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

void __osSetGlobalIntMask(OSHWIntr mask) {
    register u32 saveMask = __osDisableInt();

    __OSGlobalIntMask |= mask;
    __osRestoreInt(saveMask);
}
