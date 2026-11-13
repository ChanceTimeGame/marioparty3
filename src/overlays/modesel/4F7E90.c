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

/* Camera move (func_80109188_modesel): eases the camera target from `from` to `to` over `len` frames. */
typedef struct MsCamMove {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 t;
    /* 0x08 */ s32 len;
    /* 0x0C */ s32 no;
    /* 0x10 */ Vec from;
    /* 0x1C */ Vec to;
} MsCamMove; /* size = 0x28 */

/* Camera shake (func_80109444_modesel). */
typedef struct MsCamShake {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 t;
    /* 0x08 */ s32 sign;
    /* 0x0C */ Vec eye;
    /* 0x18 */ Vec at;
    /* 0x24 */ Vec up;
} MsCamShake; /* size = 0x30 */

extern MsCamMove D_80110C10_modesel;
extern MsCamShake D_80110C38_modesel;

void func_80108F8C_modesel(Vec *eye, Vec *at, Vec *up) {
    Hu3DCamSetPositionOrientation(0, eye, at, up);
    Hu3DCamUpdateMtx(0);
}

void func_80108FC4_modesel(void) {
    D_80110C10_modesel.obj = NULL;
}

void func_80108FD0_modesel(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec from;
    Vec to;
    Vec cur;
    f32 t;
    f32 s;

    HuVecCopy3F(&from, &D_80110C10_modesel.from);
    HuVecCopy3F(&to, &D_80110C10_modesel.to);
    t = (f32)D_80110C10_modesel.t / (f32)D_80110C10_modesel.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        s = 1.0f;
    } else {
        s = sindf(t * 90.0f);
    }
    HuVecCopyXYZ(&cur, (to.x - from.x) * s + from.x, (to.y - from.y) * s + from.y, (to.z - from.z) * s + from.z);
    func_801089DC_modesel(&eye, &at, &up);
    if (D_80110C10_modesel.t > D_80110C10_modesel.len) {
        omDelObj(obj);
        func_80108A34_modesel(&eye, &to, &up);
        D_80110C10_modesel.obj = NULL;
        return;
    }
    D_80110C10_modesel.t++;
    func_80108A34_modesel(&eye, &cur, &up);
}

void func_80109154_modesel(void) {
    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    D_80110C10_modesel.obj = NULL;
}

/* Moves the camera target to point `no` (x only) over `len` frames. */
omObjData *func_80109188_modesel(s32 no, s32 len) {
    Vec eye;
    Vec at;
    Vec up;
    Vec pos;
    omObjData *obj;

    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    obj = omAddObj(6, 0, 0, -1, func_80108FD0_modesel);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_80110C10_modesel.obj = obj;
    D_80110C10_modesel.t = 0;
    D_80110C10_modesel.len = len;
    D_80110C10_modesel.no = no;
    func_801089DC_modesel(&eye, &at, &up);
    HuVecCopyXYZ(&D_80110C10_modesel.from, at.x, at.y, at.z);
    if (no < 0) {
        pos.x = 0.0f;
    } else {
        func_8010E138_modesel(no, &pos.x, &pos.y, &pos.z);
    }
    pos.y = at.y;
    pos.z = at.z;
    HuVecCopyXYZ(&D_80110C10_modesel.to, pos.x, pos.y, pos.z);
    return obj;
}

void func_80109290_modesel(omObjData *obj) {
    Vec eye;
    Vec at;
    f32 d;
    f32 amp;
    s32 t;

    t = D_80110C38_modesel.t;
    HuVecCopy3F(&eye, &D_80110C38_modesel.eye);
    HuVecCopy3F(&at, &D_80110C38_modesel.at);
    if (t > 32) {
        omDelObj(obj);
        D_80110C38_modesel.obj = NULL;
        t = 0;
    } else {
        D_80110C38_modesel.sign = ~D_80110C38_modesel.sign;
        if (D_80110C38_modesel.sign) {
            d = rand8() & 0xFF;
        } else {
            d = -(f32)(rand8() & 0xFF);
        }
        d = d * (1.0f / 255.0f) * ((1.0f - t * (1.0f / 32.0f)) * 0.8f + 0.2f);
        amp = d * 40.0f;
        eye.y += amp;
        at.y += amp;
    }
    func_80108A34_modesel(&eye, &at, &D_80110C38_modesel.up);
    D_80110C38_modesel.t = t + 1;
}

void func_80109408_modesel(void) {
    if (D_80110C38_modesel.obj != NULL) {
        omDelObj(D_80110C38_modesel.obj);
        D_80110C38_modesel.obj = NULL;
    }
}

void func_80109444_modesel(void) {
    D_80110C38_modesel.obj = omAddObj(6, 0, 0, -1, func_80109290_modesel);
    D_80110C38_modesel.t = 0;
    func_801089DC_modesel(&D_80110C38_modesel.eye, &D_80110C38_modesel.at, &D_80110C38_modesel.up);
    D_80110C38_modesel.sign = 1;
}

f32 func_801094A8_modesel(f32 x0, f32 y0, f32 x1, f32 y1) {
    return -(atan2df(y1 - y0, x1 - x0) - 90.0f);
}









#ifdef NON_MATCHING
/* Turns the horizontal direction a towards b by the fraction t (angles about y, shortest way round);
   writes the unit direction to out. */
