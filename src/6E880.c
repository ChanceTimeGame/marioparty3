/* 6E880: n_audio sound player API (n_alSndpSetVol). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DC80_main(s16 arg)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    evt.vol.type = N_AL_SNDP_VOL_EVT;
    evt.vol.state = &sState[sndp->target];
    evt.vol.vol = arg;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}
