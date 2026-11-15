#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/data.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "mallocblock.h"

// eatsa A: Eatsa Pizza (two teams of two eat a pizza from opposite halves of the screen)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* MgWork::unk158 of a player: screen-space state (2D, origin at the screen centre). */
typedef struct EpPlayer {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 prevX;
    /* 0x10 */ f32 prevY;
    /* 0x14 */ f32 heading;
    /* 0x18 */ f32 cpuHeading; /* CPU: heading it steers to */
    /* 0x1C */ f32 radius;
    /* 0x20 */ s16 cellX; /* pizza slice cell under the player (32x32 px) */
    /* 0x22 */ s16 cellY;
    /* 0x24 */ s16 tgtX; /* CPU: target cell */
    /* 0x26 */ s16 tgtY;
    /* 0x28 */ u16 timer; /* CPU: frames to the next decision */
    /* 0x2A */ s16 pushed; /* frames pushed by another player */
    /* 0x2C */ s32 model; /* model file */
    /* 0x30 */ u8 player;
    /* 0x31 */ u8 difficulty;
    /* 0x32 */ u8 side; /* team: 0 left half, 1 right half */
    /* 0x33 */ u8 slot; /* index in the team */
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 cpu;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
} EpPlayer; /* size 0x38 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);
f64 fabs(f64);
f32 sqrtf(f32);

extern s32 D_800A178C_main[][6];

u8 rand8(void);

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y); /* stick: x << 16 | y */
s32 func_800E4A90_minigame(omObjData* obj);

extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105AF4_eatsa_pizza(omObjData* obj);
void func_80105BE4_eatsa_pizza(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105C64_eatsa_pizza(f32 (*src)[4], f32 (*dst)[4]);
void func_80105FF0_eatsa_pizza(void);
void func_80106084_eatsa_pizza(omObjData* obj);
void func_80106504_eatsa_pizza(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4);
void func_8010679C_eatsa_pizza(omObjData* obj);
u16 func_801070E8_eatsa_pizza(omObjData* obj);
void func_801078C4_eatsa_pizza(omObjData* obj);
void func_80107A64_eatsa_pizza(omObjData* obj);
s16 func_80107E6C_eatsa_pizza(omObjData* obj);
void func_801083A8_eatsa_pizza(omObjData* obj, MgWork** work, EpPlayer** ep);
void func_801083BC_eatsa_pizza(void);
void func_80108470_eatsa_pizza(omObjData* obj);
void func_801084F8_eatsa_pizza(omObjData* obj);
void func_801087DC_eatsa_pizza(omObjData* obj);
void func_80108C50_eatsa_pizza(omObjData* obj);
s16 func_80108E48_eatsa_pizza(u16 color, EpPlayer* ep);
u32 func_80108F4C_eatsa_pizza(void);
s16 func_80108FA4_eatsa_pizza(s32 file);
s16 func_80108FEC_eatsa_pizza(s16 tex, s16 n);
void* func_801090B4_eatsa_pizza(s16 tex, s16 frame);

extern u8 D_80109100_eatsa_pizza[4][2]; /* [n][1]: the n-th player to spawn */
extern u8 D_80109108_eatsa_pizza; /* players spawned */
extern u8 D_8010910C_eatsa_pizza[4]; /* players spawned per team */
extern s16 D_80109110_eatsa_pizza[4][3]; /* start positions [team * 2 + slot] */
extern f32 D_80109128_eatsa_pizza[4]; /* start headings [team * 2 + slot] */
extern s32 D_80109138_eatsa_pizza; /* message / wipe timer */
extern s16 D_8010913A_eatsa_pizza[]; /* [0]: the low half of D_80109138 (big-endian), read as the wipe-out speed */
extern u16 D_8010913C_eatsa_pizza; /* game timer, frames */
extern s32 D_80109140_eatsa_pizza; /* winning team, -1 none */
extern s16 D_80109144_eatsa_pizza; /* frames since the wipe-in finished */
extern u32 D_80109148_eatsa_pizza; /* random seed */
extern s32 D_80109260_eatsa_pizza[2]; /* per team: slice pixels at the start */
extern s16 D_80109278_eatsa_pizza; /* pizza texture */
extern s16 D_8010927A_eatsa_pizza[2]; /* per team: its pizza's remaining-slice texture */
extern s16 D_8010927E_eatsa_pizza[2]; /* per team: its pizza's mask texture */
extern s16 D_80109282_eatsa_pizza[2]; /* textures: [0] bite shape, [1] bite mark (D_80109284) */
extern s16 D_801092B8_eatsa_pizza[2]; /* per team: slice pixels left */
extern s16 D_801092C0_eatsa_pizza[2][5][7]; /* per team: slice pixels left per 32x32 cell [x][y] */ /* bite mark texture */
extern s16 D_80109288_eatsa_pizza[]; /* [0]: pizza sprite group */
extern s16 D_8010928A_eatsa_pizza[3]; /* sprite groups: [team] its pizza, [2] the bite marks (D_8010928E) */ /* bite mark sprite group */
extern s16 D_80109298_eatsa_pizza[16]; /* bite mark members in use */
extern u16 D_8010934C_eatsa_pizza[2]; /* per team: thin mask pixels (unused) */
extern s16 D_80109350_eatsa_pizza; /* game state */
extern EpPlayer* D_80109268_eatsa_pizza[2][2]; /* [team][slot] */

extern f32 D_80109358_eatsa_pizza[4][4]; /* world to view (D_80109390 is its [3][2]) */
extern f32 D_80109390_eatsa_pizza; /* D_80109358[3][2]: the view depth offset */
extern f32 D_80109398_eatsa_pizza[4][4]; /* view to world */
extern f32 D_801093D8_eatsa_pizza; /* tan(fov / 2) */

void func_801059A0_eatsa_pizza(void) {
    omObjData* obj;
    u8 cam;

    Hu3DAnimInit(1);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x10, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 5.0f, 80.0f, 4000.0f);
    func_800E1804_minigame();
    func_80105AF4_eatsa_pizza(obj);
    func_801083BC_eatsa_pizza();
    func_80105FF0_eatsa_pizza();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105AF4_eatsa_pizza(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 2000.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_801093D8_eatsa_pizza = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_80109358_eatsa_pizza, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_80109398_eatsa_pizza, &cam->mtxs[0].lookAtMtx);
    func_80105C64_eatsa_pizza(D_80109398_eatsa_pizza, D_80109398_eatsa_pizza);
}

