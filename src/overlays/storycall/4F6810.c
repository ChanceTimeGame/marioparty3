#include "common.h"

// m1 lf1
extern u8 D_800CE20A_main; /* story event to call; the board-story player's coin field carries the variant */

void func_801059A0_storycall(void) {
    s32 event = D_800CE20A_main;

    omInitObjMan(10, 10);
    switch (event) {
    case 1:
        omOvlGotoEx(0x7A, 1, 0x192);
        break;
    case 3:
        GwPlayer[0].coin = 0;
        omOvlGotoEx(0x6B, 0, 0x94);
        break;
    case 5:
        GwPlayer[0].coin = 1;
        omOvlGotoEx(0x6B, 0, 0x94);
        break;
    case 7:
        GwPlayer[0].coin = 2;
        omOvlGotoEx(0x6B, 0, 0x94);
        break;
    case 15:
        GwPlayer[0].coin = 0;
        omOvlGotoEx(0x6C, 0, 0x94);
        break;
    case 2:
        GwPlayer[0].coin = 1;
        omOvlGotoEx(0x6C, 0, 0x94);
        break;
    case 4:
        GwPlayer[0].coin = 2;
        omOvlGotoEx(0x6C, 0, 0x94);
        break;
    case 6:
        GwPlayer[0].coin = 3;
        omOvlGotoEx(0x6C, 0, 0x94);
        break;
    case 8:
        GwPlayer[0].coin = 4;
        omOvlGotoEx(0x6C, 0, 0x94);
        break;
    case 12:
        GwPlayer[0].coin = 0;
        omOvlGotoEx(0x6D, 0, 0x94);
        break;
    case 10:
        GwPlayer[0].coin = 1;
        omOvlGotoEx(0x6D, 0, 0x94);
        break;
    case 13:
        GwPlayer[0].coin = 0;
        omOvlGotoEx(0x6E, 0, 0x4190);
        break;
    case 14:
        GwPlayer[0].coin = 1;
        omOvlGotoEx(0x6E, 0, 0x4190);
        break;
    case 9:
        GwPlayer[0].coin = 0;
        omOvlGotoEx(0x6F, 0, 0x94);
        break;
    case 11:
        GwPlayer[0].coin = 1;
        omOvlGotoEx(0x6F, 0, 0x94);
        break;
    default:
        omOvlReturnEx(1);
        break;
    }
}
