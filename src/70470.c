/* 70470: n_audio n_synaddplayer.c (n_alSynAddPlayer, n_alSynAddSndPlayer, n_alSynAddSeqPlayer),
   n_synallocfx.c (n_alSynAllocFX) and n_synallocvoice.c (n_alSynAllocVoice, _n_allocatePVoice). */
#include "2.0L/audio/n_synthInternals.h"
#include <os.h>

void func_8006E910_main(ALFx **fx, ALSynConfig *c, ALHeap *hp); /* n_alFxNew */
s32 func_8006FAE8_main(N_PVoice **pvoice, s16 priority);

void func_8006F870_main(ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->samplesLeft = n_syn->curSamples;

    client->next = n_syn->head;
    n_syn->head = client;

    osSetIntMask(mask);
}

void func_8006F8BC_main(ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->samplesLeft = n_syn->curSamples;

    client->next = n_syn->head;
    n_syn->head = client;

    if (!(n_syn->n_sndp))
        n_syn->n_sndp = client;

    osSetIntMask(mask);
}

void func_8006F914_main(ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->samplesLeft = n_syn->curSamples;

    client->next = n_syn->head;
    n_syn->head = client;

    if (n_syn->n_seqp1 == 0) {
        n_syn->n_seqp1 = client;
    } else if (n_syn->n_seqp2 == 0) {
        n_syn->n_seqp2 = client;
    }

    osSetIntMask(mask);
}

ALFx *func_8006F980_main(s16 bus, ALSynConfig *c, ALHeap *hp)
{
    func_8006E910_main(&n_syn->auxBus->fx_array[bus], c, hp);
    return n_syn->auxBus->fx_array[bus];
}

s32 func_8006F9D0_main(N_ALVoice *voice, ALVoiceConfig *vc)
{
    N_PVoice *pvoice = 0;
    ALParam *update;
    s32 stolen;

    voice->priority = vc->priority;
    voice->unityPitch = vc->unityPitch;
    voice->table = 0;
    voice->fxBus = vc->fxBus;
    voice->state = AL_STOPPED;
    voice->pvoice = 0;

    stolen = func_8006FAE8_main(&pvoice, vc->priority);

    if (pvoice) {
        if (stolen) {
            pvoice->offset = 552;
            pvoice->vvoice->pvoice = 0;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;

            update = func_8006BBBC_main();
            update->delta = n_syn->paramSamples;
            update->type = AL_FILTER_SET_VOLUME;
            update->data.i = 0;
            update->moredata.i = 368;
            func_8006A9C8_main(voice->pvoice, AL_FILTER_ADD_UPDATE, update);

            update = func_8006BBBC_main();
            if (update) {
                update->delta = n_syn->paramSamples + pvoice->offset;
                update->type = AL_FILTER_STOP_VOICE;
                update->next = 0;
                func_8006A9C8_main(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            }
        } else {
            pvoice->offset = 0;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;
        }
    }

    return (pvoice != 0);
}

s32 func_8006FAE8_main(N_PVoice **pvoice, s16 priority)
{
    ALLink *dl;
    N_PVoice *pv;
    s32 stolen = 0;

    if ((dl = n_syn->pLameList.next) != 0) {
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else if ((dl = n_syn->pFreeList.next) != 0) {
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else {
        for (dl = n_syn->pAllocList.next; dl != 0; dl = dl->next) {
            pv = (N_PVoice *)dl;
            if ((pv->vvoice->priority <= priority) && (pv->offset == 0)) {
                *pvoice = pv;
                priority = pv->vvoice->priority;
                stolen = 1;
            }
        }
    }
    return stolen;
}
