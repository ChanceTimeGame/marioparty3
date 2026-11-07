#include "common.h"
#include "PR/os_internal.h"
#include "PR/sptask.h"
#include "PR/rdb.h"
#include "PR/rmon.h"
#include "rmonint.h"

#define UNUSED __attribute__((unused))

extern OSMesgQueue D_800C4D00_main;                       // IOmq
extern OSMesg D_800C4D18_main;                            // IOmsgs
extern void *D_800C9948_main;                             // __osRdb_DbgRead_Buf
extern u8 D_800D1720_main[RMON_DBG_BUF_SIZE];             // rmonRdbReadBuf

void __rmonSendFault(OSThread *thread) {
    volatile float f UNUSED;
    u8 *tPtr;
    u32 sent = 0;

    f = 0.0f;
    tPtr = (u8 *)thread;
    while (sent < sizeof(OSThread)) {
        sent += __osRdbSend(tPtr + sent, sizeof(OSThread) - sent, RDB_TYPE_GtoH_FAULT);
    }
}

void __rmonIOflush(void) {
    int sent = 0;
    char tstr[4];

    while (sent <= 0) {
        sent += __osRdbSend((u8 *)tstr, 1, RDB_TYPE_GtoH_DEBUG_DONE);
    }
}

void __rmonIOputw(u32 word) {
    int sent = 0;
    char *cPtr = (char *)&word;

    while (sent < 4) {
        sent += __osRdbSend((u8 *)cPtr + sent, sizeof(word) - sent, RDB_TYPE_GtoH_DEBUG);
    }
}

void __rmonIOhandler(void) {
    int sent;
    char tstr[4];

    osCreateMesgQueue(&D_800C4D00_main, &D_800C4D18_main, 1);
    osSetEventMesg(OS_EVENT_RDB_DBG_DONE, &D_800C4D00_main, NULL);
    D_800C9948_main = D_800D1720_main;

    while (TRUE) {
        osRecvMesg(&D_800C4D00_main, NULL, OS_MESG_BLOCK);
        __rmonExecute((KKHeader *)&D_800D1720_main);
        D_800C9948_main = D_800D1720_main;
        sent = 0;
        while (sent <= 0) {
            sent += __osRdbSend((u8 *)tstr, 1, RDB_TYPE_GtoH_DEBUG_READY);
        }
    }
}
