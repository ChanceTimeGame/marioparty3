/* 6F470: libultra audio/drvrnew.c alFxNew and audio/reverb.c alFxParamHdl (second copy), from MP3's
   own src/2.0L/audio/drvrnew.c and reverb.c (MP1 src/96AA0.c, src/972D0.c). The effect parameter
   tables are data in the data asm; the rest of the unit (no reference) stays asm. */

#include <libaudio.h>
#include "2.0L/audio/synthInternals.h"
#include <PR/n_libaudio.h>
#include "2.0L/audio/n_synthInternals.h"
#include "include_asm.h"

#define SCALE 16384

extern s32 D_800A2890_main[]; /* SMALLROOM_PARAMS */
extern s32 D_800A28F8_main[]; /* BIGROOM_PARAMS */
extern s32 D_800A2980_main[]; /* ECHO_PARAMS */
extern s32 D_800A29A8_main[]; /* CHORUS_PARAMS */
extern s32 D_800A29D0_main[]; /* FLANGE_PARAMS */
extern s32 D_800A29F8_main[]; /* NULL_PARAMS */
extern N_ALGlobals* D_800A2884_main; /* n_alGlobals: this copy is the n_audio library's */

void _init_lpfilter(ALLowPass* lp);

#define N_AL_AUX_L_OUT 1984
#define N_AL_DIVIDED 368

Acmd *func_8006A450_main(void *filter, s32 sampleOffset, Acmd *p); /* n_alEnvmixerPull */

/* n_auxbus.c */
Acmd *func_8006E870_main(s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    N_ALAuxBus *m = (N_ALAuxBus *)n_syn->auxBus;
    N_PVoice **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, N_AL_AUX_L_OUT, N_AL_DIVIDED << 1);

    for (i = 0; i < m->sourceCount; i++)
        ptr = func_8006A450_main(sources[i], sampleOffset, ptr);

    return ptr;
}

