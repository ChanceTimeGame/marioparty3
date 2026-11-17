#include "common.h"
#include "mallocblock.h"

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801059A0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80105B98_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80105C08_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106080_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801060A4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010614C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106560_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106878_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106CCC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106CF0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106D0C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106E8C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107108_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801075D4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107794_slot_synch);

void func_80107A80_slot_synch(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107A88_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107B00_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107BAC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107D54_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010800C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108238_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108428_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108848_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801089F8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108A7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108AA8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108B74_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108C88_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108CD0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108D14_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108D3C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801091D8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801092B8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801094E0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109508_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC78_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109754_slot_synch);

// m1 sy2
typedef struct SsReel {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 player;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s16 models[4];
    /* 0x0C */ s16 sprs[4][3];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ Vec pos;
    /* 0x40 */ Vec unk40;
    /* 0x4C */ Vec unk4C;
} SsReel; // Size 0x58

typedef struct SsSprIds {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4[8];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ struct {
        s16 unk0;
        s16 unk2;
    } unk1A[2];
    /* 0x22 */ s16 unk22[15];
} SsSprIds; // Size 0x40

typedef struct SsCounter {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk6[2];
    /* 0x0A */ s16 value;
    /* 0x0C */ s16 target;
    /* 0x0E */ s16 timer;
} SsCounter; // Size 0x10

extern Vec D_8010D820_slot_synch[];
extern s16 D_8010D838_slot_synch[][2];
extern omObjData *D_8010DF84_slot_synch;
extern SsReel *D_8010DF88_slot_synch;
extern SsSprIds *D_8010DF8C_slot_synch;
extern SsCounter *D_8010DF90_slot_synch;

void func_801094E0_slot_synch(u8 player, f32 y, f32 dy);
void func_8010A7D0_slot_synch(omObjData *obj);

// <func_80109FA4_slot_synch>
s16 func_80109FA4_slot_synch(u8 player, s16 arg1) {
    SsReel *reel;
    s32 i;
    s16 model;

    if (D_8010DF88_slot_synch == NULL) {
        return -1;
    }
    reel = D_8010DF88_slot_synch;
    for (i = 0; i < 5; i++, reel++) {
        if (reel->active == 0) {
            reel->active = 1;
            reel->player = player;
            reel->unk2 = 0;
            reel->unk3 = 0;
            reel->unk26 = arg1;
            reel->unk2A = 0;
            reel->unk2C = 0;
            reel->pos.x = D_8010D820_slot_synch[reel->player].x;
            reel->pos.z = D_8010D820_slot_synch[reel->player].z;
            reel->pos.y = D_8010D820_slot_synch[reel->player].y - 20.0000002980232239;
            reel->unk40.x = reel->unk40.y = reel->unk40.z = 0.0f;
            reel->unk4C.x = reel->unk4C.y = reel->unk4C.z = 0.1f;
            if (reel->unk26 != 4) {
                reel->unk28 = 0;
                model = reel->models[reel->unk26];
                func_8001C258_main(model, 4, 4);
                HmfModelData[model].unk02 = reel->sprs[reel->unk26][1];
                HmfModelData[model].unk40 = 0.0f;
                HmfModelData[model].unk44 = 0.0f;
                HmfModelData[model].unk03 &= ~2;
            } else {
                reel->unk28 = 0x10;
            }
            func_801094E0_slot_synch(reel->player, reel->pos.y, 20.0f);
            return i;
        }
    }
    return -1;
}
// </func_80109FA4_slot_synch>

// <func_8010A178_slot_synch>
s32 func_8010A178_slot_synch(s16 idx) {
    SsReel *reel;

    if (D_8010DF88_slot_synch == NULL) {
        return 1;
    }
    reel = &D_8010DF88_slot_synch[idx];
    if (reel->active == 0 || reel->unk2 != 0) {
        return 1;
    }
    return 0;
}
// </func_8010A178_slot_synch>

// <func_8010A1D0_slot_synch>
void func_8010A1D0_slot_synch(void) {
    SsReel *reel = D_8010DF88_slot_synch;
    s32 i;
    s32 j;

    if (reel != NULL) {
        for (i = 0; i < 5; i++, reel++) {
            for (j = 0; j < 4; j++) {
                HmfModelData[reel->models[j]].unk02 = 0xFF;
                func_8001ACDC_main(reel->models[j]);
                func_8002D4B8_main(reel->sprs[j][0]);
                func_8002D4B8_main(reel->sprs[j][1]);
                func_8002D4B8_main(reel->sprs[j][2]);
            }
            func_8001ACDC_main(reel->unk24);
        }
        HuMemFree(D_8010DF88_slot_synch);
        D_8010DF88_slot_synch = NULL;
        D_8010DF84_slot_synch->func = NULL;
    }
}
// </func_8010A1D0_slot_synch>

// <func_8010A2C4_slot_synch>
u16 func_8010A2C4_slot_synch(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}
// </func_8010A2C4_slot_synch>

// <func_8010A308_slot_synch>
void func_8010A308_slot_synch(s16 grp, s16 member, f32 x, f32 y) {
    HuSprGrp *group = HuSprGrpData[grp];
    HuSprite *spr = HuSprGet(grp, member);

    if (spr->unk_48 != x || spr->unk_4C != y) {
        group->unk_0C = 1;
        spr->unk_48 = x;
        spr->unk_4C = y;
    }
}
// </func_8010A308_slot_synch>

// <func_8010A39C_slot_synch>
void func_8010A39C_slot_synch(void) {
    SsCounter *counter;
    s32 i;

    D_8010DF8C_slot_synch->unk14 = func_8010A2C4_slot_synch(0x35000C);
    D_8010DF8C_slot_synch->unk16 = func_8010A2C4_slot_synch(0x35000B);
    D_8010DF8C_slot_synch->unk18 = func_8010A2C4_slot_synch(0x2D);
    counter = D_8010DF90_slot_synch = HuMemAllocTag(sizeof(SsCounter) * 2, 0x7918);
    for (i = 0; i < 2; i++, counter++) {
        counter->grp = -1;
        counter->x = D_8010D838_slot_synch[i][0];
        counter->y = D_8010D838_slot_synch[i][1];
        counter->unk6[0] = 0;
        counter->unk6[1] = 0;
        counter->value = 0;
        counter->target = 0;
        counter->timer = 0;
    }
    omAddObj(0x1E, 0, 0, -1, func_8010A7D0_slot_synch);
}
// </func_8010A39C_slot_synch>

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A480_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A7D0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AA9C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AAB8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AC14_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AD68_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AF38_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DD28_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B064_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B754_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BB90_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BD7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BF6C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C0C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C1C4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C384_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C39C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C3FC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C428_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C47C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C4C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D0A8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D2AC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D3E0_slot_synch);
