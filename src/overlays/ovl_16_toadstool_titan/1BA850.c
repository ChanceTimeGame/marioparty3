#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// ts A: Toadstool Titan

typedef func_800E1BA8_minigame_ObjData MgWork;

/* A player's record (D_8010F528, pointed to by D_8010F568) */
typedef struct TtPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player; /* GwPlayer index */
    /* 0x02 */ u8 group;
    /* 0x03 */ u8 pad;
    /* 0x04 */ s8 com; /* cpu difficulty, -1 human */
    /* 0x05 */ char unk05[9];
    /* 0x0E */ s16 unkE;
} TtPlayer; /* size 0x10 */

/* .data */
extern u8 D_8010EDA0_toadstool_titan;
extern f32 D_8010EDA4_toadstool_titan; /* viewport rect */
extern f32 D_8010EDA8_toadstool_titan;
extern f32 D_8010EDAC_toadstool_titan;
extern f32 D_8010EDB0_toadstool_titan;
extern u8 D_8010EDB4_toadstool_titan[]; /* debris timers (14) */
extern u8 D_8010EDC4_toadstool_titan[]; /* panel timers (9) */
extern u8 D_8010EDCD_toadstool_titan;
extern s16 D_8010EDCE_toadstool_titan;
extern s16 D_8010EDD0_toadstool_titan;
extern f32 D_8010EDD4_toadstool_titan;
extern f32 D_8010EDD8_toadstool_titan;
extern f32 D_8010EDDC_toadstool_titan;
extern f32 D_8010EDE0_toadstool_titan;
extern u16 D_8010EDE4_toadstool_titan;
extern s16 D_8010EDE8_toadstool_titan[];

/* .bss */
extern f32 D_8010F3D0_toadstool_titan[14];
extern f32 D_8010F408_toadstool_titan[14];
extern f32 D_8010F440_toadstool_titan[14];
extern f32 D_8010F478_toadstool_titan[14];
extern f32 D_8010F4B0_toadstool_titan[14];
extern f32 D_8010F4E8_toadstool_titan[14];
extern TtPlayer D_8010F528_toadstool_titan[4];
extern TtPlayer* D_8010F568_toadstool_titan[4];
extern u32 D_8010F580_toadstool_titan;
extern u8 D_8010F584_toadstool_titan;
extern s16 D_8010F586_toadstool_titan;
extern s16 D_8010F588_toadstool_titan;
extern s8 D_8010F58A_toadstool_titan;
extern f32 D_8010F58C_toadstool_titan;
extern f32 D_8010F5B8_toadstool_titan;
extern u16 D_8010F5BC_toadstool_titan;
extern omObjData* D_8010F5D0_toadstool_titan[9];
extern u8 D_8010F5F4_toadstool_titan;
extern omObjData* D_8010F5F8_toadstool_titan;
extern s16 D_8010F5FC_toadstool_titan;
extern f32 D_8010F600_toadstool_titan;
extern f32 D_8010F604_toadstool_titan;
extern f32 D_8010F608_toadstool_titan;
extern s8 D_8010F60E_toadstool_titan;
extern f32 D_8010F610_toadstool_titan;
extern u8 D_8010F614_toadstool_titan;
extern u8 D_8010F615_toadstool_titan;
extern u8 D_8010F616_toadstool_titan[4];
extern u32 D_8010F61C_toadstool_titan;
extern u8 D_8010F620_toadstool_titan;
extern omObjData* D_8010F640_toadstool_titan[4];
extern u8 D_8010F650_toadstool_titan[9];
extern u8 D_8010F659_toadstool_titan[4];
extern u8 D_8010F65D_toadstool_titan[4];
extern f32 D_8010F664_toadstool_titan;
extern u8 D_8010F668_toadstool_titan[4];
extern u8 D_8010F66C_toadstool_titan;
extern f32 D_8010F670_toadstool_titan;

extern u8 D_800D6A90_main;
extern s16 D_800D418E_main;
extern s16 D_800D037E_main;

void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E5138_minigame(omObjData* obj);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_8010AD8C_toadstool_titan(s16 x0, s16 y0, s16 x1, s16 y1);
void func_8010B4D4_toadstool_titan(s16 mdl, s16 frame);

#define TT_TICK() (func_80049F98_main() + D_800D6A90_main == 0)

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_801059A0_toadstool_titan);

void func_80105E48_toadstool_titan(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80105E50_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EE80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EECC_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_801060AC_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80106984_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF10_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF34_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_801069DC_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80106C98_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF68_toadstool_titan);

