#include "common.h"
#include "modesel.h"
#include "mallocblock.h"

/* Camera view a model's HmfData points to at 0xBC (read by the debug print func_80107954_modesel). */
typedef struct MsHmfCamView {
    /* 0x00 */ char unk0[8];
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec at;
    /* 0x20 */ Vec up;
} MsHmfCamView;

void func_801059A0_modesel(void) {
    ovlEventCall(D_8010F270_modesel, omovlevtno);
}

MS_FILE_END()

void func_801059D0_modesel(void) {
    Vec pos;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    pos = D_8010F3B0_modesel;
    target = D_8010F3BC_modesel;
    up = D_8010F3C8_modesel;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCamSetPositionOrientation(0, &pos, &target, &up);
    func_80030030_main(1.0f);
    if (func_800465D0_main() != 0) {
        func_8004A950_main();
    }
    pfInit();
    func_8005A6B0_main();
    HmfLightMaxSet(1);
    HmfLightColorSet(0, 0x80, 0x80, 0x80);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
    _ClearFlag(0xD);
}

void func_80105BD8_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

void func_80105BFC_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

void func_80105C20_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

MS_FILE_END()

void func_80105C50_modesel(void) {
    func_80105C7C_modesel();
    func_80106234_modesel();
    func_801074AC_modesel();
}

#ifdef NON_MATCHING
void func_80105C7C_modesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_8010FE10_modesel[i] = -1;
        D_8010F710_modesel[i].espId = -1;
        D_8010F710_modesel[i].x = D_8010F710_modesel[i].y = 0;
        D_8010F710_modesel[i].scaleX = D_8010F710_modesel[i].scaleY = 0.0f;
        D_8010F710_modesel[i].unk14 = 0.0f;
        D_8010F710_modesel[i].unk18 = 0xFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80105C7C_modesel);
#endif

s16 func_80105D10_modesel(s32 no) {
    return D_8010FE10_modesel[no];
}

s16 func_80105D24_modesel(s32 no) {
    return D_8010F710_modesel[no].espId;
}

void func_80105D40_modesel(s32 no, s32 dataNum) {
    D_8010FE10_modesel[no] = func_8000B838_main(dataNum);
}

void func_80105D78_modesel(s32 no) {
    if (D_8010FE10_modesel[no] != -1) {
        HuSprKill(D_8010FE10_modesel[no]);
    }
    D_8010FE10_modesel[no] = -1;
}

void func_80105DD0_modesel(s32 no, s16 animNo) {
    D_8010F710_modesel[no].espId = InitEspriteSlot(D_8010FE10_modesel[animNo], 0, 0);
    func_8010601C_modesel(no, 160, 120);
}

void func_80105E38_modesel(s32 no) {
    if (D_8010F710_modesel[no].espId != -1) {
        func_8000C184_main(D_8010F710_modesel[no].espId);
    }
    D_8010F710_modesel[no].espId = -1;
}

void func_80105EA8_modesel(s32 no, s32 dataNum) {
    func_80105D40_modesel(no, dataNum);
    func_80105DD0_modesel(no, no);
}

void func_80105EDC_modesel(s32 no, s32 dataNum) {
    func_80105EA8_modesel(no, dataNum);
    func_8000BC48_main(D_8010F710_modesel[no].espId, 0x4000);
}

void func_80105F20_modesel(s32 no) {
    func_80105E38_modesel(no);
    func_80105D78_modesel(no);
}

void func_80105F4C_modesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80105F20_modesel(i);
    }
}

void func_80105F84_modesel(s32 no) {
    func_8000BB54_main(D_8010F710_modesel[no].espId);
}

void func_80105FB4_modesel(s32 no) {
    func_8000BB94_main(D_8010F710_modesel[no].espId);
}

void func_80105FE4_modesel(s32 no) {
    func_80105F84_modesel(no);
}

void func_80106000_modesel(s32 no) {
    func_80105FB4_modesel(no);
}

