#include "common.h"
#include "mgcol.h"
#include "mallocblock.h"

/* .data (0x800EB720-0x800EBB10): actor and player physics constants (the first 0x60 bytes as MP2
   src/1130.c), then tables the other units and the minigame overlays use. */
/* 800EB720 size 0x4 */ f32 D_800EB720_minigame = 1.0f;
/* 800EB724 size 0x4 */ f32 D_800EB724_minigame = 20.0f;
/* 800EB728 size 0x4 */ f32 D_800EB728_minigame = 4.0f;
/* 800EB72C size 0x4 */ f32 D_800EB72C_minigame = 0.06f;
/* 800EB730 size 0x4 */ s32 D_800EB730_minigame = 0;
/* 800EB734 size 0x1 */ u8 D_800EB734_minigame = 0x00;
/* 800EB735 size 0x1 */ u8 D_800EB735_minigame = 0x01;
/* 800EB736 size 0x2 */ s16 D_800EB736_minigame = 0x0000;
/* 800EB738 size 0x1 */ u8 D_800EB738_minigame = 0xFF;
/* 800EB739 size 0x1 */ u8 D_800EB739_minigame = 0x00;
/* 800EB73A size 0x1 */ u8 D_800EB73A_minigame = 0x00;
/* 800EB73B size 0x1 */ u8 D_800EB73B_minigame = 0x00;
/* 800EB73C size 0x4 */ f32 D_800EB73C_minigame = 15.0f;
/* 800EB740 size 0x4 */ f32 D_800EB740_minigame = 0.5f;
/* 800EB744 size 0x4 */ f32 D_800EB744_minigame = 1.47f;
/* 800EB748 size 0x4 */ f32 D_800EB748_minigame = 0.15f;
/* 800EB74C size 0x4 */ f32 D_800EB74C_minigame = 7.0f;
/* 800EB750 size 0x4 */ f32 D_800EB750_minigame = 30.0f;
/* 800EB754 size 0x4 */ f32 D_800EB754_minigame = 60.0f;
/* 800EB758 size 0x4 */ f32 D_800EB758_minigame = 20.0f;
/* 800EB75C size 0x4 */ f32 D_800EB75C_minigame = 3.3333333f;
/* 800EB760 size 0x4 */ f32 D_800EB760_minigame = 18.0f;
/* 800EB764 size 0x4 */ f32 D_800EB764_minigame = 13.5f;
/* 800EB768 size 0x4 */ f32 D_800EB768_minigame = 9.0f;
/* 800EB76C size 0x4 */ f32 D_800EB76C_minigame = 4.5f;
/* 800EB770 size 0x4 */ f32 D_800EB770_minigame = 0.0f;
/* 800EB774 size 0x4 */ f32 D_800EB774_minigame = 1.7f;
/* 800EB778 size 0x4 */ f32 D_800EB778_minigame = 0.5f;
/* 800EB77C size 0x4 */ f32 D_800EB77C_minigame = 0.147f;
/* 800EB780 */ s8 D_800EB780_minigame = 0;
/* 800EB784: per player sound ids (MP2 D_800BF7E4_C03E4); asm names row 0's elements
   1-13 (undefined_syms.txt) */
