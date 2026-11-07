#include "common.h"
#include "PR/os_internal.h"
#include "piint.h"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register u32 stat;
    register u32 domain;

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);
    return 0;
}