void func_801094F0_modesel(Vec *a, Vec *b, f32 t, Vec *out) {
    f32 end;
    f32 ang;
    f32 angA;
    f32 angB;

    angA = func_801094A8_modesel(0.0f, 0.0f, a->x, a->z);
    if (angA < 0.0f) {
        angA += 360.0f;
    }
    angB = func_801094A8_modesel(0.0f, 0.0f, b->x, b->z);
    if (angB < 0.0f) {
        angB += 360.0f;
    }
    if (-a->z * b->x + a->x * b->z > 0.0f) {
        end = (angB - angA < 0.0f) ? angB : angB - 360.0f;
        ang = (end - angA) * t + angA;
        if (ang < 0.0f) {
            ang += 360.0f;
        }
    } else {
        end = (angB - angA > 0.0f) ? angB : angB + 360.0f;
        ang = (end - angA) * t + angA;
        if (ang > 360.0f) {
            ang -= 360.0f;
        }
    }
    out->x = sindf(ang);
    out->y = 0.0f;
    out->z = cosdf(ang);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_801094F0_modesel);
#endif

/* Camera target move along an arc around the eye (func_80109968_modesel). Retail adds the full y
   difference (to.y - from.y) without the time factor. */
void func_801096D4_modesel(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec dir;
    Vec from;
    Vec to;
    Vec d0;
    Vec d1;
    f32 t0;
    f32 t;
    f32 s;
    f32 len0;

    t0 = (f32)D_80110C10_modesel.t / (f32)D_80110C10_modesel.len;
    if (t0 < 0.0f) {
        t0 = 0.0f;
    }
    if (t0 > 1.0f) {
        t = 1.0f;
    } else {
        t = t0;
    }
    func_801089DC_modesel(&eye, &at, &up);
    HuVecCopy3F(&from, &D_80110C10_modesel.from);
    HuVecCopy3F(&to, &D_80110C10_modesel.to);
    HuVecCopyXYZ(&at, (to.x - from.x) * t + from.x, (to.y - from.y) * t + from.y, (to.z - from.z) * t + from.z);
    HuVecCopyXYZ(&d0, from.x - eye.x, 0.0f, from.z - eye.z);
    HuVecCopyXYZ(&d1, to.x - eye.x, 0.0f, to.z - eye.z);
    s = sindf(t * 90.0f);
    func_801094F0_modesel(&d0, &d1, s, &dir);
    len0 = HuVecGetLength3F(&d0);
    t0 = (HuVecGetLength3F(&d1) - len0) * s + len0;
    HuVecCopyXYZ(&at, t0 * dir.x + eye.x, (to.y - from.y) + from.y, t0 * dir.z + eye.z);
    if (D_80110C10_modesel.t > D_80110C10_modesel.len) {
        omDelObj(obj);
        func_80108A34_modesel(&eye, &D_80110C10_modesel.to, &up);
        D_80110C10_modesel.obj = NULL;
        return;
    }
    D_80110C10_modesel.t++;
    func_80108A34_modesel(&eye, &at, &up);
}

omObjData *func_80109968_modesel(s32 no, s32 len) {
    Vec eye;
    Vec at;
    Vec up;
    omObjData *obj;

    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    obj = omAddObj(6, 0, 0, -1, func_801096D4_modesel);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_80110C10_modesel.obj = obj;
    D_80110C10_modesel.t = 0;
    D_80110C10_modesel.len = len;
    D_80110C10_modesel.no = no;
    func_801089DC_modesel(&eye, &at, &up);
    HuVecCopy3F(&D_80110C10_modesel.from, &at);
    if (no < 0) {
        at.x = 0.0f;
    } else {
        func_8010E138_modesel(no, &at.x, &at.y, &at.z);
    }
    HuVecCopyXYZ(&D_80110C10_modesel.to, at.x, at.y, at.z);
    return obj;
}

#ifdef NON_MATCHING
/* Stick direction of controller `pad` as a button mask (0x100 right, 0x200 left, 0x800 up, 0x400 down
   and their diagonals), reported once each time the stick leaves the centre. */
s32 func_80109A58_modesel(s32 pad) {
    s32 ax;
    s32 ay;
    s32 x;
    s32 y;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];
    if (D_8010F2C8_modesel != 0) {
        if ((x == 0) & (y == 0)) {
            D_8010F2C8_modesel = 0;
            return 0;
        }
        return 0;
    }
    if ((x != 0) | (y != 0)) {
        ax = (x < 0) ? -x : x;
        ay = (y < 0) ? -y : y;
        if (ay < ax) {
            if (ay * 2 < ax) {
                D_8010F2C8_modesel = (x < 0) ? 0x200 : 0x100;
            } else if (y > 0) {
                D_8010F2C8_modesel = (x < 0) ? 0xA00 : 0x900;
            } else {
                D_8010F2C8_modesel = (x < 0) ? 0x600 : 0x500;
            }
        } else if (ax * 2 < ay) {
            D_8010F2C8_modesel = (y < 0) ? 0x400 : 0x800;
        } else if (y > 0) {
            D_8010F2C8_modesel = (x < 0) ? 0xA00 : 0x900;
        } else {
            D_8010F2C8_modesel = (x < 0) ? 0x600 : 0x500;
        }
    }
    return D_8010F2C8_modesel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_80109A58_modesel);
#endif

/* Bobbing objects for models 7..9: D_80110C68_modesel[no - 7]. */
typedef struct MsBob {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ omObjData *obj;
    /* 0x0C */ Vec pos; /* height when the bob stopped (func_80109E90_modesel) */
} MsBob; /* size = 0x18 */

