#include "common.h"
#include "game/object.h"
#include "math.h"

/* sldebug: the story-mode debug screen (minigame/character unlocks, story chapter, hero and difficulty) */

void func_80105B64_sldebug(omObjData *);
void func_80106124_sldebug(omObjData *);
s32 func_8010612C_sldebug(void);
void func_80106254_sldebug(omObjData *);
void func_80106850_sldebug(void);
void func_801068D4_sldebug(omObjData *);
void func_80106930_sldebug(omObjData *);
s32 func_80050064_main(s32 write);
extern s32 fontcolor;

/* .data (defined at the end of the file) */
extern u16 D_80106960_sldebug;    /* quit */
extern s32 D_80106964_sldebug;
extern u8 D_80106968_sldebug[13]; /* per story chapter: 0 duel, 1 battle, 2 other */
extern s32 D_80106978_sldebug;    /* cursor row */
extern s32 D_8010697C_sldebug;    /* story chapter */
extern s32 D_80106980_sldebug;    /* story settings were touched */
extern s32 D_80106984_sldebug;    /* hero */
extern s32 D_80106988_sldebug;    /* difficulty */
extern s16 D_8010698C_sldebug;    /* show the camera text */

/* .bss */
extern Vec D_80106C10_sldebug; /* camera rotation at reset */
extern f32 D_80106C1C_sldebug; /* zoom at reset */
extern Vec D_80106C20_sldebug; /* camera rotation */
extern Vec D_80106C2C_sldebug; /* centre at reset */

void func_801059A0_sldebug(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x2D);
    omInitObjMan(0x33, 0xA);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0U);
    omAddObj(0x2710, 0, 0, -1, func_801068D4_sldebug);
    HmfLightMaxSet(4);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    D_80106C10_sldebug.x = D_80106C10_sldebug.y = D_80106C10_sldebug.z = 0.0f;
    D_80106C1C_sldebug = 400.0f;
    D_80106C2C_sldebug.x = D_80106C2C_sldebug.z = 0.0f;
    D_80106C2C_sldebug.y = 150.0f;
    gCameraList->fov[0] = 45.0f;
    func_80106850_sldebug();
    omAddObj(0x7D0, 0xA, 0xA, -1, func_80105B64_sldebug);
    omAddObj(0x7D0, 0, 0, -1, func_80106254_sldebug);
    WipeCreateIn(0, 0x10);
    D_800CD280_main = 1;
    func_80050ABC_main();
    HuAudSeqPlay(8);
}

