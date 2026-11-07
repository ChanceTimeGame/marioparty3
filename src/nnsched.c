#include "common.h"
#include "PR/sptask.h"

// Hudson's variant of the N64 SDK "nn" scheduler (nnsched.c), from MP1 src/engine/nnsched.c and
// MP2 src/7E850.c: globals instead of an NNSched struct, client masks instead of message types.

typedef struct NNScClient {
    struct NNScClient* next;
    OSMesgQueue* msgQ;
    s32 mask;
} NNScClient;

typedef struct {
    OSTask list;
    OSMesgQueue* msgQ;
    OSMesg msg; // bit 0 also requests func_8004D888_main after the frame
} NNScTask;

extern s32 D_800CCF2C_main;         // pre-NMI received
extern u32 D_800CE210_main;         // retraces since pre-NMI
extern u32 D_800CE2C8_main;         // fields per retrace
extern u32 D_800D2094_main;         // retrace count
extern NNScClient* D_800BBAC0_main; // client list
extern NNScTask* D_800BCC80_main;   // current audio task
extern NNScTask* D_800BCC84_main;   // current graphics task
extern OSMesg D_800BCC88_main;      // graphics RSP done message
extern s32 D_800BCCB0_main;         // graphics task waiting on audio
extern OSMesgQueue D_800BBAC8_main; // retrace
extern OSMesg D_800BBAE0_main[];
extern OSMesgQueue D_800BBB00_main; // RSP
extern OSMesg D_800BBB18_main[];
extern OSMesgQueue D_800BBB38_main; // RDP
extern OSMesg D_800BBB50_main[];
extern OSMesgQueue D_800CC3C0_main; // graphics requests
extern OSMesg D_800BCC90_main[];
extern OSMesgQueue D_800BCCB8_main; // wait
extern OSMesg D_800BCCD0_main[];
extern OSMesgQueue D_800CC3A0_main; // audio requests
extern OSMesg D_800BCCD8_main[];
extern OSViMode D_800A2E00_main[]; // libultra osViModeTable order, indexed by videoMode
// Each thread's 0x400-byte stack follows its OSThread.
extern OSThread D_800BBB70_main;
extern OSThread D_800BC120_main;
extern OSThread D_800BC6D0_main;
extern u64 D_800BBD20_main[0x400 / sizeof(u64)];
extern u64 D_800BC2D0_main[0x400 / sizeof(u64)];
extern u64 D_800BC880_main[0x400 / sizeof(u64)];
extern s32 _osPreNMI;

void HuProfRecordAwaitRsp(void);
s16 func_8004D710_main(u8 arg0, u8 arg1, u8 arg2);
void func_8004D788_main(s16 sampleIdx);
void func_8004D888_main(void);
void PRENMICallbackVibrator(void);
s32 osAfterPreNMI(void);

void AddSchedulerClient(NNScClient* client, OSMesgQueue* msgQ, s32 mask);
void EventBroadcast(s32 mask);
void EventHandler(void* arg);
void ScExecuteAudio(void* arg);
void ScExecuteGraphics(void* arg);

void InitSchedulerEvent(void) {
    osCreateMesgQueue(&D_800BBAC8_main, D_800BBAE0_main, 8);
    osSetEventMesg(OS_EVENT_PRENMI, &D_800BBAC8_main, (OSMesg)0x29D);
}

void InitScheduler(u8 videoMode, u8 numFields) {
    D_800CE2C8_main = numFields;
    D_800CCF2C_main = 0;
    D_800CE210_main = 0;
    D_800D2094_main = 0;
    D_800BBAC0_main = NULL;
    D_800BCC80_main = NULL;
    D_800BCC84_main = NULL;
    D_800BCC88_main = NULL;
    D_800BCCB0_main = 0;
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&D_800A2E00_main[videoMode]);
    osViSetYScale(1.0f);
    osViBlack(TRUE);
    osCreateMesgQueue(&D_800BBB00_main, D_800BBB18_main, 8);
    osCreateMesgQueue(&D_800BBB38_main, D_800BBB50_main, 8);
    osCreateMesgQueue(&D_800CC3C0_main, D_800BCC90_main, 8);
    osCreateMesgQueue(&D_800BCCB8_main, D_800BCCD0_main, 1);
    osCreateMesgQueue(&D_800CC3A0_main, D_800BCCD8_main, 8);
    osViSetEvent(&D_800BBAC8_main, (OSMesg)0x29A, numFields);
    osSetEventMesg(OS_EVENT_SP, &D_800BBB00_main, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &D_800BBB38_main, (OSMesg)0x29C);
    osCreateThread(&D_800BBB70_main, 19, EventHandler, NULL, D_800BBD20_main + ARRAY_COUNT(D_800BBD20_main), 120);
    osStartThread(&D_800BBB70_main);
    while (_osPreNMI) {
    }
    osCreateThread(&D_800BC120_main, 18, ScExecuteAudio, NULL, D_800BC2D0_main + ARRAY_COUNT(D_800BC2D0_main), 111);
    osStartThread(&D_800BC120_main);
    osCreateThread(&D_800BC6D0_main, 17, ScExecuteGraphics, NULL, D_800BC880_main + ARRAY_COUNT(D_800BC880_main), 101);
    osStartThread(&D_800BC6D0_main);
}

