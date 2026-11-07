/* libultra audio/env.c + audio/reverb.c (2.0I), one unit here. The static tables (eqpower,
   L_INC) live in the data asm. */

#include <libaudio.h>
#include "synthInternals.h"
#include <os.h>



#define EQPOWER_LENGTH 128
extern s16 D_800A2C20_main[EQPOWER_LENGTH]; /* eqpower */
#define eqpower D_800A2C20_main

extern	f64	__pow(f64, f64);

static  Acmd *_pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount,
                            s32 sampleOffset, Acmd *p) ;
static  s16 _getRate(f64 vol, f64 tgt, s32 count, u16* ratel);

static  f32 _getVol(f32 ivol, s32 samples, s16 ratem, u16 ratel);

Acmd *alEnvmixerPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset,
                     Acmd *p) 
{
    Acmd        *ptr = p;
    ALEnvMixer	*e = (ALEnvMixer *)filter;
    s16         inp;
    s32         lastOffset;
    s32         thisOffset = sampleOffset;
    s32         samples;
    s16         loutp = 0;
    s32         fVol;
    ALParam     *thisParam;

    inp = AL_RESAMPLER_OUT;

    while (e->ctrlList != 0) { 
        lastOffset = thisOffset;
        thisOffset = e->ctrlList->delta;
        samples    = thisOffset - lastOffset;
        if (samples > outCount)
            break;

        switch (e->ctrlList->type) {
          case (AL_FILTER_START_VOICE_ALT):
              {                  
                  ALStartParamAlt *param = (ALStartParamAlt *)e->ctrlList;
                  ALFilter     *f = (ALFilter *) e;
                  s32 tmp;

                  if (param->unity) {
                      (*e->filter.setParam)(&e->filter,
                                            AL_FILTER_SET_UNITY_PITCH, 0);
                  }

                  (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE,
                                        param->wave);
                  (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);

                  e->first  = 1;

                  e->delta  = 0;
                  e->segEnd = param->samples;

                  tmp = ((s32)param->volume * (s32)param->volume) >> 15;
                  e->volume = (s16) tmp;
                  e->pan    = param->pan;
                  e->dryamt = eqpower[param->fxMix];
                  e->wetamt = eqpower[EQPOWER_LENGTH - param->fxMix - 1];

                  if (param->samples) {
                      e->cvolL  = 1;
                      e->cvolR  = 1;
                  } else {

                      e->cvolL = (e->volume * eqpower[e->pan]) >> 15;
                      e->cvolR = (e->volume *
                                  eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
                  }

                  if (f->source) {
                      union {
                          f32 f;
                          s32 i;
                      } data;                    
                      data.f = param->pitch;
                      (*f->source->setParam)(f->source, AL_FILTER_SET_PITCH,
                                            (void *)data.i);
                  }

              }

              break;

          case (AL_FILTER_SET_FXAMT):
          case (AL_FILTER_SET_PAN):
          case (AL_FILTER_SET_VOLUME):
	      ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);

              if (e->delta >= e->segEnd){

                  e->ltgt = (e->volume * eqpower[e->pan]) >> 15;
                  e->rtgt = (e->volume *
                             eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
                  e->delta = e->segEnd;   
                  e->cvolL = e->ltgt;
                  e->cvolR = e->rtgt;
              } else {

                  e->cvolL = _getVol(e->cvolL, e->delta, e->lratm, e->lratl);
                  e->cvolR = _getVol(e->cvolR, e->delta, e->rratm, e->rratl);
              }

              if( e->cvolL == 0 ) e->cvolL = 1;
              if( e->cvolR == 0 ) e->cvolR = 1;

              if (e->ctrlList->type == AL_FILTER_SET_PAN)

                  e->pan = (s16) e->ctrlList->data.i;

              if (e->ctrlList->type == AL_FILTER_SET_VOLUME){

                  e->delta = 0;

                  fVol = (e->ctrlList->data.i);
                  fVol = (fVol*fVol)>>15;
                  e->volume = (s16) fVol;

                  e->segEnd = e->ctrlList->moredata.i;

              }

              if (e->ctrlList->type == AL_FILTER_SET_FXAMT){
                  e->dryamt = eqpower[e->ctrlList->data.i];
                  e->wetamt = eqpower[EQPOWER_LENGTH - e->ctrlList->data.i - 1];
              }

              e->first = 1;
              break;

          case (AL_FILTER_START_VOICE):
              {
                  ALStartParam *p = (ALStartParam *)e->ctrlList;

                  if (p->unity) {
                      (*e->filter.setParam)(&e->filter,
                                            AL_FILTER_SET_UNITY_PITCH, 0);
                  }

                  (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE,
                                        p->wave);
                  (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);
              }
              break;

          case (AL_FILTER_STOP_VOICE):
              {

		  ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
		  (*e->filter.setParam)(&e->filter, AL_FILTER_RESET, 0);
              }
              break;

          case (AL_FILTER_FREE_VOICE):
              {                  
                  ALSynth *drvr = &alGlobals->drvr;
                  ALFreeParam *param = (ALFreeParam *)e->ctrlList;
                  param->pvoice->offset = 0;
                  _freePVoice(drvr, (PVoice *)param->pvoice);
              }
              break;

          default:

	      ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
              (*e->filter.setParam)(&e->filter, e->ctrlList->type,
                                    (void *) e->ctrlList->data.i);
              break;
        }
        loutp  += (samples<<1);
        outCount -= samples;

        thisParam = e->ctrlList;
        e->ctrlList = e->ctrlList->next;
        if (e->ctrlList == 0)
            e->ctrlTail = 0;

        __freeParam(thisParam);

    }

    ptr = _pullSubFrame(e, &inp, &loutp, outCount, sampleOffset, ptr);

    if (e->delta > e->segEnd)
        e->delta = e->segEnd;

    return ptr;
}

s32 alEnvmixerParam(void *filter, s32 paramID, void *param)
{
    ALFilter      *f = (ALFilter *) filter;
    ALEnvMixer	*e = (ALEnvMixer *) filter;

    switch (paramID) {

      case (AL_FILTER_ADD_UPDATE):
          if (e->ctrlTail) {
              e->ctrlTail->next = (ALParam *)param;
          } else {
              e->ctrlList = (ALParam *)param;
          }            
          e->ctrlTail = (ALParam *)param;

          break;

      case (AL_FILTER_RESET):
          e->first = 1;
          e->motion = AL_STOPPED;
          e->volume = 1;
          if (f->source)
              (*f->source->setParam)(f->source, AL_FILTER_RESET, param);
          break;

      case (AL_FILTER_START):
          e->motion = AL_PLAYING;
          if (f->source)
              (*f->source->setParam)(f->source, AL_FILTER_START, param);
          break;

      case (AL_FILTER_SET_SOURCE):
          f->source = (ALFilter *) param;
          break;

      default:
          if (f->source)
              (*f->source->setParam)(f->source, paramID, param);
    }
    return 0;
}
static Acmd* _pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount,
                    s32 sampleOffset, Acmd *p) 
{
    Acmd        *ptr = p;
    ALEnvMixer	*e = (ALEnvMixer *)filter;
    ALFilter      *source= e->filter.source;

    if (e->motion != AL_PLAYING || !outCount)
        return ptr;

    ptr = (*source->handler)(source, inp, outCount, sampleOffset, p);

    aSetBuffer(ptr++, A_MAIN, *inp, AL_MAIN_L_OUT + *outp, outCount<<1);
    aSetBuffer(ptr++, A_AUX, AL_MAIN_R_OUT + *outp, AL_AUX_L_OUT + *outp,
	       AL_AUX_R_OUT + *outp);

    if (e->first){
	e->first = 0;

        e->ltgt = (e->volume * eqpower[e->pan]) >> 15;
        e->lratm = _getRate((f64)e->cvolL, (f64)e->ltgt,
                            e->segEnd, &(e->lratl));
        e->rtgt = (e->volume *
                   eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
        e->rratm = _getRate((f64)e->cvolR, (f64)e->rtgt, e->segEnd,
                            &(e->rratl));

        aSetVolume(ptr++, A_LEFT | A_VOL, e->cvolL, 0, 0);
        aSetVolume(ptr++, A_RIGHT | A_VOL, e->cvolR, 0, 0);
	aSetVolume(ptr++, A_LEFT  | A_RATE, e->ltgt, e->lratm, e->lratl);
	aSetVolume(ptr++, A_RIGHT | A_RATE, e->rtgt, e->rratm, e->rratl);
	aSetVolume(ptr++, A_AUX, e->dryamt, 0, e->wetamt);
	aEnvMixer (ptr++, A_INIT | A_AUX, osVirtualToPhysical(e->state));
    }
    else
	aEnvMixer(ptr++, A_CONTINUE | A_AUX, osVirtualToPhysical(e->state));

    *inp += (outCount<<1);
    e->delta += outCount;

    return ptr;
}

#define EXP_MASK  0x7f800000
#define MANT_MASK 0x807fffff

f64
_frexpf(f64 value, s32 *eptr)
{
    f64 absvalue;

    *eptr = 0;
    if (value == 0.0) 
        return (value);
    absvalue = (value > 0.0) ? value : -value;
    for ( ; absvalue >= 1.0; absvalue *= 0.5)
        ++*eptr;
    for ( ; absvalue < 0.5; absvalue += absvalue)
        --*eptr;
    return (value > 0.0 ? absvalue : -absvalue);
}

f64
_ldexpf(f64 in, s32 ex)
{
    s32 exp;

    if ( ex ) {
	exp = 1 << ex;
	in *= (f64)exp;
    }

    return ( in );
}

static
s16 _getRate(f64 vol, f64 tgt, s32 count, u16* ratel)
{
    s16         s;

    f64         invn = 1.0/count, eps, a, fs, mant;
    s32         i_invn, ex, indx;

    if (count == 0){
        if (tgt >= vol){
            *ratel = 0xffff;
            return 0x7fff;
        }
        else{
            *ratel = 0;
            return 0;
        }
    }

    if (tgt < 1.0)
        tgt = 1.0;
    if (vol <= 0) vol = 1;	

#define NBITS (3)
#define NPOS  (1<<NBITS)
#define NFRACBITS (30)
#define M_LN2		0.69314718055994530942

    {
	f64 logtab[] = { -0.912537, -0.752072, -0.607683, -0.476438,
                         -0.356144, -0.245112, -0.142019, -0.045804  };

	i_invn = (s32) _ldexpf( invn, NFRACBITS );
	mant = _frexpf( tgt/vol, &ex );
	indx = (s32) (_ldexpf( mant, NBITS+1 ) ); 
	eps = (logtab[indx - NPOS] + ex) * M_LN2;
	eps /= _ldexpf( 1, NFRACBITS ); 
	fs = (1.0 + eps);
	a = 1.0;
	while( i_invn ) {
	    if( i_invn & 1 )
		a = a * fs;
	    fs *= fs;
	    i_invn >>= 1;
	}
    }

    a *= (a *= (a *= a));
    s = (s16) a;
    *ratel = (s16)(0xffff * (a - (f32) s));

    return (s16)a;

}

static
f32 _getVol(f32 ivol, s32 samples, s16 ratem, u16 ratel)
{
    f32	        r, a;
    s32	      	i;

    samples >>=3;
    if (samples == 0){
        return ivol;
    }
    r = ((f32) (ratem<<16) + (f32) ratel)/65536;

    a = 1.0;
    for (i=0; i<32; i++){
	if( samples & 1 )
	    a *= r;
        samples >>= 1;
        if (samples == 0)
            break;
	r *= r;
    }
    ivol *= a;
    return ivol;
}


