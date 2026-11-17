#include "common.h"
#include "gcc/string.h"

extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern u8 D_800CD280_main;
extern u16 D_800D530C_main;

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

/* .data 0x80106500: one 0x18-byte object; only the first halfword (the quit flag) is used */
typedef struct MesChkWork {
    /* 0x00 */ u16 quit;
    /* 0x02 */ s16 unk02[3];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ s32 unk14;
} MesChkWork; // Size 0x18

MesChkWork D_80106500_meschk = { 0, { 50, 60, 0 }, 0, 1.0f, { -1, 1200 }, 0 };

/* message-check list: name, first and last message id; ends with start 0xFFFF */
MesChkEntry D_80106518_meschk[] = {
    { (u8*)"B1_snowman", 0x200, 0x204 },
    { (u8*)"B_kekka", 0x1400, 0x1418 },
    { (u8*)"B_P_starlift", 0x1500, 0x1532 },
    { (u8*)"B_R_starlift", 0x1700, 0x1705 },
    { (u8*)"B_Rule", 0x1600, 0x1633 },
    { (u8*)"B_S_starlift", 0x1A00, 0x1A16 },
    { (u8*)"B_start", 0x1800, 0x1817 },
    { (u8*)"B_syousai", 0x1900, 0x190C },
    { (u8*)"B1_lake", 0x100, 0x101 },
    { (u8*)"B1_turuturu", 0x300, 0x0 },
    { (u8*)"B2_ankou", 0x400, 0x0 },
    { (u8*)"B2_ika", 0x500, 0x0 },
    { (u8*)"B2_submarine", 0x600, 0x602 },
    { (u8*)"B3_saboten", 0x700, 0x0 },
    { (u8*)"B3_star", 0x800, 0x0 },
    { (u8*)"B4_kinokio", 0x900, 0x909 },
    { (u8*)"B4_mori", 0xA00, 0x0 },
    { (u8*)"B4_tyorobu", 0xB00, 0xB05 },
    { (u8*)"B5_battan", 0xC00, 0xC08 },
    { (u8*)"B5_torokko", 0xD00, 0xD03 },
    { (u8*)"B6_ana", 0xE00, 0xE01 },
    { (u8*)"B6_bomb", 0xF00, 0xF04 },
    { (u8*)"B6_guruguru", 0x1000, 0x0 },
    { (u8*)"B6_hasi", 0x1100, 0x0 },
    { (u8*)"bankmasu", 0x1200, 0x1204 },
    { (u8*)"battlemasu", 0x1300, 0x1305 },
    { (u8*)"chancetime", 0x1B00, 0x1B1D },
    { (u8*)"charname", 0x1C00, 0x1C5F },
    { (u8*)"D_battle", 0x1E00, 0x1E01 },
    { (u8*)"D_event", 0x1F00, 0x1F30 },
    { (u8*)"D_kekka", 0x2000, 0x2006 },
    { (u8*)"D_map1", 0x2100, 0x2103 },
    { (u8*)"D_map5", 0x2200, 0x0 },
    { (u8*)"D_map6", 0x2300, 0x0 },
    { (u8*)"D_P_starlift", 0x2400, 0x2433 },
    { (u8*)"D_R_starlift", 0x2600, 0x2605 },
    { (u8*)"D_Rule", 0x2500, 0x253A },
    { (u8*)"D_S_starlift", 0x2900, 0x2920 },
    { (u8*)"D_start", 0x2700, 0x2711 },
    { (u8*)"D_syousai", 0x2800, 0x2809 },
    { (u8*)"Dhelp", 0x1D00, 0x1D15 },
    { (u8*)"fileselect", 0x2A00, 0x2A19 },
    { (u8*)"gamble1", 0x2B00, 0x2B0F },
    { (u8*)"gamble2", 0x2C00, 0x2C07 },
    { (u8*)"gamble3", 0x2D00, 0x2D0A },
    { (u8*)"gamble4", 0x2E00, 0x2E10 },
    { (u8*)"gamblemasu", 0x2F00, 0x2F04 },
    { (u8*)"help", 0x3000, 0x301B },
    { (u8*)"hiroba", 0x3100, 0x313E },
    { (u8*)"inst_1vs3", 0x3200, 0x322A },
    { (u8*)"inst_2vs2", 0x3300, 0x331F },
    { (u8*)"inst_4player", 0x3400, 0x343C },
    { (u8*)"inst_battle", 0x3500, 0x3517 },
    { (u8*)"inst_duel", 0x3600, 0x3631 },
    { (u8*)"inst_item", 0x3700, 0x3711 },
    { (u8*)"inst_omake", 0x3800, 0x3814 },
    { (u8*)"inst_practice", 0x3900, 0x3919 },
    { (u8*)"item", 0x3A00, 0x3A30 },
    { (u8*)"itemkinopio", 0x3B00, 0x3B09 },
    { (u8*)"itemmasu", 0x3C00, 0x3C32 },
    { (u8*)"itemminikoopa", 0x3D00, 0x3D09 },
    { (u8*)"itemsetumei", 0x3E00, 0x3E13 },
    { (u8*)"kakusiblock", 0x3F00, 0x3F0A },
    { (u8*)"kettou", 0x4000, 0x4007 },
    { (u8*)"keyman", 0x4100, 0x4106 },
    { (u8*)"koopamasu", 0x4200, 0x4222 },
    { (u8*)"last5", 0x4300, 0x4312 },
    { (u8*)"M_P_starlift", 0x4900, 0x491B },
    { (u8*)"M_S_starlift", 0x4A00, 0x4A15 },
    { (u8*)"minigame_book", 0x4400, 0x4443 },
    { (u8*)"minigame_record", 0x4500, 0x450A },
    { (u8*)"minigame_settei", 0x4600, 0x460A },
    { (u8*)"minigame_title", 0x4700, 0x4748 },
    { (u8*)"Mstar", 0x4800, 0x4805 },
    { (u8*)"name", 0x4B00, 0x4B6B },
    { (u8*)"narebox", 0x4C00, 0x4C3C },
    { (u8*)"OPdemo", 0x4D00, 0x4D26 },
    { (u8*)"option", 0x4E00, 0x4E13 },
    { (u8*)"otachara", 0x4F00, 0x4F0D },
    { (u8*)"party_record", 0x5000, 0x5011 },
    { (u8*)"pause", 0x5100, 0x512C },
    { (u8*)"playername", 0x5200, 0x5207 },
    { (u8*)"quizparty_a", 0x5300, 0x533C },
    { (u8*)"quizparty_b", 0x5400, 0x541D },
    { (u8*)"quizparty_c", 0x5500, 0x558F },
    { (u8*)"Room_battle", 0x5600, 0x5619 },
    { (u8*)"Room_freeplay", 0x5700, 0x5729 },
    { (u8*)"Room_gamble", 0x5800, 0x5814 },
    { (u8*)"save", 0x5900, 0x5901 },
    { (u8*)"Sdemo", 0x5A00, 0x5A82 },
    { (u8*)"Sdemo_L", 0x5B00, 0x5B4D },
    { (u8*)"select", 0x5C00, 0x5C03 },
    { (u8*)"soundbox", 0x5D00, 0x5D4B },
    { (u8*)"stariti", 0x5E00, 0x5E0A },
    { (u8*)"starlevel", 0x5F00, 0x5F02 },
    { (u8*)"story_record", 0x6100, 0x612D },
    { (u8*)"storymode", 0x6000, 0x6006 },
    { (u8*)"teresa", 0x6200, 0x6215 },
    { (u8*)"wakarukana", 0x6300, 0x6307 },
    { (u8*)"yakusyoku", 0x6400, 0x642A },
    { (u8*)"", 0xFFFF, 0xFFFF },
};

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
    D_80106500_meschk.quit = 1;
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
    if ((D_80106500_meschk.quit != 0) || (D_800D530C_main != 0)) {
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
        if (D_80106500_meschk.quit != 0) {
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

