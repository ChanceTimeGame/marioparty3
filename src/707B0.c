/* 707B0: n_audio n_synfreevoice.c (n_alSynFreeVoice). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_8006BC60_main(N_PVoice *pvoice); /* _n_freePVoice */

void func_8006FBB0_main(N_ALVoice *voice)
{
    ALFreeParam *update;

    if (voice->pvoice) {
        if (voice->pvoice->offset) {
            update = (ALFreeParam *)func_8006BBBC_main();
            ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

            update->delta = n_syn->paramSamples + voice->pvoice->offset;
            update->type = AL_FILTER_FREE_VOICE;
            update->pvoice = (struct PVoice_s *)voice->pvoice;

            func_8006A9C8_main(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
        } else {
            func_8006BC60_main(voice->pvoice);
        }
        voice->pvoice = 0;
    }
}
