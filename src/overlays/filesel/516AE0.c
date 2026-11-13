#include "common.h"
#include "game/vibrator.h"

#include "filesel.h"
#include "mallocblock.h"

#define UNK_VALUE FS_FILE_USED

extern u16 D_800D1244_main;

void func_801059A0_filesel(void) {
    ovlEventCall(D_801127A0_filesel, omovlevtno);
}

FS_FILE_END()

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801059D0_filesel);

void func_80105BC0_filesel(void) {
    D_80112E90_filesel = 0;
    func_801059D0_filesel();
    func_80107C84_filesel();
}

FS_FILE_END()

void func_80105BF0_filesel(void) {
    func_80105C1C_filesel();
    func_801061D4_filesel();
    func_8010744C_filesel();
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105C1C_filesel);

s16 func_80105CB0_filesel(s32 no) {
    return D_801135D0_filesel[no];
}

s16 func_80105CC4_filesel(s32 no) {
    return D_80112ED0_filesel[no].espId;
}

void func_80105CE0_filesel(s32 no, s32 dataNum) {
    D_801135D0_filesel[no] = func_8000B838_main(dataNum);
}

void func_80105D18_filesel(s32 no) {
    if (D_801135D0_filesel[no] != -1) {
        HuSprKill(D_801135D0_filesel[no]);
    }
    D_801135D0_filesel[no] = -1;
}

void func_80105D70_filesel(s32 no, s16 animNo) {
    D_80112ED0_filesel[no].espId = InitEspriteSlot(D_801135D0_filesel[animNo], 0, 0);
    func_80105FBC_filesel(no, 160, 120);
}

void func_80105DD8_filesel(s32 no) {
    if (D_80112ED0_filesel[no].espId != -1) {
        func_8000C184_main(D_80112ED0_filesel[no].espId);
    }
    D_80112ED0_filesel[no].espId = -1;
}

void func_80105E48_filesel(s32 no, s32 dataNum) {
    func_80105CE0_filesel(no, dataNum);
    func_80105D70_filesel(no, no);
}

void func_80105E7C_filesel(s32 no, s32 dataNum) {
    func_80105E48_filesel(no, dataNum);
    func_8000BC48_main(D_80112ED0_filesel[no].espId, 0x4000);
}

void func_80105EC0_filesel(s32 no) {
    func_80105DD8_filesel(no);
    func_80105D18_filesel(no);
}

void func_80105EEC_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80105EC0_filesel(i);
    }
}

void func_80105F24_filesel(s32 no) {
    func_8000BB54_main(D_80112ED0_filesel[no].espId);
}

void func_80105F54_filesel(s32 no) {
    func_8000BB94_main(D_80112ED0_filesel[no].espId);
}

void func_80105F84_filesel(s32 no) {
    func_80105F24_filesel(no);
}

void func_80105FA0_filesel(s32 no) {
    func_80105F54_filesel(no);
}

void func_80105FBC_filesel(s32 no, s32 x, s32 y) {
    D_80112ED0_filesel[no].x = x;
    D_80112ED0_filesel[no].y = y;
    func_8000BBD4_main(D_80112ED0_filesel[no].espId, x, y);
}

void func_80106014_filesel(s32 no, s32 *x, s32 *y) {
    *x = D_80112ED0_filesel[no].x;
    *y = D_80112ED0_filesel[no].y;
}

void func_80106044_filesel(s32 no, f32 x, f32 y) {
    D_80112ED0_filesel[no].scaleX = x;
    D_80112ED0_filesel[no].scaleY = y;
    func_8000BE5C_main(D_80112ED0_filesel[no].espId, x, y);
}

void func_80106094_filesel(s32 no, u16 alpha) {
    func_8000BBFC_main(D_80112ED0_filesel[no].espId, alpha);
}

void func_801060CC_filesel(s32 no, u16 attr) {
    func_8000BC48_main(D_80112ED0_filesel[no].espId, attr);
}

