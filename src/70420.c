/* 70420: n_audio n_save.c (n_alSavePull). */
#include "2.0L/audio/n_synthInternals.h"

Acmd *func_80071AC0_main(s32 sampleOffset, Acmd *p); /* n_alMainBusPull */

Acmd *func_8006F820_main(s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;

    ptr = func_80071AC0_main(sampleOffset, ptr);

    n_aInterleave(ptr++);
    n_aSaveBuffer(ptr++, FIXED_SAMPLE << 2, 0, n_syn->sv_dramout);

    return ptr;
}
