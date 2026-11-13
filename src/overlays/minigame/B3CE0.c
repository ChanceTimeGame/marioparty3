#include "common.h"
#include "game/hmfman.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/gamework_data.h"
#include "game/util.h"
#include "mallocblock.h"
#include "include_asm.h"

// EXTERN

s16 func_8000B0D4_main(s32, s32);
void func_800DDD94_minigame(omObjData *);

// LOCAL

void func_800E3584_minigame(s16);

extern s8 D_800EB735_minigame;
extern u8 D_800EB739_minigame;
extern u8 D_800EB73A_minigame;
extern f32 D_800EB73C_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB74C_minigame;
extern f32 D_800EB750_minigame;
extern f32 D_800EB75C_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EB774_minigame;
extern f32 D_800EB778_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB784_minigame[][14];


typedef func_800E1BA8_minigame_ObjData MgWork;

/* An entry of D_800CBB60_main (0x24 bytes; src/14EA0.c's unk_800ECDE0). */
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x22];
} MgSprModel;

extern MgSprModel* D_800CBB60_main;
extern s32 D_800EB730_minigame; /* scene state, copied to D_800EBE24_minigame */
extern u8 D_800EB734_minigame;
extern s32 D_800EB800_minigame[]; /* per character: its file directory */
extern s32 D_800EBE24_minigame;
extern s16 D_800EBE10_minigame[];

u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
s16 HmfAnimRead(HmfData* arg0, s32 arg1, char* arg2);
void func_80032FC0_main(s16 arg0, u8 arg1, u8 arg2);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_8001F450_main(s16 arg0, s16 arg1, f32 arg2);
f32 func_800202A8_main(f32 angle);

/* Loads player `player`'s character model into slot idx. */
void func_800E1160_minigame(omObjData* obj, u16 idx, u16 player, s32 file, s32 flags, f32 arg5) {
    s32 dir = D_800EB800_minigame[GwPlayer[player].chr];
    s16 mot;

    obj->model[idx] = func_8000B108_main(file, flags & ~0x11);
    mot = func_80017790_main(obj->model[idx], 0, GwPlayer[player].chr, dir);
    func_80017954_main(obj->model[idx], 0, GwPlayer[player].chr, mot);
}

void func_800E123C_minigame(omObjData* obj, u16 idx, s32 dir, s32 file, f32 arg4) {
    s16 mdl = func_8000B108_main(dir, file);

    obj->model[idx] = mdl;
    func_8001F450_main(obj->model[0], mdl, arg4);
}

void func_800E12B0_minigame(omObjData* obj, f32 angle) {
    MgWork* work = obj->data;

    work->unk3C = func_800202A8_main(angle);
}

void func_800E12E0_minigame(omObjData* obj, f32 arg1) {
    ((MgWork*)obj->data)->unk40 = arg1;
}

void func_800E12EC_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk38 = arg1;
}

void func_800E12F8_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk44 = arg1;
}

void func_800E1304_minigame(omObjData* obj, f32 arg1) {
    ((MgWork*)obj->data)->unk08 = arg1;
}

void func_800E1310_minigame(omObjData* obj, f32 arg1) {
    ((MgWork*)obj->data)->unk0C = arg1;
}

void func_800E131C_minigame(omObjData* obj, f32 arg1) {
    ((MgWork*)obj->data)->unk10 = arg1;
}

void func_800E1328_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk48 = arg1;
}

void func_800E1334_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk34 = arg1;
}

void func_800E1340_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk64 = arg1;
}

void func_800E134C_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk68 = arg1;
}

void func_800E1358_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk6C = arg1;
}

void func_800E1364_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk70 = arg1;
}

void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2) {
    MgWork* work = obj->data;

    work->unk06 = (u8)flags | work->unk06;
    if (flags & 2) {
        work->unk14 = arg2;
    }
}

/* Hit box: radius and XZ bounds. */
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ) {
    MgWork* work = obj->data;

    work->unk06 |= 8;
    work->unk14 = arg1;
    work->unkA0 = minX;
    work->unkA4 = minZ;
    work->unkA8 = maxX;
    work->unkAC = maxZ;
}

