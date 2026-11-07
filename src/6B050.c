/* 6B050: n_audio n_env.c (n_alEnvmixerPull, n_alEnvmixerParam, __n_pullSubFrame, __n_getRate,
   __n_getVol). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>

#define EQPOWER_LENGTH 128
extern s16 D_800A2780_main[EQPOWER_LENGTH]; /* eqpower */
#define eqpower D_800A2780_main

Acmd *func_8006AA6C_main(void *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p);
s16 func_8006AC8C_main(f64 vol, f64 tgt, s32 count, u16 *ratel);
s16 func_8006ADCC_main(s16 ivol, s32 samples, s16 ratem, u16 ratel);
Acmd *func_8006B540_main(void *filter, s16 *outp, Acmd *p); /* n_alResamplePull */
s32 func_8006B268_main(void *filter, s32 paramID, void *param); /* n_alLoadParam */
void func_8006BC60_main(N_PVoice *pvoice); /* _n_freePVoice */

Acmd *func_8006A450_main(void *filter, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    N_PVoice *e = (N_PVoice *)filter;
    s16 inp;
    s16 loutp;
    s32 lastOffset;
    s32 thisOffset = sampleOffset;
    s32 samples;
    s32 outCount = N_AL_MAX_RSP_SAMPLES;
    ALParam *thisParam;

    loutp = 0;
    inp = 0;

    while (e->em_ctrlList != 0) {
        lastOffset = thisOffset;
        thisOffset = e->em_ctrlList->delta;
        samples = SAMPLE184(thisOffset - lastOffset);
        if (samples == 0)
            thisOffset = lastOffset;
        if (samples > outCount)
            break;

        switch (e->em_ctrlList->type) {
            case AL_FILTER_START_VOICE_ALT:
            {
                ALStartParamAlt *param = (ALStartParamAlt *)e->em_ctrlList;

                if (param->unity) {
                    e->rs_upitch = 1;
                }
                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, param->wave);
                e->em_motion = AL_PLAYING;
                e->em_first = 1;
                e->em_delta = 0;
                e->em_segEnd = SAMPLE184(param->samples);
                e->em_volume = SQR(param->volume) >> 15;
                e->em_pan = param->pan;
                e->em_dryamt = eqpower[param->fxMix];
                e->em_wetamt = eqpower[EQPOWER_LENGTH - param->fxMix - 1];

                if (param->samples) {
                    e->em_cvolL = 1;
                    e->em_cvolR = 1;
                } else {
                    e->em_cvolL = (e->em_volume * eqpower[e->em_pan]) >> 15;
                    e->em_cvolR = (e->em_volume * eqpower[EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
                }
                e->rs_ratio = param->pitch;
            }
            break;

            case AL_FILTER_SET_FXAMT:
            case AL_FILTER_SET_PAN:
            case AL_FILTER_SET_VOLUME:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);

                if (e->em_delta >= e->em_segEnd) {
                    e->em_ltgt = (e->em_volume * eqpower[e->em_pan]) >> 15;
                    e->em_rtgt = (e->em_volume * eqpower[EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
                    e->em_delta = e->em_segEnd;
                    e->em_cvolL = e->em_ltgt;
                    e->em_cvolR = e->em_rtgt;
                } else {
                    e->em_cvolL = func_8006ADCC_main(e->em_cvolL, e->em_delta, e->em_lratm, e->em_lratl);
                    e->em_cvolR = func_8006ADCC_main(e->em_cvolR, e->em_delta, e->em_rratm, e->em_rratl);
                }

                if (e->em_cvolL == 0)
                    e->em_cvolL = 1;
                if (e->em_cvolR == 0)
                    e->em_cvolR = 1;

                if (e->em_ctrlList->type == AL_FILTER_SET_PAN)
                    e->em_pan = (s16)e->em_ctrlList->data.i;

                if (e->em_ctrlList->type == AL_FILTER_SET_VOLUME) {
                    e->em_delta = 0;
                    e->em_volume = SQR(e->em_ctrlList->data.i) >> 15;
                    e->em_segEnd = SAMPLE184(e->em_ctrlList->moredata.i);
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_FXAMT) {
                    e->em_dryamt = eqpower[e->em_ctrlList->data.i];
                    e->em_wetamt = eqpower[EQPOWER_LENGTH - e->em_ctrlList->data.i - 1];
                }

                e->em_first = 1;
                break;

            case AL_FILTER_START_VOICE:
            {
                ALStartParam *param = (ALStartParam *)e->em_ctrlList;

                if (param->unity) {
                    e->rs_upitch = 1;
                }
                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, param->wave);
                e->em_motion = AL_PLAYING;
            }
            break;

            case AL_FILTER_STOP_VOICE:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006A9C8_main(e, AL_FILTER_RESET, 0);
                break;

            case AL_FILTER_FREE_VOICE:
            {
                ALFreeParam *param = (ALFreeParam *)e->em_ctrlList;
                ((N_PVoice *)param->pvoice)->offset = 0;
                func_8006BC60_main((N_PVoice *)param->pvoice);
            }
            break;

            case AL_FILTER_SET_PITCH:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                e->rs_ratio = e->em_ctrlList->data.f;
                break;

            case AL_FILTER_SET_UNITY_PITCH:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                e->rs_upitch = 1;
                break;

            case AL_FILTER_SET_WAVETABLE:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, (void *)e->em_ctrlList->data.i);
                break;

            default:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006A9C8_main(e, e->em_ctrlList->type, (void *)e->em_ctrlList->data.i);
                break;
        }
        loutp += (samples << 1);
        outCount -= samples;

        thisParam = e->em_ctrlList;
        e->em_ctrlList = e->em_ctrlList->next;
        if (e->em_ctrlList == 0)
            e->em_ctrlTail = 0;

        func_8006BBE8_main(thisParam);
    }

    ptr = func_8006AA6C_main(e, &inp, &loutp, outCount, ptr);

    if (e->em_delta > e->em_segEnd)
        e->em_delta = e->em_segEnd;

    return ptr;
}