extern MsBob D_80110C68_modesel[3];

void func_80109B74_modesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80110C68_modesel[i].obj = NULL;
        D_80110C68_modesel[i].unk4 = 0;
        D_80110C68_modesel[i].unk0 = 0;
    }
}

void func_80109BC0_modesel(omObjData *obj) {
    s32 no;
    s32 t;
    f32 s;
    f32 ft;

    no = obj->work[0];
    t = obj->work[1];
    ft = t;
    ft *= 1.4117647f;
    s = sindf(ft);
    func_8010648C_modesel(no);
    func_8010B75C_modesel(no, 0.0f, s * 8.0f + 8.0f + 8.0f, 0.0f, s * 16.0f + 20.0f);
    obj->work[1] = t + 4;
}

void func_80109C8C_modesel(s32 no) {
    s32 i = no - 7;

    if (D_80110C68_modesel[i].obj != NULL) {
        omDelObj(D_80110C68_modesel[i].obj);
    }
    D_80110C68_modesel[i].obj = NULL;
}

omObjData *func_80109CEC_modesel(u32 no) {
    omObjData *obj;
    s32 i = no - 7;

    if (D_80110C68_modesel[i].obj != NULL) {
        func_80109C8C_modesel(no);
    }
    obj = omAddObj(6, 0, 0, -1, func_80109BC0_modesel);
    D_80110C68_modesel[i].obj = obj;
    obj->work[0] = no;
    obj->work[1] = rand8() & 0xFF;
    D_80110C68_modesel[i].unk0 = 0;
    D_80110C68_modesel[i].unk4 = 0;
    return obj;
}

void func_80109DB8_modesel(omObjData *obj) {
    s32 no;
    s32 i;
    s32 t;
    f32 s0;
    f32 s;

    no = obj->work[0];
    i = no - 7;
    t = obj->work[1];
    s0 = t;
    s0 *= 0.1f;
    s0 = 1.0f - s0;
    if (s0 < 0.0f) {
        s = 0.0f;
    } else {
        s = s0;
    }
    func_8010B75C_modesel(no, 0.0f, (D_80110C68_modesel[i].pos.y - 10.0f) * s + 10.0f, 0.0f, 0.0f);
    if (t < 10) {
        t++;
    }
    obj->work[1] = t;
}

/* Stops the bob of model `no` and settles it. Retail stores `no` into the old (just deleted)
   object's work[0] and returns that object, or writes through NULL when there was none. */
void *func_80109E90_modesel(s32 no) {
    s32 i = no - 7;
    omObjData *obj;
    f32 ft;

    obj = D_80110C68_modesel[i].obj;
    if (obj != NULL) {
        ft = (s32)obj->work[1];
        ft *= 1.4117647f;
        ft = sindf(ft);
        HuVecCopyXYZ(&D_80110C68_modesel[i].pos, 0.0f, ft * 8.0f + 8.0f + 8.0f, 0.0f);
        omDelObj(D_80110C68_modesel[i].obj);
    } else {
        HuVecCopyXYZ(&D_80110C68_modesel[i].pos, 0.0f, 0.0f, 0.0f);
    }
    D_80110C68_modesel[i].obj = omAddObj(6, 0, 0, -1, func_80109DB8_modesel);
    D_80110C68_modesel[i].unk4 = 0;
    obj->work[0] = no;
    return obj;
}

void func_80109FCC_modesel(omObjData *obj) {
    s32 no = obj->work[0];
    s32 t = obj->work[1];

    if (t == 200) {
        func_8010677C_modesel(no, 0);
    } else if (t == 0) {
        func_8010677C_modesel(no, 1);
    }
    t += 4;
    obj->work[1] = t;
}

void func_8010A020_modesel(u32 no) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_80109FCC_modesel);

    obj->work[0] = no;
    obj->work[1] = 0;
}












/* Bob part of model `no` sinks out of view, then the model is hidden. */
void func_8010A068_modesel(omObjData *obj) {
    Vec pos;
    s32 no;
    s32 t;
    f32 y;
    f32 dy;

    no = obj->work[0];
    t = obj->work[1];
    dy = t * (1.0f / 255.0f);
    pos.x = D_8010F2CC_modesel[no - 7].x;
    pos.y = D_8010F2CC_modesel[no - 7].y;
    pos.z = D_8010F2CC_modesel[no - 7].z;
    pos.y -= dy * 400.0f;
    func_8010653C_modesel(no, 0.0f, 0.0f, 0.0f);
    y = pos.y + 20.0f - 12.0f;
    if (y < 0.0f) {
        y = 0.0f;
    }
    func_8010B790_modesel(no, pos.x, pos.y, pos.z, y);
    func_8010B804_modesel(no, 0.0f);
    func_8010B824_modesel(no);
    t += 20;
    if (t != 100) {
        if (t >= 256) {
            omDelObj(obj);
            func_801066FC_modesel(no);
        }
    }
    obj->work[1] = t;
}