u16 D_800EB784_minigame[4][14] = { 0 };
/* 800EB7F4 */ s32 D_800EB7F4_minigame[3] = { 0, 0, 0 }; /* unreferenced */
/* 800EB800 size 0x20 */ u32 D_800EB800_minigame[8] = {
    0x000200A3, 0x000300A3, 0x000700A3, 0x000400A3,
    0x000500A3, 0x000600A3, 0x000800A3, 0x0009001A,
};
/* 800EB820 size 0xE0 */ u32 D_800EB820_minigame[56] = {
    0x000000A4, 0x000000A5, 0x000000A6, 0x000000A7,
    0x000000A8, 0x000000A9, 0x000000AA, 0x000000A4,
    0x000000A5, 0x000000A6, 0x000000A7, 0x000000A8,
    0x000000A9, 0x000000AA, 0x000000A4, 0x000000A5,
    0x000000A6, 0x000000A7, 0x000000A8, 0x000000A9,
    0x000000AA, 0x000000A4, 0x000000A5, 0x000000A6,
    0x000000A7, 0x000000A8, 0x000000A9, 0x000000AA,
    0x000000A4, 0x000000A5, 0x000000A6, 0x000000A7,
    0x000000A8, 0x000000A9, 0x000000AA, 0x000000A4,
    0x000000A5, 0x000000A6, 0x000000A7, 0x000000A8,
    0x000000A9, 0x000000AA, 0x000000A4, 0x000000A5,
    0x000000A6, 0x000000A7, 0x000000A8, 0x000000A9,
    0x000000AA, 0x000000A4, 0x000000A5, 0x000000A6,
    0x000000A7, 0x000000A8, 0x000000A9, 0x000000AA,
};
/* 800EB900 size 0x10 */ u32 D_800EB900_minigame[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
/* 800EB910 size 0x2 */ s16 D_800EB910_minigame = 0x0000;
/* 800EB912 size 0x2 */ s16 D_800EB912_minigame = 0x0000;
/* 800EB914 size 0x2 */ s16 D_800EB914_minigame = 0x0000;
/* 800EB916 size 0x2 */ s16 D_800EB916_minigame = 0x0000;
/* 800EB918 size 0x2 */ s16 D_800EB918_minigame = 0x0000;
/* 800EB91A size 0x2 */ s16 D_800EB91A_minigame = 0x0000;
/* 800EB91C size 0x4 */ u32 D_800EB91C_minigame = 0x00000090;
/* 800EB920 size 0x4 */ u32 D_800EB920_minigame = 0x000000D0;
/* 800EB924 size 0x2 */ s16 D_800EB924_minigame = 0x0000;
/* 800EB926 */ s16 D_800EB926_minigame = 0x0001;
/* 800EB928 */ s16 D_800EB928_minigame = 0x0000;
/* 800EB92A size 0x2 */ s16 D_800EB92A_minigame = -1;
/* 800EB92C size 0x2 */ s16 D_800EB92C_minigame = -1;
/* 800EB92E size 0x2 */ s16 D_800EB92E_minigame = -1;
/* 800EB930 size 0x2 */ s16 D_800EB930_minigame = -1;
/* 800EB932 size 0x2 */ s16 D_800EB932_minigame = 0x004B;
/* 800EB934 size 0x4 */ s16 D_800EB934_minigame[2] = {
    0x0000, 0x0000,
};
/* 800EB938 size 0x4 */ f32 D_800EB938_minigame = 0.0f;
/* 800EB93C size 0x4 */ u32 D_800EB93C_minigame = 0x00000000;
/* 800EB940 size 0x10 */ u32 D_800EB940_minigame[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
/* 800EB950 size 0x78 */ u32 D_800EB950_minigame[30] = {
    0x00150000, 0x0000FFB5, 0x00150002, 0x00000008,
    0x00150011, 0xFFAAFFEA, 0x00150012, 0x0000FFEA,
    0x00150013, 0x0056FFEA, 0x00150014, 0xFFAA0018,
    0x00150015, 0x00000018, 0x00150016, 0x00560018,
    0x00150017, 0xFFAAFFEA, 0x00150018, 0x0000FFEA,
    0x00150019, 0x0056FFEA, 0x0015001A, 0xFFAA0018,
    0x0015001B, 0x00000018, 0x0015001C, 0x00560018,
    0x0015001E, 0x00000001,
};
/* 800EB9C8 size 0x1C */ u32 D_800EB9C8_minigame[7] = {
    0x0015000D, 0x0015000C, 0x0015000B, 0x0015000A,
    0x0015000A, 0x0015000A, 0x0015000A,
};
/* 800EB9E4 size 0x18 */ u32 D_800EB9E4_minigame[6] = {
    0x00150004, 0x00150005, 0x00150006, 0x00150007,
    0x00150008, 0x00150009,
};
/* 800EB9FC size 0x18 */ u32 D_800EB9FC_minigame[6] = {
    0x00001C00, 0x00001C01, 0x00001C02, 0x00001C03,
    0x00001C04, 0x00001C05,
};
/* 800EBA14 size 0x10 */ u32 D_800EBA14_minigame[4] = {
    0x00006102, 0x00006103, 0x00006104, 0x00006105,
};
/* 800EBA24 size 0x1C */ u32 D_800EBA24_minigame[7] = {
    0x00006112, 0x00006113, 0x00006116, 0x00006117,
    0x00006118, 0x00006118, 0x00006118,
};
/* 800EBA40 size 0xC */ u32 D_800EBA40_minigame[3] = {
    0xFF505050, 0xFF50FFFF, 0x50000000,
};
/* 800EBA4C size 0xC */ u32 D_800EBA4C_minigame[3] = {
    0xFF5050FF, 0xFFFF0000, 0x00000000,
};
/* 800EBA58 size 0x18; asm names +1 and +2 (undefined_syms.txt) */ u8 D_800EBA58_minigame[24] = {
    0x8C, 0x87, 0x87, 0x7B, 0x2A, 0xBF, 0xF0, 0xD9, 0x12, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
};
/* 800EBA70 size 0x2 */ s16 D_800EBA70_minigame = -72;
/* 800EBA72 size 0x2 */ s16 D_800EBA72_minigame = -98;
/* 800EBA74 size 0x2C; asm names +2 (undefined_syms.txt) */ s16 D_800EBA74_minigame[22] = {
    0x0050, 0x0030, 0x0006, -98, 0x0070, 0x0014, 0x0006, -84,
    0x0070, 0x0014, 0x0006, -70, 0x0070, 0x0014, -120, -50,
    0x00F0, 0x0014, -104, -18, 0x0070, 0x0069,
};
/* 800EBAA0 size 0x1C */ u32 D_800EBAA0_minigame[7] = {
    0xFFAAFFFD, 0x0000FFFD, 0x0056FFFD, 0xFFAA002B,
    0x0000002B, 0x0056002B, 0x00000014,
};
/* 800EBABC size 0x10 */ u32 D_800EBABC_minigame[4] = {
    0x00006106, 0x00006107, 0x00006108, 0x00006109,
};
/* 800EBACC size 0x8 */ u8 D_800EBACC_minigame[8] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0B, 0x00, 0x00,
};
/* 800EBAD4 size 0x8 */ u8 D_800EBAD4_minigame[8] = {
    0x01, 0x03, 0x05, 0x07, 0x09, 0x0A, 0x00, 0x00,
};
/* 800EBADC size 0x8 */ u8 D_800EBADC_minigame[8] = {
    0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00,
};
/* 800EBAE4 size 0x8 */ u8 D_800EBAE4_minigame[8] = {
    0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00,
};
/* 800EBAEC size 0x4 */ u8 D_800EBAEC_minigame[4] = {
    0x0D, 0x1A, 0x1E, 0x22,
};
/* 800EBAF0 size 0x4 */ s16 D_800EBAF0_minigame[2] = {
    0x0000, 0x0000,
};
/* 800EBAF4 size 0x1C */ u8 D_800EBAF4_minigame[28] = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x01, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

f32 func_800D6E14_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800D6E74_minigame(omObjData* obj, Vec* n);
void func_800D6F20_minigame(omObjData* obj, Vec* n);
void func_800D7084_minigame(ColActorWork* w);
void func_800D710C_minigame(omObjData* obj);
void func_800D71F0_minigame(omObjData* obj);
f32 func_800D72B0_minigame(omObjData* obj, Vec4f* p);
void func_800D7388_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n);
f32 func_800D74AC_minigame(omObjData* obj, Vec4f* p, Vec* n);
void func_800D7AA8_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800D7C14_minigame(omObjData* obj, Vec4f* p);
void func_800D7FA8_minigame(omObjData* obj);
void func_800D80DC_minigame(omObjData* obj);

