#include "common.h"
#include "ovl_81.h"

/* Duel telops (player banner, last-turns banner, minigame type) and the guide camera; a duplicate of
   F5E80.c's MBTelop* / MBGuide* in ovl_80_shared_board. */

typedef struct DuelTelopData {
    s32 state;
    s32 playerNo;
    char unk_08[8];
} DuelTelopData; // sizeof 0x10

typedef struct DuelTelopSprIds {
    u8 unk_00[10];
} DuelTelopSprIds;

typedef struct DuelTelopChrFiles {
    u16 unk_00[8];
} DuelTelopChrFiles;

extern char* D_80100FC0_name_81[];  /* minigame type telop strings */
extern s8 D_80100FC8_name_81[];     /* last sprite of each telop string */
extern s8 D_80100FCC_name_81[];     /* x offset of each telop string */
extern char D_80102C30_name_81[0x20];
extern s16 D_80102C50_name_81[];
extern s16 D_80102CA4_name_81;
extern u8 D_80102CA6_name_81;
extern s16 D_80102CA8_name_81;
extern s16 D_80102CAA_name_81[2];
extern omObjData* D_80102CB0_name_81;
extern omObjData* D_80102CB4_name_81;
extern s8 D_80102CB8_name_81;
extern s16 D_80102CBA_name_81[2];
extern s16 D_80102CBE_name_81[2];
extern s32 D_80102CC4_name_81;
extern s32 D_80102CC8_name_81;

void func_800E02B4_name_81(s32);

const char D_80102450_name_81[] = "\x03%2d\x08";

const char D_80102458_name_81[] = "  HAPPENING!  ";

const char D_80102468_name_81[] = "  1 VS 1 GAME ";

const DuelTelopSprIds D_80102478_name_81 = { { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 } };

const DuelTelopChrFiles D_80102484_name_81 = { { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 } };

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102494_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024A0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024D0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102500_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102520_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102540_name_81);

void func_800E2870_name_81(void) {
    D_80102CA4_name_81 = -1;
    D_80102CA6_name_81 = 0;
    D_80102CA8_name_81 = -1;
    D_80102CAA_name_81[0] = D_80102CAA_name_81[1] = -1;
    D_80102CB0_name_81 = NULL;
    D_80102CB4_name_81 = NULL;
}

void func_800E28B0_name_81(void) {
    if (D_80102CA6_name_81 & 0x20) {
        func_8003B128_main(D_80102C30_name_81);
    }
    if (D_80102CA6_name_81 & 0x10) {
        HuSprGrpKill(D_80102CA8_name_81);
        HuSprKill(D_80102CAA_name_81[0]);
        HuSprKill(D_80102CAA_name_81[1]);
    }
    if (D_80102CB0_name_81 != NULL) {
        omDelObj(D_80102CB0_name_81);
        D_80102CB0_name_81 = NULL;
    }
    if (D_80102CB4_name_81 != NULL) {
        omDelObj(D_80102CB4_name_81);
        D_80102CB4_name_81 = NULL;
    }
    D_80102CA6_name_81 &= ~(0x20 | 0x10);
}

void func_800E2978_name_81(omObjData* obj) {
    s32 i;
    f32 scale;

    switch (obj->work[0]) {
    case 0:
        obj->rot.x += 30.0f;
        scale = sindf(obj->rot.x) * 0.5f + 1.0f;
        obj->scale.x = scale;
        HuSprScaleSet(D_80102CBA_name_81[0], 0, scale, scale);
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        break;
    case 1:
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            if (D_80102CBE_name_81[i] != -1) {
                HuSprKill(D_80102CBE_name_81[i]);
            }
            if (D_80102CBA_name_81[i] != -1) {
                HuSprGrpKill(D_80102CBA_name_81[i]);
            }
        }
        D_80102CB4_name_81 = NULL;
        omDelObj(obj);
        break;
    }
}

