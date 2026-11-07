/* 66E70: n_audio n_synstartvoiceparam.c (n_alSynStartVoiceParams) with Hudson's mono patch, built -O0 -g
   (as MP1/MP2 build their synstartvoiceparam.c). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>
#include <ultraerror.h>

void func_80066270_main(N_ALVoice *v, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix,
                        ALMicroTime t)
{
    ALStartParamAlt *update;

    if (v->pvoice) {
        update = (ALStartParamAlt *)func_8006BBBC_main();
        ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

        if ((s8)fxmix < 0)
            fxmix = -fxmix;

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->next = 0;
        update->type = AL_FILTER_START_VOICE_ALT;

        update->unity = v->unityPitch;
        /* MONO PATCH */
        if (D_800CB8AC_main & 1 & 0xFF) {
            update->pan = 0x40;
        } else {
            update->pan = pan;
        }
        update->volume = vol;
        update->fxMix = fxmix;
        update->pitch = pitch;
        update->samples = func_8006BCE8_main(t);
        update->wave = w;

        func_8006A9C8_main(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