/* out = (x, y, z) * the 3x3 part of m */
void func_80105BE4_eatsa_pizza(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

/* dst = inverse of the affine matrix src */
void func_80105C64_eatsa_pizza(f32 (*src)[4], f32 (*dst)[4]) {
    f32 m[4][4];
    f32 c0;
    f32 c1;
    f32 c2;
    f32 det;

    func_8002367C_main(m, src);
    c0 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    c1 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
    c2 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
    det = c0 * m[0][0] + c1 * m[0][1] + c2 * m[0][2];
    if (det != 0.0f) {
        det = 1.0f / det;
        dst[0][0] = c0 * det;
        dst[1][0] = c1 * det;
        dst[2][0] = c2 * det;
        dst[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * det;
        dst[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det;
        dst[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * det;
        dst[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * det;
        dst[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * det;
        dst[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * det;
        dst[0][3] = dst[1][3] = dst[2][3] = 0.0f;
        dst[3][3] = 1.0f;
        func_80105BE4_eatsa_pizza(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

/* world position -> screen position (origin at the centre) */
void func_80105E54_eatsa_pizza(Vec* pos, f32* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_80109358_eatsa_pizza, m);
    t = m[3][2] * D_801093D8_eatsa_pizza;
    w = fabsf(t);
    if (w != 0.0) {
        out[0] = m[3][0] * 160.0f / w / 1.3333334f;
        out[1] = -m[3][1] * 120.0f / w;
    }
}

/* screen position at depth z -> world position */
void func_80105F24_eatsa_pizza(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_80109390_eatsa_pizza;
    w = fabsf(d * D_801093D8_eatsa_pizza);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_80109398_eatsa_pizza, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

void func_80105FF0_eatsa_pizza(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 11, 50, -1, func_80106084_eatsa_pizza);
    }
}

void func_80106084_eatsa_pizza(omObjData* obj) {
    u8 player;
    u8 group;
    s8 chr;
    s32 file0;
    s32 file1;
    MgWork* work;
    EpPlayer* ep;

    player = D_80109100_eatsa_pizza[D_80109108_eatsa_pizza][1];
    group = GwPlayer[player].group;
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_80106504_eatsa_pizza(obj, file0, file1, player, 0x2D9);
    work = obj->data;
    obj->trans.x = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][0];
    obj->trans.y = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][1];
    obj->trans.z = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][2];
    obj->rot.x = 90.0f;
    obj->rot.z = D_80109128_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]];
    work->unk3C = obj->rot.z + 180.0;
    obj->scale.x = obj->scale.y = obj->scale.z = work->unkAC * 0.15;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    ep = work->unk158;
    ep->player = player;
    ep->side = group;
    ep->slot = D_8010910C_eatsa_pizza[group];
    ep->cpuHeading = ep->heading = work->unk3C;
    ep->cpu = GwPlayer[player].stat & 1;
    ep->difficulty = GwPlayer[player].cpu_difficulty;
    ep->model = file0 | 0x4E;
    ep->unk34 = 0;
    ep->unk36 = 0;
    ep->radius = 11.0f;
    ep->x = obj->trans.x;
    ep->y = obj->trans.y;
    ep->z = obj->trans.z;
    ep->tgtX = ep->tgtY = -1;
    ep->timer = 8;
    ep->pushed = 0;
    D_80109268_eatsa_pizza[group][D_8010910C_eatsa_pizza[group]] = ep;
    obj->model[3] = func_8000B108_main(3, 0x2DD);
    obj->model[4] = func_8000B108_main(4, 0x2DD);
    obj->model[6] = func_8000B108_main(5, 0x2DD);
    obj->model[5] = func_8000B108_main(6, 0x2DD);
    obj->model[7] = func_8000B108_main(8, 0x2DD);
    obj->model[8] = func_8000B108_main(7, 0x2DD);
    obj->func = func_8010679C_eatsa_pizza;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 16, func_80017BB8_main(chr, 0x3E), 1, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x4E), 2, 120);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x3A), 2, 60);
    func_800E5690_minigame(obj, 0);
    D_80109108_eatsa_pizza++;
    D_8010910C_eatsa_pizza[group]++;
}

