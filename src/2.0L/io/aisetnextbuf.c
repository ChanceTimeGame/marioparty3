#include "common.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/osint.h"

extern u8 D_800A2A80_main; // hdwrBugFlag (function-local static in the library)

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    char *bptr;

    if (__osAiDeviceBusy()) {
        return -1;
    }

    bptr = bufPtr;

    if (D_800A2A80_main) {
        bptr = (u8 *)bufPtr - 0x2000;
    }

    if ((((u32)bufPtr + size) & 0x1fff) == 0) {
        D_800A2A80_main = TRUE;
    } else {
        D_800A2A80_main = FALSE;
    }

    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);

    return 0;
}
