#include "common.h"
#include "../ovl_81_name/ovl_81.h"

void func_8010BA98_boardresult(void);
void func_8010BBF0_boardresult(omObjData *);
void func_8010BC3C_boardresult(void);
void func_8010BCA4_boardresult(void);
extern s32 D_8010E72C_boardresult[];
extern u32 D_8010E738_boardresult[];
extern s32 D_8010E73C_boardresult[];
extern s32 *D_8010E88C_boardresult[];
extern s32 *D_8010E8AC_boardresult[];
extern u8 D_8010EAF0_boardresult;

void func_801059A0_boardresult(void) {
    s32 i;
    u32 j;

    D_8010EAF0_boardresult = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_8010BCA4_boardresult();
    func_8010BC3C_boardresult();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    func_8005A6B0_main();
    omAddPrcObj(func_8010BA98_boardresult, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_8010BBF0_boardresult);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E72C_boardresult[0]; j++) {
            D_8010E88C_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E72C_boardresult[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E738_boardresult[0]; j++) {
            D_8010E8AC_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E738_boardresult[j + 1]);
        }
    }

    func_800EF3EC_name_81(4);
}

/* event e6: the end-of-game results (func_80105B68..func_80107F84). Duel Mode's results
   (duelresult/4554C0.c) are the two-player version of the same code. */

typedef struct BrHmfPart { /* a model part looked up by name (func_8001D33C_main) */
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ char unk_0C[0xC];
    /* 0x18 */ f32 unk_18;
} BrHmfPart;

typedef struct BrFiles4 { s32 v[4]; } BrFiles4;
typedef struct BrPos4 { Vec2f v[4]; } BrPos4;
typedef struct BrF8 { f32 v[8]; } BrF8;

s16 func_8000B5BC_main(s32);
void *func_8001D33C_main(s16, const char *);
void func_8001F974_main(s16, s16);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8008A120_main(f32 (*m)[4], f32 angle);
void func_800EB708_name_81(Vec *, Vec *, Vec *);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 frames);
void func_800F3C98_name_81(s16 playerNo, s32 *motions, s32 arg2);
void func_800F3EC0_name_81(s16 playerNo);
void func_800461B4_main(s16);
s32 func_8001C954_main(s16);
void func_8001C814_main(s16, s16, s16);
s16 func_8004ACE0_main(s16, s16);
void func_8001ACDC_main(s16);
void func_80046558_main(s16);
void HuPrcSleep(s32);

void func_80105B68_boardresult(omObjData *obj);

extern Vec D_8010E48C_boardresult;
extern Vec D_8010E4C8_boardresult;
extern s32 D_8010E8CC_boardresult[5];
extern BrFiles4 D_8010E960_boardresult;
extern BrPos4 D_8010E970_boardresult;
extern BrPos4 D_8010E990_boardresult;
extern BrF8 D_8010E9B0_boardresult;

/* .bss */
extern Object *D_8010EAF4_boardresult;
extern GW_PLAYER *D_8010EB38_boardresult[4];

