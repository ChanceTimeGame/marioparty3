#include "synthInternals.h"
#include <os_internal.h>
#include <PR/n_libaudio.h>

#include "include_asm.h"

extern N_ALGlobals *D_800A2884_main; /* n_alGlobals: the second (n_audio) copy of this unit's library */

/* This copy is n_alSynRemovePlayer(ALPlayer *client): the synth is the global, and the one argument is the
   player (it also clears the synth's n_sndp/n_seqp1/n_seqp2 when they are the player).
   include/PR/libaudio.h declares it as alSynRemovePlayer(ALSynth *), hence the parameter type. */
void alSynRemovePlayer(ALSynth *c) {
    ALPlayer *client = (ALPlayer *)c;
    ALPlayer *thing;
    ALPlayer *prev = 0;
    OSIntMask mask;

    if (D_800A2884_main->drvr.head != 0) {
        mask = osSetIntMask(OS_IM_NONE);

        for (thing = D_800A2884_main->drvr.head; thing != 0; thing = thing->next) {
            if (thing == client) {
                if (prev) {
                    prev->next = thing->next;
                } else {
                    D_800A2884_main->drvr.head = thing->next;
                }
                client->next = 0;
                break;
            }
            prev = thing;
        }
        osSetIntMask(mask);
    }

    mask = osSetIntMask(OS_IM_NONE);
    if (D_800A2884_main->drvr.n_sndp == client) {
        D_800A2884_main->drvr.n_sndp = 0;
    } else if (D_800A2884_main->drvr.n_seqp1 == client) {
        D_800A2884_main->drvr.n_seqp1 = 0;
    } else if (D_800A2884_main->drvr.n_seqp2 == client) {
        D_800A2884_main->drvr.n_seqp2 = 0;
    }
    osSetIntMask(mask);
}
