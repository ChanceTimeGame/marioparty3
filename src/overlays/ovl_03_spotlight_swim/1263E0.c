#include "common.h"
// m5 sp: Spotlight Swim
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

typedef func_800E1BA8_minigame_ObjData MgWork;

/* One slot of the overlay's object table (D_8010D480_spotlight_swim, 50 x 0x84). */
typedef struct SsEnt {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} SsEnt; // Size 0x84

extern SsEnt D_8010D480_spotlight_swim[50];

void func_8000BC48_main(u16, s32);
omObjData *func_80045ED0_main(u32 arg0);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_800335BC_main(char *arg0, void *arg1);
void func_8004AE00_main(s16 handle, s16 pan);
s32 func_8000B710_main(s32 arg0);
void func_800E6F0C_minigame(s8 arg0);
void func_800DDD94_minigame(omObjData *obj);
void func_800E149C_minigame(omObjData *obj, u8 idx, u8 val);
void func_800E5978_minigame(omObjData *obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
extern s32 D_800EBE24_minigame;
void osViBlack(u8 active);
extern u16 D_800D530C_main;
f32 fabsf(f32);
f64 fabs(f64);
void func_8001C624_main(s16, s16, s16, s16, s16);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
s16 func_8004AC98_main(s16, s16);
void func_800E1304_minigame(omObjData *obj, f32 arg1);
void func_800E1310_minigame(omObjData *obj, f32 arg1);
void func_800E131C_minigame(omObjData *obj, f32 arg1);
void func_800E139C_minigame(omObjData *obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E4C88_minigame(omObjData *obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
extern f32 D_800EB73C_minigame;
extern D_800CCF58_main_Struct *D_800CCF58_main;


/* A camera (D_8010D1D4_spotlight_swim). */
typedef struct SsCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} SsCamera; // Size 0x2C

extern SsCamera D_8010D1D4_spotlight_swim[1];
extern const s16 D_8010D2E0_spotlight_swim[];

extern s16 D_8010CCF4_spotlight_swim[];
extern s16 D_8010D3B0_spotlight_swim[];
/* Views of D_8010D480_spotlight_swim[1].unk04 / .unk06 (retail addresses them as their own symbols). */
extern s16 D_8010D508_spotlight_swim;
extern s16 D_8010D50A_spotlight_swim;
/* Views of D_8010D480_spotlight_swim[2].pos.x / .pos.z. */
extern f32 D_8010D5CC_spotlight_swim;
extern f32 D_8010D5D4_spotlight_swim;
extern f32 D_8010D338_spotlight_swim[2];
extern s8 D_8010D343_spotlight_swim;
extern omObjData *D_8010D348_spotlight_swim;

extern s16 D_800D418E_main; /* the viewport being drawn */
void func_80088850_main(Mtx *m, f32 x, f32 y, f32 z);

extern f32 D_8010D380_spotlight_swim[3];
extern f32 D_8010D38C_spotlight_swim[3];
extern s8 D_8010D398_spotlight_swim[3];
extern s8 D_8010D39B_spotlight_swim[3];
extern s8 D_8010D32C_spotlight_swim;
extern s8 D_8010EE48_spotlight_swim;
extern s8 D_8010CD50_spotlight_swim[][9];

extern s8 D_8010D367_spotlight_swim;
extern s8 D_8010D2F4_spotlight_swim;
extern s8 D_8010D478_spotlight_swim;
extern s32 D_8010CCD4_spotlight_swim[];

/* The player's two splash rings (D_8010D350_spotlight_swim). */
typedef struct SsSplash {
    /* 0x00 */ s8 state;
    /* 0x01 */ s8 cnt;
    /* 0x02 */ u8 alpha[2];
    /* 0x04 */ f32 x[2];
    /* 0x0C */ f32 z[2];
} SsSplash; // Size 0x14

extern SsSplash D_8010D350_spotlight_swim;
void func_8001F9E4_main(s16 model, u8 alpha);

/* Views of D_8010D480_spotlight_swim[2] (.unk04, .unk06), and the entry itself. */
extern SsEnt D_8010D588_spotlight_swim;
extern s16 D_8010D58C_spotlight_swim;
extern s16 D_8010D58E_spotlight_swim;
/* D_8010D329_spotlight_swim: edge flags; .mode is D_8010D32C_spotlight_swim (two views of one block). */
typedef struct SsFlags {
    /* 0x00 */ s8 edge;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ s8 mode;
} SsFlags;
extern SsFlags D_8010D329_spotlight_swim;
extern s8 D_8010CD98_spotlight_swim[][2];
extern f32 D_8010D450_spotlight_swim[5][2];

extern f32 D_8010D334_spotlight_swim[1];
extern f32 D_8010D344_spotlight_swim;
extern f32 D_8010D370_spotlight_swim[2];
extern s8 D_8010D3CC_spotlight_swim;

/* This overlay's functions */
void func_80106148_spotlight_swim(omObjData *obj);
s8 func_80105DC8_spotlight_swim(omObjData *obj);
void func_80106808_spotlight_swim(omObjData *obj);
void func_801069BC_spotlight_swim(omObjData *obj);
void func_801072C4_spotlight_swim(omObjData *obj);
s8 func_80107674_spotlight_swim(omObjData *obj);
s8 func_80107710_spotlight_swim(omObjData *obj);
void func_801061DC_spotlight_swim(omObjData *obj);
void func_8010CB78_spotlight_swim(void);
void func_80106150_spotlight_swim(omObjData *obj);
void func_80106350_spotlight_swim(omObjData *obj);
void func_801065C4_spotlight_swim(omObjData *obj);
void func_8010B828_spotlight_swim(omObjData *obj);
void func_8010C25C_spotlight_swim(omObjData *obj);
void func_8010C900_spotlight_swim(omObjData *obj);

void func_801059A0_spotlight_swim(void) {
    func_8010CB78_spotlight_swim();
}

f32 func_801059BC_spotlight_swim(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_spotlight_swim(void) {
    SsEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010D480_spotlight_swim; i < 50; i++, ent++) {
        ent->obj = NULL;
        ent->unk04 = 0;
        ent->unk06 = 0;
        ent->unk08 = 0;
        ent->unk0A = 0;
        ent->unk0C = 0;
        ent->unk0E = 0;
        ent->unk10 = 0;
        ent->unk12 = 0;
        ent->unk14 = 0;
        ent->unk16 = 0;
        ent->unk18 = 0;
        ent->unk1C = 0;
        ent->unk20 = 0;
        ent->unk24 = 0;
        ent->unk28 = 0;
        ent->unk2C = 0;
        ent->unk30 = 0;
        ent->unk34 = 0;
        ent->unk38 = 0;
        ent->unk3C = 0;
        ent->grp = -1;
        ent->spr = -1;
        ent->pos.x = ent->pos.y = ent->pos.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->unk5C.x = ent->unk5C.y = ent->unk5C.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105B04_spotlight_swim(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105B7C_spotlight_swim(s16 se, s16 ch) {
    if (D_8010D3B0_spotlight_swim[ch] != -1) {
        HuAudFXStop(D_8010D3B0_spotlight_swim[ch]);
    }
    D_8010D3B0_spotlight_swim[ch] = func_8004AC98_main(D_8010CCF4_spotlight_swim[se], ch);
}

void func_80105C04_spotlight_swim(s16 se, s16 ch) {
    if (D_8010D3B0_spotlight_swim[ch] != -1) {
        HuAudFXStop(D_8010D3B0_spotlight_swim[ch]);
    }
    D_8010D3B0_spotlight_swim[ch] = func_8004ACE0_main(D_8010CCF4_spotlight_swim[se], ch);
}

s32 func_80105C8C_spotlight_swim(s32 max) {
    return rand8() % max;
}

void func_80105CE0_spotlight_swim(omObjData *obj, u16 motion, s16 arg2) {
    if (motion < 10) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], arg2, arg2);
    }
}

void func_80105D4C_spotlight_swim(omObjData *obj, u16 motion, s16 arg2, s16 arg3, s16 arg4) {
    if (motion < 10) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, arg2, arg3, arg4);
    }
}

