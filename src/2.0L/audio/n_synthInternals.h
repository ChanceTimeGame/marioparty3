/* n_audio (libultra's second, "n_" audio library) private definitions for MP3's copy in main
   (66E70-723E0). Layouts follow the SDK's n_synthInternals.h. */
#ifndef __N_SYNTHINTERNALS_H__
#define __N_SYNTHINTERNALS_H__

#include <libaudio.h>
#include "2.0L/audio/synthInternals.h"
#include <PR/n_libaudio.h>

/* n_abi.h command macros */
#define	n_aADPCMdec(pkt, s, f, c, a, d)					\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_ADPCM, 24, 8) | _SHIFTL(s, 0, 24));   \
	_a->words.w1 = (_SHIFTL(f, 28, 4) | _SHIFTL(c, 16, 12) |        \
			_SHIFTL(a, 12, 4) | _SHIFTL(d, 0, 12));         \
}

#define n_aPoleFilter(pkt, f, g, t, s)					\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_POLEF, 24, 8) | _SHIFTL(f, 16, 8) |	\
			_SHIFTL(g, 0, 16)); 				\
	_a->words.w1 = (_SHIFTL(t, 24, 8) |                             \
			_SHIFTL((unsigned int)(s), 0, 24));		\
}

#define n_aEnvMixer(pkt, f, t, s)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL(f, 16, 8) |\
			_SHIFTL(t, 0, 16));                     	\
	_a->words.w1 = (unsigned int)(s);				\
}

#define n_aInterleave(pkt)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_INTERLEAVE, 24, 8);    		\
}

#define n_aLoadBuffer(pkt, c, d, s)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_LOADBUFF, 24, 8) | _SHIFTL(c, 12, 12)|\
			_SHIFTL(d, 0, 12));                             \
	_a->words.w1 = (unsigned int)(s);				\
}

#define n_aResample(pkt, s, f, p, i, o)					\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_RESAMPLE, 24, 8) | _SHIFTL(s, 0, 24));\
	_a->words.w1 = (_SHIFTL(f, 30, 2) | _SHIFTL(p, 14, 16) |        \
			_SHIFTL(i, 2, 12) | _SHIFTL(o, 0, 2));          \
}

#define n_aSaveBuffer(pkt, c, d, s)					\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_SAVEBUFF, 24, 8) | _SHIFTL(c, 12, 12)|\
			_SHIFTL(d, 0, 12));                             \
	_a->words.w1 = (unsigned int)(s);				\
}

#define n_aSetVolume(pkt, f, v, t, r)					\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = (_SHIFTL(A_SETVOL, 24, 8) | _SHIFTL(f, 16, 8) |	\
			_SHIFTL(v, 0, 16)); 				\
	_a->words.w1 = _SHIFTL(t, 16, 16) | _SHIFTL(r, 0, 16);		\
}

#define n_aLoadADPCM(pkt, c, d)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_LOADADPCM, 24, 8) | _SHIFTL(c, 0, 24);	\
        _a->words.w1 = (unsigned int) d;                                \
}


typedef struct N_PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ struct N_ALVoice_s *vvoice;
    /* ALLoadFilter */
    /* 0x0C */ ADPCM_STATE *dc_state;
    /* 0x10 */ ADPCM_STATE *dc_lstate;
    /* 0x14 */ ALRawLoop dc_loop;
    /* 0x20 */ struct ALWaveTable_s *dc_table;
    /* 0x24 */ s32 dc_bookSize;
    /* 0x28 */ ALDMAproc dc_dma;
    /* 0x2C */ void *dc_dmaState;
    /* 0x30 */ s32 dc_sample;
    /* 0x34 */ s32 dc_lastsam;
    /* 0x38 */ s32 dc_first;
    /* 0x3C */ s32 dc_memin;
    /* ALResampler */
    /* 0x40 */ RESAMPLE_STATE *rs_state;
    /* 0x44 */ f32 rs_ratio;
    /* 0x48 */ s32 rs_upitch;
    /* 0x4C */ f32 rs_delta;
    /* 0x50 */ s32 rs_first;
    /* ALEnvMixer */
    /* 0x54 */ ENVMIX_STATE *em_state;
    /* 0x58 */ s16 em_pan;
    /* 0x5A */ s16 em_volume;
    /* 0x5C */ s16 em_cvolL;
    /* 0x5E */ s16 em_cvolR;
    /* 0x60 */ s16 em_dryamt;
    /* 0x62 */ s16 em_wetamt;
    /* 0x64 */ u16 em_lratl;
    /* 0x66 */ s16 em_lratm;
    /* 0x68 */ s16 em_ltgt;
    /* 0x6A */ u16 em_rratl;
    /* 0x6C */ s16 em_rratm;
    /* 0x6E */ s16 em_rtgt;
    /* 0x70 */ s32 em_delta;
    /* 0x74 */ s32 em_segEnd;
    /* 0x78 */ s32 em_first;
    /* 0x7C */ ALParam *em_ctrlList;
    /* 0x80 */ ALParam *em_ctrlTail;
    /* 0x84 */ s32 em_motion;
    /* 0x88 */ s32 offset;
} N_PVoice; /* size = 0x8C */

#define SAMPLES 184
#define SAMPLE184(delta) ((((delta) + (SAMPLES / 2)) / SAMPLES) * SAMPLES)
#define FIXED_SAMPLE SAMPLES
#define N_AL_MAX_RSP_SAMPLES 184
#ifndef SQR
#define SQR(x) ((x) * (x))
#endif

extern N_ALGlobals *D_800A2884_main; /* n_alGlobals */
#define n_syn (&D_800A2884_main->drvr)

extern u8 D_800CB8AC_main; /* mono flag (Hudson's MONO PATCH) */

ALParam *func_8006BBBC_main(void);              /* __n_allocParam */
void func_8006BBE8_main(ALParam *param);        /* __n_freeParam */
s32 func_8006BCE8_main(s32 micros);             /* _n_timeToSamples */
s32 func_8006A9C8_main(N_PVoice *v, s32 paramId, void *param); /* n_alEnvmixerParam */

#endif
