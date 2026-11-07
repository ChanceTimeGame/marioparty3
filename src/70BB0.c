/* 70BB0: n_audio n_synstopvoice.c (n_alSynStopVoice). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_8006FFB0_main(N_ALVoice *v)
{
    ALParam *update;

    if (v->pvoice) {
        update = func_8006BBBC_main();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_STOP_VOICE;
        update->next = 0;

        func_8006A9C8_main(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
