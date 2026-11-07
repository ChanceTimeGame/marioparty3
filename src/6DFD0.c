/* 6DFD0: n_audio n_sndplayer.c (n_alSndpNew, _n_sndpVoiceHandler, _n_handleEvent, _n_removeEvents,
   _DivS32ByF32). */
#include "2.0L/audio/n_synthInternals.h"
#include <os.h>

#define MIN_RATIO 0.0001

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

ALMicroTime func_8006D4E8_main(void *node);
void func_8006D578_main(N_ALSndpEvent *event);
void func_8006D9B0_main(ALEventQueue *evtq, N_ALSoundState *state);
s32 func_8006DA58_main(s32 i, f32 f);

void func_8006D3D0_main(N_ALSndPlayer *sndp, ALSndpConfig *c)
{
    u32 i;
    N_ALEvent evt;
    N_ALSoundState *sState;
    ALEventListItem *items;

    sndp->maxSounds = c->maxSounds;
    sndp->target = -1;
    sndp->frameTime = 16000;
    sState = alHeapAlloc(c->heap, 1, c->maxSounds * sizeof(N_ALSoundState));
    sndp->sndState = sState;

    for (i = 0; i < c->maxSounds; i++)
        sState[i].sound = 0;

    items = alHeapAlloc(c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&sndp->evtq, items, c->maxEvents);

    sndp->node.next = NULL;
    sndp->node.handler = func_8006D4E8_main;
    sndp->node.clientData = sndp;
    func_8006F8BC_main(&sndp->node);

    evt.type = N_AL_SNDP_API_EVT;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
    sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, (ALEvent *)&sndp->nextEvent);
}

ALMicroTime func_8006D4E8_main(void *node)
{
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)node;
    N_ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case N_AL_SNDP_API_EVT:
                evt.common.type = N_AL_SNDP_API_EVT;
                evt.common.state = (N_ALSoundState *)-1;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;

            default:
                func_8006D578_main((N_ALSndpEvent *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, (ALEvent *)&sndp->nextEvent);
    } while (sndp->nextDelta == 0);

    sndp->curTime += sndp->nextDelta;

    return sndp->nextDelta;
}

void func_8006D578_main(N_ALSndpEvent *event)
{
    ALVoiceConfig vc;
    ALSound *snd;
    N_ALVoice *voice;
    ALPan pan;
    f32 pitch;
    N_ALSndpEvent evt;
    ALMicroTime delta;
    s16 vol;
    s16 tmp;
    s32 vtmp;
    N_ALSoundState *state;
    N_ALSndPlayer *sndp = SNDP;

    state = event->common.state;
    snd = state->sound;

    switch (event->msg.type) {
        case N_AL_SNDP_PLAY_EVT:
            if (state->state != AL_STOPPED || !snd)
                return;
            vc.fxBus = 0;
            vc.priority = state->priority;
            vc.unityPitch = 0;
            voice = &state->voice;
            func_8006F9D0_main(voice, &vc);
            vol = (s16)((s32)snd->envelope->attackVolume * state->vol / AL_VOL_FULL);
            tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
            tmp = MAX(tmp, AL_PAN_LEFT);
            pan = (ALPan)MIN(tmp, AL_PAN_RIGHT);
            pitch = state->pitch;
            delta = func_8006DA58_main(snd->envelope->attackTime, pitch);
            func_8006FF20_main(voice, snd->wavetable);
            state->state = AL_PLAYING;
            func_80066400_main(voice, pan);
            func_8006FE70_main(voice, vol, delta);
            func_8006FDE0_main(voice, pitch);
            func_8006FD40_main(voice, state->fxMix);
            evt.common.type = N_AL_SNDP_DECAY_EVT;
            evt.common.state = state;
            delta = func_8006DA58_main(snd->envelope->attackTime, state->pitch);
            alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            break;

        case N_AL_SNDP_STOP_EVT:
            if (state->state != AL_PLAYING || !snd)
                return;
            delta = func_8006DA58_main(snd->envelope->releaseTime, state->pitch);
            func_8006FE70_main(&state->voice, 0, delta);
            if (delta) {
                evt.common.type = N_AL_SNDP_END_EVT;
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
                state->state = AL_STOPPING;
            } else {
                func_8006FFB0_main(&state->voice);
                func_8006FBB0_main(&state->voice);
                func_8006D9B0_main(&sndp->evtq, state);
                state->state = AL_STOPPED;
            }
            break;

        case N_AL_SNDP_PAN_EVT:
            state->pan = event->pan.pan;
            if (state->state == AL_PLAYING && snd) {
                tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
                tmp = MAX(tmp, AL_PAN_LEFT);
                pan = (ALPan)MIN(tmp, AL_PAN_RIGHT);
                func_80066400_main(&state->voice, pan);
            }
            break;

        case N_AL_SNDP_PITCH_EVT:
            if ((state->pitch = event->pitch.pitch) < MIN_RATIO)
                state->pitch = MIN_RATIO;
            if (state->state == AL_PLAYING) {
                func_8006FDE0_main(&state->voice, state->pitch);
            }
            break;

        case N_AL_SNDP_FX_EVT:
            state->fxMix = event->fx.mix;
            if (state->state == AL_PLAYING)
                func_8006FD40_main(&state->voice, state->fxMix);
            break;

        case N_AL_SNDP_VOL_EVT:
            state->vol = event->vol.vol;
            if (state->state == AL_PLAYING && snd) {
                vtmp = snd->envelope->decayVolume * state->vol / AL_VOL_FULL;
                func_8006FE70_main(&state->voice, (s16)vtmp, 1000);
            }
            break;

        case N_AL_SNDP_DECAY_EVT:
            if (snd->envelope->decayTime != -1) {
                vtmp = snd->envelope->decayVolume * state->vol / AL_VOL_FULL;
                delta = func_8006DA58_main(snd->envelope->decayTime, state->pitch);
                func_8006FE70_main(&state->voice, (s16)vtmp, delta);
                evt.common.type = N_AL_SNDP_STOP_EVT;
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            }
            break;

        case N_AL_SNDP_END_EVT:
            func_8006FFB0_main(&state->voice);
            func_8006FBB0_main(&state->voice);
            func_8006D9B0_main(&sndp->evtq, state);
            state->state = AL_STOPPED;
            break;

        default:
            break;
    }
}

void func_8006D9B0_main(ALEventQueue *evtq, N_ALSoundState *state)
{
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    N_ALSndpEvent *thisEvent;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (N_ALSndpEvent *)&thisItem->evt;
        if (thisEvent->common.state == state) {
            if (nextItem)
                nextItem->delta += thisItem->delta;
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }
    osSetIntMask(mask);
}

s32 func_8006DA58_main(s32 i, f32 f)
{
#define INT_MAX 2147483647
    f64 rd;
    int ri;

    rd = i / f;
    if (rd > INT_MAX)
        ri = INT_MAX;
    else
        ri = rd;
    return ri;
}
