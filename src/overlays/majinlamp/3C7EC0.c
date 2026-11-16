#include "common.h"
#include "game/board.h"
#include "game/hmfman.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/1006F0.h"

// event e5: the Genie lamp (the genie carries the player to the star)
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_8008A120_main(f32 (*m)[4], f32 angle);
void func_80007DD8_main(s16);
void func_80105B14_majinlamp(omObjData *obj);
void func_80105E2C_majinlamp(omObjData *obj);
void func_801067EC_majinlamp(omObjData *obj);
void func_80106BB0_majinlamp(omObjData *obj);
void func_80106D3C_majinlamp(omObjData *obj);
void func_80106E74_majinlamp(void);
void func_8010771C_majinlamp(void);
void func_80107D98_majinlamp(void);
void func_80107DD8_majinlamp(omObjData *obj);
void func_80107E1C_majinlamp(omObjData *obj);
void func_80107E40_majinlamp(void);
void func_80107E64_majinlamp(void);
void func_80107EA0_majinlamp(void);
void func_80107F54_majinlamp(void);
void func_801080C4_majinlamp(void);

extern f32 D_801080D0_majinlamp; /* camera 0 fov, near, far */
extern f32 D_801080D4_majinlamp;
extern f32 D_801080D8_majinlamp;
extern f32 D_801080DC_majinlamp; /* camera 1 fov, near, far */
extern f32 D_801080E0_majinlamp;
extern f32 D_801080E4_majinlamp;
extern s16 D_801080E8_majinlamp; /* the player rides the genie */
extern s16 D_801080EA_majinlamp; /* the player turns with the genie */
extern s16 D_801080EC_majinlamp; /* the genie bobs */
extern f32 D_801080F0_majinlamp; /* the player's height above the genie */
extern Vec D_801080F4_majinlamp[3];
extern Vec D_80108118_majinlamp;
extern s32 D_80108124_majinlamp;

extern Process *D_801082E0_majinlamp;
extern Vec D_801082E4_majinlamp;
extern Vec D_801082F0_majinlamp;
extern Vec D_801082FC_majinlamp;
extern Vec D_80108308_majinlamp;
extern Vec D_80108314_majinlamp;
extern Vec D_80108320_majinlamp;
extern Object *D_8010832C_majinlamp; /* the genie */
extern Object *D_80108330_majinlamp; /* the sky background */
extern GW_PLAYER *D_80108334_majinlamp;
extern s16 D_80108338_majinlamp;
extern s16 D_8010833A_majinlamp;
extern s32 D_8010833C_majinlamp; /* the player */
extern s16 D_8010833E_majinlamp;
extern s16 D_80108340_majinlamp[2]; /* the player's ride motion, then its second id (D_80108342) */
extern omObjData *D_80108350_majinlamp[32]; /* the movers */

void func_801059A0_majinlamp(void) {
    D_8010833C_majinlamp = GwSystem.current_player_index;
    omInitObjMan(80, 80);
    func_80107F54_majinlamp();
    func_80107E40_majinlamp();
    func_8005A6B0_main();
    omAddPrcObj(func_80107D98_majinlamp, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80107E1C_majinlamp);
}

void func_80105A20_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80108350_majinlamp[i] = NULL;
    }
}

void func_80105A50_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] != NULL
            && (D_80108350_majinlamp[i]->func == func_80105B14_majinlamp || D_80108350_majinlamp[i]->func == func_80105E2C_majinlamp
                || D_80108350_majinlamp[i]->func == func_801067EC_majinlamp)) {
            if (D_80108350_majinlamp[i]->stat & 4) {
                D_80108350_majinlamp[i]->data = NULL;
                omDelObj(D_80108350_majinlamp[i]);
            }
        }
    }
}

void func_80105B14_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->coords.x = obj->trans.x;
            GwPlayer[obj->work[0]].player_obj->coords.y = obj->trans.y;
            GwPlayer[obj->work[0]].player_obj->coords.z = obj->trans.z;
            omDelObj(obj);
            return;
        }
        GwPlayer[obj->work[0]].player_obj->coords.x += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += obj->scale.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += obj->scale.z;
    } else {
        if (obj->work[1] == 0) {
            model->coords.x = obj->trans.x;
            model->coords.y = obj->trans.y;
            model->coords.z = obj->trans.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        model->coords.x += obj->scale.x;
        model->coords.y += obj->scale.y;
        model->coords.z += obj->scale.z;
    }
}

