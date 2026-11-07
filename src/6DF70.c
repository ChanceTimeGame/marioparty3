/* 6DF70: n_audio n_sndpdelete.c (n_alSndpDelete). */
#include "2.0L/audio/n_synthInternals.h"

void func_8006D370_main(void)
{
    /* alSynRemovePlayer (0x8006FC50) is n_alSynRemovePlayer(ALPlayer *); libaudio.h declares it
       with an ALSynth * parameter. */
    alSynRemovePlayer((ALSynth *)&SNDP->node);
}