/* A player's actor work: the framework's func_800E1BA8_minigame cut down, plus the EpPlayer block. */
void func_80106504_eatsa_pizza(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4) {
    MgWork* work;
    s32 i;

    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = HuMemAllocTag(sizeof(MgWork), 0x7918);
    memset(obj->data, 0, sizeof(MgWork));
    work = obj->data;
    work->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 0x7918);
    memset(work->unkE8, 0, obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData));
    work->unk158 = HuMemAllocTag(sizeof(EpPlayer), 0x7918);
    memset(work->unk158, 0, sizeof(EpPlayer));
    obj->model[0] = func_8000B108_main(file0 | file1, arg4);
    for (i = 0; i < obj->mtncnt; i++) {
        obj->motion[i] = -1;
    }
    for (i = 0; i < obj->mtncnt; i++) {
        func_800E1BA8_minigame_UnkE8_ObjData* mtn = work->unkE8;
        mtn[i].unk02 = 0;
        mtn[i].unk00 = 0;
    }
    work->unk57 = GwPlayer[(u16)player].pad;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unkA0 = work->unk9C = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unk3C = atan2df(-obj->trans.x, -obj->trans.z);
    func_800E1328_minigame(obj, 60.0f);
    func_800E1334_minigame(obj, 150.0f);
    func_800E1340_minigame(obj, 20.0f);
    func_800E12EC_minigame(obj, 1000.0f);
    switch (file0 >> 16) {
        case 6:
            work->unkAC = 0.8f;
            break;
        case 5:
            work->unkAC = 0.9f;
            break;
        case 4:
        default:
            work->unkAC = 1.0f;
            break;
    }
}

/* A player's per-frame function. */
void func_8010679C_eatsa_pizza(omObjData* obj) {
    f32 pos[12];
    MgWork* work;
    EpPlayer* ep;
    u16 btn;
    u16 se;
    u16 state;
    s16 sx;
    s16 sy;
    u8 pad;
    f32 cur;
    f32 tgt;

    btn = 0;
    work = obj->data;
    ep = work->unk158;
    cur = work->unk3C;
    se = 0;
    state = func_800E4A90_minigame(obj);
    ep->cellX = (s16)(ep->x + 160.0f) >> 5;
    ep->cellY = ((s16)(ep->y + 120.0f) - 8) >> 5;
    if (ep->cellX >= 5) {
        ep->cellX -= 5;
    }
    switch (D_80109350_eatsa_pizza) {
        case 2:
            ep = work->unk158;
            pad = work->unk57;
            if (state == 2) {
                func_800E5690_minigame(obj, 0x10);
            }
            if (ep->cpu == 0) {
                s32 stick = func_800E2250_minigame(obj, D_800CBB6E_main[(s8)pad], D_800D20A1_main[(s8)pad]);
                sx = (u32)stick >> 16;
                sy = stick;
                btn = D_800D5558_main[(s8)pad];
                ep->tgtX = ep->cellX;
                ep->tgtY = ep->cellY;
            } else {
                btn = func_801070E8_eatsa_pizza(obj);
                sy = 0x30;
                sx = 0x30;
            }
            ep->prevX = ep->x;
            ep->prevY = ep->y;
            if (fabs(sx) < 16.0) {
                sx = 0;
            }
            if (fabs(sy) < 16.0) {
                sy = 0;
            }
            work->unk40 = sqrtf(sx * sx + sy * sy) / 6.0;
            if (work->unk40 > 16.0) {
                work->unk40 = 16.0f;
            }
            if (work->unk40 != 0.0) {
                if (state == 2) {
                    func_800E5690_minigame(obj, 0x10);
                }
                if (ep->cpu == 0) {
                    tgt = atan2df(sx, -sy) + 180.0;
                } else {
                    tgt = ep->cpuHeading;
                }
                if (tgt >= 360.0) {
                    tgt -= 360.0;
                }
                if (tgt != cur) {
                    if ((tgt - cur < -180.0f && tgt - cur < 0.0f) || (tgt - cur < 180.0f && tgt - cur > 0.0f)) {
                        cur += 20.0f;
                        if ((tgt - cur > -180.0f && tgt - cur < 0.0f) || (tgt - cur > 180.0f && tgt - cur > 0.0f)) {
                            cur = tgt;
                        }
                        if (cur > 360.0) {
                            cur -= 360.0;
                        }
                    } else {
                        cur -= 20.0f;
                        if ((tgt - cur < -180.0f && tgt - cur < 0.0f) || (tgt - cur < 180.0f && tgt - cur > 0.0f)) {
                            cur = tgt;
                        }
                        if (cur < 0.0) {
                            cur += 360.0;
                        }
                    }
                }
                work->unk3C = cur;
                ep->heading = cur;
                obj->rot.z = cur - 180.0;
                if (HmfModelData[obj->model[0]].unk40 == 0.0) {
                    se = 1;
                }
                ep->unk36 = 4;
                ep->x -= sindf(tgt) * work->unk40 * 0.1;
                ep->y -= cosdf(tgt) * work->unk40 * 0.1;
            }
            if (ep->unk37 != 0) {
                func_8001C92C_main(obj->model[0], 1.0f);
                ep->unk37--;
            } else {
                func_8001C92C_main(obj->model[0], work->unk40 * 0.075);
            }
            break;
        case 3:
        case 4:
            func_800E5690_minigame(obj, 0);
            func_8001C92C_main(obj->model[0], 1.0f);
            ep->unk36 = 2;
            break;
        case 5:
            if (ep->unk36 != 0) {
                if (ep->unk34 != 0) {
                    func_800E5690_minigame(obj, 0xD);
                    func_80045F1C_main(ep->model, ep->side * 40 + 0x2C, ep->player);
                    GwPlayer[work->unk59].bonusCoin += 10;
                } else {
                    func_800E5690_minigame(obj, 0xE);
                }
            }
            break;
        case 6:
            if (work != NULL) {
                HuMemFree(work->unkE8);
                HuMemFree(work->unk158);
                HuMemFree(work);
                obj->data = NULL;
                obj->func = NULL;
            }
            return;
        case 7:
            return;
        case 0:
        case 1:
            break;
    }
    if (btn & 0x8000) {
        u16 r = func_80107E6C_eatsa_pizza(obj);

        if (r != 0) {
            se = r;
        }
        if (ep->unk37 == 0) {
            ep->unk37 = 16;
        }
    }
    if (se == 1) {
        CharFXPlay(0x1F, GwPlayer[work->unk59].chr);
    } else if (se == 3) {
        CharFXPlay(0x350, GwPlayer[work->unk59].chr);
    } else if (se == 2) {
        CharFXPlay(0x347, GwPlayer[work->unk59].chr);
    }
    if (ep->unk36 != 0) {
        ep->unk36--;
        func_801078C4_eatsa_pizza(obj);
        func_80107A64_eatsa_pizza(obj);
    }
    if (ep->side == 0) {
        if (ep->x < -144.0f) {
            ep->x = -144.0f;
        }
        if (ep->x > -16.0f) {
            ep->x = -16.0f;
        }
    } else {
        if (ep->x < 16.0f) {
            ep->x = 16.0f;
        }
        if (ep->x > 144.0f) {
            ep->x = 144.0f;
        }
    }
    if (ep->y < -104.0f) {
        ep->y = -104.0f;
    }
    if (ep->y > 104.0f) {
        ep->y = 104.0f;
    }
    func_80105F24_eatsa_pizza(ep->x, ep->y, ep->z, pos);
    obj->trans.x = pos[0];
    obj->trans.y = pos[1];
    func_800E4E30_minigame(obj);
}

