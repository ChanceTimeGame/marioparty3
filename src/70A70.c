/* 70A70: n_audio n_synsetvol.c (n_alSynSetVol). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_8006FE70_main(N_ALVoice *v, s16 volume, ALMicroTime t)
{
    ALParam *update;

    if (v->pvoice) {
        update = func_8006BBBC_main();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_SET_VOLUME;
        update->data.i = volume;
        update->moredata.i = func_8006BCE8_main(t);
        update->next = 0;

        func_8006A9C8_main(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
