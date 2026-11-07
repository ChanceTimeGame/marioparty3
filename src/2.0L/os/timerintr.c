#include "common.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

extern OSTimer *D_800A2DD0_main;     // __osTimerList
extern u32 D_800D2000_main;          // __osTimerCounter
extern OSMesgQueue D_800D41A8_main;  // __osProfTimerQ
extern OSProf *D_800CCF24_main;      // __osProfileList
extern OSProf *D_800D4190_main;      // __osProfileListEnd
extern u32 D_800CC0B0_main;          // __osProfileOverflowBin

#define TIMER_LIST D_800A2DD0_main
#define TIMER_COUNTER D_800D2000_main

void __osTimerServicesInit(void) {
    __osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;
    TIMER_LIST->next = TIMER_LIST->prev = TIMER_LIST;
    TIMER_LIST->interval = TIMER_LIST->value = 0;
    TIMER_LIST->mq = NULL;
    TIMER_LIST->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;
    u32 pc;
    s32 offset;
    OSProf *prof = D_800CCF24_main;

    if (TIMER_LIST->next == TIMER_LIST) {
        return;
    }

    for (;;) {
        t = TIMER_LIST->next;
        if (t == TIMER_LIST) {
            __osSetCompare(0);
            TIMER_COUNTER = 0;
            break;
        }

        count = osGetCount();
        elapsed_cycles = count - TIMER_COUNTER;
        TIMER_COUNTER = count;

        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            break;
        }

        t->prev->next = t->next;
        t->next->prev = t->prev;
        t->next = NULL;
        t->prev = NULL;

        if (t->mq != NULL) {
            if (t->mq != &D_800D41A8_main) {
                osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
            } else {
                pc = __osRunQueue->context.pc;
                for (prof = D_800CCF24_main; prof < D_800D4190_main; prof++) {
                    offset = pc - (u32)prof->text_start;
                    if (offset >= 0) {
                        if ((s32)prof->text_end - (s32)pc > 0) {
                            (*(u16 *)(u32)((offset >> 2) + prof->histo_base))++;
                            goto __ProfDone;
                        }
                    }
                }
                D_800CC0B0_main++;
            }
        }
    __ProfDone:
        if (t->interval != 0) {
            t->value = t->interval;
            __osInsertTimer(t);
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;

    if (tim < 468) {
        tim = 468;
    }

    savedMask = __osDisableInt();
    TIMER_COUNTER = osGetCount();
    NewTime = TIMER_COUNTER + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask = __osDisableInt();

    timep = TIMER_LIST->next;
    tim = t->value;

    for (; timep != TIMER_LIST && tim > timep->value; timep = timep->next) {
        tim -= timep->value;
    }

    t->value = tim;
    if (timep != TIMER_LIST) {
        timep->value -= tim;
    }

    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;

    __osRestoreInt(savedMask);

    return tim;
}
