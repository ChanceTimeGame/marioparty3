/* 6BA20: libultra audio/load.c (second copy: alAdpcmPull, alLoadParam, _decodeChunk), from MP3's
   own src/2.0L/audio/load.c (MP1 src/lib/2.0I/audio/load.c). This copy's alLoadParam sets no
   handler and copies the loop state with bcopy. */
#include <libaudio.h>
#include "2.0L/audio/synthInternals.h"
#include <os.h>
#include <R4300.h>
#include "include_asm.h"

/* This copy's load filter: a 0xC-byte filter header instead of ALFilter (0x14). */
typedef struct {
    /* 0x00 */ char filter[0xC];
    /* 0x0C */ ADPCM_STATE *state;
    /* 0x10 */ ADPCM_STATE *lstate;
    /* 0x14 */ ALRawLoop loop;
    /* 0x20 */ struct ALWaveTable_s *table;
    /* 0x24 */ s32 bookSize;
    /* 0x28 */ ALDMAproc dma;
    /* 0x2C */ void *dmaState;
    /* 0x30 */ s32 sample;
    /* 0x34 */ s32 lastsam;
    /* 0x38 */ s32 first;
    /* 0x3C */ s32 memin;
} HuLoadFilter; /* size = 0x40 */

#ifndef MIN
#   define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#define ADPCMFBYTES      9
#define LFSAMPLES        4

Acmd *func_8006B3F4_main(Acmd *ptr, HuLoadFilter *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags);
void bcopy(const void *src, void *dst, int len);

/* This copy takes no sampleOffset. */
Acmd *func_8006AE20_main(void *filter, s16 *outp, s32 outCount, Acmd *p) 
{
    Acmd        *ptr = p;
    s16         inp;
    s32         tsam;
    s32         nframes;
    s32         nbytes;
    s32         overFlow;
    s32         startZero;
    s32         nOver;
    s32         nSam;
    s32         op;
    s32         nLeft;
    s32         bEnd;
    s32         decoded = 0;
    s32         looped = 0;
    
    HuLoadFilter *f = (HuLoadFilter *)filter;

#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    if (outCount == 0)
        return ptr;

    inp = AL_DECODER_IN;
    aLoadADPCM(ptr++, f->bookSize,
               K0_TO_PHYS(f->table->waveInfo.adpcmWave.book->book));

    looped = (outCount + f->sample > f->loop.end) && (f->loop.count != 0);
    if (looped)
        nSam = f->loop.end - f->sample;
    else
        nSam = outCount;
    
    if (f->lastsam)
        nLeft = ADPCMFSIZE - f->lastsam;
    else
        nLeft = 0;
    tsam = nSam - nLeft;
    if (tsam<0) tsam = 0;
    
    nframes = (tsam+ADPCMFSIZE-1)>>LFSAMPLES;
    nbytes =  nframes*ADPCMFBYTES;

    if (looped){

        ptr = func_8006B3F4_main(ptr, f, tsam, nbytes, *outp, inp, f->first);

        /*
         * Fix up output pointer, which will be used as the input pointer
         * by the following module.
         */
        if (f->lastsam)
            *outp += (f->lastsam<<1);
        else
            *outp += (ADPCMFSIZE<<1);

        /*
         * Now fix up state info to reflect the loop start point
         */
        f->lastsam = f->loop.start &0xf;
        f->memin = (s32) f->table->base + ADPCMFBYTES *
            ((s32) (f->loop.start>>LFSAMPLES) + 1);
        f->sample = f->loop.start;

        bEnd = *outp;
        while (outCount > nSam){
            
            outCount -= nSam;
            
            /*
             * Put next one after the end of the last lot - on the
             * frame boundary (32 byte) after the end.
             */
            op = (bEnd + ((nframes+1)<<(LFSAMPLES+1)) + 16) & ~0x1f;

            /*
             * The actual end of data
             */
            bEnd += (nSam<<1);
            
            /*
             * -1 is loop forever - the loop count is not exact now
             * for small loops!
             */
            if ((f->loop.count != -1) && (f->loop.count != 0))
                f->loop.count--;
            
            /*
             * What's left to compute.
             */
            nSam = MIN(outCount, f->loop.end - f->loop.start);
            tsam = nSam - ADPCMFSIZE + f->lastsam;  
            if (tsam<0) tsam = 0;
            nframes = (tsam+ADPCMFSIZE-1)>>LFSAMPLES;
            nbytes =  nframes*ADPCMFBYTES;
            ptr = func_8006B3F4_main(ptr, f, tsam, nbytes, op, inp, f->first | A_LOOP);
            /*
             * Merge the two sections in DMEM.
             */
            aDMEMMove(ptr++, op+(f->lastsam<<1), bEnd, nSam<<1);

        }
        
        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += ADPCMFBYTES*nframes;    
#ifdef AUD_PROFILE
        PROFILE_AUD(adpcm_num, adpcm_cnt, adpcm_max, adpcm_min);
#endif
        return ptr;
    }

    /*
     * The unlooped case, which is executed most of the time
     */

    nSam = nframes<<LFSAMPLES;
    
    /*
     * overFlow is the number of bytes past the end
     * of the bitstream I try to generate
     */
    overFlow = f->memin + nbytes - ((s32) f->table->base + f->table->len);
    if (overFlow < 0)
        overFlow = 0;
    nOver = (overFlow/ADPCMFBYTES)<<LFSAMPLES;
    if (nOver > nSam + nLeft)
        nOver = nSam + nLeft;
    
    nbytes -= overFlow;

    if ((nOver - (nOver & 0xf))< outCount){
        decoded = 1;
        ptr = func_8006B3F4_main(ptr, f, nSam - nOver, nbytes, *outp, inp, f->first);
    
        if (f->lastsam)
            *outp += (f->lastsam<<1);
        else
            *outp += (ADPCMFSIZE<<1);

        f->lastsam = (outCount + f->lastsam) & 0xf;
        f->sample += outCount;
        f->memin += ADPCMFBYTES*nframes;    
    } else {        
        f->lastsam = 0;
        f->memin += ADPCMFBYTES*nframes;    
    }

    /*
     * Put zeros in if necessary
     */
    if (nOver){
        f->lastsam = 0;
        if (decoded)
            startZero = (nLeft + nSam - nOver)<<1;
        else
            startZero = 0;
        aClearBuffer(ptr++, startZero + *outp, nOver<<1);
    }
#ifdef AUD_PROFILE
    PROFILE_AUD(adpcm_num, adpcm_cnt, adpcm_max, adpcm_min);
#endif

    return ptr;
}