/* Hit box with its own radius. */
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ) {
    MgWork* work = obj->data;

    work->unk06 |= 0x10;
    work->unk14 = arg1;
    work->unk98 = arg2;
    work->unkA0 = minX;
    work->unkA4 = minZ;
    work->unkA8 = maxX;
    work->unkAC = maxZ;
}

void func_800E1404_minigame(omObjData* obj, f32 arg1, f32 arg2) {
    MgWork* work = obj->data;

    work->unk06 |= 0x20;
    work->unk14 = arg1;
    work->unk9C = arg2;
}

/* Cylinder hit shape: top, depth below it, radius. */
void func_800E1420_minigame(omObjData* obj, f32 top, f32 depth, f32 radius) {
    MgWork* work = obj->data;

    work->unk06 |= 0x40;
    work->unk14 = top;
    work->unk98 = depth;
    work->unk9C = radius;
}

void func_800E1440_minigame(omObjData* obj) {
    ((MgWork*)obj->data)->unk06 |= 0x80;
}

void func_800E1454_minigame(omObjData* obj) {
    ((MgWork*)obj->data)->unk06 |= 0x100;
}

void func_800E1468_minigame(omObjData* obj) {
    ((MgWork*)obj->data)->unk06 |= 0x200;
}

void func_800E147C_minigame(omObjData* obj) {
    ((MgWork*)obj->data)->unk06 |= 0x400;
}

void func_800E1490_minigame(u16 arg0) {
    D_800EB734_minigame = arg0;
}

void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val) {
    u8* work = obj->data;

    work[idx] = val;
}

void func_800E14B0_minigame(omObjData* obj, u8 idx, u8 on) {
    if (on == 0) {
        func_8001C258_main(obj->model[idx], 4, 4);
    } else {
        func_8001C258_main(obj->model[idx], 4, 0);
    }
}

/* 0 when the ground object with id `id` has flag 0x200 (or id < 0). */
s32 func_800E1510_minigame(s8 id) {
    s32 i;
    MgWork* work;

    if (id < 0) {
        return 0;
    }
    for (i = 0; i < (u16)D_800EBE28_minigame; i++) {
        work = D_800EC1C0_minigame[i]->data;
        if (work->unk04 == id) {
            if (work->unk06 & 0x200) {
                return 0;
            }
            break;
        }
    }
    return 1;
}

void func_800E1594_minigame(omObjData* obj, s32 dir, s32 file, s32 arg3) {
    MgWork* work = obj->data;

    work->unk55 = SprModelRead(dir, file, arg3);
    obj->model[0] = D_800CBB60_main[work->unk55].unk00;
    func_8001C2FC_main(obj->model[0], 0x70000000, 0x70000000);
}

void func_800E1610_minigame(omObjData* obj, u8 idx, s32 dir, s32 arg3, char* arg4, s32 arg5) {
    u8* work = obj->data;
    HmfModel* m;
    u8 r;

    obj->model[idx] = func_8000B0D4_main(dir, arg5);
    m = &HmfModelData[obj->model[idx]];
    r = HmfAnimRead(m->hmf, arg3, arg4);
    (work + idx)[0x21] = r;
    func_8001C448_main(obj->model[idx]);
    func_80032FC0_main(r, 1, 1);
    func_80032FC0_main(r, 2, 2);
    Hu3DModelScaleSet(obj->model[idx], 2.0f, 2.0f, 2.0f);
}

void func_800E1718_minigame(omObjData* obj, s32 idx, s32 dir, s32 file, s32 arg4) {
    u8* work = obj->data;
    u16 img = SprModelRead(dir, file, arg4);

    obj->model[(u8)idx] = D_800CBB60_main[(u8)img].unk00;
    work += (u8)idx;
    work[0x21] = img;
    func_8001C2FC_main(D_800CBB60_main[(u8)img].unk00, 0x70000000, 0x70000000);
    func_800146DC_main((u8)img, 4, 4);
}

void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void func_800E17E4_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

void func_800E17F4_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    obj->scale.x = x;
    obj->scale.y = y;
    obj->scale.z = z;
}

