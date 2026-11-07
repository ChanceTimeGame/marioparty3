#include "common.h"
#include "PR/os_internal.h"
#include "PR/viint.h"

// TODO: this comes from a header

void osViSetMode(OSViMode *modep) {
    register u32 saveMask = __osDisableInt();

    __osViNext->modep = modep;
    __osViNext->state = VI_STATE_01;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
