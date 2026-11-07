/* 6E7E0: n_audio sound player API (n_alSndpSetPitch). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006DBE0_main(f32 arg)
{
    N_ALSndpEvent evt;
    N_ALSndPlayer *sndp = SNDP;
    N_ALSoundState *sState = sndp->sndState;

    evt.pitch.type = N_AL_SNDP_PITCH_EVT;
    evt.pitch.state = &sState[sndp->target];
    evt.pitch.pitch = arg;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}