void func_8010601C_modesel(s32 no, s32 x, s32 y) {
    D_8010F710_modesel[no].x = x;
    D_8010F710_modesel[no].y = y;
    func_8000BBD4_main(D_8010F710_modesel[no].espId, x, y);
}

void func_80106074_modesel(s32 no, s32 *x, s32 *y) {
    *x = D_8010F710_modesel[no].x;
    *y = D_8010F710_modesel[no].y;
}

void func_801060A4_modesel(s32 no, f32 x, f32 y) {
    D_8010F710_modesel[no].scaleX = x;
    D_8010F710_modesel[no].scaleY = y;
    func_8000BE5C_main(D_8010F710_modesel[no].espId, x, y);
}

void func_801060F4_modesel(s32 no, u16 alpha) {
    func_8000BBFC_main(D_8010F710_modesel[no].espId, alpha);
}

void func_8010612C_modesel(s32 no, u16 attr) {
    func_8000BC48_main(D_8010F710_modesel[no].espId, attr);
}

void func_80106160_modesel(s32 no, u16 attr) {
    func_8000BC88_main(D_8010F710_modesel[no].espId, attr);
}

void func_80106194_modesel(s32 no, u16 arg1) {
    func_8000BCC8_main(D_8010F710_modesel[no].espId, arg1);
}

void func_801061C8_modesel(s32 no, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_8010F710_modesel[no].espId, 1);
    func_8000BD94_main(D_8010F710_modesel[no].espId, arg1, arg2);
}

void func_80106234_modesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_8010FE90_modesel[i].model = -1;
        D_8010FE90_modesel[i].motion = -1;
    }
}

void func_80106280_modesel(s32 no, s32 arg1, s32 dataNum) {
    s16 model = func_8000B108_main(arg1, dataNum);

    D_8010FE90_modesel[no].model = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_8010631C_modesel(s32 no, s32 dataNum, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(dataNum);
    D_8010FE90_modesel[no].motion = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_801063A4_modesel(s32 no) {
    if (D_8010FE90_modesel[no].model != -1) {
        func_8001ACDC_main(D_8010FE90_modesel[no].model);
        D_8010FE90_modesel[no].model = -1;
    }
    if (D_8010FE90_modesel[no].motion != -1) {
        func_8002D4B8_main(D_8010FE90_modesel[no].motion);
        D_8010FE90_modesel[no].motion = -1;
    }
}

void func_80106454_modesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_801063A4_modesel(i);
    }
}

s16 func_8010648C_modesel(s32 no) {
    return D_8010FE90_modesel[no].model;
}

s16 func_801064B0_modesel(s32 no) {
    return D_8010FE90_modesel[no].motion;
}

void func_801064D4_modesel(s32 no, f32 x, f32 y, f32 z) {
    D_8010FE90_modesel[no].rot.x = x;
    D_8010FE90_modesel[no].rot.y = y;
    D_8010FE90_modesel[no].rot.z = z;
    Hu3DModelRotSet(D_8010FE90_modesel[no].model, x, y, z);
}

void func_8010653C_modesel(s32 no, f32 x, f32 y, f32 z) {
    D_8010FE90_modesel[no].pos[0] = x;
    D_8010FE90_modesel[no].pos[1] = y;
    D_8010FE90_modesel[no].pos[2] = z;
    Hu3DModelPosSet(D_8010FE90_modesel[no].model, x, y, z);
}

void func_801065B0_modesel(s32 no, f32 x, f32 y, f32 z) {
    D_8010FE90_modesel[no].scale.x = x;
    D_8010FE90_modesel[no].scale.y = y;
    D_8010FE90_modesel[no].scale.z = z;
    Hu3DModelScaleSet(D_8010FE90_modesel[no].model, x, y, z);
}

void func_80106618_modesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_8010FE90_modesel[no].pos[0];
    *y = D_8010FE90_modesel[no].pos[1];
    *z = D_8010FE90_modesel[no].pos[2];
}