/* AB1C0 */
f32 func_800D8818_minigame(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri, Vec* dir, Vec* out);
s32 func_800DB704_minigame(s32 n, u16* idx, ColVtx* verts, HitProbe* probe);
s32 func_800DBCF4_minigame(s32 n, s16* idx, ColVtx* verts, HitProbe* probe);
void func_800DC354_minigame(omObjData* g, Vec4f* p, Vec* save);
void func_800DC7D8_minigame(omObjData* g, Vec4f* p);
void func_800DC8E4_minigame(omObjData* g, Vec4f* p, f32 h);
void func_800DCCB0_minigame(omObjData* g, Vec4f* p, Vec* save, f32 h);
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d);
/* B3CE0 */
void func_800E1594_minigame(omObjData* obj, s32 arg1, s32 arg2, s32 arg3);
void func_800E1718_minigame(omObjData* obj, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E17F4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E28BC_minigame(f32 (*l2w)[4], f32 (*w2l)[4], Vec* p, omObjData* g);
void func_800E2B58_minigame(f32 (*m)[4], Vec* v);
void func_800E2BD4_minigame(f32 (*m)[4], Vec* v);
void func_800E2C68_minigame(f32 (*m)[4], Vec* v);
s32 func_800E2F40_minigame(void* parts, Vec* p);
s32 func_800E2FD8_minigame(void* parts, Vec* p, f32 r);
s32 func_800E30B8_minigame(Vec* p, GroundWork* gw);
void func_800E3628_minigame(s16 mdl, Vec* n);

/* main */
s32 func_800202FC_main(Vec* v);                                     /* normalise */
void func_8002038C_main(ColVtx* a, ColVtx* b, ColVtx* c, Vec* n);  /* face normal */
f32 func_800204F4_main(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri); /* face height */
void func_80021C14_main(s16 mi, HitList* l, s32 (*cb)(s32, u16*, ColVtx*, HitProbe*), HitProbe* probe);
u16* func_80022198_main(HitList* l);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014714_main(s16 index, u16 arg1);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
f32 HuVecDot3F(Vec* a, Vec* b);
f64 fabs(f64);


extern Vec D_800EBDC0_minigame;          /* the actor's position at the start of its step */
extern u16 D_800EBE28_minigame;          /* ground object count */
extern f32 D_800EBE2C_minigame;          /* push x this frame */
extern f32 D_800EBE30_minigame[4][4];    /* ground object: world to local */
extern HitList D_800EBEB0_minigame;      /* face query */
extern omObjData* D_800EC1C0_minigame[]; /* ground objects */
extern f32 D_800EC240_minigame[4][4];    /* ground object: local to world */
extern u16 D_800EC280_minigame;          /* player count */
extern Vec D_800EC298_minigame[];        /* contact points */
extern omObjData* D_800EC598_minigame[]; /* player objects */
extern f32 D_800EC5D8_minigame;          /* push z this frame */

void func_800D6B70_minigame(omObjData* obj) {
    ColActorWork* w = obj->data;
    s32 ret = 0;
    f32 x, y, z;
    f32 rot;
    f32 vy;
    f32 h;

    if (w->unk_50 & 0x20) {
        if (w->unk_50 & 0x10) {
            return;
        }
    }
    {
        D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
        D_800EBDC0_minigame.x = x = obj->trans.x;
        D_800EBDC0_minigame.y = y = obj->trans.y;
        D_800EBDC0_minigame.z = z = obj->trans.z;
        rot = w->unk_3C;
        if (w->unk_84[0] != NULL && w->unk_84[0](obj) == 1) {
            return;
        }
        x += sindf(rot) * w->unk_40;
        z += cosdf(rot) * w->unk_40;
        func_800D7084_minigame(w);
        vy = w->unk_38;
        if (vy != 1000.0f) {
            y += vy * vy * ((vy >= 0.0f) ? -35.0f : 35.0f);
            w->unk_38 += D_800EB72C_minigame;
            if (D_800EB720_minigame < w->unk_38) {
                w->unk_38 = D_800EB720_minigame;
            }
            h = func_800D6E14_minigame(obj, x, y, z);
            if (y < h) {
                if (w->unk_84[4] != NULL) {
                    ret = w->unk_84[4](obj);
                }
                y = h;
                if (ret != 1) {
                    w->unk_38 = -w->unk_38 * 0.7f;
                    if (w->unk_38 >= -0.4f) {
                        w->unk_38 = 1000.0f;
                    }
                    func_800D710C_minigame(obj);
                }
            }
        } else {
            y = func_800D6E14_minigame(obj, x, y, z);
            func_800D710C_minigame(obj);
            func_800D71F0_minigame(obj);
        }
        func_800E17D4_minigame(obj, x + D_800EBE2C_minigame, y, z + D_800EC5D8_minigame);
        func_800D80DC_minigame(obj);
        if (w->unk_84[1] != NULL) {
            w->unk_84[1](obj);
        }
    }
}

f32 func_800D6E14_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    ColActorWork* w = obj->data;
    Vec4f p;

    p.x = x;
    p.y = y;
    p.z = z;
    p.w = w->unk_48;
    func_800D7AA8_minigame(obj, x, y, z);
    func_800D7C14_minigame(obj, &p);
    return func_800D72B0_minigame(obj, &p);
}