void func_800E1804_minigame(void) {
    D_800EB730_minigame = 0;
}

void func_800E1810_minigame(void) {
    D_800EB730_minigame = 2;
}

void func_800E1820_minigame(void) {
    D_800EB730_minigame = 3;
}

void func_800E1830_minigame(void) {
    D_800EB730_minigame = 1;
}

void func_800E1840_minigame(void) {
    D_800EBE24_minigame = D_800EB730_minigame;
}

/* Index of the ground object whose byte 0x5F (retail reads the low byte of the object's own
   `data` pointer, not a field of its work block) is `id`; D_800EB734_minigame if none. */
s32 func_800E1854_minigame(s32 id) {
    s32 i;

    for (i = 0; i < (u16)D_800EBE28_minigame; i++) {
        if (((u8*)D_800EC1C0_minigame[i])[0x5F] == id) {
            return i;
        }
    }
    return D_800EB734_minigame;
}

void func_800E18B4_minigame(void) {
    s32 buf;

    memset(&buf, 0, 1);
}

void func_800E18D8_minigame(void) {
    D_800EB73C_minigame = 15.0f;
    D_800EB740_minigame = 0.5f;
    D_800EB744_minigame = 1.45f;
    D_800EB748_minigame = 0.15f;
    D_800EB74C_minigame = 7.0f;
    D_800EB750_minigame = 30.0f;
    D_800EB778_minigame = 0.5f;
    D_800EB75C_minigame = 3.3333333f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    D_800EB770_minigame = 0;
    D_800EB774_minigame = 1.6f;
    D_800EB77C_minigame = 0.14500001f;
    D_800EB735_minigame = 1;
    D_800EB73A_minigame = 0;
}

void func_800E19E4_minigame(u8 arg0) {
    D_800EB73A_minigame = arg0;
}

void func_800E19F0_minigame(s8 arg0) {
    D_800EB739_minigame = arg0;
}

/* Plays the player's voice/sound `arg1` (D_800EB784_minigame) unless it is already playing. */
void func_800E19FC_minigame(MgWork* work, s32 arg1) {
    s8 player = work->unk59;
    s16 id = D_800EB784_minigame[player][arg1];

    if (id >= 0) {
        if (work->unkC4 != arg1) {
            work->unkC5 = func_8004AC98_main(id, player);
            work->unkC4 = arg1;
            D_800EBE10_minigame[work->unk59] = id;
        }
    } else {
        work->unkC4 = -1;
    }
}

void func_800E1A9C_minigame(MgWork* work, s32 arg1) {
    s8 player = work->unk59;
    s16 id = D_800EB784_minigame[player][arg1];

    if (id >= 0) {
        if (work->unkC4 != arg1) {
            work->unkC5 = func_8004AC98_main(id, player);
            work->unkC4 = arg1;
            D_800EBE10_minigame[work->unk59] = id;
        }
    } else {
        work->unkC4 = -1;
    }
}

void func_800E1B3C_minigame(void) {
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        HuAudFXStop(((MgWork*)D_800EC598_minigame[i]->data)->unkC5);
    }
}

