#include "common.h"
#include "gcc/string.h"

extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern u8 D_800CD280_main;
extern u16 D_800D530C_main;
extern u16 D_80106500_meschk;

extern void func_800142A0_main(s32);
extern void func_8004DEC8_main(s16);
extern void func_80105B50_meschk(void);
extern void func_80105B8C_meschk(void);
extern void func_80106334_meschk(omObjData *data);
extern void func_80106390_meschk(omObjData *data);
extern void func_801063BC_meschk(void);

// m1 lf1
typedef struct unk1EA70StructC unk1EA70StructC; /* matrix bake record, src/14EA0.c */
unk1EA70StructC* func_80016784_main(s16 arg0, s16 arg1);
void func_80016FB4_main(s16 arg0, unk1EA70StructC* arg1, s16 arg2);
void func_80017320_main(unk1EA70StructC* arg0);
void func_80060858_main(s32 winId, u16 btn);

typedef struct MesChkEntry {
    /* 0x00 */ u8* name; /* rewritten in place for the font: . ! _ - */
    /* 0x04 */ u32 start; /* first message id */
    /* 0x08 */ u32 end;   /* last message id; 0 = start only */
} MesChkEntry; // Size 0xC

extern MesChkEntry D_80106518_meschk[];

void func_801059A0_meschk() {
    omObjData *temp_v0;

    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 10);
    func_8005A6B0_main();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    Center.y = 100.0f;
    CZoom = 600.0f;
    CRot.x = -30.0f;
    omSetStatBit(temp_v0, 0xA0);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        func_8004DEC8_main(D_800A1786_main);
        D_800A1786_main = -1;
    }
    omAddObj(0x2710, 0, 0, -1, func_80106334_meschk);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    omAddPrcObj(func_80105B50_meschk, 0x3F00, 0x800, 0);
    omAddPrcObj(func_801063BC_meschk, 0x3F00, 0x800, 0);
    WipeCreateIn(0, 0);
    D_800CD280_main = 1;
    func_8001F38C_main(0xFF, 0xFF, 0xFF);
}