s8 func_80105DC8_spotlight_swim(omObjData *obj) {
    s8 ret = 0;

    if (obj->rot.y != 0.0f) {
        if (obj->rot.y < 180.0f) {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, -7.0f);
            if (obj->rot.y > 350.0f) {
                obj->rot.y = 0.0f;
            }
        } else {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, 7.0f);
            if (obj->rot.y < 10.0f) {
                obj->rot.y = 0.0f;
            }
        }
        ret = 1;
    }
    return ret;
}

/* Projects (x, y, z) through camera cam into screen coordinates out[0], out[1]. */
void func_80105E9C_spotlight_swim(s16 cam, f32 x, f32 y, f32 z, f32 *out) {
    Mtx mtx;
    HuCamera *c;
    Mtx *look;
    Mtx *m;
    HuCamera *vp;
    f32 sx, sy, sz;
    f64 sn;
    f32 t;
    f32 dist;

    c = &gCameraList[cam];
    look = &c->mtxs[D_800D418E_main].lookAtMtx;
    m = &mtx;
    func_80088850_main(m, x, y, z);
    guMtxCatL(m, look, m);
    sx = (s32)((((u16 *)&mtx)[12] << 16) | ((u16 *)&mtx)[28]) >> 16;
    sy = (s32)((((u16 *)&mtx)[13] << 16) | ((u16 *)&mtx)[29]) >> 16;
    sz = (s32)((((u16 *)&mtx)[14] << 16) | ((u16 *)&mtx)[30]) >> 16;
    sn = sind(gCameraList[cam].fov[0] / 2.0);
    t = sz * sn / cosdf(gCameraList[cam].fov[0] / 2.0);
    dist = (t >= 0.0f) ? t : 0.0f - t;
    if (dist != 0.0) {
        vp = (HuCamera *)((u8 *)c + D_800D418E_main * 16);
        out[0] = (s16)(vp->viewports[0].vp.vscale[0] / 4.0 * sx / dist / 1.3333333730697632) + vp->viewports[0].vp.vtrans[0] / 4.0;
        out[1] = (s16)(vp->viewports[0].vp.vscale[1] / 4.0 * -sy / dist) + vp->viewports[0].vp.vtrans[1] / 4.0;
    }
}

