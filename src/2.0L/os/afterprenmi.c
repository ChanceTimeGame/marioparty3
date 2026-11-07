#include "common.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

s32 osAfterPreNMI(void) {
    return __osSpSetPc(0);
}
