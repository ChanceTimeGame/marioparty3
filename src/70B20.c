/* 70B20: n_audio n_synstartvoice.c (n_alSynStartVoice). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_8006FF20_main(N_ALVoice *v, ALWaveTable *table)
{
    ALStartParam *update;

    if (v->pvoice) {
        update = (ALStartParam *)func_8006BBBC_main();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_START_VOICE;
        update->wave = table;
        update->next = 0;
        update->unity = v->unityPitch;

        func_8006A9C8_main(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