omObjData *func_80105CA8_majinlamp(s32 player, Vec *pos, s32 frames, Object *model) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105B14_majinlamp);
    obj->work[0] = player;
    obj->work[1] = frames;
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    if (model == NULL) {
        obj->scale.x = (pos->x - GwPlayer[player].player_obj->coords.x) / frames;
        obj->scale.y = (pos->y - GwPlayer[player].player_obj->coords.y) / frames;
        obj->scale.z = (pos->z - GwPlayer[player].player_obj->coords.z) / frames;
    } else {
        obj->scale.x = (pos->x - model->coords.x) / frames;
        obj->scale.y = (pos->y - model->coords.y) / frames;
        obj->scale.z = (pos->z - model->coords.z) / frames;
    }
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80105E2C_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->coords.x = obj->trans.x;
            GwPlayer[obj->work[0]].player_obj->coords.y = obj->trans.y;
            GwPlayer[obj->work[0]].player_obj->coords.z = obj->trans.z;
            omDelObj(obj);
            return;
        }
        GwPlayer[obj->work[0]].player_obj->coords.x += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += obj->scale.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += obj->scale.z;
        GwPlayer[obj->work[0]].player_obj->coords.x += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z;
    } else {
        if (obj->work[1] == 0) {
            model->coords.x = obj->trans.x;
            model->coords.y = obj->trans.y;
            model->coords.z = obj->trans.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        model->coords.x += obj->scale.x;
        model->coords.y += obj->scale.y;
        model->coords.z += obj->scale.z;
        model->coords.x += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x;
        model->coords.y += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y;
        model->coords.z += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z;
    }
}

/* model is an Object, or a player index smuggled in the pointer (retail tells them apart by the sign bit: KSEG0) */
omObjData *func_80106634_majinlamp(Object *model, Vec *pos, s32 frames, Vec *arc) {
    omObjData *obj;
    s32 player = -1;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105E2C_majinlamp);
    if ((s32)model >= 0) {
        player = (s32)model;
        model = NULL;
        obj->work[0] = player;
    }
    obj->work[1] = frames;
    obj->work[2] = frames;
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    if (model == NULL) {
        obj->scale.x = (pos->x - GwPlayer[player].player_obj->coords.x) / frames;
        obj->scale.y = (pos->y - GwPlayer[player].player_obj->coords.y) / frames;
        obj->scale.z = (pos->z - GwPlayer[player].player_obj->coords.z) / frames;
    } else {
        obj->scale.x = (pos->x - model->coords.x) / frames;
        obj->scale.y = (pos->y - model->coords.y) / frames;
        obj->scale.z = (pos->z - model->coords.z) / frames;
    }
    obj->rot.x = arc->x;
    obj->rot.y = arc->y;
    obj->rot.z = arc->z;
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_801067EC_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->rot.x = obj->rot.x;
            GwPlayer[obj->work[0]].player_obj->rot.y = obj->rot.y;
            GwPlayer[obj->work[0]].player_obj->rot.z = obj->rot.z;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->rot.x = sinf(obj->scale.y * (M_PI / 180.0));
        GwPlayer[obj->work[0]].player_obj->rot.y = 0.0f;
        GwPlayer[obj->work[0]].player_obj->rot.z = cosf(obj->scale.y * (M_PI / 180.0));
    } else {
        if (obj->work[1] == 0) {
            model->rot.x = obj->rot.x;
            model->rot.y = obj->rot.y;
            model->rot.z = obj->rot.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
        model->rot.x = sinf(obj->scale.y * (M_PI / 180.0));
        model->rot.y = 0.0f;
        model->rot.z = cosf(obj->scale.y * (M_PI / 180.0));
    }
}

