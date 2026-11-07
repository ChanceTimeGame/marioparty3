/* 6C140: n_audio n_resample.c (n_alResamplePull, n_alResampleParam). */
#include "2.0L/audio/n_synthInternals.h"
#include <os_internal.h>

#define N_AL_DECODER_OUT 368
#define MAX_RATIO 1.99996
#define UNITY_PITCH 0x8000

Acmd *func_8006AE20_main(void *filter, s16 *outp, s32 outCount, Acmd *p); /* n_alAdpcmPull */
s32 func_8006B268_main(void *filter, s32 paramID, void *param);          /* n_alLoadParam */

Acmd *func_8006B540_main(N_PVoice *e, s16 *outp, Acmd *p)
{
    Acmd *ptr = p;
    s16 inp;
    s32 inCount;
    s32 incr;
    f32 finCount;

    inp = N_AL_DECODER_OUT;

    if (e->rs_upitch) {
        ptr = func_8006AE20_main(e, &inp, FIXED_SAMPLE, p);
        aDMEMMove(ptr++, inp, *outp, FIXED_SAMPLE << 1);
    } else {
        if (e->rs_ratio > MAX_RATIO)
            e->rs_ratio = MAX_RATIO;

        e->rs_ratio = (s32)(e->rs_ratio * UNITY_PITCH);
        e->rs_ratio = e->rs_ratio / UNITY_PITCH;

        finCount = e->rs_delta + (e->rs_ratio * (f32)FIXED_SAMPLE);
        inCount = (s32)finCount;
        e->rs_delta = finCount - (f32)inCount;

        ptr = func_8006AE20_main(e, &inp, inCount, p);

        incr = (s32)(e->rs_ratio * UNITY_PITCH);
        n_aResample(ptr++, osVirtualToPhysical(e->rs_state), e->rs_first, incr, inp, 0);
        e->rs_first = 0;
    }

    return ptr;
}

s32 func_8006B6FC_main(N_PVoice *filter, s32 paramID, void *param)
{
    func_8006B268_main(filter, paramID, param);
    return 0;
}
