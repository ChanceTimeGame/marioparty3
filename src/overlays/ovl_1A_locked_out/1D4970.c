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
#include "input.h"

// lo A: Locked Out

typedef func_800E1BA8_minigame_ObjData MgWork;
typedef f32 Matrix4f[4][4];

/* MgWork::unk158 of a player. */
typedef struct LoPlayer {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ Vec prev; /* position at the start of the frame */
    /* 0x18 */ s16 unk18; /* stick, low half */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ s32 model; /* model file */
    /* 0x20 */ u8 player;
    /* 0x21 */ u8 chr;
    /* 0x22 */ u8 difficulty;
    /* 0x23 */ u8 escaped; /* through a door; counts on in the results */
    /* 0x24 */ u8 unk24; /* coins won */
    /* 0x25 */ u8 key; /* key carried, index + 1; 0 none */
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 cpu;
    /* 0x28 */ u8 ai; /* CPU state */
    /* 0x29 */ u8 unk29; /* motion */
    /* 0x2A */ u8 unk2A; /* motion */
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 target; /* CPU: key index */
    /* 0x2E */ u16 unk2E; /* CPU: picked a wrong key, may give up on it */
    /* 0x30 */ u16 door; /* CPU: door index */
    /* 0x32 */ s16 unk32;
    /* 0x34 */ char unk34[8];
    /* 0x3C */ s16 state;
    /* 0x3E */ s16 doorIdx; /* door being opened */
    /* 0x40 */ s16 timer;
    /* 0x42 */ char unk42[0xA];
} LoPlayer; /* size 0x4C */

s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);
f64 fabs(f64);
f32 sqrtf(f32);
extern s32 D_800A178C_main[][6];
u8 rand8(void);
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y); /* stick: x << 16 | y */
s32 func_800E4A90_minigame(omObjData* obj);
extern s32 D_800EBEB0_minigame[];

void func_80105C34_locked_out(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105CB4_locked_out(f32 (*src)[4], f32 (*dst)[4]);
void func_801090FC_locked_out(omObjData* obj, MgWork** work, LoPlayer** lp);
s16 func_80109FF4_locked_out(s16 tex, s16 n);

/* The ground/camera object's data (func_80106134_locked_out); Slot Synch's SsGround. */
typedef struct LoGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} LoGround; // Size 0xB4

/* A door (D_8010A638_locked_out[3]). */
typedef struct LoDoor {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 model; /* low byte of obj->model[2 + i] */
    /* 0x0E */ u8 unk0E; /* linked model */
    /* 0x0F */ u8 unk0F; /* model */
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[3];
} LoDoor; // Size 0x14

/* A key's object data (func_80109264_locked_out). */
typedef struct LoKey {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 kind; /* D_8010A678 % 3: model 7 + kind */
    /* 0x03 */ u8 unk03; /* state 2 countdown */
    /* 0x04 */ f32 unk04; /* radius */
    /* 0x08 */ Vec vel;
    /* 0x14 */ omObjData* holder; /* the player carrying it */
} LoKey; // Size 0x18

s16 func_8000B0D4_main(s32, s32);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E6F0C_minigame(s8 arg0);

void func_80105B38_locked_out(omObjData* obj);
void func_80106040_locked_out(void);
void func_80106134_locked_out(omObjData* obj);
void func_80106424_locked_out(omObjData* obj);
void func_801064E0_locked_out(omObjData* obj);
void func_8010713C_locked_out(void);
void func_80109110_locked_out(void);
s32 func_80109D70_locked_out(void);
void func_80109264_locked_out(omObjData* obj);
void func_80109444_locked_out(omObjData* obj);
void func_80109858_locked_out(omObjData* obj, u8 isPlayer, u8 drop);
void func_8001EF6C_main(s16, s16, char*);
void func_80109E88_locked_out(s16 mdl, char* part, s16 frame, Vec* out);
void func_80016B00_main(s16 model, s16 frame, char* name, Matrix4f* mtx);
void func_80088800_main(Matrix4f mf, f32 x, f32 y, f32 z); /* guTranslateF */
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_80106FBC_locked_out(omObjData* obj);
void func_801071D8_locked_out(omObjData* obj);
void func_80107ABC_locked_out(omObjData* obj);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
u16 func_80108A90_locked_out(omObjData* obj);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2); /* hmfman.c defines (s16, u8, s8) */
void func_800DDD94_minigame(omObjData* obj);
void func_800E5138_minigame(omObjData* obj);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z); /* guRotateRPYF */
void func_80107844_locked_out(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4);
void func_801089F8_locked_out(omObjData* obj, f32 x, f32 y, f32 z);
void func_80109CDC_locked_out(void);
f32 func_80109DBC_locked_out(f32 x, f32 z);
f32 func_80109E34_locked_out(Vec* a, Vec* b);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);

extern Vec D_8010A110_locked_out[7];
extern s32 D_8010A164_locked_out; /* result timer */
extern u16 D_8010A168_locked_out; /* game timer, frames */
extern s32 D_8010A16C_locked_out; /* last player through a door, -1 none */
extern s16 D_8010A170_locked_out; /* winner camera angle */
extern s8 D_8010A172_locked_out; /* players through a door */
extern s8 D_8010A173_locked_out; /* doors */
extern u8 D_8010A174_locked_out; /* first round */
extern u8 D_8010A178_locked_out[4][2]; /* [n][1]: the n-th player to spawn */
extern u8 D_8010A180_locked_out; /* players spawned */
extern Vec D_8010A184_locked_out[4]; /* start positions */
extern f32 D_8010A1B4_locked_out[4]; /* start headings */
extern Vec D_8010A1C4_locked_out[]; /* positions past the doors */ /* positions; the doors use [0], [3], [6] */
extern u32 D_8010A1E8_locked_out; /* random seed */
extern s32 D_8010A580_locked_out; /* result jingle timer */
extern s16 D_8010A584_locked_out; /* music start timer */
extern D_80111B50_vine_with_me_Struct D_8010A588_locked_out;
extern omObjData* D_8010A610_locked_out[10];
extern LoDoor D_8010A638_locked_out[3];
extern s16 D_8010A674_locked_out;
extern s16 D_8010A676_locked_out;
extern s16 D_8010A678_locked_out;
extern s16 D_8010A67A_locked_out;
extern f32 D_8010A680_locked_out[4][4]; /* world to view (D_8010A6B8 is its [3][2]) */
extern f32 D_8010A6B8_locked_out; /* D_8010A680[3][2] */
extern f32 D_8010A6C0_locked_out[4][4]; /* view to world */
extern f32 D_8010A700_locked_out; /* tan(fov / 2) */
extern u8 D_8010A704_locked_out[12]; /* shuffled slot order */

