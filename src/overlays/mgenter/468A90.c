#include "mgenter.h"

/* .data (0x46CB70) */
OvlEntrypoint D_80109A80_mgenter[] = {
    { 0, func_801059D0_mgenter },
    { 1, func_80105C60_mgenter },
    { -1, NULL },
};

void func_801059A0_mgenter(void) {
    ovlEventCall(D_80109A80_mgenter, omovlevtno);
}
