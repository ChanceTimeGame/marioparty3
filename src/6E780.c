/* 6E780: n_audio sound player API (n_alSndpSetPan). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DB80_main(ALPan arg)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    evt.pan.type = N_AL_SNDP_PAN_EVT;
    evt.pan.pan = arg;
    evt.pan.state = &sState[sndp->target];
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}
