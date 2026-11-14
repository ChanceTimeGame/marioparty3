#include "common.h"

/* A hook list (4DEB60 rodata): the number of hooks, then their names. */
typedef struct InstHookList {
    /* 0x00 */ s16 count;
    /* 0x04 */ char *names[1];
} InstHookList;

s16 func_8000B0D4_main(s32, s32);
void func_80016B00_main(s16 model, s16 frame, char *name, f32 (*mtx)[4][4]);
void func_8008A120_main(f32 (*m)[4], f32 angle);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]);
void func_80018044_main(f32 (*a)[4], f32 (*b)[4], f32 (*c)[4]);
void func_80017358_main(s16 arg0, char *arg1, s16 arg2, char *arg3);
s32 func_80107E20_inst(void);
void func_801080FC_inst(void);

void func_8010A750_inst(omObjData *obj);
void func_8010AC04_inst(omObjData *obj);
void func_8010AC30_inst(omObjData *obj);
void func_8010AD78_inst(omObjData *obj);
void func_8010B038_inst(omObjData *obj);
void func_8010B040_inst(void);
void func_8010B2A4_inst(omObjData *obj);
void func_8010B628_inst(omObjData *obj);

extern u8 D_800CB8B1_main[];

extern s8 D_8010D400_inst[];
extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D40C_inst[];
extern f32 D_8010D414_inst;
extern InstHookList *D_8010D4C0_inst[][2];
extern const char D_8010DA24_inst[];
extern const char D_8010DA34_inst[];
extern const char D_8010DA44_inst[];
extern const char D_8010DA54_inst[];
extern const char D_8010DA64_inst[];
extern const char D_8010DA74_inst[];
extern const char D_8010DA84_inst[];
extern const char D_8010DA94_inst[];
extern const char D_8010DAA4_inst[];
extern const char D_8010DAB0_inst[];
extern const char D_8010DABC_inst[];
extern const char D_8010DAC8_inst[];
/* .data (8010D550), defined here: after the last function KMC as puts that function's
   delay-slot nop at the start of .text. */
s8 D_8010D550_inst = 0;
s8 D_8010D551_inst = 0;
u8 D_8010D554_inst[4] = { 0, 0, 0, 0 }; /* hook colour per player */
s32 D_8010D558_inst = 0;
/* Per character: the grid part the hook hangs from. */
char *D_8010D55C_inst[8] = {
    (char *)D_8010DA94_inst, (char *)D_8010DA84_inst, (char *)D_8010DA74_inst, (char *)D_8010DA64_inst,
    (char *)D_8010DA54_inst, (char *)D_8010DA44_inst, (char *)D_8010DA34_inst, (char *)D_8010DA24_inst,
};
s32 D_8010D57C_inst[4] = { 0x17002A, 0x17002B, 0x17002C, 0x17002D }; /* hook model per colour */
/* Per hook colour: its part name. */
char *D_8010D58C_inst[4] = {
    (char *)D_8010DAC8_inst, (char *)D_8010DABC_inst, (char *)D_8010DAB0_inst, (char *)D_8010DAA4_inst,
};
s32 D_8010D59C_inst = 0;
s32 D_8010D5A0_inst = 0;
extern omObjData *D_8010DC90_inst;
extern void (*D_8010DC94_inst)(omObjData *);
extern f32 D_8010DC50_inst[4][4];
extern s16 D_8010DC98_inst[];
extern omObjData *D_8010DDD8_inst;

const s32 D_8010D9C8_inst[] = { 0x0017002E, 0x0017002F, 0x00170030, 0x00170031,
                                0x00170032, 0x00170033, 0x00170034, 0x00170035 };
const s32 D_8010D9E8_inst[] = { 0x00170038, 0x00170039, 0x0017003A, 0x0017003B, 0x0017003C,
                                0x0017003D, 0x0017003E, 0x0017003F, 0x00170040, 0x00170041,
                                0x00170042, 0x00170045, 0x00170044, 0x00170043, 0x00170046 };

