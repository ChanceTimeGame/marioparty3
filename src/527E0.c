/* libultra audio/sndplayer.c (alSndpNew and its static helpers), from MP1 src/64FD0.c;
   func_800522D4_main (_DivS32ByF32) from MP2 src/7FAE0.c, without MP1's assert.
   It calls the 2.0L/audio copies of the event and synthesizer functions, still unnamed here. */
#include "common.h"
#include "PR/sndp.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define MIN_RATIO 0.0001

typedef enum {
    AL_SNDP_PLAY_EVT,
    AL_SNDP_STOP_EVT,
    AL_SNDP_PAN_EVT,
    AL_SNDP_VOL_EVT,
    AL_SNDP_PITCH_EVT,
    AL_SNDP_API_EVT,
    AL_SNDP_DECAY_EVT,
    AL_SNDP_END_EVT,
    AL_SNDP_FX_EVT
} ALSndpMsgType;

typedef union {
    ALEvent msg;
    struct {
        s16 type;
        ALSoundState *state;
    } common;
    struct {
        s16 type;
        ALSoundState *state;
        s16 vol;
    } vol;
    struct {
        s16 type;
        ALSoundState *state;
        f32 pitch;
    } pitch;
    struct {
        s16 type;
        ALSoundState *state;
        ALPan pan;
    } pan;
    struct {
        s16 type;
        ALSoundState *state;
        u8 mix;
    } fx;
} ALSndpEvent;

/* 2.0L/audio/event */
void func_800757B0_main(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount); /* alEvtqNew */
ALMicroTime func_8007582C_main(ALEventQueue *evtq, ALEvent *evt);                    /* alEvtqNextEvent */
void func_800758C4_main(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta);        /* alEvtqPostEvent */
/* 2.0L/audio/heapalloc */
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);         /* alHeapDBAlloc */
/* 2.0L/audio synthesizer units */
void alSynFreeVoice(ALSynth *s, ALVoice *voice);                                 /* alSynFreeVoice */
s32 alSynAllocVoice(ALSynth *s, ALVoice *v, ALVoiceConfig *vc);                   /* alSynAllocVoice */
void alSynStopVoice(ALSynth *s, ALVoice *v);                                     /* alSynStopVoice */
void alSynStartVoice(ALSynth *s, ALVoice *v, ALWaveTable *w);                     /* alSynStartVoice */
void alSynSetPitch(ALSynth *s, ALVoice *v, f32 ratio);                          /* alSynSetPitch */
void alSynSetVol(ALSynth *s, ALVoice *v, s16 vol, ALMicroTime delta);         /* alSynSetVol */
void alSynSetFXMix(ALSynth *s, ALVoice *v, u8 fxmix);                           /* alSynSetFXMix */
void func_80078A10_main(ALSynth *s, ALVoice *v, ALPan pan);                          /* alSynSetPan */

ALMicroTime func_80051D20_main(void *node);
void func_80051DB4_main(ALSndPlayer *sndp, ALSndpEvent *event);
void func_8005222C_main(ALEventQueue *evtq, ALSoundState *state);
s32 func_800522D4_main(s32 i, f32 f);

void func_80051BE0_main(ALSndPlayer* sndp, ALSndpConfig* c) {
    ALEvent evt;
    ALSoundState* sState;
    u32 i;
    u8* ptr;

    sndp->maxSounds = c->maxSounds;
    sndp->target = -1;
    sndp->frameTime = AL_USEC_PER_FRAME;
    sState = alHeapDBAlloc(0, 0, c->heap, 1, c->maxSounds * sizeof(ALSoundState));
    sndp->sndState = sState;
    for (i = 0; i < c->maxSounds; i++) {
        sState[i].sound = NULL;
    }
    ptr = alHeapDBAlloc(0, 0, c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    func_800757B0_main(&sndp->evtq, (ALEventListItem*)ptr, c->maxEvents);
    sndp->drvr = &alGlobals->drvr;
    sndp->node.next = NULL;
    sndp->node.handler = func_80051D20_main;
    sndp->node.clientData = sndp;
    alSynAddPlayer(sndp->drvr, &sndp->node);
    evt.type = AL_SNDP_API_EVT;
    func_800758C4_main(&sndp->evtq, &evt, sndp->frameTime);
    sndp->nextDelta = func_8007582C_main(&sndp->evtq, &sndp->nextEvent);
}
ALMicroTime func_80051D20_main(void* node) {
    ALSndPlayer* sndp = (ALSndPlayer*)node;
    ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
        case AL_SNDP_API_EVT:
            evt.common.type = AL_SNDP_API_EVT;
            evt.common.state = (ALSoundState*)-1;
            func_800758C4_main(&sndp->evtq, (ALEvent*)&evt, sndp->frameTime);
            break;
        default:
            func_80051DB4_main(sndp, (ALSndpEvent*)&sndp->nextEvent);
            break;
        }
        sndp->nextDelta = func_8007582C_main(&sndp->evtq, &sndp->nextEvent);
    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}