void func_80106148_spotlight_swim(omObjData *obj) {
}

void func_80106150_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240000, 0x299);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80106148_spotlight_swim;
}

void func_801061A0_spotlight_swim(void) {
    D_8010D480_spotlight_swim[0].obj = omAddObj(500, 1, 0, -1, func_80106150_spotlight_swim);
}

void func_801061DC_spotlight_swim(omObjData *obj) {
    SsEnt *ent = &D_8010D480_spotlight_swim[1];

    if (++D_8010D50A_spotlight_swim >= 30) {
        D_8010D508_spotlight_swim++;
        D_8010D50A_spotlight_swim = 0;
    }
    switch (ent->unk04 & 1) {
    case 0:
        obj->trans.y += 0.5f;
        obj->trans.z -= 0.5f;
        if (D_8010D343_spotlight_swim != 7) {
            D_8010D338_spotlight_swim[0] += 0.5f;
            D_8010D348_spotlight_swim->trans.z -= 0.5f;
        }
        break;
    case 1:
        obj->trans.y -= 0.5f;
        obj->trans.z += 0.5f;
        if (D_8010D343_spotlight_swim != 7) {
            D_8010D338_spotlight_swim[0] -= 0.5f;
            D_8010D348_spotlight_swim->trans.z += 0.5f;
        }
        break;
    }
    obj->trans.x -= 4.0f;
    if (obj->trans.x == -254.0f) {
        obj->trans.x = 250.0f;
    }
}

void func_80106350_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240001, 0xA9);
    obj->trans.x = 250.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -50.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, -50.0f);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_801061DC_spotlight_swim;
}

void func_801063E4_spotlight_swim(void) {
    D_8010D480_spotlight_swim[1].obj = omAddObj(600, 1, 0, -1, func_80106350_spotlight_swim);
}

