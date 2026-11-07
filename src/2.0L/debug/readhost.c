#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

extern int D_800A4040_main;           // readHostInitialized
extern OSMesgQueue D_800C4CD0_main;   // readHostMesgQueue
extern OSMesg D_800C4CE8_main[1];     // readHostMesgBuf
extern u32 D_800D5200_main;           // __osRdb_Read_Data_Buf
extern u32 D_800CDA78_main;           // __osRdb_Read_Data_Ct

void osReadHost(void *dramAddr, u32 nbytes) {
    char tstr[4];
    u32 sent = 0;

    if (!D_800A4040_main) {
        osCreateMesgQueue(&D_800C4CD0_main, D_800C4CE8_main, 1);
        osSetEventMesg(OS_EVENT_RDB_READ_DONE, &D_800C4CD0_main, NULL);
        D_800A4040_main = TRUE;
    }

    D_800D5200_main = (u32)dramAddr;
    D_800CDA78_main = nbytes;

    while (sent == 0) {
        sent += __osRdbSend((u8 *)tstr, 1, RDB_TYPE_GtoH_READY_FOR_DATA);
    }

    osRecvMesg(&D_800C4CD0_main, NULL, OS_MESG_BLOCK);
    return;
}
