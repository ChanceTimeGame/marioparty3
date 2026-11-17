#include "common.h"

// story u4: .data 0x801153B0..0x801154F0 (the rodata 80115740..80115880 is asm/data/overlays/mstory3/4C2780.rodata.s)
extern char D_80115880_mstory3[], D_8011588C_mstory3[], D_80115898_mstory3[], D_801158A4_mstory3[];
extern char D_801158B0_mstory3[], D_801158BC_mstory3[], D_801158C8_mstory3[], D_801158D4_mstory3[];
Vec D_801153B0_mstory3 = { 0.0f, 90.0f, 0.0f };
Vec D_801153BC_mstory3 = { 0.0f, 0.0f, 0.0f };
Vec D_801153C8_mstory3 = { 0.0f, 0.0f, 0.0f };
Vec D_801153D4_mstory3 = { 0.0f, -157.81f, 0.0f };
/* model names, as D_80115380 in 4B29E0 */
char *D_801153E0_mstory3[8] = {
    D_801158D4_mstory3, D_801158C8_mstory3, D_801158BC_mstory3, D_801158B0_mstory3,
    D_801158A4_mstory3, D_80115898_mstory3, D_8011588C_mstory3, D_80115880_mstory3,
};
Vec D_80115400_mstory3[4] = { { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_80115430_mstory3[6] = { { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f }, { 400.0f, 400.0f, 200.0f }, { -50.0f, 120.0f, 450.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_80115478_mstory3[4] = { { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_801154A8_mstory3[6] = { { -70.0f, 300.0f, 300.0f }, { 122.0f, 450.0f, -122.0f }, { 314.0f, 500.0f, -544.0f }, { 506.0f, 450.0f, -966.0f }, { 700.0f, 150.0f, -1390.3f }, { 9999.0f, 9999.0f, 9999.0f } };
// end story u4

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010C9F0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010CCF4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010D59C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010D5CC_mstory3);

void func_8010D774_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010D77C_mstory3);

void func_8010D974_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010D97C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010DA00_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010E170_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010EBE4_mstory3);

void func_8010F658_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010F660_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010FCA4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010FD64_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115880_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011588C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115898_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158A4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158B0_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010FDB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801103E8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110474_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110558_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110628_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011065C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011067C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110774_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110978_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110A84_mstory3);

void func_80110CAC_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110CB4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115908_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115914_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115920_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011592C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115938_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115944_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115950_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011595C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110E30_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110F04_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80110FE8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111064_mstory3);

void func_801110AC_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801110B4_mstory3);

// story u4
/* a chapter 3 scene actor: its object, the action its process runs every frame, and its state */
typedef struct Story3Actor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
} Story3Actor; /* size = 0x14 */

typedef void (*Story3Func)(omObjData *);
typedef struct ObPath ObPath; /* the path library at the start of this unit (mstory1's 48D950) */

extern Story3Actor D_80115CB0_mstory3[11];
extern s16 D_80115D8C_mstory3; /* shadow model, linked by every actor */
extern s16 D_80115D8E_mstory3;
extern s16 D_80115D90_mstory3[3]; /* texture animations */
extern s16 D_80115D96_mstory3;
extern s16 D_80115C9C_mstory3[];
extern s16 D_80115CA2_mstory3[];
extern const Vec D_8011598C_mstory3;
extern const Vec D_80115998_mstory3;
extern const Vec D_801159BC_mstory3;
extern const Vec D_801159C8_mstory3;
extern const Vec D_801159D4_mstory3;
extern const Vec D_801159E0_mstory3;
extern const Vec D_801159F8_mstory3;
extern const Vec D_80115A10_mstory3;
extern const Vec D_80115A1C_mstory3;
extern const Vec D_80115A28_mstory3;
extern const Vec D_80115A34_mstory3;
extern const Vec D_80115A40_mstory3;
extern const Vec D_80115A4C_mstory3;
extern const Vec D_80115A58_mstory3;
extern const Vec D_80115A64_mstory3;
extern const Vec D_80115A70_mstory3;
extern const Vec D_80115A7C_mstory3;
extern const Vec D_80115A88_mstory3;
extern const Vec D_80115A94_mstory3;
extern const Vec D_80115AA0_mstory3;
extern const Vec D_80115B24_mstory3;
extern const Vec D_80115B30_mstory3;
extern const Vec D_80115B3C_mstory3;
extern const Vec D_80115B48_mstory3;
extern const Vec D_80115B54_mstory3;
extern Vec D_80115400_mstory3[4];
extern Vec D_80115430_mstory3[6];
extern Vec D_80115478_mstory3[4];
extern Vec D_801154A8_mstory3[6];