void func_80106100_filesel(s32 no, u16 attr) {
    func_8000BC88_main(D_80112ED0_filesel[no].espId, attr);
}

void func_80106134_filesel(s32 no, u16 arg1) {
    func_8000BCC8_main(D_80112ED0_filesel[no].espId, arg1);
}

void func_80106168_filesel(s32 no, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80112ED0_filesel[no].espId, 1);
    func_8000BD94_main(D_80112ED0_filesel[no].espId, arg1, arg2);
}

void func_801061D4_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_80113650_filesel[i].model = -1;
        D_80113650_filesel[i].motion = -1;
    }
}

void func_80106220_filesel(s32 no, s32 arg1, s32 dataNum) {
    s16 model = func_8000B108_main(arg1, dataNum);

    D_80113650_filesel[no].model = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_801062BC_filesel(s32 no, s32 dataNum, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(dataNum);
    D_80113650_filesel[no].motion = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_80106344_filesel(s32 no) {
    if (D_80113650_filesel[no].model != -1) {
        func_8001ACDC_main(D_80113650_filesel[no].model);
        D_80113650_filesel[no].model = -1;
    }
    if (D_80113650_filesel[no].motion != -1) {
        func_8002D4B8_main(D_80113650_filesel[no].motion);
        D_80113650_filesel[no].motion = -1;
    }
}

void func_801063F4_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80106344_filesel(i);
    }
}

s16 func_8010642C_filesel(s32 no) {
    return D_80113650_filesel[no].model;
}

s16 func_80106450_filesel(s32 no) {
    return D_80113650_filesel[no].motion;
}

void func_80106474_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].rot.x = x;
    D_80113650_filesel[no].rot.y = y;
    D_80113650_filesel[no].rot.z = z;
    Hu3DModelRotSet(D_80113650_filesel[no].model, x, y, z);
}

void func_801064DC_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].pos[0] = x;
    D_80113650_filesel[no].pos[1] = y;
    D_80113650_filesel[no].pos[2] = z;
    Hu3DModelPosSet(D_80113650_filesel[no].model, x, y, z);
}

void func_80106550_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].scale.x = x;
    D_80113650_filesel[no].scale.y = y;
    D_80113650_filesel[no].scale.z = z;
    Hu3DModelScaleSet(D_80113650_filesel[no].model, x, y, z);
}

void func_801065B8_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].pos[0];
    *y = D_80113650_filesel[no].pos[1];
    *z = D_80113650_filesel[no].pos[2];
}

void func_8010660C_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].rot.x;
    *y = D_80113650_filesel[no].rot.y;
    *z = D_80113650_filesel[no].rot.z;
}

void func_80106654_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].scale.x;
    *y = D_80113650_filesel[no].scale.y;
    *z = D_80113650_filesel[no].scale.z;
}

void func_8010669C_filesel(s32 no) {
    func_8001C258_main(D_80113650_filesel[no].model, 4, 4);
}

void func_801066DC_filesel(s32 no) {
    func_8001C258_main(D_80113650_filesel[no].model, 4, 0);
}

void func_8010671C_filesel(s32 no, s16 flag) {
    func_8001C814_main(D_80113650_filesel[no].model, -1, flag);
}

void func_80106760_filesel(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80113650_filesel[no].model, D_80113650_filesel[motNo].motion, arg2, arg3, arg4);
}

void func_801067D0_filesel(s32 no, s16 arg1) {
    func_8001C814_main(D_80113650_filesel[no].model, arg1, 0);
}

void func_80106814_filesel(s32 no, f32 speed) {
    func_8001C92C_main(D_80113650_filesel[no].model, speed);
}

void func_8010684C_filesel(s32 no, u32 time) {
    func_8001C6A8_main(D_80113650_filesel[no].model, time);
}

