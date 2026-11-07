/* 6E8E0: n_audio n_sndpstop.c (n_alSndpStop). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DCE0_main(void)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    evt.common.type = N_AL_SNDP_STOP_EVT;
    evt.common.state = &sState[sndp->target];
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}
