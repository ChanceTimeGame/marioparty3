#include "common.h"
#include "PR/rdb.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"

extern rdbPacket *D_800D5554_main; // __osRdb_IP6_Data
extern u32 D_800CE174_main;        // __osRdb_IP6_Size
extern u32 D_800D6A8C_main;        // __osRdb_IP6_Ct
extern u32 D_800CC43C_main;        // __osRdb_IP6_CurWrite
extern u32 D_800A2D80_main;        // __osRdb_IP6_Empty

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

u32 __osRdbSend(u8 *buf, u32 size, u32 type) {
    rdbPacket *pPtr;
    rdbPacket pkt;
    u32 len;
    u32 c;
    u32 inCt = 0;
    u32 needFirst = 0;
    u32 mask;
    u32 sent = 0;

    mask = __osDisableInt();

    if (D_800A2D80_main != 0) {
        D_800A2D80_main = 0;
        pkt.type = type;

        len = MIN(size, sizeof(pkt.buf));

        pkt.length = len;

        c = 0;
        while (c < len) {
            pkt.buf[c++] = buf[inCt++];
        }

        size -= len;
        sent = len;
        needFirst = 1;
    }

    while (size != 0 && D_800D6A8C_main < D_800CE174_main) {
        len = MIN(size, sizeof(pPtr->buf));

        pPtr = &D_800D5554_main[D_800CC43C_main];

        pPtr->type = type;
        pPtr->length = len;

        c = 0;
        while (c < len) {
            pPtr->buf[c++] = buf[inCt++];
        }

        D_800CC43C_main++;
        if (D_800CC43C_main >= D_800CE174_main) {
            D_800CC43C_main = 0;
        }

        D_800D6A8C_main++;
        size -= len;
        sent += len;
    }

    if (needFirst) {
        *(u32 *)RDB_BASE_REG = *(u32 *)&pkt;
    }
    __osRestoreInt(mask);

    return sent;
}
