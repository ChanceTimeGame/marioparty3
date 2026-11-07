/* 6C320: n_audio n_sl.c (n_alInit, n_alClose). */
#include "2.0L/audio/n_synthInternals.h"

extern N_ALGlobals *D_800A2880_main; /* n_alGlobals */

void func_8006B7A0_main(void);                 /* n_alSynDelete */
void func_8006B7C0_main(ALSynConfig *c);       /* n_alSynNew */

void func_8006B720_main(N_ALGlobals *g, ALSynConfig *config)
{
    if (D_800A2880_main == NULL) {
        D_800A2880_main = g;
        if (D_800A2884_main == NULL) {
            D_800A2884_main = g;
            func_8006B7C0_main(config);
        }
    }
}

void func_8006B764_main(N_ALGlobals *glob)
{
    if (D_800A2880_main) {
        func_8006B7A0_main();
        D_800A2880_main = NULL;
        D_800A2884_main = NULL;
    }
}