void func_80105B68_boardresult(omObjData *obj) {
    D_8010EAF4_boardresult->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* Process: the results scene opens; the four players come out of the pipe and the host appears. */
void func_80105BD8_boardresult(void) {
    s16 models[5];
    Vec pos[4];
    UnkBoard4 *banner[2];
    BrFiles4 files;
    BrPos4 pos1;
    BrPos4 pos2;
    BrF8 heights;
    omObjData *obj;
    BrHmfPart *part;
    s32 i;
    s32 j;
    u16 model;
    f32 base;

    files = D_8010E960_boardresult;
    pos1 = D_8010E970_boardresult;
    pos2 = D_8010E990_boardresult;
    heights = D_8010E9B0_boardresult;
    banner[0] = func_800F4528_name_81(4, 2);
    for (i = 0; i < 4; i++) {
        void *data = DataRead(files.v[i]);
        banner[0]->unk_0C[i] = func_80055810_main(data);
        func_80055024_main(banner[0]->unk_0A, i, banner[0]->unk_0C[i], 0);
        HuSprPriSet(banner[0]->unk_0A, i, 1);
        HuSprAttrSet(banner[0]->unk_0A, i, 0);
        func_80054904_main(banner[0]->unk_0A, i, pos1.v[i].x, pos1.v[i].y);
        DataClose(data);
    }
    banner[1] = func_800F4528_name_81(4, 2);
    for (i = 0; i < 4; i++) {
        void *data = DataRead(files.v[i]);
        banner[1]->unk_0C[i] = func_80055810_main(data);
        func_80055024_main(banner[1]->unk_0A, i, banner[0]->unk_0C[i], 0);
        HuSprPriSet(banner[1]->unk_0A, i, 1);
        HuSprAttrSet(banner[1]->unk_0A, i, 1);
        func_80054904_main(banner[1]->unk_0A, i, pos2.v[i].x, pos2.v[i].y);
        DataClose(data);
    }
    for (i = 0; i < 4; i++) {
        D_8010EB38_boardresult[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_8010E88C_boardresult[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_8010EB38_boardresult[i]->player_obj->coords, &D_8010E4C8_boardresult);
        func_800D8944_name_81(D_8010EB38_boardresult[i]->player_obj);
        D_8010EB38_boardresult[i]->player_obj->flags |= 1;
        D_8010EB38_boardresult[i]->stat |= 4;
    }
    WipeCreateIn(2, 0x10);
    HuPrcSleep(0x11);
    MBDBackTPLvlSet(0);
    HuAudFXPlay(0x173);
    for (i = 0; i < 160; i += 3) {
        func_80054904_main(banner[0]->unk_0A, 0, i + pos1.v[0].x, pos1.v[0].y);
        func_80054904_main(banner[1]->unk_0A, 0, pos2.v[0].x - i, pos2.v[0].y);
        HuPrcVSleep();
    }
    func_800F4584_name_81(banner[0]);
    func_800F4584_name_81(banner[1]);
    HuPrcSleep(10);
    MBDBackTPLvlSet(0xFF);
    D_8010EAF4_boardresult = func_800D8010_name_81(0x3B, NULL);
    func_800461B4_main(D_8010EAF4_boardresult->omObj1->model[0]);
    func_800D8944_name_81(D_8010EAF4_boardresult);
    HuVecCopy3F(&D_8010EAF4_boardresult->coords, &D_8010E48C_boardresult);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105B68_boardresult);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;
    model = func_8000B108_main(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = func_8000B5BC_main(D_8010E8CC_boardresult[i]);
    }
    func_8001C954_main(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    func_8001F974_main(model, models[0]);
    func_8001C814_main(model, 2, 1);
    HuPrcSleep(10);
    for (i = 0; i < 4; i++) {
        func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&pos[i], 0.0f, 0.0f, 0.0f);
        func_800EB708_name_81(&pos[i], &D_8010EB38_boardresult[i]->player_obj->coords, &D_8010EB38_boardresult[i]->player_obj->rot);
        pos[i].y += heights.v[GwPlayer[i].chr];
        D_8010EB38_boardresult[i]->player_obj->coords.y += heights.v[GwPlayer[i].chr] - 80.0f;
        func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &pos[i], &D_8010EB38_boardresult[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 8) {
                func_8001C814_main(model, 0, 1);
            }
            if (j == 18) {
                func_8001C814_main(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                    case 2:
                        HuAudFXPlay(0x166);
                        break;
                    case 3:
                        HuAudFXPlay(0x167);
                        break;
                }
            }
        }
        func_800D8F0C_name_81(D_8010EB38_boardresult[i]->player_obj);
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x168);
    func_8001C814_main(model, 3, 0);
    HuPrcSleep(0x2F);
    func_8001C814_main(model, 0, 1);
    func_8002FD8C_main(D_8010EAF4_boardresult->omObj1->model[0], HmfModelData[D_8010EAF4_boardresult->omObj1->model[0]].unk02, "l_mayu", 0x4C, 0x47);
    part = func_8001D33C_main(D_8010EAF4_boardresult->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        part->unk_18 = i;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x174);
    func_8002FD8C_main(D_8010EAF4_boardresult->omObj1->model[0], HmfModelData[D_8010EAF4_boardresult->omObj1->model[0]].unk02, "hige", 0x17, 0x46);
    part = func_8001D33C_main(D_8010EAF4_boardresult->omObj1->model[0], "hige");
    base = part->unk_08;
    for (i = 0; i < 30; i += 2) {
        part->unk_08 = sindf(i * 45) * 10.0f + base;
        HuPrcVSleep();
    }
    part->unk_08 = base;
    func_8001C814_main(model, 3, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x169);
    for (i = 0; i < 4; i++) {
        func_8004ACE0_main(0x286, i);
        func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, 1, 2);
        func_8001C814_main(D_8010EB38_boardresult[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&pos[i], &D_8010E4C8_boardresult);
        pos[i].y += 400.0f;
        func_8008A120_main((f32 (*)[4])HmfModelData[D_8010EB38_boardresult[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        func_800D8E88_name_81(D_8010EB38_boardresult[i]->player_obj);
        func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &pos[i], &D_8010EB38_boardresult[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; ) {
            HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f);
            j--;
            HuPrcVSleep();
        }
    }
    WipeCreateOut(2, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8001ACDC_main(model);
    for (i = 0; i < 5; i++) {
        func_8001ACDC_main(models[i]);
    }
    omDelObj(obj);
    func_80046558_main(D_8010EAF4_boardresult->omObj1->model[0]);
    func_800D8F3C_name_81(D_8010EAF4_boardresult);
    for (i = 0; i < 4; i++) {
        func_800F3EC0_name_81(i);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010685C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106968_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106A38_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106A80_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106CA8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106DA4_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106F54_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801070F8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107598_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801076A0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107AB4_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107B50_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107EE8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107F84_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80108378_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109128_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109320_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010935C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801094A8_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA60_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA70_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA80_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA90_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EAB0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109754_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BA98_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BAD8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BBF0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BC3C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BC70_boardresult);

void func_8010BCA4_boardresult(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BD04_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EADC_boardresult);