void func_80105B64_sldebug(omObjData *obj) {
    char *storyNames[13] = {
        "STORY NO.00", "STORY NO.01", "STORY NO.02", "STORY NO.03", "STORY NO.04", "STORY NO.05", "STORY NO.06",
        "STORY NO.07", "STORY NO.08", "STORY NO.09", "STORY NO.10", "STORY NO.11", "STORY NO.12",
    };
    char *heroNames[6] = {
        "STORY HERO  MARIO", "STORY HERO  LUIGI", "STORY HERO  PEACH",
        "STORY HERO  YOSHI", "STORY HERO  WARIO", "STORY HERO  DONKEY",
    };
    char *diffNames[4] = { "STORY DIFF  EASY", "STORY DIFF  NORMAL", "STORY DIFF  HARD", "STORY DIFF  VERYHARD" };
    s16 i;

    fontcolor = 0xF;
    print8(0x46, 0x50, "ALL MINIGAME ENABLE");
    print8(0x46, 0x5A, "WLUIGI & DAISY ENABLE");
    print8(0x46, 0x64, storyNames[D_8010697C_sldebug]);
    print8(0x46, 0x6E, heroNames[D_80106984_sldebug]);
    print8(0x46, 0x78, diffNames[D_80106988_sldebug]);
    print8(0x46, 0x82, "WLUIGILAND & REVKUNMAP ENABLE");
    print8(0x46, 0x8C, "EXIT");
    if ((u16)D_800D0590_main[0] & 0x800) {
        HuAudFXPlay(1);
        if (--D_80106978_sldebug < 0) {
            D_80106978_sldebug = 6;
        }
    } else if ((u16)D_800D0590_main[0] & 0x400) {
        HuAudFXPlay(1);
        if (++D_80106978_sldebug >= 7) {
            D_80106978_sldebug = 0;
        }
    } else if ((u16)D_800D0590_main[0] & 0x200) {
        switch (D_80106978_sldebug) {
        case 2:
            HuAudFXPlay(1);
            if (--D_8010697C_sldebug < 0) {
                D_8010697C_sldebug = 12;
            }
            break;
        case 3:
            HuAudFXPlay(1);
            if (--D_80106984_sldebug < 0) {
                D_80106984_sldebug = 5;
            }
            break;
        case 4:
            HuAudFXPlay(1);
            if (--D_80106988_sldebug < 0) {
                D_80106988_sldebug = 3;
            }
            break;
        }
    } else if ((u16)D_800D0590_main[0] & 0x100) {
        switch (D_80106978_sldebug) {
        case 2:
            HuAudFXPlay(1);
            if (++D_8010697C_sldebug >= 13) {
                D_8010697C_sldebug = 0;
            }
            break;
        case 3:
            HuAudFXPlay(1);
            if (++D_80106984_sldebug >= 6) {
                D_80106984_sldebug = 0;
            }
            break;
        case 4:
            HuAudFXPlay(1);
            if (++D_80106988_sldebug >= 4) {
                D_80106988_sldebug = 0;
            }
            break;
        }
    } else if (D_800D5558_main[0] & 0x8000) {
        if (func_8010612C_sldebug() != 0) {
            if (D_80106980_sldebug != 0) {
                GwStory.unk0 = D_8010697C_sldebug;
                /* i == 12 writes unk3[12], which is unkF */
                for (i = 0; i < 13; i++) {
                    if (i < D_8010697C_sldebug) {
                        GwStory.unk3[i] = 4;
                    } else {
                        GwStory.unk3[i] = 0;
                    }
                }
                if (D_8010697C_sldebug == 12) {
                    GwStory.unkF = 4;
                }
                GwStory.unk2 = D_80106988_sldebug;
                GwStory.unk1 = D_80106984_sldebug;
                _ClearFlag(0x28);
                _SetFlag(0x18);
                GwSystem.playMode = 4;
                if (D_80106968_sldebug[D_8010697C_sldebug] == 0) {
                    D_80106964_sldebug = 2;
                    GwSystem.playMode = 5;
                } else if (D_80106968_sldebug[D_8010697C_sldebug] == 1) {
                    D_80106964_sldebug = 0x4000;
                    GwSystem.playMode |= 2;
                } else {
                    D_80106964_sldebug = 4;
                }
                func_8005035C_main(1);
            } else {
                func_80050064_main(1);
            }
            D_80106960_sldebug = 1;
            obj->func = func_80106124_sldebug;
        }
        return;
    }
    print8(0x3C, D_80106978_sldebug * 10 + 0x50, ">");
}

void func_80106124_sldebug(omObjData *obj) {
}

/* the A press on the cursor row; 1: leave the screen */
s32 func_8010612C_sldebug(void) {
    s16 i;

    HuAudFXPlay(2);
    switch (D_80106978_sldebug) {
    case 0:
        _SetFlag(0x1D);
        if ((u16)D_800CDA7C_main[0] & 0x8000) {
            for (i = 0; i < 0x48; i++) {
                GWMgUnlockSet(i);
            }
        } else {
            for (i = 0; i < 0x48; i += 3) {
                GWMgUnlockSet(i);
            }
        }
        _SetFlag(0x1E);
        _SetFlag(0x1F);
        break;
    case 1:
        _SetFlag(0x2E);
        _SetFlag(0x2F);
        break;
    case 2:
    case 3:
    case 4:
        D_80106980_sldebug = 1;
        break;
    case 5:
        _SetFlag(0x30);
        _SetFlag(0x31);
        break;
    case 6:
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/sldebug/3D76C0", func_80106254_sldebug);

void func_80106850_sldebug(void) {
    CRot = D_80106C10_sldebug;
    D_80106C20_sldebug = CRot;
    CZoom = D_80106C1C_sldebug;
    Center = D_80106C2C_sldebug;
}

void func_801068D4_sldebug(omObjData *obj) {
    if (D_80106960_sldebug != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 8);
        obj->func = func_80106930_sldebug;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106930_sldebug(omObjData *obj) {
    if (WipeStatGet() == 0) {
        omOvlGotoEx(0x58, 0, 0x81);
    }
}
