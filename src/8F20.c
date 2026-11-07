#include "common.h"

/* Audio manager thread (N64 SDK audiomgr.c), from MP2 src/169B0.c and MP1 src/138F0.c. */

#include "PR/libaudio.h"
#include "PR/sptask.h"
#include "PR/ucode.h"

/* The sound config, viewed from here (layout as MP2's AMConfig). */
typedef struct AMConfig {
    /* 0x00 */ s32 unk_00[5];
    /* 0x14 */ u8* heapBase;
    /* 0x18 */ s32 heapSize;
    /* 0x1C */ s32 outputRate;
    /* 0x20 */ s32 maxVoices;
    /* 0x24 */ s32 maxUpdates;
    /* 0x28 */ char unk_28[0x4];
    /* 0x2C */ s32* params; /* NULL: no effect; else a custom effect */
    /* 0x30 */ s32 maxACMDSize;
    /* 0x34 */ s32 numDMABuffers;
    /* 0x38 */ s32 dmaBufferLength;
    /* 0x3C */ s32 frameLag;
    /* 0x40 */ s32 framesPerField;
    /* 0x44 */ s32 fieldRate;
    /* 0x48 */ s32 extraSamples;
    /* 0x4C */ char unk_4C[0x10];
    /* 0x5C */ OSPri pri;
    /* 0x60 */ OSId id;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ OSPiHandle* unk_68;
} AMConfig;

typedef struct AMTask {
    /* 0x00 */ OSTask list;
    /* 0x40 */ OSMesgQueue* msgQ;
    /* 0x44 */ OSMesg msg;
} AMTask; /* size = 0x48 */

struct AudioInfo;

typedef struct AMAudioMsg {
    /* 0x00 */ s16 type;
    /* 0x04 */ struct AudioInfo* done;
} AMAudioMsg;

typedef struct AudioInfo {
    /* 0x00 */ s16* data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ AMTask task;
    /* 0x50 */ AMAudioMsg msg;
} AudioInfo; /* size = 0x58 */

typedef struct AMAudioMgr {
    /* 0x000 */ Acmd* ACMDList[2];
    /* 0x008 */ AudioInfo* audioInfo[3];
    /* 0x018 */ OSThread thread;
    /* 0x1C8 */ OSMesgQueue audioFrameMsgQ;
    /* 0x1E0 */ OSMesg audioFrameMsgBuf[8];
    /* 0x200 */ OSMesgQueue audioReplyMsgQ;
    /* 0x218 */ OSMesg audioReplyMsgBuf[8];
    /* 0x238 */ ALGlobals g;
} AMAudioMgr; /* size = 0x288 */

typedef struct DMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} DMABuffer; /* size = 0x14 */

typedef struct DMAState {
    /* 0x00 */ DMABuffer* firstUsed;
    /* 0x04 */ DMABuffer* firstFree;
} DMAState;

/* Scheduler client (0x10 bytes), followed directly by the 0x2000-byte audio thread stack. */
extern u8 D_800A97C0_main[];
extern OSMesgQueue* D_800AB7D0_main; /* scheduler audio queue; its address is also the stack top */
extern AMAudioMgr D_800AB7D8_main;
extern DMAState D_800ABA70_main;
extern u32 D_800ABA78_main; /* audFrameCt */
extern s32 D_800ABA7C_main; /* nextDMA */
extern s32 D_800ABA80_main; /* DMA buffer length */
extern u32 D_800ABA84_main; /* frame lag */
extern s32 D_800ABA88_main; /* curAcmdList */
extern u32 D_800ABA8C_main; /* minFrameSize */
extern u32 D_800ABA90_main; /* maxFrameSize */
extern u32 D_800ABA94_main; /* frameSize */
extern s32 D_800ABA98_main; /* AMConfig.extraSamples */
extern OSIoMesg D_800ABAA0_main[]; /* one PI request per DMA this frame */
extern OSMesgQueue D_800ABDA0_main;
extern OSMesg D_800ABDB8_main[];
extern OSPiHandle* D_800ABE38_main;
extern s32 D_800ABE3C_main;
extern OSMesgQueue D_800CC3A0_main;
extern u64 n_aspMain_code[];
extern u64 n_aspMain_data[];