/* CPU player: returns the bite button (bit 15) and steers ep->cpuHeading at the nearest slice pixel of its
   target cell, or at the nearest non-empty cell around it (not the partner's). */
#ifdef NON_MATCHING
/* 536 of 533 instructions, masked ~100: register allocation and the heading wrap-around code; logic checked
   block by block against the asm */
u16 func_801070E8_eatsa_pizza(omObjData* obj) {
    MgWork* work;
    EpPlayer* ep;
    EpPlayer* mate;
    u16* slice;
    s16 cx;
    s16 cy;
    s16 fx;
    s16 fy;
    s16 ox;
    s16 oy;
    s16 ccx;
    s16 ccy;
    s16 xx;
    s16 yy;
    s16 found;
    s16 v;
    u16 btn;
    f32 best;
    f32 px;
    f32 py;
    f32 tx;
    f32 ty;
    f32 dx;
    f32 dy;
    f32 d;
    f32 h;
    s32 i;
    s32 j;
    s32 k;
    s32 a;
    s32 b;
    s32 n;

    found = 0;
    best = 65536.0f;
    func_801083A8_eatsa_pizza(obj, &work, &ep);
    btn = ((s32)func_80108F4C_eatsa_pizza() % (9 - ep->difficulty * 2) == 0) << 15;
    if (ep->pushed >= 4) {
        h = ep->cpuHeading + 60.0 - (func_80108F4C_eatsa_pizza() & 1) * 120;
        if (h > 360.0) {
            h -= 360.0;
        }
        if (h < 0.0) {
            h += 360.0;
        }
        ep->cpuHeading = h;
        ep->timer = (func_80108F4C_eatsa_pizza() & 7) + 5;
    }
    if (work->unk3C == ep->cpuHeading) {
        if (--ep->timer == 0) {
            if (ep->side != 0) {
                px = ep->x;
            } else {
                px = ep->x + 160.0f;
            }
            h = work->unk3C + (f32)((s32)func_80108F4C_eatsa_pizza() - 0x8000) * (1.0 / 32768.0) * 20.0;
            px = px - sindf(h) * 4.0;
            py = ep->y + 120.0f - cosdf(h) * 4.0;
            if (ep->tgtX == -1 || ep->tgtY == -1) {
                ep->tgtX = ep->cellX;
                ep->tgtY = ep->cellY;
            }
            cx = ep->tgtX;
            cy = ep->tgtY;
            if (D_801092C0_eatsa_pizza[ep->side][cx][cy] != 0) {
                /* tx, ty stay unset (retail) when the cell has no pixel left */
                slice = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[ep->side], 0);
                for (j = 0; j < 32; j++) {
                    yy = (cy << 5) + j + 8;
                    for (i = 0; i < 32; i++) {
                        xx = (cx << 5) + i;
                        if (slice[(u16)(xx + yy * 160)] & 1) {
                            dx = px - xx;
                            dy = py - yy;
                            d = sqrtf(dx * dx + dy * dy);
                            if (!(best < d)) {
                                best = d;
                                ep->timer = (func_80108F4C_eatsa_pizza() & 3) + 3;
                                tx = xx;
                                ty = yy;
                            }
                        }
                    }
                }
                dx = px - tx;
            } else {
                k = func_80108F4C_eatsa_pizza() & 1;
                for (;;) {
                    k++;
                    if (k >= 7) {
                        break;
                    }
                    mate = D_80109268_eatsa_pizza[ep->side][ep->slot ^ 1];
                    ox = mate->tgtX;
                    oy = mate->tgtY;
                    for (a = k; a >= -k; a--) {
                        b = k - ((a < 0) ? -a : a);
                        for (n = 0; n < 2; n++) {
                            ccx = cx - a;
                            ccy = cy - b;
                            if (ccx >= 0 && ccy >= 0 && ccx < 5 && ccy < 7 && !(ccx == ox && ccy == oy)) {
                                dx = px - (ccx << 5) + 16.0f;
                                dy = py - (ccy << 5) + 24.0f;
                                d = sqrtf(dx * dx + dy * dy);
                                if (!(best < d)) {
                                    v = D_801092C0_eatsa_pizza[ep->side][ccx][ccy];
                                    if (v != 0) {
                                        best = d;
                                        found = v;
                                        fx = ccx;
                                        fy = ccy;
                                    }
                                }
                            }
                            b = -b;
                        }
                    }
                    if (found != 0) {
                        break;
                    }
                }
                /* nothing found: aim at the partner's cell, but fx, fy stay unset (retail) */
                if (found != 0) {
                    ep->tgtX = fx;
                    ep->tgtY = fy;
                } else {
                    ep->tgtX = ox;
                    ep->tgtY = oy;
                }
                ty = (fy << 5) + 24;
                ep->timer = (func_80108F4C_eatsa_pizza() & 7) + 5;
                dx = px - ((fx << 5) + 16);
            }
            h = atan2df(dx, py - ty);
            if (h > 360.0) {
                h -= 360.0;
            }
            if (h < 0.0) {
                h += 360.0;
            }
            ep->cpuHeading = h;
        }
    }
    return btn;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801070E8_eatsa_pizza);