void func_801068B0_filesel(s32 no) {
    while (HmfModelData[D_80113650_filesel[no].model].unk40 !=
           D_800CCF58_main[HmfModelData[D_80113650_filesel[no].model].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80106950_filesel(s32 no) {
    return HmfModelData[D_80113650_filesel[no].model].unk40 ==
           D_800CCF58_main[HmfModelData[D_80113650_filesel[no].model].unk02].unk02;
}

void func_801069D8_filesel(s32 no, s32 motNo, s16 flag) {
    s16 model = func_8010642C_filesel(no);
    s16 motion = func_80106450_filesel(motNo);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, flag);
}

void func_80106A48_filesel(s32 dataNum) {
    D_80114150_filesel = func_8000B838_main(dataNum);
    D_80114152_filesel = InitEspriteSlot(D_80114150_filesel, 0, 0);
    func_8000BC48_main(D_80114152_filesel, 0x4000);
    func_8000BBD4_main(D_80114152_filesel, 160, 120);
}

void func_80106AAC_filesel(void) {
    func_8000C184_main(D_80114152_filesel);
    HuSprKill(D_80114150_filesel);
}

u32 func_80106AD8_filesel(u32 mes) {
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
void func_80106B40_filesel(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 id;
    u32 buf;

    switch (type) {
        case 1:
            buf = func_80106AD8_filesel(mes);
            id = func_80106ED8_filesel(buf, x, y, w, h, type);
            break;
        case 2:
            buf = func_80106AD8_filesel(mes);
            id = func_80107040_filesel(buf, x, y, w, h, type);
            break;
        case 3:
            buf = func_80106AD8_filesel(mes);
            id = func_801071E8_filesel(buf, x, y, type);
            break;
        case 4:
            buf = func_80106AD8_filesel(mes);
            id = func_801072B4_filesel(buf, x, y, type);
            break;
        case 5:
            buf = func_80106AD8_filesel(mes);
            id = func_80107380_filesel(buf, x, y, type);
            break;
        case 0:
        default:
            buf = func_80106AD8_filesel(mes);
            id = func_80106D8C_filesel(buf, x, y, w, h, type);
            break;
    }
    if (buf > 0x80000000) {
        D_80114158_filesel[no].unk_04 = buf;
    }
    D_80114158_filesel[no].unk_00 = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106B40_filesel);
#endif

s16 func_80106D8C_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
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

s16 func_80106ED8_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
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

s16 func_80107040_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
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

s16 func_801071E8_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801072B4_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x14);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 0);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107380_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005FE54_main(win, 1);
    func_80060C14_main(win, 0);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

void func_8010744C_filesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80114158_filesel[i].unk_00 = -1;
        D_80114158_filesel[i].unk_04 = 0;
    }
}

void func_80107490_filesel(s32 no) {
    if (D_80114158_filesel[no].unk_08 == 3) {
        func_80060EA8_main(D_80114158_filesel[no].unk_00, 1);
        func_800610E0_main(D_80114158_filesel[no].unk_00);
    } else {
        func_8005FE90_main(D_80114158_filesel[no].unk_00);
        func_8005F364_main(D_80114158_filesel[no].unk_00);
        D_80114158_filesel[no].unk_00 = -1;
    }
    if (D_80114158_filesel[no].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[no].unk_04);
        D_80114158_filesel[no].unk_04 = 0;
    }
}

void func_80107574_filesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80114158_filesel[i].unk_00 != -1) {
            func_80107490_filesel(i);
        }
    }
}

void func_801075D8_filesel(s32 no, f32 x, f32 y) {
    func_8005BB18_main(D_80114158_filesel[no].unk_00, x, y);
}

void func_80107608_filesel(s32 no, f32 x, f32 y) {
    func_8005BA90_main(D_80114158_filesel[no].unk_00, x, y);
}

void func_80107670_filesel(s32 no) {
    func_8005FFA8_main(D_80114158_filesel[no].unk_00);
}

void func_801076A0_filesel(s32 no) {
    func_8005FE90_main(D_80114158_filesel[no].unk_00);
}

