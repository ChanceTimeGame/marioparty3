#include "common.h"
#include "PR/os_internal.h"
#include "PR/sptask.h"
#include "PR/rcp.h"
#include "PR/rdb.h"
#include "rmonint.h"

#define UNUSED __attribute__((unused))

extern int D_800A4320_main;       // __rmonActive
extern vu32 D_800C8F50_main;      // somethingToDo
extern u32 D_800C8F60_main[280];  // inbuffer
extern u8 D_800C93C1_main;        // cmdoutptr
extern u8 D_800C93C0_main;        // cmdinptr
extern int D_800C93C4_main;       // state
extern char *D_800C93C8_main;     // inPointer
extern OSMesgQueue D_800D6A60_main; // __rmonMQ

void __rmonSendHeader(KKHeader *const block, u32 blockSize, u32 type) {
    int sent;
    char *cPtr = (char *)block;

    block->rev = KK_REV;
    block->type = type;

    sent = 0;
    while (sent < blockSize) {
        sent += __osRdbSend((u8 *)cPtr + sent, blockSize - sent, RDB_TYPE_GtoH_DEBUG);
    }
}

void __rmonSendReply(KKHeader *const block, u32 blockSize, u32 replyType) {
    char *cPtr;
    int sent = 0;

    block->length = blockSize;
    cPtr = (char *)&blockSize;

    while (sent < (signed)sizeof(blockSize)) {
        sent += __osRdbSend((u8 *)cPtr + sent, sizeof(blockSize) - sent, RDB_TYPE_GtoH_DEBUG);
    }

    __rmonSendHeader(block, blockSize, replyType);
    __rmonIOflush();
}

void __rmonSendData(char *const block, unsigned int blockSize) {
    int *blockPointer = (int *)block;
    unsigned int wordCount = (u32)(blockSize + 3) / 4;
    u32 data;
    union {
        char bufBytes[4];
        u32 bufWord;
    } buffer;

    if (((u32)block & 3) == 0) {
        while (wordCount--) {
            if ((u32)blockPointer >= SP_DMEM_START && (u32)blockPointer < 0x05000000) {
                __osSpRawReadIo((u32)blockPointer++, &data);
                __rmonIOputw(data);
            } else {
                __rmonIOputw(*(blockPointer++));
            }
        }
    } else {
        while (wordCount--) {
            __rmonMemcpy((u8 *)buffer.bufBytes, (u8 *)blockPointer, sizeof(buffer));
            __rmonIOputw(buffer.bufWord);
            blockPointer++;
        }
    }

    __rmonIOflush();
}

void rmonMain(void *arg) {
    register int newChars UNUSED;

    D_800C8F50_main = 0;
    D_800C93C1_main = 0;
    D_800C93C0_main = 0;
    __rmonInit();
    D_800A4320_main = TRUE;
    D_800C93C4_main = 0, newChars = 0, D_800C93C8_main = (void *)&D_800C8F60_main;

    for (;;) {
        OSMesg work;

        osRecvMesg(&D_800D6A60_main, &work, OS_MESG_BLOCK);
        D_800C8F50_main |= (u32)work;

        if (D_800C8F50_main & RMON_MESG_CPU_BREAK) {
            D_800C8F50_main &= ~RMON_MESG_CPU_BREAK;
            __rmonHitBreak();
        }

        if (D_800C8F50_main & RMON_MESG_SP_BREAK) {
            D_800C8F50_main &= ~RMON_MESG_SP_BREAK;
            __rmonHitSpBreak();
        }

        if (D_800C8F50_main & RMON_MESG_FAULT) {
            D_800C8F50_main &= ~RMON_MESG_FAULT;
            __rmonHitCpuFault();
        }

        if (D_800C8F50_main & 0x10) {
            D_800C8F50_main;
            D_800C8F50_main &= (u8)~0x10;
        }

        if (D_800C8F50_main & 0x20) {
            D_800C8F50_main;
            D_800C8F50_main &= (u8)~0x20;
        }
    }
}