#endif

/* Push the player out of the other players. */
void func_801078C4_eatsa_pizza(omObjData* obj) {
    MgWork* work;
    EpPlayer* ep;
    MgWork* work2;
    EpPlayer* ep2;
    f32 dx;
    f32 dy;
    f32 d;
    f32 r;
    f32 r2;
    s32 i;
    s32 j;
    s32 hits;

    hits = 0;
    func_801083A8_eatsa_pizza(obj, &work, &ep);
    r = ep->radius;
    for (i = 0, j = 0; i < 4; i++, j++) {
        if (work->unk59 != j) {
            func_801083A8_eatsa_pizza(D_800EC598_minigame[i], &work2, &ep2);
            dx = ep2->x - ep->x;
            dy = ep2->y - ep->y;
            r2 = ep2->radius;
            d = sqrtf(dx * dx + dy * dy);
            if (d < r + r2) {
                if (d != 0.0) {
                    dx /= d;
                    dy /= d;
                }
                d = r + r2 - d;
                ep->x -= dx * d;
                ep->y -= dy * d;
                hits++;
            }
        }
    }
    if (hits != 0) {
        ep->pushed++;
    } else {
        ep->pushed = 0;
    }
}

/* Keep the player off the pizza's edge: push it back to its radius from the nearest pizza
   pixel in its 32x32 neighbourhood (D_8010927E: the team's pizza mask, 4 bits per pixel). */
void func_80107A64_eatsa_pizza(omObjData* obj) {
    MgWork* work;
    EpPlayer* ep;
    u8* mask;
    f32 cx;
    f32 cy;
    f32 dx;
    f32 dy;
    f32 d;
    f32 best;
    f32 bestX;
    f32 bestY;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s32 x;
    s32 y;
    s32 n;

    bestY = 65535.0f;
    bestX = 65535.0f;
    best = 65535.0f;
    n = 0;
    func_801083A8_eatsa_pizza(obj, &work, &ep);
    mask = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[ep->side], 0);
    cx = ep->x + 160.0f;
    cy = ep->y + 120.0f;
    y0 = cy - 16.0f;
    if (y0 < 0) {
        y0 = 0;
    }
    y1 = cy + 16.0f;
    if (y1 > 240) {
        y1 = 240;
    }
    x0 = cx - 16.0f;
    if (x0 < 0) {
        x0 = 0;
    }
    x1 = cx + 16.0f;
    if (x1 > 320) {
        x1 = 320;
    }
    if (ep->side == 1) {
        cx -= 160.0f;
        x0 -= 160;
        x1 -= 160;
    }
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            u8 b = mask[(y * 160 + x) >> 1];

            if ((x & 1) ? (b & 0xF0) : (b & 0xF)) {
                dx = x - cx;
                dy = y - cy;
                d = sqrtf(dx * dx + dy * dy);
                if (!(best < d)) {
                    best = d;
                    bestX = x - 160 + ep->side * 160;
                    bestY = y - 120;
                    n++;
                }
            }
        }
    }
    if (n != 0 && best < ep->radius) {
        dx = bestX - ep->prevX;
        dy = bestY - ep->prevY;
        d = sqrtf(dx * dx + dy * dy);
        if (d != 0.0) {
            dx /= d;
            dy /= d;
            ep->x = bestX - dx * ep->radius;
            ep->y = bestY - dy * ep->radius;
        }
    }
}

