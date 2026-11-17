#include "common.h"
#include "mallocblock.h"
#include "math.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801059A0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80105B9C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80105C10_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801060C4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801060E8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106190_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E1F0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801065E8_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E218_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106968_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106F48_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106FAC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107080_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107C84_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108840_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108A80_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108CE0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108D1C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108D50_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108E54_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109044_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010910C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109140_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109190_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801091DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010925C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109350_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2C0_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2CC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801094E4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109A00_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109A7C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109AD8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109B34_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109B8C_log_jam);

// m1 lj2
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct LjEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} LjEffect; // Size 0x34

typedef struct LjCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} LjCamera; // Size 0x24

typedef struct LjBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} LjBytes;

typedef union LjPack {
    void *p;
    LjBytes b;
} LjPack;

typedef struct LjCloud {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 grp;
    /* 0x04 */ s16 angle;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 sx;
    /* 0x18 */ f32 sy;
    /* 0x1C */ f32 speed;
    /* 0x20 */ s32 unk20;
} LjCloud; // Size 0x24

typedef struct LjCounter {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 grp;
    /* 0x04 */ s16 timer;
    /* 0x06 */ s16 digit; /* member popping in */
    /* 0x08 */ s16 value;
    /* 0x0A */ s16 shown;
} LjCounter; // Size 0xC

typedef struct LjVec2 {
    f32 x;
    f32 y;
} LjVec2;

#define LJ_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern s32 fontcolor;
extern s8 HmfPauseF;
extern s16 *D_8010E5CC_log_jam; // s16[0x20] sprite/file ids
extern LjCounter *D_8010E5D0_log_jam;
extern LjCloud *D_8010E5D4_log_jam;
extern omObjData *D_8010E5D8_log_jam;
extern LjEffect *D_8010E5DC_log_jam;
extern omObjData *D_8010E5E0_log_jam;
extern LjEffect *D_8010E5E4_log_jam;
extern LjCamera D_8010E5E8_log_jam[2];
extern s32 D_8010E630_log_jam;
extern s32 D_8010E634_log_jam;
extern s32 D_8010E638_log_jam;

/* .data (0x8010DE90..0x8010E1D0). Inner labels the remaining asm uses are undefined_syms.txt aliases. */
Vec D_8010DE90_log_jam[4] = { /* D_8010DE98 = [0].z */
    { -233.0f, 0.0f, 70.0f }, { -131.0f, 0.0f, -5.0f }, { 131.0f, 0.0f, -5.0f }, { 233.0f, 0.0f, 70.0f },
};
Vec D_8010DEC0_log_jam[4] = { /* D_8010DEC8 = [0].z */
    { -170.0f, 0.0f, 40.0f }, { -128.0f, 0.0f, 20.0f }, { 128.0f, 0.0f, 20.0f }, { 170.0f, 0.0f, 40.0f },
};
Vec D_8010DEF0_log_jam[4] = { /* D_8010DEF8 = [0].z */
    { -70.0f, 0.0f, 200.0f }, { -190.0f, 0.0f, 250.0f }, { 190.0f, 0.0f, 250.0f }, { 70.0f, 0.0f, 200.0f },
};
f32 D_8010DF20_log_jam[4] = { 45.0f, 15.0f, -15.0f, -45.0f };
Vec D_8010DF30_log_jam[2] = { /* D_8010DF34 = [0].y, D_8010DF38 = [0].z */
    { -100.0f, 50.0f, 115.0f },
    { 100.0f, 50.0f, 115.0f },
};
RGBA D_8010DF48_log_jam = { 0xE9, 0xDD, 0xA1, 0x80 };
RGBA D_8010DF4C_log_jam = { 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_8010DF50_log_jam[8] = { 0x200A5, 0x300A5, 0x700A5, 0x400A5, 0x500A5, 0x600A5, 0x800A5, 0x9001C };
s32 D_8010DF70_log_jam[8] = { 0x200A6, 0x300A6, 0x700A6, 0x400A6, 0x500A6, 0x600A6, 0x800A6, 0x9001D };
s32 D_8010DF90_log_jam = 0; /* D_8010DF92 = its low half */
s32 D_8010DF94_log_jam[4] = { 0, 1, 2, 3 };
s16 D_8010DFA4_log_jam[4][4] = { { 0, 1, 2, 3 }, { 3, 0, 1, 2 }, { 2, 3, 0, 1 }, { 1, 2, 3, 0 } };
s16 D_8010DFC4_log_jam[4] = { 0, 1, 1, 0 };
s16 D_8010DFCC_log_jam[4] = { 0x12, 0x13, 0x15, 0x14 };
s32 D_8010DFD4_log_jam[8] = { 0x20000, 0x30000, 0x70000, 0x40000, 0x50000, 0x60000, 0x80000, 0x90000 }; /* D_8010DFE8 = [5] */
s32 D_8010DFF4_log_jam[4] = { 0x2F, 0x30, 0x36, 0x37 }; /* D_8010DFF6/D_8010DFFE = low halves of [0]/[2] */
s32 D_8010E004_log_jam[3] = { 3, 4, 5 };
f32 D_8010E010_log_jam[8] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 250.0f, 200.0f, 200.0f };
s32 D_8010E030_log_jam[9] = { 0x340003, 0x340004, 0x340005, 0x340006, 0x340007, 0x340008, 0x340009, 0x34000A, 0x34000B };
LjVec2 D_8010E054_log_jam[5] = { /* cloud start positions; D_8010E058 = [0].y */
    { 120.0f, 30.0f }, { 360.0f, 45.0f }, { 0.0f, 52.0f }, { 240.0f, 60.0f }, { 480.0f, 75.0f },
};
f32 D_8010E07C_log_jam[5] = { 0.7f, 0.6f, 0.55f, 0.47f, 0.4f }; /* cloud scales */
s16 D_8010E090_log_jam[2] = { 38, 282 }; /* counter x */
s32 D_8010E094_log_jam = 0; /* debug camera mode */
s32 D_8010E098_log_jam = 0; /* debug text x; D_8010E09A = low half */
s32 D_8010E09C_log_jam = 0; /* debug text y; D_8010E09E = low half */

