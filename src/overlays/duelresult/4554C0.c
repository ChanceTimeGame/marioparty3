#include "common.h"
#include "../ovl_81_name/ovl_81.h"

/* duel r1: duelresult (0x62), the Duel Mode results. */

/* A list of motion file ids (count, then ids); D_8010D608/D_8010D628[chr] point at one per
   character: [0] holds the template file ids, [1..7] get each character's ids at init. */
typedef struct DrMotList {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[1]; /* [count] */
} DrMotList;

typedef struct DrMotList2 {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[2];
} DrMotList2; /* size = 0xC */

typedef struct DrMotList6 {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[6];
} DrMotList6; /* size = 0x1C */

typedef struct DuelResultWork DuelResultWork; /* 45A700.c */

DuelResultWork *func_8010ABE0_duelresult(s32 file);
void func_8010AC6C_duelresult(DuelResultWork *work, u32 file);
void func_8010AC74_duelresult(DuelResultWork *work, f32 x, f32 y, f32 z);
void func_8010AC84_duelresult(DuelResultWork *work, f32 x, f32 y, f32 z);
void func_8010AC94_duelresult(DuelResultWork *work, s16 time);
void func_8010AC9C_duelresult(DuelResultWork *work, u16 clear, u16 set);
s16 func_8010ACB4_duelresult(DuelResultWork *work);
void func_8010ACBC_duelresult(DuelResultWork *work, s16 time);

void func_8010AAE8_duelresult(void);
void func_8010AB1C_duelresult(void);
void func_8010AB50_duelresult(void);
void func_8010ABB0_duelresult(void);
void func_80105BD0_duelresult(void);
void func_8010753C_duelresult(omObjData *obj);
void func_80107AF4_duelresult(omObjData *obj);
void func_80108174_duelresult(DuelResultWork *work, s32 i);
void func_8010856C_duelresult(void);
void func_8010A938_duelresult(void);
void func_8010A978_duelresult(omObjData *obj);
void func_8010AA9C_duelresult(omObjData *obj);

typedef struct DrTexAnim { /* D_800D1714_main entry */
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ char unk_0B;
} DrTexAnim; /* size = 0xC */

extern DrTexAnim *D_800D1714_main;
s32 func_80017BB8_main(s16, s16);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void DataClose(void *);
void func_80007EC0_main(s32);
s32 func_80050064_main(s32 write);
s32 func_80050200_main(s32 write);
void GWPlayNumInc(s16 board);
void GWCharPlayNumInc(s16 board, s16 chr);
u8 rand8(void);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 frames);

extern s16 kakusiMasuItemHis[]; /* Duel Mode: [0] the winner, [2] nonzero on a draw */


typedef struct DrHmfPart { /* a model part looked up by name (func_8001D33C_main) */
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ char unk_0C[0xC];
    /* 0x18 */ f32 unk_18;
} DrHmfPart;

typedef struct DrFiles4 { s32 v[4]; } DrFiles4;
typedef struct DrPos4 { Vec2f v[4]; } DrPos4;
typedef struct DrF8 { f32 v[8]; } DrF8;

s16 func_8000B5BC_main(s32);
void *func_8001D33C_main(s16, const char *);
void func_8001F974_main(s16, s16);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8008A120_main(f32 (*m)[4], f32 angle);
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800F3C98_name_81(s16 playerNo, s32 *motions, s32 arg2);
void func_800F3EC0_name_81(s16 playerNo);
u16 func_8000B108_main(s32, s32);
void func_800461B4_main(s16);
s32 func_8001C954_main(s16);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void func_8001C814_main(s16, s16, s16);
s16 func_8004ACE0_main(s16, s16);
void func_8001ACDC_main(s16);
void func_80046558_main(s16);
void WipeCreateIn(s32, s32);
void HuPrcSleep(s32);