/* A bite: subtract the bite shape (D_80109282, 32x32, 4 bits per pixel) from the team's pizza mask in
   front of the player; every 2x2 block eaten down to nothing clears its slice pixels and counts them off.
   Returns 0 when nothing was eaten, else 2, or 3 when the bite hit a thick part (it also rumbles). */
#ifdef NON_MATCHING
/* 356 of 361 instructions, masked 89: register allocation and a 16-byte smaller frame (retail keeps more of
   the loop state on the stack); logic checked block by block against the asm */
s16 func_80107E6C_eatsa_pizza(omObjData* obj) {
    MgWork* work;
    EpPlayer* ep;
    u16* slice;
    u8* mask;
    u8* shape;
    u16 color;
    s32 cx;
    s32 cy;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s32 x;
    s32 y;
    s32 r;
    s32 c;
    s32 i;
    s32 j;
    u32 b;
    u32 s;
    u32 n;
    u8 cnt;
    s16 ret;

    ret = 0;
    func_801083A8_eatsa_pizza(obj, &work, &ep);
    slice = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[ep->side], 0);
    mask = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[ep->side], 0);
    shape = func_801090B4_eatsa_pizza(D_80109282_eatsa_pizza[0], 0);
    if (ep->side != 0) {
        cx = ep->x - sindf(work->unk3C) * 2.0;
    } else {
        cx = ep->x + 160.0 - sindf(work->unk3C) * 2.0;
    }
    cy = ep->y + 120.0 - cosdf(work->unk3C) * 2.0;
    y0 = cy - 16;
    if (y0 < 0) {
        y0 = 0;
    }
    y1 = cy + 16;
    if (y1 > 240) {
        y1 = 240;
    }
    x0 = cx - 16;
    if (x0 < 0) {
        x0 = 0;
    }
    x1 = cx + 16;
    if (x1 > 320) {
        x1 = 320;
    }
    if (x0 & 1) {
        x0++;
    }
    for (y = y0, r = 0; y < y1; y++, r++) {
        for (x = x0, c = 0; x < x1; x++, c++) {
            i = (y * 160 + x) >> 1;
            if (y & 1) {
                j = ((y - 1) * 160 + x) >> 1;
            } else {
                j = ((y + 1) * 160 + x) >> 1;
            }
            if (slice[i * 2 + (x & 1)] & 1) {
                b = mask[i];
                if (c & 1) {
                    s = shape[((r << 5) + c) >> 1];
                    if ((b & 0xF) != 0 && (n = s & 0xF) != 0 && !(s & 8)) {
                        if ((b & 0xF) >= 4) {
                            omVibrate(work->unk59, 5, 0, 5);
                            ret |= 0x8000;
                        }
                        b -= n;
                    }
                } else {
                    s = shape[((r << 5) + c) >> 1];
                    if ((b & 0xF0) != 0 && (n = s & 0xF0) != 0 && !(s & 0x80)) {
                        if ((b & 0xF0) >= 0x40) {
                            omVibrate(work->unk59, 5, 0, 5);
                            ret |= 0x8000;
                        }
                        b -= n;
                    }
                }
                mask[i] = b;
                if (mask[i] == 0 && mask[j] == 0) {
                    ret++;
                    cnt = 0;
                    if (slice[i * 2] & 1) {
                        cnt = 1;
                    }
                    if (slice[i * 2 + 1] & 1) {
                        cnt++;
                    }
                    if (slice[j * 2] & 1) {
                        cnt++;
                    }
                    if (slice[j * 2 + 1] & 1) {
                        cnt++;
                    }
                    color = slice[i * 2] &= ~1;
                    slice[i * 2 + 1] &= ~1;
                    slice[j * 2] &= ~1;
                    slice[j * 2 + 1] &= ~1;
                    D_801092B8_eatsa_pizza[ep->side] -= cnt;
                    D_801092C0_eatsa_pizza[ep->side][x >> 5][(y - 8) >> 5] -= cnt;
                }
            }
        }
    }
    if (ret != 0) {
        func_80108E48_eatsa_pizza(color, ep);
        ret = (ret & 0x8000) ? 3 : 2;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80107E6C_eatsa_pizza);
#endif

void func_801083A8_eatsa_pizza(omObjData* obj, MgWork** work, EpPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

void func_801083BC_eatsa_pizza(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80108470_eatsa_pizza);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_801084F8_eatsa_pizza);
    D_80109350_eatsa_pizza = 0;
}

