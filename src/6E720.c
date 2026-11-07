/* 6E720: n_audio sound player API (n_alSndpSetFXMix). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DB20_main(u8 arg)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    evt.fx.type = N_AL_SNDP_FX_EVT;
    evt.fx.state = &sState[sndp->target];
    evt.fx.mix = arg;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}
