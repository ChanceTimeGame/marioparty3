#include "common.h"
#include "mallocblock.h"
#include "math.h"

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

typedef struct SsCounter {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk6[2];
    /* 0x0A */ s16 value;
    /* 0x0C */ s16 target;
    /* 0x0E */ s16 timer;
} SsCounter; // Size 0x10

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct SsEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} SsEffect; // Size 0x34

typedef struct SsCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} SsCamera; // Size 0x24

typedef struct SsBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} SsBytes;

typedef union SsPack {
    void *p;
    SsBytes b;
} SsPack;

#define SS_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

extern Vec D_8010D820_slot_synch[];
extern RGBA D_8010D868_slot_synch;
extern omObjData *D_8010DF94_slot_synch;
extern s32 D_8010DA60_slot_synch;
extern s32 D_8010DA64_slot_synch;
extern s32 D_8010DA68_slot_synch;
extern s32 fontcolor;
extern SsCamera D_8010DFA0_slot_synch[2];
extern s32 D_8010DFE8_slot_synch;
extern s32 D_8010DFEC_slot_synch;
extern s32 D_8010DFF0_slot_synch;
extern SsEffect *D_8010DF98_slot_synch;
extern s32 D_8010DA40_slot_synch[];
extern s16 D_8010D838_slot_synch[][2];
extern omObjData *D_8010DF84_slot_synch;
extern SsReel *D_8010DF88_slot_synch;
extern s16 *D_8010DF8C_slot_synch; // s16[0x20] sprite/file ids
extern SsCounter *D_8010DF90_slot_synch;

void func_801094E0_slot_synch(u8 player, f32 y, f32 dy);
void func_8010A7D0_slot_synch(omObjData *obj);
void func_8010AA9C_slot_synch(s16 idx, s16 target);
void func_8010AC14_slot_synch(omObjData *obj);
s16 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *spr, RGBA *color);
s16 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *spr, u16 model, RGBA *color);
void func_8010B754_slot_synch(omObjData *obj);
void func_8010BB90_slot_synch(s32 idx);
void func_8010BD7C_slot_synch(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010BF6C_slot_synch(s32 idx);
f32 func_8010C0C0_slot_synch(f32 a, f32 b);
f32 func_8010C1C4_slot_synch(f32 target, f32 cur, f32 step);
f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b);
f32 func_8010C39C_slot_synch(f32 t, f32 a, f32 b);
f32 fabsf(f32);
f64 fmod(f64, f64);
void func_8010D2AC_slot_synch(u16 model, HuSprite_Unk84_Struct *spr, u16 frame, RGBA *color);

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

    D_8010DF8C_slot_synch[10] = func_8010A2C4_slot_synch(0x35000C);
    D_8010DF8C_slot_synch[11] = func_8010A2C4_slot_synch(0x35000B);
    D_8010DF8C_slot_synch[12] = func_8010A2C4_slot_synch(0x2D);
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

// <func_8010A480_slot_synch>
void func_8010A480_slot_synch(s16 idx, s16 file0, s16 file1, s16 target) {
    SsCounter *counter = &D_8010DF90_slot_synch[idx];
    s32 grp;
    s32 i;

    D_8010DF8C_slot_synch[idx * 2 + 13] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[file0]);
    D_8010DF8C_slot_synch[idx * 2 + 14] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[file1]);
    counter->grp = grp = HuSprGrpCreate(6, 0);
    counter->unk6[0] = -8;
    counter->unk6[1] = 8;
    counter->timer = 0;
    counter->target = 0;
    counter->value = 0;
    func_8010AA9C_slot_synch(idx, target);
    for (i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                HuSprAttrSet(grp, i, 0x8000);
            case 1:
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[12], 0);
                func_80054904_main(grp, i, counter->x + counter->unk6[i], counter->y);
                break;
            case 2:
                func_80054904_main(grp, i, counter->x - 26, counter->y - 9);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[idx * 2 + 13], 0);
                break;
            case 3:
                func_80054904_main(grp, i, counter->x - 26, counter->y + 8);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[idx * 2 + 14], 0);
                break;
            case 4:
                func_80054904_main(grp, i, counter->x + 27, counter->y);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[11], 0);
                break;
            case 5:
                func_80054904_main(grp, i, counter->x, counter->y);
                HuSprScaleSet(grp, i, 1.0f, 1.0f);
                func_80055484_main(grp, i, 0, 0, 0xFF, 0xA0);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[10], 0);
                break;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        HuSprPriSet(grp, i, i - 0x10);
    }
}
// </func_8010A480_slot_synch>