void func_80105B50_meschk() {
    func_80105B8C_meschk();
    D_80106500_meschk = 1;
    func_8005F524_main();
    while (1) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
void func_80105B8C_meschk(void) {
    s16 size[2];
    s16 msgWin;
    s16 titleWin;
    s16 count;
    s16 quit;
    MesChkEntry* entry;
    s16 sel;
    s16 i;
    s16 cur;
    u8* msg;
    u8* p;
    s32 noWait;
    s32 portrait;

    count = 0;
    while (D_80106518_meschk[count].start != 0xFFFF) {
        count++;
    }
    titleWin = func_80061188_main(-1, 60, 20, 200, 20, 0);
    func_80061388_main(titleWin);
    sel = 0;
    quit = 0;
    do {
        entry = &D_80106518_meschk[sel];
        for (i = 0; i < strlen((char*)entry->name); i++) {
            if (entry->name[i] == '.') {
                entry->name[i] = 0x85;
            }
            if (entry->name[i] == '!') {
                entry->name[i] = 0xC2;
            }
            if (entry->name[i] == '_' || entry->name[i] == '-') {
                entry->name[i] = 0x3D;
            }
        }
        func_8005D294_main(titleWin);
        func_8005B43C_main(titleWin, (s32)entry->name, -1, -1);
        if (entry->end == 0) {
            entry->end = entry->start;
        }
        func_800604A8_main(size, entry->start, entry->end);
        msg = func_800364DC_main((void*)entry->start);
        for (i = 0, p = msg; i < 5; i++, p++) {
            if ((p[0] == 0x10 || p[0] == 0x20 || p[0] == 0x1A) && (p[1] == 0x10 || p[1] == 0x20 || p[1] == 0x1A) &&
                (p[2] == 0x10 || p[2] == 0x20 || p[2] == 0x1A)) {
                break;
            }
        }
        func_800365E8_main(msg);
        if (i == 5) {
            msgWin = func_80061188_main(0, 50, 44, size[0], size[1], 0);
            portrait = 0;
        } else {
            msgWin = func_80061188_main(7, 50, 44, size[0], size[1], 0);
            portrait = 1;
        }
        func_80060858_main(msgWin, 0x3F);
        func_8005FBF8_main(msgWin, 0xC0, 0x20, 0xC0);
        func_80061388_main(msgWin);
        for (cur = entry->start; cur <= entry->end; cur++) {
            func_8005D294_main(msgWin);
            msg = func_800364DC_main((void*)(s32)cur);
            p = msg;
            noWait = 0;
            for (; *p != 0; p++) {
                if (*p == 0xFF) {
                    noWait = 1;
                    break;
                }
                p += (*p == 0x18);
            }
            for (p = msg, i = 0; i < 5; i++, p++) {
                if ((p[0] == 0x10 || p[0] == 0x20 || p[0] == 0x1A) && (p[1] == 0x10 || p[1] == 0x20 || p[1] == 0x1A) &&
                    (p[2] == 0x10 || p[2] == 0x20 || p[2] == 0x1A)) {
                    break;
                }
            }
            if ((i == 5) & (portrait & 1)) {
                func_80061934_main(msgWin, 0);
                portrait = 0;
            } else if ((i != 5) && (portrait ^ 1)) {
                func_80061934_main(msgWin, 7);
                portrait = 1;
            }
            func_800365E8_main(msg);
            func_8005B43C_main(msgWin, cur, -1, -1);
            while (func_8005E0C0_main(msgWin) != 0) {
                HuPrcVSleep();
            }
            if (D_800CC69C_main[msgWin].unk_30 != 0) {
                func_8005E1D8_main(msgWin, 0, 0);
            } else if (noWait == 0) {
                while (!(D_800D5558_main[0] & 0xC03F)) {
                    HuPrcVSleep();
                }
            }
            if ((D_800CC69C_main[msgWin].unkA8 & 0x4000) || (D_800D5558_main[0] & 0x4000)) {
                if (entry->start < cur) {
                    cur -= 2;
                } else {
                    cur -= 1;
                }
            }
            if ((D_800CC69C_main[msgWin].unkA8 & 8) || (D_800D5558_main[0] & 8)) {
                if (sel != 0) {
                    sel -= 2;
                } else {
                    sel -= 1;
                }
                break;
            }
            if ((D_800CC69C_main[msgWin].unkA8 & 4) || (D_800D5558_main[0] & 4)) {
                break;
            }
            if ((D_800CC69C_main[msgWin].unkA8 & 2) || (D_800D5558_main[0] & 2)) {
                if (sel - 5 >= 0) {
                    sel -= 6;
                } else {
                    sel = -1;
                }
                break;
            }
            if ((D_800CC69C_main[msgWin].unkA8 & 1) || (D_800D5558_main[0] & 1)) {
                if (sel + 5 < count) {
                    sel += 4;
                } else {
                    sel = count - 1;
                }
                break;
            }
            if ((D_800CDA7C_main[0] & 0x30) == 0x30) {
                quit = 1;
                break;
            }
        }
        func_8005F364_main(msgWin);
        D_800CC69C_main[msgWin].unkA8 = 0;
        sel++;
        if (sel >= count) {
            sel--;
        }
    } while (quit == 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/meschk/4F69F0", func_80105B8C_meschk);
#endif

void func_80106334_meschk(omObjData *arg0) {
    if ((D_80106500_meschk != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(0, 8);
        arg0->func = &func_80106390_meschk;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106390_meschk(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_801063BC_meschk(void) {
    s16 model;
    s16 data;
    unk1EA70StructC* bake;
    s16 frame;

    model = func_8000B108_main(0x700A0, 0x2A9);
    data = func_8000B108_main(0x70001, 8);
    func_8001C5B4_main(model, data);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 100.0f);
    bake = func_80016784_main(model, 2);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        if (D_80106500_meschk != 0) {
            break;
        }
        func_80016FB4_main(model, bake, frame);
        if (frame >= D_800CCF58_main[HmfModelData[data].unk02].unk02) {
            frame = 0;
        }
        frame += 2;
    }
    func_80017320_main(bake);
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_801069E0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_801069E4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_801069F0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_801069FC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A04_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A10_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A20_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A2C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A34_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A40_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A48_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A50_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A58_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A60_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A6C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A7C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A88_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106A94_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AA0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AAC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AB8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AC0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AD0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106ADC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AE4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AEC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AF4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106AFC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B04_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B14_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B24_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B34_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B44_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B54_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B64_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B6C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B78_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B80_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B88_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106B94_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BA0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BB0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BBC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BC8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BD0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BE0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BEC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106BF8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C04_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C10_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C20_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C2C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C38_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C40_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C48_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C54_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C5C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C64_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C6C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C74_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C80_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C88_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C94_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106C9C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CAC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CB4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CC4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CD4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CDC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CE4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CEC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CF4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106CFC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D08_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D14_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D20_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D2C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D38_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D40_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D4C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D54_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D5C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D68_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D74_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D80_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D88_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D94_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106D9C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DA8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DB8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DC0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DCC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DD8_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DE0_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DEC_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106DF4_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106E04_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106E0C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106E1C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106E2C_meschk);

INCLUDE_RODATA("asm/nonmatchings/overlays/meschk/4F69F0", D_80106E34_meschk);