void func_800E2AD0_name_81(omObjData* arg0) {
    s32 i;

    if (arg0->rot.y > 0.0f) {
        arg0->rot.y = arg0->rot.y - 1.0f;
    }

    switch (arg0->work[0]) {
    case 0:
        arg0->scale.x += 0.2f;
        HuSprScaleSet(D_80102CA8_name_81, 0, arg0->scale.x, arg0->scale.x);
        if (arg0->scale.x >= 1.0f) {
            arg0->work[0] = 1;
            arg0->work[1] = 0xC;
            return;
        }
        break;

    case 1:
        if (arg0->work[3] == 6) {
            arg0->work[1]--;
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[i].stat & 1)) {
                    break;
                }
            }
            if (i != 4) {
                for (i = 0; i < 4; i++) {
                    if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                        arg0->work[0] = 2;
                    }
                }
            } else if (arg0->work[1] == 0) {
                arg0->work[0] = 2;
            }
            if (arg0->work[2] == 0) {
                func_80054904_main(D_80102CA8_name_81, 0, 0xA0, (s32)(sindf(arg0->rot.x) * 5.0f + 0.5f) + 0x78);
                arg0->rot.x += 10.0f;
                if (arg0->rot.x >= 360.0f) {
                    arg0->rot.x -= 360.0f;
                }
            } else {
                arg0->work[2]--;
            }
            return;
        }

        if (arg0->work[1] != 0) {
            arg0->work[1]--;
            return;
        }

        if (!(GwPlayer[arg0->work[3]].stat & 1)) {
            if (!(arg0->rot.y <= 0.0f)) {
                if (!(D_800D5558_main[GwPlayer[arg0->work[3]].pad] & (A_BUTTON | B_BUTTON))) {
                    return;
                }
            }
        }
        arg0->work[0] = 2;
        return;

    case 2:
        arg0->scale.x += 0.2f;
        HuSprScaleSet(D_80102CA8_name_81, 0, arg0->scale.x, arg0->scale.x);
        func_80055458_main(D_80102CA8_name_81, 0, (2.0f - arg0->scale.x) * 256.0f);
        if (arg0->scale.x >= 2.0f) {
            arg0->work[0] = 3;
            return;
        }
        break;
    case 3:
        HuSprGrpKill(D_80102CA8_name_81);
        HuSprKill(D_80102CAA_name_81[0]);
        D_80102CA8_name_81 = -1;
        D_80102CAA_name_81[0] = -1;
        if (D_80102CB4_name_81 != NULL) {
            for (i = 0; i < 2; i++) {
                if (D_80102CBE_name_81[i] != -1) {
                    HuSprKill(D_80102CBE_name_81[i]);
                }
                if (D_80102CBA_name_81[i] != -1) {
                    HuSprGrpKill(D_80102CBA_name_81[i]);
                }
            }
            omDelObj(D_80102CB4_name_81);
            D_80102CB4_name_81 = NULL;
        }
        D_80102CB0_name_81 = NULL;
        omDelObj(arg0);
        break;
    }
}

void func_800E2F84_name_81(void) {
    D_80102CB8_name_81 = 1;
}

void func_800E2F94_name_81(omObjData* obj) {
    s32 i;

    if (obj->work[2] != 0) {
        obj->work[2]--;
        return;
    }

    obj->scale.x += 0.05f;
    if (obj->scale.x >= 1.0f) {
        obj->scale.x = 1.0f;
        obj->rot.z += 20.0f;
        if (obj->rot.z >= 360.0f) {
            obj->rot.z -= 360.0f;
        }
    }

    func_80054904_main(D_80102C50_name_81[D_80102CA4_name_81], 0, (obj->rot.x + 80.0f),
                       (D_80102CC8_name_81 + 2.0f * sindf(obj->rot.z)));

    for (i = 1; D_80100FC8_name_81[obj->work[0]] >= i; i++) {
        func_80055458_main(D_80102C50_name_81[D_80102CA4_name_81], i, (obj->scale.x * 256.0f));
    }
}

void func_800E31A0_name_81(void) {
    omObjData* obj;
    void* data;
    DuelTelopSprIds sp18 = D_80102478_name_81;

    obj = omAddObj(-0x8000, 0, 0, -1, func_800E2978_name_81);
    D_80102CB4_name_81 = obj;
    obj->rot.x = 0.0f;

    if (D_80102CC4_name_81 == 0) {
        D_80102CBA_name_81[0] = HuSprGrpCreate(1, 0);
        data = DataRead(0x1301E0);
        D_80102CBE_name_81[0] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80102CBA_name_81[0], 0, D_80102CBE_name_81[0], 0);
        HuSprPriSet(D_80102CBA_name_81[0], 0, 0x10);
        HuSprAttrSet(D_80102CBA_name_81[0], 0, 0x1000);
        func_80054904_main(D_80102CBA_name_81[0], 0, 0xA0, 0x32);
        D_80102CBE_name_81[1] = -1;
        D_80102CBA_name_81[1] = -1;
        obj->work[0] = 1;
        return;
    }

    D_80102CBA_name_81[0] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DF);
    D_80102CBE_name_81[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80102CBA_name_81[0], 0, D_80102CBE_name_81[0], sp18.unk_00[D_80102CC4_name_81]);
    HuSprPriSet(D_80102CBA_name_81[0], 0, 0x10);
    HuSprAttrSet(D_80102CBA_name_81[0], 0, 0x1000);
    func_80054904_main(D_80102CBA_name_81[0], 0, 0xA0, 0x32);

    D_80102CBA_name_81[1] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DE);
    D_80102CBE_name_81[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80102CBA_name_81[1], 0, D_80102CBE_name_81[1], 0);
    HuSprPriSet(D_80102CBA_name_81[1], 0, 0x11);
    HuSprAttrSet(D_80102CBA_name_81[1], 0, 0x1000);
    func_80054904_main(D_80102CBA_name_81[1], 0, 0xA0, 0x32);
    obj->work[0] = 0;
}