void func_8010A1D0_inst(void) {
    omObjData *obj;
    InstHookList *list;
    s32 i;
    s16 model;
    s32 player;

    obj = omAddObj(0x15, 30, 1, -1, NULL);
    D_8010DC90_inst = obj;
    func_8010B040_inst();
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        obj->model[1 + i] = func_8000B0D4_main(D_8010D57C_inst[D_8010D554_inst[i]], 0x1AB9);
    }
    obj->model[5] = func_8000B0D4_main(0x170036, 0x16B9);
    for (i = 1; i < list->count; i++) {
        obj->model[5 + i] = Hu3DModelLink(obj->model[5]);
    }
    for (i = 0; i < list->count; i++) {
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
    for (i = 0; i < list->count; i++) {
        Hu3DModelPosSet(obj->model[1 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[1 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[1 + i], 4, 0);
        func_8001C814_main(obj->model[1 + i], 1, 1);
        Hu3DModelPosSet(obj->model[5 + i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[5 + i], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(obj->model[5 + i], 4, 4);
        func_8001C814_main(obj->model[5 + i], 1, 1);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        obj->model[10 + i] = func_8000B0D4_main(D_8010D9E8_inst[D_8010D40C_inst[i]], 0x1AB9);
    }
    if (list->count > 0) {
        obj->model[15] = func_8000B0D4_main(0x170037, 0x16B9);
        for (i = 1; i < list->count; i++) {
            obj->model[15 + i] = Hu3DModelLink(obj->model[15]);
        }
    }
    for (i = 0; i < list->count; i++) {
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

void func_8010A750_inst(omObjData *obj) {
    omObjData *host;
    InstHookList *list;
    f32 end;
    f32 frame;
    s8 i;
    HmfModel *mdl;

    host = D_8010DDD8_inst;
    end = D_800CCF58_main[HmfModelData[host->model[0]].unk02].unk02;
    frame = HmfModelData[host->model[0]].unk40;
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        mdl = &HmfModelData[obj->model[1 + i]];
        func_80016B00_main(host->model[0], frame, list->names[i], (f32 (*)[4][4])mdl->mtx);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        mdl = &HmfModelData[obj->model[10 + i]];
        func_80016B00_main(host->model[0], frame, list->names[i], (f32 (*)[4][4])mdl->mtx);
    }
    if (func_80107E20_inst() == 1) {
        list = D_8010D4C0_inst[D_8010D40A_inst][0];
        for (i = 0; i < list->count; i++) {
            func_8001C6A8_main(obj->model[1 + i], 0.0f);
            func_8001C814_main(obj->model[1 + i], 1, 0);
            HmfModelData[obj->model[1 + i]].rot.x = 0.0f;
            func_80016B00_main(host->model[0], end, list->names[i], &D_8010DC50_inst);
            Hu3DModelPosSet(obj->model[5 + i], D_8010DC50_inst[3][0] * 0.5f, D_8010DC50_inst[3][1] * 0.5f,
                            D_8010DC50_inst[3][2] * 0.5f);
        }
        list = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < list->count; i++) {
            func_8001C6A8_main(obj->model[10 + i], 0.0f);
            func_8001C814_main(obj->model[10 + i], 1, 0);
            HmfModelData[obj->model[10 + i]].rot.x = 0.0f;
            func_80016B00_main(host->model[0], end, list->names[i], &D_8010DC50_inst);
            Hu3DModelPosSet(obj->model[15 + i], D_8010DC50_inst[3][0] * 0.5f, D_8010DC50_inst[3][1] * 0.5f,
                            D_8010DC50_inst[3][2] * 0.5f);
        }
        if (D_8010D558_inst == 0) {
            if (D_8010D408_inst == 0) {
                D_8010DC94_inst = func_8010AC04_inst;
            } else {
                D_8010DC94_inst = func_8010B628_inst;
            }
        } else {
            D_8010DC94_inst = func_8010B038_inst;
        }
    }
}

void func_8010AC04_inst(omObjData *obj) {
    if (D_8010D550_inst == 1) {
        D_8010DC94_inst = func_8010AC30_inst;
    }
}

void func_8010AC30_inst(omObjData *obj) {
    InstHookList *list;
    s32 i;

    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8001C258_main(obj->model[5 + i], 4, 0);
        func_8001C6A8_main(obj->model[5 + i], 0.0f);
        func_8001C814_main(obj->model[5 + i], 1, 0);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        func_8001C258_main(obj->model[15 + i], 4, 0);
        func_8001C6A8_main(obj->model[15 + i], 0.0f);
        func_8001C814_main(obj->model[15 + i], 1, 0);
    }
    D_8010DC94_inst = func_8010AD78_inst;
}

void func_8010AD78_inst(omObjData *obj) {
    f32 rot[4][4];
    f32 mtx[4][4];
    InstHookList *list;
    f32 frames;
    s8 i;

    frames = D_800CCF58_main[HmfModelData[obj->model[5]].unk02].unk02 - 20.0f;
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, 1.0f / frames * D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, 1.0f / frames * D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
    }
    D_8010D59C_inst++;
    if (frames <= D_8010D59C_inst) {
        D_8010DC94_inst = func_8010B038_inst;
        D_8010D551_inst = 1;
        D_8010D59C_inst = 0;
    }
}

void func_8010B038_inst(omObjData *obj) {
}

const char D_8010DA24_inst[] = "y002_13-grid1";
const char D_8010DA34_inst[] = "y002_12-grid1";
const char D_8010DA44_inst[] = "y002_11-grid1";
const char D_8010DA54_inst[] = "y002_10-grid1";
const char D_8010DA64_inst[] = "y002_09-grid1";
const char D_8010DA74_inst[] = "y002_08-grid1";
const char D_8010DA84_inst[] = "y002_07-grid1";
const char D_8010DA94_inst[] = "y002_06-grid1";
const char D_8010DAA4_inst[] = "hook_last";
const char D_8010DAB0_inst[] = "hook_midori";
const char D_8010DABC_inst[] = "hook_aka";
const char D_8010DAC8_inst[] = "hook_ao";

void func_8010B040_inst(void) {
    s32 i;

    switch (D_8010D40A_inst) {
        case 0:
        case 1:
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_800CB8B1_main[D_8010D400_inst[i]] == 0) {
                    D_8010D554_inst[i] = 0;
                } else {
                    D_8010D554_inst[i] = 1;
                }
            }
            break;
        case 3:
        case 4:
        case 5:
        case 7:
            D_8010D554_inst[0] = 2;
            D_8010D554_inst[1] = 2;
            D_8010D554_inst[2] = 2;
            D_8010D554_inst[3] = 2;
            break;
        case 8:
            D_8010D554_inst[0] = 3;
            D_8010D554_inst[1] = 3;
            D_8010D554_inst[2] = 3;
            D_8010D554_inst[3] = 3;
            break;
    }
}

