/* 6E840: n_audio n_sndpsetpriority.c (n_alSndpSetPriority). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DC40_main(ALSndId id, u8 priority)
{
    N_ALSoundState *sState = SNDP->sndState;

    sState[id].priority = priority;
}