void func_80106420_spotlight_swim(omObjData *obj) {
    f32 *z;
    s8 i;

    for (i = 0; i < 3; i++) {
        switch (D_8010D39B_spotlight_swim[i]) {
        case 1:
            if (++D_8010D398_spotlight_swim[i] >= i * 7) {
                D_8010D39B_spotlight_swim[i] = 2;
                D_8010D398_spotlight_swim[i] = 0;
            }
            break;
        case 2:
            if (++D_8010D398_spotlight_swim[i] >= 10) {
                D_8010D398_spotlight_swim[i] = 0;
                D_8010D39B_spotlight_swim[i] = 0;
                D_8010D380_spotlight_swim[i] = 1000.0f;
            }
            z = D_8010D38C_spotlight_swim;
            Hu3DModelPosSet(obj->model[i + 1], D_8010D380_spotlight_swim[i], -200.0f, z[i]);
            break;
        case 0:
            break;
        }
    }
}

void func_801065C4_spotlight_swim(omObjData *obj) {
    void *data;
    f32 *px;
    f32 *pz;
    s8 i;

    data = DataRead(0x24000F);
    for (i = 0; i < 3; i++) {
        obj->model[i + 1] = func_8000B108_main(0x24000E, 0x289);
        HmfAnimCreate(HmfModelData[obj->model[i + 1]].hmf, data, 0, "s203_004_DEF");
        func_8001C448_main(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_8001C8A8_main(obj->model[i + 1], 1);
        px = D_8010D380_spotlight_swim;
        pz = D_8010D38C_spotlight_swim;
        px[i] = 1000.0f;
        pz[i] = 0.0f;
        Hu3DModelPosSet(obj->model[i + 1], px[i], -200.0f, pz[i]);
        D_8010D398_spotlight_swim[i] = 0;
        D_8010D39B_spotlight_swim[i] = 0;
    }
    DataClose(data);
    obj->func = func_80106420_spotlight_swim;
}

void func_80106754_spotlight_swim(void) {
    D_8010D480_spotlight_swim[16].obj = omAddObj(1200, 5, 3, -1, func_801065C4_spotlight_swim);
}

void func_80106790_spotlight_swim(omObjData *obj) {
    if (obj->work[2] == 0 && D_8010D343_spotlight_swim == 1) {
        func_80105C04_spotlight_swim(3, (s16)obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 10;
}

#ifdef NON_MATCHING
/* one extra nop after the sindf call (scheduling only) */
void func_80106808_spotlight_swim(omObjData *obj) {
    SsEnt *ent = &D_8010D480_spotlight_swim[2];
    f32 angle;

    func_8001C6A8_main(obj->model[5], 0.0f);
    if (obj->work[1] != 5) {
        D_8010D5CC_spotlight_swim = obj->trans.x;
        D_8010D5D4_spotlight_swim = obj->trans.z + 35.0f;
    } else {
        angle = func_801059BC_spotlight_swim(obj->rot.y, -90.0f);
        ent->pos.x = obj->trans.x - cosdf(angle) * 50.0f;
        ent->pos.z = sindf(angle) * 50.0f + obj->trans.z + 60.0f;
    }
    ent->pos.y = obj->trans.y - D_8010CD50_spotlight_swim[obj->work[1]][D_8010D343_spotlight_swim] - 25.0f;
    if (D_8010D32C_spotlight_swim == 2 || D_8010EE48_spotlight_swim == 5) {
        Hu3DModelScaleSet(obj->model[5], 0.6f, 0.5f, 1.0f);
    } else {
        Hu3DModelScaleSet(obj->model[5], 0.8f, 0.6f, 1.0f);
    }
    Hu3DModelPosSet(obj->model[5], ent->pos.x, -200.0f, ent->pos.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106808_spotlight_swim);
#endif

void func_801069BC_spotlight_swim(omObjData *obj) {
    s32 pad;
    s32 x;
    s32 y;

    if (D_8010D32C_spotlight_swim == 2) {
        if (D_8010D343_spotlight_swim != 2 && D_8010D343_spotlight_swim != 3) {
            func_8001C92C_main(obj->model[0], -1.0f);
            D_8010D343_spotlight_swim = 2;
            D_8010D367_spotlight_swim = 0;
        }
        if (D_8010D343_spotlight_swim != 3) {
            if (++D_8010D367_spotlight_swim >= 10) {
                func_80105D4C_spotlight_swim(obj, 3, 0, 1, 2);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C92C_main(obj->model[0], 2.0f);
                D_8010D343_spotlight_swim = 3;
            }
        }
    } else if (D_8010D32C_spotlight_swim == 1) {
        if (D_8010D343_spotlight_swim != D_8010D32C_spotlight_swim) {
            func_80105D4C_spotlight_swim(obj, 1, 0, 5, 0);
            func_8001C92C_main(obj->model[0], 1.0f);
            D_8010D343_spotlight_swim = 1;
        }
    } else {
        pad = obj->work[3];
        x = D_800CBB6E_main[pad];
        if (x < 0) {
            x = -x;
        }
        if (x < 5) {
            y = D_800D20A1_main[pad];
            if (y < 0) {
                y = -y;
            }
            if (y < 5) {
                if (D_8010D343_spotlight_swim != 4) {
                    func_80105D4C_spotlight_swim(obj, 4, 0, 10, 2);
                    func_8001C92C_main(obj->model[0], 1.0f);
                    D_8010D343_spotlight_swim = 4;
                }
                return;
            }
        }
        if (D_8010D343_spotlight_swim != 0) {
            func_80105D4C_spotlight_swim(obj, 0, 0, 10, 2);
            func_8001C92C_main(obj->model[0], 2.0f);
            D_8010D343_spotlight_swim = 0;
        }
    }
}

void func_80106BC8_spotlight_swim(omObjData *obj) {
    if (D_8010D2F4_spotlight_swim == 7) {
        if (D_8010D343_spotlight_swim != 5) {
            func_80105D4C_spotlight_swim(obj, 5, 0, 15, 2);
            func_8001C92C_main(obj->model[0], 1.0f);
            D_8010D343_spotlight_swim = 5;
            if (obj->trans.x <= -440.0f) {
                obj->trans.x += 25.0f;
            }
            if (obj->trans.x >= 440.0f) {
                obj->trans.x -= 20.0f;
            }
            if (obj->trans.z <= -440.0f) {
                obj->trans.z += 50.0f;
            }
        }
        func_80105DC8_spotlight_swim(obj);
        return;
    }
    if (D_8010EE48_spotlight_swim >= 3) {
        if (D_8010D343_spotlight_swim < 5) {
            func_80105D4C_spotlight_swim(obj, 6, 0, 15, 1);
            func_8001C92C_main(obj->model[0], 1.0f);
            D_8010D343_spotlight_swim = 8;
            if (obj->trans.x <= -440.0f) {
                obj->trans.x += 25.0f;
            }
            if (obj->trans.x >= 440.0f) {
                obj->trans.x -= 20.0f;
            }
            if (obj->trans.z <= -440.0f) {
                obj->trans.z += 50.0f;
            }
            if (D_8010D32C_spotlight_swim == 1) {
                D_8010D478_spotlight_swim = 1;
                func_80106808_spotlight_swim(obj);
            }
        }
        if ((D_8010D343_spotlight_swim != 8 || func_80105DC8_spotlight_swim(obj) == 0) &&
            D_8010EE48_spotlight_swim == 5 && D_8010D343_spotlight_swim != 6) {
            func_80105CE0_spotlight_swim(obj, 6, 0);
            func_80045ED0_main((D_8010CCD4_spotlight_swim[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
            func_8001C92C_main(obj->model[0], 1.0f);
            D_8010D343_spotlight_swim = 6;
        }
    }
}

/* The two splash rings (models 6 and 7) behind the player. */
void func_80106EB0_spotlight_swim(omObjData *obj) {
    f32 y;

    switch (D_8010D350_spotlight_swim.state) {
    case 0:
        if (D_8010D478_spotlight_swim != 0) {
            D_8010D350_spotlight_swim.cnt = 0;
            D_8010D350_spotlight_swim.state = 1;
            D_8010D478_spotlight_swim = 0;
        }
        break;
    case 1:
        if (D_8010D350_spotlight_swim.cnt == 0) {
            func_8001C6A8_main(obj->model[6], 0.0f);
            func_8001C258_main(obj->model[6], 4, 0);
            if (obj->work[1] != 5) {
                D_8010D350_spotlight_swim.x[0] = obj->trans.x;
                D_8010D350_spotlight_swim.z[0] = obj->trans.z;
            } else {
                D_8010D350_spotlight_swim.x[0] = obj->trans.x - sindf(obj->rot.y) * 50.0f;
                D_8010D350_spotlight_swim.z[0] = obj->trans.z - cosdf(obj->rot.y) * 50.0f;
            }
            D_8010D350_spotlight_swim.alpha[0] = 255;
            func_8001F9E4_main(obj->model[6], 255);
        } else if (D_8010D350_spotlight_swim.cnt >= 5) {
            if (D_8010D350_spotlight_swim.alpha[0] >= 36) {
                D_8010D350_spotlight_swim.alpha[0] -= 20;
            } else {
                func_8001C258_main(obj->model[6], 4, 4);
                D_8010D350_spotlight_swim.alpha[0] = 0;
            }
            func_8001F9E4_main(obj->model[6], D_8010D350_spotlight_swim.alpha[0]);
        }
        if (D_8010D350_spotlight_swim.cnt == 8) {
            func_8001C6A8_main(obj->model[7], 0.0f);
            func_8001C258_main(obj->model[7], 4, 0);
            if (obj->work[1] != 5) {
                D_8010D350_spotlight_swim.x[1] = obj->trans.x;
                D_8010D350_spotlight_swim.z[1] = obj->trans.z;
            } else {
                /* Retail writes the first ring's position here, not the second's. */
                D_8010D350_spotlight_swim.x[0] = obj->trans.x - sindf(obj->rot.y) * 50.0f;
                D_8010D350_spotlight_swim.z[0] = obj->trans.z - cosdf(obj->rot.y) * 50.0f;
            }
            D_8010D350_spotlight_swim.alpha[1] = 255;
            func_8001F9E4_main(obj->model[7], 255);
        } else if (D_8010D350_spotlight_swim.cnt >= 10) {
            if (D_8010D350_spotlight_swim.alpha[1] >= 36) {
                D_8010D350_spotlight_swim.alpha[1] -= 20;
            } else {
                func_8001C258_main(obj->model[7], 4, 4);
                D_8010D350_spotlight_swim.alpha[1] = 0;
                D_8010D350_spotlight_swim.state = 0;
            }
            func_8001F9E4_main(obj->model[7], D_8010D350_spotlight_swim.alpha[1]);
        }
        D_8010D350_spotlight_swim.cnt++;
        break;
    }
    if (D_8010EE48_spotlight_swim == 3 && D_8010D32C_spotlight_swim != 1) {
        Hu3DModelScaleSet(obj->model[6], 2.5f, 2.5f, 2.5f);
        Hu3DModelScaleSet(obj->model[7], 2.5f, 2.5f, 2.5f);
    } else if (obj->work[1] != 5) {
        Hu3DModelScaleSet(obj->model[6], 1.5f, 1.5f, 1.5f);
        Hu3DModelScaleSet(obj->model[7], 1.5f, 1.5f, 1.5f);
    } else {
        Hu3DModelScaleSet(obj->model[6], 1.7f, 1.7f, 1.78f);
        Hu3DModelScaleSet(obj->model[7], 1.7f, 1.7f, 1.7f);
    }
    y = D_8010D338_spotlight_swim[0] + -200.0f + 3.0f;
    Hu3DModelPosSet(obj->model[6], D_8010D350_spotlight_swim.x[0], y, D_8010D350_spotlight_swim.z[0]);
    Hu3DModelPosSet(obj->model[7], D_8010D350_spotlight_swim.x[1], y, D_8010D350_spotlight_swim.z[1]);
}

#ifdef NON_MATCHING
/* retail reloads D_8010D58E_spotlight_swim for the model index after the z store; mine reuses it (regalloc follows) */
void func_801072C4_spotlight_swim(omObjData *obj) {
    SsEnt *ent = &D_8010D588_spotlight_swim;
    s32 edge;
    f32 angle;
    s8 kind;
    s8 i;

    if (D_8010D329_spotlight_swim.mode <= 0) {
        kind = obj->work[1];
        if (D_8010D343_spotlight_swim == 0) {
            if (D_8010D58C_spotlight_swim == 0) {
                D_8010D58E_spotlight_swim = (D_8010D58E_spotlight_swim + 1) & 3;
                edge = D_8010D329_spotlight_swim.edge != 0;
                angle = func_801059BC_spotlight_swim(obj->rot.y, -90.0f);
                D_8010D450_spotlight_swim[D_8010D58E_spotlight_swim + 1][0] =
                    obj->trans.x - D_8010CD98_spotlight_swim[kind][edge] * cosdf(angle);
                D_8010D450_spotlight_swim[D_8010D58E_spotlight_swim + 1][1] =
                    D_8010CD98_spotlight_swim[kind][edge] * sindf(angle) + obj->trans.z + 15.0f;
                func_8001C6A8_main(obj->model[D_8010D58E_spotlight_swim + 1], 0.0f);
                func_80105C04_spotlight_swim(1, (s16)obj->work[0]);
            }
            ent->unk04 = (ent->unk04 + 1) % 6;
        }
        for (i = 1; i < 5; i++) {
            Hu3DModelPosSet(obj->model[i], D_8010D450_spotlight_swim[i][0],
                            obj->trans.y - D_8010CD50_spotlight_swim[kind][D_8010D343_spotlight_swim] - 25.0f,
                            D_8010D450_spotlight_swim[i][1]);
            Hu3DModelScaleSet(obj->model[i], 0.3f, 0.5f, 0.5f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801072C4_spotlight_swim);
#endif

void func_8010755C_spotlight_swim(omObjData *obj) {
    f32 dx;
    f32 dz;
    s8 i;

    for (i = 0; i < 3; i++) {
        dx = func_80105C8C_spotlight_swim(30) + 15;
        if (func_80105C8C_spotlight_swim(2) != 0) {
            dx = 0.0f - dx;
        }
        dz = func_80105C8C_spotlight_swim(30) + 15;
        if (func_80105C8C_spotlight_swim(2) != 0) {
            dz = 0.0f - dz;
        }
        D_8010D380_spotlight_swim[i] = dx + obj->trans.x;
        D_8010D38C_spotlight_swim[i] = dz + obj->trans.z;
        D_8010D39B_spotlight_swim[i] = 1;
    }
}

s8 func_80107674_spotlight_swim(omObjData *obj) {
    if ((D_800CBB6E_main[obj->work[3]] < 3 && obj->trans.x <= -450.0f) ||
        (D_800CBB6E_main[obj->work[3]] >= 4 && obj->trans.x >= 450.0f)) {
        D_8010D329_spotlight_swim.edge |= 1;
        return 0;
    }
    return 1;
}

s8 func_80107710_spotlight_swim(omObjData *obj) {
    if ((D_800D20A1_main[obj->work[3]] >= 4 && obj->trans.z <= -450.0f) ||
        (D_800D20A1_main[obj->work[3]] < 3 && obj->trans.z >= 260.0f)) {
        D_8010D329_spotlight_swim.edge |= 2;
        return 0;
    }
    return 1;
}

/* Converts the heading (rot.y) into stick values for the player's pad. */
void func_801077AC_spotlight_swim(omObjData *obj) {
    s16 pad = obj->work[3];
    f32 angle = obj->rot.y;
    s16 quad = 0;

    if (angle >= 90.0f) {
        quad = 1;
    }
    if (angle >= 180.0f) {
        quad++;
    }
    if (angle >= 270.0f) {
        quad++;
    }
    switch (quad) {
    case 0:
        D_800CBB6E_main[pad] = angle * D_8010D334_spotlight_swim[0];
        D_800D20A1_main[pad] = 0.0f - (90.0f - angle) * D_8010D334_spotlight_swim[0];
        break;
    case 1:
        angle -= 90.0f;
        D_800CBB6E_main[pad] = (90.0f - angle) * D_8010D334_spotlight_swim[0];
        D_800D20A1_main[pad] = angle * D_8010D334_spotlight_swim[0];
        break;
    case 2:
        angle -= 180.0f;
        D_800CBB6E_main[pad] = 0.0f - angle * D_8010D334_spotlight_swim[0];
        D_800D20A1_main[pad] = (90.0f - angle) * D_8010D334_spotlight_swim[0];
        break;
    case 3:
        angle -= 270.0f;
        D_800CBB6E_main[pad] = 0.0f - (90.0f - angle) * D_8010D334_spotlight_swim[0];
        D_800D20A1_main[pad] = 0.0f - angle * D_8010D334_spotlight_swim[0];
        break;
    }
}

void func_801079FC_spotlight_swim(omObjData *obj) {
    s8 x;
    s8 y;

    x = D_800CBB6E_main[obj->work[3]];
    if (x >= 64) {
        x = 63;
    } else if (x < -63) {
        x = -63;
    }
    y = -D_800D20A1_main[obj->work[3]];
    if (y >= 64) {
        y = 63;
    } else if (y < -63) {
        y = -63;
    }
    D_8010D329_spotlight_swim.edge = 0;
    if (func_80107674_spotlight_swim(obj)) {
        obj->trans.x = x / D_8010D344_spotlight_swim + obj->trans.x;
    }
    if (func_80107710_spotlight_swim(obj)) {
        obj->trans.z = y / D_8010D344_spotlight_swim + obj->trans.z;
    }
    if (D_8010D3CC_spotlight_swim != 0) {
        if (((x < 0) ? -x : x) >= 5 || ((y < 0) ? -y : y) >= 5) {
            obj->rot.y = func_801059BC_spotlight_swim(atan2df(x, y), 0.0f);
        }
    }
    func_80105E9C_spotlight_swim(0, obj->trans.x, obj->trans.y + 50.0f, obj->trans.z, D_8010D370_spotlight_swim);
    func_801072C4_spotlight_swim(obj);
    func_801069BC_spotlight_swim(obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107C10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010846C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010881C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80108AD8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109088_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109194_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010932C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109468_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109558_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109690_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801098A8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109A94_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109C1C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109E08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109F60_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A328_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A670_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A7AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AAB8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010ADF8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AE9C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010B828_spotlight_swim);

void func_8010BA30_spotlight_swim(void) {
    D_8010D480_spotlight_swim[13].obj = omAddObj(1300, 5, 5, -1, func_8010B828_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BA6C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BD10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BD5C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BDE0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BFD0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C094_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C25C_spotlight_swim);

void func_8010C444_spotlight_swim(void) {
    omObjData *obj = omAddObj(1100, 1, 0, -1, func_8010C25C_spotlight_swim);

    obj->work[0] = 0;
    D_8010D480_spotlight_swim[12].obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C484_spotlight_swim);

void func_8010C52C_spotlight_swim(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C550_spotlight_swim(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C52C_spotlight_swim;
    }
}

void func_8010C588_spotlight_swim(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C550_spotlight_swim;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C5E0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C900_spotlight_swim);

void func_8010CA00_spotlight_swim(void) {
}

void func_8010CA08_spotlight_swim(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010D1D4_spotlight_swim[i].scissor[0], D_8010D1D4_spotlight_swim[i].scissor[1],
                   D_8010D1D4_spotlight_swim[i].scissor[2], D_8010D1D4_spotlight_swim[i].scissor[3]);
        ViewportSet(i, D_8010D1D4_spotlight_swim[i].viewport[0], D_8010D1D4_spotlight_swim[i].viewport[1],
                    D_8010D1D4_spotlight_swim[i].viewport[2], D_8010D1D4_spotlight_swim[i].viewport[3],
                    D_8010D1D4_spotlight_swim[i].viewport[4], D_8010D1D4_spotlight_swim[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010D1D4_spotlight_swim[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010CB78_spotlight_swim(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010CA08_spotlight_swim();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010D2E0_spotlight_swim, 0);
    func_80045010_main(D_8010D2E0_spotlight_swim, 1);
    omAddObj(1500, 0, 0, -1, func_8010C900_spotlight_swim);
    omAddObj(1500, 0, 0, -1, func_8010C588_spotlight_swim);
    func_80105A3C_spotlight_swim();
}

/* Shift-JIS fullwidth "ABC", passed to func_80045010_main. */
const s16 D_8010D2E0_spotlight_swim[] = { 0x8260, 0x8261, 0x8262, 0 };