omObjData *func_801069B8_majinlamp(s32 player, Vec *target, s32 frames, Object *model) {
    omObjData *obj;
    Vec dir;
    f32 from;
    f32 to;
    s32 i;

    if (model == NULL) {
        MBVecDirGet(&GwPlayer[player].player_obj->coords, target, &dir);
    } else {
        MBVecDirGet(&model->coords, target, &dir);
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_801067EC_majinlamp);
    obj->work[0] = player;
    obj->work[1] = frames;
    obj->rot.x = dir.x;
    obj->rot.y = dir.y;
    obj->rot.z = dir.z;
    if (model == NULL) {
        from = MBVecAngleGet(&GwPlayer[player].player_obj->rot);
        to = MBVecAngleGet(&dir);
        if (to < from) {
            if (from - to >= 180.0f) {
                to += 360.0f;
            }
        } else if (to - from >= 180.0f) {
            from += 360.0f;
        }
    } else {
        from = MBVecAngleGet(&model->rot);
        to = MBVecAngleGet(&dir);
        if (to < from) {
            if (from - to >= 180.0f) {
                to += 360.0f;
            }
        } else if (to - from >= 180.0f) {
            from += 360.0f;
        }
    }
    obj->scale.y = from;
    obj->scale.x = (to - from) / frames;
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80106BB0_majinlamp(omObjData *obj) {
    func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "bg_in", 0);
    obj->trans.x += 1.0f;
    if (D_80108124_majinlamp != 0) {
        func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, obj->trans.y, 0x40, 0x40, "bg_out", 0);
        obj->trans.y += 1.0f;
    }
    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void func_80106D3C_majinlamp(omObjData *obj) {
    if (D_801080EC_majinlamp != 0) {
        D_8010832C_majinlamp->velocity.x = sindf(obj->rot.y) * 30.0f;
        obj->rot.y += 2.0f;
        if (obj->rot.y >= 360.0f) {
            obj->rot.y -= 360.0f;
        }
    }
    if (D_801080E8_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->velocity.x = D_801080F0_majinlamp * D_8010832C_majinlamp->scale.x + D_8010832C_majinlamp->velocity.x;
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_8010832C_majinlamp->coords);
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->scale, &D_8010832C_majinlamp->scale);
    }
    if (D_801080EA_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->rot.x = D_8010832C_majinlamp->rot.x;
        D_80108334_majinlamp->player_obj->rot.z = D_8010832C_majinlamp->rot.z;
    }
}

/* event e5: NON_MATCHING. With func_80017AD8_main returning s16 (functions.us.h says u8: one extra
   andi 0xFF) only stack offsets differ: retail lays the four Vecs over motA/motB (0x18..0x57), which
   KMC GCC does not do for sibling blocks. */
