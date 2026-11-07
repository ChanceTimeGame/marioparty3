#include "synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

// alSynSetPan
void func_80078A10_main(ALSynth *synth, ALVoice *v, u8 pan) {
    ALParam *update;
    ALFilter *f;

    if (v->pvoice) {
        update = __allocParam();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        update->delta = synth->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_SET_PAN;
        update->data.i = pan;
        update->next = 0;

        f = v->pvoice->channelKnob;
        (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
    }
}