void func_801076D0_filesel(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80114158_filesel[arg0].unk_00);
    if (D_80114158_filesel[arg0].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[arg0].unk_04);
        D_80114158_filesel[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106AD8_filesel(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80114158_filesel[arg0].unk_04 = temp_v0;
    }
    func_8005B43C_main(D_80114158_filesel[arg0].unk_00, temp_v0, -1, -1);
}

void func_8010779C_filesel(s32 no, s8 arg1, s32 arg2) {
    func_800601BC_main(D_80114158_filesel[no].unk_00, arg2, arg1);
}

s32 func_801077D8_filesel(s32 no, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_80114158_filesel[no].unk_00, arg1, arg2);
}

s16 func_80107810_filesel(s32 no) {
    return D_80114158_filesel[no].unk_00;
}

void func_8010782C_filesel(s32 no) {
    while (func_8005E0C0_main(D_80114158_filesel[no].unk_00) != 0) {
        HuPrcVSleep();
    }
}

void func_80107880_filesel(s32 btn) {
    do {
        HuPrcVSleep();
    } while (!(btn & D_800D5558_main[0]));
}

void func_801078BC_filesel(s32 no, s16 arg1) {
    func_8005BE30_main(D_80114158_filesel[no].unk_00, arg1);
}

u16 func_801078F4_filesel(s32 val) {
    char buf[0x100];
    FsHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, "\n%d\n", val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(FsHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
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

void func_80107AA8_filesel(void) {
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

void func_80107C50_filesel(omObjData *obj) {
    if (D_800D5558_main[0] & 0x4000) {
        func_8001F38C_main(0xFF, 0, 0);
    }
}

void func_80107C84_filesel(void) {
    func_80105BF0_filesel();
    func_801119F4_filesel();
    func_80111C30_filesel();
    D_80114468_filesel = omAddPrcObj(func_80107CF8_filesel, 0x5000, 0x2000, 0);
    D_8011446C_filesel = omAddObj(6, 0, 0, -1, func_80107C50_filesel);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107CF8_filesel);

void func_801083AC_filesel(void) {
    func_80105E48_filesel(1, 0x1F000D);
    func_80105F54_filesel(1);
    func_80105E48_filesel(2, 0x1F000E);
    func_80106168_filesel(2, 0, 0);
    func_801060CC_filesel(2, 0x800);
    func_80105F54_filesel(2);
    func_80105E48_filesel(3, 0x1F000F);
    func_80106168_filesel(3, 0, 0);
    func_801060CC_filesel(3, 0x800);
    func_80105F54_filesel(3);
}

void func_80108440_filesel(void) {
    func_80105EC0_filesel(1);
    func_80105EC0_filesel(2);
    func_80105EC0_filesel(3);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A64_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A68_filesel);

u32 func_8010846C_filesel(void) {
    s32 sel;
    s32 i;
    s32 file;

    sel = FS_LAST_FILE;
    if (sel >= 3) {
        sel = 2;
    }
    if (D_801142DC_filesel[FS_LAST_FILE].unk_00 != FS_FILE_USED) {
        for (i = 0; i < 3; i++) {
            if (D_801142DC_filesel[i].unk_00 == FS_FILE_USED) {
                sel = i;
                break;
            }
        }
    }
    func_80105F24_filesel(18);
    func_8010AB1C_filesel(18, sel);
    for (i = 0; i < 8; i++) {
        func_80106044_filesel(18, 1.0f, i * 0.125f);
        HuPrcVSleep();
    }
    func_80106044_filesel(18, 1.0f, 1.0f);
    func_801110F0_filesel(sel);
    while (TRUE) {
        while ((sel = func_80109570_filesel(sel)) == -1) {
            HuPrcVSleep();
        }
        switch (sel) {
            case 0:
            case 1:
            case 2:
                HuAudFXPlay(2);
                func_80105F54_filesel(18);
                return sel;
            case 3:
                HuAudFXPlay(2);
                func_80109B2C_filesel();
                break;
            case 4:
                HuAudFXPlay(2);
                func_8010A028_filesel();
                break;
            case 5:
            case 6:
            case 7:
                HuAudFXPlay(2);
                file = sel - 5;
                func_80105FA0_filesel(18);
                func_80108D74_filesel();
                func_80108A94_filesel();
                func_80105FA0_filesel(12);
                func_8010F874_filesel(0);
                func_8010F874_filesel(1);
                func_8010F874_filesel(2);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010F874_filesel(i);
                        func_8010FF48_filesel(i, 16);
                    }
                }
                HuAudFXPlay(0x2F2);
                func_80110320_filesel(file, 32);
                HuAudFXPlay(0x2F0);
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010669C_filesel(i);
                        func_8010669C_filesel(i + 3);
                    }
                }
                HuPrcSleep(16);
                func_80107670_filesel(0);
                func_8010F65C_filesel();
                func_8010F678_filesel(4);
                if (func_80109968_filesel(file) != 0) {
                    func_80107670_filesel(4);
                    func_80107608_filesel(4, 160.0f, 208.0f);
                    func_801076D0_filesel(4, 0x2A15);
                    HuPrcSleep(3);
                    SLCurBoxNoSet(file);
                    func_80112584_filesel(file);
                    func_80112184_filesel(file);
                    func_801076A0_filesel(4);
                    HuPrcSleep(3);
                }
                func_801076A0_filesel(0);
                func_8010F65C_filesel();
                func_8011072C_filesel(file, 32);
                HuAudFXPlay(0x2F1);
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010FBE0_filesel(i, 16);
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_801066DC_filesel(i);
                        func_801066DC_filesel(i + 3);
                    }
                }
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    func_8010F844_filesel(i);
                }
                func_8010F678_filesel(0);
                func_801088DC_filesel();
                func_80108C34_filesel();
                func_80105F84_filesel(18);
                break;
        }
        func_8010AB1C_filesel(18, sel);
        HuPrcVSleep();
    }
}

