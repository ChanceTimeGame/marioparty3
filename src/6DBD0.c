#include "common.h"
#include "PR/libaudio.h"

/* Wrapper around alSynRemovePlayer; the shape of MP1's func_800F7310_PaddleBattle
   (src/overlays/ovl_33_PaddleBattle/2341E0.c). */
void func_8006CFD0_main(ALSynth *s) {
    alSynRemovePlayer(s);
}
