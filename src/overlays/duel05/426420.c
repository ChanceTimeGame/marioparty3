#include "common.h"

void func_80105B64_duel05(void);
void func_80105BA0_duel05(void);
void func_8010DA94_duel05(void);
void func_8010DB10_duel05(void);

// board dc3: the unit's .data (0x436100, 0x30 bytes with the section padding)
OvlEntrypoint D_80115680_duel05[] = {
    { 0, func_80105B64_duel05 },
    { 1, func_80105BA0_duel05 },
    { 2, func_8010DA94_duel05 },
    { 3, func_8010DB10_duel05 },
    { -1, NULL },
};

void func_801059A0_duel05(void) {
    ovlEventCall(D_80115680_duel05, omovlevtno);
}
