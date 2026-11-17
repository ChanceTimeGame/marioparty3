#include "common.h"

void func_80105B64_duel10(void);
void func_80105BA0_duel10(void);
void func_80111D0C_duel10(void);

// board ec3: the unit's .data (0x4551C0, 0x20 bytes)
OvlEntrypoint D_801149B0_duel10[] = {
    { 0, func_80105B64_duel10 },
    { 1, func_80105BA0_duel10 },
    { 2, func_80111D0C_duel10 },
    { -1, NULL },
};

void func_801059A0_duel10(void) {
    ovlEventCall(D_801149B0_duel10, omovlevtno);
}