void func_80051DB4_main(ALSndPlayer* sndp, ALSndpEvent* event) {
    ALVoiceConfig vc;
    ALSndpEvent evt;
    ALSound* snd;
    ALSoundState* state;
    ALVoice* voice;
    s16 vol;
    s32 decayVol;
    s16 tmp;
    s16 pan;
    s32 delta;
    f32 pitch;

    state = event->common.state;
    snd = state->sound;
    switch (event->msg.type) {
    case AL_SNDP_PLAY_EVT:
        if (state->state != AL_STOPPED || snd == NULL) {
            return;
        }
        voice = &state->voice;
        vc.fxBus = 0;
        vc.priority = state->priority;
        vc.unityPitch = 0;
        alSynAllocVoice(sndp->drvr, voice, &vc);
        vol = (snd->envelope->attackVolume * state->vol) / AL_VOL_FULL;
        tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
        tmp = MAX(tmp, AL_PAN_LEFT);
        pan = MIN(tmp, AL_PAN_RIGHT);
        pitch = state->pitch;
        delta = snd->envelope->attackTime;
        alSynStartVoice(sndp->drvr, voice, snd->wavetable);
        state->state = AL_PLAYING;
        func_80078A10_main(sndp->drvr, voice, pan);
        alSynSetVol(sndp->drvr, voice, vol, delta);
        alSynSetPitch(sndp->drvr, voice, pitch);
        alSynSetFXMix(sndp->drvr, voice, state->fxMix);
        evt.common.type = AL_SNDP_DECAY_EVT;
        evt.common.state = state;
        func_800758C4_main(&sndp->evtq, (ALEvent*)&evt, func_800522D4_main(snd->envelope->attackTime, state->pitch));
        break;
    case AL_SNDP_STOP_EVT:
        if (state->state != AL_PLAYING || snd == NULL) {
            return;
        }
        delta = func_800522D4_main(snd->envelope->releaseTime, state->pitch);
        alSynSetVol(sndp->drvr, &state->voice, 0, delta);
        if (delta) {
            evt.common.type = AL_SNDP_END_EVT;
            evt.common.state = state;
            func_800758C4_main(&sndp->evtq, (ALEvent*)&evt, delta);
            state->state = AL_STOPPING;
        } else {
            alSynStopVoice(sndp->drvr, &state->voice);
            alSynFreeVoice(sndp->drvr, &state->voice);
            func_8005222C_main(&sndp->evtq, state);
            state->state = AL_STOPPED;
        }
        break;
    case AL_SNDP_PAN_EVT:
        state->pan = event->pan.pan;
        if (state->state == AL_PLAYING && snd != NULL) {
            tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
            tmp = MAX(tmp, AL_PAN_LEFT);
            pan = MIN(tmp, AL_PAN_RIGHT);
            func_80078A10_main(sndp->drvr, &state->voice, pan);
        }
        break;
    case AL_SNDP_PITCH_EVT:
        if ((state->pitch = event->pitch.pitch) < MIN_RATIO) {
            state->pitch = MIN_RATIO;
        }
        if (state->state == AL_PLAYING) {
            alSynSetPitch(sndp->drvr, &state->voice, state->pitch);
        }
        break;
    case AL_SNDP_FX_EVT:
        state->fxMix = event->fx.mix;
        if (state->state == AL_PLAYING) {
            alSynSetFXMix(sndp->drvr, &state->voice, state->fxMix);
        }
        break;
    case AL_SNDP_VOL_EVT:
        state->vol = event->vol.vol;
        if (state->state == AL_PLAYING && snd != NULL) {
            decayVol = (snd->envelope->decayVolume * state->vol) / AL_VOL_FULL;
            alSynSetVol(sndp->drvr, &state->voice, (s16)decayVol, AL_GAIN_CHANGE_TIME);
        }
        break;
    case AL_SNDP_DECAY_EVT:
        if (snd->envelope->decayTime != -1) {
            decayVol = (snd->envelope->decayVolume * state->vol) / AL_VOL_FULL;
            delta = func_800522D4_main(snd->envelope->decayTime, state->pitch);
            alSynSetVol(sndp->drvr, &state->voice, (s16)decayVol, delta);
            evt.common.type = AL_SNDP_STOP_EVT;
            evt.common.state = state;
            func_800758C4_main(&sndp->evtq, (ALEvent*)&evt, delta);
        }
        break;
    case AL_SNDP_END_EVT:
        alSynStopVoice(sndp->drvr, &state->voice);
        alSynFreeVoice(sndp->drvr, &state->voice);
        func_8005222C_main(&sndp->evtq, state);
        state->state = AL_STOPPED;
        break;
    default:
        break;
    }
}
void func_8005222C_main(ALEventQueue* evtq, ALSoundState* state) {
    ALLink* thisNode;
    ALLink* nextNode;
    ALEventListItem* thisItem;
    ALEventListItem* nextItem;
    ALSndpEvent* thisEvent;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    thisNode = evtq->allocList.next;
    while (thisNode != NULL) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem*)thisNode;
        nextItem = (ALEventListItem*)nextNode;
        thisEvent = (ALSndpEvent*)&thisItem->evt;
        if (thisEvent->common.state == state) {
            if (nextItem != NULL) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }
    osSetIntMask(mask);
}
s32 func_800522D4_main(s32 i, f32 f) {
    f64 rd;
    s32 ri;

    rd = i / f;
    if (rd > 2147483647) {
        ri = 2147483647;
    } else {
        ri = rd;
    }
    return ri;
}
