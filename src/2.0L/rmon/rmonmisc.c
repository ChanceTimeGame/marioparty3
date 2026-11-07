#include "common.h"
#include "PR/os_internal.h"
#include "PR/sptask.h"
#include "rmonint.h"

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof(x[0])))

extern OSMesgQueue D_800D6A60_main;  // __rmonMQ
extern OSMesg D_800C4ED0_main[8];    // rmonMsgs
extern OSThread D_800C4D20_main;     // rmonIOThread, then rmonIOStack (0x4000)
extern OSMesg D_800C8EF0_main[8];    // rmonPiMsgs (also the end of rmonIOStack)
extern OSMesgQueue D_800C8F10_main;
extern u8 rmonIOStackEnd[];           // end of rmonIOStack (alias in undefined_syms.txt)  // rmonPiMQ

int __rmonSetFault(KKHeader *req) {
    KKFaultRequest *request = (KKFaultRequest *)req;
    KKObjectEvent reply;

    reply.header.code = request->header.code;
    reply.header.error = TV_ERROR_NO_ERROR;
    reply.object = request->tid;
    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}

void __rmonInit(void) {
    osCreateMesgQueue(&D_800D6A60_main, D_800C4ED0_main, ARRLEN(D_800C4ED0_main));
    osSetEventMesg(OS_EVENT_CPU_BREAK, &D_800D6A60_main, (OSMesg)RMON_MESG_CPU_BREAK);
    osSetEventMesg(OS_EVENT_SP_BREAK, &D_800D6A60_main, (OSMesg)RMON_MESG_SP_BREAK);
    osSetEventMesg(OS_EVENT_FAULT, &D_800D6A60_main, (OSMesg)RMON_MESG_FAULT);
    osSetEventMesg(OS_EVENT_THREADSTATUS, &D_800D6A60_main, NULL);
    osCreateThread(&D_800C4D20_main, 0, (void (*)(void *))__rmonIOhandler, NULL, (void *)rmonIOStackEnd,
                   OS_PRIORITY_MAX);
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_800C8F10_main, D_800C8EF0_main, ARRLEN(D_800C8EF0_main));
    osStartThread(&D_800C4D20_main);
}

void __rmonPanic(void) {
    for (;;) {
        ;
    }
}

int __rmonSetComm(KKHeader *req) {
    KKObjectEvent reply;

    reply.header.code = req->code;
    reply.object = 0;
    reply.header.error = TV_ERROR_NO_ERROR;
    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}