s32 func_80108834_filesel(void) {
    s32 i;
    s32 total;

    for (i = 0, total = 0; i < ARRAY_COUNT(D_801142DC_filesel); i++) {
        if (D_801142DC_filesel[i].unk_00 == UNK_VALUE) {
            total++;
        }
    }

    return total;
}

void func_80108878_filesel(void) {
    s32 n = func_80108834_filesel();

    if (n == 1 || n == 2) {
        func_80106168_filesel(2, 1, 0);
    } else {
        func_80106168_filesel(2, 0, 0);
    }
    if (n != 0) {
        func_80106168_filesel(3, 1, 0);
    } else {
        func_80106168_filesel(3, 0, 0);
    }
}

void func_801088DC_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    for (i = 0; i < 3; i++) {
    }
    func_80105F24_filesel(1);
    func_80105F24_filesel(2);
    func_80105F24_filesel(3);
    func_80108878_filesel();
    for (i = 0; i < 11; i++) {
        t = i * 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        HuVecCopyXYZ(&from, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&to, 224.0f, 40.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80105FBC_filesel(1, pos.x, pos.y);
        func_80105FBC_filesel(2, pos.x - 22.0f, pos.y);
        func_80105FBC_filesel(3, pos.x + 26.0f, pos.y);
        HuPrcVSleep();
    }
}

void func_80108A94_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    for (i = 0; i < 11; i++) {
        t = 1.0f - i * 0.1f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        HuVecCopyXYZ(&from, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&to, 224.0f, 40.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80105FBC_filesel(1, pos.x, pos.y);
        func_80105FBC_filesel(2, pos.x - 22.0f, pos.y);
        func_80105FBC_filesel(3, pos.x + 26.0f, pos.y);
        HuPrcVSleep();
    }
    func_80105F54_filesel(1);
    func_80105F54_filesel(2);
    func_80105F54_filesel(3);
}

