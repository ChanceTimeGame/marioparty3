#include "common.h"

// event e3
typedef struct {
    /* 0x00 */ s8 state;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 pos;
    /* 0x0C */ f32 target;
    /* 0x10 */ s16 top;
    /* 0x12 */ s16 next;
    /* 0x14 */ s16 anim[3];
    /* 0x1A */ s8 count;
    /* 0x1B */ s8 items[13];
} ChanceWheel; /* sizeof 0x28 */

typedef struct {
    s16 x;
    s16 y;
} ChancePos16;

void func_80032FC0_main(s16, u8, u8);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s16 func_8000B0D4_main(s32, s32);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800F5E30_shared_board(s32 arg0, s32 arg1);
void func_800F5F4C_shared_board(s32 arg0, s32 arg1);
void func_800F5F60_shared_board(void);
void func_800F5F7C_shared_board(void);
void func_800F7108_shared_board(void);
s32 func_800EDC40_shared_board(void);
void MBPlayerCoinAdd(s32 playerNo, s32 amount);

void func_80108704_chancetime(void);
s32 func_8010872C_chancetime(void);
void func_80108A88_chancetime(void);
void func_80108B50_chancetime(void);
void func_8010BF48_chancetime(void);
void func_80106F10_chancetime(void);
void func_8010705C_chancetime(void);
void func_801071A8_chancetime(void);