void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8001FA68_main(s16);
void func_8001F9E4_main(s16, u8);
void func_80106CF0_mstory3(s16 model, s16 anim, s16 frame);
void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107070_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107244_mstory3(s16 model);
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_80107674_mstory3(omObjData *obj, omObjData *target);
ObPath *func_8010C9F0_mstory3(Vec *points, s16 flags);
void func_8010CCF4_mstory3(ObPath *path, f32 t, Vec *out);
void func_8010D59C_mstory3(ObPath *path);
void func_8010D774_mstory3(void);
void func_8010FCA4_mstory3(omObjData *obj);
void func_8010FD64_mstory3(omObjData *obj);
void func_80110474_mstory3(omObjData *obj);
void func_80110558_mstory3(omObjData *obj);
void func_80110F04_mstory3(omObjData *obj);
void func_80110FE8_mstory3(omObjData *obj);
void func_8011175C_mstory3(void);
void func_801122BC_mstory3(void);
void func_80112B80_mstory3(void);
void func_801134D8_mstory3(void);
void func_80113960_mstory3(void);
void func_80113BA8_mstory3(void);
void func_80114AF8_mstory3(void);
void func_80111CB8_mstory3(omObjData *obj);
void func_80111E2C_mstory3(omObjData *obj);
void func_80111F3C_mstory3(omObjData *obj);
void func_801125C4_mstory3(omObjData *obj);
void func_8011268C_mstory3(omObjData *obj);
void func_8011270C_mstory3(omObjData *obj);
void func_80112650_mstory3(omObjData *obj);
void func_80112834_mstory3(omObjData *obj);
void func_80112EF0_mstory3(omObjData *obj);
void func_80112FB0_mstory3(omObjData *obj);
void func_8011322C_mstory3(omObjData *obj);
void func_80113874_mstory3(omObjData *obj);
void func_80114920_mstory3(omObjData *obj);
void func_80114EF8_mstory3(omObjData *obj);
void func_80114FA4_mstory3(omObjData *obj);
void func_8011522C_mstory3(omObjData *obj);

#define STORY3_IDLE ((Story3Func)func_8010D774_mstory3)
// end story u4