// Matches, but this unit is two source files (drvrnew-like, then reverb-like from func_8006F140_main):
// the first one's .rodata is padded to 0x10, so func_8006E910_main can be C only once the unit is split
// at ROM 0x6FD40.
#ifdef NON_MATCHING
/* This copy allocates the ALFx itself and sets up no filter or parameter handler. */
void func_8006E910_main(ALFx** fx, ALSynConfig* c, ALHeap* hp) {
    u16 i, j, k;
    s32* param = 0;
    ALDelay* d;
    ALFx* r;

    *fx = r = alHeapAlloc(hp, 1, sizeof(ALFx));
    switch (c->fxType) {
        case AL_FX_SMALLROOM: param = D_800A2890_main; break;
        case AL_FX_BIGROOM:   param = D_800A28F8_main; break;
        case AL_FX_ECHO:      param = D_800A2980_main; break;
        case AL_FX_CHORUS:    param = D_800A29A8_main; break;
        case AL_FX_FLANGE:    param = D_800A29D0_main; break;
        case AL_FX_CUSTOM:    param = c->params;  break;
        default:              param = D_800A29F8_main; break;
    }
    j = 0;
    r->section_count = param[j++];
    r->length = param[j++];
    r->delay = alHeapAlloc(hp, r->section_count, sizeof(ALDelay));
    r->base = alHeapAlloc(hp, r->length, sizeof(s16));
    r->input = r->base;
    for (k = 0; k < r->length; k++) {
        r->base[k] = 0;
    }
    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        d->input = param[j++];
        d->output = param[j++];
        d->fbcoef = param[j++];
        d->ffcoef = param[j++];
        d->gain = param[j++];
        if (param[j]) {
#define RANGE 2.0
            d->rsinc = ((((f32)param[j++]) / 1000) * RANGE) / c->outputRate;
#define CONVERT 173123.404906676
#define LENGTH (d->output - d->input)
            d->rsgain = (((f32)param[j++]) / CONVERT) * LENGTH;
            d->rsval = 1.0;
            d->rsdelta = 0.0;
            d->rs = alHeapAlloc(hp, 1, sizeof(ALResampler));
            d->rs->state = alHeapAlloc(hp, 1, sizeof(RESAMPLE_STATE));
            d->rs->delta = 0.0;
            d->rs->first = 1;
        } else {
            d->rs = 0;
            j++;
            j++;
        }
        if (param[j]) {
            d->lp = alHeapAlloc(hp, 1, sizeof(ALLowPass));
            d->lp->fstate = alHeapAlloc(hp, 1, sizeof(POLEF_STATE));
            d->lp->fc = param[j++];
            _init_lpfilter(d->lp);
        } else {
            d->lp = 0;
            j++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/6F470", func_8006E910_main);
#endif

/* n_drvrNew.c n_alPVoiceNew */
void func_8006ECFC_main(N_PVoice *mv, ALDMANew dmaNew, ALHeap *hp)
{
    mv->dc_state = alHeapAlloc(hp, 1, sizeof(ADPCM_STATE));
    mv->dc_lstate = alHeapAlloc(hp, 1, sizeof(ADPCM_STATE));
    mv->dc_dma = dmaNew(&mv->dc_dmaState);
    mv->dc_lastsam = 0;
    mv->dc_first = 1;
    mv->dc_memin = 0;

    mv->rs_state = alHeapAlloc(hp, 1, sizeof(RESAMPLE_STATE));
    mv->rs_delta = 0.0;
    mv->rs_first = 1;
    mv->rs_ratio = 1.0;
    mv->rs_upitch = 0;

    mv->em_state = alHeapAlloc(hp, 1, sizeof(ENVMIX_STATE));
    mv->em_first = 1;
    mv->em_motion = AL_STOPPED;
    mv->em_volume = 1;
    mv->em_ltgt = 1;
    mv->em_rtgt = 1;
    mv->em_cvolL = 1;
    mv->em_cvolR = 1;
    mv->em_dryamt = 0;
    mv->em_wetamt = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_delta = 0;
    mv->em_segEnd = 0;
    mv->em_pan = 0;
    mv->em_ctrlList = 0;
    mv->em_ctrlTail = 0;
}

#define N_AL_TEMP_0 0
#define N_AL_TEMP_1 368
#define N_AL_TEMP_2 736
#define N_AL_AUX_R_OUT 2352
#define N_REVERB_OUTCOUNT 184
#define UNITY_PITCH 0x8000

#define SWAP(in, out) \
    { \
        s16 t = out; \
        out = in; \
        in = t; \
    }

Acmd *func_8006F330_main(ALFx *r, ALDelay *d, s32 buff, Acmd *p);                  /* _n_loadOutputBuffer */
Acmd *func_8006F540_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p);    /* _n_loadBuffer */
Acmd *func_8006F668_main(ALFx *r, s16 *curr_ptr, s32 buff, Acmd *p);               /* __n_saveBuffer */
Acmd *func_8006F780_main(ALLowPass *lp, s32 buff, Acmd *p);                        /* __n_filterBuffer */
f32 _doModFunc(ALDelay *d, s32 count);

/* n_reverb.c n_alFxPull */
Acmd *func_8006EE30_main(s32 sampleOffset, Acmd *p)
{
    ALFx *r = (ALFx *)n_syn->auxBus->fx;
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay *d;
    Acmd *ptr;

    ptr = func_8006E870_main(sampleOffset, p);

    input = N_AL_AUX_L_OUT;
    output = N_AL_AUX_R_OUT;
    buff1 = N_AL_TEMP_0;
    buff2 = N_AL_TEMP_1;

    aMix(ptr++, 0, 0xDA83, N_AL_AUX_L_OUT, input);
    aMix(ptr++, 0, 0x5A82, N_AL_AUX_R_OUT, input);

    ptr = func_8006F668_main(r, r->input, input, ptr);

    aClearBuffer(ptr++, output, N_REVERB_OUTCOUNT << 1);

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            SWAP(buff1, buff2);
        } else {
            ptr = func_8006F540_main(r, in_ptr, buff1, N_REVERB_OUTCOUNT, ptr);
        }
        ptr = func_8006F330_main(r, d, buff2, ptr);

        if (d->ffcoef) {
            aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = func_8006F668_main(r, out_ptr, buff2, ptr);
            }
        }

        if (d->fbcoef) {
            aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = func_8006F668_main(r, in_ptr, buff1, ptr);
        }

        if (d->lp)
            ptr = func_8006F780_main(d->lp, buff2, ptr);

        if (!d->rs)
            ptr = func_8006F668_main(r, out_ptr, buff2, ptr);

        if (d->gain)
            aMix(ptr++, 0, (u16)d->gain, buff2, output);

        /* retail adds d->output here (the SDK's loop compares in_ptr against it) */
        prev_out_ptr = &r->input[d->output];
    }

    r->input += N_REVERB_OUTCOUNT;
    if (r->input > &r->base[r->length])
        r->input -= r->length;

    aDMEMMove(ptr++, output, N_AL_AUX_L_OUT, N_REVERB_OUTCOUNT << 1);

    return ptr;
}

#undef RANGE
#define RANGE 2.0
#undef CONVERT
#undef LENGTH