void func_800E1BA8_minigame(omObjData *arg0, u32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5) {
    func_800E1BA8_minigame_ObjData *temp_s0;
    s32 var_a0;

    for (var_a0 = 0; var_a0 < arg0->mdlcnt; var_a0++) {
        arg0->model[var_a0] = 0;
    }
    arg0->data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), 31000);
    memset(arg0->data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    temp_s0 = arg0->data;
    temp_s0->unkE8 = HuMemAllocTag(arg0->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 31000);
    if (D_800EB73A_minigame == 1) {
        func_800E1160_minigame(arg0, 0, arg3, arg1 | arg2, arg4, 750.0f);
    } else {
        arg0->model[0] = func_8000B108_main(arg1 | arg2, arg4);
    }
    arg0->model[1] = func_8000B0D4_main((D_800EB739_minigame != 0) ? 9 : 0, arg5);
    func_800E3584_minigame(arg0->model[1]);
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        arg0->motion[var_a0] = -1;
    }
    for (var_a0 = 0; var_a0 < 21; var_a0++) {
        temp_s0->unk104[var_a0] = 0;
    }
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        temp_s0->unkE8[var_a0].unk00 = 0;
        temp_s0->unkE8[var_a0].unk02 = 0;
        temp_s0->unkE8[var_a0].unk04 = -1;
        temp_s0->unkE8[var_a0].unk08 = -1;
    }
    temp_s0->unk57 = GwPlayer[arg3].pad;
    arg0->func = func_800DDD94_minigame;
    temp_s0->unk52 = 0;
    temp_s0->unkB4 = 1.0f;
    temp_s0->unk8C = 65536.0f;
    temp_s0->unkD0 = 0xFFFF;
    temp_s0->unk4C = 0.5f;
    temp_s0->unkCC = 1.0f;
    temp_s0->unk60 = 0;
    func_800E1328_minigame(arg0, 60.0f);
    func_800E1334_minigame(arg0, 150.0f);
    func_800E1340_minigame(arg0, 20.0f);
    func_800E134C_minigame(arg0, 30.0f);
    func_800E1358_minigame(arg0, 50.0f);
    func_800E1364_minigame(arg0, 40.0f);
    func_800E12EC_minigame(arg0, 1000.0f);
    temp_s0->unk9C = temp_s0->unkA0 = temp_s0->unkA4 = 0.0f;
    temp_s0->unk59 = (s8)arg3;
    temp_s0->unkC3 = -1;
    temp_s0->unkC4 = -1;
    temp_s0->unkB0 = 1.0f;
    switch (arg1 >> 16) {
        case 6:
            temp_s0->unkAC = 0.7f;
            break;
        case 4:
            temp_s0->unkAC = 0.9f;
            break;
        case 5:
            temp_s0->unkAC = 0.8f;
            break;
        default:
            temp_s0->unkAC = 1.0f;
            break;
    }
    var_a0 = GwPlayer[arg3].chr + 1;
    D_800EB784_minigame[temp_s0->unk59][0] = var_a0 + 0x1F;
    D_800EB784_minigame[temp_s0->unk59][1] = var_a0 + 0x28;
    D_800EB784_minigame[temp_s0->unk59][2] = var_a0 + 0x43;
    D_800EB784_minigame[temp_s0->unk59][3] = var_a0 + 0x3A;
    D_800EB784_minigame[temp_s0->unk59][4] = var_a0 + 0x31;
    D_800EB784_minigame[temp_s0->unk59][5] = var_a0 + 0x4C;
    D_800EB784_minigame[temp_s0->unk59][6] = var_a0 + 0x55;
    D_800EB784_minigame[temp_s0->unk59][7] = var_a0 + 0x9D;
    D_800EB784_minigame[temp_s0->unk59][8] = var_a0 + 0x94;
    D_800EB784_minigame[temp_s0->unk59][9] = var_a0 + 0xA6;
    D_800EB784_minigame[temp_s0->unk59][10] = var_a0 + 0x5E;
    D_800EB784_minigame[temp_s0->unk59][11] = var_a0 + 0x67;
    D_800EB784_minigame[temp_s0->unk59][12] = var_a0 + 0xAF;
    D_800EB784_minigame[temp_s0->unk59][13] = var_a0 + 0xB8;
}

extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
extern s32 D_800EB820_minigame[][7]; /* per character: motion keys */
extern u16 D_800EBE18_minigame[]; /* frames since the last quadrant change */
extern u8 D_800EBE20_minigame[];  /* last stick quadrant */
extern s8 D_800EC1BA_minigame[];  /* rotation direction (-1, 0, 1) */
extern s8 D_800EC282_minigame[];  /* frames held in one quadrant */
extern s16 D_800EC28A_minigame[]; /* frames per half turn */
extern u8 D_800EC5DC_minigame[];  /* quadrant two changes ago */

s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
s32 func_800202FC_main(Vec* v); /* normalise */
void func_80088800_main(HuMtx4F mf, f32 x, f32 y, f32 z);
void func_8008A070_main(HuMtx4F mf); /* identity */
void func_80017D24_main(HuMtx4F mf, f32 x, f32 y, f32 z);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src); /* matrix copy */
s32 func_80018F18_main(HuMtx4F a, HuMtx4F out);