#ifdef NON_MATCHING
void func_80106E74_majinlamp(void) {
    omObjData *obj;
    void *data;
    f32 speed;
    s32 i;

    D_80108338_majinlamp = HuSprGrpCreate(1, 5);
    data = DataRead(0x1301BF);
    D_8010833A_majinlamp = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108338_majinlamp, 0, D_8010833A_majinlamp, 0);
    HuSprPriSet(D_80108338_majinlamp, 0, 10);
    func_800550F4_main(D_80108338_majinlamp, 0, 1);
    HuSprAttrSet(D_80108338_majinlamp, 0, 0x5000);
    func_80054904_main(D_80108338_majinlamp, 0, 160, 120);
    HuSprScaleSet(D_80108338_majinlamp, 0, 50.0f, 50.0f);
    D_80108334_majinlamp = MBPlayerGet(D_8010833C_majinlamp);
    MBPlayerModelCreate(D_8010833E_majinlamp, D_80101734_shared_board[GwPlayer[D_8010833C_majinlamp].chr], 2);
    {
        s32 motA[8] = { 0x200A4, 0x300A4, 0x700A4, 0x400A4, 0x500A4, 0x600A4, 0x800A4, 0x9001B };
        s32 motB[8] = { 0x200AB, 0x300AB, 0x700AB, 0x400AB, 0x500AB, 0x600AB, 0x800AB, 0x90027 };

        D_80108340_majinlamp[0] = func_80017790_main(D_80108334_majinlamp->player_obj->omObj1->model[0], 2, GwPlayer[D_8010833C_majinlamp].chr,
                                                  motA[GwPlayer[D_8010833C_majinlamp].chr]);
        D_80108340_majinlamp[1] = func_80017AD8_main(motB[GwPlayer[D_8010833C_majinlamp].chr]);
    }
    func_80017954_main(D_80108334_majinlamp->player_obj->omObj1->model[0], 2, GwPlayer[D_8010833C_majinlamp].chr, D_80108340_majinlamp[0]);
    MBPlayerMotionSet(D_8010833C_majinlamp, 4, 2);
    HuVecCopyXYZ(&D_80108334_majinlamp->player_obj->coords, 150.0f, -100.0f, 3000.0f);
    D_80108334_majinlamp->player_obj->flags |= 1;
    D_8010832C_majinlamp = MBModelCreate(0x25, NULL);
    HuVecCopyXYZ(&D_8010832C_majinlamp->coords, -150.0f, -50.0f, 3000.0f);
    obj = omAddObj(0x1000, 0, 0, -1, func_80106D3C_majinlamp);
    obj->rot.y = 0.0f;
    obj->scale.x = 0.0f;
    D_800C9930_main = func_8004A5C4_main(60);
    HuAudFXPlay(0x129);
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_800F2388_shared_board(D_8010833C_majinlamp, -1, 0, 10, 2);
    HuPrcSleep(15);
    MBDlgResultWinExec(0x3A17);
    D_801080EC_majinlamp = 0;
    speed = 20.0f;
    while (D_8010832C_majinlamp->velocity.x < 1000.0f) {
        D_8010832C_majinlamp->velocity.x += speed;
        speed += 5.0f;
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8010832C_majinlamp->coords, -1600.0f, -100.0f, 1600.0f);
    D_801080EC_majinlamp = 1;
    func_8008A120_main((f32 (*)[4])HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, 60.0f);
    D_8010832C_majinlamp->rot.x = sindf(45.0f);
    D_8010832C_majinlamp->rot.z = cosdf(45.0f);
    speed = 50.0f;
    while (D_8010832C_majinlamp->coords.x < 0.0f) {
        D_8010832C_majinlamp->coords.x += 2.0f * speed;
        D_8010832C_majinlamp->coords.z += 2.0f * speed;
        speed -= 1.6f;
        if (speed <= 5.0f) {
            speed = 5.0f;
        }
        HuPrcVSleep();
    }
    MBPlayerMotionSet(D_8010833C_majinlamp, 2, 0);
    {
        Vec pos = { 0.0f, -90.0f, 3200.0f };

        MBPlayerPosMoveCreate(&D_80108334_majinlamp->player_obj->coords, &pos, &D_80108334_majinlamp->player_obj->coords, 20);
    }
    D_80108334_majinlamp->player_obj->velocity.y = 30.0f;
    D_80108334_majinlamp->player_obj->velocity.z = -2.5f;
    HuPrcSleep(20);
    {
        Object *player = D_80108334_majinlamp->player_obj;

        player->velocity.y = player->velocity.z = 0.0f;
    }
    D_801080F0_majinlamp = D_80108334_majinlamp->player_obj->coords.y - D_8010832C_majinlamp->coords.y - 15.0f;
    D_801080E8_majinlamp = 1;
    D_801080EA_majinlamp = 1;
    MBPlayerMotionSet(D_8010833C_majinlamp, -1, 2);
    {
        Vec target = { 500.0f, 0.0f, 4000.0f };

        func_801069B8_majinlamp(D_8010833C_majinlamp, &target, 5, NULL);
    }
    HuPrcSleep(5);
    MBDlgWinExecY(-1, 0x3A18, 40);
    HuAudFXPlay(0x12B);
    {
        Vec pos = { 200.0f, 200.0f, 5000.0f };
        Vec arc = { 0.0f, 0.0f, -200.0f };

        func_801069B8_majinlamp(0, &pos, 30, D_8010832C_majinlamp);
        func_80106634_majinlamp(D_8010832C_majinlamp, &pos, 30, &arc);
    }
    speed = 60.0f;
    for (i = 0; i < 30; i++) {
        func_8008A120_main((f32 (*)[4])HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, speed);
        func_8008A120_main((f32 (*)[4])HmfModelData[D_80108334_majinlamp->player_obj->omObj1->model[0]].mtx, speed - 60.0f);
        speed -= 2.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    WipeColorSet(255, 255, 255);
    WipeCreateOut(11, 2);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(D_80108334_majinlamp->player_obj);
    MBModelDispOff(D_8010832C_majinlamp);
    func_80055458_main(D_80108338_majinlamp, 0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80106E74_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108270_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108290_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082B0_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082BC_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082C8_majinlamp);
INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082D4_majinlamp);
#endif

