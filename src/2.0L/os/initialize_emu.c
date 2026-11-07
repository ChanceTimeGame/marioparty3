#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

extern void *__printfunc;

static void *proutSyncPrintf(void *str, const char *buf, u32 n);

void __osInitialize_emu(void) {
    __printfunc = proutSyncPrintf;
}

static void *proutSyncPrintf(void *str, const char *buf, u32 n) {
    u32 sent = 0;

    while (sent < n) {
        sent += __osRdbSend((u8 *)buf + sent, n - sent, RDB_TYPE_GtoH_PRINT);
    }
    return (void *)1;
}