void func_800D6E74_minigame(omObjData* obj, Vec* n) {
    ColActorWork* w = obj->data;
    GroundWork* gw;

    if (w->unk_53 >= 0 && w->unk_38 == 1000.0f) {
        gw = D_800EC1C0_minigame[w->unk_53]->data;
        w->unk_5C = n->x * gw->unk_10;
        w->unk_60 = n->y;
        w->unk_64 = n->z * gw->unk_10;
        if (gw->unk_06 & 0x400) {
            func_800D6F20_minigame(obj, n);
        }
    } else {
        w->unk_5C = 0.0f;
        w->unk_60 = 0.0f;
        w->unk_64 = 0.0f;
    }
}

void func_800D6F20_minigame(omObjData* obj, Vec* n) {
    ColActorWork* w = obj->data;
    f32 ax = -(atan2df(n->y, n->z) - 90.0f);
    f32 az = atan2df(n->y, n->x) - 90.0f;
    f32 cx = w->unk_68;
    f32 cz = w->unk_70;

    if (cx < ax) {
        w->unk_68 = cx + D_800EB728_minigame;
        if (ax < w->unk_68) {
            w->unk_68 = ax;
        }
    } else if (ax < cx) {
        w->unk_68 -= D_800EB728_minigame;
        if (w->unk_68 < ax) {
            w->unk_68 = ax;
        }
    }
    if (cz < az) {
        w->unk_70 += D_800EB728_minigame;
        if (az < w->unk_70) {
            w->unk_70 = az;
        }
    } else if (az < cz) {
        w->unk_70 -= D_800EB728_minigame;
        if (w->unk_70 < az) {
            w->unk_70 = az;
        }
    }
    obj->rot.x = w->unk_68;
    obj->rot.z = w->unk_70;
}

