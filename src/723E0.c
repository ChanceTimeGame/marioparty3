/* 723E0: n_audio's copy of libultra audio/seq.c (alSeqNextEvent, alSeqNewMarker, read8, readVarLen; the
   rest of the file is shared with the plain copy) and n_mainbus.c (n_alMainBusPull). The seq.c code
   is MP3's own src/2.0L/audio/seq.c. */
#define alSeqNextEvent func_800717E0_main
#define alSeqNewMarker func_80071948_main
#define read8 func_80071A5C_main
#define readVarLen func_80071A70_main
#include <libaudio.h>
#include <os_internal.h>
#include <ultraerror.h>
#include "2.0L/audio/seq.h"
#include "2.0L/audio/n_synthInternals.h"

static s32 readVarLen(ALSeq *s);
static u8 read8(ALSeq *s);

void alSeqNextEvent(ALSeq *seq, ALEvent *event)
{
    u8          status;
    s16         delta;
    s32         len;
    s32         deltaTicks;
    s32         i;

#ifdef _DEBUG
    /* sct 1/17/96 - Warn if curPtr is beyond the end of sequence. */
    if (seq->curPtr >= seq->base + seq->len)
	__osError(ERR_ALSEQOVERRUN, 0);
#endif
    
    deltaTicks = readVarLen(seq);   /* read the delta time */
    seq->lastTicks += deltaTicks;
    status = read8(seq);
    
#if _DEBUG
    /*
     * System exclusives are not supported, so just skip them and read
     * the next event
     */
    if ((status == 0xf0) || (status == 0xf7)) {
        __osError(ERR_ALSEQSYSEX, 0);
        len = readVarLen(seq);
        for (i = 0; i < len; i++) {
            read8(seq);
        }
        alSeqNextEvent(seq,event);
        return;
    }
#endif
    
    if (status == AL_MIDI_Meta) {
        u8 type = read8(seq);
        
        if (type == AL_MIDI_META_TEMPO) {
            event->type = AL_TEMPO_EVT;
            event->msg.tempo.ticks = deltaTicks;
            event->msg.tempo.status = status;
            event->msg.tempo.type = type;
            event->msg.tempo.len  = read8(seq);
            event->msg.tempo.byte1 = read8(seq);
            event->msg.tempo.byte2 = read8(seq);
            event->msg.tempo.byte3 = read8(seq);
        } else if (type == AL_MIDI_META_EOT) {
            event->type = AL_SEQ_END_EVT;
            event->msg.end.ticks  = deltaTicks;
            event->msg.end.status = status;
            event->msg.end.type   = type;
            event->msg.end.len    = read8(seq);
        } else {
#ifdef _DEBUG
            __osError(ERR_ALSEQMETA, 1, type);
            len = readVarLen(seq);
            for (i = 0; i < len; i++) {
                read8(seq);
            }
            alSeqNextEvent(seq,event);
            return;
#endif            
        }

        seq->lastStatus = 0;
        
    } else {
        event->type = AL_SEQ_MIDI_EVT;
        event->msg.midi.ticks = deltaTicks;
        if (status & 0x80) {
            event->msg.midi.status = status;
            event->msg.midi.byte1 = read8(seq);
            seq->lastStatus = status;
        } else {
            /* running status */
            event->msg.midi.status = seq->lastStatus;
            event->msg.midi.byte1 = status;
        }
        
        if (((event->msg.midi.status & 0xf0) != AL_MIDI_ProgramChange) &&
            ((event->msg.midi.status & 0xf0) != AL_MIDI_ChannelPressure)) {
            event->msg.midi.byte2 = read8(seq);
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
}

void alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks)
{
    ALEvent     evt;
    u8          *savePtr, *lastPtr;
    s32         saveTicks, lastTicks;
    s16         saveStatus, lastStatus;
    
    /* does not check that ticks is within bounds */
    
    if (ticks == 0) { /* common case */
        m->curPtr     = seq->trackStart;
        m->lastStatus = 0;
        m->lastTicks  = 0;
	m->curTicks = 0;
        return;
    } else {
        savePtr     = seq->curPtr;
        saveStatus  = seq->lastStatus;
        saveTicks   = seq->lastTicks;

        seq->curPtr     = seq->trackStart;
        seq->lastStatus = 0;
        seq->lastTicks  = 0;

        do {
            lastPtr    = seq->curPtr;
            lastStatus = seq->lastStatus;
            lastTicks  = seq->lastTicks;
        
            alSeqNextEvent(seq, &evt);
            
            if (evt.type == AL_SEQ_END_EVT)
	    {
		lastPtr    = seq->curPtr;
		lastStatus = seq->lastStatus;
		lastTicks  = seq->lastTicks;
                break;
	    }
            
        } while (seq->lastTicks < ticks);

        m->curPtr     = lastPtr;
        m->lastStatus = lastStatus;
        m->lastTicks  = lastTicks;
	m->curTicks = seq->lastTicks;	/* Used by test loop condition. */
    
        seq->curPtr     = savePtr;
        seq->lastStatus = saveStatus;
        seq->lastTicks  = saveTicks;

    }    
}

static u8 read8(ALSeq *seq)
{
    return *seq->curPtr++;
}

static s32 readVarLen(ALSeq *seq)
{
    s32 value;
    s32 c;

    c = *seq->curPtr++;
    value = c;
    if ( c & 0x80 ) {
        value &= 0x7f;
        do {
            c = *seq->curPtr++;
            value = (value << 7) + (c & 0x7f);
        } while (c & 0x80);
    }
    return (value);
}

/* n_mainbus.c */
#define N_AL_MAIN_L_OUT 1248
#define N_AL_MAIN_R_OUT 1616
#define N_AL_AUX_L_OUT 1984
#define N_AL_AUX_R_OUT 2352
#define N_AL_DIVIDED 368

Acmd *func_80071AC0_main(s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;

    aClearBuffer(ptr++, N_AL_MAIN_L_OUT, N_AL_DIVIDED << 1);

    ptr = (n_syn->mainBus->filter.handler)(sampleOffset, ptr);

    aMix(ptr++, 0, 0x7FFF, N_AL_AUX_L_OUT, N_AL_MAIN_L_OUT);
    aMix(ptr++, 0, 0x7FFF, N_AL_AUX_R_OUT, N_AL_MAIN_R_OUT);

    return ptr;
}
