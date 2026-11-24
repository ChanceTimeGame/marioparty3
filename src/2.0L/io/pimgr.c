#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"
#include "piint.h"
#include "include_asm.h"

/* The library's file-local statics live in the data asm:
   D_800C2180_main  piThread, then piThreadStack (OS_PIM_STACKSIZE)
   D_800C3330_main  ramromThread, then ramromThreadStack (0x400)
   D_800C38E0_main  getRamromQ, D_800C38F8_main getRamromBuf, D_800C3900_main freeRamromQ,
   D_800C3918_main  freeRamromBuf, D_800C3920_main piEventQueue, D_800C3938_main piEventBuf */
extern OSThread D_800C2180_main;
extern u64 piThreadStack[OS_PIM_STACKSIZE / sizeof(u64)];
extern OSThread D_800C3330_main;
extern u64 ramromThreadStack[0x400 / sizeof(u64)];
extern OSMesgQueue D_800C38E0_main;
extern OSMesg D_800C38F8_main[1];
extern OSMesgQueue D_800C3900_main;
extern OSMesg D_800C3918_main[1];
extern OSMesgQueue D_800C3920_main;
extern OSMesg D_800C3938_main[1];

extern OSMesgQueue __osPiAccessQueue;

void ramromMain(void *arg);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (__osPiDevMgr.active) {
        return;
    }

    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&D_800C3920_main, (OSMesg *)D_800C3938_main, 1);

    if (!__osPiAccessQueueEnabled) {
        __osPiCrateAccessQueue();
    }

    osSetEventMesg(OS_EVENT_PI, &D_800C3920_main, (OSMesg)0x22222222);

    oldPri = -1;
    myPri = osGetThreadPri(NULL);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(NULL, pri);
    }

    savedMask = __osDisableInt();

    __osPiDevMgr.active = 1;
    __osPiDevMgr.thread = &D_800C2180_main;
    __osPiDevMgr.cmdQueue = cmdQ;
    __osPiDevMgr.evtQueue = &D_800C3920_main;
    __osPiDevMgr.acsQueue = &__osPiAccessQueue;
    __osPiDevMgr.dma = osPiRawStartDma;
    __osPiDevMgr.edma = __osEPiRawStartDma;

    osCreateThread(&D_800C2180_main, 0, __osDevMgrMain, &__osPiDevMgr, piThreadStack + OS_PIM_STACKSIZE / sizeof(u64), pri);
    osStartThread(&D_800C2180_main);

    osCreateThread(&D_800C3330_main, 0, ramromMain, NULL, ramromThreadStack + 0x400 / sizeof(u64), (OSPri)pri - 1);
    osStartThread(&D_800C3330_main);

    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}

void ramromMain(void *arg) {
    u32 sent;
    u8 tmp[3];

    osCreateMesgQueue(&D_800C38E0_main, D_800C38F8_main, 1);
    osCreateMesgQueue(&D_800C3900_main, D_800C3918_main, 1);
    osSetEventMesg(OS_EVENT_RDB_REQ_RAMROM, &D_800C38E0_main, NULL);
    osSetEventMesg(OS_EVENT_RDB_FREE_RAMROM, &D_800C3900_main, NULL);

    while (TRUE) {
        osRecvMesg(&D_800C38E0_main, NULL, OS_MESG_BLOCK);
        __osPiGetAccess();
        sent = 0;
        while (sent < 1) {
            sent += __osRdbSend(tmp, 1, RDB_TYPE_GtoH_RAMROM);
        }
        osRecvMesg(&D_800C3900_main, NULL, OS_MESG_BLOCK);
        __osPiRelAccess();
    }
}