void func_800D7084_minigame(ColActorWork* w) {
    if (fabs(w->unk_5C) > 1.0) {
        D_800EBE2C_minigame += w->unk_5C * w->unk_58;
    }
    if (fabs(w->unk_64) > 1.0) {
        D_800EC5D8_minigame += w->unk_64 * w->unk_58;
    }
}

/* Friction: slow the actor on its ground object. */
void func_800D710C_minigame(omObjData* obj) {
    ColActorWork* w = obj->data;
    f32 f;

    if (w->unk_53 != -1) {
        if (w->unk_84[2] == NULL || w->unk_84[2](obj) != 1) {
            f = ((GroundWork*)D_800EC1C0_minigame[w->unk_53]->data)->unk_08;
            if (f != 0.0f) {
                w->unk_40 = w->unk_40 - f;
            } else {
                w->unk_40 = w->unk_40 - D_800EB740_minigame;
            }
            if (w->unk_40 < D_800EB770_minigame) {
                w->unk_40 = D_800EB770_minigame;
            }
            if (w->unk_40 > D_800EB724_minigame) {
                w->unk_40 = D_800EB724_minigame;
            }
        }
    }
}

void func_800D71F0_minigame(omObjData* obj) {
    ColActorWork* w = obj->data;
    Vec v;

    if (w->unk_84[3] == NULL || w->unk_84[3](obj) != 1) {
        v.x = -D_800EBE2C_minigame;
        v.y = 0.0f;
        v.z = -D_800EC5D8_minigame;
        func_800202FC_main(&v);
        v.x = sindf(w->unk_3C) - v.x / 20.0f;
        v.z = cosdf(w->unk_3C) - v.z / 20.0f;
        w->unk_3C = atan2df(v.x, v.z);
    }
}

f32 func_800D72B0_minigame(omObjData* obj, Vec4f* p) {
    ColActorWork* w = obj->data;
    Vec n;
    f32 y = p->y;
    f32 h = func_800D74AC_minigame(obj, p, &n);
    f32 g = h;

    if (h < y - w->unk_34 || y + w->unk_34 <= h) {
        if (w->unk_38 == 1000.0f) {
            w->unk_38 = 0.0f;
        }
        h = y;
    }
    func_800D7388_minigame(obj, p->x, h, p->z, g, &n);
    return h;
}

/* The shadow (model[1]) follows the ground under the actor, shrinking with the height. */
void func_800D7388_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n) {
    ColActorWork* w = obj->data;
    f32 s = 1.0f;
    f32 d;

    if (obj->model[1] != 0) {
        d = y - g;
        if (d != 0.0f) {
            if (d > 400.0f) {
                s = 0.6f;
            } else {
                s = 1.0 - fabs(d) / 1000.0;
            }
            w->unk_53 = -1;
        }
        Hu3DModelPosSet(obj->model[1], x, g + 5.0f, z);
        Hu3DModelScaleSet(obj->model[1], s, 1.0f, s);
        func_800E3628_minigame(obj->model[1], n);
    }
}