void func_80108C34_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    func_80107670_filesel(4);
    for (i = 0; i < 11; i++) {
        t = i * 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        HuVecCopyXYZ(&from, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&to, 160.0f, 192.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80107608_filesel(4, 160.0f, (96.0f - t * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108D74_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108EB8_filesel);

#define CLAMP_BELOW(val, limit) ((val) < (limit) ? (val) : 0)

enum OptionsFileSelect {
    OPTION_FILE0 = 0,
    OPTION_FILE1 = 1,
    OPTION_FILE2 = 2,
    OPTION_FILES_END,
    OPTION_COPY = 3,
    OPTION_ERASE = 4,
    OPTION_FILES_NAME_BEGIN,
    OPTION_FILE0_NAME = 5,
    OPTION_FILE1_NAME = 6,
    OPTION_FILE2_NAME = 7,
    OPTION_MAX = 7,
};

// TODO: can the gotos be removed?
// main function for handling input when an option hasn't been select yet
u32 func_80109570_filesel(s32 arg0) {
    s32 temp_v0;
    u32 temp_v1;
    s32 animTimerAdjusted;
    s32 animTimer;
    u16 pressedInput;
    s32 cursorIndex;
    u32 selectedOption;
    s32 unkValue;

    animTimer = 0;

    if (arg0 < 0) {
        arg0 = 0;
    }

    selectedOption = arg0;
    cursorIndex = selectedOption;
    unkValue = UNK_VALUE;

    while (1) {
        pressedInput = D_800D1244_main;
        temp_v0 = func_80111B14_filesel(0);
        if (temp_v0 != -1) {
            pressedInput |= temp_v0;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            switch (selectedOption) {
                case OPTION_FILE0:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE1:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE2:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_COPY:
                case OPTION_ERASE:
                case OPTION_FILE0_NAME:
                case OPTION_FILE1_NAME:
                case OPTION_FILE2_NAME:
                    break;
                default:
                    goto checkIfCursorIndexChanged;
            }
            return selectedOption;
        }
        if ((D_800D5558_main[0] & B_BUTTON)) {
            if (selectedOption > OPTION_MAX) {
                goto checkIfCursorIndexChanged;
            }
        }
        switch (selectedOption) {
            case OPTION_FILE0:
            case OPTION_FILE1:
            case OPTION_FILE2:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    func_801076D0_filesel(4, 0x2A00);
                    func_80110FB0_filesel(selectedOption);
                    cursorIndex = selectedOption + 1;
                    if (pressedInput & L_JPAD) {
                        cursorIndex = selectedOption - 1;
                        // if less than 0, wrap index back around to file index 2
                        if (cursorIndex < 0) {
                            cursorIndex = OPTION_FILE2;
                        }
                    } else {
                        cursorIndex = CLAMP_BELOW(cursorIndex, OPTION_FILES_END);
                    }
                } else if (pressedInput & (U_JPAD | D_JPAD)) {
                    if (pressedInput & U_JPAD) {
                        cursorIndex = OPTION_COPY;
                        if ((temp_v1 - 1) < (OPTION_FILES_END - 1)) {
                            func_801076D0_filesel(4, 0x2A01);
                        } else {
                            func_801076D0_filesel(4, 0x2A03);
                        }
                        func_80110FB0_filesel(selectedOption);
                    } else {
                        if (D_801142DC_filesel[cursorIndex].unk_00 == unkValue) {
                            cursorIndex = selectedOption + OPTION_FILES_NAME_BEGIN;
                            func_80110FB0_filesel(selectedOption);
                        }
                    }
                }
                break;
            case OPTION_COPY:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    if (temp_v1 == 0) {
                        func_801076D0_filesel(4, 0x2A13);
                    } else {
                        func_801076D0_filesel(4, 0x2A07);
                    }
                    cursorIndex = OPTION_ERASE;
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = OPTION_FILE1;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_ERASE:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    cursorIndex = OPTION_FILES_END;
                    if ((temp_v1 - 1) < 2) {
                        func_801076D0_filesel(4, 0x2A01);
                    } else {
                        func_801076D0_filesel(4, 0x2A03);
                    }
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = 2;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_FILE0_NAME:
            case OPTION_FILE1_NAME:
            case OPTION_FILE2_NAME:
                func_801076D0_filesel(4, 0x2A11);
                if (pressedInput & L_JPAD) {
                    cursorIndex = selectedOption;
                    do {
                        cursorIndex -= 1;
                        if (cursorIndex < OPTION_FILES_NAME_BEGIN) {
                            cursorIndex = 7;
                        }
                    } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                } else {
                    if (pressedInput & R_JPAD) {
                        cursorIndex = selectedOption;
                        do {
                            // if cursor goes over max, wrap around back to file 0 name
                            if (++cursorIndex > OPTION_MAX) {
                                cursorIndex = OPTION_FILE0_NAME;
                            }
                        } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                    }
                }
                if (pressedInput & U_JPAD) {
                    cursorIndex = selectedOption - OPTION_FILES_NAME_BEGIN;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
        }

    checkIfCursorIndexChanged:
        if (selectedOption != cursorIndex) {
            // animate cursor to new position
            func_8010AB60_filesel(18, cursorIndex);
            selectedOption = cursorIndex;

            if (selectedOption < OPTION_FILES_END) {
                func_801110F0_filesel(selectedOption);
            }
        }
        func_8010AB1C_filesel(18, selectedOption);

        animTimerAdjusted = (animTimer < 0) ? animTimer + 7 : animTimer;
        animTimerAdjusted = (animTimerAdjusted >> 3);
        func_8010AB58_filesel(18, -animTimerAdjusted);

        animTimer = (animTimer < 20) ? animTimer + 1 : 0;

        HuPrcVSleep();
    }
    return selectedOption;
}

s32 func_80109904_filesel(s32 arg0) {
    u8 buf[32]; // TODO: figure out correct type of this
    s32 temp_s0;

    bzero(&buf, sizeof(buf));
    func_80112494_filesel(arg0, buf);
    HuPrcSleep(3);
    func_801076D0_filesel(4, 0x2A11);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 func_80109968_filesel(s32 arg0) {
    s32 temp_s0;

    HuPrcSleep(3);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801099A8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80109B2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A028_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A680_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A7D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A978_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AF0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AB1C_filesel);

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AB60_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AC58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B4D0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B4FC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B528_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B554_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B598_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B5D4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B6F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B80C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B18_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B24_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B30_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B3C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B48_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B54_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B60_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B78_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B84_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B90_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BA8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BB4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BC0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BCC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BD8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BF0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BFC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C08_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C14_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C20_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C38_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C44_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C50_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C5C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C68_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C74_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C80_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C98_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CA4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CB0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CBC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CC8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D00_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D1C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D38_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B998_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BDC4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BE14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BE30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C25C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C688_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D7C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DAC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010CCA8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D13C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DD54_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DDC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DEEC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DF58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DFF4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E1B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E250_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E740_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E864_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F10C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F12C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F168_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F5C8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F65C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DF8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F678_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F760_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F844_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F874_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F8A4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FBE0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FC58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FF48_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FFA0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801102F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110320_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801103A0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801106FC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011072C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801107AC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110B4C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110B7C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110C84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110CC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110D0C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110E70_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110F04_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110FB0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111004_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801110F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111144_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011132C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011139C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801113E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111790_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111944_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801119F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111A08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111B14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111C30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111CBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111E78_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111FFC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112184_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801122B0_filesel);

s32 func_80112494_filesel(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_801142DC_filesel[arg0].unk_01[i] = arg1[i];
    }

    // terminate string
    D_801142DC_filesel[arg0].unk_01[i] = '\0';
    D_801142DC_filesel[arg0].unk_01[i + 1] = '\0';
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112508_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112584_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801125E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112630_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801126C0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112758_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E68_filesel);
