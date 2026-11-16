/* Not common.h: functions.us.h declares func_80017AD8_main as returning u8 (an extra andi);
   it returns s16 (src/14EA0.c). */
#include "ultra64.h"
#include "types.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/process.h"
#include "game/util.h"
#include "include_asm.h"

// event e1
/* The host character (the event's first player) on the right-hand podium:
   walks in, turns to the camera, hits the block on cue. */
typedef struct ChanceTimeHost {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*objFunc)(omObjData *);
} ChanceTimeHost;

extern u16 D_800D5558_main[4];
/* Motion info table (D_800CCF58_main_Struct in common_structs.h); unk02 is the motion's end frame. */
typedef struct ChanceTimeMotInfo {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04[0x14];
} ChanceTimeMotInfo; // sizeof 0x18
extern ChanceTimeMotInfo *D_800CCF58_main;
extern ChanceTimeHost D_801100C0_chancetime;
extern s8 D_801100D0_chancetime[4];
extern s32 D_800A178C_main[][6];
extern s32 D_8010FAF0_chancetime;
extern f32 D_8010FAF4_chancetime;
extern f32 D_8010FAF8_chancetime;
extern f32 D_8010FAFC_chancetime;
extern s32 D_8010FE70_chancetime;
extern s32 D_8010FE74_chancetime;
extern s8 D_8010FE78_chancetime;
extern s16 D_8010FE7A_chancetime[3];

void func_80106760_chancetime(omObjData *obj);
void func_80106768_chancetime(omObjData *obj);
void func_80106770_chancetime(omObjData *obj);
void func_8010684C_chancetime(omObjData *obj);
void func_80106A2C_chancetime(omObjData *obj);
void func_80106BEC_chancetime(omObjData *obj);
void func_8010D92C_chancetime(s8 arg0);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s32 func_80017BB8_main(s16, s16);
s16 func_80017AD8_main(s32);
void func_80017954_main(s16, s16, s16, s16);

void func_80106320_chancetime(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 10, -1, NULL);
    D_801100C0_chancetime.obj = obj;
    chr = GwPlayer[D_801100D0_chancetime[0]].chr;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 360.0f, 0.0f, -50.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, -90.0f, 0.0f);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 360.0f, -10.0f, -50.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C8A8_main(obj->model[2], 2);
    obj->model[3] = func_8000B108_main(0x1C000B, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 180.0f, 220.0f, 0.0f);
    func_8001C814_main(obj->model[3], 2, 0);
    Hu3DModelScaleSet(obj->model[3], 0.7f, 0.7f, 0.7f);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C8A8_main(obj->model[3], 2);
    obj->model[4] = func_8000B108_main(0x5D0008, 0x2B9);
    Hu3DModelPosSet(obj->model[4], 180.0f, 220.0f, 0.0f);
    func_8001C258_main(obj->model[4], 4, 4);
    D_8010FE7A_chancetime[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_8010FE7A_chancetime[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_8010FE7A_chancetime[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA6));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2B));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x1F));
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106768_chancetime);
    D_801100C0_chancetime.objFunc = func_80106760_chancetime;
    while (1) {
        D_801100C0_chancetime.objFunc(obj);
        HuPrcVSleep();
    }
}

void func_80106760_chancetime(omObjData *obj) {
}

void func_80106768_chancetime(omObjData *obj) {
}

/* Walk in from the right to x = 180. */
void func_80106770_chancetime(omObjData *obj) {
    s16 done = 0;

    D_8010FAF4_chancetime -= 25.0f;
    if (D_8010FAF4_chancetime <= 180.0f) {
        D_8010FAF4_chancetime = 180.0f;
        done = 1;
    }
    Hu3DModelPosSet(obj->model[1], D_8010FAF4_chancetime, 0.0f, -50.0f);
    Hu3DModelPosSet(obj->model[2], D_8010FAF4_chancetime, -10.0f, -50.0f);
    if (done == 1) {
        D_8010FAF4_chancetime = 360.0f;
        D_801100C0_chancetime.objFunc = func_8010684C_chancetime;
    }
}

/* Turn to face the camera, then show the block above the head. */
void func_8010684C_chancetime(omObjData *obj) {
    s16 done = 0;

    D_8010FAF8_chancetime += 8.0f;
    if (D_8010FAF8_chancetime >= 90.0f) {
        D_8010FAF8_chancetime = 90.0f;
        done = 1;
    }
    Hu3DModelRotSet(obj->model[1], 0.0f, D_8010FAF8_chancetime + -90.0f, 0.0f);
    if (done == 1) {
        D_8010FAF8_chancetime = 0.0f;
        D_8010FE70_chancetime = 0;
        D_8010FE74_chancetime = done;
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
        Hu3DModelScaleSet(obj->model[3], 0.2f, 0.2f, 0.2f);
        func_8001C814_main(obj->model[3], 2, 0);
        func_8001C814_main(obj->model[3], 1, 1);
        func_8001C258_main(obj->model[3], 4, 0);
        Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[3]].pos.x, HmfModelData[obj->model[3]].pos.y,
                        HmfModelData[obj->model[3]].pos.z);
        func_8001C258_main(obj->model[4], 4, 0);
        func_8001C814_main(obj->model[4], 2, 0);
        func_8001C814_main(obj->model[4], 1, 0);
        D_801100C0_chancetime.objFunc = func_80106A2C_chancetime;
    }
}