s32
func_8006B268_main(void *filter, s32 paramID, void *param)
{
    HuLoadFilter *a = (HuLoadFilter *) filter;
    
    switch (paramID) {
        case (AL_FILTER_SET_WAVETABLE):
            a->table = (ALWaveTable *) param;
            a->memin = (s32) a->table->base;
            a->sample = 0;
            switch (a->table->type){
                case (AL_ADPCM_WAVE):

                    /*
                     * Make sure the table length is an integer number of
                     * frames
                     */
                    a->table->len = ADPCMFBYTES *
                        ((s32) (a->table->len/ADPCMFBYTES));
                    
                    a->bookSize = 2*a->table->waveInfo.adpcmWave.book->order*
                    a->table->waveInfo.adpcmWave.book->npredictors*ADPCMVSIZE;
                    if (a->table->waveInfo.adpcmWave.loop) {
                        a->loop.start = a->table->waveInfo.adpcmWave.loop->start;
                        a->loop.end = a->table->waveInfo.adpcmWave.loop->end;
                        a->loop.count = a->table->waveInfo.adpcmWave.loop->count;
                        bcopy(a->table->waveInfo.adpcmWave.loop->state,
                               a->lstate, sizeof(ADPCM_STATE));
                    } else {
                        a->loop.start = a->loop.end = a->loop.count = 0;
                    }
                    break;
                    
                case (AL_RAW16_WAVE):
                    if (a->table->waveInfo.rawWave.loop) {
                        a->loop.start = a->table->waveInfo.rawWave.loop->start;
                        a->loop.end = a->table->waveInfo.rawWave.loop->end;
                        a->loop.count = a->table->waveInfo.rawWave.loop->count;
                    } else {
                        a->loop.start = a->loop.end = a->loop.count = 0;
                    }
                    break;
                    
                default:
                    break;

            }
            break;
            
        case (AL_FILTER_RESET):
            a->lastsam = 0;
            a->first   = 1;
            a->sample = 0;
	    
	    /* sct 2/14/96 - Check table since it is initialized to null and */
	    /* Get loop info according to table type. */
	    if (a->table)
	    {
		a->memin  = (s32) a->table->base;
		if (a->table->type == AL_ADPCM_WAVE)
		{
		    if (a->table->waveInfo.adpcmWave.loop)
			a->loop.count = a->table->waveInfo.adpcmWave.loop->count;
		}
		else if (a->table->type == AL_RAW16_WAVE)
		{
		    if (a->table->waveInfo.rawWave.loop)
			a->loop.count = a->table->waveInfo.rawWave.loop->count;
		}
	    }
	    
            break;
            
        default:
            break;
    }
}

/* _decodeChunk; this copy builds n_aLoadBuffer and n_aADPCMdec commands. */
Acmd *func_8006B3F4_main(Acmd *ptr, HuLoadFilter *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags)
{
    s32 dramAlign, dramLoc;

    if (nbytes > 0) {
        dramLoc = (f->dma)(f->memin, nbytes, f->dmaState);
        dramAlign = dramLoc & 0x7;
        nbytes += dramAlign;
        {
            Acmd *_a = ptr++;
            _a->words.w0 = _SHIFTL(A_LOADBUFF, 24, 8) | _SHIFTL(nbytes + 8 - (nbytes & 0x7), 12, 12) | _SHIFTL(inp, 0, 12);
            _a->words.w1 = (unsigned int)(dramLoc - dramAlign);
        }
    } else
        dramAlign = 0;

    if (flags & A_LOOP) {
        aSetLoop(ptr++, K0_TO_PHYS(f->lstate));
    }

    {
        Acmd *_a = ptr++;
        _a->words.w0 = _SHIFTL(A_ADPCM, 24, 8) | _SHIFTL(f->state, 0, 24);
        _a->words.w1 = _SHIFTL(flags, 28, 4) | _SHIFTL(tsam << 1, 16, 12) | _SHIFTL(dramAlign, 12, 4) | _SHIFTL(outp, 0, 12);
    }

    f->first = 0;

    return ptr;
}