Gfx D_8010E0A0_log_jam[] = {
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

Gfx D_8010E158_log_jam[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8010E178_log_jam[] = {
    gsSPDisplayList(D_8010E158_log_jam),
    gsSPDisplayList(D_8010E0A0_log_jam),
    gsSPEndDisplayList(),
};

Gfx D_8010E190_log_jam[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_8010E178_log_jam),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

u16 func_8010A300_log_jam(s32 dirAndFile);
void func_8010A4C0_log_jam(omObjData *obj);
void func_8010A880_log_jam(omObjData *obj);
void func_8010AD04_log_jam(omObjData *obj);
s32 func_8010CB64_log_jam(HuSprite_Unk84_Struct *spr, RGBA *color);
s32 func_8010D74C_log_jam(HuSprite_Unk84_Struct *spr, u16 model, RGBA *color);
void func_8010B86C_log_jam(omObjData *obj);
void func_8010BCA8_log_jam(s32 idx);
void func_8010BE94_log_jam(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010C084_log_jam(s32 idx);
f32 func_8010C1D8_log_jam(f32 a, f32 b);
f32 func_8010C2DC_log_jam(f32 target, f32 cur, f32 step);
f32 func_8010C49C_log_jam(f32 t, f32 a, f32 b);
f32 func_8010C4B4_log_jam(f32 t, f32 a, f32 b);
f32 fabsf(f32);
f64 fabs(f64);
f64 fmod(f64, f64);
s32 func_8010DA84_log_jam(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010D950_log_jam(u16 model, HuSprite_Unk84_Struct *spr, u16 frame, RGBA *color);
void func_8010C5DC_log_jam(omObjData *obj, s16 slot, s16 frames);
void func_800E4BA4_minigame(u8 mdl);
typedef f32 Matrix4f[4][4];
extern Matrix4f *D_800D1358_main; /* matrix table being filled */
extern s16 *D_800D04B4_main;      /* per matrix: its motion object */
extern s16 D_800CD1B0_main;       /* matrices written */
extern s16 D_800D138A_main;       /* matrix stack depth */
extern Matrix4f D_800D5A00_main[]; /* matrix stack */
void func_8002DFF8_main(HmfData *, f32, D_800CCF58_main_Struct *, s32);
void func_8002EAC0_main(HmfData *, f32, f32);
s16 func_8002C834_main(HmfData *, char *);
void func_8008A070_main(Matrix4f);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_80016C2C_main(HmfData *arg0, s16 arg1, s16 arg2);
void func_8010C8E0_log_jam(s16 mdl, char *part, Matrix4f *out);

void func_8010A0B0_log_jam(omObjData *obj) {
    LjCloud *cloud;
    HuSprite *spr;
    f32 wave;
    s16 i;

    for (i = 0, cloud = D_8010E5D4_log_jam; i < 5; i++, cloud++) {
        wave = sindf(cloud->angle);
        cloud->x += cloud->speed * ((f32)(u8)(rand8() % 100) * 0.01 * 0.4f + 0.6f);
        cloud->sx = cloud->scale + 0.075f + wave * 0.075f;
        cloud->sy = cloud->scale + 0.075f - wave * 0.075f;
        if (cloud->x <= -64.0f) {
            cloud->x += 416.0f;
        } else if (cloud->x > 384.0f) {
            cloud->x -= 320.0f;
        }
        HuSprScaleSet(cloud->grp, 0, cloud->sx, cloud->sy);
        HuSprScaleSet(cloud->grp, 1, cloud->sx, cloud->sy);
        spr = HuSprGet(cloud->grp, 0);
        spr->unk_48 = cloud->x;
        spr->unk_4C = cloud->y;
        spr = HuSprGet(cloud->grp, 1);
        spr->unk_48 = cloud->x;
        spr->unk_4C = cloud->y;
        cloud->angle += (u8)(rand8() % 7) + 2;
        if (cloud->angle >= 360) {
            cloud->angle -= 360;
        }
    }
}

u16 func_8010A300_log_jam(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

void func_8010A344_log_jam(void) {
    LjCounter *counter;
    s32 x;
    s32 i;
    s32 j;

    D_8010E5CC_log_jam[3] = func_8010A300_log_jam(0x34000F);
    counter = D_8010E5D0_log_jam = HuMemAllocTag(sizeof(LjCounter) * 2, 0x7918);
    for (i = 0; i < 2; i++, counter++) {
        x = D_8010E090_log_jam[i];
        memset(counter, 0, sizeof(LjCounter));
        counter->id = i;
        counter->grp = HuSprGrpCreate(10, 0);
        for (j = 0; j < 10; j++) {
            func_80055024_main(counter->grp, j, D_8010E5CC_log_jam[3], 0);
            func_800550F4_main(counter->grp, j, 0);
            func_80054FF8_main(counter->grp, j, 0);
            func_80055458_main(counter->grp, j, 0x100);
            HuSprAttrSet(counter->grp, j, 0x9000);
            func_80054904_main(counter->grp, j, x, 0x1C);
            if (i == 0) {
                x += 16;
            } else {
                x -= 16;
            }
        }
    }
    omAddObj(0x1E, 0, 0, -1, func_8010A4C0_log_jam);
}

void func_8010A4C0_log_jam(omObjData *obj) {
    LjCounter *counter;
    f32 t;
    s32 fives;
    s32 count;
    s32 i;
    s32 j;

    for (i = 0, counter = D_8010E5D0_log_jam; i < 2; i++, counter++) {
        fives = (s16)(counter->value / 5);
        count = fives + (s16)(counter->value % 5);
        if (counter->shown != counter->value) {
            for (j = 0; j < 10; j++) {
                func_80055458_main(counter->grp, j, 0x100);
                HuSprScaleSet(counter->grp, j, 1.0f, 1.0f);
            }
            counter->timer = 15;
            if (count != 0) {
                counter->digit = count - 1;
            }
        }
        if (counter->timer > 0) {
            if (counter->timer == 1) {
                t = 0.0f;
            } else {
                t = counter->timer / 15.0f;
            }
            func_80055458_main(counter->grp, counter->digit, (s32)((1.0f - t) * 256.0f));
            HuSprScaleSet(counter->grp, counter->digit, t + 1.0f, t + 1.0f);
            counter->timer--;
        }
        for (j = 0; j < 10; j++) {
            if (j < fives) {
                func_80054FF8_main(counter->grp, j, 1);
            } else {
                func_80054FF8_main(counter->grp, j, 0);
            }
            if (j < count) {
                HuSprAttrReset(counter->grp, j, 0x8000);
            } else {
                HuSprAttrSet(counter->grp, j, 0x8000);
            }
        }
        counter->shown = counter->value;
    }
}

void func_8010A6FC_log_jam(s16 idx, s16 value) {
    LjCounter *counter = &D_8010E5D0_log_jam[idx];

    counter->value = value;
}

void func_8010A724_log_jam(void) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[6] = func_8010A300_log_jam(0xB));
    D_8010E5D8_log_jam = omAddObj(0x1E, 0, 0, -1, func_8010A880_log_jam);
    D_8010E5DC_log_jam = effect = HuMemAllocTag(sizeof(LjEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(spr, &D_8010DF48_log_jam);
        } else {
            effect->model = func_8010D74C_log_jam(spr, D_8010E5DC_log_jam->model, &D_8010DF48_log_jam);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010A880_log_jam(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010E5CC_log_jam[6]);
    effect = D_8010E5DC_log_jam;
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
                func_8010D950_log_jam(effect->model, spr, (s32)effect->frame, &effect->color);
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

s32 func_8010A9D4_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[6]);
    for (i = 0, effect = D_8010E5DC_log_jam; i < 8; i++, effect++) {
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
            func_8010D950_log_jam(effect->model, spr, 0, &effect->color);
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

void func_8010ABA4_log_jam(void) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[7] = func_8010A300_log_jam(0x340012));
    D_8010E5E0_log_jam = omAddObj(0x1E, 0, 0, -1, func_8010AD04_log_jam);
    D_8010E5E4_log_jam = effect = HuMemAllocTag(sizeof(LjEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(spr, &D_8010DF48_log_jam);
        } else {
            effect->model = func_8010D74C_log_jam(spr, D_8010E5E4_log_jam->model, &D_8010DF48_log_jam);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010AD04_log_jam(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010E5CC_log_jam[7]);
    effect = D_8010E5E4_log_jam;
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
                func_8010D950_log_jam(effect->model, spr, (s32)effect->frame, &effect->color);
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

s32 func_8010AE58_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[7]);
    for (i = 0, effect = D_8010E5E4_log_jam; i < 8; i++, effect++) {
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
            if (color != NULL) {
                effect->color = *color;
            } else {
                memset(&effect->color, 0xFF, 4);
            }
            effect->speed = speed;
            effect->frame = 0.0f;
            func_8010D950_log_jam(effect->model, spr, 0, &effect->color);
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

void func_8010B04C_log_jam(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = 126.8f;
    Center.z = -0.8f;
    CRot.x = 350.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1062.0f;
    func_8010BCA8_log_jam(0);
    func_8010BCA8_log_jam(1);
    D_8010E630_log_jam = D_8010E634_log_jam = D_8010E638_log_jam = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010B86C_log_jam);
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

void func_8010B17C_log_jam(void) {
    LjCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010E094_log_jam) {
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
                func_8010BE94_log_jam(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010E098_log_jam++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010E098_log_jam--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010E09C_log_jam++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010E09C_log_jam--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 104, D_800D5218_main);
            break;
        case 3:
            D_8010E094_log_jam = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010E094_log_jam == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010E094_log_jam++ >= 4) {
            D_8010E094_log_jam = 0;
        }
    }
}

void func_8010B86C_log_jam(omObjData *obj) {
    f32 t;

    if (D_8010E634_log_jam <= 0) {
        func_8010C084_log_jam(0);
        D_8010E638_log_jam = 0;
        return;
    }
    if (D_8010E630_log_jam == 0) {
        Center.x = D_8010E5E8_log_jam[0].center.x;
        Center.y = D_8010E5E8_log_jam[0].center.y;
        Center.z = D_8010E5E8_log_jam[0].center.z;
        CRot.x = D_8010E5E8_log_jam[0].rot.x;
        CRot.y = D_8010E5E8_log_jam[0].rot.y;
        CRot.z = D_8010E5E8_log_jam[0].rot.z;
        CZoom = D_8010E5E8_log_jam[0].zoom;
        LJ_WRAP(CRot.x);
        LJ_WRAP(CRot.y);
        LJ_WRAP(CRot.z);
        D_8010E634_log_jam = 0;
    } else {
        t = (f32)D_8010E630_log_jam / (f32)D_8010E634_log_jam;
        Center.x = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.x, D_8010E5E8_log_jam[1].center.x);
        Center.y = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.y, D_8010E5E8_log_jam[1].center.y);
        Center.z = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.z, D_8010E5E8_log_jam[1].center.z);
        CRot.x = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.x, D_8010E5E8_log_jam[1].rot.x);
        CRot.y = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.y, D_8010E5E8_log_jam[1].rot.y);
        CRot.z = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.z, D_8010E5E8_log_jam[1].rot.z);
        CZoom = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].zoom, D_8010E5E8_log_jam[1].zoom);
        LJ_WRAP(CRot.x);
        LJ_WRAP(CRot.y);
        LJ_WRAP(CRot.z);
        if (D_8010E630_log_jam > 0) {
            D_8010E630_log_jam--;
        } else {
            D_8010E630_log_jam++;
        }
    }
    D_8010E638_log_jam = 1;
    func_8010C084_log_jam(0);
}

