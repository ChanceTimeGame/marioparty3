#include "common.h"
#include "mallocblock.h"
#include "math.h"
#include "gcc/memory.h"

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

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern omObjData *D_8010DF94_slot_synch;
extern s32 fontcolor;
extern SsCamera D_8010DFA0_slot_synch[2];
extern s32 D_8010DFE8_slot_synch;
extern s32 D_8010DFEC_slot_synch;
extern s32 D_8010DFF0_slot_synch;
extern SsEffect *D_8010DF98_slot_synch;
extern omObjData *D_8010DF84_slot_synch;
extern SsReel *D_8010DF88_slot_synch;
extern s16 *D_8010DF8C_slot_synch; // s16[0x20] sprite/file ids
extern SsCounter *D_8010DF90_slot_synch;

typedef struct SsSlotPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 n;
} SsSlotPos; // Size 6

/* .data (0x8010D7F0..0x8010DBA0). Inner labels the remaining asm uses are undefined_syms.txt aliases. */
Vec D_8010D7F0_slot_synch[4] = { /* D_8010D7F8 = [0].z */
    { -300.0f, 0.0f, 0.0f }, { -125.0f, 0.0f, -0.0f }, { 125.0f, 0.0f, -0.0f }, { 300.0f, 0.0f, 0.0f },
};
Vec D_8010D820_slot_synch[2] = { /* D_8010D824 = [0].y, D_8010D828 = [0].z */
    { -255.0f, 0.0f, -300.0f },
    { 255.0f, 0.0f, -300.0f },
};
s16 D_8010D838_slot_synch[2][2] = { { 70, 40 }, { 250, 40 } }; /* counter positions; D_8010D83A = [0][1] */
f32 D_8010D840_slot_synch[5] = { 0.0f, 90.0f, 180.0f, 270.0f, 0.0f };
u8 D_8010D854_slot_synch[8] = { 0, 1, 2, 3, 2, 3, 1, 0 };
s16 D_8010D85C_slot_synch[4] = { 3, 1, 2, -1 };
RGBA D_8010D864_slot_synch = { 0xE9, 0xDD, 0xA1, 0x80 };
RGBA D_8010D868_slot_synch = { 0xFF, 0xFF, 0xFF, 0x80 };
RGBA D_8010D86C_slot_synch = { 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_8010D870_slot_synch[8] = { 0x200A5, 0x300A5, 0x700A5, 0x400A5, 0x500A5, 0x600A5, 0x800A5, 0x9001C };
s32 D_8010D890_slot_synch[8] = { 0x200A6, 0x300A6, 0x700A6, 0x400A6, 0x500A6, 0x600A6, 0x800A6, 0x9001D };
s32 D_8010D8B0_slot_synch = 0; /* D_8010D8B2 = its low half */
s32 D_8010D8B4_slot_synch[4] = { 0, 1, 2, 3 };
s16 D_8010D8C4_slot_synch[4][4] = { { 0, 1, 2, 3 }, { 3, 0, 1, 2 }, { 2, 3, 0, 1 }, { 1, 2, 3, 0 } };
s16 D_8010D8E4_slot_synch[4] = { 0x12, 0x13, 0x15, 0x14 };
s32 D_8010D8EC_slot_synch[8] = { 0x20000, 0x30000, 0x70000, 0x40000, 0x50000, 0x60000, 0x80000, 0x90000 };
s32 D_8010D90C_slot_synch[4] = { 0x2F, 0x30, 0x36, 0x37 }; /* D_8010D910 = [1], D_8010D912/D_8010D916 = low halves of [1]/[2] */
s16 D_8010D91C_slot_synch[6] = { 0, 2, 1, 3, 0, 0 };
s16 D_8010D928_slot_synch[8] = { 3, 3, 3, 3, 2, 3, 3, 0 };
SsSlotPos D_8010D938_slot_synch[12] = { /* D_8010D93A = [0].y, D_8010D93D = low byte of [0].n */
    { 0x10, 0x5C, 0 }, { 0x28, 0x5C, 1 }, { 0x40, 0x5C, 2 }, { 0x58, 0x5C, 3 },
    { 0x1E, 0x6C, 3 }, { 0x36, 0x6C, 2 }, { 0x4E, 0x6C, 1 }, { 0x66, 0x6C, 0 },
    { 0x10, 0x7C, 3 }, { 0x28, 0x7C, 0 }, { 0x40, 0x7C, 1 }, { 0x58, 0x7C, 2 },
};
SsSlotPos D_8010D980_slot_synch[12] = { /* D_8010D982 = [0].y, D_8010D985 = low byte of [0].n */
    { 0x130, 0x5C, 0 }, { 0x118, 0x5C, 1 }, { 0x100, 0x5C, 2 }, { 0xE8, 0x5C, 3 },
    { 0x122, 0x6C, 3 }, { 0x10A, 0x6C, 2 }, { 0xF2, 0x6C, 1 }, { 0xDA, 0x6C, 0 },
    { 0x130, 0x7C, 3 }, { 0x118, 0x7C, 0 }, { 0x100, 0x7C, 1 }, { 0xE8, 0x7C, 2 },
};
u8 D_8010D9C8_slot_synch[8] = { 0, 0, 0, 1, 0, 1, 0, 0 };
f32 D_8010D9D0_slot_synch[8] = { 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 180.0f, 150.0f, 150.0f };
s32 D_8010D9F0_slot_synch[4] = { 0xA0000, 0xA00A5, 0xA008E, 0xA00EE };
s32 D_8010DA00_slot_synch[4] = { 0xA0018, 0xA00B3, 0xA00A0, 0xA00FA };
s32 D_8010DA10_slot_synch[4] = { 0xA0002, 0xA00A9, 0xA0090, 0xA00F1 };
f32 D_8010DA20_slot_synch[4] = { 1.5f, 1.75f, 1.0f, 1.2f };
s32 D_8010DA30_slot_synch[4] = { 0x393, 0x391, 0x392, 0x394 }; /* D_8010DA32 = low half of [0] */
s32 D_8010DA40_slot_synch[8] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
s32 D_8010DA60_slot_synch = 0; /* debug camera mode */
s32 D_8010DA64_slot_synch = 0; /* debug text x; D_8010DA66 = low half */
s32 D_8010DA68_slot_synch = 0; /* debug text y; D_8010DA6A = low half */
s32 D_8010DA6C_slot_synch = 0;

Gfx D_8010DA70_slot_synch[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8010DB28_slot_synch[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8010DB48_slot_synch[] = {
    gsSPDisplayList(D_8010DB28_slot_synch),
    gsSPDisplayList(D_8010DA70_slot_synch),
    gsSPEndDisplayList(),
};

Gfx D_8010DB60_slot_synch[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_8010DB48_slot_synch),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

void func_801094E0_slot_synch(u8 player, f32 y, f32 dy);
void func_8010A7D0_slot_synch(omObjData *obj);
void func_8010AA9C_slot_synch(s16 idx, s16 target);
void func_8010AC14_slot_synch(omObjData *obj);
s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *spr, RGBA *color);
s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *spr, u16 model, RGBA *color);
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
s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010D2AC_slot_synch(u16 model, HuSprite_Unk84_Struct *spr, u16 frame, RGBA *color);

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

u16 func_8010A2C4_slot_synch(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

void func_8010A308_slot_synch(s16 grp, s16 member, f32 x, f32 y) {
    HuSprGrp *group = HuSprGrpData[grp];
    HuSprite *spr = HuSprGet(grp, member);

    if (spr->unk_48 != x || spr->unk_4C != y) {
        group->unk_0C = 1;
        spr->unk_48 = x;
        spr->unk_4C = y;
    }
}

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

void func_8010AA9C_slot_synch(s16 idx, s16 target) {
    SsCounter *counter;
    s32 offset = idx * sizeof(SsCounter);

    counter = (SsCounter *)((u8 *)D_8010DF90_slot_synch + offset);
    counter->target = target;
}

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

f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010C39C_slot_synch(f32 t, f32 a, f32 b) {
    return func_8010C1C4_slot_synch(b, a, fabsf(func_8010C0C0_slot_synch(b, a) * t));
}

void func_8010C3FC_slot_synch(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010C428_slot_synch(omObjData *obj) {
    SsPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

s16 func_8010C47C_slot_synch(s32 dirAndFile) {
    s16 id = func_8001F1FC_main(DataRead(dirAndFile), 0x18);

    if (id >= 0) {
        return id;
    }
    return -1;
}

s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;

    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    temp_v0 = func_8001A894_main(0x8C1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_8010D3E0_slot_synch(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_8010DB60_slot_synch));
    gDPPipeSync(temp_v0_2++);
    gDPSetCycleType(temp_v0_2++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0_2++);
    gSPClearGeometryMode(temp_v0_2++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(temp_v0_2++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0_2++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0_2++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0_2++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0_2++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0_2++, G_AC_NONE);
    gDPSetBlendColor(temp_v0_2++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0_2++);
    gDPSetRenderMode(temp_v0_2++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
    if (arg0->unk18 & 0x8000) {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk10 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk10, temp_s0);
    HuMemFree(temp_v0_0);
    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    gSPTexture(temp_v0_2++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0_2++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0_2++, G_TT_RGBA16);
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0_2++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0_2++, arg0->unk0C);
        }
        gDPPipeSync(temp_v0_2++);
        var_a2 = 2;
    } else {
        gDPSetTextureLUT(temp_v0_2++, G_TT_NONE);
        gDPPipeSync(temp_v0_2++);
        var_a2 = (arg0->unk18 & 0x8000) ? 4 : 0;
    }
    switch (arg0->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(temp_v0_2++, 0x02000000, var_a2,
                                   arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_8b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_16b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(temp_v0_2++);
    gSPSegment(temp_v0_2++, 0x01, osVirtualToPhysical(temp_s4->unk44[0]));
    gSPVertex(temp_v0_2++, 0x01000000, 4, 0);
    gSP2Triangles(temp_v0_2++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk14 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk14, temp_s0);
    HuMemFree(temp_v0_0);
    for (var_s1 = 0; var_s1 < D_800D1FF0_main; var_s1++) {
        temp_v0_2 = temp_s4->unk3C->unk00[var_s1 + 1] = HuMemAllocTag(0x100, temp_s4->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg1->r, arg1->g, arg1->b, arg1->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
    HmfModel *model = &HmfModelData[arg1];
    HmfData *src = model->hmf;
    HmfData *temp_s1;
    Gfx *temp_v0_2;
    s32 temp_v0;
    s32 var_s2;

    temp_v0 = func_8001A894_main(model->unk18, NULL, 4);
    temp_s1 = HmfModelData[temp_v0].hmf;
    temp_s1->unk60->unk50 = src->unk60->unk50;
    HuMemFree(temp_s1->unk3C);
    temp_s1->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    temp_s1->unk3C->unk10 = src->unk3C->unk10;
    temp_s1->unk3C->unk14 = src->unk3C->unk14;
    for (var_s2 = 0; var_s2 < D_800D1FF0_main; var_s2++) {
        temp_v0_2 = temp_s1->unk3C->unk00[var_s2 + 1] = HuMemAllocTag(0x100, temp_s1->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg2->r, arg2->g, arg2->b, arg2->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s1->unk3C->unk00[0] = temp_s1->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

void func_8010D2AC_slot_synch(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s3 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s3->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s3->unk3C->unk10));
    gDPSetPrimColor(&temp_s0[3], 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPPipeSync(&temp_s0[4]);
    gSPDisplayList(&temp_s0[5], osVirtualToPhysical(temp_s3->unk3C->unk14));
    gDPPipeSync(&temp_s0[6]);
    gSPEndDisplayList(&temp_s0[7]);
}

s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = temp_s4 * 100.0 * arg2 / 32.0;
    temp_f2 = temp_a1 * 100.0 * arg2 / 32.0;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}