void func_8010771C_majinlamp(void) {
    Vec v[4]; /* [0] the previous position, [2] the path step / turn target, [3] the sway / forward */
    s16 se;
    s32 i;

    D_80108330_majinlamp = MBModelFileCreate(0x1301F6, -1, 1.0f, 0.0f, NULL);
    HuVecCopyXYZ(&D_80108330_majinlamp->scale, 2.0f, 2.0f, 2.0f);
    func_8001C954_main(D_80108330_majinlamp->omObj1->model[0]);
    func_8001C92C_main(D_80108330_majinlamp->omObj1->model[0], 0.25f);
    HuVecCopyXYZ(&D_80108330_majinlamp->scale, 4.0f, 4.0f, 4.0f);
    func_8001C8A8_main(D_80108330_majinlamp->omObj1->model[0], 2);
    omAddObj(0x1000, 0, 0, -1, func_80106BB0_majinlamp);
    D_801080D0_majinlamp = 45.0f;
    D_801080DC_majinlamp = 100.0f;
    D_801080E0_majinlamp = 10.0f;
    D_801080E4_majinlamp = 20000.0f;
    func_8008A120_main((f32 (*)[4])HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, 60.0f);
    func_8008A120_main((f32 (*)[4])HmfModelData[D_80108334_majinlamp->player_obj->omObj1->model[0]].mtx, 0.0f);
    HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_801080F4_majinlamp[0]);
    HuVecCopy3F(&D_8010832C_majinlamp->coords, &D_801080F4_majinlamp[0]);
    MBMotionSet(D_80108334_majinlamp->player_obj, -1, 2);
    MBVecForwardSet(&D_80108334_majinlamp->player_obj->rot);
    MBVecForwardSet(&D_8010832C_majinlamp->rot);
    D_801080F0_majinlamp = 0.0f;
    D_801080E8_majinlamp = 1;
    D_801080EA_majinlamp = 1;
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    se = HuAudFXPlay(0x12A);
    i = 0;
    MBModelDispOn(D_80108334_majinlamp->player_obj);
    MBModelDispOn(D_8010832C_majinlamp);
    do {
        HuVecCopy3F(&v[0], &D_80108334_majinlamp->player_obj->coords);
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_801080F4_majinlamp[0]);
        HuVecSubtract(&v[2], &D_801080F4_majinlamp[2], &D_801080F4_majinlamp[0]);
        HuVecMulScalar(&v[2], sindf(i / 2), &v[2]);
        HuVecAdd(&D_80108334_majinlamp->player_obj->coords, &v[2], &D_80108334_majinlamp->player_obj->coords);
        v[3].x = -sindf(i * 2) * (500 - i);
        v[3].y = -sindf(i * 2) * (300 - i);
        v[3].z = 0.0f;
        HuVecAdd(&D_80108334_majinlamp->player_obj->coords, &v[3], &D_80108334_majinlamp->player_obj->coords);
        MBVecDirGet(&v[0], &D_80108334_majinlamp->player_obj->coords, &D_80108334_majinlamp->player_obj->rot);
        HuVecCopy3F(&D_8010832C_majinlamp->coords, &D_80108334_majinlamp->player_obj->coords);
        HuVecCopy3F(&D_8010832C_majinlamp->rot, &D_80108334_majinlamp->player_obj->rot);
        i += 2;
        HuPrcVSleep();
    } while (i < 181);
    D_80108124_majinlamp = 1;
    D_801080EA_majinlamp = 0;
    {
        Vec *dir = &v[2];
        Vec *fwd = &v[3];

        MBVecForwardSet(fwd);
        HuVecCopy3F(dir, &D_80108334_majinlamp->player_obj->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_80108334_majinlamp->player_obj->rot, fwd, &D_80108334_majinlamp->player_obj->rot, 10));
    }
    HuPrcChildWait();
    func_80007DD8_main(se);
    func_8004ACE0_main(0x2BD, D_8010833E_majinlamp);
    func_80017954_main(D_80108334_majinlamp->player_obj->omObj1->model[0], 2, GwPlayer[D_8010833C_majinlamp].chr, D_80108340_majinlamp[1]);
    MBPlayerMotionSet(D_8010833C_majinlamp, 5, 2);
    HuPrcSleep(50);
    MBVecDirGet(&D_80108334_majinlamp->player_obj->coords, &D_80108118_majinlamp, &v[2]);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_80108334_majinlamp->player_obj->rot, &v[2], &D_80108334_majinlamp->player_obj->rot, 10));
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_8010832C_majinlamp->rot, &v[2], &D_8010832C_majinlamp->rot, 10));
    HuPrcChildWait();
    D_801080EA_majinlamp = 1;
    HuPrcSleep(10);
    HuAudFXPlay(0x12B);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_80108334_majinlamp->player_obj->coords, &D_80108118_majinlamp, &D_80108334_majinlamp->player_obj->coords, 20));
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_8010832C_majinlamp->coords, &D_80108118_majinlamp, &D_8010832C_majinlamp->coords, 20));
    HuPrcSleep(10);
    WipeColorSet(255, 255, 255);
    WipeCreateOut(11, 20);
    HuPrcChildWait();
}