// register allocation, stack layout and scheduling (frame 0x130, obj spilled); logic checked block by block
#ifdef NON_MATCHING
void func_80107360_toadstool_titan(omObjData* obj) {
    Vec2f sa;
    Vec2f sb;
    f32 cx;
    f32 cy;
    Vec a;
    Vec b;
    Vec c;
    f32 mf[4][4];
    s32 i;
    s32 j;
    s32 m;
    s32 cnt;
    s32 k;
    f64 d;
    s16 c2;
    u8 s;
    s32 n;
    f32 f;
    f32 g;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;
    f32 w;
    f32 h;
    f32 best;
    s8 bi;
    s8 q;
    u8 v;
    MgWork* mw;
    omObjData* p;
    omObjData* p2;
    HmfModel* hm;
    HuCamMtxs* cm;
    s16 k2;

    i = 0;
    if (D_8010F5FC_toadstool_titan == 4 && D_8010F580_toadstool_titan >= 30 && D_8010F580_toadstool_titan < 50) {
        p = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan];
        b.x = p->trans.x;
        b.y = p->trans.y + 75.0f;
        b.z = p->trans.z;
        a = b;
        c.x = p->trans.x + 25.0f;
        c.y = p->trans.y + 75.0f;
        c.z = p->trans.z;
        b = c;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        func_80012B14_main(0, &a, &sa);
        func_80012B14_main(0, &b, &sb);
        f = (sb.x - sa.x) * 12.0f;
        sb.x = f + sa.x;
        sa.x = sa.x - f;
        d = (sb.x - sa.x) * 0.75 * 0.5;
        sa.y = sa.y - d;
        sb.y = sb.y + d;
        f = 1.0f - (f32)(D_8010F580_toadstool_titan - 30) / 20.0f;
        f = 1.0f - f * f * f * f;
        g = 1.0f - f;
        sa.x = f * sa.x + g * 0.0f;
        sa.y = f * sa.y + g * 0.0f;
        sb.x = f * sb.x + g * 320.0f;
        sb.y = f * sb.y + g * 240.0f;
        zoom = 320.0f / (sb.x - sa.x);
        if (sa.x < 0.0f) {
            sb.x -= sa.x;
            sa.x -= sa.x;
        }
        if (sa.y < 0.0f) {
            sb.y -= sa.y;
            sa.y -= sa.y;
        }
        if (sb.x > 320.0f) {
            f = sb.x - 320.0f;
            sa.x -= f;
            sb.x -= f;
        }
        if (sb.y > 240.0f) {
            f = sb.y - 240.0f;
            sa.y -= f;
            sb.y -= f;
        }
        cx = (sa.x + sb.x) * 0.5;
        cy = (sa.y + sb.y) * 0.5;
        D_8010EDA4_toadstool_titan = (s32)((0.0f - cx) / (sa.x - cx) * (0.0f - cx) + cx);
        D_8010EDA8_toadstool_titan = (s32)((0.0f - cy) / (sa.y - cy) * (0.0f - cy) + cy);
        D_8010EDAC_toadstool_titan = (s32)((320.0f - cx) / (sb.x - cx) * (320.0f - cx) + cx);
        D_8010EDB0_toadstool_titan = (s32)((240.0f - cy) / (sb.y - cy) * (240.0f - cy) + cy);
        f = 0.0f;
        if (sa.x != 0.0f) {
            f = 0.0f - (sa.x - 0.0f) * zoom;
        }
        D_8010EDA4_toadstool_titan = f;
        f = 0.0f;
        if (sa.y != 0.0f) {
            f = 0.0f - (sa.y - 0.0f) * zoom;
        }
        D_8010EDA8_toadstool_titan = f;
        f = 320.0f;
        if (sb.x != 320.0f) {
            f = 320.0f - (sb.x - 320.0f) * zoom;
        }
        D_8010EDAC_toadstool_titan = f;
        f = 240.0f;
        if (sb.y != 240.0f) {
            f = 240.0f - (sb.y - 240.0f) * zoom;
        }
        D_8010EDB0_toadstool_titan = f;
        w = (s32)(zoom * 640.0f);
        h = (s32)(zoom * 480.0f);
        ViewportSet(0, w, h, 511.0f, (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan != 0 && D_8010F5F4_toadstool_titan < 13) {
        if (TT_TICK()) {
            f = D_8010F670_toadstool_titan + rand8() / 255.0 * 30.0 - 15.0;
        } else {
            f = D_8010F670_toadstool_titan;
        }
        d = sindf(f) * 0.5;
        if (!(D_8010F5F4_toadstool_titan & 1)) {
            d = d * D_8010F5F4_toadstool_titan;
        } else {
            d = d * -D_8010F5F4_toadstool_titan;
        }
        D_8010EDA4_toadstool_titan = (s16)d;
        D_8010EDAC_toadstool_titan = D_8010EDA4_toadstool_titan + 320.0f;
        d = cosdf(f) * 0.5;
        if (!(D_8010F5F4_toadstool_titan & 1)) {
            d = d * D_8010F5F4_toadstool_titan;
        } else {
            d = d * -D_8010F5F4_toadstool_titan;
        }
        D_8010EDA8_toadstool_titan = (s16)d;
        D_8010EDB0_toadstool_titan = D_8010EDA8_toadstool_titan + 240.0f;
        v = D_8010F5F4_toadstool_titan;
        if (TT_TICK()) {
            v--;
        }
        D_8010F5F4_toadstool_titan = v;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan == 13) {
        v = 13;
        if (TT_TICK()) {
            v = 12;
        }
        D_8010F5F4_toadstool_titan = v;
    }
    func_8010AD8C_toadstool_titan(D_8010EDA4_toadstool_titan, D_8010EDA8_toadstool_titan, D_8010EDAC_toadstool_titan, D_8010EDB0_toadstool_titan);
    if (!TT_TICK()) {
        return;
    }
    D_8010F61C_toadstool_titan++;
    switch (D_8010F586_toadstool_titan) {
    case 0:
        if (D_8010F61C_toadstool_titan >= 47) {
            D_8010F586_toadstool_titan = 7;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 4; j++) {
                q = D_8010F568_toadstool_titan[j]->chr;
                D_8010F640_toadstool_titan[j]->model[6] = func_8000B108_main(5, 0x88D);
                D_8010F640_toadstool_titan[j]->model[7] = func_8000B108_main(8, 0x88D);
                D_8010F640_toadstool_titan[j]->model[8] = func_8000B108_main(7, 0x88D);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 1, func_80017BB8_main(q, 1), 1, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0x12, func_80017BB8_main(q, 0xF), 2, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 2, func_80017BB8_main(q, 2), 1, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0x11, func_80017BB8_main(q, 0xE), 1, 0xF);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x1E, func_80017BB8_main(q, 0x20), 2, 0);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x1F, func_80017BB8_main(q, 0x21), 2, 0);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x20, func_80017BB8_main(q, 0x22), 0, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 5, func_80017BB8_main(q, 3), 0, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 8, func_80017BB8_main(q, 6), 1, 0x1B);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0xC, func_80017BB8_main(q, 0x25), 1, 0x78);
            }
        }
        break;
    case 1:
    case 2:
        k = rand8() & 3;
        for (cnt = 0; cnt < 4; cnt++) {
            k = (k + 1) % 4;
            mw = D_8010F640_toadstool_titan[k]->data;
            if (D_8010F586_toadstool_titan == 1 && D_8010F61C_toadstool_titan < 4) {
                if ((u32)(mw->unk56 - 1) < 9 && D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] == 2) {
                    s = rand8() % 9;
                    for (n = 0; n < 9; n++) {
                        m = (s + n) % 9;
                        if (D_8010F650_toadstool_titan[m] == 1) {
                            D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] = 1;
                            D_8010F650_toadstool_titan[m] = 2;
                            break;
                        }
                    }
                }
            }
            if ((u32)(mw->unk56 - 1) < 9 && D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] != 3) {
                s = (s8)mw->unk56 - 1;
                v = D_8010F650_toadstool_titan[s];
                if (v == 2) {
                    mw->unk38 += 0.5;
                    HmfModelData[D_8010F640_toadstool_titan[k]->model[0]].unk0E = HmfModelData[D_8010F640_toadstool_titan[k]->model[0]].unk0C;
                    D_8010F620_toadstool_titan = s;
                    for (j = 0; j < 9; j++) {
                        D_8010F650_toadstool_titan[j] = D_8010F650_toadstool_titan[j] != 0;
                    }
                    D_8010F650_toadstool_titan[s] = 3;
                    D_8010F586_toadstool_titan = 2;
                    D_8010F61C_toadstool_titan = 0;
                    D_8010F60E_toadstool_titan = k;
                } else if (v != 3) {
                    D_8010F650_toadstool_titan[s] = 0;
                    mw->unkC5 = func_8004AC98_main(0x3A5, mw->unk59);
                    mw->unkC4 = -1;
                    for (j = 0; j < 4; j++) {
                        func_800E149C_minigame(D_8010F640_toadstool_titan[j], s + 1, 1);
                    }
                    func_8001C258_main(D_8010F5D0_toadstool_titan[s]->model[0], 4, 4);
                    func_8001C258_main(D_8010F5D0_toadstool_titan[s]->model[1], 4, 4);
                    func_8001C258_main(D_8010F5F8_toadstool_titan->model[17 + s], 4, 0);
                    func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[17 + s], 0);
                    D_8010EDC4_toadstool_titan[s] = 1;
                    for (n = 0, j = 0; n < 4 && j < 14; j++) {
                        if (D_8010EDB4_toadstool_titan[j] == 0) {
                            D_8010EDB4_toadstool_titan[j] = 1;
                            if (!(n & 1)) {
                                D_8010F3D0_toadstool_titan[j] = -25.0f;
                            } else {
                                D_8010F3D0_toadstool_titan[j] = 25.0f;
                            }
                            if (n / 2 == 0) {
                                D_8010F408_toadstool_titan[j] = -25.0f;
                            } else {
                                D_8010F408_toadstool_titan[j] = 25.0f;
                            }
                            D_8010F440_toadstool_titan[j] = rand8() / 255.0 * 50.0 - 25.0;
                            D_8010F478_toadstool_titan[j] = rand8() / 255.0 * 15.0;
                            D_8010F4B0_toadstool_titan[j] = 30.0 - rand8() / 255.0 * 10.0;
                            D_8010F4B0_toadstool_titan[j] = HuSqrtf(D_8010F478_toadstool_titan[j] * D_8010F478_toadstool_titan[j] + D_8010F4B0_toadstool_titan[j] * D_8010F4B0_toadstool_titan[j]);
                            D_8010F4E8_toadstool_titan[j] = rand8() / 255.0 * 20.0;
                            if (D_8010F3D0_toadstool_titan[j] < 0.0f) {
                                D_8010F478_toadstool_titan[j] = -D_8010F478_toadstool_titan[j];
                            }
                            if (D_8010F440_toadstool_titan[j] < 0.0f) {
                                D_8010F4E8_toadstool_titan[j] = -D_8010F4E8_toadstool_titan[j];
                            }
                            D_8010F3D0_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.x;
                            D_8010F408_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.y;
                            D_8010F440_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.z;
                            func_8001C258_main(obj->model[29 + j], 4, 0);
                            func_8001C258_main(obj->model[43 + j], 4, 0);
                            n++;
                        }
                    }
                }
            }
        }
        if (D_8010F586_toadstool_titan == 1) {
            break;
        }
        if (D_8010F61C_toadstool_titan >= 55) {
            D_8010F586_toadstool_titan = 3;
            D_8010F61C_toadstool_titan = 0;
            func_8001C258_main(D_8010F5F8_toadstool_titan->model[1], 4, 4);
            func_8001C258_main(D_8010F5F8_toadstool_titan->model[56], 4, 4);
            func_800036E8_main(D_800CDBC8_main, D_8010F600_toadstool_titan);
            break;
        }
        if (D_8010F61C_toadstool_titan == 35) {
            f = 0.0f;
            for (j = 0; j < 9; j++) {
                if (D_8010F650_toadstool_titan[j] != 0) {
                    f += 1.0f;
                    func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                    func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
                }
            }
            D_8010EDCD_toadstool_titan = 1;
            if (f > 0.0f) {
                HuAudFXPlay(0x3A9);
            }
        } else if (D_8010F61C_toadstool_titan == 42) {
            for (j = 0; j < 9; j++) {
                D_8010F650_toadstool_titan[j] = 0;
                for (m = 0; m < 4; m++) {
                    func_800E149C_minigame(D_8010F640_toadstool_titan[m], j + 1, 1);
                }
            }
        } else if (D_8010F61C_toadstool_titan == 45) {
            for (j = 0; j < 9; j++) {
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 4);
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 4);
            }
        }
        if (D_8010F61C_toadstool_titan < 7) {
            f = 2.0f * (f32)((D_8010F61C_toadstool_titan + 1) / 7.0) - 1.0f;
            f = -(f * f - 1.0f) * 25.0f + 375.0f;
            D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.y = f;
            HmfModelData[D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->model[0]].pos.y = f;
        } else if (D_8010F61C_toadstool_titan >= 12 && D_8010F61C_toadstool_titan < 45) {
            if (D_8010F61C_toadstool_titan < 35) {
                f = (D_8010F61C_toadstool_titan - 12) / 23.0;
            } else {
                f = 1.0f;
            }
            func_8001C258_main(obj->model[1], 4, 0);
            p = D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan];
            Hu3DModelPosSet(obj->model[1], p->trans.x, f * 75.0f + p->trans.y + 12.5, p->trans.z - 25.0f);
            if (D_8010F61C_toadstool_titan == 12) {
                HuAudFXPlay(0x3A8);
                for (j = 0; j < 4; j++) {
                    mw = D_8010F640_toadstool_titan[k]->data;
                    mw->unkC4 = -1;
                    mw->unkC5 = -1;
                }
            }
        } else if (D_8010F61C_toadstool_titan >= 45) {
            best = 32767.0f;
            bi = -1;
            if (D_8010F61C_toadstool_titan == 45) {
                m = rand8() / 256.0 * 360.0;
                D_8010F610_toadstool_titan = HmfModelData[obj->model[1]].pos.x;
                D_8010F664_toadstool_titan = HmfModelData[obj->model[1]].pos.y;
                D_8010F604_toadstool_titan = HmfModelData[obj->model[1]].pos.z;
                f = m;
                D_8010F5B8_toadstool_titan = cosdf(f) * 7.0f;
                D_8010F608_toadstool_titan = -sindf(f) * 7.0f;
                D_8010F58C_toadstool_titan = 0.0f;
            }
            D_8010F610_toadstool_titan += D_8010F5B8_toadstool_titan;
            D_8010F664_toadstool_titan += D_8010F58C_toadstool_titan;
            D_8010F604_toadstool_titan += D_8010F608_toadstool_titan;
            D_8010F58C_toadstool_titan -= 3.0f;
            if (D_8010F664_toadstool_titan < 50.0f) {
                D_8010F664_toadstool_titan = 50.0f;
                D_8010F58C_toadstool_titan = 0.0f;
            }
            if (D_8010F610_toadstool_titan < -450.0f) {
                D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan - 900.0f;
                D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
            }
            if (D_8010F610_toadstool_titan > 450.0f) {
                D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan + 900.0f;
                D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
            }
            if (D_8010F604_toadstool_titan < -400.0f) {
                D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan - 800.0f;
                D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
            }
            if (D_8010F604_toadstool_titan > 400.0f) {
                D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan + 800.0f;
                D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
            }
            Hu3DModelPosSet(obj->model[1], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
            Hu3DModelPosSet(obj->model[56], D_8010F610_toadstool_titan, 0.0f, D_8010F604_toadstool_titan);
            func_8001C258_main(obj->model[56], 4, 0);
            for (q = 0; q < 4; q++) {
                p = D_8010F640_toadstool_titan[q];
                x = p->trans.x - D_8010F610_toadstool_titan;
                y = (p->trans.y + 75.0f - D_8010F664_toadstool_titan) / 1.75;
                z = p->trans.z - D_8010F604_toadstool_titan;
                f = HuSqrtf(x * x + y * y + z * z);
                if (f <= 100.0f && f < best) {
                    bi = q;
                    best = f;
                }
            }
            if (bi != -1) {
                D_8010F60E_toadstool_titan = bi;
                D_8010F61C_toadstool_titan = 54;
            } else {
                D_8010F61C_toadstool_titan = 46;
            }
            if (D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) {
                D_8010F586_toadstool_titan = 9;
                D_8010F61C_toadstool_titan = 0;
                func_8001C258_main(obj->model[1], 4, 4);
                func_8001C258_main(obj->model[56], 4, 4);
                func_8001C258_main(obj->model[57], 4, 0);
                Hu3DModelPosSet(obj->model[57], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
                func_8010B4D4_toadstool_titan(obj->model[57], 6);
            }
        }
        break;
    case 3:
        if ((D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) && D_8010F61C_toadstool_titan >= 2 && D_8010EDD0_toadstool_titan == 0) {
            D_8010F586_toadstool_titan = 9;
            D_8010F61C_toadstool_titan = 0;
            func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
            D_8010EDD0_toadstool_titan = 1;
        }
        if (D_8010F61C_toadstool_titan == 1) {
            D_8010EDCE_toadstool_titan = 1;
            if (D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A670_main(90);
                D_8010F614_toadstool_titan = 0;
            }
            HuAudFXPlay(0x3AB);
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
            if (!(D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6)) {
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0xC);
            }
            func_8001C8E4_main(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x800);
            for (j = 0; j < 5; j++) {
                func_8001C8E4_main(D_8010F5F8_toadstool_titan->model[3 + j], 0x800);
            }
        } else if (D_8010F61C_toadstool_titan == 46) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
        } else if (D_8010F61C_toadstool_titan >= 55) {
            D_8010F586_toadstool_titan = 4;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 5; j++) {
                func_8001C8E4_main(D_8010F5F8_toadstool_titan->model[3 + j], 0x400);
            }
        }
        break;
    case 4:
        if (D_8010F61C_toadstool_titan == 3) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            mw->unkC5 = func_8004AC98_main(0x3A7, mw->unk59);
            mw->unkC4 = -1;
            omVibrate(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->player, 10, 0, 10);
        }
        p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
        Hu3DModelScaleSet(p->model[1], p->scale.x, p->scale.y, p->scale.z);
        if (D_8010F61C_toadstool_titan < 24) {
            u8 tbl[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };

            f = tbl[D_8010F61C_toadstool_titan & 7];
            if (D_8010F61C_toadstool_titan >= 12) {
                f = 2.0 - f * 0.5;
            } else {
                f = f * 0.5 + 1.0;
            }
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], f, f, f);
        } else {
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
        }
        if (D_8010F61C_toadstool_titan >= 35) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            if (D_8010F5FC_toadstool_titan == 2) {
                mw->unk50 |= 0x400;
            }
            D_8010F586_toadstool_titan = 5;
            D_8010F61C_toadstool_titan = (D_8010F5FC_toadstool_titan != 2) ? 150 : 0;
            func_8001C8E4_main(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x400);
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_80003A70_main(D_800CDBC8_main);
                func_8004A5C4_main(69);
                D_8010F615_toadstool_titan = 1;
            }
        }
        break;
    case 5:
        omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
        if (D_8010F61C_toadstool_titan >= 150) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            mw->unk50 &= ~0x400;
            D_8010F586_toadstool_titan = 6;
            D_8010F61C_toadstool_titan = 0;
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A7C4_main(40);
                D_8010F615_toadstool_titan = 0;
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (D_8010F616_toadstool_titan[i] == 0 && D_8010F60E_toadstool_titan != i && D_8010F5FC_toadstool_titan == 2) {
                    p = D_8010F640_toadstool_titan[i];
                    p2 = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                    x = p->trans.x - p2->trans.x;
                    y = (p->trans.y - p2->trans.y) * 0.5;
                    z = p->trans.z - p2->trans.z;
                    if (x * x + y * y + z * z < 22500.0f && p->trans.y < 270.0f) {
                        mw = p->data;
                        mw->unk50 |= 0x400;
                        mw->unkC5 = func_8004AC98_main(0x3A6, mw->unk59);
                        mw->unkC4 = -1;
                        omVibrate(D_8010F568_toadstool_titan[i]->player, 20, 0, 20);
                        D_8010F616_toadstool_titan[i] = 1;
                        D_8010F659_toadstool_titan[i] = !(D_8010F640_toadstool_titan[i]->trans.x < D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x);
                        if (D_8010F568_toadstool_titan[i]->com == -1) {
                            D_8010F66C_toadstool_titan--;
                        }
                        for (n = 0, j = 0; j < 4; j++) {
                            n += D_8010F616_toadstool_titan[j] != 0;
                        }
                        if (n == 3) {
                            D_8010F58A_toadstool_titan = D_8010F60E_toadstool_titan;
                            D_8010F61C_toadstool_titan = 120;
                        }
                    }
                }
            }
            i = 0;
        }
        break;
    case 6:
        if (D_8010F61C_toadstool_titan < 24) {
            u8 tbl[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };

            f = tbl[D_8010F61C_toadstool_titan & 7];
            if (D_8010F61C_toadstool_titan >= 6) {
                f = 1.5 - f * 0.5;
            } else {
                f = f * 0.5 + 1.5;
            }
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], f, f, f);
            if (D_8010F61C_toadstool_titan == 1) {
                mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
                mw->unkC5 = func_8004AC98_main(0x3A4, mw->unk59);
                mw->unkC4 = -1;
            }
        } else {
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
        }
        p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
        Hu3DModelScaleSet(p->model[1], p->scale.x, p->scale.y, p->scale.z);
        if (D_8010F61C_toadstool_titan == 13) {
            if (D_8010F5FC_toadstool_titan == 2) {
                D_8010F586_toadstool_titan = 7;
                D_8010F61C_toadstool_titan = 0;
            } else {
                D_8010F586_toadstool_titan = 9;
                D_8010F61C_toadstool_titan = 0;
                func_800E5A00_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0xD,
                                       func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->chr, D_8010F568_toadstool_titan[i]->unkE), 1, 0x78);
            }
        }
        break;
    case 7:
        if (D_8010F61C_toadstool_titan == 1) {
            for (j = 0; j < 9; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
            }
            D_8010EDCD_toadstool_titan = 1;
            HuAudFXPlay(0x3A9);
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0 && D_8010F614_toadstool_titan == 0) {
                func_800035E8_main(D_800D037E_main);
                func_80003B70_main(D_800CDBC8_main, 0);
                func_8004A72C_main(35);
                D_8010F614_toadstool_titan = 1;
            }
        }
        if (D_8010F61C_toadstool_titan == 10) {
            D_8010F586_toadstool_titan = 1;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 9; j++) {
                D_8010F650_toadstool_titan[j] = 1;
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 0);
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 0);
                for (m = 0; m < 4; m++) {
                    func_800E149C_minigame(D_8010F640_toadstool_titan[m], j + 1, 2);
                }
            }
            s = rand8() % 9;
            do {
                v = rand8() % 9;
            } while (s == v);
            D_8010F650_toadstool_titan[v] = 2;
            D_8010F650_toadstool_titan[s] = 2;
        }
        break;
    case 9:
        if (D_8010F5FC_toadstool_titan >= 3 && D_8010F58A_toadstool_titan < 4 && D_8010F61C_toadstool_titan >= 7) {
            mw = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->data;
            f = mw->unk3C;
            if (f < -10.0f) {
                mw->unk3C = f + 9.0f - f * 0.1;
            } else if (f > 10.0f) {
                mw->unk3C = f - 9.0f - f * 0.1;
            } else {
                mw->unk3C = 0.0f;
            }
        }
        break;
    }
    for (i = 0; i < 4; i++) {
        mw = D_8010F640_toadstool_titan[i]->data;
        mw->unk56 = 0;
        if (D_8010F616_toadstool_titan[i] != 0 && D_8010F616_toadstool_titan[i] < 60) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[i], 0x12);
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk40 = 0.0f;
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk44 = 0.0f;
            func_800E4E30_minigame(D_8010F640_toadstool_titan[i]);
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk0E = HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk0C;
            func_800E5138_minigame(D_8010F640_toadstool_titan[i]);
            D_8010F640_toadstool_titan[i]->trans.x += sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y += cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F640_toadstool_titan[i]->rot.y += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.z += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.x = 0.0f;
            D_8010F640_toadstool_titan[i]->trans.x += D_8010F659_toadstool_titan[i] ? 30.0f : -30.0f;
            if (D_8010F616_toadstool_titan[i] < 14) {
                D_8010F640_toadstool_titan[i]->trans.y += (1.0 - D_8010F616_toadstool_titan[i] / 13.0) * 65.0 + 15.0;
            } else {
                D_8010F640_toadstool_titan[i]->trans.y += 15.0;
            }
            D_8010F640_toadstool_titan[i]->trans.x -= sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y -= cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F616_toadstool_titan[i]++;
            if (D_8010F616_toadstool_titan[i] == 15) {
                mw->unkC5 = func_8004ACE0_main(0x286, mw->unk59);
                mw->unkC4 = -1;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (D_8010EDC4_toadstool_titan[j] != 0) {
            if (D_8010EDC4_toadstool_titan[j] >= 61) {
                D_8010EDC4_toadstool_titan[j] = 0;
                func_8001C258_main(obj->model[17 + j], 4, 4);
            } else {
                D_8010EDC4_toadstool_titan[j]++;
            }
        }
    }
    if (D_8010EDCD_toadstool_titan != 0) {
        if (D_8010EDCD_toadstool_titan >= 19) {
            D_8010EDCD_toadstool_titan = 0;
            for (j = 0; j < 9; j++) {
                func_8001C258_main(obj->model[8 + j], 4, 4);
            }
        } else {
            D_8010EDCD_toadstool_titan++;
        }
    }
    for (j = 0; j < 14; j++) {
        if (D_8010EDB4_toadstool_titan[j] != 0) {
            if (D_8010EDB4_toadstool_titan[j] >= 13) {
                D_8010EDB4_toadstool_titan[j] = 0;
                func_8001C258_main(obj->model[29 + j], 4, 4);
                func_8001C258_main(obj->model[43 + j], 4, 4);
            } else {
                D_8010EDB4_toadstool_titan[j]++;
                D_8010F4B0_toadstool_titan[j] -= 5.0f;
                D_8010F3D0_toadstool_titan[j] += D_8010F478_toadstool_titan[j];
                D_8010F408_toadstool_titan[j] += D_8010F4B0_toadstool_titan[j];
                D_8010F440_toadstool_titan[j] += D_8010F4E8_toadstool_titan[j];
                if (D_8010F408_toadstool_titan[j] < 0.0f) {
                    D_8010F408_toadstool_titan[j] = 0.0f;
                    D_8010F4B0_toadstool_titan[j] = -D_8010F4B0_toadstool_titan[j] * 0.3;
                }
                Hu3DModelPosSet(obj->model[29 + j], D_8010F3D0_toadstool_titan[j], D_8010F408_toadstool_titan[j], D_8010F440_toadstool_titan[j]);
                Hu3DModelPosSet(obj->model[43 + j], D_8010F3D0_toadstool_titan[j], 0.0f, D_8010F440_toadstool_titan[j]);
            }
        }
    }
    if (D_8010EDCE_toadstool_titan != 0 && D_8010EDD0_toadstool_titan == 0) {
        cm = &gCameraList->mtxs[D_800D418E_main];
        D_8010EDDC_toadstool_titan = 0.0f;
        D_8010EDD4_toadstool_titan = 0.0f;
        if (D_8010EDCE_toadstool_titan == 1) {
            func_8001F9E4_main(obj->model[3], 0xFF);
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 1 && D_8010EDCE_toadstool_titan < 55) {
            if (D_8010EDCE_toadstool_titan < 15) {
                f = 1.0 - D_8010EDCE_toadstool_titan / 15.0;
                D_8010EDD4_toadstool_titan = (1.0f - f * f * f) * 100.0f;
            } else {
                D_8010EDD4_toadstool_titan = 90.0f;
            }
            if (D_8010EDCE_toadstool_titan < 45) {
                D_8010EDD4_toadstool_titan += D_8010EDCE_toadstool_titan / 45.0 * 125.0;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan < 56) {
                f = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                D_8010EDD4_toadstool_titan = 215.0f - (f32)(1.0 - (f * f * 0.75 + f * 0.25)) * 180.0f;
            }
            if (D_8010EDCE_toadstool_titan < 55) {
                D_8010EDD8_toadstool_titan += (f32)(D_8010EDCE_toadstool_titan / 45.0) * 7.0f + 8.0f;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan < 55) {
                f = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                D_8010EDD8_toadstool_titan += (f32)(1.0 - (f * f * 0.75 + f * 0.25)) * 12.0f;
            }
        }
        if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 85) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 55 && D_8010EDCE_toadstool_titan < 85) {
            f = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
            D_8010EDDC_toadstool_titan = 2.0 * (1.0f - (f32)(f * f * 0.75 + f * 0.25)) + 1.0;
            if (D_8010EDCE_toadstool_titan >= 75) {
                D_8010EDD8_toadstool_titan += 5.0f;
            } else {
                D_8010EDD8_toadstool_titan += (1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0) * 15.0;
            }
            D_8010EDE0_toadstool_titan = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
        }
        if (D_8010EDD4_toadstool_titan > 0.0f) {
            for (j = 0; j < 5; j++) {
                if (D_8010EDCE_toadstool_titan >= 45) {
                    f = (D_8010EDCE_toadstool_titan - 45) / 10.0;
                } else {
                    f = 0.0f;
                }
                g = 1.0f - f;
                p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                hm = &HmfModelData[obj->model[1]];
                x = f * p->trans.x + g * hm->pos.x;
                y = (p->trans.y + 175.0f) * f + g * hm->pos.y;
                z = (p->trans.z + 85.0f) * f + g * hm->pos.z;
                guMtxL2F(mf, &cm->lookAtMtx);
                h = j * 72;
                func_80017C10_main((Mtx*)mf, cosdf(h + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + x,
                                   sindf(h + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + y, z);
                mf[0][0] = 0.45f;
                mf[0][1] = 0.0f;
                mf[0][2] = 0.0f;
                mf[1][0] = 0.0f;
                mf[1][1] = 0.45f;
                mf[1][2] = 0.0f;
                mf[2][0] = 0.0f;
                mf[2][1] = 0.0f;
                mf[2][2] = 0.45f;
                func_8002367C_main((f32(*)[4])HmfModelData[D_8010F5F8_toadstool_titan->model[3 + j]].mtx, mf);
            }
        }
        if (D_8010EDDC_toadstool_titan > 0.0f) {
            p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
            x = p->trans.x;
            y = p->trans.y + 175.0f;
            z = p->trans.z + 85.0f;
            guMtxL2F(mf, &cm->lookAtMtx);
            func_80017C10_main((Mtx*)mf, x, y, z);
            mf[0][0] = -sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[0][1] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[0][2] = 0.0f;
            mf[1][0] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[1][1] = sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[1][2] = 0.0f;
            mf[2][0] = 0.0f;
            mf[2][1] = 0.0f;
            mf[2][2] = D_8010EDDC_toadstool_titan;
            func_8002367C_main((f32(*)[4])HmfModelData[D_8010F5F8_toadstool_titan->model[2]].mtx, mf);
            func_8001F9E4_main(obj->model[2], (u32)(D_8010EDE0_toadstool_titan * 255.0f));
        }
        D_8010EDCE_toadstool_titan++;
        if (D_8010EDCE_toadstool_titan == 90) {
            D_8010EDCE_toadstool_titan = 0;
        }
    } else if (D_8010EDD0_toadstool_titan != 0) {
        f = 1.0 - D_8010EDD0_toadstool_titan / 20.0;
        func_8001F9E4_main(obj->model[3], (s32)(f * f * 255.0f));
        D_8010EDD0_toadstool_titan++;
        if (D_8010EDD0_toadstool_titan == 20) {
            D_8010EDD0_toadstool_titan = 0;
            D_8010EDCE_toadstool_titan = 0;
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
    }
    if (D_8010F586_toadstool_titan == 5) {
        c2 = (D_8010EDE4_toadstool_titan + 1) % 51;
        D_8010EDE4_toadstool_titan = c2;
        if (c2 % 17 == 0) {
            k2 = c2 / 17;
            D_8010EDE8_toadstool_titan[k2] = 0;
            func_8010B4D4_toadstool_titan(obj->model[26 + k2], 0);
            func_8001C258_main(obj->model[26 + k2], 4, 0);
            p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
            Hu3DModelPosSet(obj->model[26 + k2], p->trans.x * 0.9, 300.0f, p->trans.z - 15.0f);
        }
    } else {
        D_8010EDE4_toadstool_titan = 0;
    }
    for (j = 0; j < 3; j++) {
        D_8010EDE8_toadstool_titan[j] = (D_8010EDE8_toadstool_titan[j] >= 55) ? D_8010EDE8_toadstool_titan[j] : D_8010EDE8_toadstool_titan[j] + 1;
        if (D_8010EDE8_toadstool_titan[j] >= 55) {
            D_8010EDE8_toadstool_titan[j] = 55;
            func_8001C258_main(obj->model[26 + j], 4, 4);
        }
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF88_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80107360_toadstool_titan);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010AD8C_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B4D4_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B510_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B658_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B99C_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BA80_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BB64_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BC48_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F218_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F238_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F278_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BD2C_toadstool_titan);
