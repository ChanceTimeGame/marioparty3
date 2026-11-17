#include "mgenter.h"

void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);

/* .data (0x46CB90) */
f32 D_80109AA0_mgenter = 115.0f; /* setting card y */
u16 D_80109AA4_mgenter = 0;
s16 D_80109AA6_mgenter = 0;

void func_801059D0_mgenter(void) {
    s16 n;
    void (*func)(void);

    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    func_8005A6B0_main();
    func_8004A208_main();
    omAddObj(0x2710, 0, 0, -1, func_80108934_mgenter);
    HmfLightMaxSet(1);
    D_80109B78_mgenter = 8000.0f;
    D_80109AB0_mgenter = 45.0f;
    D_80109B64_mgenter = 80.0f;
    CRot.x = 354.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2240.0f;
    Center.x = 0.0f;
    Center.y = 260.0f;
    Center.z = 13.0f;
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    omPrcSetStatBit(omAddPrcObj(func_80109020_mgenter, 0x1100, 0x800, 0), 0xA0);
    WipeCreateIn(0xFF, 0x10);
    D_800CD280_main = 1;
    func_8001F38C_main(0xFF, 0xFF, 0xFF);
    D_80109B74_mgenter = D_800D1F36_main;
    D_80109B7C_mgenter = 1;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109B2A_mgenter = GwSystem.minigame_index - 1;
    n = (D_800A6D40_main[D_80109B2A_mgenter].unk6 & 0x3800) >> 11;
    D_80109B2E_mgenter = n + 1;
    if (D_80109B2E_mgenter >= 2) {
        D_80109B2E_mgenter = n;
    }
    if (D_80109B2A_mgenter == 0x46) {
        func = func_80105CD8_mgenter;
    } else if (D_80109B2A_mgenter == 0x1E) {
        func = func_801079B4_mgenter;
    } else {
        func = func_80106294_mgenter;
    }
    omAddPrcObj(func, 0x3F00, 0x2000, 0);
    if (D_800D1FE0_main != 0) {
        GwSystem.show_minigame_explanations = 1;
    } else {
        D_800D1FE0_main++;
    }
    _SetFlag(0xD);
    HuAudSeqPlay(8);
}

void func_80105C60_mgenter(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    omOvlHisChg(0, 0x68, 0, 4);
    omOvlCallEx(0x70, 0, 2);
    _SetFlag(0xD);
    D_800D1FE0_main++;
}