void* func_800010B8_main(s32 size);
void func_80002528_main(void);
void func_800023B4_main(void);
void func_80006E30_main(void);
void func_80006FC4_main(void);
void func_8006B720_main(ALGlobals* g, ALSynConfig* c); /* alInit */
void func_8006B764_main(ALGlobals* g);                 /* alClose */
void AddSchedulerClient(void* client, OSMesgQueue* msgQ, s32 mask);
void RemoveSchedulerClient(void* client);

void func_80008750_main(void* arg);
u32 func_8000889C_main(AudioInfo* info, AudioInfo* lastInfo);
void func_800089D8_main(AudioInfo* info);
s32 func_800089E0_main(s32 addr, s32 len, void* state);
ALDMAproc func_80008B94_main(void* state);
void func_80008BAC_main(void);
void func_80008CC0_main(s32 arg0, s32 remove);
void func_80008D28_main(AMTask* t, AMAudioMsg* msg, Acmd* cmdp);
Acmd* func_8006BA3C_main(Acmd* cmdList, s32* cmdLen, s16* outBuf, s32 outLen); /* n_alAudioFrame */

s32 func_80008320_main(AMConfig* amc, ALHeap* heap) {
    ALSynConfig c;
    f32 fsize;
    s32 i;
    DMABuffer* dmaBuffs;

    c.outputRate = osAiSetFrequency(amc->outputRate);
    D_800ABA98_main = amc->extraSamples;
    fsize = (f32) amc->framesPerField * c.outputRate / (f32) amc->fieldRate;
    D_800ABA94_main = (s32) fsize;
    if (D_800ABA94_main < fsize) {
        D_800ABA94_main++;
    }
    D_800ABA94_main = (D_800ABA94_main / 184 + 1) * 184;
    D_800ABA8C_main = D_800ABA94_main - 184;
    D_800ABA90_main = D_800ABA94_main;
    D_800ABE3C_main = 1;
    if (amc->params != NULL) {
        c.fxType = AL_FX_CUSTOM;
        c.params = amc->params;
    } else {
        c.fxType = AL_FX_NONE;
        c.params = NULL;
    }
    c.maxVVoices = c.maxPVoices = amc->maxVoices;
    c.maxUpdates = amc->maxUpdates;
    c.dmaproc = func_80008B94_main;
    c.heap = heap;
    c.maxFXbusses = 0;
    func_8006B720_main(&D_800AB7D8_main.g, &c);
    D_800ABA88_main = 0;
    D_800ABA7C_main = 0;
    D_800ABA78_main = 0;
    D_800ABA80_main = amc->dmaBufferLength;
    D_800ABA84_main = amc->frameLag;
    dmaBuffs = func_800010B8_main(amc->numDMABuffers * sizeof(DMABuffer));
    if (dmaBuffs == NULL) {
        return 1;
    }
    dmaBuffs[amc->numDMABuffers - 1].node.next = NULL;
    dmaBuffs[0].node.next = NULL;
    dmaBuffs[0].node.prev = NULL;
    for (i = 0; i < amc->numDMABuffers - 1; i++) {
        alLink(&dmaBuffs[i + 1].node, &dmaBuffs[i].node);
        if ((dmaBuffs[i].ptr = func_800010B8_main(D_800ABA80_main)) == NULL) {
            return 1;
        }
    }
    if ((dmaBuffs[i].ptr = func_800010B8_main(D_800ABA80_main)) == NULL) {
        return 1;
    }
    D_800ABA70_main.firstUsed = NULL;
    D_800ABA70_main.firstFree = dmaBuffs;
    D_800ABE38_main = amc->unk_68;
    for (i = 0; i < 2; i++) {
        if ((D_800AB7D8_main.ACMDList[i] = func_800010B8_main(amc->maxACMDSize * sizeof(Acmd))) == NULL) {
            return 2;
        }
    }
    for (i = 0; i < 3; i++) {
        if ((D_800AB7D8_main.audioInfo[i] = func_800010B8_main(sizeof(AudioInfo))) == NULL) {
            return 3;
        }
        D_800AB7D8_main.audioInfo[i]->msg.type = 0;
        D_800AB7D8_main.audioInfo[i]->msg.done = D_800AB7D8_main.audioInfo[i];
        D_800AB7D8_main.audioInfo[i]->data = func_800010B8_main(D_800ABA90_main * 4);
        if (D_800AB7D8_main.audioInfo[i]->data == NULL) {
            return 4;
        }
    }
    return 0;
}