void func_8010B0FC_inst(void) {
    D_8010D550_inst = 1;
}

s8 func_8010B10C_inst(void) {
    return D_8010D550_inst;
}

s8 func_8010B118_inst(void) {
    return D_8010D551_inst;
}

void func_8010B124_inst(void) {
    omObjData *obj;
    InstHookList *list;
    s8 i;

    obj = D_8010DC90_inst;
    D_8010D558_inst = 1;
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8001C814_main(obj->model[5 + i], 1, 0);
        func_8001C814_main(obj->model[5 + i], 4, 4);
        func_8001C258_main(obj->model[5 + i], 4, 0);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        func_8001C814_main(obj->model[15 + i], 1, 0);
        func_8001C814_main(obj->model[15 + i], 4, 4);
        func_8001C258_main(obj->model[15 + i], 4, 0);
    }
    D_8010DC94_inst = func_8010B2A4_inst;
}

void func_8010B2A4_inst(omObjData *obj) {
    f32 rot[4][4];
    f32 mtx[4][4];
    InstHookList *list;
    f32 frames;
    s8 i;

    frames = D_800CCF58_main[HmfModelData[obj->model[5]].unk02].unk02 - 20.0f;
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, 1.0f / frames * D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, 1.0f / frames * D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
    }
    D_8010D5A0_inst++;
    if (D_8010D5A0_inst == frames) {
        list = D_8010D4C0_inst[D_8010D40A_inst][0];
        for (i = 0; i < list->count; i++) {
            func_8001C258_main(obj->model[5 + i], 4, 4);
        }
        list = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < list->count; i++) {
            func_8001C258_main(obj->model[15 + i], 4, 4);
        }
        func_801080FC_inst();
        D_8010DC94_inst = func_8010A750_inst;
        D_8010D5A0_inst = 0;
    }
}

void func_8010B628_inst(omObjData *obj) {
    f32 rot[4][4];
    f32 mtx[4][4];
    InstHookList *list;
    f32 end;
    s32 i;

    end = D_800CCF58_main[HmfModelData[obj->model[5]].unk02].unk02;
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8001C258_main(obj->model[5 + i], 4, 0);
        func_8001C6A8_main(obj->model[5 + i], end);
        func_8001C814_main(obj->model[5 + i], 1, 0);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    end = D_800CCF58_main[HmfModelData[obj->model[15]].unk02].unk02;
    for (i = 0; i < list->count; i++) {
        func_8001C258_main(obj->model[15 + i], 4, 0);
        func_8001C6A8_main(obj->model[15 + i], end);
        func_8001C814_main(obj->model[15 + i], 1, 0);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[1 + i]].mtx);
    }
    list = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < list->count; i++) {
        func_8008A120_main(rot, D_8010D414_inst);
        func_8002367C_main(mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
        func_80018044_main(rot, mtx, (f32 (*)[4])HmfModelData[obj->model[10 + i]].mtx);
    }
    D_8010DC94_inst = func_8010B038_inst;
}

