#ifndef OSTHREAD_FULL_H
#define OSTHREAD_FULL_H

#include "PR/os_internal.h"

/* The retail library's OSThread has the profiling pointer at 0x1C, which pushes the context to 0x20;
   include/PR/os.h's OSThread lacks it. */
typedef struct {
    u32 flag;
    u32 count;
    u64 time;
} ThreadProf;

typedef struct OSThreadFull_s {
    struct OSThreadFull_s *next;
    OSPri priority;
    struct OSThreadFull_s **queue;
    struct OSThreadFull_s *tlnext;
    u16 state;
    u16 flags;
    OSId id;
    int fp;
    ThreadProf *thprof;
    __OSThreadContext context;
} OSThreadFull;

#endif
