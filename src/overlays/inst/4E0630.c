#include "common.h"

/* Model part name lists (D_8010D4C0_inst[type][0..1]): the parts of the instruction board
   model func_80107470_inst marks. */
#define INST_PART_LIST(n) struct { s16 count; const char *names[n]; }
typedef INST_PART_LIST(1) InstPartList; /* names[count] */

const INST_PART_LIST(4) D_8010D770_inst = { 4, { "4p_1", "4p_2", "4p_3", "4p_4" } };
const INST_PART_LIST(1) D_8010D7A4_inst = { 0, { "" } };
const INST_PART_LIST(4) D_8010D7B0_inst = { 4, { "2vs2_1", "2vs2_2", "2vs2_3", "2vs2_4" } };
const INST_PART_LIST(1) D_8010D7E4_inst = { 0, { "" } };
const INST_PART_LIST(4) D_8010D7EC_inst = { 4, { "3vs1_1", "3vs1_2", "3vs1_3", "3vs1_4" } };
const INST_PART_LIST(1) D_8010D820_inst = { 0, { "" } };
const INST_PART_LIST(4) D_8010D828_inst = { 4, { "battle1", "battle2", "battle3", "battle4" } };
const INST_PART_LIST(1) D_8010D85C_inst = { 0, { "" } };
const INST_PART_LIST(2) D_8010D864_inst = { 2, { "duel1", "duel2" } };
const INST_PART_LIST(1) D_8010D880_inst = { 0, { "" } };
const INST_PART_LIST(1) D_8010D888_inst = { 1, { "item_chara" } };
const INST_PART_LIST(5) D_8010D89C_inst = { 5, { "item1", "item2", "item3", "item4", "item5" } };
const INST_PART_LIST(1) D_8010D8DC_inst = { 1, { "omake1" } };
const INST_PART_LIST(1) D_8010D8EC_inst = { 0, { "" } };
const INST_PART_LIST(1) D_8010D8F4_inst = { 1, { "last1" } };
const INST_PART_LIST(1) D_8010D904_inst = { 0, { "" } };

/* Per minigame type: the board's two texture/model ids (low halves of 0x0017xxxx). */
const s32 D_8010D90C_inst[9][2] = {
    { 0x10, 0x18 }, { 0x11, 0x19 }, { 0x12, 0x1A }, { 0x13, 0x1B }, { 0x14, 0x1C },
    { 0x15, 0x1D }, { 0x15, 0x1D }, { 0x17, 0x1F }, { 0x16, 0x1E },
};
/* Per minigame type: the title model. */
const s32 D_8010D954_inst[9] = {
    0x00170020, 0x00170021, 0x00170022, 0x00170023, 0x00170024,
    0x00170025, 0x00170025, 0x00170027, 0x00170026,
};

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107470_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107938_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801079CC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107A24_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107BE4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E0630", D_8010D978_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E0630", D_8010D980_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107BF8_inst);

void func_80107E18_inst(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107E20_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107E98_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107EE0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107F18_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107F98_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801080A8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801080FC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_8010815C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108350_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_8010872C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108808_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108870_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108954_inst);

void func_80108A10_inst(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108A18_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80108AF0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801094B0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801097DC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_8010986C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801098D8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_801099C0_inst);

void func_80109A84_inst(void) {
}