void func_8010666C_modesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_8010FE90_modesel[no].rot.x;
    *y = D_8010FE90_modesel[no].rot.y;
    *z = D_8010FE90_modesel[no].rot.z;
}

void func_801066B4_modesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_8010FE90_modesel[no].scale.x;
    *y = D_8010FE90_modesel[no].scale.y;
    *z = D_8010FE90_modesel[no].scale.z;
}

void func_801066FC_modesel(s32 no) {
    func_8001C258_main(D_8010FE90_modesel[no].model, 4, 4);
}

void func_8010673C_modesel(s32 no) {
    func_8001C258_main(D_8010FE90_modesel[no].model, 4, 0);
}

void func_8010677C_modesel(s32 no, s16 flag) {
    func_8001C814_main(D_8010FE90_modesel[no].model, -1, flag);
}

void func_801067C0_modesel(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_8010FE90_modesel[no].model, D_8010FE90_modesel[motNo].motion, arg2, arg3, arg4);
}

void func_80106830_modesel(s32 no, s16 arg1) {
    func_8001C814_main(D_8010FE90_modesel[no].model, arg1, 0);
}

void func_80106874_modesel(s32 no, f32 speed) {
    func_8001C92C_main(D_8010FE90_modesel[no].model, speed);
}

void func_801068AC_modesel(s32 no, u32 time) {
    func_8001C6A8_main(D_8010FE90_modesel[no].model, time);
}

void func_80106910_modesel(s32 no) {
    while (HmfModelData[D_8010FE90_modesel[no].model].unk40 !=
           D_800CCF58_main[HmfModelData[D_8010FE90_modesel[no].model].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_801069B0_modesel(s32 no) {
    return HmfModelData[D_8010FE90_modesel[no].model].unk40 ==
           D_800CCF58_main[HmfModelData[D_8010FE90_modesel[no].model].unk02].unk02;
}

void func_80106A38_modesel(s32 no, s32 motNo, s16 flag) {
    s16 model = func_8010648C_modesel(no);
    s16 motion = func_801064B0_modesel(motNo);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, flag);
}

void func_80106AA8_modesel(s32 dataNum) {
    D_80110990_modesel = func_8000B838_main(dataNum);
    D_80110992_modesel = InitEspriteSlot(D_80110990_modesel, 0, 0);
    func_8000BC48_main(D_80110992_modesel, 0x4000);
    func_8000BBD4_main(D_80110992_modesel, 160, 120);
}

void func_80106B0C_modesel(void) {
    func_8000C184_main(D_80110992_modesel);
    HuSprKill(D_80110990_modesel);
}

u32 func_80106B38_modesel(u32 mes) {
    u8 buf[0x100];
    s32 size;
    void *copy;
    u32 ret;

    if (mes <= 0x80000000) {
        ret = mes;
    } else {
        size = func_800452A0_main(buf, (void *)mes);
        copy = HuMemAlloc(size);
        bcopy(buf, copy, size);
        ret = (u32)copy;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_80106BA0_modesel(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 id;
    u32 buf;

    switch (type) {
        case 1:
            buf = func_80106B38_modesel(mes);
            id = func_80106F38_modesel(buf, x, y, w, h, type);
            break;
        case 2:
            buf = func_80106B38_modesel(mes);
            id = func_801070A0_modesel(buf, x, y, w, h, type);
            break;
        case 3:
            buf = func_80106B38_modesel(mes);
            id = func_80107248_modesel(buf, x, y, type);
            break;
        case 4:
            buf = func_80106B38_modesel(mes);
            id = func_80107314_modesel(buf, x, y, type);
            break;
        case 5:
            buf = func_80106B38_modesel(mes);
            id = func_801073E0_modesel(buf, x, y, type);
            break;
        case 0:
        default:
            buf = func_80106B38_modesel(mes);
            id = func_80106DEC_modesel(buf, x, y, w, h, type);
            break;
    }
    if (buf > 0x80000000) {
        D_80110998_modesel[no].mes = buf;
    }
    D_80110998_modesel[no].id = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80106BA0_modesel);
#endif

s16 func_80106DEC_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0, 0x40, 0x40);
    func_8005C02C_main(win, 7);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80106F38_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 4);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 1);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801070A0_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 7, 0xFF, 0xFF, 0xFF);
    func_8005C060_main(win, 0, 0, 0, 0);
    func_8005C060_main(win, 3, 0, 0, 0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 6);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107248_modesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107314_modesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x14);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 0);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801073E0_modesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005FE54_main(win, 1);
    func_80060C14_main(win, 0);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

