#include "common.h"
#include "PR/os_internal.h"
#include "PR/viint.h"

// TODO: this comes from a header

void osViBlack(u8 active) {
    register u32 saveMask = __osDisableInt();
    
    if (active) {
        __osViNext->state |= VI_STATE_BLACK;
    } else {
        __osViNext->state &= ~VI_STATE_BLACK;
    }

    __osRestoreInt(saveMask);
}