extern Vec D_8010D324_duelresult;
extern Vec D_8010D36C_duelresult;
extern s32 D_8010D648_duelresult[5];
extern DrFiles4 D_8010D6D0_duelresult;
extern DrPos4 D_8010D6E0_duelresult;
extern DrPos4 D_8010D700_duelresult;
extern DrF8 D_8010D720_duelresult;

/* .data */
extern s32 D_8010D290_duelresult;
extern Vec D_8010D378_duelresult[];
extern DrMotList2 D_8010D4C8_duelresult;
extern DrMotList6 D_8010D4D4_duelresult;
extern DrMotList *D_8010D608_duelresult[8];
extern DrMotList *D_8010D628_duelresult[8];
extern omObjData *D_8010D668_duelresult[4];
extern s32 D_8010D678_duelresult;
extern f32 D_8010D67C_duelresult;
extern s32 D_8010D680_duelresult[6];
extern s32 D_8010D698_duelresult[];

/* .bss */
extern u8 D_8010D860_duelresult;
extern Object *D_8010D864_duelresult;
extern GW_PLAYER *D_8010D8A8_duelresult[2];
extern Object *D_8010D8B0_duelresult[6];
extern Object *D_8010D8C8_duelresult[2];
extern Object *D_8010D8E0_duelresult;
extern s16 D_8010D8E4_duelresult;
extern s16 D_8010D8E6_duelresult;
extern s32 D_8010D900_duelresult[2];
extern s32 D_8010D910_duelresult;
extern Object *D_8010D914_duelresult[2];
extern void *D_8010D91C_duelresult[2];
extern s32 D_8010D924_duelresult[2];
extern f32 D_8010D930_duelresult[6];

void func_801059A0_duelresult(void) {
    s32 i;
    u32 j;

    D_8010D860_duelresult = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_8010AB50_duelresult();
    func_8010AAE8_duelresult();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    func_8005A6B0_main();
    omAddPrcObj(func_8010A938_duelresult, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_8010AA9C_duelresult);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010D4C8_duelresult.count; j++) {
            D_8010D608_duelresult[i]->ids[j] = func_80017BB8_main(i, D_8010D4C8_duelresult.ids[j]);
        }
    }
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010D4D4_duelresult.count; j++) {
            D_8010D628_duelresult[i]->ids[j] = func_80017BB8_main(i, D_8010D4D4_duelresult.ids[j]);
        }
    }
}

