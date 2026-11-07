#include "synthInternals.h"
#include <os_internal.h>
#include <PR/n_libaudio.h>

#include "include_asm.h"

extern N_ALGlobals *D_800A2884_main; /* n_alGlobals: the second (n_audio) copy of this unit's library */

#ifdef NON_MATCHING
/* Differs in register allocation and in loading thing->next through the (equal) client register. This copy is n_alSynRemovePlayer(ALPlayer *client): the synth is the global, and the one argument is the
   player. include/PR/libaudio.h declares it as alSynRemovePlayer(ALSynth *), hence the parameter type. */
void alSynRemovePlayer(ALSynth *c) {
    ALPlayer *client = (ALPlayer *)c;
    ALPlayer *prev = 0;
    ALPlayer *thing;

    if (D_800A2884_main->drvr.head != 0) {
        OSIntMask mask = osSetIntMask(OS_IM_NONE);

        for (thing = D_800A2884_main->drvr.head; thing != 0; thing = thing->next) {
            if (thing == client) {
                if (prev) {
                    prev->next = client->next;
                } else {
                    D_800A2884_main->drvr.head = client->next;
                }
                client->next = 0;
                break;
            }
            prev = thing;
        }
        osSetIntMask(mask);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synremoveplayer", alSynRemovePlayer);
#endif
