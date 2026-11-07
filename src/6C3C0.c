/* 6C3C0: n_audio n_synthesizer.c (n_alSynNew, n_alAudioFrame, __n_allocParam, __n_freeParam,
   _n_collectPVoices, _n_freePVoice, _n_timeToSamplesNoRound, _n_timeToSamples, __n_nextSampleTime). */
#include "2.0L/audio/n_synthInternals.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

Acmd *func_8006E870_main(s32 sampleOffset, Acmd *p);           /* n_alAuxBusPull */
Acmd *func_8006EE30_main(s32 sampleOffset, Acmd *p);           /* n_alFxPull */
void func_8006ECFC_main(N_PVoice *mv, ALDMANew dmaNew, ALHeap *hp); /* n_alPVoiceNew */
ALFx *func_8006F980_main(s32 bus, ALSynConfig *c, ALHeap *hp);  /* n_alSynAllocFX */
Acmd *func_8006F820_main(s32 sampleOffset, Acmd *p);           /* n_alSavePull */
void func_8006BC00_main(void);
void func_8006BC60_main(N_PVoice *pvoice);
s32 func_8006BC98_main(s32 micros);
s32 func_8006BD3C_main(ALPlayer **client);

void func_8006B7C0_main(ALSynConfig *c)
{
    s32 i;
    N_PVoice *pv;
    N_PVoice *pvoices;
    ALHeap *hp = c->heap;
    ALParam *params;
    ALParam *paramPtr;

    n_syn->head = NULL;
    n_syn->n_seqp1 = NULL;
    n_syn->n_seqp2 = NULL;
    n_syn->n_sndp = NULL;
    n_syn->numPVoices = c->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = c->outputRate;
    n_syn->maxOutSamples = N_AL_MAX_RSP_SAMPLES;
    n_syn->dma = (ALDMANew)c->dmaproc;
    n_syn->sv_dramout = 0;
    n_syn->sv_first = 1;

    n_syn->auxBus = alHeapAlloc(hp, 1, sizeof(N_ALAuxBus));
    n_syn->auxBus->sourceCount = 0;
    n_syn->auxBus->maxSources = c->maxPVoices;
    n_syn->auxBus->sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));

    n_syn->mainBus = alHeapAlloc(hp, 1, sizeof(N_ALMainBus));

    if (c->fxType != AL_FX_NONE) {
        n_syn->auxBus->fx = func_8006F980_main(0, c, hp);
        n_syn->mainBus->filter.handler = func_8006EE30_main;
    } else {
        n_syn->mainBus->filter.handler = func_8006E870_main;
    }

    n_syn->pFreeList.next = 0;
    n_syn->pFreeList.prev = 0;
    n_syn->pLameList.next = 0;
    n_syn->pLameList.prev = 0;
    n_syn->pAllocList.next = 0;
    n_syn->pAllocList.prev = 0;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &n_syn->pFreeList);
        pv->vvoice = 0;
        func_8006ECFC_main(pv, n_syn->dma, hp);
        n_syn->auxBus->sources[n_syn->auxBus->sourceCount++] = pv;
    }

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    n_syn->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = n_syn->paramList;
        n_syn->paramList = paramPtr;
    }

    n_syn->heap = hp;
}

Acmd *func_8006BA3C_main(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen)
{
    ALPlayer *client;
    Acmd *cmdlEnd = cmdList;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (n_syn->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }

    for (n_syn->paramSamples = func_8006BD3C_main(&client);
         n_syn->paramSamples - n_syn->curSamples < outLen;
         n_syn->paramSamples = func_8006BD3C_main(&client)) {
        n_syn->paramSamples &= ~0xF;
        client->samplesLeft += func_8006BC98_main((*client->handler)(client));
    }
    n_syn->paramSamples &= ~0xF;

    while (outLen > 0) {
        nOut = MIN(n_syn->maxOutSamples, outLen);
        n_syn->sv_dramout = (s32)lOutBuf;
        cmdlEnd = func_8006F820_main(n_syn->curSamples, cmdlEnd);
        outLen -= nOut;
        lOutBuf += nOut << 1;
        n_syn->curSamples += nOut;
    }

    *cmdLen = (s32)(cmdlEnd - cmdList);

    func_8006BC00_main();

    return cmdlEnd;
}

ALParam *func_8006BBBC_main(void)
{
    ALParam *update = 0;

    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}

void func_8006BBE8_main(ALParam *param)
{
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

void func_8006BC00_main(void)
{
    ALLink *dl;

    while ((dl = n_syn->pLameList.next) != 0) {
        alUnlink(dl);
        alLink(dl, &n_syn->pFreeList);
    }
}

void func_8006BC60_main(N_PVoice *pvoice)
{
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &n_syn->pLameList);
}

s32 func_8006BC98_main(s32 micros)
{
    f32 tmp = ((f32)micros) * n_syn->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

s32 func_8006BCE8_main(s32 micros)
{
    return func_8006BC98_main(micros) & ~0xF;
}

s32 func_8006BD3C_main(ALPlayer **client)
{
    ALMicroTime idelta;
    ALMicroTime delta = 0x7FFFFFFF;
    ALPlayer *cl;

    *client = 0;

    if (n_syn->n_sndp != NULL) {
        idelta = n_syn->n_sndp->samplesLeft - n_syn->curSamples;
        if (idelta < delta) {
            *client = n_syn->n_sndp;
            delta = idelta;
        }
    }

    cl = n_syn->n_seqp1;
    if (cl != NULL) {
        idelta = cl->samplesLeft - n_syn->curSamples;
        if (idelta < delta) {
            *client = cl;
            delta = idelta;
        }
    }

    cl = n_syn->n_seqp2;
    if (cl != NULL) {
        if ((cl->samplesLeft - n_syn->curSamples) < delta) {
            *client = cl;
            delta = idelta;
        }
    }

    return (*client)->samplesLeft;
}