void func_8010A1C4_modesel(omObjData *obj) {
    Vec pos;
    s32 no;
    s32 t;
    f32 y;

    no = obj->work[0];
    t = obj->work[1];
    pos.x = D_8010F2CC_modesel[no - 7].x;
    pos.y = D_8010F2CC_modesel[no - 7].y;
    pos.z = D_8010F2CC_modesel[no - 7].z;
    func_8010653C_modesel(no, 0.0f, 0.0f, 0.0f);
    y = pos.y + 20.0f - 12.0f;
    if (y < 0.0f) {
        y = 0.0f;
    }
    func_8010B790_modesel(no, pos.x, pos.y, pos.z, y);
    func_8010B804_modesel(no, 0.0f);
    func_8010B824_modesel(no);
    t++;
    if (t > 20) {
        HuAudFXPlay(0x2E2);
        obj->func = func_8010A068_modesel;
        obj->work[1] = 0;
    }
    obj->work[1] = t;
}

void func_8010A2E8_modesel(omObjData *obj) {
    Vec pos;
    s32 no;
    s32 t;

    no = obj->work[0];
    t = obj->work[1];
    pos.x = D_8010F2CC_modesel[no - 7].x;
    pos.y = D_8010F2CC_modesel[no - 7].y;
    pos.z = D_8010F2CC_modesel[no - 7].z;
    func_8010653C_modesel(no, 0.0f, 0.0f, 0.0f);
    func_8010B790_modesel(no, pos.x, pos.y, pos.z, pos.y + 20.0f - 12.0f);
    func_8010B940_modesel(no, 35.5f);
    func_8010B824_modesel(no);
    t += 20;
    if (t >= 256) {
        t = 0;
        D_8010F2CC_modesel[no - 7].x = pos.x;
        D_8010F2CC_modesel[no - 7].y = pos.y;
        D_8010F2CC_modesel[no - 7].z = pos.z;
        obj->func = func_8010A1C4_modesel;
    }
    obj->work[1] = t;
}

#ifdef NON_MATCHING
/* Bob part of model `no` jumps to (0, 200, 300) on an arc. */
void func_8010A420_modesel(omObjData *obj) {
    Vec pos;
    Vec dst;
    Vec cur;
    s32 no;
    s32 t;
    s32 i;
    f32 f;
    f32 f1;
    f32 k;

    no = obj->work[0];
    t = obj->work[1];
    f = t * (1.0f / 255.0f);
    if (f < 1.0) {
        f1 = f;
    } else {
        f1 = 1.0f;
    }
    k = f1 * -5.0f * (f1 - 1.2f);
    i = no - 7;
    pos.x = D_8010F2CC_modesel[i].x;
    pos.y = D_8010F2CC_modesel[i].y;
    pos.z = D_8010F2CC_modesel[i].z;
    HuVecCopyXYZ(&dst, 0.0f, 200.0f, 300.0f);
    cur.x = (dst.x - pos.x) * f + pos.x;
    cur.y = (dst.y - pos.y) * k + pos.y;
    cur.z = (dst.z - pos.z) * f + pos.z;
    func_8010653C_modesel(no, 0.0f, 0.0f, 0.0f);
    func_8010B790_modesel(no, cur.x, cur.y, cur.z, cur.y + 20.0f - 12.0f);
    func_8010B940_modesel(no, 35.5f);
    func_8010B824_modesel(no);
    t += 12;
    if (t < 256) {
        obj->work[1] = t;
        return;
    }
    obj->work[1] = 0;
    D_8010F2CC_modesel[i].x = cur.x;
    D_8010F2CC_modesel[i].y = cur.y;
    D_8010F2CC_modesel[i].z = cur.z;
    obj->func = func_8010A2E8_modesel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A420_modesel);
#endif

void func_8010A62C_modesel(u32 no) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A420_modesel);

    obj->work[0] = no;
    obj->work[1] = 0;
}

extern Vec D_80110CB0_modesel; /* model position (func_80106618_modesel) */
extern Vec D_80110CBC_modesel; /* move target */
extern f32 D_80110CD4_modesel; /* model 10's y rotation */

typedef struct MsVecPair {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
} MsVecPair;

extern MsVecPair D_80110CD8_modesel; /* model 10's jump; splat also names D_80110CE4_modesel */

#ifdef NON_MATCHING
/* Model `no` bobs at its position while model 10 turns towards the camera, 2 degrees a frame. */
void func_8010A674_modesel(omObjData *obj) {
    Vec pos;
    Vec base;
    Vec eye;
    Vec at;
    Vec up;
    Vec m;
    s32 no;
    s32 t;
    f32 ft;
    f32 d;
    f32 ang;
    f32 a1;
    f32 a2;
    f32 a3;

    no = obj->work[0];
    t = obj->work[1];
    ft = sindf(t * 1.4117647f);
    HuVecCopy3F(&base, &D_80110CB0_modesel);
    HuVecCopyXYZ(&pos, base.x, ft * 5.0f * 5.0f + base.y, base.z);
    func_8010653C_modesel(no, pos.x, pos.y, pos.z);
    func_801089DC_modesel(&eye, &at, &up);
    func_80106618_modesel(10, &m.x, &m.y, &m.z);
    ang = D_80110CD4_modesel;
    d = func_8010EC74_modesel(eye.x - m.x, eye.z - m.z) - ang;
    if (d < -2.0f) {
        ang -= 2.0f;
    }
    a1 = ang;
    if (ang < 0.0f) {
        a1 = ang + 360.0f;
    }
    a2 = a1;
    if (d > 2.0f) {
        a2 += 2.0f;
    }
    a3 = a2;
    if (a2 > 360.0f) {
        a3 = a2 - 360.0f;
    }
    D_80110CD4_modesel = a3;
    func_801064D4_modesel(10, 0.0f, a3, 0.0f);
    obj->work[1] = t + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A674_modesel);