void func_80008678_main(AMConfig* amc) {
    osCreateMesgQueue(&D_800AB7D8_main.audioReplyMsgQ, D_800AB7D8_main.audioReplyMsgBuf, 8);
    osCreateMesgQueue(&D_800ABDA0_main, D_800ABDB8_main, 0x20);
    func_80008CC0_main(amc->unk_64, 0);
    // Stack top: end of the 0x2000-byte stack after the 0x10-byte client.
    osCreateThread(&D_800AB7D8_main.thread, amc->id, func_80008750_main, NULL, D_800A97C0_main + 0x2010, amc->pri);
    osStartThread(&D_800AB7D8_main.thread);
}

void func_8000870C_main(AMConfig* amc) {
    osDestroyThread(&D_800AB7D8_main.thread);
    func_8006B764_main(&D_800AB7D8_main.g);
    func_80008CC0_main(amc->unk_64, 1);
}

void func_80008750_main(void* arg) {
    OSMesg msg;
    AMAudioMsg* reply;
    s32 done = 0;
    AudioInfo* lastInfo = NULL;

    do {
        osRecvMesg(&D_800AB7D8_main.audioFrameMsgQ, &msg, OS_MESG_BLOCK);
        switch ((u32)msg) {
            case 1:
                if (func_8000889C_main(D_800AB7D8_main.audioInfo[D_800ABA78_main % 3], lastInfo)) {
                    osRecvMesg(&D_800AB7D8_main.audioReplyMsgQ, (OSMesg*)&reply, OS_MESG_BLOCK);
                    func_800089D8_main(reply->done);
                    lastInfo = reply->done;
                    func_800023B4_main();
                    func_80006E30_main();
                }
                break;
            case 2:
                done = 1;
                func_80002528_main();
                func_80006FC4_main();
                break;
            case 10:
                done = 1;
                break;
        }
    } while (!done);
    func_8006B764_main(&D_800AB7D8_main.g);
}

/* __amHandleFrameMsg (n_audio audiomgr.c): synthesize the next audio frame and send its task.
   The first frame after a long enough backlog is the short (minFrameSize) one. */
