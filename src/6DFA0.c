/* 6DFA0: n_audio n_sndpgetstate.c (n_alSndpGetState). */
#include "2.0L/audio/n_synthInternals.h"

s32 func_8006D3A0_main(void)
{
    N_ALSoundState *sState = SNDP->sndState;

    return sState[SNDP->target].state;
}