void func_80111500_mstory3(omObjData *obj) {
    func_8001C624_main(D_80115CB0_mstory3[2].obj->model[1], HmfModelData[D_80115CB0_mstory3[2].obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, (Vec *)&D_8011598C_mstory3, 10);
    func_8001C624_main(D_80115CB0_mstory3[2].obj->model[1], HmfModelData[D_80115CB0_mstory3[2].obj->motion[0]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[2].func = STORY3_IDLE;
}

void func_801115D8_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    D_80115CB0_mstory3[8].func = func_80114920_mstory3;
    func_8001C624_main(D_80115CB0_mstory3[0].obj->model[1], HmfModelData[D_80115CB0_mstory3[0].obj->motion[13]].unk02, 0, 10, 2);
    func_8001C92C_main(D_80115CB0_mstory3[0].obj->model[1], 0.5f);
    D_80115CB0_mstory3[2].unk0C = 1;
    D_80115CB0_mstory3[2].unk10 = 40;
    func_80106DC4_mstory3(obj, (Vec *)&D_80115998_mstory3, 60);
    D_80115CB0_mstory3[2].unk0C = 0;
    func_8001C92C_main(D_80115CB0_mstory3[0].obj->model[1], 1.0f);
    func_8001C624_main(D_80115CB0_mstory3[0].obj->model[1], HmfModelData[D_80115CB0_mstory3[0].obj->motion[0]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[2].unk08 = 1;
    D_80115CB0_mstory3[2].func = STORY3_IDLE;
}

void func_8011175C_mstory3(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011598C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115998_mstory3);

void func_80111764_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[3].obj = obj;
    D_80115CB0_mstory3[3].unk08 = 0;
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 38.0f, 100.0f, 214.0f);
    Hu3DModelPosSet(obj->model[2], 38.0f, -5.0f, 214.0f);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    data = DataRead(0xA007E);
    D_80115D90_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    D_80115D8E_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D90_mstory3[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0080);
    D_80115D90_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115D8E_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D90_mstory3[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0083);
    D_80115D90_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115D90_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115D90_mstory3[0], 0);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    omPrcSetDestructor(0, func_8011175C_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[3].func(obj);
        HuPrcVSleep();
    }
}

const Vec D_801159B0_mstory3 = { 10.0f, 378.9f, 0.0f };

void func_80111A58_mstory3(omObjData *obj) {
    HuPrcSleep(60);
    D_80115CB0_mstory3[0].func = func_8010FCA4_mstory3;
    D_80115CB0_mstory3[4].func = func_801125C4_mstory3;
    func_80107070_mstory3(obj, (Vec *)&D_801159B0_mstory3, 30);
    func_80106DC4_mstory3(obj, (Vec *)&D_801159D4_mstory3, 20);
    HuPrcSleep(30);
    func_80107070_mstory3(obj, (Vec *)&D_801159BC_mstory3, 10);
    func_80106DC4_mstory3(obj, (Vec *)&D_801159E0_mstory3, 15);
    D_80115CB0_mstory3[0].func = func_8010FD64_mstory3;
    func_80107070_mstory3(obj, (Vec *)&D_801159C8_mstory3, 10);
    D_80115CB0_mstory3[3].unk08 = 1;
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159E0_mstory3);

#ifdef NON_MATCHING
void func_80111B34_mstory3(omObjData *obj) {
    f32 y;
    s16 i;

    y = HmfModelData[obj->model[1]].pos.y;
    for (i = 0; i < 12; i++) {
        HmfModelData[obj->model[1]].pos.y = y + sindf(i * 15.0) * 80.0f;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[3].unk08 = 1;
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111B34_mstory3);
#endif

void func_80111C50_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    func_80107070_mstory3(obj, (Vec *)&D_801159F8_mstory3, 5);
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159F8_mstory3);

#ifdef NON_MATCHING
void func_80111CB8_mstory3(omObjData *obj) {
    f32 y;
    s16 i;

    y = HmfModelData[obj->model[1]].pos.y;
    for (i = 0; i < 10; i++) {
        HmfModelData[obj->model[1]].pos.y = y + sindf(i * 15.0) * 100.0f;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[0].func = func_80110558_mstory3;
    D_80115CB0_mstory3[4].func = func_8011268C_mstory3;
    D_80115CB0_mstory3[5].func = func_80112EF0_mstory3;
    D_80115CB0_mstory3[3].unk08 = 1;
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111CB8_mstory3);
#endif

void func_80111DF8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, (Vec *)&D_80115A10_mstory3, 5);
    D_80115CB0_mstory3[3].func = func_80111E2C_mstory3;
}

void func_80111E2C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111E4C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
        func_80107070_mstory3(obj, (Vec *)&D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].unk08 = 2;
        D_80115CB0_mstory3[3].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[3].unk08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[1]);
        func_80107070_mstory3(obj, (Vec *)&D_80115A28_mstory3, 10);
        D_80115CB0_mstory3[3].unk08 = 3;
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    } else if (D_80115CB0_mstory3[3].unk08 == 3) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    }
}

void func_80111F3C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111F5C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[3].func = STORY3_IDLE;
}

void func_80111FA4_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk08 == 0) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk08 = 1;
        D_80115CB0_mstory3[3].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[3].unk08 == 1) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A40_mstory3, 10);
        D_80115CB0_mstory3[3].unk08 = 2;
        D_80115CB0_mstory3[3].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[3].unk08 == 2) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk08 = 0;
        D_80115CB0_mstory3[3].func = STORY3_IDLE;
    }
}