/* With MgWork::unk06 & 0x80 two matrices are kept at 0x18 and 0x58 (func_800E2780_minigame). */
#define MG_MTX(w, off) ((f32(*)[4])((u8*)(w) + (off)))

/* Plays motion `motion` of the player's character on model `model`. */
void func_800E210C_minigame(omObjData* obj, s16 model, s16 motion) {
    MgWork* work = obj->data;
    s32 chr;
    s32 dir;

    work->unk5A = model;
    work->unk5B = motion;
    chr = GwPlayer[work->unk59].chr;
    dir = D_800A178C_main[chr][0];
    func_80017790_main(model, motion, chr, dir | func_80017B6C_main(chr, motion, 0));
}

/* Loads motion key `idx` of `player`'s character into slot idx. Retail takes the file directory
   from player 0's character, not `player`'s. */
void func_800E21B8_minigame(omObjData* obj, s32 player, s32 idx) {
    MgWork* work = obj->data;

    work->unkF2[idx] = func_80017AD8_main(D_800EB820_minigame[GwPlayer[player].chr][idx] |
                                          D_800A178C_main[GwPlayer[0].chr][0]);
}

// NON_MATCHING: register allocation (masked 2, raw 18), as MP1 func_80009C90 and MP2
// func_8000CDC8_D9C8: retail keeps sx in a0 and i in a1 (ours swapped).
#ifdef NON_MATCHING
/* Averages the last six stick samples. */
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y) {
    MgWork* work = obj->data;
    s32 v = (x << 16) | (y & 0xFFFF);
    s16 sy;
    s16 sx;
    u8 i;

    work->unk74[work->unk58++] = v;
    if (work->unk58 >= 6) {
        work->unk58 = 0;
    }
    sy = 0;
    sx = 0;
    for (i = 0; i < 6; i++) {
        sx += work->unk74[i] >> 16;
        sy += (u16)work->unk74[i];
    }
    return ((sx / 6) << 16) | ((sy / 6) & 0xFFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2250_minigame);
#endif

/* Clamps the stick vector (x, y) to length 60. */
void func_800E2308_minigame(s16* x, s16* y) {
    Vec v;
    f32 fx = *x;
    f32 fy = *y;

    if (HuSqrtf(fx * fx + fy * fy) > 60.0f) {
        v.x = fx;
        v.y = 0.0f;
        v.z = fy;
        func_800202FC_main(&v);
        *x = v.x * 60.0f;
        *y = v.z * 60.0f;
    }
}

void func_800E23E0_minigame(omObjData* obj) {
    MgWork* work = obj->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        work->unk74[i] = 0;
    }
}

/* Stick rotation counter: +-1 (x2 for a fast half turn) per quadrant turned in one direction. */
s16 func_800E240C_minigame(s16 player, s16 limit, s8 x, s8 y) {
    s16 mult = 1;
    s16 quad;
    s16 d;
    s8 dir;

    if ((x == 0) & (y == 0)) {
        return 0;
    }
    quad = atan2df(y, x);
    if (quad < 0) {
        quad += 360;
    }
    quad /= 90;
    if (quad == D_800EBE20_minigame[player]) {
        if (++D_800EC282_minigame[player] > limit) {
            D_800EC282_minigame[player] = limit;
            D_800EC1BA_minigame[player] = 0;
            D_800EC5DC_minigame[player] = quad;
            D_800EBE18_minigame[player] = 0;
            return 0;
        }
        D_800EBE18_minigame[player]++;
        return D_800EC1BA_minigame[player];
    }
    D_800EBE18_minigame[player]++;
    D_800EC282_minigame[player] = 0;
    if (D_800EC5DC_minigame[player] == quad) {
        mult = 2;
        D_800EC28A_minigame[player] = D_800EBE18_minigame[player];
        D_800EBE18_minigame[player] = 0;
    }
    d = quad - D_800EBE20_minigame[player];
    if ((d < 0 ? -d : d) == 3) {
        d = -d;
    }
    dir = (d >> 31) | 1;
    if (dir != 0 && dir != D_800EC1BA_minigame[player]) {
        D_800EC1BA_minigame[player] = dir;
        D_800EBE20_minigame[player] = quad;
        D_800EC282_minigame[player] = 0;
        D_800EC5DC_minigame[player] = quad;
        D_800EBE18_minigame[player] = 0;
        return 0;
    }
    D_800EBE18_minigame[player]++;
    if (((D_800EBE20_minigame[player] + D_800EC1BA_minigame[player]) & 3) == quad) {
        D_800EBE20_minigame[player] = quad;
        return D_800EC1BA_minigame[player] * mult;
    }
    D_800EC1BA_minigame[player] = dir;
    D_800EBE20_minigame[player] = quad;
    D_800EC282_minigame[player] = 0;
    D_800EBE18_minigame[player] = 0;
    return 0;
}