/* The pizza sprite: loads it and hands over to func_801087DC_eatsa_pizza. */
void func_80108470_eatsa_pizza(omObjData* obj) {
    D_80109278_eatsa_pizza = func_80108FA4_eatsa_pizza(0x2C0000);
    D_80109288_eatsa_pizza[0] = func_80108FEC_eatsa_pizza(D_80109278_eatsa_pizza, 1);
    func_80054904_main(D_80109288_eatsa_pizza[0], 0, 160, 120);
    HuSprAttrSet(D_80109288_eatsa_pizza[0], 0, 0x4000);
    obj->func = func_801087DC_eatsa_pizza;
}

/* The pizzas: per team load the slice texture (count its pixels, in all and per 32x32 cell) and the mask
   texture (count its thin pixels); then the bite textures and the bite mark group. */
void func_801084F8_eatsa_pizza(omObjData* obj) {
    u16* slice;
    u8* mask;
    s16 grp;
    s32 t;
    s32 x;
    s32 y;

    for (t = 0; t < 2; t++) {
        D_8010927A_eatsa_pizza[t] = func_80108FA4_eatsa_pizza((t + 1) | 0x2C0000);
        D_8010928A_eatsa_pizza[t] = func_80108FEC_eatsa_pizza(D_8010927A_eatsa_pizza[t], 1);
        HuSprAttrSet(D_8010928A_eatsa_pizza[t], 0, 0x1008);
        slice = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[t], 0);
        for (y = 0; y < 240; y++) {
            for (x = 0; x < 160; x++) {
                if (slice[y * 160 + x] & 1) {
                    D_801092B8_eatsa_pizza[t]++;
                    D_801092C0_eatsa_pizza[t][x >> 5][(y - 8) >> 5]++;
                }
            }
        }
        D_8010927E_eatsa_pizza[t] = func_80108FA4_eatsa_pizza((t + 3) | 0x2C0000);
        mask = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[t], 0);
        for (x = 0; x < 0x4B00; x++) {
            if ((mask[x] & 0xF) && !(mask[x] & 8)) {
                D_8010934C_eatsa_pizza[t]++;
            }
            if ((mask[x] & 0xF0) && !(mask[x] & 0x80)) {
                D_8010934C_eatsa_pizza[t]++;
            }
        }
    }
    func_80054904_main(D_8010928A_eatsa_pizza[0], 0, 80, 120);
    func_80054904_main(D_8010928A_eatsa_pizza[1], 0, 240, 120);
    D_80109282_eatsa_pizza[0] = func_80108FA4_eatsa_pizza(0x2C0005);
    D_80109282_eatsa_pizza[1] = func_80108FA4_eatsa_pizza(0x2C0006);
    D_8010928A_eatsa_pizza[2] = grp = HuSprGrpCreate(16, 0);
    for (t = 0; t < 16; t++) {
        HuSprAttrSet(grp, t, 0x9000);
        D_80109298_eatsa_pizza[t] = 0;
    }
    obj->func = func_80108C50_eatsa_pizza;
}