/* Highest ground under the actor (below y + 150), its object in w->unk_53 and its normal in n. */
f32 func_800D74AC_minigame(omObjData* obj, Vec4f* p, Vec* n) {
    Vec q;
    s32 pad[8];
    Vec a;
    Vec d;
    f32 x = p->x;
    f32 y = p->y;
    f32 z = p->z;
    ColActorWork* w = obj->data;
    f32 best = -65536.0f;
    s16 i;
    omObjData* g;
    GroundWork* gw;
    f32 h;
    s16 mdl;
    ColVtx* verts;
    ColTri* tri;
    u8 moved;

    w->unk_53 = -1;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        g = D_800EC1C0_minigame[i];
        gw = g->data;
        if (w->unk_00[i] & 1) {
            continue;
        }
        q.x = x;
        q.y = y;
        q.z = z;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &q, g);
        if ((gw->unk_06 & 4) && func_800E2F40_minigame(HmfModelData[*g->model].hmf->unk60, &q) == 0) {
            continue;
        }
        if (gw->unk_06 & 0x7A) {
            if ((gw->unk_06 & 0x50) && func_800E30B8_minigame(&q, gw) == 0) {
                continue;
            }
            h = gw->unk_14;
            if (g->trans.x != 0.0f || g->trans.y != 0.0f || g->trans.z != 0.0f || g->rot.x != 0.0f ||
                g->rot.y != 0.0f || g->rot.z != 0.0f) {
                q.y = h;
                func_800E2C68_minigame(D_800EC240_minigame, &q);
                if (best <= q.y && q.y < y + 150.0f) {
                    best = q.y;
                    w->unk_53 = i;
                    if (n != NULL) {
                        a.x = 0.0f;
                        a.y = 1.0f;
                        a.z = 0.0f;
                        func_800E2B58_minigame(D_800EC240_minigame, &a);
                        n->x = a.x;
                        n->y = a.y;
                        n->z = a.z;
                        func_800202FC_main(n);
                    }
                }
            } else if (best <= h && h < y + 150.0f) {
                best = h;
                w->unk_53 = i;
                if (n != NULL) {
                    n->x = 0.0f;
                    n->y = 1.0f;
                    n->z = 0.0f;
                }
            }
        } else {
            mdl = *g->model;
            verts = HmfModelData[mdl].hmf->unk50;
            func_80021C14_main(mdl, &D_800EBEB0_minigame, func_800DB704_minigame, (HitProbe*)&q);
            for (tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame); tri != NULL;
                 tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame)) {
                HmfModel* m = &HmfModelData[mdl];

                moved = 0;
                if (m->pos.x != 0.0f || m->pos.y != 0.0f || m->pos.z != 0.0f || m->rot.x != 0.0f ||
                    m->rot.y != 0.0f || m->rot.z != 0.0f) {
                    a.x = x;
                    a.y = y + 10.0f;
                    a.z = z;
                    func_800E2BD4_minigame(D_800EBE30_minigame, &a);
                    d.x = a.x - q.x;
                    d.y = a.y - q.y;
                    d.z = a.z - q.z;
                    func_800202FC_main(&d);
                    func_800D8818_minigame(q.x, q.y, q.z, verts, tri, &d, &q);
                    func_800E2C68_minigame(D_800EC240_minigame, &q);
                    h = q.y;
                    moved = 1;
                } else {
                    h = func_800204F4_main(q.x, q.y, q.z, verts, tri);
                }
                if (best <= h && h < y + 150.0f) {
                    best = h;
                    w->unk_53 = i;
                    if (n != NULL) {
                        func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], n);
                        if (moved == 1) {
                            a.x = n->x;
                            a.y = n->y;
                            a.z = n->z;
                            func_800E2B58_minigame(D_800EC240_minigame, &a);
                            n->x = a.x;
                            n->y = a.y;
                            n->z = a.z;
                            func_800202FC_main(n);
                        }
                    }
                }
            }
        }
    }
    func_800D6E74_minigame(obj, n);
    return best;
}