void func_801074AC_modesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80110998_modesel[i].id = -1;
        D_80110998_modesel[i].mes = 0;
    }
}

void func_801074F0_modesel(s32 no) {
    if (D_80110998_modesel[no].type == 3) {
        func_80060EA8_main(D_80110998_modesel[no].id, 1);
        func_800610E0_main(D_80110998_modesel[no].id);
    } else {
        func_8005FE90_main(D_80110998_modesel[no].id);
        func_8005F364_main(D_80110998_modesel[no].id);
        D_80110998_modesel[no].id = -1;
    }
    if (D_80110998_modesel[no].mes != 0) {
        func_80019C00_main((void *)D_80110998_modesel[no].mes);
        D_80110998_modesel[no].mes = 0;
    }
}

void func_801075D4_modesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80110998_modesel[i].id != -1) {
            func_801074F0_modesel(i);
        }
    }
}

void func_80107638_modesel(s32 no, f32 x, f32 y) {
    func_8005BB18_main(D_80110998_modesel[no].id, x, y);
}

void func_80107668_modesel(s32 no, f32 x, f32 y) {
    func_8005BA90_main(D_80110998_modesel[no].id, x, y);
}

void func_801076D0_modesel(s32 no) {
    func_8005FFA8_main(D_80110998_modesel[no].id);
}

void func_80107700_modesel(s32 no) {
    func_8005FE90_main(D_80110998_modesel[no].id);
}

void func_80107730_modesel(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80110998_modesel[arg0].id);
    if (D_80110998_modesel[arg0].mes != 0) {
        func_80019C00_main((void *)D_80110998_modesel[arg0].mes);
        D_80110998_modesel[arg0].mes = 0;
    }

    temp_v0 = func_80106B38_modesel(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80110998_modesel[arg0].mes = temp_v0;
    }
    func_8005B43C_main(D_80110998_modesel[arg0].id, temp_v0, -1, -1);
}

void func_801077FC_modesel(s32 no, s8 arg1, s32 arg2) {
    func_800601BC_main(D_80110998_modesel[no].id, arg2, arg1);
}

s32 func_80107838_modesel(s32 no, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_80110998_modesel[no].id, arg1, arg2);
}

s16 func_80107870_modesel(s32 no) {
    return D_80110998_modesel[no].id;
}

void func_8010788C_modesel(s32 no) {
    while (func_8005E0C0_main(D_80110998_modesel[no].id) != 0) {
        HuPrcVSleep();
    }
}

void func_801078E0_modesel(s32 btn) {
    do {
        HuPrcVSleep();
    } while (!(btn & D_800D5558_main[0]));
}

void func_8010791C_modesel(s32 no, s16 arg1) {
    func_8005BE30_main(D_80110998_modesel[no].id, arg1);
}