s32 func_8006A9C8_main(N_PVoice *filter, s32 paramID, void *param)
{
    N_PVoice *e = filter;

    switch (paramID) {
        case AL_FILTER_ADD_UPDATE:
            if (e->em_ctrlTail) {
                e->em_ctrlTail->next = (ALParam *)param;
            } else {
                e->em_ctrlList = (ALParam *)param;
            }
            e->em_ctrlTail = (ALParam *)param;
            break;

        case AL_FILTER_RESET:
            e->em_first = 1;
            e->em_motion = AL_STOPPED;
            e->em_volume = 1;
            e->em_segEnd = 0;
            e->rs_delta = 0.0f;
            e->rs_first = 1;
            e->rs_upitch = 0;
            func_8006B268_main(e, AL_FILTER_RESET, param);
            break;

        case AL_FILTER_START:
            e->em_motion = AL_PLAYING;
            break;

        default:
            func_8006B268_main(e, paramID, param);
            break;
    }
    return 0;
}

Acmd *func_8006AA6C_main(void *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p)
{
    Acmd *ptr = p;
    N_PVoice *e = (N_PVoice *)filter;

    if ((e->em_motion != AL_PLAYING) | (outCount == 0))
        return ptr;

    ptr = func_8006B540_main(e, inp, ptr);

    if (e->em_first) {
        e->em_first = 0;

        e->em_ltgt = (e->em_volume * eqpower[e->em_pan]) >> 15;
        e->em_lratm = func_8006AC8C_main(e->em_cvolL, e->em_ltgt, e->em_segEnd, &e->em_lratl);
        e->em_rtgt = (e->em_volume * eqpower[EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
        e->em_rratm = func_8006AC8C_main(e->em_cvolR, e->em_rtgt, e->em_segEnd, &e->em_rratl);

        n_aSetVolume(ptr++, A_RATE, e->em_ltgt, e->em_lratm, e->em_lratl);
        n_aSetVolume(ptr++, A_LEFT | A_VOL, e->em_cvolL, e->em_dryamt, e->em_wetamt);
        n_aSetVolume(ptr++, A_RIGHT | A_VOL, e->em_rtgt, e->em_rratm, e->em_rratl);
        n_aEnvMixer(ptr++, A_INIT | A_NOAUX, e->em_cvolR, osVirtualToPhysical(e->em_state));
    } else {
        n_aEnvMixer(ptr++, A_CONTINUE | A_NOAUX, 0, osVirtualToPhysical(e->em_state));
    }

    *inp += FIXED_SAMPLE << 1;
    e->em_delta += FIXED_SAMPLE;

    return ptr;
}

s16 func_8006AC8C_main(f64 vol, f64 tgt, s32 count, u16 *ratel)
{
    s16 s;
    s16 tmp;
    f64 invn;
    f64 a;
    f64 f;

    if (count == 0) {
        if (tgt >= vol) {
            *ratel = 0xFFFF;
            return 0x7FFF;
        } else {
            *ratel = 0;
            return -0x8000;
        }
    }

    invn = 1.0 / count;

    if (tgt < 1.0)
        tgt = 1.0;
    if (vol <= 0.0)
        vol = 1.0;

    a = (tgt - vol) * invn * 8.0;
    s = a;
    f = a - s;
    s--;
    f += 1.0;
    tmp = f;
    s += tmp;
    f -= tmp;

    *ratel = 65535.0 * f;

    return s;
}

s16 func_8006ADCC_main(s16 ivol, s32 samples, s16 ratem, u16 ratel)
{
    s32 m;

    samples >>= 3;
    if (samples == 0) {
        return ivol;
    }
    m = ((ratel * samples) >> 16) + (ratem * samples);
    return ivol + m;
}