void func_8011204C_mstory3(omObjData *obj) {
    f32 rot;
    f32 d;
    s16 i;

    if (D_80115CB0_mstory3[3].unk08 == 0) {
        HuPrcSleep(30);
    }
    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        d = sindf(i * 9.0f) * 120.0f;
        HmfModelData[obj->model[1]].rot.y = rot + d;
        HuPrcVSleep();
    }
    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        d = sindf(i * 4.5f) * 240.0f;
        HmfModelData[obj->model[1]].rot.y = rot - d;
        HuPrcVSleep();
    }
    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        d = sindf(i * 9.0f) * 120.0f;
        HmfModelData[obj->model[1]].rot.y = rot + d;
        HuPrcVSleep();
    }
    if (D_80115CB0_mstory3[3].unk08 == 0) {
        D_80115CB0_mstory3[3].unk08 = 0;
        D_80115CB0_mstory3[3].func = func_80111CB8_mstory3;
    } else {
        D_80115CB0_mstory3[3].unk08 = 0;
        D_80115CB0_mstory3[3].func = STORY3_IDLE;
    }
}

void func_801122BC_mstory3(void) {
}

void func_801122C4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[4].obj = obj;
    D_80115CB0_mstory3[4].unk08 = 0;
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    func_8000B460_main(obj, 3, 0xA0129);
    func_8000B460_main(obj, 4, 0xA012A);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 150.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 150.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    omPrcSetDestructor(0, func_801122BC_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[4].func(obj);
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
void func_8011249C_mstory3(void) {
    Vec pos;
    f32 angle;
    omObjData *obj;
    f32 bob;

    angle = 0.0f;
    obj = D_80115CB0_mstory3[4].obj;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = HmfModelData[obj->model[1]].pos.x;
        pos.z = HmfModelData[obj->model[1]].pos.z;
        bob = sindf(angle) * 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        Hu3DModelPosSet(obj->model[1], pos.x, bob + 25.0f + pos.y, pos.z);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011249C_mstory3);
#endif

void func_801125C4_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, (Vec *)&D_80115A4C_mstory3, 20);
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_801125F8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, (Vec *)&D_80115A58_mstory3, 5);
    D_80115CB0_mstory3[8].unk08 = 2;
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_80112650_mstory3(omObjData *obj) {
    func_801074D8_mstory3(obj, 2.0f, 60);
    D_80115CB0_mstory3[4].unk08 = 1;
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_8011268C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, (Vec *)&D_80115A64_mstory3, 10);
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_801126D8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, (Vec *)&D_80115A70_mstory3, 5);
    D_80115CB0_mstory3[4].func = func_8011270C_mstory3;
}

void func_8011270C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_8011272C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk08 == 1) {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].unk08 = 2;
        D_80115CB0_mstory3[4].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[4].unk08 == 2) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A88_mstory3, 10);
        D_80115CB0_mstory3[4].unk08 = 3;
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    } else if (D_80115CB0_mstory3[4].unk08 == 3) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    }
}

void func_80112834_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112854_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_8011289C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk08 == 0) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk08 = 1;
        D_80115CB0_mstory3[4].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[4].unk08 == 1) {
        func_80107070_mstory3(obj, (Vec *)&D_80115AA0_mstory3, 10);
        D_80115CB0_mstory3[4].unk08 = 2;
        D_80115CB0_mstory3[4].func = STORY3_IDLE;
    } else if (D_80115CB0_mstory3[4].unk08 == 2) {
        func_80107070_mstory3(obj, (Vec *)&D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk08 = 0;
        D_80115CB0_mstory3[4].func = STORY3_IDLE;
    }
}

void func_80112944_mstory3(omObjData *obj) {
    f32 rot;
    f32 d;
    s16 i;

    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        d = sindf(i * 6.0f) * 30.0f;
        HmfModelData[obj->model[1]].rot.y = rot + d;
        HuPrcVSleep();
    }
    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 30; i++) {
        d = sindf(i * 3.0f) * 60.0f;
        HmfModelData[obj->model[1]].rot.y = rot - d;
        HuPrcVSleep();
    }
    rot = HmfModelData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        d = sindf(i * 6.0f) * 30.0f;
        HmfModelData[obj->model[1]].rot.y = rot + d;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].func = STORY3_IDLE;
}

void func_80112B80_mstory3(void) {
}

void func_80112B88_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[5].obj = obj;
    D_80115CB0_mstory3[5].unk08 = 0;
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0032);
    func_8000B460_main(obj, 4, 0x1D0034);
    func_8000B460_main(obj, 5, 0x1D0033);
    func_8000B460_main(obj, 6, 0x1D0035);
    func_8000B460_main(obj, 7, 0xA0038);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -700.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -700.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omPrcSetDestructor(0, func_80112B80_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A10_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A1C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A28_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A34_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A40_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A4C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A64_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A70_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A7C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A88_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A94_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115AA0_mstory3);

