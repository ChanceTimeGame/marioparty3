#include "common.h"

/* libleo LeoBootGame, from MP1 src/83490.c (IDO-compiled there too: NON_MATCHING). It decrypts
   __LeoBootGame2 and the 0x50 bytes after it (D_80071FD0_main) in place, keyed by the sum of
   __LeoBootGame2's address bytes, then calls it. __LeoBootGame2 is encrypted code, not
   compilable C: it stays as asm. */

void __LeoBootGame2(void* entry);
extern u8 D_80071FD0_main[];

#ifdef NON_MATCHING
void LeoBootGame(void* entry) {
    u8* p;
    u32 addr = (u32)__LeoBootGame2;
    u8 key = (addr >> 24) + ((addr & 0xFF0000) >> 16) + ((addr & 0xFF00) >> 8) + addr;
    u32 i;

    for (p = (u8*)__LeoBootGame2, i = 0; i < 0x344; i += 4, p += 4) {
        p[2] -= key;
        p[3] += key;
    }
    osWritebackDCacheAll();
    osInvalICache(__LeoBootGame2, 0x344);
    for (p = D_80071FD0_main, i = 0; i < 0x50; i += 4, p += 4) {
        p[2] -= key;
        p[3] += key;
    }
    osWritebackDCacheAll();
    osInvalICache(D_80071FD0_main, 0x50);
    __LeoBootGame2(entry);
}
#else
INCLUDE_ASM("asm/nonmatchings/72750", LeoBootGame);
#endif

/* Encrypted (see above). */
INCLUDE_ASM("asm/nonmatchings/72750", __LeoBootGame2);