// <func_8010A7D0_slot_synch>
void func_8010A7D0_slot_synch(omObjData *obj) {
    SsCounter *counter = D_8010DF90_slot_synch;
    u16 digit[2];
    f32 scale;
    s32 i;

    for (i = 0; i < 2; i++, counter++) {
        digit[0] = counter->value / 10;
        digit[1] = counter->value - digit[0] * 10;
        if (digit[0] >= 10) {
            digit[0] = 9;
        }
        if (digit[1] >= 10) {
            digit[1] = 9;
        }
        func_80054FF8_main(counter->grp, 0, (s16)digit[0]);
        func_80054FF8_main(counter->grp, 1, (s16)digit[1]);
        if (counter->value != counter->target && counter->timer == 0) {
            counter->timer = 15;
            if (counter->value < counter->target) {
                counter->value++;
            } else {
                counter->value--;
            }
            HuSprAttrSet(counter->grp, 0, 0x838);
            HuSprAttrSet(counter->grp, 1, 0x838);
            if (counter->value >= 10) {
                HuSprAttrReset(counter->grp, 0, 0x8000);
            } else {
                HuSprAttrSet(counter->grp, 0, 0x8000);
            }
        }
        scale = sindf(counter->timer / 15.0f * 180.0f) * 0.5f + 1.0f;
        func_80054904_main(counter->grp, 0, counter->x + counter->unk6[0] * scale, counter->y);
        func_80054904_main(counter->grp, 1, counter->x + counter->unk6[1] * scale, counter->y);
        HuSprScaleSet(counter->grp, 0, scale, scale);
        HuSprScaleSet(counter->grp, 1, scale, scale);
        if (counter->timer != 0) {
            if (--counter->timer == 0) {
                HuSprAttrReset(counter->grp, 0, 0x838);
                HuSprAttrReset(counter->grp, 1, 0x838);
            }
        }
    }
}
// </func_8010A7D0_slot_synch>

// <func_8010AA9C_slot_synch>
void func_8010AA9C_slot_synch(s16 idx, s16 target) {
    SsCounter *counter;
    s32 offset = idx * sizeof(SsCounter);

    counter = (SsCounter *)((u8 *)D_8010DF90_slot_synch + offset);
    counter->target = target;
}
// </func_8010AA9C_slot_synch>

// <func_8010AAB8_slot_synch>
void func_8010AAB8_slot_synch(void) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010DF8C_slot_synch[1] = func_8010A2C4_slot_synch(0xB));
    D_8010DF94_slot_synch = omAddObj(0x1E, 0, 0, -1, func_8010AC14_slot_synch);
    D_8010DF98_slot_synch = effect = HuMemAllocTag(sizeof(SsEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010C4C0_slot_synch(spr, &D_8010D868_slot_synch);
        } else {
            effect->model = func_8010D0A8_slot_synch(spr, D_8010DF98_slot_synch->model, &D_8010D868_slot_synch);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010D868_slot_synch;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}
// </func_8010AAB8_slot_synch>

// <func_8010AC14_slot_synch>
void func_8010AC14_slot_synch(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010DF8C_slot_synch[1]);
    effect = D_8010DF98_slot_synch;
    do {
        if (effect->active != 0) {
            model = &HmfModelData[effect->model];
            if (!(model->unk18 & 4)) {
                effect->pos.x += effect->vel.x;
                effect->pos.y += effect->vel.y;
                effect->pos.z += effect->vel.z;
                model->pos.x = effect->pos.x;
                model->pos.y = effect->pos.y;
                model->pos.z = effect->pos.z;
                model->scale.x = effect->scale.x;
                model->scale.y = effect->scale.y;
                model->scale.z = effect->scale.z;
                func_8010D2AC_slot_synch(effect->model, spr, (s32)effect->frame, &effect->color);
                effect->frame += effect->speed;
                if ((s32)effect->frame >= (s32)spr->unk10) {
                    effect->active = 0;
                    effect->frame = 0.0f;
                    model->unk18 |= 4;
                }
            }
        }
        i++;
        effect++;
    } while (i < 8);
}
// </func_8010AC14_slot_synch>