/* The block grows to full size. */
void func_80106A2C_chancetime(omObjData *obj) {
    s16 done = 0;

    HuPrcSleep(2);
    HuAudFXPlay(0x501);
    do {
        D_8010FAFC_chancetime += 0.14f;
        if (D_8010FAFC_chancetime >= 0.7f) {
            D_8010FAFC_chancetime = 0.7f;
            done = 1;
        }
        Hu3DModelScaleSet(obj->model[3], D_8010FAFC_chancetime, D_8010FAFC_chancetime, D_8010FAFC_chancetime);
        HuPrcVSleep();
    } while (done != 1);
    D_8010FAFC_chancetime = 0.0f;
    D_801100C0_chancetime.objFunc = func_80106760_chancetime;
}

/* Start the walk-in. */
void func_80106B18_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;

    D_8010FE70_chancetime = 1;
    D_8010FE74_chancetime = 0;
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_801100C0_chancetime.objFunc = func_80106770_chancetime;
}

/* 1 once the host stands ready under the block. */
s32 func_80106BB8_chancetime(void) {
    return D_8010FE74_chancetime;
}

/* Hit the block for wheel `arg0`. */
void func_80106BC4_chancetime(s8 arg0) {
    D_8010FE78_chancetime = arg0;
    D_801100C0_chancetime.objFunc = func_80106BEC_chancetime;
}

/* 1 once the hit has finished. */
s32 func_80106BE0_chancetime(void) {
    return D_8010FAF0_chancetime;
}

#ifdef NON_MATCHING
/* event e1: masked differs only in block order: retail keeps the COM wait (HuPrcSleep) right
   after the COM test and the A-button test after it; every loop form tried here (while, for,
   do-while, goto, else-if/continue) has GCC move the COM block below the loop's back jump
   (3 fewer instructions). Logic checked against the asm. */
/* Wait for A (a COM waits 15-29 frames), jump, stop wheel D_8010FE78 at the jump's peak, land. */
void func_80106BEC_chancetime(omObjData *obj) {
    f32 time;
    s16 hit;
    s8 player;

    player = D_801100D0_chancetime[0];
    D_8010FAF0_chancetime = 0;
    while (1) {
        if (GwPlayer[player].stat & 1) {
            HuPrcSleep((u8)(rand8() % 15) + 15);
        } else if (!(D_800D5558_main[GwPlayer[player].pad] & 0x8000)) {
            HuPrcVSleep();
            continue;
        }
        break;
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 20, 0);
    hit = 0;
    func_8001C92C_main(obj->model[1], 3.0f);
    do {
        time = func_8001C7D0_main(obj->model[1]);
        if (hit == 0) {
            if (time >= 5.0f) {
            hit = 1;
            func_8010D92C_chancetime(D_8010FE78_chancetime);
            func_8001C814_main(obj->model[3], 2, 0);
            func_8001C814_main(obj->model[3], 1, 0);
            func_8001C6A8_main(obj->model[3], 0.0f);
            func_8001C92C_main(obj->model[3], 1.2f);
            func_8001C258_main(obj->model[3], 4, 0);
            }
        }
        HuPrcVSleep();
    } while (time >= 0.0f);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 20, 0);
    func_8001C92C_main(obj->model[1], 3.0f);
    do {
        time = func_8001C7D0_main(obj->model[1]);
        HuPrcVSleep();
    } while (time >= 0.0f);
    time = 0.0f;
    Hu3DModelPosSet(obj->model[1], 180.0f, time, -50.0f);
    Hu3DModelPosSet(obj->model[3], 180.0f, 220.0f, time);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 20, 2);
    func_8001C92C_main(obj->model[1], 1.0f);
    D_8010FAF0_chancetime = 1;
    D_801100C0_chancetime.objFunc = func_80106760_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106BEC_chancetime);
#endif

/* Reactions: play a voice and a motion, wait for the motion's end. */
void func_80106F10_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;
    f32 time;
    f32 end;

    HuAudFXPlay(0x502);
    CharFXPlay(0x274, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[obj->model[1]].unk40;
        end = D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02;
        HuPrcVSleep();
    } while (time < end);
}

void func_8010705C_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;
    f32 time;
    f32 end;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[obj->model[1]].unk40;
        end = D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02;
        HuPrcVSleep();
    } while (time < end);
}

void func_801071A8_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;
    f32 time;
    f32 end;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[4]].unk02, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[obj->model[1]].unk40;
        end = D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02;
        HuPrcVSleep();
    } while (time < end);
}