u32 func_8000889C_main(AudioInfo* info, AudioInfo* lastInfo) {
    s16* audioPtr;
    Acmd* cmdp;
    s32 cmdLen;
    s32 samplesLeft;

    samplesLeft = osAiGetLength() >> 2;
    func_80008BAC_main();
    audioPtr = (s16*) osVirtualToPhysical(info->data);
    if (lastInfo != NULL) {
        osAiSetNextBuffer(lastInfo->data, lastInfo->frameSamples << 2);
    }
    if (samplesLeft > D_800ABA98_main + 184 && D_800ABE3C_main) {
        info->frameSamples = D_800ABA8C_main;
        D_800ABE3C_main = 0;
    } else {
        info->frameSamples = D_800ABA94_main;
        D_800ABE3C_main = 1;
    }
    cmdp = func_8006BA3C_main(D_800AB7D8_main.ACMDList[D_800ABA88_main], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    func_80008D28_main(&info->task, &info->msg, cmdp);
    osSendMesg(D_800AB7D0_main, &info->task, OS_MESG_BLOCK);
    D_800ABA88_main ^= 1;
    return 1;
}

void func_800089D8_main(AudioInfo* info) {
}

/* N64 SDK audiomgr.c __amDma, the PI request written out in place. */
s32 func_800089E0_main(s32 addr, s32 len, void* state) {
    void* foundBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    DMABuffer* dmaPtr;
    DMABuffer* lastDmaPtr;
    OSIoMesg* mb;

    lastDmaPtr = NULL;
    dmaPtr = D_800ABA70_main.firstUsed;
    addrEnd = addr + len;
    while (dmaPtr != NULL) {
        buffEnd = dmaPtr->startAddr + D_800ABA80_main;
        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = D_800ABA78_main;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (DMABuffer*)dmaPtr->node.next;
    }

    dmaPtr = D_800ABA70_main.firstFree;
    if (dmaPtr == NULL) {
        return osVirtualToPhysical(D_800ABA70_main.firstUsed);
    }
    D_800ABA70_main.firstFree = (DMABuffer*)dmaPtr->node.next;
    alUnlink(&dmaPtr->node);
    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (D_800ABA70_main.firstUsed != NULL) {
        lastDmaPtr = D_800ABA70_main.firstUsed;
        D_800ABA70_main.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        D_800ABA70_main.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_800ABA78_main;
    mb = &D_800ABAA0_main[D_800ABA7C_main++];
    mb->hdr.pri = OS_MESG_PRI_NORMAL;
    mb->hdr.retQueue = &D_800ABDA0_main;
    mb->dramAddr = foundBuffer;
    mb->devAddr = addr;
    mb->size = D_800ABA80_main;
    osEPiStartDma(D_800ABE38_main, mb, OS_READ);
    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc func_80008B94_main(void* state) {
    *(DMAState**)state = &D_800ABA70_main;
    return (ALDMAproc)func_800089E0_main;
}

/* audiomgr.c __clearAudioDMA */
void func_80008BAC_main(void) {
    OSMesg iomsg;
    u32 i;
    DMABuffer* dmaPtr;
    DMABuffer* nextPtr;

    for (i = 0; i < D_800ABA7C_main; i++) {
        osRecvMesg(&D_800ABDA0_main, &iomsg, OS_MESG_NOBLOCK);
    }
    dmaPtr = D_800ABA70_main.firstUsed;
    while (dmaPtr != NULL) {
        nextPtr = (DMABuffer*)dmaPtr->node.next;
        if (dmaPtr->lastFrame + D_800ABA84_main < D_800ABA78_main) {
            if (D_800ABA70_main.firstUsed == dmaPtr) {
                D_800ABA70_main.firstUsed = nextPtr;
            }
            alUnlink(&dmaPtr->node);
            if (D_800ABA70_main.firstFree != NULL) {
                alLink(&dmaPtr->node, &D_800ABA70_main.firstFree->node);
            } else {
                D_800ABA70_main.firstFree = dmaPtr;
                dmaPtr->node.next = NULL;
                dmaPtr->node.prev = NULL;
            }
        }
        dmaPtr = nextPtr;
    }
    D_800ABA7C_main = 0;
    D_800ABA78_main++;
}

void func_80008CC0_main(s32 arg0, s32 remove) {
    if (remove) {
        RemoveSchedulerClient(D_800A97C0_main);
        return;
    }
    osCreateMesgQueue(&D_800AB7D8_main.audioFrameMsgQ, D_800AB7D8_main.audioFrameMsgBuf, 8);
    D_800AB7D0_main = &D_800CC3A0_main;
    AddSchedulerClient(D_800A97C0_main, &D_800AB7D8_main.audioFrameMsgQ, 3);
}

void func_80008D28_main(AMTask* t, AMAudioMsg* msg, Acmd* cmdp) {
    t->msgQ = &D_800AB7D8_main.audioReplyMsgQ;
    t->msg = msg;
    t->list.t.data_ptr = (u64*)D_800AB7D8_main.ACMDList[D_800ABA88_main];
    t->list.t.data_size = (cmdp - D_800AB7D8_main.ACMDList[D_800ABA88_main]) * sizeof(Acmd);
    t->list.t.type = M_AUDTASK;
    t->list.t.ucode_boot = (u64*)rspbootTextStart;
    t->list.t.ucode_boot_size = (u32)gspF3DEX2_fifoTextStart - (u32)rspbootTextStart;
    t->list.t.flags = 0;
    t->list.t.ucode = n_aspMain_code;
    t->list.t.ucode_data = n_aspMain_data;
    t->list.t.ucode_data_size = 0x800;
    t->list.t.dram_stack = NULL;
    t->list.t.dram_stack_size = 0;
    t->list.t.output_buff = NULL;
    t->list.t.output_buff_size = 0;
    t->list.t.yield_data_ptr = NULL;
    t->list.t.yield_data_size = 0;
}