void func_80105B60_duelresult(omObjData *obj) {
    D_8010D864_duelresult->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* Process: the results scene opens; both duelers come out of the pipe and the host appears. */
void func_80105BD0_duelresult(void) {
    s16 models[5];
    Vec pos[2];
    Vec unused[2];
    UnkBoard4 *banner[2];
    DrFiles4 files;
    DrPos4 pos1;
    DrPos4 pos2;
    DrF8 heights;
    omObjData *obj;
    DrHmfPart *part;
    s32 i;
    s32 j;
    u16 model;
    f32 base;

    files = D_8010D6D0_duelresult;
    pos1 = D_8010D6E0_duelresult;
    pos2 = D_8010D700_duelresult;
    heights = D_8010D720_duelresult;
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
    for (i = 0; i < 2; i++) {
        D_8010D8A8_duelresult[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, (s32 *)D_8010D608_duelresult[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D36C_duelresult);
        D_8010D8A8_duelresult[i]->player_obj->flags |= 1;
        D_8010D8A8_duelresult[i]->stat |= 4;
        func_800D8944_name_81(D_8010D8A8_duelresult[i]->player_obj);
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
    D_8010D864_duelresult = func_800D8010_name_81(0x3B, NULL);
    func_800461B4_main(D_8010D864_duelresult->omObj1->model[0]);
    func_800D8944_name_81(D_8010D864_duelresult);
    HuVecCopy3F(&D_8010D864_duelresult->coords, &D_8010D324_duelresult);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;
    model = func_8000B108_main(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = func_8000B5BC_main(D_8010D648_duelresult[i]);
    }
    func_8001C954_main(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    func_8001F974_main(model, models[1]);
    func_8001C814_main(model, 2, 1);
    HuPrcSleep(10);
    for (i = 0; i < 2; i++) {
        func_800D90D0_name_81(D_8010D8A8_duelresult[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&pos[i], 0.0f, 0.0f, 0.0f);
        func_800EB708_name_81(&pos[i], &D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D8A8_duelresult[i]->player_obj->rot);
        pos[i].y += heights.v[GwPlayer[i].chr];
        D_8010D8A8_duelresult[i]->player_obj->coords.y += heights.v[GwPlayer[i].chr] - 80.0f;
        func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &pos[i], &D_8010D8A8_duelresult[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 18) {
                func_8001C814_main(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                }
            }
        }
        func_800D8F0C_name_81(D_8010D8A8_duelresult[i]->player_obj);
        HuPrcSleep(9);
    }
    HuAudFXPlay(0x168);
    func_8001C814_main(model, 3, 0);
    HuPrcSleep(0x34);
    func_8001C814_main(model, 0, 1);
    func_8002FD8C_main(D_8010D864_duelresult->omObj1->model[0], HmfModelData[D_8010D864_duelresult->omObj1->model[0]].unk02, "l_mayu", 0x4C, 0x47);
    part = func_8001D33C_main(D_8010D864_duelresult->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        part->unk_18 = i;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x174);
    func_8002FD8C_main(D_8010D864_duelresult->omObj1->model[0], HmfModelData[D_8010D864_duelresult->omObj1->model[0]].unk02, "hige", 0x17, 0x46);
    part = func_8001D33C_main(D_8010D864_duelresult->omObj1->model[0], "hige");
    base = part->unk_08;
    for (i = 0; i < 30; i += 2) {
        part->unk_08 = sindf(i * 45) * 10.0f + base;
        HuPrcVSleep();
    }
    part->unk_08 = base;
    func_8001C814_main(model, 3, 0);
    HuPrcSleep(3);
    HuAudFXPlay(0x169);
    for (i = 0; i < 2; i++) {
        func_8004ACE0_main(0x286, i);
        func_800D90D0_name_81(D_8010D8A8_duelresult[i]->player_obj, 1, 2);
        func_8001C814_main(D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&pos[i], &D_8010D36C_duelresult);
        pos[i].y += 400.0f;
        func_8008A120_main((f32 (*)[4])HmfModelData[D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        func_800D8E88_name_81(D_8010D8A8_duelresult[i]->player_obj);
        func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &pos[i], &D_8010D8A8_duelresult[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; ) {
            HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f);
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
    func_80046558_main(D_8010D864_duelresult->omObj1->model[0]);
    func_800D8F3C_name_81(D_8010D864_duelresult);
    for (i = 0; i < 2; i++) {
        func_800F3EC0_name_81(i);
    }
}

s16 func_80106800_duelresult(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    u16 tex;

    data = DataRead(file);
    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_8010D8E4_duelresult = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    tex = D_800D1714_main[(s16)anim].unk_00;
    D_8010D8E6_duelresult = func_80032694_main(HmfModelData[model].hmf, anim, 0, name);
    func_8001C448_main(model);
    return tex;
}

void func_8010690C_duelresult(s16 model, s16 tex) {
    DrTexAnim *slot;

    if (D_8010D8E6_duelresult != 0xFF) {
        if (tex == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[D_8010D8E6_duelresult];
            slot->unk_00 = tex;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}

s16 func_801069DC_duelresult(s32 file) {
    void *data;
    s16 ret;

    data = DataRead(file);
    ret = func_800329B4_main(data);
    DataClose(data);
    return ret;
}

/* Scrolls the cloud texture of the three cloud layers. */
void func_80106A24_duelresult(omObjData *obj) {
    func_8001E888_main(D_8010D8B0_duelresult[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010D8B0_duelresult[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010D8B0_duelresult[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    obj->trans.x -= 4.0f;
    obj->trans.y -= 2.0f;
    obj->trans.z -= 1.0f;
    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.z >= 64.0f) {
        obj->trans.z -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
    if (obj->trans.z <= -64.0f) {
        obj->trans.z += 64.0f;
    }
}

void func_80106C4C_duelresult(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010D8C8_duelresult[i]->rot.x = sindf(obj->rot.x);
        D_8010D8C8_duelresult[i]->rot.z = cosdf(obj->rot.x);
    }
    if (obj->work[0] == 0) {
        obj->rot.x += 20.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
    } else if (obj->rot.x < 360.0f) {
        obj->rot.x += 20.0f;
    } else {
        obj->rot.x = 360.0f;
    }
}

void func_80106D48_duelresult(omObjData *obj) {
    Object *o = D_8010D8C8_duelresult[obj->work[1]];

    obj->work[0]++;
    o->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    o->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    o->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_80106EF8_duelresult(omObjData *obj) {
    Object *o = D_8010D8E0_duelresult;

    obj->work[0]++;
    o->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    o->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    o->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

/* Rotates model about X by angle (degrees). */
#define DR_ROTX(model, angle)                                                                      \
    sincosdf(angle, &HmfModelData[model].mtx[6], &HmfModelData[model].mtx[5]);                    \
    HmfModelData[model].mtx[9] = -HmfModelData[model].mtx[6];                                      \
    HmfModelData[model].mtx[10] = HmfModelData[model].mtx[5];                                      \
    HmfModelData[model].mtx[1] = HmfModelData[model].mtx[2] = HmfModelData[model].mtx[3] =          \
        HmfModelData[model].mtx[4] = HmfModelData[model].mtx[7] = HmfModelData[model].mtx[8] =      \
        HmfModelData[model].mtx[11] = HmfModelData[model].mtx[12] = HmfModelData[model].mtx[13] =   \
        HmfModelData[model].mtx[14] = 0.0f;                                                       \
    HmfModelData[model].mtx[0] = HmfModelData[model].mtx[15] = 1.0f

/* Process: player *(s32 *)user_data jumps out of the loser's block. */
void func_8010709C_duelresult(void) {
    s32 i;
    s32 k;
    f32 angle;

    i = *(s32 *)HuPrcCurrentGet()->user_data;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords,
                                                           &D_8010D378_duelresult[i + 2],
                                                           &D_8010D8A8_duelresult[i]->player_obj->coords, 10));
    func_800D90D0_name_81(D_8010D8A8_duelresult[i]->player_obj, 0, 0);
    angle = 90.0f;
    do {
        DR_ROTX(D_8010D8C8_duelresult[1 - i]->omObj1->model[0], angle);
        HuPrcVSleep();
        angle -= 9.0f;
    } while (angle > 0.0f);
    DR_ROTX(D_8010D8C8_duelresult[1 - i]->omObj1->model[0], 0.0f);
    HuAudFXPlay(0x175);
    k = 0;
    for (angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->coords, D_8010D378_duelresult[i + 2].x,
                     D_8010D378_duelresult[i + 2].y - sindf(angle) * 100.0f + k, D_8010D378_duelresult[i + 2].z);
        HuVecCopyXYZ(&D_8010D8C8_duelresult[1 - i]->coords, D_8010D378_duelresult[i + 2].x,
                     D_8010D378_duelresult[i + 2].y - sindf(angle) * 100.0f + k, D_8010D378_duelresult[i + 2].z);
        k -= 10;
        HuPrcVSleep();
    }
    func_800D90D0_name_81(D_8010D8A8_duelresult[i]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void func_8010753C_duelresult(omObjData *obj) {
    f32 scale;
    s32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(D_8010D900_duelresult[obj->work[0]], i, scale, scale);
    }
    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* Coin count sprites over both duelers; the richer one's pulse. */
void func_80107644_duelresult(void) {
    s32 digits[3];
    Vec pos;
    Vec2f pos2d;
    void *data;
    s32 i;
    s32 j;
    s32 n;
    s32 coin;
    s32 max;

    data = DataRead(0x1301C5);
    D_8010D910_duelresult = func_80055810_main(data);
    DataClose(data);
    for (i = 0; i < 2; i++) {
        D_8010D900_duelresult[i] = HuSprGrpCreate(3, 5);
        coin = GwPlayer[i].coin;
        if (coin >= 100) {
            n = 3;
            digits[0] = coin / 100;
            coin -= digits[0] * 100;
            digits[1] = coin / 10;
            coin -= digits[1] * 10;
            digits[2] = coin;
        } else if (coin >= 10) {
            n = 2;
            coin %= 100;
            digits[0] = coin / 10;
            coin -= digits[0] * 10;
            digits[1] = coin;
        } else {
            n = 1;
            digits[0] = coin;
        }
        for (j = 0; j < n; j++) {
            func_80055024_main(D_8010D900_duelresult[i], j, D_8010D910_duelresult, 0);
            func_800550F4_main(D_8010D900_duelresult[i], j, 1);
            func_80055140_main(D_8010D900_duelresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010D900_duelresult[i], j, 0x4790);
            HuSprAttrSet(D_8010D900_duelresult[i], j, 0x1000);
            func_80055420_main(D_8010D900_duelresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos.x = GwPlayer[i].player_obj->coords.x;
                pos.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos, &pos2d);
                func_80054904_main(D_8010D900_duelresult[i], 0, pos2d.x - (n - 1) * 7, pos2d.y);
            } else {
                func_80054904_main(D_8010D900_duelresult[i], j, j * 14, 0);
            }
        }
        max = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && max < GwPlayer[j].coin) {
                max = GwPlayer[j].coin;
            }
        }
        if (max == GwPlayer[i].coin) {
            D_8010D668_duelresult[i] = omAddObj(0x1000, 0, 0, -1, func_8010753C_duelresult);
            D_8010D668_duelresult[i]->work[0] = i;
            D_8010D668_duelresult[i]->work[1] = n;
            D_8010D668_duelresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107A58_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8010D668_duelresult[i] != NULL) {
            omDelObj(D_8010D668_duelresult[i]);
            D_8010D668_duelresult[i] = NULL;
        }
        HuSprGrpKill(D_8010D900_duelresult[i]);
    }
    HuSprKill(D_8010D910_duelresult);
    HuPrcVSleep();
}

void func_80107AF4_duelresult(omObjData *obj) {
    f32 scale;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.2f + 0.5;
    HuVecCopyXYZ(&D_8010D914_duelresult[obj->work[0]]->scale, scale, scale, scale);
    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

/* Star count models over both duelers; the one with more stars pulses. */
void func_80107BC0_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010D914_duelresult[i] = func_800D8314_name_81(0x14000A, -1, 1.0f, 0.0f, NULL);
        if (GwPlayer[i].star == 0) {
            D_8010D91C_duelresult[i] = DataRead(0x130135);
            D_8010D924_duelresult[i] = (s16)HmfAnimCreate(HmfModelData[D_8010D914_duelresult[i]->omObj1->model[0]].hmf,
                                                     D_8010D91C_duelresult[i], 0, "sitagocoro_DEF");
        } else {
            D_8010D91C_duelresult[i] = DataRead(0x140034);
            D_8010D924_duelresult[i] = (s16)HmfAnimCreate(HmfModelData[D_8010D914_duelresult[i]->omObj1->model[0]].hmf,
                                                     D_8010D91C_duelresult[i], (s16)(GwPlayer[i].star - 1), "sitagocoro_DEF");
        }
        func_8001C448_main(D_8010D914_duelresult[i]->omObj1->model[0]);
        HuVecCopy3F(&D_8010D914_duelresult[i]->coords, &GwPlayer[i].player_obj->coords);
        D_8010D914_duelresult[i]->velocity.x = 280.0f;
        HuVecCopyXYZ(&D_8010D914_duelresult[i]->scale, 0.5f, 0.5f, 0.5f);
    }
    if (GwPlayer[0].star > GwPlayer[1].star) {
        D_8010D668_duelresult[0] = omAddObj(0x1000, 0, 0, -1, func_80107AF4_duelresult);
        D_8010D668_duelresult[0]->work[0] = 0;
    } else if (GwPlayer[1].star > GwPlayer[0].star) {
        D_8010D668_duelresult[0] = omAddObj(0x1000, 0, 0, -1, func_80107AF4_duelresult);
        D_8010D668_duelresult[0]->work[0] = 1;
    }
}

void func_80107E7C_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_80033430_main(D_8010D924_duelresult[i]);
        DataClose(D_8010D91C_duelresult[i]);
        func_800D8F3C_name_81(D_8010D914_duelresult[i]);
        if (D_8010D668_duelresult[i] != NULL) {
            omDelObj(D_8010D668_duelresult[i]);
            D_8010D668_duelresult[i] = NULL;
        }
    }
    HuPrcVSleep();
}

/* Process: the six cloud models fall; each wraps back to the top until D_8010D678 is set. */
void func_80107F3C_duelresult(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->coords, D_8010D8B0_duelresult[i]->coords.x,
                         D_8010D67C_duelresult + D_8010D930_duelresult[i] + D_8010D8B0_duelresult[i]->coords.y,
                         D_8010D8B0_duelresult[i]->coords.z);
            if (D_8010D8B0_duelresult[i]->coords.y >= 1000.0f) {
                HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->coords, (func_800EFE20_name_81(300.0f) - 150) * 5.0f,
                             -(func_800EFE20_name_81(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                D_8010D930_duelresult[i] = func_800EFE20_name_81(D_8010D67C_duelresult / 2.0f) - D_8010D67C_duelresult / 4.0f;
                if (D_8010D678_duelresult != 0) {
                    func_800D8F0C_name_81(D_8010D8B0_duelresult[i]);
                    D_8010D680_duelresult[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

/* All six clouds have stopped. */
s32 func_80108138_duelresult(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010D680_duelresult[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void func_80108174_duelresult(DuelResultWork *work, s32 i) {
    s32 x;
    s32 y;
    s32 z;

    x = func_800EFE20_name_81(256.0f) - 128;
    y = -func_800EFE20_name_81(256.0f) - 500;
    func_8010AC84_duelresult(work, x, y, 0);
    x = func_800EFE20_name_81(100.0f) + i * 500 - 550;
    y = func_800EFE20_name_81(64.0f) + 218;
    z = func_800EFE20_name_81(500.0f) - 500;
    func_8010AC74_duelresult(work, x, y, z);
    func_8010AC94_duelresult(work, func_800EFE20_name_81(60.0f) + 30);
}

/* Process: three flyers cross the screen; now and then all three line up behind the first. */
void func_801082C0_duelresult(void) {
    DuelResultWork *works[3];
    s32 i;
    s32 n;

    for (i = 0; i < 3; i++) {
        works[i] = func_8010ABE0_duelresult(D_8010D698_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
        func_80108174_duelresult(works[i], i);
        func_8010AC9C_duelresult(works[i], 2, 2);
    }
    while (1) {
        for (i = 0; i < 3; i++) {
            if ((func_8010ACB4_duelresult(works[i]) & 1) && (rand8() & 0xFF) < 0x20) {
                while (1) {
                    for (i = 0, n = 0; i < 3; i++) {
                        func_8010AC9C_duelresult(works[i], 2, 0);
                        n += func_8010ACB4_duelresult(works[i]) & 1;
                    }
                    if (n >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                func_80108174_duelresult(works[0], 0);
                func_8010AC74_duelresult(works[0], 0.0f, 250.0f, 1500.0f);
                func_8010AC9C_duelresult(works[0], 1, 0);
                func_8010AC6C_duelresult(works[0], 0xB0046);
                func_8010ACBC_duelresult(works[0], 120);
                while (1) {
                    for (i = 0, n = 0; i < 3; i++) {
                        func_8010AC9C_duelresult(works[i], 2, 0);
                        n += func_8010ACB4_duelresult(works[i]) & 1;
                    }
                    if (n >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    func_8010AC9C_duelresult(works[i], 3, 2);
                    func_8010AC6C_duelresult(works[i], D_8010D698_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                func_8010ACBC_duelresult(works[0], 60);
                func_80108174_duelresult(works[0], 0);
                break;
            }
            func_80108174_duelresult(works[i], i);
        }
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D7F0_duelresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D810_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/4554C0", func_8010856C_duelresult);

void func_8010A938_duelresult(void) {
    func_80105BD0_duelresult();
    func_8010856C_duelresult();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010A978_duelresult(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010ABB0_duelresult();
        func_8010AB1C_duelresult();
        if (D_8010D290_duelresult == 0) {
            func_8005F524_main();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            if (kakusiMasuItemHis[2] == 0) {
                GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
            }
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0) != 0) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0) != 0) {
            _ClearFlag(0);
            _ClearFlag(0x17);
            func_80050200_main(1);
        } else {
            func_80050064_main(1);
        }
        omOvlGotoEx(0x63, 0, 0x4190);
    }
}

void func_8010AA9C_duelresult(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 0x14);
        func_80007EC0_main(0x28);
        obj->func = func_8010A978_duelresult;
    }
}

void func_8010AAE8_duelresult() {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800EF840_name_81();
    func_800F4300_name_81();
}

void func_8010AB1C_duelresult() {
    func_800F4314_name_81();
    func_800EF880_name_81();
    func_800F4030_name_81();
    func_800D7F0C_name_81();
}

void func_8010AB50_duelresult(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

void func_8010ABB0_duelresult() {
    MBDBackKill();
    MBDBackClose();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D83C_duelresult);

/* .data */

s32 D_8010D290_duelresult = 0;
Vec D_8010D294_duelresult = { -750.0f, 400.0f, 2000.0f };
Vec D_8010D2A0_duelresult = { 750.0f, 400.0f, 2000.0f };
Vec D_8010D2AC_duelresult = { -750.0f, 500.0f, 4000.0f };
Vec D_8010D2B8_duelresult[2] = {
    { -250.0f, 0.0f, 2500.0f },
    { -250.0f, -400.0f, 2500.0f },
};
Vec D_8010D2D0_duelresult = { -500.0f, 400.0f, 3500.0f };
Vec D_8010D2DC_duelresult[3] = {
    { 750.0f, 250.0f, 4000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f },
};
Vec D_8010D300_duelresult[3] = {
    { 0.0f, -700.0f, 1500.0f },
    { 0.0f, -500.0f, 1000.0f },
    { 0.0f, -300.0f, 500.0f },
};
Vec D_8010D324_duelresult = { -200.0f, 400.0f, -150.0f };
Vec D_8010D330_duelresult = { 0.0f, 750.0f, 2500.0f };
Vec D_8010D33C_duelresult = { 0.0f, 250.0f, 2500.0f };
Vec D_8010D348_duelresult = { 0.0f, 400.0f, 2500.0f };
Vec D_8010D354_duelresult = { 0.0f, 1000.0f, 2500.0f };
Vec D_8010D360_duelresult = { 0.0f, 100.0f, 2500.0f };
Vec D_8010D36C_duelresult = { 500.0f, 50.0f, 500.0f };
Vec D_8010D378_duelresult[16] = {
    { -150.0f, 750.0f, 2000.0f },
    { 150.0f, 750.0f, 2000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f },
    { -150.0f, 100.0f, 2000.0f },
    { 150.0f, 100.0f, 2000.0f },
    { -150.0f, 0.0f, 2000.0f },
    { 150.0f, 0.0f, 2000.0f },
    { -150.0f, -500.0f, 2000.0f },
    { 150.0f, -500.0f, 2000.0f },
    { -150.0f, 800.0f, 2000.0f },
    { 150.0f, 800.0f, 2000.0f },
    { -150.0f, 150.0f, 2000.0f },
    { 150.0f, 150.0f, 2000.0f },
    { -150.0f, 350.0f, 2000.0f },
    { 150.0f, 350.0f, 2000.0f },
};
Vec D_8010D438_duelresult[8] = {
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 240.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
};
Vec D_8010D498_duelresult[2] = {
    { -750.0f, 150.0f, 1500.0f },
    { 750.0f, 150.0f, 1500.0f },
};
Vec D_8010D4B0_duelresult[2] = {
    { -225.0f, 150.0f, 2500.0f },
    { 225.0f, 150.0f, 2500.0f },
};
DrMotList2 D_8010D4C8_duelresult = { 2, { 0x2001B, 0x20024 } };
DrMotList6 D_8010D4D4_duelresult = { 6, { 0x2001F, 0x20030, 0x20034, 0x20039, 0x20029, 0x2008F } };
DrMotList2 D_8010D4F0_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D4FC_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D518_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D524_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D540_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D54C_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D568_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D574_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D590_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D59C_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D5B8_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D5C4_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList2 D_8010D5E0_duelresult = { 2, { 0, 0 } };
DrMotList6 D_8010D5EC_duelresult = { 6, { 0, 0, 0, 0, 0, 0 } };
DrMotList *D_8010D608_duelresult[8] = {
    (DrMotList *)&D_8010D4C8_duelresult,
    (DrMotList *)&D_8010D4F0_duelresult,
    (DrMotList *)&D_8010D518_duelresult,
    (DrMotList *)&D_8010D540_duelresult,
    (DrMotList *)&D_8010D568_duelresult,
    (DrMotList *)&D_8010D590_duelresult,
    (DrMotList *)&D_8010D5B8_duelresult,
    (DrMotList *)&D_8010D5E0_duelresult,
};
DrMotList *D_8010D628_duelresult[8] = {
    (DrMotList *)&D_8010D4D4_duelresult,
    (DrMotList *)&D_8010D4FC_duelresult,
    (DrMotList *)&D_8010D524_duelresult,
    (DrMotList *)&D_8010D54C_duelresult,
    (DrMotList *)&D_8010D574_duelresult,
    (DrMotList *)&D_8010D59C_duelresult,
    (DrMotList *)&D_8010D5C4_duelresult,
    (DrMotList *)&D_8010D5EC_duelresult,
};
s32 D_8010D648_duelresult[5] = { 0x13015C, 0x13015D, 0x13015E, 0x13015F, 0x130160 };
DrMotList2 D_8010D65C_duelresult = { 2, { 0xA0077, 0xA0078 } };
omObjData *D_8010D668_duelresult[4] = { NULL, NULL, NULL, NULL };
s32 D_8010D678_duelresult = 0;
f32 D_8010D67C_duelresult = 50.0f;
s32 D_8010D680_duelresult[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_8010D698_duelresult[10] = { 0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045, 0, 0 };
u8 D_8010D6C0_duelresult[4][4] = { /* RGB colours (45A700.c) */
    { 0x00, 0xFF, 0xFF, 0x00 },
    { 0xFF, 0xA0, 0x28, 0x00 },
    { 0xFF, 0xFF, 0x00, 0x00 },
    { 0x00, 0xFF, 0x00, 0x00 },
};
DrFiles4 D_8010D6D0_duelresult = { { 0x1301C1, 0x1301C2, 0x1301C3, 0x1301C4 } };
DrPos4 D_8010D6E0_duelresult = { { { 200.0f, 60.0f }, { 80.0f, 0.0f }, { 0.0f, 120.0f }, { 80.0f, 120.0f } } };
DrPos4 D_8010D700_duelresult = { { { 120.0f, 60.0f }, { -80.0f, 0.0f }, { 0.0f, 120.0f }, { -80.0f, 120.0f } } };
DrF8 D_8010D720_duelresult = { { 120.0f, 120.0f, 180.0f, 160.0f, 160.0f, 190.0f, 120.0f, 180.0f } };
