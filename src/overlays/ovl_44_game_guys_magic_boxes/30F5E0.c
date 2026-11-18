#include "ultra64.h"

// magic boxes C: a data-only object linked after 30DC30 (its .data follows 30DC30's), holding the face sprite file of
// each character; 308D10's func_80105FB4 copies it to the stack

typedef struct GgmFaces {
    s32 file[8];
} GgmFaces;

GgmFaces D_8010C270_game_guys_magic_boxes = { { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 } };