void func_801059A0_locked_out(void) {
    omObjData* obj;
    u8 cam;

    Hu3DAnimInit(2);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105B38_locked_out(obj);
    func_80106040_locked_out();
    memset(&D_8010A588_locked_out, 0, 0x28);
    D_8010A588_locked_out.unk01 = 4;
    func_800E5EA0_minigame(&D_8010A588_locked_out);
    func_8010713C_locked_out();
    D_8010A676_locked_out = 9;
    D_8010A678_locked_out = 0;
    func_80109110_locked_out();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105B38_locked_out(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 1400.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010A700_locked_out = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010A680_locked_out, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010A6C0_locked_out, &cam->mtxs[0].lookAtMtx);
    func_80105CB4_locked_out(D_8010A6C0_locked_out, D_8010A6C0_locked_out);
}

void func_80105C34_locked_out(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80105CB4_locked_out(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_80105C34_locked_out(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80105EA4_locked_out(Vec* pos, f32* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010A680_locked_out, m);
    t = m[3][2] * D_8010A700_locked_out;
    w = fabsf(t);
    if (w != 0.0) {
        out[0] = m[3][0] * 160.0f / w / 1.3333334f;
        out[1] = -m[3][1] * 120.0f / w;
    }
}

void func_80105F74_locked_out(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010A6B8_locked_out;
    w = fabsf(d * D_8010A700_locked_out);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010A6C0_locked_out, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

void func_80106040_locked_out(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_8010A67A_locked_out = (f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 3.0;
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 8, 0, -1, func_80106134_locked_out);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106424_locked_out);
    D_8010A674_locked_out = 0;
}

void func_80106134_locked_out(omObjData* obj) {
    LoGround* gw;
    s32 i;
    s32 attr;

    obj->data = gw = HuMemAllocTag(sizeof(LoGround), 31000);
    memset(gw, 0, sizeof(LoGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 0.0f, -600.0f, -615.0f, 600.0f, 615.0f);
    attr = 0x2D9;
    obj->model[0] = func_8000B108_main(0x3B0000, 0x2D9);
    obj->model[1] = func_8000B108_main(0x3B0003, 0x2D9);
    obj->model[6] = func_8000B108_main(0x3B0010, 0x2DD);
    obj->model[7] = func_8000B108_main(0x3B0011, 0x2DD);
    for (i = 0; i < 3; i++) {
        D_8010A638_locked_out[i].pos.x = D_8010A110_locked_out[i * 3].x;
        D_8010A638_locked_out[i].pos.y = D_8010A110_locked_out[i * 3].y;
        D_8010A638_locked_out[i].pos.z = D_8010A110_locked_out[i * 3].z;
        D_8010A638_locked_out[i].unk0C = 0;
        D_8010A638_locked_out[i].unk10 = 1;
        D_8010A638_locked_out[i].model = obj->model[2 + i] = func_8000B108_main((D_8010A67A_locked_out + 4) | 0x3B0000, attr);
        Hu3DModelPosSet(obj->model[2 + i], D_8010A638_locked_out[i].pos.x, D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
        func_8001C92C_main(obj->model[2 + i], 0.0f);
        D_8010A638_locked_out[i].unk0F = func_8000B0A0_main(7, 0x2DD);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 0.0f);
        Hu3DModelRotSet(D_8010A638_locked_out[i].unk0F, 90.0f, 0.0f, 0.0f);
        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(obj->model[6]);
        func_8001C258_main(D_8010A638_locked_out[i].unk0E, 4, 4);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0E, 0.0f);
    }
    obj->model[5] = func_8000B108_main(0x3B000A, 0x2B9);
    obj->func = func_801064E0_locked_out;
}

void func_80106424_locked_out(omObjData* obj) {
    LoGround* gw;

    obj->data = gw = HuMemAllocTag(sizeof(LoGround), 31000);
    memset(gw, 0, sizeof(LoGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 0.0f, -600.0f, -615.0f, 600.0f, 665.0f);
    obj->func = NULL;
}

/* The game controller (the ground object's per-frame function). */
void func_801064E0_locked_out(omObjData* obj) {
    LoPlayer* lp;
    s32 n;
    s32 i;
    s32 r;
    s32 found;
    s32 shut;
    s16 st;
    u16 attr;
    f32 s;
    f32 c;

    n = 0;
    switch (D_8010A674_locked_out) {
        case 0:
            GMesCreate(7);
            D_8010A168_locked_out = 300;
            D_8010A674_locked_out++;
            D_8010A584_locked_out = 20;
            /* fallthrough */
        case 1:
            if (--D_8010A584_locked_out == 0) {
                HuAudSeqPlay(0x35);
            }
            if (GMesStatGet() == 0) {
                func_800E6F0C_minigame(2);
                D_8010A674_locked_out++;
                GMesCreate(0x1A, (D_8010A168_locked_out + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x35);
            }
            break;
        case 2:
            shut = 0;
            for (i = 0; i < D_8010A173_locked_out; i++) {
                shut += D_8010A638_locked_out[i].unk10 == 0;
            }
            if (shut >= D_8010A172_locked_out - 1) {
                D_8010A674_locked_out = 3;
            }
            D_8010A168_locked_out--;
            func_8003F578_main((D_8010A168_locked_out + 29) / 30);
            if (D_8010A168_locked_out == 0) {
                D_8010A674_locked_out = 3;
            }
            break;
        case 3:
            D_8010A172_locked_out = 0;
            D_8010A16C_locked_out = -1;
            for (i = 0; i < 4; i++) {
                if (((LoPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)->escaped != 0) {
                    D_8010A172_locked_out++;
                    n++;
                    D_8010A16C_locked_out = i;
                }
                st = ((LoPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)->state;
                if ((st != 0) & (st < 5)) {
                    break;
                }
            }
            if (i < 4) {
                break;
            }
            for (i = 0; i < 4; i++) {
                lp = ((MgWork*)D_800EC598_minigame[i]->data)->unk158;
                if (lp->escaped == 0 && lp->unk24 == 0) {
                    lp->unk24 = n;
                }
            }
            if (D_8010A172_locked_out >= 2) {
                WipeCreateOut(12, 30);
                D_8010A674_locked_out = 4;
                D_8010A174_locked_out = 0;
            } else {
                func_8003F5C0_main();
                GMesCreate(0x12);
                HuAudSeqFadeOut(120);
                D_8010A674_locked_out = 6;
            }
            break;
        case 4:
            if (WipeStatGet() != 0) {
                break;
            }
            attr = 0x2B9;
            func_8001ACDC_main(obj->model[1]);
            obj->model[1] = func_8000B108_main(0x3B0002, 0x2B9);
            D_8010A67A_locked_out = (f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 3.0;
            D_8010A173_locked_out = 2;
            for (i = 0; i < 3; i++) {
                if (obj->model[2 + i] != 0) {
                    func_8001ACDC_main(obj->model[2 + i]);
                    func_8001ACDC_main(D_8010A638_locked_out[i].unk0E);
                    obj->model[2 + i] = 0;
                    D_8010A638_locked_out[i].unk10 = 0;
                }
                if (i < 2) {
                    D_8010A638_locked_out[i].pos.x = D_8010A110_locked_out[i * 3 + 1].x;
                    D_8010A638_locked_out[i].pos.y = D_8010A110_locked_out[i * 3 + 1].y;
                    D_8010A638_locked_out[i].pos.z = D_8010A110_locked_out[i * 3 + 1].z;
                    D_8010A638_locked_out[i].unk0C = 0;
                    D_8010A638_locked_out[i].unk10 = 1;
                    if (D_8010A172_locked_out == 2) {
                        D_8010A638_locked_out[i].model = obj->model[2 + i] = func_8000B108_main((D_8010A67A_locked_out + 13) | 0x3B0000, attr);
                    } else {
                        D_8010A638_locked_out[i].model = obj->model[2 + i] = func_8000B108_main((D_8010A67A_locked_out + 4) | 0x3B0000, attr);
                    }
                    if (D_8010A172_locked_out == 2) {
                        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(obj->model[7]);
                    } else {
                        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(obj->model[6]);
                    }
                    func_8001C92C_main(D_8010A638_locked_out[i].unk0E, 0.0f);
                    func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 0.0f);
                    func_8001C6A8_main(D_8010A638_locked_out[i].unk0F, 0.0f);
                    func_8001C258_main(D_8010A638_locked_out[i].unk0F, 4, 4);
                    Hu3DModelPosSet(obj->model[2 + i], D_8010A638_locked_out[i].pos.x, D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
                    func_8001C92C_main(obj->model[2 + i], 0.0f);
                }
            }
            func_8001ACDC_main(obj->model[5]);
            obj->model[5] = func_8000B108_main((14 - D_8010A172_locked_out) | 0x3B0000, attr);
            func_80109CDC_locked_out();
            D_8010A676_locked_out = (D_8010A172_locked_out - 1) * 3;
            D_8010A678_locked_out = 0;
            func_80109110_locked_out();
            func_8003F578_main(10);
            WipeCreateIn(12, 30);
            D_8010A674_locked_out++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                D_8010A168_locked_out = 300;
                D_8010A674_locked_out = 2;
            }
            break;
        case 6:
            if (D_8010A16C_locked_out != -1 && D_8010A170_locked_out != 0) {
                s = sindf(D_8010A170_locked_out * 0.5);
                c = cosdf(D_8010A170_locked_out * 0.5);
                CZoom = (s * 47.0 + 23.0) * 20.0;
                CRot.x = -(s * 22.0 + 18.0);
                Center.x = c * D_8010A638_locked_out[((LoPlayer*)((MgWork*)D_800EC598_minigame[D_8010A16C_locked_out]->data)->unk158)->doorIdx].pos.x;
                Center.y = (s * 1.5 + 4.0) * 20.0;
                Center.z = c * D_8010A638_locked_out[((LoPlayer*)((MgWork*)D_800EC598_minigame[D_8010A16C_locked_out]->data)->unk158)->doorIdx].pos.z;
                D_8010A170_locked_out -= 6;
            }
            if (D_8010A16C_locked_out == -1 && D_8010A174_locked_out != 0) {
                for (i = 0; i < 4; i++) {
                    ((LoPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)->unk24 = 3;
                }
            } else {
                n = 0;
                for (r = 0; r < 4; r++) {
                    found = 0;
                    for (i = 0; i < 4; i++) {
                        lp = ((MgWork*)D_800EC598_minigame[i]->data)->unk158;
                        if (lp->unk24 == r) {
                            lp->unk24 = n;
                            found = 1;
                        }
                    }
                    n += found;
                }
            }
            if (GMesStatGet() == 0) {
                if (D_8010A16C_locked_out == -1) {
                    D_8010A164_locked_out = 0x9F;
                } else {
                    D_8010A164_locked_out = 0x71;
                }
                D_8010A580_locked_out = 15;
                D_8010A674_locked_out++;
                func_800E6F0C_minigame(4);
            }
            break;
        case 7:
            if (--D_8010A164_locked_out == 0) {
                D_8010A674_locked_out++;
            }
            if (--D_8010A580_locked_out == 0) {
                if (D_8010A16C_locked_out == -1) {
                    HuAudSeqPlay(0x6C);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 8:
            if (D_8010A164_locked_out != 0) {
                if (--D_8010A164_locked_out == 0) {
                    D_8010A674_locked_out++;
                }
            } else {
                func_800E6F0C_minigame(5);
                D_8010A164_locked_out = 16;
                /* retail reads the low half of the s32 D_8010A164 (big-endian) as the fade length */
                WipeCreateOut(0, ((s16*)&D_8010A164_locked_out)[1]);
                HuAudSeqFadeOut(((s16*)&D_8010A164_locked_out)[1]);
                func_8004AB0C_main(((s16*)&D_8010A164_locked_out)[1]);
            }
            break;
        case 9:
            func_8004A950_main();
            omOvlReturnEx(1);
            break;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010A674_locked_out = 8;
    }
}

// register allocation and scheduling of the HmfModelData base load (masked 4)
#ifdef NON_MATCHING
/* Pushes the player out of the doors' swing circles. */
void func_80106FBC_locked_out(omObjData* obj) {
    HmfModel* m;
    Vec pos;
    f32 n;
    f32 r;
    f32 a;
    s32 i;
    LoDoor* d;

    for (i = 0; i < 3; i++) {
        d = &D_8010A638_locked_out[i];
        if (d->unk0C != 0) {
            m = &HmfModelData[d->unk0E];
            n = D_800CCF58_main[m->unk02].unk02;
            r = m->unk40 * 175.0 / n + 50.0;
            pos.x = d->pos.x - 86.5;
            pos.y = d->pos.y;
            pos.z = d->pos.z;
            if (!(r < func_80109E34_locked_out(&pos, &obj->trans))) {
                a = func_80109DBC_locked_out(pos.x - obj->trans.x, pos.z - obj->trans.z);
                obj->trans.x = pos.x - r * sindf(a);
                obj->trans.z = pos.z - r * cosdf(a);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106FBC_locked_out);
#endif

void func_8010713C_locked_out(void) {
    s32 i;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_801071D8_locked_out);
    }
}

void func_801071D8_locked_out(omObjData* obj) {
    u8 motTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 files[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    u8 player;
    s8 chr;
    u32 file0;
    s32 mot;
    s32 file1;
    MgWork* work;
    LoPlayer* lp;

    player = D_8010A178_locked_out[D_8010A180_locked_out][1];
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    mot = D_800A178C_main[chr][1];
    file1 = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, file0, mot, player, 0x2D9, 0x2D9);
    obj->model[9] = func_8000B108_main(file0 | file1, 0x2ED);
    work = obj->data;
    work->unk50 &= ~1;
    work->unkEC = NULL;
    obj->trans.x = D_8010A184_locked_out[D_8010A180_locked_out].x;
    obj->trans.y = D_8010A184_locked_out[D_8010A180_locked_out].y;
    obj->trans.z = D_8010A184_locked_out[D_8010A180_locked_out].z;
    work->unk3C = D_8010A1B4_locked_out[D_8010A180_locked_out];
    switch (file0 >> 16) {
        case 6:
            work->unk48 *= 1.25f;
            break;
        case 4:
            work->unk48 *= 1.1f;
            break;
        case 5:
            work->unk48 *= 1.2f;
            break;
    }
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->trans.x = D_8010A184_locked_out[D_8010A180_locked_out].x;
    obj->trans.y = D_8010A184_locked_out[D_8010A180_locked_out].y;
    obj->trans.z = D_8010A184_locked_out[D_8010A180_locked_out].z;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    work->unk158 = HuMemAllocTag(sizeof(LoPlayer), 31000);
    memset(work->unk158, 0, sizeof(LoPlayer));
    lp = work->unk158;
    lp->player = player;
    lp->chr = chr;
    lp->cpu = GwPlayer[player].stat & 1;
    lp->difficulty = GwPlayer[player].cpu_difficulty;
    lp->model = file0 | 0x2F;
    lp->escaped = 0;
    lp->unk24 = 0;
    lp->x = obj->trans.x;
    lp->y = obj->trans.y;
    lp->z = obj->trans.z;
    lp->key = 0;
    lp->ai = 0;
    lp->unk2B = func_80017790_main(obj->model[9], 2, motTbl[chr], file0 | files[2][chr]);
    lp->unk29 = func_80017AD8_main(file0 | files[0][chr]);
    lp->unk2A = func_80017AD8_main(file0 | files[1][chr]);
    func_8001C514_main(obj->model[9]);
    func_800E149C_minigame(obj, 0, 2);
    work->unk50 |= 0x8000;
    obj->func = func_80107ABC_locked_out;
    obj->model[3] = func_8000B108_main(3, 0x2DD);
    obj->model[6] = func_8000B108_main(5, 0x2DD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 3), 0, 0);
    func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 0xE), 0, 0);
    func_800E5A00_minigame(obj, 32, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 30, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(obj, 31, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5A00_minigame(obj, 15, func_80017BB8_main(chr, 0x38), 1, 100);
    switch (file0 >> 16) {
        case 2:
        case 5:
        case 7:
            func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x39), 1, 60);
            break;
        case 3:
        case 4:
        case 6:
        case 8:
        case 9:
            func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x3A), 1, 60);
            break;
    }
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(chr, 0x8D), 1, 0);
    func_800E5A00_minigame(obj, 39, func_80017BB8_main(chr, 0x8E), 0, 0);
    func_800E5690_minigame(obj, 0);
    D_8010A180_locked_out++;
}

/* A player's actor work: the framework's func_800E1BA8_minigame cut down. */
void func_80107844_locked_out(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4) {
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
void func_80107ABC_locked_out(omObjData* obj) {
    u8 motTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    Vec hinge;
    s32 stick;
    MgWork* work;
    LoPlayer* lp;
    u8 pad;
    s32 drop;
    u16 btn;
    LoDoor* door;
    omObjData* ko;
    LoKey* key;
    s32 i;
    s32 tmp;
    f32 a;
    f32 speed;
    f32 frame;

    work = obj->data;
    lp = work->unk158;
    pad = work->unk57;
    drop = 0;
    if (D_8010A674_locked_out != 2) {
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
        D_800D5558_main[pad] = 0;
        D_800CDA7C_main[pad] = 0;
    }
    switch (D_8010A674_locked_out) {
        case 0:
            lp->doorIdx = 0;
            lp->state = 0;
            lp->timer = 0;
            lp->unk32 = 0;
            lp->door = 0;
            lp->unk2E = 0;
            lp->target = 0;
            lp->ai = 0;
            break;
        case 2:
            if (lp->cpu != 0 && lp->state == 0) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_80108A90_locked_out(obj);
            }
            break;
        case 3:
            if (lp->key != 0) {
                drop = 1;
            }
            if (lp->escaped == 0) {
                func_800E5690_minigame(obj, 15);
            }
            D_8010A180_locked_out = 0;
            break;
        case 4:
            if (lp->escaped == 0 && lp->timer == 0) {
                func_8004AC5C_main(lp->chr + 0x287, work->unk59);
                lp->timer = 1;
            }
            if (WipeStatGet() == 0) {
                if (lp->escaped == 0) {
                    func_8001C258_main(obj->model[0], 4, 4);
                    func_8001C258_main(obj->model[1], 4, 4);
                    work->unk50 |= 0x600;
                    lp->state = 6;
                    return;
                }
                obj->trans.x = D_8010A1C4_locked_out[D_8010A180_locked_out].x;
                obj->trans.y = D_8010A1C4_locked_out[D_8010A180_locked_out].y;
                obj->trans.z = D_8010A1C4_locked_out[D_8010A180_locked_out++].z;
                work->unk3C = 180.0f;
                work->unk40 = 0;
                work->unk50 &= ~0x200;
                lp->escaped = 0;
                lp->doorIdx = 0;
                lp->state = 0;
                lp->unk32 = 0;
                lp->door = 0;
                lp->unk2E = 0;
                lp->target = 0;
                lp->ai = 0;
            }
            break;
        case 5:
            work->unk3C = 180.0f;
            break;
        case 6:
            if (lp->escaped != 0) {
                if (lp->timer == 0) {
                    lp->timer = 1;
                    func_8004AC5C_main(0x3D7, work->unk59);
                }
                func_8001C92C_main(D_8010A638_locked_out[lp->doorIdx].unk0E, 1.0f);
                D_8010A638_locked_out[lp->doorIdx].unk0C = 1;
                work->unk3C = 0.0f;
                func_8001C92C_main(obj->model[0], 1.0f);
            }
            if (lp->state != 6) {
                func_8001C258_main(obj->model[0], 4, 4);
                tmp = obj->model[0];
                obj->model[0] = obj->model[9];
                obj->model[9] = tmp;
                func_8001C258_main(obj->model[0], 4, 0);
                func_800E5690_minigame(obj, 0);
            }
            lp->state = 6;
            break;
        case 7:
            if (lp->escaped == 1) {
                func_80045ED0_main(lp->model);
                GwPlayer[work->unk59].bonusCoin += 10;
                GwPlayer[work->unk59].bonusCoin = lp->unk24;
                func_800E5690_minigame(obj, 13);
                func_80017954_main(obj->model[0], 2, motTbl[lp->chr], lp->unk29);
                lp->escaped++;
            } else if (lp->escaped == 0) {
                GwPlayer[work->unk59].bonusCoin = lp->unk24;
                lp->escaped--;
            }
            break;
        case 8:
            if (work != NULL) {
                HuMemFree(work->unk158);
                obj->data = NULL;
                obj->func = NULL;
            }
            /* fallthrough */
        case 9:
            return;
    }
    btn = D_800D5558_main[pad];
    stick = func_800E4A90_minigame(obj);
    lp->prev.x = obj->trans.x;
    lp->prev.y = obj->trans.y;
    lp->prev.z = obj->trans.z;
    if (lp->key != 0) {
        D_800D5558_main[pad] &= ~0x4000;
    } else {
        HmfModelData[obj->model[0]].unk06 = 0xFF;
    }
    door = &D_8010A638_locked_out[lp->doorIdx];
    switch (lp->state) {
        case 0:
            if (stick & 0x200000) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                work->unk40 = 0;
                frame = HmfModelData[obj->model[0]].unk40;
                if ((f32)D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= frame) {
                    lp->unk26 = 0;
                    if (lp->key != 0) {
                        func_8001EED8_main(obj->model[0], obj->motion[38], 0);
                    }
                } else if (lp->key == 0 && fabs(frame - 15.0) <= 1.0) {
                    drop = 1;
                }
            } else {
                lp->unk26 = 0;
            }
            if (btn & 0x8000) {
                if (lp->key == 0) {
                    if (lp->unk26 == 0 && func_800E5690_minigame(obj, 39) != 0) {
                        func_8001C6A8_main(obj->model[0], 0.0f);
                        lp->unk26 = 1;
                    }
                } else {
                    drop = 1;
                }
            }
            if ((stick & 0x8000) && lp->key != 0) {
                drop = 1;
            }
            func_800DDD94_minigame(obj);
            if (lp->key != 0) {
                for (i = 0; i < 3; i++) {
                    if (D_8010A638_locked_out[i].unk10 != 0) {
                        ko = D_8010A610_locked_out[lp->key - 1];
                        key = ko->data;
                        if (key->kind == D_8010A67A_locked_out
                            && !(func_80109E34_locked_out(&obj->trans, &D_8010A638_locked_out[i].pos) > work->unk48 + 20.0)) {
                            func_8001C258_main(D_8010A638_locked_out[i].unk0E, 4, 0);
                            func_8001C258_main(D_8010A638_locked_out[i].model, 4, 4);
                            drop = 1;
                            Hu3DModelPosSet(D_8010A638_locked_out[i].unk0E, D_8010A638_locked_out[i].pos.x,
                                            D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
                            func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 1.0f);
                            func_8001C258_main(D_8010A638_locked_out[i].unk0F, 4, 0);
                            Hu3DModelPosSet(D_8010A638_locked_out[i].unk0F, D_8010A638_locked_out[i].pos.x,
                                            D_8010A638_locked_out[i].pos.y + 200.0, D_8010A638_locked_out[i].pos.z);
                            func_8004AC5C_main(0x3D9, 4);
                            D_8010A638_locked_out[i].unk10 = 0;
                            lp->escaped = 1;
                            lp->state = 1;
                            lp->doorIdx = i;
                            work->unk50 |= 0x200;
                            func_8001C258_main(ko->model[0], 4, 4);
                            key->unk00 = 4;
                        }
                    }
                }
            }
            func_80109858_locked_out(obj, 1, drop);
            func_80106FBC_locked_out(obj);
            hinge.x = -610.5f;
            hinge.y = 0.0f;
            hinge.z = -607.0f;
            if (func_80109E34_locked_out(&hinge, &obj->trans) <= work->unk48 + 90.0) {
                a = func_80109DBC_locked_out(hinge.x - obj->trans.x, hinge.z - obj->trans.z);
                obj->trans.x = hinge.x - (work->unk48 + 90.0) * sindf(a);
                obj->trans.z = hinge.z - (work->unk48 + 90.0) * cosdf(a);
            }
            hinge.x = 610.5f;
            hinge.y = 0.0f;
            hinge.z = -607.0f;
            /* retail tests +80 but pushes out to +90, as the keys do */
            if (func_80109E34_locked_out(&hinge, &obj->trans) <= work->unk48 + 80.0) {
                a = func_80109DBC_locked_out(hinge.x - obj->trans.x, hinge.z - obj->trans.z);
                obj->trans.x = hinge.x - (work->unk48 + 90.0) * sindf(a);
                obj->trans.z = hinge.z - (work->unk48 + 90.0) * cosdf(a);
            }
            break;
        case 1:
            func_800E5690_minigame(obj, 1);
            work->unk3C = 180.0f;
            a = func_80109DBC_locked_out(obj->trans.x - (door->pos.x + work->unk48 * 1.75),
                                         obj->trans.z - (door->pos.z + work->unk48 * 1.4));
            obj->trans.x = lp->prev.x - sindf(a) * 4.0;
            obj->trans.z = lp->prev.z - cosdf(a) * 4.0;
            hinge.x = door->pos.x + work->unk48 * 1.75;
            hinge.y = door->pos.y;
            hinge.z = door->pos.z + work->unk48 * 1.4;
            if (func_80109E34_locked_out(&obj->trans, &hinge) < 5.0) {
                func_8001C92C_main(door->unk0E, 0.5f);
                func_8004AC5C_main(0x3D7, work->unk59);
                door->unk0C = 1;
                work->unk3C = 180.0f;
                lp->state++;
            }
            break;
        case 2:
            if (work->unk3C < 250.0) {
                work->unk3C += 6.0;
            } else {
                func_800E5690_minigame(obj, 0);
            }
            if ((f32)D_800CCF58_main[HmfModelData[door->unk0E].unk02].unk02 <= HmfModelData[door->unk0E].unk40) {
                lp->state++;
                lp->timer = 30;
            }
            break;
        case 3:
            func_800E5690_minigame(obj, 1);
            if (work->unk3C > 180.0) {
                work->unk3C += -3.0;
            }
            a = work->unk3C;
            if (lp->chr == 4 || lp->chr == 5) {
                speed = 10.2f;
            } else {
                speed = 6.8f;
            }
            obj->trans.x = speed * sindf(a) + lp->prev.x;
            obj->trans.z = speed * cosdf(a) + lp->prev.z;
            if (--lp->timer == 0) {
                func_8004AC5C_main(0x3D8, work->unk59);
                lp->state++;
            }
            break;
        case 4:
            func_8001C92C_main(door->unk0E, 0.0f);
            func_8001C6A8_main((s16)door->unk0E, HmfModelData[door->unk0E].unk40 - 1.5);
            if (HmfModelData[door->unk0E].unk40 < 0.0) {
                func_8001C6A8_main((s16)door->unk0E, 0.0f);
                omVibrate(work->unk59, 2, 3, 10);
                door->unk0C = 0;
                lp->state++;
            }
            break;
        case 5:
            return;
        case 6:
            if (lp->escaped == 0) {
                func_80109858_locked_out(obj, 1, drop);
                func_80106FBC_locked_out(obj);
            }
            break;
    }
    lp->unk18 = stick;
    if (lp->state != 0) {
        func_80088910_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
        func_800E4E30_minigame(obj);
        func_800E5138_minigame(obj);
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 1.0f, obj->trans.z);
}

/* Spawns effect 9..11 (the first free one) at a point. */
void func_801089F8_locked_out(omObjData* obj, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[obj->model[i]].unk18 & 4) {
            func_800E4C88_minigame(obj, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

/* A CPU player's input: pick a key, fetch it (or chase its holder), carry it to a door. */
/* Returns an uninitialised u16 (retail); the caller ignores it. */
u16 func_80108A90_locked_out(omObjData* obj) {
    Matrix4f unused; /* retail's frame leaves these 64 bytes */
    u16 ret;
    MgWork* work;
    LoPlayer* lp;
    omObjData* ko;
    LoKey* key;
    omObjData* holder;
    LoDoor* door;
    f32 a;
    s32 i;
    s16 pad;
    u8 t;

    func_801090FC_locked_out(obj, &work, &lp);
    pad = (s8)work->unk57;
    func_800E4A90_minigame(obj);
    switch (lp->ai) {
        case 4:
            break;
        case 0:
            if (lp->key != 0) {
                D_800D5558_main[pad] |= 0x8000;
            }
            lp->target = 0;
            lp->unk2E = 0;
            t = (s32)((f32)func_80109D70_locked_out() * (1.0 / 65536.0) * D_8010A676_locked_out);
            ko = D_8010A610_locked_out[t];
            key = ko->data;
            if (key->kind != D_8010A67A_locked_out) {
                if ((s32)((f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 100.0) >= lp->difficulty * 5 + 5) {
                    lp->unk2E = 1;
                    goto pick;
                }
            } else {
            pick:
                lp->target = t;
                lp->ai++;
            }
            break;
        case 1:
            ko = D_8010A610_locked_out[lp->target];
            key = ko->data;
            if (lp->key != 0) {
                lp->ai = 2;
                break;
            }
            if (key->unk00 == 1) {
                holder = key->holder;
                a = func_80109DBC_locked_out(holder->trans.x - obj->trans.x, holder->trans.z - obj->trans.z);
                if (func_80109E34_locked_out(&obj->trans, &holder->trans) < work->unk48 * 2.2 + work->unk64) {
                    D_800D5558_main[pad] |= 0x4000;
                }
                for (i = 0; i < D_8010A678_locked_out; i++) {
                    key = D_8010A610_locked_out[i]->data;
                    if (key->kind == D_8010A67A_locked_out && key->unk00 == 0) {
                        break;
                    }
                }
                if (i < D_8010A678_locked_out
                    && (s32)((f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 100.0) < lp->difficulty * 5 + 5) {
                    lp->ai = 0;
                }
            } else if (key->unk00 == 4) {
                lp->ai = 0;
                break;
            } else {
                a = func_80109DBC_locked_out(ko->trans.x - obj->trans.x, ko->trans.z - obj->trans.z);
                if (func_80109E34_locked_out(&obj->trans, &ko->trans) <= work->unk48 + key->unk04 + 2.0
                    && fabs(a - work->unk3C) < 40.0) {
                    D_800D5558_main[pad] |= 0x8000;
                }
            }
            D_800CBB6E_main[pad] = (lp->difficulty * 6.0 + 46.0) * sindf(a);
            D_800D20A1_main[pad] = (lp->difficulty * 6.0 + 46.0) * -cosdf(a);
            break;
        case 2:
            if (lp->key != lp->target + 1) {
                D_800D5558_main[pad] |= 0x8000;
                lp->ai = 1;
                break;
            }
            lp->door = (s32)((f32)func_80109D70_locked_out() * (1.0 / 65536.0) * (s16)(D_8010A676_locked_out / 3));
            if (D_8010A638_locked_out[lp->door].unk10 == 0) {
                break;
            }
            lp->ai++;
            /* fallthrough */
        case 3:
            if (lp->key == 0) {
                lp->ai = 1;
            }
            door = &D_8010A638_locked_out[lp->door];
            if (door->unk10 == 0) {
                lp->ai = 2;
            }
            a = func_80109DBC_locked_out(door->pos.x - obj->trans.x, door->pos.z - obj->trans.z);
            D_800CBB6E_main[pad] = (lp->difficulty * 6.0 + 46.0) * sindf(a);
            D_800D20A1_main[pad] = (lp->difficulty * 6.0 + 46.0) * -cosdf(a);
            break;
    }
    if (lp->unk2E != 0
        && (s32)((f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 100.0) < lp->difficulty * 5 + 5) {
        lp->ai = 0;
    }
    return ret;
}

void func_801090FC_locked_out(omObjData* obj, MgWork** work, LoPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

/* Creates the keys(?) objects and shuffles their slot order. */
void func_80109110_locked_out(void) {
    s32 i;
    s16 j;
    u8 t;

    for (i = 0; i < D_8010A676_locked_out; i++) {
        D_8010A610_locked_out[i] = omAddObj(3, 5, 5, -1, func_80109264_locked_out);
    }
    for (i = 0; i < D_8010A676_locked_out; i++) {
        D_8010A704_locked_out[i] = i;
    }
    for (i = D_8010A676_locked_out; i > 0; i--) {
        j = (f32)func_80109D70_locked_out() * (1.0 / 65536.0) * i;
        t = D_8010A704_locked_out[i - 1];
        D_8010A704_locked_out[i - 1] = D_8010A704_locked_out[j];
        D_8010A704_locked_out[j] = t;
    }
}

void func_80109264_locked_out(omObjData* obj) {
    Vec pos[9] = {
        { 50.0f, 50.0f, 60.0f },   { -50.0f, 50.0f, -60.0f }, { 150.0f, 50.0f, -60.0f },
        { -150.0f, 50.0f, 60.0f }, { 250.0f, 50.0f, 60.0f },  { -250.0f, 50.0f, -60.0f },
        { 350.0f, 50.0f, -60.0f }, { -350.0f, 50.0f, 60.0f }, { 450.0f, 50.0f, 60.0f },
    };
    LoKey* key;

    obj->data = key = HuMemAllocTag(sizeof(LoKey), 31000);
    memset(key, 0, sizeof(LoKey));
    key->unk00 = 0;
    key->kind = D_8010A678_locked_out % 3;
    key->unk04 = 20.0f;
    key->holder = NULL;
    key->unk01 = 0;
    obj->model[0] = func_8000B108_main((key->kind + 7) | 0x3B0000, 0x2D9);
    obj->model[1] = func_8000B0D4_main(9, 0x2D9);
    Hu3DModelScaleSet(obj->model[1], 0.75f, 0.75f, 0.75f);
    obj->trans.x = pos[D_8010A704_locked_out[D_8010A678_locked_out]].x;
    obj->trans.y = pos[D_8010A704_locked_out[D_8010A678_locked_out]].y;
    obj->trans.z = pos[D_8010A704_locked_out[D_8010A678_locked_out]].z;
    obj->rot.x = -90.0f;
    obj->func = func_80109444_locked_out;
    D_8010A678_locked_out++;
}

/* A key's per-frame function: state, bounce, the door hinges' push-out, the room bounds. */
void func_80109444_locked_out(omObjData* obj) {
    Vec hinge;
    LoKey* key;
    f32 a;

    key = obj->data;
    func_8001C258_main(obj->model[1], 4, 0);
    switch (key->unk00) {
        case 0:
            key->unk01 = 1;
            break;
        case 2:
            key->unk01 = 0;
            key->unk03--;
            if (key->unk03 == 0) {
                key->unk00 = 3;
            }
            /* fallthrough */
        case 3:
            key->unk01 = 1;
            key->vel.y += -2.0f;
            obj->trans.x += key->vel.x;
            obj->trans.y += key->vel.y;
            obj->trans.z += key->vel.z;
            if (obj->trans.y < 50.0) {
                key->unk00 = 0;
                obj->trans.y = 50.0f;
                key->vel.y = 6.0f;
            }
            break;
        case 1:
        case 4:
            func_8001C258_main(obj->model[1], 4, 4);
            key->unk01 = 0;
            break;
    }
    hinge.x = -610.5f;
    hinge.y = 0.0f;
    hinge.z = -607.0f;
    if (func_80109E34_locked_out(&hinge, &obj->trans) <= key->unk04 + 90.0) {
        a = func_80109DBC_locked_out(hinge.x - obj->trans.x, hinge.z - obj->trans.z);
        obj->trans.x = hinge.x - (key->unk04 + 90.0) * sindf(a);
        obj->trans.z = hinge.z - (key->unk04 + 90.0) * cosdf(a);
    }
    hinge.x = 610.5f;
    hinge.y = 0.0f;
    hinge.z = -607.0f;
    /* retail tests +80 but pushes out to +90 */
    if (func_80109E34_locked_out(&hinge, &obj->trans) <= key->unk04 + 80.0) {
        a = func_80109DBC_locked_out(hinge.x - obj->trans.x, hinge.z - obj->trans.z);
        obj->trans.x = hinge.x - (key->unk04 + 90.0) * sindf(a);
        obj->trans.z = hinge.z - (key->unk04 + 90.0) * cosdf(a);
    }
    if (obj->trans.x < -600.0) {
        obj->trans.x = -600.0f;
    }
    if (obj->trans.x > 600.0) {
        obj->trans.x = 600.0f;
    }
    if (obj->trans.z < -575.0) {
        obj->trans.z = -575.0f;
    }
    if (obj->trans.z > 575.0) {
        obj->trans.z = 575.0f;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 1.0f, obj->trans.z);
    func_80109858_locked_out(obj, 0, 0);
    func_80106FBC_locked_out(obj);
}

/* Keys against an object: a player (isPlayer) drops its key when drop is set and grabs one it faces;
 * a key (isPlayer 0) pushes the other keys out of its radius. */
void func_80109858_locked_out(omObjData* obj, u8 isPlayer, u8 drop) {
    Vec hook;
    MgWork* work;
    LoPlayer* lp;
    omObjData* ko;
    LoKey* key;
    LoKey* self;
    f32 radius;
    f32 dist;
    f32 a;
    f32 d;
    s32 i;
    s16 mdl;

    self = NULL;
    if (D_8010A678_locked_out == 0) {
        return;
    }
    if (isPlayer) {
        func_801090FC_locked_out(obj, &work, &lp);
        radius = work->unk48;
    } else {
        self = obj->data;
        radius = self->unk04;
        drop = 0;
    }
    if (drop && lp->key != 0) {
        ko = D_8010A610_locked_out[lp->key - 1];
        key = ko->data;
        func_8001C258_main(ko->model[0], 0x4000, 0);
        key->vel.x = sindf(work->unk3C) * 4.0;
        key->vel.y = 15.0f;
        key->vel.z = cosdf(work->unk3C) * 4.0;
        mdl = obj->model[0];
        func_80109E88_locked_out(mdl, "item_hook", HmfModelData[mdl].unk40, &hook);
        ko->trans.x = key->vel.x * 20.0f + hook.x;
        ko->trans.y = hook.y + 50.0;
        ko->trans.z = key->vel.z * 20.0f + hook.z;
        lp->key = 0;
        if (key->unk00 != 4) {
            key->unk00 = 2;
        }
        key->unk01 = 0;
        key->unk03 = 5;
        drop = 0;
    }
    for (i = 0; i < D_8010A676_locked_out; i++) {
        ko = D_8010A610_locked_out[i];
        key = ko->data;
        if (key == self) {
            continue;
        }
        dist = func_80109E34_locked_out(&obj->trans, &ko->trans);
        if (!(dist < radius + key->unk04 + 24.0)) {
            continue;
        }
        a = func_80109DBC_locked_out(ko->trans.x - obj->trans.x, ko->trans.z - obj->trans.z);
        /* retail: always true */
        if (dist < radius + key->unk04 && ((key->unk00 != 1) | (key->unk00 != 4))) {
            d = func_80109DBC_locked_out(obj->trans.x - ko->trans.x, obj->trans.z - ko->trans.z);
            ko->trans.x = obj->trans.x - (radius + key->unk04) * sindf(d);
            ko->trans.z = obj->trans.z - (radius + key->unk04) * cosdf(d);
        }
        if (drop && lp->key == 0 && key->unk01 != 0) {
            a = a - work->unk3C;
            while (a < -180.0) {
                a += 360.0;
            }
            while (a > 180.0) {
                a -= 360.0;
            }
            if (fabs(a) < 45.0) {
                func_8001EF6C_main(ko->model[0], obj->model[0], "item_hook");
                func_8001C258_main(ko->model[0], 0x4000, 0x4000);
                func_8004AC5C_main(0x3D6, work->unk59);
                lp->key = i + 1;
                key->unk00 = 1;
                key->unk01 = 0;
                key->holder = obj;
            }
        }
    }
}

void func_80109CDC_locked_out(void) {
    omObjData* o;
    s32 i;

    for (i = 0; i < D_8010A676_locked_out; i++) {
        o = D_8010A610_locked_out[i];
        func_8001ACDC_main(o->model[0]);
        func_8001ACDC_main(o->model[1]);
        HuMemFree(o->data);
        o->data = NULL;
        omDelObj(o);
    }
}

s32 func_80109D70_locked_out(void) {
    u32 r;

    r = (rand8() + D_8010A1E8_locked_out) * 0x41C64E6D + 0x3039;
    D_8010A1E8_locked_out = r;
    return r >> 16;
}

/* atan2df(x, z) wrapped to -180..180. */
f32 func_80109DBC_locked_out(f32 x, f32 z) {
    f32 a;
    f32 full = 360.0f;

    a = atan2df(x, z);
    if (a < -180.0f) {
        a += full;
    } else if (a >= 180.0) {
        a -= full;
    }
    return a;
}

// register allocation (masked 0, raw 4)
#ifdef NON_MATCHING
/* Distance in XZ. */
f32 func_80109E34_locked_out(Vec* a, Vec* b) {
    f32 dx;
    f32 dz;

    dx = a->x - b->x;
    dx = dx * dx;
    dz = a->z - b->z;
    return sqrtf(dx + dz * dz);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E34_locked_out);
#endif

/* Gets a model part's world position. */
void func_80109E88_locked_out(s16 mdl, char* part, s16 frame, Vec* out) {
    Matrix4f m;
    Matrix4f res;
    Matrix4f partMtx;
    HmfModel* model;

    func_80016B00_main(mdl, frame, part, &partMtx);
    model = &HmfModelData[mdl];
    func_80088800_main(m, model->pos.x, model->pos.y, model->pos.z);
    func_80017D24_main(m, model->rot.x, model->rot.y, model->rot.z);
    func_80017CD0_main(m, model->scale.x, model->scale.y, model->scale.z);
    func_80018044_main(partMtx, m, res);
    out->x = res[0][0] + res[1][0] + res[2][0] + res[3][0];
    out->y = res[0][1] + res[1][1] + res[2][1] + res[3][1];
    out->z = res[0][2] + res[1][2] + res[2][2] + res[3][2];
}

s16 func_80109FAC_locked_out(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_80109FF4_locked_out(s16 tex, s16 n) {
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

/* A sprite's frame entry (unused here). */
HuSprite_Unk84_Unk00_Struct* func_8010A0BC_locked_out(s16 tex, s16 frame) {
    return &func_80055194_main(tex)->unk00[frame];
}