#endif

#ifdef NON_MATCHING
void func_8010A84C_modesel(omObjData *obj) {
    Vec cur;
    Vec from;
    Vec to;
    s32 no;
    s32 t;
    f32 f;
    f32 e;
    f32 k;

    no = obj->work[0];
    t = obj->work[1];
    f = t * 0.05f;
    if (f > 1.0f) {
        e = 1.0f;
    } else {
        e = f * f;
    }
    k = e * -3.0f * (e - 1.3333334f);
    HuVecCopy3F(&from, &D_80110CB0_modesel);
    HuVecCopy3F(&to, &D_80110CBC_modesel);
    HuVecCopyXYZ(&cur, (to.x - from.x) * e + from.x, (to.y - from.y) * k + from.y,
                 (to.z - from.z) * e + from.z);
    func_8010653C_modesel(no, cur.x, cur.y, cur.z);
    if (t > 20) {
        obj->func = func_8010A674_modesel;
        HuVecCopy3F(&D_80110CB0_modesel, &cur);
        t = 0;
    } else {
        t++;
    }
    obj->work[1] = t;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010A84C_modesel);
#endif

omObjData *func_8010A9B8_modesel(u32 no) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A84C_modesel);

    obj->work[0] = no;
    obj->work[1] = 0;
    func_80106618_modesel(no, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    HuVecCopyXYZ(&D_80110CBC_modesel, 0.0f, 25.0f, 300.0f);
    D_80110CD4_modesel = 0.0f;
    return obj;
}

omObjData *func_8010AA48_modesel(u32 no) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A674_modesel);

    obj->work[0] = no;
    obj->work[1] = 0;
    func_80106618_modesel(no, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    D_80110CD4_modesel = 0.0f;
    return obj;
}

void func_8010AAC0_modesel(omObjData *obj) {
    Vec from;
    Vec to;
    Vec cur;
    s32 no;
    s32 t;
    f32 f;

    no = obj->work[0];
    t = obj->work[1];
    f = t * 0.05f;
    HuVecCopy3F(&from, &D_80110CB0_modesel);
    HuVecCopy3F(&to, &D_80110CBC_modesel);
    HuVecCopyXYZ(&cur, (to.x - from.x) * f + from.x, (to.y - from.y) * f + from.y, (to.z - from.z) * f + from.z);
    func_8010653C_modesel(no, cur.x, cur.y, cur.z);
    if (t < 21) {
        t++;
    }
    obj->work[1] = t;
}

omObjData *func_8010ABB4_modesel(u32 no) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010AAC0_modesel);

    obj->work[0] = no;
    obj->work[1] = 0;
    func_80106618_modesel(no, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    HuVecCopyXYZ(&D_80110CBC_modesel, 0.0f, -400.0f, 300.0f);
    return obj;
}

/* Turns model 10 to face the camera. */
void func_8010AC3C_modesel(void) {
    Vec m;
    Vec eye;
    Vec at;
    Vec up;

    func_80106618_modesel(10, &m.x, &m.y, &m.z);
    func_801089DC_modesel(&eye, &at, &up);
    func_801064D4_modesel(10, 0.0f, func_8010EC74_modesel(eye.x - m.x, eye.z - m.z), 0.0f);
}

#ifdef NON_MATCHING
void func_8010ACA8_modesel(omObjData *obj) {
    Vec pos;
    s32 no;
    s32 t;
    f32 f;

    no = 10;
    t = obj->work[0];
    f = t * (1.0f / 255.0f);
    pos.x = D_80110CD8_modesel.to.x;
    pos.y = D_80110CD8_modesel.to.y - f * 400.0f;
    pos.z = D_80110CD8_modesel.to.z;
    func_8010653C_modesel(no, pos.x, pos.y, pos.z);
    t += 20;
    func_8010AC3C_modesel();
    if (t >= 256) {
        omDelObj(obj);
        func_801066FC_modesel(no);
    }
    obj->work[0] = t;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7E90", func_8010ACA8_modesel);
#endif

void func_8010AD74_modesel(omObjData *obj) {
    s32 t;

    t = obj->work[0];
    t++;
    func_8010AC3C_modesel();
    if (t > 30) {
        obj->func = func_8010ACA8_modesel;
        t = 0;
    }
    obj->work[0] = t;
}

void func_8010ADC8_modesel(omObjData *obj) {
    Vec pos;
    s32 no;
    s32 t;
    f32 f;
    f32 f1;

    no = 10;
    t = obj->work[0];
    f = t * (1.0f / 255.0f);
    if (f < 1.0) {
        f1 = f;
    } else {
        f1 = 1.0f;
    }
    pos.x = (D_80110CD8_modesel.to.x - D_80110CD8_modesel.from.x) * f + D_80110CD8_modesel.from.x;
    pos.y = (D_80110CD8_modesel.to.y - D_80110CD8_modesel.from.y) * f1 + (1.0f - (f1 - 0.5f) * 4.0f * (f1 - 0.5f)) * 80.0f + D_80110CD8_modesel.from.y;
    pos.z = (D_80110CD8_modesel.to.z - D_80110CD8_modesel.from.z) * f + D_80110CD8_modesel.from.z;
    func_8010653C_modesel(no, pos.x, pos.y, pos.z);
    t += 12;
    func_8010AC3C_modesel();
    if (t >= 256) {
        obj->func = func_8010AD74_modesel;
        t = 0;
    }
    obj->work[0] = t;
}

omObjData *func_8010AF18_modesel(void) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010ADC8_modesel);

    func_80106618_modesel(10, &D_80110CD8_modesel.from.x, &D_80110CD8_modesel.from.y, &D_80110CD8_modesel.from.z);
    HuVecCopyXYZ(&D_80110CD8_modesel.to, 0.0f, 200.0f, 300.0f);
    obj->work[0] = 0;
    return obj;
}
