// <func_8010AD68_slot_synch>
s32 func_8010AD68_slot_synch(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010DF8C_slot_synch[1]);
    for (i = 0, effect = D_8010DF98_slot_synch; i < 8; i++, effect++) {
        if (effect->active == 0) {
            effect->active = 1;
            model = &HmfModelData[effect->model];
            if (pos != NULL) {
                effect->pos.x = pos->x;
                effect->pos.y = pos->y;
                effect->pos.z = pos->z;
            } else {
                effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
            }
            if (vel != NULL) {
                effect->vel.x = vel->x;
                effect->vel.y = vel->y;
                effect->vel.z = vel->z;
            } else {
                effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
            }
            if (scale != NULL) {
                effect->scale.x = scale->x;
                effect->scale.y = scale->y;
                effect->scale.z = scale->z;
            } else {
                effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
            }
            effect->color = *color;
            effect->speed = speed;
            effect->frame = 0.0f;
            func_8010D2AC_slot_synch(effect->model, spr, 0, &effect->color);
            func_8001C258_main(effect->model, 4, 0);
            model->unk40 = 0.0f;
            model->pos.x = effect->pos.x;
            model->pos.y = effect->pos.y;
            model->pos.z = effect->pos.z;
            model->scale.x = effect->scale.x;
            model->scale.y = effect->scale.y;
            model->scale.z = effect->scale.z;
            return i;
        }
    }
    return -1;
}
// </func_8010AD68_slot_synch>

// <func_8010AF38_slot_synch>
void func_8010AF38_slot_synch(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = 184.8f;
    Center.z = -708.8f;
    CRot.x = 354.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2000.0f;
    func_8010BB90_slot_synch(0);
    func_8010BB90_slot_synch(1);
    D_8010DFE8_slot_synch = D_8010DFEC_slot_synch = D_8010DFF0_slot_synch = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010B754_slot_synch);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}
// </func_8010AF38_slot_synch>

// <func_8010B064_slot_synch>
void func_8010B064_slot_synch(void) {
    SsCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010DA60_slot_synch) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & 0x200) {
                    c.center.x = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 0x100) {
                    c.center.x = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x800) {
                    c.center.z = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x400) {
                    c.center.z = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 8) {
                    c.center.y = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 4) {
                    c.center.y = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 1) {
                    c.zoom = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 2) {
                    c.zoom = -(2.0 * speed);
                }
                c.center.x += Center.x;
                c.center.y += Center.y;
                c.center.z += Center.z;
                c.rot.x += CRot.x;
                c.rot.y += CRot.y;
                c.rot.z += CRot.z;
                c.zoom += CZoom;
                func_8010BD7C_slot_synch(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010DA64_slot_synch++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010DA64_slot_synch--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010DA68_slot_synch++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010DA68_slot_synch--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 104, D_800D5218_main);
            break;
        case 3:
            D_8010DA60_slot_synch = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010DA60_slot_synch == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010DA60_slot_synch++ >= 4) {
            D_8010DA60_slot_synch = 0;
        }
    }
}
// </func_8010B064_slot_synch>

// <func_8010B754_slot_synch>
void func_8010B754_slot_synch(omObjData *obj) {
    f32 t;

    if (D_8010DFEC_slot_synch <= 0) {
        func_8010BF6C_slot_synch(0);
        D_8010DFF0_slot_synch = 0;
        return;
    }
    if (D_8010DFE8_slot_synch == 0) {
        Center.x = D_8010DFA0_slot_synch[0].center.x;
        Center.y = D_8010DFA0_slot_synch[0].center.y;
        Center.z = D_8010DFA0_slot_synch[0].center.z;
        CRot.x = D_8010DFA0_slot_synch[0].rot.x;
        CRot.y = D_8010DFA0_slot_synch[0].rot.y;
        CRot.z = D_8010DFA0_slot_synch[0].rot.z;
        CZoom = D_8010DFA0_slot_synch[0].zoom;
        SS_WRAP(CRot.x);
        SS_WRAP(CRot.y);
        SS_WRAP(CRot.z);
        D_8010DFEC_slot_synch = 0;
    } else {
        t = (f32)D_8010DFE8_slot_synch / (f32)D_8010DFEC_slot_synch;
        Center.x = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.x, D_8010DFA0_slot_synch[1].center.x);
        Center.y = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.y, D_8010DFA0_slot_synch[1].center.y);
        Center.z = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.z, D_8010DFA0_slot_synch[1].center.z);
        CRot.x = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.x, D_8010DFA0_slot_synch[1].rot.x);
        CRot.y = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.y, D_8010DFA0_slot_synch[1].rot.y);
        CRot.z = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.z, D_8010DFA0_slot_synch[1].rot.z);
        CZoom = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].zoom, D_8010DFA0_slot_synch[1].zoom);
        SS_WRAP(CRot.x);
        SS_WRAP(CRot.y);
        SS_WRAP(CRot.z);
        if (D_8010DFE8_slot_synch > 0) {
            D_8010DFE8_slot_synch--;
        } else {
            D_8010DFE8_slot_synch++;
        }
    }
    D_8010DFF0_slot_synch = 1;
    func_8010BF6C_slot_synch(0);
}
// </func_8010B754_slot_synch>

