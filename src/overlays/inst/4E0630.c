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

/* Views of hmfman.c's HmfMotionObjM / HmfDataM / HmfPartM (func_8001D33C_main's result). */
typedef struct InstHmfPart {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0x42];
} InstHmfPart; /* size 0x68 */
typedef struct InstHmfData {
    /* 0x00 */ char unk00[0x60];
    /* 0x60 */ InstHmfPart *parts;
} InstHmfData;
typedef struct InstMotionObj {
    /* 0x00 */ s16 count;
    /* 0x02 */ char unk02[0x4E];
    /* 0x50 */ s16 *children; /* part index, or 0x8000 | motion object index */
    /* 0x54 */ InstHmfData *hmf;
} InstMotionObj;

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

extern s8 D_8010D400_inst[7];
extern s8 D_8010D404_inst;
extern s8 D_8010D405_inst;
extern s8 D_8010D406_inst;
extern s8 D_8010D407_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst; /* minigame type */
extern s8 D_8010D40B_inst; /* minigame index */
extern f32 D_8010D414_inst; /* board tilt */
extern s32 D_8010D4A4_inst; /* instruction message */
extern s32 D_8010D508_inst;
extern f32 D_8010D50C_inst;
extern InstPartList *D_8010D4C0_inst[9][2];
extern void *D_8010DC10_inst;
extern void *D_8010DC14_inst;
extern void *D_8010DC18_inst;
extern omObjData *D_8010DDD8_inst;
extern void (*D_8010DDDC_inst)(omObjData *);

u16 func_8000B0D4_main(s32, s32);
void *func_8001D33C_main(s16 model, const char *name);
void func_80107938_inst(omObjData *);
void func_801079CC_inst(omObjData *);
void func_80107A24_inst(omObjData *);
void func_80107BF8_inst(omObjData *);
void func_80107E18_inst(omObjData *);
s8 func_8010B10C_inst(void);
void func_80107EE0_inst(void);
void func_8010815C_inst(omObjData *);
void func_80108AF0_inst(s16, void *, void *, void *);

/* Process: builds the instruction board object (model 0 the board, 2 the text page, 4 the
   title, 6 the cursor, 8 the frame), marks the parts named by the type's part lists, loads
   the message pages and runs the current page handler (D_8010DDDC_inst) every frame. */
#ifdef NON_MATCHING
/* Matches except scheduling in the part loop (masked 2: the parts pointer is loaded before
   the index arithmetic). */
void func_80107470_inst(void) {
    omObjData *obj;
    InstPartList *list;
    InstHmfData *hmf;
    InstMotionObj *part;
    s32 i;
    s32 j;
    s32 k;
    s16 idx;

    obj = omAddObj(0x14, 10, 5, -1, NULL);
    D_8010DDD8_inst = obj;
    obj->model[0] = func_8000B0D4_main(D_8010D90C_inst[D_8010D40A_inst][0] | 0x170000, 0x16B9);
    obj->model[1] = func_8000B0D4_main(0x170029, 0x1E89);
    obj->model[2] = func_8000B0D4_main(D_8010D954_inst[D_8010D40A_inst], 0x1AB9);
    obj->model[3] = func_8000B0D4_main(0x170028, 0x2B9);
    obj->model[4] = func_8000B0D4_main(D_8010D90C_inst[D_8010D40A_inst][1] | 0x170000, 0x239);
    func_8001C814_main(obj->model[0], 2, 0);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C814_main(obj->model[2], 2, 0);
    func_8001C814_main(obj->model[3], 2, 0);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C814_main(obj->model[1], 1, 1);
    func_8001C814_main(obj->model[2], 1, 1);
    func_8001C814_main(obj->model[3], 1, 1);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(obj->model[2], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(obj->model[3], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    for (i = 0; i < 5; i++) {
        Hu3DModelScaleSet(obj->model[i], 0.5f, 0.5f, 0.5f);
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(obj->model[i + 1], 0.45f, 0.45f, 0.45f);
    }
    for (k = 0; k < 2; k++) {
        list = D_8010D4C0_inst[D_8010D40A_inst][k];
        for (j = 0; j < list->count; j++) {
            part = func_8001D33C_main(obj->model[0], list->names[j]);
            hmf = part->hmf;
            for (i = 0; i < part->count; i++) {
                idx = part->children[i];
                if (idx >= 0) {
                    hmf->parts[idx].unk24 = 1;
                }
            }
        }
    }
    D_8010DC10_inst = DataRead(D_8010D4A4_inst | 0x170000);
    D_8010DC18_inst = DataRead((D_8010D4A4_inst + 1) | 0x170000);
    D_8010DC14_inst = DataRead(0x170007);
    func_80108AF0_inst(obj->model[1], D_8010DC18_inst, D_8010DC10_inst, D_8010DC14_inst);
    HmfModelData[obj->model[1]].rot.x = -90.0f;
    omPrcSetDestructor(0, func_80107EE0_inst);
    if (D_8010D408_inst == 0) {
        D_8010DDDC_inst = func_80107938_inst;
    } else {
        D_8010DDDC_inst = func_8010815C_inst;
    }
    while (TRUE) {
        D_8010DDDC_inst(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107470_inst);
#endif

/* Page handler: waits for the text window, then starts the board and title motions. */
void func_80107938_inst(omObjData *obj) {
    if (func_8010B10C_inst() == 1) {
        func_8001C814_main(obj->model[1], 1, 0);
        func_8001C814_main(obj->model[2], 1, 0);
        func_8001C258_main(obj->model[1], 4, 0);
        func_8001C258_main(obj->model[2], 4, 0);
        D_8010DDDC_inst = func_801079CC_inst;
    }
}

void func_801079CC_inst(omObjData *obj) {
    func_8001C814_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    D_8010DDDC_inst = func_80107A24_inst;
}

/* Page handler: tilts the board and title up and grows the page models with the cursor
   model's motion, then idles. */
void func_80107A24_inst(omObjData *obj) {
    f32 frames;
    f32 rot;
    s32 i;

    frames = D_800CCF58_main[HmfModelData[obj->model[3]].unk02].unk02 - 25.0f;
    rot = D_8010D508_inst / frames * D_8010D414_inst;
    HmfModelData[obj->model[1]].rot.x = rot - 90.0f;
    HmfModelData[obj->model[2]].rot.x = rot;
    D_8010D50C_inst = 0.15f / frames * D_8010D508_inst;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(obj->model[i + 1], D_8010D50C_inst + 0.45f, D_8010D50C_inst + 0.45f, D_8010D50C_inst + 0.45f);
    }
    D_8010D508_inst++;
    if (D_8010D508_inst == frames) {
        D_8010DDDC_inst = func_80107E18_inst;
        D_8010D50C_inst = 0.0f;
        D_8010D508_inst = 0;
    }
}

void func_80107BE4_inst(void) {
    D_8010DDDC_inst = func_80107BF8_inst;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E0630", D_8010D978_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E0630", D_8010D980_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E0630", func_80107BF8_inst);

void func_80107E18_inst(omObjData *obj) {
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
