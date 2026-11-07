/* 67000: n_audio n_synsetpan.c (n_alSynSetPan) with Hudson's mono patch, built -O0 -g. */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_80066400_main(N_ALVoice *v, u8 pan)
{
    ALParam *update;

    if (v->pvoice) {
        update = func_8006BBBC_main();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_SET_PAN;
        /* MONO PATCH */
        if (D_800CB8AC_main & 1 & 0xFF) {
            update->data.i = 0x40;
        } else {
            update->data.i = pan;
        }
        update->next = 0;

        func_8006A9C8_main(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