const Vec D_80115AAC_mstory3[10] = { { -350.0f, 0.0f, 480.0f } };

void func_80112DA0_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80115CB0_mstory3[0].func = func_80110474_mstory3;
    D_80115CB0_mstory3[4].func = func_80112650_mstory3;
    D_80115CB0_mstory3[1].func = func_80110F04_mstory3;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106DC4_mstory3(obj, (Vec *)D_80115AAC_mstory3, 60);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (TRUE) {
        if (D_80115CB0_mstory3[4].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].unk08 = 0;
    D_80115CB0_mstory3[1].func = STORY3_IDLE;
    D_80115CB0_mstory3[5].unk08 = 1;
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_80112EF0_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, (Vec *)&D_80115B24_mstory3, 10);
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_80112F7C_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, (Vec *)&D_80115B30_mstory3, 5);
    D_80115CB0_mstory3[5].func = func_80112FB0_mstory3;
}

void func_80112FB0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112FD0_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106DC4_mstory3(obj, (Vec *)&D_80115B3C_mstory3, 60);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[5].unk08 = 1;
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_801130A4_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_8011315C_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106DC4_mstory3(obj, (Vec *)&D_80115B48_mstory3, 30);
    func_8001C624_main(D_80115CB0_mstory3[5].obj->model[1], HmfModelData[D_80115CB0_mstory3[5].obj->motion[2]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_8011322C_mstory3(omObjData *obj) {
    f32 angle;
    s16 i;

    D_80115CB0_mstory3[9].func = STORY3_IDLE;
    HmfModelData[D_80115CB0_mstory3[5].obj->model[2]].pos.x = HmfModelData[D_80115CB0_mstory3[5].obj->model[1]].pos.x = -380.0f;
    func_8001C624_main(D_80115CB0_mstory3[5].obj->model[1], HmfModelData[D_80115CB0_mstory3[5].obj->motion[5]].unk02, 0, 10, 2);
    HmfModelData[D_80115CB0_mstory3[2].obj->model[1]].pos.x = HmfModelData[D_80115CB0_mstory3[2].obj->model[2]].pos.x = 100.0f;
    func_8001C5B4_main(D_80115CB0_mstory3[2].obj->model[1], D_80115CB0_mstory3[2].obj->motion[3]);
    func_8001C92C_main(D_80115CB0_mstory3[2].obj->model[1], 0.0f);
    func_8001C6A8_main(D_80115CB0_mstory3[2].obj->model[1], 19.0f);
    HuAudFXPlay(0x29D);
    for (i = 0; i < 30; i++) {
        angle = i * 3.0f;
        HmfModelData[D_80115CB0_mstory3[5].obj->model[1]].pos.x = sindf(angle) * -300.0f + -80.0f;
        HmfModelData[D_80115CB0_mstory3[5].obj->model[2]].pos.x = sindf(angle) * -175.0f + -80.0f;
        HmfModelData[D_80115CB0_mstory3[5].obj->model[2]].scale.x = HmfModelData[D_80115CB0_mstory3[5].obj->model[2]].scale.z = 5.0f;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[9].func = func_80114EF8_mstory3;
    D_80115CB0_mstory3[5].func = STORY3_IDLE;
}

void func_801134D8_mstory3(void) {
}

void func_801134E0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[6].obj = obj;
    D_80115CB0_mstory3[6].unk08 = 0;
    D_80115CB0_mstory3[6].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0x1D0039);
    func_8000B460_main(obj, 3, 0x1D003A);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    omPrcSetDestructor(0, func_801134D8_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113668_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, (Vec *)&D_80115B54_mstory3, 60);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[6].func = STORY3_IDLE;
}

void func_801136E8_mstory3(omObjData *obj) {
    s16 i;

    func_8001C624_main(obj->model[1], HmfModelData[D_80115CB0_mstory3[6].obj->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    for (i = 0; i < 10; i++) {
        f32 y = sindf(i * 9.0f) * 100.0f;

        HmfModelData[D_80115CB0_mstory3[5].obj->model[1]].pos.y = y;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[6].unk08 = 1;
    D_80115CB0_mstory3[6].func = STORY3_IDLE;
}

void func_80113800_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[D_80115CB0_mstory3[6].obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    D_80115CB0_mstory3[6].func = func_80113874_mstory3;
}

#ifdef NON_MATCHING
void func_80113874_mstory3(omObjData *obj) {
    Story3Actor *actors = &D_80115CB0_mstory3[6];
    omObjData *obj6 = actors[0].obj;
    omObjData *obj7 = actors[1].obj;
    omObjData *obj5 = actors[-1].obj;

    HmfModelData[obj6->model[2]].pos.x = HmfModelData[obj6->model[1]].pos.x += 10.0f;
    HmfModelData[obj7->model[2]].pos.x = HmfModelData[obj7->model[1]].pos.x += 10.0f;
    HmfModelData[obj5->model[1]].pos.x += 10.0f;
    HmfModelData[obj5->model[2]].pos.x += 10.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113874_mstory3);
#endif

void func_80113960_mstory3(void) {
}

void func_80113968_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[7].obj = obj;
    D_80115CB0_mstory3[7].unk08 = 0;
    D_80115CB0_mstory3[7].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 700.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 700.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    func_8001C624_main(obj->model[1], HmfModelData[D_80115CB0_mstory3[6].obj->motion[1]].unk02, 0, 10, 2);
    omPrcSetDestructor(0, func_80113960_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[7].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B24_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B30_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B3C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B48_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B54_mstory3);

const Vec D_80115B60_mstory3 = { -400.0f, 0.0f, 700.0f };

void func_80113AA8_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, (Vec *)&D_80115B60_mstory3, 60);
    Hu3DModelPosSet(obj->model[1], -500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -500.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115CB0_mstory3[7].unk08 = 1;
    D_80115CB0_mstory3[7].func = STORY3_IDLE;
}

void func_80113B3C_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[D_80115CB0_mstory3[6].obj->motion[3]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[7].func = STORY3_IDLE;
}

void func_80113BA8_mstory3(void) {
}

void func_80113BB0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[8].obj = obj;
    D_80115CB0_mstory3[8].unk08 = 0;
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0x1D0008, 0x20299);
    obj->model[2] = func_8000B108_main(0x1D0009, 0x20299);
    obj->model[4] = func_8000B108_main(0x1D0013, 0x2B9);
    obj->model[6] = func_8000B108_main(0x83, 0x2B9);
    obj->model[7] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[4], 750.0f, 100.0f, -1500.3f);
    Hu3DModelPosSet(obj->model[6], -150.0f, 270.0f, 300.0f);
    Hu3DModelPosSet(obj->model[7], 750.0f, 0.0f, -1500.3f);
    obj->model[3] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(obj->model[3], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[3], 60.0f);
    func_800138EC_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[5] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(obj->model[5], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[5], 60.0f);
    func_800138EC_main(obj->model[5], 1, 0);
    func_8001C258_main(obj->model[5], 4, 4);
    omPrcSetDestructor(0, func_80113BA8_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[8].func(obj);
        HuPrcVSleep();
    }
}