void func_8010BCA8_log_jam(s32 idx) {
    LJ_WRAP(CRot.x);
    LJ_WRAP(CRot.y);
    LJ_WRAP(CRot.z);
    D_8010E5E8_log_jam[idx].center.x = Center.x;
    D_8010E5E8_log_jam[idx].center.y = Center.y;
    D_8010E5E8_log_jam[idx].center.z = Center.z;
    D_8010E5E8_log_jam[idx].rot.x = CRot.x;
    D_8010E5E8_log_jam[idx].rot.y = CRot.y;
    D_8010E5E8_log_jam[idx].rot.z = CRot.z;
    D_8010E5E8_log_jam[idx].zoom = CZoom;
    D_8010E5E8_log_jam[idx].unk1C = D_8010E5E8_log_jam[idx].unk20 = 0.0f;
}

void func_8010BE94_log_jam(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010E630_log_jam = frames - 1;
        D_8010E634_log_jam = frames;
        if (cx != 65535.0f) {
            D_8010E5E8_log_jam[0].center.x = cx;
        } else {
            D_8010E5E8_log_jam[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010E5E8_log_jam[0].center.y = cy;
        } else {
            D_8010E5E8_log_jam[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010E5E8_log_jam[0].center.z = cz;
        } else {
            D_8010E5E8_log_jam[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.x = rx;
        } else {
            D_8010E5E8_log_jam[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.y = ry;
        } else {
            D_8010E5E8_log_jam[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.z = rz;
        } else {
            D_8010E5E8_log_jam[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010E5E8_log_jam[0].zoom = zoom;
        } else {
            D_8010E5E8_log_jam[0].zoom = CZoom;
        }
        func_8010BCA8_log_jam(1);
    }
}

void func_8010C084_log_jam(s32 idx) {
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

f32 func_8010C1D8_log_jam(f32 a, f32 b) {
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

f32 func_8010C2DC_log_jam(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    LJ_WRAP(target);
    LJ_WRAP(cur);
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
    LJ_WRAP(v);
    return v;
}

f32 func_8010C49C_log_jam(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010C4B4_log_jam(f32 t, f32 a, f32 b) {
    return func_8010C2DC_log_jam(b, a, fabsf(func_8010C1D8_log_jam(b, a) * t));
}

f32 func_8010C514_log_jam(f32 target, f32 cur, f32 step) {
    if (fabs(target - cur) < step) {
        return target;
    }
    if (target < cur) {
        step = -step;
    }
    return cur + step;
}

void func_8010C55C_log_jam(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010C588_log_jam(omObjData *obj) {
    LjPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

void func_8010C5DC_log_jam(omObjData *obj, s16 slot, s16 frames) {
    HmfModel *model = &HmfModelData[obj->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *mtn;

    func_8001C624_main(obj->model[0], obj->motion[slot], 0, frames, 0);
    mtn = &((func_800E1BA8_minigame_ObjData *)obj->data)->unkE8[slot];
    if (mtn->unk00 & 1) {
        model->unk05 = 2;
    } else {
        model->unk05 = 0;
    }
    model->unk54 = mtn->unk02;
}

void func_8010C6A4_log_jam(omObjData *obj, s16 slot, s16 frame) {
    HmfModel *model = &HmfModelData[obj->model[0]];

    func_8010C5DC_log_jam(obj, slot, 5);
    model->unk4C = frame;
}

void func_8010C714_log_jam(omObjData *obj, s16 slot, s16 frame) {
    HmfModel *model = &HmfModelData[obj->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *mtn;

    model->unk02 = obj->motion[slot];
    model->unk48 = model->unk40 = model->unk44 = 1.0f;
    model->unk04 = 0xFF;
    model->unk40 = frame;
    mtn = &((func_800E1BA8_minigame_ObjData *)obj->data)->unkE8[slot];
    if (mtn->unk00 & 1) {
        model->unk03 = 2;
    } else {
        model->unk03 = 0;
    }
    model->unk48 = mtn->unk02;
}

void func_8010C7D0_log_jam(omObjData *obj) {
    HmfModel *model = &HmfModelData[obj->model[0]];

    model->unk44 = 0.0f;
}

void func_8010C7F8_log_jam(omObjData *obj) {
    f32 frame = 0.0f;
    HmfModel *model = &HmfModelData[obj->model[0]];

    if (model->unk04 != 0xFF) {
        if (HmfPauseF == 0) {
            frame = model->unk0E + 2;
        }
        if (model->unk0C <= frame) {
            model->unk02 = model->unk04;
            model->unk40 = model->unk4C;
            model->unk03 = model->unk05;
            model->unk48 = model->unk54;
            model->unk04 = 0xFF;
            model->unk44 = 1.0f;
        }
    }
}

void func_8010C8B0_log_jam(omObjData *obj) {
    if (obj->model[6] != -1) {
        func_800E4BA4_minigame(obj->model[6]);
    }
}

void func_8010C8E0_log_jam(s16 mdl, char *part, Matrix4f *out) {
    HmfModel *model = &HmfModelData[mdl];
    HmfData *hmf = model->hmf;
    s16 idx = func_8002C834_main(hmf, part);
    D_800CCF58_main_Struct *anim = &D_800CCF58_main[HmfModelData[mdl].unk02];
    s16 parts[4]; /* retail's frame leaves 8 bytes here, as in func_80016B00_main */

    D_800D1358_main = out;
    D_800D04B4_main = parts;
    D_800CD1B0_main = 0;
    if (model->unk06 != 0xFF) {
        hmf->unk94 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk06];
        hmf->unkAC = model->unk58;
    } else {
        hmf->unk94 = NULL;
    }
    if (model->unk04 != 0xFF && model->unk0C != 0) {
        hmf->unk90 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk04];
        hmf->unkA4 = model->unk4C;
        hmf->unkA8 = (f32)model->unk0E / (f32)model->unk0C;
    } else {
        hmf->unk90 = NULL;
    }
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(hmf, model->unk40, anim, 1);
    if (hmf->unk90 != NULL) {
        func_8002EAC0_main(hmf, hmf->unkA4, hmf->unkA8);
    }
    if (hmf->unk94 != NULL) {
        func_8002DFF8_main(hmf, hmf->unkAC, (D_800CCF58_main_Struct *)hmf->unk94, 0);
    }
    D_800D138A_main = 0;
    func_80016C2C_main(hmf, 0, idx);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void func_8010CAC0_log_jam(omObjData *obj, char *part, Matrix4f out) {
    Matrix4f m;
    Matrix4f partMtx;

    func_8008A070_main(m);
    func_80017C10_main((Mtx *)m, obj->trans.x, obj->trans.y, obj->trans.z);
    func_80017D24_main(m, obj->rot.x, obj->rot.y, obj->rot.z);
    func_80017CD0_main(m, obj->scale.x, obj->scale.y, obj->scale.z);
    func_8010C8E0_log_jam(obj->model[0], part, &partMtx);
    func_80018044_main(partMtx, m, out);
}

s32 func_8010CB64_log_jam(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
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
    func_8010DA84_log_jam(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_8010E190_log_jam));
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
    gDPSetRenderMode(temp_v0_2++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
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

s32 func_8010D74C_log_jam(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
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

void func_8010D950_log_jam(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
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

s32 func_8010DA84_log_jam(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
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
