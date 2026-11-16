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

typedef struct BrTexAnim { /* D_800D1714_main entry */
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ char unk_0B;
} BrTexAnim; /* size = 0xC */

extern BrTexAnim *D_800D1714_main;
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);

extern Vec D_8010E4D4_boardresult[]; /* [4 + i]: where player i lands on its block */
extern Object *D_8010EB48_boardresult[6]; /* the cloud models */
extern Object *D_8010EB60_boardresult[4]; /* the players' blocks */
extern Object *D_8010EB70_boardresult;
extern s16 D_8010EB74_boardresult;
extern s16 D_8010EB76_boardresult;
extern s32 D_8010EB88_boardresult[4]; /* coin count sprite groups */
extern s32 D_8010EB98_boardresult;    /* the digit sprite */

s16 func_8010685C_boardresult(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    u16 tex;

    data = DataRead(file);
    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_8010EB74_boardresult = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    tex = D_800D1714_main[(s16)anim].unk_00;
    D_8010EB76_boardresult = func_80032694_main(HmfModelData[model].hmf, anim, 0, name);
    func_8001C448_main(model);
    return tex;
}

void func_80106968_boardresult(s16 model, s16 tex) {
    BrTexAnim *slot;

    if (D_8010EB76_boardresult != 0xFF) {
        if (tex == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[D_8010EB76_boardresult];
            slot->unk_00 = tex;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}

s16 func_80106A38_boardresult(s32 file) {
    void *data;
    s16 ret;

    data = DataRead(file);
    ret = func_800329B4_main(data);
    DataClose(data);
    return ret;
}

/* Scrolls the cloud texture of the three cloud layers. */
void func_80106A80_boardresult(omObjData *obj) {
    func_8001E888_main(D_8010EB48_boardresult[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB48_boardresult[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB48_boardresult[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);
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

void func_80106CA8_boardresult(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010EB60_boardresult[i]->rot.x = sindf(obj->rot.x);
        D_8010EB60_boardresult[i]->rot.z = cosdf(obj->rot.x);
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

void func_80106DA4_boardresult(omObjData *obj) {
    Object *o = D_8010EB60_boardresult[obj->work[1]];

    obj->work[0]++;
    o->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    o->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    o->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_80106F54_boardresult(omObjData *obj) {
    Object *o = D_8010EB70_boardresult;

    obj->work[0]++;
    o->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    o->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    o->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

/* Rotates model about X by angle (degrees). */
#define BR_ROTX(model, angle)                                                                      \
    sincosdf(angle, &HmfModelData[model].mtx[6], &HmfModelData[model].mtx[5]);                    \
    HmfModelData[model].mtx[9] = -HmfModelData[model].mtx[6];                                      \
    HmfModelData[model].mtx[10] = HmfModelData[model].mtx[5];                                      \
    HmfModelData[model].mtx[1] = HmfModelData[model].mtx[2] = HmfModelData[model].mtx[3] =          \
        HmfModelData[model].mtx[4] = HmfModelData[model].mtx[7] = HmfModelData[model].mtx[8] =      \
        HmfModelData[model].mtx[11] = HmfModelData[model].mtx[12] = HmfModelData[model].mtx[13] =   \
        HmfModelData[model].mtx[14] = 0.0f;                                                       \
    HmfModelData[model].mtx[0] = HmfModelData[model].mtx[15] = 1.0f

/* Process: player *(s32 *)user_data jumps out of its block. */
void func_801070F8_boardresult(void) {
    s32 i;
    s32 k;
    f32 angle;

    i = *(s32 *)HuPrcCurrentGet()->user_data;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                           &D_8010E4D4_boardresult[i + 4],
                                                           &D_8010EB38_boardresult[i]->player_obj->coords, 10));
    func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, 0, 0);
    angle = 90.0f;
    do {
        BR_ROTX(D_8010EB60_boardresult[3 - i]->omObj1->model[0], angle);
        HuPrcVSleep();
        angle -= 9.0f;
    } while (angle > 0.0f);
    BR_ROTX(D_8010EB60_boardresult[3 - i]->omObj1->model[0], 0.0f);
    HuAudFXPlay(0x175);
    k = 0;
    for (angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->coords, D_8010E4D4_boardresult[i + 4].x,
                     D_8010E4D4_boardresult[i + 4].y - sindf(angle) * 100.0f + k, D_8010E4D4_boardresult[i + 4].z);
        HuVecCopyXYZ(&D_8010EB60_boardresult[3 - i]->coords, D_8010E4D4_boardresult[i + 4].x,
                     D_8010E4D4_boardresult[i + 4].y - sindf(angle) * 100.0f + k, D_8010E4D4_boardresult[i + 4].z);
        k -= 10;
        HuPrcVSleep();
    }
    func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void func_80107598_boardresult(omObjData *obj) {
    f32 scale;
    s32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(D_8010EB88_boardresult[obj->work[0]], i, scale, scale);
    }
    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

extern omObjData *D_8010E8EC_boardresult[4]; /* the pulse objects over the leaders */
extern Object *D_8010EBA0_boardresult[4];   /* the stars that fall onto the players */
extern s16 D_8010EBB0_boardresult[4];        /* their sparkle effects */

void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800EFA8C_name_81(Object *arg0, s16 arg1, u16 arg2);

/* Coin count sprites over the players; the richest ones pulse. */
void func_801076A0_boardresult(void) {
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
    D_8010EB98_boardresult = func_80055810_main(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        D_8010EB88_boardresult[i] = HuSprGrpCreate(3, 5);
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
            func_80055024_main(D_8010EB88_boardresult[i], j, D_8010EB98_boardresult, 0);
            func_800550F4_main(D_8010EB88_boardresult[i], j, 1);
            func_80055140_main(D_8010EB88_boardresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010EB88_boardresult[i], j, 0x4790);
            HuSprAttrSet(D_8010EB88_boardresult[i], j, 0x1000);
            func_80055420_main(D_8010EB88_boardresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos.x = GwPlayer[i].player_obj->coords.x;
                pos.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos, &pos2d);
                func_80054904_main(D_8010EB88_boardresult[i], 0, pos2d.x - (n - 1) * 7, pos2d.y);
            } else {
                func_80054904_main(D_8010EB88_boardresult[i], j, j * 14, 0);
            }
        }
        max = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && max < GwPlayer[j].coin) {
                max = GwPlayer[j].coin;
            }
        }
        if (max == GwPlayer[i].coin) {
            D_8010E8EC_boardresult[i] = omAddObj(0x1000, 0, 0, -1, func_80107598_boardresult);
            D_8010E8EC_boardresult[i]->work[0] = i;
            D_8010E8EC_boardresult[i]->work[1] = n;
            D_8010E8EC_boardresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107AB4_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

/* Star count sprites over the players; the ones with the most stars pulse. */
void func_80107B50_boardresult(void) {
    s32 digits[2];
    Vec pos;
    Vec2f pos2d;
    void *data;
    s32 i;
    s32 j;
    s32 n;
    s32 star;
    s32 max;

    data = DataRead(0x1301C5);
    D_8010EB98_boardresult = func_80055810_main(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        D_8010EB88_boardresult[i] = HuSprGrpCreate(2, 5);
        star = GwPlayer[i].star;
        if (star >= 10) {
            n = 2;
            star %= 100;
            digits[0] = star / 10;
            star -= digits[0] * 10;
            digits[1] = star;
        } else {
            n = 1;
            digits[0] = star;
        }
        for (j = 0; j < n; j++) {
            func_80055024_main(D_8010EB88_boardresult[i], j, D_8010EB98_boardresult, 0);
            func_800550F4_main(D_8010EB88_boardresult[i], j, 1);
            func_80055140_main(D_8010EB88_boardresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010EB88_boardresult[i], j, 0x4790);
            HuSprAttrSet(D_8010EB88_boardresult[i], j, 0x1000);
            func_80055420_main(D_8010EB88_boardresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos.x = GwPlayer[i].player_obj->coords.x;
                pos.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos, &pos2d);
                func_80054904_main(D_8010EB88_boardresult[i], 0, pos2d.x - (n - 1) * 7, pos2d.y);
            } else {
                func_80054904_main(D_8010EB88_boardresult[i], j, j * 14, 0);
            }
        }
        max = GwPlayer[i].star;
        for (j = 0; j < 4; j++) {
            if (j != i && max < GwPlayer[j].star) {
                max = GwPlayer[j].star;
            }
        }
        if (max == GwPlayer[i].star) {
            D_8010E8EC_boardresult[i] = omAddObj(0x1000, 0, 0, -1, func_80107598_boardresult);
            D_8010E8EC_boardresult[i]->work[0] = i;
            D_8010E8EC_boardresult[i]->work[1] = n;
            D_8010E8EC_boardresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107EE8_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

/* A star falls onto each player with get[i] set (capped at 99 stars); then all the stars shrink away. */
void func_80107F84_boardresult(u8 *get) {
    s32 i;
    s32 j; /* the star's height while it falls; a player index after */
    f32 angle;

    for (i = 0; i < 4; i++) {
        if (get[i] != 0) {
            GwPlayer[i].star++;
            if (GwPlayer[i].star >= 100) {
                GwPlayer[i].star = 99;
            }
            func_800EFA8C_name_81(GwPlayer[i].player_obj, 1, 0);
            func_8004ACE0_main(0x274, i);
            func_800138EC_main(D_8010EBB0_boardresult[i], 0, 1);
            for (j = 800; j >= 250; j -= 15) {
                func_800D8E88_name_81(D_8010EBA0_boardresult[i]);
                HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->scale, 0.75f, 0.75f, 0.75f);
                HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->coords, GwPlayer[i].player_obj->coords.x,
                             j + GwPlayer[i].player_obj->coords.y, GwPlayer[i].player_obj->coords.z - 50.0f);
                angle = j * 2 - 160;
                D_8010EBA0_boardresult[i]->rot.x = sindf(angle);
                D_8010EBA0_boardresult[i]->rot.z = cosdf(angle);
                func_8000CFA4_main(D_8010EBB0_boardresult[i], D_8010EBA0_boardresult[i]->coords.x,
                                   D_8010EBA0_boardresult[i]->coords.y - 20.0f, D_8010EBA0_boardresult[i]->coords.z);
                if (j == 650) {
                    HuAudFXPlay(0x176);
                }
                HuPrcVSleep();
            }
            func_800138EC_main(D_8010EBB0_boardresult[i], 1, 0);
        }
    }
    for (j = 0; j < 4; j++) {
        if (get[j] != 0) {
            func_800EFABC_name_81(GwPlayer[j].player_obj);
        }
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x171);
    do {
        for (i = 0; i < 4; i++) {
            D_8010EBA0_boardresult[i]->scale.x -= 0.1f;
            D_8010EBA0_boardresult[i]->scale.y -= 0.1f;
            D_8010EBA0_boardresult[i]->scale.z -= 0.1f;
            D_8010EBA0_boardresult[i]->coords.y -= 20.0f;
        }
        HuPrcVSleep();
    } while (!(D_8010EBA0_boardresult[0]->scale.x <= 0.05f));
    for (i = 0; i < 4; i++) {
        func_800D8F0C_name_81(D_8010EBA0_boardresult[i]);
        HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->scale, 0.75f, 0.75f, 0.75f);
    }
    for (j = 0; j < 4; j++) {
        if (get[j] != 0) {
            func_800EFA8C_name_81(GwPlayer[j].player_obj, -1, 2);
        }
    }
}

// event e7: functions 80108378..8010BD04
struct BoardResultWork; /* 3BFA00.c: the 0x4C-byte work of a func_8010BD30 process */
struct BoardResultWork *func_8010BD30_boardresult(s32 arg0);
void func_8010BDBC_boardresult(struct BoardResultWork *arg0, s32 arg1);
void func_8010BDC4_boardresult(struct BoardResultWork *arg0, f32 x, f32 y, f32 z);
void func_8010BDD4_boardresult(struct BoardResultWork *arg0, f32 x, f32 y, f32 z);
void func_8010BDE4_boardresult(struct BoardResultWork *arg0, s16 arg1);
void func_8010BDEC_boardresult(struct BoardResultWork *arg0, s32 mask, s32 bits);
s16 func_8010BE04_boardresult(struct BoardResultWork *arg0);
void func_8010BE0C_boardresult(struct BoardResultWork *arg0, s16 arg1);
void func_80105BD8_boardresult(void);
void func_80109754_boardresult(void);
void func_8010BAD8_boardresult(omObjData *obj);
void func_8010BD04_boardresult(void);
void func_8010BC70_boardresult(void);
void func_80007EC0_main(s32);
s32 func_80050064_main(s32 write);
void GWPlayNumInc(s16 board);
void GWCharPlayNumInc(s16 board, s16 chr);
extern s16 kakusiMasuItemHis[];
extern s32 D_8010E3E0_boardresult;
extern s32 D_8010E908_boardresult;
extern f32 D_8010E90C_boardresult;
extern s32 D_8010E910_boardresult[6];
extern s32 D_8010E928_boardresult[];
extern Object *D_8010EB48_boardresult[6];
extern f32 D_8010EBB8_boardresult[6];
void func_80106968_boardresult(s16 model, s16 motion);
void func_80107F84_boardresult(u8 *tied);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800EB164_name_81(s16 arg0, s32 arg1);
void func_800EB4DC_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 frames);
extern u32 D_80101200_shared_board[]; /* per-character name, indexed by chr */
extern Vec D_8010E408_boardresult;
extern Vec D_8010E414_boardresult;
extern Vec D_8010E534_boardresult[4];
extern Vec *D_8010E8F8_boardresult[];
extern GW_PLAYER *D_8010EB38_boardresult[4];
extern Object *D_8010EB60_boardresult[4];
extern Object *D_8010EB70_boardresult;
extern s16 D_8010EB78_boardresult;
extern s16 D_8010EB7C_boardresult;
extern s16 D_8010EB7E_boardresult;
extern Object *D_8010EBA0_boardresult[4];
extern s16 D_8010EBB0_boardresult[4];

/* The bonus stars: for each award (minigame, coin, happening) the tied leaders' names fill the message,
   the host plays its animation and the winners walk up with their partner figure. */
// NON_MATCHING: masked 0; raw: the tie count and the walk-target table pointer take each other's
// saved registers (s4/s5).
#ifdef NON_MATCHING
void func_80108378_boardresult(void) {
    u8 tied[4];
    u32 names[4];
    s32 i;
    s32 j;
    s32 k;
    s32 max;
    Vec *dst;
    s32 n;

    for (i = 0; i < 4; i++) {
        Object *obj;

        obj = func_800D8010_name_81(0x1D, NULL);
        D_8010EBA0_boardresult[i] = obj;
        func_800D8F0C_name_81(obj);
        HuPrcVSleep();
        D_8010EBB0_boardresult[i] = func_8000CED8_main(0xB0004, 0x6A9);
        func_8000CD00_main(D_8010EBB0_boardresult[i], 10.0f, 20.0f, 8.0f);
        func_800138EC_main(D_8010EBB0_boardresult[i], 1, 0);
        HuPrcVSleep();
    }

    func_800EB164_name_81(-1, 0x1402);
    func_800EB164_name_81(-1, 0x1403);
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].gamePrize) {
            max = GwPlayer[i].gamePrize;
        }
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (GwPlayer[i].gamePrize == max) {
            tied[i] = 1;
            n++;
        } else {
            tied[i] = 0;
        }
    }
    for (i = 0, k = 0; i < 4; i++) {
        if (tied[i]) {
            names[k++] = D_80101200_shared_board[GwPlayer[i].chr];
        }
    }
    for (; k < 4; k++) {
        names[k] = 0;
    }
    {
        s32 msgs[4] = { 0x1404, 0x1405, 0x1406, 0x1407 };

        if (n == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[n - 1], names[0], names[1], names[2], names[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (n == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (n != 4) {
            dst = D_8010E8F8_boardresult[n];
            for (j = 0, i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &dst[j],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dst[j++],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWait();
            func_80107F84_boardresult(tied);
            dst = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                         &dst[i],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords,
                                                         &dst[i],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWait();
        }
        if (n == 3) {
            HuPrcChildLink(HuPrcCurrentGet(),
                           func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                 &D_8010EB70_boardresult->coords, 10));
        }
    }

    func_800EB164_name_81(-1, 0x1408);
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].coinPrize) {
            max = GwPlayer[i].coinPrize;
        }
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (GwPlayer[i].coinPrize == max) {
            tied[i] = 1;
            n++;
        } else {
            tied[i] = 0;
        }
    }
    for (i = 0, k = 0; i < 4; i++) {
        if (tied[i]) {
            names[k++] = D_80101200_shared_board[GwPlayer[i].chr];
        }
    }
    for (; k < 4; k++) {
        names[k] = 0;
    }
    {
        s32 msgs[4] = { 0x1409, 0x140A, 0x140B, 0x140C };

        if (n == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[n - 1], names[0], names[1], names[2], names[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (n == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (n != 4) {
            dst = D_8010E8F8_boardresult[n];
            for (j = 0, i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &dst[j],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dst[j++],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWait();
            func_80107F84_boardresult(tied);
            dst = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                         &dst[i],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords,
                                                         &dst[i],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWait();
        }
        if (n == 3) {
            HuPrcChildLink(HuPrcCurrentGet(),
                           func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                 &D_8010EB70_boardresult->coords, 10));
        }
    }

    func_800EB164_name_81(-1, 0x140D);
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].stats.prize.hatenaPrize) {
            max = GwPlayer[i].stats.prize.hatenaPrize;
        }
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (GwPlayer[i].stats.prize.hatenaPrize == max) {
            tied[i] = 1;
            n++;
        } else {
            tied[i] = 0;
        }
    }
    for (i = 0, k = 0; i < 4; i++) {
        if (tied[i]) {
            names[k++] = D_80101200_shared_board[GwPlayer[i].chr];
        }
    }
    for (; k < 4; k++) {
        names[k] = 0;
    }
    {
        s32 msgs[4] = { 0x140E, 0x140F, 0x1410, 0x1411 };

        if (n == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[n - 1], names[0], names[1], names[2], names[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (n == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (n != 4) {
            dst = D_8010E8F8_boardresult[n];
            for (j = 0, i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &dst[j],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dst[j++],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWait();
            func_80107F84_boardresult(tied);
            dst = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (tied[i]) {
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                         &dst[i],
                                                         &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords,
                                                         &dst[i],
                                                         &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWait();
        }
        if (n == 3) {
            HuPrcChildLink(HuPrcCurrentGet(),
                           func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                 &D_8010EB70_boardresult->coords, 10));
        }
    }
    for (i = 0; i < 4; i++) {
        func_800D8F3C_name_81(D_8010EBA0_boardresult[i]);
        func_8000D044_main(D_8010EBB0_boardresult[i]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80108378_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA60_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA70_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA80_boardresult);
#endif

void func_80109128_boardresult(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            Object *obj = D_8010EB48_boardresult[i];

            HuVecCopyXYZ(&obj->coords, obj->coords.x,
                         obj->coords.y - (D_8010E90C_boardresult + D_8010EBB8_boardresult[i]), obj->coords.z);
            if (D_8010EB48_boardresult[i]->coords.y <= -1000.0f) {
                HuVecCopyXYZ(&D_8010EB48_boardresult[i]->coords, (func_800EFE20_name_81(300.0f) - 150) * 5.0f,
                             (func_800EFE20_name_81(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                D_8010EBB8_boardresult[i] =
                    func_800EFE20_name_81(D_8010E90C_boardresult / 2.0f) - D_8010E90C_boardresult / 4.0f;
                if (D_8010E908_boardresult != 0) {
                    func_800D8F0C_name_81(D_8010EB48_boardresult[i]);
                    D_8010E910_boardresult[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

s32 func_80109320_boardresult(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010E910_boardresult[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void func_8010935C_boardresult(struct BoardResultWork *work, s32 slot) {
    s32 x;
    s32 y;
    s32 z;

    x = func_800EFE20_name_81(256.0f) - 128;
    y = -func_800EFE20_name_81(256.0f) - 500;
    func_8010BDD4_boardresult(work, x, y, 0.0f);
    x = func_800EFE20_name_81(100.0f) + slot * 500 - 550;
    y = func_800EFE20_name_81(64.0f) + 218;
    z = func_800EFE20_name_81(500.0f) - 500;
    func_8010BDC4_boardresult(work, x, y, z);
    func_8010BDE4_boardresult(work, func_800EFE20_name_81(60.0f) + 30);
}

void func_801094A8_boardresult(void) {
    struct BoardResultWork *work[3];
    s32 i;
    s32 n;

    for (i = 0; i < 3; i++) {
        work[i] = func_8010BD30_boardresult(D_8010E928_boardresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
        func_8010935C_boardresult(work[i], i);
        func_8010BDEC_boardresult(work[i], 2, 2);
    }
    while (1) {
        for (i = 0; i < 3; i++) {
            if ((func_8010BE04_boardresult(work[i]) & 1) && rand8() < 0x20) {
                while (1) {
                    for (i = 0, n = 0; i < 3; i++) {
                        func_8010BDEC_boardresult(work[i], 2, 0);
                        n += func_8010BE04_boardresult(work[i]) & 1;
                    }
                    if (n >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                func_8010935C_boardresult(work[0], 0);
                func_8010BDC4_boardresult(work[0], 0.0f, 250.0f, 1500.0f);
                func_8010BDEC_boardresult(work[0], 1, 0);
                func_8010BDBC_boardresult(work[0], 0xB0046);
                func_8010BE0C_boardresult(work[0], 120);
                while (1) {
                    for (i = 0, n = 0; i < 3; i++) {
                        func_8010BDEC_boardresult(work[i], 2, 0);
                        n += func_8010BE04_boardresult(work[i]) & 1;
                    }
                    if (n >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    func_8010BDEC_boardresult(work[i], 3, 2);
                    func_8010BDBC_boardresult(work[i], D_8010E928_boardresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                func_8010BE0C_boardresult(work[0], 60);
                func_8010935C_boardresult(work[0], 0);
                break;
            }
            func_8010935C_boardresult(work[i], i);
        }
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA90_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EAB0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109754_boardresult);

void func_8010BA98_boardresult(void) {
    func_80105BD8_boardresult();
    func_80109754_boardresult();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010BAD8_boardresult(omObjData *obj) {
    if (WipeStatGet() != 0) {
        return;
    }
    func_8010BD04_boardresult();
    func_8010BC70_boardresult();
    if (D_8010E3E0_boardresult == 0) {
        func_8005F524_main();
    }
    if (!(GwSystem.playMode & 4)) {
        GWPlayNumInc(-1);
        GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
    }
    if (GwSystem.playMode & 4) {
        if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x28);
        }
    } else if (_CheckFlag(0)) {
        _ClearFlag(0);
        _ClearFlag(0x16);
        func_800500E0_main(1);
    } else {
        func_80050064_main(1);
    }
    omOvlGotoEx(0x55, 0, 0x4190);
}

void func_8010BBF0_boardresult(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        func_80007EC0_main(40);
        obj->func = func_8010BAD8_boardresult;
    }
}

void func_8010BC3C_boardresult(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800EF840_name_81();
    func_800F4300_name_81();
}

void func_8010BC70_boardresult(void) {
    func_800F4314_name_81();
    func_800EF880_name_81();
    func_800F4030_name_81();
    func_800D7F0C_name_81();
}

void func_8010BCA4_boardresult(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

void func_8010BD04_boardresult(void) {
    MBDBackKill();
    MBDBackClose();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EADC_boardresult);
