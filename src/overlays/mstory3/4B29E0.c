#include "common.h"

// story u4: .data 0x80115260..0x801153B0 (the rodata after it, 801154F0..80115740, is asm/data/overlays/mstory3/4C2530.rodata.s)
extern char D_80115668_mstory3[], D_80115674_mstory3[], D_80115680_mstory3[], D_8011568C_mstory3[];
extern char D_80115698_mstory3[], D_801156A4_mstory3[], D_801156B0_mstory3[], D_801156BC_mstory3[];
Vec D_80115260_mstory3 = { 14.0f, 193.0f, 1400.0f };
Vec D_8011526C_mstory3 = { -25.0f, 0.0f, -650.0f };
Vec D_80115278_mstory3 = { 0.0f, 1.0f, -0.0001f };
s16 D_80115284_mstory3 = 0;
s16 D_80115286_mstory3 = 0;
s32 D_80115288_mstory3 = 0;
s32 D_8011528C_mstory3 = 0;
Vec D_80115290_mstory3[4] = { { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_801152C0_mstory3[6] = { { -100.0f, 300.0f, 300.0f }, { -200.0f, 400.0f, -100.0f }, { 0.0f, 200.0f, 100.0f }, { 9999.0f, 9999.0f, 9999.0f }, { 0.0f, 158.73f, 0.0f }, { 0.0f, 167.01f, 0.0f } };
Vec D_80115308_mstory3 = { 0.0f, 158.46f, 0.0f };
Vec D_80115314_mstory3 = { 0.0f, -70.43f, 0.0f };
Vec D_80115320_mstory3 = { 0.0f, -77.13f, 0.0f };
Vec D_8011532C_mstory3[4] = { { 0.0f, -135.0f, 0.0f }, { 0.0f, 162.4f, 0.0f }, { 0.0f, -147.34f, 0.0f }, { 0.0f, 306.61f, 0.0f } };
Vec D_8011535C_mstory3 = { 0.0f, 90.0f, 0.0f };
Vec D_80115368_mstory3 = { 0.0f, 50.19f, 0.0f };
Vec D_80115374_mstory3 = { 0.0f, 100.78f, 0.0f };
/* model names "c000l_0_DEF" .. "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF" */
char *D_80115380_mstory3[8] = {
    D_801156BC_mstory3, D_801156B0_mstory3, D_801156A4_mstory3, D_80115698_mstory3,
    D_8011568C_mstory3, D_80115680_mstory3, D_80115674_mstory3, D_80115668_mstory3,
};
char *D_801153A0_mstory3[2] = { D_801156BC_mstory3, D_801156B0_mstory3 };
u32 D_801153A8_mstory3[2] = { 0 }; /* file end padding (the unit's data ends on a 16-byte boundary) */
// end story u4

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801059A0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801059BC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801059E4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105A64_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105B44_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105B60_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105C1C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105D98_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105E8C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105E9C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105EE4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105F2C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105F54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010603C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010606C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106090_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801060E4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106154_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106184_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801061A4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801061C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106220_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106284_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106340_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106400_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010643C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106CDC_mstory3);

void func_80106CE8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106CF0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DC4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DE0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107014_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107040_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107070_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107218_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107244_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107290_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010733C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801074D8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107674_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801077BC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107A18_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107D80_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108084_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010892C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010895C_mstory3);

void func_80108A94_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108A9C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108C34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108CA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108E28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A23C_mstory3);

void func_8010A7C8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A7D0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A8EC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AB34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AB54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010ACBC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AF28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B154_mstory3);

void func_8010B634_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B63C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B72C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BBB4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BC34_mstory3);

void func_8010BF40_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BF48_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C15C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C17C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C23C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C3F4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C490_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C4B0_mstory3);

void func_8010C654_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C65C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C7A0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C7C0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C810_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C870_mstory3);

void func_8010C9E0_mstory3(void) {
}