void func_80113E68_mstory3(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    f32 t;
    s16 i;

    path[0] = func_8010C9F0_mstory3(D_80115400_mstory3, 0);
    path[1] = func_8010C9F0_mstory3(D_80115430_mstory3, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    func_800138EC_main(obj->model[3], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        if (i == 20) {
            func_8001C624_main(D_80115CB0_mstory3[0].obj->model[1], HmfModelData[D_80115CB0_mstory3[0].obj->motion[12]].unk02, 0, 10, 2);
        }
        t = i * 0.02f;
        func_8010CCF4_mstory3(path[0], t * t, &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    func_8001C624_main(D_80115CB0_mstory3[4].obj->model[1], HmfModelData[D_80115CB0_mstory3[4].obj->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_80115CB0_mstory3[8].unk08 = 1;
    func_8001C624_main(D_80115CB0_mstory3[4].obj->model[1], HmfModelData[D_80115CB0_mstory3[4].obj->motion[0]].unk02, 0, 10, 0);
    HuAudFXPlay(0x218);
    for (i = 0; i < 120; i++) {
        t = i * (1.0f / 120.0f);
        func_8010CCF4_mstory3(path[1], t * t, &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        HmfModelData[obj->model[1]].rot.y += 24.0f;
        if (HmfModelData[obj->model[1]].rot.y >= 360.0f) {
            HmfModelData[obj->model[1]].rot.y -= 360.0f;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x21A);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_800138EC_main(obj->model[3], 1, 0);
    func_8010D59C_mstory3(path[0]);
    func_8010D59C_mstory3(path[1]);
    D_80115CB0_mstory3[8].unk08 = 2;
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
}

void func_80114260_mstory3(omObjData *obj) {
    func_80107674_mstory3(D_80115CB0_mstory3[5].obj, D_80115CB0_mstory3[0].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[0].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[4].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[3].obj, D_80115CB0_mstory3[5].obj);
}

void func_801142C0_mstory3(omObjData *obj) {
    Vec pos;
    ObPath *path;
    f32 t;
    s16 i;

    path = func_8010C9F0_mstory3(D_80115478_mstory3, 0);
    Hu3DModelPosSet(obj->model[2], -100.0f, 200.0f, 100.0f);
    func_8000CFA4_main(obj->model[5], -100.0f, 200.0f, 100.0f);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[5], 4, 0);
    func_800138EC_main(obj->model[5], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 30; i++) {
        t = i * (1.0f / 30.0f);
        func_8010CCF4_mstory3(path, t * t, &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010D59C_mstory3(path);
    D_80115CB0_mstory3[8].unk08 = 1;
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
}

void func_80114474_mstory3(omObjData *obj) {
    Vec pos;
    omObjData *actor2;
    ObPath *path;
    s16 i;

    actor2 = D_80115CB0_mstory3[2].obj;
    path = func_8010C9F0_mstory3(D_801154A8_mstory3, 0);
    func_8001C258_main(obj->model[6], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[5], 4, 0);
    func_800138EC_main(obj->model[5], 1, 1);
    HuAudFXPlay(0x21F);
    for (i = 0; i < 30; i++) {
        func_8010CCF4_mstory3(path, i * (1.0f / 30.0f), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        if (i == 25) {
            D_80115CB0_mstory3[1].func = func_80110FE8_mstory3;
        }
        HuPrcVSleep();
    }
    func_8010D59C_mstory3(path);
    func_8001C258_main(obj->model[5], 4, 4);
    func_800138EC_main(obj->model[3], 1, 0);
    HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[4]].pos.x;
    HmfModelData[obj->model[2]].pos.y = HmfModelData[obj->model[4]].pos.y;
    HmfModelData[obj->model[2]].pos.z = HmfModelData[obj->model[4]].pos.z;
    HmfModelData[obj->model[2]].rot.y = 0.0f;
    D_80115D96_mstory3 = 1;
    func_8001C258_main(actor2->model[1], 4, 4);
    func_8001C258_main(actor2->model[2], 4, 4);
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
}

void func_8011475C_mstory3(omObjData *obj) {
    Vec pos;
    s16 i;

    pos.x = HmfModelData[obj->model[4]].pos.x;
    pos.y = HmfModelData[obj->model[4]].pos.y;
    pos.z = HmfModelData[obj->model[4]].pos.z;
    for (i = 0; i < 50; i++) {
        pos.x -= 3.5;
        pos.y += 1.75;
        pos.z += 19.25;
        HmfModelData[obj->model[2]].pos.z = HmfModelData[obj->model[4]].pos.z = pos.z;
        HmfModelData[obj->model[2]].pos.y = HmfModelData[obj->model[4]].pos.y = pos.y;
        HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[4]].pos.x = pos.x;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
}

void func_80114920_mstory3(omObjData *obj) {
    s16 i;

    for (i = 0; i < 60; i++) {
        HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[4]].pos.x += 15.0f;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = STORY3_IDLE;
}

void func_801149D0_mstory3(void) {
    while (TRUE) {
        if (D_80115D96_mstory3 == 1) {
            HmfModelData[D_80115CB0_mstory3[8].obj->model[2]].rot.y += 12.0f;
            HmfModelData[D_80115CB0_mstory3[8].obj->model[7]].pos.x = HmfModelData[D_80115CB0_mstory3[8].obj->model[4]].pos.x;
            HmfModelData[D_80115CB0_mstory3[8].obj->model[7]].pos.y = -85.8f;
            HmfModelData[D_80115CB0_mstory3[8].obj->model[7]].pos.z = HmfModelData[D_80115CB0_mstory3[8].obj->model[4]].pos.z;
        }
        HuPrcVSleep();
    }
}

void func_80114AF8_mstory3(void) {
}

void func_80114B00_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[9].obj = obj;
    D_80115CB0_mstory3[9].unk08 = 0;
    D_80115CB0_mstory3[9].func = STORY3_IDLE;
    obj->model[1] = func_8000B108_main(0x1D0030, 0x2A8);
    obj->model[2] = func_8000B108_main(0x83, 0x2B9);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8001FA68_main(obj->model[1]);
    func_8001F9E4_main(obj->model[1], 0xFF);
    Hu3DModelPosSet(obj->model[1], 0.0f, -25.0f, 800.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x1D0030);
    func_8000B460_main(obj, 1, 0x83);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    omPrcSetDestructor(0, func_80114AF8_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[9].func(obj);
        HuPrcVSleep();
    }
}

void func_80114CD8_mstory3(omObjData *obj) {
    f32 scale;
    s16 i;

    HuPrcSleep(10);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C258_main(obj->model[4], 4, 0);
    HuAudFXPlay(0x220);
    for (i = 0; i < 10; i++) {
        scale = 2.0f * sindf(i * 9.0f);
        Hu3DModelScaleSet(obj->model[1], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    HmfModelData[D_80115CB0_mstory3[2].obj->model[1]].pos.x = HmfModelData[D_80115CB0_mstory3[2].obj->model[2]].pos.x = 100.0f;
    HmfModelData[D_80115CB0_mstory3[3].obj->model[1]].rot.y = 0.0f;
    HmfModelData[D_80115CB0_mstory3[4].obj->model[1]].rot.y = 0.0f;
    HmfModelData[D_80115CB0_mstory3[0].obj->model[1]].rot.y = 0.0f;
    func_8001C624_main(D_80115CB0_mstory3[4].obj->model[1], HmfModelData[D_80115CB0_mstory3[4].obj->motion[4]].unk02, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[9].func = func_80114FA4_mstory3;
}

void func_80114EF8_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], 4, 4);
    HuPrcSleep(30);
    func_8001C92C_main(D_80115CB0_mstory3[2].obj->model[1], 1.0f);
    func_8001C624_main(D_80115CB0_mstory3[2].obj->model[1], HmfModelData[D_80115CB0_mstory3[2].obj->motion[0]].unk02, 0, 10, 2);
    D_80115CB0_mstory3[9].unk08 = 1;
    D_80115CB0_mstory3[9].func = STORY3_IDLE;
}

#ifdef NON_MATCHING
void func_80114FA4_mstory3(omObjData *obj) {
    f32 angle;
    f32 x;
    s16 i;

    for (i = 2; i < 5; i++) {
        if (D_80115C9C_mstory3[i] == 0) {
            if ((u8)(rand8() % 7) == 0) {
                angle = (u8)(rand8() % 200) - 10.0f;
                x = cosdf(angle) * 175.0f;
                Hu3DModelPosSet(obj->model[i], x, sindf(angle) * 175.0f, 500.0f);
                func_8001C5B4_main(obj->model[i], obj->motion[1]);
                D_80115C9C_mstory3[i] = 1;
                D_80115CA2_mstory3[i] = 10;
            }
        } else if (--D_80115CA2_mstory3[i] <= 0) {
            D_80115C9C_mstory3[i] = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114FA4_mstory3);
#endif

void func_8011517C_mstory3(omObjData *obj) {
    do {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[(rand8() & 1) + 8]].unk02, 0, 10, 0);
        func_80107244_mstory3(obj->model[1]);
        HuPrcVSleep();
    } while (D_80115CB0_mstory3[2].unk08 != 1);
    D_80115CB0_mstory3[2].func = func_8011522C_mstory3;
}

void func_8011522C_mstory3(omObjData *obj) {
    D_80115CB0_mstory3[5].func = func_8011322C_mstory3;
    D_80115CB0_mstory3[2].func = STORY3_IDLE;
    D_80115CB0_mstory3[2].unk08 = 0;
}