/* The game flow: start message, 30 s countdown, result, wipe out, return. */
void func_801087DC_eatsa_pizza(omObjData* obj) {
    s32 i;

    switch (D_80109350_eatsa_pizza) {
        case 0:
            GMesCreate(5);
            D_8010913C_eatsa_pizza = 900;
            D_80109350_eatsa_pizza++;
        case 1:
            if (WipeStatGet() == 0) {
                if (++D_80109144_eatsa_pizza == 1) {
                    HuAudSeqPlay(0x36);
                }
            }
            if (GMesStatGet() == 0) {
                D_80109350_eatsa_pizza++;
                GMesCreate(0x1A, (D_8010913C_eatsa_pizza + 29) / 30, 160, 32);
                HuAudFXPlay(0xE);
                for (i = 0; i < 2; i++) {
                    D_80109260_eatsa_pizza[i] = D_801092B8_eatsa_pizza[i];
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (D_801092B8_eatsa_pizza[i] == 0) {
                    D_80109350_eatsa_pizza = 3;
                }
            }
            D_8010913C_eatsa_pizza--;
            func_8003F578_main((D_8010913C_eatsa_pizza + 29) / 30);
            if (D_8010913C_eatsa_pizza == 0) {
                D_80109350_eatsa_pizza = 3;
            }
            break;
        case 3:
            for (i = 0; i < 2; i++) {
                HuSprAttrSet(D_8010928A_eatsa_pizza[i], 0, 0x4000);
            }
            if (D_80109260_eatsa_pizza[0] == D_801092B8_eatsa_pizza[0] && D_80109260_eatsa_pizza[1] == D_801092B8_eatsa_pizza[1]) {
                D_80109140_eatsa_pizza = -1;
            } else if (D_801092B8_eatsa_pizza[0] < D_801092B8_eatsa_pizza[1]) {
                D_80109268_eatsa_pizza[0][0]->unk34 = 1;
                D_80109268_eatsa_pizza[0][1]->unk34 = 1;
                D_80109140_eatsa_pizza = 0;
            } else {
                D_80109268_eatsa_pizza[1][0]->unk34 = 1;
                D_80109268_eatsa_pizza[1][1]->unk34 = 1;
                D_80109140_eatsa_pizza = 1;
            }
            func_8003F5C0_main();
            GMesCreate(0x10);
            HuAudSeqFadeOut(120);
            D_80109138_eatsa_pizza = 15;
            D_80109350_eatsa_pizza++;
            break;
        case 4:
            if (GMesStatGet() == 0) {
                if (--D_80109138_eatsa_pizza == 0) {
                    if (D_80109140_eatsa_pizza == -1) {
                        GMesCreate(0x20);
                        HuAudSeqPlay(0x6C);
                    } else {
                        GMesCreate(0x1E, GwPlayer[D_80109268_eatsa_pizza[D_80109140_eatsa_pizza][0]->player].chr,
                                   GwPlayer[D_80109268_eatsa_pizza[D_80109140_eatsa_pizza][1]->player].chr);
                        HuAudSeqPlay(0x66);
                    }
                    D_80109138_eatsa_pizza = 15;
                    D_80109350_eatsa_pizza++;
                }
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                if (--D_80109138_eatsa_pizza == 0) {
                    D_80109350_eatsa_pizza++;
                }
            }
            break;
        case 6:
            if (D_80109138_eatsa_pizza != 0) {
                if (--D_80109138_eatsa_pizza == 0) {
                    D_80109350_eatsa_pizza++;
                }
            } else {
                D_80109138_eatsa_pizza = 16;
                WipeCreateOut(0, D_8010913A_eatsa_pizza[0]);
                HuAudSeqFadeOut(D_8010913A_eatsa_pizza[0]);
                func_8004AB0C_main(D_8010913A_eatsa_pizza[0]);
            }
            break;
        case 7:
            func_8004A950_main();
            omOvlReturnEx(1);
            break;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_80109350_eatsa_pizza = 6;
    }
}

/* Bite marks: step each live one's animation, hide it at its last frame. */
void func_80108C50_eatsa_pizza(omObjData* obj) {
    HuSprite* spr;
    s16* live;
    s16 grp;
    s32 i;

    grp = D_8010928A_eatsa_pizza[2];
    for (i = 0; i < 16; i++) {
        live = &D_80109298_eatsa_pizza[i];
        if (*live != 0) {
            spr = HuSprGet(grp, i);
            func_800551AC_main(grp, i);
            if (spr->unk_8A >= spr->unk_84->unk10 - 1) {
                HuSprAttrSet(grp, i, 0x8000);
                *live = 0;
            }
        }
    }
}

/* Shows a bite mark (texture tex) at screen (x, y), rotated; returns its member or -1. */
s16 func_80108D1C_eatsa_pizza(s16 tex, s16 x, s16 y, f32 rot) {
    s16 grp;
    s32 i;

    if (tex == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_80109298_eatsa_pizza[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    D_80109298_eatsa_pizza[i] = 1;
    grp = D_8010928A_eatsa_pizza[2];
    func_80055024_main(grp, i, tex, 0);
    func_800550F4_main(grp, i, 2);
    func_80054904_main(grp, i, x, y);
    func_800552DC_main(grp, i, rot);
    HuSprAttrReset(grp, i, 0x8000);
    return i;
}

/* A bite mark at the player, tinted with an RGBA5551 colour. */
#ifdef NON_MATCHING
/* masked 3: retail copies grp into the colour's register after the colour is unpacked (one extra move) */
s16 func_80108E48_eatsa_pizza(u16 color, EpPlayer* ep) {
    s32 grp;
    s32 i;
    u32 c;

    grp = D_8010928A_eatsa_pizza[2];
    i = func_80108D1C_eatsa_pizza(D_80109282_eatsa_pizza[1], ep->x + 160.0, ep->y + 120.0, ep->heading);
    if (i == -1) {
        return -1;
    }
    c = color;
    func_80055484_main(grp, i, (c >> 11) << 3, (c >> 3) & 0xF8, (c << 2) & 0xF8, 0x100);
    HuSprScaleSet(grp, i, 0.75f, 0.75f);
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108E48_eatsa_pizza);
#endif

/* Random number: a 16-bit LCG output, mixed with rand8. */
u32 func_80108F4C_eatsa_pizza(void) {
    D_80109148_eatsa_pizza = D_80109148_eatsa_pizza * 0x41C64E6D + 0x3039;
    D_80109148_eatsa_pizza += rand8();
    return D_80109148_eatsa_pizza >> 16;
}

s16 func_80108FA4_eatsa_pizza(s32 file) {
    void* data;
    s16 tex;

    data = DataRead(file);
    tex = func_80055810_main(data);
    DataClose(data);
    return tex;
}

/* A sprite group of n members showing texture tex. */
s16 func_80108FEC_eatsa_pizza(s16 tex, s16 n) {
    s16 grp;
    s32 i;

    if (tex == -1) {
        return -1;
    }
    grp = HuSprGrpCreate(n, 0);
    if (grp == -1) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        func_80055024_main(grp, i, tex, 0);
    }
    return grp;
}

/* Texel data of frame `frame` of texture tex. */
#ifdef NON_MATCHING
/* masked 2: retail scales the index before loading unk00 (scheduling only) */
void* func_801090B4_eatsa_pizza(s16 tex, s16 frame) {
    return func_80055194_main(tex)->unk00[frame].unk00;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801090B4_eatsa_pizza);
#endif