void func_800E3400_name_81(s32 arg0) {
    omObjData* obj;
    void* data;
    DuelTelopChrFiles sp18 = D_80102484_name_81;

    D_80102CA8_name_81 = HuSprGrpCreate(1, 0);
    data = DataRead(sp18.unk_00[GwPlayer[arg0].chr] | 0x130000);
    D_80102CAA_name_81[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80102CA8_name_81, 0, D_80102CAA_name_81[0], 0);
    HuSprPriSet(D_80102CA8_name_81, 0, 0x10);
    HuSprAttrSet(D_80102CA8_name_81, 0, 0x1000);
    func_80054904_main(D_80102CA8_name_81, 0, 0xA0, 0x78);
    obj = omAddObj(-0x8000, 0, 0, -1, func_800E2AD0_name_81);
    D_80102CB0_name_81 = obj;

    obj->scale.x = 0;
    obj->rot.x = 180.0f;
    obj->rot.y = 150.0f;
    obj->work[2] = 30;
    obj->work[0] = 0;
    obj->work[1] = 12;

    if (D_80102CB4_name_81 != NULL) {
        obj->work[1] = 24;
    }
    obj->work[3] = arg0;
    if (arg0 >= 2) {
        obj->work[3] = 4;
    }
}

s32 func_800E35C4_name_81(void) {
    return D_80102CA6_name_81 & 4;
}

void func_800E35D4_name_81(void) {
    HuSprGrpKill(D_80102CA8_name_81);
    HuSprKill(D_80102CAA_name_81[0]);
    HuSprKill(D_80102CAA_name_81[1]);
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    D_80102CA6_name_81 &= ~(0x20 | 0x10 | 0x08 | 0x04);
}

void func_800E363C_name_81(s32 arg0, Vec* pos) {
    Vec2f sp18;
    omObjData* obj;
    s32 i;
    s32 type;

    if (!(D_80102CA6_name_81 & 4)) {
        type = arg0;
        D_80102CA4_name_81 = func_8003A308_main(D_80102C30_name_81, D_80100FC0_name_81[arg0], 0, 0, 0);
        MBDCamera3Dto2D(pos, &sp18);
        D_80102CC8_name_81 = sp18.y - 24.0f;
        if (MBDCameraZoomGet() == 2.0f) {
            D_80102CC8_name_81 -= 10;
        }
        func_80054904_main(D_80102C50_name_81[D_80102CA4_name_81], 0, D_80100FCC_name_81[type] + 0x50, D_80102CC8_name_81);

        for (i = 1; D_80100FC8_name_81[type] >= i; i++) {
            func_80055458_main(D_80102C50_name_81[D_80102CA4_name_81], i, 0);
        }

        obj = omAddObj(-0x8000, 0, 0, -1, func_800E2F94_name_81);
        D_80102CB0_name_81 = obj;
        obj->scale.x = 0.0f;
        obj->trans.x = 400.0f;
        obj->trans.z = 0.0f;
        obj->rot.x = D_80100FCC_name_81[type];
        obj->rot.y = 0.0f;
        obj->rot.z = 0.0f;
        obj->work[0] = type;
        obj->work[1] = D_80102CA4_name_81;
        obj->work[2] = 30;
        obj->work[3] = 7;
        D_80102CA6_name_81 = 0x26;
        func_800E02B4_name_81(arg0);
    }
}

s32 func_800E3858_name_81(void) {
    return D_80102CA6_name_81 & (8 | 4);
}

void func_800E3868_name_81(void) {
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    func_8003B128_main(D_80102C30_name_81);
    D_80102CA6_name_81 &= ~(0x20 | 0x10 | 0x08 | 0x04);
}

void func_800E38B0_name_81(void) {
    s32 turnsRemaining;
    DuelTelopData* data;

    data = HuPrcCurrentGet()->user_data;
    while (1) {
        switch (data->state) {
        case 0:
            HuAudFXPlay(0x10C);
            if (data->playerNo == 0) {
                turnsRemaining = GwSystem.total_turns - GwSystem.current_turn;
                D_80102CC4_name_81 = turnsRemaining;
                if (turnsRemaining >= 0) {
                    if (turnsRemaining < 5) {
                        func_800E31A0_name_81();
                    } else if (turnsRemaining == 9) {
                        func_800E31A0_name_81();
                    }
                }
            }
            func_800E3400_name_81(data->playerNo);
            data->state++;
            break;
        case 1:
            if (D_80102CA8_name_81 == -1) {
                omDelPrcObj(NULL);
            }
            break;
        }
        HuPrcVSleep();
    }
}

Process* func_800E39AC_name_81(s32 playerNo) {
    Process* proc;
    DuelTelopData* data;

    proc = omAddPrcObj(func_800E38B0_name_81, 0, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, sizeof(DuelTelopData));
    proc->user_data = data;
    data->state = 0;
    data->playerNo = playerNo;
    return proc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3A0C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3C6C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E415C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4188_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E47B8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4914_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4A74_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4AD0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4B38_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4B64_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4E64_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4EAC_name_81);