void func_8010C5F4_chancetime(omObjData *obj);
void func_8010C610_chancetime(omObjData *obj);
void func_8010C870_chancetime(omObjData *obj);
void func_8010C98C_chancetime(void);
void func_8010C994_chancetime(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010CF78_chancetime(s8 set);
void func_8010D320_chancetime(omObjData *obj);
void func_8010D6A4_chancetime(s8 wheel);
void func_8010D92C_chancetime(s8 wheel);
void func_8010DAB0_chancetime(void);
void func_8010DB1C_chancetime(s8 wheel);
void func_8010DF68_chancetime(void);
void func_8010DF70_chancetime(omObjData *obj);
void func_8010DFA4_chancetime(omObjData *obj);
void func_8010E1E0_chancetime(omObjData *obj);
void func_8010E210_chancetime(omObjData *obj);
void func_8010E280_chancetime(omObjData *obj);
void func_8010E4D0_chancetime(omObjData *obj);
void func_8010F1F8_chancetime(omObjData *obj);
void func_8010F984_chancetime(omObjData *obj);
void func_8010F42C_chancetime(omObjData *obj);
void func_8010F44C_chancetime(s32 prize, s32 total, s32 amount);

extern s8 D_8010FB80_chancetime;
extern s8 D_8010FB81_chancetime;
extern ChancePos16 D_8010FB84_chancetime;
extern f32 D_8010FB88_chancetime;
extern f32 D_8010FB8C_chancetime;
extern Vec D_8010FB94_chancetime[];
extern char *D_8010FBD8_chancetime[];
extern s32 D_8010FBF0_chancetime;
extern s32 D_8010FBF4_chancetime[3];
extern s32 D_8010FC00_chancetime;
extern s32 D_8010FC10_chancetime;
extern s32 D_8010FC14_chancetime;
extern s32 D_8010FC18_chancetime;
extern s32 D_8010FC1C_chancetime;
extern s32 D_8010FAE4_chancetime;

extern s16 D_8010FE90_chancetime;
extern s16 D_8010FE92_chancetime;
extern s16 D_8010FE94_chancetime[3];
extern s16 D_8010FE9A_chancetime;
extern HuSprite *D_8010FE9C_chancetime;
extern void *D_8010FEA0_chancetime;
extern void *D_8010FEA4_chancetime;
extern ChancePos16 D_8010FEA8_chancetime;
extern s16 D_8010FEB0_chancetime[3][3];
extern s32 D_8010FEC4_chancetime;
extern s8 D_8010FEC8_chancetime;
extern s8 D_8010FEC9_chancetime;
extern ChanceWheel D_8010FED0_chancetime[3];
typedef struct {
    s32 state;
    s32 timer;
} ChanceFx;

extern s32 D_8010FF48_chancetime[3];
extern ChanceFx D_8010FF60_chancetime[20];
extern s16 D_8010FF4A_chancetime;
extern s16 D_8010FF4E_chancetime;
extern s16 D_8010FF52_chancetime;
extern s8 D_80110000_chancetime;
extern s32 D_80110004_chancetime;
extern s16 D_80110006_chancetime;
extern s32 D_80110008_chancetime;
extern s16 D_80110010_chancetime[10];
extern s16 D_80110028_chancetime[20];
extern omObjData *D_80110080_chancetime;
extern void (*D_80110084_chancetime)(omObjData *);
extern omObjData *D_801100C8_chancetime;
extern void (*D_801100CC_chancetime)(omObjData *);
extern s8 D_801100D0_chancetime[4];
extern s8 D_801100DC_chancetime;
extern s8 D_801100DD_chancetime[3];
extern s16 D_800D10F2_main;

// NON_MATCHING: the sign extension of the sprite id is done in s1 instead of v0; logic checked
#ifdef NON_MATCHING
void func_8010BF80_chancetime(void) {
    omObjData *obj;
    void *data;
    HuSprite *spr;
    s32 sprId;
    s16 grp;
    s8 i;

    obj = omAddObj(20, 16, 0, -1, NULL);
    D_801100C8_chancetime = obj;
    obj->model[1] = func_8000B108_main(0x1C0009, 0x229);
    data = DataRead(0x1C0002);
    D_8010FEB0_chancetime[0][0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8010FBD8_chancetime[0]);
    func_80032FC0_main(D_8010FEB0_chancetime[0][0], 1, 1);
    func_80032FF8_main(D_8010FEB0_chancetime[0][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        D_8010FEB0_chancetime[0][i] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8010FEB0_chancetime[0][0], 0,
                                                         D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[0][i], 1, 1);
        func_80032FF8_main(D_8010FEB0_chancetime[0][i], 0);
    }
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C8A8_main(obj->model[1], 1);
    obj->model[2] = func_8000B108_main(0x1C0009, 0x229);
    for (i = 0; i < 3; i++) {
        D_8010FEB0_chancetime[1][i] = func_80032694_main(HmfModelData[obj->model[2]].hmf, D_8010FEB0_chancetime[0][0], 0,
                                                         D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[1][i], 1, 1);
        func_80032FF8_main(D_8010FEB0_chancetime[1][i], 0);
    }
    func_8001C448_main(obj->model[2]);
    func_8001C514_main(obj->model[2]);
    func_8001C814_main(obj->model[2], 2, 0);
    func_8001C8A8_main(obj->model[2], 1);
    obj->model[3] = func_8000B108_main(0x1C0009, 0x229);
    data = DataRead(0x1C0003);
    D_8010FEB0_chancetime[2][0] = HmfAnimCreate(HmfModelData[obj->model[3]].hmf, data, 0, D_8010FBD8_chancetime[0]);
    func_80032FC0_main(D_8010FEB0_chancetime[2][0], 1, 1);
    func_80032FF8_main(D_8010FEB0_chancetime[2][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        D_8010FEB0_chancetime[2][i] = func_80032694_main(HmfModelData[obj->model[3]].hmf, D_8010FEB0_chancetime[2][0], 0,
                                                         D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[2][i], 1, 1);
        func_80032FF8_main(D_8010FEB0_chancetime[2][i], 0);
    }
    func_8001C448_main(obj->model[3]);
    func_8001C514_main(obj->model[3]);
    func_8001C814_main(obj->model[3], 2, 0);
    func_8001C8A8_main(obj->model[3], 1);
    sprId = func_8000B838_main(0x1C0000);
    D_8010FE92_chancetime = sprId;
    grp = HuSprGrpCreate(1, 0);
    HuSprAttrSet(grp, 0, 0x8000);
    func_80055024_main(grp, 0, sprId, 0);
    spr = HuSprGet(grp, 0);
    D_8010FE9C_chancetime = spr;
    D_8010FEA0_chancetime = spr->unk_84->unk08;
    D_8010FEA4_chancetime = spr->unk_84->unk0C;
    D_8010FEA8_chancetime.x = spr->unk_84->unk14;
    D_8010FEA8_chancetime.y = spr->unk_84->unk16;
    D_8010FE90_chancetime = func_8001AC8C_main(0, func_8010C994_chancetime, 2);
    func_8001C8A8_main(D_8010FE90_chancetime, 1);
    data = DataRead(0x1C0007);
    for (i = 0; i < 3; i++) {
        D_8010FE94_chancetime[i] = InitEspriteSlot(func_80055810_main(data), 0, 0);
        func_8000BB94_main(D_8010FE94_chancetime[i]);
    }
    HuMemMemoryFreePerm(data);
    D_8010FE9A_chancetime = InitEspriteSlot(func_8000B838_main(0x1C0004), 0, 0);
    func_8000BB94_main(D_8010FE9A_chancetime);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], -111.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[2], 119.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[3], 3.0f, 265.0f, -541.0f);
    func_8010CF78_chancetime(D_801100DC_chancetime);
    func_8010DAB0_chancetime();
    omPrcSetDestructor(0, func_8010C98C_chancetime);
    D_801100CC_chancetime = func_8010C5F4_chancetime;
    while (TRUE) {
        D_801100CC_chancetime(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010BF80_chancetime);
#endif

void func_8010C5F4_chancetime(omObjData *obj) {
    func_8010D320_chancetime(obj);
}

void func_8010C610_chancetime(omObjData *obj) {
    Vec pos;
    Vec2f screen;

    D_8010FB8C_chancetime += 1.2f;
    D_8010FB8C_chancetime = (D_8010FB8C_chancetime > 30.0f) ? 30.0f : D_8010FB8C_chancetime;
    if ((D_8010FB88_chancetime -= D_8010FB8C_chancetime) < 0.0f) {
        D_8010FB8C_chancetime = D_8010FB8C_chancetime * -0.1f;
        D_8010FB88_chancetime = 0.0f;
        if (D_8010FC00_chancetime == 0) {
            func_80108704_chancetime();
            D_8010FC00_chancetime = 1;
        }
        if (D_8010FB8C_chancetime >= -0.24000001f) {
            D_8010FC00_chancetime = 0;
            D_801100CC_chancetime = func_8010C870_chancetime;
            D_8010FB88_chancetime = 0.0f;
            return;
        }
    }
    pos.x = 0.0f;
    pos.y = (D_8010FB94_chancetime[0].x + D_8010FB88_chancetime) - 168.0f;
    pos.z = D_8010FB94_chancetime[0].y;
    Hu3DCam3DToScreen(0, &pos, &screen);
    D_8010FB84_chancetime.x = 74;
    D_8010FB84_chancetime.y = (screen.y - 120.0f) + 25.0f;
    func_8000BBD4_main(D_8010FE9A_chancetime, 161, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[0], D_8010FB84_chancetime.x + 51, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[1], D_8010FB84_chancetime.x + 124, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[2], D_8010FB84_chancetime.x + 87, D_8010FB84_chancetime.y + 116);
}

void func_8010C870_chancetime(omObjData *obj) {
    D_8010FB84_chancetime.x = 74;
    D_8010FB84_chancetime.y = 25;
    func_8000BBD4_main(D_8010FE9A_chancetime, 161, 71);
    func_8000BBD4_main(D_8010FE94_chancetime[0], D_8010FB84_chancetime.x + 51, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[1], D_8010FB84_chancetime.x + 124, D_8010FB84_chancetime.y + 46);
    func_8000BBD4_main(D_8010FE94_chancetime[2], D_8010FB84_chancetime.x + 87, D_8010FB84_chancetime.y + 116);
    if (func_8010872C_chancetime() == 1) {
        D_8010FB88_chancetime = 600.0f;
        D_8010FB8C_chancetime = 0.0f;
        D_8010FB80_chancetime = 0;
        D_8010FB81_chancetime = 1;
        D_801100CC_chancetime = func_8010C5F4_chancetime;
    }
}

void func_8010C98C_chancetime(void) {
}

void func_8010C994_chancetime(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *g;
    s16 s[4];
    s16 t[2];
    s16 x;
    s16 y;
    s16 w;
    s16 row;
    s16 rows;
    s16 k;
    s16 tw = D_8010FEA8_chancetime.x;
    s16 th = D_8010FEA8_chancetime.y;
    s16 px = D_8010FB84_chancetime.x;
    s16 py = D_8010FB84_chancetime.y;

    if ((((px + tw) < 0) | (px >= 320)) != 0) {
        return;
    }
    if ((((py + th) < 0) | (py >= 240)) != 0) {
        return;
    }
    s[0] = (px >= 0) ? 0 : -px;
    s[1] = (px + tw <= 320) ? tw : 320 - px;
    if (px < 0) {
        x = 0;
    } else if (px >= 319) {
        x = 319;
    } else {
        x = px;
    }
    w = s[1] - s[0];
    t[0] = (py >= 0) ? 0 : -py;
    t[1] = (py + th <= 240) ? th : 240 - py;
    if (py < 0) {
        y = 0;
    } else if (py >= 319) {
        y = 319;
    } else {
        y = py;
    }
    g = *gfx;
    gDPPipeSync(g++);
    gDPSetScissor(g++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                                  G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 255);
    gDPSetRenderMode(g++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gDPSetCombineMode(g++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureLUT(g++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(g++, D_8010FEA4_chancetime);
    rows = 4;
    k = 0;
    for (row = t[0]; row < t[1]; row += rows) {
        if (row + rows > t[1]) {
            rows = t[1] - row;
        }
        gDPLoadTextureTile(g++, D_8010FEA0_chancetime, G_IM_FMT_CI, G_IM_SIZ_8b, tw, 0, s[0], row,
                           s[1] - 1, row + rows - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, w << 2, rows << 2);
        gSPTextureRectangle(g++, x << 2, (k + y) << 2, (w + x) << 2, (k + rows + y) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
        k += rows;
    }
    gDPSetScissor(g++, G_SC_NON_INTERLACE, 104, 52, 215, 163);
    *gfx = g;
}

void func_8010CF78_chancetime(s8 set) {
    static const s8 D_8010FC98_chancetime[3][13] = {
        { 4, 2, 8, 3, 7, 4, 8, 2, 3, 0, 3, 5, 8 },
        { 0, 3, 6, 1, 8, 7, 2, 8, 4, 5, 0, 7, 2 },
        { 1, 7, 5, 4, 7, 1, 0, 6, 2, 0, 7, 8, 6 },
    };
    s8 i;
    s8 j;
    s8 k;

    D_8010FBF0_chancetime = 0;
    for (i = 0; i < 3; i++) {
        D_8010FBF4_chancetime[i] = 0;
        D_801100DD_chancetime[i] = -1;
        D_8010FED0_chancetime[i].state = 0;
        D_8010FED0_chancetime[i].top = 2;
        D_8010FED0_chancetime[i].next = 4;
        D_8010FED0_chancetime[i].speed = 0.0f;
        D_8010FED0_chancetime[i].target = -1.0f;
    }
    for (i = 0; i < 2; i++) {
        k = rand8() & 3;
        for (j = 0; j < 4; j++) {
            D_8010FED0_chancetime[i].items[k] = GwPlayer[D_801100D0_chancetime[j]].chr;
            k++;
            if (k >= 4) {
                k = 0;
            }
        }
        D_8010FED0_chancetime[i].count = 4;
    }
    k = rand8() % 13;
    for (j = 0; j < 13; j++) {
        D_8010FED0_chancetime[2].items[k] = D_8010FC98_chancetime[set][j];
        k++;
        if (k >= 13) {
            k = 0;
        }
    }
    D_8010FED0_chancetime[2].count = 13;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            D_8010FED0_chancetime[i].anim[j] = D_8010FEB0_chancetime[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            func_8003302C_main(D_8010FED0_chancetime[i].anim[j], D_8010FED0_chancetime[i].items[2 - j]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCE8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCF8_chancetime);

// NON_MATCHING: one register (top is stored from the s16 temp instead of the copy in s1); logic checked
// decomp-permuter
void func_8010D320_chancetime(omObjData *obj)
{
  static const f32 D_8010FD08_chancetime[3][2] = {{10.0f, 10.0f}, {20.0f, 20.0f}, {40.0f, 40.0f}};
  static const s32 D_8010FD20_chancetime[3][2] = {{125, 71}, {198, 71}, {161, 141}};
  static const Vec D_8010FD38_chancetime[3] = {{-111.0f, 486.0f, -541.0f}, {119.0f, 486.0f, -541.0f}, {3.0f, 265.0f, -541.0f}};
  s16 n;
  s16 k;
  ChanceWheel *w;
  s8 i;
  s8 j;
  for (i = 0; i < 3; i++)
  {
    w = &D_8010FED0_chancetime[i];
    if (w->state == 4)
    {
      w->speed += D_8010FD08_chancetime[D_8010FBF0_chancetime - 1][0];
      w->speed = (w->speed > D_8010FD08_chancetime[D_8010FBF0_chancetime - 1][1]) ? (D_8010FD08_chancetime[D_8010FBF0_chancetime - 1][1]) : (w->speed);
    }
    if (w->state == 1)
    {
      w->target = (((s32) (w->pos / 100.0f)) + 1) * 100.0f;
      w->state = 2;
    }
    w->pos += w->speed;
    w->speed *= 0.98f;
    if ((w->state == 2) && (w->pos >= w->target))
    {
      w->pos = w->target;
      w->speed = 0.0f;
      w->state = 3;
    }
    if (w->pos >= 200.0f)
    {
      w->pos -= 200.0f;
      n = w->next;
      if (n >= w->count)
      {
        n -= w->count;
      }
      w->next = n;
      k = n;
      w->top = k;
      for (j = 0; j < 3; j++)
      {
        func_8003302C_main(w->anim[j], w->items[k]);
        k = (((s16) (k - 1)) < 0) ? (w->count + ((s16) (k - 1))) : ((s16) (k - 1));
      }

      w->next += 2;
      w->next = (w->next >= w->count) ? (w->next - w->count) : (w->next);
    }
    if (w->state == 3)
    {
      n = (w->top + ((s32) (w->pos / 100.0f))) - 2;
      n = (n < 0) ? (w->count + n) : (n);
      n = (n >= w->count) ? (n - w->count) : (n);
      D_801100DD_chancetime[i] = w->items[n];
      w->state = 0;
    }
    k = obj->model[i + 1];
    Hu3DModelPosSet(k, D_8010FD38_chancetime[i].x, D_8010FD38_chancetime[i].y - w->pos, D_8010FD38_chancetime[i].z);
  }

}

void func_8010D6A4_chancetime(s8 wheel) {
    s8 i;
    s8 n;

    D_8010FBF0_chancetime++;
    switch (D_8010FBF0_chancetime) {
    case 1:
        D_8010FF48_chancetime[0] = HuAudFXPlay(0x4F9);
        D_8010FBF4_chancetime[0] = 1;
        break;
    case 2:
        D_8010FF48_chancetime[1] = HuAudFXPlay(0x4FA);
        D_8010FBF4_chancetime[1] = 1;
        break;
    case 3:
        D_8010FF48_chancetime[2] = HuAudFXPlay(0x4FB);
        D_8010FBF4_chancetime[2] = 1;
        break;
    }
    D_8010FED0_chancetime[wheel].state = 4;
    if (wheel < 2 && D_801100DD_chancetime[1 - wheel] != -1) {
        n = 0;
        for (i = 0; i < 4; i++) {
            if (D_801100DD_chancetime[1 - wheel] != GwPlayer[D_801100D0_chancetime[i]].chr) {
                D_8010FED0_chancetime[wheel].items[n] = GwPlayer[D_801100D0_chancetime[i]].chr;
                n++;
            }
        }
        D_8010FED0_chancetime[wheel].count = 3;
        for (i = 0; i < 3; i++) {
            func_8003302C_main(D_8010FED0_chancetime[wheel].anim[i], D_8010FED0_chancetime[wheel].items[2 - i]);
        }
    }
    func_8010DB1C_chancetime(wheel);
}

void func_8010D92C_chancetime(s8 wheel) {
    switch (D_8010FBF0_chancetime) {
    case 1:
        if (D_8010FBF4_chancetime[0] == 1) {
            HuAudFXStop(D_8010FF4A_chancetime);
        }
        HuAudFXPlay(0x4FC);
        break;
    case 2:
        if (D_8010FBF4_chancetime[1] == 1) {
            HuAudFXStop(D_8010FF4E_chancetime);
        }
        HuAudFXPlay(0x4FD);
        break;
    case 3:
        if (D_8010FBF4_chancetime[2] == 1) {
            HuAudFXStop(D_8010FF52_chancetime);
        }
        HuAudFXPlay(0x4FE);
        break;
    }
    D_8010FED0_chancetime[wheel].state = 1;
}

void func_8010DA24_chancetime(void) {
    s32 i;

    D_8010FB80_chancetime = 1;
    D_8010FB81_chancetime = 0;
    for (i = 0; i < 3; i++) {
        func_8000BB54_main(D_8010FE94_chancetime[i]);
    }
    func_8000BB54_main(D_8010FE9A_chancetime);
    D_801100CC_chancetime = func_8010C610_chancetime;
}

s8 func_8010DAA4_chancetime(void) {
    return D_8010FB81_chancetime;
}

void func_8010DAB0_chancetime(void) {
    omObjData *obj = D_801100C8_chancetime;
    s8 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(obj->model[i + 1], 4, 4);
    }
}

void func_8010DB1C_chancetime(s8 wheel) {
    omObjData *obj = D_801100C8_chancetime;

    func_8000BB94_main(D_8010FE94_chancetime[wheel]);
    func_8001C258_main(obj->model[wheel + 1], 4, 0);
}

void func_8010DB78_chancetime(void) {
    D_8010FEC4_chancetime = 0;
    D_8010FEC8_chancetime = 1;
    D_8010FEC9_chancetime = 0;
}

void func_8010DB98_chancetime(void) {
    D_8010FEC8_chancetime = 0;
    D_8010FEC9_chancetime = 1;
}

void func_8010DBB0_chancetime(void) {
    omObjData *obj;
    HmfModel *mdl;
    s16 sprId;
    s8 i;

    obj = omAddObj(20, 21, 0, -1, NULL);
    D_80110080_chancetime = obj;
    mdl = &HmfModelData[D_800D10F2_main];
    mdl->unk00 = (mdl->unk00 & 0xF9) | 3;
    func_8001C8A8_main(D_800D10F2_main, 2);
    sprId = func_8000B838_main(0x210026);
    for (i = 0; i < 20; i++) {
        D_80110028_chancetime[i] = InitEspriteSlot(sprId, 0, 1);
        func_8000BCC8_main(D_80110028_chancetime[i], 0);
        func_8000BB94_main(D_80110028_chancetime[i]);
        func_8000BD94_main(D_80110028_chancetime[i], 0, 0);
        func_8000BDDC_main(D_80110028_chancetime[i], 1);
        func_8000BE5C_main(D_80110028_chancetime[i], 0.5f, 0.5f);
    }
    obj->model[1] = func_8000B0D4_main(0x1301CC, 0x2B9);
    Hu3DModelScaleSet(obj->model[1], 0.5f, 0.5f, 0.5f);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C8A8_main(obj->model[1], 4);
    func_8001C258_main(obj->model[1], 4, 4);
    for (i = 1; i < 10; i++) {
        obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        Hu3DModelScaleSet(obj->model[i + 1], 0.5f, 0.5f, 0.5f);
        func_8001C8A8_main(obj->model[i + 1], 4);
        func_8001C258_main(obj->model[i + 1], 4, 4);
        func_8001C814_main(obj->model[i + 1], 2, 2);
    }
    for (i = 0; i < 10; i++) {
        D_80110010_chancetime[i] = func_8000CED8_main(0xB0004, 0x6A9);
        func_8000CD00_main(D_80110010_chancetime[i], 4.0f, 20.0f, 4.0f);
        func_8000D018_main(D_80110010_chancetime[i], 60.0f);
        func_8001C8A8_main(D_80110010_chancetime[i], 4);
        func_800138EC_main(D_80110010_chancetime[i], 1, 0);
        func_8001C258_main(D_80110010_chancetime[i], 4, 4);
    }
    D_80110004_chancetime = func_80060880_main(100, 160, 14);
    func_80061100_main(D_80110004_chancetime, 5);
    if (!(GwPlayer[D_801100D0_chancetime[0]].stat & 1)) {
        func_8005FE54_main(D_80110004_chancetime, 1 << GwPlayer[D_801100D0_chancetime[0]].pad);
    }
    omPrcSetDestructor(0, func_8010DF68_chancetime);
    D_80110084_chancetime = func_8010DF70_chancetime;
    while (TRUE) {
        D_80110084_chancetime(obj);
        HuPrcVSleep();
    }
}

void func_8010DF68_chancetime(void) {
}

void func_8010DF70_chancetime(omObjData *obj) {
}

void func_8010DF78_chancetime(s8 arg0) {
    D_8010FC14_chancetime = 0;
    D_80110008_chancetime = arg0;
    D_80110084_chancetime = func_8010DFA4_chancetime;
}

// NON_MATCHING: matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id, as
// window.c defines it; the s16 prototype truncates the argument); logic checked
#ifdef NON_MATCHING
void func_8010DFA4_chancetime(omObjData *obj) {
    static const s32 D_8010FD5C_chancetime[3] = { 0x1B01, 0x1B02, 0x1B03 };
    s32 set = D_80110008_chancetime;

    func_8005D294_main(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, 2, 2);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    func_8005B43C_main(D_80110004_chancetime, D_8010FD5C_chancetime[set], -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (func_8005E0C0_main(D_80110004_chancetime) != 0) {
        HuPrcVSleep();
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005F904_main();
    }
    D_80110000_chancetime = set;
    D_80110084_chancetime = func_8010E1E0_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DFA4_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD5C_chancetime);
#endif

void func_8010E1E0_chancetime(omObjData *obj) {
    func_8010D6A4_chancetime(D_80110000_chancetime);
    D_80110084_chancetime = func_8010E210_chancetime;
}

void func_8010E210_chancetime(omObjData *obj) {
    if (++D_8010FC1C_chancetime >= 10) {
        D_8010FC14_chancetime = 1;
        D_8010FC1C_chancetime = 0;
        D_80110084_chancetime = func_8010DF70_chancetime;
    }
}

s32 func_8010E258_chancetime(void) {
    return D_8010FC14_chancetime;
}

void func_8010E264_chancetime(void) {
    D_8010FC18_chancetime = 0;
    D_80110084_chancetime = func_8010E280_chancetime;
}

void func_8010E280_chancetime(omObjData *obj) {
    s32 found[2];
    s32 coin;
    s32 star;
    s32 i;
    s32 j;

    coin = GwPlayer[D_801100D0_chancetime[0]].coin;
    star = GwPlayer[D_801100D0_chancetime[0]].star;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[j].chr) {
                found[i] = j;
                break;
            }
        }
    }
    func_8010F984_chancetime(obj);
    HuPrcSleep(10);
    D_8010FAE4_chancetime = 1;
    func_800F5E30_shared_board(found[0], found[1]);
    func_800F7108_shared_board();
    func_800F5F4C_shared_board(found[0], found[1]);
    func_800F5F60_shared_board();
    func_800F5F7C_shared_board();
    HuPrcSleep(40);
    func_8010E4D0_chancetime(obj);
    if (coin + 1 == GwPlayer[D_801100D0_chancetime[0]].coin) {
        func_8010705C_chancetime();
    } else if (coin < GwPlayer[D_801100D0_chancetime[0]].coin) {
        func_80106F10_chancetime();
    } else if (star < GwPlayer[D_801100D0_chancetime[0]].star) {
        func_80106F10_chancetime();
    } else if (GwPlayer[D_801100D0_chancetime[0]].coin < coin) {
        func_801071A8_chancetime();
    } else if (GwPlayer[D_801100D0_chancetime[0]].star < star) {
        func_801071A8_chancetime();
    } else {
        func_8010705C_chancetime();
    }
    HuPrcSleep(30);
    D_8010FC18_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

s32 func_8010E4C4_chancetime(void) {
    return D_8010FC18_chancetime;
}

// NON_MATCHING: instruction-for-instruction except the order of the two prize-table loads, the amount test
// (branch layout), one model-index computation and an 8-byte larger frame; logic checked
#ifdef NON_MATCHING
void func_8010E4D0_chancetime(omObjData *obj) {
    static const ChancePos16 D_8010FD68_chancetime[9] = {
        { 1000, 0 }, { 30, 0 }, { 20, 0 }, { 10, 0 }, { 1, 0 }, { 0, 1000 }, { 0, 3 }, { 0, 2 }, { 0, 1 },
    };
    struct {
        f32 coin[2];
        f32 star[2];
        s32 player[2];
    } p;
    f32 yOfs;
    u16 isStar;
    f32 per;
    f32 given;
    f32 taken;
    f32 v;
    f32 s;
    f32 sc;
    f32 x;
    f32 y;
    f32 ft;
    s32 coins;
    s32 i;
    s32 j;
    s32 t;
    s32 wait;
    s32 launched;
    s32 arrived;
    s32 interval;
    s32 count;
    s16 amt;
    u16 coinAmt;
    u16 starAmt;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[D_801100D0_chancetime[j]].chr) {
                p.player[i] = D_801100D0_chancetime[j];
                break;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        p.coin[i] = GwPlayer[p.player[i]].coin;
        p.star[i] = GwPlayer[p.player[i]].star;
    }
    coinAmt = D_8010FD68_chancetime[D_801100DD_chancetime[2]].x;
    starAmt = D_8010FD68_chancetime[D_801100DD_chancetime[2]].y;
    coins = D_8010FD68_chancetime[D_801100DD_chancetime[2]].x;
    if (coins > 0) {
        if (GwPlayer[p.player[0]].coin < coins) {
            coinAmt = GwPlayer[p.player[0]].coin;
        }
        isStar = 0;
    } else {
        if (GwPlayer[p.player[0]].star < (s16)starAmt) {
            starAmt = GwPlayer[p.player[0]].star;
        }
        isStar = 1;
    }
    amt = (isStar == 0) ? coinAmt : starAmt;
    if (amt > 0) {
        if (isStar == 0) {
            yOfs = 0.0f;
            count = (s16)coinAmt;
            if (count > 20) {
                count = 20;
            }
            amt = coinAmt;
        } else {
            yOfs = 16.0f;
            count = (s16)starAmt;
            if (count > 10) {
                count = 10;
            }
            amt = starAmt;
        }
        per = (f32)amt / count;
        given = 0.0f;
        taken = 0.0f;
        interval = 20 / count;
        interval = (interval < 5) ? 5 : interval;
        for (i = 0; i < 20; i++) {
            D_8010FF60_chancetime[i].state = 0;
            D_8010FF60_chancetime[i].timer = 0;
        }
        wait = 0;
        launched = 0;
        arrived = 0;
        if (count > 0) {
            do {
                for (i = 0; i < 20; i++) {
                    switch (D_8010FF60_chancetime[i].state) {
                    case 0:
                        if (interval < wait) {
                            if (launched < count) {
                            D_8010FF60_chancetime[i].state = 1;
                            wait = 0;
                            launched++;
                            if (isStar == 0) {
                                taken += per;
                                v = p.coin[0] - taken;
                                if (v >= 0.0f) {
                                    GwPlayer[p.player[0]].coin = (u32)v;
                                } else {
                                    GwPlayer[p.player[0]].coin = 0;
                                }
                                HuAudFXPlay(0x109);
                            } else {
                                taken += per;
                                v = p.star[0] - taken;
                                if (v >= 0.0f) {
                                    GwPlayer[p.player[0]].star = (u32)v;
                                } else {
                                    GwPlayer[p.player[0]].star = 0;
                                }
                            }
                        }
                            }
                        break;
                    case 1:
                        if (isStar == 0) {
                            func_8000BB54_main(D_80110028_chancetime[i]);
                            func_8000BDDC_main(D_80110028_chancetime[i], 1);
                            func_8000BD94_main(D_80110028_chancetime[i], 0, 0);
                            func_8000BBD4_main(D_80110028_chancetime[i], 80, 74.0f - yOfs);
                        } else {
                            func_8001C258_main(obj->model[i + 1], 4, 0);
                            func_8001C258_main(D_80110010_chancetime[i], 4, 0);
                            func_800138EC_main(D_80110010_chancetime[i], 1, 1);
                            Hu3DModelPosSet(obj->model[i + 1], -170.0f, 375.0f, 0.0f);
                            func_8000CFA4_main(D_80110010_chancetime[i], -170.0f, 375.0f, 0.0f);
                        }
                        D_8010FF60_chancetime[i].timer = 0;
                        D_8010FF60_chancetime[i].state = 3;
                        break;
                    case 2:
                        D_8010FF60_chancetime[i].state = 0;
                        if (isStar == 0) {
                            func_8000BB94_main(D_80110028_chancetime[i]);
                            given += per;
                            v = given + p.coin[1];
                            if (v <= 999.0f) {
                                GwPlayer[p.player[1]].coin = v;
                                HuAudFXPlay(0x106);
                            } else {
                                GwPlayer[p.player[1]].coin = 999;
                                HuAudFXPlay(0x106);
                            }
                        } else {
                            func_8001C258_main(obj->model[i + 1], 4, 4);
                            func_800138EC_main(D_80110010_chancetime[i], 1, 0);
                            given += per;
                            v = given + p.star[1];
                            if (v <= 99.0f) {
                                GwPlayer[p.player[1]].star = v;
                                HuAudFXPlay(0x11B);
                            } else {
                                GwPlayer[p.player[1]].star = 99;
                                HuAudFXPlay(0x11B);
                            }
                        }
                        arrived++;
                        break;
                    case 3:
                        t = D_8010FF60_chancetime[i].timer;
                        if (isStar == 0) {
                            x = t * 8.5f;
                            s = sindf(t * 9.0f);
                            y = s * 32.0f;
                            func_8000BBD4_main(D_80110028_chancetime[i], x + 80.0f, (74.0f - y) - yOfs);
                            sc = s * 0.5f + 0.5f;
                            func_8000BE5C_main(D_80110028_chancetime[i], sc, sc);
                            D_8010FF60_chancetime[i].timer++;
                            if (t >= 20) {
                                D_8010FF60_chancetime[i].state = 2;
                            }
                        } else {
                            x = t * 9.25f;
                            ft = t;
                            s = sindf(ft * 4.5f);
                            y = s * 88.0f;
                            x = x + -170.0f;
                            y = y + 375.0f;
                            Hu3DModelPosSet(obj->model[i + 1], x, y, 0.0f);
                            func_8000CFA4_main(D_80110010_chancetime[i], x, y, 0.0f);
                            sc = s * 0.5f + 0.5f;
                            Hu3DModelScaleSet(obj->model[i + 1], sc, sc, sc);
                            Hu3DModelRotSet(obj->model[i + 1], 0.0f, ft * 15.0f, 0.0f);
                            sc = 2.0f * s + 4.0f;
                            func_8000CD00_main(D_80110010_chancetime[i], sc, 20.0f, sc);
                            D_8010FF60_chancetime[i].timer++;
                            if (t >= 40) {
                                D_8010FF60_chancetime[i].state = 2;
                            }
                        }
                        break;
                    }
                }
                wait++;
                HuPrcVSleep();
            } while (arrived < count);
        }
        if (isStar == 0) {
            v = p.coin[0] - (s16)coinAmt;
            if (v >= 0.0f) {
                GwPlayer[p.player[0]].coin = v;
            } else {
                GwPlayer[p.player[0]].coin = 0;
            }
            v = (s16)coinAmt + p.coin[1];
            if (v <= 999.0f) {
                GwPlayer[p.player[1]].coin = v;
            } else {
                GwPlayer[p.player[1]].coin = 999;
            }
        } else {
            v = p.star[0] - (s16)starAmt;
            if (v >= 0.0f) {
                GwPlayer[p.player[0]].star = v;
            } else {
                GwPlayer[p.player[0]].star = 0;
            }
            v = (s16)starAmt + p.star[1];
            if (v <= 99.0f) {
                GwPlayer[p.player[1]].star = v;
            } else {
                GwPlayer[p.player[1]].star = 99;
            }
        }
        MBPlayerCoinAdd(p.player[1], 0);
        HuPrcSleep(30);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4D0_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD68_chancetime);
#endif

void func_8010F1DC_chancetime(void) {
    D_8010FC10_chancetime = 0;
    D_80110084_chancetime = func_8010F1F8_chancetime;
}

// NON_MATCHING: matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id); logic
// checked
#ifdef NON_MATCHING
void func_8010F1F8_chancetime(omObjData *obj) {
    func_8005D294_main(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, 2, 2);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    func_8010BF48_chancetime();
    HuAudFXPlay(0x298);
    func_8005B43C_main(D_80110004_chancetime, 0x1B00, -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (func_8005E0C0_main(D_80110004_chancetime) != 0) {
        HuPrcVSleep();
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005F904_main();
    }
    D_80110084_chancetime = func_8010F42C_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F1F8_chancetime);
#endif

s32 func_8010F420_chancetime(void) {
    return D_8010FC10_chancetime;
}

void func_8010F42C_chancetime(omObjData *obj) {
    D_8010FC10_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

// NON_MATCHING: matches with the header fix in e3A.header.patch (func_80060EA8_main takes an s32 window id); logic
// checked
#ifdef NON_MATCHING
void func_8010F44C_chancetime(s32 prize, s32 total, s32 amount) {
    static const s32 D_8010FD8C_chancetime[9] = { 0x1B0C, 0x1B06, 0x1B06, 0x1B06, 0x1B04, 0x1B0E, 0x1B09, 0x1B09, 0x1B09 };
    static const s32 D_8010FDB0_chancetime[9] = { 0, 0x1B07, 0x1B07, 0x1B07, 0, 0, 0x1B0A, 0x1B0A, 0x1B0A };
    static const s32 D_8010FDD4_chancetime[9] = { 0x1B0D, 0x1B08, 0x1B08, 0x1B08, 0x1B05, 0x1B0F, 0x1B0B, 0x1B0B, 0x1B0B };
    static const s32 D_8010FDF8_chancetime[9] = { 0, 0x1B1A, 0x1B19, 0x1B18, 0, 0, 0x1B1D, 0x1B1C, 0x1B1B };
    static const s32 D_8010FE1C_chancetime[8] = { 0x1B10, 0x1B11, 0x1B12, 0x1B13, 0x1B14, 0x1B15, 0x1B16, 0x1B17 };
    s32 mes;
    s32 i;

    for (i = 0; i < 2; i++) {
        func_8005B6BC_main(D_80110004_chancetime, D_8010FE1C_chancetime[D_801100DD_chancetime[i]], i);
    }
    if (D_801100DD_chancetime[2] < 5) {
        if (D_8010FDF8_chancetime[D_801100DD_chancetime[2]] != 0) {
            func_8005B6BC_main(D_80110004_chancetime, D_8010FDF8_chancetime[D_801100DD_chancetime[2]], 2);
        }
    } else {
        if (D_8010FDF8_chancetime[D_801100DD_chancetime[2]] != 0) {
            func_8005B6BC_main(D_80110004_chancetime, D_8010FDF8_chancetime[D_801100DD_chancetime[2]], 3);
        }
    }
    func_8005D294_main(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, 2, 2);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    func_8005B43C_main(D_80110004_chancetime, D_8010FD8C_chancetime[prize], -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (func_8005E0C0_main(D_80110004_chancetime) != 0) {
        HuPrcVSleep();
    }
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, 2, 2);
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    if (amount < total) {
        if (amount > 0) {
            mes = D_8010FDB0_chancetime[prize];
            if (mes != 0) {
                func_80060EA8_main(D_80110004_chancetime, 1);
                func_8005B43C_main(D_80110004_chancetime, mes, -1, -1);
                HuAudFXPlay(0x29A);
                func_80060C14_main(D_80110004_chancetime, 1);
                while (func_8005E0C0_main(D_80110004_chancetime) != 0) {
                    HuPrcVSleep();
                }
            }
        } else {
            func_80060EA8_main(D_80110004_chancetime, 1);
            func_8005B43C_main(D_80110004_chancetime, D_8010FDD4_chancetime[prize], -1, -1);
            HuAudFXPlay(0x29A);
            func_80060C14_main(D_80110004_chancetime, 1);
            while (func_8005E0C0_main(D_80110004_chancetime) != 0) {
                HuPrcVSleep();
            }
        }
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005F904_main();
    }
    D_80110084_chancetime = func_8010E1E0_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F44C_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD8C_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDB0_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDD4_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDF8_chancetime);
INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE1C_chancetime);
#endif

void func_8010F984_chancetime(omObjData *obj) {
    static const ChancePos16 D_8010FE3C_chancetime[9] = {
        { 1000, 0 }, { 30, 0 }, { 20, 0 }, { 10, 0 }, { 1, 0 }, { 0, 1000 }, { 0, 3 }, { 0, 2 }, { 0, 1 },
    };
    s32 found[4];
    s32 i;
    s32 j;
    s32 coins;
    u16 coinAmt;
    s32 stars;
    s16 starAmt;
    u16 isStar;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[D_801100D0_chancetime[j]].chr) {
                found[i] = D_801100D0_chancetime[j];
                break;
            }
        }
    }
    coinAmt = D_8010FE3C_chancetime[D_801100DD_chancetime[2]].x;
    coins = D_8010FE3C_chancetime[D_801100DD_chancetime[2]].x;
    stars = D_8010FE3C_chancetime[D_801100DD_chancetime[2]].y;
    starAmt = stars;
    if (coins > 0) {
        if (GwPlayer[found[0]].coin < coins) {
            coinAmt = GwPlayer[found[0]].coin;
        }
        isStar = 0;
    } else {
        if (starAmt > GwPlayer[found[0]].star) {
            starAmt = GwPlayer[found[0]].star;
        }
        isStar = 1;
    }
    if (isStar == 0) {
        func_8010F44C_chancetime(D_801100DD_chancetime[2], (s16)coins, (s16)coinAmt);
    } else {
        func_8010F44C_chancetime(D_801100DD_chancetime[2], (s16)stars, starAmt);
    }
}
