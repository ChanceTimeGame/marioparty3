#include "common.h"

s16 func_8000B0D4_main(s32, s32);
void func_80017358_main(s16 arg0, char *arg1, s16 arg2, char *arg3);

void func_8010A750_inst(omObjData *obj);
void func_8010B040_inst(void);

extern s8 D_8010D400_inst[];
extern s8 D_8010D40A_inst;
extern s8 D_8010D40C_inst[];
extern s16 *D_8010D4C0_inst[][2];
extern u8 D_8010D554_inst[];
extern char *D_8010D55C_inst[];
extern s32 D_8010D57C_inst[];
extern char *D_8010D58C_inst[];
extern omObjData *D_8010DC90_inst;
extern void (*D_8010DC94_inst)(omObjData *);
extern s16 D_8010DC98_inst[];

const s32 D_8010D9C8_inst[] = { 0x0017002E, 0x0017002F, 0x00170030, 0x00170031,
                                0x00170032, 0x00170033, 0x00170034, 0x00170035 };
const s32 D_8010D9E8_inst[] = { 0x00170038, 0x00170039, 0x0017003A, 0x0017003B, 0x0017003C,
                                0x0017003D, 0x0017003E, 0x0017003F, 0x00170040, 0x00170041,
                                0x00170042, 0x00170045, 0x00170044, 0x00170043, 0x00170046 };

void func_8010A1D0_inst(void) {
    omObjData *obj;
    s16 *count;
    s32 i;
    s16 model;
    s32 player;

    obj = omAddObj(0x15, 30, 1, -1, NULL);
    D_8010DC90_inst = obj;
    func_8010B040_inst();
    count = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < *count; i++) {
        obj->model[1 + i] = func_8000B0D4_main(D_8010D57C_inst[D_8010D554_inst[i]], 0x1AB9);
    }
    obj->model[5] = func_8000B0D4_main(0x170036, 0x16B9);
    for (i = 1; i < *count; i++) {
        obj->model[5 + i] = Hu3DModelLink(obj->model[5]);
    }
    for (i = 0; i < *count; i++) {
        player = D_8010D400_inst[i];
        D_8010DC98_inst[i] = model = func_8000B0D4_main(D_8010D9C8_inst[GwPlayer[player].chr], 0x1AB9);
        func_80017358_main(model, D_8010D55C_inst[GwPlayer[player].chr], obj->model[1 + i],
                           D_8010D58C_inst[D_8010D554_inst[i]]);
        func_8001C258_main(D_8010DC98_inst[i], 4, 4);
        func_8001C6A8_main(obj->model[1 + i], 0.0f);
        func_8001C814_main(obj->model[1 + i], 2, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    for (i = 0; i < *count; i++) {
        Hu3DModelPosSet(obj->model[1 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[1 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[1 + i], 4, 0);
        func_8001C814_main(obj->model[1 + i], 1, 1);
        Hu3DModelPosSet(obj->model[5 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[5 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[5 + i], 4, 4);
        func_8001C814_main(obj->model[5 + i], 1, 1);
    }
    count = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < *count; i++) {
        obj->model[10 + i] = func_8000B0D4_main(D_8010D9E8_inst[D_8010D40C_inst[i]], 0x1AB9);
    }
    if (*count > 0) {
        obj->model[15] = func_8000B0D4_main(0x170037, 0x16B9);
        for (i = 1; i < *count; i++) {
            obj->model[15 + i] = Hu3DModelLink(obj->model[15]);
        }
    }
    for (i = 0; i < *count; i++) {
        Hu3DModelPosSet(obj->model[10 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[10 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[10 + i], 4, 0);
        func_8001C814_main(obj->model[10 + i], 1, 1);
        Hu3DModelPosSet(obj->model[15 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[15 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[15 + i], 4, 4);
        func_8001C814_main(obj->model[15 + i], 1, 1);
    }
    D_8010DC94_inst = func_8010A750_inst;
    while (TRUE) {
        D_8010DC94_inst(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A750_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AC04_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AC30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AD78_inst);

void func_8010B038_inst(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA34_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA44_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA54_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA64_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA74_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA84_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA94_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAA4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAB0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DABC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAC8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B040_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B0FC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B10C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B118_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B124_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B2A4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B628_inst);