void func_80107D98_majinlamp(void) {
    func_80106E74_majinlamp();
    func_8010771C_majinlamp();
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107DD8_majinlamp(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_801080C4_majinlamp();
        func_80107E64_majinlamp();
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_80107E1C_majinlamp(omObjData *obj) {
    if (D_800D530C_main != 0) {
        obj->func = func_80107DD8_majinlamp;
    }
}

void func_80107E40_majinlamp(void) {
    MBModelInit();
    func_800F26E8_shared_board();
}

void func_80107E64_majinlamp(void) {
    HuSprKill(D_8010833A_majinlamp);
    HuSprGrpKill(D_80108338_majinlamp);
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_80107EA0_majinlamp(void) {
    while (TRUE) {
        Hu3DCamSetPerspective(0, D_801080D0_majinlamp, D_801080D4_majinlamp, D_801080D8_majinlamp);
        Hu3DCamSetPositionOrientation(0, &D_801082E4_majinlamp, &D_801082F0_majinlamp, &D_801082FC_majinlamp);
        Hu3DCamUpdateMtx(0);
        Hu3DCamSetPerspective(1, D_801080DC_majinlamp, D_801080E0_majinlamp, D_801080E4_majinlamp);
        Hu3DCamSetPositionOrientation(1, &D_80108308_majinlamp, &D_80108314_majinlamp, &D_80108320_majinlamp);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

void func_80107F54_majinlamp(void) {
    Hu3DCamInit(2);
    D_801082E0_majinlamp = omAddPrcObj(func_80107EA0_majinlamp, 0x1001, 0, 0);
    omPrcSetStatBit(D_801082E0_majinlamp, 0x80);
    HuVecCopyXYZ(&D_801082E4_majinlamp, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&D_801082F0_majinlamp, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_801082FC_majinlamp, 0.0f, 1.0f, 0.0f);
    Hu3DCamSetPerspective(0, D_801080D0_majinlamp, D_801080D4_majinlamp, D_801080D8_majinlamp);
    Hu3DCamSetPositionOrientation(0, &D_801082E4_majinlamp, &D_801082F0_majinlamp, &D_801082FC_majinlamp);
    Hu3DCamUpdateMtx(0);
    HuVecCopyXYZ(&D_80108308_majinlamp, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&D_80108314_majinlamp, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_80108320_majinlamp, 0.0f, 1.0f, 0.0f);
    Hu3DCamSetPerspective(1, D_801080DC_majinlamp, D_801080E0_majinlamp, D_801080E4_majinlamp);
    Hu3DCamSetPositionOrientation(1, &D_80108308_majinlamp, &D_80108314_majinlamp, &D_80108320_majinlamp);
    Hu3DCamUpdateMtx(1);
}

void func_801080C4_majinlamp(void) {
}

