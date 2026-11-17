#include "common.h"

extern s16 omovlevtno;
extern OvlEntrypoint D_80115680_duel05[]; /* the overlay's event table (.data, still asm) */

void func_801059A0_duel05(void) {
    ovlEventCall(D_80115680_duel05, omovlevtno);
}
