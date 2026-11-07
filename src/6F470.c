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

INCLUDE_ASM("asm/nonmatchings/6F470", func_8006EE30_main);

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

INCLUDE_ASM("asm/nonmatchings/6F470", func_8006F330_main);

INCLUDE_ASM("asm/nonmatchings/6F470", func_8006F540_main);

INCLUDE_ASM("asm/nonmatchings/6F470", func_8006F668_main);

INCLUDE_ASM("asm/nonmatchings/6F470", func_8006F780_main);