/* Players standing next to a grounded actor push it away. */
// register allocation (masked 0, raw 6): the hoisted 0.0f outranks x/z (f26 vs retail f30), as in
// MP2's func_80001468_2068
#ifdef NON_MATCHING
void func_800D7AA8_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    ColActorWork* w = obj->data;
    omObjData* o;
    MgWork* ow;
    f32 dx, dz;
    f32 d;
    s32 i;

    if (!(w->unk_52 & 7)) {
        for (i = 0; i < D_800EC280_minigame; i++) {
            o = D_800EC598_minigame[i];
            ow = o->data;
            dx = o->trans.x - (x + D_800EBE2C_minigame);
            dz = o->trans.z - (z + D_800EC5D8_minigame);
            d = HuSqrtf(dx * dx + dz * dz) - (w->unk_48 + ow->unk_48);
            if (d < 0.0f && w->unk_38 == 1000.0f && ow->unk_38 == 1000.0f) {
                func_800DFCDC_minigame(dx, dz, d);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7AA8_minigame);
#endif

/* Ground objects with a primitive shape (GroundWork.unk_06 8/0x10/0x20/0x40) or a face list push
   the actor out; each new contact point (D_800EC298_minigame) is moved to world space. Retail adds
   the z push to the probe's y (not z) before the primitive tests. */
void func_800D7C14_minigame(omObjData* obj, Vec4f* p) {
    ColActorWork* w = obj->data;
    Vec4f base;
    Vec4f probe;
    Vec save;
    s16 i;
    omObjData* g;
    GroundWork* gw;
    s16 prev;

    base.x = p->x;
    base.y = w->unk_34 / 2.0f + p->y;
    base.z = p->z;
    base.w = p->w;
    D_800EB736_minigame = 0;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        g = D_800EC1C0_minigame[i];
        gw = g->data;
        if (gw->unk_06 & 2) {
            continue;
        }
        if (w->unk_00[i] & 1) {
            continue;
        }
        prev = D_800EB736_minigame;
        probe.x = save.x = p->x;
        probe.y = save.y = w->unk_34 / 2.0f + p->y;
        probe.z = save.z = p->z;
        probe.w = base.w = p->w;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, (Vec*)&probe, g);
        if ((gw->unk_06 & 4) &&
            func_800E2FD8_minigame(HmfModelData[*g->model].hmf->unk60, (Vec*)&probe, w->unk_48) == 0) {
            continue;
        }
        if (gw->unk_06 & 8) {
            probe.x += D_800EBE2C_minigame;
            probe.y += D_800EC5D8_minigame;
            func_800DC354_minigame(g, &probe, &save);
        } else if (gw->unk_06 & 0x10) {
            probe.x += D_800EBE2C_minigame;
            probe.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(g, &probe, &save, w->unk_34 / 2.0f);
        } else if (gw->unk_06 & 0x20) {
            probe.x += D_800EBE2C_minigame;
            probe.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(g, &probe);
        } else if (gw->unk_06 & 0x40) {
            probe.x += D_800EBE2C_minigame;
            probe.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(g, &probe, w->unk_34 / 2.0f);
        } else {
            func_80021C14_main(*D_800EC1C0_minigame[i]->model, &D_800EBEB0_minigame,
                               (s32 (*)(s32, u16*, ColVtx*, HitProbe*))func_800DBCF4_minigame,
                               (HitProbe*)&probe);
        }
        if (prev != D_800EB736_minigame) {
            func_800E2B58_minigame(D_800EC240_minigame, &D_800EC298_minigame[prev]);
        }
    }
    func_800D7FA8_minigame(obj);
}

/* After a contact, reflect the heading off the first contact normal. */
void func_800D7FA8_minigame(omObjData* obj) {
    ColActorWork* w;
    Vec a;
    Vec b;
    Vec c;
    f32 d;

    if (D_800EB736_minigame != 0) {
        w = obj->data;
        if (w->unk_84[5] == NULL || w->unk_84[5](obj) != 1) {
            a.x = D_800EC298_minigame[0].x;
            a.y = b.y = 0.0f;
            a.z = D_800EC298_minigame[0].z;
            b.x = sindf(w->unk_3C + 180.0f);
            b.z = cosdf(w->unk_3C + 180.0f);
            d = HuVecDot3F(&a, &b);
            a.x *= d;
            a.z *= d;
            HuVecSubtract(&c, &a, &b);
            HuVecAdd(&c, &a, &c);
            w->unk_3C = atan2df(c.x, c.z);
            w->unk_40 *= 0.8f;
        }
    }
}

/* Lifetime: the last 45 frames blink the model, then the actor is switched off. */
void func_800D80DC_minigame(omObjData* obj) {
    ColActorWork* w = obj->data;
    s32 left;

    w->unk_78++;
    if (w->unk_84[7] == NULL || w->unk_84[7](obj) != 1) {
        if (w->unk_7C > 0) {
            left = w->unk_7C - w->unk_78;
            if (left < 45) {
                switch (left & 2) {
                    case 0:
                        func_8001C258_main(obj->model[0], 4, 4);
                        break;
                    case 2:
                        func_8001C258_main(obj->model[0], 4, 0);
                        break;
                }
                if (w->unk_7C <= w->unk_78) {
                    w->unk_54 = 0;
                    func_8001C258_main(obj->model[0], 4, 4);
                    func_8001C258_main(obj->model[1], 4, 4);
                }
            }
        }
    }
}

