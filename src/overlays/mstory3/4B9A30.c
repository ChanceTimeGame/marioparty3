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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111500_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801115D8_mstory3);

void func_8011175C_mstory3(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011598C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111764_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111B34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111C50_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159F8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111CB8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111DF8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111E2C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111E4C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111F3C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111F5C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111FA4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011204C_mstory3);

void func_801122BC_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801122C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011249C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801125C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801125F8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112650_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011268C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801126D8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011270C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011272C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112834_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112854_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011289C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112944_mstory3);

void func_80112B80_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112B88_mstory3);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112DA0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112EF0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112F7C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112FB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112FD0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801130A4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011315C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011322C_mstory3);

void func_801134D8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801134E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113668_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801136E8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113800_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113874_mstory3);

void func_80113960_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113968_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B24_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B30_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B3C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B48_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113AA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113B3C_mstory3);

void func_80113BA8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113BB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113E68_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114260_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801142C0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114474_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011475C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114920_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801149D0_mstory3);

void func_80114AF8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114B00_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114CD8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114EF8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114FA4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011517C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011522C_mstory3);