/* A pre-NMI client added late is told at once. */
void AddSchedulerClient(NNScClient* client, OSMesgQueue* msgQ, s32 mask) {
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);

    client->next = D_800BBAC0_main;
    client->msgQ = msgQ;
    client->mask = mask;
    D_800BBAC0_main = client;
    osSetIntMask(intMask);
    if ((mask & 2) && D_800CCF2C_main != 0) {
        osSendMesg(msgQ, (OSMesg)2, OS_MESG_NOBLOCK);
    }
}

void RemoveSchedulerClient(NNScClient* c) {
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);
    NNScClient* client = D_800BBAC0_main;
    NNScClient* prev = NULL;

    while (client != NULL) {
        if (client == c) {
            if (prev != NULL) {
                prev->next = client->next;
            } else {
                D_800BBAC0_main = c->next;
            }
            break;
        }
        prev = client;
        client = client->next;
    }
    osSetIntMask(intMask);
}

void EventBroadcast(s32 mask) {
    NNScClient* client;

    for (client = D_800BBAC0_main; client != NULL; client = client->next) {
        if (mask & client->mask) {
            osSendMesg(client->msgQ, (OSMesg)mask, OS_MESG_NOBLOCK);
        }
    }
}

void EventHandler(void* arg) {
    OSMesg msg;

    while (TRUE) {
        osRecvMesg(&D_800BBAC8_main, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case 0x29A:
                D_800D2094_main++;
                HuProfRecordAwaitRsp();
                EventBroadcast(1);
                if (D_800CCF2C_main != 0) {
                    D_800CE210_main++;
                    if (D_800CE210_main >= 10 / D_800CE2C8_main) {
                        osAfterPreNMI();
                    }
                }
                break;
            case 0x29D:
                osViSetYScale(1.0f);
                osViBlack(TRUE);
                EventBroadcast(2);
                PRENMICallbackVibrator();
                D_800CCF2C_main = 1;
                break;
        }
    }
}

void ScExecuteAudio(void* arg) {
    NNScClient client;
    OSMesgQueue msgQ;
    OSMesg msgBuf[1];
    NNScTask* task = NULL;
    s32 yieldFlag;
    NNScTask* gfxTask;

    osCreateMesgQueue(&msgQ, msgBuf, 1);
    AddSchedulerClient(&client, &msgQ, 1);
    while (TRUE) {
        osRecvMesg(&msgQ, NULL, OS_MESG_BLOCK);
        if (osRecvMesg(&D_800CC3A0_main, (OSMesg*)&task, OS_MESG_NOBLOCK) != 0) {
            continue;
        }
        osWritebackDCacheAll();
        yieldFlag = 0;
        gfxTask = D_800BCC84_main;
        if (gfxTask != NULL && D_800BCC88_main == NULL) {
            osSpTaskYield();
            yieldFlag = 2;
            osRecvMesg(&D_800BBB00_main, NULL, OS_MESG_BLOCK);
            if (osSpTaskYielded(&gfxTask->list)) {
                yieldFlag = 1;
            }
        }
        D_800BCC80_main = task;
        osSpTaskStart(&task->list);
        osRecvMesg(&D_800BBB00_main, NULL, OS_MESG_BLOCK);
        D_800BCC80_main = NULL;
        if (D_800BCCB0_main != 0) {
            osSendMesg(&D_800BCCB8_main, NULL, OS_MESG_BLOCK);
        }
        switch (yieldFlag) {
            case 1:
                osSpTaskStart(&gfxTask->list);
                break;
            case 2:
                osSendMesg(&D_800BBB00_main, (OSMesg)0x29B, OS_MESG_BLOCK);
                break;
        }
        osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
    }
}

void ScExecuteGraphics(void* arg) {
    NNScTask* task = NULL;
    OSIntMask intMask;
    s16 perf0;
    s16 perf1;

    while (TRUE) {
        osRecvMesg(&D_800CC3C0_main, (OSMesg*)&task, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        intMask = osSetIntMask(OS_IM_NONE);
        if (D_800BCC80_main != NULL) {
            D_800BCCB0_main = 1;
            osSetIntMask(intMask);
            osRecvMesg(&D_800BCCB8_main, NULL, OS_MESG_BLOCK);
            intMask = osSetIntMask(OS_IM_NONE);
            D_800BCCB0_main = 0;
        }
        D_800BCC84_main = task;
        osSpTaskStart(&task->list);
        osSetIntMask(intMask);
        perf0 = func_8004D710_main(0, 0, 0xFF);
        perf1 = func_8004D710_main(0, 0xFF, 0);
        osRecvMesg(&D_800BBB00_main, &D_800BCC88_main, OS_MESG_BLOCK);
        func_8004D788_main(perf0);
        intMask = osSetIntMask(OS_IM_NONE);
        D_800BCC84_main = NULL;
        D_800BCC88_main = NULL;
        osSetIntMask(intMask);
        osRecvMesg(&D_800BBB38_main, NULL, OS_MESG_BLOCK);
        func_8004D788_main(perf1);
        osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
        if ((s32)task->msg & 1) {
            func_8004D888_main();
        }
    }
}