/* Bob parts of models 7..9: two model parts (func_8001D33C_main) placed at pos and turned by rot. */
typedef struct MsHmfPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec unk1C; /* scale (func_8010BA70_modesel resets both to 1) */
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec unk40;
    /* 0x4C */ char unk4C[0xC];
    /* 0x58 */ HuMtx4F mtx;
} MsHmfPart; /* size = 0x98 */

typedef struct MsBobPart {
    /* 0x00 */ MsHmfPart *part[2];
    /* 0x08 */ Vec pos;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 rot;
} MsBobPart; /* size = 0x1C */

extern MsBobPart D_80110B18_modesel[3];
void func_80088800_main(HuMtx4F mf, f32 x, f32 y, f32 z);
void *func_8001D33C_main(s16 model, char *name);

/* Builds the mode-select scene: the board models, the cannon (model 5, part "taiho"), the three star
   models 7..9 with their bob parts, model 10 and the camera models 11..13. Characters not yet
   unlocked (func_800E905C_minigame bit 15 set) are moved out of view on model 2. */
void func_8010AF90_modesel(void) {
    s16 model;
    s32 i;

    func_80106280_modesel(0, 0xD0000, 0x2002A9);
    func_8010653C_modesel(0, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(0, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(0, 0);
    func_8010677C_modesel(0, 1);
    func_80106280_modesel(1, 0xD0001, 0x229);
    func_8010653C_modesel(1, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(1, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(1, 0);
    func_8010677C_modesel(1, 1);
    func_80106280_modesel(2, 0xD0002, 0x6A9);
    func_8010653C_modesel(2, 0.0f, 0.0f, -585.0f);
    func_801065B0_modesel(2, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(2, 0);
    func_8010677C_modesel(2, 1);
    {
        char *names[6] = { "mario", "luigi", "peach", "yoshi", "wario", "donkey" };

        model = func_8010648C_modesel(2);
        for (i = 0; i < 6; i++) {
            if (func_800E905C_minigame(i) < 0) { /* bit 15: not unlocked */
                func_80088800_main(((MsHmfPart *)func_8001D33C_main(model, names[i]))->mtx, 0.0f, -4000.0f, 0.0f);
            }
        }
    }
    {
        Vec pos;

        HuVecCopyXYZ(&pos, 0.0f, 0.0f, -200.0f);
        pos.z = pos.z - 8.0f - 2.5f;
        func_80106280_modesel(3, 0xD0003, 0x7A9);
        func_8010653C_modesel(3, pos.x, pos.y, pos.z);
    }
    func_801065B0_modesel(3, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(3, 0);
    func_8010677C_modesel(3, 1);
    func_80106280_modesel(4, 0xD0004, 0xAA9);
    func_8010653C_modesel(4, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(4, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(4, 0);
    func_8010677C_modesel(4, 1);
    func_80106280_modesel(5, 0xD0005, 0x6A9);
    func_8010653C_modesel(5, 325.0f, 9.5f, 45.0f);
    func_801065B0_modesel(5, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(5, 0);
    func_8010677C_modesel(5, 1);
    D_80110BD4_modesel = func_8001D33C_main(func_8010648C_modesel(5), "taiho");
    func_8010631C_modesel(17, 0xD000B, -1);
    func_80106280_modesel(18, 0xD000C, 0xAA9);
    func_8010653C_modesel(18, 275.0f, 97.0f, 122.5f);
    func_801065B0_modesel(18, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(18, 0);
    func_8010677C_modesel(18, 2);
    func_801066FC_modesel(18);
    func_80106280_modesel(7, 0xD0007, 0xAA9);
    func_8010653C_modesel(7, 250.0f, 25.0f, 355.0f);
    func_801065B0_modesel(7, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(7, 1);
    func_80109CEC_modesel(7);
    model = func_8010648C_modesel(7);
    D_80110B18_modesel[0].part[0] = func_8001D33C_main(model, "star_red");
    D_80110B18_modesel[0].part[1] = func_8001D33C_main(model, "red_kage");
    func_8010B804_modesel(7, 0.0f);
    func_8010B75C_modesel(7, 0.0f, 16.0f, 0.0f, 20.0f);
    func_80106280_modesel(8, 0xD0008, 0xAA9);
    func_8010653C_modesel(8, -250.0f, 25.0f, 355.0f);
    func_801065B0_modesel(8, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(8, 1);
    func_80109CEC_modesel(8);
    model = func_8010648C_modesel(8);
    D_80110B18_modesel[1].part[0] = func_8001D33C_main(model, "star_blue");
    D_80110B18_modesel[1].part[1] = func_8001D33C_main(model, "blue_kage");
    func_8010B804_modesel(8, 0.0f);
    func_8010B75C_modesel(8, 0.0f, 0.0f, 16.0f, 20.0f);
    func_80106280_modesel(9, 0xD0009, 0x6A9);
    func_8010653C_modesel(9, 0.0f, 25.0f, 70.0f);
    func_801065B0_modesel(9, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(9, 1);
    func_80109CEC_modesel(9);
    model = func_8010648C_modesel(9);
    D_80110B18_modesel[2].part[0] = func_8001D33C_main(model, "star_yellow");
    D_80110B18_modesel[2].part[1] = func_8001D33C_main(model, "yellow_kage");
    func_8010B75C_modesel(9, 0.0f, 0.0f, 16.0f, 20.0f);
    func_80106280_modesel(10, 0xA0122, 0xAA9);
    if (GwStory.unk0 == 12 && func_800465D0_main() == 0) {
        func_8010653C_modesel(10, -300.0f, 225.0f, 300.0f);
        func_8010673C_modesel(10);
    } else {
        func_8010653C_modesel(10, 0.0f, -75.0f, 300.0f);
        func_801066FC_modesel(10);
    }
    func_801065B0_modesel(10, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(10, 0);
    func_800461B4_main(func_8010648C_modesel(10));
    func_8010631C_modesel(19, 0xA0125, 0);
    func_8010631C_modesel(20, 0xA0123, 0);
    func_80106280_modesel(11, 0xD000D, 0x200009);
    func_801068AC_modesel(11, 0);
    func_8010677C_modesel(11, 1);
    func_80106280_modesel(12, 0xD000E, 0x2002B9);
    func_801068AC_modesel(12, 0);
    func_8010677C_modesel(12, 1);
    func_80106280_modesel(13, 0xD000F, 0x2002B9);
    func_801068AC_modesel(13, 0);
    func_8010677C_modesel(13, 1);
}

void func_8010B6B0_modesel(void) {
    func_801063A4_modesel(0);
    func_801063A4_modesel(1);
    func_801063A4_modesel(2);
    func_801063A4_modesel(3);
    func_801063A4_modesel(4);
    func_801063A4_modesel(17);
    func_801063A4_modesel(18);
    func_801063A4_modesel(5);
    func_801063A4_modesel(7);
    func_801063A4_modesel(8);
    func_801063A4_modesel(9);
    func_80046558_main(func_8010648C_modesel(10));
    func_801063A4_modesel(10);
    omDelObj(D_80110BD0_modesel);
    func_80109154_modesel();
    func_801063A4_modesel(11);
    func_801063A4_modesel(12);
}

void func_8010B75C_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14) {
    func_8010B790_modesel(no, x, y, z, unk14);
    func_8010B824_modesel(no);
}

void func_8010B790_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14) {
    no -= 7;
    D_80110B18_modesel[no].pos.x = x;
    D_80110B18_modesel[no].pos.y = y;
    D_80110B18_modesel[no].pos.z = z;
    D_80110B18_modesel[no].unk14 = (unk14 < 0.0f) ? 0.0f : unk14;
}

void func_8010B804_modesel(s32 no, f32 rot) {
    D_80110B18_modesel[no - 7].rot = rot;
}

/* Applies pos and rot to both parts; the second (shadow) part sits at y 4 when the bob is above 8,
   else out of view at -200. */
void func_8010B824_modesel(s32 no) {
    f32 y;

    no -= 7;
    func_80088800_main(D_80110B18_modesel[no].part[0]->mtx, D_80110B18_modesel[no].pos.x,
                       D_80110B18_modesel[no].pos.y, D_80110B18_modesel[no].pos.z);
    func_800185A4_main((Mtx *)D_80110B18_modesel[no].part[0]->mtx, D_80110B18_modesel[no].rot);
    if (D_80110B18_modesel[no].pos.y > 8.0f) {
        y = 4.0f;
    } else {
        y = -200.0f;
    }
    func_80088800_main(D_80110B18_modesel[no].part[1]->mtx, D_80110B18_modesel[no].pos.x, y,
                       D_80110B18_modesel[no].pos.z);
    func_800185A4_main((Mtx *)D_80110B18_modesel[no].part[1]->mtx, D_80110B18_modesel[no].rot);
}

void func_8010B940_modesel(s32 no, f32 speed) {
    f32 rot;

    no -= 7;
    if (speed > 360.0f) {
        speed = 360.0f;
    }
    rot = speed + D_80110B18_modesel[no].rot;
    D_80110B18_modesel[no].rot = rot;
    if (rot > 360.0f) {
        D_80110B18_modesel[no].rot = rot - 360.0f;
    }
}

Process *func_8010B9C4_modesel(void) {
    s16 model;

    model = func_8010648C_modesel(omovlevtno != 1 ? 11 : 13);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_80013320_main(model, 0);
    func_8001C6A8_main(model, 0.0f);
    func_8001C814_main(model, 1, 1);
    func_80108AE0_modesel(&D_80110BE8_modesel[0], &D_80110BE8_modesel[1], &D_80110BE8_modesel[2]);
    return omAddPrcObj(func_801088AC_modesel, 0x5000, 0x2000, 0);
}







/* Mode-select menu loop: picks a model (sel) with the stick or D-pad, confirms with A
   (func_8010CD00_modesel), B asks whether to go back. Returns the choice after its exit animation. */
s32 func_8010BA70_modesel(void) {
    s32 sel;
    s32 ret;
    s32 btn;
    s32 res;
    s16 model;
    MsHmfPart *part;

    sel = 10;
    if (func_800465D0_main() == 1) {
        if (_CheckFlag(0x16) == 0 && _CheckFlag(0x17) == 0) {
            func_80107730_modesel(0, 0x3124);
        } else {
            goto cannon;
        }
    } else if (_CheckFlag(0x28) != 0) {
    cannon:
        sel = 5;
        func_80107730_modesel(0, 0x3106);
    } else if (GwStory.unk0 != 12) {
        sel = 7;
        func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
        func_80107730_modesel(0, 0x3135);
        if (GwSystem.playMode & 1) {
            sel = 8;
        }
    }
    func_8010DF70_modesel();
    func_8010DFD0_modesel(sel);
    omDelPrcObj(D_80110BE0_modesel);
    D_80110BE0_modesel = func_8010899C_modesel();
    func_80013350_main(0);
    func_80109188_modesel(sel, 7);
    while (TRUE) {
        btn = D_800D5558_main[0];
        btn |= func_80109A58_modesel(0);
        if (btn & 0x8000) {
            ret = func_8010CD00_modesel(sel, btn);
            if (ret >= 0) {
                break;
            }
        } else if (btn & 0xF00) {
            ret = func_8010D8DC_modesel(sel, btn);
            if (ret >= 0) {
                sel = ret;
            }
        } else if (btn & 0x4000) {
            func_80105FB4_modesel(1);
            func_80109188_modesel(10, 8);
            HuPrcSleep(8);
            func_801074F0_modesel(0);
            func_801067C0_modesel(10, 19, 8, 8, 2);
            func_80106BA0_modesel(0, 0x3115, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
            func_8010788C_modesel(0);
            res = func_80107838_modesel(0, 1, 0);
            func_801067C0_modesel(10, 20, 8, 8, 2);
            if (res == 0) {
                ret = 16;
                HuPrcVSleep();
                func_80107730_modesel(0, 0x3116);
                func_8010788C_modesel(0);
                break;
            }
            if (func_800465D0_main() == 1) {
                func_8005F698_main(-0x8000, 0, 0, 0, 1);
                func_80107730_modesel(0, 0x3101);
            } else if (GwStory.unk0 == 12) {
                func_80107730_modesel(0, 0x3136);
            } else {
                func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
                func_80107730_modesel(0, 0x3134);
            }
            func_8010788C_modesel(0);
            func_8010DC6C_modesel(sel);
            func_80109188_modesel(sel, 8);
            HuPrcSleep(8);
            func_80105F84_modesel(1);
        }
        func_8010DFD0_modesel(sel);
        func_8010E6D8_modesel(sel);
        HuPrcVSleep();
    }
    switch (ret) {
    case 0:
        func_80105FB4_modesel(1);
    case 16:
        break;
    case 1:
        func_80105FB4_modesel(1);
        func_80107700_modesel(0);
        func_8010EC40_modesel();
        func_80109188_modesel(-1, 20);
        func_80109E90_modesel(9);
        if (GwStory.unk0 != 12 || func_800465D0_main() != 0) {
            func_8010ABB4_modesel(10);
        }
        HuPrcSleep(20);
        model = func_8010648C_modesel(12);
        func_80013320_main(model, 0);
        func_8001C6A8_main(model, 2.0f);
        func_8001C92C_main(model, 0.7f);
        func_8001C814_main(model, 3, 0);
        HuPrcSleep(20);
        HuAudFXPlay(0x2E1);
        func_80106830_modesel(3, 3);
        HuPrcSleep(30);
        break;
    case 4:
    case 6:
    case 7:
    case 9:
    case 10:
    case 13:
        func_80105FB4_modesel(1);
        func_80107700_modesel(0);
        func_8010EC40_modesel();
        func_8010E558_modesel(sel);
        HuAudFXPlay(0x2E0);
        func_8010A62C_modesel(sel);
        func_80109188_modesel(-1, 20);
        omDelObj(D_80110BD0_modesel);
        if (GwStory.unk0 != 12 || func_800465D0_main() != 0) {
            D_80110BD0_modesel = func_8010ABB4_modesel(10);
        }
        goto zoom;
    case 5:
    case 8:
    case 11:
        func_8010E558_modesel(5);
        part = D_80110BD4_modesel;
        part->unk1C.z = 1.0f;
        part->unk40.z = 1.0f;
        part->unk1C.y = 1.0f;
        part->unk40.y = 1.0f;
        part->unk1C.x = 1.0f;
        part->unk40.x = 1.0f;
        HuPrcSleep(8);
        func_80106A38_modesel(5, 17, 0);
        func_801068AC_modesel(18, 0);
        func_8010677C_modesel(18, 0);
        func_8010673C_modesel(18);
        func_80109154_modesel();
        HuPrcSleep(4);
        HuAudFXPlay(0x2FA);
        func_80109444_modesel();
        func_80106910_modesel(18);
        HuPrcSleep(24);
        func_80109408_modesel();
        break;
    case 14:
        func_80105FB4_modesel(1);
        func_80107700_modesel(0);
        func_8010EC40_modesel();
        func_8010E558_modesel(sel);
        omDelObj(D_80110BD0_modesel);
        func_8010AF18_modesel();
        func_80109188_modesel(-1, 20);
    zoom:
        HuPrcSleep(20);
        model = func_8010648C_modesel(11);
        func_80013320_main(model, 0);
        func_8001C6A8_main(model, 0.0f);
        func_8001C92C_main(model, 0.7f);
        func_8001C814_main(model, 3, 0);
        HuPrcSleep(50);
        func_8010ED00_modesel();
        break;
    default:
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    func_8010DFB4_modesel();
    return ret;
}

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
