/* 6E6B0: n_audio n_sndpplay.c (n_alSndpPlay). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DAB0_main(void)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    if ((sState + sndp->target)->state == AL_STOPPED) {
        evt.common.type = N_AL_SNDP_PLAY_EVT;
        evt.common.state = &sState[sndp->target];
        alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
    }
}