/* Builds the two matrices func_800E28BC_minigame uses with flag 0x80 from obj's translation and
   rotation. */
void func_800E2780_minigame(omObjData* obj) {
    s32 mdl = obj->model[0];
    MgWork* work = obj->data;

    if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f) {
        func_80088800_main(MG_MTX(work, 0x18), obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        func_8008A070_main(MG_MTX(work, 0x18));
    }
    if (obj->rot.x != 0.0f || obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
        func_80017D24_main(MG_MTX(work, 0x18), obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (work->unk06 & 0x100) {
        guMtxCatF((f32(*)[4])HmfModelData[mdl].mtx, MG_MTX(work, 0x18), MG_MTX(work, 0x18));
    }
    func_80018F18_main(MG_MTX(work, 0x18), MG_MTX(work, 0x58));
}

/* Transforms p by obj's translation and rotation (or by the matrices stored in its work when
   flag 0x80 is set); m is scratch, out receives the matrix. */
void func_800E28BC_minigame(HuMtx4F m, HuMtx4F out, Vec* p, omObjData* obj) {
    MgWork* work = obj->data;
    s32 mdl = obj->model[0];
    f32 rx = obj->rot.x;
    f32 ry = obj->rot.y;
    f32 rz = obj->rot.z;
    f32 tx = obj->trans.x;
    f32 ty = obj->trans.y;
    f32 tz = obj->trans.z;
    f32 x = p->x;
    f32 y = p->y;
    f32 z = p->z;

    if (work->unk06 & 0x80) {
        func_8002367C_main(m, MG_MTX(work, 0x18));
        func_8002367C_main(out, MG_MTX(work, 0x58));
    } else {
        if (((tx != 0.0f) | (ty != 0.0f)) || tz != 0.0f) {
            func_80088800_main(m, tx, ty, tz);
        } else {
            func_8008A070_main(m);
        }
        if (((rx != 0.0f) | (ry != 0.0f)) || rz != 0.0f) {
            func_80017D24_main(m, rx, ry, rz);
        }
        if (work->unk06 & 0x100) {
            guMtxCatF((f32(*)[4])HmfModelData[mdl].mtx, m, m);
        }
        func_80018F18_main(m, out);
    }
    p->x = x * out[0][0] + y * out[1][0] + z * out[2][0] + out[3][0];
    p->y = x * out[0][1] + y * out[1][1] + z * out[2][1] + out[3][1];
    p->z = x * out[0][2] + y * out[1][2] + z * out[2][2] + out[3][2];
}

void func_800E2B58_minigame(f32 m[4][4], Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;

    v->x = x * m[0][0] + y * m[1][0] + z * m[2][0];
    v->y = x * m[0][1] + y * m[1][1] + z * m[2][1];
    v->z = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_800E2BD4_minigame(f32 m[4][4], Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;

    v->x = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
    v->y = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
    v->z = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
}

void func_800E2C68_minigame(f32 m[4][4], Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;

    v->y = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2CA4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2DA4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2E98_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2ED4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2F40_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2FD8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E30B8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E317C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E341C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E34D8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E3568_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E3584_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E3628_minigame);