u16 func_80107954_modesel(s32 val) {
    char buf[0x100];
    MsHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, "\n%d\n", val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(MsHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
            sprintf(buf, "POS:%4.2f,%4.2f,%4.2f", view->pos.x, view->pos.y, view->pos.z);
            print8(16, 180, buf);
            sprintf(buf, "A T:%4.2f,%4.2f,%4.2f", view->at.x, view->at.y, view->at.z);
            print8(16, 190, buf);
            sprintf(buf, "U P:%4.2f,%4.2f,%4.2f", view->up.x, view->up.y, view->up.z);
            print8(16, 200, buf);
        } else {
            sprintf(buf, "%d", val);
            print8(16, 220, buf);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_80107B08_modesel(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 n;

    for (i = 0; i < 4; i++) {
        GwPlayer[i].pad = 0xFF;
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            GwPlayer[n].pad = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].pad == 0xFF) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    if (GwPlayer[k].pad == j) {
                        break;
                    }
                }
                if (k == 4) {
                    break;
                }
            }
            GwPlayer[i].pad = j;
        }
    }
}

void func_80107CB0_modesel(void) {
    func_80105C50_modesel();
    D_80110BDC_modesel = omAddPrcObj(func_80107CEC_modesel, 0x5000, 0x2000, 0);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F454_modesel);

extern const char D_8010F454_modesel[]; /* "" */