// <func_8010BB90_slot_synch>
void func_8010BB90_slot_synch(s32 idx) {
    SS_WRAP(CRot.x);
    SS_WRAP(CRot.y);
    SS_WRAP(CRot.z);
    D_8010DFA0_slot_synch[idx].center.x = Center.x;
    D_8010DFA0_slot_synch[idx].center.y = Center.y;
    D_8010DFA0_slot_synch[idx].center.z = Center.z;
    D_8010DFA0_slot_synch[idx].rot.x = CRot.x;
    D_8010DFA0_slot_synch[idx].rot.y = CRot.y;
    D_8010DFA0_slot_synch[idx].rot.z = CRot.z;
    D_8010DFA0_slot_synch[idx].zoom = CZoom;
    D_8010DFA0_slot_synch[idx].unk1C = D_8010DFA0_slot_synch[idx].unk20 = 0.0f;
}
// </func_8010BB90_slot_synch>

// <func_8010BD7C_slot_synch>
void func_8010BD7C_slot_synch(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010DFE8_slot_synch = frames - 1;
        D_8010DFEC_slot_synch = frames;
        if (cx != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.x = cx;
        } else {
            D_8010DFA0_slot_synch[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.y = cy;
        } else {
            D_8010DFA0_slot_synch[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.z = cz;
        } else {
            D_8010DFA0_slot_synch[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.x = rx;
        } else {
            D_8010DFA0_slot_synch[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.y = ry;
        } else {
            D_8010DFA0_slot_synch[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.z = rz;
        } else {
            D_8010DFA0_slot_synch[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010DFA0_slot_synch[0].zoom = zoom;
        } else {
            D_8010DFA0_slot_synch[0].zoom = CZoom;
        }
        func_8010BB90_slot_synch(1);
    }
}
// </func_8010BD7C_slot_synch>

// <func_8010BF6C_slot_synch>
void func_8010BF6C_slot_synch(s32 idx) {
    HuCamera *cam = &gCameraList[idx];
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}
// </func_8010BF6C_slot_synch>

// <func_8010C0C0_slot_synch>
f32 func_8010C0C0_slot_synch(f32 a, f32 b) {
    f32 d;

    if (a >= 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    if (b >= 360.0f) {
        b -= 360.0f;
    } else if (b < 0.0f) {
        b += 360.0f;
    }
    d = a - b;
    if (d <= -180.0f) {
        d += 360.0f;
    } else if (d >= 180.0f) {
        d -= 360.0f;
    }
    return d;
}
// </func_8010C0C0_slot_synch>

// <func_8010C1C4_slot_synch>
f32 func_8010C1C4_slot_synch(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    SS_WRAP(target);
    SS_WRAP(cur);
    d = fmod(target - cur + 360.0, 360.0);
    if (d < 180.0) {
        if (d <= step) {
            v = d;
        } else {
            v = step;
        }
    } else {
        e = 360.0 - d;
        if (e <= step) {
            v = -e;
        } else {
            v = -step;
        }
    }
    v += cur;
    SS_WRAP(v);
    return v;
}
// </func_8010C1C4_slot_synch>

// <func_8010C384_slot_synch>
f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}
// </func_8010C384_slot_synch>

// <func_8010C39C_slot_synch>
f32 func_8010C39C_slot_synch(f32 t, f32 a, f32 b) {
    return func_8010C1C4_slot_synch(b, a, fabsf(func_8010C0C0_slot_synch(b, a) * t));
}
// </func_8010C39C_slot_synch>

// <func_8010C3FC_slot_synch>
void func_8010C3FC_slot_synch(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}
// </func_8010C3FC_slot_synch>

// <func_8010C428_slot_synch>
void *func_8010C428_slot_synch(omObjData *obj) {
    SsPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}
// </func_8010C428_slot_synch>

// <func_8010C47C_slot_synch>
s16 func_8010C47C_slot_synch(s32 dirAndFile) {
    s16 id = func_8001F1FC_main(DataRead(dirAndFile), 0x18);

    if (id >= 0) {
        return id;
    }
    return -1;
}
// </func_8010C47C_slot_synch>

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C4C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D0A8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D2AC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D3E0_slot_synch);
