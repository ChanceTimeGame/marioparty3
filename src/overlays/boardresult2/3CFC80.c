#include "common.h"
#include "../ovl_81_name/ovl_81.h"

// event e9: board results, page 2 (the star/coin ranking and the board-record scroll)

/* Texture-animation slot (MP2 TexAnimSlot; 14EA0.c). */
typedef struct BR2TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} BR2TexAnimSlot; // sizeof 0xC

/* The board-record scroll's model and window (built by func_80107964). */
typedef struct BR2Record {
    /* 0x00 */ Object* obj;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ s16 win;
} BR2Record;

extern BR2TexAnimSlot* D_800D1714_main;
extern u16 D_800D530C_main;
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData*);
void func_80033970_main(HmfData*);
s16 func_800329B4_main(void*);
void func_800D7EB8_name_81(void);
void func_800F3F4C_name_81(void);
void func_800F4300_name_81(void);
void func_800D7F0C_name_81(void);
void func_800F4030_name_81(void);
void func_800F4314_name_81(void);

void func_80108E1C_boardresult2(void);
void func_801096AC_boardresult2(omObjData* obj);
void func_801096F0_boardresult2(omObjData* obj);
void func_80109714_boardresult2(void);
void func_80109740_boardresult2(void);
void func_8010976C_boardresult2(void);
void func_8010979C_boardresult2(void);

extern UnkBoard4* D_801099A0_boardresult2;
extern UnkBoard4* D_801099A4_boardresult2;
extern UnkBoard4* D_801099A8_boardresult2;
extern UnkBoard4* D_801099B0_boardresult2[4];
extern UnkBoard4* D_801099C0_boardresult2;
extern UnkBoard4* D_801099C4_boardresult2;
extern BR2Record* D_801099C8_boardresult2;
extern UnkBoard4* D_801099CC_boardresult2;
extern UnkBoard4* D_801099D0_boardresult2;
extern UnkBoard4* D_801099D4_boardresult2;
extern UnkBoard4* D_801099D8_boardresult2[4];
extern UnkBoard4* D_801099E8_boardresult2;
extern UnkBoard4* D_801099EC_boardresult2;
extern UnkBoard4* D_801099F0_boardresult2;
extern UnkBoard4* D_801099F4_boardresult2;
extern s32 D_801099F8_boardresult2[16];
extern s16 D_80109A38_boardresult2[10];
extern s16 D_80109A4C_boardresult2;
extern s16 D_80109A4E_boardresult2;

void func_801059A0_boardresult2(void) {
    u32 i;
    s32 r;

    omInitObjMan(0x50, 0x50);
    func_8010976C_boardresult2();
    func_80109714_boardresult2();
    func_8005A6B0_main();
    omAddPrcObj(func_80108E1C_boardresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801096F0_boardresult2);
    for (i = 0; i < 16; i++) {
        do {
            r = func_800EFE20_name_81(7.0f);
            D_801099F8_boardresult2[i] = r;
        } while (i != 0 && D_801099F8_boardresult2[i - 1] == r);
    }
}

s16 func_80105A8C_boardresult2(s16 model, s32 file, char* name) {
    void* data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80109A4C_boardresult2 = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].unk_00;
    D_80109A4E_boardresult2 = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_80105B98_boardresult2(s16 model, s16 frame) {
    BR2TexAnimSlot* p;

    if (D_80109A4E_boardresult2 != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80109A4E_boardresult2];
        p->unk_00 = frame;
        p->unk_04 = 0;
        p->unk_0A = 0;
        p->unk_06 = 0;
        p->unk_02 = 0;
    }
}

s16 func_80105C68_boardresult2(s32 file) {
    void* data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105CB0_boardresult2);

void func_80106924_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099A4_boardresult2);
    func_800F4584_name_81(D_801099A8_boardresult2);
    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099B0_boardresult2[i]);
    }
    func_800F4584_name_81(D_801099C0_boardresult2);
    func_800F4584_name_81(D_801099C4_boardresult2);
}

void func_801069A4_boardresult2(void) {
    s32 j;
    s32 i;

    for (j = 0; j < 4; j++) {
        HuSprAttrSet(D_801099A4_boardresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrSet(D_801099A8_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrSet(D_801099C0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_801099C4_boardresult2->unk_0A, 0, 0x8000);
}

void func_80106A9C_boardresult2(void) {
    s32 j;
    s32 i;

    for (j = 0; j < 4; j++) {
        HuSprAttrReset(D_801099A4_boardresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrReset(D_801099A8_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrReset(D_801099B0_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrReset(D_801099C0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_801099C4_boardresult2->unk_0A, 0, 0x8000);
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80106B94_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109864_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_801074B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109880_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098C4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098DC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098FC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010991C_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010992C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80107964_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108548_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_801085F8_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_8010879C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108958_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108A48_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108C70_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108E1C_boardresult2);

void func_801096AC_boardresult2(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8010979C_boardresult2();
        func_80109740_boardresult2();
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_801096F0_boardresult2(omObjData* obj) {
    if (D_800D530C_main != 0) {
        obj->func = func_801096AC_boardresult2;
    }
}

void func_80109714_boardresult2(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80109740_boardresult2(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
}

void func_8010976C_boardresult2(void) {
    Hu3DCamInit(2);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_8010979C_boardresult2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010996C_boardresult2);