void func_80107CEC_modesel(void) {
    s32 i;
    s32 ok;
    s32 j;
    s16 model;
    omOvlHisData *his;

    D_80110BD8_modesel = 0;
    for (i = 0; i < 6; i++) {
        if (func_800E905C_minigame(i) >= 0) {
            D_80110BD8_modesel = i;
            break;
        }
    }
    if (_CheckFlag(0x21)) {
        D_80110BD8_modesel = 0;
    } else if (_CheckFlag(0x22)) {
        D_80110BD8_modesel = 1;
    } else if (_CheckFlag(0x23)) {
        D_80110BD8_modesel = 2;
    } else if (_CheckFlag(0x24)) {
        D_80110BD8_modesel = 3;
    } else if (_CheckFlag(0x25)) {
        D_80110BD8_modesel = 4;
    } else if (_CheckFlag(0x26)) {
        D_80110BD8_modesel = 5;
    }
    func_8001F38C_main(0, 0x40, 0x40);
    D_800CD280_main = 0;
    func_80109B74_modesel();
    func_8010E7B4_modesel();
    func_8010AF90_modesel();
    func_8010E50C_modesel();
    func_80108FC4_modesel();
    func_8010E984_modesel();
    func_8010EBF8_modesel();
    if (GwStory.unk0 == 12 && func_800465D0_main() == 0) {
        HuAudSeqPlay(0x29);
    } else {
        HuAudSeqPlay(4);
    }
    D_80110BE0_modesel = func_8010B9C4_modesel();
    if (omovlevtno != 1) {
        if (omovlevtno == 2) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
        }
        WipeCreateIn(0xB, 0x10);
        model = func_8010648C_modesel(0xB);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_80013320_main(model, 0);
        HuPrcSleep(0x10);
    } else {
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateIn(0xB, 0x10);
        func_8010EC40_modesel();
        HuPrcSleep(1);
        func_801068AC_modesel(0xD, 0);
        func_80106830_modesel(0xD, 1);
        HuPrcSleep(0xF);
        func_80106910_modesel(0xD);
        model = func_8010648C_modesel(0xB);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_80013320_main(model, 0);
        func_8010EBF8_modesel();
    }
    if (func_800465D0_main() == 1) {
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            func_801068AC_modesel(5, 0);
            func_80106830_modesel(5, 1);
            func_80106910_modesel(5);
        }
    } else if (_CheckFlag(0x28)) {
        func_801068AC_modesel(5, 0);
        func_80106830_modesel(5, 1);
        func_80106910_modesel(5);
    }
    if (GwStory.unk0 == 12 && func_800465D0_main() == 0) {
        omDelPrcObj(D_80110BE0_modesel);
        D_80110BE0_modesel = func_8010899C_modesel();
        D_80110BD0_modesel = func_8010AA48_modesel(0xA);
    } else {
        D_80110BD0_modesel = func_8010A9B8_modesel(0xA);
    }
    func_8010673C_modesel(0xA);
    HuPrcSleep(0x28);
    func_801067C0_modesel(0xA, 0x13, 8, 8, 2);
    HuAudFXPlay(0x159);
    if (func_800465D0_main() == 1) {
        if (func_800465E8_main() == 0) {
            func_80106BA0_modesel(0, 0x3100, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
            HuPrcSleep(0x1E);
            func_8010788C_modesel(0);
            i = -1;
            if (_CheckFlag(0x21)) {
                i = 0;
            } else if (_CheckFlag(0x22)) {
                i = 1;
            } else if (_CheckFlag(0x23)) {
                i = 2;
            } else if (_CheckFlag(0x24)) {
                i = 3;
            } else if (_CheckFlag(0x25)) {
                i = 4;
            } else if (_CheckFlag(0x26)) {
                i = 5;
            }
            _ClearFlag(0x21);
            _ClearFlag(0x22);
            _ClearFlag(0x23);
            _ClearFlag(0x24);
            _ClearFlag(0x25);
            _ClearFlag(0x26);
            if (i != -1) {
                func_80107730_modesel(0, 0x311A);
                func_801077FC_modesel(0, 0, i + 0x1C00);
                func_8010788C_modesel(0);
                ok = 1;
                for (j = 0; j < 12; j++) {
                    ok &= -(GwStory.unk10[i][j] >= 4);
                }
                ok &= -(GwStory.unk58[i] >= 4);
                if (ok) {
                    func_80107730_modesel(0, 0x313B);
                    func_8010788C_modesel(0);
                    func_801074F0_modesel(0);
                    func_80106BA0_modesel(0, (u32)D_8010F454_modesel, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
                }
            }
            func_800465F4_main(1);
            func_80107730_modesel(0, 0x3101);
        } else {
            func_80106BA0_modesel(0, 0x3101, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
        }
        func_8010788C_modesel(0);
        HuPrcVSleep();
    } else {
        i = -1;
        if (GwStory.unk0 == 12) {
            func_80106BA0_modesel(0, 0x3136, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
            func_8010788C_modesel(0);
            func_80107730_modesel(0, 0x3119);
        } else {
            if (_CheckFlag(0x21)) {
                i = 0;
            } else if (_CheckFlag(0x22)) {
                i = 1;
            } else if (_CheckFlag(0x23)) {
                i = 2;
            } else if (_CheckFlag(0x24)) {
                i = 3;
            } else if (_CheckFlag(0x25)) {
                i = 4;
            } else if (_CheckFlag(0x26)) {
                i = 5;
            }
            _ClearFlag(0x21);
            _ClearFlag(0x22);
            _ClearFlag(0x23);
            _ClearFlag(0x24);
            _ClearFlag(0x25);
            _ClearFlag(0x26);
            if (i != -1) {
                func_80106BA0_modesel(0, (u32)D_8010F454_modesel, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
                func_80107730_modesel(0, 0x311A);
                func_801077FC_modesel(0, 0, i + 0x1C00);
                func_8010788C_modesel(0);
                ok = 1;
                for (j = 0; j < 12; j++) {
                    ok &= -(GwStory.unk10[i][j] >= 4);
                }
                ok &= -(GwStory.unk58[i] >= 4);
                if (ok) {
                    func_80107730_modesel(0, 0x313B);
                    func_8010788C_modesel(0);
                }
                func_801074F0_modesel(0);
            }
            i = func_8010F204_modesel(GwStory.unk0);
            func_80106BA0_modesel(0, (u32)D_8010F454_modesel, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
            func_801077FC_modesel(0, 0, i + 0x3127);
            func_80107730_modesel(0, 0x3134);
        }
        func_8010788C_modesel(0);
    }
    func_801067C0_modesel(0xA, 0x14, 8, 8, 2);
    i = func_8010BA70_modesel();
    D_800CD280_main = 1;
    if (i == 0x10) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
    }
    WipeCreateOut(0xB, 0x14);
    HuAudSeqFadeOut(0x14);
    HuPrcSleep(0x14);
    func_801074F0_modesel(0);
    func_80109154_modesel();
    func_8010E790_modesel(D_80110BE0_modesel);
    func_8010EBC4_modesel();
    func_8010E5B8_modesel();
    func_8010B6B0_modesel();
    omDelPrcObj(D_80110BDC_modesel);
    func_8005F524_main();
    omOvlKill();
    switch (i) {
        case 0:
            omOvlCallEx(0x7C, D_80110BDA_modesel, 0x4000);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 1:
            omOvlCallEx(0x7B, 0, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 2:
            while (TRUE) {
                HuPrcVSleep();
            }
        case 4:
            GwSystem.playMode = (GwSystem.playMode & 4) | 2;
            omOvlCallEx(0x78, 1, 0x4090);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 5:
            func_80050974_main();
            _SetFlag(0);
            GwSystem.playMode = 2;
            omOvlCallEx(0x5A, 0, 0x4090);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 6:
            GwSystem.playMode = 2;
            omOvlCallEx(0x78, 8, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 7:
            GwSystem.playMode = 1;
            omOvlCallEx(0x78, 0, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 8:
            func_8005086C_main();
            GwSystem.playMode = 1;
            _SetFlag(0);
            omOvlCallEx(0x47, 0, 0x92);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 9:
            GwSystem.playMode = (GwSystem.playMode & 4) | 1;
            omOvlCallEx(0x78, 7, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 10:
            if (GwStory.unk0 == 12) {
                omOvlCallEx(0x41, 0, 0x94);
                omOvlHisChg(1, 0x77, 0, 0x91);
                func_800E989C_minigame();
                func_80107B08_modesel();
            } else if (GwSystem.playMode & 1) {
                omOvlCallEx(0x78, 2, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            } else {
                omOvlCallEx(0x78, 3, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            }
            break;
        case 11:
            func_80050ABC_main();
            _SetFlag(0);
            if (GwStory.unk0 == 12) {
                while (TRUE) {
                    HuPrcVSleep();
                }
            }
            if (GwSystem.playMode & 1) {
                omOvlCallEx(0x47, 0, 0x92);
            } else {
                omOvlCallEx(0x5A, 0, 0x4090);
            }
            omOvlHisChg(1, 0x77, 0, 0x91);
            his = &omovlhis[omovlhisidx];
            his->overlayID = 0x7D;
            his->event = 0;
            his->stat = 0x4090;
            omovlhisidx++;
            break;
        case 12:
            break;
        case 13:
            if (func_800465D0_main() == 1) {
                omOvlCallEx(0x78, 5, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            } else {
                omOvlCallEx(0x78, 6, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            }
            break;
        case 14:
            omOvlCallEx(0x41, 0, 0x94);
            omOvlHisChg(1, 0x77, 0, 0x91);
            func_800E989C_minigame();
            func_80107B08_modesel();
            break;
        case 15:
        case 16:
        default:
            omOvlHisChg(1, 0x7A, 0, 0x92);
            if ((u16)omOvlReturnEx(1) == 0) {
                osSyncPrintf("\n%d:omMapReturn ERROR!\n", 944);
            }
            break;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801088AC_modesel(void) {
    Hu3DCamSetPerspective(0, D_8010F2BC_modesel, D_8010F2C0_modesel, D_8010F2C4_modesel);
    while (TRUE) {
        func_80108A94_modesel(0);
        HuPrcVSleep();
    }
}

void func_801088F8_modesel(void) {
    while (TRUE) {
        func_80108F8C_modesel(&D_80110BE8_modesel[0], &D_80110BE8_modesel[1], &D_80110BE8_modesel[2]);
        HuPrcVSleep();
    }
}

void func_8010893C_modesel(Process *proc) {
    Vec eye;
    Vec at;
    Vec up;

    func_80108AE0_modesel(&eye, &at, &up);
    func_80108F8C_modesel(&eye, &at, &up);
    omDelPrcObj(proc);
}

Process *func_8010899C_modesel(void) {
    func_80108AE0_modesel(&D_80110BE8_modesel[0], &D_80110BE8_modesel[1], &D_80110BE8_modesel[2]);
    return omAddPrcObj(func_801088F8_modesel, 0x5000, 0x1800, 0);
}

void func_801089DC_modesel(Vec *eye, Vec *at, Vec *up) {
    HuVecCopy3F(eye, &D_80110BE8_modesel[0]);
    HuVecCopy3F(at, &D_80110BE8_modesel[1]);
    HuVecCopy3F(up, &D_80110BE8_modesel[2]);
}

void func_80108A34_modesel(Vec *eye, Vec *at, Vec *up) {
    HuVecCopy3F(&D_80110BE8_modesel[0], eye);
    HuVecCopy3F(&D_80110BE8_modesel[1], at);
    HuVecCopy3F(&D_80110BE8_modesel[2], up);
}

void func_80108A94_modesel(s32 arg0) {
    Vec eye;
    Vec at;
    Vec up;

    func_80108AE0_modesel(&eye, &at, &up);
    func_80108F8C_modesel(&eye, &at, &up);
}

/* The current camera's eye and target, and an up vector square to the view direction. */
s32 func_80108AE0_modesel(Vec *eye, Vec *at, Vec *up) {
    MsHmfCamView *view;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 rz;

    view = *(MsHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
    eye->x = view->pos.x;
    eye->y = view->pos.y;
    eye->z = view->pos.z;
    at->x = view->at.x;
    at->y = view->at.y;
    at->z = view->at.z;
    rz = -90.0f;
    dx = at->x - eye->x;
    dy = at->y - eye->y;
    dz = at->z - eye->z;
    len = dx * dx + dy * dy + dz * dz;
    len = HuSqrtf(len);
    dx /= len;
    dy /= len;
    dz /= len;
    ux = dy * dz - dz * (dy + 1.0f);
    uy = dz * dx - dx * dz;
    uz = dx * (dy + 1.0f) - dy * dx;
    up->x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
          + uy * (dy * dx * (1.0f - cosdf(rz)) - dz * sindf(rz))
          + uz * (dz * dx * (1.0f - cosdf(rz)) + dy * sindf(rz));
    up->y = ux * (dy * dx * (1.0f - cosdf(rz)) + dz * sindf(rz))
          + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
          + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
    up->z = ux * (dz * dx * (1.0f - cosdf(rz)) - dy * sindf(rz))
          + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
          + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80108F8C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80108FC4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80108FD0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109154_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109188_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109290_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109408_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109444_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_801094A8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_801094F0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_801096D4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109968_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109A58_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109B74_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109BC0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109C8C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109CEC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109DB8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109E90_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109FCC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A020_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A068_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A1C4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A2E8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A420_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A62C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A674_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A84C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A9B8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AA48_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AAC0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ABB4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AC3C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ACA8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AD74_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ADC8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AF18_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4C8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4D0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4D8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4E0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4E8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4F0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7E90", D_8010F4F8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010AF90_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B6B0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B75C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B790_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B804_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B824_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B940_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010B9C4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010BA70_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010C094_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010C874_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010CA30_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010CB34_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010CC38_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010CD00_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010D8DC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010DC6C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010DE88_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010DF70_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010DFB4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010DFD0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E000_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E138_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E22C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E280_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E3A4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E50C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E558_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E5B8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E5F0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E6D8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E790_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E7B4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010E984_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010EBC4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010EBF8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010EC40_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010EC74_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ECAC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ED00_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ED3C_modesel);

void func_8010F1F4_modesel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010F1FC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010F204_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010F214_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010F234_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010F258_modesel);
