#include "common.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PR/viint.h"

extern __OSViContext viContexts[2];
extern OSViMode osViModeMpalLan1;

void __osViInit(void) {
    bzero(viContexts, sizeof(viContexts));
    __osViCurr = &viContexts[0];
    __osViNext = &viContexts[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;
    __osViNext->framep = (void*)K0BASE;
    __osViCurr->framep = (void*)K0BASE;
    if (osTvType == OS_TV_PAL) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == OS_TV_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }
    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    while (IO_READ(VI_CURRENT_REG) > 10) {
    }
    IO_WRITE(VI_CONTROL_REG, 0);
    osViSwapContext();
}
