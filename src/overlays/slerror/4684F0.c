#include "common.h"

void func_80105E9C_slerror(void);
void func_80105EDC_slerror(void);

/* .data */
OvlEntrypoint D_80105F20_slerror[] = {
    { 0, func_80105E9C_slerror },
    { 1, func_80105EDC_slerror },
    { -1, NULL },
};

void func_801059A0_slerror(void) {
    ovlEventCall(D_80105F20_slerror, omovlevtno);
}