/* A player (obj) touches an item actor: coins of kinds 3-6 pay 1, 3, 2, 5. */
void func_800D81C8_minigame(omObjData* obj, omObjData* actor) {
    ColActorWork* aw = actor->data;
    MgWork* w = obj->data;
    u8 slot;
    u8 mdl;

    if (aw->unk_84[8] == NULL || aw->unk_84[8](obj, actor) != 1) {
        slot = aw->unk_24;
        mdl = actor->model[3];
        func_8001C258_main(mdl, 4, 0);
        func_80014714_main(slot, 0);
        func_800146DC_main(slot, 4, 4);
        Hu3DModelPosSet(mdl, actor->trans.x, actor->trans.y, actor->trans.z);
        Hu3DModelScaleSet(mdl, 5.0f, 5.0f, 5.0f);
        switch (aw->unk_52) {
            case 3:
                GwPlayer[w->unk_59].gameCoin += 1;
                HuAudFXPlay(0);
                break;
            case 4:
                GwPlayer[w->unk_59].gameCoin += 3;
                HuAudFXPlay(0);
                break;
            case 5:
                GwPlayer[w->unk_59].gameCoin += 2;
                HuAudFXPlay(0);
                break;
            case 6:
                GwPlayer[w->unk_59].gameCoin += 5;
                HuAudFXPlay(0);
                omVibrate(w->unk_59, 2, 3, 10);
                break;
        }
        aw->unk_54 = 0;
        aw->unk_78 = 0;
        func_8001C258_main(actor->model[0], 4, 4);
        func_8001C258_main(actor->model[1], 4, 4);
    }
}

/* Set up an item actor of the given kind (3: a coin with its sparkle). */
void func_800D83D8_minigame(omObjData* obj, s32 kind) {
    ColActorWork* w;
    s16 shadow = 0x299;
    s32 i;

    /* both arms are the same: an always-true test (w is not set yet) that keeps shadow out of
       constant propagation (permuter shape from MP2's func_80001DE0_29E0) */
    if (w) {
        obj->data = HuMemAllocTag(sizeof(ColActorWork), 0x7918);
        memset(obj->data, 0, sizeof(ColActorWork));
        w = obj->data;
        w->unk_A8 = HuMemAllocTag(4, 0x7918);
    } else {
        obj->data = HuMemAllocTag(sizeof(ColActorWork), 0x7918);
        memset(obj->data, 0, sizeof(ColActorWork));
        w = obj->data;
        w->unk_A8 = HuMemAllocTag(4, 0x7918);
    }
    if (kind == 3) {
        func_800E1594_minigame(obj, 0xA, 0x689, 8);
        func_800E1718_minigame(obj, 3, 0xC, shadow | 0x400, 8);
        func_80014794_main(w->unk_24, 0xF0);
        func_800147FC_main(w->unk_24, 0xFF, 0xFF, 0x86);
    }
    if (D_800EB739_minigame == 0) {
        obj->model[1] = func_8000B0D4_main(0, shadow);
    } else {
        obj->model[1] = func_8000B0D4_main(9, shadow);
    }
    w->unk_44 = 0.0f;
    w->unk_48 = 20.0f;
    w->unk_34 = 50.0f;
    w->unk_3C = 0.0f;
    w->unk_78 = 0;
    w->unk_52 = kind;
    w->unk_7C = 300;
    w->unk_50 = 0;
    w->unk_40 = 0.0f;
    func_800E17F4_minigame(obj, 2.0f, 2.0f, 2.0f);
    for (i = 0; i < 9; i++) {
        w->unk_84[i] = 0;
    }
}

/* Launch an item actor from a player: it takes the player's heading and speed (at least
   D_800EB760_minigame) and starts on top of the player. */
void func_800D853C_minigame(omObjData* obj, omObjData* actor) {
    MgWork* w;
    ColActorWork* aw;

    aw = actor->data;
    do { w = obj->data; } while (0);
    if (aw->unk_84[6] == NULL || aw->unk_84[6](obj, actor) != 1) {
        aw->unk_38 = -D_800EB744_minigame * 0.6f;
        aw->unk_3C = w->unk_3C;
        aw->unk_40 = w->unk_40;
        if (aw->unk_40 < D_800EB760_minigame) {
            aw->unk_40 = D_800EB760_minigame;
        }
        aw->unk_80 = 0;
        actor->trans.x = obj->trans.x;
        actor->trans.y = w->unk_34 + aw->unk_48 + obj->trans.y;
        actor->trans.z = obj->trans.z;
    }
}

void func_800D861C_minigame(ColActorWork* w, s32 slot, s32 (*fn)()) {
    if (slot < 9) {
        w->unk_84[slot] = fn;
    }
}
