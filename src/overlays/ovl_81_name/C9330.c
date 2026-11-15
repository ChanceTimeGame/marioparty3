#include "common.h"
#include "malloc.h"

/* Help/message window: one line of the message table D_80100F60, kept on screen by an object. */
typedef struct DuelHelpWin {
    /* 0x00 */ u8 msgIdx;
    /* 0x01 */ u8 hideOnFlag;
    /* 0x02 */ s16 x; /* -1: centred */
    /* 0x04 */ s16 y;
    /* 0x08 */ omObjData* obj;
    /* 0x0C */ s16 winID;
    /* 0x10 */ char* prefix;
} DuelHelpWin; // sizeof 0x14

extern s32 D_80100F60_name_81[];
extern u8 D_800D6A90_main;
extern s16 D_800D41C2_main;
extern const char D_80102450_name_81[]; /* "\x03%2d\x08", CA640 .rodata */

void func_800E1560_name_81(DuelHelpWin* arg0) {
    s16 size[2];

    if (arg0->prefix != NULL) {
        func_8006022C_main((u32)arg0->prefix, 0);
    }
    func_80060394_main(1, size, D_80100F60_name_81[arg0->msgIdx]);
    if (arg0->x == -1) {
        arg0->winID = func_8005A968_main(0xA0 - size[0] / 2, arg0->y, size[0], size[1], 0, 0);
    } else {
        arg0->winID = func_8005A968_main(arg0->x, arg0->y, size[0], size[1], 0, 4);
    }
    if (arg0->prefix != NULL) {
        func_8005B6BC_main(arg0->winID, (u32)arg0->prefix, 0);
    }
    func_8005BE30_main(arg0->winID, 5);
    func_8005BEE0_main(arg0->winID, 0);
    func_8005BDFC_main(arg0->winID, 0);
    func_8005B63C_main(arg0->winID, 0, 0x20000);
    func_8005B43C_main(arg0->winID, D_80100F60_name_81[arg0->msgIdx], -1, -1);
}

void func_800E1694_name_81(DuelHelpWin* arg0) {
    func_8005F364_main(arg0->winID);
    arg0->winID = -1;
}

void func_800E16C4_name_81(omObjData* arg0) {
    DuelHelpWin* win = (DuelHelpWin*)arg0->data;

    if ((win->hideOnFlag == 1) && (D_800D6A90_main != 0)) {
        if (win->winID >= 0) {
            func_800E1694_name_81(win);
        }
    } else if (win->winID < 0) {
        func_800E1560_name_81(win);
    }
}

DuelHelpWin* func_800E172C_name_81(s16 msgIdx, s16 x, s16 y, u16 hideOnFlag) {
    DuelHelpWin* win;
    omObjData* obj;
    char* str;

    win = HuMemMemoryAllocTemp(sizeof(DuelHelpWin));
    if (win != NULL) {
        win->msgIdx = msgIdx;
        win->x = x;
        win->y = y;
        win->hideOnFlag = hideOnFlag;
        obj = omAddObj(0x100, 0, 0, -1, func_800E16C4_name_81);
        win->obj = obj;
        obj->data = win;
        omSetStatBit(win->obj, 0x80);
        win->winID = -1;
        if (msgIdx != 6) {
            win->prefix = NULL;
        } else {
            str = HuMemMemoryAllocTemp(8);
            win->prefix = str;
            sprintf(str, D_80102450_name_81, D_800D41C2_main);
            return win;
        }
    }
    return win;
}

DuelHelpWin* func_800E1824_name_81(s16 msgIdx, s16 y, u16 hideOnFlag) {
    return func_800E172C_name_81(msgIdx, -1, y, hideOnFlag);
}

void func_800E1854_name_81(DuelHelpWin* arg0) {
    if (arg0 != NULL) {
        arg0->obj->data = NULL;
        omDelObj(arg0->obj);
        if (arg0->winID >= 0) {
            func_8005F364_main(arg0->winID);
            if (arg0->prefix != NULL) {
                HuMemMemoryFreeTemp(arg0->prefix);
            }
        }
        HuMemMemoryFreeTemp(arg0);
    }
}