s32 func_8006F140_main(void *filter, s32 paramID, void *param)
{
    ALFx   *f = (ALFx *) filter;    
    s32    p = (paramID - 2) % 8; 
    s32    s = (paramID - 2) / 8;
    s32    val = *(s32*)param;

#define INPUT_PARAM         0
#define OUTPUT_PARAM        1
#define FBCOEF_PARAM        2
#define FFCOEF_PARAM        3
#define GAIN_PARAM          4
#define CHORUSRATE_PARAM    5
#define CHORUSDEPTH_PARAM   6
#define LPFILT_PARAM        7

    switch(p)
    {
        case INPUT_PARAM:
            f->delay[s].input = (u32)val & 0xFFFFFFF8;
            break;
        case OUTPUT_PARAM:
            f->delay[s].output = (u32)val & 0xFFFFFFF8;
            break;
        case FFCOEF_PARAM:
            f->delay[s].ffcoef = (s16)val;
            break;
        case FBCOEF_PARAM:
            f->delay[s].fbcoef = (s16)val;
            break;
        case GAIN_PARAM:
            f->delay[s].gain = (s16)val;
            break;
        case CHORUSRATE_PARAM:

            f->delay[s].rsinc = ((((f32)val)/1000) * RANGE)/D_800A2884_main->drvr.outputRate; 
            break;

#define CONVERT 173123.404906676
#define LENGTH  (f->delay[s].output - f->delay[s].input)

        case CHORUSDEPTH_PARAM:

            f->delay[s].rsgain = (((f32)val) / CONVERT) * LENGTH;
            break;
        case LPFILT_PARAM:
            if(f->delay[s].lp)
            {
                f->delay[s].lp->fc = (s16)val;
                _init_lpfilter(f->delay[s].lp);
            }
            break;
    }
    return 0;
}

/* _n_loadOutputBuffer */
Acmd *func_8006F330_main(ALFx *r, ALDelay *d, s32 buff, Acmd *p)
{
    Acmd *ptr = p;
    s32 ratio, count, rbuff = N_AL_TEMP_2;
    s16 *out_ptr;
    f32 fincount, fratio, delta;
    s32 ramalign = 0, length;
    s32 inCount = N_REVERB_OUTCOUNT;
    s8 tmp;

    if (d->rs) {
        length = d->output - d->input;
        delta = _doModFunc(d, inCount);
        delta /= length;
        delta = (s32)(delta * UNITY_PITCH);
        delta = delta / UNITY_PITCH;
        fratio = 1.0 - delta;
        fincount = d->rs->delta + (fratio * (f32)inCount);
        count = (s32)fincount;
        d->rs->delta = fincount - (f32)count;
        out_ptr = &r->input[-(d->output - d->rsdelta)];
        ramalign = (((s32)out_ptr & 0x7) >> 1);
        ptr = func_8006F540_main(r, out_ptr - ramalign, rbuff, count + ramalign, ptr);
        ratio = (s32)(fratio * UNITY_PITCH);
        tmp = (buff >> 8);
        n_aResample(ptr++, osVirtualToPhysical(d->rs->state), d->rs->first, ratio, rbuff + (ramalign << 1), tmp);
        d->rs->first = 0;
        d->rsdelta += count - inCount;
    } else {
        out_ptr = &r->input[-d->output];
        ptr = func_8006F540_main(r, out_ptr, buff, inCount, ptr);
    }

    return ptr;
}

/* _n_loadBuffer */
Acmd *func_8006F540_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p)
{
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base)
        curr_ptr += r->length;
    updated_ptr = curr_ptr + count;

    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;
        n_aLoadBuffer(ptr++, before_end << 1, buff, osVirtualToPhysical(curr_ptr));
        n_aLoadBuffer(ptr++, after_end << 1, buff + (before_end << 1), osVirtualToPhysical(r->base));
    } else {
        n_aLoadBuffer(ptr++, count << 1, buff, osVirtualToPhysical(curr_ptr));
    }

    return ptr;
}

/* __n_saveBuffer */
Acmd *func_8006F668_main(ALFx *r, s16 *curr_ptr, s32 buff, Acmd *p)
{
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base)
        curr_ptr += r->length;
    updated_ptr = curr_ptr + N_REVERB_OUTCOUNT;

    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;
        n_aSaveBuffer(ptr++, before_end << 1, buff, osVirtualToPhysical(curr_ptr));
        n_aSaveBuffer(ptr++, after_end << 1, buff + (before_end << 1), osVirtualToPhysical(r->base));
    } else {
        n_aSaveBuffer(ptr++, N_REVERB_OUTCOUNT << 1, buff, osVirtualToPhysical(curr_ptr));
    }

    return ptr;
}

/* __n_filterBuffer */
Acmd *func_8006F780_main(ALLowPass *lp, s32 buff, Acmd *p)
{
    Acmd *ptr = p;
    s8 t8;

    t8 = buff >> 8;
    n_aLoadADPCM(ptr++, 32, osVirtualToPhysical(lp->fcvec.fccoef));
    n_aPoleFilter(ptr++, lp->first, lp->fgain, t8, osVirtualToPhysical(lp->fstate));
    lp->first = 0;

    return ptr;
}