/* minigame 0x46: pick a setting (D_80109B2C_mgenter), then one of three options (D_80109B32_mgenter) */
void func_80105CD8_mgenter(void) {
    s16 size[2];
    s16 win;
    s32 ok;

    D_80109B2C_mgenter = D_800A11E6_main;
    if (D_800A11E6_main < 0) {
        D_80109B2C_mgenter = 0;
    }
    D_80109B30_mgenter = 0;
    D_80109B28_mgenter = -1;
    omAddPrcObj(func_80108590_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_8010677C_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80107F0C_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80106BD0_mgenter, 0x3F00, 0x800, 0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    D_80109B26_mgenter = 0;
    HuPrcSleep(0xA);
    func_80060394_main(3, size, 0x4600, 0x4601, 0x4603);
    win = func_80061188_main(-1, (0x140 - size[0]) / 2, 0xB4, size[0], size[1], 0);
    func_8005BDFC_main(win, 0);
    func_80061388_main(win);
    D_80109B32_mgenter = 0;
    while (1) {
        func_8005B43C_main(win, 0x4600, -1, -1);
        while (func_8005E0C0_main(win) != 0) {
            HuPrcVSleep();
        }
        func_80108560_mgenter(0x3C, 0x6E, 0x104, 0x6E);
        D_80109B22_mgenter = 1;
        while (1) {
            func_801098D8_mgenter();
            if (D_800CBB6E_main[D_80109B74_mgenter] > 0x1E || (D_800D5558_main[D_80109B74_mgenter] & 1)) {
                HuAudFXPlay(1);
                D_80109B30_mgenter = 1;
                D_80109B22_mgenter = 0;
                HuPrcSleep(0xA);
                D_80109B22_mgenter = 1;
            } else if (D_800CBB6E_main[D_80109B74_mgenter] < -0x1E || (D_800D5558_main[D_80109B74_mgenter] & 2)) {
                HuAudFXPlay(1);
                D_80109B30_mgenter = -1;
                D_80109B22_mgenter = 0;
                HuPrcSleep(0xA);
                D_80109B22_mgenter = 1;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x8000) {
                HuAudFXPlay(2);
                D_800A11E6_main = D_80109B2C_mgenter;
                D_800CE20A_main = D_80109B2C_mgenter;
                break;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x4000) {
                HuAudFXPlay(4);
                D_800A11E6_main = -1;
                D_80109B7C_mgenter = 0;
                D_80109AA4_mgenter = 1;
                D_80109AA6_mgenter = 1;
                while (1) {
                    HuPrcVSleep();
                }
            }
            HuPrcVSleep();
        }
        D_80109B22_mgenter = 0;
        D_80109B26_mgenter = 1;
        D_80109B28_mgenter = 0;
        HuPrcSleep(0xA);
        func_80108560_mgenter(0x50, 0x9B, 0xF0, 0x9B);
        D_80109B22_mgenter = 1;
        func_8005B43C_main(win, 0x4603, -1, -1);
        while (func_8005E0C0_main(win) != 0) {
            HuPrcVSleep();
        }
        while (1) {
            func_801098D8_mgenter();
            if (D_800CBB6E_main[D_80109B74_mgenter] > 0x1E || (D_800D5558_main[D_80109B74_mgenter] & 1)) {
                HuAudFXPlay(1);
                if (++D_80109B32_mgenter >= 3) {
                    D_80109B32_mgenter = 0;
                }
                D_80109B22_mgenter = 0;
                HuPrcSleep(0xA);
                D_80109B22_mgenter = 1;
            } else if (D_800CBB6E_main[D_80109B74_mgenter] < -0x1E || (D_800D5558_main[D_80109B74_mgenter] & 2)) {
                HuAudFXPlay(1);
                if (--D_80109B32_mgenter < 0) {
                    D_80109B32_mgenter = 2;
                }
                D_80109B22_mgenter = 0;
                HuPrcSleep(0xA);
                D_80109B22_mgenter = 1;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x8000) {
                HuAudFXPlay(2);
                ok = 1;
                break;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x4000) {
                HuAudFXPlay(4);
                ok = 0;
                break;
            }
            HuPrcVSleep();
        }
        if (ok != 0) {
            break;
        }
        D_80109B22_mgenter = 0;
        D_80109B26_mgenter = 2;
        D_80109B28_mgenter = 1;
        HuPrcSleep(0xA);
    }
    GwPlayer[0].group = 0;
    D_800CB890_main.unk04 = D_80109B32_mgenter;
    func_8005F364_main(win);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* every other minigame: the instruction card, then A to start or B to go back */
void func_80106294_mgenter(void) {
    s16 size[2];
    s16 win;
    s16 i;
    s32 spr;
    s16 btn;

    D_800A11E6_main = -1;
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    spr = func_801095F4_mgenter();
    func_801096EC_mgenter(D_800A6D40_main[D_80109B2A_mgenter].unk6 & 0x7FF);
    func_8000BBD4_main(spr, 0, -0x64);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    for (i = 0; i < 11; i++) {
        func_8000BBD4_main(spr, sindf(i * 9.0f) * 240.0f - 80.0f, 0x73);
        HuPrcVSleep();
    }
    func_80060394_main(1, size, 0x4607);
    win = func_80061188_main(-1, (0x140 - size[0]) / 2, 0xB4, size[0], size[1], 0);
    func_8005BDFC_main(win, 0);
    func_80061388_main(win);
    func_8005B43C_main(win, 0x4607, -1, -1);
    while (func_8005E0C0_main(win) != 0) {
        HuPrcVSleep();
    }
    while (1) {
        btn = D_800D5558_main[D_80109B74_mgenter];
        if (btn & 0x8000) {
            HuAudFXPlay(2);
            break;
        }
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            D_80109B7C_mgenter = 0;
            D_80109AA4_mgenter = 1;
            D_80109AA6_mgenter = 1;
            while (1) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    func_801087C0_mgenter();
    func_8005F364_main(win);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* the minigame's name, dropped in from the top */
#ifdef NON_MATCHING
void func_80106568_mgenter(void) {
    MgEntMes mes;
    f32 y;
    s16 slot;
    s16 i;
    u8 *str;

    str = func_800364DC_main((void *)(D_80109B2A_mgenter + 0x4700));
    func_80106710_mgenter(str);
    slot = func_8003A308_main((char *)&mes, (char *)str, 0, -1, -1);
    func_80054904_main(mes.strGId[slot], 0, 0, -0x64);
    func_800365E8_main(str);
    D_80109B24_mgenter = -1;
    y = 44.0f;
    if (D_80109B2E_mgenter != 1) {
        y = 28.0f;
    }
    while (1) {
        if (D_80109B24_mgenter == 0) {
            for (i = 0; i < 11; i++) {
                func_80054904_main(mes.strGId[slot], 0, sindf(i * 9.0f) * 160.0f, y);
                HuPrcVSleep();
            }
            D_80109B24_mgenter = -1;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106568_mgenter);
#endif

/* drops the characters a GAMEMES string cannot draw (keeps >= 0x20, 0x10, 0x11) */
void func_80106710_mgenter(u8 *str) {
    u8 *dst = str;
    u8 *src = str;

    while (*src != 0) {
        *dst = *src;
        if (*src >= 0x20 || *src == 0x10 || *src == 0x20 || *src == 0x11) {
            dst++;
        }
        src++;
    }
    *dst = 0;
}

// FPU register allocation (masked 0): the float-to-s16 slide positions land in other $f registers
/* the three option names (0x4608..), slid sideways when D_80109B30_mgenter steps the cursor */
#ifdef NON_MATCHING
void func_8010677C_mgenter(void) {
    MgEntMes mes[3];
    char buf[32];
    s16 i;
    s16 j;
    s16 n;
    s16 len;
    s16 slot;
    s16 cur;
    u8 *str;

    cur = D_80109B2C_mgenter;
    for (i = 0; i < 3; i++) {
        str = func_800364DC_main((void *)(i + 0x4608));
        len = strlen((char *)str);
        n = 0;
        for (j = 0; j <= len; j++) {
            if (str[j] < 0x30 && str[j] != 0x20) {
                continue;
            }
            buf[n++] = str[j];
        }
        buf[n] = 0;
        slot = func_8003A308_main((char *)&mes[i], buf, 0, -1, -1);
        func_80054904_main(mes[i].strGId[slot], 0, -0x154, 0x34);
        mes[i].unk08 = n;
        func_800365E8_main(str);
    }
    while (1) {
        if (D_80109B24_mgenter == 0) {
            for (i = 0; i < 11; i++) {
                func_80054904_main(mes[cur].strGId[slot], 0, (s32)(sindf(i * 9.0f) * 160.0f), 0x34);
                HuPrcVSleep();
            }
        }
        if (D_80109B30_mgenter != 0) {
            for (i = 1; i < 6; i++) {
                func_80054904_main(mes[cur].strGId[slot], 0,
                                   (1.0f - cosdf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f, 0x34);
                HuPrcVSleep();
            }
            cur += D_80109B30_mgenter;
            if (cur >= 3) {
                cur = 0;
            }
            if (cur < 0) {
                cur = 2;
            }
            for (i = 1; i < 6; i++) {
                func_80054904_main(mes[cur].strGId[slot], 0,
                                   -(1.0f - sindf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f, 0x34);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_8010677C_mgenter);
#endif

/* a part of an HMF model (HmfData.unk60[], 0x68 bytes); 0x24: shown with the parent's flags */
typedef struct MgEntHmfPart {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0x42];
} MgEntHmfPart;

// register allocation (masked 103): retail keeps prev in $fp, this spills it to the stack (frame +8)
/* minigame 0x46: three character models on a turntable and the option name under them; D_80109B28_mgenter
   asks for a fade (1) or to face the chosen option (0), D_80109B32_mgenter turns the table */
#ifdef NON_MATCHING
void func_80106BD0_mgenter(void) {
    s16 models[3];
    MgEntMes mes[3];
    char buf[32];
    u8 mesNo[3] = { 1, 0, 2 };
    u8 chr[3] = { 0, 2, 1 };
    HmfData *hmf;
    f32 ang;
    f32 dir;
    f32 base;
    f32 t;
    s16 i;
    s16 j;
    s16 n;
    s16 len;
    s16 model;
    s16 prev;
    u8 *str;

    func_8001EF24_main(500, 550, 0xFF, 0xFF, 0xFF);
    for (i = 0; i < 3; i++) {
        model = models[i] = func_8000B108_main(chr[i] | 0x670000, 0x2BD);
        func_8001C258_main(model, 4, 4);
        func_8001C814_main(model, 1, 1);
        func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02 / 2);
        ang = i * 120;
        Hu3DModelPosSet(model, sindf(ang) * 500.0f, 0.0f, cosdf(ang) * 500.0f);
        hmf = HmfModelData[model].hmf;
        ((MgEntHmfPart *)hmf->unk60)[func_8002C834_main(hmf, "atama_2")].unk24 = 1;
        HmfModelData[model].rot.x = 20.0f;
    }
    for (i = 0; i < 3; i++) {
        str = func_800364DC_main((void *)(mesNo[i] + 0x4604));
        len = strlen((char *)str);
        n = 0;
        for (j = 0; j <= len; j++) {
            if (str[j] >= 0x30) {
                buf[n++] = str[j];
            }
        }
        buf[n] = 0;
        func_80054904_main(mes[i].strGId[func_8003A308_main((char *)&mes[i], buf, 0, -1, -1)], 0, 0xA0, 0x82);
        mes[i].unk08 = n;
        for (j = 0; j < n;) {
            j++;
            func_80055458_main(mes[i].strGId[0], j, 0);
        }
        func_800365E8_main(str);
    }
    base = 0.0f;
    prev = D_80109B32_mgenter;
    t = 0.0f;
    while (1) {
        switch (D_80109B28_mgenter) {
            case 0:
                base = D_80109B32_mgenter * 120;
                prev = D_80109B32_mgenter;
                for (i = 0; i < 3; i++) {
                    ang = i * 120 + base;
                    Hu3DModelPosSet(models[i], sindf(ang) * 500.0f, 0.0f, cosdf(ang) * 500.0f);
                }
                for (i = 0; i < 3; i++) {
                    if (HmfModelData[models[i]].pos.z > 0.0f) {
                        func_8001C258_main(models[i], 4, 0);
                    } else {
                        func_8001C258_main(models[i], 4, 4);
                    }
                }
                for (i = 0; i < 6; i++) {
                    for (j = 0; j < mes[D_80109B32_mgenter].unk08; j++) {
                        func_80055458_main(mes[D_80109B32_mgenter].strGId[0], j + 1, i * 51.0f);
                    }
                    HuPrcVSleep();
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    func_8001C258_main(models[i], 4, 4);
                }
                func_8001C258_main(models[D_80109B32_mgenter], 4, 0);
                for (i = 0; i < 6; i++) {
                    for (j = 0; j < mes[D_80109B32_mgenter].unk08; j++) {
                        func_80055458_main(mes[D_80109B32_mgenter].strGId[0], j + 1, 255.0f - i * 51.0f);
                    }
                    HuPrcVSleep();
                }
                HuPrcSleep(5);
                for (i = 0; i < 3; i++) {
                    func_8001C258_main(models[i], 4, 4);
                }
        }
        D_80109B28_mgenter = -1;
        if (prev != D_80109B32_mgenter) {
            dir = -func_80089750_main(prev - D_80109B32_mgenter);
            if ((D_80109B32_mgenter == 2 && prev == 0) || (D_80109B32_mgenter == 0 && prev == 2)) {
                dir = -dir;
            }
            for (i = 0; i < 3; i++) {
                func_8001C258_main(models[i], 4, 0);
            }
            for (i = 1; i < 11; i++) {
                for (j = 0; j < 3; j++) {
                    ang = j * 120 + base + i * 12 * dir;
                    Hu3DModelPosSet(models[j], sindf(ang) * 500.0f, 0.0f, cosdf(ang) * 500.0f);
                    func_8008A2A0_main(HmfModelData[models[j]].mtx, t);
                }
                ang = i * 25;
                for (j = 0; j < mes[prev].unk08; j++) {
                    func_80055458_main(mes[prev].strGId[0], j + 1, 255.0f - ang);
                }
                for (j = 0; j < mes[D_80109B32_mgenter].unk08; j++) {
                    func_80055458_main(mes[D_80109B32_mgenter].strGId[0], j + 1, ang);
                }
                t += 3.0f;
                HuPrcVSleep();
            }
            prev = D_80109B32_mgenter;
            for (i = 0; i < 3; i++) {
                if (HmfModelData[models[i]].pos.z > 0.0f) {
                    func_8001C258_main(models[i], 4, 0);
                } else {
                    func_8001C258_main(models[i], 4, 4);
                }
            }
            base = D_80109B32_mgenter * 120;
        }
        for (i = 0; i < 3; i++) {
            func_8008A2A0_main(HmfModelData[models[i]].mtx, t);
        }
        t += 3.0f;
        HuPrcVSleep();
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC0_mgenter);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC4_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106BD0_mgenter);
#endif

// the A/B tests: retail loads the button word once (lhu and lh), this reloads it for B (masked 15)
/* minigame 0x1E: the instruction card, then a target number (100..1000, by 100) picked with the C buttons */
#ifdef NON_MATCHING
void func_801079B4_mgenter(void) {
    s16 size[2];
    u8 buf[24];
    s16 win0;
    s16 win1;
    s16 i;
    s32 spr;
    s16 value;
    s16 step;
    u16 btn;

    D_800A11E6_main = -1;
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    spr = func_801095F4_mgenter();
    func_801096EC_mgenter(D_800A6D40_main[D_80109B2A_mgenter].unk6 & 0x7FF);
    func_8000BBD4_main(spr, 0, -0x64);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    for (i = 0; i < 11; i++) {
        func_8000BBD4_main(spr, sindf(i * 9.0f) * 240.0f - 80.0f, 0x64);
        HuPrcVSleep();
    }
    func_80060394_main(1, size, 0x4601);
    win0 = func_80061188_main(-1, (0x140 - size[0]) / 2, 0xB4, size[0], size[1], 0);
    for (i = 0; i < 4; i++) {
        buf[i] = 0xA0;
    }
    buf[i] = 0;
    func_8006022C_main((u32)buf, 0);
    func_80060394_main(1, size, 0x4602);
    win1 = func_80061188_main(-1, (0x140 - size[0]) / 2, 0x9B, size[0], size[1], 0);
    func_8005BDFC_main(win0, 0);
    func_80061388_main(win0);
    func_8005B43C_main(win0, 0x4601, -1, -1);
    value = 100;
    func_80107E5C_mgenter(win1, 100, buf);
    func_8005B43C_main(win1, 0x4602, -1, -1);
    while (func_8005E0C0_main(win1) != 0) {
        HuPrcVSleep();
    }
    func_80061388_main(win1);
    while (1) {
        btn = D_800D0590_main[D_80109B74_mgenter];
        if (btn & 0x800) {
            step = 100;
        } else if (btn & 0x400) {
            step = -100;
        } else {
            step = 0;
        }
        if (value == 1000 && step > 0) {
            value = 100;
        } else if (value + step >= 1000) {
            value = 1000;
        } else if (value + step < 100) {
            value = 1000;
        } else {
            value += step;
        }
        if (step != 0) {
            func_80107E5C_mgenter(win1, value, buf);
            func_8005B43C_main(win1, 0x4602, -1, -1);
        }
        if ((s16)D_800D5558_main[D_80109B74_mgenter] & 0x8000) {
            HuAudFXPlay(2);
            D_800CB890_main.unk04 = value;
            break;
        }
        if (D_800D5558_main[D_80109B74_mgenter] & 0x4000) {
            HuAudFXPlay(4);
            D_80109B7C_mgenter = 0;
            D_80109AA4_mgenter = 1;
            D_80109AA6_mgenter = 1;
            while (1) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    func_801087C0_mgenter();
    func_8005F364_main(win0);
    func_8005F364_main(win1);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801079B4_mgenter);
#endif

/* a number into a window: four digits, a leading zero blanked */
void func_80107E5C_mgenter(s16 win, s16 value, u8 *buf) {
    s16 i;

    sprintf((char *)buf, "%04d", value);
    if (buf[0] == '0') {
        buf[0] = 0x1A;
    }
    for (i = 0; i < 4; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            buf[i] += 0x70;
        }
    }
    func_8005B6BC_main(win, (u32)buf, 0);
}

// FPU register allocation (masked 0): the float-to-s16 arguments land in other $f registers
/* minigame 0x46: the setting's instruction card; zooms out to the top (1) or back (2) with the menu step,
   and slides sideways when D_80109B30_mgenter steps the setting */
#ifdef NON_MATCHING
void func_80107F0C_mgenter(void) {
    s32 spr;
    s16 i;
    f32 s;
    f32 scale;
    f32 d;

    D_80109B24_mgenter = -1;
    spr = func_801095F4_mgenter();
    func_801096EC_mgenter((D_800A6D40_main[D_80109B2A_mgenter].unk6 & 0x7FF) + D_80109B2C_mgenter * 2);
    func_8000BB94_main(spr);
    D_80109B26_mgenter = -1;
    while (1) {
        switch (D_80109B26_mgenter) {
            case 0:
                func_8000BB54_main(spr);
                for (i = 0; i < 11; i++) {
                    func_8000BBD4_main(spr, sindf(i * 9.0f) * 240.0f - 80.0f, D_80109AA0_mgenter);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
            case 1:
                for (i = 1; i < 11; i++) {
                    s = sindf(i * 9.0f);
                    D_80109AA0_mgenter = 115.0f - s * 35.0f;
                    func_8000BBD4_main(spr, 0xA0, D_80109AA0_mgenter);
                    scale = 1.0f - s * 0.2f;
                    func_8000BE5C_main(spr, scale, scale);
                    d = (1.0f - s) * 100.0f;
                    func_8001EF24_main(970.0f - d, 975.0f - d, 0xFF, 0xFF, 0xFF);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
            case 2:
                for (i = 1; i < 11; i++) {
                    s = 1.0f - sindf(i * 9.0f);
                    D_80109AA0_mgenter = 115.0f - s * 35.0f;
                    func_8000BBD4_main(spr, 0xA0, D_80109AA0_mgenter);
                    scale = 1.0f - s * 0.2f;
                    func_8000BE5C_main(spr, scale, scale);
                    d = (1.0f - s) * 100.0f;
                    func_8001EF24_main(970.0f - d, 975.0f - d, 0xFF, 0xFF, 0xFF);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
        }
        if (D_80109B30_mgenter != 0) {
            for (i = 1; i < 6; i++) {
                func_8000BBD4_main(spr, (1.0f - cosdf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f,
                                   D_80109AA0_mgenter);
                HuPrcVSleep();
            }
            D_80109B2C_mgenter += D_80109B30_mgenter;
            if (D_80109B2C_mgenter >= D_80109B2E_mgenter) {
                D_80109B2C_mgenter = 0;
            }
            if (D_80109B2C_mgenter < 0) {
                D_80109B2C_mgenter = D_80109B2E_mgenter - 1;
            }
            func_801096EC_mgenter((D_800A6D40_main[D_80109B2A_mgenter].unk6 & 0x7FF) + D_80109B2C_mgenter * 2);
            for (i = 1; i < 6; i++) {
                func_8000BBD4_main(spr, -(1.0f - sindf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f,
                                   D_80109AA0_mgenter);
                HuPrcVSleep();
            }
            D_80109B30_mgenter = 0;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80107F0C_mgenter);
#endif

/* moves the two cursor arrows (func_80108590_mgenter) */
void func_80108560_mgenter(s16 x0, s16 y0, s16 x1, s16 y1) {
    D_80109B34_mgenter = x0;
    D_80109B36_mgenter = x1;
    D_80109B38_mgenter = y0;
    D_80109B3A_mgenter = y1;
    D_80109B20_mgenter = 1;
}

/* the two cursor arrows: fade in or out with D_80109B22_mgenter, move on D_80109B20_mgenter */
#ifdef NON_MATCHING
void func_80108590_mgenter(void) {
    s16 file0;
    s16 file1;
    s16 spr0;
    s16 spr1;
    s16 alpha;
    s16 old;
    s32 fading;
    s32 step;
    s8 shown;

    shown = 0;
    fading = 0;
    D_80109B22_mgenter = 0;
    D_80109B20_mgenter = 0;
    file0 = func_8000B838_main(0x140012);
    file1 = func_8000B838_main(0x140013);
    spr0 = InitEspriteSlot(file0, 0, 1);
    spr1 = InitEspriteSlot(file1, 0, 1);
    func_8000BCC8_main(spr0, 0x4800);
    func_8000BCC8_main(spr1, 0x4800);
    func_8000BBD4_main(spr0, 0xA0, 0x78);
    func_8000BBD4_main(spr1, 0xA0, 0x78);
    func_8000BB94_main(spr0);
    func_8000BB94_main(spr1);
    alpha = 0;
    step = 0;
    while (1) {
        HuPrcVSleep();
        if (shown != D_80109B22_mgenter) {
            shown = D_80109B22_mgenter;
            fading = 1;
            step = -0x3F;
            if (D_80109B22_mgenter != 0) {
                step = 0x3F;
            }
        }
        if (fading != 0) {
            old = alpha;
            alpha += step;
            if (alpha >= 0xFF) {
                fading = 0;
                alpha = 0xFF;
            } else if (alpha <= 0) {
                fading = 0;
                alpha = 0;
            }
            if (alpha != 0) {
                if (old == 0) {
                    func_8000BB54_main(spr0);
                    func_8000BB54_main(spr1);
                }
                func_8000BBFC_main(spr0, alpha);
                func_8000BBFC_main(spr1, alpha);
            } else {
                func_8000BB94_main(spr0);
                func_8000BB94_main(spr1);
            }
        }
        if (D_80109B20_mgenter != 0) {
            func_8000BBD4_main(spr0, D_80109B34_mgenter, D_80109B38_mgenter);
            func_8000BBD4_main(spr1, D_80109B36_mgenter, D_80109B3A_mgenter);
            D_80109B20_mgenter = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80108590_mgenter);
#endif

/* player groups for a 1-vs-3 (type 1) or 2-vs-2 (type 2) minigame */
#ifdef NON_MATCHING
void func_801087C0_mgenter(void) {
    s32 type;
    s16 i;

    type = D_800A6D44_main[D_80109B2A_mgenter].minigameType;
    if (type == 1 || type == 2) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].group >= 2) {
                break;
            }
        }
        if (i != 4) {
            if (type == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].group != 0) {
                        GwPlayer[i].group = 1;
                    }
                }
                return;
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].group < 2) {
                    GwPlayer[i].group = 0;
                } else {
                    GwPlayer[i].group = 1;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801087C0_mgenter);
#endif

void func_80108934_mgenter(omObjData *obj) {
    if (D_80109AA4_mgenter != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 8);
        if (D_80109AA6_mgenter == 0) {
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = func_801089A0_mgenter;
    }
}

void func_801089A0_mgenter(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80109820_mgenter();
        func_8005F524_main();
        switch (D_80109B7C_mgenter) {
            case 0:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
                break;
            case 1:
                omOvlGotoEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
                break;
        }
    }
}
